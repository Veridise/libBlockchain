//
// Created by Jon Stephens on 3/23/22.
//

#include "../include/BlkArrayType.h"
#include "../include/BlkTypeVisitor.h"

namespace blockchain {
    BlkArrayType::BlkArrayType(BlockchainToLLVM *blk2llvm, std::string &name, BlkType *base) : BlkType(blk2llvm, name) {
        baseType = base;
        baseType->parent(this);
    }

    const BlkType &BlkArrayType::base() const {
        return *baseType;
    }

    void BlkArrayType::accept(BlkTypeVisitor &v) const {
        return v.visit(*this);
    }

    BlkArrayType::~BlkArrayType() {
        delete baseType;
    }
}