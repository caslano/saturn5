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