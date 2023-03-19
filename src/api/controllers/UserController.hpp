#ifndef API_MONGODB_CPLUSPLUS_SRC_API_CONTROLLERS_USERCONTROLLER_HPP
#define API_MONGODB_CPLUSPLUS_SRC_API_CONTROLLERS_USERCONTROLLER_HPP

#include "../data/dto/JsonUser.hpp"
#include "../data/dto/JsonUserCreateOrUpdate.hpp"
#include "../data/dto/JsonUserLogin.hpp"
#include "../data/repository/UserRepository.hpp"
#include "../data/dto/JsonReponse.hpp"

#include "oatpp-swagger/Types.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include "oatpp/core/data/stream/BufferStream.hpp"

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#include "oatpp/core/utils/ConversionUtils.hpp"
#include "../config/Auth/AuthenticateHandler.hpp"
#include "../config/Auth/AuthenticateObject.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

namespace App
{
    namespace Controller
    {
        class UserController : public oatpp::web::server::api::ApiController
        {
        private:
            OATPP_COMPONENT(std::shared_ptr<App::Data::Database::UserRepository>, userRepository);
            std::shared_ptr<AuthorizationHandler> m_authHandler = std::make_shared<App::Config::Auth::AuthenticateHandler>();

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
                info->addConsumes<Object<App::Data::Json::JsonUserCreateOrUpdate>>("application/json");
                info->addResponse<Object<App::Data::Json::JsonReponse>>(Status::CODE_200, "application/json");
            }
            ENDPOINT("POST", "moc-plusplus/api/users", createUser,
                     BODY_DTO(Object<App::Data::Json::JsonUserCreateOrUpdate>, userDto))
            {

                auto out = App::Data::Json::JsonReponse::createShared();
                try
                {

                    oatpp::Object<App::Data::Json::JsonUser> data = userRepository->create(userDto);
                    out->data = data;
                    out->status = (data ? Status::CODE_200.description : Status::CODE_409.description);
                    out->msg = (data ? "" : "Email already used");

                    return createDtoResponse(data ? Status::CODE_200 : Status::CODE_409, out);
                }
                catch (const std::exception &e)
                {
                    out->msg = e.what();
                    out->status = Status::CODE_500.description;

                    return createDtoResponse(Status::CODE_500, out);
                }
            }

            ENDPOINT_INFO(putUser)
            {
                // general
                info->summary = "Update User by username";
                info->addConsumes<Object<App::Data::Json::JsonUserCreateOrUpdate>>("application/json");
                info->addResponse<Object<App::Data::Json::JsonUser>>(Status::CODE_200, "application/json");
                info->addResponse<String>(Status::CODE_404, "text/plain");
                // params specific
                info->pathParams["username"].description = "username/login";
            }
            ENDPOINT("PUT", "moc-plusplus/api/users/{username}", putUser,
                     PATH(String, username),
                     BODY_DTO(Object<App::Data::Json::JsonUserCreateOrUpdate>, userDto))
            {
                userDto->username = username;
                return createDtoResponse(Status::CODE_200, userRepository->update(userDto));
            }

            ENDPOINT_INFO(getUser)
            {
                // general
                info->summary = "Get one User by username";
                info->addResponse<Object<App::Data::Json::JsonReponse>>(Status::CODE_200, "application/json");
                info->addResponse<String>(Status::CODE_404, "text/plain");
                // params specific
                info->pathParams["username"].description = "username/login";
            }
            ENDPOINT("GET", "moc-plusplus/api/users/{username}", getUser,
                     PATH(String, username))
            {
                auto out = App::Data::Json::JsonReponse::createShared();
                try
                {

                    oatpp::Object<App::Data::Json::JsonUser> data = userRepository->getOne(username);
                    out->data = data;
                    out->status = (data ? Status::CODE_200.description : Status::CODE_404.description);
                    out->msg = (data ? "" : "User not found");

                    return createDtoResponse(data ? Status::CODE_200 : Status::CODE_404, out);
                }
                catch (const std::exception &e)
                {
                    out->msg = e.what();
                    out->status = Status::CODE_500.description;

                    return createDtoResponse(Status::CODE_500, out);
                }
            }

            ENDPOINT_INFO(getAllUsers)
            {
                info->summary = "get all stored users";
                info->addResponse<Object<App::Data::Json::JsonReponse>>(Status::CODE_200, "application/json");
            }
            ENDPOINT("GET", "moc-plusplus/api/users", getAllUsers)
            {
                auto out = App::Data::Json::JsonReponse::createShared();
                try
                {

                    oatpp::List<oatpp::Object<App::Data::Json::JsonUser>> data = userRepository->getAll();
                    out->data = data;
                    out->status = (Status::CODE_200.description);

                    return createDtoResponse(Status::CODE_200, out);
                }
                catch (const std::exception &e)
                {
                    out->msg = e.what();
                    out->status = Status::CODE_500.description;

                    return createDtoResponse(Status::CODE_500, out);
                }
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
            ENDPOINT("DELETE", "moc-plusplus/api/users/{username}", deleteUser,
                     PATH(String, username))
            {
                
                auto out = App::Data::Json::JsonReponse::createShared();
                try
                {
                    bool success = userRepository->deleteOne(username);
                    out->status = (success ? Status::CODE_500.description : Status::CODE_200.description);
                    out->msg = (success ? "User not deleted. Perhaps no such User in the Database" : "User successfully deleted");

                    return createDtoResponse(Status::CODE_200, out);
                }
                catch (const std::exception &e)
                {
                    out->msg = e.what();
                    out->status = Status::CODE_500.description;

                    return createDtoResponse(Status::CODE_500, out);
                }
            }
        };

    }
}
#include OATPP_CODEGEN_END(ApiController)

#endif /* example_oatpp_mongo_UserController_hpp */
