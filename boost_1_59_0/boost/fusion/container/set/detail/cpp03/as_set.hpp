/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_AS_SET_0932005_1341)
#define FUSION_AS_SET_0932005_1341

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/inc.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/fusion/container/set/set.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>

namespace boost { namespace fusion { namespace detail
{
BOOST_FUSION_BARRIER_BEGIN

    template <int size>
    struct as_set
    {
        BOOST_STATIC_ASSERT_MSG(
            size <= FUSION_MAX_SET_SIZE
          , "FUSION_MAX_SET_SIZE limit is too low"
        );
    };

    template <>
    struct as_set<0>
    {
        template <typename Iterator>
        struct apply
        {
            typedef set<> type;
        };

        template <typename Iterator>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator)
        {
            return set<>();
        }
    };

BOOST_FUSION_BARRIER_END
}}}

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/set/detail/cpp03/preprocessed/as_set.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/as_set" FUSION_MAX_SET_SIZE_STR ".hpp")
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

#define BOOST_PP_FILENAME_1 <boost/fusion/container/set/detail/cpp03/as_set.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_SET_SIZE)
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
    struct as_set<N>
    {
        template <typename I0>
        struct apply
        {
            BOOST_PP_REPEAT(N, BOOST_FUSION_NEXT_ITERATOR, _)
            BOOST_PP_REPEAT(N, BOOST_FUSION_VALUE_OF_ITERATOR, _)
            typedef set<BOOST_PP_ENUM_PARAMS(N, T)> type;
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


/* as_set.hpp
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
*/