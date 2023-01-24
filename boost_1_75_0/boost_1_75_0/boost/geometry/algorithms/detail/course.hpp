// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_COURSE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_COURSE_HPP

#include <boost/geometry/algorithms/detail/azimuth.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

/// Calculate course (bearing) between two points.
///
/// NOTE: left for convenience and temporary backward compatibility
template <typename ReturnType, typename Point1, typename Point2>
inline ReturnType course(Point1 const& p1, Point2 const& p2)
{
    return azimuth<ReturnType>(p1, p2);
}

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_COURSE_HPP

/* course.hpp
6Itwd3ty8RnbnnwnZH58hvfVuDOd9KEUS3UDmkf1od3sZSvOCN3UeiB2QnrmTNLWwo6ttMdW9LMw6NZn6VMxuYmlhRp+h2o9gfu1xpbzjHj1jKk/B0I7G0I5Z22xV6ydkvsfeM4622Vouv8cqZXmyLOBoXLDRjhHmLYEiEfMuxS2B9VnbXqwuZB58Czfi+7tVPwIYuwjy6XZcikUTmEwadH/HAer9aywIzoDxKeQer7SKeaS3dxbiAufY7Yr3Nb35lnnbvux4qMQo3HlIuyL2g9cSpVaJFWScuqFoOiSXQaQeIXKv+AyBZKivj8jDVUXIrrzsY0wSC/5cMErFcfeVwe3V1NZg8nbpJAdb3zFdt59DDK/eYWfd/e+0um8Kylv4kEYtnE0j1SnlOG/+4ptTfkYMj3a+Dj94hXnOH3AJTfhCRiGUQ3ndW8R/67NjH8HxD5IVyHlcPxRgcsnPI5EiPQTycC5DKwT7+YrTmKUiz/ToIhVx3KFFZ7R4swZcn2azm+9R5LgFHQSXugOBNvotwTDb9M/Pbhp+lf9kieClgFA3xwgch3P+LPRF6FJsFG+JU0D/u49tUabhxep/V3K5/oEl3HaswoXer/EXm+5p8xb5Lsb+0cGyoJfBmb5x2F5LUMJDMi6Auu3ukFZSiOheXRvESQeelgPsv2cYoHssLBAql+Fs1ctXP4TUofAmA1h8gw5gjvfu8q8dwO9
*/