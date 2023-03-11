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

      namespace MODEL
      {
        class Document : public oatpp::DTO
        {

          DTO_INIT(Document, DTO)

          DTO_FIELD(String, user_id);
          DTO_FIELD(String, created_at);
          DTO_FIELD(String, updated_at);
          DTO_FIELD(String, deleted_at);
          DTO_FIELD(Any, Data);
        };
      }
    }
  }
}

#include OATPP_CODEGEN_END(DTO)

#endif
