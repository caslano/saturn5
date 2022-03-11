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