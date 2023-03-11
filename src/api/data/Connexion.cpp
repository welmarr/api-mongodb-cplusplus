#include "oatpp/core/data/stream/BufferStream.hpp"

#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/options/insert.hpp>
#include <mongocxx/exception/operation_exception.hpp>
#include "Connexion.hpp"

namespace App
{
    namespace Data
    {

        namespace Database
        {

            Connexion::Connexion(const mongocxx::uri &uri, const std::string &dbName)
                : m_pool(std::make_shared<mongocxx::pool>(uri)), m_databaseName(dbName)
            {
            }

            auto Connexion::getConnexionAcquire(){
                return m_pool->acquire();
            }

             std::shared_ptr<mongocxx::pool> Connexion::getPool(){
                return m_pool;
            }

            std::string  Connexion::getDatabaseName(){
                return m_databaseName;
            }

            bsoncxx::document::value Connexion::createMongoDocument(const oatpp::Void &polymorph)
            {
                // if you have huge docs, you may want to increase starting BufferOutputStream size.
                // Or you may want to use oatpp::Data::stream::ChunkedBuffer instead - for no-copy growth.
                oatpp::data::stream::BufferOutputStream stream;
                m_objectMapper.write(&stream, polymorph);
                bsoncxx::document::view view(stream.getData(), stream.getCurrentPosition());
                return bsoncxx::document::value(view);
            }

            oatpp::mongo::bson::mapping::ObjectMapper Connexion::getObjectMapper()
            {
                return m_objectMapper;
            }
        }
    }
}
