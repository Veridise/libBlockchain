//
// Created by Jon Stephens on 3/23/22.
//

#ifndef LIBBLOCKCHAIN_BLKELEMENTARYTYPE_H
#define LIBBLOCKCHAIN_BLKELEMENTARYTYPE_H

#include <string>
#include "BlkType.h"

namespace blockchain {
    class BlkElementaryType : public BlkType {
    public:
        BlkElementaryType(BlockchainToLLVM *blk2llvm, std::string &name);
        ~BlkElementaryType();

        static inline bool classof(const BlkElementaryType &) { return true; }
        static inline bool classof(const BlkElementaryType *) { return true; }
        static inline bool classof(const BlkNode *node) { return classof(*node); }
        static inline bool classof(const BlkNode &node) {
            if(node.type() == ELEMENTARY_TYPE) { return true; }
            return false;
        }

        void accept(BlkTypeVisitor &v) const override;
    private:
    };
}




#endif //LIBBLOCKCHAIN_BLKELEMENTARYTYPE_H
