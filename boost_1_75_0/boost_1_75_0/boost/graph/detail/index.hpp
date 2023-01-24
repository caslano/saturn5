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
4znFTCiS45UT9iiSs1UXERPlE0iBhIHicpEaWyMj7qs/iAykf3pWCVlPGxkZcbf3y1h7VtuLvHF6EGNxQTEW05ixaCPn6LN3M3kZSwpbyVD68nTWg7hV4tCU2WgwQz3MmBFM/TlO9D1rpLxcpLPPa3Ex0OdaI0FMUHF5YIQWl2i6ISKjhXaeCXUw9jMaO9KuyMvCkYPLCxfLP5y5rh25SBdC87VPLmTycpE+v5XJC3NlsjSRPgwBpJKCFOiSoJvBBTwOq5sUTpUczcSRhKucE9myKBjhGyVHHXFMkhwtxDHDlQcEbJEKDuTLYh0pOCuLR8gJUMNmWTxO58zAJRaSo5t2DUfS87kPGJU4L0pOKjk7JWe75OyVnF2Ssxuchzxwq+DXBb9e+LXDrzMPzRV6LrxOcAnAaNUihi01p8VV0BdFA166WOI8gi470dkddLOeOKik4xEPltSJSZ2YdACpBpqj0/EFtex1L77ulXQwJBpO9HZHFz53SfqgnhR0Y0SzyPYXcngZ/e4RDGqm/gD5GEUspCApRL4URqpEJN9UDfmaGfnOMvIBrc4C+YCKzeREPpKvoAVIieT7axonXy99y8LJ93OcOmJ06lXo1M1ow2nUyWjGCwNTgE4HkE7oZ/RqsD4wkCjN/UkHhGBk1fO1vuxdN77rhncyPMeGiBSLS3hw0SkuPDy3kROoLLF24lmwR795DCccrP6STkGN
*/