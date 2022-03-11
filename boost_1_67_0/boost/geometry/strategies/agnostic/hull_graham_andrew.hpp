// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014, 2018.
// Modifications copyright (c) 2014, 2018 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_AGNOSTIC_CONVEX_GRAHAM_ANDREW_HPP
#define BOOST_GEOMETRY_STRATEGIES_AGNOSTIC_CONVEX_GRAHAM_ANDREW_HPP


#include <cstddef>
#include <algorithm>
#include <vector>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <boost/geometry/algorithms/detail/for_each_range.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/policies/compare.hpp>
#include <boost/geometry/strategies/convex_hull.hpp>
#include <boost/geometry/strategies/side.hpp>
#include <boost/geometry/views/detail/range_type.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace convex_hull
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


template
<
    typename InputRange,
    typename RangeIterator,
    typename StrategyLess,
    typename StrategyGreater
>
struct get_extremes
{
    typedef typename point_type<InputRange>::type point_type;

    point_type left, right;

    bool first;

    StrategyLess less;
    StrategyGreater greater;

    inline get_extremes()
        : first(true)
    {}

    inline void apply(InputRange const& range)
    {
        if (boost::size(range) == 0)
        {
            return;
        }

        // First iterate through this range
        // (this two-stage approach avoids many point copies,
        //  because iterators are kept in memory. Because iterators are
        //  not persistent (in MSVC) this approach is not applicable
        //  for more ranges together)

        RangeIterator left_it = boost::begin(range);
        RangeIterator right_it = boost::begin(range);

        for (RangeIterator it = boost::begin(range) + 1;
            it != boost::end(range);
            ++it)
        {
            if (less(*it, *left_it))
            {
                left_it = it;
            }

            if (greater(*it, *right_it))
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

            if (greater(*right_it, right))
            {
                right = *right_it;
            }
        }
    }
};


template
<
    typename InputRange,
    typename RangeIterator,
    typename Container,
    typename SideStrategy
>
struct assign_range
{
    Container lower_points, upper_points;

    typedef typename point_type<InputRange>::type point_type;

    point_type const& most_left;
    point_type const& most_right;

    inline assign_range(point_type const& left, point_type const& right)
        : most_left(left)
        , most_right(right)
    {}

    inline void apply(InputRange const& range)
    {
        typedef SideStrategy side;

        // Put points in one of the two output sequences
        for (RangeIterator it = boost::begin(range);
            it != boost::end(range);
            ++it)
        {
            // check if it is lying most_left or most_right from the line

            int dir = side::apply(most_left, most_right, *it);
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
    }
};

template <typename Range>
static inline void sort(Range& range)
{
    typedef typename boost::range_value<Range>::type point_type;
    typedef geometry::less<point_type> comparator;

    std::sort(boost::begin(range), boost::end(range), comparator());
}

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


/*!
\brief Graham scan strategy to calculate convex hull
\ingroup strategies
 */
template <typename InputGeometry, typename OutputPoint>
class graham_andrew
{
public :
    typedef OutputPoint point_type;
    typedef InputGeometry geometry_type;

private:

    typedef typename cs_tag<point_type>::type cs_tag;

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
    typedef partitions state_type;


    inline void apply(InputGeometry const& geometry, partitions& state) const
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

        typedef typename geometry::detail::range_type<InputGeometry>::type range_type;

        typedef typename boost::range_iterator
            <
                range_type const
            >::type range_iterator;

        detail::get_extremes
            <
                range_type,
                range_iterator,
                geometry::less<point_type>,
                geometry::greater<point_type>
            > extremes;
        geometry::detail::for_each_range(geometry, extremes);

        // Bounding left/right points
        // Second pass, now that extremes are found, assign all points
        // in either lower, either upper
        detail::assign_range
            <
                range_type,
                range_iterator,
                container_type,
                typename strategy::side::services::default_strategy<cs_tag>::type
            > assigner(extremes.left, extremes.right);

        geometry::detail::for_each_range(geometry, assigner);


        // Sort both collections, first on x(, then on y)
        detail::sort(assigner.lower_points);
        detail::sort(assigner.upper_points);

        //std::cout << boost::size(assigner.lower_points) << std::endl;
        //std::cout << boost::size(assigner.upper_points) << std::endl;

        // And decide which point should be in the final hull
        build_half_hull<-1>(assigner.lower_points, state.m_lower_hull,
                extremes.left, extremes.right);
        build_half_hull<1>(assigner.upper_points, state.m_upper_hull,
                extremes.left, extremes.right);
    }


    template <typename OutputIterator>
    inline void result(partitions const& state,
                       OutputIterator out,
                       bool clockwise,
                       bool closed) const
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


private:

    template <int Factor>
    static inline void build_half_hull(container_type const& input,
            container_type& output,
            point_type const& left, point_type const& right)
    {
        output.push_back(left);
        for(iterator it = input.begin(); it != input.end(); ++it)
        {
            add_to_hull<Factor>(*it, output);
        }
        add_to_hull<Factor>(right, output);
    }


    template <int Factor>
    static inline void add_to_hull(point_type const& p, container_type& output)
    {
        typedef typename strategy::side::services::default_strategy<cs_tag>::type side;

        output.push_back(p);
        std::size_t output_size = output.size();
        while (output_size >= 3)
        {
            rev_iterator rit = output.rbegin();
            point_type const last = *rit++;
            point_type const& last2 = *rit++;

            if (Factor * side::apply(*rit, last, last2) <= 0)
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
    static inline void output_ranges(container_type const& first, container_type const& second,
                                     OutputIterator out, bool closed)
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

}} // namespace strategy::convex_hull


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
template <typename InputGeometry, typename OutputPoint>
struct strategy_convex_hull<InputGeometry, OutputPoint, cartesian_tag>
{
    typedef strategy::convex_hull::graham_andrew<InputGeometry, OutputPoint> type;
};
#endif

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_AGNOSTIC_CONVEX_GRAHAM_ANDREW_HPP

/* hull_graham_andrew.hpp
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
*/