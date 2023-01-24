// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_STRIDED_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_STRIDED_HPP


#include <boost/range/adaptor/strided.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{

namespace traits
{

template<typename Geometry>
struct tag<boost::strided_range<Geometry> >
{
    typedef typename geometry::tag<Geometry>::type type;
};

}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_STRIDED_HPP


/* strided.hpp
o1wHLBLm4bZ0rQcNatwoV2kvnjV1FtBcVVFJZwi/r7xT4VHbMsowjBvlLiyEPkeK6hTkNEOKz54FH+8L8kjHOK8RMhKuco71ZJMtspv/2qvT/QuPaG1NKyLtthSwxH6wPtkP8xZQH4pYtcokSARvOSoUM5mIeYK1iqjQ5MGztXYuax6ZBtwbBJRNir0HFRZ2Uq2+oDuq1bQRHzypPmerrRtoCsH9LokDWi/ClcJ60AzMPAAxmaMtlt2oK4N8gEbXraANj20s0KNhNCg1KVz2Y8tP+FVaWHI75VOynq6QeVHevNcCoUtf3q0h8agMO7JYBuE8qr0/x3uC/jyKIi5rj7LWmX+XdkjEbr5qKBuNghFK0eGIjvR/LpJUqIwFbxLEKQvgiW/6p7aHx+kdNOjLlV5aCu4ladEzSoeKiw7cGwj2iTFV08Uq8Kceor7SXE/Lee1Zdpp7gJ4UvIyCiwJVJD2VVHu+KT1wWrDSzSw+Y/nVl33OdmGqO0S8zfIHBeLCF5sqsom2k/vW+lYRLL0IkmsrjAO6CfivE+COvT0wdgmarnbSV5FiJ18uUXT7zfBb2LHhM7Q88ih4WFsCBZOeivPFi9pHMOP6fRyg31iwnEzbKnIuqD7zvC8M/usWAfcvd1ALHP0avw6V73+2cuxyHEgWlhFd6MklDvaQ/Bh8V4vYyklwJQXCWmJ46ZJcGuUa8KBhOSATvPzWSa7i
*/