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
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
*/