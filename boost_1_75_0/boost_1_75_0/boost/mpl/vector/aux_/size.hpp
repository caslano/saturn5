
#ifndef BOOST_MPL_VECTOR_AUX_SIZE_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_SIZE_HPP_INCLUDED

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

#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/vector/aux_/O1_size.hpp>
#include <boost/mpl/vector/aux_/tag.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template<>
struct size_impl< aux::vector_tag >
    : O1_size_impl< aux::vector_tag >
{
};

#else

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< long N >
struct size_impl< aux::vector_tag<N> >
    : O1_size_impl< aux::vector_tag<N> >
{
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

}}

#endif // BOOST_MPL_VECTOR_AUX_SIZE_HPP_INCLUDED

/* size.hpp
lTO20g98X7uj0kzDI49aYebPtvTEifRp7Ldkakoud3Ele97YRPMUuBpgZ9ak4rjiTvTxnq7vNQa+MpbzBXm8aCEVnIe+4Ekif3YqeyZCXyblVa0sEEJZ2z0F0If3oha1xpT9LWijehcaswngpJNbqtNkND5fltrP5JXQZDF2mSgvuduM22q1+d69Unemx5sOq9Mo7sJ2q7tO/hlGHHUA4+8WGGFEf0MSjL3bwxibLIrSfvm6mFnQwDtyR3fAc3QAXkcw5S7oEm+r7+gMb0H5wruS8XZltwBblegMb38MdYK3xfO7xNtH0Q7wFkS8nX+nAW+vRLsD3t++7BRvKHe12ftf53WJt/EqTNmYUwohOIhLntOZq3ycNL4sasFyZ3YLKJEDFWQS3oCzm5brOLMb4bvAAF978J6u6wy86GpaXL2rrjtwbWxVJ2o6XKVSb3/M/DU07y3aAYZlKdhwedLYjGJPRtgOSrDYYw1bpbE5xZ6cUB+P0uiLxK2eyAnTsvdoaa6pKM5zT4FIN7L/+7UsKVGKDI7qcTeRJ/Fe8x1KccObuOFNbJJbvpK8ZZPs1EI2a2FZLXokVZnFoDHqHNpMLzvhMVMyVVzJ/CCnKhkdvph5PW1+McnXvYK0OKlSTf1TqQE6aZH6bJH2bCfB0TptqzlF7+GEAuNFlCDcPxQn//w4VPrTn0BBf5eEXr9KmFo81MLeVcC7Anq3jL3r
*/