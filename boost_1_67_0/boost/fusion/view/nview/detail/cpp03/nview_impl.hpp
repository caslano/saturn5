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