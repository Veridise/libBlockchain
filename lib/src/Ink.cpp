//
// Created by Jon Stephens on 4/10/22.
//

#include "Ink.h"
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Instruction.h>
#include <llvm/Analysis/MemoryLocation.h>
#include "InkToLLVM.h"

namespace blockchain {
    Ink::Ink(BlockchainToLLVM *blk2llvm, string &c, string &v, vector<BlkContract *> *contracts, AAWrapper &alias) : Blockchain(INK, blk2llvm, c, v, contracts), alias(alias) {}

    bool Ink::allowsReentrancy() const {
        return true;
    }

    bool Ink::modifiesStorage(Instruction &ins) const {
        auto fn = ins.getFunction();
        if(!isContractFunction(*fn)) {
            return false;
        }

        if(fn->arg_size() < 1) {
            throw runtime_error("Expected there to be at least one input to " + fn->getName().str());
        }

        Argument *selfArg = fn->getArg(0);
        MemoryLocation selfLoc = MemoryLocation::getAfter(selfArg);

        if(InkToLLVM::isMemoryStore(ins)) {
            MemoryLocation storeLoc = InkToLLVM::getStoreLocation(ins);

            llvm::AAResults *aa = alias.request(*fn);
            if(aa->alias(selfLoc, storeLoc)) {
                return true;
            }
        }

        if(auto call = dyn_cast<CallInst>(&ins)) {
            //Can only store contract variables
            if(InkToLLVM::isLazyStore(*call->getCalledFunction())) {
                return true;
            }
        }

        return false;
    }

    bool Ink::readsStorage(Instruction &ins) const {
        auto fn = ins.getFunction();
        if(!isContractFunction(*fn)) {
            return false;
        }

        if(fn->arg_size() < 1) {
            throw runtime_error("Expected there to be at least one input to " + fn->getName().str());
        }

        Argument *selfArg = fn->getArg(0);
        MemoryLocation selfLoc = MemoryLocation::getAfter(selfArg);

        if(InkToLLVM::isMemoryRead(ins)) {
            MemoryLocation readLoc = InkToLLVM::getReadLocation(ins);

            llvm::AAResults *aa = alias.request(*fn);
            if(aa->alias(selfLoc, readLoc)) {
                return true;
            }
        }

        if(auto call = dyn_cast<CallInst>(&ins)) {
            //Can only store contract variables
            if(InkToLLVM::isLazyGet(*call->getCalledFunction())) {
                return true;
            }
        }

        return false;
    }

    bool Ink::getsSender(const Instruction &ins) const {
        if(auto call = dyn_cast<CallInst>(&ins)) {
            auto fn = call->getCalledFunction();
            if(InkToLLVM::isMsgSender(*fn)) {
                return true;
            }
        }

        return false;
    }

    bool Ink::getsValue(const Instruction &ins) const {
        if(auto call = dyn_cast<CallInst>(&ins)) {
            auto fn = call->getCalledFunction();
            if(InkToLLVM::isMsgValue(*fn)) {
                return true;
            }
        }

        return false;
    }

    bool Ink::isSelfDestruct(const Instruction &ins) const {
        if(auto call = dyn_cast<CallInst>(&ins)) {
            auto fn = call->getCalledFunction();
            if(InkToLLVM::isSelfDestruct(*fn)) {
                return true;
            }
        }

        return false;
    }
}