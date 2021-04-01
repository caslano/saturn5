/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_MAP_FORWARD_CTOR_07222005_0106)
#define FUSION_MAP_FORWARD_CTOR_07222005_0106

#define FUSION_FORWARD_CTOR_FORWARD(z, n, _)    BOOST_FUSION_FWD_ELEM(U##n, _##n)

#define BOOST_PP_FILENAME_1 \
    <boost/fusion/container/map/detail/cpp03/map_forward_ctor.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_MAP_SIZE)
#include BOOST_PP_ITERATE()

#undef FUSION_FORWARD_CTOR_FORWARD
#endif
#else // defined(BOOST_PP_IS_ITERATING)
///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////

#define N BOOST_PP_ITERATION()

    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
#if N == 1
    explicit
#endif
    map(BOOST_PP_ENUM_BINARY_PARAMS(N, typename detail::call_param<T, >::type arg))
        : data(BOOST_PP_ENUM_PARAMS(N, arg)) {}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#endif
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) || \
    (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
    template <BOOST_PP_ENUM_PARAMS(N, typename U)>
    BOOST_FUSION_GPU_ENABLED
#if N == 1
    explicit
#endif
    map(BOOST_PP_ENUM_BINARY_PARAMS(N, U, && arg)
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES) && \
    N == 1
    // workaround for MSVC 10
FUSION_HASH if defined(BOOST_MSVC) && (BOOST_MSVC == 1700)
        , typename enable_if<is_same<U0, T0> >::type* = 0
FUSION_HASH endif
#endif
        )
        : data(BOOST_PP_ENUM(N, FUSION_FORWARD_CTOR_FORWARD, arg)) {}
#endif
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH endif
#endif

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* map_forward_ctor.hpp
8448XY+wYt5GntUHyeKooNnfq/0axa4+i6zEQEbVFRXGP8qYScq+h0tBLvqbH/kqRHkEg8NaDN9PFFFIpbdfnHpMHZ+a4CT9QQ1Tus5SKSucIyMvY/4LkzLr336pJBy40Xb2I/GdBFazNztZfmZYi25ZT7Nay7jCnIq8MnXGxYStP3a0eGBMrI1d9wbi0Diedrxzo7536pxbHj7mVpQsWqSlcaq62FGJHud5UksOCy7SHZXcleIajtoFtUTPRIvFsE7DZMx6x4lG6jOXBG76eXQKw2cIimj2++bqbdBmEmSazSDngZLbqd3kUwh5YGZWEGj7MTWpYyHEMFdPZd35QtyDvy+h2vintXwHGwhd6WV+xCPgLsJo5Wv9FDJdMGz4KbIHkKmBdsPo56MLMi/2G1T9ItTI4JMFmrCBgJi5qqawLz71rnrqX7Nmw/epebhN7TNMeK6jzdvDixOHzSYOAsC2TP7cY13LA5Yq1fcKKj8IpsE4DbXxg3eq9YsoFlOcBod5LChFwy6FVy9xRecmMTiAcBxrAUoYaE7k0WOAlaF+OYlbbAYOHWiIAw==
*/