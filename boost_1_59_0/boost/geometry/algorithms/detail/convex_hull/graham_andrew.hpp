// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014-2021.
// Modifications copyright (c) 2014-2021 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_CONVEX_HULL_GRAHAM_ANDREW_HPP
#define BOOST_GEOMETRY_ALGORITHMS_CONVEX_HULL_GRAHAM_ANDREW_HPP


#include <cstddef>
#include <algorithm>
#include <vector>

#include <boost/geometry/algorithms/detail/for_each_range.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/policies/compare.hpp>
#include <boost/geometry/strategies/convex_hull/cartesian.hpp>
#include <boost/geometry/strategies/convex_hull/geographic.hpp>
#include <boost/geometry/strategies/convex_hull/spherical.hpp>

#include <boost/geometry/util/range.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace convex_hull
{

// TODO: All of the copies could be avoided if this function stored pointers to points.
//       But would it be possible considering that a range can return proxy reference?
template <typename InputProxy, typename Point, typename Less>
inline void get_extremes(InputProxy const& in_proxy,
                         Point& left, Point& right,
                         Less const& less)
{
    bool first = true;
    in_proxy.for_each_range([&](auto const& range)
    {
        if (boost::empty(range))
        {
            return;
        }

        // First iterate through this range
        // (this two-stage approach avoids many point copies,
        //  because iterators are kept in memory. Because iterators are
        //  not persistent (in MSVC) this approach is not applicable
        //  for more ranges together)

        auto left_it = boost::begin(range);
        auto right_it = boost::begin(range);

        auto it = boost::begin(range);
        for (++it; it != boost::end(range); ++it)
        {
            if (less(*it, *left_it))
            {
                left_it = it;
            }

            if (less(*right_it, *it))
            {
                right_it = it;
            }
        }

        // Then compare with earlier
        if (first)
        {
            // First time, assign left/right
            left = *left_it;
            right = *right_it;
            first = false;
        }
        else
        {
            // Next time, check if this range was left/right from
            // the extremes already collected
            if (less(*left_it, left))
            {
                left = *left_it;
            }

            if (less(right, *right_it))
            {
                right = *right_it;
            }
        }
    });
}


template <typename InputProxy, typename Point, typename Container, typename SideStrategy>
inline void assign_ranges(InputProxy const& in_proxy,
                          Point const& most_left, Point const& most_right,
                          Container& lower_points, Container& upper_points,
                          SideStrategy const& side)
{
    in_proxy.for_each_range([&](auto const& range)
    {
        // Put points in one of the two output sequences
        for (auto it = boost::begin(range); it != boost::end(range); ++it)
        {
            // check if it is lying most_left or most_right from the line

            int dir = side.apply(most_left, most_right, *it);
            switch(dir)
            {
                case 1 : // left side
                    upper_points.push_back(*it);
                    break;
                case -1 : // right side
                    lower_points.push_back(*it);
                    break;

                // 0: on line most_left-most_right,
                //    or most_left, or most_right,
                //    -> all never part of hull
            }
        }
    });
}


/*!
\brief Graham scan algorithm to calculate convex hull
 */
template <typename InputPoint>
class graham_andrew
{
    typedef InputPoint point_type;
    typedef typename std::vector<point_type> container_type;
    typedef typename std::vector<point_type>::const_iterator iterator;
    typedef typename std::vector<point_type>::const_reverse_iterator rev_iterator;

    class partitions
    {
        friend class graham_andrew;

        container_type m_lower_hull;
        container_type m_upper_hull;
        container_type m_copied_input;
    };

public:
    template <typename InputProxy, typename OutputRing, typename Strategy>
    static void apply(InputProxy const& in_proxy, OutputRing & out_ring, Strategy& strategy)
    {
        partitions state;

        apply(in_proxy, state, strategy);

        result(state,
               range::back_inserter(out_ring),
               geometry::point_order<OutputRing>::value == clockwise,
               geometry::closure<OutputRing>::value != open);
    }

private:
    template <typename InputProxy, typename Strategy>
    static void apply(InputProxy const& in_proxy, partitions& state, Strategy& strategy)
    {
        // First pass.
        // Get min/max (in most cases left / right) points
        // This makes use of the geometry::less/greater predicates

        // For the left boundary it is important that multiple points
        // are sorted from bottom to top. Therefore the less predicate
        // does not take the x-only template parameter (this fixes ticket #6019.
        // For the right boundary it is not necessary (though also not harmful),
        // because points are sorted from bottom to top in a later stage.
        // For symmetry and to get often more balanced lower/upper halves
        // we keep it.

        point_type most_left, most_right;

        // TODO: User-defined CS-specific less-compare
        geometry::less<point_type> less;

        detail::convex_hull::get_extremes(in_proxy, most_left, most_right, less);

        container_type lower_points, upper_points;

        auto const side_strategy = strategy.side();

        // Bounding left/right points
        // Second pass, now that extremes are found, assign all points
        // in either lower, either upper
        detail::convex_hull::assign_ranges(in_proxy, most_left, most_right,
                              lower_points, upper_points,
                              side_strategy);

        // Sort both collections, first on x(, then on y)
        std::sort(boost::begin(lower_points), boost::end(lower_points), less);
        std::sort(boost::begin(upper_points), boost::end(upper_points), less);

        // And decide which point should be in the final hull
        build_half_hull<-1>(lower_points, state.m_lower_hull,
                            most_left, most_right,
                            side_strategy);
        build_half_hull<1>(upper_points, state.m_upper_hull,
                           most_left, most_right,
                           side_strategy);
    }

    template <int Factor, typename SideStrategy>
    static inline void build_half_hull(container_type const& input,
            container_type& output,
            point_type const& left, point_type const& right,
            SideStrategy const& side)
    {
        output.push_back(left);
        for(iterator it = input.begin(); it != input.end(); ++it)
        {
            add_to_hull<Factor>(*it, output, side);
        }
        add_to_hull<Factor>(right, output, side);
    }


    template <int Factor, typename SideStrategy>
    static inline void add_to_hull(point_type const& p, container_type& output,
                                   SideStrategy const& side)
    {
        output.push_back(p);
        std::size_t output_size = output.size();
        while (output_size >= 3)
        {
            rev_iterator rit = output.rbegin();
            point_type const last = *rit++;
            point_type const& last2 = *rit++;

            if (Factor * side.apply(*rit, last, last2) <= 0)
            {
                // Remove last two points from stack, and add last again
                // This is much faster then erasing the one but last.
                output.pop_back();
                output.pop_back();
                output.push_back(last);
                output_size--;
            }
            else
            {
                return;
            }
        }
    }


    template <typename OutputIterator>
    static void result(partitions const& state, OutputIterator out, bool clockwise, bool closed)
    {
        if (clockwise)
        {
            output_ranges(state.m_upper_hull, state.m_lower_hull, out, closed);
        }
        else
        {
            output_ranges(state.m_lower_hull, state.m_upper_hull, out, closed);
        }
    }

    template <typename OutputIterator>
    static inline void output_ranges(container_type const& first,
                                     container_type const& second,
                                     OutputIterator out,
                                     bool closed)
    {
        std::copy(boost::begin(first), boost::end(first), out);

        BOOST_GEOMETRY_ASSERT(closed ? !boost::empty(second) : boost::size(second) > 1);
        std::copy(++boost::rbegin(second), // skip the first Point
                  closed ? boost::rend(second) : --boost::rend(second), // skip the last Point if open
                  out);

        typedef typename boost::range_size<container_type>::type size_type;
        size_type const count = boost::size(first) + boost::size(second) - 1;
        // count describes a closed case but comparison with min size of closed
        // gives the result compatible also with open
        // here core_detail::closure::minimum_ring_size<closed> could be used
        if (count < 4)
        {
            // there should be only one missing
            *out++ = *boost::begin(first);
        }
    }
};


}} // namespace detail::convex_hull
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_CONVEX_HULL_GRAHAM_ANDREW_HPP

/* graham_andrew.hpp
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
*/