//
// Created by Jon Stephens on 3/20/22.
//

#include "../include/BlkVariable.h"


namespace blockchain {
    BlkVariable::BlkVariable(string &name, BlkType *type) {
        varName = name;
        varType = type;
    }

    BlkVariable::~BlkVariable() {
        delete varType;
    }

    string BlkVariable::name() {
        return varName;
    }
}