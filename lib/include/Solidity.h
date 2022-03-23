//
// Created by Jon Stephens on 3/20/22.
//

#ifndef LIBBLOCKCHAIN_SOLIDITY_H
#define LIBBLOCKCHAIN_SOLIDITY_H


#include "Blockchain.h"

namespace blockchain {
    class Solidity : public Blockchain {
    public:
        Solidity(string &c, string &v, vector<BlkContract *> *contracts);
        ~Solidity();
        bool allowsReentrancy() override;
        //bool isConstructor(Function &fn) override;
        //bool isExternalCall(Instruction &ins) override;
        //bool isView(Function &fn) override;
        //bool isPure(Function &fn) override;
        //bool isContractFunction(Function &fn) override;
        const vector<BlkContract *> &contracts() override;
        //BlkContract &findDeclaringContract(Function &fn) override;
    private:
        string srcCompiler;
        string srcVersion;
        vector<BlkContract *> *solContracts;
    };
}

#endif //LIBBLOCKCHAIN_SOLIDITY_H
