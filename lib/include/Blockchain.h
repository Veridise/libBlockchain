//
// Created by Jon Stephens on 3/20/22.
//

#ifndef LIBBLOCKCHAIN_BLOCKCHAIN_H
#define LIBBLOCKCHAIN_BLOCKCHAIN_H

#include "llvm/IR/Function.h"
#include "llvm/IR/Instruction.h"
#include "BlkContract.h"
#include "AAWrapper.h"
#include <vector>

using namespace llvm;
using namespace std;

namespace blockchain {
    class Blockchain : public BlkNode {
    public:
        Blockchain(NodeType t, BlockchainToLLVM *blk2llvm, string &name, string &version, vector<BlkContract *> *contracts) : BlkNode(t, blk2llvm, name), srcVersion(version), allContracts(contracts) {}
        ~Blockchain();

        static inline bool classof(const Blockchain &) { return true; }
        static inline bool classof(const Blockchain *) { return true; }
        static inline bool classof(const BlkNode *node) { return classof(*node); }
        static inline bool classof(const BlkNode &node) {
            if(node.type() >= BLOCKCHAIN_BEGIN && node.type() <= BLOCKCHAIN_END) { return true; }
            return false;
        }

        virtual bool allowsReentrancy() const = 0;
        virtual bool modifiesStorage(Instruction &ins) const = 0;
        virtual bool isContractFunction(const Function &fn) const;
        virtual const vector<BlkContract *> &contracts() const;
        virtual const BlkContract *findDeclaringContract(const Function &fn) const;
        virtual const BlkFunction *findFunction(const Function &fn) const;
        virtual bool isAnyExternalCall(const Function &fn) const;
        virtual bool isCall(const Function &fn) const;
        virtual bool isStaticCall(const Function &fn) const;
        virtual bool isDelegateCall(const Function &fn) const;
    protected:
        string srcVersion;
        vector<BlkContract *> *allContracts;
    };
}

#endif //LIBBLOCKCHAIN_BLOCKCHAIN_H
