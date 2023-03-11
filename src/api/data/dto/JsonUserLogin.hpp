#ifndef API_MONGODB_CPLUSPLUS_SRC_API_DATA_DTO_JSONUSER_HPP
#define API_MONGODB_CPLUSPLUS_SRC_API_DATA_DTO_JSONUSER_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

namespace App
{
  namespace Data
  {

    namespace Database
    {

      namespace Json
      {
        class JsonUserLogin : public oatpp::DTO
        {

          DTO_INIT(JsonUserLogin, DTO)

          DTO_FIELD(String, username);
          DTO_FIELD(String, password);
        };
      }
    }
  }
}

#include OATPP_CODEGEN_END(DTO)

#endif
