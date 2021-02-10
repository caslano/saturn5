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
cwHF/JOsNHtvJrPwOhPbggAFkmC/f17/57HGq2il8nrs9ahTdVJW3otgswe+b3Dn7opDlEXSkV5PVdHn6iQHP27gEZkOKHiGfFnoDk8VLW8YiIsX4KoDIaK0MLpFCIsELJa5qdlp0VCbOESYpuE934hN9eipnI2Vi0uZFVWudA21p9R+fsz2PiV/oOTzVkAzRhtrnVqd9eTupi5Py4nTngJCqcLtTheQ+T3ewuMkELc/obz37hymd+SXY2+9b3W6dXqmP6DwUXPecASAXiwwslgsZmGOdpRM8Dsk6TivUGiys7MgMmJAB/APvDcbG2svJrm37qm9KVPcEFP0ZNmXKSp3PBY/2avOdLQRrY7mcGQq57kxKpW5evizJokZQ6VV6rIK/8AbjfNpilcUmMChwp2Omw6XcXliR18F7ZuvUSF/llUG8zkGmO+6UGd9jKZdozsfN6D38UamR6ZuO3jsRUeViGBjdW6zU3nEt7RTcQauzatjvDiGOUm1hVLfITCn6/+aGxx0mzrXu885eAyL3cTSvf9YhZdBt01xhk4CVQUd+R2WBdpl3oQVcwrlgd0S3uX8V9UIJ/9DS/ipfc3Rdlm4UND/KZv0xzHgSkyRfAw3DuRC3vLo0uZC56x6+bBqY4J5tiLZkiU5L9nS
*/