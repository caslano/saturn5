// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2015, 2018.
// Modifications copyright (c) 2015-2018 Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_CLIP_LINESTRING_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_CLIP_LINESTRING_HPP

#include <boost/range.hpp>

#include <boost/geometry/algorithms/clear.hpp>
#include <boost/geometry/algorithms/convert.hpp>

#include <boost/geometry/algorithms/detail/overlay/append_no_duplicates.hpp>

#include <boost/geometry/util/select_coordinate_type.hpp>
#include <boost/geometry/geometries/segment.hpp>

#include <boost/geometry/strategies/cartesian/point_in_point.hpp>

namespace boost { namespace geometry
{

namespace strategy { namespace intersection
{

/*!
    \brief Strategy: line clipping algorithm after Liang Barsky
    \ingroup overlay
    \details The Liang-Barsky line clipping algorithm clips a line with a clipping box.
    It is slightly adapted in the sense that it returns which points are clipped
    \tparam B input box type of clipping box
    \tparam P input/output point-type of segments to be clipped
    \note The algorithm is currently only implemented for 2D Cartesian points
    \note Though it is implemented in namespace strategy, and theoretically another
        strategy could be used, it is not (yet) updated to the general strategy concepts,
        and not (yet) splitted into a file in folder strategies
    \author Barend Gehrels, and the following recourses
    - A tutorial: http://www.skytopia.com/project/articles/compsci/clipping.html
    - a German applet (link broken): http://ls7-www.cs.uni-dortmund.de/students/projectgroups/acit/lineclip.shtml
*/
template<typename Box, typename Point>
class liang_barsky
{
private:
    typedef model::referring_segment<Point> segment_type;

    template <typename CoordinateType, typename CalcType>
    inline bool check_edge(CoordinateType const& p, CoordinateType const& q, CalcType& t1, CalcType& t2) const
    {
        bool visible = true;

        if(p < 0)
        {
            CalcType const r = static_cast<CalcType>(q) / p;
            if (r > t2)
                visible = false;
            else if (r > t1)
                t1 = r;
        }
        else if(p > 0)
        {
            CalcType const r = static_cast<CalcType>(q) / p;
            if (r < t1)
                visible = false;
            else if (r < t2)
                t2 = r;
        }
        else
        {
            if (q < 0)
                visible = false;
        }

        return visible;
    }

public:

// TODO: Temporary, this strategy should be moved, it is cartesian-only

    typedef strategy::within::cartesian_point_point equals_point_point_strategy_type;

    static inline equals_point_point_strategy_type get_equals_point_point_strategy()
    {
        return equals_point_point_strategy_type();
    }

    inline bool clip_segment(Box const& b, segment_type& s, bool& sp1_clipped, bool& sp2_clipped) const
    {
        typedef typename select_coordinate_type<Box, Point>::type coordinate_type;
        typedef typename select_most_precise<coordinate_type, double>::type calc_type;

        calc_type t1 = 0;
        calc_type t2 = 1;

        coordinate_type const dx = get<1, 0>(s) - get<0, 0>(s);
        coordinate_type const dy = get<1, 1>(s) - get<0, 1>(s);

        coordinate_type const p1 = -dx;
        coordinate_type const p2 = dx;
        coordinate_type const p3 = -dy;
        coordinate_type const p4 = dy;

        coordinate_type const q1 = get<0, 0>(s) - get<min_corner, 0>(b);
        coordinate_type const q2 = get<max_corner, 0>(b) - get<0, 0>(s);
        coordinate_type const q3 = get<0, 1>(s) - get<min_corner, 1>(b);
        coordinate_type const q4 = get<max_corner, 1>(b) - get<0, 1>(s);

        if (check_edge(p1, q1, t1, t2)      // left
            && check_edge(p2, q2, t1, t2)   // right
            && check_edge(p3, q3, t1, t2)   // bottom
            && check_edge(p4, q4, t1, t2))   // top
        {
            sp1_clipped = t1 > 0;
            sp2_clipped = t2 < 1;

            if (sp2_clipped)
            {
                set<1, 0>(s, get<0, 0>(s) + t2 * dx);
                set<1, 1>(s, get<0, 1>(s) + t2 * dy);
            }

            if(sp1_clipped)
            {
                set<0, 0>(s, get<0, 0>(s) + t1 * dx);
                set<0, 1>(s, get<0, 1>(s) + t1 * dy);
            }

            return true;
        }

        return false;
    }

    template<typename Linestring, typename OutputIterator>
    inline void apply(Linestring& line_out, OutputIterator out) const
    {
        if (!boost::empty(line_out))
        {
            *out = line_out;
            ++out;
            geometry::clear(line_out);
        }
    }
};


}} // namespace strategy::intersection


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace intersection
{

/*!
    \brief Clips a linestring with a box
    \details A linestring is intersected (clipped) by the specified box
    and the resulting linestring, or pieces of linestrings, are sent to the specified output operator.
    \tparam OutputLinestring type of the output linestrings
    \tparam OutputIterator an output iterator which outputs linestrings
    \tparam Linestring linestring-type, for example a vector of points, matching the output-iterator type,
         the points should also match the input-iterator type
    \tparam Box box type
    \tparam Strategy strategy, a clipping strategy which should implement the methods "clip_segment" and "apply"
*/
template
<
    typename OutputLinestring,
    typename OutputIterator,
    typename Range,
    typename RobustPolicy,
    typename Box,
    typename Strategy
>
OutputIterator clip_range_with_box(Box const& b, Range const& range,
            RobustPolicy const&,
            OutputIterator out, Strategy const& strategy)
{
    if (boost::begin(range) == boost::end(range))
    {
        return out;
    }

    typedef typename point_type<OutputLinestring>::type point_type;

    OutputLinestring line_out;

    typedef typename boost::range_iterator<Range const>::type iterator_type;
    iterator_type vertex = boost::begin(range);
    for(iterator_type previous = vertex++;
            vertex != boost::end(range);
            ++previous, ++vertex)
    {
        point_type p1, p2;
        geometry::convert(*previous, p1);
        geometry::convert(*vertex, p2);

        // Clip the segment. Five situations:
        // 1. Segment is invisible, finish line if any (shouldn't occur)
        // 2. Segment is completely visible. Add (p1)-p2 to line
        // 3. Point 1 is invisible (clipped), point 2 is visible. Start new line from p1-p2...
        // 4. Point 1 is visible, point 2 is invisible (clipped). End the line with ...p2
        // 5. Point 1 and point 2 are both invisible (clipped). Start/finish an independant line p1-p2
        //
        // This results in:
        // a. if p1 is clipped, start new line
        // b. if segment is partly or completely visible, add the segment
        // c. if p2 is clipped, end the line

        bool c1 = false;
        bool c2 = false;
        model::referring_segment<point_type> s(p1, p2);

        if (!strategy.clip_segment(b, s, c1, c2))
        {
            strategy.apply(line_out, out);
        }
        else
        {
            // a. If necessary, finish the line and add a start a new one
            if (c1)
            {
                strategy.apply(line_out, out);
            }

            // b. Add p1 only if it is the first point, then add p2
            if (boost::empty(line_out))
            {
                detail::overlay::append_with_duplicates(line_out, p1);
            }
            detail::overlay::append_no_duplicates(line_out, p2,
                                                  strategy.get_equals_point_point_strategy());

            // c. If c2 is clipped, finish the line
            if (c2)
            {
                strategy.apply(line_out, out);
            }
        }

    }

    // Add last part
    strategy.apply(line_out, out);
    return out;
}

}} // namespace detail::intersection
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_CLIP_LINESTRING_HPP

/* clip_linestring.hpp
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
*/