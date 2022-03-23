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
        BlkElementaryType(std::string &name);
        ~BlkElementaryType();
    private:
        std::string typeName;
    };
}




#endif //LIBBLOCKCHAIN_BLKELEMENTARYTYPE_H
