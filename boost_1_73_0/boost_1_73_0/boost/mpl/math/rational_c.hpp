
#ifndef BOOST_MPL_RATIONAL_C_HPP_INCLUDED
#define BOOST_MPL_RATIONAL_C_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/static_constant.hpp>

namespace boost { namespace mpl {

template<
      typename IntegerType
    , IntegerType N
    , IntegerType D = 1
    >
struct rational_c
{
    BOOST_STATIC_CONSTANT(IntegerType, numerator = N);
    BOOST_STATIC_CONSTANT(IntegerType, denominator = D);
    
    typedef rational_c<IntegerType,N,D> type;
    rational_c() {}
};

}}

#endif // BOOST_MPL_RATIONAL_C_HPP_INCLUDED

/* rational_c.hpp
yuY7oWw5A1orZSucULa4xdLXrrb0tU1GttPI6E+oZGcEtKzUyMqMrNbI6o1sn5HtN7LvjIwzcCU7K6hlg41sjJH9wsgmGdkUI5tnZDVGttTIEka2xshuN7L1RrbRyJqMbKeRpXd55Oyalg3XTNRKel2j0KtHGfQv5CrmQGc1SS8eTXW2WYyfjOWOkPR8NNu0ocImtce2XyXsi63Oeh29IzLUNs7JSma6rPBtB8lfsg/0uWlqD6tASnYLA4hRUNQ=
*/