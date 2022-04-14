//
// Created by Jon Stephens on 3/20/22.
//

#ifndef LIBBLOCKCHAIN_BLKVARIABLE_H
#define LIBBLOCKCHAIN_BLKVARIABLE_H

#include <string>
#include <llvm/IR/Instruction.h>
#include "BlkType.h"

using namespace std;

namespace blockchain {
    class BlkVariable : public BlkNode {
    public:
        BlkVariable(BlockchainToLLVM *blk2llvm, string &name, BlkType *type);
        ~BlkVariable();

        static inline bool classof(const BlkVariable &) { return true; }
        static inline bool classof(const BlkVariable *) { return true; }
        static inline bool classof(const BlkNode *node) { return classof(*node); }
        static inline bool classof(const BlkNode &node) {
            if(node.type() == VARIABLE) { return true; }
            return false;
        }

        const BlkType &varType() const;
        bool writtenBy(llvm::Instruction &ins) const;
        bool readBy(llvm::Instruction &ins) const;
    private:
        BlkType *varTy;
    };
}



#endif //LIBBLOCKCHAIN_BLKVARIABLE_H
