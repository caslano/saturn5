//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_FEE5120A6C1211DE94E8BC9155D89593
#define BOOST_EXCEPTION_FEE5120A6C1211DE94E8BC9155D89593

#include <string>

namespace
boost
    {
    template <class Tag,class T> class error_info;

    //Usage hint:
    //FILE * f=fopen(name,mode);
    //if( !f )
    //    BOOST_THROW_EXCEPTION(
    //        file_open_error() <<
    //        errinfo_file_name(name) <<
    //        errinfo_file_open_mode(mode) );
    typedef error_info<struct errinfo_file_name_,std::string> errinfo_file_name;
    }

#endif

/* errinfo_file_name.hpp
r/4N4wcPqX+4Dow0ca3jBOxVWAiuDda9DNe3Bz4vFt+xDR52w08Nx6s8erk1h9VL2EIJWyJhH0nYQQnTc2V1T7paXcQ/+tFHVxYZGX8Tfy797txKV7iQl+lqNOMn9KQZOI/hovUMxDcA4Pi4h3S8QoUSA+lldSjskcZkc0jywVR4Jj4giTMJjPNkEniRIHA7fOL8i+FzlPiOba5mKoHxKo/eUsphyyQsU5wnHchCKCSPXpb/wPAYJT0p8OUFiA4=
*/