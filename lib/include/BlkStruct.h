//
// Created by Jon Stephens on 3/20/22.
//

#ifndef LIBBLOCKCHAIN_BLKSTRUCT_H
#define LIBBLOCKCHAIN_BLKSTRUCT_H

#include <string>
#include <vector>
#include "BlkVariable.h"
#include "BlkVariable.h"
#include "BlkStorage.h"

using namespace std;

namespace blockchain {
    class BlkStruct : public BlkStorage {
    public:
        BlkStruct(string &name, vector<BlkVariable *> *fields);
        ~BlkStruct();
        string name();
    private:
        string structName;
        vector<BlkVariable *> *structFields;
    };
}

#endif //LIBBLOCKCHAIN_BLKSTRUCT_H
