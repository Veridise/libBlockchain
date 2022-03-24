//
// Created by Jon Stephens on 3/20/22.
//

#include "../include/BlkVariable.h"


namespace blockchain {
    BlkVariable::BlkVariable(BlockchainToLLVM *blk2llvm, string &name, BlkType *type) : BlkNode(blk2llvm, name) {
        varType = type;
        type->parent(this);
    }

    BlkVariable::~BlkVariable() {
        delete varType;
    }

    const BlkType &BlkVariable::type() const {
        return *varType;
    }
}