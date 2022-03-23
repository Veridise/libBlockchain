//
// Created by Jon Stephens on 3/20/22.
//

#include "../include/BlkContract.h"

namespace blockchain {
    BlkContract::BlkContract(string &name, vector<BlkFunction *> *fns, vector<BlkVariable *> *vars, vector<BlkUserType *> *inherits,
            vector<BlkEnum *> *enums, vector<BlkStruct *> *structs, vector<BlkFunction *> *events) {
        contractName = name;
        contractFns = fns;
        contractVars = vars;
        contractInherits = inherits;
        contractEnums = enums;
        contractStructs = structs;
        contractEvents = events;
    }

    BlkContract::~BlkContract() {
        deleter(contractInherits);
        deleter(contractEvents);
        deleter(contractEnums);
        deleter(contractStructs);
        deleter(contractVars);
        deleter(contractFns);
    }

    string BlkContract::name() {
        return contractName;
    }
}