//
// Created by Jon Stephens on 3/20/22.
//

#ifndef LIBBLOCKCHAIN_BLOCKCHAIN_H
#define LIBBLOCKCHAIN_BLOCKCHAIN_H

#include "llvm/IR/Function.h"
#include "llvm/IR/Instruction.h"
#include "BlkContract.h"
#include <vector>

using namespace llvm;
using namespace std;

namespace blockchain {
    class Blockchain : public BlkNode {
    public:
        Blockchain(NodeType t, BlockchainToLLVM *blk2llvm, string &name) : BlkNode(t, blk2llvm, name) {}

        static inline bool classof(const Blockchain &) { return true; }
        static inline bool classof(const Blockchain *) { return true; }
        static inline bool classof(const BlkNode *node) { return classof(*node); }
        static inline bool classof(const BlkNode &node) {
            if(node.type() >= BLOCKCHAIN_BEGIN && node.type() <= BLOCKCHAIN_END) { return true; }
            return false;
        }

        virtual ~Blockchain() = default;
        virtual bool allowsReentrancy() const = 0;
        //virtual bool isConstructor(Function &fn) = 0;
        //virtual bool isExternalCall(const Instruction &ins) const = 0;
        //virtual bool isView(Function &fn) = 0;
        //virtual bool isPure(Function &fn) = 0;
        virtual bool isContractFunction(const Function &fn) const = 0;
        virtual const vector<BlkContract *> &contracts() const = 0;
        virtual const BlkContract *findDeclaringContract(const Function &fn) const = 0;
        virtual const BlkFunction *findFunction(const Function &fn) const = 0;
        virtual bool isAnyExternalCall(const Function &fn) const = 0;
        virtual bool isCall(const Function &fn) const = 0;
        virtual bool isStaticCall(const Function &fn) const = 0;
        virtual bool isDelegateCall(const Function &fn) const = 0;
    };
}

#endif //LIBBLOCKCHAIN_BLOCKCHAIN_H
