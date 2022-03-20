//
// Created by Jon Stephens on 3/20/22.
//

#ifndef LIBBLOCKCHAIN_BLKCONTRACT_H
#define LIBBLOCKCHAIN_BLKCONTRACT_H

#include "llvm/IR/Function.h"
#include "BlkEnum.h"
#include "BlkStruct.h"
#include "BlkVariable.h"
#include "BlkFunction.h"
#include <vector>

using namespace std;
using namespace llvm;

namespace blockchain {
    class BlkContract {
    public:
        BlkContract();
        ~BlkContract();
        const vector<BlkEnum> *enums();
        const vector<BlkStruct> *structs();
        const vector<BlkVariable> *variables();
        const vector<BlkFunction> *functions();
        string name();
        bool isConstructor(Function &fn);
        bool isContractFunction(Function &fn);
        bool isView(Function &fn);
        bool isPure(Function &fn);
        BlkFunction &findFunction(Function &fn);
    private:
        string contractName;
        vector<BlkEnum> *contractEnums;
        vector<BlkStruct> *contractStructs;
        vector<BlkVariable> *contractVars;
        vector<BlkFunction> *contractFns;
    };
}



#endif //LIBBLOCKCHAIN_BLKCONTRACT_H
