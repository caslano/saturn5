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
8tzKSu09B8INOpGJ/jF8nvfkurT5mvvZn4PbBfSy3RYULJ6C+zIolOdz7iu8D1rF71x5qyjXq28foPdMGCshcv/0JsV7xXK/Ix5iC4TefsCTVJaDrtps6JRCbgKF58W+HOLv+Z2byjWBn23mUL7KRAseX5upTErweFHPv8Qf9976Dxe+AUGiUcBA29Sg29EfwSfHWMsAh9jv/6L/WNDl+0I3KRV49KMMap8Z0tbY2PU0Ru2e44ruyET4QeI/GWOWK7un6a7UxDvo/WNoorjk718/RkQTXc/f88719kThDqonjgWfpHVzL8maUV7CdXkeOJV4W6HvWPoFJguNR7VrcRvVp0+swcMsLKcVeDYSz9culWcR1aumSZg3sVzb34NHDTuLPPjxeBPCuP+23T1aWQJEHFbSpkEhKl32h1Y28324a4nXYb4PV/Lp7+xbUn6KY425AOWuKpuON96WO07301j6ycbzJ7dFj5BTYnO91X73OlR51eB7luS9YZpbWD+QVgXDftNjlLcn698iXPX18fo0yQzSxj/qIZlkjeC86XfDu/lyUaPfpFHewuVcOo78ndU7lEnWUXV0UF9pTmMhXntHSg9yTt6bTNb6akyscMR04P5XQ/l5wdnWligm2ZqLlbZu4ne2h/xXB31iW1i/WvEPe0DZ78TzOvfP14h/n9Mh7gn6PChFWYi1wT/MIb9bjqc0EmPIHlWM9h48T60TXmsWbFbDP8Ae8Hmb2hdOyWc9j3uLuV/fReW84Ockv94mq/262Ab6kt4CeK6nOmwUa54DZnB/3AP0oXq5jfrjNNPY7Mw8F4GjiacX8ayjPkuqZqg/freNdKL1Pm/R63QX4nUCyRFozztJDrYspjmLXj65y8r1+8EbAscRX3fXlMBetprgAPEdXO8Qh2hd3xd9BTyy/3W31TqndDb6xmGStUrufwtoTtlqJ7+ss0Qb9V+Ev078z/EaIcuKDYch89gG67vxr8lfj8q5FuELSUZ9V7Qsp9y6aC/0TeNq1A56L8J3Bevj+Mb6r4hVISQPPI+SvDMxLS6XZ/qAKvdY1Ca7gMY8NGPSbF7qVJkfI487qV986pI81ned1P/3bVN5UpToy/p32xBz3z6v1hvJe87l7b7pVaC8TzyPGDwe9h3DgF0eJJ0dbQ6AP5DKvsQUp5IfmVE+tiPXdxO9e3DUc1yFeKAZ6yrJmQXeUJJzE41/h5P3SpVGm/bdYsw9NQidTHltZ5rLi0orcrEZFsackUn7lU6I00i+s1lDtGo8dXQTY1meH3jXkLwfLp8X2Vybrl8YTeWfxn69P7Sk/omuIhpSOea6jP6ZV4imNXTGkNZ8SssZa21/agziOQOePcRzlvNjjB/eXlIfonYxwvFSUIu/EL7GlI9ZLtNzntyv/LRKDbvBt4vo4BtJtMv3206p21dZSdrcJp2QFCrzWNGC91BjKa89YvvZOgWsC+kq3gmJEY767UX/+jv8A3HxWG1pdAp43abrd+VQ/KupPuxOLqu6HdVt/SENz/lP30dFIWwqxW8Va/RBjDPtqzDxLAflNeI5YqlPLN16dUp9VPOckG+ucM7LEWBt+5nOwqifLJrDDqEO4Zd9/SXHKfFnH+rv4DlJ7XMwxjweZbl43MxfTzz22sbMAfC9vZzqE/MY58fzuyVqUB8/D9AcGMZ+1IRpTlyJ8OmUH5fLXDbTI4GUIyheC7mWdyD/XBEhJpCsJQrqGrKQApUtK5Lao3RyUWmB+TvyIirbHDv5ZdnqkwyB8CZUtpmxpmeUivLpmFUrCwry9ecBjLd1lNa3Md7upqd1FHwPE98HMS5TfWtfCwrcBeWFBSVQ8ylm/h3AL4h/c4ysWzk=
*/