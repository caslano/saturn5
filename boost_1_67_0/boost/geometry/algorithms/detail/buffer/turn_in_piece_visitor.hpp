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
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
*/