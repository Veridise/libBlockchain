//
// Created by Jon Stephens on 3/20/22.
//

#ifndef LIBBLOCKCHAIN_SOLIDITY_H
#define LIBBLOCKCHAIN_SOLIDITY_H


#include "Blockchain.h"

namespace blockchain {
    class Solidity : public Blockchain {
    public:
        Solidity(BlockchainToLLVM *blk2llvm, string &c, string &v, vector<BlkContract *> *contracts);
        ~Solidity();

        static inline bool classof(const Solidity &) { return true; }
        static inline bool classof(const Solidity *) { return true; }
        static inline bool classof(const BlkNode *node) { return classof(*node); }
        static inline bool classof(const BlkNode &node) {
            if(node.type() == SOLIDITY) { return true; }
            return false;
        }

        bool allowsReentrancy() const override;
        //virtual bool isConstructor(Function &fn) = 0;
        //bool isExternalCall(Instruction &ins) const override;
        //virtual bool isView(Function &fn) = 0;
        //virtual bool isPure(Function &fn) = 0;
        bool isContractFunction(const Function &fn) const override;
        const vector<BlkContract *> &contracts() const override;
        const BlkContract *findDeclaringContract(const Function &fn) const override;
        const BlkFunction *findFunction(const Function &fn) const override;
        bool isAnyExternalCall(const Function &fn) const override;
        bool isCall(const Function &fn) const override;
        bool isStaticCall(const Function &fn) const override;
        bool isDelegateCall(const Function &fn) const override;
    private:
        string srcVersion;
        vector<BlkContract *> *solContracts;
    };
}

#endif //LIBBLOCKCHAIN_SOLIDITY_H
