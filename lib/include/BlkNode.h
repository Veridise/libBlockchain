//
// Created by Jon Stephens on 3/23/22.
//

#ifndef LIBBLOCKCHAIN_BLKNODE_H
#define LIBBLOCKCHAIN_BLKNODE_H

namespace blockchain {
    class BlkNode {
    protected:
        template<typename collection>
        void deleter(collection *collect);
    };
}



#endif //LIBBLOCKCHAIN_BLKNODE_H
