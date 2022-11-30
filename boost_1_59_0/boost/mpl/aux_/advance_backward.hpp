
#if !defined(BOOST_PP_IS_ITERATING)

///// header body

#ifndef BOOST_MPL_AUX778076_ADVANCE_BACKWARD_HPP_INCLUDED
#define BOOST_MPL_AUX778076_ADVANCE_BACKWARD_HPP_INCLUDED

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
#   include <boost/mpl/prior.hpp>
#   include <boost/mpl/apply_wrap.hpp>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if    !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER advance_backward.hpp
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
template< BOOST_MPL_AUX_NTTP_DECL(long, N) > struct advance_backward;

#   define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, BOOST_MPL_LIMIT_UNROLLING, <boost/mpl/aux_/advance_backward.hpp>))
#   include BOOST_PP_ITERATE()

// implementation for N that exceeds BOOST_MPL_LIMIT_UNROLLING
template< BOOST_MPL_AUX_NTTP_DECL(long, N) >
struct advance_backward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_backward<BOOST_MPL_LIMIT_UNROLLING>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_backward<(
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
#endif // BOOST_MPL_AUX778076_ADVANCE_BACKWARD_HPP_INCLUDED

///// iteration, depth == 1

// For gcc 4.4 compatability, we must include the
// BOOST_PP_ITERATION_DEPTH test inside an #else clause.
#else // BOOST_PP_IS_ITERATING
#if BOOST_PP_ITERATION_DEPTH() == 1
#define i_ BOOST_PP_FRAME_ITERATION(1)

template<>
struct advance_backward< BOOST_PP_FRAME_ITERATION(1) >
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;

#if i_ > 0
#   define BOOST_PP_ITERATION_PARAMS_2 \
    (3,(1, BOOST_PP_FRAME_ITERATION(1), <boost/mpl/aux_/advance_backward.hpp>))
#   include BOOST_PP_ITERATE()
#endif

        typedef BOOST_PP_CAT(iter,BOOST_PP_FRAME_ITERATION(1)) type;
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

        typedef typename prior<AUX778076_ITER_0>::type AUX778076_ITER_1;
        
#   undef AUX778076_ITER_1
#   undef AUX778076_ITER_0

#endif // BOOST_PP_ITERATION_DEPTH()
#endif // BOOST_PP_IS_ITERATING

/* advance_backward.hpp
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
*/