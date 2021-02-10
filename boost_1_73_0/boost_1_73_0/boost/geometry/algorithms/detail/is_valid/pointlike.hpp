// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2017, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_POINTLIKE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_POINTLIKE_HPP

#include <boost/core/ignore_unused.hpp>
#include <boost/range.hpp>

#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/validity_failure_type.hpp>
#include <boost/geometry/algorithms/detail/is_valid/has_invalid_coordinate.hpp>
#include <boost/geometry/algorithms/dispatch/is_valid.hpp>

#include <boost/geometry/util/condition.hpp>


namespace boost { namespace geometry
{



#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

// A point is always simple
template <typename Point>
struct is_valid<Point, point_tag>
{
    template <typename VisitPolicy, typename Strategy>
    static inline bool apply(Point const& point, VisitPolicy& visitor, Strategy const&)
    {
        boost::ignore_unused(visitor);
        return ! detail::is_valid::has_invalid_coordinate
            <
                Point
            >::apply(point, visitor);
    }
};



// A MultiPoint is simple if no two Points in the MultiPoint are equal
// (have identical coordinate values in X and Y)
//
// Reference: OGC 06-103r4 (6.1.5)
template <typename MultiPoint, bool AllowEmptyMultiGeometries>
struct is_valid<MultiPoint, multi_point_tag, AllowEmptyMultiGeometries>
{
    template <typename VisitPolicy, typename Strategy>
    static inline bool apply(MultiPoint const& multipoint,
                             VisitPolicy& visitor,
                             Strategy const&)
    {
        boost::ignore_unused(multipoint, visitor);

        if (BOOST_GEOMETRY_CONDITION(
                AllowEmptyMultiGeometries || !boost::empty(multipoint)))
        {
            // we allow empty multi-geometries, so an empty multipoint
            // is considered valid
            return ! detail::is_valid::has_invalid_coordinate
                <
                    MultiPoint
                >::apply(multipoint, visitor);
        }
        else
        {
            // we do not allow an empty multipoint
            return visitor.template apply<failure_few_points>();
        }
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_POINTLIKE_HPP

/* pointlike.hpp
JB9kS0ROEmzn1Hu7zsid7eAzGXc/DMYbGMnI+SaiLZiDi06vdzWpoQmPuW4st3GbXo0vp3UcjDBMoA04tv3xt0mVfNXGJX/TiR0mkXJ3sY20HSZ5dVN4J0LBtQ5UQQiYTOAXWAFQRsi8usy4rkSCYpcSCeOsFmaLWISJV+WhDuZ8HsUP1QPcc/ksvVVhiQIc/tcPSUSUrjDaY100JVYTnif6LdZFTF30CyZgk6DTUIrbUNXYBLokqVjcndoKy3CwxCSAhkuxh1EIECYcSGY2/iDPhOSa/qjzdohBcPnxtAFg3EXCNUGyNnomkBy3hGdIdvhGMttjcxE8wPk5dC5U8pya8EeDOs5GTrYIT7F4SHYK57BZGA1iKq64Kr4FvZVyjs9Q7hmSQWIoCmLZhN6UetVIK3D0N7aNJXGt7plgGLPPR1/h7AxeUgOefT7+arYbCh311If7cHR/0TdJT3zBHokeeY/FG5vK9bAjyey6z8baTWQ6e4JFuG9fjwb/uO4Px93OUMsklyJxfGOpiV50j1YWw1hWfF4evd5KbjgYfSgRW+F0d+BMBtP+Os4RPjkOGYYUV/qf6OUXvfyql7/q5VQvf9PLS728+kpjy+pBQkf64DijeJyRPM5oHv/6tZ0hoImX8F1tIotnZN+j
*/