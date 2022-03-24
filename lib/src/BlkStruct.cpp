//
// Created by Jon Stephens on 3/20/22.
//

#include "../include/BlkStruct.h"

namespace blockchain {
    BlkStruct::BlkStruct(BlockchainToLLVM *blk2llvm, string &name, vector<BlkVariable *> *fields) : BlkStorage (blk2llvm, name) {
        structFields = fields;
        registerParent(structFields);
    }

    BlkStruct::~BlkStruct() {
        deleter(structFields);
    }
}