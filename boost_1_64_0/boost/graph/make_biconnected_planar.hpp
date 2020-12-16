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
PiXjpiPNMz6uaY7QXz+3yn4j1pSzrbAj+hJlKHPfLPfT7r66aKixjzffGiVqGQePZJ5HC5gFW8KzYSs4xbh1vDH2ntW9793q2qgI7WG+9doepkL9WyOgTstIONb4T4Sj4TmSTi5oxl0OM+HFMAuugtlwEzwTPgbPgr+GZ8PtcBJ8Dk6G38CpMEBazoH14GzYGRbDlfBc+Cg8D/4WLoI74RL4CrwA/hleqMNxfBebceqXmHHqy+FsuEKnF15u8qXcXm+5bpv8biDXM3drj0mcPj+wtfm2K3+rrmacfjc4HPaFo2APcx56mvzqA6ea/bOM/3zjv0j83XTstdcaue5JOvohjk22K7EbBFfp44HXw0nwBngeXAMv0udW5xe8Dd6o44LPmHkFe+Gd8AC8C34O74ZBfuOX8Dj4EOwOH9bHB7+B6fAFOAa+ZOYdvKzLAXwVFsPd+vfgO/B+uBduhu/CX8H3zDyDD+Gb8FP4EfwMHtLHDhXn5QsYEXDT0Rgehs3gdzARfg+TA+44/hQYAdNgHTgP1oXnw/pwJYyGP4ex8FoYBx+H8fAt2BR+AO8h3o/hnWbeQRv8naA7TjwGngy7wY6wF+wMB8BTYDJsDkfCFnAibAmnwZN0emA3qNvGZccYQ7RxrjvG6BB/7+bvmBJ+Dw1C2SgPdRntjvXZOsY/Zscdo7My6I6laW3GyOzL5m8zpkXJmBRvHMoMtIz4VqF1aANhm5oxI2lm/McR5B/zsa2E35rmjc04gHbmumMq/OMkXinhGNBQM+4hphS7IMdpxibkmTEH61A79g1A2aisVNVutVvtVrvVbrVb7Va71W61W+1Wu9Vutdu/bfunvv+fn1tSml9UKC//lfq73v/Hqbqx7U7SnVo/jM7IykkeO1Z5fkq8Rg9Tnp8jfinJaRm6XzFK/PBJHZ2eMyRldOqQZPOuf36Cst8wXBOhZNvgvjuH5huGt8k7LnM08hnDmt5vGdvkmr9FaPdLeDZZgt1+Y/5V2T8g4Fuzv7iMXy1Vrs0c3R8lNkMC4d//k2/i4PpE9veWd+Zu/hTZtaE/l31Xke9l6mTth2v/7dovgXfQDdUpaKQqVs/CfSjSaai8tJgsUN63hV+W+EYGfMeTX1K20L4v3iH7+/mOJ7dwFiZKed8S3Cs2p/tspuul0UpDNkXYvCg2w3w2xQVTZYEz7xvyb4hNj6ppUd73+N8yeXsJ70FaK7ser0jPN/yMSKY0smvEWncYRZ+bvw8afmH4R8ND1rameH7K9zyjNVTrO7x1PMffbtfi7KWM3yjPr2fIb6jnd1rIr7/n1yPkl+j5dQ/5nez5Jco5wK+F9esn7kbW3VfcT1p3H3Gvte7e4g7cUXWdvozw96r4ZSv/On21a7z9I9Z4eydW+y+JDa6p0+Dujg1fTR98sM+XjWvXePtfWuMtRrlbBm3KtxzPUrO+2np7vXGvZX35Q1f8NdrDvK9pb96PjYAD4AR4OiyFw837lxS42Lw3W2bem10CR8ErYTqsMO/NVsMx5v1MJrzNvDdbB8fDe+EEeJ95f7bJvD97GE6E2006XoRT4KtwOnwdzoBvw1x4GM6E38FBsInjvvdqBYfAU2AyTISz4Ejz3m00LIB5cA4sgIXwYlgEV5j3ctfBufAeOB8+ARfCl+Bi+KHvvdxSGEn+XgTrw2WwnXlP18m8pxsML4XDzfu6KeY93TS4UrnrIB1aQNzJ7nuUxvxYO9QTDUVZaAYqQ8sW/vh87eLs2jnb/2lzto+er/33zdWudp72f/Ac7f/l+dm1c7P/vrnZxb452asWqtrtX7RFoGn/xOf//JkL/yFj/8sUdUPGXM7PIdppRaW51n+56+8+M5o=
*/