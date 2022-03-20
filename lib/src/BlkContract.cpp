//
// Created by Jon Stephens on 3/20/22.
//

#include "../include/BlkContract.h"

namespace blockchain {
    BlkContract::BlkContract() {

    }

    BlkContract::~BlkContract() {
        if(contractEnums != nullptr) {
            delete contractEnums;
        }

        if(contractFns != nullptr) {
            delete contractFns;
        }

        if(contractStructs != nullptr) {
            delete contractStructs;
        }

        if(contractVars != nullptr) {
            delete contractVars;
        }
    }

    string BlkContract::name() {
        return contractName;
    }

    bool BlkContract::isConstructor(Function &fn) {

    }
}