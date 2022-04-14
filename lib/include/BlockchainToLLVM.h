//
// Created by Jon Stephens on 3/23/22.
//

#ifndef LIBBLOCKCHAIN_BLOCKCHAINTOLLVM_H
#define LIBBLOCKCHAIN_BLOCKCHAINTOLLVM_H

#include "BlkFunction.h"
#include "llvm/IR/Function.h"

namespace blockchain {
    class BlockchainToLLVM {
        public:
            virtual ~BlockchainToLLVM() = default;
            virtual bool isTranslation(const BlkFunction &blockchainFn, const llvm::Function &llvmFn) const = 0;
            //virtual bool isExternalCall(const llvm::Function &llvmFn) = 0;
            //virtual bool isDelegateCall(const llvm::Function &llvmFn) = 0;
            virtual bool isAnyExternalCall(const llvm::Function &llvmFn) const = 0;
            virtual bool isCall(const llvm::Function &llvmFn) const = 0;
            virtual bool isStaticCall(const llvm::Function &llvmFn) const = 0;
            virtual bool isDelegateCall(const llvm::Function &llvmFn) const = 0;

            virtual bool writesVariable(const BlkVariable &var, llvm::Instruction &ins) const = 0;
            virtual bool readsVariable(const BlkVariable &var, llvm::Instruction &ins) const = 0;
        private:
    };
}



#endif //LIBBLOCKCHAIN_BLOCKCHAINTOLLVM_H
