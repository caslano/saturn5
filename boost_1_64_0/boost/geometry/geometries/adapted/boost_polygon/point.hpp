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
sROjCzQ1MmSqej5CURmAi/KsXyA7yqNG6WcmBZMc5DQ21HG5OiF+916S6oglaAYBDB7649kYAF6d6vy/uqTecjhKjAzCVRP0SxNWOjLapTa5uS0Mm4Ic7G4Q1fsnKkDF0HwJiGzTvDY8n2aKpBKqgmOP2moRTY1QhgldvEXGu1q4rTUJyR145SClHZJLaMfmwHhVBih8YTm4q0EWkENMaFfessTtIJ2wnsizGyt0TPxZzRFMGo30abv5owVkF16UVwLCf94QHDJUiV2vXpdsqamyWzW/Ign/W4wq+2KfXVzP3v+odyWAZcW9LSz+5EH61x1a4ZeCDoHMPRdtFNBF2Ph/OPvSycy9K6Yxv1dZYYBM0TBoIjgFTVE2HyGhQRViJJqVaPNTeCmtfNPIBIY2vz2M8rtyDnHUSa1xk7O0R4TMVOnijyxY1XMJf6hdNUgwhxvT/x7al6AF8u433yA09GaZgXWX3RtG1SINed3yUmEEdQ4B8J+v/EWJsROkc9QHNYR7zdGZHFUPVMKtFWTcNQ/upnU7zZ6bI8neQci3+QoIx030WpmlSutfeQ==
*/