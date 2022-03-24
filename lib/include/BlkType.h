//
// Created by Jon Stephens on 3/23/22.
//

#ifndef LIBBLOCKCHAIN_BLKTYPE_H
#define LIBBLOCKCHAIN_BLKTYPE_H


#include "BlkNode.h"

namespace blockchain {
    class BlkTypeVisitor;
    class BlkType : public BlkNode {
    public:
        explicit BlkType(BlockchainToLLVM *blk2llvm, std::string &name) : BlkNode(blk2llvm, name) {}
        virtual ~BlkType() = default;
        virtual void accept(BlkTypeVisitor &v) const = 0;
    };
}



#endif //LIBBLOCKCHAIN_BLKTYPE_H
