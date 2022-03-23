//
// Created by Jon Stephens on 3/23/22.
//

#ifndef LIBBLOCKCHAIN_BLKMAPTYPE_H
#define LIBBLOCKCHAIN_BLKMAPTYPE_H

#include "BlkType.h"

namespace blockchain {
    class BlkMapType : public BlkType {
    public:
        BlkMapType(BlkType *key, BlkType *val);
        ~BlkMapType();
    private:
        BlkType *keyType;
        BlkType *valueType;
    };
}



#endif //LIBBLOCKCHAIN_BLKMAPTYPE_H
