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
knSAHMQ5kohx3xt4VuBb1/JYVpFfCpvtIUCU/JLq9Dj7xo14q+GcXgoHs1JUBpXyAC8YyUCeeA7ypAUQ815ozaiTxdms/pfCd3QJEB/T+m1hMVj5aOKsps29R+wzHCncRPgTxhcCZNw6L9UJlB7uui+OUzZzAM7qtV4G9iic88UvbexRB7TCY32LV5FS6V25RMlVC5Xl+iIj113qmeJNx75Z/qLAyOCscEXO3enhRYH7vHdiuYKMRSWSj4tx/XpOkZB1aDSOBOuP6i2CD6b6srmQeXAL79N7t1iSUAp03J+oZbiCRmHMQ6WkyGGPY9P3tGwRctxjQJyF9NkWCzeOz8vK2Q2ESPIl+AcwJO9vSU7GH+hJQUXdfKCHEb0KuPhiablcJc2mrjFSF1lNcKtNPzcYMv+yVdj/bLUGEPXeWY2h/iVkHat+AM5Z6XDGcMNZy0Cyef7dap5/gVgDaedWprOxYi/yict9nzZYL2h6EWr7cE91HMYbJD9UNiiHemDgWVQ0oL4PGlBjwLqRiQas9XZ42t1tRivng97aKuzXrwBBtlF7FDvTZhmAijNN3gY8hjFHiwWT1CyXKifS5XeUeXI9886ZLBsUWQ3psCRMUbLv6InC9ZtQuGYDCqc1WWdssV5NgVfOp+vVTCAa2fu5eoqfRRYQknQ5ZsxT4E1YzeNkeDrw5WOUuFwgxUgOTKkKGd4I391dbIyT22yx
*/