//
// Created by Jon Stephens on 4/10/22.
//

#include "Blockchain.h"
#include "BlockchainToLLVM.h"

namespace blockchain {
    Blockchain::~Blockchain() {
        deleter(allContracts);
        delete blkTollvm;
    }

    bool Blockchain::isContractFunction(const Function &fn) const {
        return findDeclaringContract(fn) != nullptr;
    }

    const vector<BlkContract *> &Blockchain::contracts() const {
        return *allContracts;
    }

    const BlkFunction *Blockchain::findFunction(const Function &fn) const {
        for(auto contract : *allContracts) {
            const BlkFunction *blkFn = contract->findFunction(fn);
            if(blkFn != nullptr) {
                return blkFn;
            }
        }

        return nullptr;
    }

    const BlkContract *Blockchain::findDeclaringContract(const Function &fn) const {
        for(auto contract : *allContracts) {
            if(contract->isContractFunction(fn)) {
                return contract;
            }
        }

        return nullptr;
    }

    bool Blockchain::isAnyExternalCall(const Function &fn) const  {
        return blkTollvm->isAnyExternalCall(fn);
    }

    bool Blockchain::isCall(const Function &fn) const {
        return blkTollvm->isCall(fn);
    }

    bool Blockchain::isStaticCall(const Function &fn) const {
        return blkTollvm->isStaticCall(fn);
    }

    bool Blockchain::isDelegateCall(const Function &fn) const {
        return blkTollvm->isDelegateCall(fn);
    }
}