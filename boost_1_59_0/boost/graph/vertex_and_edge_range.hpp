// Copyright 2004 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine

#ifndef BOOST_GRAPH_VERTEX_AND_EDGE_RANGE_HPP
#define BOOST_GRAPH_VERTEX_AND_EDGE_RANGE_HPP

#include <boost/graph/graph_traits.hpp>
#include <iterator>

namespace boost
{

namespace graph
{
    template < typename Graph, typename VertexIterator, typename EdgeIterator >
    class vertex_and_edge_range
    {
        typedef graph_traits< Graph > traits_type;

    public:
        typedef typename traits_type::directed_category directed_category;
        typedef
            typename traits_type::edge_parallel_category edge_parallel_category;
        struct traversal_category : public virtual vertex_list_graph_tag,
                                    public virtual edge_list_graph_tag
        {
        };

        typedef std::size_t vertices_size_type;
        typedef VertexIterator vertex_iterator;
        typedef typename std::iterator_traits< VertexIterator >::value_type
            vertex_descriptor;

        typedef EdgeIterator edge_iterator;
        typedef typename std::iterator_traits< EdgeIterator >::value_type
            edge_descriptor;

        typedef std::size_t edges_size_type;

        typedef void adjacency_iterator;
        typedef void out_edge_iterator;
        typedef void in_edge_iterator;
        typedef void degree_size_type;

        static vertex_descriptor null_vertex()
        {
            return traits_type::null_vertex();
        }

        vertex_and_edge_range(const Graph& g, VertexIterator first_v,
            VertexIterator last_v, vertices_size_type n, EdgeIterator first_e,
            EdgeIterator last_e, edges_size_type m)
        : g(&g)
        , first_vertex(first_v)
        , last_vertex(last_v)
        , m_num_vertices(n)
        , first_edge(first_e)
        , last_edge(last_e)
        , m_num_edges(m)
        {
        }

        vertex_and_edge_range(const Graph& g, VertexIterator first_v,
            VertexIterator last_v, EdgeIterator first_e, EdgeIterator last_e)
        : g(&g)
        , first_vertex(first_v)
        , last_vertex(last_v)
        , first_edge(first_e)
        , last_edge(last_e)
        {
            m_num_vertices = std::distance(first_v, last_v);
            m_num_edges = std::distance(first_e, last_e);
        }

        const Graph* g;
        vertex_iterator first_vertex;
        vertex_iterator last_vertex;
        vertices_size_type m_num_vertices;
        edge_iterator first_edge;
        edge_iterator last_edge;
        edges_size_type m_num_edges;
    };

    template < typename Graph, typename VertexIterator, typename EdgeIterator >
    inline std::pair< VertexIterator, VertexIterator > vertices(
        const vertex_and_edge_range< Graph, VertexIterator, EdgeIterator >& g)
    {
        return std::make_pair(g.first_vertex, g.last_vertex);
    }

    template < typename Graph, typename VertexIterator, typename EdgeIterator >
    inline typename vertex_and_edge_range< Graph, VertexIterator,
        EdgeIterator >::vertices_size_type
    num_vertices(
        const vertex_and_edge_range< Graph, VertexIterator, EdgeIterator >& g)
    {
        return g.m_num_vertices;
    }

    template < typename Graph, typename VertexIterator, typename EdgeIterator >
    inline std::pair< EdgeIterator, EdgeIterator > edges(
        const vertex_and_edge_range< Graph, VertexIterator, EdgeIterator >& g)
    {
        return std::make_pair(g.first_edge, g.last_edge);
    }

    template < typename Graph, typename VertexIterator, typename EdgeIterator >
    inline typename vertex_and_edge_range< Graph, VertexIterator,
        EdgeIterator >::edges_size_type
    num_edges(
        const vertex_and_edge_range< Graph, VertexIterator, EdgeIterator >& g)
    {
        return g.m_num_edges;
    }

    template < typename Graph, typename VertexIterator, typename EdgeIterator >
    inline typename vertex_and_edge_range< Graph, VertexIterator,
        EdgeIterator >::vertex_descriptor
    source(typename vertex_and_edge_range< Graph, VertexIterator,
               EdgeIterator >::edge_descriptor e,
        const vertex_and_edge_range< Graph, VertexIterator, EdgeIterator >& g)
    {
        return source(e, *g.g);
    }

    template < typename Graph, typename VertexIterator, typename EdgeIterator >
    inline typename vertex_and_edge_range< Graph, VertexIterator,
        EdgeIterator >::vertex_descriptor
    target(typename vertex_and_edge_range< Graph, VertexIterator,
               EdgeIterator >::edge_descriptor e,
        const vertex_and_edge_range< Graph, VertexIterator, EdgeIterator >& g)
    {
        return target(e, *g.g);
    }

    template < typename Graph, typename VertexIterator, typename EdgeIterator >
    inline vertex_and_edge_range< Graph, VertexIterator, EdgeIterator >
    make_vertex_and_edge_range(const Graph& g, VertexIterator first_v,
        VertexIterator last_v, EdgeIterator first_e, EdgeIterator last_e)
    {
        typedef vertex_and_edge_range< Graph, VertexIterator, EdgeIterator >
            result_type;
        return result_type(g, first_v, last_v, first_e, last_e);
    }

} // end namespace graph

using graph::make_vertex_and_edge_range;
using graph::vertex_and_edge_range;

} // end namespace boost
#endif // BOOST_GRAPH_VERTEX_AND_EDGE_RANGE_HPP

/* vertex_and_edge_range.hpp
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
*/