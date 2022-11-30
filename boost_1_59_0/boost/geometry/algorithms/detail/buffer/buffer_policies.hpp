// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012-2014 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017-2020.
// Modifications copyright (c) 2017-2020, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_BUFFER_POLICIES_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_BUFFER_POLICIES_HPP

#include <cstddef>

#include <boost/range/value_type.hpp>

#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/algorithms/detail/overlay/backtrack_check_si.hpp>
#include <boost/geometry/algorithms/detail/overlay/traversal_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>

#include <boost/geometry/strategies/buffer.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace buffer
{

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

// Version of turn_info for buffer with its turn index and other helper variables
template <typename Point, typename SegmentRatio>
struct buffer_turn_info
    : public detail::overlay::turn_info
        <
            Point,
            SegmentRatio,
            buffer_turn_operation<Point, SegmentRatio>
        >
{
    typedef Point point_type;

    std::size_t turn_index;

    // Information if turn can be used. It is not traversable if it is within
    // another piece, or within the original (depending on deflation),
    // or (for deflate) if there are not enough points to traverse it.
    bool is_turn_traversable;

    bool close_to_offset;
    bool is_linear_end_point;
    bool within_original;
    signed_size_type count_in_original; // increased by +1 for in ext.ring, -1 for int.ring

    inline buffer_turn_info()
        : turn_index(0)
        , is_turn_traversable(true)
        , close_to_offset(false)
        , is_linear_end_point(false)
        , within_original(false)
        , count_in_original(0)
    {}
};

struct buffer_less
{
    template <typename Indexed>
    inline bool operator()(Indexed const& left, Indexed const& right) const
    {
        if (! (left.subject->seg_id == right.subject->seg_id))
        {
            return left.subject->seg_id < right.subject->seg_id;
        }

        // Both left and right are located on the SAME segment.
        if (! (left.subject->fraction == right.subject->fraction))
        {
            return left.subject->fraction < right.subject->fraction;
        }

        return left.turn_index < right.turn_index;
    }
};

template <typename Strategy>
struct piece_get_box
{
    explicit piece_get_box(Strategy const& strategy)
        : m_strategy(strategy)
    {}

    template <typename Box, typename Piece>
    inline void apply(Box& total, Piece const& piece) const
    {
        assert_coordinate_type_equal(total, piece.m_piece_border.m_envelope);

        if (piece.m_piece_border.m_has_envelope)
        {
            geometry::expand(total, piece.m_piece_border.m_envelope,
                             m_strategy);
        }
    }

    Strategy const& m_strategy;
};

template <typename Strategy>
struct piece_overlaps_box
{
    explicit piece_overlaps_box(Strategy const& strategy)
        : m_strategy(strategy)
    {}

    template <typename Box, typename Piece>
    inline bool apply(Box const& box, Piece const& piece) const
    {
        assert_coordinate_type_equal(box, piece.m_piece_border.m_envelope);

        if (piece.type == strategy::buffer::buffered_flat_end
            || piece.type == strategy::buffer::buffered_concave)
        {
            // Turns cannot be inside a flat end (though they can be on border)
            // Neither we need to check if they are inside concave helper pieces

            // Skip all pieces not used as soon as possible
            return false;
        }
        if (! piece.m_piece_border.m_has_envelope)
        {
            return false;
        }

        return ! geometry::detail::disjoint::disjoint_box_box(box, piece.m_piece_border.m_envelope,
                                                              m_strategy);
    }

    Strategy const& m_strategy;
};

template <typename Strategy>
struct turn_get_box
{
    explicit turn_get_box(Strategy const& strategy)
        : m_strategy(strategy)
    {}

    template <typename Box, typename Turn>
    inline void apply(Box& total, Turn const& turn) const
    {
        assert_coordinate_type_equal(total, turn.point);
        geometry::expand(total, turn.point, m_strategy);
    }

    Strategy const& m_strategy;
};

template <typename Strategy>
struct turn_overlaps_box
{
    explicit turn_overlaps_box(Strategy const& strategy)
        : m_strategy(strategy)
    {}

    template <typename Box, typename Turn>
    inline bool apply(Box const& box, Turn const& turn) const
    {
        assert_coordinate_type_equal(turn.point, box);
        return ! geometry::detail::disjoint::disjoint_point_box(turn.point, box,
                                                                m_strategy);
    }

    Strategy const& m_strategy;
};

struct enriched_map_buffer_include_policy
{
    template <typename Operation>
    static inline bool include(Operation const& op)
    {
        return op != detail::overlay::operation_intersection
            && op != detail::overlay::operation_blocked;
    }
};

}} // namespace detail::buffer
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_BUFFER_POLICIES_HPP

/* buffer_policies.hpp
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
*/