//
// Created by Jon Stephens on 3/20/22.
//

#ifndef LIBBLOCKCHAIN_BLKSTRUCT_H
#define LIBBLOCKCHAIN_BLKSTRUCT_H

#include <string>

using namespace std;

namespace blockchain {
    class BlkStruct {
    public:
        BlkStruct();
        ~BlkStruct();
        string name();
    private:
        string structName;
    };
}

#endif //LIBBLOCKCHAIN_BLKSTRUCT_H
