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
+ivdzmQ769XmyxTXcSjgJ8MZwo14sP2DGUDWa984Slc8EmkgB/wnD6aaaGvZaqfeBlMAUrW29dLIje6MKqTIZFaYnbe4tPIc40aFgN6M5rTMjdi/+qoJZtX8rb0KeqZz/h6YDNVnmal3wBSlmBTHsh6xiuuMItBtPjJLT7kp4ku7OjG+7ImtCsI+4sqS9lCKtn75vgpTRelnf1ydukE3kIny0Z7WJ6B+QdO6PyVoCqWd4Pi+fm0DSU8y25s38yAc0VR2pDvz2B6KBj8X8me6w45GkkhBKHw0nxuRkHVGn5hoxID37Tb7IabSFiPMOSFqFHYizZlRr7ZNdGu/S0q7Zf+ZCS2KT+egKvwY4tyOmJ/MGdqZ6hwRCpgd4EjNg+kky3TZyxlMiMtnphLkKOE3wdovQUh9FVhTm7MkUH4SVdDTWcq0Pzg2ymQs3I2SjTykHXAf8z/jGUOb9vdpQ/TUXf8IKLXo4QTrTYg6ga4RgmgiPX8Ju2WG0VeUI4WNEyCKGqAjkjDNKSOfmrI59OYX+dtUcPyPwXf0BZPFCzhLdwuyhDmnXa+e+X+2HQ==
*/