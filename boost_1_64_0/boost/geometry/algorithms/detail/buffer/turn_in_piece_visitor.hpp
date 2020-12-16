// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2016, 2018.
// Modifications copyright (c) 2016-2018 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_TURN_IN_PIECE_VISITOR
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_TURN_IN_PIECE_VISITOR


#include <boost/core/ignore_unused.hpp>

#include <boost/range.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/config.hpp>

#include <boost/geometry/arithmetic/dot_product.hpp>
#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/algorithms/comparable_distance.hpp>
#include <boost/geometry/algorithms/equals.hpp>
#include <boost/geometry/algorithms/expand.hpp>
#include <boost/geometry/algorithms/detail/disjoint/point_box.hpp>
#include <boost/geometry/algorithms/detail/disjoint/box_box.hpp>
#include <boost/geometry/algorithms/detail/overlay/segment_identifier.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_turn_info.hpp>
#include <boost/geometry/policies/compare.hpp>
#include <boost/geometry/strategies/buffer.hpp>
#include <boost/geometry/algorithms/detail/buffer/buffer_policies.hpp>

#include <boost/geometry/strategies/cartesian/side_of_intersection.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace buffer
{

struct piece_get_box
{
    template <typename Box, typename Piece>
    static inline void apply(Box& total, Piece const& piece)
    {
        geometry::expand(total, piece.robust_envelope);
    }
};

template <typename DisjointBoxBoxStrategy>
struct piece_ovelaps_box
{
    template <typename Box, typename Piece>
    static inline bool apply(Box const& box, Piece const& piece)
    {
        if (piece.type == strategy::buffer::buffered_flat_end
            || piece.type == strategy::buffer::buffered_concave)
        {
            // Turns cannot be inside a flat end (though they can be on border)
            // Neither we need to check if they are inside concave helper pieces

            // Skip all pieces not used as soon as possible
            return false;
        }

        return ! geometry::detail::disjoint::disjoint_box_box(box, piece.robust_envelope,
                                                              DisjointBoxBoxStrategy());
    }
};

struct turn_get_box
{
    template <typename Box, typename Turn>
    static inline void apply(Box& total, Turn const& turn)
    {
        geometry::expand(total, turn.robust_point);
    }
};

template <typename DisjointPointBoxStrategy>
struct turn_ovelaps_box
{
    template <typename Box, typename Turn>
    static inline bool apply(Box const& box, Turn const& turn)
    {
        return ! geometry::detail::disjoint::disjoint_point_box(turn.robust_point, box,
                                                                DisjointPointBoxStrategy());
    }
};


enum analyse_result
{
    analyse_unknown,
    analyse_continue,
    analyse_disjoint,
    analyse_within,
    analyse_on_original_boundary,
    analyse_on_offsetted,
    analyse_near_offsetted
};

template <typename Point>
inline bool in_box(Point const& previous,
        Point const& current, Point const& point)
{
    // Get its box (TODO: this can be prepared-on-demand later)
    typedef geometry::model::box<Point> box_type;
    box_type box;
    geometry::assign_inverse(box);
    geometry::expand(box, previous);
    geometry::expand(box, current);

    return geometry::covered_by(point, box);
}

template <typename NumericType>
inline bool is_one_sided(NumericType const& left, NumericType const& right)
{
    static NumericType const zero = 0;
    return geometry::math::equals(left, zero)
        || geometry::math::equals(right, zero);
}

template <typename Point, typename DistanceStrategy>
inline bool has_zero_distance_at(Point const& point,
                                 DistanceStrategy const& distance_strategy)
{
    return is_one_sided(distance_strategy.apply(point, point,
            strategy::buffer::buffer_side_left),
        distance_strategy.apply(point, point,
            strategy::buffer::buffer_side_right));
}

// meta-programming-structure defining if to use side-of-intersection
// (only for cartesian / only necessary with rescaling)
template <typename Tag>
struct use_side_of_intersection {};

#if defined(BOOST_GEOMETRY_USE_RESCALING)
// With rescaling, let Cartesian use side-of-intersection
template <>
struct use_side_of_intersection<cartesian_tag> { static bool const value = true; };
#else
template <>
struct use_side_of_intersection<cartesian_tag> { static bool const value = false; };
#endif

template <>
struct use_side_of_intersection<spherical_tag> { static bool const value = false; };

template <>
struct use_side_of_intersection<geographic_tag> { static bool const value = false; };


template <bool UseSideOfIntersection>
struct check_segment {};

// Implementation using side-of-intersection
template <>
struct check_segment<true>
{
    template <typename Point, typename Turn, typename SideStrategy>
    static inline analyse_result apply(Point const& previous,
            Point const& current, Turn const& turn,
            bool from_monotonic,
            SideStrategy const& )
    {
        typedef geometry::model::referring_segment<Point const> segment_type;
        segment_type const p(turn.rob_pi, turn.rob_pj);
        segment_type const q(turn.rob_qi, turn.rob_qj);
        segment_type const r(previous, current);
        int const side = strategy::side::side_of_intersection::apply(p, q, r,
                    turn.robust_point);

        if (side == 0)
        {
            return analyse_on_offsetted;
        }
        if (side == -1 && from_monotonic)
        {
            return analyse_within;
        }
        if (side == 1 && from_monotonic)
        {
            return analyse_disjoint;
        }
        return analyse_continue;
    }
};

template <>
struct check_segment<false>
{
    template <typename Point, typename Turn, typename SideStrategy>
    static inline analyse_result apply(Point const& previous,
            Point const& current, Turn const& turn,
            bool from_monotonic,
            SideStrategy const& side_strategy)
    {
        int const side = side_strategy.apply(previous, current, turn.robust_point);

        if (side == 0)
        {
            // Collinear, only on segment if it is covered by its bbox
            if (in_box(previous, current, turn.robust_point))
            {
                return analyse_on_offsetted;
            }
        }
        else if (side == -1)
        {
            // It is in the triangle right-of the segment where the
            // segment is the hypothenusa. Check if it is close
            // (within rounding-area)
            if (in_box(previous, current, turn.robust_point))
            {
                return analyse_near_offsetted;
            }
            else if (from_monotonic)
            {
                return analyse_within;
            }
        }
        else if (from_monotonic)
        {
            // Left of segment
            return analyse_disjoint;
        }

        // Not monotonic, on left or right side: continue analysing
        return analyse_continue;
    }
};

template <bool UseSideOfIntersection>
class analyse_turn_wrt_point_piece {};

template <>
class analyse_turn_wrt_point_piece<true>
{
public :
    template <typename Turn, typename Piece, typename PointInGeometryStrategy, typename SideStrategy>
    static inline analyse_result apply(Turn const& turn, Piece const& piece,
                                       PointInGeometryStrategy const& ,
                                       SideStrategy const& )
    {
        typedef typename Piece::section_type section_type;
        typedef typename Turn::robust_point_type point_type;
        typedef typename geometry::coordinate_type<point_type>::type coordinate_type;

        typedef geometry::model::referring_segment<point_type const> segment_type;
        segment_type const p(turn.rob_pi, turn.rob_pj);
        segment_type const q(turn.rob_qi, turn.rob_qj);

        BOOST_GEOMETRY_ASSERT(! piece.sections.empty());

        coordinate_type const point_x = geometry::get<0>(turn.robust_point);

        for (std::size_t s = 0; s < piece.sections.size(); s++)
        {
            section_type const& section = piece.sections[s];
            // If point within horizontal range of monotonic section:
            if (! section.duplicate
                && section.begin_index < section.end_index
                && point_x >= geometry::get<min_corner, 0>(section.bounding_box) - 1
                && point_x <= geometry::get<max_corner, 0>(section.bounding_box) + 1)
            {
                for (signed_size_type i = section.begin_index + 1; i <= section.end_index; i++)
                {
                    point_type const& previous = piece.robust_ring[i - 1];
                    point_type const& current = piece.robust_ring[i];


                    // First check if it is in range - if it is not, the
                    // expensive side_of_intersection does not need to be
                    // applied
                    coordinate_type x1 = geometry::get<0>(previous);
                    coordinate_type x2 = geometry::get<0>(current);

                    if (x1 > x2)
                    {
                        std::swap(x1, x2);
                    }

                    if (point_x >= x1 - 1 && point_x <= x2 + 1)
                    {
                        segment_type const r(previous, current);
                        int const side = strategy::side::side_of_intersection::apply(p, q, r,
                                    turn.robust_point);

                        // Sections are monotonic in x-dimension
                        if (side == 1)
                        {
                            // Left on segment
                            return analyse_disjoint;
                        }
                        else if (side == 0)
                        {
                            // Collinear - TODO: check if really on segment
                            return analyse_on_offsetted;
                        }
                    }
                }
            }
        }

        // It is nowhere outside, and not on segment, so it is within
        return analyse_within;
    }

};

template <>
class analyse_turn_wrt_point_piece<false>
{
public :
    template <typename Turn, typename Piece, typename PointInGeometryStrategy, typename SideStrategy>
    static inline analyse_result apply(Turn const& turn, Piece const& piece,
                                       PointInGeometryStrategy const& point_in_geometry_strategy,
                                       SideStrategy const& side_strategy)
    {
        typedef typename Piece::section_type section_type;
        typedef typename Turn::robust_point_type point_type;
        typedef typename geometry::coordinate_type<point_type>::type coordinate_type;

        typename PointInGeometryStrategy::state_type state;

        BOOST_GEOMETRY_ASSERT(! piece.sections.empty());

        coordinate_type const point_x = geometry::get<0>(turn.robust_point);

        for (std::size_t s = 0; s < piece.sections.size(); s++)
        {
            section_type const& section = piece.sections[s];
            // If point within horizontal range of monotonic section:
            if (! section.duplicate
                && section.begin_index < section.end_index
                && point_x >= geometry::get<min_corner, 0>(section.bounding_box) - 1
                && point_x <= geometry::get<max_corner, 0>(section.bounding_box) + 1)
            {
                for (signed_size_type i = section.begin_index + 1; i <= section.end_index; i++)
                {
                    point_type const& previous = piece.robust_ring[i - 1];
                    point_type const& current = piece.robust_ring[i];

                    analyse_result code = check_segment<false>::apply(previous, current, turn, false, side_strategy);
                    if (code != analyse_continue)
                    {
                        return code;
                    }

                    // Get the state (to determine it is within), we don't have
                    // to cover the on-segment case (covered above)
                    point_in_geometry_strategy.apply(turn.robust_point, previous, current, state);
                }
            }
        }

        int const code = point_in_geometry_strategy.result(state);
        if (code == 1)
        {
            return analyse_within;
        }
        else if (code == -1)
        {
            return analyse_disjoint;
        }

        // Should normally not occur - on-segment is covered
        return analyse_unknown;
    }

};

template <bool UseSideOfIntersection>
struct check_helper_segment {};

template <>
struct check_helper_segment<true>
{
    template <typename Point, typename Turn,  typename SideStrategy>
    static inline analyse_result apply(Point const& s1,
                Point const& s2, Turn const& turn,
                bool is_original,
                analyse_result result_for_original,
                Point const& offsetted,
                SideStrategy const& )
    {
        boost::ignore_unused(offsetted, is_original);

        typedef geometry::model::referring_segment<Point const> segment_type;
        segment_type const p(turn.rob_pi, turn.rob_pj);
        segment_type const q(turn.rob_qi, turn.rob_qj);
        segment_type const r(s1, s2);
        int const side = strategy::side::side_of_intersection::apply(p, q, r,
                    turn.robust_point);

        if (side == 1)
        {
            // left of segment
            return analyse_disjoint;
        }
        else if (side == 0)
        {
            // If is collinear, either on segment or before/after
            typedef geometry::model::box<Point> box_type;

            box_type box;
            geometry::assign_inverse(box);
            geometry::expand(box, s1);
            geometry::expand(box, s2);

            if (geometry::covered_by(turn.robust_point, box))
            {
                return result_for_original;
            }

            // It is collinear but not on the segment. Because these
            // segments are convex, it is outside
            // Unless the offsetted ring is collinear or concave w.r.t.
            // helper-segment but that scenario is not yet supported
            return analyse_disjoint;
        }

        // right of segment
        return analyse_continue;
    }

};

template <>
struct check_helper_segment<false>
{
    template <typename Point, typename Turn, typename SideStrategy>
    static inline analyse_result apply(Point const& s1,
                Point const& s2, Turn const& turn,
                bool is_original,
                analyse_result result_for_original,
                Point const& offsetted,
                SideStrategy const& side_strategy)
    {
        switch(side_strategy.apply(s1, s2, turn.robust_point))
        {
            case 1 :
                return analyse_disjoint; // left of segment
            case 0 :
                {
                    // If is collinear, either on segment or before/after
                    typedef geometry::model::box<Point> box_type;

                    box_type box;
                    geometry::assign_inverse(box);
                    geometry::expand(box, s1);
                    geometry::expand(box, s2);

                    if (geometry::covered_by(turn.robust_point, box))
                    {
                        // It is on the segment
                        if (! is_original
                            && geometry::comparable_distance(turn.robust_point, offsetted) <= 1)
                        {
                            // It is within, and close to the offsetted-boundary,
                            // take any rounding-issues into account
                            return analyse_near_offsetted;
                        }

                        // Points on helper-segments are considered as within
                        // Points on original boundary are processed differently
                        return result_for_original;
                    }

                    // It is collinear but not on the segment. Because these
                    // segments are convex, it is outside
                    // Unless the offsetted ring is collinear or concave w.r.t.
                    // helper-segment but that scenario is not yet supported
                    return analyse_disjoint;
                }
                break;
        }

        // right of segment
        return analyse_continue;
    }
};

template <bool UseSideOfIntersection>
class analyse_turn_wrt_piece
{
    template
    <
        typename Turn,
        typename Piece,
        typename DistanceStrategy,
        typename SideStrategy
    >
    static inline analyse_result
    check_helper_segments(Turn const& turn, Piece const& piece,
                          DistanceStrategy const& distance_strategy,
                          SideStrategy const& side_strategy)
    {
        typedef typename Turn::robust_point_type point_type;
        geometry::equal_to<point_type> comparator;

        point_type points[4];

        signed_size_type helper_count = static_cast<signed_size_type>(piece.robust_ring.size())
                                            - piece.offsetted_count;
        if (helper_count == 4)
        {
            for (int i = 0; i < 4; i++)
            {
                points[i] = piece.robust_ring[piece.offsetted_count + i];
            }

            //      3--offsetted outline--0
            //      |                     |
            // left |                     | right
            //      |                     |
            //      2===>==original===>===1

        }
        else if (helper_count == 3)
        {
            // Triangular piece, assign points but assign second twice
            for (int i = 0; i < 4; i++)
            {
                int index = i < 2 ? i : i - 1;
                points[i] = piece.robust_ring[piece.offsetted_count + index];
            }
        }
        else
        {
            // Some pieces (e.g. around points) do not have helper segments.
            // Others should have 3 (join) or 4 (side)
            return analyse_continue;
        }

        // If a turn is located on the original, it is considered as within,
        // unless it is at a flat start or end, or the buffer (at that point)
        // is one-sided (zero-distance)
        bool const one_sided = has_zero_distance_at(turn.point, distance_strategy);

        analyse_result const result_for_original
                = one_sided || piece.is_flat_end || piece.is_flat_start
                ? analyse_on_original_boundary
                : analyse_within;

        // First check point-equality
        point_type const& point = turn.robust_point;
        if (comparator(point, points[0]) || comparator(point, points[3]))
        {
            return analyse_on_offsetted;
        }
        if (comparator(point, points[1]))
        {
            // On original, with right corner of piece
            return result_for_original;
        }
        if (comparator(point, points[2]))
        {
            // On original, with left corner of piece
            return result_for_original;
        }

        // Right side of the piece (never an original)
        analyse_result result
            = check_helper_segment<UseSideOfIntersection>::apply(points[0], points[1], turn,
                    false, analyse_within, points[0], side_strategy);
        if (result != analyse_continue)
        {
            return result;
        }

        // Left side of the piece (never an original)
        result = check_helper_segment<UseSideOfIntersection>::apply(points[2], points[3], turn,
                    false, analyse_within, points[3], side_strategy);
        if (result != analyse_continue)
        {
            return result;
        }

        // Side of the piece at side of original geometry
        // (here flat start/end will result in within)
        if (! comparator(points[1], points[2]))
        {
            result = check_helper_segment<UseSideOfIntersection>::apply(points[1],
                    points[2], turn, true,
                    one_sided ? analyse_on_original_boundary : analyse_within,
                    point, side_strategy);
            if (result != analyse_continue)
            {
                return result;
            }
        }

        // We are within the \/ or |_| shaped piece, where the top is the
        // offsetted ring.
        if (! geometry::covered_by(point, piece.robust_offsetted_envelope))
        {
            // Not in offsetted-area. This makes a cheap check possible
            switch(side_strategy.apply(points[3], points[0], point))
            {
                case 1 : return analyse_disjoint;
                case -1 : return analyse_within;
                case 0 : return analyse_disjoint;
            }
        }

        return analyse_continue;
    }

    template <typename Turn, typename Piece, typename Compare,  typename SideStrategy>
    static inline analyse_result check_monotonic(Turn const& turn, Piece const& piece, Compare const& compare, SideStrategy const& side_strategy)
    {
        typedef typename Piece::piece_robust_ring_type ring_type;
        typedef typename ring_type::const_iterator it_type;
        it_type end = piece.robust_ring.begin() + piece.offsetted_count;
        it_type it = std::lower_bound(piece.robust_ring.begin(),
                    end,
                    turn.robust_point,
                    compare);

        if (it != end
            && it != piece.robust_ring.begin())
        {
            // iterator points to point larger than point
            // w.r.t. specified direction, and prev points to a point smaller
            // We now know if it is inside/outside
            it_type prev = it - 1;
            return check_segment<UseSideOfIntersection>::apply(*prev, *it, turn, true, side_strategy);
        }
        return analyse_continue;
    }

public :
    template
    <
        typename Turn,
        typename Piece,
        typename DistanceStrategy,
        typename SideStrategy
    >
    static inline analyse_result apply(Turn const& turn, Piece const& piece,
                                       DistanceStrategy const& distance_strategy,
                                       SideStrategy const& side_strategy)
    {
        typedef typename Turn::robust_point_type point_type;
        analyse_result code = check_helper_segments(turn, piece, distance_strategy, side_strategy);
        if (code != analyse_continue)
        {
            return code;
        }

        geometry::equal_to<point_type> comparator;

        if (piece.offsetted_count > 8)
        {
            // If the offset contains some points and is monotonic, we try
            // to avoid walking all points linearly.
            // We try it only once.
            if (piece.is_monotonic_increasing[0])
            {
                code = check_monotonic(turn, piece, geometry::less<point_type, 0>(), side_strategy);
                if (code != analyse_continue) return code;
            }
            else if (piece.is_monotonic_increasing[1])
            {
                code = check_monotonic(turn, piece, geometry::less<point_type, 1>(), side_strategy);
                if (code != analyse_continue) return code;
            }
            else if (piece.is_monotonic_decreasing[0])
            {
                code = check_monotonic(turn, piece, geometry::greater<point_type, 0>(), side_strategy);
                if (code != analyse_continue) return code;
            }
            else if (piece.is_monotonic_decreasing[1])
            {
                code = check_monotonic(turn, piece, geometry::greater<point_type, 1>(), side_strategy);
                if (code != analyse_continue) return code;
            }
        }

        // It is small or not monotonic, walk linearly through offset
        // TODO: this will be combined with winding strategy

        for (signed_size_type i = 1; i < piece.offsetted_count; i++)
        {
            point_type const& previous = piece.robust_ring[i - 1];
            point_type const& current = piece.robust_ring[i];

            // The robust ring can contain duplicates
            // (on which any side or side-value would return 0)
            if (! comparator(previous, current))
            {
                code = check_segment<UseSideOfIntersection>::apply(previous, current, turn, false, side_strategy);
                if (code != analyse_continue)
                {
                    return code;
                }
            }
        }

        return analyse_unknown;
    }

};

// Helper Structure, of which the apply method returns a side value in {-1, 0, 1}
template <bool UseSideOfIntersection>
struct turn_in_piece {};

template <>
struct turn_in_piece<true>
{

private :
    template <typename Turn, typename Piece>
    static inline int in_convex_piece(Turn const& turn, Piece const& piece)
    {
        typedef typename Turn::robust_point_type point_type;
        typedef typename Piece::piece_robust_ring_type ring_type;
        typedef geometry::model::referring_segment<point_type const> segment;

        segment const p(turn.rob_pi, turn.rob_pj);
        segment const q(turn.rob_qi, turn.rob_qj);

        typedef typename boost::range_iterator<ring_type const>::type iterator_type;
        iterator_type it = boost::begin(piece.robust_ring);
        iterator_type end = boost::end(piece.robust_ring);

        // A robust ring is always closed, and always clockwise
        for (iterator_type previous = it++; it != end; ++previous, ++it)
        {
            geometry::equal_to<point_type> comparator;
            if (comparator(*previous, *it))
            {
                // Points are the same
                continue;
            }

            segment r(*previous, *it);

            int const side = strategy::side::side_of_intersection::apply(p, q, r,
                        turn.robust_point);

            if (side == 1)
            {
                // IP is left of segment, so it is outside
                return -1; // outside
            }
            else if (side == 0)
            {
                // IP is collinear with segment. TODO: we should analyze this further
                // For now we use the fallback point
                if (in_box(*previous, *it, turn.robust_point))
                {
                    return 0;
                }
                else
                {
                    return -1; // outside
                }
            }
        }
        return 1; // inside
    }

public :

    template <typename Turn, typename Piece, typename Strategy>
    static inline int apply(Turn const& turn, Piece const& piece,
            Strategy const& strategy)
    {
        if (piece.is_convex)
        {
            return in_convex_piece(turn, piece);
        }
        else
        {
            // side-of-intersection only supported for convex pieces
            // Call point_in_geometry, a performance-bottleneck
            // TODO: might be replaced by extending analysing piece
            return detail::within::point_in_geometry(turn.robust_point,
                piece.robust_ring, strategy);
        }
    }
};

template <>
struct turn_in_piece<false>
{
public :

    template <typename Turn, typename Piece, typename Strategy>
    static inline int apply(Turn const& turn, Piece const& piece,
            Strategy const& strategy)
    {
        return detail::within::point_in_geometry(turn.robust_point,
            piece.robust_ring, strategy);
    }
};

template
<
    typename CsTag,
    typename Turns,
    typename Pieces,
    typename DistanceStrategy,
    typename PointInGeometryStrategy,
    typename SideStrategy

>
class turn_in_piece_visitor
{
    Turns& m_turns; // because partition is currently operating on const input only
    Pieces const& m_pieces; // to check for piece-type
    DistanceStrategy const& m_distance_strategy; // to check if point is on original
    PointInGeometryStrategy const& m_point_in_geometry_strategy;
    SideStrategy const& m_side_strategy;

    template <typename Operation, typename Piece>
    inline bool skip(Operation const& op, Piece const& piece) const
    {
        if (op.piece_index == piece.index)
        {
            return true;
        }
        Piece const& pc = m_pieces[op.piece_index];
        if (pc.left_index == piece.index || pc.right_index == piece.index)
        {
            if (pc.type == strategy::buffer::buffered_flat_end)
            {
                // If it is a flat end, don't compare against its neighbor:
                // it will always be located on one of the helper segments
                return true;
            }
            if (pc.type == strategy::buffer::buffered_concave)
            {
                // If it is concave, the same applies: the IP will be
                // located on one of the helper segments
                return true;
            }
        }

        return false;
    }


public:

    inline turn_in_piece_visitor(Turns& turns, Pieces const& pieces,
                                 DistanceStrategy const& distance_strategy,
                                 PointInGeometryStrategy const& strategy,
                                 SideStrategy const& side_strategy)
        : m_turns(turns)
        , m_pieces(pieces)
        , m_distance_strategy(distance_strategy)
        , m_point_in_geometry_strategy(strategy)
        , m_side_strategy(side_strategy)
    {}

    template <typename Turn, typename Piece>
    inline bool apply(Turn const& turn, Piece const& piece, bool first = true)
    {
        boost::ignore_unused(first);

        if (turn.count_within > 0)
        {
            // Already inside - no need to check again
            return true;
        }

        if (piece.type == strategy::buffer::buffered_flat_end
            || piece.type == strategy::buffer::buffered_concave)
        {
            // Turns cannot be located within flat-end or concave pieces
            return true;
        }

        if (! geometry::covered_by(turn.robust_point, piece.robust_envelope))
        {
            // Easy check: if the turn is not in the envelope, we can safely return
            return true;
        }

        if (skip(turn.operations[0], piece) || skip(turn.operations[1], piece))
        {
            return true;
        }

        // TODO: mutable_piece to make some on-demand preparations in analyse
        Turn& mutable_turn = m_turns[turn.turn_index];

        if (piece.type == geometry::strategy::buffer::buffered_point)
        {
            // Optimization for buffer around points: if distance from center
            // is not between min/max radius, the result is clear
            typedef typename default_comparable_distance_result
                <
                    typename Turn::robust_point_type
                >::type distance_type;

            distance_type const cd
                = geometry::comparable_distance(piece.robust_center,
                        turn.robust_point);

            if (cd < piece.robust_min_comparable_radius)
            {
                mutable_turn.count_within++;
                return true;
            }
            if (cd > piece.robust_max_comparable_radius)
            {
                return true;
            }
        }

        static const bool use_soi = use_side_of_intersection<CsTag>::value;
        boost::ignore_unused(use_soi);

        analyse_result const analyse_code =
            piece.type == geometry::strategy::buffer::buffered_point
                ? analyse_turn_wrt_point_piece<use_soi>::apply(turn, piece, m_point_in_geometry_strategy, m_side_strategy)
                : analyse_turn_wrt_piece<use_soi>::apply(turn, piece, m_distance_strategy, m_side_strategy);

        switch(analyse_code)
        {
            case analyse_disjoint :
            case analyse_on_offsetted :
            case analyse_on_original_boundary :
                return true;
            case analyse_within :
                mutable_turn.count_within++;
                return true;
            case analyse_near_offsetted :
                mutable_turn.count_within_near_offsetted++;
                return true;
            default :
                break;
        }

        int const geometry_code = turn_in_piece<use_soi>::apply(turn, piece,
                m_point_in_geometry_strategy);

        if (geometry_code == 1)
        {
            mutable_turn.count_within++;
        }

        return true;
    }
};


}} // namespace detail::buffer
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_TURN_IN_PIECE_VISITOR

/* turn_in_piece_visitor.hpp
LiCKioi4g6CCCyBuKO4rRdwVnTn3v/PmTu/LUvHTft/7mjMzZ86cOXPmnDP3LKtN/f9uyydea43Olpg8348Y/xuCOomfMHcMNYTn9Ta+tb4B62CUoeejdh3cLHUVeeg8iYrXoj+0CJ3jJ3IXTDyiTerHNNH161A0Y4uiabqKNBh/qSxztnWz0WXU+uSshuJcarmJ3fREtN/NJs7Ra/TzzZXmLAzq3W90Tjokec3ZFuh8oAH3bRie0Dvlg79R920Maf7Ikwd/8U3gv03Zx72L+GfiXQ1SR7FJnmMcq76jPbMhPD94VkN4vv5sKcPhRO9juNstBp7/mF/kGTc8hw3PEcVzWPH8PuRMGLnfdJL+JunT2/Ybhxw/UfOn3UaOC4wcqUAO4CAH5kZ0L7ixCSorcgyZbPDn3e/HenheuXdwYAbrYb2X3yyLLVr2EeRQJ+jD+YTrVH94H/RRCOoGGnsv5V6ji9sIX+SJOy5MH7vI8LSx6eeC53VqHa7vbfnAfFmXo0yVX+GZr8YXDH6BpCGP6MHcm2LkwTvuQm/H6ssaRIcyh9A6qYjQycuNTuz4/EqDf8zEH19t8HkzFl9u8AWDf50Zd2za5l9g8r8psHGc319WibY3Nn6l0ImckXRvUb726XSu5ilEUwOdLH6Kr7O3KpnyDdZ2KR5m8O+z8TDl6/8c4Br8Nn6nj+N+In7g3cYPvMfY/ntNeZ8zdvG+AI+8Vt7rFP66CDv8YIPEJPEtHen5klbf46NjvTeAx0OIq/7A7KHYr+IqGk9gweu5ho0BftzMRWyM8pMGb2OMnzJ1PEvXEWn9Hd/GbT5j+Nu47mdVmz9kYiWfd7hy911D79P9YkP0N4evYO31JcJr2ur5pWlvN7Rk+yVpv9IQbou1EuOSNOomaelbX9EymL719UBHoLOxrXukj/rtt6Y6erz6psxLHJ3Vkfz0vOTbOo8re/o894XzkM6mz/MdqSNkM9+svmv67u/mh/dVWfofiD/SdTX7fQxNVKzux0a3cl+U0e1PhE54RdL9LKgnzhRZuX8RyAQ8w61Mv2oIf3eyffY3Bm/77O+gy54aPz3fxM3PfJL+VoU0+HGe6+2bayIz8Ih5aJn/qOdU1Q7vYjF2ffFnRbdvCrq/qjqe5+bX5l02s06JkumfxvdsWWDubxZZ2MZKy1LWCDp8FytFN6dRf3OMlumIxnDbWZnmqrJumUKmIxWf87D20HyOJrwu93LzLcmW+4TG8D23fzjFx9+zwMdXBXiczbD4apP/yaf5+G8Dv9Dkt/jjTP470d4eYvM1Jr/FLzb56zDOrgb/JSa/xZ9o8j8DfeQ5x/v4pSa/xZ9i8M88PvxW26mG/92Q/+sof7nJb/ErTH70B1lbnW7yW/zTTf57gScbdPiVJr/F15r8sDdZy9WZ/Ba/plF/s6ZY1RKVxlkWSZs5+svr1duWikejKpNhdm6xrhFx8+PD88QNjeF5RjPSBEfZfr5fmnytJl+b6qut9f6vk36bEacgetdXOxrDfmiT2U/RBb7flzke6q7OgNr7NbpRtw6cSbX0jYa+J5C9UspAmbrOmHubeVi/kZ956Hn0AGTZBFlwjszljVd7kta6bYmQ+wqnG3P+UXyqs2nYgZad7gNG+dx+eg39LEpresI7+mcrnm3GtjbBtmKqzpzP2lZc4TmPxY8YnT0S6BT4BNrjUf2ND/QM225iPuMBP8yTrQ3tJrzEQ6rDa4qUyRvg+X8XD2E8voPiWy3Spi/im7DW1xnQV1bptD9oJ/P9Na/kOCNCZ3sUnvNY/D7I+RX0kzvnS1rk1GunK+fr+Z8v0zITM7+4Mchj6go/99uI+dkBJeddJx46P3tBoAs=
*/