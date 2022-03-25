//
// Created by Jon Stephens on 3/23/22.
//

#include "BlockchainTest.h"
#include <iostream>
#include <SummaryReader.h>
#include <Blockchain.h>
#include <BlkContract.h>
#include "llvm/IR/Module.h"
#include "llvm/Support/CommandLine.h"

using namespace blockchain;

namespace blockchainTest {
    cl::opt<string> InputSummary("summary", cl::desc("Input Smart Contract Summary"), cl::value_desc("filename"), cl::Required);

    BlockchainTest::BlockchainTest() : ModulePass(ID) {
        SummaryReader reader(InputSummary);
        blockchain = reader.blockchain();
        externalCallCnt = 0;
        for(auto contract : blockchain->contracts()) {
            cout << "found contract: " << contract->name() << endl;
            for(auto function : contract->functions()) {
                cout << "  found function: " << function->name() << endl;
                fnCount[function] = 0;
            }
        }
    }

    BlockchainTest::~BlockchainTest() {
        delete blockchain;
        //FunctionPass::~FunctionPass();
    }

    bool BlockchainTest::runOnModule(Module &mod) {
        for(const Function &fn : mod) {
            //if(fn.hasName()) {
            //    cout << fn.getName().str() << endl;
            //}
            const BlkFunction *blkFn = blockchain->findFunction(fn);
            if(blkFn != nullptr) {
                //cout << blkFn->name() << " == " << fn.getName().str() << endl;
                fnCount[blkFn]++;
            }
            if(blockchain->isAnyExternalCall(fn)) {
                externalCallCnt++;
                cout << "Found external call: " << fn.getName().str() << endl;
            }
        }

        for(auto entry : fnCount) {
            if(entry.second == 0) {
                cerr << "Warning: Could not find function " << entry.first->name() << endl;
            }
            if(entry.second > 1) {
                cerr << "Error: Found " << entry.second << " instances of " << entry.first->name() << endl;
            }
        }

        if(externalCallCnt != 3) {
            cerr << "Error: Found " << externalCallCnt << " external calls" << endl;
        }

        return false;
    }

    char BlockchainTest::ID = 0;
    static RegisterPass<BlockchainTest> X("libBlockchain-test", "Testing libBlockchain",
                                                  true /* Only looks at CFG */,
                                                  true /* Analysis Pass */);
}