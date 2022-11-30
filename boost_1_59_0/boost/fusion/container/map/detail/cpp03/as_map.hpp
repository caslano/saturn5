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
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
*/