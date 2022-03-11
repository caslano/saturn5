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