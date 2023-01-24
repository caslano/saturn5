
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
0/pptbhmttVGuHnikcJhiFno0x+Xjt8lepD8yh3xT1qQ61XIkUnEJFlLF0p8WkAtuDWEuL1aZ3pnar/T2hHI+uKdWvVtqkeCj/mls/EsOYl+Gp0VY3CReU65TnVvmZWEtp/0J+x7ySIJvR5goO5x9w48+wCJO5ebdfcFz/j09AHPGuYVMPC6QDt0sz8IhV52XILT2RFiweNnhjKX9NAEWFBXvrMJMaLwACp1Sf0EW7UAU25oO4/rUCDIMoEvuPfIN3sIFFnqlDFEwsqqCFC/l18WBse5qfnzWxD/b2d+OkS4fq5iDADxg+Yx7y9H1nQInBzhLi/qgGFEmdjimx6geVBTOcbrsHhgEc2T83XXCQId0U3TI/x1phF1CbqDssoN23sNGnmwz4V4s71cPAI1UqgWZmBP5O/vh272IAZw9utH57dr922+BshD58Hz2OnArKc98/TxpO97COOyvHDEP4foT29MfVn/bwr/L7vpXBy8/1b0SDg7Wdl+dfz36Rd/TZ0MxOREWBcGCqFNvojTGxxVDDrkkGZV2f0kXP0/CYs9knAkvsqVKltt5wiHE1fwM9fOxzO1PH7JbgxvWYh/w6pP8qx7xtzSYdrWItahz3ru6eWxbh5U1drShLhJH+Ggk/hx92Bwd/AUCO0+yL3JuemeFD14OR//2aRhLOLvv6/CVFZd8saXW+szUeNK+mc1Zgzi66cJTeZUJ2V4
*/