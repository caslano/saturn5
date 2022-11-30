// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2015-2020.
// Modifications copyright (c) 2015-2020 Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_CLIP_LINESTRING_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_CLIP_LINESTRING_HPP

#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>

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