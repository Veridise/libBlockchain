add_library(BlockchainObjects OBJECT)
add_library(Blockchain SHARED $<TARGET_OBJECTS:BlockchainObjects>)
add_library(BlockchainStatic STATIC $<TARGET_OBJECTS:BlockchainObjects>)
add_library(BlockchainTest SHARED)

include_directories(
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDE_DIR}/include>
)
add_subdirectory(src)
add_subdirectory(test)

# Use C++11 to compile your pass (i.e., supply -std=c++11).
target_compile_features(Blockchain PRIVATE cxx_range_for cxx_auto_type)
target_compile_features(BlockchainStatic PRIVATE cxx_range_for cxx_auto_type)
target_compile_features(BlockchainTest PRIVATE cxx_range_for cxx_auto_type)

target_link_libraries(BlockchainTest PUBLIC BlockchainStatic)
#set_target_properties(BlockchainTest PROPERTIES LINK_FLAGS "-lBlockchainStatic")

# LLVM is (typically) built with no C++ RTTI. We need to match that;
# otherwise, we'll get linker errors about missing RTTI data.
set_target_properties(Blockchain PROPERTIES
    COMPILE_FLAGS "-fno-rtti"
)
set_target_properties(BlockchainStatic PROPERTIES
    COMPILE_FLAGS "-fno-rtti"
)

set_target_properties(BlockchainTest PROPERTIES
    COMPILE_FLAGS "-fno-rtti"
)

# Get proper shared-library behavior (where symbols are not necessarily
# resolved when the shared library is linked) on OS X.
if(APPLE)
    set_target_properties(Blockchain PROPERTIES
        LINK_FLAGS "-undefined dynamic_lookup"
    )   
    set_target_properties(BlockchainStatic PROPERTIES
        LINK_FLAGS "-undefined dynamic_lookup"
    )
    set_target_properties(BlockchainTest PROPERTIES
        LINK_FLAGS "-undefined dynamic_lookup"
    )
endif(APPLE)
