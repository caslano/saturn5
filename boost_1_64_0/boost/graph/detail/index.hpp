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
+KbkGW3zdC90rH4tZd6gbsxiWWlD+1dZtqHN7f4sVV+0SuZPtX1msXi8n7r1jvQxNK28evlU/crr6a+v7bzFZqykU+k9VpvzfVi6jXOR9OPEmmjIvZbS1ndF+uvo8nzYLvV8pI9P13nsNCZ0Hc4FKaM9ZTg9bynC7DfzkOTpZ9thCXB6ncmkXuhC6rgaJ89voZGH+23qcfYzhmc6iWRf13XmfyXlNM24LjnsWJfqF+CU5Oll20Jfmi71Svrex08lTxvbcouf0/bQDelgusp0uvdvu+yzfmwB2yAx832R2zzuU7v2SBqY1C+5ax+1X5ribVlHfdtfqLsq4VJ3tczFzO5h6cCbvSNpeZB7vdW7knSdl75/fSnJcd/6Ot5g60krSLNDaCeGc9Ceby7a676mG/rhse4rYqdZ9/XXbe73UXxhxnR92EUzVkHfl2HGwvR9Gdvc763Yv8393opN29zvrVi8zf3eipfNWBV9/8Y293sr+pox/Ty6mjH9POoRc63DK07Muc4u+/aMdXa8zzLU2fH57FZndzqTOrvzhvs9Gpd0Pv2ZqO/dmC559eegxGPd77eXeNsMcbMfkuu6fP1e9NYVPoS6wvBAqWtbtXTClC4pS6K+WrFg7fjUG966wv+lusI0q+O3lfy2k7pC++d+H3XKF6bqCitgYYzAMlgDJ2FNnI21cBM2whPYBN/FaLyBMfgtNsefsQXexzj0V3V2WbANFsS2WAzbYznsgBWwE9bCzhiJXTAau2IL7I6tsAe2x57YBXthAiZhIj6DfbEPpmBfHIT9cCim4POYinOwJi7AKFyNDXADbsatuAX34lY8jNvwFG7Hq7gD7+Mu/A13Yz728WAsjEOwONbDahiJtfBZbIbDsB0+j4NxBE5UY2lMxTG4CsfiRpyA13ESWnh/TMasOBUfwWlYEF/CJ3ANhuM6bIqbsCXOwufwFRyN83AszseJ+CrOw8W4CJfiElyGb+Fy3I6v4x5V7mHcjT+qOtQe++gfdN/vtyEdS3zOPm9dqrcu1VuX6q1L/XPVpb6o61NJ+7z1qd6H9+F9eB/eh/fhfXgf3of34X385x9/8PX/7gMiHk7b/1S36//E3K7/E3O7/k8s0+v/xN2v/+u4j/v1fIn7qnKcY36OMpyWD3ZvPyDxEJf2A/lUPFTicS3q1m9kv0Bft6m6Zp/q4Zr9DKdr9jWyG/LoGEAdvnIOc3JuUNfseRV+Z5xClXeVh+vxer7bfQON1fXck29In1C+vvQEWI5a5K7UfBa3FKNHwly0os9rjLdsNxpYBxr7rbmMT615jV+suY3HbFmpyw80OnN1ebOPTV/f7bRJ+tH3cbn2r/sB3yHbMtWaPs1V5C3SHl+27alcjmu+Zt+7WYmnurQF2Ctl5KVXwCxWl+v8uh1/suSZ75/ZNf58qpyTb0kflTxrX6M6qSNHGuuVa+f25YJluQHdU4emDIxPMfs0HPKmfbkiuq/QV2Q6r75+7bZsM0P34dlD8kbSf6O/vn6fWRuD3KrfsPaSP8Goyba1IamxBzy2PViFqfLcl2TWP67uZ3eo5Jnn7972wOxftpG8lrV8xrGHnrfYLFltBY2ytpyWQuq1OyXzw3yKMfrXz5aJxmKOkbdsNt0X6TOyjjVu22EYmfVznNItIZ6O1J36UV+2keXJUU/1M9pSyqvs35y7R4bRd+kS0jnScFsx6rICjIuk+zZfY5LPTWOKby5jne8jxiHfYOOab2NLsJTh2ObvLQXpbcHtdUo13zPJst8LqGnHa+wj221/72d2b0obluup9r2MWVlAnheXYcz2FGU2p/fNZuV4ya3udxkty7zov4rOVPb72lzbYuh7ZwZJvtk=
*/