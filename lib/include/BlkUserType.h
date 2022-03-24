//
// Created by Jon Stephens on 3/23/22.
//

#ifndef LIBBLOCKCHAIN_BLKUSERTYPE_H
#define LIBBLOCKCHAIN_BLKUSERTYPE_H

#include <string>
#include "BlkStorage.h"
#include "BlkType.h"

namespace blockchain {
    class BlkTypeVisitor;
    class BlkUserType : public BlkType {
    public:
        BlkUserType(BlockchainToLLVM *blk2llvm, std::string &name, BlkStorage *referenced);
        ~BlkUserType();
        void accept(BlkTypeVisitor &v) const override;
        void setReferenced(BlkStorage *referenced);
    private:
        BlkStorage *ref;
    };
}



#endif //LIBBLOCKCHAIN_BLKUSERTYPE_H
