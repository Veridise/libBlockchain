//
// Created by Jon Stephens on 4/10/22.
//

#include "InkToLLVM.h"
#include "BlkElementaryType.h"
#include "BlkMapType.h"
#include "BlkUserType.h"
#include "BlkArrayType.h"
#include <regex>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include "BlkTypeVisitor.h"
#include "BlkContract.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Instructions.h"
#include <iostream>
#include "llvm/IR/IntrinsicInst.h"

namespace blockchain {
    InkToLLVM::InkToLLVM(AAWrapper &alias) : alias(alias) {}

    Value *InkToLLVM::getSelfRef(const BlkFunction &blkFn, Function &fn) {
        if(InkToLLVM::isConstructorClosure(blkFn, fn)) {
            return fn.getArg(fn.arg_size() - 1);
        }

        return fn.getArg(0);
    }

    MemoryLocation getContractVarLocation(const BlkContract &contract, const BlkVariable &var, llvm::Instruction &ins) {
        Function &fn = *ins.getFunction();
        auto blkFn = contract.findFunction(fn);
        if(blkFn == nullptr) {
            throw runtime_error("Should be contract function");
        }

        auto arg = InkToLLVM::getSelfRef(*blkFn, fn);
        auto it = std::find(contract.variables().begin(), contract.variables().end(), &var);
        auto id = std::distance(contract.variables().begin(), it);

        if(!arg->getType()->isPointerTy()) {
            throw runtime_error("Should be pointer type");
        }

        auto argType = cast<PointerType>(arg->getType());
        if(!argType->getElementType()->isStructTy()) {
            throw runtime_error("Should be struct type");
        }
        auto structType = cast<StructType>(argType->getElementType());
        IntegerType *intType = IntegerType::get(ins.getContext(), 32);
        Value* indexList[2] = {ConstantInt::get(intType, 0), ConstantInt::get(intType, id)};
        auto gep = GetElementPtrInst::Create(argType->getElementType(), arg, ArrayRef<Value*>(indexList, 2), "acc");
        auto &layout = fn.getParent()->getDataLayout();
        auto elementSize = layout.getTypeSizeInBits(structType->getElementType(id));
        //cout << elementSize << endl;
        //auto loc = MemoryLocation(gep, LocationSize::precise(elementSize));
        auto loc = MemoryLocation(gep, LocationSize::precise(1));
        return loc;
    }

    bool InkToLLVM::isMemoryStore(const Instruction &ins) {
        return isa<StoreInst>(ins) || isa<MemIntrinsic>(ins);
    }

    bool InkToLLVM::isMemoryRead(const Instruction &ins) {
        return isa<LoadInst>(ins) || isa<MemTransferInst>(ins);
    }

    MemoryLocation InkToLLVM::getStoreLocation(const Instruction &ins) {
        if(auto store = dyn_cast<StoreInst>(&ins)) {
            MemoryLocation storeLoc = MemoryLocation::get(store);
            return storeLoc;
        }
        else if(auto call = dyn_cast<MemIntrinsic>(&ins)) {
            MemoryLocation storeLoc = MemoryLocation::getForDest(call);
            return storeLoc;
        }

        throw runtime_error("error");
    }

    MemoryLocation InkToLLVM::getReadLocation(const Instruction &ins) {
        if(auto load = dyn_cast<LoadInst>(&ins)) {
            MemoryLocation loadLoc = MemoryLocation::get(load);
            return loadLoc;
        }
        else if(auto call = dyn_cast<MemTransferInst>(&ins)) {
            MemoryLocation loadLoc = MemoryLocation::getForSource(call);
            return loadLoc;
        }

        throw runtime_error("error");
    }

    bool InkToLLVM::writesVariable(const BlkVariable &var, llvm::Instruction &ins) const {
        if(isMemoryStore(ins)){
            MemoryLocation storeLoc = getStoreLocation(ins);

            if(auto contract = dyn_cast<BlkContract>(var.parent())) {
                //assuming no aliasing outside of contract functions.
                Function &fn = *ins.getFunction();
                if(!contract->isContractFunction(fn)) {
                    return false;
                }

                MemoryLocation varLoc = getContractVarLocation(*contract, var, ins);
                auto aa = alias.request(fn);
                if(aa->alias(storeLoc, varLoc) > llvm::AliasResult::MayAlias) {
                    return true;
                }

                return false;
            }
            else {
                throw runtime_error("Only works for contract variables right now");
            }
        }
        if(auto call = dyn_cast<CallInst>(&ins)) {
            auto calledFn = call->getCalledFunction();
            if(isLazyStore(*calledFn)) {
                MemoryLocation loc = MemoryLocation::getBeforeOrAfter(call->getArgOperand(0));

                if (auto contract = dyn_cast<BlkContract>(var.parent())) {
                    //assuming no aliasing outside of contract functions.
                    Function &fn = *ins.getFunction();
                    if (!contract->isContractFunction(fn)) {
                        return false;
                    }

                    MemoryLocation varLoc = getContractVarLocation(*contract, var, ins);
                    auto aa = alias.request(fn);
                    if (aa->alias(loc, varLoc) > llvm::AliasResult::MayAlias) {
                        return true;
                    }

                    return false;
                } else {
                    throw runtime_error("Only works for contract variables right now");
                }
            }
        }


        return false;
    }

    bool InkToLLVM::readsVariable(const BlkVariable &var, llvm::Instruction &ins) const {
        if(isMemoryRead(ins)) {
            MemoryLocation readLoc = getReadLocation(ins);

            if(auto contract = dyn_cast<BlkContract>(var.parent())) {
                //assuming no aliasing outside of contract functions.
                Function &fn = *ins.getFunction();
                if(!contract->isContractFunction(fn)) {
                    return false;
                }

                MemoryLocation varLoc = getContractVarLocation(*contract, var, ins);
                auto aa = alias.request(fn);
                if(aa->alias(readLoc, varLoc) > llvm::AliasResult::MayAlias) {
                    return true;
                }

                return false;
            }
            else {
                throw runtime_error("Only works for contract variables right now");
            }
        }
        if(auto call = dyn_cast<CallInst>(&ins)) {
            auto calledFn = call->getCalledFunction();
            if(isLazyGet(*calledFn)) {
                MemoryLocation loc = MemoryLocation::getBeforeOrAfter(call->getArgOperand(0));

                if (auto contract = dyn_cast<BlkContract>(var.parent())) {
                    //assuming no aliasing outside of contract functions.
                    Function &fn = *ins.getFunction();
                    if (!contract->isContractFunction(fn)) {
                        return false;
                    }

                    MemoryLocation varLoc = getContractVarLocation(*contract, var, ins);
                    auto aa = alias.request(fn);
                    if (aa->alias(loc, varLoc) > llvm::AliasResult::MayAlias) {
                        return true;
                    }

                    return false;
                } else {
                    throw runtime_error("Only works for contract variables right now");
                }
            }
        }

        return false;
    }

    bool InkToLLVM::isSelfDestruct(const llvm::Function &fn) {
        if(!fn.hasName()) {
            return false;
        }

        string fnName = fn.getName().str();

        stringstream ss;
        ss << ".*ink_lang.*env_access.*EnvAccess.*terminate_contract[a-hA-F0-9]{20}$";

        std::regex reg(ss.str());
        return regex_match(fnName, reg);
    }

    bool InkToLLVM::isMsgSender(const llvm::Function &fn) {
        //_ZN8ink_lang10env_access18EnvAccess$LT$E$GT$6caller17h56520365e2893a15E
        if(!fn.hasName()) {
            return false;
        }

        string fnName = fn.getName().str();

        stringstream ss;
        ss << ".*ink_lang.*env_access.*EnvAccess.*caller[a-hA-F0-9]{20}$";

        std::regex reg(ss.str());
        return regex_match(fnName, reg);
    }

    bool InkToLLVM::isMsgValue(const llvm::Function &fn) {
        //ink_lang10env_access18EnvAccess$LT$E$GT$17transferred_value
        if(!fn.hasName()) {
            return false;
        }

        string fnName = fn.getName().str();

        stringstream ss;
        ss << ".*ink_lang.*env_access.*EnvAccess.*transferred_value[a-hA-F0-9]{20}$";

        std::regex reg(ss.str());
        return regex_match(fnName, reg);
    }

    bool InkToLLVM::isLazyGet(const llvm::Function &fn) {
        if(!fn.hasName()) {
            return false;
        }

        string fnName = fn.getName().str();

        stringstream ss;
        ss << ".*ink_storage.*lazy.*Mapping.*get[a-hA-F0-9]{20}$";

        std::regex reg(ss.str());
        return regex_match(fnName, reg);
    }

    bool InkToLLVM::isLazyStore(const llvm::Function &fn) {
        if(!fn.hasName()) {
            return false;
        }

        string fnName = fn.getName().str();

        stringstream ss;
        ss << ".*ink_storage.*lazy.*Mapping.*insert[a-hA-F0-9]{20}$";

        std::regex reg(ss.str());
        return regex_match(fnName, reg);
    }

    bool InkToLLVM::isConstructorClosure(const BlkFunction &blockchainFn, const llvm::Function &llvmFn) {
        stringstream ss;
        ss << ".*\\.\\." << blockchainFn.parent()->name() << ".*" << blockchainFn.name() << ".*closure.*";
        std::regex reg(ss.str());
        string name = llvmFn.getName().str();
        return regex_match(llvmFn.getName().str(), reg);
    }

    bool InkToLLVM::isTranslation(const BlkFunction &blockchainFn, const llvm::Function &llvmFn) const {
        if(!llvmFn.hasName()) {
            return false;
        }

        if(blockchainFn.isConstructor() && isConstructorClosure(blockchainFn, llvmFn)) {
            return true;
        }

        stringstream ss;
        ss << ".*\\.\\." << blockchainFn.parent()->name() << ".*" << blockchainFn.name() << "[a-hA-F0-9]{20}$";

        std::regex reg(ss.str());
        string name = llvmFn.getName().str();
        return regex_match(llvmFn.getName().str(), reg);
    }

    bool InkToLLVM::isAnyExternalCall(const llvm::Function &fn) const {
        return isCall(fn) || isStaticCall(fn) || isDelegateCall(fn);
    }

    bool InkToLLVM::isCall(const llvm::Function &fn) const {
        if(!fn.hasName()) {
            return false;
        }

        //call::call_builder::CallBuilder
        stringstream ss;
        ss << ".*CallBuilder.*ink_env..call..call_builder..Call.*fire[a-hA-F0-9]{20}$";

        std::regex reg(ss.str());
        return regex_match(fn.getName().str(), reg);
    }

    bool InkToLLVM::isStaticCall(const llvm::Function &fn) const {
        if(!fn.hasName()) {
            return false;
        }

        return false;
    }

    bool InkToLLVM::isDelegateCall(const llvm::Function &fn) const {
        if(!fn.hasName()) {
            return false;
        }

        stringstream ss;
        ss << ".*CallBuilder.*ink_env..call..call_builder..DelegateCall.*fire[a-hA-F0-9]{20}$";

        std::regex reg(ss.str());
        return regex_match(fn.getName().str(), reg);
    }
}