
#if !defined(BOOST_PP_IS_ITERATING)

///// header body

#ifndef BOOST_MPL_AUX_ADVANCE_FORWARD_HPP_INCLUDED
#define BOOST_MPL_AUX_ADVANCE_FORWARD_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/next.hpp>
#   include <boost/mpl/apply_wrap.hpp>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if    !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER advance_forward.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/unrolling.hpp>
#   include <boost/mpl/aux_/nttp_decl.hpp>
#   include <boost/mpl/aux_/config/eti.hpp>

#   include <boost/preprocessor/iterate.hpp>
#   include <boost/preprocessor/cat.hpp>
#   include <boost/preprocessor/inc.hpp>

namespace boost { namespace mpl { namespace aux {

// forward declaration
template< BOOST_MPL_AUX_NTTP_DECL(long, N) > struct advance_forward;

#   define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, BOOST_MPL_LIMIT_UNROLLING, <boost/mpl/aux_/advance_forward.hpp>))
#   include BOOST_PP_ITERATE()

// implementation for N that exceeds BOOST_MPL_LIMIT_UNROLLING
template< BOOST_MPL_AUX_NTTP_DECL(long, N) > 
struct advance_forward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_forward<BOOST_MPL_LIMIT_UNROLLING>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_forward<(
                (N - BOOST_MPL_LIMIT_UNROLLING) < 0
                    ? 0
                    : N - BOOST_MPL_LIMIT_UNROLLING
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_AUX_ADVANCE_FORWARD_HPP_INCLUDED

///// iteration, depth == 1

// For gcc 4.4 compatability, we must include the
// BOOST_PP_ITERATION_DEPTH test inside an #else clause.
#else // BOOST_PP_IS_ITERATING
#if BOOST_PP_ITERATION_DEPTH() == 1
#define i_ BOOST_PP_FRAME_ITERATION(1)

template<>
struct advance_forward< BOOST_PP_FRAME_ITERATION(1) >
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;

#if i_ > 0
#   define BOOST_PP_ITERATION_PARAMS_2 \
    (3,(1, i_, <boost/mpl/aux_/advance_forward.hpp>))
#   include BOOST_PP_ITERATE()
#endif
        typedef BOOST_PP_CAT(iter,i_) type;
    };

#if defined(BOOST_MPL_CFG_MSVC_60_ETI_BUG)
    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
    };
#endif
};

#undef i_

///// iteration, depth == 2

#elif BOOST_PP_ITERATION_DEPTH() == 2

#   define AUX778076_ITER_0 BOOST_PP_CAT(iter,BOOST_PP_DEC(BOOST_PP_FRAME_ITERATION(2)))
#   define AUX778076_ITER_1 BOOST_PP_CAT(iter,BOOST_PP_FRAME_ITERATION(2))

        typedef typename next<AUX778076_ITER_0>::type AUX778076_ITER_1;
        
#   undef AUX778076_ITER_1
#   undef AUX778076_ITER_0

#endif // BOOST_PP_ITERATION_DEPTH()
#endif // BOOST_PP_IS_ITERATING

/* advance_forward.hpp
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
*/