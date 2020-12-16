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
ZuemWzZDjsh03yt5ZVn8Gw4ynr//du41FfOdjM+VhXVDD+LMQMbHukGXnsW/t9isPxN92aZLW8RHxmvQc+nM1VgLyGyZLe687zxqkIznb1mNmD5Yz8iMzKodW3kOuSWryazswBd9cd4lq8jsnu+2JcgtGa/d9bUOOuJMRMbHult141bE95N+rjj0G4yx9iLj9VKywXxb5I/MmdfLV//BHAsn4+Ny5Pu+xZ+Vk+k+D+j73ID8kfE83C81whX7rWjX7NO3bzD/yHh9fv2sWyvk9md9fGdzjxY/r5DxMXPdUbI4PjLelzGjsyyRPzJeSzNOTixAfGRVeC0dM05EfGS8dq3WrCl+nibjdXar2/1+yJ8wu1Oej5C/Lfq9/6dbGTWQPzI+Zkdb7fPFXkVmz3P0YI8F5p9oV7ls4hzEJ9q9P1XlMepTtKvxaN9A5I+M52HTzSewAjJeL9G5lbE/mCq1GrNc97M4Q3uQGZn1vPbmBc6DZM7M/OeMTEL+yPjcrPhmG/aAKDI+1s8n//Qn4iPjud18ZWVVxCf6+VuH3sXf3yWzYZZ9N30Y6nObflw2Drh4DfVJxvs5d9iOFYhP2KsXJ9pj7yDTfY/66CsbrC/ifm0bxv8X8Yl2LgkDbyE+Mp7bDuG1jiI+MjtmbbYvKd7Dt+vHZeNXxsOIj4zf72zmN60QHxmvM68hI4vPWWRlmV3qk7QbuSXjOTrQ4egA5JasNrNPgupbY26S8Xl0fcZCWLboS0b+buS2gIzP6fCQI40wN+OK+2lqnz70jSdiJ7NmVqGDJcbTU7Sbld7fG+NCVo7ZoUZJxb+hInNhZug77ivknazFx7/3ZBrz97u+Rg2mxuH5qMiqjDdMRXxkbZjt/u7v8lhfdlA/mb093hvPK7478Jl3kdX5x/UknqvInFm735d6vUKdkXVg5v/UoTaeLXYWx1el6P+jIxLx+ZKVZbbRvgLOtAE78Tu3Ipv1lf1MzBXRrlLL0vjcKZSsDGvX5MXW3vjbKcKuDx1U/Dv9ncXjaZqjHo3aTEOdkRmZtXg3oSNiZ/GZ5tqVS/O9sE7sovnO7KRzLt5BOO0qjq+aqX7++rEr6mwX9qoiC/u6A2rJl6w6s6l1Nk3EPCJzZPb63zGYt1Fk9Zg1uG2LPSeZrAazbysGlMZZn8yJWcVlyy5hnY/X9/NpwaQRmA9kdZlt6lQNFkzWgJnv7ZWo61gyV2b/ZuXkYqzJeOwNX7m9w3om7jdy4ffrUYO7KUfMVi5ZPBfjScbbBR5bjnNyuLBPPHaew7pLVo3ZqeuDMtFPMj4ulRfYr8XcJHNgNmGFfTTWnl/0Yz3j/cDXmLdkNZlZDJ/3J8aTjOcvf/aiBsi7uOah5HXHUdeincU3h2pi/STjY/Z67s2jyPt/aD/iNfFdg1+RdzJ+v5A5vj7YA8j4uPRv2vQ05h8ZH+ttw0seRD9Fu77lPPahn2TOzC7YxizGPpZAewczQ/Myk3EOISvD5l+7PkM+RwxklsyS+rmNRR6E7RgQ1BDrvLCa35QKQ50Jc4+++gX2AGE/bPvNCWMmbPnPL4cg7yKGzjfG5mMtEHaxmUMTnBXFNRfEtSz+uxXCTr85/xo5Ela+TptqqDOy0sxG/ufAW5w/RbtxP50egPku7Oz+MFicsC8mHm+G+SfuFzHNZzjqRbQbsjbUEmudaHc3+nes86nCai25uRdzWthap+LvuGQKm2BZsvgZXfTl6JHe47C2CvvV/8EdrGfC8ssV/6aiQFjHv+421sywR9+Xqs79W2I+kPF2Q/s6YN01Civoug3mIGz2t7Uwns7ifgUF8TjXuYl2o0buRP48RLs4y4uIz1NY5pLmuJ8XGa/rT6Y=
*/