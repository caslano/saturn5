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