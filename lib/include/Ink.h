//
// Created by Jon Stephens on 4/10/22.
//

#ifndef LIBBLOCKCHAIN_INK_H
#define LIBBLOCKCHAIN_INK_H

#include "Blockchain.h"

namespace blockchain {
    class Ink : public Blockchain {
    public:
        Ink(BlockchainToLLVM *blk2llvm, string &c, string &v, vector<BlkContract *> *contracts, AAWrapper &alias);

        static inline bool classof(const Ink &) { return true; }
        static inline bool classof(const Ink *) { return true; }
        static inline bool classof(const BlkNode *node) { return classof(*node); }
        static inline bool classof(const BlkNode &node) {
            if(node.type() == INK) { return true; }
            return false;
        }

        bool allowsReentrancy() const override;
        bool readsStorage(Instruction &ins) const override;
        bool writesStorage(Instruction &ins) const override;
        bool getsSender(const Instruction &ins) const override;
        bool getsValue(const Instruction &ins) const override;
        bool isSelfDestruct(const Instruction &ins) const override;
    private:
        AAWrapper &alias;
    };
}




#endif //LIBBLOCKCHAIN_INK_H
