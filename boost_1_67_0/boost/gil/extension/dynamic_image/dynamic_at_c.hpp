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