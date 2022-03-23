//
// Created by Jon Stephens on 3/23/22.
//

#ifndef LIBBLOCKCHAIN_BLOCKCHAINTEST_H
#define LIBBLOCKCHAIN_BLOCKCHAINTEST_H

#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include <Blockchain.h>

using namespace llvm;
using namespace blockchain;

namespace blockchainTest {
    class BlockchainTest : public FunctionPass  {
    public:
        static char ID;
        BlockchainTest();
        ~BlockchainTest();
        bool runOnFunction(Function &F) override;
    private:
        Blockchain *blockchain;
    };
}



#endif //LIBBLOCKCHAIN_BLOCKCHAINTEST_H
