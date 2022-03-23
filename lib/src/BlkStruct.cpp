//
// Created by Jon Stephens on 3/20/22.
//

#include "../include/BlkStruct.h"

namespace blockchain {
    BlkStruct::BlkStruct(string &name, vector<BlkVariable *> *fields) {
        structName = name;
        structFields = fields;
    }

    BlkStruct::~BlkStruct() {
        deleter(structFields);
    }

    string BlkStruct::name() {
        return structName;
    }
}