
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
t7Rdcse7nU4XlBYVivlVe4u2HZjj7kUHPnW+QD/7Cv3RTzb2hFFGXKicFNxhAn1upQCDvF5ctfNfK1kGXZHgopJqBht8BttQt1mQkIDdWFFri+xaK0dYUbFdEpbDFxdXblEzNlijAlfp1awC6U4tjZFY7FIriyB0ibTCHTgjZzM0tnFgp0pqdU60pwbZynoJwSJVNiBBC0irTt05WE2VYImoLmHKZX0B8ANhrvTmVTVrquEZBV9Zz4wGSZPScLREG/m74U4CX4W8pDfTeG+xD2NnO6VxXUvfeEhDNBMqmCJ3K2qzxzwGy/M79iHPx0MWYk/jY0EapPVY5dySdvZTSBVfYO/w2QC3c2/CVBuIopCNcvUCNuQX9b9A0L6hNw6SQeQ35WmwJMw4gEIq9GJBVgbaJI5PbkZ5MRwnJ55vPJoUcffz5Z4I3is6KCE7DUnTyTN/Iy+KfBzU2IGRhjufyL8nNHK6BW8u8KkjFB+XP0xQcUtRUXNtytW1WbpuagmA4J0Wuu4xb8x/O9gdgG6L3WjrEvirqsXez76oJ/fF00PxmGX9jK6+Hg6zf19XLfZIHkTZjDpLQKxMHZ88DSb5cPTQYpkQuKTls/hsz0dHRqEIZLeIyyir5RpbrEX+HPtL0Rht/DnpsctL2no1
*/