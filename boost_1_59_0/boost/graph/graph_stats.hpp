// Copyright 2005 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Alex Breuer
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_GRAPH_STATS_HPP
#define BOOST_GRAPH_GRAPH_STATS_HPP

#include <map>
#include <list>
#include <boost/graph/iteration_macros.hpp>
#include <boost/assert.hpp>

namespace boost
{
namespace graph
{

    template < typename Graph > struct sort_edge_by_origin
    {
    public:
        typedef typename graph_traits< Graph >::edge_descriptor edge_type;

        explicit sort_edge_by_origin(Graph& g) : g(g) {}

        inline bool operator()(edge_type a, edge_type b)
        {
            return source(a, g) == source(b, g) ? target(a, g) < target(b, g)
                                                : source(a, g) < source(b, g);
        }

    private:
        Graph& g;
    };

    template < typename Graph > struct equal_edge
    {
    public:
        typedef typename graph_traits< Graph >::edge_descriptor edge_type;

        explicit equal_edge(Graph& g) : g(g) {}

        inline bool operator()(edge_type a, edge_type b)
        {
            return source(a, g) == source(b, g) && target(a, g) == target(b, g);
        }

    private:
        Graph& g;
    };

    template < typename Graph > unsigned long num_dup_edges(Graph& g)
    {
        typedef typename graph_traits< Graph >::edge_iterator e_iterator_type;
        typedef typename graph_traits< Graph >::edge_descriptor edge_type;

        std::list< edge_type > all_edges;

        BGL_FORALL_EDGES_T(e, g, Graph) { all_edges.push_back(e); }

        sort_edge_by_origin< Graph > cmp1(g);
        all_edges.sort(cmp1);
        equal_edge< Graph > cmp2(g);
        all_edges.unique(cmp2);

        return num_edges(g) - all_edges.size();
    }

    template < typename Graph >
    std::map< unsigned long, unsigned long > dup_edge_dist(Graph& g)
    {
        std::map< unsigned long, unsigned long > dist;
        typedef
            typename graph_traits< Graph >::adjacency_iterator a_iterator_type;
        typedef typename graph_traits< Graph >::vertex_descriptor vertex_type;

        BGL_FORALL_VERTICES_T(v, g, Graph)
        {
            std::list< vertex_type > front_neighbors;
            a_iterator_type a_iter, a_end;
            for (boost::tie(a_iter, a_end) = adjacent_vertices(v, g);
                 a_iter != a_end; ++a_iter)
            {
                front_neighbors.push_back(*a_iter);
            }

            front_neighbors.sort();
            front_neighbors.unique();
            dist[out_degree(v, g) - front_neighbors.size()] += 1;
        }
        return dist;
    }

    template < typename Graph >
    std::map< unsigned long, unsigned long > degree_dist(Graph& g)
    {
        std::map< unsigned long, unsigned long > dist;
        typedef
            typename graph_traits< Graph >::adjacency_iterator a_iterator_type;
        typedef typename graph_traits< Graph >::vertex_descriptor vertex_type;

        BGL_FORALL_VERTICES_T(v, g, Graph) { dist[out_degree(v, g)] += 1; }

        return dist;
    }

    template < typename Graph >
    std::map< unsigned long, double > weight_degree_dist(Graph& g)
    {
        std::map< unsigned long, double > dist, n;
        typedef
            typename graph_traits< Graph >::adjacency_iterator a_iterator_type;
        typedef typename graph_traits< Graph >::vertex_descriptor vertex_type;
        typedef typename property_map< Graph, edge_weight_t >::const_type
            edge_map_type;
        typedef typename property_traits< edge_map_type >::value_type
            edge_weight_type;

        typename property_map< Graph, edge_weight_t >::type em
            = get(edge_weight, g);

        BGL_FORALL_VERTICES_T(v, g, Graph)
        {
            edge_weight_type tmp = 0;
            BGL_FORALL_OUTEDGES_T(v, e, g, Graph) { tmp += em[e]; }
            n[out_degree(v, g)] += 1.;
            dist[out_degree(v, g)] += tmp;
        }

        for (std::map< unsigned long, double >::iterator iter = dist.begin();
             iter != dist.end(); ++iter)
        {
            BOOST_ASSERT(n[iter->first] != 0);
            dist[iter->first] /= n[iter->first];
        }

        return dist;
    }

}
}

#endif

/* graph_stats.hpp
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
*/