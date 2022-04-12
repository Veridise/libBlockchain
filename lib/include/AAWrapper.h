//
// Created by Jon Stephens on 4/11/22.
//

#ifndef LIBBLOCKCHAIN_AAWRAPPER_H
#define LIBBLOCKCHAIN_AAWRAPPER_H

#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Pass.h"

namespace blockchain {
    class AAWrapper {
    public:
        AAWrapper(llvm::Pass &pass);
        llvm::AAResults *request(llvm::Function &reqFn);
        bool noAlias(llvm::Function &fn);
    private:
        llvm::Pass &pass;
        llvm::Function *curFn;
        llvm::AAResults *fnAlias;
    };
}

#endif //LIBBLOCKCHAIN_AAWRAPPER_H
