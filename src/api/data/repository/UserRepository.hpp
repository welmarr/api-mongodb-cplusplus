#ifndef API_MONGODB_CPLUSPLUS_SRC_API_DATA_REPOSITORY_USERREPOSITORY_HPP
#define API_MONGODB_CPLUSPLUS_SRC_API_DATA_REPOSITORY_USERREPOSITORY_HPP

#include "../Connexion.hpp"

#include "../dto/JsonUser.hpp"
#include "../model/User.hpp"

#include "oatpp-mongo/bson/mapping/ObjectMapper.hpp"

#include <mongocxx/pool.hpp>
#include <bsoncxx/document/value.hpp>

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

namespace App
{
    namespace Data
    {

        namespace Database
        {
            class UserRepository
            {
            private:
                oatpp::Object<App::Data::Database::Model::User> userFromJson(const oatpp::Object<App::Data::Json::JsonUser> &dto);
                oatpp::Object<App::Data::Json::JsonUser> jsonFromUser(const oatpp::Object<App::Data::Database::Model::User> &user);

            public:
                UserRepository(const std::string &cName);
                bool deleteOne(const oatpp::String &username);

                oatpp::Object<App::Data::Json::JsonUser> create(const oatpp::Object<App::Data::Json::JsonUser> &userDto);
                oatpp::Object<App::Data::Json::JsonUser> update(const oatpp::Object<App::Data::Json::JsonUser> &userDto);

                oatpp::Object<App::Data::Json::JsonUser> getOne(const oatpp::String &username);
                oatpp::List<oatpp::Object<App::Data::Json::JsonUser>> getAll();

            private:
                std::string collectionName;
                oatpp::mongo::bson::mapping::ObjectMapper s_objectMapper;
                OATPP_COMPONENT(std::shared_ptr<App::Data::Database::Connexion>, connexxion);
            };

        }
    }
}
#endif