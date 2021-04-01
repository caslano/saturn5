
#ifndef BOOST_MPL_POP_BACK_HPP_INCLUDED
#define BOOST_MPL_POP_BACK_HPP_INCLUDED

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

#include <boost/mpl/pop_back_fwd.hpp>
#include <boost/mpl/aux_/pop_back_impl.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct pop_back
    : pop_back_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,pop_back,(Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, pop_back)

}}

#endif // BOOST_MPL_POP_BACK_HPP_INCLUDED

/* pop_back.hpp
izzMZqXs9EW3VSMHexP+Q7xwDdEwQT5KQSYwfgmt5OzY808yMAfU0cr9WA0Ze1CcLQ/iZlmx5S0e2pqqFKu1kBegFTk1gvlwkdbddAeFb2ChIgRT9++Hs4MdxXnM8K0cJIZ0n7jMHCaMQ4pbfXOEvMwY4lwwIoUeDl2HuAalJrwEklAmWlCcVs3MRfkwCSVqlskyDKBgknCQnAdEZelMJSL2IXPWqwVCO2VNIitDz7v78cMEXpQv0/psMLDDs7UKRScvE3RitS03IOQDLsl+VaCDHD94R6x1yWAXpzETxsWFcN6by7KSc0eoksdXzszfxnsPPAZ8oZTZWS9MKvbFU+n3bk4x9mxE6pRThY4h9w3escsGNAZCkb3N4J6p135GjQl3Ph+b56It34+23OsGk5PQm+9ypc/+7bLxLEtVi2bGFuUhSEKRhIR1v7yorARqBwmdh7H7LPU57Xu+wImzyBFyP/c/S67JOitwCG8X5AkDW4ZFcN3GiM2LX8h5LMm3i/sQYbdXb/wfsVqvjIJEJOeIL8VYOy7NrM+onotTTS16Lg+quf6Gg6Wnxg==
*/