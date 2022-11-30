//
//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//
#ifndef BOOST_GRAPH_TOPOLOGICAL_SORT_HPP
#define BOOST_GRAPH_TOPOLOGICAL_SORT_HPP

#include <boost/config.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/exception.hpp>
#include <boost/throw_exception.hpp>

namespace boost
{

// Topological sort visitor
//
// This visitor merely writes the linear ordering into an
// OutputIterator. The OutputIterator could be something like an
// ostream_iterator, or it could be a back/front_insert_iterator.
// Note that if it is a back_insert_iterator, the recorded order is
// the reverse topological order. On the other hand, if it is a
// front_insert_iterator, the recorded order is the topological
// order.
//
template < typename OutputIterator >
struct topo_sort_visitor : public dfs_visitor<>
{
    topo_sort_visitor(OutputIterator _iter) : m_iter(_iter) {}

    template < typename Edge, typename Graph >
    void back_edge(const Edge&, Graph&)
    {
        BOOST_THROW_EXCEPTION(not_a_dag());
    }

    template < typename Vertex, typename Graph >
    void finish_vertex(const Vertex& u, Graph&)
    {
        *m_iter++ = u;
    }

    OutputIterator m_iter;
};

// Topological Sort
//
// The topological sort algorithm creates a linear ordering
// of the vertices such that if edge (u,v) appears in the graph,
// then u comes before v in the ordering. The graph must
// be a directed acyclic graph (DAG). The implementation
// consists mainly of a call to depth-first search.
//

template < typename VertexListGraph, typename OutputIterator, typename P,
    typename T, typename R >
void topological_sort(VertexListGraph& g, OutputIterator result,
    const bgl_named_params< P, T, R >& params)
{
    typedef topo_sort_visitor< OutputIterator > TopoVisitor;
    depth_first_search(g, params.visitor(TopoVisitor(result)));
}

template < typename VertexListGraph, typename OutputIterator >
void topological_sort(VertexListGraph& g, OutputIterator result)
{
    topological_sort(
        g, result, bgl_named_params< int, buffer_param_t >(0)); // bogus
}

} // namespace boost

#endif /*BOOST_GRAPH_TOPOLOGICAL_SORT_H*/

/* topological_sort.hpp
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
*/