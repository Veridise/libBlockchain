//
// Created by Jon Stephens on 3/23/22.
//

#ifndef LIBBLOCKCHAIN_BLKNODE_H
#define LIBBLOCKCHAIN_BLKNODE_H

#include <string>

namespace blockchain {
    class BlockchainToLLVM;

    enum NodeType {
        BLOCKCHAIN_BEGIN,
        SOLIDITY = BLOCKCHAIN_BEGIN,
        BLOCKCHAIN_END = SOLIDITY,
        //storage
        STORAGE_BEGIN,
        CONTRACT = STORAGE_BEGIN,
        ENUM,
        STRUCT,
        STORAGE_END = STRUCT,
        //contract entities
        FUNCTION,
        VARIABLE,
        //Types
        TYPE_BEGIN,
        ELEMENTARY_TYPE = TYPE_BEGIN,
        MAP_TYPE,
        USER_TYPE,
        ARRAY_TYPE,
        TYPE_END = ARRAY_TYPE
    };

    class BlkNode {
    public:
        explicit BlkNode(NodeType t, BlockchainToLLVM *blk2llvm, std::string &name);

        static inline bool classof(const BlkNode &) { return true; }
        static inline bool classof(const BlkNode *) { return true; }

        virtual ~BlkNode() = default;
        std::string name() const;
        BlkNode *parent() const;
        void parent(BlkNode *parent);
        NodeType type() const;
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
        NodeType ty;
        std::string blkName;
        BlkNode *blkParent;
    };
}



#endif //LIBBLOCKCHAIN_BLKNODE_H
