//
// Created by Jon Stephens on 3/20/22.
//

#include "../include/BlkVariable.h"
#include "BlockchainToLLVM.h"


namespace blockchain {
    BlkVariable::BlkVariable(BlockchainToLLVM *blk2llvm, string &name, BlkType *type) : BlkNode(VARIABLE, blk2llvm, name), varTy(type) {
        type->parent(this);
    }

    BlkVariable::~BlkVariable() {
        delete varTy;
    }

    const BlkType &BlkVariable::varType() const {
        return *varTy;
    }

    bool BlkVariable::modifiedBy(llvm::Instruction &ins) const {
        return blkTollvm->modifiesVariable(*this, ins);
    }
    bool BlkVariable::readBy(llvm::Instruction &ins) const {
        return blkTollvm->readsVariable(*this, ins);
    }
}