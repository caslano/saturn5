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