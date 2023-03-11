#ifndef API_MONGODB_CPLUSPLUS_SRC_API_APPCONFIG_HPP
#define API_MONGODB_CPLUSPLUS_SRC_API_APPCONFIG_HPP

#include "./data/Connexion.hpp"
#include "./utility/SwaggerDoc.hpp"
#include "./data/repository/UserRepository.hpp"

#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/web/server/HttpRouter.hpp"

#include "oatpp/network/tcp/server/ConnectionProvider.hpp"

#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include "oatpp/core/base/CommandLineArguments.hpp"
#include "oatpp/core/macro/component.hpp"

#include <mongocxx/client.hpp>

/**
 *  Class which creates and holds Application components and registers components in oatpp::base::Environment
 *  Order of components initialization is from top to bottom
 */
class AppComponent
{
private:
  oatpp::base::CommandLineArguments m_cmdArgs;

public:
  AppComponent(const oatpp::base::CommandLineArguments &cmdArgs)
      : m_cmdArgs(cmdArgs)
  {
  }

public:
  /**
   *  Swagger component
   */
  App::Utility::SwaggerDoc swaggerComponent;

  /**
   *  Create ConnectionProvider component which listens on the port
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider)
  ([]
   { return oatpp::network::tcp::server::ConnectionProvider::createShared({"0.0.0.0", 8000, oatpp::network::Address::IP_4}); }());

  /**
   *  Create Router component
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)
  ([]
   { return oatpp::web::server::HttpRouter::createShared(); }());

  /**
   *  Create ConnectionHandler component which uses Router component to route requests
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, serverConnectionHandler)
  ([]
   {
    
    OATPP_LOGI("Config", "ROUTE HANDELER INITIALISATION")
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router); // get Router component
    return oatpp::web::server::HttpConnectionHandler::createShared(router); }());

  /**
   *  Create ObjectMapper component to serialize/deserialize DTOs in Contoller's API
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper)
  ([]
   {
    auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
    objectMapper->getDeserializer()->getConfig()->allowUnknownFields = false;
    objectMapper->getSerializer()->getConfig()->useBeautifier = true;
    return objectMapper; }());

  OATPP_CREATE_COMPONENT(std::shared_ptr<App::Data::Database::Connexion>, cdatabase)
  ([this]
   {
    OATPP_LOGI("Config", "DATABASE INITIALISATION")


     oatpp::String connectionString = std::getenv("DEMO_MONGO_CONN_STR");
     if (!connectionString)
     {
       connectionString = m_cmdArgs.getNamedArgumentValue("--conn-str", "mongodb://172.27.208.1:27017/welmarr");
     }
     std::cout << "Connection link = " << *connectionString << std::endl;
     mongocxx::uri uri(*connectionString);
     return std::make_shared<App::Data::Database::Connexion>(uri, "welmarr");
   }());

   
  OATPP_CREATE_COMPONENT(std::shared_ptr<App::Data::Database::UserRepository>, cuserRepository)
  ([this]
   {
    
    OATPP_LOGI("Config", "USER REPOSITORY INITIALISATION")
     return std::make_shared<App::Data::Database::UserRepository>("users");
   }());
};

#endif /* example_oatpp_mongo_AppComponent_hpp */
