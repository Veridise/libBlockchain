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