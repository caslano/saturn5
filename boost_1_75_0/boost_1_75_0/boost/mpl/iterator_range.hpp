
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
7/slYv1hfy0otSqgekOM9i7/NnhDi16sc85rRel0m9pJu5H6UWO21ZeebdPCDKbWe0u22DwX1AvpZ8omukRngLyc5eQ0myeeig5deo+230RFEvGzNX65t2FvSFv+ZhVj7ePn6mLQImqSWq3QI8tDXchAKdGInTf9eVRBRyMQNwmjo/iYSQX8B1fK4+cURLNyL9sseKIE6KT71Dn0iylL6luHc6C3QYtlyLUht9FBU/um3eeCc4qGffiH+cCogr5DvO1IhdAdx1LhqChfCu/vA7kXA7mXKff+A7zudPss9X5Cww8iM9EQyfaVqahDy5HGHYwJsGbXu8lYXKtaB6VV17seLDhYSX14zqrkQTuA1kUEjCMEb38Qvr7coayhIemVqYXJowTC0SVPiX22PwYRjyjVgGpiujIT9nI8kh2n5mW5UmL3Ah/jldm/dW2PRVMDJ4X793sCGC8HwqVga3F7EoadHg5pBftTkw/lPwr4+6JvVs3mzPjZyEd89iWEOz3ycxoGXdA84h1dQ3V9JuaxbWKyRmmJXxRvUKsH46zbB8W9uBQOZ0SNlXJkImXyCnmOqI44HH778ofYt5U0+mgrOJ9QqZPaafnwWU1CbgnIrgPaZ5RXpQl1xfKKK47Ewx2oKu2TT+TYFGunqz5n0VQy0HFuvcdO6L4TOtinv67x1VKPdYty2uloC9noYZYkijT1XGY6ceB0Ka6+Q6f/
*/