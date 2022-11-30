// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_NORMALIZE_HPP
#define BOOST_GEOMETRY_STRATEGIES_NORMALIZE_HPP

#include <cstddef>
#include <type_traits>

#include <boost/numeric/conversion/cast.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/normalize_spheroidal_coordinates.hpp>
#include <boost/geometry/util/normalize_spheroidal_box_coordinates.hpp>

#include <boost/geometry/views/detail/indexed_point_view.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace normalize
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

struct do_nothing
{
    template <typename GeometryIn, typename GeometryOut>
    static inline void apply(GeometryIn const&, GeometryOut&)
    {
    }
};


template <std::size_t Dimension, std::size_t DimensionCount>
struct assign_loop
{
    template <typename CoordinateType, typename PointIn, typename PointOut>
    static inline void apply(CoordinateType const& longitude,
                             CoordinateType const& latitude,
                             PointIn const& point_in,
                             PointOut& point_out)
    {
        geometry::set<Dimension>(point_out, boost::numeric_cast
            <
                typename coordinate_type<PointOut>::type
            >(geometry::get<Dimension>(point_in)));

        assign_loop
            <
                Dimension + 1, DimensionCount
            >::apply(longitude, latitude, point_in, point_out);
    }
};

template <std::size_t DimensionCount>
struct assign_loop<DimensionCount, DimensionCount>
{
    template <typename CoordinateType, typename PointIn, typename PointOut>
    static inline void apply(CoordinateType const&,
                             CoordinateType const&,
                             PointIn const&,
                             PointOut&)
    {
    }
};

template <std::size_t DimensionCount>
struct assign_loop<0, DimensionCount>
{
    template <typename CoordinateType, typename PointIn, typename PointOut>
    static inline void apply(CoordinateType const& longitude,
                             CoordinateType const& latitude,
                             PointIn const& point_in,
                             PointOut& point_out)
    {
        geometry::set<0>(point_out, boost::numeric_cast
            <
                typename coordinate_type<PointOut>::type
            >(longitude));

        assign_loop
            <
                1, DimensionCount
            >::apply(longitude, latitude, point_in, point_out);
    }
};

template <std::size_t DimensionCount>
struct assign_loop<1, DimensionCount>
{
    template <typename CoordinateType, typename PointIn, typename PointOut>
    static inline void apply(CoordinateType const& longitude,
                             CoordinateType const& latitude,
                             PointIn const& point_in,
                             PointOut& point_out)
    {
        geometry::set<1>(point_out, boost::numeric_cast
            <
                typename coordinate_type<PointOut>::type
            >(latitude));

        assign_loop
            <
                2, DimensionCount
            >::apply(longitude, latitude, point_in, point_out);
    }
};


template <typename PointIn, typename PointOut, bool IsEquatorial = true>
struct normalize_point
{
    static inline void apply(PointIn const& point_in, PointOut& point_out)
    {
        typedef typename coordinate_type<PointIn>::type in_coordinate_type;

        in_coordinate_type longitude = geometry::get<0>(point_in);
        in_coordinate_type latitude = geometry::get<1>(point_in);

        math::normalize_spheroidal_coordinates
            <
                typename geometry::detail::cs_angular_units<PointIn>::type,
                IsEquatorial,
                in_coordinate_type
            >(longitude, latitude);

        assign_loop
            <
                0, dimension<PointIn>::value
            >::apply(longitude, latitude, point_in, point_out);
    }
};


template <typename BoxIn, typename BoxOut, bool IsEquatorial = true>
class normalize_box
{
    template <typename UnitsIn, typename UnitsOut, typename CoordinateInType>
    static inline void apply_to_coordinates(CoordinateInType& lon_min,
                                            CoordinateInType& lat_min,
                                            CoordinateInType& lon_max,
                                            CoordinateInType& lat_max,
                                            BoxIn const& box_in,
                                            BoxOut& box_out)
    {
        geometry::detail::indexed_point_view<BoxOut, min_corner> p_min_out(box_out);
        assign_loop
            <
                0, dimension<BoxIn>::value
            >::apply(lon_min,
                     lat_min,
                     geometry::detail::indexed_point_view
                         <
                             BoxIn const, min_corner
                         >(box_in),
                     p_min_out);

        geometry::detail::indexed_point_view<BoxOut, max_corner> p_max_out(box_out);
        assign_loop
            <
                0, dimension<BoxIn>::value
            >::apply(lon_max,
                     lat_max,
                     geometry::detail::indexed_point_view
                         <
                             BoxIn const, max_corner
                         >(box_in),
                     p_max_out);
    }

public:
    static inline void apply(BoxIn const& box_in, BoxOut& box_out)
    {
        typedef typename coordinate_type<BoxIn>::type in_coordinate_type;

        in_coordinate_type lon_min = geometry::get<min_corner, 0>(box_in);
        in_coordinate_type lat_min = geometry::get<min_corner, 1>(box_in);
        in_coordinate_type lon_max = geometry::get<max_corner, 0>(box_in);
        in_coordinate_type lat_max = geometry::get<max_corner, 1>(box_in);

        math::normalize_spheroidal_box_coordinates
            <
                typename geometry::detail::cs_angular_units<BoxIn>::type,
                IsEquatorial,
                in_coordinate_type
            >(lon_min, lat_min, lon_max, lat_max);

        apply_to_coordinates
            <
                typename geometry::detail::cs_angular_units<BoxIn>::type,
                typename geometry::detail::cs_angular_units<BoxOut>::type
            >(lon_min, lat_min, lon_max, lat_max, box_in, box_out);
    }
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL

struct cartesian_point
    : detail::do_nothing
{};

struct cartesian_box
    : detail::do_nothing
{};

struct spherical_point
{
    template <typename PointIn, typename PointOut>
    static inline void apply(PointIn const& point_in, PointOut& point_out)
    {
        detail::normalize_point
            <
                PointIn, PointOut,
                (! std::is_same
                    <
                        typename cs_tag<PointIn>::type,
                        spherical_polar_tag
                    >::value)
            >::apply(point_in, point_out);
    }
};

struct spherical_box
{
    template <typename BoxIn, typename BoxOut>
    static inline void apply(BoxIn const& box_in, BoxOut& box_out)
    {
        detail::normalize_box
            <
                BoxIn, BoxOut,
                (! std::is_same
                    <
                        typename cs_tag<BoxIn>::type,
                        spherical_polar_tag
                    >::value)
            >::apply(box_in, box_out);
    }
};

}} // namespace strategy::normalize

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_NORMALIZE_HPP

/* normalize.hpp
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
*/