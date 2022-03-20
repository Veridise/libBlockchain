//
// Created by Jon Stephens on 3/20/22.
//

#ifndef LIBBLOCKCHAIN_BLKENUM_H
#define LIBBLOCKCHAIN_BLKENUM_H

#include <string>

using namespace std;

namespace blockchain {
    class BlkEnum {
    public:
        BlkEnum();
        ~BlkEnum();
        string name();
        string memberName(int id);
        int memberValue(string name);
    private:
        string enumName;
    };
}

#endif //LIBBLOCKCHAIN_BLKENUM_H
