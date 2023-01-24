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
+R9/RnBs/pvzshMjOZr/lsfxfyQ/nzDaZsAe+OerunOXS27g+ai9U7rlmbTQggm9jbaZPBPjgKyffkfedy1Mrp5fMAkKzrsSnD1rjOddIE75lwEDD/ai8oe/bb58V1aevOTH2JS7x9KFAezB/b3YnAe+QGEAanr5PDXF2zcMtRX67ocrBsGNBDPr6wuDWQcw5QTT65vmYRI4DJyxBXIh/HSCFdTbZKbeDk9A1Zbt8mU1upzIFJIv2CZEU31a4FIGIsxUeUZhaKfmfJXyB6HBSmGQ446jbYbjilbCENP3LbrIffXio5Dh0n2596jZncj+CbZefPQ9eNMG3rSEfyJTqnaSPzEartFfN7ubTeT/FbdFMsSNEcnnLO6CPyW4LMJ+FlU4i6UuzhKpC94jYY8Keqykxyp6aAFoJb8zMRiRUiX5FqP/l3c14DPcGakywd3oITC6YSVGuuadXGKq9oIkCD2tHty+JRLFnZhUeCfeWxR3QHgt72Et2mWMlpL3BWol/DZGS9WRchWj194X1tB37ToG+3IxfVnFvxj8RtSe+GUl/1Khf/mZvlTwL6X6l0/oSyl9oRHG4th4r/zDpNK5SSZ3zC5nEpMMI6+0mryT25v4KMlffEb1/8ZfXJzNhNj/X27szBkq1F3WM9ydUzhvrhqlOW+OGmN03nwPnTf3qC75wxDnzae0OwT/hpSfidaM0LLjm3jXH50/7ymC
*/