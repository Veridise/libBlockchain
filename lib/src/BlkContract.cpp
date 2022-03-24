//
// Created by Jon Stephens on 3/20/22.
//

#include "../include/BlkContract.h"
#include "../include/BlockchainToLLVM.h"

namespace blockchain {
    BlkContract::BlkContract(BlockchainToLLVM *blk2llvm, string &name, vector<BlkFunction *> *fns, vector<BlkVariable *> *vars, vector<BlkUserType *> *inherits,
            vector<BlkEnum *> *enums, vector<BlkStruct *> *structs, vector<BlkFunction *> *events) : BlkStorage(blk2llvm, name) {
        contractFns = fns;
        registerParent(contractFns);
        contractVars = vars;
        registerParent(contractVars);
        contractInherits = inherits;
        registerParent(contractInherits);
        contractEnums = enums;
        registerParent(contractEnums);
        contractStructs = structs;
        registerParent(contractStructs);
        contractEvents = events;
        registerParent(contractEvents);
    }

    BlkContract::~BlkContract() {
        deleter(contractInherits);
        deleter(contractEvents);
        deleter(contractEnums);
        deleter(contractStructs);
        deleter(contractVars);
        deleter(contractFns);
    }

    bool BlkContract::isContractFunction(const Function &fn) const {
        return findFunction(fn) != nullptr;
    }

    const BlkFunction *BlkContract::findFunction(const Function &fn) const {
        for(auto blkFn : *contractFns) {
            if(blkFn->isTranslation(fn)) {
                return blkFn;
            }
        }

        return nullptr;
    }

    const vector<BlkFunction *> &BlkContract::functions() const {
        return *contractFns;
    }
}