set (Sources
        ${CMAKE_CURRENT_SOURCE_DIR}/BlkContract.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Solidity.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/BlkEnum.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/BlkStruct.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/BlkVariable.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/BlkFunction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/BlkArrayType.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/BlkElementaryType.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/BlkMapType.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/BlkUserType.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/SummaryReader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/SolangToLLVM.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/BlkNode.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Blockchain.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Ink.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/InkToLLVM.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/AAWrapper.cpp
        )

target_sources(Blockchain PRIVATE
        ${Sources})
target_sources(BlockchainStatic PRIVATE
        ${Sources})

include_directories(../include)