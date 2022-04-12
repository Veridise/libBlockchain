//
// Created by Jon Stephens on 3/20/22.
//

#include "../include/Blockchain.h"
#include "../include/Solidity.h"
#include "../include/BlockchainToLLVM.h"
#include <llvm/IR/Instructions.h>


namespace blockchain {
    Solidity::Solidity(BlockchainToLLVM *blk2llvm, string &c, string &v, vector<BlkContract *> *contracts) : Blockchain(SOLIDITY, blk2llvm, c, v, contracts) {}


    bool Solidity::allowsReentrancy() const {
        return true;
    }

    bool Solidity::modifiesStorage(Instruction &ins) const {
        if (auto call = dyn_cast<CallInst>(&ins)) {
            auto fn = call->getCalledFunction();
            if(fn->hasName() && fn->getName().str() == "storageStore") {
                return true;
            }
        }

        return false;
    }
}