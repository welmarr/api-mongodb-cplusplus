
#ifndef API_MONGODB_CPLUSPLUS_SRC_API_CONFIG_AUTH_AUTHENTICATEOBJECT_HPP
#define API_MONGODB_CPLUSPLUS_SRC_API_CONFIG_AUTH_AUTHENTICATEOBJECT_HPP

#include "oatpp/web/server/handler/AuthorizationHandler.hpp"
namespace App
{
    namespace Config
    {
        class AuthenticateObject : public oatpp::web::server::handler::AuthorizationObject
        {
        public:
            oatpp::String user;
            oatpp::String password;
            oatpp::String token;
        };
    }
}

#endif