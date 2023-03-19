cmake_minimum_required(VERSION 3.1)

set(project_name api-moc-plusplus)

project(${project_name})

set(CMAKE_CXX_STANDARD 14)

add_library(${project_name}-lib
        src/api/data/Connexion.cpp
        src/api/data/Connexion.hpp
        src/api/data/model/User.hpp
        src/api/data/dto/JsonUser.hpp
        src/api/data/dto/JsonUserLogin.hpp
        src/api/data/repository/UserRepository.cpp
        src/api/data/repository/UserRepository.hpp
        src/api/config/SwaggerDoc.hpp
        src/api/controllers/UserController.hpp
        src/api/AppConfig.hpp
        src/utility/UUID.hpp
        src/utility/Time.hpp)

###################################################################
# Find mongocxx

find_package(mongocxx REQUIRED)

message("LIBBSONCXX_INCLUDE_DIRS=${LIBBSONCXX_INCLUDE_DIRS}")
message("LIBBSONCXX_LIBRARIES=${LIBBSONCXX_LIBRARIES}")

message("LIBMONGOCXX_INCLUDE_DIRS=${LIBMONGOCXX_INCLUDE_DIRS}")
message("LIBMONGOCXX_LIBRARIES=${LIBMONGOCXX_LIBRARIES}")

###################################################################

find_package(oatpp          1.3.0 REQUIRED)
find_package(oatpp-swagger  1.3.0 REQUIRED)
find_package(oatpp-mongo    1.3.0 REQUIRED)

## include directories

target_include_directories(${project_name}-lib
        PUBLIC src
)

## link libs

target_link_libraries(${project_name}-lib
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-swagger
        PUBLIC oatpp::oatpp-mongo
)

target_link_libraries(${project_name}-lib
        PUBLIC bcrypt
)

if (TARGET mongo::mongocxx_shared)
    target_link_libraries(${project_name}-lib
            PUBLIC mongo::mongocxx_shared
    )
    message("mongo::mongocxx_shared is used")
elseif(TARGET mongo::mongocxx_static)
    target_link_libraries(${project_name}-lib
            PUBLIC mongo::mongocxx_static
    )
endif()

## define path to swagger-ui res folder

add_definitions(
        -DOATPP_SWAGGER_RES_PATH="${oatpp-swagger_INCLUDE_DIRS}/../bin/oatpp-swagger/res"
)

#################################################################
## add executables

add_executable(${project_name}
        src/main.cpp
)

target_link_libraries(${project_name} ${project_name}-lib)
add_dependencies(${project_name} ${project_name}-lib)