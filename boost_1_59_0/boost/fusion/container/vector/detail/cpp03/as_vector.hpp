/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_AS_VECTOR_09222005_0950)
#define FUSION_AS_VECTOR_09222005_0950

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/inc.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/fusion/container/vector/vector.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>

namespace boost { namespace fusion { namespace detail
{
BOOST_FUSION_BARRIER_BEGIN

    template <int size>
    struct as_vector
    {
        BOOST_STATIC_ASSERT_MSG(
            size <= FUSION_MAX_VECTOR_SIZE
          , "FUSION_MAX_VECTOR_SIZE limit is too low"
        );
    };

    template <>
    struct as_vector<0>
    {
        template <typename Iterator>
        struct apply
        {
            typedef vector0<> type;
        };

        template <typename Iterator>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator)
        {
            return vector0<>();
        }
    };

BOOST_FUSION_BARRIER_END
}}}

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/vector/detail/cpp03/preprocessed/as_vector.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/as_vector" FUSION_MAX_VECTOR_SIZE_STR ".hpp")
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

#define BOOST_PP_FILENAME_1 <boost/fusion/container/vector/detail/cpp03/as_vector.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_VECTOR_SIZE)
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
    struct as_vector<N>
    {
        template <typename I0>
        struct apply
        {
            BOOST_PP_REPEAT(N, BOOST_FUSION_NEXT_ITERATOR, _)
            BOOST_PP_REPEAT(N, BOOST_FUSION_VALUE_OF_ITERATOR, _)
            typedef BOOST_PP_CAT(vector, N)<BOOST_PP_ENUM_PARAMS(N, T)> type;
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


/* as_vector.hpp
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
*/