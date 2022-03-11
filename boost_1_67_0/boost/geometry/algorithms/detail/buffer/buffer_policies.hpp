// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012-2014 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2018.
// Modifications copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_BUFFER_POLICIES_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_BUFFER_POLICIES_HPP

#include <cstddef>

#include <boost/range.hpp>

#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/algorithms/covered_by.hpp>
#include <boost/geometry/algorithms/detail/overlay/backtrack_check_si.hpp>
#include <boost/geometry/algorithms/detail/overlay/traversal_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>

#include <boost/geometry/strategies/buffer.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace buffer
{


enum intersection_location_type
{
    location_ok, inside_buffer, location_discard
};

class backtrack_for_buffer
{
public :
    typedef detail::overlay::backtrack_state state_type;

    template
        <
            typename Operation,
            typename Rings,
            typename Turns,
            typename Geometry,
            typename Strategy,
            typename RobustPolicy,
            typename Visitor
        >
    static inline void apply(std::size_t size_at_start,
                Rings& rings, typename boost::range_value<Rings>::type& ring,
                Turns& turns,
                typename boost::range_value<Turns>::type const& /*turn*/,
                Operation& operation,
                detail::overlay::traverse_error_type /*traverse_error*/,
                Geometry const& ,
                Geometry const& ,
                Strategy const& ,
                RobustPolicy const& ,
                state_type& state,
                Visitor& /*visitor*/
                )
    {
#if defined(BOOST_GEOMETRY_COUNT_BACKTRACK_WARNINGS)
extern int g_backtrack_warning_count;
g_backtrack_warning_count++;
#endif
//std::cout << "!";
//std::cout << "WARNING " << traverse_error_string(traverse_error) << std::endl;

        state.m_good = false;

        // Make bad output clean
        rings.resize(size_at_start);
        ring.clear();

        // Reject this as a starting point
        operation.visited.set_rejected();

        // And clear all visit info
        clear_visit_info(turns);
    }
};

struct buffer_overlay_visitor
{
public :
    void print(char const* /*header*/)
    {
    }

    template <typename Turns>
    void print(char const* /*header*/, Turns const& /*turns*/, int /*turn_index*/)
    {
    }

    template <typename Turns>
    void print(char const* /*header*/, Turns const& /*turns*/, int /*turn_index*/, int /*op_index*/)
    {
    }

    template <typename Turns>
    void visit_turns(int , Turns const& ) {}

    template <typename Clusters, typename Turns>
    void visit_clusters(Clusters const& , Turns const& ) {}

    template <typename Turns, typename Turn, typename Operation>
    void visit_traverse(Turns const& /*turns*/, Turn const& /*turn*/, Operation const& /*op*/, const char* /*header*/)
    {
    }

    template <typename Turns, typename Turn, typename Operation>
    void visit_traverse_reject(Turns const& , Turn const& , Operation const& ,
            detail::overlay::traverse_error_type )
    {}

    template <typename Rings>
    void visit_generated_rings(Rings const& )
    {}
};


// Should follow traversal-turn-concept (enrichment, visit structure)
// and adds index in piece vector to find it back
template <typename Point, typename SegmentRatio>
struct buffer_turn_operation
    : public detail::overlay::traversal_turn_operation<Point, SegmentRatio>
{
    signed_size_type piece_index;
    signed_size_type index_in_robust_ring;

    inline buffer_turn_operation()
        : piece_index(-1)
        , index_in_robust_ring(-1)
    {}
};

// Version for buffer including type of location, is_opposite, and helper variables
template <typename Point, typename RobustPoint, typename SegmentRatio>
struct buffer_turn_info
    : public detail::overlay::turn_info
        <
            Point,
            SegmentRatio,
            buffer_turn_operation<Point, SegmentRatio>
        >
{
    typedef Point point_type;
    typedef RobustPoint robust_point_type;

    std::size_t turn_index; // TODO: this might go if partition can operate on non-const input

    RobustPoint robust_point;

    inline RobustPoint const& get_robust_point() const
    {
        return robust_point;
    }

    intersection_location_type location;

    robust_point_type rob_pi, rob_pj, rob_qi, rob_qj;

    std::size_t count_within;

    bool within_original;
    signed_size_type count_in_original; // increased by +1 for in ext.ring, -1 for int.ring

    std::size_t count_on_offsetted;
    std::size_t count_on_helper;
    std::size_t count_within_near_offsetted;

    inline buffer_turn_info()
        : turn_index(0)
        , location(location_ok)
        , count_within(0)
        , within_original(false)
        , count_in_original(0)
        , count_on_offsetted(0)
        , count_on_helper(0)
        , count_within_near_offsetted(0)
    {}
};

struct buffer_operation_less
{
    template <typename Turn>
    inline bool operator()(Turn const& left, Turn const& right) const
    {
        segment_identifier const& sl = left.seg_id;
        segment_identifier const& sr = right.seg_id;

        // Sort them descending
        return sl == sr
            ? left.fraction < right.fraction
            : sl < sr;
    }
};

}} // namespace detail::buffer
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_BUFFER_POLICIES_HPP

/* buffer_policies.hpp
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
*/