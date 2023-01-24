//Copyright (c) 2006-2010 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_C3E1741C754311DDB2834CCA55D89593
#define BOOST_EXCEPTION_C3E1741C754311DDB2834CCA55D89593

#include <boost/config.hpp>
#include <boost/core/typeinfo.hpp>
#include <boost/core/demangle.hpp>
#include <boost/current_function.hpp>
#include <string>

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
    template <class T>
    inline
    std::string
    tag_type_name()
        {
#ifdef BOOST_NO_TYPEID
        return BOOST_CURRENT_FUNCTION;
#else
        return core::demangle(typeid(T*).name());
#endif
        }

    template <class T>
    inline
    std::string
    type_name()
        {
#ifdef BOOST_NO_TYPEID
        return BOOST_CURRENT_FUNCTION;
#else
        return core::demangle(typeid(T).name());
#endif
        }

    namespace
    exception_detail
        {
        struct
        type_info_
            {
            core::typeinfo const * type_;

            explicit
            type_info_( core::typeinfo const & type ):
                type_(&type)
                {
                }

            friend
            bool
            operator<( type_info_ const & a, type_info_ const & b )
                {
                return 0!=(a.type_->before(*b.type_));
                }
            };
        }
    }

#define BOOST_EXCEPTION_STATIC_TYPEID(T) ::boost::exception_detail::type_info_(BOOST_CORE_TYPEID(T))

#ifndef BOOST_NO_RTTI
#define BOOST_EXCEPTION_DYNAMIC_TYPEID(x) ::boost::exception_detail::type_info_(typeid(x))
#endif

#if defined(_MSC_VER) && !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(pop)
#endif
#endif

/* type_info.hpp
rh933gvMfTIX2iYrf9x0HsOaMxaukwWjqrAuJuTCzXtPlA7iIQkd8bDOUOjpTIzk+dQ0ijuNlrC/cFEjBdKxaaecLyX6MoubyDJsYT7WEoc7CL/c4/NllrccoIiOIG9JJPfNUg1oVV+2gjdFA1qbpg+AExXdwCeqOXwXePtr7iIvIVvIDD9ZJkofyp7R+Nl4xs8yMrM4CXja6Xu2QgXKu7/HwInjdXq8xB5wen2GXm88S69r6HUgew2s02W5uV1dm9uPttUoWI46s5LrLuD17+24IV7U0Y7oE6x7OoC2Fw73o99iuEbBtt9gMGRn/nz2X7QzD9Pbmfv6AAVpyuAJmjQFd1Cvw7odlFhHOygZdtDfaQdFjcAd9PYI3EGrR/ThQLyxnhsie82fHooT5smvbWm7g6Qjegl6hnw29VlEaaUUrnuNMARPhLlCX+aATtXkSJv72QodZlGXAzI2qxl70WDNUOolG15sednncXqb7gy/AzQKTaSnfBwpkOgZV2TwiRgpIEz9PL4tTPmqdkR+rhdIHUJiR6N2LQKoWqYq69j8rA9tZH1o84xrVf5gFB9l7reqUPba4Y4IBa5+MhiUTW8RUDaxBXeOsyUmqO1quN84ffbO5Yf9986m/6+9c/hQR/bOpCeCjarsVzGqZb8GWbO0cfqx/OanjnPboQBr9hyu2VR21m8FQSCKaxvv6iWRvIZADQcQc6gj1zcA
*/