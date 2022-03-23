//
// Created by Jon Stephens on 3/23/22.
//

#include "BlockchainTest.h"
#include <iostream>
#include <SummaryReader.h>
#include <Blockchain.h>
#include <BlkContract.h>

using namespace blockchain;

namespace blockchainTest {
    BlockchainTest::BlockchainTest() : FunctionPass(ID) {
        SummaryReader reader("test/summary.json");
        blockchain = reader.blockchain();
        cout << blockchain->contracts()[0]->name() << endl;
    }

    BlockchainTest::~BlockchainTest() {
        delete blockchain;
        //FunctionPass::~FunctionPass();
    }

    bool BlockchainTest::runOnFunction(Function &fn) {
        if(fn.hasName()) {
            std::cout << fn.getName().str() << std::endl;
        }

        return false;
    }

    char BlockchainTest::ID = 0;
    static RegisterPass<BlockchainTest> X("libBlockchain-test", "Testing libBlockchain",
                                                  true /* Only looks at CFG */,
                                                  true /* Analysis Pass */);
}