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
zQVddro92Ubw4Ugx+iHhOmLUdFnqnlXtj9mfFDAIbWXKurXtfz+67yYuiJHdQsezh5KWLUTAEsxrffn3EwzPI8mf8YRg/feAXIU41BguxJAEK7W7BHqk7PqiYNWUzQBtMydM7AfFY0u0mFHLWclrzkEyb4v1/kzVf2/qiE+FmD+5ay2xb636Onp4WBoQT2UwwGX33MMjoewQUCNnEP5eGUEuAfBs8ngKIrSvoUlbtP+emfCrUFQJFDPVuYr2Qf5nYRdhyV98Ri6OJ0+mn/ar9wh13zglMIdUSpLJVOSdZFb5cHYSsA2MVWPz54Hzdn7j8oBo0eLeQTBOpHu70/qeofQ/WDvqm8Z5MQLGMWk99j//Q9Js50TFDN+E0XhFV5opptSxxKGmL/E2Hdd+V/TlbS9gnPMQsh9Ckoz3qLVAY/jud+nO/4qMvhXkj4UEHNebe/cubZeOkK40KtTx0eNFSkKfVTwEpsP0RPlFCY5MP53AQLlQUiMf1IkpP2Fk0pInNLkNKB6oXiUg5bRMksv0BkBTvxxhC6Qtzix1bs9OxTkrO4sEfXnsABgSTQ==
*/