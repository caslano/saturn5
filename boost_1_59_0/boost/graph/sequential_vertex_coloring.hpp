//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Copyright 2004 The Trustees of Indiana University
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#ifndef BOOST_GRAPH_SEQUENTIAL_VERTEX_COLORING_HPP
#define BOOST_GRAPH_SEQUENTIAL_VERTEX_COLORING_HPP

#include <vector>
#include <boost/graph/graph_traits.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/limits.hpp>

#ifdef BOOST_NO_TEMPLATED_ITERATOR_CONSTRUCTORS
#include <iterator>
#endif

/* This algorithm is to find coloring of a graph

   Algorithm:
   Let G = (V,E) be a graph with vertices (somehow) ordered v_1, v_2, ...,
   v_n. For k = 1, 2, ..., n the sequential algorithm assigns v_k to the
   smallest possible color.

   Reference:

   Thomas F. Coleman and Jorge J. More, Estimation of sparse Jacobian
   matrices and graph coloring problems. J. Numer. Anal. V20, P187-209, 1983

   v_k is stored as o[k] here.

   The color of the vertex v will be stored in color[v].
   i.e., vertex v belongs to coloring color[v] */

namespace boost
{
template < class VertexListGraph, class OrderPA, class ColorMap >
typename property_traits< ColorMap >::value_type sequential_vertex_coloring(
    const VertexListGraph& G, OrderPA order, ColorMap color)
{
    typedef graph_traits< VertexListGraph > GraphTraits;
    typedef typename GraphTraits::vertex_descriptor Vertex;
    typedef typename property_traits< ColorMap >::value_type size_type;

    size_type max_color = 0;
    const size_type V = num_vertices(G);

    // We need to keep track of which colors are used by
    // adjacent vertices. We do this by marking the colors
    // that are used. The mark array contains the mark
    // for each color. The length of mark is the
    // number of vertices since the maximum possible number of colors
    // is the number of vertices.
    std::vector< size_type > mark(V,
        std::numeric_limits< size_type >::max
            BOOST_PREVENT_MACRO_SUBSTITUTION());

    // Initialize colors
    typename GraphTraits::vertex_iterator v, vend;
    for (boost::tie(v, vend) = vertices(G); v != vend; ++v)
        put(color, *v, V - 1);

    // Determine the color for every vertex one by one
    for (size_type i = 0; i < V; i++)
    {
        Vertex current = get(order, i);
        typename GraphTraits::adjacency_iterator v, vend;

        // Mark the colors of vertices adjacent to current.
        // i can be the value for marking since i increases successively
        for (boost::tie(v, vend) = adjacent_vertices(current, G); v != vend;
             ++v)
            mark[get(color, *v)] = i;

        // Next step is to assign the smallest un-marked color
        // to the current vertex.
        size_type j = 0;

        // Scan through all useable colors, find the smallest possible
        // color that is not used by neighbors.  Note that if mark[j]
        // is equal to i, color j is used by one of the current vertex's
        // neighbors.
        while (j < max_color && mark[j] == i)
            ++j;

        if (j == max_color) // All colors are used up. Add one more color
            ++max_color;

        // At this point, j is the smallest possible color
        put(color, current, j); // Save the color of vertex current
    }

    return max_color;
}

template < class VertexListGraph, class ColorMap >
typename property_traits< ColorMap >::value_type sequential_vertex_coloring(
    const VertexListGraph& G, ColorMap color)
{
    typedef typename graph_traits< VertexListGraph >::vertex_descriptor
        vertex_descriptor;
    typedef typename graph_traits< VertexListGraph >::vertex_iterator
        vertex_iterator;

    std::pair< vertex_iterator, vertex_iterator > v = vertices(G);
#ifndef BOOST_NO_TEMPLATED_ITERATOR_CONSTRUCTORS
    std::vector< vertex_descriptor > order(v.first, v.second);
#else
    std::vector< vertex_descriptor > order;
    order.reserve(std::distance(v.first, v.second));
    while (v.first != v.second)
        order.push_back(*v.first++);
#endif
    return sequential_vertex_coloring(G,
        make_iterator_property_map(order.begin(), identity_property_map(),
            graph_traits< VertexListGraph >::null_vertex()),
        color);
}
}

#endif

/* sequential_vertex_coloring.hpp
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
*/