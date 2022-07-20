# use existing rapidjson config
find_package(RapidJSON REQUIRED CONFIG)
if (RapidJSON_FOUND AND NOT TARGET RapidJSON::RapidJSON)
    add_library(RapidJSON::RapidJSON INTERFACE IMPORTED)
    target_include_directories(RapidJSON::RapidJSON INTERFACE ${RapidJSON_INCLUDE_DIRS})
endif()
