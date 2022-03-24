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
        explicit BlkStorage(BlockchainToLLVM *blk2llvm, std::string &name) : BlkNode(blk2llvm, name) {}
    };
}



#endif //LIBBLOCKCHAIN_BLKSTORAGE_H
