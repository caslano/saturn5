// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2016-2022.
// Modifications copyright (c) 2016-2022 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_BUFFERED_PIECE_COLLECTION_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_BUFFERED_PIECE_COLLECTION_HPP

#include <algorithm>
#include <cstddef>
#include <set>

#include <boost/core/ignore_unused.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/algorithms/covered_by.hpp>
#include <boost/geometry/algorithms/envelope.hpp>

#include <boost/geometry/strategies/buffer.hpp>

#include <boost/geometry/geometries/ring.hpp>

#include <boost/geometry/algorithms/detail/buffer/buffered_ring.hpp>
#include <boost/geometry/algorithms/detail/buffer/buffer_policies.hpp>
#include <boost/geometry/algorithms/detail/overlay/cluster_info.hpp>
#include <boost/geometry/algorithms/detail/buffer/get_piece_turns.hpp>
#include <boost/geometry/algorithms/detail/buffer/piece_border.hpp>
#include <boost/geometry/algorithms/detail/buffer/turn_in_piece_visitor.hpp>
#include <boost/geometry/algorithms/detail/buffer/turn_in_original_visitor.hpp>

#include <boost/geometry/algorithms/detail/disjoint/point_box.hpp>
#include <boost/geometry/algorithms/detail/overlay/add_rings.hpp>
#include <boost/geometry/algorithms/detail/overlay/assign_parents.hpp>
#include <boost/geometry/algorithms/detail/overlay/enrichment_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/enrich_intersection_points.hpp>
#include <boost/geometry/algorithms/detail/overlay/ring_properties.hpp>
#include <boost/geometry/algorithms/detail/overlay/select_rings.hpp>
#include <boost/geometry/algorithms/detail/overlay/traversal_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/traverse.hpp>
#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>
#include <boost/geometry/algorithms/detail/partition.hpp>
#include <boost/geometry/algorithms/detail/sections/sectionalize.hpp>
#include <boost/geometry/algorithms/detail/sections/section_box_policies.hpp>

#include <boost/geometry/views/detail/closed_clockwise_view.hpp>
#include <boost/geometry/util/range.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace buffer
{


/*
 *  Terminology
 *
 *  Suppose we make a buffer (using blocked corners) of this rectangle:
 *
 *         +-------+
 *         |       |
 *         |  rect |
 *         |       |
 *         +-------+
 *
 * For the sides we get these four buffered side-pieces (marked with s)
 * and four buffered corner pieces (marked with c)
 *
 *     c---+---s---+---c
 *     |   | piece |   |     <- see below for details of the middle top-side-piece
 *     +---+-------+---+
 *     |   |       |   |
 *     s   |  rect |   s     <- two side pieces left/right of rect
 *     |   |       |   |
 *     +---+-------+---+
 *     |   | piece |   |     <- one side-piece below, and two corner pieces
 *     c---+---s---+---c
 *
 *  The outer part of the picture above, using all pieces,
 *    form together the offsetted ring (marked with o below)
 *  The 8 pieces are part of the piece collection and use for inside-checks
 *  The inner parts form (using 1 or 2 points per piece, often co-located)
 *    form together the robust_polygons (marked with r below)
 *  The remaining piece-segments are helper-segments (marked with h)
 *
 *     ooooooooooooooooo
 *     o   h       h   o
 *     ohhhrrrrrrrrrhhho
 *     o   r       r   o
 *     o   r       r   o
 *     o   r       r   o
 *     ohhhrrrrrrrrrhhho
 *     o   h       h   o
 *     ooooooooooooooooo
 *
 */

template
<
    typename Ring,
    typename Strategy,
    typename DistanceStrategy,
    typename RobustPolicy
>
struct buffered_piece_collection
{
    typedef typename geometry::point_type<Ring>::type point_type;
    typedef typename geometry::coordinate_type<Ring>::type coordinate_type;

    // Ring/polygon type, always clockwise
    typedef geometry::model::ring<point_type> clockwise_ring_type;

    typedef geometry::model::box<point_type> box_type;

    typedef buffer_turn_info
    <
        point_type,
        typename segment_ratio_type<point_type, RobustPolicy>::type
    > buffer_turn_info_type;

    typedef buffer_turn_operation
    <
        point_type,
        typename segment_ratio_type<point_type, RobustPolicy>::type
    > buffer_turn_operation_type;

    typedef std::vector<buffer_turn_info_type> turn_vector_type;

    typedef piece_border<Ring, point_type> piece_border_type;

    struct piece
    {
        strategy::buffer::piece_type type;
        signed_size_type index;

        signed_size_type left_index; // points to previous piece of same ring
        signed_size_type right_index; // points to next piece of same ring

        // The next two members (1, 2) form together a complete clockwise ring
        // for each piece (with one dupped point)
        // The complete clockwise ring is also included as a robust ring (3)

        // 1: half, part of offsetted_rings

        // Segment identifier of this piece, including its start index
        segment_identifier first_seg_id;

        // One-beyond index of this piece, to iterate over a ring
        // from:                ring.begin() + pc.first_seg_id.segment_index;
        // to (not including):  ring.begin() + pc.beyond_last_segment_index;
        // Its ring_id etc are shared with first_seg_id
        signed_size_type beyond_last_segment_index;

        // part in offsetted ring which is part of offsetted ring
        signed_size_type offsetted_count;

        bool is_flat_start;
        bool is_flat_end;

        bool is_deflated;

        // Ring (parts) of this piece, always clockwise
        piece_border_type m_piece_border;

        point_type m_label_point;

        // For a point buffer
        point_type m_center;

        piece()
            : type(strategy::buffer::piece_type_unknown)
            , index(-1)
            , left_index(-1)
            , right_index(-1)
            , beyond_last_segment_index(-1)
            , offsetted_count(-1)
            , is_flat_start(false)
            , is_flat_end(false)
            , is_deflated(false)
        {
        }
    };

    struct original_ring
    {
        typedef geometry::sections<box_type, 1> sections_type;

        // Creates an empty instance
        inline original_ring()
            : m_is_interior(false)
            , m_has_interiors(false)
        {}

        inline original_ring(clockwise_ring_type const& ring,
                             bool is_interior, bool has_interiors,
                             Strategy const& strategy)
            : m_ring(ring)
            , m_is_interior(is_interior)
            , m_has_interiors(has_interiors)
        {
            geometry::envelope(m_ring, m_box, strategy);

            // create monotonic sections in x-dimension
            // The dimension is critical because the direction is later used
            // in the optimization for within checks using winding strategy
            // and this strategy is scanning in x direction.
            typedef std::integer_sequence<std::size_t, 0> dimensions;
            geometry::sectionalize
                <
                    false, dimensions
                >(m_ring, detail::no_rescale_policy(), m_sections, strategy);
        }

        clockwise_ring_type m_ring;
        box_type m_box;
        sections_type m_sections;

        bool m_is_interior;
        bool m_has_interiors;
    };

    typedef std::vector<piece> piece_vector_type;

    piece_vector_type m_pieces;
    turn_vector_type m_turns;
    signed_size_type m_first_piece_index;
    bool m_deflate;
    bool m_has_deflated;

    // Offsetted rings, and representations of original ring(s)
    // both indexed by multi_index
    buffered_ring_collection<buffered_ring<Ring> > offsetted_rings;
    std::vector<original_ring> original_rings;
    std::vector<point_type> m_linear_end_points;

    buffered_ring_collection<Ring> traversed_rings;
    segment_identifier current_segment_id;

    // Monotonic sections (used for offsetted rings around points)
    // are still using a robust type, to be comparable with turn calculations,
    // which is using rescaling.
    typedef geometry::model::box
    <
        typename geometry::robust_point_type<point_type, RobustPolicy>::type
    > robust_box_type;
    typedef geometry::sections <robust_box_type, 2> robust_sections_type;
    robust_sections_type monotonic_sections;

    // Define the clusters, mapping cluster_id -> turns
    typedef std::map
        <
            signed_size_type,
            detail::overlay::cluster_info
        > cluster_type;

    cluster_type m_clusters;

    Strategy m_strategy;
    DistanceStrategy m_distance_strategy;
    RobustPolicy const& m_robust_policy;

    buffered_piece_collection(Strategy const& strategy,
                              DistanceStrategy const& distance_strategy,
                              RobustPolicy const& robust_policy)
        : m_first_piece_index(-1)
        , m_deflate(false)
        , m_has_deflated(false)
        , m_strategy(strategy)
        , m_distance_strategy(distance_strategy)
        , m_robust_policy(robust_policy)
    {}

    inline bool is_following(buffer_turn_info_type const& turn,
                             buffer_turn_operation_type const& op)
    {
        return turn.operations[0].seg_id.segment_index == op.seg_id.segment_index
            || turn.operations[1].seg_id.segment_index == op.seg_id.segment_index;
    }

    // Verify if turns which are classified as OK (outside or on border of
    // offsetted ring) do not traverse through other turns which are classified
    // as WITHIN (inside a piece). This can happen if turns are nearly colocated
    // and due to floating point precision just classified as within, while
    // they should not be within.
    // In those cases the turns are fine to travel through (and should),
    // but they are not made startable.
    template <typename Vector>
    inline void pretraverse(Vector const& indexed_operations)
    {
        // Verify if the turns which are OK don't skip segments
        typedef typename boost::range_value<Vector>::type indexed_type;
        buffer_turn_operation_type last_traversable_operation;
        buffer_turn_info_type last_traversable_turn;
        bool first = true;
        for (std::size_t i = 0; i < indexed_operations.size(); i++)
        {
            indexed_type const & itop = indexed_operations[i];
            buffer_turn_info_type const& turn = m_turns[itop.turn_index];

            if (turn.is_turn_traversable && ! first)
            {
               // Check previous and next turns. The first is handled
               BOOST_GEOMETRY_ASSERT(i > 0);
               indexed_type const& previous_itop = indexed_operations[i - 1];
               std::size_t const next_index = i + 1 < indexed_operations.size() ? i + 1 : 0;
               indexed_type const& next_itop = indexed_operations[next_index];

               buffer_turn_info_type& previous_turn = m_turns[previous_itop.turn_index];
               buffer_turn_info_type& next_turn = m_turns[next_itop.turn_index];

               if (previous_turn.close_to_offset
                   && is_following(previous_turn, last_traversable_operation))
               {
                   previous_turn.is_turn_traversable = true;
               }
               else if (next_turn.close_to_offset
                        && is_following(next_turn, last_traversable_operation))
               {
                   next_turn.is_turn_traversable = true;
               }
            }

            if (turn.is_turn_traversable)
            {
                first = false;
                last_traversable_operation = *itop.subject;
                last_traversable_turn = turn;
            }
        }
    }

    inline void check_linear_endpoints(buffer_turn_info_type& turn) const
    {
        // TODO this is quadratic. But the #endpoints, expected, is low,
        // and only applicable for linear features
        // (in a multi linestring with many short lines, the #endpoints can be
        // much higher)
        for (typename boost::range_iterator<std::vector<point_type> const>::type it
             = boost::begin(m_linear_end_points);
             it != boost::end(m_linear_end_points);
             ++it)
        {
            if (detail::equals::equals_point_point(turn.point, *it, m_strategy))
            {
                turn.is_linear_end_point = true;
            }
        }
    }

    inline void verify_turns()
    {
        typedef detail::overlay::indexed_turn_operation
            <
                buffer_turn_operation_type
            > indexed_turn_operation;
        typedef std::map
            <
                ring_identifier,
                std::vector<indexed_turn_operation>
            > mapped_vector_type;
        mapped_vector_type mapped_vector;

        detail::overlay::create_map(m_turns, mapped_vector,
                                    enriched_map_buffer_include_policy());

        // Sort turns over offsetted ring(s)
        for (typename mapped_vector_type::iterator mit
            = mapped_vector.begin();
            mit != mapped_vector.end();
            ++mit)
        {
            std::sort(mit->second.begin(), mit->second.end(), buffer_less());
        }

        for (typename mapped_vector_type::iterator mit
            = mapped_vector.begin();
            mit != mapped_vector.end();
            ++mit)
        {
            pretraverse(mit->second);
        }
    }

    inline void deflate_check_turns()
    {
        if (! m_has_deflated)
        {
            return;
        }

        // Deflated rings may not travel to themselves, there should at least
        // be three turns (which cannot be checked here - TODO: add to traverse)
        for (typename boost::range_iterator<turn_vector_type>::type it =
            boost::begin(m_turns); it != boost::end(m_turns); ++it)
        {
            buffer_turn_info_type& turn = *it;
            if (! turn.is_turn_traversable)
            {
                continue;
            }
            for (int i = 0; i < 2; i++)
            {
                buffer_turn_operation_type& op = turn.operations[i];
                if (op.enriched.get_next_turn_index() == static_cast<signed_size_type>(turn.turn_index)
                    && m_pieces[op.seg_id.piece_index].is_deflated)
                {
                    // Keep traversable, but don't start here
                    op.enriched.startable = false;
                }
            }
        }
    }

    // Check if a turn is inside any of the originals
    inline void check_turn_in_original()
    {
        turn_in_original_visitor
            <
                turn_vector_type,
                Strategy
            > visitor(m_turns, m_strategy);

        geometry::partition
            <
                box_type,
                include_turn_policy,
                detail::partition::include_all_policy
            >::apply(m_turns, original_rings, visitor,
                     turn_get_box<Strategy>(m_strategy),
                     turn_in_original_overlaps_box<Strategy>(m_strategy),
                     original_get_box<Strategy>(m_strategy),
                     original_overlaps_box<Strategy>(m_strategy));

        bool const deflate = m_distance_strategy.negative();

        for (typename boost::range_iterator<turn_vector_type>::type it =
            boost::begin(m_turns); it != boost::end(m_turns); ++it)
        {
            buffer_turn_info_type& turn = *it;
            if (turn.is_turn_traversable)
            {
                if (deflate && turn.count_in_original <= 0)
                {
                    // For deflate/negative buffers:
                    // it is not in the original, so don't use it
                    turn.is_turn_traversable = false;
                }
                else if (! deflate && turn.count_in_original > 0)
                {
                    // For inflate: it is in original, so don't use it
                    turn.is_turn_traversable = false;
                }
            }
        }
    }

    inline void update_turn_administration()
    {
        std::size_t index = 0;
        for (typename boost::range_iterator<turn_vector_type>::type it =
            boost::begin(m_turns); it != boost::end(m_turns); ++it, ++index)
        {
            buffer_turn_info_type& turn = *it;

            // Update member used
            turn.turn_index = index;

            // Verify if a turn is a linear endpoint
            if (! turn.is_linear_end_point)
            {
                check_linear_endpoints(turn);
            }
        }
    }

    // Calculate properties of piece borders which are not influenced
    // by turns themselves:
    // - envelopes (essential for partitioning during calc turns)
    // - convexity
    // - monotonicity
    // - min/max radius of point buffers
    // - (if pieces are reversed)
    inline void update_piece_administration()
    {
        for (typename piece_vector_type::iterator it = boost::begin(m_pieces);
            it != boost::end(m_pieces);
            ++it)
        {
            piece& pc = *it;
            piece_border_type& border = pc.m_piece_border;
            buffered_ring<Ring> const& ring = offsetted_rings[pc.first_seg_id.multi_index];

            if (pc.offsetted_count > 0)
            {
                if (pc.type != strategy::buffer::buffered_concave)
                {
                    border.set_offsetted(ring, pc.first_seg_id.segment_index,
                                       pc.beyond_last_segment_index);
                }

                // Calculate envelopes for piece borders
                border.get_properties_of_border(pc.type == geometry::strategy::buffer::buffered_point,
                                                pc.m_center, m_strategy);
                if (! pc.is_flat_end && ! pc.is_flat_start)
                {
                    border.get_properties_of_offsetted_ring_part(m_strategy);
                }
            }
        }
    }

    inline void get_turns()
    {
        update_piece_administration();

        {
            // Calculate the turns
            piece_turn_visitor
                <
                    piece_vector_type,
                    buffered_ring_collection<buffered_ring<Ring> >,
                    turn_vector_type,
                    Strategy,
                    RobustPolicy
                > visitor(m_pieces, offsetted_rings, m_turns,
                          m_strategy, m_robust_policy);

            detail::sectionalize::enlarge_sections(monotonic_sections, m_strategy);

            geometry::partition
                <
                    robust_box_type
                >::apply(monotonic_sections, visitor,
                         detail::section::get_section_box<Strategy>(m_strategy),
                         detail::section::overlaps_section_box<Strategy>(m_strategy));
        }

        update_turn_administration();

        {
            // Check if turns are inside pieces
            turn_in_piece_visitor
                <
                    typename geometry::cs_tag<point_type>::type,
                    turn_vector_type, piece_vector_type, DistanceStrategy, Strategy
                > visitor(m_turns, m_pieces, m_distance_strategy, m_strategy);

            geometry::partition
                <
                    box_type
                >::apply(m_turns, m_pieces, visitor,
                         turn_get_box<Strategy>(m_strategy),
                         turn_overlaps_box<Strategy>(m_strategy),
                         piece_get_box<Strategy>(m_strategy),
                         piece_overlaps_box<Strategy>(m_strategy));
        }
    }

    inline void start_new_ring(bool deflate)
    {
        std::size_t const n = offsetted_rings.size();
        current_segment_id.source_index = 0;
        current_segment_id.multi_index = static_cast<signed_size_type>(n);
        current_segment_id.ring_index = -1;
        current_segment_id.segment_index = 0;

        offsetted_rings.resize(n + 1);
        original_rings.resize(n + 1);

        m_first_piece_index = static_cast<signed_size_type>(boost::size(m_pieces));
        m_deflate = deflate;
        if (deflate)
        {
            // Pieces contain either deflated exterior rings, or inflated
            // interior rings which are effectively deflated too
            m_has_deflated = true;
        }
    }

    inline void abort_ring()
    {
        // Remove all created pieces for this ring, sections, last offsetted
        while (! m_pieces.empty()
               && m_pieces.back().first_seg_id.multi_index
               == current_segment_id.multi_index)
        {
            m_pieces.pop_back();
        }

        offsetted_rings.pop_back();
        original_rings.pop_back();

        m_first_piece_index = -1;
    }

    inline void update_last_point(point_type const& p,
            buffered_ring<Ring>& ring)
    {
        // For the first point of a new piece, and there were already
        // points in the offsetted ring, for some piece types the first point
        // is a duplicate of the last point of the previous piece.

        // TODO: disable that, that point should not be added

        // For now, it is made equal because due to numerical instability,
        // it can be a tiny bit off, possibly causing a self-intersection

        BOOST_GEOMETRY_ASSERT(boost::size(m_pieces) > 0);
        if (! ring.empty()
            && current_segment_id.segment_index
                == m_pieces.back().first_seg_id.segment_index)
        {
            ring.back() = p;
        }
    }

    inline void set_piece_center(point_type const& center)
    {
        BOOST_GEOMETRY_ASSERT(! m_pieces.empty());
        m_pieces.back().m_center = center;
    }

    inline bool finish_ring(strategy::buffer::result_code code)
    {
        if (code == strategy::buffer::result_error_numerical)
        {
            abort_ring();
            return false;
        }

        if (m_first_piece_index == -1)
        {
            return false;
        }

        // Casted version
        std::size_t const first_piece_index
                = static_cast<std::size_t>(m_first_piece_index);
        signed_size_type const last_piece_index
                = static_cast<signed_size_type>(boost::size(m_pieces)) - 1;

        if (first_piece_index < boost::size(m_pieces))
        {
            // If pieces were added,
            // reassign left-of-first and right-of-last
            geometry::range::at(m_pieces, first_piece_index).left_index
                    = last_piece_index;
            geometry::range::back(m_pieces).right_index = m_first_piece_index;
        }

        buffered_ring<Ring>& added = offsetted_rings.back();
        if (! boost::empty(added))
        {
            // Make sure the closing point is identical (they are calculated
            // separately by different pieces)
            range::back(added) = range::front(added);
        }

        for (std::size_t i = first_piece_index; i < boost::size(m_pieces); i++)
        {
            sectionalize(m_pieces[i], added);
        }

        m_first_piece_index = -1;
        return true;
    }

    template <typename InputRing>
    inline void finish_ring(strategy::buffer::result_code code,
                            InputRing const& input_ring,
                            bool is_interior, bool has_interiors)
    {
        if (! finish_ring(code))
        {
            return;
        }

        if (! input_ring.empty())
        {
            // Assign the ring to the original_ring collection
            // For rescaling, it is recalculated. Without rescaling, it
            // is just assigning (note that this Ring type is the
            // GeometryOut type, which might differ from the input ring type)
            clockwise_ring_type clockwise_ring;

            using view_type = detail::closed_clockwise_view<InputRing const>;
            view_type const view(input_ring);

            for (typename boost::range_iterator<view_type const>::type it =
                boost::begin(view); it != boost::end(view); ++it)
            {
                clockwise_ring.push_back(*it);
            }

            original_rings.back()
                = original_ring(clockwise_ring,
                    is_interior, has_interiors,
                    m_strategy);
        }
    }

    inline void set_current_ring_concave()
    {
        BOOST_GEOMETRY_ASSERT(boost::size(offsetted_rings) > 0);
        offsetted_rings.back().has_concave = true;
    }

    inline signed_size_type add_point(point_type const& p)
    {
        BOOST_GEOMETRY_ASSERT(boost::size(offsetted_rings) > 0);

        buffered_ring<Ring>& current_ring = offsetted_rings.back();
        update_last_point(p, current_ring);

        current_segment_id.segment_index++;
        current_ring.push_back(p);
        return static_cast<signed_size_type>(current_ring.size());
    }

    //-------------------------------------------------------------------------

    inline piece& create_piece(strategy::buffer::piece_type type,
            bool decrease_segment_index_by_one)
    {
        if (type == strategy::buffer::buffered_concave)
        {
            offsetted_rings.back().has_concave = true;
        }

        piece pc;
        pc.type = type;
        pc.index = static_cast<signed_size_type>(boost::size(m_pieces));
        pc.is_deflated = m_deflate;

        current_segment_id.piece_index = pc.index;

        pc.first_seg_id = current_segment_id;

        // Assign left/right (for first/last piece per ring they will be re-assigned later)
        pc.left_index = pc.index - 1;
        pc.right_index = pc.index + 1;

        std::size_t const n = boost::size(offsetted_rings.back());
        pc.first_seg_id.segment_index = decrease_segment_index_by_one ? n - 1 : n;
        pc.beyond_last_segment_index = pc.first_seg_id.segment_index;

        m_pieces.push_back(pc);
        return m_pieces.back();
    }

    inline void init_rescale_piece(piece& pc)
    {
        if (pc.first_seg_id.segment_index < 0)
        {
            // This indicates an error situation: an earlier piece was empty
            // It currently does not happen
            pc.offsetted_count = 0;
            return;
        }

        BOOST_GEOMETRY_ASSERT(pc.first_seg_id.multi_index >= 0);
        BOOST_GEOMETRY_ASSERT(pc.beyond_last_segment_index >= 0);

        pc.offsetted_count = pc.beyond_last_segment_index - pc.first_seg_id.segment_index;
        BOOST_GEOMETRY_ASSERT(pc.offsetted_count >= 0);
    }

    inline void add_piece_point(piece& pc, const point_type& point, bool add_to_original)
    {
        if (add_to_original && pc.type != strategy::buffer::buffered_concave)
        {
            pc.m_piece_border.add_original_point(point);
        }
        else
        {
            pc.m_label_point = point;
        }
    }

    inline void sectionalize(piece const& pc, buffered_ring<Ring> const& ring)
    {
        using sectionalizer = geometry::detail::sectionalize::sectionalize_part
        <
            std::integer_sequence<std::size_t, 0, 1> // x,y dimension
        >;

        // Create a ring-identifier. The source-index is the piece index
        // The multi_index is as in this collection (the ring), but not used here
        // The ring_index is not used
        ring_identifier const ring_id(pc.index, pc.first_seg_id.multi_index, -1);

        sectionalizer::apply(monotonic_sections,
            boost::begin(ring) + pc.first_seg_id.segment_index,
            boost::begin(ring) + pc.beyond_last_segment_index,
            m_robust_policy,
            m_strategy,
            ring_id, 10);
    }

    inline void finish_piece(piece& pc)
    {
        init_rescale_piece(pc);
    }

    inline void finish_piece(piece& pc,
                    point_type const& point1,
                    point_type const& point2,
                    point_type const& point3)
    {
        init_rescale_piece(pc);
        if (pc.offsetted_count == 0)
        {
            return;
        }

        add_piece_point(pc, point1, false);
        add_piece_point(pc, point2, true);
        add_piece_point(pc, point3, false);
    }

    inline void finish_piece(piece& pc,
                    point_type const& point1,
                    point_type const& point2,
                    point_type const& point3,
                    point_type const& point4)
    {
        init_rescale_piece(pc);

        // Add the four points. Note that points 2 and 3 are the originals,
        // and that they are already passed in reverse order
        // (because the offsetted ring is in clockwise order)
        add_piece_point(pc, point1, false);
        add_piece_point(pc, point2, true);
        add_piece_point(pc, point3, true);
        add_piece_point(pc, point4, false);
    }

    template <typename Range>
    inline void add_range_to_piece(piece& pc, Range const& range, bool add_front)
    {
        BOOST_GEOMETRY_ASSERT(boost::size(range) != 0u);

        typename Range::const_iterator it = boost::begin(range);

        // If it follows a non-join (so basically the same piece-type) point b1 should be added.
        // There should be two intersections later and it should be discarded.
        // But for now we need it to calculate intersections
        if (add_front)
        {
            add_point(*it);
        }

        for (++it; it != boost::end(range); ++it)
        {
            pc.beyond_last_segment_index = add_point(*it);
        }
    }

    inline void add_piece(strategy::buffer::piece_type type, point_type const& p,
            point_type const& b1, point_type const& b2)
    {
        piece& pc = create_piece(type, false);
        add_point(b1);
        pc.beyond_last_segment_index = add_point(b2);
        finish_piece(pc, b2, p, b1);
    }

    template <typename Range>
    inline void add_piece(strategy::buffer::piece_type type, Range const& range,
            bool decrease_segment_index_by_one)
    {
        piece& pc = create_piece(type, decrease_segment_index_by_one);

        if (boost::size(range) > 0u)
        {
            add_range_to_piece(pc, range, offsetted_rings.back().empty());
        }
        finish_piece(pc);
    }

    template <typename Range>
    inline void add_piece(strategy::buffer::piece_type type,
            point_type const& p, Range const& range)
    {
        piece& pc = create_piece(type, true);

        if (boost::size(range) > 0u)
        {
            add_range_to_piece(pc, range, offsetted_rings.back().empty());
            finish_piece(pc, range.back(), p, range.front());
        }
        else
        {
            finish_piece(pc);
        }
    }

    template <typename Range>
    inline void add_side_piece(point_type const& original_point1,
            point_type const& original_point2,
            Range const& range, bool first)
    {
        BOOST_GEOMETRY_ASSERT(boost::size(range) >= 2u);

        piece& pc = create_piece(strategy::buffer::buffered_segment, ! first);
        add_range_to_piece(pc, range, first);

        // Add the four points of the side, starting with the last point of the
        // range, and reversing the order of the originals to keep it clockwise
        finish_piece(pc, range.back(), original_point2, original_point1, range.front());
    }

    template <typename EndcapStrategy, typename Range>
    inline void add_endcap(EndcapStrategy const& strategy, Range const& range,
            point_type const& end_point)
    {
        boost::ignore_unused(strategy);

        if (range.empty())
        {
            return;
        }
        strategy::buffer::piece_type pt = strategy.get_piece_type();
        if (pt == strategy::buffer::buffered_flat_end)
        {
            // It is flat, should just be added, without helper segments
            add_piece(pt, range, true);
        }
        else
        {
            // Normal case, it has an "inside", helper segments should be added
            add_piece(pt, end_point, range);
        }
    }

    inline void mark_flat_start(point_type const& point)
    {
        if (! m_pieces.empty())
        {
            piece& back = m_pieces.back();
            back.is_flat_start = true;

            // This happens to linear buffers, and it will be the very
            // first or last point. If that coincides with a turn,
            // and the turn was marked as ON_BORDER
            // the turn should NOT be within (even though it can be marked
            // as such)
            m_linear_end_points.push_back(point);
        }
    }

    inline void mark_flat_end(point_type const& point)
    {
        if (! m_pieces.empty())
        {
            piece& back = m_pieces.back();
            back.is_flat_end = true;
            m_linear_end_points.push_back(point);
        }
    }

    //-------------------------------------------------------------------------

    inline void enrich()
    {
        enrich_intersection_points<false, false, overlay_buffer>(m_turns,
            m_clusters, offsetted_rings, offsetted_rings,
            m_robust_policy,
            m_strategy);
    }

    // Discards all rings which do have not-OK intersection points only.
    // Those can never be traversed and should not be part of the output.
    inline void discard_rings()
    {
        for (typename boost::range_iterator<turn_vector_type const>::type it =
            boost::begin(m_turns); it != boost::end(m_turns); ++it)
        {
            if (it->is_turn_traversable)
            {
                offsetted_rings[it->operations[0].seg_id.multi_index].has_accepted_intersections = true;
                offsetted_rings[it->operations[1].seg_id.multi_index].has_accepted_intersections = true;
            }
            else
            {
                offsetted_rings[it->operations[0].seg_id.multi_index].has_discarded_intersections = true;
                offsetted_rings[it->operations[1].seg_id.multi_index].has_discarded_intersections = true;
            }
        }
    }

    inline bool point_coveredby_original(point_type const& point)
    {
        signed_size_type count_in_original = 0;

        // Check of the robust point of this outputted ring is in
        // any of the robust original rings
        // This can go quadratic if the input has many rings, and there
        // are many untouched deflated rings around
        for (typename std::vector<original_ring>::const_iterator it
            = original_rings.begin();
            it != original_rings.end();
            ++it)
        {
            original_ring const& original = *it;
            if (original.m_ring.empty())
            {
                continue;
            }
            if (detail::disjoint::disjoint_point_box(point, original.m_box,m_strategy))
            {
                continue;
            }

            int const geometry_code
                = detail::within::point_in_geometry(point, original.m_ring, m_strategy);

            if (geometry_code == -1)
            {
                // Outside, continue
                continue;
            }

            // Apply for possibly nested interior rings
            if (original.m_is_interior)
            {
                count_in_original--;
            }
            else if (original.m_has_interiors)
            {
                count_in_original++;
            }
            else
            {
                // Exterior ring without interior rings
                return true;
            }
        }
        return count_in_original > 0;
    }

    // For a deflate, all rings around inner rings which are untouched
    // (no intersections/turns) and which are OUTSIDE the original should
    // be discarded
    inline void discard_nonintersecting_deflated_rings()
    {
        for(typename buffered_ring_collection<buffered_ring<Ring> >::iterator it
            = boost::begin(offsetted_rings);
            it != boost::end(offsetted_rings);
            ++it)
        {
            buffered_ring<Ring>& ring = *it;
            if (! ring.has_intersections()
                && boost::size(ring) > 0u
                && geometry::area(ring, m_strategy) < 0)
            {
                if (! point_coveredby_original(geometry::range::front(ring)))
                {
                    ring.is_untouched_outside_original = true;
                }
            }
        }
    }

    inline void block_turns()
    {
        for (typename boost::range_iterator<turn_vector_type>::type it =
            boost::begin(m_turns); it != boost::end(m_turns); ++it)
        {
            buffer_turn_info_type& turn = *it;
            if (! turn.is_turn_traversable)
            {
                // Discard this turn (don't set it to blocked to avoid colocated
                // clusters being discarded afterwards
                turn.discarded = true;
            }
        }
    }

    inline void traverse()
    {
        typedef detail::overlay::traverse
            <
                false, false,
                buffered_ring_collection<buffered_ring<Ring> >,
                buffered_ring_collection<buffered_ring<Ring > >,
                overlay_buffer,
                backtrack_for_buffer
            > traverser;
        std::map<ring_identifier, overlay::ring_turn_info> turn_info_per_ring;

        traversed_rings.clear();
        buffer_overlay_visitor visitor;
        traverser::apply(offsetted_rings, offsetted_rings,
                        m_strategy, m_robust_policy,
                        m_turns, traversed_rings,
                        turn_info_per_ring,
                        m_clusters, visitor);
    }

    inline void reverse()
    {
        for(typename buffered_ring_collection<buffered_ring<Ring> >::iterator it = boost::begin(offsetted_rings);
            it != boost::end(offsetted_rings);
            ++it)
        {
            if (! it->has_intersections())
            {
                std::reverse(it->begin(), it->end());
            }
        }
        for (typename boost::range_iterator<buffered_ring_collection<Ring> >::type
                it = boost::begin(traversed_rings);
                it != boost::end(traversed_rings);
                ++it)
        {
            std::reverse(it->begin(), it->end());
        }
    }

    template <typename GeometryOutput, typename OutputIterator>
    inline OutputIterator assign(OutputIterator out) const
    {
        typedef typename geometry::area_result
            <
                buffered_ring<Ring>, Strategy
            >::type area_result_type;
        typedef detail::overlay::ring_properties
            <
                point_type, area_result_type
            > properties;

        std::map<ring_identifier, properties> selected;

        // Select all rings which do not have any self-intersection
        // Inner rings, for deflate, which do not have intersections, and
        // which are outside originals, are skipped
        // (other ones should be traversed)
        signed_size_type index = 0;
        for(typename buffered_ring_collection<buffered_ring<Ring> >::const_iterator it = boost::begin(offsetted_rings);
            it != boost::end(offsetted_rings);
            ++it, ++index)
        {
            if (! it->has_intersections()
                && ! it->is_untouched_outside_original)
            {
                properties p = properties(*it, m_strategy);
                if (p.valid)
                {
                    ring_identifier id(0, index, -1);
                    selected[id] = p;
                }
            }
        }

        // Select all created rings
        index = 0;
        for (typename boost::range_iterator<buffered_ring_collection<Ring> const>::type
                it = boost::begin(traversed_rings);
                it != boost::end(traversed_rings);
                ++it, ++index)
        {
            properties p = properties(*it, m_strategy);
            if (p.valid)
            {
                ring_identifier id(2, index, -1);
                selected[id] = p;
            }
        }

        detail::overlay::assign_parents<overlay_buffer>(offsetted_rings, traversed_rings,
                selected, m_strategy);
        return detail::overlay::add_rings<GeometryOutput>(selected, offsetted_rings, traversed_rings, out,
                                                          m_strategy);
    }

};


}} // namespace detail::buffer
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_BUFFERED_PIECE_COLLECTION_HPP

/* buffered_piece_collection.hpp
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
*/