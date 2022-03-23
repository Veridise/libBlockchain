//
// Created by Jon Stephens on 3/23/22.
//

#include "../include/BlkArrayType.h"

namespace blockchain {
    BlkArrayType::BlkArrayType(BlkType *base) {
        baseType = base;
    }

    BlkType &BlkArrayType::base() {
        return *baseType;
    }

    BlkArrayType::~BlkArrayType() {
        delete baseType;
    }
}