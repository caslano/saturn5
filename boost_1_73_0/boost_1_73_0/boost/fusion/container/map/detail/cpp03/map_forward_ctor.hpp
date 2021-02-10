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
YJExke0GDRbRlEYTFrE/TYyGt0AgzVcDMNEV0mBCHWpSoe7KQL6gKgHbVKZGM6DKE6MRsPXxuBGYyphtnGG3qbPVgKpdUzHTK4CZlU2gmnVKANnUqC65BLCl3FJWAdgzg1h1JoT7xUWgBEw11bKVYrp3hEaIQifSGPNdQ5jExmwKF/I24DHg7o6x1C+4SGGgChmFqzJQnOA1ADbw035WexfXZcIa6WbeyuUBgDdqN9hIzgr6YLCFcoCtYBSSE4WVM7GPZxJr0emkaVEnZBst3OE/bxzcOTn2ZkkHEOGO1+50RUP6uL0vwmDV7iSt3AOLfWfFuL8I2p3zdHffuoETOMk57oPDi50b3I+LyOepNBbI5Q7BLiSKq/XsIZE57LgqqXf11rbI1REE6+W2gOQqSb498l4FpNblAlXtcgGpdnmPNLssVuOS22U1BeRy53I98+64mqvjyPsEwcZ8g6fMKJh/d1w3rMevj2jchaH59ahq0VtdVfKLRK7V2ZXlRbke81AuniX/c3muErgsuleFXF0fRX4t5blvKckcFmuDQvrTYdoAc3FYBOaLI2GEZ7hVEL5AHDrz79x/yBr7rYq9qJjLODC1CP0yVvvivDRfuWeeoHAMm3jx08Z2ONcyJ8u1+K68npcQJL4AFJFt
*/