// (C) Copyright 2007-2009 Andrew Sutton
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0 (See accompanying file
// LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_DETAIL_INDEX_HPP
#define BOOST_GRAPH_DETAIL_INDEX_HPP

#include <boost/graph/graph_traits.hpp>

// The structures in this module are responsible for selecting and defining
// types for accessing a builting index map. Note that the selection of these
// types requires the Graph parameter to model either VertexIndexGraph or
// EdgeIndexGraph.

namespace boost
{
namespace detail
{
    template < typename Graph > struct vertex_indexer
    {
        typedef vertex_index_t index_type;
        typedef typename property_map< Graph, vertex_index_t >::type map_type;
        typedef typename property_map< Graph, vertex_index_t >::const_type
            const_map_type;
        typedef typename property_traits< map_type >::value_type value_type;
        typedef typename graph_traits< Graph >::vertex_descriptor key_type;

        static const_map_type index_map(const Graph& g)
        {
            return get(vertex_index, g);
        }

        static map_type index_map(Graph& g) { return get(vertex_index, g); }

        static value_type index(key_type k, const Graph& g)
        {
            return get(vertex_index, g, k);
        }
    };

    template < typename Graph > struct edge_indexer
    {
        typedef edge_index_t index_type;
        typedef typename property_map< Graph, edge_index_t >::type map_type;
        typedef typename property_map< Graph, edge_index_t >::const_type
            const_map_type;
        typedef typename property_traits< map_type >::value_type value_type;
        typedef typename graph_traits< Graph >::edge_descriptor key_type;

        static const_map_type index_map(const Graph& g)
        {
            return get(edge_index, g);
        }

        static map_type index_map(Graph& g) { return get(edge_index, g); }

        static value_type index(key_type k, const Graph& g)
        {
            return get(edge_index, g, k);
        }
    };

    // NOTE: The Graph parameter MUST be a model of VertexIndexGraph or
    // VertexEdgeGraph - whichever type Key is selecting.
    template < typename Graph, typename Key > struct choose_indexer
    {
        typedef typename mpl::if_<
            is_same< Key, typename graph_traits< Graph >::vertex_descriptor >,
            vertex_indexer< Graph >, edge_indexer< Graph > >::type indexer_type;
        typedef typename indexer_type::index_type index_type;
    };
}
}

#endif

/* index.hpp
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
*/