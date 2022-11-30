//=======================================================================
// Copyright 2007 Aaron Windsor
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#ifndef __IS_STRAIGHT_LINE_DRAWING_HPP__
#define __IS_STRAIGHT_LINE_DRAWING_HPP__

#include <boost/config.hpp>
#include <boost/next_prior.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/planar_detail/bucket_sort.hpp>

#include <algorithm>
#include <vector>
#include <set>
#include <map>

namespace boost
{

// Return true exactly when the line segments s1 = ((x1,y1), (x2,y2)) and
// s2 = ((a1,b1), (a2,b2)) intersect in a point other than the endpoints of
// the line segments. The one exception to this rule is when s1 = s2, in
// which case false is returned - this is to accomodate multiple edges
// between the same pair of vertices, which shouldn't invalidate the straight
// line embedding. A tolerance variable epsilon can also be used, which
// defines how far away from the endpoints of s1 and s2 we want to consider
// an intersection.

inline bool intersects(double x1, double y1, double x2, double y2, double a1,
    double b1, double a2, double b2, double epsilon = 0.000001)
{

    if (x1 - x2 == 0)
    {
        std::swap(x1, a1);
        std::swap(y1, b1);
        std::swap(x2, a2);
        std::swap(y2, b2);
    }

    if (x1 - x2 == 0)
    {
        BOOST_USING_STD_MAX();
        BOOST_USING_STD_MIN();

        // two vertical line segments
        double min_y = min BOOST_PREVENT_MACRO_SUBSTITUTION(y1, y2);
        double max_y = max BOOST_PREVENT_MACRO_SUBSTITUTION(y1, y2);
        double min_b = min BOOST_PREVENT_MACRO_SUBSTITUTION(b1, b2);
        double max_b = max BOOST_PREVENT_MACRO_SUBSTITUTION(b1, b2);
        if ((max_y > max_b && max_b > min_y)
            || (max_b > max_y && max_y > min_b))
            return true;
        else
            return false;
    }

    double x_diff = x1 - x2;
    double y_diff = y1 - y2;
    double a_diff = a2 - a1;
    double b_diff = b2 - b1;

    double beta_denominator = b_diff - (y_diff / ((double)x_diff)) * a_diff;

    if (beta_denominator == 0)
    {
        // parallel lines
        return false;
    }

    double beta = (b2 - y2 - (y_diff / ((double)x_diff)) * (a2 - x2))
        / beta_denominator;
    double alpha = (a2 - x2 - beta * (a_diff)) / x_diff;

    double upper_bound = 1 - epsilon;
    double lower_bound = 0 + epsilon;

    return (beta < upper_bound && beta > lower_bound && alpha < upper_bound
        && alpha > lower_bound);
}

template < typename Graph, typename GridPositionMap, typename VertexIndexMap >
bool is_straight_line_drawing(
    const Graph& g, GridPositionMap drawing, VertexIndexMap)
{

    typedef typename graph_traits< Graph >::vertex_descriptor vertex_t;
    typedef typename graph_traits< Graph >::edge_descriptor edge_t;
    typedef typename graph_traits< Graph >::edge_iterator edge_iterator_t;

    typedef std::size_t x_coord_t;
    typedef std::size_t y_coord_t;
    typedef boost::tuple< edge_t, x_coord_t, y_coord_t > edge_event_t;
    typedef typename std::vector< edge_event_t > edge_event_queue_t;

    typedef tuple< y_coord_t, y_coord_t, x_coord_t, x_coord_t >
        active_map_key_t;
    typedef edge_t active_map_value_t;
    typedef std::map< active_map_key_t, active_map_value_t > active_map_t;
    typedef typename active_map_t::iterator active_map_iterator_t;

    edge_event_queue_t edge_event_queue;
    active_map_t active_edges;

    edge_iterator_t ei, ei_end;
    for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
    {
        edge_t e(*ei);
        vertex_t s(source(e, g));
        vertex_t t(target(e, g));
        edge_event_queue.push_back(
            make_tuple(e, static_cast< std::size_t >(drawing[s].x),
                static_cast< std::size_t >(drawing[s].y)));
        edge_event_queue.push_back(
            make_tuple(e, static_cast< std::size_t >(drawing[t].x),
                static_cast< std::size_t >(drawing[t].y)));
    }

    // Order by edge_event_queue by first, then second coordinate
    // (bucket_sort is a stable sort.)
    bucket_sort(edge_event_queue.begin(), edge_event_queue.end(),
        property_map_tuple_adaptor< edge_event_t, 2 >());

    bucket_sort(edge_event_queue.begin(), edge_event_queue.end(),
        property_map_tuple_adaptor< edge_event_t, 1 >());

    typedef typename edge_event_queue_t::iterator event_queue_iterator_t;
    event_queue_iterator_t itr_end = edge_event_queue.end();
    for (event_queue_iterator_t itr = edge_event_queue.begin(); itr != itr_end;
         ++itr)
    {
        edge_t e(get< 0 >(*itr));
        vertex_t source_v(source(e, g));
        vertex_t target_v(target(e, g));
        if (drawing[source_v].y > drawing[target_v].y)
            std::swap(source_v, target_v);

        active_map_key_t key(get(drawing, source_v).y, get(drawing, target_v).y,
            get(drawing, source_v).x, get(drawing, target_v).x);

        active_map_iterator_t a_itr = active_edges.find(key);
        if (a_itr == active_edges.end())
        {
            active_edges[key] = e;
        }
        else
        {
            active_map_iterator_t before, after;
            if (a_itr == active_edges.begin())
                before = active_edges.end();
            else
                before = prior(a_itr);
            after = boost::next(a_itr);

            if (before != active_edges.end())
            {

                edge_t f = before->second;
                vertex_t e_source(source(e, g));
                vertex_t e_target(target(e, g));
                vertex_t f_source(source(f, g));
                vertex_t f_target(target(f, g));

                if (intersects(drawing[e_source].x, drawing[e_source].y,
                        drawing[e_target].x, drawing[e_target].y,
                        drawing[f_source].x, drawing[f_source].y,
                        drawing[f_target].x, drawing[f_target].y))
                    return false;
            }

            if (after != active_edges.end())
            {

                edge_t f = after->second;
                vertex_t e_source(source(e, g));
                vertex_t e_target(target(e, g));
                vertex_t f_source(source(f, g));
                vertex_t f_target(target(f, g));

                if (intersects(drawing[e_source].x, drawing[e_source].y,
                        drawing[e_target].x, drawing[e_target].y,
                        drawing[f_source].x, drawing[f_source].y,
                        drawing[f_target].x, drawing[f_target].y))
                    return false;
            }

            active_edges.erase(a_itr);
        }
    }

    return true;
}

template < typename Graph, typename GridPositionMap >
bool is_straight_line_drawing(const Graph& g, GridPositionMap drawing)
{
    return is_straight_line_drawing(g, drawing, get(vertex_index, g));
}

}

#endif // __IS_STRAIGHT_LINE_DRAWING_HPP__

/* is_straight_line_drawing.hpp
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
*/