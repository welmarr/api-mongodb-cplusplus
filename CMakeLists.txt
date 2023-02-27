cmake_minimum_required(VERSION 3.16)
project(my-rest-api)

set(CMAKE_CXX_STANDARD 17)

# Find and link restbed
find_package(restbed CONFIG REQUIRED)
include_directories(${restbed_INCLUDE_DIRS})
link_libraries(${restbed_LIBRARIES})

# Find and link MongoDB C++ driver
find_package(libmongocxx REQUIRED)
include_directories(${libmongocxx_INCLUDE_DIRS})
link_libraries(${libmongocxx_LIBRARIES})

# Find and link nlohmann-json
find_package(nlohmann_json REQUIRED)
include_directories(${nlohmann_json_INCLUDE_DIRS})
link_libraries(${nlohmann_json_LIBRARIES})

# Find and link re2
find_package(RE2 REQUIRED)
include_directories(${RE2_INCLUDE_DIRS})
link_libraries(${RE2_LIBRARIES})

# Find and link gtest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
link_libraries(${GTEST_BOTH_LIBRARIES})

# Add source files to build executable
add_executable(my-rest-api
    src/main.cpp
    src/api/error.cpp
    src/api/request_handler.cpp
    src/api/route.cpp
    src/api/router.cpp
    src/api/singleton_mongo_client.cpp
    src/models/document.cpp
)

# Add include directories
target_include_directories(my-rest-api PRIVATE
    include/api
    include/models
)

# Set compile options
target_compile_options(my-rest-api PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

# Set linker options
target_link_options(my-rest-api PRIVATE
    -pthread
)

# Set install target
install(TARGETS my-rest-api DESTINATION bin)

# Add test executable
add_executable(api-restbed-mongodb-cplusplus
    test/test_main.cpp
    src/api/error.cpp
    src/api/request_handler.cpp
    src/api/route.cpp
    src/api/router.cpp
    src/api/singleton_mongo_client.cpp
    src/models/document.cpp
)

# Add include directories for test executable
target_include_directories(api-restbed-mongodb-cplusplus PRIVATE
    include/api
    include/models
)

# Set compile options for test executable
target_compile_options(api-restbed-mongodb-cplusplus PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    --coverage
)

# Set linker options for test executable
target_link_options(api-restbed-mongodb-cplusplus PRIVATE
    -pthread
    --coverage
)

# Link against restbed, libmongocxx, nlohmann_json, and RE2 libraries
target_link_libraries(api-restbed-mongodb-cplusplus PRIVATE
    ${restbed_LIBRARIES}
    ${libmongocxx_LIBRARIES}
    ${nlohmann_json_LIBRARIES}
    ${RE2_LIBRARIES}
)