// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2017, 2019.
// Modifications copyright (c) 2017, 2019 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_SORT_BY_SIDE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_SORT_BY_SIDE_HPP

#include <algorithm>
#include <map>
#include <vector>

#include <boost/geometry/algorithms/detail/overlay/approximately_equals.hpp>
#include <boost/geometry/algorithms/detail/overlay/copy_segment_point.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_ring.hpp>
#include <boost/geometry/algorithms/detail/direction_code.hpp>
#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>

#include <boost/geometry/util/condition.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_coordinate_type.hpp>
#include <boost/geometry/util/select_most_precise.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay { namespace sort_by_side
{

enum direction_type { dir_unknown = -1, dir_from = 0, dir_to = 1 };

typedef signed_size_type rank_type;


// Point-wrapper, adding some properties
template <typename Point>
struct ranked_point
{
    ranked_point()
        : rank(0)
        , turn_index(-1)
        , operation_index(-1)
        , direction(dir_unknown)
        , count_left(0)
        , count_right(0)
        , operation(operation_none)
    {}

    ranked_point(Point const& p, signed_size_type ti, int oi,
                 direction_type d, operation_type op, segment_identifier const& si)
        : point(p)
        , rank(0)
        , zone(-1)
        , turn_index(ti)
        , operation_index(oi)
        , direction(d)
        , count_left(0)
        , count_right(0)
        , operation(op)
        , seg_id(si)
    {}

    using point_type = Point;

    Point point;
    rank_type rank;
    signed_size_type zone; // index of closed zone, in uu turn there would be 2 zones
    signed_size_type turn_index;
    int operation_index; // 0,1
    direction_type direction;
    std::size_t count_left;
    std::size_t count_right;
    operation_type operation;
    segment_identifier seg_id;
};

struct less_by_turn_index
{
    template <typename T>
    inline bool operator()(const T& first, const T& second) const
    {
        return first.turn_index == second.turn_index
            ? first.index < second.index
            : first.turn_index < second.turn_index
            ;
    }
};

struct less_by_index
{
    template <typename T>
    inline bool operator()(const T& first, const T& second) const
    {
        // Length might be considered too
        // First order by from/to
        if (first.direction != second.direction)
        {
            return first.direction < second.direction;
        }
        // Then by turn index
        if (first.turn_index != second.turn_index)
        {
            return first.turn_index < second.turn_index;
        }
        // This can also be the same (for example in buffer), but seg_id is
        // never the same
        return first.seg_id < second.seg_id;
    }
};

struct less_false
{
    template <typename T>
    inline bool operator()(const T&, const T& ) const
    {
        return false;
    }
};

template <typename Point, typename SideStrategy, typename LessOnSame, typename Compare>
struct less_by_side
{
    less_by_side(const Point& p1, const Point& p2, SideStrategy const& strategy)
        : m_origin(p1)
        , m_turn_point(p2)
        , m_strategy(strategy)
    {}

    template <typename T>
    inline bool operator()(const T& first, const T& second) const
    {
        typedef typename SideStrategy::cs_tag cs_tag;

        LessOnSame on_same;
        Compare compare;

        int const side_first = m_strategy.apply(m_origin, m_turn_point, first.point);
        int const side_second = m_strategy.apply(m_origin, m_turn_point, second.point);

        if (side_first == 0 && side_second == 0)
        {
            // Both collinear. They might point into different directions: <------*------>
            // If so, order the one going backwards as the very first.

            int const first_code = direction_code<cs_tag>(m_origin, m_turn_point, first.point);
            int const second_code = direction_code<cs_tag>(m_origin, m_turn_point, second.point);

            // Order by code, backwards first, then forward.
            return first_code != second_code
                ? first_code < second_code
                : on_same(first, second)
                ;
        }
        else if (side_first == 0
                && direction_code<cs_tag>(m_origin, m_turn_point, first.point) == -1)
        {
            // First collinear and going backwards.
            // Order as the very first, so return always true
            return true;
        }
        else if (side_second == 0
            && direction_code<cs_tag>(m_origin, m_turn_point, second.point) == -1)
        {
            // Second is collinear and going backwards
            // Order as very last, so return always false
            return false;
        }

        // They are not both collinear

        if (side_first != side_second)
        {
            return compare(side_first, side_second);
        }

        // They are both left, both right, and/or both collinear (with each other and/or with p1,p2)
        // Check mutual side
        int const side_second_wrt_first = m_strategy.apply(m_turn_point, first.point, second.point);

        if (side_second_wrt_first == 0)
        {
            return on_same(first, second);
        }

        int const side_first_wrt_second = m_strategy.apply(m_turn_point, second.point, first.point);
        if (side_second_wrt_first != -side_first_wrt_second)
        {
            // (FP) accuracy error in side calculation, the sides are not opposite.
            // In that case they can be handled as collinear.
            // If not, then the sort-order might not be stable.
            return on_same(first, second);
        }

        // Both are on same side, and not collinear
        // Union: return true if second is right w.r.t. first, so -1,
        // so other is 1. union has greater as compare functor
        // Intersection: v.v.
        return compare(side_first_wrt_second, side_second_wrt_first);
    }

private :
    Point const& m_origin;
    Point const& m_turn_point;
    SideStrategy const& m_strategy;
};

// Sorts vectors in counter clockwise order (by default)
template
<
    bool Reverse1,
    bool Reverse2,
    overlay_type OverlayType,
    typename Point,
    typename SideStrategy,
    typename Compare
>
struct side_sorter
{
    typedef ranked_point<Point> rp;

private :
    struct include_union
    {
        inline bool operator()(rp const& ranked_point) const
        {
            // New candidate if there are no polygons on left side,
            // but there are on right side
            return ranked_point.count_left == 0
                && ranked_point.count_right > 0;
        }
    };

    struct include_intersection
    {
        inline bool operator()(rp const& ranked_point) const
        {
            // New candidate if there are two polygons on right side,
            // and less on the left side
            return ranked_point.count_left < 2
                && ranked_point.count_right >= 2;
        }
    };

public :
    side_sorter(SideStrategy const& strategy)
        : m_origin_count(0)
        , m_origin_segment_distance(0)
        , m_strategy(strategy)
    {}

    template <typename Operation>
    void add_segment_from(signed_size_type turn_index, int op_index,
            Point const& point_from,
            Operation const& op,
            bool is_origin)
    {
        m_ranked_points.push_back(rp(point_from, turn_index, op_index,
                                     dir_from, op.operation, op.seg_id));
        if (is_origin)
        {
            m_origin = point_from;
            m_origin_count++;
        }
    }

    template <typename Operation>
    void add_segment_to(signed_size_type turn_index, int op_index,
            Point const& point_to,
            Operation const& op)
    {
        m_ranked_points.push_back(rp(point_to, turn_index, op_index,
                                     dir_to, op.operation, op.seg_id));
    }

    template <typename Operation>
    void add_segment(signed_size_type turn_index, int op_index,
            Point const& point_from, Point const& point_to,
            Operation const& op, bool is_origin)
    {
        add_segment_from(turn_index, op_index, point_from, op, is_origin);
        add_segment_to(turn_index, op_index, point_to, op);
    }

    template <typename Operation, typename Geometry1, typename Geometry2>
    static Point walk_over_ring(Operation const& op, int offset,
            Geometry1 const& geometry1,
            Geometry2 const& geometry2)
    {
        Point point;
        geometry::copy_segment_point<Reverse1, Reverse2>(geometry1, geometry2, op.seg_id, offset, point);
        return point;
    }

    template <typename Turn, typename Operation, typename Geometry1, typename Geometry2>
    Point add(Turn const& turn, Operation const& op, signed_size_type turn_index, int op_index,
            Geometry1 const& geometry1,
            Geometry2 const& geometry2,
            bool is_origin)
    {
        Point point_from, point2, point3;
        geometry::copy_segment_points<Reverse1, Reverse2>(geometry1, geometry2,
                op.seg_id, point_from, point2, point3);
        Point point_to = op.fraction.is_one() ? point3 : point2;

        // If the point is in the neighbourhood (the limit is arbitrary),
        // then take a point (or more) further back.
        // The limit of offset avoids theoretical infinite loops.
        // In practice it currently walks max 1 point back in all cases.
        // Use the coordinate type, but if it is too small (e.g. std::int16), use a double
        using ct_type = typename geometry::select_most_precise
            <
                typename geometry::coordinate_type<Point>::type,
                double
            >::type;

        ct_type const tolerance = 1000000000;

        int offset = 0;
        while (approximately_equals(point_from, turn.point, tolerance)
               && offset > -10)
        {
            point_from = walk_over_ring(op, --offset, geometry1, geometry2);
        }

        // Similarly for the point_to, walk forward
        offset = 0;
        while (approximately_equals(point_to, turn.point, tolerance)
               && offset < 10)
        {
            point_to = walk_over_ring(op, ++offset, geometry1, geometry2);
        }

        add_segment(turn_index, op_index, point_from, point_to, op, is_origin);

        return point_from;
    }

    template <typename Turn, typename Operation, typename Geometry1, typename Geometry2>
    void add(Turn const& turn,
             Operation const& op, signed_size_type turn_index, int op_index,
            segment_identifier const& departure_seg_id,
            Geometry1 const& geometry1,
            Geometry2 const& geometry2,
            bool is_departure)
    {
        Point potential_origin = add(turn, op, turn_index, op_index, geometry1, geometry2, false);

        if (is_departure)
        {
            bool const is_origin
                    = op.seg_id.source_index == departure_seg_id.source_index
                    && op.seg_id.ring_index == departure_seg_id.ring_index
                    && op.seg_id.multi_index == departure_seg_id.multi_index;

            if (is_origin)
            {
                signed_size_type const sd
                        = departure_seg_id.source_index == 0
                          ? segment_distance(geometry1, departure_seg_id, op.seg_id)
                          : segment_distance(geometry2, departure_seg_id, op.seg_id);

                if (m_origin_count == 0 || sd < m_origin_segment_distance)
                {
                    m_origin = potential_origin;
                    m_origin_segment_distance = sd;
                }
                m_origin_count++;
            }
        }
    }

    void apply(Point const& turn_point)
    {
        // We need three compare functors:
        // 1) to order clockwise (union) or counter clockwise (intersection)
        // 2) to order by side, resulting in unique ranks for all points
        // 3) to order by side, resulting in non-unique ranks
        //    to give colinear points

        // Sort by side and assign rank
        less_by_side<Point, SideStrategy, less_by_index, Compare> less_unique(m_origin, turn_point, m_strategy);
        less_by_side<Point, SideStrategy, less_false, Compare> less_non_unique(m_origin, turn_point, m_strategy);

        std::sort(m_ranked_points.begin(), m_ranked_points.end(), less_unique);

        std::size_t colinear_rank = 0;
        for (std::size_t i = 0; i < m_ranked_points.size(); i++)
        {
            if (i > 0
                && less_non_unique(m_ranked_points[i - 1], m_ranked_points[i]))
            {
                // It is not collinear
                colinear_rank++;
            }

            m_ranked_points[i].rank = colinear_rank;
        }
    }

    void find_open_by_piece_index()
    {
        // For buffers, use piece index
        std::set<signed_size_type> handled;

        for (std::size_t i = 0; i < m_ranked_points.size(); i++)
        {
            const rp& ranked = m_ranked_points[i];
            if (ranked.direction != dir_from)
            {
                continue;
            }

            signed_size_type const& index = ranked.seg_id.piece_index;
            if (handled.count(index) > 0)
            {
                continue;
            }
            find_polygons_for_source<&segment_identifier::piece_index>(index, i);
            handled.insert(index);
        }
    }

    void find_open_by_source_index()
    {
        // Check for source index 0 and 1
        bool handled[2] = {false, false};
        for (std::size_t i = 0; i < m_ranked_points.size(); i++)
        {
            const rp& ranked = m_ranked_points[i];
            if (ranked.direction != dir_from)
            {
                continue;
            }

            signed_size_type const& index = ranked.seg_id.source_index;
            if (index < 0 || index > 1 || handled[index])
            {
                continue;
            }
            find_polygons_for_source<&segment_identifier::source_index>(index, i);
            handled[index] = true;
        }
    }

    void find_open()
    {
        if (BOOST_GEOMETRY_CONDITION(OverlayType == overlay_buffer))
        {
            find_open_by_piece_index();
        }
        else
        {
            find_open_by_source_index();
        }
    }

    void reverse()
    {
        if (m_ranked_points.empty())
        {
            return;
        }

        std::size_t const last = 1 + m_ranked_points.back().rank;

        // Move iterator after rank==0
        bool has_first = false;
        typename container_type::iterator it = m_ranked_points.begin() + 1;
        for (; it != m_ranked_points.end() && it->rank == 0; ++it)
        {
            has_first = true;
        }

        if (has_first)
        {
            // Reverse first part (having rank == 0), if any,
            // but skip the very first row
            std::reverse(m_ranked_points.begin() + 1, it);
            for (typename container_type::iterator fit = m_ranked_points.begin();
                 fit != it; ++fit)
            {
                BOOST_ASSERT(fit->rank == 0);
            }
        }

        // Reverse the rest (main rank > 0)
        std::reverse(it, m_ranked_points.end());
        for (; it != m_ranked_points.end(); ++it)
        {
            BOOST_ASSERT(it->rank > 0);
            it->rank = last - it->rank;
        }
    }

    bool has_origin() const
    {
        return m_origin_count > 0;
    }

//private :

    typedef std::vector<rp> container_type;
    container_type m_ranked_points;
    Point m_origin;
    std::size_t m_origin_count;
    signed_size_type m_origin_segment_distance;
    SideStrategy m_strategy;

private :

    //! Check how many open spaces there are
    template <typename Include>
    inline std::size_t open_count(Include const& include_functor) const
    {
        std::size_t result = 0;
        rank_type last_rank = 0;
        for (std::size_t i = 0; i < m_ranked_points.size(); i++)
        {
            rp const& ranked_point = m_ranked_points[i];

            if (ranked_point.rank > last_rank
                && ranked_point.direction == sort_by_side::dir_to
                && include_functor(ranked_point))
            {
                result++;
                last_rank = ranked_point.rank;
            }
        }
        return result;
    }

    std::size_t move(std::size_t index) const
    {
        std::size_t const result = index + 1;
        return result >= m_ranked_points.size() ? 0 : result;
    }

    //! member is pointer to member (source_index or multi_index)
    template <signed_size_type segment_identifier::*Member>
    std::size_t move(signed_size_type member_index, std::size_t index) const
    {
        std::size_t result = move(index);
        while (m_ranked_points[result].seg_id.*Member != member_index)
        {
            result = move(result);
        }
        return result;
    }

    void assign_ranks(rank_type min_rank, rank_type max_rank, int side_index)
    {
        for (std::size_t i = 0; i < m_ranked_points.size(); i++)
        {
            rp& ranked = m_ranked_points[i];
            // Suppose there are 8 ranks, if min=4,max=6: assign 4,5,6
            // if min=5,max=2: assign from 5,6,7,1,2
            bool const in_range
                = max_rank >= min_rank
                ? ranked.rank >= min_rank && ranked.rank <= max_rank
                : ranked.rank >= min_rank || ranked.rank <= max_rank
                ;

            if (in_range)
            {
                if (side_index == 1)
                {
                    ranked.count_left++;
                }
                else if (side_index == 2)
                {
                    ranked.count_right++;
                }
            }
        }
    }

    template <signed_size_type segment_identifier::*Member>
    void find_polygons_for_source(signed_size_type the_index,
                std::size_t start_index)
    {
        bool in_polygon = true; // Because start_index is "from", arrives at the turn
        rp const& start_rp = m_ranked_points[start_index];
        rank_type last_from_rank = start_rp.rank;
        rank_type previous_rank = start_rp.rank;

        for (std::size_t index = move<Member>(the_index, start_index);
             ;
             index = move<Member>(the_index, index))
        {
            rp& ranked = m_ranked_points[index];

            if (ranked.rank != previous_rank && ! in_polygon)
            {
                assign_ranks(last_from_rank, previous_rank - 1, 1);
                assign_ranks(last_from_rank + 1, previous_rank, 2);
            }

            if (index == start_index)
            {
                return;
            }

            if (ranked.direction == dir_from)
            {
                last_from_rank = ranked.rank;
                in_polygon = true;
            }
            else if (ranked.direction == dir_to)
            {
                in_polygon = false;
            }

            previous_rank = ranked.rank;
        }
    }

    //! Find closed zones and assign it
    template <typename Include>
    std::size_t assign_zones(Include const& include_functor)
    {
        // Find a starting point (the first rank after an outgoing rank
        // with no polygons on the left side)
        rank_type start_rank = m_ranked_points.size() + 1;
        std::size_t start_index = 0;
        rank_type max_rank = 0;
        for (std::size_t i = 0; i < m_ranked_points.size(); i++)
        {
            rp const& ranked_point = m_ranked_points[i];
            if (ranked_point.rank > max_rank)
            {
                max_rank = ranked_point.rank;
            }
            if (ranked_point.direction == sort_by_side::dir_to
                && include_functor(ranked_point))
            {
                start_rank = ranked_point.rank + 1;
            }
            if (ranked_point.rank == start_rank && start_index == 0)
            {
                start_index = i;
            }
        }

        // Assign the zones
        rank_type const undefined_rank = max_rank + 1;
        std::size_t zone_id = 0;
        rank_type last_rank = 0;
        rank_type rank_at_next_zone = undefined_rank;
        std::size_t index = start_index;
        for (std::size_t i = 0; i < m_ranked_points.size(); i++)
        {
            rp& ranked_point = m_ranked_points[index];

            // Implement cyclic behavior
            index++;
            if (index == m_ranked_points.size())
            {
                index = 0;
            }

            if (ranked_point.rank != last_rank)
            {
                if (ranked_point.rank == rank_at_next_zone)
                {
                    zone_id++;
                    rank_at_next_zone = undefined_rank;
                }

                if (ranked_point.direction == sort_by_side::dir_to
                    && include_functor(ranked_point))
                {
                    rank_at_next_zone = ranked_point.rank + 1;
                    if (rank_at_next_zone > max_rank)
                    {
                        rank_at_next_zone = 0;
                    }
                }

                last_rank = ranked_point.rank;
            }

            ranked_point.zone = zone_id;
        }
        return zone_id;
    }

public :
    inline std::size_t open_count(operation_type for_operation) const
    {
        return for_operation == operation_union
            ? open_count(include_union())
            : open_count(include_intersection())
            ;
    }

    inline std::size_t assign_zones(operation_type for_operation)
    {
        return for_operation == operation_union
            ? assign_zones(include_union())
            : assign_zones(include_intersection())
            ;
    }

};


//! Metafunction to define side_order (clockwise, ccw) by operation_type
template <operation_type OpType>
struct side_compare {};

template <>
struct side_compare<operation_union>
{
    typedef std::greater<int> type;
};

template <>
struct side_compare<operation_intersection>
{
    typedef std::less<int> type;
};


}}} // namespace detail::overlay::sort_by_side
#endif //DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_SORT_BY_SIDE_HPP

/* sort_by_side.hpp
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
*/