//
// Created by Jon Stephens on 3/23/22.
//

#ifndef LIBBLOCKCHAIN_SUMMARYREADER_H
#define LIBBLOCKCHAIN_SUMMARYREADER_H

#include <string>
#include <map>
#include "Blockchain.h"
#include "BlkUserType.h"
#include "BlkMapType.h"
#include "BlkElementaryType.h"
#include "BlkArrayType.h"
#include "BlkType.h"
#include "BlkVariable.h"
#include "BlkFunction.h"
#include "BlkStruct.h"
#include "BlkEnum.h"
#include "BlkContract.h"
#include "BlkStorage.h"

#include "../rapidjson/document.h"

namespace blockchain {
    class SummaryReader{
    public:
        SummaryReader(std::string projectFile);
        Blockchain *blockchain();
    private:
        std::map<int, BlkStorage *> storageDecls;
        std::map<BlkUserType *, int> storageRefs;
        Blockchain *summary;

        Blockchain *readSummary(rapidjson::Value &val);
        BlkContract *readContract(rapidjson::Value &val);
        BlkStruct *readStruct(rapidjson::Value &val);
        BlkEnum *readEnum(rapidjson::Value &val);
        BlkFunction *readFunction(rapidjson::Value &val);
        BlkVariable *readVariable(rapidjson::Value &val);
        BlkType *readType(rapidjson::Value &val);
        BlkArrayType *readArrayType(rapidjson::Value &val);
        BlkUserType *readUserType(rapidjson::Value &val);
        BlkMapType *readMapType(rapidjson::Value &val);
        BlkElementaryType *readElementaryType(rapidjson::Value &val);
    };
}



#endif //LIBBLOCKCHAIN_SUMMARYREADER_H
