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
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
*/