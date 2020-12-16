
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
ImJjmn+gAVpr1d5pkzARqsNGqpW7ZTLGCfZHKeWpTfR7Hj7H1MQmOkib6JR6+wZ9W/JZMIFrv9ebCPP3l+95Ey1DoRpsooOEqXkFBtRbSz692iCYgbX3fkVYWzKNSgzgbKlpwi8W8o91meUM6QwQHhzybz/qPyzqVxXuh7MwsxW3AIYLPzC/Q69MiPG5NMMnc76o8BHnG8KXqXpwf8AP7s0VaOtwbfaP5GP5/14IejhNuB31Kq4JZqWcjUPDp1N2emgIob6IR/kkzjafp3+ZNVIP2vMGjqdZXtcA4jrD3H3dgUMXXwn8/tsZ6n266G6FUaP1H+6R8s/779NUu8XcGrcCick5Mrq9qnsi7HuD7JbfzS+FQhmNMujhrRMeLLquEj3d5rFiI3cxHhYofNK9tNgjAzfTw+jTO7DS2BA9lh6GZqfSV/EKrgR6d0qvviSUySaGFN7iHsHmy6a9K1/hZLoHFRc/laHFU56T49FL90a+x8+ZLt7jaU/IGzWO/suvou2hPxAZP7vOjtqfUtEHCOLxEBBx5Id+yiMZy49IoVGF/2sbOJNncFpgKs3gEuBSf3hSuG2gkDNKkVEuM86ijGLOuA4ZAZnRV6osnLIIA7E5MFPuoL20KEznSC9AONjORYexTlu2pGB/ql2WjDj3gBU5RwRqpxm50BjvlJuHfWXhtPUAi1x7z8oG3Pw9p0J9LfCW763h7xSXgp11CaHcZg9/p+tqXVJP3Mn9tzRjT5mVw7EpGvs/WSDlA2CF+xBVPOAwL7kvSitqNE7oumsxy8pHTwu2ZNBuxU5EqOPaCg92fxu5lB9MUEsJzdXUntxx4p/Mjwnv84viwLs7EAHvRfenAu/QJ44avJ/fFRPehcviwDvz6gh4e96TCrxzFx81eIfEhrf43jjwvnNNBLw/3pcKvItCRwFe8+JbG79f586X79f49+eFVTZ/lxebLa+2sF4nI5dPMu78h/nO3zFTadX11S5K/oY18mh/Tqffht/KI+F3iw6k7LcqOv7FvAj4rg/Y4fuFDb6XGL7+MeB7745I+B69NQK+C44Evg7z9P2hwRykb1XzCkWZwf5JQ7BoagQE5y44VAgs+qcyYn6Kr7LPT53Dmp/HeH78M6Ln52Mjcn7Kb4mAbtC9hwqdpH9utvM7hi4/kIq+yVbia5uVhjWK3MA1aggL2eVL8XRFdla/zNcy+3MPXWKLYl9ynZr5YwPXy2tVNeDjBsKTaXi4yInKONW6yOtxkftxkaN+KdcvU/W3TeP6vcMdjBl6iktV9vMyOytSYNUCk/n5PUfxVo6cP8ci0D+R81lWYbdP8DgpfNxyAidCrTaFwERiPTfM0vqPt8fUf50F+cfSOPQWanY8R5S5485Y9V3nqPaviNX+uimR4zM/Olu01Tlef+YLZ0fx/+5MxM/bMzOK/5ew/JizI/h/S5Px/2bMjOD/JS3/ApGm9vXcdh/G3+j839HIHkQ8RJ3BLPpL9iCLBNeg0CmtNqZoqw2jgT6QsV+Db5QL1V9VYOZsm93HrMXyB4otsRdbYy82T/7AS2oSDlMgzWx+I8Ypuf/vCoBe4xrlb00CvqFC8yeikDiPd4s2yXqjXL98oBFMvv6YG0EVlb1SeglSUGseal10p1VrLmo9cYVVawFqvb7YqrUQtRqkfPYgGW6i6mJUXclRblB1Car+iIvtaPp9TfUD/rQ+f2eUxzo/HXD+Wj2Q6Pz9dZQo0/SOWPV/M0q1/5dZ0fn8fmsOZ39FYPlLB/clPvLEQVsQ/uxjxZ+ZRPZm6gHcWJ+bHH288ctogLG/hy2OPO+9AXs/plgT+q8RO8ucdE3ieIvmp2dG6X9ii3Gn8fz/zdb+cC0=
*/