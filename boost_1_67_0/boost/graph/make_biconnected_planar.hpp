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