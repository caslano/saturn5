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