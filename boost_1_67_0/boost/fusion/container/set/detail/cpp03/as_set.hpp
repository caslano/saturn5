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