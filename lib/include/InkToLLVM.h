//
// Created by Jon Stephens on 4/10/22.
//

#ifndef LIBBLOCKCHAIN_INKTOLLVM_H
#define LIBBLOCKCHAIN_INKTOLLVM_H

#include "BlockchainToLLVM.h"

namespace blockchain {
    class InkToLLVM : public BlockchainToLLVM {
    public:
        bool isTranslation(const BlkFunction &blockchainFn, const llvm::Function &llvmFn) const override;
        bool isAnyExternalCall(const llvm::Function &llvmFn) const override;
        bool isCall(const llvm::Function &llvmFn) const override;
        bool isStaticCall(const llvm::Function &llvmFn) const override;
        bool isDelegateCall(const llvm::Function &llvmFn) const override;
        static bool isLazyStore(const llvm::Function &llvmFn);
        static bool isMsgSender(const llvm::Function &llvmFn);
        static bool isMsgValue(const llvm::Function &llvmFn);
        static bool isSelfDestruct(const llvm::Function &llvmFn);
    };
}


#endif //LIBBLOCKCHAIN_INKTOLLVM_H
