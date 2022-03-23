//
// Created by Jon Stephens on 3/23/22.
//

#include "../include/BlkElementaryType.h"
namespace blockchain {
    BlkElementaryType::BlkElementaryType(std::string &name) {
        typeName = name;
    }

    BlkElementaryType::~BlkElementaryType() = default;
}