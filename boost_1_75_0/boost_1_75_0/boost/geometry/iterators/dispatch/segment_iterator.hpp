// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_DISPATCH_SEGMENT_ITERATOR_HPP
#define BOOST_GEOMETRY_ITERATORS_DISPATCH_SEGMENT_ITERATOR_HPP

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// dispatch for segments_begin
template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct segments_begin
    : not_implemented<Geometry>
{};



// dispatch for segments_end
template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct segments_end
    : not_implemented<Geometry>
{};



} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ITERATORS_DISPATCH_SEGMENT_ITERATOR_HPP

/* segment_iterator.hpp
/idMk2fWi7s60fMf1vE6kfpVMPEPdmKnbED+RmVnZbeVkXgP7J1fwt/WY2dzt5ZzfP2Max23VX9woKEnSHgWmDNrycbCcnp9/YzAaI5WdfXZagYJKA3ndLsIK7WkLFim7JzV2i/P1w0mhX886F6lP/ntO/Si/pvyvw09BZCKF8aiVtqVb02tQOVA0GTd1soPUqp/jmw1OL2Rtpz0JQap6MPwdXYWOao4fLmOndQiX4pE8QND/lzvaMimcjo1JuLw2CQtQOUi4Bf2nvCw96ViiIBq+b8zFqdl06H1oOzIB13EWXeBVHBOp+PZqg/Gk7+lpKDFrQXHkpKFiohsavu3noTsK9TSPjeb+DWTWFJqLjayc17sw5k7Hbpxph1XiWwx/LWPwNqOKE2jaCAmJPpZHtnmapAmzaJ296Hu/rrqrX93ebUeFUfdeHOVKtx7ScxDJfyyZE71qygn9fluRlEzb8/+mWq5WkrH+F6w2DrhbWTwHTKI2KDj7CdbKz/21Rjb6NqS7/QOXK4f9iBiOlKhPAnjDw4T9hjRpjP32hCOZ/3N0tVX8uGzqWgU42EEW/oq4hxR0fx7+LzQ7eHd9XP7mAHk13tIHVuw45zq3XqxZ/djV/l/RqPhNAb25zquW39ZSP3vwNPK+eMkJlQ5heZC2KYuhvienhA0CCY4UIrUmG/3p/II5ZTIYHk3kiEnjH0R1H1I04+tIC+Z0njv
*/