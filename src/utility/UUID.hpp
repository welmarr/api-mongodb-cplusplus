/*
    happy_sisyphus [Feb 12, 2020 at 22:52]
    https://stackoverflow.com/questions/24365331/how-can-i-generate-uuid-in-c-without-using-boost-library
*/

#ifndef API_MONGODB_CPLUSPLUS_SRC_API_UTILITY_UUID_HPP
#define API_MONGODB_CPLUSPLUS_SRC_API_UTILITY_UUID_HPP

#include <random>
#include <sstream>
namespace App
{
    namespace Utility
    {

        namespace UUID
        {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            static std::uniform_int_distribution<> dis(0, 15);
            static std::uniform_int_distribution<> dis2(8, 11);

            std::string generate_uuid_v4()
            {
                std::stringstream ss;
                int i;
                ss << std::hex;
                for (i = 0; i < 8; i++)
                {
                    ss << dis(gen);
                }
                ss << "-";
                for (i = 0; i < 4; i++)
                {
                    ss << dis(gen);
                }
                ss << "-4";
                for (i = 0; i < 3; i++)
                {
                    ss << dis(gen);
                }
                ss << "-";
                ss << dis2(gen);
                for (i = 0; i < 3; i++)
                {
                    ss << dis(gen);
                }
                ss << "-";
                for (i = 0; i < 12; i++)
                {
                    ss << dis(gen);
                };
                return ss.str();
            }
        }
    }
}

#endif