//
// Created by Jon Stephens on 3/20/22.
//

#ifndef LIBBLOCKCHAIN_BLKVARIABLE_H
#define LIBBLOCKCHAIN_BLKVARIABLE_H

#include <string>

using namespace std;

namespace blockchain {
    class BlkVariable {
    public:
        BlkVariable();
        ~BlkVariable();
        bool isContractVariable();
        string name();
    private:
        string varName;
    };
}



#endif //LIBBLOCKCHAIN_BLKVARIABLE_H
