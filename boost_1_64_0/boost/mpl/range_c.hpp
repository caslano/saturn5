
#ifndef BOOST_MPL_RANGE_C_HPP_INCLUDED
#define BOOST_MPL_RANGE_C_HPP_INCLUDED

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

#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/aux_/range_c/front.hpp>
#include <boost/mpl/aux_/range_c/back.hpp>
#include <boost/mpl/aux_/range_c/size.hpp>
#include <boost/mpl/aux_/range_c/O1_size.hpp>
#include <boost/mpl/aux_/range_c/empty.hpp>
#include <boost/mpl/aux_/range_c/iterator.hpp>
#include <boost/mpl/aux_/range_c/tag.hpp>

namespace boost { namespace mpl {

template<
      typename T
    , T Start
    , T Finish
    >
struct range_c
{
    typedef aux::half_open_range_tag tag;
    typedef T value_type;
    typedef range_c type;

    typedef integral_c<T,Start> start;
    typedef integral_c<T,Finish> finish;

    typedef r_iter<start> begin;
    typedef r_iter<finish> end;
};

}}

#endif // BOOST_MPL_RANGE_C_HPP_INCLUDED

/* range_c.hpp
p9elFeueFz8mxmVU33xujysa3KVdmEX/Wp5dA86F4GLdg+5mnGLhQXeHZR5hCNl8PcEDXnPo6g4PN4Y3IK3QUXbxpNgUmQPoDpRVElCuY4Yw3D1PENi/r02mX5Ho719xuZG/TdEh93mcs5yNMbmxEmVdpRLOc/F5/A2EDuiE7ELfH5nhZb3DTZsl5P+bKNnJTN92dtfrxfWp912V9Ionueb1YqdHbNVsmZQer+ra0n6bOzl940bngn3GgWmD9V8ZRcUKClWAzbE7Irr2/+3lk+yUqHq35GrDKHlPQoZ0EZ7F8UwxRiU8ZHpBmvhg8kXEMRQe7RZ+9wQVN98FxWoXyii2lj2cosGbrJI4cENCA9HXioCrYRo35lYHmfoQ4NCnGLVNqu+/r1ds58YTCpeai6vObSH3fprQXK+EkBVqyjhcnANN+iWR+Mx6Lvoyu97PEOmd2FpEgnHvrJfrsNO9pgj3lZWJdqdd32UqFUdjX6elGHILPrTWIob54jJaSu5schqE5EW7OnuBrb/kHS0xGIfELSj+IJ8Y590V4wUiaFq2htSoFo1moJGf0g==
*/