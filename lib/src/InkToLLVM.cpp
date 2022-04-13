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

namespace blockchain {
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

    bool InkToLLVM::isTranslation(const BlkFunction &blockchainFn, const llvm::Function &llvmFn) const {
        if(!llvmFn.hasName()) {
            return false;
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