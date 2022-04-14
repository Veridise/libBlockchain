//
// Created by Jon Stephens on 3/20/22.
//

#include "../include/Blockchain.h"
#include "../include/Solidity.h"
#include "../include/BlockchainToLLVM.h"
#include "SolangToLLVM.h"
#include <llvm/IR/Instructions.h>


namespace blockchain {
    Solidity::Solidity(BlockchainToLLVM *blk2llvm, string &c, string &v, vector<BlkContract *> *contracts) : Blockchain(SOLIDITY, blk2llvm, c, v, contracts) {}


    bool Solidity::allowsReentrancy() const {
        return true;
    }

    bool Solidity::writesStorage(Instruction &ins) const {
        if (auto call = dyn_cast<CallInst>(&ins)) {
            auto fn = call->getCalledFunction();

            return SolangToLLVM::writesStorage(*fn);

            //assume assigns goes through setter
            /*auto fn = call->getCalledFunction();
            if(fn->hasName() && fn->getName().str() == "storageStore") {
                return true;
            }*/
        }

        return false;
    }

    bool Solidity::readsStorage(Instruction &ins) const {
        if (auto call = dyn_cast<CallInst>(&ins)) {
            auto fn = call->getCalledFunction();

            return SolangToLLVM::readsStorage(*fn);

            //assume assigns goes through setter
            /*auto fn = call->getCalledFunction();
            if(fn->hasName() && fn->getName().str() == "storageStore") {
                return true;
            }*/
        }

        return false;
    }



    bool Solidity::getsSender(const Instruction &ins) const {
        if(auto call = dyn_cast<CallInst>(&ins)) {
            auto fn = call->getCalledFunction();
            if(fn->hasName() && fn->getName().str() == "getCaller") {
                return true;
            }
        }

        return false;
    }

    bool Solidity::getsValue(const Instruction &ins) const {
        if(auto call = dyn_cast<CallInst>(&ins)) {
            auto fn = call->getCalledFunction();
            if(fn->hasName() && fn->getName().str() == "getCallValue") {
                return true;
            }
        }

        return false;
    }

    bool Solidity::isSelfDestruct(const Instruction &ins) const {
        if(auto call = dyn_cast<CallInst>(&ins)) {
            auto fn = call->getCalledFunction();
            if(fn->hasName() && fn->getName().str() == "selfDestruct") {
                return true;
            }
        }

        return false;
    }
}