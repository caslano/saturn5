/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_VECTOR_FORWARD_CTOR_07122005_1123)
#define FUSION_VECTOR_FORWARD_CTOR_07122005_1123

#define FUSION_FORWARD_CTOR_FORWARD(z, n, _)    BOOST_FUSION_FWD_ELEM(U##n, _##n)

#define BOOST_PP_FILENAME_1 \
    <boost/fusion/container/vector/detail/cpp03/vector_forward_ctor.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_VECTOR_SIZE)
#include BOOST_PP_ITERATE()

#undef FUSION_FORWARD_CTOR_FORWARD
#endif
#else // defined(BOOST_PP_IS_ITERATING)
///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////

#define M BOOST_PP_ITERATION()

    // XXX:
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
FUSION_HASH endif
#else
#if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
#endif
#endif
    BOOST_FUSION_GPU_ENABLED
#if M == 1
    explicit
#endif
    vector(BOOST_PP_ENUM_BINARY_PARAMS(
        M, typename detail::call_param<T, >::type arg))
        : vec(BOOST_PP_ENUM_PARAMS(M, arg)) {}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#endif
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) || \
    (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
    template <BOOST_PP_ENUM_PARAMS(M, typename U)>
    // XXX:
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
FUSION_HASH endif
#else
#if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
#endif
#endif
    BOOST_FUSION_GPU_ENABLED
#if M == 1
    explicit
#endif
    vector(BOOST_PP_ENUM_BINARY_PARAMS(M, U, && arg)
#if M == 1
        , typename boost::disable_if_c<boost::is_same<vector, typename boost::remove_cv_ref<U0>::type>::value, detail::enabler_>::type = detail::enabler
#endif
        )
        : vec(BOOST_PP_ENUM(M, FUSION_FORWARD_CTOR_FORWARD, arg)) {}
#endif
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH endif
#endif

#undef M
#endif // defined(BOOST_PP_IS_ITERATING)

/* vector_forward_ctor.hpp
h8qxHl7A5qiMjdcX6+BgrItj8CqcgfVwLl6NN2N9XI8NcT82wtewMZ7BAPwar8F6XJcCsRs2xd7YHIdgC8zENngnXos7sD0+jh3w99gRP8dOeBY740/YBdsoxxH2wq44GrvhROyBM7EnxmIvVH6nFX9C+xBSGSnw0wZVtgn6X2kP9KMPbYLsu8zbBcWQkk3aBU2cfHWNtw1y9Il9GdoGRZq0D+rBdo4iJZNWknaQ9pOOkcpJjU81sPQgTSSlkgpIO0j7SSdIP5JafEZsPymWlPeZP3beP/kn/+Sf/JN/8k/+yT/5J//kn7yd6lquSPx/oj3t0uP/lRj8h3R9+9slVv5TUjDpI1InJX6omzOe3RFplZic7Gy7X3Wcm1k8ufQXSByhe6xOtPq5ElGn9XWd5YxhzK2Me7Fq85nG+q8mNSMtkz52I7s7y18Tfezq+6YslPj7BFJr0hxSqJVySH6ufc360mfmeS/6lXepC7W+Hnf+zStgY1/aYfJMdqyUd4T0jZvQw7y8zsDGXK+3szf9415s+1nlnWsTChOMDbA7M5e4lE/2v2r1T6yUK9W9XCZ9FLvFu5nWd5ihvp3tE+b01PVtyd+vaH8b+86W9a2M750jce7WXrr1JezKubte+v6aVzmWgLQXicOerFCRa35qtVTdB7QSn/dBb2N8XoJSBi/rPEw9vnPT9ce3xE3LNjDWucQhS50b4zHLrzJvk5MQdmXa5BRILP9hOcZeI/VW4oWd+SsVIvHCSYSJV90uxjVWWNrjyN/zXevLUJZzUpbhUhcRpDClLH1cy6L0Pe9rWZYYYpTt0k9/d1nvzqS+VvLraxana8uw5dmqFaMrMZZShmRDGSpMytDfStn6eooVvrQ44WTHZ84FKeUYL+XYWd89Zvl6ylHssRzxE6N0n1ksl1auQe7xy8ynxi8b6ixIHvmGKPNKeYdY+b9+7mWtum98T2Uz5rmjgft2ukHZV8zyTMvKteXkVSvPyn2locm+0rGhexmGK/uKWRk4J/qyTYY66j+VDaBtk2GOz5KUzwzx7Xsamh83xWblyLFx4bMtqe42MDt2Rkg5IiTOviuplcQPjKQcZSblcA64kb00y9G8p3plqayX9iTKkgGGejnUyL1eRiv7SH9n/Hi6+/kk3p6X43VZ9NecZob9hKW47K8Rjd2PkbHKvlJZlks4RrRyGNe/SPJsTQqQfKOsfG6WJ/snbT8yMrzIV79eLQLc1+tWNn6JaR6LM305Bta1kvVyPfYD3LfrOGU/M8vTvjg31Yc8fdmmHZu47++38R9hA9zL4bxIel8O1t2tHHJ9Ts53+b2wU8oxSOqjL2mgsm85y+HIWdmnnNfoqn8DSrsAfdsi8teP12Pcz6Klf/0Lsg98Q0pi3hK3/GlXlpTuvFx5cR/TxHA/l+jVbz25f3H7bVcucS7mce6e4/rN4/R9j/f3ta91X/tIN28P4Xu7AV/j+s3bK3iO6zdvz+Ep3r/m2nM8nK983vrHbU/m/XP5D7F5jc4/WdH5sOd2J844KXlugZ+SKmoZ46TCJK64D3bC/tgPB+JIHIQzMRzn4hBcjBG4Cm/AzTgUd+EwfBkj8QMcgR/hSDX+Wp5D4Gopjz7++k5dn+6dcQuG4lYMx21Snh2YjvfhMrxft/yTsvwEk+W31vWx3QWvxe4YjP3xOhyKbSWfdjgHrWq8vDwnwLGyfH28fCdZfqgst6vUZzeMxB44AnvK8kotcl8v9/sVck96UJY3VrbPBOyIE2W5k3AQTsZhOAXHYTROx6lSP9MwF6fjzRiD9+AMfARn4hM4C5/B2fgnnIOHMQ4/xbl4FudhBSbgj5iI/8b52ICyJ+n6PLb20m8=
*/