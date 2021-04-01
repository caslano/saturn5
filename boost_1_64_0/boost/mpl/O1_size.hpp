
#ifndef BOOST_MPL_O1_SIZE_HPP_INCLUDED
#define BOOST_MPL_O1_SIZE_HPP_INCLUDED

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

#include <boost/mpl/O1_size_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/O1_size_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

// returns sequence size if it's an O(1) operation; otherwise returns -1
template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct O1_size
    : O1_size_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1, O1_size, (Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, O1_size)

}}

#endif // BOOST_MPL_O1_SIZE_HPP_INCLUDED

/* O1_size.hpp
5ngG4pzxGhpfC9YgfOSfeTi+kMxnoxsWN7IsI7UVJCAWHqWuASkBF8V1PxKJ9X4mZpXAHXjuD86qkWKqcr2W4pHaJbC+8adxFr1/Q+Y8i39zfB69gDY2maJHoGfTo2A+uMv1ecLp/Fs9l32HFBoA/+6KMQH+DTzLM89kdTpYQDCSDFo18qszYw+fqPezu5bPdBi59Nx4TvziiDyVNHM2RgVd23T2xJ0dwTR5YhlKvw8UBtOz56Cb6/tosOR42sf5Pa/GzJAjsxYDN6cB8MomGvQ7xEU0L6/SX4d6qwpNXbUbWtT/fzK20eXn3Qyq96axP7qapCsFed6k49VknGhZOMOymqgg9KEfMWdCPGYRR2pbU2pRyUffvr8mWXIesPDZ27P2OwTxSP9IAMMN/ZQszvOFwRExQZCU5unr9OR/epdoaxFYX/4nfjc68kBys4wltzpBpOneyPi8/3Gu3bSDAQK93udGiy46s1Rw1bOGFKz0kfez1jsMOyw2cX5uyaYUdUZZyGrmZhhmdOqo46uyps//HQi/WP51zkr0slN9bE2bPuBDG5r5/St9vw==
*/