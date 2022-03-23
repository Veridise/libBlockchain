//
// Created by Jon Stephens on 3/23/22.
//

#ifndef LIBBLOCKCHAIN_BLKUSERTYPE_H
#define LIBBLOCKCHAIN_BLKUSERTYPE_H

#include <string>
#include "BlkStorage.h"
#include "BlkType.h"

namespace blockchain {
    class BlkUserType : public BlkType {
    public:
        BlkUserType(std::string &name, BlkStorage *referenced);
        ~BlkUserType();
        void setReferenced(BlkStorage *referenced);
        std::string name();
    private:
        std::string typeName;
        BlkStorage *ref;
    };
}



#endif //LIBBLOCKCHAIN_BLKUSERTYPE_H
