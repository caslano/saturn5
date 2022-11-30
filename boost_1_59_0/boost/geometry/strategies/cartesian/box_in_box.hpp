// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2015 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2015-2020.
// Modifications copyright (c) 2016-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BOX_IN_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BOX_IN_BOX_HPP


#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
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


struct box_within_coord
{
    template <typename BoxContainedValue, typename BoxContainingValue>
    static inline bool apply(BoxContainedValue const& bed_min,
                             BoxContainedValue const& bed_max,
                             BoxContainingValue const& bing_min,
                             BoxContainingValue const& bing_max)
    {
        return bing_min <= bed_min && bed_max <= bing_max // contained in containing
            && bed_min < bed_max;                         // interiors overlap
    }
};


struct box_covered_by_coord
{
    template <typename BoxContainedValue, typename BoxContainingValue>
    static inline bool apply(BoxContainedValue const& bed_min,
                             BoxContainedValue const& bed_max,
                             BoxContainingValue const& bing_min,
                             BoxContainingValue const& bing_max)
    {
        return bed_min >= bing_min && bed_max <= bing_max;
    }
};


struct box_within_longitude_diff
{
    template <typename CalcT>
    static inline bool apply(CalcT const& diff_ed)
    {
        return diff_ed > CalcT(0);
    }
};

struct box_covered_by_longitude_diff
{
    template <typename CalcT>
    static inline bool apply(CalcT const&)
    {
        return true;
    }
};

template <typename Geometry,
          typename CoordCheck,
          typename InteriorCheck>
struct box_longitude_range
{
    template <typename BoxContainedValue, typename BoxContainingValue>
    static inline bool apply(BoxContainedValue const& bed_min,
                             BoxContainedValue const& bed_max,
                             BoxContainingValue const& bing_min,
                             BoxContainingValue const& bing_max)
    {
        typedef typename select_most_precise
            <
                BoxContainedValue,
                BoxContainingValue
            >::type calc_t;
        typedef typename geometry::detail::cs_angular_units<Geometry>::type units_t;
        typedef math::detail::constants_on_spheroid<calc_t, units_t> constants;

        if (CoordCheck::apply(bed_min, bed_max, bing_min, bing_max))
        {
            return true;
        }

        // min <= max <=> diff >= 0
        calc_t const diff_ed = bed_max - bed_min;
        calc_t const diff_ing = bing_max - bing_min;
        
        // if containing covers the whole globe it contains all
        if (diff_ing >= constants::period())
        {
            return true;
        }

        // if containing is smaller it cannot contain
        // and check interior (within vs covered_by)
        if (diff_ing < diff_ed || ! InteriorCheck::apply(diff_ed))
        {
            return false;
        }

        // calculate positive longitude translation with bing_min as origin
        calc_t const diff_min = math::longitude_distance_unsigned<units_t>(bing_min, bed_min);

        // max of contained translated into the containing origin must be lesser than max of containing
        return bing_min + diff_min + diff_ed <= bing_max
            /*|| bing_max - diff_min - diff_ed >= bing_min*/;
    }
};


template
<
    template <typename, std::size_t, typename> class SubStrategy,
    typename CSTag,
    std::size_t Dimension,
    std::size_t DimensionCount
>
struct relate_box_box_loop
{
    template <typename Box1, typename Box2>
    static inline bool apply(Box1 const& b_contained, Box2 const& b_containing)
    {
        assert_dimension_equal<Box1, Box2>();
        
        if (! SubStrategy<Box1, Dimension, CSTag>::apply(
                    get<min_corner, Dimension>(b_contained),
                    get<max_corner, Dimension>(b_contained),
                    get<min_corner, Dimension>(b_containing),
                    get<max_corner, Dimension>(b_containing)
                )
            )
        {
            return false;
        }

        return within::detail::relate_box_box_loop
            <
                SubStrategy, CSTag,
                Dimension + 1, DimensionCount
            >::apply(b_contained, b_containing);
    }
};

template
<
    template <typename, std::size_t, typename> class SubStrategy,
    typename CSTag,
    std::size_t DimensionCount
>
struct relate_box_box_loop<SubStrategy, CSTag, DimensionCount, DimensionCount>
{
    template <typename Box1, typename Box2>
    static inline bool apply(Box1 const& , Box2 const& )
    {
        return true;
    }
};


template <typename Geometry, std::size_t Dimension, typename CSTag>
struct box_within_range
    : within::detail::box_within_coord
{};


template <typename Geometry, std::size_t Dimension, typename CSTag>
struct box_covered_by_range
    : within::detail::box_covered_by_coord
{};


// spherical_equatorial_tag, spherical_polar_tag and geographic_cat are casted to spherical_tag
template <typename Geometry>
struct box_within_range<Geometry, 0, spherical_tag>
    : within::detail::box_longitude_range
        <
            Geometry,
            within::detail::box_within_coord,
            within::detail::box_within_longitude_diff
        >
{};


template <typename Geometry>
struct box_covered_by_range<Geometry, 0, spherical_tag>
    : within::detail::box_longitude_range
        <
            Geometry,
            within::detail::box_covered_by_coord,
            within::detail::box_covered_by_longitude_diff
        >
{};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


struct cartesian_box_box
{
    template <typename Box1, typename Box2>
    static inline bool apply(Box1 const& box1, Box2 const& box2)
    {
        return within::detail::relate_box_box_loop
            <
                within::detail::box_within_range,
                cartesian_tag,
                0, dimension<Box1>::type::value
            >::apply(box1, box2);
    }
};

struct spherical_box_box
{
    template <typename Box1, typename Box2>
    static inline bool apply(Box1 const& box1, Box2 const& box2)
    {
        return within::detail::relate_box_box_loop
            <
                within::detail::box_within_range,
                spherical_tag,
                0, dimension<Box1>::type::value
            >::apply(box1, box2);
    }
};


} // namespace within


namespace covered_by
{


struct cartesian_box_box
{
    template <typename Box1, typename Box2>
    static inline bool apply(Box1 const& box1, Box2 const& box2)
    {
        return within::detail::relate_box_box_loop
            <
                within::detail::box_covered_by_range,
                cartesian_tag,
                0, dimension<Box1>::type::value
            >::apply(box1, box2);
    }
};

struct spherical_box_box
{
    template <typename Box1, typename Box2>
    static inline bool apply(Box1 const& box1, Box2 const& box2)
    {
        return within::detail::relate_box_box_loop
            <
                within::detail::box_covered_by_range,
                spherical_tag,
                0, dimension<Box1>::type::value
            >::apply(box1, box2);
    }
};


}


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


namespace within { namespace services
{

template <typename BoxContained, typename BoxContaining>
struct default_strategy
    <
        BoxContained, BoxContaining,
        box_tag, box_tag,
        areal_tag, areal_tag,
        cartesian_tag, cartesian_tag
    >
{
    typedef cartesian_box_box type;
};

// spherical_equatorial_tag, spherical_polar_tag and geographic_cat are casted to spherical_tag
template <typename BoxContained, typename BoxContaining>
struct default_strategy
    <
        BoxContained, BoxContaining,
        box_tag, box_tag,
        areal_tag, areal_tag,
        spherical_tag, spherical_tag
    >
{
    typedef spherical_box_box type;
};


}} // namespace within::services

namespace covered_by { namespace services
{

template <typename BoxContained, typename BoxContaining>
struct default_strategy
    <
        BoxContained, BoxContaining,
        box_tag, box_tag,
        areal_tag, areal_tag,
        cartesian_tag, cartesian_tag
    >
{
    typedef cartesian_box_box type;
};

// spherical_equatorial_tag, spherical_polar_tag and geographic_cat are casted to spherical_tag
template <typename BoxContained, typename BoxContaining>
struct default_strategy
    <
        BoxContained, BoxContaining,
        box_tag, box_tag,
        areal_tag, areal_tag,
        spherical_tag, spherical_tag
    >
{
    typedef spherical_box_box type;
};


}} // namespace covered_by::services


#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}}} // namespace boost::geometry::strategy

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BOX_IN_BOX_HPP

/* box_in_box.hpp
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
*/