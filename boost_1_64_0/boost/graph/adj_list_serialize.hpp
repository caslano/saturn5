//=======================================================================
// Copyright 2005 Jeremy G. Siek
// Authors: Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#ifndef BOOST_GRAPH_ADJ_LIST_SERIALIZE_HPP
#define BOOST_GRAPH_ADJ_LIST_SERIALIZE_HPP

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/pending/property_serialize.hpp>
#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#include <boost/serialization/collections_save_imp.hpp>
#include <boost/serialization/collections_load_imp.hpp>
#include <boost/serialization/split_free.hpp>

namespace boost
{

namespace serialization
{

    // Turn off tracking for adjacency_list. It's not polymorphic, and we
    // need to do this to enable saving of non-const adjacency lists.
    template < class OEL, class VL, class D, class VP, class EP, class GP,
        class EL >
    struct tracking_level< boost::adjacency_list< OEL, VL, D, VP, EP, GP, EL > >
    {
        typedef mpl::integral_c_tag tag;
        typedef mpl::int_< track_never > type;
        BOOST_STATIC_CONSTANT(int, value = tracking_level::type::value);
    };

    template < class Archive, class OEL, class VL, class D, class VP, class EP,
        class GP, class EL >
    inline void save(Archive& ar,
        const boost::adjacency_list< OEL, VL, D, VP, EP, GP, EL >& graph,
        const unsigned int /* file_version */
    )
    {
        typedef adjacency_list< OEL, VL, D, VP, EP, GP, EL > Graph;
        typedef typename graph_traits< Graph >::vertex_descriptor Vertex;

        int V = num_vertices(graph);
        int E = num_edges(graph);
        ar << BOOST_SERIALIZATION_NVP(V);
        ar << BOOST_SERIALIZATION_NVP(E);

        // assign indices to vertices
        std::map< Vertex, int > indices;
        int num = 0;
        BGL_FORALL_VERTICES_T(v, graph, Graph)
        {
            indices[v] = num++;
            ar << serialization::make_nvp(
                "vertex_property", get(vertex_all_t(), graph, v));
        }

        // write edges
        BGL_FORALL_EDGES_T(e, graph, Graph)
        {
            ar << serialization::make_nvp("u", indices[source(e, graph)]);
            ar << serialization::make_nvp("v", indices[target(e, graph)]);
            ar << serialization::make_nvp(
                "edge_property", get(edge_all_t(), graph, e));
        }

        ar << serialization::make_nvp(
            "graph_property", get_property(graph, graph_all_t()));
    }

    template < class Archive, class OEL, class VL, class D, class VP, class EP,
        class GP, class EL >
    inline void load(
        Archive& ar, boost::adjacency_list< OEL, VL, D, VP, EP, GP, EL >& graph,
        const unsigned int /* file_version */
    )
    {
        typedef adjacency_list< OEL, VL, D, VP, EP, GP, EL > Graph;
        typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
        typedef typename graph_traits< Graph >::edge_descriptor Edge;

        unsigned int V;
        ar >> BOOST_SERIALIZATION_NVP(V);
        unsigned int E;
        ar >> BOOST_SERIALIZATION_NVP(E);

        std::vector< Vertex > verts(V);
        int i = 0;
        while (V-- > 0)
        {
            Vertex v = add_vertex(graph);
            verts[i++] = v;
            ar >> serialization::make_nvp(
                "vertex_property", get(vertex_all_t(), graph, v));
        }
        while (E-- > 0)
        {
            int u;
            int v;
            ar >> BOOST_SERIALIZATION_NVP(u);
            ar >> BOOST_SERIALIZATION_NVP(v);
            Edge e;
            bool inserted;
            boost::tie(e, inserted) = add_edge(verts[u], verts[v], graph);
            ar >> serialization::make_nvp(
                "edge_property", get(edge_all_t(), graph, e));
        }
        ar >> serialization::make_nvp(
            "graph_property", get_property(graph, graph_all_t()));
    }

    template < class Archive, class OEL, class VL, class D, class VP, class EP,
        class GP, class EL >
    inline void serialize(Archive& ar,
        boost::adjacency_list< OEL, VL, D, VP, EP, GP, EL >& graph,
        const unsigned int file_version)
    {
        boost::serialization::split_free(ar, graph, file_version);
    }

} // serialization
} // boost

#endif // BOOST_GRAPH_ADJ_LIST_SERIALIZE_HPP

/* adj_list_serialize.hpp
E7wFdoC3wTvgXfAeeB/sBB+AtjHKQDAYDAXDwHAwAuwLRoH9wGhwABgDDgQHgYNBOzgEHAoOB2PBkeAoMA6MBxPAseA4MBFMAieAk8BkMBVMAyeDGeBUMBPMBnPAXDAPzAcLwOngDHAmWAgWg6VgGVgOzgErQSfoAt2gB5wL1oILwIXgInAxuBRcBq4AV4KrwTXgOrABXA9uADeCm8DN4BZwK7gN3A7uAHeCu8Dd4B5wL7gP3A8eAA+CjeAh8DB4BGwCj4EnwJNgM3gaPAO2gK1gG3gWPAeeBy+AF8FL4GXwCngVvAb6wHbwJngL7ABvg3fAu+A98D7YCT4AbWOVgWAwGAqGgeFgBNgXjAL7gdHgADAGHAgOAgeDdnAIOBQcDsaCI8FRYBwYDyaAY8FxYCKYBE4AJ4HJYCqYBk4GM8CpYCaYDeaAuWAemA8WgNPBGUJzHm+uJ6T9g6VgGVgOzgErQSfoAt2gB5wL1oILwIXgInAxuBRcBq4AV4KrwTXgOrABXA9uADeCm8DN4BZwK7gN3A7uAHeCu8Dd4B5wL7gP3A8eAA+CjeAh8DB4BGwCj4EnwJNgM3gaPAO2gK1gG3gWPAeeBy+AF8FL4GXwCngVvAb6wHbwJngL7ABvg3fAu+A98D7YCT4AbR9UBoLBYCgYBoaDEWBfMArsB0aDA8AYcCA4CBwM2sEh4FBwOBgLjgRHgXFgPJgAjgXHgYlgEjgBnAQmg6lgGjgZzACngplgNpgD5oJ5YD5YAE4HZ4AzwUKwGCwFy8BycA5YCTpBF+gGPeBcsBZcAC4EF4GLwaXgMnAFuBJcDa4B14EN4HpwA7gR3ARuBreAW8Ft4HZwB7gT3AXuBveAe8F94H7wAHgQbAQPgYfBI2ATeAw8AZ4Em8HT4BmwBWwF28Cz4DnwPHgBvAheAi+DV8Cr4DXQB7aDN8FbYAd4G7wD3gXvgffBTvABaBunDASDwVAwDAwHI8C+YBTYD4wGB4Ax4EBwEDgYtINDwKHgcDAWHAmOAuPAeDABHAuOAxPBJHACOAlMBlPBNHAymAFOBTPBbDAHzAXzwHywAJwOzgBngoVgMVgKloHl4BywEnSCLtANesC5YC24AFwILgIXg0vBZeAKcCW4GlwDrgMbwPXgBnAjuAncDG4Bt4LbwO3gDnAnuAvcDe4B94L7wP3gAfAg2AgeAg+DR8Am8Bh4AjwJNoOnwTNgC9gKtoFnwXPgefACeBG8BF4Gr4BXwWugD2wHb4K3wA7wNngHvAveA++DneAD0PYhZSAYDIaCYWA4GAH2BaPAfmA0OACMAQeCg8DBoB0cAg4Fh4Ox4EhwFBgHxoMJ4FhwHJgIJoETwElgMpgKpoGTwQxwKpgJZoM5YC6YB+aDBeB0cAY4EywEi8FSsAwsB+eAlaATdIFu0APOBWvBBeBCcBG4GFwKLgNXgCvB1eAacB3YAK4HN4AbwU3gZnALuBXcBm4Hd4A7wV3gbnAPuBfcB+4HD4AHwUbwEHgYPAI2gcfAE+BJsBk8DZ4BW8BWsA08C54Dz4MXwIvgJfAyeAW8Cl4DfWA7eBO8BXaAt8E74F3wHngf7AQfgLZEZSAYDIaCYWA4GAH2BaPAfmA0OACMAQeCg8DBoB0cAg4Fh4Ox4EhwFBgHxoMJ4FhwHJgIJoETwElgMpgKpoGTwQxwKpgJZoM5YC6YB+aDBeB0cAY4EywEi8FSsAwsB+eAlaATdIFu0APOBWvBBeBCcBG4GFwKLgNXgCvB1eAacB3YAK4HN4AbwU3gZnALuBXcBm4Hd4A7wV3gbnAPuBfcB+4HD4AHwUbwEHgYPAI2gcfAE+BJsBk8DZ4BW8BWsA08C54Dz4M=
*/