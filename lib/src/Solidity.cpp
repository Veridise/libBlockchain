//
// Created by Jon Stephens on 3/20/22.
//

#include "../include/Blockchain.h"
#include "../include/Solidity.h"


namespace blockchain {
    Solidity::Solidity(string &c, string &v, vector<BlkContract *> *contracts) {
        srcCompiler = c;
        srcVersion = v;
        solContracts = contracts;
    }

    Solidity::~Solidity() {
        if(solContracts != nullptr) {
            for(auto c : *solContracts) {
                delete c;
            }
            solContracts->clear();
        }
        delete solContracts;
    }

    bool Solidity::allowsReentrancy() {
        return true;
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

    const vector<BlkContract *> &Solidity::contracts() {
        return *solContracts;
    }
}