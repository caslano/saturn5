// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ASSIGN_INDEXED_POINT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ASSIGN_INDEXED_POINT_HPP


#include <cstddef>

#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/algorithms/detail/assign_values.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

/*!
\brief Assign a box or segment with the value of a point
\ingroup assign
\tparam Index indicates which box-corner, min_corner (0) or max_corner (1)
    or which point of segment (0/1)
\tparam Point \tparam_point
\tparam Geometry \tparam_box_or_segment
\param point \param_point
\param geometry \param_box_or_segment

\qbk{
[heading Example]
[assign_point_to_index] [assign_point_to_index_output]
}
*/
template <std::size_t Index, typename Geometry, typename Point>
inline void assign_point_to_index(Point const& point, Geometry& geometry)
{
    concepts::check<Point const>();
    concepts::check<Geometry>();

    detail::assign::assign_point_to_index
        <
            Geometry, Point, Index, 0, dimension<Geometry>::type::value
        >::apply(point, geometry);
}


/*!
\brief Assign a point with a point of a box or segment
\ingroup assign
\tparam Index indicates which box-corner, min_corner (0) or max_corner (1)
    or which point of segment (0/1)
\tparam Geometry \tparam_box_or_segment
\tparam Point \tparam_point
\param geometry \param_box_or_segment
\param point \param_point

\qbk{
[heading Example]
[assign_point_from_index] [assign_point_from_index_output]
}
*/
template <std::size_t Index, typename Point, typename Geometry>
inline void assign_point_from_index(Geometry const& geometry, Point& point)
{
    concepts::check<Geometry const>();
    concepts::check<Point>();

    detail::assign::assign_point_from_index
        <
            Geometry, Point, Index, 0, dimension<Geometry>::type::value
        >::apply(geometry, point);
}


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ASSIGN_INDEXED_POINT_HPP

/* assign_indexed_point.hpp
y1sn9FZZRLvny+fOKWdGuP65uxE4nLXpjYR8QaXa4zTB3rcU3rdZizz76/u9Qr7ZRZ4r9X181u83o29GnziXuZPXXxGEcfaA/bek02OY9eE+J+XBs/YyUe1ROqmC++EinfHeBoLLcXi5at+GFf927tM6XN0epgjfTzMFuQOeLs20wDksz7mbLMul4pHORmHvOK/Hdr1cxW2GXW+R7T/wJkaM+U4F/mmyngG/VvXhPwzcraLP2Crq7ZkRPD6i6upHweMs1W4TLvfLdbv9MdCcA5qno89xyXbPAh0Ma8j6rJWo4x+qcPfyJLCmfDqFY14uRTWE27MzbPs3kBjB/OjZtt0znp1owGOuhzd+RN1b6Nm7B2zyso4e4VHltlBH/3HTDpKc1oPjLp33kMLOFfWwucDeikWFxyzCtSgY+jPnK3/5CWVXF6AMPinL2OLRp8r4U8C9kHGp36b4XBTBZ7uqX58B7mdVH/ITsM3oeYydvEtB97nRdMCPprscdFdEyLZc5fHzwL1K2rGSDTRsx18EzZdG03C91zRXg+YaWZ9VOrI+Xwf8r+g0CtSvr4Hm66PTYP8t0/gm8K8H/pIx+6JBXdtGNJNFXfu0qXuiHl1s6p6sR6Cpdf0jOnDabYntXkhTBxnuARdnEBiTeAB3IeBUDxl3selfCZ6X2X4nwQS/ds91hSS/K00/BHDJb52Pm6YeF/1kGvAeVPE+7RcoLmXTNdUy0M+Xbb8TcC/A3Qo+jA0+19p+J8exzrf5+6kdNstziQ8Xur7K649H4V5HcI27nWDUiYzLfH7V9D0B9+X6hu1zGueGsyamn2nDZtDh1vKnmzvHhL97KPBfuiupwbjPd4xzNNILaij84HdUvbkBdZO+Uf2RG1EPvhtBw3NziuZm0HxP+lvQSH97K/C+L30R8KYoP3k7cO/QchSo8z8AzQ/9Ol+izy/L+hvdhk32zwV5cu98YqMByT5xqaj/N9n6HdjVLbZu9ydRGBbnNlOvI9rSuarNvNPW6Uw864YUvKEmA5o7bf1enzf+LlvX2Satjtq9nlRK7K3YlRR8t7DJNUWcrYtct95BWzZlc09gI/Q76Gfdq2znPtjOjzG2uR9l+xMxHppXXuhMUzrD9zTSTynDzyoK0fUHdP1huodAt2803SCTDYpzMRUF96D1ye04CDHtz0HbIe4MlWdXHqxAPhF+2Ib7OfyoC/MY6RcVLk3/noGdqPv8y4rizpt8t2D/NNOzMa77p+n4QDxNjjjOY8kTbLto31S3eA+YeoN9eHxOxtad8Fm92Y6/tnWstwdnEeQdgAs9U73dPZs7k73/Stj74iLOMd4rxuu/Uf7q8Qr3SX/1BOzzSeD+DPoiOzZlFsrzZJXn7XZfgj6zmIrH09ijzeNZ2lWWtpf+en4+Z2PM64fncl3nth57D7rXU2H0sq8j3MVBn2IgKdJplnCa6cmNZG1ffBdzN5rQY3vRfXFXp3+s1gh+D509DZ1hvYbmDeWcofPz27GWLtdrniU6zDdG0Oh+50TvOaTXgbJFerT2G6ZN5UnvRYyl70YbSCLbO1j3RHgvsZ5H6dPYNGItkcfOwbr5DL2WKHBOLYvGeUWMr0+KWLt9jeLlWsKfy6LWySZ4fwvwKK38eH+H7l6WZcVzG+7bG3MGb1W4/EvdvU0wufZJ0fKuVNAgHyLdf/lrfsCrzZvGTt47aq5jCqfB+CyvTGNcpefJciwjOslnHJdrwEeX68RKyClwpC6lnJMJV8lFOKPzvkuAh3kO952q1ljfU4kzDJVFndmxd2bgQsSuuiWt2HqVN5rbv93B3+hmD6xXP1XiyTkyXledEZHvcqJH/ec5Mnk/1m6or0SH+Hw=
*/