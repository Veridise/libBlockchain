//
// Created by Jon Stephens on 4/10/22.
//

#ifndef LIBBLOCKCHAIN_INKTOLLVM_H
#define LIBBLOCKCHAIN_INKTOLLVM_H

#include "BlockchainToLLVM.h"
#include <AAWrapper.h>
#include "llvm/Analysis/MemoryLocation.h"

namespace blockchain {
    class InkToLLVM : public BlockchainToLLVM {
    public:
        explicit InkToLLVM(AAWrapper &alias);
        bool isTranslation(const BlkFunction &blockchainFn, const llvm::Function &llvmFn) const override;
        bool isAnyExternalCall(const llvm::Function &llvmFn) const override;
        bool isCall(const llvm::Function &llvmFn) const override;
        bool isStaticCall(const llvm::Function &llvmFn) const override;
        bool isDelegateCall(const llvm::Function &llvmFn) const override;
        bool writesVariable(const BlkVariable &var, llvm::Instruction &ins) const override;
        bool readsVariable(const BlkVariable &var, llvm::Instruction &ins) const override;

        static bool isLazyGet(const llvm::Function &llvmFn);
        static bool isLazyStore(const llvm::Function &llvmFn);
        static bool isMsgSender(const llvm::Function &llvmFn);
        static bool isMsgValue(const llvm::Function &llvmFn);
        static bool isSelfDestruct(const llvm::Function &llvmFn);
        static bool isMemoryStore(const llvm::Instruction &ins);
        static bool isMemoryRead(const llvm::Instruction &ins);
        static llvm::MemoryLocation getStoreLocation(const llvm::Instruction &ins);
        static llvm::MemoryLocation getReadLocation(const llvm::Instruction &ins);

    private:
        AAWrapper &alias;
    };
}


#endif //LIBBLOCKCHAIN_INKTOLLVM_H
