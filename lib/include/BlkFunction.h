//
// Created by Jon Stephens on 3/20/22.
//

#ifndef LIBBLOCKCHAIN_BLKFUNCTION_H
#define LIBBLOCKCHAIN_BLKFUNCTION_H

#include <string>
#include <vector>
#include "BlkVariable.h"

using namespace std;
namespace blockchain {
    class BlkFunction {
    public:
        BlkFunction();
        ~BlkFunction();
        string name();
        vector<BlkVariable> *params;
    private:
        string fnName;
        vector<BlkVariable> *fnParams;
    };
}



#endif //LIBBLOCKCHAIN_BLKFUNCTION_H
