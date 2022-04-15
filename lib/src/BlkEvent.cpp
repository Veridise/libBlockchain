//
// Created by Jon Stephens on 4/14/22.
//

#include "../include/BlkEvent.h"


namespace blockchain {
    BlkEvent::BlkEvent(BlockchainToLLVM *blk2llvm, std::string &name, vector<BlkVariable *> *params) : eventParams(params), BlkNode(EVENT, blk2llvm, name) {
        registerParent(eventParams);
    }

    BlkEvent::~BlkEvent() {
        deleter(eventParams);
    }

    const vector<BlkVariable *> &BlkEvent::parameters() const {
        return *eventParams;
    }

    bool BlkEvent::emits(const llvm::Instruction &ins) const {
        return false;
    }
}