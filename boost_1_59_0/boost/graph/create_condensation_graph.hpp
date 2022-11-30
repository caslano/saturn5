//=======================================================================
// Copyright 2002 Indiana University.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_CREATE_CONDENSATION_GRAPH_HPP
#define BOOST_CREATE_CONDENSATION_GRAPH_HPP

#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>

namespace boost
{

template < typename Graph, typename ComponentLists, typename ComponentNumberMap,
    typename CondensationGraph, typename EdgeMultiplicityMap >
void create_condensation_graph(const Graph& g, const ComponentLists& components,
    ComponentNumberMap component_number, CondensationGraph& cg,
    EdgeMultiplicityMap edge_mult_map)
{
    typedef typename graph_traits< Graph >::vertex_descriptor vertex;
    typedef typename graph_traits< Graph >::vertices_size_type size_type;
    typedef
        typename graph_traits< CondensationGraph >::vertex_descriptor cg_vertex;
    std::vector< cg_vertex > to_cg_vertex(components.size());
    for (size_type s = 0; s < components.size(); ++s)
        to_cg_vertex[s] = add_vertex(cg);

    for (size_type si = 0; si < components.size(); ++si)
    {
        cg_vertex s = to_cg_vertex[si];
        std::vector< cg_vertex > adj;
        for (size_type i = 0; i < components[si].size(); ++i)
        {
            vertex u = components[s][i];
            typename graph_traits< Graph >::adjacency_iterator v, v_end;
            for (boost::tie(v, v_end) = adjacent_vertices(u, g); v != v_end;
                 ++v)
            {
                cg_vertex t = to_cg_vertex[component_number[*v]];
                if (s != t) // Avoid loops in the condensation graph
                    adj.push_back(t);
            }
        }
        std::sort(adj.begin(), adj.end());
        if (!adj.empty())
        {
            size_type i = 0;
            cg_vertex t = adj[i];
            typename graph_traits< CondensationGraph >::edge_descriptor e;
            bool inserted;
            boost::tie(e, inserted) = add_edge(s, t, cg);
            put(edge_mult_map, e, 1);
            ++i;
            while (i < adj.size())
            {
                if (adj[i] == t)
                    put(edge_mult_map, e, get(edge_mult_map, e) + 1);
                else
                {
                    t = adj[i];
                    boost::tie(e, inserted) = add_edge(s, t, cg);
                    put(edge_mult_map, e, 1);
                }
                ++i;
            }
        }
    }
}

template < typename Graph, typename ComponentLists, typename ComponentNumberMap,
    typename CondensationGraph >
void create_condensation_graph(const Graph& g, const ComponentLists& components,
    ComponentNumberMap component_number, CondensationGraph& cg)
{
    create_condensation_graph(
        g, components, component_number, cg, dummy_property_map());
}

} // namespace boost

#endif // BOOST_CREATE_CONDENSATION_GRAPH_HPP

/* create_condensation_graph.hpp
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
*/