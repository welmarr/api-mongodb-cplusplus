
#ifndef API_MONGODB_CPLUSPLUS_SRC_API_DATA_DATABASE_HPP
#define API_MONGODB_CPLUSPLUS_SRC_API_DATA_DATABASE_HPP

#include "oatpp-mongo/bson/mapping/ObjectMapper.hpp"

#include <mongocxx/pool.hpp>
#include <bsoncxx/document/value.hpp>

namespace App
{
  namespace Data
  {

    namespace Database
    {

      class Connexion
      {
      private:
        std::shared_ptr<mongocxx::pool> m_pool;
        std::string m_databaseName;
        oatpp::mongo::bson::mapping::ObjectMapper m_objectMapper;

      public:
        Connexion(const mongocxx::uri &uri, const std::string &dbName);
        auto getConnexionAcquire();
        std::string getDatabaseName();
        std::shared_ptr<mongocxx::pool> getPool();
        bsoncxx::document::value createMongoDocument(const oatpp::Void &polymorph);
        oatpp::mongo::bson::mapping::ObjectMapper getObjectMapper();
      };

    }
  }
}

#endif
