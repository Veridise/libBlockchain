//
// Created by Jon Stephens on 3/20/22.
//

#ifndef LIBBLOCKCHAIN_BLKVARIABLE_H
#define LIBBLOCKCHAIN_BLKVARIABLE_H

#include <string>
#include "BlkType.h"

using namespace std;

namespace blockchain {
    class BlkVariable : public BlkNode {
    public:
        BlkVariable(BlockchainToLLVM *blk2llvm, string &name, BlkType *type);
        ~BlkVariable();
        const BlkType &type() const;
    private:
        BlkType *varType;
    };
}



#endif //LIBBLOCKCHAIN_BLKVARIABLE_H
