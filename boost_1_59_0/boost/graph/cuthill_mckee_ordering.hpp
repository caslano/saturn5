//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Copyright 2004, 2005 Trustees of Indiana University
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek,
//          Doug Gregor, D. Kevin McGrath
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#ifndef BOOST_GRAPH_CUTHILL_MCKEE_HPP
#define BOOST_GRAPH_CUTHILL_MCKEE_HPP

#include <boost/config.hpp>
#include <boost/graph/detail/sparse_ordering.hpp>
#include <boost/graph/graph_utility.hpp>
#include <algorithm>

/*
  (Reverse) Cuthill-McKee Algorithm for matrix reordering
*/

namespace boost
{

namespace detail
{

    template < typename OutputIterator, typename Buffer, typename DegreeMap >
    class bfs_rcm_visitor : public default_bfs_visitor
    {
    public:
        bfs_rcm_visitor(OutputIterator* iter, Buffer* b, DegreeMap deg)
        : permutation(iter), Qptr(b), degree(deg)
        {
        }
        template < class Vertex, class Graph >
        void examine_vertex(Vertex u, Graph&)
        {
            *(*permutation)++ = u;
            index_begin = Qptr->size();
        }
        template < class Vertex, class Graph >
        void finish_vertex(Vertex, Graph&)
        {
            using std::sort;

            typedef typename property_traits< DegreeMap >::value_type ds_type;

            typedef indirect_cmp< DegreeMap, std::less< ds_type > > Compare;
            Compare comp(degree);

            sort(Qptr->begin() + index_begin, Qptr->end(), comp);
        }

    protected:
        OutputIterator* permutation;
        int index_begin;
        Buffer* Qptr;
        DegreeMap degree;
    };

} // namespace detail

// Reverse Cuthill-McKee algorithm with a given starting Vertex.
//
// If user provides a reverse iterator, this will be a reverse-cuthill-mckee
// algorithm, otherwise it will be a standard CM algorithm

template < class Graph, class OutputIterator, class ColorMap, class DegreeMap >
OutputIterator cuthill_mckee_ordering(const Graph& g,
    std::deque< typename graph_traits< Graph >::vertex_descriptor >
        vertex_queue,
    OutputIterator permutation, ColorMap color, DegreeMap degree)
{

    // create queue, visitor...don't forget namespaces!
    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
    typedef typename boost::sparse::sparse_ordering_queue< Vertex > queue;
    typedef typename detail::bfs_rcm_visitor< OutputIterator, queue, DegreeMap >
        Visitor;
    typedef typename property_traits< ColorMap >::value_type ColorValue;
    typedef color_traits< ColorValue > Color;

    queue Q;

    // create a bfs_rcm_visitor as defined above
    Visitor vis(&permutation, &Q, degree);

    typename graph_traits< Graph >::vertex_iterator ui, ui_end;

    // Copy degree to pseudo_degree
    // initialize the color map
    for (boost::tie(ui, ui_end) = vertices(g); ui != ui_end; ++ui)
    {
        put(color, *ui, Color::white());
    }

    while (!vertex_queue.empty())
    {
        Vertex s = vertex_queue.front();
        vertex_queue.pop_front();

        // call BFS with visitor
        breadth_first_visit(g, s, Q, vis, color);
    }
    return permutation;
}

// This is the case where only a single starting vertex is supplied.
template < class Graph, class OutputIterator, class ColorMap, class DegreeMap >
OutputIterator cuthill_mckee_ordering(const Graph& g,
    typename graph_traits< Graph >::vertex_descriptor s,
    OutputIterator permutation, ColorMap color, DegreeMap degree)
{

    std::deque< typename graph_traits< Graph >::vertex_descriptor >
        vertex_queue;
    vertex_queue.push_front(s);

    return cuthill_mckee_ordering(g, vertex_queue, permutation, color, degree);
}

// This is the version of CM which selects its own starting vertex
template < class Graph, class OutputIterator, class ColorMap, class DegreeMap >
OutputIterator cuthill_mckee_ordering(const Graph& G,
    OutputIterator permutation, ColorMap color, DegreeMap degree)
{
    if (boost::graph::has_no_vertices(G))
        return permutation;

    typedef typename boost::graph_traits< Graph >::vertex_descriptor Vertex;
    typedef typename property_traits< ColorMap >::value_type ColorValue;
    typedef color_traits< ColorValue > Color;

    std::deque< Vertex > vertex_queue;

    // Mark everything white
    BGL_FORALL_VERTICES_T(v, G, Graph) put(color, v, Color::white());

    // Find one vertex from each connected component
    BGL_FORALL_VERTICES_T(v, G, Graph)
    {
        if (get(color, v) == Color::white())
        {
            depth_first_visit(G, v, dfs_visitor<>(), color);
            vertex_queue.push_back(v);
        }
    }

    // Find starting nodes for all vertices
    // TBD: How to do this with a directed graph?
    for (typename std::deque< Vertex >::iterator i = vertex_queue.begin();
         i != vertex_queue.end(); ++i)
        *i = find_starting_node(G, *i, color, degree);

    return cuthill_mckee_ordering(G, vertex_queue, permutation, color, degree);
}

template < typename Graph, typename OutputIterator, typename VertexIndexMap >
OutputIterator cuthill_mckee_ordering(
    const Graph& G, OutputIterator permutation, VertexIndexMap index_map)
{
    if (boost::graph::has_no_vertices(G))
        return permutation;

    std::vector< default_color_type > colors(num_vertices(G));
    return cuthill_mckee_ordering(G, permutation,
        make_iterator_property_map(&colors[0], index_map, colors[0]),
        make_out_degree_map(G));
}

template < typename Graph, typename OutputIterator >
inline OutputIterator cuthill_mckee_ordering(
    const Graph& G, OutputIterator permutation)
{
    return cuthill_mckee_ordering(G, permutation, get(vertex_index, G));
}
} // namespace boost

#endif // BOOST_GRAPH_CUTHILL_MCKEE_HPP

/* cuthill_mckee_ordering.hpp
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
*/