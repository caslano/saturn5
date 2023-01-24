
#ifndef BOOST_MPL_ITER_FOLD_BACKWARD_HPP_INCLUDED
#define BOOST_MPL_ITER_FOLD_BACKWARD_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
// Copyright Dave Abrahams 2001-2002
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/O1_size.hpp>
#include <boost/mpl/arg.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/aux_/reverse_iter_fold_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(State)
    , typename BOOST_MPL_AUX_NA_PARAM(BackwardOp)
    , typename ForwardOp = arg<1>
    >
struct reverse_iter_fold
{
    typedef typename aux::reverse_iter_fold_impl<
          ::boost::mpl::O1_size<Sequence>::value
        , typename begin<Sequence>::type
        , typename end<Sequence>::type
        , State
        , typename lambda<BackwardOp>::type
        , typename lambda<ForwardOp>::type
        >::state type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          4
        , reverse_iter_fold
        , (Sequence,State,BackwardOp,ForwardOp)
        )
};

BOOST_MPL_AUX_NA_SPEC(3, reverse_iter_fold)

}}

#endif // BOOST_MPL_ITER_FOLD_BACKWARD_HPP_INCLUDED

/* reverse_iter_fold.hpp
E/wc2RxthMNchotx41N2hG3zl242t4GjaDGdn9ZSRS2F1k6Mj9pO7t0wXz++TB+V5GTKKedfcJlLQJvuHX9pNM4Y1WVOmGr/GjXPylO6V82tu2LxEEjpYdku2i5uCRTJ8zwmMgjDACo5zlJ3BUnyo1wEu3i+tyCuH4PW/DAsXj4G96AIzVZwjBeGfy3R3GLT44/semgCnFusMHI8EF6GdomqnFAX0B5mECXSHlH7yW39pKXUa5l525xCfSap+3LtBj2+naDtFuRXe5XWZhy8zA64xfI1esRRA3v45oLLVTwBjqju4eBqFc9AcjR38if1/Mt3PAnt6Pc/27Huk9pRFBLb0Q8Ohx3TaxLbUTrF5aACRZc429TupU/wZT6D8bKbXYvAjubH/gAIen3p1XJ7FmehRN1NiLoRL4Hv8KC7L+uKJY3abgRHsgJGBlvpNkH0AM3T6UgZ9JNTGLJ0zGztHuhVymACHxNxN2Q3eZnGm2Vw2DM1fLLXi+mDQJrbi+lNXXr7yMxDJezYy2uk9uSmoIa5NnVhyyO35PAcpr0GLbpgveJ7vBYaJgOCVvrBJD7nYBJWej0/t72ukcsAqPyeN+HcndnmOlr2EYzyEt/1T9K+djf4AgxzWOq8iV+9a+jN5NmGrcbekL89kEMz3Ifvcqb3DtmaO4g2X9GPjfbTa2Dj9+xCkqcH++nO8OaOI3M8x7OjeicYeQwzyIqU
*/