/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_AS_DEQUE_20061213_2210)
#define FUSION_AS_DEQUE_20061213_2210

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/inc.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/fusion/container/deque/deque.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>

namespace boost { namespace fusion { namespace detail
{
BOOST_FUSION_BARRIER_BEGIN

    template <int size>
    struct as_deque
    {
        BOOST_STATIC_ASSERT_MSG(
            size <= FUSION_MAX_DEQUE_SIZE
          , "FUSION_MAX_DEQUE_SIZE limit is too low"
        );
    };

    template <>
    struct as_deque<0>
    {
        template <typename Iterator>
        struct apply
        {
            typedef deque<> type;
        };

        template <typename Iterator>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator)
        {
            return deque<>();
        }
    };

BOOST_FUSION_BARRIER_END
}}}

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/deque/detail/cpp03/preprocessed/as_deque.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/as_deque" FUSION_MAX_DEQUE_SIZE_STR ".hpp")
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

#define BOOST_FUSION_VALUE_OF_ITERATOR(z, n, data)                              \
    typedef typename fusion::result_of::value_of<BOOST_PP_CAT(I, n)>::type      \
        BOOST_PP_CAT(T, n);

#define BOOST_PP_FILENAME_1 <boost/fusion/container/deque/detail/cpp03/as_deque.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_DEQUE_SIZE)
#include BOOST_PP_ITERATE()

#undef BOOST_FUSION_NEXT_ITERATOR
#undef BOOST_FUSION_NEXT_CALL_ITERATOR
#undef BOOST_FUSION_VALUE_OF_ITERATOR

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

    template <>
    struct as_deque<N>
    {
        template <typename I0>
        struct apply
        {
            BOOST_PP_REPEAT(N, BOOST_FUSION_NEXT_ITERATOR, _)
            BOOST_PP_REPEAT(N, BOOST_FUSION_VALUE_OF_ITERATOR, _)
            typedef deque<BOOST_PP_ENUM_PARAMS(N, T)> type;
        };

        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            BOOST_PP_REPEAT(BOOST_PP_DEC(N), BOOST_FUSION_NEXT_CALL_ITERATOR, _)
            return result(BOOST_PP_ENUM_PARAMS(N, *i));
        }
    };

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* as_deque.hpp
37nMr89lO9N0RyFqsuwZjqxQ0m5YpJ/rgiuNKpy5rGPpUfuNdc3h5jC8eSS7Rn34Goz6j7nuAY7Km3i2Mmmo1aSn1vLaB5k4RCLJ1vdIeMj/GOSMsR/T2QOfoCgx8BM67f8xnqbRoTcd7qTD7fyWLvzYnh+b0xCRdAimw7XV1HhhNZ7+RQeZDsd542E63UeHXXTYSoeveJ+1q/D001VC1x8jtFHbm2i1URdJ56Qo+WtfaGiMsBoK77U6B56Rc9sYVDPEmhf80TclDxZWbY2qqWClh/2mGgTPQwfbNdGFDmZKJzKlWhLElH1nzxdIEFugE8QWoCA2LdtUuieMW7f3hjWatTHkBdzODc1RsjZNXX0OU6fCiZo6tdygSZ36UKTIXHrvlwzzWVJkJ5G6NEP6FhOR1Sh5r0Jc5mclIGdTWWaY9tFTJFgvhuYqTw5o/MnvnjfxJ3/3hT9Pds2hJx8O1T7ZSE/OV55c9nGjT/7ub/Hk+/16cil/cp7uyc/PASF9VIF6pXAObaDTWT9K9+ug7Go8jKwRsLaFi0+x/gAVLOrTc3/A+tNBYP3YRAvWGQcixK4g5JlVjSJk6p8CIX38erKNP/kx3ZMnOwAhb4jkvXTxIQfhpF+T/xQdJ+sEUB995g9QP5cRUL+EaJ9/vAyB+lYH1LdlBNTGkP8UqMEK0cb6BdR9HKiROqAyEaisAmWX0RvUrZhE0DbAAhcg
*/