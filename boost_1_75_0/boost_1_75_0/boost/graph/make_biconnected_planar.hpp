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
ly0nPbU7kLLS9jYZCHFFUzQTBhKwUV/lES3QWpD1+JjD76I42mTtJJqj+aybokNnS7gf0qomdmxHITzIvhwvT0jDOarA41EtxDTOO5cKcZ/ME+Ymo5647kDrMk/BTp4rbVnuYKJz9NZ3/C1NaHGUNPUeSxCPE9JIUIjt17JTlfdrh1O9s1KSPkM8Y+/+izC5phN1c88tY4ZLGXSy7O2baKr91J75sO01HXUFESWPtv7kRIEwVfnuAw5omyxMmssSls9HSzo7kB6pk0xfkCrsQs6I6vGDQMSTtzj3XSsUeFb4GGoxjzumyvCbrQ1Now8OaVuIOYtNTV6rB6tNy4lnj1nE4hVsO8cnyGjZQ7QquOd5miLrC2XIsgcNG+c6zsZhbNbpkc6H0X9aiHMOK0Gi1UsMhuUov/Lt/ulD3i0l2s8QgXa6+Icrr7slDXZo6HKAxt3ND7k+YiElsNTt7LMrrvjYBf0L0T8sd7KeiMRiw9zj8wuV5y2P4CtTyNj8QcPf2ghR99KGWTwE/qkgwFTmnu4mevlY8fQVShIlK1FSkIEw70Q5ZgejUKIpSIkGGFIiAeOcgRw7l/nYJ+DLfcsMK/iGM/lHH/3BjKMWskfvHu6j4ev0eRjNmBQ7V/VqoITN8C42+m2+eRMKXg4ECxbOAgCTLiJuHqnxpNc8khFyZ0w0naUm6HBQCmARtU/Or5OrWjK1zLVMZovXUraG
*/