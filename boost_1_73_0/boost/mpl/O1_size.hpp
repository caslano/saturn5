
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
sSE2xIbY8L88FBVG/1b9/0X6uZg2IXQB+I/1ARhpV+Sb8ll16St/8r4vdn/3n3p/533eWD/zsSE2xIbYEBtiQ2yIDbEhNsSG2PBvHH7r+//k1Db/lPv/Ntl95IZ3cBplvx/CSRXck03M7R8lOfXsNpGuadMK/X39okTaRl3GQdY9mUemhvaJ87aVH5nP+HfZfRbbZlzYaHbbqA9NzN8Hx/ao8WKpueN5+7/dm51GoYhwhBBJ
*/