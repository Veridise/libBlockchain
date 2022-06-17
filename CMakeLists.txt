cmake_minimum_required(VERSION 3.14)
project(libBlockchain)

include (GNUInstallDirs)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(LIBBLOCKCHAIN_MAJOR_VERSION 0)
set(LIBBLOCKCHAIN_MINOR_VERSION 1)
set(LIBBLOCKCHAIN_PATCH_VERSION 0)
set(LIBBLOCKCHAIN_VERSION
        ${LIBBLOCKCHAIN_MAJOR_VERSION}.${LIBBLOCKCHAIN_MINOR_VERSION}.${LIBBLOCKCHAIN_PATCH_VERSION})


if(NOT DEFINED ENV{LLVM_DIR})
    message(FATAL_ERROR "$LLVM_HOME is not defined")
else ()
    set(ENV{LLVM_DIR} $ENV{LLVM_DIR}/lib/cmake/llvm)
endif()

# find_package(rapidjson REQUIRED)
# include_directories(${rapidjson_INCLUDE_DIRS})
# link_directories(${rapidjson_LIBRARY_DIRS})

find_package(LLVM REQUIRED CONFIG)
add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})
if (${LLVM_VERSION_MAJOR} VERSION_GREATER_EQUAL 10) 
    set(CMAKE_CXX_STANDARD 14) 
endif ()

add_subdirectory(lib)

# Add all targets to the build-tree export set
export(TARGETS Blockchain BlockchainStatic
        FILE "${PROJECT_BINARY_DIR}/libBlockchainTargets.cmake")

set (INSTALL_CMAKE_DIR ${PROJECT_BINARY_DIR}/lib)
set (INSTALL_INCLUDE_DIR ${PROJECT_BINARY_DIR}/lib/include)

# Create the libBlockchain.cmake and libBlockchainConfigVersion files
file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
        "${INSTALL_INCLUDE_DIR}")
# ... for the build tree
set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/lib/include" "${PROJECT_BINARY_DIR}/lib")
configure_file(libBlockchainConfig.cmake.in
        "${PROJECT_BINARY_DIR}/libBlockchainConfig.cmake" @ONLY)
# ... for the install tree
set(CONF_INCLUDE_DIRS "\${LIBBLOCKCHAIN_CMAKE_DIR}/${REL_INCLUDE_DIR}")
configure_file(libBlockchainConfig.cmake.in
        "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/libBlockchainConfig.cmake" @ONLY)
# ... for both
configure_file(libBlockchainConfigVersion.cmake.in
        "${PROJECT_BINARY_DIR}/libBlockchainConfigVersion.cmake" @ONLY)

## Install target

# Libraries
install(TARGETS Blockchain BlockchainStatic
  EXPORT ${PROJECT_NAME}Targets
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT ${PROJECT_NAME}Targets DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

# Headers
install(DIRECTORY "${PROJECT_SOURCE_DIR}/lib/include/" TYPE INCLUDE)

# CMake configuration
install(FILES
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/libBlockchainConfig.cmake"
  "${PROJECT_BINARY_DIR}/libBlockchainConfigVersion.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")
