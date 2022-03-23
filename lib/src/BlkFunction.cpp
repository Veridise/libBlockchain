//
// Created by Jon Stephens on 3/20/22.
//

#include "../include/BlkFunction.h"

namespace blockchain {
    BlkFunction::BlkFunction(std::string &name, vector<BlkVariable *> *params, vector<BlkVariable *> *rets, vector<string> *mods) {
        fnName = name;
        fnParams = params;
        fnReturns = rets;
        fnMods = mods;
    }

    BlkFunction::~BlkFunction() {
        deleter(fnParams);
        deleter(fnReturns);
        delete fnMods;
    }

    string BlkFunction::name() {
        return fnName;
    }
}