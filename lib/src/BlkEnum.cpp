//
// Created by Jon Stephens on 3/20/22.
//

#include "../include/BlkEnum.h"

namespace blockchain {
    BlkEnum::BlkEnum(string &name, map<std::string, int> *vals) {
        enumName = name;
        values = vals;
    }

    BlkEnum::~BlkEnum() {
        delete values;
    }

    string BlkEnum::name() {
        return enumName;
    }
}