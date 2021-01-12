
#ifndef BOOST_MPL_ITERATOR_RANGE_HPP_INCLUDED
#define BOOST_MPL_ITERATOR_RANGE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

struct iterator_range_tag;

template<
      typename BOOST_MPL_AUX_NA_PARAM(First)
    , typename BOOST_MPL_AUX_NA_PARAM(Last)
    >
struct iterator_range
{
    typedef iterator_range_tag tag;
    typedef iterator_range type;
    typedef First begin;
    typedef Last end;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,iterator_range,(First,Last))
};

BOOST_MPL_AUX_NA_SPEC(2, iterator_range)

}}

#endif // BOOST_MPL_ITERATOR_RANGE_HPP_INCLUDED

/* iterator_range.hpp
At/AI/ge3sIPUDk+P8EA3ItNcB+2xc+wC36BI3A/xuEBHIeHcBYexnl4BDdiFr6BR3E/HsPDmI1ZeBJP4Gm8jjnoSd58h9UxFxvgJeyAedgVf8IReAXH4684Ba/jSryB7+Mt/BQLKcc/euI3WBSvYDEsSv57Y0Usjo2wFLbB0tgdy2BfLIsjsBzOwvL4EvriEqyEa9Ef12Nl3IK1cBvWxQysjx9jAznP9hGs75iyDXKeVSLY
*/