//
// Created by Jon Stephens on 3/23/22.
//

#include "../include/SolangToLLVM.h"
#include "llvm/IR/Instructions.h"
#include "BlkElementaryType.h"
#include "BlkMapType.h"
#include "BlkUserType.h"
#include "BlkArrayType.h"
#include <regex>
#include <sstream>
#include <stdexcept>
#include "BlkTypeVisitor.h"

using namespace llvm;

namespace blockchain {
    class TypeTrans : public BlkTypeVisitor {
    public:
        string result;
        void visit(const BlkArrayType &t) override {
            t.base().accept(*this);
            result += ":";
        }

        void visit(const BlkMapType &t) override {
            t.key().accept(*this);
            string keyType = result;
            result = "";
            t.value().accept(*this);
            string valType = result;

            stringstream namestream;
            namestream << "mapping:"
                       << keyType << ":"
                       << valType;
            result = namestream.str();
        }

        void visit(const BlkUserType &t) override {
            result = t.name().substr(t.name().find_last_of(' ') + 1,  t.name().length());
        }

        void visit(const BlkElementaryType &t) override {
            result = t.name();
        }
    };


    string getTypeString(const BlkType &type) {
        TypeTrans trans;
        type.accept(trans);
        return trans.result;
    }

    bool SolangToLLVM::isTranslation(const BlkFunction &blockchainFn, const llvm::Function &llvmFn) const {
        if(!llvmFn.hasName()) {
            return false;
        }

        stringstream ss;
        ss << ".*" << blockchainFn.parent()->name() << "::function::" << blockchainFn.name() ;

        if(blockchainFn.isConstructor()) {
            ss << ".*";
        }
        else {
            if(!blockchainFn.parameters().empty() || !blockchainFn.modifiers().empty()) {
                ss << "__";
            }

            for(auto var : blockchainFn.parameters()) {
                ss << getTypeString(var->varType()) << ".*";
            }

            for(auto &modifier : blockchainFn.modifiers()) {
                ss << modifier << ".*";
            }

            ss << "$";
        }

        std::regex reg(ss.str());
        return regex_match(llvmFn.getName().str(), reg);
    }

    bool SolangToLLVM::isAnyExternalCall(const llvm::Function &fn) const {
        return isCall(fn) || isStaticCall(fn) || isDelegateCall(fn);
    }

    bool SolangToLLVM::isCall(const llvm::Function &fn) const {
        if(!fn.hasName()) {
            return false;
        }

        return fn.getName().str() == "call";
    }

    bool SolangToLLVM::isStaticCall(const llvm::Function &fn) const {
        if(!fn.hasName()) {
            return false;
        }

        return fn.getName().str() == "callStatic";
    }

    bool SolangToLLVM::isDelegateCall(const llvm::Function &fn) const {
        if(!fn.hasName()) {
            return false;
        }

        return fn.getName().str() == "callDelegate";
    }

    bool SolangToLLVM::modifiesVariable(const BlkVariable &var, llvm::Instruction &ins) const {
        if(auto call = dyn_cast<CallInst>(&ins)) {
            auto fn = call->getCalledFunction();
            if(fn->hasName() && fn->getName().str() == ("v__set_" + var.name())) {
                return true;
            }
        }

        return false;
    }

    bool SolangToLLVM::readsVariable(const BlkVariable &var, llvm::Instruction &ins) const {
        if(auto call = dyn_cast<CallInst>(&ins)) {
            auto fn = call->getCalledFunction();
            if(fn->hasName() && fn->getName().str() == ("v__get_" + var.name())) {
                return true;
            }
        }

        return false;
    }

    bool SolangToLLVM::modifiesStorage(const llvm::Function &fn) {
        if(!fn.hasName()) {
            return false;
        }

        string fnName = fn.getName().str();

        stringstream ss;
        ss << "^v__set_";

        std::regex reg(ss.str());
        return regex_match(fnName, reg);
    }

    bool SolangToLLVM::fetchesStorage(const llvm::Function &fn) {
        if(!fn.hasName()) {
            return false;
        }

        string fnName = fn.getName().str();

        stringstream ss;
        ss << "^v__get_";

        std::regex reg(ss.str());
        return regex_match(fnName, reg);
    }
}