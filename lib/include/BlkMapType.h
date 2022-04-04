//
// Created by Jon Stephens on 3/23/22.
//

#ifndef LIBBLOCKCHAIN_BLKMAPTYPE_H
#define LIBBLOCKCHAIN_BLKMAPTYPE_H

#include <string>
#include "BlkType.h"

namespace blockchain {
    class BlkMapType : public BlkType {
    public:
        BlkMapType(BlockchainToLLVM *blk2llvm, std::string &name, BlkType *key, BlkType *val);
        ~BlkMapType();

        static inline bool classof(const BlkMapType &) { return true; }
        static inline bool classof(const BlkMapType *) { return true; }
        static inline bool classof(const BlkNode *node) { return classof(*node); }
        static inline bool classof(const BlkNode &node) {
            if(node.type() == MAP_TYPE) { return true; }
            return false;
        }

        void accept(BlkTypeVisitor &v) const override;
        const BlkType &key() const;
        const BlkType &value() const;
    private:
        BlkType *keyType;
        BlkType *valueType;
    };
}



#endif //LIBBLOCKCHAIN_BLKMAPTYPE_H
