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