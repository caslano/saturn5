
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
aQ7IW7G0sEA0G/CPLMRjEvS/MZHah36cXmJoGsOegrF7StPgrc1QncAaqeL7I566jQRZXOaxaacOxZ4VVVNgFL9ixARlekEhv5O4QicEyHWZcGJHliaXq2KJHpg65tsS50B0C/wsP0MppGD+smYVLLnYjB3lxS1M/WsAuA+zRKqyWTYw3NIdO/e2qAKtU0i82PZQk80nRlY1HRfIM6vU//dA70+dDy/5Yb3JIkk01UZq3pFOzptDUZ9Mc+gA/xk7iIhCiWliWj+++2TT487uM5pwXEwTyyUnUaSWXiYNveBr6kY8EB7jtAyS3Mnq6nrS+X0YQeP54SEoHN+fpeF2XUobA6MVESa/7PX/Iwcx34mOtWDgcwADXnrA2pnsh7sxeMchOU2CJkoBLXn343XKGtqxA+xSgcrd+a87xY8itX7zxW6Kr9xx0zfsKUbhambK75X6trtxFIPfmpQpe9iAG4tfRrSLhVpEoMHvGIfnxBolPS2SxIHCFtDABFOI+c6NU/6CzAUKib3mTsa4jFIx2pRLR6ja0/XUowPo2nimnQUvKOD7M+0nwgN1Ag==
*/