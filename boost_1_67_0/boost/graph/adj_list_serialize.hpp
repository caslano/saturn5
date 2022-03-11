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