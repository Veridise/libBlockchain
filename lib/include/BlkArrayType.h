//
// Created by Jon Stephens on 3/23/22.
//

#ifndef LIBBLOCKCHAIN_BLKARRAYTYPE_H
#define LIBBLOCKCHAIN_BLKARRAYTYPE_H

#include "BlkType.h"

namespace blockchain {
    class BlkArrayType : public BlkType {
    public:
        explicit BlkArrayType(BlockchainToLLVM *blk2llvm, std::string &name, BlkType *base);

        static inline bool classof(const BlkArrayType &) { return true; }
        static inline bool classof(const BlkArrayType *) { return true; }
        static inline bool classof(const BlkNode *node) { return classof(*node); }
        static inline bool classof(const BlkNode &node) {
            if(node.type() == ARRAY_TYPE) { return true; }
            return false;
        }

        const BlkType &base() const;
        ~BlkArrayType();
        void accept(BlkTypeVisitor &v) const override;
    private:
        BlkType *baseType;
    };
}




#endif //LIBBLOCKCHAIN_BLKARRAYTYPE_H
