// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2016, 2018.
// Modifications copyright (c) 2016-2018 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_TURN_IN_ORIGINAL_VISITOR
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_TURN_IN_ORIGINAL_VISITOR


#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/algorithms/detail/buffer/buffer_policies.hpp>
#include <boost/geometry/algorithms/expand.hpp>
#include <boost/geometry/strategies/agnostic/point_in_poly_winding.hpp>
#include <boost/geometry/strategies/buffer.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace buffer
{

struct original_get_box
{
    template <typename Box, typename Original>
    static inline void apply(Box& total, Original const& original)
    {
        geometry::expand(total, original.m_box);
    }
};

template <typename DisjointBoxBoxStrategy>
struct original_ovelaps_box
{
    template <typename Box, typename Original>
    static inline bool apply(Box const& box, Original const& original)
    {
        return ! detail::disjoint::disjoint_box_box(box, original.m_box,
                                                    DisjointBoxBoxStrategy());
    }
};

struct include_turn_policy
{
    template <typename Turn>
    static inline bool apply(Turn const& turn)
    {
        return turn.location == location_ok;
    }
};

template <typename DisjointPointBoxStrategy>
struct turn_in_original_ovelaps_box
{
    template <typename Box, typename Turn>
    static inline bool apply(Box const& box, Turn const& turn)
    {
        if (turn.location != location_ok || turn.within_original)
        {
            // Skip all points already processed
            return false;
        }

        return ! geometry::detail::disjoint::disjoint_point_box(
                    turn.robust_point, box, DisjointPointBoxStrategy());
    }
};

//! Check if specified is in range of specified iterators
//! Return value of strategy (true if we can bail out)
template
<
    typename Strategy,
    typename State,
    typename Point,
    typename Iterator
>
inline bool point_in_range(Strategy& strategy, State& state,
        Point const& point, Iterator begin, Iterator end)
{
    boost::ignore_unused(strategy);

    Iterator it = begin;
    for (Iterator previous = it++; it != end; ++previous, ++it)
    {
        if (! strategy.apply(point, *previous, *it, state))
        {
            // We're probably on the boundary
            return false;
        }
    }
    return true;
}

template
<
    typename Strategy,
    typename State,
    typename Point,
    typename CoordinateType,
    typename Iterator
>
inline bool point_in_section(Strategy& strategy, State& state,
        Point const& point, CoordinateType const& point_x,
        Iterator begin, Iterator end,
        int direction)
{
    if (direction == 0)
    {
        // Not a monotonic section, or no change in X-direction
        return point_in_range(strategy, state, point, begin, end);
    }

    // We're in a monotonic section in x-direction
    Iterator it = begin;

    for (Iterator previous = it++; it != end; ++previous, ++it)
    {
        // Depending on sections.direction we can quit for this section
        CoordinateType const previous_x = geometry::get<0>(*previous);

        if (direction == 1 && point_x < previous_x)
        {
            // Section goes upwards, x increases, point is is below section
            return true;
        }
        else if (direction == -1 && point_x > previous_x)
        {
            // Section goes downwards, x decreases, point is above section
            return true;
        }

        if (! strategy.apply(point, *previous, *it, state))
        {
            // We're probably on the boundary
            return false;
        }
    }
    return true;
}


template <typename Point, typename Original, typename PointInGeometryStrategy>
inline int point_in_original(Point const& point, Original const& original,
                             PointInGeometryStrategy const& strategy)
{
    typename PointInGeometryStrategy::state_type state;

    if (boost::size(original.m_sections) == 0
        || boost::size(original.m_ring) - boost::size(original.m_sections) < 16)
    {
        // There are no sections, or it does not profit to walk over sections
        // instead of over points. Boundary of 16 is arbitrary but can influence
        // performance
        point_in_range(strategy, state, point,
                original.m_ring.begin(), original.m_ring.end());
        return strategy.result(state);
    }

    typedef typename Original::sections_type sections_type;
    typedef typename boost::range_iterator<sections_type const>::type iterator_type;
    typedef typename boost::range_value<sections_type const>::type section_type;
    typedef typename geometry::coordinate_type<Point>::type coordinate_type;

    coordinate_type const point_x = geometry::get<0>(point);

    // Walk through all monotonic sections of this original
    for (iterator_type it = boost::begin(original.m_sections);
        it != boost::end(original.m_sections);
        ++it)
    {
        section_type const& section = *it;

        if (! section.duplicate
            && section.begin_index < section.end_index
            && point_x >= geometry::get<min_corner, 0>(section.bounding_box)
            && point_x <= geometry::get<max_corner, 0>(section.bounding_box))
        {
            // x-coordinate of point overlaps with section
            if (! point_in_section(strategy, state, point, point_x,
                    boost::begin(original.m_ring) + section.begin_index,
                    boost::begin(original.m_ring) + section.end_index + 1,
                    section.directions[0]))
            {
                // We're probably on the boundary
                break;
            }
        }
    }

    return strategy.result(state);
}


template <typename Turns, typename PointInGeometryStrategy>
class turn_in_original_visitor
{
public:
    turn_in_original_visitor(Turns& turns, PointInGeometryStrategy const& strategy)
        : m_mutable_turns(turns)
        , m_point_in_geometry_strategy(strategy)
    {}

    template <typename Turn, typename Original>
    inline bool apply(Turn const& turn, Original const& original)
    {
        if (boost::empty(original.m_ring))
        {
            // Skip empty rings
            return true;
        }

        if (turn.location != location_ok || turn.within_original)
        {
            // Skip all points already processed
            return true;
        }

        if (geometry::disjoint(turn.robust_point, original.m_box))
        {
            // Skip all disjoint
            return true;
        }

        int const code = point_in_original(turn.robust_point, original, m_point_in_geometry_strategy);

        if (code == -1)
        {
            return true;
        }

        Turn& mutable_turn = m_mutable_turns[turn.turn_index];

        if (code == 0)
        {
            // On border of original: always discard
            mutable_turn.location = location_discard;
        }

        // Point is inside an original ring
        if (original.m_is_interior)
        {
            mutable_turn.count_in_original--;
        }
        else if (original.m_has_interiors)
        {
            mutable_turn.count_in_original++;
        }
        else
        {
            // It is an exterior ring and there are no interior rings.
            // Then we are completely ready with this turn
            mutable_turn.within_original = true;
            mutable_turn.count_in_original = 1;
        }

        return true;
    }

private :
    Turns& m_mutable_turns;
    PointInGeometryStrategy const& m_point_in_geometry_strategy;
};


}} // namespace detail::buffer
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_TURN_IN_ORIGINAL_VISITOR

/* turn_in_original_visitor.hpp
AG6SPnadaupHd6lvTegvwyOaBs40dyecpPrvOVXTGLOoP8rkqv/eU00sGejwJozrfNDchPQMjPsnke5EOq9Q4SpnaTXOA/G3yqm6L0ZsAE0TXPfbWt7ylHGP77bmLbai3OeWDjA6tHiW94GON9pK6G9/74vg/G11IsGNPj38EIHbvcOzgDtd2fTV+fH0eIKPo/QYSu9p0lYejsNfAnkKqXwBpQ+i9ERK701p4aU+J8v/atJXNelrPPlwagg+juDTCD6G4B8m+J4EP0bHjOrDrD3JZ6priSafLZ1J8ELiWUfwAoLPIfhBBK8n+ESCH0fwvQk+34z3d/Pj/XGhgZXTPvdj0FU5+RPLjB+sWXCsr2oRzUnHR7KB/k0cmymCo6zLt+NnqZGvlOT7hIEtKYiPqxMNLEPzyUkRT9DspnhOy6ZifqE5LZNH7+Nq3/G2o563tXezlpM+3jNnQt81Z8F/i/p2KE3vtwu/b5Otd4qv2y7O9tIzwBmc290zivOB8oVk8/bo2qf05Zf83uqphFuQnxs3TbgHj8yN2y+4VsYX9onLuNrqAHBe+9YSDf5ucjrB1W8X+Uij/gG4tXU/HcJG/np0tp9/JuznKtdnJX3YvvIrjJ9B/hzae/9RoBXJgTIsx5lRXQ2c67qBcJJsgbNNfT5Lfe5cpJ0eIZPa+hZeoPjW5vG61dgmoqswpg764I/JD+7gHOfxq6A/rTK+t6jXvYa1daBX+Vm9XqJ61TIqs00fZWjaeDYcM+KyqXH4JQS/guDcv75F8KMI/h2CcwyJ7xn48gT5fmDaQPISffNXow1+ODU7DzyTn33HYsYgvrU3Ny5q0s/3nI89/bWgr+8b4/eCftPgNTMv+DHa61m0x4dGxe/bX6DzkqahD9ispK8bTf/+EWjL/+FZeOqvSWPoFqPv6+TvZ0nfmwz9MZDtOtC/NYQ5Peh8cBute7+kMfcr4ncmrTG/VrgvC3mhL4HfibadTN+V79I5Qvuc4ITr0d0CUzwzTzDevSTrFNrbr0M6T9MqK/Y/5L+YGofzWNhCcP5G8aBpv4YS5YE5C7GhDQ2Xx3uqRwyNaZXJfeAxwkmaRx+P+gH4WHvjCS3vYZCTfBk616rN5MflXrgjMlrW58Tz4f4cmD3JZdLRe5zoc8cOPK5dwUxnWvzkcloNr7smw0D3edBN/lYQL6LScS5ovQhaX4b/7zlJCw2pB94WkLTctZZi6cSYNS8JvDDoEtKtOM/n49U4BJwD83fLu+Rim/qyj5R4NvaMWWnQq2lnq1finEQ53pJ6eaq5Xz7wuXw/7l804/4vrn7DcPZU/rZr31+nuh/FLsI4/htwlYaZO/6BMq7u/vIfyrwGPHyDET2Eb+S2ygcNpAWaTnWKB74Hfvwiz7VLPiwAJy/+Vt9E72Nt17NwG8NvU72ndMj7GPDVv2H0U7RT7R/W5yXa876J+ryF+sxAfX4yScDSdqlVvVlZJS0EtX4jJS3X9bc7g1iOe4tvG1kLdzCGrE9QfmrX9AfWx7Fr8I7Kr/4Gtb9t+h1Nozylr6b0sKJ4+pDqeHo8pcdRegyl9zRpe0ab9/zDa2BzUvkCSh9E6YmUxp6f/S/wm9jYPfAz1Wi9MRfacrljQhbU2PrQnlXqM5rgk2i/O5bgV1P5QoK/Q/D9CL6J4PsTnOMKjK9RfOjf+qGSfQwHEc0JQZzGRNDMME2DP4ruQ04imuwLKSY4+w0OV3hon46ie7JHGvjGhNhNJTXxmL+Pqq9QY1c6msDBO6Q18fiWmYDxwj7yX+auBLyuqgjfpCEtm6ZpC7FUKBRqRalp2oYkbdPsbSBNQpIuVOXxkrw0r7y8F97SBQXrhriLKygi7ig=
*/