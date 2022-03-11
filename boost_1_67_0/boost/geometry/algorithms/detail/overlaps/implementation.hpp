// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014, 2015, 2017.
// Modifications copyright (c) 2014-2017 Oracle and/or its affiliates.

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

#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/algorithms/relate.hpp>
#include <boost/geometry/algorithms/detail/overlaps/interface.hpp>


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