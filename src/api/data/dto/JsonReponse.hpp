#ifndef API_MONGODB_CPLUSPLUS_SRC_API_DATA_DTO_JSONREPONSE_HPP
#define API_MONGODB_CPLUSPLUS_SRC_API_DATA_DTO_JSONREPONSE_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

namespace App
{
  namespace Data
  {

    namespace Json
    {
      class JsonReponse : public oatpp::DTO
      {

        DTO_INIT(JsonReponse, DTO)

        DTO_FIELD(String, status);
        DTO_FIELD(Any, data);
        DTO_FIELD(String, msg);
      };
    }

  }
}

#include OATPP_CODEGEN_END(DTO)

#endif
