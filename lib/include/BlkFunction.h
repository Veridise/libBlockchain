//
// Created by Jon Stephens on 3/20/22.
//

#ifndef LIBBLOCKCHAIN_BLKFUNCTION_H
#define LIBBLOCKCHAIN_BLKFUNCTION_H

#include "llvm/IR/Function.h"
#include <string>
#include <vector>
#include "BlkVariable.h"

using namespace std;
namespace blockchain {
    class BlkFunction : public BlkNode {
    public:
        BlkFunction(BlockchainToLLVM *blk2llvm, std::string &name, bool isCnstr, vector<BlkVariable *> *params, vector<BlkVariable *> *rets, vector<string> *mods);
        ~BlkFunction();
        const vector<std::string> &modifiers() const;
        const vector<BlkVariable *> &parameters() const;
        bool isTranslation(const llvm::Function &fn) const;
        bool isConstructor() const;
    private:
        bool fnIsConstructor;
        vector<BlkVariable *> *fnParams;
        vector<BlkVariable *> *fnReturns;
        vector<std::string> *fnMods;
    };
}



#endif //LIBBLOCKCHAIN_BLKFUNCTION_H
