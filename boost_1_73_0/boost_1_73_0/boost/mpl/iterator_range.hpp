
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
OjsXeFDWdwRmVczf/rakRuQCD8r6D4FZ2RlZw3cKyp8LPCjrFHEeL0mlcoEHZf0fgVkXf/D7+G5B3Z4LPCjrewKzuh56JEdSa3OBB2WRDJj1zIw3rl4nqO25wIOyMjJg1r4738yT1Iu5wIOyzkJZ9Lq8S1BHcoEHZZ2Nsj6Y/ctRkjqZCzwoq5eSJT9pzxoIPCjrHJRF11GSGjEQeFBWb5Q1vWvgu9sENW4g8KCsPihrR6JvjqRSA4EHZf0IZV0=
*/