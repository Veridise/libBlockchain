//
// Created by Jon Stephens on 3/23/22.
//

#include "../include/BlkElementaryType.h"
#include "../include/BlkTypeVisitor.h"

namespace blockchain {
    BlkElementaryType::BlkElementaryType(BlockchainToLLVM *blk2llvm, std::string &name) : BlkType(blk2llvm, name) {}

    BlkElementaryType::~BlkElementaryType() = default;

    void BlkElementaryType::accept(BlkTypeVisitor &v) const {
        return v.visit(*this);
    }
}