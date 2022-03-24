//
// Created by Jon Stephens on 3/23/22.
//

#ifndef LIBBLOCKCHAIN_SOLANGTOLLVM_H
#define LIBBLOCKCHAIN_SOLANGTOLLVM_H

#include "BlockchainToLLVM.h"
#include "llvm/IR/Function.h"

namespace blockchain {
    class SolangToLLVM : public BlockchainToLLVM {
    public:
        bool isTranslation(const BlkFunction &blockchainFn, const llvm::Function &llvmFn) const override;
        //bool isExternalCall(const llvm::Function &llvmFn) override;
        //bool isDelegateCall(const llvm::Function &llvmFn) override;
        bool isAnyExternalCall(const llvm::Function &llvmFn) const override;
        bool isCall(const llvm::Function &llvmFn) const override;
        bool isStaticCall(const llvm::Function &llvmFn) const override;
        bool isDelegateCall(const llvm::Function &llvmFn) const override;

    private:
    };
}



#endif //LIBBLOCKCHAIN_SOLANGTOLLVM_H
