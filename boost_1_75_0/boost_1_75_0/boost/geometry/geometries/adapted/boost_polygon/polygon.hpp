// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_POLYGON_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_POLYGON_HPP

// Adapts Geometries from Boost.Polygon for usage in Boost.Geometry
// boost::polygon::polygon_with_holes_data -> boost::geometry::polygon

#include <boost/polygon/polygon.hpp>

#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>

#include <boost/geometry/geometries/adapted/boost_polygon/ring_proxy.hpp>
#include <boost/geometry/geometries/adapted/boost_polygon/hole_iterator.hpp>
#include <boost/geometry/geometries/adapted/boost_polygon/holes_proxy.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{

template <typename CoordinateType>
struct tag<boost::polygon::polygon_with_holes_data<CoordinateType> >
{
    typedef polygon_tag type;
};

template <typename CoordinateType>
struct ring_const_type<boost::polygon::polygon_with_holes_data<CoordinateType> >
{
    typedef adapt::bp::ring_proxy<boost::polygon::polygon_with_holes_data<CoordinateType> const> type;
};

template <typename CoordinateType>
struct ring_mutable_type<boost::polygon::polygon_with_holes_data<CoordinateType> >
{
    typedef adapt::bp::ring_proxy<boost::polygon::polygon_with_holes_data<CoordinateType> > type;
};

template <typename CoordinateType>
struct interior_const_type<boost::polygon::polygon_with_holes_data<CoordinateType> >
{
    typedef adapt::bp::holes_proxy<boost::polygon::polygon_with_holes_data<CoordinateType> const> type;
};

template <typename CoordinateType>
struct interior_mutable_type<boost::polygon::polygon_with_holes_data<CoordinateType> >
{
    typedef adapt::bp::holes_proxy<boost::polygon::polygon_with_holes_data<CoordinateType> > type;
};


template <typename CoordinateType>
struct exterior_ring<boost::polygon::polygon_with_holes_data<CoordinateType> >
{
    typedef boost::polygon::polygon_with_holes_data<CoordinateType> polygon_type;
    typedef adapt::bp::ring_proxy<polygon_type> proxy;
    typedef adapt::bp::ring_proxy<polygon_type const> const_proxy;

    static inline proxy get(polygon_type& p)
    {
        return proxy(p);
    }

    static inline const_proxy get(polygon_type const& p)
    {
        return const_proxy(p);
    }
};

template <typename CoordinateType>
struct interior_rings<boost::polygon::polygon_with_holes_data<CoordinateType> >
{
    typedef boost::polygon::polygon_with_holes_data<CoordinateType> polygon_type;
    typedef adapt::bp::holes_proxy<polygon_type> proxy;
    typedef adapt::bp::holes_proxy<polygon_type const> const_proxy;

    static inline proxy get(polygon_type& p)
    {
        return proxy(p);
    }

    static inline const_proxy get(polygon_type const& p)
    {
        return const_proxy(p);
    }
};



} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_POLYGON_HPP


/* polygon.hpp
nJEkxVAbGbwHl6P9frhUqzcqMOiRBVgv+OqP1faV3wP6lRVYN/nTDY725SygV2Je8X3/MtHZQBJPIzfCnpvw3YM3inN3bC7C/il0aOwDhWw+Np6eZNFYmeED7l6O+PP1dUnO63A68qVlGx3FVFX8rCxyP+y+GX7z/s/JdVs6w8Np/gXQjeEbmX7hvgfnn422uvVgW5gN5AdCHHfCD1znR9sCoxauYCZwb/sJ42tEZAc45KKbbHz4EuOzcOd5zOXR70tLGuMM9vLh2xFvfdurtXqgwoHumw874eyTFq0laCL3xNFa1N+ej/PnApvUbUScPnYb/Kw//Wh9R6uJ3BsraqE3do7J9ZLwoOgYMsoFnvYbUO5XLOtU4j9l86DzHng2SfjHRM7A3lsgd+V5xz4Wa4UNPJd8+PayTzPDd4May949C/79MziXH0OewUu3YgwFPsHHUJJ1Y/DMW4Yyvv7r7cNCYQJXdQPa77fpDRGxhxy5CUcxF/iPP+iWtY3Tz9aiTNnfbRzqo1ML4rnxGyH/IygSN86BQ57VPGPzH8lW1PjH/NDtud9j7bNpSFDiyIHYXoO1iSefa+GLQMKHOYTciHWsPf03/DYR2IKFkPqurg6Or4HNYjz0e8Tu8LvgNvx+88sjfeL3UW7PHzkW3NoRYqNkBPsxgfdhzi8I3j8QGgizDsR6fWwYq6agjSNWVPCbMk5rDEkSf27jMu4H
*/