#ifndef API_MONGODB_CPLUSPLUS_SRC_API_DATA_DTO_JSONUSERCREATEORUPDATE_HPP
#define API_MONGODB_CPLUSPLUS_SRC_API_DATA_DTO_JSONUSERCREATEORUPDATE_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

namespace App
{
  namespace Data
  {

    namespace Json
    {
      class JsonUserCreateOrUpdate : public oatpp::DTO
      {

        DTO_INIT(JsonUserCreateOrUpdate, DTO)

        DTO_FIELD(String, username);
        DTO_FIELD(String, password);
        DTO_FIELD(Boolean, active);
        DTO_FIELD(String, role);
      };
    }

  }
}

#include OATPP_CODEGEN_END(DTO)

#endif
