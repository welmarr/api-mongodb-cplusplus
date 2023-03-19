
#ifndef API_MONGODB_CPLUSPLUS_SRC_API_CONFIG_AUTH_AUTHENTICATEHANDLER_HPP
#define API_MONGODB_CPLUSPLUS_SRC_API_CONFIG_AUTH_AUTHENTICATEHANDLER_HPP

#include "oatpp/web/server/handler/AuthorizationHandler.hpp"
#include "./AuthenticateObject.hpp"
#include "Poco/JWT/Token.h"
#include "Poco/JWT/Signer.h"
namespace App
{
    namespace Config
    {
        namespace Auth
        {
            class AuthenticateHandler : public oatpp::web::server::handler::BearerAuthorizationHandler
            {
                AuthenticateHandler()
                    : oatpp::web::server::handler::BearerAuthorizationHandler("custom-bearer-realm")
                {
                }

                std::shared_ptr<AuthorizationObject> authorize(const oatpp::String &token) override
                {
                    std::cout << "----------------------------------------- " << token << std::endl;

                    Poco::JWT::Signer signer("0123456789ABCDEF0123456789ABCDEF");
                    Poco::JWT::Token token = signer.verify(token);

                    if (token == "4e99e8c12de7e01535248d2bac85e732")
                    {
                        auto obj = std::make_shared<App::Config::Auth::AuthenticateObject>();
                        obj->user = "foo";
                        obj->password = "bar";
                        obj->token = token;
                        return obj;
                    }

                    return nullptr;
                }
            };
        }
    }
}

#endif