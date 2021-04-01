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
RbXa92K8skFWZAVmuegzNVok9PMVZH3fwMcce+O4w2vQcb4cgKcErNYv+e+07CM/9zl/K11NKdLoFYIpuMZ04kuAX18ZVt7xDqs3V27/1D1S6qff7uNYOmgl9EJYMySQyx+Qm13a+qafivlR6DcxP7ARI6bjAf031KU8uhCIr01cGQry7XGr7zsI6sEXGrQltcknFHsMscckoTc1wAcyDO86bGAYRtAG0fgU3fQjG/voTf1d3W9j2qFgt7yrbS1giUm6qa0gyLvkSG0MRxcj0t5Poxhfv+7MWInqdYkX1ajK8alBcTN1XjMNLcOvfLZ+9sqTgKzVW6g4U0fvwYYrr4lK2qPbD6i6GNnc6IGmLytq1XAZfTea9qjPEZ5jiPbz8veeUlC4oHGIfaW4EQOzpf86ZDBCgclKx9gmz6tiGXYfuBJpJ0/DJalHDlK4F+wbc3jUSzwJXB1TEAzYyvln5rqaDDocj/mUJl6V+tcDRHsKJXSiW5dkbaHf1VoWnvvqea7ZGsDjgeG5r3RfetzlYoBp6u14TE4UoLgII/Vfib4oI1jdVcw2QfhumA==
*/