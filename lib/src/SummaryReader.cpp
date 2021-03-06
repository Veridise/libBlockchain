//
// Created by Jon Stephens on 3/23/22.
//

#include "../include/SummaryReader.h"
#include "Solidity.h"
#include <fstream>
#include <document.h>
#include <istreamwrapper.h>
#include <stdexcept>
#include <iostream>
#include <../include/SolangToLLVM.h>
#include "InkToLLVM.h"
#include "Ink.h"
#include "BlkEvent.h"

using namespace std;

namespace blockchain {


    SummaryReader::SummaryReader(std::string projectFile, AAWrapper *alias) : alias(alias) {
        ifstream inStream(projectFile);
        rapidjson::IStreamWrapper jsonStream(inStream);
        cout << "starting" << endl;

        rapidjson::Document doc;
        doc.ParseStream(jsonStream);
        summary = readSummary(doc);
    }

    Blockchain *SummaryReader::blockchain() {
        return summary;
    }

    void error(string msg) {
        throw std::runtime_error(msg);
    }

    void require(bool cond, string msg = "") {
        if(!cond) {
            error(msg);
        }
    }

    Blockchain *SummaryReader::readSummary(rapidjson::Value &val) {
        require(val.HasMember("compiler") && val["compiler"].IsString(), "Summary must declare compiler");
        require(val.HasMember("version") && val["version"].IsString(), "Summary must declare version");

        string compiler = val["compiler"].GetString();
        string version = val["version"].GetString();

        Blockchain *blockchain;
        auto contracts = new vector<BlkContract *>();
        if(compiler == "Solang") {
            llvmTrans = new SolangToLLVM();
            blockchain = new Solidity(llvmTrans, compiler, version, contracts);
        }
        else if(compiler == "cargo-contract") {
            llvmTrans = new InkToLLVM(*alias);
            blockchain = new Ink(llvmTrans, compiler, version, contracts, *alias);
        }
        else {
            error(string("Unknown compiler: ") + compiler);
        }

        if(val.HasMember("contracts")) {
            require(val["contracts"].IsArray(), "Summary contracts must be an array");
            for(rapidjson::Value &contractVal : val["contracts"].GetArray()) {
                contracts->push_back(readContract(contractVal));
            }
        }

        for(auto &ref : storageRefs) {
            require(storageDecls.find(ref.second) != storageDecls.end(), string("Could not find referenced declaration for ") + ref.first->name());
            ref.first->setReferenced(storageDecls[ref.second]);
        }

        return blockchain;
    }

    BlkContract *SummaryReader::readContract(rapidjson::Value &val) {
        require(val.HasMember("id") && val["id"].IsNumber(), "Contract must have an id");
        require(val.HasMember("name") && val["name"].IsString(), "Contract must have a name");

        int id = val["id"].GetInt();
        string name = val["name"].GetString();

        auto inherits = new vector<BlkUserType *>();
        if(val.HasMember("inherits")) {
            require(val["inherits"].IsArray(), "contract inherits must be an array of UserType");

            for(rapidjson::Value &iVal : val["inherits"].GetArray()) {
                inherits->push_back(readUserType(iVal));
            }
        }

        auto events = new vector<BlkEvent *>();
        if(val.HasMember("events")) {
            require(val["events"].IsArray(), "Contract events must be an array of Function");

            for(rapidjson::Value &eVal : val["events"].GetArray()) {
                events->push_back(readEvent(eVal));
            }
        }

        auto functions = new vector<BlkFunction *>();
        if(val.HasMember("functions")) {
            require(val["functions"].IsArray(), "Contract functions must be an array of Function");

            for(rapidjson::Value &fVal : val["functions"].GetArray()) {
                functions->push_back(readFunction(fVal));
            }
        }

        auto variables = new vector<BlkVariable *>();
        if(val.HasMember("variables")) {
            require(val["variables"].IsArray(), "Contract variables must be an array of Variable");

            for(rapidjson::Value &vVal : val["variables"].GetArray()) {
                variables->push_back(readVariable(vVal));
            }
        }

        auto structs = new vector<BlkStruct *>();
        if(val.HasMember("structs")) {
            require(val["structs"].IsArray(), "Contract structs must be an array of Struct");
            for(rapidjson::Value &sVal : val["structs"].GetArray()) {
                structs->push_back(readStruct(sVal));
            }
        }

        auto enums = new vector<BlkEnum *>();
        if(val.HasMember("enums")) {
            require(val["enums"].IsArray(), "Contract enums must be an array of Enum");

            for(rapidjson::Value &eVal : val["enums"].GetArray()) {
                enums->push_back(readEnum(eVal));
            }
        }

        auto contract = new BlkContract(llvmTrans, name, functions, variables, inherits, enums, structs, events);
        storageDecls[id] = contract;
        return contract;
    }

    BlkEvent *SummaryReader::readEvent(rapidjson::Value &val) {
        require(val.HasMember("name") && val["name"].IsString(), "Function must have a name");

        string name = val["name"].GetString();

        auto params = new vector<BlkVariable *>();
        if(val.HasMember("params")) {
            require(val["params"].IsArray(), "Function params must be array of Variable");

            for(auto &pVal : val["params"].GetArray()) {
                params->push_back(readVariable(pVal));
            }
        }

        BlkEvent *event = new BlkEvent(llvmTrans, name, params);

        return event;
    }

    BlkStruct *SummaryReader::readStruct(rapidjson::Value &val) {
        require(val.HasMember("id") && val["id"].IsNumber(), "Struct must have an id");
        require(val.HasMember("name") && val["name"].IsString(), "Struct must have a name");

        int id = val["id"].GetInt();
        string name = val["name"].GetString();

        auto fields = new vector<BlkVariable *>();
        if(val.HasMember("fields")) {
            require(val["fields"].IsArray(), "Struct fields must be an array of Variable");

            for(auto &fVal : val["fields"].GetArray()) {
                fields->push_back(readVariable(fVal));
            }
        }

        auto aStruct = new BlkStruct(llvmTrans, name, fields);
        storageDecls[id] = aStruct;
        return aStruct;
    }

    BlkEnum *SummaryReader::readEnum(rapidjson::Value &val) {
        require(val.HasMember("id") && val["id"].IsNumber(), "Struct must have an id");
        require(val.HasMember("name") && val["name"].IsString(), "Struct must have a name");

        int id = val["id"].GetInt();
        string name = val["name"].GetString();

        auto values = new map<string, int>();
        if(val.HasMember("values")) {
            require(val["values"].IsObject(), "Enum values must be an object");
            for(auto &enumVal : val["values"].GetObject()) {
                require(enumVal.name.IsString(), "Enum value names must be a string");
                require(enumVal.value.IsNumber(), "Enum value must map to number");
                string valName = enumVal.name.GetString();
                int valId = enumVal.value.GetInt();
                (*values)[valName] = valId;
            }
        }

        auto anEnum = new BlkEnum(llvmTrans, name, values);
        storageDecls[id] = anEnum;
        return anEnum;
    }

    BlkFunction *SummaryReader::readFunction(rapidjson::Value &val) {
        require(val.HasMember("name") && val["name"].IsString(), "Function must have a name");
        require(val.HasMember("isConstructor") && val["isConstructor"].IsBool(), "Must identify if function is a constructor");
        require(val.HasMember("visibility") && val["visibility"].IsString(), "Function must have a visibility");
        require(val.HasMember("mutability") && val["mutability"].IsString(), "Function must have a mutability");

        string name = val["name"].GetString();
        bool isConstructor = val["isConstructor"].GetBool();
        Visibility visibility = BlkFunction::toVisibility(val["visibility"].GetString());
        Mutability mutability = BlkFunction::toMutability(val["mutability"].GetString());

        auto params = new vector<BlkVariable *>();
        if(val.HasMember("params")) {
            require(val["params"].IsArray(), "Function params must be array of Variable");

            for(auto &pVal : val["params"].GetArray()) {
                params->push_back(readVariable(pVal));
            }
        }

        auto returns = new vector<BlkVariable *>();
        if(val.HasMember("returns")) {
            require(val["returns"].IsArray(), "Function returns must be array of Variable");

            for(auto &rVal : val["returns"].GetArray()) {
                returns->push_back(readVariable(rVal));
            }
        }

        auto modifiers = new vector<string>();
        if(val.HasMember("modifiers")) {
            require(val["modifiers"].IsArray(), "Function modifiers must be array of string");

            for(auto &mVal : val["modifiers"].GetArray()) {
                require(mVal.IsString(), "Found modifier that isn't a string modifier");

                modifiers->emplace_back(mVal.GetString());
            }
        }

        BlkFunction *fn = new BlkFunction(llvmTrans, name, isConstructor, visibility, mutability, params, returns, modifiers);

        if(val.HasMember("selector")) {
            fn->setSelector(val["selector"].GetString());
        }

        return fn;
    }

    BlkVariable *SummaryReader::readVariable(rapidjson::Value &val) {
        require(val.HasMember("type") && val["type"].IsObject(), "Variable must have a type");

        BlkType *type = readType(val["type"]);

        string name = "";
        if(val.HasMember("name")) {
            require(val["name"].IsString(), "Variable name must be a string");
            name = val["name"].GetString();
        }

        return new BlkVariable(llvmTrans, name, type);
    }

    BlkType *SummaryReader::readType(rapidjson::Value &val) {
        require(val.HasMember("subType") && val["subType"].IsString(), "Type must have a subtype");
        string subType = val["subType"].GetString();

        if(subType == "UserType") {
            return readUserType(val);
        }
        else if(subType == "ArrayType") {
            return readArrayType(val);
        }
        else if(subType == "MapType") {
            return readMapType(val);
        }
        else if(subType == "ElementaryType") {
            return readElementaryType(val);
        }

        error(string("Unknown Type: ") + subType);
        return nullptr;
    }

    BlkArrayType *SummaryReader::readArrayType(rapidjson::Value &val) {
        require(val.HasMember("subType") && val["subType"].IsString(), "Type must have a subtype");
        string subType = val["subType"].GetString();
        require(subType == "ArrayType");

        require(val.HasMember("name") && val["name"].IsString(), "ArrayType must have a name");
        require(val.HasMember("base"), "ArrayType must have a base type");
        BlkType *base = readType(val["base"]);
        string name = val["name"].GetString();
        return new BlkArrayType(llvmTrans, name, base);
    }

    BlkUserType *SummaryReader::readUserType(rapidjson::Value &val) {
        require(val.HasMember("subType") && val["subType"].IsString(), "Type must have a subtype");
        string subType = val["subType"].GetString();
        require(subType == "UserType");

        require(val.HasMember("name") && val["name"].IsString(), "UserType must have a name");
        require(val.HasMember("refId") && val["refId"].IsNumber(), "UserType must have a reference id");

        string name = val["name"].GetString();
        uint id = val["refId"].GetUint();

        auto userType = new BlkUserType(llvmTrans, name, nullptr);
        storageRefs[userType] = id;

        return userType;
    }

    BlkMapType *SummaryReader::readMapType(rapidjson::Value &val) {
        require(val.HasMember("subType") && val["subType"].IsString(), "Type must have a subtype");
        string subType = val["subType"].GetString();
        require(subType == "MapType");

        require(val.HasMember("name") && val["name"].IsString(), "MapType must have a name");
        require(val.HasMember("key"), "MapType must have a key type");
        require(val.HasMember("value"), "MapType must have a value type");
        BlkType *key = readType(val["key"]);
        BlkType *value = readType(val["value"]);
        string name = val["name"].GetString();
        return new BlkMapType(llvmTrans, name, key, value);
    }

    BlkElementaryType *SummaryReader::readElementaryType(rapidjson::Value &val) {
        require(val.HasMember("subType") && val["subType"].IsString(), "Type must have a subtype");
        string subType = val["subType"].GetString();
        require(subType == "ElementaryType");

        require(val.HasMember("name") && val["name"].IsString(), "ElementaryType must have a name");
        string name = val["name"].GetString();
        return new BlkElementaryType(llvmTrans, name);
    }
}