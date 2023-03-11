#ifndef API_MONGODB_CPLUSPLUS_SRC_API_CONTROLLERS_USERCONTROLLER_HPP
#define API_MONGODB_CPLUSPLUS_SRC_API_CONTROLLERS_USERCONTROLLER_HPP

#include "../data/dto/JsonUser.hpp"
#include "../data/dto/JsonUserLogin.hpp"
#include "../data/repository/UserRepository.hpp"

#include "oatpp-swagger/Types.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include "oatpp/core/data/stream/BufferStream.hpp"

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

namespace App
{
    namespace Controller
    {

        class UserController : public oatpp::web::server::api::ApiController
        {
        private:
            OATPP_COMPONENT(std::shared_ptr<App::Data::Database::UserRepository>, userRepository);

        public:
            UserController(const std::shared_ptr<ObjectMapper> &objectMapper)
                : oatpp::web::server::api::ApiController(objectMapper)
            {
            }

        public:
            static std::shared_ptr<UserController> createShared(
                OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
            {
                return std::make_shared<UserController>(objectMapper);
            }

            ENDPOINT_INFO(createUser)
            {
                info->summary = "Create new User";
                info->addConsumes<Object<App::Data::Json::JsonUser>>("application/json");
                info->addResponse<Object<App::Data::Json::JsonUser>>(Status::CODE_200, "application/json");
            }
            ENDPOINT("POST", "demo/api/users", createUser,
                     BODY_DTO(Object<App::Data::Json::JsonUser>, userDto))
            {
                
                printf("OK ----------");
                
                return createDtoResponse(Status::CODE_200, userRepository->create(userDto));
            }

            ENDPOINT_INFO(putUser)
            {
                // general
                info->summary = "Update User by username";
                info->addConsumes<Object<App::Data::Json::JsonUser>>("application/json");
                info->addResponse<Object<App::Data::Json::JsonUser>>(Status::CODE_200, "application/json");
                info->addResponse<String>(Status::CODE_404, "text/plain");
                // params specific
                info->pathParams["username"].description = "username/login";
            }
            ENDPOINT("PUT", "demo/api/users/{username}", putUser,
                     PATH(String, username),
                     BODY_DTO(Object<App::Data::Json::JsonUser>, userDto))
            {
                userDto->username = username;
                return createDtoResponse(Status::CODE_200, userRepository->update(userDto));
            }

            ENDPOINT_INFO(getUser)
            {
                // general
                info->summary = "Get one User by username";
                info->addResponse<Object<App::Data::Json::JsonUser>>(Status::CODE_200, "application/json");
                info->addResponse<String>(Status::CODE_404, "text/plain");
                // params specific
                info->pathParams["username"].description = "username/login";
            }
            ENDPOINT("GET", "demo/api/users/{username}", getUser,
                     PATH(String, username))
            {
                auto user = userRepository->getOne(username);
                OATPP_ASSERT_HTTP(user, Status::CODE_404, "User not found");
                return createDtoResponse(Status::CODE_200, user);
            }

            ENDPOINT_INFO(getAllUsers)
            {
                info->summary = "get all stored users";
                info->addResponse<List<Object<App::Data::Json::JsonUser>>>(Status::CODE_200, "application/json");
            }
            ENDPOINT("GET", "demo/api/users", getAllUsers)
            {
                return createDtoResponse(Status::CODE_200, userRepository->getAll());
            }

            ENDPOINT_INFO(deleteUser)
            {
                // general
                info->summary = "Delete User by username";
                info->addResponse<String>(Status::CODE_200, "text/plain");
                info->addResponse<String>(Status::CODE_404, "text/plain");
                // params specific
                info->pathParams["username"].description = "username/login";
            }
            ENDPOINT("DELETE", "demo/api/users/{username}", deleteUser,
                     PATH(String, username))
            {
                bool success = userRepository->deleteOne(username);
                OATPP_ASSERT_HTTP(success, Status::CODE_500, "User not deleted. Perhaps no such User in the Database");
                return createResponse(Status::CODE_200, "User successfully deleted");
            }
        };

    }
}
#include OATPP_CODEGEN_END(ApiController)

#endif /* example_oatpp_mongo_UserController_hpp */
