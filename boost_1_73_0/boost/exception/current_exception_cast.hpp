//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_7E83C166200811DE885E826156D89593
#define BOOST_EXCEPTION_7E83C166200811DE885E826156D89593

#ifndef BOOST_EXCEPTION_ENABLE_WARNINGS
#if __GNUC__*100+__GNUC_MINOR__>301
#pragma GCC system_header
#endif
#ifdef __clang__
#pragma clang system_header
#endif
#ifdef _MSC_VER
#pragma warning(push,1)
#endif
#endif

namespace
boost
    {
    template <class E>
    inline
    E *
    current_exception_cast()
        {
        try
            {
            throw;
            }
        catch(
        E & e )
            {
            return &e;
            }
        catch(
        ...)
            {
            return 0;
            }
        }
    }

#if defined(_MSC_VER) && !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(pop)
#endif
#endif

/* current_exception_cast.hpp
wbAxHAKbwEzYCg6FneEZsCccCTPheDgKToBj4RQ4Qd2dCifD09R+mtqfpf7z4Rg4X+3127faB9CfWb59O0PTnQPlWQnTYD5sCudovs51dB8E7Abnw+5wAewHi+AgWAKHwFI4Bi6CE2E5PAUuhVPgOXA6PBfOhMvhHLgCzoOr4EJ4AVwOL4QpP+Naq32d9Yfvl7fsk/d8D+CH75E/4K6rns++eCQLKTz/xDrrid+J3//z72ed
*/