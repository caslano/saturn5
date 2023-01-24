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
4+hHHSFmlSBeqvBAxrFlqLfdm3i/EEy8ABjPrSvQ9p0PO8cmnjtaAT353m+Kca1z4Nm9K/Hs9La28JaYiFYKIx2xrf4boAN/ERJnPsQBOLhkoI35QFt4i0Kz4h8Ffuis2u9zhClkNftRB0s+rstKDMeJfngl6rDySYXOT35hPyGfB2aiu/707RELS3p6MWyatnsiXUN8owVkHVyIb3r7O9SyQXkilnclDbRPvlSP0JkmcnmdZe0wy//IO3S/S3qJNjN4a5ehvH/8uniH5BEeK+gnloC+8gmdLmoE9OKFqI/RZQ461/EoZ/rNoD8edr9dxHeDS6Fz1xpqPBJ45PPNZZOsGk7l8d9l4H/dt8QuJNF3ga+agfowB/je382hmNzrixwAxk1YW47Odp2PoEUO5A04fRN8yJ3f5nXGl40EETnNTlVjr83PEX9VSZrfBb4V8xALvucY9iUyGqvEwWAgFpTLVZwnuAJrwRcftnliCckAes1kyBiYRHTZSzQZrXPA81w/8bDhFo73h/T3XFmE+Pvyr0keHtIkDtAbbwV9Zw3RhR5R6Bdvwd6t19UR3druqZaVz9G+n+wkHrFTijbdgz5+C97x9TcSvT44EJaHFUzkYjh2E2IRe37grHO5dg6egltgozzyjKDHTeSMi/rg/z5baLWHPCyAPZeMPoa9RL6p9zB6ME4vBH4v+pqvfD7H89KYJnLNnZqD+GvT
*/