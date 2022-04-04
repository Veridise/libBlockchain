//
// Created by Jon Stephens on 3/20/22.
//

#ifndef LIBBLOCKCHAIN_BLKENUM_H
#define LIBBLOCKCHAIN_BLKENUM_H

#include <map>
#include <string>
#include "BlkStorage.h"

using namespace std;

namespace blockchain {
    class BlkEnum : public BlkStorage {
    public:
        BlkEnum(BlockchainToLLVM *blk2llvm, string &name, map<std::string, int> *values);
        ~BlkEnum();

        static inline bool classof(const BlkEnum &) { return true; }
        static inline bool classof(const BlkEnum *) { return true; }
        static inline bool classof(const BlkNode *node) { return classof(*node); }
        static inline bool classof(const BlkNode &node) {
            if(node.type() == ENUM) { return true; }
            return false;
        }
    private:
        map<std::string, int> *values;
    };
}

#endif //LIBBLOCKCHAIN_BLKENUM_H
