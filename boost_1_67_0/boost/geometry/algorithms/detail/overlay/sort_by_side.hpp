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

#include <boost/geometry/algorithms/detail/overlay/copy_segment_point.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_ring.hpp>
#include <boost/geometry/algorithms/detail/direction_code.hpp>
#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>

#include <boost/geometry/util/condition.hpp>

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

        int const side_first_wrt_second = -side_second_wrt_first;

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

    void add_segment_from(signed_size_type turn_index, int op_index,
            Point const& point_from,
            operation_type op, segment_identifier const& si,
            bool is_origin)
    {
        m_ranked_points.push_back(rp(point_from, turn_index, op_index, dir_from, op, si));
        if (is_origin)
        {
            m_origin = point_from;
            m_origin_count++;
        }
    }

    void add_segment_to(signed_size_type turn_index, int op_index,
            Point const& point_to,
            operation_type op, segment_identifier const& si)
    {
        m_ranked_points.push_back(rp(point_to, turn_index, op_index, dir_to, op, si));
    }

    void add_segment(signed_size_type turn_index, int op_index,
            Point const& point_from, Point const& point_to,
            operation_type op, segment_identifier const& si,
            bool is_origin)
    {
        add_segment_from(turn_index, op_index, point_from, op, si, is_origin);
        add_segment_to(turn_index, op_index, point_to, op, si);
    }

    template <typename Operation, typename Geometry1, typename Geometry2>
    Point add(Operation const& op, signed_size_type turn_index, int op_index,
            Geometry1 const& geometry1,
            Geometry2 const& geometry2,
            bool is_origin)
    {
        Point point1, point2, point3;
        geometry::copy_segment_points<Reverse1, Reverse2>(geometry1, geometry2,
                op.seg_id, point1, point2, point3);
        Point const& point_to = op.fraction.is_one() ? point3 : point2;
        add_segment(turn_index, op_index, point1, point_to, op.operation, op.seg_id, is_origin);
        return point1;
    }

    template <typename Operation, typename Geometry1, typename Geometry2>
    void add(Operation const& op, signed_size_type turn_index, int op_index,
            segment_identifier const& departure_seg_id,
            Geometry1 const& geometry1,
            Geometry2 const& geometry2,
            bool check_origin)
    {
        Point const point1 = add(op, turn_index, op_index, geometry1, geometry2, false);

        if (check_origin)
        {
            bool const is_origin
                    = op.seg_id.source_index == departure_seg_id.source_index
                    && op.seg_id.ring_index == departure_seg_id.ring_index
                    && op.seg_id.multi_index == departure_seg_id.multi_index;

            if (is_origin)
            {
                signed_size_type const segment_distance = calculate_segment_distance(op, departure_seg_id, geometry1, geometry2);
                if (m_origin_count == 0 ||
                        segment_distance < m_origin_segment_distance)
                {
                    m_origin = point1;
                    m_origin_segment_distance = segment_distance;
                }
                m_origin_count++;
            }
        }
    }

    template <typename Operation, typename Geometry1, typename Geometry2>
    static signed_size_type calculate_segment_distance(Operation const& op,
            segment_identifier const& departure_seg_id,
            Geometry1 const& geometry1,
            Geometry2 const& geometry2)
    {
        if (op.seg_id.segment_index >= departure_seg_id.segment_index)
        {
            // dep.seg_id=5, op.seg_id=7, distance=2, being segments 5,6
            return op.seg_id.segment_index - departure_seg_id.segment_index;
        }
        // Take wrap into account
        // Suppose point_count=10 (10 points, 9 segments), dep.seg_id=7, op.seg_id=2,
        // then distance=9-7+2=4, being segments 7,8,0,1
        std::size_t const segment_count
                    = op.seg_id.source_index == 0
                    ? segment_count_on_ring(geometry1, op.seg_id)
                    : segment_count_on_ring(geometry2, op.seg_id);
        return segment_count - departure_seg_id.segment_index + op.seg_id.segment_index;
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

    template <signed_size_type segment_identifier::*Member, typename Map>
    void find_open_generic(Map& handled, bool check)
    {
        for (std::size_t i = 0; i < m_ranked_points.size(); i++)
        {
            const rp& ranked = m_ranked_points[i];
            if (ranked.direction != dir_from)
            {
                continue;
            }

            signed_size_type const& index = ranked.seg_id.*Member;
            if (check && (index < 0 || index > 1))
            {
                // Should not occur
                continue;
            }
            if (! handled[index])
            {
                find_polygons_for_source<Member>(index, i);
                handled[index] = true;
            }
        }
    }

    void find_open()
    {
        if (BOOST_GEOMETRY_CONDITION(OverlayType == overlay_buffer))
        {
            // For buffers, use piece index
            std::map<signed_size_type, bool> handled;
            find_open_generic
                <
                    &segment_identifier::piece_index
                >(handled, false);
        }
        else
        {
            // For other operations, by source (there should only source 0,1)
            bool handled[2] = {false, false};
            find_open_generic
                <
                    &segment_identifier::source_index
                >(handled, true);
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
GEdxIxiR79riejiHCF/sjaDhYbuxVFnELoHwplpwEYKZ1A019Sz3G6LhZhzxDDJixjeDp1fEonkiwjkPV7EHt+5hjFzFmAvvCFYXcyXB8nPyImGggOly0L3an5Nptf3GYB+ZXDkSmTBVzKRrKaIDUvPrigWTC1+B+NAsafern1s38E/p5l3NxadKHLlfzNm+8UrFP6oiivhOMTU1+6Ru2/5SPypgx1ds6+3jV+cq+FMjC2R/dNDKlpzWPAz7o5fLjmZY1492v/HDdkFS8lIG66J71o0tYhNoCFLYwFjfnhXBkREJffCR1oPe0X1wyT8Rnc2AqUKLL4DBZ5YJzEB4PWNhVf7qxc+n7OPyDstDFHWiawH9kc4lgDgbGE8jK9nxY+h0/E3fokuOQOIA+7v3z/Gq79dH9TMPeA8klwZsi9dHpus57I0dbhpNzF9Hf3bS/Xj/ctX1ZUG3XFDDHsUMwECAfKSRWuvZAknzEx0A8xrSFgZ36Vaz7itFLVSJcqLXAb5gSWxAnk8gXFLLbEF6tIeX1KO7NWkxHB6rb3vOTgMvat9sSB8BaFdsSqXrj4lj0HZOB/r79Dz/WB9x3u3lzumbOzEecTrcxmkPmJrmkLoxA3KVbu1QX1bWlUEq8CAveNDvv7HJCkg3vDA7RvWr57nK4LkjId0lPJZCJdKwi0jl0pD+A8c79c5R2KWmhTpujGij4M282SMZjb0Sx3r3t5MbnzeETTkQLv6JV7xhohPWdSzth74gfgP6LD5KowbZNzph0CD+zfm1wMfmxaW93z+e2hq98yaFYXrcBehJvd/rYTgUg03dyIItXYPzqkcscivMJfHw6kwckdNEqchYuIsYeUdfhHGKg82zlcGCHwUcDPKAUW5xew9CJATeVG73X2O7VkHsKWslVVWp9bOe9ElkGhqx99Dj//1qr5f2jOV//3vqApJ0n41PaxrAcmiyt3bZNjrM1l9YOiSjTmXqQi7izVvkl397f8GJTNE/PZu92G1++faGWp9bZwtbD7nriyHXtlFm2yCKkXYTSUwLuFRNaWoLnHGP0R/+itw0QOhozoqiE8ailsm21F+k06n+7lKiXGGkbX5ElGJm3ZW+/iIAq2zetF1qN2ZNFLSjdfJ4+Zb9turUPk2KorcC2onNn4EQRo2U3ICUsGdmyIe6qXNycZZPaS/r+PJJBWSbcQVrwYHGbLjPSl8nkrocsrm6XSDOlFVL/L0KSEnOdDIzDIQnVVzAio8o2sAmgfDsrFqQVYJoRqHoxHCRBJWdEa2O5Q8UnsTBgypNFH2/dsV8HY7Z+rNqa30Uqo59MTDBKnphag8j8RjiqLQEWBkx3cXwmbMLhzw6bMBs1I9QfPqkoFM+fAKvMIJjJK8RRparjAOmq3FJSSnH/XG+mduuqxFuV0LJrsMNwaoXyswDeu2NmnNuovfqpvHvBs9P76beyFKG3HjOODLd8dL6URGNCUMlfrPLtLPapzBiSTsyRHnA72s0HmN42cl7Qw4Dbuo4/RUOOaJjKLSG/hyDHmEBtDSu4GiUht2ylcy/47/z171mt6Gu+lQzPzIdlyVAmbW2mWm/CcYuO+3cFPo6VD11e1dgwI6YXn6rbDzS3NZofVDC6n2xwVHoOYXCIRWZvzH2zocXJFrbiSosfBioheXphwQvHVvhfwEpOSGsNxxXGi5XpyCEImgGtxTZTDz2hnnT8kOUogHl8rT/3Eds6CwHbMQPNA6iNrKZWkKdYZJQ6BO25h6QPFFca6e3q7O5PZTp7jKsCsxJiZXVBHPQc/Oi7wM7NxNTO+6cdXNEXFfmBYU+EktSt5oOwpg8hlodZetDYfJzyqM9oCN24tk3m05s6FcgISU2Xm9YSlq3roypM+4rl+MFV7uGYe8zB20XRc0Nss1qNSEcr960ASXkpA5ZHe6VRtJO3wqeoOmJ+aBwS1hXAKfDNTsKzJCxiVQvnaELgMvCpdCZ+foXKWjIlxt2BEyQUuu2Tsz9/zOg1LD1vaNhU56DERgb1FK13er/l2TYCaa1G0Fp5HYx5gDNg+txQHPXDHomeF/Ydan6IqZC6g20sOTqxy7hwPWwDh9XdLrrmzgQ9Xs0WaJ6PHfUb+3XELh0PRCv4sSvW0o4al5c62MHhtR8Zlku+Xf6UFsGaaChDzqOBAUeWAGZQm5vZqfwxg/tJnsqIPSLPGweGZztCNSaqGKHLbfSxaXhRgswXU9jCDofFnHlwxJ0cLtOth7yPU+nDVAuqzCRVLYwlglX07Y9WxMGdhc1DnymVhPklTJm3NJK1hU/ehPa18pEvsihcGjvDp69C9NMo+A/rPTy1Ih8Gmu8bl0kSr2Sy2v6otP1YYrLdywxITnnp0VmsuYzCnZxyc6Z2qzsQVBsSMXdyYgmkjnYgQZ/2cV4md8VxXjsQiFBYkO+RSM7Mm6vPbfgkIE2gRo6tewl3DP2hrENXh71L08pqflVp8EUbjJDcpB88oON2LnLV6bFbqSTbDaf9aJJC3gnYhpT1eOsGeV3CvfH90fWHYdA/Qag/em2vIg1LjvBB42Zl9uG7DajWUeie8fGuEnTJ3KIomPI+/YNcT7yRIpSFok4DSjhnSfcUGfQcLuYXTH4+mQz3bKmxKxS6jt96HMqvPt4VrOPdku1crlrzD1eJDFN4YzRKdMBhEgi7Mc4Fed4BCyLWyZ74ZwIVW+h2ifXD99mTus9mp7SPtGI6vVBnh3FYXgf5ksYvHoG5GC+2fGdF/km4R/dqpKARJ8SDHT+JLjRsi8VPEwUMIFJwIIX3suue+xo4SQnUOe0jQ90wCNgVmPbPaXS850rsxLvTWNcCQWfVfgfIF96zGIHtCjOC0lnaUMXQqfJml3mvun5KtfAN8iPC0n2V8AozLdujIiAZYxfDzEItph2gf0qDK1IoQELslaNY/yLmXE2AXoe1orHS8yHxaDWrO2k4IkzhbGJQt4iMJ6iUhrMyQW3dxkupNEOtGUt9GoZ2kwNX25Xc/sPXAHUM0LJQdA+pvzegzoUg4xslXPY+07AOHpQ4YfcJ4yZ9SP+vZnH7cJ4NDtUD0OJH26ffdKQtK5iiCJz+VX7Mt3s1dV6ocOiqRC+Jf8tIgnm5g21/+WZkn1bT9ruWyfUbKV1RfTeeC302w6mvKTy5D2lILHNulcz5/3Bl2vU3cpHEPQ90UHql9ovlIPBerf1wptD2axh/qO/mDOJbTE5rnoV7JCdxPueUzQRxamCCPaVf3GBNg/k2cNTGdldDH1qhfrDzv716QwqCr4tcZucoIfKsMKbQAQD01x9eLmteqg5rPi4rZ4VjOdXeCNkqjK5z2aVuW5Nt7hecBCl+FSpZYH3MiUYUa2HvXIwyuWzcjwMZG7fotOVKasRjJsExbLsfoBmA9JsfvhKsqNJnLUO2FH7V6GRlsEAOIaAnNIYJKEWYyojiJJWRN8Ip3CKQtHXUX5DIb87WJK1QIfadSoH9esYrAb359guTMmF42HxpEG2/uE5ALSCXn/vWG4LZE5PvBma/Bj4BqU+XWME54BrQFheVVagUtthpHPRKIVDa7lvwntXOxizrNmUKM18ifG8wZ7JGzOCcBCA/ffW3vU3d5zHfovbQ3YaT0YnzkTYjXZE27ygRY2Lwe/DkLmWaN08z0az96j1ZVat+WXn9WVcCd3nKxndBVS7Kd5GDXuH9vsWeCPd2OaUNuRxOES8ZZL71T7i+6gjY3YGguYnZH7yFbrC7OCHMUucXVmok31Zg+HM4zqYCu9HHYWa7lfl0nBxQa360Y8+xQ1734EFdq/2yBJdz/aYEhvPN3Kl1NsHBcGr4W5ji3WwEOEfAFF46VU3b468/56eSFxJDulIesmTEJlRiUJM8KX8Rl50rzCU3snt4bbwa1XyQqOT0rAdp5398Y+KIeUb0dJlQE++Tixvhh5YQGICSWdE/4/mA1koGjwPY6PSAjkCz63wf0vI2wyeKc43/AwKTUexK0JJdOdFcAxt57TN9V4G7F2B8z82ICeXtr3l5fPC/j+VVVW/f2dSLy79L5uNiQmPmImJiphpp2BX2o2Gpd0om1RdtbNAmSCa2HaWkoG1zR+X6+BMrD8+qd30EHPvEIHpeK2Pm1OKY85vB7JtU9PE55u1eLJXuwMB+u08VjetGFgAh7AuU8rF2Vk0GKxBP73Ch5TahP7a5b0wAxXN7XgPjN2RzVPcp5oVF7QsrhJj1qgf/pL8ZtHtA63/tiMZomt+IhqqVHmjcHYbyT3LmjX1WOvIZ/CgYCr/HfSgljmo8iZ9mmU4K4I7/7ujG/re1bupEaLvh7PhgTN6/20bTskRg/7aCYacPGxkpy2c67kVPXaC+hYl6ZToF1EZECmHrAyokkUYwWnbvMTcyElsVyYUyqzkhLfgBPyvCivTjvzZ8YRc1ES828jzxQnD4doJnnwmVv1ye4R9KxKSGjqnzWvg7e6UY+ax4w7rL4KRYEj67EP937uwRWKT4WzVB7gnfh24MICjy341i3KeLB0lOCx1tVclBvCU69ICf+z85yD1dgGez152GfNltV8++TDlO+6/be35Dix5TAWIuW+1u19tvtFtAKaluxAEkRABcuge15hgC/xqoZoP038G/BYdq07f0SmjRyReQJFZx3G3CCONGA5aH8YeXpUS6ogFYW9yF/rZNd3VpPdLK9nU3e4XGgz7nJge3qQUWVK6p/fr/eulNFZAhOhLKqsmIO2WbB/e41ftNOyBHNGiGTSMg7we/1lbF070atq6YPyD3QInR4EIST8LhqXhPqOD3QYakfVLHB5dodvfoG944F0+ME4FE+0tgu6IwuvRTWTATnTdPD1HiocsIeyIK99yTLLIaKsHEO7jIGKd/jLr0Afl56OEOmOBe1Ty9LKND7urntrMVrQCzksXpybxicvE1URt/9wUwTtFf92kub49JHgrq6OIv5tcBepPu0/l95EVdouDlnI1QRes+Kg/KCaeP+vsqslVbFGwsC6VzqLiSEijbqBDAHxSGQ4zIv/Y+T9SGmhLUp1mzc0RRDOvgIExqEP6X52HouNFfB3/BVOzRV9JRL8HtmDuvyKGCtmG/PJb4NFNMlzmcdtc+oU+89tz+4ZLSHfv9QeQp+MDw7O49z43rOR1+CUaX5fykfuplu0wnP5XJblaA0tzoI9S2fE2zh8fJPtHWGLflFnMPAPVUmmaUPiAlWuqaxh/99JdOxQclvO4eR8cFsnAwyH1XEk9NGzrTuXg0AyqRcx8TURu+dKlTB5d2xWEOa4w+43fvEiC6EcKyeM+UP2EMgyrg/dSfzqPWcbVaO6SjlVqTGYvFiASXQbhLAoSgwG00GTIAoUZLoHWsJwltoWz+DdfQ/ADgYme55mL6gGWsiS7PC89qJCeflH9O1HkPUmZ0te457zsZ0q56HHiHWelIFoBq3adVNyspeJlu4xDIdaJBGXTghVJFj4vlCZwuqDDlh2G0jFPNIa0POPSoWLzlTzSkise7XefP9iycbQapmX8P8A5NzsoEEG6BED6TYs3TFMqd+nxewBykbp9W9I5Vvx4tnkbNxpY0L+1MgPyBZJKAzB8MSQZ/Qg2YoYRRLcQ2PdTHucbjI3f7+qhzoG6RhUh840bLKRKo6E6FBQRTzcOaTSvjz/etZdtwFYx3KItIJ7BnIHaQe/GAplEtASdBNXA78B3a+9Xow3e9xIEAeGVEloxPEVeaG6Cd/Oxn2HYv1DAg9Fe/uur6gi4vuEvyZiBRksS16XcJLVtgV2ULwlwEC3WK/6yX0Kbc4tyq3PzsRvcN3F1cNHXEvAeAIzzZN5XCuqBFYHyjR7sYsdx+JKLQg7d/d8+uPhnZBOWL6on6YtpRDiOhcUsT3Zu37rdd6enrTF6RZRLaCNBjOJK1tG3AekkbiJtu+BBxGboqo/9TmsDmIemECELTGIOUIK1P8wpDtLr9OAkzDjCW0MItDgi4wDiFbxsovKoWkgMlB984y9xjvwQEbg3bMuwkMkGxCOoJZhoYhq0MgI3Nu6olyn9xbbI3Q9aEeJNaH9iELFnYscuFiC/z3stGkOT67Ko/+m28MV1EPjDFzLC4N+CS4GaA9UN70vomTJY0azW3eEpYkOn1/NUUA1C0MOh1VohO7S+mMlED9ZnvyRd1ehfXm4OWkuq4c3IifK9Vu12RDz/cabKlAdLUhSC8uq6zp2pVELqyYpvIBh3HJBUjNo/HeieKomErN2UiGwFv8NwK2VKutpzMK6JDFF+2QkBNB46MNFAuD5aAePwxAcwNz0E4OvYRMhAAiQQelwLHrwRPghEADLfRq0wdEODDHfBuwQIiDloBkhgohfUm8KnTmSQ/g3hTTb2DFzN8htGDmy3yv7rLveu067V7oxM5288UYymfSFLIMXjH50Hsi4ALqV1FG5ylpK2UpAg9QX9bjBNDvr2l+0XqFvZG8NrXCGcTqxO7E500Ibg1XQ5WifhJny34bFk57m5itsfZd2QDNZFzXxNpCaF0pwhPTuC8nT1Cit0DS7cJVCYNXltzTIRSJbjdk8JE8jqZPddv2/Lxur7R+9MB5IIXr8Tb0eIPeLLFyScPtH4Vs04wRf4G9SbKmwAQv+FeK137/OSwB0rnLfmXTRR8+ppPYR0+wjboRoe8RE5iCI+SB9a5iaJOXxWC5s8wLGox/VCRZFgNaN7P8g3oQWXRgcZ07pWORWJ+2dpmzgajnWT8kDoOtsiYr6iWLxL0Ve5Y5ZiQS3UDCUsNB3oF8KITOZSnGWRThyiWlFsd6hLu3624C6Z1cdaQ5zmE6r61OezVllWifchoNq7Q+HHx8fPd3qcMhEuT/gXxRtWbAeFwy15/K0Hvckl3Hx4ZG6N0lvxJkRuhVIr8S3aRdf8ZWRuiVI78SncciB2tbkcNyK3dGm6+BReOZ7EzTGZ8fiJkWuGSE9xTMU3CnrPRTjZ9fIhV3Ul6S55OrU5GQEG6145agNbTyup37VJZXD9ghKndvcsxF4/xbf3QsCwi9Dff4j7uyDRQpf96GlHxv0eO+uaB5WIuCTH4CuSH/9jIABdloEDWinnR2HgdqqyLE2+Joa40he7JGVv3HycH/k/xqDTTahY4kK0qEJk+zcwyRPrm0QV1pqvRaoyROGI2V6v+3HBtR4jjFlkCmCLnUJGHRSInF8ogBZkeLZ1G09LAFYYsYwHYYGPEgCod0eBDmLdPDdk2EDe9BBeGqMV0dJAqgIoyIBpB+JGW8IlQNBJEO8Jzuj9q1Fe0jcE9OTNPp0o42tIyt906BWxhItu13YR5j4SD0wMBEhR7K4c5feHOt3bCswbRuiEPmYa8hu4JrKvfxekCuHBF3s98GD+p1frvtSgk4CS1XvvG6tdYHC4XOcjwzXE+/YJusIRQn85/tUfi+fnfeS3fbk7b8O/TMVGtfnJahu328Ga/s5YVTRBvMEUsKLQ4OTBib9ezKxzZA6KOlhupRnmssIFzvqX2/YbvSh9AGglt7oLH8EX+cZ1dHIqrSULpK6tEUwAoW9v4uAHbQ78Neo2wSbJpsRnpFXvEtxHxMI5uKV4w13D++MKEXZq7mvsXu8K9hX2ytEaYFxDdWNtouYw3+I7Kt2c9GoFlshuFrI7sd+k767tYmE/wz9/hm23xEXP4L1eKqHFEH1YbrKfY4eac6SoVOKe3WMYB5GzkQOmO95lcj+Pn8QTV39MANnYFQs30/rTx43hktN5sQxWqT0tkfbBRyl6w4JOIqNOFVfmTRdDeqlO6qF6kjgCx/FMWX0BpQALcnGqQuJ804r6v1//TYjZBtVV3dO2Y67ruu7RI8bK9HMjdifsEv/s30qIc4op9wfSAYe2HFv3aUjJgxzFsOl+lCaHEGGio1CNuVI68sksdNqXX+Ra8WoHLzi2qES3Qa0Ita7Dox2k6r/FDgJxuBd7r9ltdyJXIR19V/KrCv3VAR/BtSuFyXWqobpUIDFsZKpWOfGJmqSvsSXK6CsGJhvl743gZ+zqQDRfgeSIswf+zfEO9wpM+0empgN62cfLlsWb8n0DGTobtOlm3Q23JV/UiFysiERvbQljJLBv8i5jLyZS+TJy70HAVEAhjecCMab0TU3AChTCf49PmeL9aImeQJZAYI3hnPY9nIBFAvmh5NJSgUOEOFrM0flPWAAl3ExAHDNSPOayXD8XJniBRoHBBu3vmpbsxIFs739IT5yZb+ny5mpqYaHDdC5Q/McsdgUlqHwxKQK4ogHKUFt3aTvQxDTKKcTC1fv3rvsdHkAeIFX7hnt69eEqLH5G8CxluxE3xU9LsrSYhxVx24aaGkuV6UnRor9bbrRncub48N/CnQfya93iq5McaYXFtLa5cXUkxtWcbgcBAB39wZXkO1JLayBXmCbhQD393XGdVtUvqRyjMt20gcTOOp5ikIp9ZQg2hVufzWAzbAa6mldDKFVlK8l9FOoqU9j8IJ5ScdY3XPzM4QeJTa5sRp+2hL6kq/t/3uWN3jfeu4LlFkbntAZKPPeGfVyH38ygtJzT73C17tI445lf5b3imOHk2yaUG/3Ujpr6TlzvS+Wo8dQd2QIVbsUvE77ubupRS7KqWbeqziQ5V2eZyiJpEafdsWkRpyeMJeMXdxozrKf843SBeGnYSjCdfbCXGV+oeEVkrtqrpzji6EaN+9ob66ogHdM1Yyffhmn/yZb47ie8yTDcjxvKfCb/msNMJP/ar9xoJ3zkKkrN6n60q2zLN/s+0uAJORVWB0AYRmZ6M+A3wKV6Grzq/7bjj3IWmStks086/ROsHs0jGS9Wx++l9XeTWq2QhAPBrhpNfgIPxZ4UbB6G0VYhK/VFEfgbEmJk1cVzxEMX9Tjfx9YNsBNZ/ih4a21nY2teJZegFSUxRuvx9yYd6DGayMJpMaXVhzMny4+dyOKp8bgUZTDiVy9+O9Ku/vVrCkuvzEJErc05gdFfz+r3uGP1d86haObPW8Mzolw7Bjs0nIy77E2mlZWuRKull343RnqmijE3DW3QVGSxZVr30MoBcRMKTm9K6MfzOG74b7pNfiJi5S9VJGuztKSiXbjM686AlOfPAnKRIHpUk/HsMGO3IqlkIerB9ijSpA7kzGg4gmOBAaE4xWgmh9mfB0OH1kOHxAu2E5GphzKtSoWerJliRdW5NO0UA+3N/s0qul8vwHJ6EUay0FopdaVrehxcR0gS/OeqXTo9lpV8ygk=
*/