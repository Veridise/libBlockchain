//
// Created by Jon Stephens on 3/23/22.
//

#include "../include/BlkMapType.h"

namespace blockchain {
    BlkMapType::BlkMapType(BlkType *key, BlkType *val) {
        keyType = key;
        valueType = val;
    }

    BlkMapType::~BlkMapType() {
        delete keyType;
        delete valueType;
    }
}