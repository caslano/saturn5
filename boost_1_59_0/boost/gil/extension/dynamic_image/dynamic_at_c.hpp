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
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
*/