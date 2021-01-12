
#ifndef BOOST_MPL_INSERT_RANGE_HPP_INCLUDED
#define BOOST_MPL_INSERT_RANGE_HPP_INCLUDED

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

#include <boost/mpl/insert_range_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/insert_range_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Pos)
    , typename BOOST_MPL_AUX_NA_PARAM(Range)
    >
struct insert_range
    : insert_range_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,Pos,Range >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,insert_range,(Sequence,Pos,Range))
};

BOOST_MPL_AUX_NA_SPEC(3, insert_range)

}}

#endif // BOOST_MPL_INSERT_RANGE_HPP_INCLUDED

/* insert_range.hpp
Uquji48am5gk699qK5dHW+PvkHFu7JzjS57W8OcP1rOCFfT5UE3bZunb3qSn6BzFD7tMX870vqSNcmhikjmWZxRS7mc5twgRxEvOUI/LRZIfljpfx3sDWXcL1m25KO9W1/2Ci3Uzj1PezGS+SGbotEfWJffLdTmYE0ePNtvKOlPl/knq8WVvO+fzDpY1h2kHPpE0ONxLy3zKUeU4j+XCuQqW7FPXHyHrilF+J2Q5MTItSW9O
*/