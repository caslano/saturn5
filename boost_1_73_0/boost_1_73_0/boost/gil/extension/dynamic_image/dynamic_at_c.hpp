//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_DYNAMIC_IMAGE_DYNAMIC_AT_C_HPP
#define BOOST_GIL_EXTENSION_DYNAMIC_IMAGE_DYNAMIC_AT_C_HPP

#include <boost/gil/detail/mp11.hpp>

#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

#include <stdexcept>

namespace boost { namespace gil {

// Constructs for static-to-dynamic integer convesion

#define BOOST_GIL_AT_C_VALUE(z, N, text) mp11::mp_at_c<IntTypes, S+N>::value,
#define BOOST_GIL_DYNAMIC_AT_C_LIMIT 226 // size of the maximum vector to handle

#define BOOST_GIL_AT_C_LOOKUP(z, NUM, text)                                   \
    template<std::size_t S>                                             \
    struct at_c_fn<S,NUM> {                                             \
    template <typename IntTypes, typename ValueType> inline           \
        static ValueType apply(std::size_t index) {                    \
            static ValueType table[] = {                               \
                BOOST_PP_REPEAT(NUM, BOOST_GIL_AT_C_VALUE, BOOST_PP_EMPTY)    \
            };                                                          \
            return table[index];                                        \
        }                                                               \
    };

namespace detail {
    namespace at_c {
        template <std::size_t START, std::size_t NUM> struct at_c_fn;
        BOOST_PP_REPEAT(BOOST_GIL_DYNAMIC_AT_C_LIMIT, BOOST_GIL_AT_C_LOOKUP, BOOST_PP_EMPTY)

        template <std::size_t QUOT> struct at_c_impl;

        template <>
        struct at_c_impl<0> {
            template <typename IntTypes, typename ValueType> inline
            static ValueType apply(std::size_t index) {
                return at_c_fn<0, mp11::mp_size<IntTypes>::value>::template apply<IntTypes,ValueType>(index);
            }
        };

        template <>
        struct at_c_impl<1> {
            template <typename IntTypes, typename ValueType> inline
            static ValueType apply(std::size_t index) {
                const std::size_t SIZE = mp11::mp_size<IntTypes>::value;
                const std::size_t REM = SIZE % BOOST_GIL_DYNAMIC_AT_C_LIMIT;
                switch (index / BOOST_GIL_DYNAMIC_AT_C_LIMIT) {
                    case 0: return at_c_fn<0                   ,BOOST_GIL_DYNAMIC_AT_C_LIMIT-1>::template apply<IntTypes,ValueType>(index);
                    case 1: return at_c_fn<BOOST_GIL_DYNAMIC_AT_C_LIMIT  ,REM                 >::template apply<IntTypes,ValueType>(index - BOOST_GIL_DYNAMIC_AT_C_LIMIT);
                };
                throw;
            }
        };

        template <>
        struct at_c_impl<2> {
            template <typename IntTypes, typename ValueType> inline
            static ValueType apply(std::size_t index) {
                const std::size_t SIZE = mp11::mp_size<IntTypes>::value;
                const std::size_t REM = SIZE % BOOST_GIL_DYNAMIC_AT_C_LIMIT;
                switch (index / BOOST_GIL_DYNAMIC_AT_C_LIMIT) {
                    case 0: return at_c_fn<0                   ,BOOST_GIL_DYNAMIC_AT_C_LIMIT-1>::template apply<IntTypes,ValueType>(index);
                    case 1: return at_c_fn<BOOST_GIL_DYNAMIC_AT_C_LIMIT  ,BOOST_GIL_DYNAMIC_AT_C_LIMIT-1>::template apply<IntTypes,ValueType>(index - BOOST_GIL_DYNAMIC_AT_C_LIMIT);
                    case 2: return at_c_fn<BOOST_GIL_DYNAMIC_AT_C_LIMIT*2,REM                 >::template apply<IntTypes,ValueType>(index - BOOST_GIL_DYNAMIC_AT_C_LIMIT*2);
                };
                throw;
            }
        };

        template <>
        struct at_c_impl<3> {
            template <typename IntTypes, typename ValueType> inline
            static ValueType apply(std::size_t index) {
                const std::size_t SIZE = mp11::mp_size<IntTypes>::value;
                const std::size_t REM = SIZE % BOOST_GIL_DYNAMIC_AT_C_LIMIT;
                switch (index / BOOST_GIL_DYNAMIC_AT_C_LIMIT) {
                    case 0: return at_c_fn<0                   ,BOOST_GIL_DYNAMIC_AT_C_LIMIT-1>::template apply<IntTypes,ValueType>(index);
                    case 1: return at_c_fn<BOOST_GIL_DYNAMIC_AT_C_LIMIT  ,BOOST_GIL_DYNAMIC_AT_C_LIMIT-1>::template apply<IntTypes,ValueType>(index - BOOST_GIL_DYNAMIC_AT_C_LIMIT);
                    case 2: return at_c_fn<BOOST_GIL_DYNAMIC_AT_C_LIMIT*2,BOOST_GIL_DYNAMIC_AT_C_LIMIT-1>::template apply<IntTypes,ValueType>(index - BOOST_GIL_DYNAMIC_AT_C_LIMIT*2);
                    case 3: return at_c_fn<BOOST_GIL_DYNAMIC_AT_C_LIMIT*3,REM                 >::template apply<IntTypes,ValueType>(index - BOOST_GIL_DYNAMIC_AT_C_LIMIT*3);
                };
                throw;
            }
        };
    }
}

////////////////////////////////////////////////////////////////////////////////////
///
/// \brief Given an Boost.MP11-compatible list and a dynamic index n,
/// returns the value of the n-th element.
/// It constructs a lookup table at compile time.
///
////////////////////////////////////////////////////////////////////////////////////

template <typename IntTypes, typename ValueType> inline
ValueType at_c(std::size_t index) {
    const std::size_t Size=mp11::mp_size<IntTypes>::value;
    return detail::at_c::at_c_impl<Size/BOOST_GIL_DYNAMIC_AT_C_LIMIT>::template apply<IntTypes,ValueType>(index);
}

#undef BOOST_GIL_AT_C_VALUE
#undef BOOST_GIL_DYNAMIC_AT_C_LIMIT
#undef BOOST_GIL_AT_C_LOOKUP

}} // namespace boost::gil

#endif

/* dynamic_at_c.hpp
e4FHjI0fjZwZ6FDBPEl1wTR7Ssj9ZVLQKnQUs9pShomzWJee/eXNLdBHa9p+wzlL3SlEpit6V0Fk3agEIk+JJjVxTrchw+cuCB/x6opY5ePezdAWwhtY6Gb6CtURjza4TiI8E1NzoFKlYmOlmgaXTr72ehlGYfF0N1hreT/xMFhhOlhreT/RZJV+sNbyfvLJKuDBWsv7mabTF0/3g7W8fqoq4XHnmhEr/woNd06wuHdCL5M6awvzEdfK0Utmt5IjGaARynv06PLlJfblDDoxjBPF2kuOOf7JiHbFIUQVHqcOZi7jtXzDOb7r3Co9s2YM9IGsZ9cGAv1Mt2azlDfnnF/p8GlONXd6WQHOB+/J5DmrJqHS7asHaJGHCbqj+zV1LwN0KCWAMxoyJrFz9sSieLfVtJ3shKOrs8aQ0pvzLGwJFgEVP3i//jAV/6x6Vv3zu7HysnDnlZLlK7QQlK3CLRwiMZ0cVLRAkrGtKhdQaqGOUuF1pgdLqpsWX5dXmmvxVTkNdptrZVQYDO0GRvrmwLlMSlj6Khjibz7uJuAtHu3zNAKn3Fxj75V6d9l7T9wL7b0H5lZ7vyObR+11bzRHp9Q1YpzikuHmpWNHiflWosAZfsftxJDjHL0w5nuH8L+qjeEzyrrBHVC+ZTv0
*/