//=======================================================================
// Copyright 2000 University of Notre Dame.
// Authors: Jeremy G. Siek, Andrew Lumsdaine, Lie-Quan Lee
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_EDGE_CONNECTIVITY
#define BOOST_EDGE_CONNECTIVITY

// WARNING: not-yet fully tested!

#include <boost/config.hpp>
#include <vector>
#include <set>
#include <algorithm>
#include <boost/graph/edmonds_karp_max_flow.hpp>

namespace boost
{

namespace detail
{

    template < class Graph >
    inline std::pair< typename graph_traits< Graph >::vertex_descriptor,
        typename graph_traits< Graph >::degree_size_type >
    min_degree_vertex(Graph& g)
    {
        typedef graph_traits< Graph > Traits;
        typename Traits::vertex_descriptor p;
        typedef typename Traits::degree_size_type size_type;
        size_type delta = (std::numeric_limits< size_type >::max)();

        typename Traits::vertex_iterator i, iend;
        for (boost::tie(i, iend) = vertices(g); i != iend; ++i)
            if (degree(*i, g) < delta)
            {
                delta = degree(*i, g);
                p = *i;
            }
        return std::make_pair(p, delta);
    }

    template < class Graph, class OutputIterator >
    void neighbors(const Graph& g,
        typename graph_traits< Graph >::vertex_descriptor u,
        OutputIterator result)
    {
        typename graph_traits< Graph >::adjacency_iterator ai, aend;
        for (boost::tie(ai, aend) = adjacent_vertices(u, g); ai != aend; ++ai)
            *result++ = *ai;
    }

    template < class Graph, class VertexIterator, class OutputIterator >
    void neighbors(const Graph& g, VertexIterator first, VertexIterator last,
        OutputIterator result)
    {
        for (; first != last; ++first)
            neighbors(g, *first, result);
    }

} // namespace detail

// O(m n)
template < class VertexListGraph, class OutputIterator >
typename graph_traits< VertexListGraph >::degree_size_type edge_connectivity(
    VertexListGraph& g, OutputIterator disconnecting_set)
{
    //-------------------------------------------------------------------------
    // Type Definitions
    typedef graph_traits< VertexListGraph > Traits;
    typedef typename Traits::vertex_iterator vertex_iterator;
    typedef typename Traits::edge_iterator edge_iterator;
    typedef typename Traits::out_edge_iterator out_edge_iterator;
    typedef typename Traits::vertex_descriptor vertex_descriptor;
    typedef typename Traits::degree_size_type degree_size_type;
    typedef color_traits< default_color_type > Color;

    typedef adjacency_list_traits< vecS, vecS, directedS > Tr;
    typedef typename Tr::edge_descriptor Tr_edge_desc;
    typedef adjacency_list< vecS, vecS, directedS, no_property,
        property< edge_capacity_t, degree_size_type,
            property< edge_residual_capacity_t, degree_size_type,
                property< edge_reverse_t, Tr_edge_desc > > > >
        FlowGraph;
    typedef typename graph_traits< FlowGraph >::edge_descriptor edge_descriptor;

    //-------------------------------------------------------------------------
    // Variable Declarations
    vertex_descriptor u, v, p, k;
    edge_descriptor e1, e2;
    bool inserted;
    vertex_iterator vi, vi_end;
    edge_iterator ei, ei_end;
    degree_size_type delta, alpha_star, alpha_S_k;
    std::set< vertex_descriptor > S, neighbor_S;
    std::vector< vertex_descriptor > S_star, non_neighbor_S;
    std::vector< default_color_type > color(num_vertices(g));
    std::vector< edge_descriptor > pred(num_vertices(g));

    //-------------------------------------------------------------------------
    // Create a network flow graph out of the undirected graph
    FlowGraph flow_g(num_vertices(g));

    typename property_map< FlowGraph, edge_capacity_t >::type cap
        = get(edge_capacity, flow_g);
    typename property_map< FlowGraph, edge_residual_capacity_t >::type res_cap
        = get(edge_residual_capacity, flow_g);
    typename property_map< FlowGraph, edge_reverse_t >::type rev_edge
        = get(edge_reverse, flow_g);

    for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
    {
        u = source(*ei, g), v = target(*ei, g);
        boost::tie(e1, inserted) = add_edge(u, v, flow_g);
        cap[e1] = 1;
        boost::tie(e2, inserted) = add_edge(v, u, flow_g);
        cap[e2] = 1; // not sure about this
        rev_edge[e1] = e2;
        rev_edge[e2] = e1;
    }

    //-------------------------------------------------------------------------
    // The Algorithm

    boost::tie(p, delta) = detail::min_degree_vertex(g);
    S_star.push_back(p);
    alpha_star = delta;
    S.insert(p);
    neighbor_S.insert(p);
    detail::neighbors(
        g, S.begin(), S.end(), std::inserter(neighbor_S, neighbor_S.begin()));

    boost::tie(vi, vi_end) = vertices(g);
    std::set_difference(vi, vi_end, neighbor_S.begin(), neighbor_S.end(),
        std::back_inserter(non_neighbor_S));

    while (!non_neighbor_S.empty())
    { // at most n - 1 times
        k = non_neighbor_S.front();

        alpha_S_k = edmonds_karp_max_flow(
            flow_g, p, k, cap, res_cap, rev_edge, &color[0], &pred[0]);

        if (alpha_S_k < alpha_star)
        {
            alpha_star = alpha_S_k;
            S_star.clear();
            for (boost::tie(vi, vi_end) = vertices(flow_g); vi != vi_end; ++vi)
                if (color[*vi] != Color::white())
                    S_star.push_back(*vi);
        }
        S.insert(k);
        neighbor_S.insert(k);
        detail::neighbors(g, k, std::inserter(neighbor_S, neighbor_S.begin()));
        non_neighbor_S.clear();
        boost::tie(vi, vi_end) = vertices(g);
        std::set_difference(vi, vi_end, neighbor_S.begin(), neighbor_S.end(),
            std::back_inserter(non_neighbor_S));
    }
    //-------------------------------------------------------------------------
    // Compute edges of the cut [S*, ~S*]
    std::vector< bool > in_S_star(num_vertices(g), false);
    typename std::vector< vertex_descriptor >::iterator si;
    for (si = S_star.begin(); si != S_star.end(); ++si)
        in_S_star[*si] = true;

    degree_size_type c = 0;
    for (si = S_star.begin(); si != S_star.end(); ++si)
    {
        out_edge_iterator ei, ei_end;
        for (boost::tie(ei, ei_end) = out_edges(*si, g); ei != ei_end; ++ei)
            if (!in_S_star[target(*ei, g)])
            {
                *disconnecting_set++ = *ei;
                ++c;
            }
    }
    return c;
}

} // namespace boost

#endif // BOOST_EDGE_CONNECTIVITY

/* edge_connectivity.hpp
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
*/