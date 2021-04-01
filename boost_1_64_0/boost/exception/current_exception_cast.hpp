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
HPd4Nm+d/t3rReZoSuNNCeS/7jm/0VxuloEczhwWlRITNkRDBeck3vXHcY/qyYuWU8HZGEcgFXhUtCSJjBYjCwaYZmZ7SXbOGh/4lRvyFZNpyC8+lXbtFyHi6Uz/VD54Ss6ZeRTS3/TxDRlaalAtqP0o1e6EHs7NOus0KaumW9iBhsJ0HsVr/R8QgoI0DIB2XB6XeBq6bJOTusd0s5z2HC9bP0OsZ72A1xqX/T0w8JDEt2jqzuS7+9w1dFJcU/tjv9GFiMZt1uhKaTh/V1IkqcNWyQGL3IBAFx0lgzaapC22i+AMeqiokXucTEIdOWXtgoTWO/zMCzhMDUfqqr7oUAOdvYqlf/yntFuAJthOHeBJAre2vNJI+Xq34zawrRea211thuxl0j++FOqxTdJ3GyDERiCGABnFUI2wmrKxQd2YE6dbKtbXvcBBMpZ0bEk54kv4yRVb8PaSsPb04LnwWY/srczA5qOcXx/4UAFzidLgd6GjcePyEmK+YArz22AxTBjZcYtQlGUwG/nyw4rfA9GrNAKpJpXzYv0RBxyXBPWw9xHSFS+LPXbJwg==
*/