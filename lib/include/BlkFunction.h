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
    enum Mutability {
        PURE,
        VIEW,
        PAYABLE,
        NONPAYABLE
    };

    enum Visibility {
        EXTERNAL,
        PUBLIC,
        INTERNAL,
        PRIVATE,
        DEFAULT
    };

    class BlkFunction : public BlkNode {
    public:
        BlkFunction(BlockchainToLLVM *blk2llvm, std::string &name, bool isCnstr, Visibility visibility, Mutability mutability, vector<BlkVariable *> *params, vector<BlkVariable *> *rets, vector<string> *mods);
        ~BlkFunction();

        static inline bool classof(const BlkFunction &) { return true; }
        static inline bool classof(const BlkFunction *) { return true; }
        static inline bool classof(const BlkNode *node) { return classof(*node); }
        static inline bool classof(const BlkNode &node) {
            if(node.type() == FUNCTION) { return true; }
            return false;
        }

        const vector<std::string> &modifiers() const;
        const vector<BlkVariable *> &parameters() const;
        bool isTranslation(const llvm::Function &fn) const;
        bool isConstructor() const;
        Visibility visibility() const;
        Mutability mutability() const;

        static Mutability toMutability(string mutStr);
        static Visibility toVisibility(string visStr);
    private:
        bool fnIsConstructor;
        vector<BlkVariable *> *fnParams;
        vector<BlkVariable *> *fnReturns;
        vector<std::string> *fnMods;
        Visibility visible;
        Mutability mut;
    };
}



#endif //LIBBLOCKCHAIN_BLKFUNCTION_H
