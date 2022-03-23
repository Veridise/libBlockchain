//
// Created by Jon Stephens on 3/20/22.
//

#ifndef LIBBLOCKCHAIN_BLOCKCHAIN_H
#define LIBBLOCKCHAIN_BLOCKCHAIN_H

#include "llvm/IR/Function.h"
#include "llvm/IR/Instruction.h"
#include "BlkContract.h"
#include <vector>

using namespace llvm;
using namespace std;

namespace blockchain {
    class Blockchain {
    public:
        virtual bool allowsReentrancy() = 0;
        /*virtual bool isConstructor(Function &fn) = 0;
        virtual bool isExternalCall(Instruction &ins) = 0;
        virtual bool isView(Function &fn) = 0;
        virtual bool isPure(Function &fn) = 0;
        virtual bool isContractFunction(Function &fn) = 0;*/
        virtual const vector<BlkContract *> &contracts() = 0;
        //virtual BlkContract &findDeclaringContract(Function &fn) = 0;
    };
}

#endif //LIBBLOCKCHAIN_BLOCKCHAIN_H
