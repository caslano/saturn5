
#ifndef BOOST_MPL_VECTOR_AUX_BACK_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_BACK_HPP_INCLUDED

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

#include <boost/mpl/back_fwd.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/vector/aux_/at.hpp>
#include <boost/mpl/vector/aux_/tag.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template<>
struct back_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
        : v_at<
              Vector
            , prior<typename Vector::size>::type::value
            >
    {
    };
};

#else

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< long n_ >
struct back_impl< aux::vector_tag<n_> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

}}

#endif // BOOST_MPL_VECTOR_AUX_BACK_HPP_INCLUDED

/* back.hpp
r/W02UWrcNyquoSbbeSNRiNwSyhRBriuqhr47p4zjfN8+fuhPbtP3X67+/n1K+YNM5krNMq+MOPn2Vnt+TvXIj1BtRzAUossqBiqMwQHZmDPuYQbc1D2htC3uhYpCq2silUWkPk0nDr/bC209oP+T3nHJpXOu1ane1DGTrr+sN3Bp4tAobSdXGwhUDmZzP5rBLP4/kLOloOnJtoCroJDvj2vomorr2qod5HoXa/BX1BLAwQKAAAACAAtZ0pSCSmccasCAABvBAAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDg4OVVUBQABtkgkYLVUbW/aMBD+bqn/waJC2tSGQMJLqQIS0ECpUqDhnWmqnMSMlCTOHAdKf/3OgUKl7euUyBfbd/fcPY8dQ9BEuCShTWT40ZqB2dLDnnEvaaLRcKSjcWtsZQNuTSePeChHDdndTqmml6WtFI+2WivXpa1VtTtkqJc0hnrMjK7RNR5TvqNcSXyPIoPTODiAQ5ItuqHXRBeQttmyTRvZ5shaHrFvTpO8Uy3/iG5JI4XA23yxtGGJaJS0WqEITwkWYsZFIy/rHw3tCSyQVGwabUo45TjsvtYL7cpaKRdKT7+fYRfen5Azj28wPTx9eL1u0Vs8+0P/KXai1cbp
*/