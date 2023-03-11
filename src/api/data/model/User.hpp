#ifndef API_MONGODB_CPLUSPLUS_SRC_API_DATA_MODEL_USER_HPP
#define API_MONGODB_CPLUSPLUS_SRC_API_DATA_MODEL_USER_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

namespace App
{
    namespace Data
    {

        namespace Database
        {

            namespace Model
            {
                class User : public oatpp::DTO
                {

                    DTO_INIT(User, DTO)

                    DTO_FIELD(String, _id);
                    DTO_FIELD(String, username);
                    DTO_FIELD(String, password);
                    DTO_FIELD(Boolean, active);
                    DTO_FIELD(String, role);
                    DTO_FIELD(String, created_at);
                    DTO_FIELD(String, updated_at);
                    DTO_FIELD(String, deleted_at);
                };

            }
        }
    }
}

#include OATPP_CODEGEN_END(DTO)
#endif
