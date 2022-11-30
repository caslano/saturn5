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
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
*/