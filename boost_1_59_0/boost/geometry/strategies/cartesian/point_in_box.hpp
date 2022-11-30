// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015-2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_POINT_IN_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_POINT_IN_BOX_HPP


#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/strategies/covered_by.hpp>
#include <boost/geometry/strategies/within.hpp>
#include <boost/geometry/util/normalize_spheroidal_coordinates.hpp>


namespace boost { namespace geometry { namespace strategy
{

namespace within
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

struct within_coord
{
    template <typename Value1, typename Value2>
    static inline bool apply(Value1 const& value, Value2 const& min_value, Value2 const& max_value)
    {
        return value > min_value && value < max_value;
    }
};

struct covered_by_coord
{
    template <typename Value1, typename Value2>
    static inline bool apply(Value1 const& value, Value2 const& min_value, Value2 const& max_value)
    {
        return value >= min_value && value <= max_value;
    }
};

template <typename Geometry, std::size_t Dimension, typename CSTag>
struct within_range
    : within_coord
{};


template <typename Geometry, std::size_t Dimension, typename CSTag>
struct covered_by_range
    : covered_by_coord
{};


// NOTE: the result would be the same if instead of structs defined below
// the above xxx_range were used with the following arguments:
// (min_value + diff_min, min_value, max_value)
struct within_longitude_diff
{
    template <typename CalcT>
    static inline bool apply(CalcT const& diff_min, CalcT const& min_value, CalcT const& max_value)
    {
        CalcT const c0 = 0;
        return diff_min > c0
            && (min_value + diff_min < max_value
             /*|| max_value - diff_min > min_value*/);
    }
};

struct covered_by_longitude_diff
{
    template <typename CalcT>
    static inline bool apply(CalcT const& diff_min, CalcT const& min_value, CalcT const& max_value)
    {
        return min_value + diff_min <= max_value
            /*|| max_value - diff_min >= min_value*/;
    }
};


template <typename Geometry,
          typename CoordCheck,
          typename DiffCheck>
struct longitude_range
{
    template <typename Value1, typename Value2>
    static inline bool apply(Value1 const& value, Value2 const& min_value, Value2 const& max_value)
    {
        typedef typename select_most_precise
            <
                Value1, Value2
            >::type calc_t;
        typedef typename geometry::detail::cs_angular_units<Geometry>::type units_t;
        typedef math::detail::constants_on_spheroid<calc_t, units_t> constants;

        if (CoordCheck::apply(value, min_value, max_value))
        {
            return true;
        }

        // min <= max <=> diff >= 0
        calc_t const diff_ing = max_value - min_value;

        // if containing covers the whole globe it contains all
        if (diff_ing >= constants::period())
        {
            return true;
        }

        // calculate positive longitude translation with min_value as origin
        calc_t const diff_min = math::longitude_distance_unsigned<units_t, calc_t>(min_value, value);

        return DiffCheck::template apply<calc_t>(diff_min, min_value, max_value);
    }
};


// spherical_equatorial_tag, spherical_polar_tag and geographic_cat are casted to spherical_tag
template <typename Geometry>
struct within_range<Geometry, 0, spherical_tag>
    : longitude_range<Geometry, within_coord, within_longitude_diff>
{};


template <typename Geometry>
struct covered_by_range<Geometry, 0, spherical_tag>
    : longitude_range<Geometry, covered_by_coord, covered_by_longitude_diff>
{};


template
<
    template <typename, std::size_t, typename> class SubStrategy,
    typename CSTag, // cartesian_tag or spherical_tag
    std::size_t Dimension,
    std::size_t DimensionCount
>
struct relate_point_box_loop
{
    template <typename Point, typename Box>
    static inline bool apply(Point const& point, Box const& box)
    {
        if (! SubStrategy<Point, Dimension, CSTag>::apply(get<Dimension>(point),
                    get<min_corner, Dimension>(box),
                    get<max_corner, Dimension>(box))
            )
        {
            return false;
        }

        return relate_point_box_loop
            <
                SubStrategy,
                CSTag,
                Dimension + 1, DimensionCount
            >::apply(point, box);
    }
};


template
<
    template <typename, std::size_t, typename> class SubStrategy,
    typename CSTag,
    std::size_t DimensionCount
>
struct relate_point_box_loop<SubStrategy, CSTag, DimensionCount, DimensionCount>
{
    template <typename Point, typename Box>
    static inline bool apply(Point const& , Box const& )
    {
        return true;
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

struct cartesian_point_box
{
    template <typename Point, typename Box>
    static inline bool apply(Point const& point, Box const& box)
    {
        return detail::relate_point_box_loop
            <
                detail::within_range,
                cartesian_tag,
                0, dimension<Point>::value
            >::apply(point, box);
    }
};

struct spherical_point_box
{
    template <typename Point, typename Box>
    static inline bool apply(Point const& point, Box const& box)
    {
        return detail::relate_point_box_loop
            <
                detail::within_range,
                spherical_tag,
                0, dimension<Point>::value
            >::apply(point, box);
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template <typename Point, typename Box>
struct default_strategy
    <
        Point, Box,
        point_tag, box_tag,
        pointlike_tag, areal_tag,
        cartesian_tag, cartesian_tag
    >
{
    typedef within::cartesian_point_box type;
};

// spherical_equatorial_tag, spherical_polar_tag and geographic_cat are casted to spherical_tag
template <typename Point, typename Box>
struct default_strategy
    <
        Point, Box,
        point_tag, box_tag,
        pointlike_tag, areal_tag,
        spherical_tag, spherical_tag
    >
{
    typedef within::spherical_point_box type;
};


} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

} // namespace within

namespace covered_by
{

struct cartesian_point_box
{
    template <typename Point, typename Box>
    static inline bool apply(Point const& point, Box const& box)
    {
        return within::detail::relate_point_box_loop
            <
                within::detail::covered_by_range,
                cartesian_tag,
                0, dimension<Point>::value
            >::apply(point, box);
    }
};

struct spherical_point_box
{
    template <typename Point, typename Box>
    static inline bool apply(Point const& point, Box const& box)
    {
        return within::detail::relate_point_box_loop
            <
                within::detail::covered_by_range,
                spherical_tag,
                0, dimension<Point>::value
            >::apply(point, box);
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{


template <typename Point, typename Box>
struct default_strategy
    <
        Point, Box,
        point_tag, box_tag,
        pointlike_tag, areal_tag,
        cartesian_tag, cartesian_tag
    >
{
    typedef covered_by::cartesian_point_box type;
};

// spherical_equatorial_tag, spherical_polar_tag and geographic_cat are casted to spherical_tag
template <typename Point, typename Box>
struct default_strategy
    <
        Point, Box,
        point_tag, box_tag,
        pointlike_tag, areal_tag,
        spherical_tag, spherical_tag
    >
{
    typedef covered_by::spherical_point_box type;
};


} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


} // namespace covered_by


}}} // namespace boost::geometry::strategy


#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_POINT_IN_BOX_HPP

/* point_in_box.hpp
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
*/