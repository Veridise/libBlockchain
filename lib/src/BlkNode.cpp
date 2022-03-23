//
// Created by Jon Stephens on 3/23/22.
//

#include "../include/BlkNode.h"
namespace blockchain {
    template<typename collection>
    void BlkNode::deleter(collection *collect) {
        if(collect != nullptr) {
            for(auto it : *collect) {
                delete *it;
            }
            collect->clear();
        }

        delete collect;
    }
}