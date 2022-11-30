#ifndef BOOST_SERIALIZATION_FACTORY_HPP
#define BOOST_SERIALIZATION_FACTORY_HPP

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

// factory.hpp: create an instance from an extended_type_info instance.

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <cstdarg> // valist
#include <cstddef> // NULL

#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/comparison/greater.hpp>
#include <boost/assert.hpp>

namespace std{
    #if defined(__LIBCOMO__)
        using ::va_list;
    #endif
} // namespace std

namespace boost {
namespace serialization {

// default implementation does nothing.
template<class T, int N>
T * factory(std::va_list){
    BOOST_ASSERT(false);
    // throw exception here?
    return NULL;
}

} // namespace serialization
} // namespace boost

#define BOOST_SERIALIZATION_FACTORY(N, T, A0, A1, A2, A3) \
namespace boost {                                         \
namespace serialization {                                 \
    template<>                                            \
    T * factory<T, N>(std::va_list ap){                   \
        BOOST_PP_IF(BOOST_PP_GREATER(N, 0)                \
            , A0 a0 = va_arg(ap, A0);, BOOST_PP_EMPTY())  \
        BOOST_PP_IF(BOOST_PP_GREATER(N, 1)                \
            , A1 a1 = va_arg(ap, A1);, BOOST_PP_EMPTY())  \
        BOOST_PP_IF(BOOST_PP_GREATER(N, 2)                \
            , A2 a2 = va_arg(ap, A2);, BOOST_PP_EMPTY())  \
        BOOST_PP_IF(BOOST_PP_GREATER(N, 3)                \
            , A3 a3 = va_arg(ap, A3);, BOOST_PP_EMPTY())  \
        return new T(                                     \
            BOOST_PP_IF(BOOST_PP_GREATER(N, 0)            \
                , a0, BOOST_PP_EMPTY())                   \
            BOOST_PP_IF(BOOST_PP_GREATER(N, 1))           \
                , BOOST_PP_COMMA, BOOST_PP_EMPTY)()       \
            BOOST_PP_IF(BOOST_PP_GREATER(N, 1)            \
                , a1, BOOST_PP_EMPTY())                   \
            BOOST_PP_IF(BOOST_PP_GREATER(N, 2))           \
                , BOOST_PP_COMMA, BOOST_PP_EMPTY)()       \
            BOOST_PP_IF(BOOST_PP_GREATER(N, 2)            \
                , a2, BOOST_PP_EMPTY())                   \
            BOOST_PP_IF(BOOST_PP_GREATER(N, 3))           \
                , BOOST_PP_COMMA, BOOST_PP_EMPTY)()       \
            BOOST_PP_IF(BOOST_PP_GREATER(N, 3)            \
                , a3, BOOST_PP_EMPTY())                   \
        );                                                \
    }                                                     \
}                                                         \
}   /**/

#define BOOST_SERIALIZATION_FACTORY_4(T, A0, A1, A2, A3) \
    BOOST_SERIALIZATION_FACTORY(4, T, A0, A1, A2, A3)

#define BOOST_SERIALIZATION_FACTORY_3(T, A0, A1, A2)     \
    BOOST_SERIALIZATION_FACTORY(3, T, A0, A1, A2, 0)

#define BOOST_SERIALIZATION_FACTORY_2(T, A0, A1)         \
    BOOST_SERIALIZATION_FACTORY(2, T, A0, A1, 0, 0)

#define BOOST_SERIALIZATION_FACTORY_1(T, A0)             \
    BOOST_SERIALIZATION_FACTORY(1, T, A0, 0, 0, 0)

#define BOOST_SERIALIZATION_FACTORY_0(T)                 \
namespace boost {                                        \
namespace serialization {                                \
    template<>                                           \
    T * factory<T, 0>(std::va_list){                     \
        return new T();                                  \
    }                                                    \
}                                                        \
}                                                        \
/**/

#endif // BOOST_SERIALIZATION_FACTORY_HPP

/* factory.hpp
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
*/