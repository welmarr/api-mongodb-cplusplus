#include "UserRepository.hpp"
#include "../../../utility/UUID.hpp"
#include "../../../utility/Time.hpp"

#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/options/insert.hpp>
#include <mongocxx/exception/operation_exception.hpp>
#include "bcrypt/BCrypt.hpp"

namespace App
{
    namespace Data
    {

        namespace Database
        {
            oatpp::Object<App::Data::Database::Model::User> UserRepository::userFromJson(const oatpp::Object<App::Data::Json::JsonUser> &dto)
            {
                auto user = App::Data::Database::Model::User::createShared();
                user->_id = App::Utility::UUID::generate_uuid_v4();
                user->username = dto->username;
                user->active = dto->active;
                user->role = dto->role;
                user->created_at = App::Utility::Time::currentISO8601TimeUTC();
                user->updated_at = user->created_at;
                return user;
            }

            oatpp::Object<App::Data::Database::Model::User> UserRepository::userFromCreationOrUpdatingJson(const oatpp::Object<App::Data::Json::JsonUserCreateOrUpdate> &dto)
            {
                auto user = App::Data::Database::Model::User::createShared();
                user->_id = App::Utility::UUID::generate_uuid_v4();
                user->username = dto->username;
                user->password = BCrypt::generateHash(dto->password);
                user->active = dto->active;
                user->role = dto->role;
                user->created_at = App::Utility::Time::currentISO8601TimeUTC();
                user->updated_at = user->created_at;
                return user;
            }

            oatpp::Object<App::Data::Json::JsonUser> UserRepository::jsonFromUser(const oatpp::Object<App::Data::Database::Model::User> &user)
            {
                auto dto = App::Data::Json::JsonUser::createShared();
                dto->id = user->_id;
                dto->username = user->username;
                dto->active = user->active;
                dto->role = user->role;
                dto->created_at = user->created_at;
                dto->updated_at = user->updated_at;
                return dto;
            }

            UserRepository::UserRepository(const std::string &cName) : collectionName(cName)
            {
            }

            bool UserRepository::deleteOne(const oatpp::String &key)
            {
                auto connacquire = connexxion->getPool()->acquire();
                auto collection = (*connacquire)[connexxion->getDatabaseName()][collectionName];

                auto result =
                    collection.delete_one(connexxion->createMongoDocument(
                        oatpp::Fields<oatpp::String>({{"_id", key}})));

                if (result)
                {
                    return result->deleted_count() == 1;
                }
                return false;
            }

            oatpp::Object<App::Data::Json::JsonUser> UserRepository::create(const oatpp::Object<App::Data::Json::JsonUserCreateOrUpdate> &userDto)
            {
                auto connacquire = connexxion->getPool()->acquire();
                auto collection = (*connacquire)[connexxion->getDatabaseName()][collectionName];
                auto result = collection.find_one(connexxion->createMongoDocument(oatpp::Fields<oatpp::String>({{"username", userDto->username}})));

                if (result)
                {
                    return nullptr;
                }

                oatpp::Object<App::Data::Database::Model::User> user = userFromCreationOrUpdatingJson(userDto);

                collection.insert_one(connexxion->createMongoDocument(user));

                return jsonFromUser(user);
            }

            oatpp::Object<App::Data::Json::JsonUser> UserRepository::update(const oatpp::Object<App::Data::Json::JsonUserCreateOrUpdate> &userDto)
            {
                return oatpp::Object<App::Data::Json::JsonUser>();
            }

            oatpp::Object<App::Data::Json::JsonUser> UserRepository::getOne(const oatpp::String &key)
            {
                auto connacquire = connexxion->getPool()->acquire();
                auto collection = (*connacquire)[connexxion->getDatabaseName()][collectionName];

                auto result = collection.find_one(connexxion->createMongoDocument(oatpp::Fields<oatpp::String>({{"_id", key}})));

                if (result)
                {
                    auto view = result->view();
                    auto bson = oatpp::String((const char *)view.data(), view.length());
                    auto user = (connexxion->getObjectMapper()).readFromString<oatpp::Object<App::Data::Database::Model::User>>(bson);
                    return jsonFromUser(user);
                }

                return nullptr;
            }

            oatpp::List<oatpp::Object<App::Data::Json::JsonUser>> UserRepository::getAll()
            {
                auto connacquire = connexxion->getPool()->acquire();
                auto collection = (*connacquire)[connexxion->getDatabaseName()][collectionName];

                auto cursor = collection.find(connexxion->createMongoDocument(oatpp::Fields<oatpp::String>({})));

                oatpp::List<oatpp::Object<App::Data::Json::JsonUser>> list({});

                for (auto view : cursor)
                {
                    auto bson = oatpp::String((const char *)view.data(), view.length());
                    auto user = (connexxion->getObjectMapper()).readFromString<oatpp::Object<App::Data::Database::Model::User>>(bson);
                    list->push_back(jsonFromUser(user));
                }

                return list;
            }
        }
    }
}
