//
// Created by Jon Stephens on 3/23/22.
//

#ifndef LIBBLOCKCHAIN_BLKNODE_H
#define LIBBLOCKCHAIN_BLKNODE_H

#include <string>

namespace blockchain {
    class BlockchainToLLVM;

    class BlkNode {
    public:
        explicit BlkNode(BlockchainToLLVM *blk2llvm, std::string &name);
        virtual ~BlkNode() = default;
        std::string name() const;
        BlkNode *parent() const;
        void parent(BlkNode *parent);
    protected:
        BlockchainToLLVM *blkTollvm;
        template<typename collection>
        void deleter(collection *collect) {
            if(collect != nullptr) {
                for(auto it : *collect) {
                    delete it;
                }
                collect->clear();
            }

            delete collect;
        }

        template<typename collection>
        void registerParent(collection *collect) {
            if(collect != nullptr) {
                for(auto it : *collect) {
                    it->parent(this);
                }
            }
        }
    private:
        std::string blkName;
        BlkNode *blkParent;
    };
}



#endif //LIBBLOCKCHAIN_BLKNODE_H
