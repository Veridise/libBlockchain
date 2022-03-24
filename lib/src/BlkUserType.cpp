//
// Created by Jon Stephens on 3/23/22.
//

#include "../include/BlkUserType.h"
#include "../include/BlkTypeVisitor.h"

namespace blockchain {
    BlkUserType::BlkUserType(BlockchainToLLVM *blk2llvm, std::string &name, BlkStorage *referenced) : BlkType(blk2llvm, name) {
        ref = referenced;
    }

    //Do not delete ref!
    BlkUserType::~BlkUserType() = default;

    void BlkUserType::setReferenced(BlkStorage *referenced) {
        if(referenced == nullptr) {
            ref = referenced;
        }
    }

    void BlkUserType::accept(BlkTypeVisitor &v) const {
        return v.visit(*this);
    }
}