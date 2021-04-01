
#ifndef BOOST_MPL_AT_HPP_INCLUDED
#define BOOST_MPL_AT_HPP_INCLUDED

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

#include <boost/mpl/at_fwd.hpp>
#include <boost/mpl/aux_/at_impl.hpp>
#include <boost/mpl/long.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(N)
    >
struct at
    : at_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,N >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,at,(Sequence,N))
};

template<
      typename Sequence
    , BOOST_MPL_AUX_NTTP_DECL(long, N)
    >
struct at_c
    : at_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,mpl::long_<N> >
{
};

BOOST_MPL_AUX_NA_SPEC(2, at)

}}

#endif // BOOST_MPL_AT_HPP_INCLUDED

/* at.hpp
d+SEbv2bwwQLM/rVMWY9IQ5qFViacGF6vZY1Uub719oWarNtPVmuuIxEKb+FLnkeUZnMOx66aChTnigXnn6RfpOT8O+iKnJqiTsz/MKRkU593RXIgvK1fLUMUlC3MR1rZ27AFFY24lxf9Hrqefdcx/eNQnO8LarJ0iU3pqoK/Qdew+nBqnLLrngaK7zh3aReTjaSQbP6Xapc7A7P//JWPaWatr8gtzfwfqebltW7oHcWWHUS3WQ3W4fs4rJSszMHGIgmP/ZqkqROw1bOAwPzBOagfeldG9L+YD9dO2PXc+7Cn2m7EoDs/mboRud097saB2b4byKLUGtZF2DMqL/HBQhfoecL+MR43q3gbu+0xs/tGhhNytnHmRC7EjOHDmGHezYKgzsspKFVWSvJ2GeHEtYuV2t/gyRRUTlNTsxaXpCPCY6hCrnHwr2sKOmCACH8Bw1IUrWqz+EPQaWBeP42vJWfoNBnEa2xuwCajnzljlkvVTnI83+af8ebNn74jRuGJ36KMTyWXjcEZZXNy9m3Bet7rnUU5+xmS3PflNBinzs8+PCxg7Iyn4RdOA==
*/