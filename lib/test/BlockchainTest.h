//
// Created by Jon Stephens on 3/23/22.
//

#ifndef LIBBLOCKCHAIN_BLOCKCHAINTEST_H
#define LIBBLOCKCHAIN_BLOCKCHAINTEST_H

#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include <Blockchain.h>
#include <BlkFunction.h>
#include <map>

using namespace llvm;
using namespace blockchain;

namespace blockchainTest {
    class BlockchainTest : public ModulePass  {
    public:
        static char ID;
        BlockchainTest();
        ~BlockchainTest();
        bool runOnModule(Module &mod) override;
    private:
        map<const BlkFunction *, int> fnCount;
        int externalCallCnt = 0;
        Blockchain *blockchain;
    };
}



#endif //LIBBLOCKCHAIN_BLOCKCHAINTEST_H
