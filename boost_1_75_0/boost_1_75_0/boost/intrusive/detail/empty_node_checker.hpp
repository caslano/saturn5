/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_EMPTY_NODE_CHECKER_HPP
#define BOOST_INTRUSIVE_DETAIL_EMPTY_NODE_CHECKER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {
namespace detail {

template<class ValueTraits>
struct empty_node_checker
{
   typedef ValueTraits                             value_traits;
   typedef typename value_traits::node_traits      node_traits;
   typedef typename node_traits::const_node_ptr    const_node_ptr;

   struct return_type {};

   void operator () (const const_node_ptr&, const return_type&, const return_type&, return_type&) {}
};

}  //namespace detail{
}  //namespace intrusive{
}  //namespace boost{

#endif //BOOST_INTRUSIVE_DETAIL_EMPTY_NODE_CHECKER_HPP

/* empty_node_checker.hpp
lVeGTiuVX45tVoMZ4kGnKkm544JZHcL6P0TQtsLl4+jl8hdtO8FgwiLowoiX+ukgflc9y1sjD97jfhNuz0GCXfR8FexW/okR5XGFIEGyYFYQYecLjUrAYulgvVjvUkvXuO+wRxt+y0ySf6lBWsr8xUqEvTvKC5vNcVSD7G0ju2GKEXehUU613FLJ6ez43P3gA7LpEXMQ5W2PM4aPfB4A3enD5eM2JVZu8dbPqyqKNxDj009E+fLBEahywzp3klaRpWvGRo2sinHwpbtGwkW/P5rUFS4AvsmI5gJrsgHXnt/vl9F85OsxvIUd2vW7oRtSI3HtgJzfKEMb4jUaIIokOMIzTwXfwkNg6P1rrIYovBR+Hh7/91Vc8WD6/EhkNSabAfnfyusUDrjNkVWmWcvMF3iIMLYDPr9z0KMoG/Aes6Ticln6ULCENUNV8HfiYVhSe4DqhZjHeHqUWiiVnXf0M2RGFAgALVggQx84+gofi7NskG/i+G8rvFt3hk978d8Lm+kwOrtD/fJn3L2umaP2KdIaon8auNKwFxtOWFJkyE4B4dY4I9OsHZ6WCE1WI4xSVMk7I2xr4Lq0Q3mir0Io3mqRHHHzP9V9/dVxBlJdBF5b6jIDmIEM67fAmWpJlzm340oAshsBMY5V9yrfQoYml/tCKQWffxSdZjfSULHdwQFS9U+ioD9AOt7pluVYHDtoPhLynej1XWhOEVbM
*/