
#ifndef BOOST_MPL_AUX_PARTITION_OP_HPP_INCLUDED
#define BOOST_MPL_AUX_PARTITION_OP_HPP_INCLUDED

// Copyright Eric Friedman 2003
// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/apply.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/aux_/lambda_spec.hpp>

namespace boost { namespace mpl { 

namespace aux {

template< typename Pred, typename In1Op, typename In2Op >
struct partition_op
{
    template< typename State, typename T >
    struct apply
    {
        typedef typename State::first first_;
        typedef typename State::second second_;
        typedef typename apply1< Pred,T >::type pred_;

        typedef typename eval_if<
              pred_
            , apply2<In1Op,first_,T>
            , apply2<In2Op,second_,T>
            >::type result_;

        typedef typename if_<
              pred_
            , pair< result_,second_ >
            , pair< first_,result_ >
            >::type type;
    };
};

} // namespace aux

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(3, aux::partition_op)

}}

#endif // BOOST_MPL_AUX_PARTITION_OP_HPP_INCLUDED

/* partition_op.hpp
M2oPfsZ/ZjyOQEL2V4vbaZjMGIQ63UTO3wOrLozeX+ZfbDvTVOe7i97kkDbueKJRaKNrKyj69c/1/WPRAPZDkxJu/aivjkEAMI1OtUvlZk8HiCfKj3Djmzo83i3rIrNAJZjfmj+VxWOpA9nGwOczyKTEWaVf1u7Ldql5ZBa9Ud923IzBXkd9Y1HWRePobZddPhbItt22nfWGQC7E68Xl4N2zHeWrDDHjEpqFoXXpJ8me94uFvv0E04w8kcS16JMOZs0G7DE67ChaCqgLSlGl2fEACmNKqoPTkxI/P9QXYReFR9Qn8hcq/5wAMfhXpj7b2qoawaFA1BTz5A26AOmKPo68LP3z8luzIh2m46+hLTLOmd5kLgWh5X2T21uCR05HzbVVOQXwHpLujJ9imPSisuDw2y+B45lcdEx0jNXaRpOAGBIrnljSjNMRy5rZEYLTwbWe2xnAroVIRZ1L6Kq3cTHaL8K8mZ8JGKZ02MOqUBfy4d+GywOyv8j+yLKzAKZzXMDCrKf4KO9f2VIH28IGmYjkqzxlfawGWKFWN4uXz60D2T8V99xo5YEsOYj9GT7CTtaf2XzO3gZOaTUxpU6KW32l2S1nKDPZaxy50vH00GpStqrTW7GrPX20S7Pz+bUaxyLqEvCZMw/KXSR7mZGRoJ/6u/s76aNsX1dG3GfUs09epr+khWJIDIU49H+mo/+GScScFHkzltdF+2T7
*/