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
    class BlkFunction : public BlkNode {
    public:
        BlkFunction(std::string &name, vector<BlkVariable *> *params, vector<BlkVariable *> *rets, vector<string> *mods);
        ~BlkFunction();
        string name();
    private:
        string fnName;
        vector<BlkVariable *> *fnParams;
        vector<BlkVariable *> *fnReturns;
        vector<std::string> *fnMods;
    };
}



#endif //LIBBLOCKCHAIN_BLKFUNCTION_H
