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
tPB4j9PPxX7t84oYh/AVLWtwPLKOg0fWwM7yiAgtKw8P1bJyzMvLRTu/Lx2r2zkqikjrQ6T10/rYbE4qwLwiVOsTKhKV+4LWR2qdAj/vc27vc27vc27vc26PnnNr/C0s4YHlrUrekM3zJiUv5nmNXqXX6zGv1Gk0CqtBIySlRQUGg1nD89nIYOB5iw4GHE/WJSK/QaPX8RbapM3AzueJLAa9VaPQ8Fi7kk/E8+162v8tpHVwUHCQ70u+je2q4ODgkHAVAeZCWodgvnVIMMvg98Evv2xXhfQNCQ5q3FjazlPVNxy5gwOlh/TmEMq+3FjKG5RmpUqn05jdP+emqVmiGqcPidq4EtnwSdaPUvzqx93XjPjP5d2vk+riT4kOg73pW9ySxJ+2YelwJNi2ej7EztPCqojxIOeviST+I9s3sL0bHty4AnmXz8Ct05kO/nN371XXW/adnP+niz/BsFMWtueHC7+M5Ncj52fxt8vLWAzx0od33OrvLk/8J3dv/erwtg2wI3YJJCyPgmWRk6G+9s9MMbD47WwPqwtZkLd+BuStmgh3Fg+H23P7wC19d7gx5VO4Me49uD76HQcd6fN3xn9p+0qA2Z+gW9AdCsPas3VuRcoiKN8+D8qSIqE0YQbYNkwBfm0oWKJHgWXpEChe2B9O9A9g/Fd3x+FwFAKwahiURakZf36sHvLWhMHd5ePgzk/DBD3Cv4Kb0zrC
*/