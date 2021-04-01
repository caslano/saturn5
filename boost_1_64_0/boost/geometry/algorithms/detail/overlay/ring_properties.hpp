// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017.
// Modifications copyright (c) 2017 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_RING_PROPERTIES_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_RING_PROPERTIES_HPP


#include <boost/geometry/algorithms/area.hpp>
#include <boost/geometry/algorithms/within.hpp>
#include <boost/geometry/algorithms/detail/point_on_border.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

template <typename Point, typename AreaType>
struct ring_properties
{
    typedef Point point_type;
    typedef AreaType area_type;

    bool valid;

    // Filled by "select_rings"
    Point point;
    area_type area;

    // Filled by "update_ring_selection"
    bool reversed;

    // Filled/used by "assign_rings"
    bool discarded;
    ring_identifier parent;
    area_type parent_area;
    std::vector<ring_identifier> children;

    inline ring_properties()
        : valid(false)
        , area(area_type())
        , reversed(false)
        , discarded(false)
        , parent_area(-1)
    {}

    template <typename RingOrBox, typename AreaStrategy>
    inline ring_properties(RingOrBox const& ring_or_box, AreaStrategy const& strategy)
        : reversed(false)
        , discarded(false)
        , parent_area(-1)
    {
        this->area = geometry::area(ring_or_box, strategy);
        valid = geometry::point_on_border(this->point, ring_or_box);
    }

    inline area_type get_area() const
    {
        return reversed ? -area : area;
    }
};

}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_RING_PROPERTIES_HPP

/* ring_properties.hpp
THwRSPhyhyrXeqHkrZAdy6+cB8FfOb1F9PSHQmNkGiQ0XCkR3X9U5Jeg0CPqoxv0RBD1AiSO2E295Vr3p9j+4H9FiaN6oDV25j61NXNHsb9YJWSzx5dRs+PtP6BkdNwgDu7n4L7wIG8BSRj/9H8uhlZs9xRzg/PTKIHNqnPPiu/lb4sAbL4QS1siGvRiU+wfdIVdCgsMRdDW1uDZAGNqh6xzc9nAWRMNBXB0gcZ7ZkGlo0dDmjKN55QoUtW4pZu2H96saJx3mDVdphM1vJwV0f1py2L0eVr3Qdq/zxsRGGV/5KY/4TUwS4I0eroCsBxCJTStscm6u+3GZb9iv3vx7850n6noodtMsVxN8/CQiMnl3hQ0TRmPIk+9JtZB8MXWj8Vz52IPvtgib6w5Aib0S2900RUs7lL9EV+Gfzx7Zs4AgNlwXYg/9QTVm3Q3PZZ0bhvj/pTj3rZjUXH3YsGKO/1kiA240RC0wUHv4Jwd7uecx8QzmTqcWCRDhbCxOcqDMfBCFrhmyXgxC7iDd0SM3Lmtt4Pg0ODulubco1Skpuf8RF7WasZwZkmvng==
*/