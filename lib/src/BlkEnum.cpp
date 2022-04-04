//
// Created by Jon Stephens on 3/20/22.
//

#include "../include/BlkEnum.h"

namespace blockchain {
    BlkEnum::BlkEnum(BlockchainToLLVM *blk2llvm, string &name, map<std::string, int> *vals) : BlkStorage(ENUM, blk2llvm, name) {
        values = vals;
    }

    BlkEnum::~BlkEnum() {
        delete values;
    }
}