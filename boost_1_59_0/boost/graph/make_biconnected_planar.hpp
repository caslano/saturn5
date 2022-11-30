//=======================================================================
// Copyright 2007 Aaron Windsor
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#ifndef __MAKE_BICONNECTED_PLANAR_HPP__
#define __MAKE_BICONNECTED_PLANAR_HPP__

#include <boost/config.hpp>
#include <boost/tuple/tuple.hpp> //for tie
#include <boost/graph/biconnected_components.hpp>
#include <boost/property_map/property_map.hpp>
#include <vector>
#include <iterator>
#include <algorithm>

#include <boost/graph/planar_detail/add_edge_visitors.hpp>

namespace boost
{

template < typename Graph, typename PlanarEmbedding, typename EdgeIndexMap,
    typename AddEdgeVisitor >
void make_biconnected_planar(
    Graph& g, PlanarEmbedding embedding, EdgeIndexMap em, AddEdgeVisitor& vis)
{
    typedef typename graph_traits< Graph >::vertex_descriptor vertex_t;
    typedef typename graph_traits< Graph >::edge_descriptor edge_t;
    typedef typename graph_traits< Graph >::edges_size_type edge_size_t;
    typedef typename property_traits< PlanarEmbedding >::value_type
        embedding_value_t;
    typedef typename embedding_value_t::const_iterator embedding_iterator_t;
    typedef iterator_property_map< std::vector< std::size_t >::iterator,
        EdgeIndexMap >
        component_map_t;

    edge_size_t n_edges(num_edges(g));
    std::vector< vertex_t > articulation_points;
    std::vector< edge_size_t > component_vector(n_edges);
    component_map_t component_map(component_vector.begin(), em);

    biconnected_components(
        g, component_map, std::back_inserter(articulation_points));

    typename std::vector< vertex_t >::iterator ap, ap_end;
    ap_end = articulation_points.end();
    for (ap = articulation_points.begin(); ap != ap_end; ++ap)
    {
        vertex_t v(*ap);
        embedding_iterator_t pi = embedding[v].begin();
        embedding_iterator_t pi_end = embedding[v].end();
        edge_size_t previous_component(n_edges + 1);
        vertex_t previous_vertex = graph_traits< Graph >::null_vertex();

        for (; pi != pi_end; ++pi)
        {
            edge_t e(*pi);
            vertex_t e_source(source(e, g));
            vertex_t e_target(target(e, g));

            // Skip self-loops and parallel edges
            if (e_source == e_target || previous_vertex == e_target)
                continue;

            vertex_t current_vertex = e_source == v ? e_target : e_source;
            edge_size_t current_component = component_map[e];
            if (previous_vertex != graph_traits< Graph >::null_vertex()
                && current_component != previous_component)
            {
                vis.visit_vertex_pair(current_vertex, previous_vertex, g);
            }
            previous_vertex = current_vertex;
            previous_component = current_component;
        }
    }
}

template < typename Graph, typename PlanarEmbedding, typename EdgeIndexMap >
inline void make_biconnected_planar(
    Graph& g, PlanarEmbedding embedding, EdgeIndexMap em)
{
    default_add_edge_visitor vis;
    make_biconnected_planar(g, embedding, em, vis);
}

template < typename Graph, typename PlanarEmbedding >
inline void make_biconnected_planar(Graph& g, PlanarEmbedding embedding)
{
    make_biconnected_planar(g, embedding, get(edge_index, g));
}

} // namespace boost

#endif //__MAKE_BICONNECTED_PLANAR_HPP__

/* make_biconnected_planar.hpp
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
*/