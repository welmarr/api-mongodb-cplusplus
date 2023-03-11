/*
    function which uses std::put_time with a std::ostringstream to generate the resulting std::string
    https://techoverflow.net/2018/03/30/iso8601-utc-time-as-stdstring-using-c11-chrono/
*/

#ifndef API_MONGODB_CPLUSPLUS_SRC_API_UTILITY_TIME_HPP
#define API_MONGODB_CPLUSPLUS_SRC_API_UTILITY_TIME_HPP
#include <chrono>
#include <iomanip>
#include <sstream>
namespace App
{
    namespace Utility
    {

        namespace Time
        {
            /**
             * Generate a UTC ISO8601-formatted timestamp
             * and return as std::string
             */
            std::string currentISO8601TimeUTC()
            {
                auto now = std::chrono::system_clock::now();
                auto itt = std::chrono::system_clock::to_time_t(now);
                std::ostringstream ss;
                ss << std::put_time(gmtime(&itt), "%FT%TZ");
                return ss.str();
            }

        }
    }
}
#endif