
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