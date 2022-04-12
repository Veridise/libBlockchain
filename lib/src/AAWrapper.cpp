//
// Created by Jon Stephens on 4/11/22.
//

#include "AAWrapper.h"
#include "llvm/Analysis/AliasAnalysis.h"

namespace blockchain {
    AAWrapper::AAWrapper(llvm::Pass &pass) : pass(pass), curFn(nullptr), fnAlias(nullptr) {}

    llvm::AAResults *AAWrapper::request(llvm::Function &reqFn) {
        if(noAlias(reqFn)) {
            return nullptr;
        }

        if(curFn == &reqFn) {
            return fnAlias;
        }

        curFn = &reqFn;
        fnAlias = &pass.getAnalysis<llvm::AAResultsWrapperPass>(*curFn).getAAResults();

        return fnAlias;
    }

    bool AAWrapper::noAlias(llvm::Function &fn) {
        return fn.isDeclaration();
    }
}