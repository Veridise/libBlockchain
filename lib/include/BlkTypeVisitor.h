//
// Created by Jon Stephens on 3/24/22.
//

#ifndef LIBBLOCKCHAIN_BLKTYPEVISITOR_H
#define LIBBLOCKCHAIN_BLKTYPEVISITOR_H

#include "BlkArrayType.h"
#include "BlkMapType.h"
#include "BlkElementaryType.h"
#include "BlkUserType.h"

namespace blockchain {
    class BlkTypeVisitor {
    public:
        virtual void visit(const BlkArrayType &t) = 0;
        virtual void visit(const BlkMapType &t) = 0;
        virtual void visit(const BlkUserType &t) = 0;
        virtual void visit(const BlkElementaryType &t) = 0;
    };
}



#endif //LIBBLOCKCHAIN_BLKTYPEVISITOR_H
