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