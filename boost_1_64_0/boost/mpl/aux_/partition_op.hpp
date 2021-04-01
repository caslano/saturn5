
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
J9dt2IyRagk46YsNRtEoVd/NNOO/uvOkMEViXi07L7NOMXzUoVLHCEBgPaD0oNY9Mey+ZlKuZ8TzPsWP4VxSnNTjzulZI5CqzdlZOnUa6wPxAo02BnkSNQ5m8pVKamP4H3/N4uHup7d0qh6NhPVor8eb1q8md+9MV9MQK9mnu1vLGhkqukybuJaBSCfvnnrRuMLnT2jnB5w4+ErIewwxNNuAd39Y++cuGcUL71wUMCqyksiFonTvJBApfRVkTUtO4KP96WyJYxePFO9V9JASyaHACe7erjj4O3Uy4+5UTf7CXgdpaDHHmwgLx7cYaiYutMwxQaj0BNtreiftfd0y11PmsjOk4CC4+HsIMnatJmlsEScFHR5rV789Jb9HavpRr5eOtHewDsSgwFTSU8PbfxRDF0ctlyXpZsPndAbikDPJ0HZQLUk3l8GEt3GFuOjNnYVr//EODSVrVszwEiMdynSROBAHnAdhK1I+hYwI1lHfsJi184gw6HDH5w6eQx9/pb+R9T55kXmm5ud9eFmbNSNQWXbZ7uBp7ucL2Bu3Y/8K6Yg/ZmL8V9ccNQ==
*/