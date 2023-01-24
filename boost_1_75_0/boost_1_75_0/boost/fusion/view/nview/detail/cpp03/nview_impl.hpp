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
BNdfOXJCGs3bLLTXZdvly92oLpWIV4VJ5bIaqDfFFJ93XMgMG1gEwA3KmNYmuouwSp/frn/FJM/xkIE1B7N+a0M9BfS1EzI+vLpU12tsJRi4q6qTsMOxrhT541BxFwNn1VOexjNf4YghmhnZy27UrvmtXNyVNdAOxFmsVCSBN2vewc0eLbmLl3tTNKFf2taKK6M+Pzp838OIDu66C/zQRPCTjuBpbvaGHhzbf3G1OeJcEqyHwZ3ZUeNe9Ryn5eninPswwtpmq2CUSZZZI1lIltfuzjZ8qs/aVZ6+FvG9xQQghupu30WG7wn++Gf9hsbCSwqy8q6PzeNSnNE00yRlpSt1Tevl66FoPeD0jA5UcKFDCIKOP0RUtPhDv9WGckcPI0cW69/hBtzcSqJXYwiT4BTtf632ssMlsugAG8Z0j2Of+0u3nh83RCix/guNRmq7Y514S2fPTt/mlVIdoVaBpSXKrm9L0dArrD4PHzBWdmL2DsR9Qcg/o7Joef4u+igiRbo5z3Qoxuq1Sf0Gnvzr1Dn/vbYUx4ezbLehLlu1ptaZ1T5QbIgwULjiKhJGsuP8VAUamh2CU4nnW14iVfuk56QlGm173A5n4TcnXuezyMp15Mrj4SkmPXy57LpFcWnM5HZ1WcviWu/omgqIXk8Ghb1Sh+QjyfXrjfyAZR5k97A9asEU58eboaZL1ZYLn3NZpb/ak76FpHA2Oocm
*/