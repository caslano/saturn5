// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_POINT_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_POINT_HPP

// Adapts Geometries from Boost.Polygon for usage in Boost.Geometry
// boost::polygon::point_data -> boost::geometry::point


#include <boost/polygon/polygon.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{


template <typename CoordinateType>
struct tag<boost::polygon::point_data<CoordinateType> >
{
    typedef point_tag type;
};


template <typename CoordinateType>
struct coordinate_type<boost::polygon::point_data<CoordinateType> >
{
    typedef CoordinateType type;
};


template <typename CoordinateType>
struct coordinate_system<boost::polygon::point_data<CoordinateType> >
{
    typedef cs::cartesian type;
};


template <typename CoordinateType>
struct dimension<boost::polygon::point_data<CoordinateType> >
            : boost::mpl::int_<2>
{};


template <typename CoordinateType>
struct access<boost::polygon::point_data<CoordinateType>, 0>
{
    typedef boost::polygon::point_data<CoordinateType> point_type;

    static inline CoordinateType get(point_type const& p)
    {
        return p.x();
    }

    static inline void set(point_type& p, CoordinateType const& value)
    {
        p.x(value);
    }
};


template <typename CoordinateType>
struct access<boost::polygon::point_data<CoordinateType>, 1>
{
    typedef boost::polygon::point_data<CoordinateType> point_type;

    static inline CoordinateType get(point_type const& p)
    {
        return p.y();
    }

    static inline void set(point_type& p, CoordinateType const& value)
    {
        p.y(value);
    }
};


} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_POINT_HPP

/* point.hpp
h/+mUC7sZ7FCtbaRmJYiwXNPlkHizbx8W94btVEp02TAhOcNlzaRnqmhr0zsBSNV8qNmJWdmVslNq1LOU56SzMd2HiYVeMxDoxQLOzqkjc5cWj6MjstTchEtrVRmI+axkJwLkKlEpRKThyCgSPLPpIhWGoqzjzxlc4T7BeuVu/JlamDET//zwHmC2EI9QFZAggWD1BWWhdK36M4KGqBNduYHUAq+DE9fTZmfctNH6R2U6C8nvs5z3V08i8o01ZSVX7QDNVHN7TyMHYUy0DrHyUhyMlM2+IHzuL4iE/OQbJSpmMEEMjKXF3fqolqD/YamN0EiyOs5PFPbuMPmhxab6UMtPaDPSNlnPumtdd1xGlGGMGb7Y2YcUorSYERWHJoQd6iSAnAa9XU+vFOHXw0mMsMxs6QsC4Vzca3Jf+MFwIQimxyeyjKZDhLwfh26DYAF4AYZPg20/crxfg+i0nzxSiTfE7o8RUAk4ttIiFbbVs5/R3hRJ2LmJDV0Qk8oCvwUOD4b2emI5yMAeooyCZvFPswslF2I13gzUCYD8BQX7m6hFyru1ukTUpmBbuSBWnk0lAuqWhtpGiuskOaD0mw76F86ah7cH62uxwbq1yyKr3+Rt0eoUSGlaCrpUsPG0LnGBSqRkjr2Me1FXDm5
*/