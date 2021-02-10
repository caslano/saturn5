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
AAAWAAkAY3VybC1tYXN0ZXIvbGliL21xdHQuY1VUBQABtkgkYNVb/VLbSBL/n6eY5SrEBgOGZOv2IHDngEN8CzZrm0vlCKUS1sjWRpYcSQ6wG17rXuBe7Lp7ZqQZfdg4ydbdOUVsS9M9Pd093b9ujXc3v99rjW2ypS+L/ix4wTtRXEbhr3yUlI+2rC9M/AOqD/C+bJJdlpF8sepsOckXViMSS87yCj9b1rKJPqBs+N8uUn6w8CNcATKkPAlnD5E3niSsdlJn+839JtvGt70GO7UDj/tskPDglkfjBnvl0JW/Tez7+52YHzcYT5jt75Tx2ftLg73+9d//igKdwe2vYRSk9FKE4cSLWRy6yZ0dcQaffW/Eg5g7zI6Zw+NR5N3CFy9gyYQz1/M5O+ldvu90zxrsbuKNJsjkIZyzeBLOfYdN7M+cRXzEvc+Cx8yOEha6QA7MHS9OgOE88cJgB+bmLOHRNEYeOL3txyGzP9ueb9/CRHbCJkkyiw92d0fzyAepd51wFO+O1HJ3JsmUNIAM3oMQU/uBhbOEJSGbx7zBcGSDTUPHc/Ed9AAXZ/Nb34snjUwamCpwdsOIxdz3kRfQeTwWYnM2kOpp4DA2A4m9BN/iMIhxqrtJODUGgh6RizuPApgI9ACDnBDU3GDz
*/