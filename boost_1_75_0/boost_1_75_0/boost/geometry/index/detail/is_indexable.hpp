// Boost.Geometry Index
//
// Copyright (c) 2011-2015 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_IS_INDEXABLE_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_IS_INDEXABLE_HPP

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

namespace boost { namespace geometry { namespace index { namespace detail {

template
<
    typename Geometry,
    typename Tag = typename geometry::tag<Geometry>::type
>
struct is_indexable
{
    static const bool value = false;
};

template <typename Point>
struct is_indexable<Point, geometry::point_tag>
{
    static const bool value = true;
};

template <typename Box>
struct is_indexable<Box, geometry::box_tag>
{
    static const bool value = true;
};

template <typename Segment>
struct is_indexable<Segment, geometry::segment_tag>
{
    static const bool value = true;
};

}}}} // namespave boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_IS_INDEXABLE_HPP

/* is_indexable.hpp
RfUld1ziCggyBJaGQh9lmoyYOF+3HOtJfFnSa1J333SlwDK50MPk3xc48aPvqE0gHMYNrsbyLtt8/t2CA7ZXrH05jdPrc1ZbWigncVCafVjWgU+aMKt34PEK4zS+UZHaoqgm30ezsFZK19GVM6vDN0Xie/7bPY9R4z7V1xqzDYqoznqDFUJGJILBMcGqHdaL1q1WgeNul7Eah4z92C7Dw4pLziIzHSAA1Kbb94OTuHtj36zExf6GSMCzsxeBKQWoazv+4onMKs08IhWoL+p9RMET4a+rzOKW083uC0KHGuuRh2rzhp3j763ZRRJtPEXj6mOhEUNcN2WW578ZS0hbbYamYTwCeWioll45GRy0GUNPz+5yIA6cflg8Pxqz/12XHFiiFjGpdXWCCWM/AGvFGDOgE+ciZGkUtlfkXy1MJLhN3PZ9sdSR881q0EJw5utfOp3ZEh+RY2yi7+bZghTbv2qEVFlZiF6jkQu8U0Cn7anTv+Z+FEUIA193U/2sxOA+pQ4ZGgCPd4yro7TnweLR6qkj4mQLZGYUGDBP0T/UDRkVVr8uLwJYuFa0a9zoM3NpiX25+HAnwA26xLHmLZjbPrDpuTWN3RHvAof+hTNK9b5QXmb3rfojz3Kak0OFxJYgBgdsDHsZyZqJoteojdlBRN/Znm8kPN8/lf5xrR5yGb8sX0kjH+W1R0m8oOwRclMlsHo0I+hKUnUqyl4c
*/