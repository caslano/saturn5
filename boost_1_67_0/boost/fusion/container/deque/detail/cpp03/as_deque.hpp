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