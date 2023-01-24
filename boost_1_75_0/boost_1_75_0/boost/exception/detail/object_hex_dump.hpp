//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_6F463AC838DF11DDA3E6909F56D89593
#define BOOST_EXCEPTION_6F463AC838DF11DDA3E6909F56D89593

#include <boost/exception/detail/type_info.hpp>
#include <iomanip>
#include <ios>
#include <string>
#include <sstream>
#include <cstdlib>

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
    namespace
    exception_detail
        {
        template <class T>
        inline
        std::string
        object_hex_dump( T const & x, std::size_t max_size=16 )
            {
            std::ostringstream s;
            s << "type: " << type_name<T>() << ", size: " << sizeof(T) << ", dump: ";
            std::size_t n=sizeof(T)>max_size?max_size:sizeof(T);
            s.fill('0');
            s.width(2);
            unsigned char const * b=reinterpret_cast<unsigned char const *>(&x);
            s << std::setw(2) << std::hex << (unsigned int)*b;
            for( unsigned char const * e=b+n; ++b!=e; )
                s << " " << std::setw(2) << std::hex << (unsigned int)*b;
            return s.str();
            }
        }
    }

#if defined(_MSC_VER) && !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(pop)
#endif
#endif

/* object_hex_dump.hpp
zviT4Y/wQvrJdne4nX5mtHjDn/y5X4fsXbO85jnfxHF717vYrwvYuyZxe9eiNvauR/4V1wF715yK4Pauqv+pbx19pKaDnf38T9kC+J9KCuB/ysb9T3nCvzGCFx8b9+ID84oziA58hhpVBz69cdosMMW7ULXHAlM8lX7CFEfTT5ji78PxJ5viyOt/6ic13b7f6w3k62plrt7XVVmu5utqIvutvBKCfqRyc//PfF39PIP1LvPcuY74ujo2o42vq80sQQmlPu6YIXxdvTOjXV9XPuMfNUM/ftsMbfyxUPcrBqw7Ycb/2fjfmA7j/7ND439iepvxF0yH8VMfl0wX458/vePj7zRdP37jdG38h6fB+CWsu3Ha/9n475kG4z/bofHfNq3N+JOhj6HUx+HTxPgHT+v4+PdO1Y+/Zqo2/kenwvi956DuTVP/z8Z/zVQY/5kOjb/X1Dbjb5kC46c+/jlFjP+3KRccfwK6OVGWn/V6yQVYAvlwVh56oa0LMFtxU0bT6LOaDa1J/Z3UFKpL76/+Tm06ekYr0+2sZlt7SE1PbqpWfyc0vXJGK3Nc/Z3RtFZXfs8ZrX75jNbuHF1bM3Rl1uvqn6Krc7yurYG6+vvryt9KvzOykTH2wP2oexqjkq4km3spODqYdCuQ349tbiub5TNIpbxmQw5LlFsYwWJ0qp9nlMEmO422lE8V4/Mwq6wCmVUgswo8s6Om7UHP
*/