//
// Created by Jon Stephens on 3/20/22.
//

#ifndef LIBBLOCKCHAIN_BLKENUM_H
#define LIBBLOCKCHAIN_BLKENUM_H

#include <map>
#include <string>
#include "BlkStorage.h"

using namespace std;

namespace blockchain {
    class BlkEnum : public BlkStorage {
    public:
        BlkEnum(string &name, map<std::string, int> *values);
        ~BlkEnum();
        string name();
    private:
        string enumName;
        map<std::string, int> *values;
    };
}

#endif //LIBBLOCKCHAIN_BLKENUM_H
