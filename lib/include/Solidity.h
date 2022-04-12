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

        static inline bool classof(const Solidity &) { return true; }
        static inline bool classof(const Solidity *) { return true; }
        static inline bool classof(const BlkNode *node) { return classof(*node); }
        static inline bool classof(const BlkNode &node) {
            if(node.type() == SOLIDITY) { return true; }
            return false;
        }

        bool allowsReentrancy() const override;
        bool modifiesStorage(Instruction &ins) const override;
    };
}

#endif //LIBBLOCKCHAIN_SOLIDITY_H
