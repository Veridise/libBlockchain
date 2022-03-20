target_sources(Blockchain PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/BlkContract.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Solidity.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/BlkEnum.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/BlkStruct.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/BlkVariable.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/BlkFunction.cpp)
target_sources(BlockchainStatic PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/BlkContract.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Solidity.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/BlkEnum.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/BlkStruct.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/BlkVariable.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/BlkFunction.cpp)

include_directories(../include)