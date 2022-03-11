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