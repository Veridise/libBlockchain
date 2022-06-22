add_library(BlockchainObjects OBJECT)
add_library(Blockchain SHARED)
add_library(BlockchainStatic STATIC)
add_library(BlockchainTest SHARED)

add_subdirectory(src)
add_subdirectory(test)

target_include_directories(BlockchainObjects PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
  ${LLVM_INCLUDE_DIRS}
)
separate_arguments(llvm_defs NATIVE_COMMAND ${LLVM_DEFINITIONS})
target_compile_definitions(BlockchainObjects PUBLIC ${llvm_defs})
target_link_libraries(BlockchainObjects PUBLIC LLVMTarget RapidJSON::RapidJSON)
llvm_update_compile_flags(BlockchainObjects)

# reenable exceptions (if needed) since we might use them
target_compile_options(BlockchainObjects PRIVATE "-fexceptions")


target_link_libraries(Blockchain PUBLIC BlockchainObjects)
target_link_libraries(BlockchainStatic PUBLIC BlockchainObjects)
target_link_libraries(BlockchainTest PUBLIC Blockchain)

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


## Install target

install(TARGETS Blockchain BlockchainStatic BlockchainObjects
  EXPORT ${LIBBLOCKCHAIN_TARGET_EXPORT}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/" TYPE INCLUDE)
