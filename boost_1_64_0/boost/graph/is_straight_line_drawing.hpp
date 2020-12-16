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
f/Yusz2V2vQPvsfsFQa/+j7z16zy4WL0Wyt9tpj/3mr/a/Y3P7Da/+DuJiIWJsXBnBjYFf/GYl9I3GNHI7sZW/YyffEuIOu7Jas7K7u41hXTxuLZL9nxWj+94/2R/W5AXLLEpLS4ZItJfdmx4JB7pygW5Vu2mWRdM8uGZpr9wtVZqe5Uqi3r8x+xY2ai/at3zb/Uqu/umQ+qZH/Hvvm3T7mf308HxcQf31MPtJO/YF/dEz9V82+/n+xPpez/ff0P+Jr6XWvyL9l1f7keW1/dHWbwM//79t/DqVR+im/uv6N27C/dg7Pv+U378F+yQn+5H0+aPU7G7HJss8/pmp3O0Ox1VNnd7YTc/Y75rWRSXHV/G9kVT8diaegXrtZpcfLrtVrh4k+swjL5VGRq1eFj+flndPccQ3fXYSYe93dm52GZvUfS7D4yP/N7xZis1OZ3i7/694oYZU2tHM9v9em/NOtUxd0ph9y9sky7uMy7lJ54//h59531+RdNvd/6u8Y/YfLFp1aHqd/q6e+Ze+r/P3/xny8AUEsDBBQAAAAIAMCxvEoQmMqqtSMJAADQIwARAAAAYmluNjQvb3BlbnNzbC5wZGLsXQl8VMUZn93NnQDZHBuIgOFQzoQEQjhEIBckkIscHBpdN8kGVpPdZXeDUC2HpZ6gaFW8wQPrgQJVEUUrgi1CqVA8iloVj9YLFRCRtir9zzfz5r0sCdhqfz1+7/sxfG/+8833zTfXm5n3Xrbc0xjwBX3NoYzCYYVDhmSU10zKGJWVnd0lLr2ohoESGbOCnY3/DsQxonFWZpJJJplkkkkmmWSSSSaZZJJJJv0P0ZZvjptkkkkmmWSSSSaZZJJJJplkkkn/5zTaxn4M2n/cJJNMMskkk0wyySSTTDLJJJNM+q+l+J05ltH0nj8FIo5HELepeDgfzCJTGVsc9iVAg8fnDIZY1oT8OnE5cSI7fCiOWRO57gRmYQuZLcmayvVW+S52B+qC7kBVwB10e0PsEMctOl7hC2lJhynNqqeVel2NIc88N+O4TcfLXfM9rW2tQpfNKD/P1eJpYocmsejUSHzSEGL4D2Vy1tUUVzvzC2tLp5fWznJWVRfXFFcUFnMXZuR2kginDj2q/Kitchbml5UV5BdOhURpZTUXLSmdXMLIn47TKyqry/PLNL86limrnCH96Di9tGJ6fllp0UllCivrKmrZl4cPFRj8juB+dyQuvO4wifv8NHwWPk2pLHBWFkwpLqx1VhTXOqvza4thqqK2urLMWVyRX1BWDJvCt5PKlufPdBbkVxTNKC2qFfUVcVL5oprCKmdt/mThc/RJZalynJPK8ifXoJ7Pgf8R0v+oRHaynCKPqItTivF6ubajeimt7LBaqE5OJldTi/rIL6usKHZOryyrKy+W7ds+T+eufil8tUlfY4Sves7v4ypJnegp1z3YpvlaWFleWp4/uVikOktR5LJZwr/wtBHDC0prq4un1ZVWF8v+GnFifmdZaUF1frXQEROeXoOSVEyuyC8vrimdXAE1on8lhstV5GO0FjuLUfJZVZWlFbXS3mJ2Yplrq9HFi4oL6iYX5dfmMynXSfkx+icVV8MB5WO1c3pxdU1pZQX68RQeGw5bHadRnsj2eGmFxGMILyouK64tLnJyF51lxRWTa0vgo54+vZZ3oMn5Ve0kRFtIp2tnVRXTmCos0MbfccpbWlZeXFtSWeSs4c1bg6lHjD3udk3pOcXa3CucRg6UrsQp8lRPz9fmqbD04hI9LSYsrQB6CwvKKgunarp1H0R9qrrS8bxchUcY8UnVleXOuory/AqYKBJ11nm6s7q4Nr+0wplfVVVUWY4rrS4SjXkKqQ4qa2o=
*/