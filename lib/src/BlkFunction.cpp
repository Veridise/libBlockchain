//
// Created by Jon Stephens on 3/20/22.
//

#include "../include/BlkFunction.h"
#include "../include/BlockchainToLLVM.h"

namespace blockchain {
    BlkFunction::BlkFunction(BlockchainToLLVM *blk2llvm, std::string &name, bool isCnstr, vector<BlkVariable *> *params,
                             vector<BlkVariable *> *rets, vector<string> *mods) : BlkNode(blk2llvm, name){
        fnIsConstructor = isCnstr;
        fnParams = params;
        registerParent(fnParams);
        fnReturns = rets;
        registerParent(fnReturns);
        fnMods = mods;
    }

    BlkFunction::~BlkFunction() {
        deleter(fnParams);
        deleter(fnReturns);
        delete fnMods;
    }

    bool BlkFunction::isConstructor() const {
        return fnIsConstructor;
    }

    const vector<BlkVariable *> &BlkFunction::parameters() const {
        return *fnParams;
    }

    const vector<std::string> &BlkFunction::modifiers() const {
        return *fnMods;
    }

    bool BlkFunction::isTranslation(const llvm::Function &fn) const {
        return blkTollvm->isTranslation(*this, fn);
    }
}