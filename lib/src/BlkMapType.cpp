//
// Created by Jon Stephens on 3/23/22.
//

#include "../include/BlkMapType.h"
#include "../include/BlkTypeVisitor.h"

namespace blockchain {
    BlkMapType::BlkMapType(BlockchainToLLVM *blk2llvm, std::string &name, BlkType *key, BlkType *val) : BlkType(blk2llvm, name) {
        keyType = key;
        keyType->parent(this);
        valueType = val;
        valueType->parent(this);
    }

    BlkMapType::~BlkMapType() {
        delete keyType;
        delete valueType;
    }

    const BlkType &BlkMapType::key() const {
        return *keyType;
    }

    const BlkType &BlkMapType::value() const {
        return *valueType;
    }

    void BlkMapType::accept(BlkTypeVisitor &v) const {
        return v.visit(*this);
    }
}