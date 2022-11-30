// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014-2021.
// Modifications copyright (c) 2014-2021 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAPS_IMPLEMENTATION_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAPS_IMPLEMENTATION_HPP


#include <cstddef>

#include <boost/geometry/core/access.hpp>

#include <boost/geometry/algorithms/detail/overlaps/interface.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>
#include <boost/geometry/algorithms/relate.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/strategies/relate/cartesian.hpp>
#include <boost/geometry/strategies/relate/geographic.hpp>
#include <boost/geometry/strategies/relate/spherical.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlaps
{

template
<
    std::size_t Dimension,
    std::size_t DimensionCount
>
struct box_box_loop
{
    template <typename Box1, typename Box2>
    static inline void apply(Box1 const& b1, Box2 const& b2,
            bool& overlaps, bool& one_in_two, bool& two_in_one)
    {
        assert_dimension_equal<Box1, Box2>();

        typedef typename coordinate_type<Box1>::type coordinate_type1;
        typedef typename coordinate_type<Box2>::type coordinate_type2;

        coordinate_type1 const& min1 = get<min_corner, Dimension>(b1);
        coordinate_type1 const& max1 = get<max_corner, Dimension>(b1);
        coordinate_type2 const& min2 = get<min_corner, Dimension>(b2);
        coordinate_type2 const& max2 = get<max_corner, Dimension>(b2);

        // We might use the (not yet accepted) Boost.Interval
        // submission in the future

        // If:
        // B1: |-------|
        // B2:           |------|
        // in any dimension -> no overlap
        if (max1 <= min2 || min1 >= max2)
        {
            overlaps = false;
            return;
        }

        // If:
        // B1: |--------------------|
        // B2:   |-------------|
        // in all dimensions -> within, then no overlap
        // B1: |--------------------|
        // B2: |-------------|
        // this is "within-touch" -> then no overlap. So use < and >
        if (min1 < min2 || max1 > max2)
        {
            one_in_two = false;
        }

        // Same other way round
        if (min2 < min1 || max2 > max1)
        {
            two_in_one = false;
        }

        box_box_loop
            <
                Dimension + 1,
                DimensionCount
            >::apply(b1, b2, overlaps, one_in_two, two_in_one);
    }
};

template
<
    std::size_t DimensionCount
>
struct box_box_loop<DimensionCount, DimensionCount>
{
    template <typename Box1, typename Box2>
    static inline void apply(Box1 const& , Box2 const&, bool&, bool&, bool&)
    {
    }
};

struct box_box
{
    template <typename Box1, typename Box2, typename Strategy>
    static inline bool apply(Box1 const& b1, Box2 const& b2, Strategy const& /*strategy*/)
    {
        bool overlaps = true;
        bool within1 = true;
        bool within2 = true;
        box_box_loop
            <
                0,
                dimension<Box1>::type::value
            >::apply(b1, b2, overlaps, within1, within2);

        /*
        \see http://docs.codehaus.org/display/GEOTDOC/02+Geometry+Relationships#02GeometryRelationships-Overlaps
        where is stated that "inside" is not an "overlap",
        this is true and is implemented as such.
        */
        return overlaps && ! within1 && ! within2;
    }
};

}} // namespace detail::overlaps
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename Box1, typename Box2>
struct overlaps<Box1, Box2, box_tag, box_tag>
    : detail::overlaps::box_box
{};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAPS_IMPLEMENTATION_HPP

/* implementation.hpp
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
*/