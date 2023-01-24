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
dGa1ZqiQMpGpjt7Xf9OHwfoPHWimZP0UhrP4nJQq78doOi4SPETr2ulIQIk7Na4lx3+/4m0yDTxVX+k2jSh3AEjgNoHLpLpQEvSnyHG2rq+4rNat4FnzFWmfzaMIP3sbNTuMmD2V8dyeiiPKnkqv8dvHSZ5pGD9EDqYxSgiYWDkb9HJG7JPQclQOlY0lOofVL8M+fAqlmF5kedXx92Sv/v4I5OraCmXZDGXZRO3IkHc9AuTJeQwmigNQ3m7IRPh/YZxjGmFCIxqILZOR3AbN0DNAkk43YrK0zmoHcsJ65Lyo89/J+xDHze3VNmSH/d3eF/2ezHtTqoJSG0ej1GorSoX9JHVDxH5OyKQSG1aw921QQmzs7R4y9oSvM1B6ArRpEnjGfk36kYw608gCAvrFT4WP8DxSju9Dv5h2xrWVWQafYZLGdeCZH0ljlUzT6BbrsbCGJOJMHYEsplqtDJGxtBY+6aPjHzybv9bmTI94K8bTURb+Tv2fr7k+ywvgef1rja/M1wNlI/Lho4IzAZDwOoGNgzkwDmoj41H4xpB3EgRgILYjre8fgL7fxerN6xr4xlDXq74h/EFhE1SOndtdhzyNlbCGzYI1rCJybtcC0apIHjeDZ+U3Whn5zFZMGHcJ5bDVrhBU7BzNbDdR/Pcbo/0v8t0S5IB06PharfVJ9ZA+IWNjPWZ6jqpptq4DBC0eeZc7EsZNI04NLMCp
*/