//
// Created by Jon Stephens on 3/23/22.
//

#ifndef LIBBLOCKCHAIN_BLKSTORAGE_H
#define LIBBLOCKCHAIN_BLKSTORAGE_H

#include <string>
#include "BlkNode.h"

namespace blockchain {
    class BlkStorage : public BlkNode {
    public:
        explicit BlkStorage(NodeType t, BlockchainToLLVM *blk2llvm, std::string &name) : BlkNode(t, blk2llvm, name) {}

        static inline bool classof(const BlkStorage &) { return true; }
        static inline bool classof(const BlkStorage *) { return true; }
        static inline bool classof(const BlkNode *node) { return classof(*node); }
        static inline bool classof(const BlkNode &node) {
            if(node.type() >= STORAGE_BEGIN && node.type() <= STORAGE_END) { return true; }
            return false;
        }
    };
}



#endif //LIBBLOCKCHAIN_BLKSTORAGE_H
