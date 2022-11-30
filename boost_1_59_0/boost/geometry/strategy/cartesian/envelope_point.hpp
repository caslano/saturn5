// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015, 2016, 2017, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGY_CARTESIAN_ENVELOPE_POINT_HPP
#define BOOST_GEOMETRY_STRATEGY_CARTESIAN_ENVELOPE_POINT_HPP

#include <cstddef>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/views/detail/indexed_point_view.hpp>

#include <boost/geometry/algorithms/detail/convert_point_to_point.hpp>

#include <boost/geometry/strategy/envelope.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace envelope
{

template <std::size_t Dimension, std::size_t DimensionCount>
struct envelope_one_point
{
    template <std::size_t Index, typename Point, typename Box>
    static inline void apply(Point const& point, Box& mbr)
    {
        detail::indexed_point_view<Box, Index> box_corner(mbr);
        detail::conversion::point_to_point
            <
                Point,
                detail::indexed_point_view<Box, Index>,
                Dimension,
                DimensionCount
            >::apply(point, box_corner);
    }

    template <typename Point, typename Box>
    static inline void apply(Point const& point, Box& mbr)
    {
        apply<min_corner>(point, mbr);
        apply<max_corner>(point, mbr);
    }
};


}} // namespace detail::envelope
#endif // DOXYGEN_NO_DETAIL


namespace strategy { namespace envelope
{

struct cartesian_point
{
    template <typename Point, typename Box>
    static inline void apply(Point const& point, Box& mbr)
    {
        geometry::detail::envelope::envelope_one_point
            <
                0, dimension<Point>::value
            >::apply(point, mbr);
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<point_tag, cartesian_tag, CalculationType>
{
    typedef strategy::envelope::cartesian_point type;
};


}

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::envelope


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGY_CARTESIAN_ENVELOPE_POINT_HPP

/* envelope_point.hpp
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
*/