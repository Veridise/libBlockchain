//
// Created by Jon Stephens on 3/20/22.
//

#include "../include/BlkFunction.h"

namespace blockchain {
    BlkFunction::BlkFunction() {

    }

    BlkFunction::~BlkFunction() {
        if(fnParams != nullptr) {
            delete fnParams;
        }
    }

    string BlkFunction::name() {
        return fnName;
    }
}