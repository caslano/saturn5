/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_PP_IS_ITERATING

#if !defined(BOOST_FUSION_NVIEW_IMPL_SEP_23_2009_1017PM)
#define BOOST_FUSION_NVIEW_IMPL_SEP_23_2009_1017PM

#include <climits>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/fusion/adapted/mpl.hpp>
#include <boost/fusion/adapted/mpl/mpl_iterator.hpp>

#define BOOST_PP_ITERATION_PARAMS_1                                           \
    (3, (1, FUSION_MAX_VECTOR_SIZE,                                           \
    "boost/fusion/view/nview/detail/cpp03/nview_impl.hpp"))                   \
    /**/

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace fusion { namespace result_of
{
    template <typename Sequence
      , BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(FUSION_MAX_VECTOR_SIZE, int I, INT_MAX)>
    struct as_nview
    {
        typedef mpl::vector_c<
            int, BOOST_PP_ENUM_PARAMS(FUSION_MAX_VECTOR_SIZE, I)
        > index_type;
        typedef nview<Sequence, index_type> type;
    };
}}}

#include BOOST_PP_ITERATE()

#endif

///////////////////////////////////////////////////////////////////////////////
//  Preprocessor vertical repetition code
///////////////////////////////////////////////////////////////////////////////
#else // defined(BOOST_PP_IS_ITERATING)

#define N BOOST_PP_ITERATION()

#if N < FUSION_MAX_VECTOR_SIZE
namespace boost { namespace fusion { namespace result_of
{
    template <typename Sequence, BOOST_PP_ENUM_PARAMS(N, int I)>
    struct as_nview<Sequence, BOOST_PP_ENUM_PARAMS(N, I)>
    {
        typedef mpl::vector_c<int, BOOST_PP_ENUM_PARAMS(N, I)> index_type;
        typedef nview<Sequence, index_type> type;
    };
}}}
#endif

namespace boost { namespace fusion
{
    template<BOOST_PP_ENUM_PARAMS(N, int I), typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline nview<Sequence, mpl::vector_c<int, BOOST_PP_ENUM_PARAMS(N, I)> >
    as_nview(Sequence& s)
    {
        typedef mpl::vector_c<int, BOOST_PP_ENUM_PARAMS(N, I)> index_type;
        return nview<Sequence, index_type>(s);
    }

}}

#undef N

#endif

/* nview_impl.hpp
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
*/