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
#include "BlkUserType.h"
#include <vector>

using namespace std;
using namespace llvm;
#include "BlkNode.h"

namespace blockchain {
    class BlkContract : public BlkStorage {
    public:
        BlkContract(BlockchainToLLVM *blk2llvm, string &name, vector<BlkFunction *> *fns, vector<BlkVariable *> *vars, vector<BlkUserType *> *inherits,
                    vector<BlkEnum *> *enums, vector<BlkStruct *> *structs, vector<BlkFunction *> *events);
        ~BlkContract();

        static inline bool classof(const BlkContract &) { return true; }
        static inline bool classof(const BlkContract *) { return true; }
        static inline bool classof(const BlkNode *node) { return classof(*node); }
        static inline bool classof(const BlkNode &node) {
            if(node.type() == CONTRACT) { return true; }
            return false;
        }

        bool isContractFunction(const Function &fn) const;
        const BlkFunction *findFunction(const Function &fn) const;
        const vector<BlkFunction *> &functions() const;
        const vector<BlkVariable *> &variables() const;
        vector<BlkContract *> inherits() const;
    private:
        vector<BlkUserType *> *contractInherits;
        vector<BlkFunction *> *contractEvents;
        vector<BlkEnum *> *contractEnums;
        vector<BlkStruct *> *contractStructs;
        vector<BlkVariable *> *contractVars;
        vector<BlkFunction *> *contractFns;
    };
}



#endif //LIBBLOCKCHAIN_BLKCONTRACT_H
