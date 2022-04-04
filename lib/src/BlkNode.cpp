//
// Created by Jon Stephens on 3/23/22.
//

#include "../include/BlkNode.h"
#include "BlockchainToLLVM.h"

namespace blockchain {
    BlkNode::BlkNode(NodeType t, BlockchainToLLVM *blk2llvm, std::string &name) : ty(t), blkName(name), blkTollvm(blk2llvm), blkParent(nullptr) {}

    std::string BlkNode::name() const {
        return blkName;
    }

    void BlkNode::parent(BlkNode *parent){
        if(blkParent == nullptr) {
            blkParent = parent;
        }
    }

    BlkNode *BlkNode::parent() const {
        return blkParent;
    }

    NodeType BlkNode::type() const {
        return ty;
    }
}