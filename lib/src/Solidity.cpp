//
// Created by Jon Stephens on 3/20/22.
//

#include "../include/Blockchain.h"
#include "../include/Solidity.h"
#include "../include/BlockchainToLLVM.h"


namespace blockchain {
    Solidity::Solidity(BlockchainToLLVM *blk2llvm, string &c, string &v, vector<BlkContract *> *contracts) : Blockchain(SOLIDITY, blk2llvm, c) {
        srcVersion = v;
        solContracts = contracts;
    }

    Solidity::~Solidity() {
        deleter(solContracts);
        delete blkTollvm;
    }

    bool Solidity::allowsReentrancy() const {
        return true;
    }

    bool Solidity::isContractFunction(const Function &fn) const {
        return findDeclaringContract(fn) != nullptr;
    }

    const vector<BlkContract *> &Solidity::contracts() const {
        return *solContracts;
    }

    const BlkFunction *Solidity::findFunction(const Function &fn) const {
        for(auto contract : *solContracts) {
            const BlkFunction *blkFn = contract->findFunction(fn);
            if(blkFn != nullptr) {
                return blkFn;
            }
        }

        return nullptr;
    }

    const BlkContract *Solidity::findDeclaringContract(const Function &fn) const {
        for(auto contract : *solContracts) {
            if(contract->isContractFunction(fn)) {
                return contract;
            }
        }

        return nullptr;
    }

    bool Solidity::isAnyExternalCall(const Function &fn) const  {
        return blkTollvm->isAnyExternalCall(fn);
    }

    bool Solidity::isCall(const Function &fn) const {
        return blkTollvm->isCall(fn);
    }

    bool Solidity::isStaticCall(const Function &fn) const {
        return blkTollvm->isStaticCall(fn);
    }

    bool Solidity::isDelegateCall(const Function &fn) const {
        return blkTollvm->isDelegateCall(fn);
    }

    /*bool Solidity::isConstructor(Function &fn) {
        BlkContract &contract = findDeclaringContract(fn);
        return contract.isConstructor(fn);
    }

    bool Solidity::isContractFunction(Function &fn) {
        BlkContract &contract = findDeclaringContract(fn);
        return contract.isContractFunction(fn);
    }

    bool Solidity::isView(Function &fn) {
        BlkContract &contract = findDeclaringContract(fn);
        return contract.isView(fn);
    }

    bool Solidity::isPure(Function &fn) {
        BlkContract &contract = findDeclaringContract(fn);
        return contract.isPure(fn);
    }*/
}