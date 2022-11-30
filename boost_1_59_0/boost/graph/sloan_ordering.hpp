//
//=======================================================================
// Copyright 2002 Marc Wintermantel (wintermantel@even-ag.ch)
// ETH Zurich, Center of Structure Technologies
// (https://web.archive.org/web/20050307090307/http://www.structures.ethz.ch/)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//

#ifndef BOOST_GRAPH_SLOAN_HPP
#define BOOST_GRAPH_SLOAN_HPP

#define WEIGHT1 1 // default weight for the distance in the Sloan algorithm
#define WEIGHT2 2 // default weight for the degree in the Sloan algorithm

#include <boost/config.hpp>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
#include <boost/pending/queue.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/properties.hpp>
#include <boost/pending/indirect_cmp.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cuthill_mckee_ordering.hpp>

////////////////////////////////////////////////////////////
//
// Sloan-Algorithm for graph reordering
//(optimzes profile and wavefront, not primiraly bandwidth
//
////////////////////////////////////////////////////////////

namespace boost
{

/////////////////////////////////////////////////////////////////////////
// Function that returns the maximum depth of
// a rooted level strucutre (RLS)
//
/////////////////////////////////////////////////////////////////////////
template < class Distance > typename Distance::value_type RLS_depth(Distance& d)
{
    typename Distance::value_type h_s = 0;
    typename Distance::iterator iter;

    for (iter = d.begin(); iter != d.end(); ++iter)
    {
        if (*iter > h_s)
        {
            h_s = *iter;
        }
    }

    return h_s;
}

/////////////////////////////////////////////////////////////////////////
// Function that returns the width of the largest level of
// a rooted level strucutre (RLS)
//
/////////////////////////////////////////////////////////////////////////
template < class Distance, class my_int >
typename Distance::value_type RLS_max_width(Distance& d, my_int depth)
{

    typedef typename Distance::value_type Degree;

    // Searching for the maximum width of a level
    std::vector< Degree > dummy_width(depth + 1, 0);
    typename std::vector< Degree >::iterator my_it;
    typename Distance::iterator iter;
    Degree w_max = 0;

    for (iter = d.begin(); iter != d.end(); ++iter)
    {
        dummy_width[*iter]++;
    }

    for (my_it = dummy_width.begin(); my_it != dummy_width.end(); ++my_it)
    {
        if (*my_it > w_max)
            w_max = *my_it;
    }

    return w_max;
}

/////////////////////////////////////////////////////////////////////////
// Function for finding a good starting node for Sloan algorithm
//
// This is to find a good starting node. "good" is in the sense
// of the ordering generated.
/////////////////////////////////////////////////////////////////////////
template < class Graph, class ColorMap, class DegreeMap >
typename graph_traits< Graph >::vertex_descriptor sloan_start_end_vertices(
    Graph& G, typename graph_traits< Graph >::vertex_descriptor& s,
    ColorMap color, DegreeMap degree)
{
    typedef typename property_traits< DegreeMap >::value_type Degree;
    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
    typedef typename std::vector<
        typename graph_traits< Graph >::vertices_size_type >::iterator vec_iter;
    typedef typename graph_traits< Graph >::vertices_size_type size_type;

    typedef typename property_map< Graph, vertex_index_t >::const_type VertexID;

    s = *(vertices(G).first);
    Vertex e = s;
    Vertex i;
    Degree my_degree = get(degree, s);
    Degree dummy, h_i, h_s, w_i, w_e;
    bool new_start = true;
    Degree maximum_degree = 0;

    // Creating a std-vector for storing the distance from the start vertex in
    // dist
    std::vector< typename graph_traits< Graph >::vertices_size_type > dist(
        num_vertices(G), 0);

    // Wrap a property_map_iterator around the std::iterator
    boost::iterator_property_map< vec_iter, VertexID, size_type, size_type& >
        dist_pmap(dist.begin(), get(vertex_index, G));

    // Creating a property_map for the indices of a vertex
    typename property_map< Graph, vertex_index_t >::type index_map
        = get(vertex_index, G);

    // Creating a priority queue
    typedef indirect_cmp< DegreeMap, std::greater< Degree > > Compare;
    Compare comp(degree);
    std::priority_queue< Vertex, std::vector< Vertex >, Compare > degree_queue(
        comp);

    // step 1
    // Scan for the vertex with the smallest degree and the maximum degree
    typename graph_traits< Graph >::vertex_iterator ui, ui_end;
    for (boost::tie(ui, ui_end) = vertices(G); ui != ui_end; ++ui)
    {
        dummy = get(degree, *ui);

        if (dummy < my_degree)
        {
            my_degree = dummy;
            s = *ui;
        }

        if (dummy > maximum_degree)
        {
            maximum_degree = dummy;
        }
    }
    // end 1

    do
    {
        new_start = false; // Setting the loop repetition status to false

        // step 2
        // initialize the the disance std-vector with 0
        for (typename std::vector< typename graph_traits<
                 Graph >::vertices_size_type >::iterator iter
             = dist.begin();
             iter != dist.end(); ++iter)
            *iter = 0;

        // generating the RLS (rooted level structure)
        breadth_first_search(G, s,
            visitor(
                make_bfs_visitor(record_distances(dist_pmap, on_tree_edge()))));

        // end 2

        // step 3
        // calculating the depth of the RLS
        h_s = RLS_depth(dist);

        // step 4
        // pushing one node of each degree in an ascending manner into
        // degree_queue
        std::vector< bool > shrink_trace(maximum_degree, false);
        for (boost::tie(ui, ui_end) = vertices(G); ui != ui_end; ++ui)
        {
            dummy = get(degree, *ui);

            if ((dist[index_map[*ui]] == h_s) && (!shrink_trace[dummy]))
            {
                degree_queue.push(*ui);
                shrink_trace[dummy] = true;
            }
        }

        // end 3 & 4

        // step 5
        // Initializing w
        w_e = (std::numeric_limits< Degree >::max)();
        // end 5

        // step 6
        // Testing for termination
        while (!degree_queue.empty())
        {
            i = degree_queue.top(); // getting the node with the lowest degree
                                    // from the degree queue
            degree_queue.pop(); // ereasing the node with the lowest degree from
                                // the degree queue

            // generating a RLS
            for (typename std::vector< typename graph_traits<
                     Graph >::vertices_size_type >::iterator iter
                 = dist.begin();
                 iter != dist.end(); ++iter)
                *iter = 0;

            breadth_first_search(G, i,
                boost::visitor(make_bfs_visitor(
                    record_distances(dist_pmap, on_tree_edge()))));

            // Calculating depth and width of the rooted level
            h_i = RLS_depth(dist);
            w_i = RLS_max_width(dist, h_i);

            // Testing for termination
            if ((h_i > h_s) && (w_i < w_e))
            {
                h_s = h_i;
                s = i;
                while (!degree_queue.empty())
                    degree_queue.pop();
                new_start = true;
            }
            else if (w_i < w_e)
            {
                w_e = w_i;
                e = i;
            }
        }
        // end 6

    } while (new_start);

    return e;
}

//////////////////////////////////////////////////////////////////////////
// Sloan algorithm with a given starting Vertex.
//
// This algorithm requires user to provide a starting vertex to
// compute Sloan ordering.
//////////////////////////////////////////////////////////////////////////
template < class Graph, class OutputIterator, class ColorMap, class DegreeMap,
    class PriorityMap, class Weight >
OutputIterator sloan_ordering(Graph& g,
    typename graph_traits< Graph >::vertex_descriptor s,
    typename graph_traits< Graph >::vertex_descriptor e,
    OutputIterator permutation, ColorMap color, DegreeMap degree,
    PriorityMap priority, Weight W1, Weight W2)
{
    // typedef typename property_traits<DegreeMap>::value_type Degree;
    typedef typename property_traits< PriorityMap >::value_type Degree;
    typedef typename property_traits< ColorMap >::value_type ColorValue;
    typedef color_traits< ColorValue > Color;
    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
    typedef typename std::vector<
        typename graph_traits< Graph >::vertices_size_type >::iterator vec_iter;
    typedef typename graph_traits< Graph >::vertices_size_type size_type;

    typedef typename property_map< Graph, vertex_index_t >::const_type VertexID;

    // Creating a std-vector for storing the distance from the end vertex in it
    typename std::vector< typename graph_traits< Graph >::vertices_size_type >
        dist(num_vertices(g), 0);

    // Wrap a property_map_iterator around the std::iterator
    boost::iterator_property_map< vec_iter, VertexID, size_type, size_type& >
        dist_pmap(dist.begin(), get(vertex_index, g));

    breadth_first_search(g, e,
        visitor(make_bfs_visitor(record_distances(dist_pmap, on_tree_edge()))));

    // Creating a property_map for the indices of a vertex
    typename property_map< Graph, vertex_index_t >::type index_map
        = get(vertex_index, g);

    // Sets the color and priority to their initial status
    Degree cdeg;
    typename graph_traits< Graph >::vertex_iterator ui, ui_end;
    for (boost::tie(ui, ui_end) = vertices(g); ui != ui_end; ++ui)
    {
        put(color, *ui, Color::white());
        cdeg = get(degree, *ui) + 1;
        put(priority, *ui, W1 * dist[index_map[*ui]] - W2 * cdeg);
    }

    // Priority list
    typedef indirect_cmp< PriorityMap, std::greater< Degree > > Compare;
    Compare comp(priority);
    std::list< Vertex > priority_list;

    // Some more declarations
    typename graph_traits< Graph >::out_edge_iterator ei, ei_end, ei2, ei2_end;
    Vertex u, v, w;

    put(color, s,
        Color::green()); // Sets the color of the starting vertex to gray
    priority_list.push_front(s); // Puts s into the priority_list

    while (!priority_list.empty())
    {
        priority_list.sort(comp); // Orders the elements in the priority list in
                                  // an ascending manner

        u = priority_list
                .front(); // Accesses the last element in the priority list
        priority_list
            .pop_front(); // Removes the last element in the priority list

        if (get(color, u) == Color::green())
        {
            // for-loop over all out-edges of vertex u
            for (boost::tie(ei, ei_end) = out_edges(u, g); ei != ei_end; ++ei)
            {
                v = target(*ei, g);

                put(priority, v, get(priority, v) + W2); // updates the priority

                if (get(color, v)
                    == Color::white()) // test if the vertex is inactive
                {
                    put(color, v,
                        Color::green()); // giving the vertex a preactive status
                    priority_list.push_front(
                        v); // writing the vertex in the priority_queue
                }
            }
        }

        // Here starts step 8
        *permutation++
            = u; // Puts u to the first position in the permutation-vector
        put(color, u, Color::black()); // Gives u an inactive status

        // for loop over all the adjacent vertices of u
        for (boost::tie(ei, ei_end) = out_edges(u, g); ei != ei_end; ++ei)
        {

            v = target(*ei, g);

            if (get(color, v) == Color::green())
            { // tests if the vertex is inactive

                put(color, v,
                    Color::red()); // giving the vertex an active status
                put(priority, v, get(priority, v) + W2); // updates the priority

                // for loop over alll adjacent vertices of v
                for (boost::tie(ei2, ei2_end) = out_edges(v, g); ei2 != ei2_end;
                     ++ei2)
                {
                    w = target(*ei2, g);

                    if (get(color, w) != Color::black())
                    { // tests if vertex is postactive

                        put(priority, w,
                            get(priority, w) + W2); // updates the priority

                        if (get(color, w) == Color::white())
                        {

                            put(color, w, Color::green()); // gives the vertex a
                                                           // preactive status
                            priority_list.push_front(
                                w); // puts the vertex into the priority queue

                        } // end if

                    } // end if

                } // end for

            } // end if

        } // end for

    } // end while

    return permutation;
}

/////////////////////////////////////////////////////////////////////////////////////////
// Same algorithm as before, but without the weights given (taking default
// weights
template < class Graph, class OutputIterator, class ColorMap, class DegreeMap,
    class PriorityMap >
OutputIterator sloan_ordering(Graph& g,
    typename graph_traits< Graph >::vertex_descriptor s,
    typename graph_traits< Graph >::vertex_descriptor e,
    OutputIterator permutation, ColorMap color, DegreeMap degree,
    PriorityMap priority)
{
    return sloan_ordering(
        g, s, e, permutation, color, degree, priority, WEIGHT1, WEIGHT2);
}

//////////////////////////////////////////////////////////////////////////
// Sloan algorithm without a given starting Vertex.
//
// This algorithm finds a good starting vertex itself to
// compute Sloan-ordering.
//////////////////////////////////////////////////////////////////////////

template < class Graph, class OutputIterator, class Color, class Degree,
    class Priority, class Weight >
inline OutputIterator sloan_ordering(Graph& G, OutputIterator permutation,
    Color color, Degree degree, Priority priority, Weight W1, Weight W2)
{
    typedef typename boost::graph_traits< Graph >::vertex_descriptor Vertex;

    Vertex s, e;
    e = sloan_start_end_vertices(G, s, color, degree);

    return sloan_ordering(
        G, s, e, permutation, color, degree, priority, W1, W2);
}

/////////////////////////////////////////////////////////////////////////////////////////
// Same as before, but without given weights (default weights are taken instead)
template < class Graph, class OutputIterator, class Color, class Degree,
    class Priority >
inline OutputIterator sloan_ordering(Graph& G, OutputIterator permutation,
    Color color, Degree degree, Priority priority)
{
    return sloan_ordering(
        G, permutation, color, degree, priority, WEIGHT1, WEIGHT2);
}

} // namespace boost

#endif // BOOST_GRAPH_SLOAN_HPP

/* sloan_ordering.hpp
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
*/