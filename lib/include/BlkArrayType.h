//
// Created by Jon Stephens on 3/23/22.
//

#ifndef LIBBLOCKCHAIN_BLKARRAYTYPE_H
#define LIBBLOCKCHAIN_BLKARRAYTYPE_H

#include "BlkType.h"

namespace blockchain {
    class BlkArrayType : public BlkType {
    public:
        explicit BlkArrayType(BlkType *base);
        BlkType &base();
        ~BlkArrayType();
    private:
        BlkType *baseType;
    };
}




#endif //LIBBLOCKCHAIN_BLKARRAYTYPE_H
