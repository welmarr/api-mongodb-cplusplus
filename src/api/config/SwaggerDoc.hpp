
#ifndef API_MONGODB_CPLUSPLUS_SRC_API_CONFIG_SWAGGERDOC_HPP
#define API_MONGODB_CPLUSPLUS_SRC_API_CONFIG_SWAGGERDOC_HPP

#include "oatpp-swagger/Model.hpp"
#include "oatpp-swagger/Resources.hpp"
#include "oatpp/core/macro/component.hpp"

namespace App
{
    namespace Config
    {

        /**
         *  Swagger ui is served at
         *  http://host:port/swagger/ui
         */
        class SwaggerDoc
        {
        public:
            /**
             *  General API docs info
             */
            OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::DocumentInfo>, swaggerDocumentInfo)
            ([]
             {
                 oatpp::swagger::DocumentInfo::Builder builder;

                 builder
                     .setTitle("Example Project - Oat++ MongoDB")
                     .setDescription("Example project how-to work with MongoDB using oatpp-mongo module")
                     .setVersion("1.0")
                     .setContactName("Mr. Porridge")
                     .setContactUrl("https://oatpp.io/")

                     .addServer("http://172.27.218.204:8000", "server on localhost");

                 return builder.build(); }());

            /**
             *  Swagger-Ui Resources (<oatpp-examples>/lib/oatpp-swagger/res)
             */
            OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::Resources>, swaggerResources)
            ([]
             {
                // Make sure to specify correct full path to oatpp-swagger/res folder !!!
                return oatpp::swagger::Resources::loadResources(OATPP_SWAGGER_RES_PATH); }());
        };

    }
}
#endif