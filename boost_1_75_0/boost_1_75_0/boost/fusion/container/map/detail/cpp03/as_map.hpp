/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_AS_MAP_0932005_1339)
#define FUSION_AS_MAP_0932005_1339

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/inc.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/fusion/container/map/detail/cpp03/map.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>

namespace boost { namespace fusion { namespace detail
{
BOOST_FUSION_BARRIER_BEGIN

    template <int size, bool is_assoc>
    struct as_map
    {
        BOOST_STATIC_ASSERT_MSG(
            size <= FUSION_MAX_MAP_SIZE
          , "FUSION_MAX_MAP_SIZE limit is too low"
        );
    };

    template <bool is_assoc>
    struct as_map<0, is_assoc>
    {
        template <typename Iterator>
        struct apply
        {
            typedef map<> type;
        };

        template <typename Iterator>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator)
        {
            return map<>();
        }
    };

BOOST_FUSION_BARRIER_END
}}}

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/map/detail/cpp03/preprocessed/as_map.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/as_map" FUSION_MAX_MAP_SIZE_STR ".hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

namespace boost { namespace fusion { namespace detail
{
BOOST_FUSION_BARRIER_BEGIN

#define BOOST_FUSION_NEXT_ITERATOR(z, n, data)                                  \
    typedef typename fusion::result_of::next<BOOST_PP_CAT(I, n)>::type          \
        BOOST_PP_CAT(I, BOOST_PP_INC(n));

#define BOOST_FUSION_NEXT_CALL_ITERATOR(z, n, data)                             \
    typename gen::BOOST_PP_CAT(I, BOOST_PP_INC(n))                              \
        BOOST_PP_CAT(i, BOOST_PP_INC(n)) = fusion::next(BOOST_PP_CAT(i, n));

#define BOOST_FUSION_PAIR_FROM_ITERATOR(z, n, data)                             \
    typedef pair_from<BOOST_PP_CAT(I, n), is_assoc> BOOST_PP_CAT(D, n);         \
    typedef typename BOOST_PP_CAT(D, n)::type BOOST_PP_CAT(T, n);

#define BOOST_FUSION_DREF_CALL_ITERATOR(z, n, data)                             \
    gen::BOOST_PP_CAT(D, n)::call(BOOST_PP_CAT(i, n))

#define BOOST_PP_FILENAME_1 <boost/fusion/container/map/detail/cpp03/as_map.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_MAP_SIZE)
#include BOOST_PP_ITERATE()

#undef BOOST_FUSION_NEXT_ITERATOR
#undef BOOST_FUSION_NEXT_CALL_ITERATOR
#undef BOOST_FUSION_PAIR_FROM_ITERATOR
#undef BOOST_FUSION_DREF_CALL_ITERATOR

BOOST_FUSION_BARRIER_END
}}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif
#else // defined(BOOST_PP_IS_ITERATING)
///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////

#define N BOOST_PP_ITERATION()

    template <bool is_assoc>
    struct as_map<N, is_assoc>
    {
        template <typename I0>
        struct apply
        {
            BOOST_PP_REPEAT(BOOST_PP_DEC(N), BOOST_FUSION_NEXT_ITERATOR, _)
            BOOST_PP_REPEAT(N, BOOST_FUSION_PAIR_FROM_ITERATOR, _)
            typedef map<BOOST_PP_ENUM_PARAMS(N, T)> type;
        };

        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            BOOST_PP_REPEAT(BOOST_PP_DEC(N), BOOST_FUSION_NEXT_CALL_ITERATOR, _)
            return result(BOOST_PP_ENUM(N, BOOST_FUSION_DREF_CALL_ITERATOR, _));
        }
    };

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* as_map.hpp
JbRWMuq9JFKVfJ2eb65yiSwNu+6bTQd/kv2Mg3+XSA6OF4listfiZE+EmS/9w+osu0r/BS6m4Zd/nLtUs/ovMSrMVnaIxb1xJTwxGMKf50Ct5xoKKaLJJE46HRsBnmM6PD+J5ODXp80lE3WB1J0iEfpdGrT63fCnD/zpBH/alB63OstfFwUDN8U0JqwEW3WNtpXRePHIOYZPHRasqLHjSrAy0ahyvPKZTAF6yg/t3xbSvoUhzwuBHGcEvRWx0XIo2D2k4EGegj6Rulyvl7wASgZPmUs2cMm4SCVr9ZJ/2mD9nyLz7uTZ/HPA5UejGJfbR8GM7iJcfgg/HtQn9Rz913aL/PWUnOjBMNHOcgs/pwBY+KYil9UTtjMuq3sAsk4ImamwROuhkQobaN0XCn/zT1hhidldIhSWmN0KSr4eXlLi96GY5vEbhIiC40RJRidTcYnlG2Kax/LFMQZKOsu6ino0V/t+cQIJIlVJKP5kpPoYxR8IqW/XSb0SvKytOxnWQzkr/SP00DQrPaCTZScR2YtxNRToa6Cr/usruQbGtwzZ94olF7w8HCSJ73XRZ8T3hVD4zxNhhRO58DPROvpmK9MQS0UWsMPeDf6cW3qCDP0VEaa7tZ0Cv9sSfv+FKRgFiJ0DDVWENyRxu2/0mXC7C5TNDi8r0dsRqYcGeh8U0ASd4YUlhu+POiOGr4PCu4+To4QUJKugZjF/rUSr
*/