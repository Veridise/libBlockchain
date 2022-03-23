//
// Created by Jon Stephens on 3/23/22.
//

#include "../include/BlkUserType.h"

namespace blockchain {
    BlkUserType::BlkUserType(std::string &name, BlkStorage *referenced) {
        typeName = name;
        ref = referenced;
    }

    //Do not delete ref!
    BlkUserType::~BlkUserType() = default;

    void BlkUserType::setReferenced(BlkStorage *referenced) {
        if(referenced == nullptr) {
            ref = referenced;
        }
    }

    std::string BlkUserType::name() {
        return typeName;
    }
}