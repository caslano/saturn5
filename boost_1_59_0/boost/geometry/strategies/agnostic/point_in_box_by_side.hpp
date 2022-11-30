// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2018-2020.
// Modifications copyright (c) 2018-2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_AGNOSTIC_POINT_IN_BOX_BY_SIDE_HPP
#define BOOST_GEOMETRY_STRATEGIES_AGNOSTIC_POINT_IN_BOX_BY_SIDE_HPP

#include <boost/array.hpp>
#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>

#include <boost/geometry/algorithms/assign.hpp>

#include <boost/geometry/strategies/side.hpp>

#include <boost/geometry/strategies/covered_by.hpp>
#include <boost/geometry/strategies/within.hpp>
#include <boost/geometry/strategies/geographic/side.hpp>
#include <boost/geometry/strategies/spherical/ssf.hpp>


namespace boost { namespace geometry { namespace strategy
{

namespace within
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

struct decide_within
{
    static inline bool apply(int side, bool& result)
    {
        if (side != 1)
        {
            result = false;
            return false;
        }
        return true; // continue
    }
};

struct decide_covered_by
{
    static inline bool apply(int side, bool& result)
    {
        if (side != 1)
        {
            result = side >= 0;
            return false;
        }
        return true; // continue
    }
};


// WARNING
// This strategy is not suitable for boxes in non-cartesian CSes having edges
// longer than 180deg because e.g. the SSF formula picks the side of the closer
// longitude, so for long edges the side is the opposite.
// Actually it is not suitable for shorter edges either because the edges of
// boxes are defined by meridians and parallels, not great circles or geodesics.
template <typename Decide, typename Point, typename Box, typename Strategy>
inline bool point_in_box_by_side(Point const& point, Box const& box,
                                 Strategy const& strategy)
{
    boost::ignore_unused(strategy);

    // Create (counterclockwise) array of points, the fifth one closes it
    // Every point should be on the LEFT side (=1), or ON the border (=0),
    // So >= 1 or >= 0
    boost::array<typename point_type<Box>::type, 5> bp;
    geometry::detail::assign_box_corners_oriented<true>(box, bp);
    bp[4] = bp[0];

    bool result = true;
    for (int i = 1; i < 5; i++)
    {
        int const side = strategy.apply(point, bp[i - 1], bp[i]);
        if (! Decide::apply(side, result))
        {
            return result;
        }
    }

    return result;
}


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


// There should probably be another category of geometry different than box,
// e.g. rectangle or convex_ring. This strategy should probably be an
// algorithm calling side strategy.

template <typename CalculationType = void>
struct cartesian_point_box_by_side
{
    template <typename Point, typename Box>
    static inline bool apply(Point const& point, Box const& box)
    {
        using side_strategy_type
            = typename strategy::side::services::default_strategy
                <cartesian_tag, CalculationType>::type;

        return within::detail::point_in_box_by_side
            <
                within::detail::decide_within
            >(point, box, side_strategy_type());
    }
};

template <typename CalculationType = void>
struct spherical_point_box_by_side
{
    template <typename Point, typename Box>
    static inline bool apply(Point const& point, Box const& box)
    {
        return within::detail::point_in_box_by_side
            <
                within::detail::decide_within
            >(point, box,
              strategy::side::spherical_side_formula<CalculationType>());
    }
};

template
<
    typename FormulaPolicy = strategy::andoyer,
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
struct geographic_point_box_by_side
{
    geographic_point_box_by_side() = default;

    explicit geographic_point_box_by_side(Spheroid const& spheroid)
        : m_side(spheroid)
    {}

    template <typename Point, typename Box>
    bool apply(Point const& point, Box const& box) const
    {
        return within::detail::point_in_box_by_side
            <
                within::detail::decide_within
            >(point, box, m_side);
    }

    Spheroid const& model() const
    {
        return m_side.model();
    }

private:
    strategy::side::geographic
        <
            FormulaPolicy, Spheroid, CalculationType
        > m_side;
};


} // namespace within


namespace covered_by
{


template <typename CalculationType = void>
struct cartesian_point_box_by_side
{
    template <typename Point, typename Box>
    static bool apply(Point const& point, Box const& box)
    {
        using side_strategy_type
            = typename strategy::side::services::default_strategy
                <cartesian_tag, CalculationType>::type;
        return within::detail::point_in_box_by_side
            <
                within::detail::decide_covered_by
            >(point, box, side_strategy_type());
    }
};

template <typename CalculationType = void>
struct spherical_point_box_by_side
{
    template <typename Point, typename Box>
    static bool apply(Point const& point, Box const& box)
    {
        return within::detail::point_in_box_by_side
            <
                within::detail::decide_covered_by
            >(point, box,
              strategy::side::spherical_side_formula<CalculationType>());
    }
};

template
<
    typename FormulaPolicy = strategy::andoyer,
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
struct geographic_point_box_by_side
{
    geographic_point_box_by_side() = default;

    explicit geographic_point_box_by_side(Spheroid const& spheroid)
        : m_side(spheroid)
    {}

    template <typename Point, typename Box>
    bool apply(Point const& point, Box const& box) const
    {
        return within::detail::point_in_box_by_side
            <
                within::detail::decide_covered_by
            >(point, box, m_side);
    }

    Spheroid const& model() const
    {
        return m_side.model();
    }

private:
    strategy::side::geographic
        <
            FormulaPolicy, Spheroid, CalculationType
        > m_side;
};


}


}}} // namespace boost::geometry::strategy


#endif // BOOST_GEOMETRY_STRATEGIES_AGNOSTIC_POINT_IN_BOX_BY_SIDE_HPP

/* point_in_box_by_side.hpp
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
*/