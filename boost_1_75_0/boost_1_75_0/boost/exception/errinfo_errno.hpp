//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_F0EE17BE6C1211DE87FF459155D89593
#define BOOST_EXCEPTION_F0EE17BE6C1211DE87FF459155D89593

#include <boost/exception/info.hpp>
#include <errno.h>
#include <string.h>

#ifndef BOOST_EXCEPTION_ENABLE_WARNINGS
#if __GNUC__*100+__GNUC_MINOR__>301
#pragma GCC system_header
#endif
#ifdef __clang__
#pragma clang system_header
#endif
#ifdef _MSC_VER
#pragma warning(push,1)
#pragma warning(disable:4996)
#endif
#endif

namespace
boost
    {
    typedef error_info<struct errinfo_errno_,int> errinfo_errno;

    //Usage hint:
    //if( c_function(....)!=0 )
    //    BOOST_THROW_EXCEPTION(
    //        failure() <<
    //        errinfo_errno(errno) <<
    //        errinfo_api_function("c_function") );
    inline
    std::string
    to_string( errinfo_errno const & e )
        {
        std::ostringstream tmp;
        int v=e.value();
        tmp  << '[' << error_info_name(e) << "] = " << v << ", \"" << strerror(v) << "\"\n";
        return tmp.str();
        }
    }

#if defined(_MSC_VER) && !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(pop)
#endif
#endif

/* errinfo_errno.hpp
szpulmv+Ku7V9RGL1OsKKkGfQ2d9jzGdyDE/7A1uZj50k2vWwEfoycbz3dDB7kWyg0XiWX5ZX/z+Trr1hPz+rsvV99eKl/6tvj/G/v086/u3n09PctXU2nlbi+1BxYDxDEJV87FAcPacgimX5KKxP9vfJMP/acUB19M1mQIJIB5GtMkIDk+WjgNxGyzXq4Hg5SRXHJjqVk9wcCfwAZoECs3uZ8S3D7hmSJJRqFhYoaZr5LKu0bwfKXS5yqMk5J4TfaXcwwnHYBug/OegWIQauJ6+DvaLxvE+Gi3tMe+O5hi4G9tglcJrbmzo7E0ecojIGz5Q2y0HT4GtRsTBAlx/yW0HlYWxnlbPaHa7XxYNZWVw/63lE2XN77sSNt/qD+Tmm5V2ls13Xl/YfHelhWy+F6PE5lsrN9+xPnLz+aNIGqLjaSicpmw09/0O1h1xoxzcnA6mDV/iCUslFA2i01rrCcGfeVEaiopuZa8xOJMvwTepQDfkee1jHbAbEUUF5PPgHrrLboUDl3no5ym7An3e8E7JFbq/+5k+lqLvjrI5mbeZLzZX/m6h5veGA5fVzdnBfDKNcCKB8wu7oEYmjxL879+8ICfw7gSYwDQxoDvwzT8vR2YMcaAvABP6Ea/NjKo2UTAiZx+LDc2A1DXhxyG2AIoA1potm+se+KtEP1OBCf3VjEc1Pk1m5qsIIgscoYZxsRhG3YMo4harEaTg
*/