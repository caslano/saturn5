//
//=======================================================================
// Copyright 1997-2001 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//
#ifndef BOOST_GRAPH_CONNECTED_COMPONENTS_HPP
#define BOOST_GRAPH_CONNECTED_COMPONENTS_HPP

#include <boost/config.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/graph/overloading.hpp>
#include <boost/graph/detail/mpi_include.hpp>
#include <boost/static_assert.hpp>
#include <boost/concept/assert.hpp>

namespace boost
{

namespace detail
{

    // This visitor is used both in the connected_components algorithm
    // and in the kosaraju strong components algorithm during the
    // second DFS traversal.
    template < class ComponentsMap >
    class components_recorder : public dfs_visitor<>
    {
        typedef typename property_traits< ComponentsMap >::value_type comp_type;

    public:
        components_recorder(ComponentsMap c, comp_type& c_count)
        : m_component(c), m_count(c_count)
        {
        }

        template < class Vertex, class Graph > void start_vertex(Vertex, Graph&)
        {
            if (m_count == (std::numeric_limits< comp_type >::max)())
                m_count = 0; // start counting components at zero
            else
                ++m_count;
        }
        template < class Vertex, class Graph >
        void discover_vertex(Vertex u, Graph&)
        {
            put(m_component, u, m_count);
        }

    protected:
        ComponentsMap m_component;
        comp_type& m_count;
    };

} // namespace detail

// This function computes the connected components of an undirected
// graph using a single application of depth first search.

template < class Graph, class ComponentMap, class P, class T, class R >
inline typename property_traits< ComponentMap >::value_type
connected_components(const Graph& g, ComponentMap c,
    const bgl_named_params< P, T, R >& params BOOST_GRAPH_ENABLE_IF_MODELS_PARM(
        Graph, vertex_list_graph_tag))
{
    if (num_vertices(g) == 0)
        return 0;

    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
    BOOST_CONCEPT_ASSERT((WritablePropertyMapConcept< ComponentMap, Vertex >));
    typedef typename boost::graph_traits< Graph >::directed_category directed;
    BOOST_STATIC_ASSERT((boost::is_same< directed, undirected_tag >::value));

    typedef typename property_traits< ComponentMap >::value_type comp_type;
    // c_count initialized to "nil" (with nil represented by (max)())
    comp_type c_count((std::numeric_limits< comp_type >::max)());
    detail::components_recorder< ComponentMap > vis(c, c_count);
    depth_first_search(g, params.visitor(vis));
    return c_count + 1;
}

template < class Graph, class ComponentMap >
inline typename property_traits< ComponentMap >::value_type
connected_components(const Graph& g,
    ComponentMap c BOOST_GRAPH_ENABLE_IF_MODELS_PARM(
        Graph, vertex_list_graph_tag))
{
    if (num_vertices(g) == 0)
        return 0;

    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
    BOOST_CONCEPT_ASSERT((WritablePropertyMapConcept< ComponentMap, Vertex >));
    // typedef typename boost::graph_traits<Graph>::directed_category directed;
    // BOOST_STATIC_ASSERT((boost::is_same<directed, undirected_tag>::value));

    typedef typename property_traits< ComponentMap >::value_type comp_type;
    // c_count initialized to "nil" (with nil represented by (max)())
    comp_type c_count((std::numeric_limits< comp_type >::max)());
    detail::components_recorder< ComponentMap > vis(c, c_count);
    depth_first_search(g, visitor(vis));
    return c_count + 1;
}

} // namespace boost

#include BOOST_GRAPH_MPI_INCLUDE(< boost / graph / distributed / connected_components.hpp >)

#endif // BOOST_GRAPH_CONNECTED_COMPONENTS_HPP

/* connected_components.hpp
a8mn+uEU8lx4FNa8qy9xIz5kzGSYFPMvu1DsUH1Iox4gLfP+0S8fxLQkaw5QFRq8lbOCUDG+PZaLzpofltQCXeFtr1TD8Es8fTw5hEm2qQ4decE+47ZBPd+7cHQfzSn5BVDIDVghQKpjs6XqGGEi9zlvD9HPNmZDqlzaNr2Ch6zQkRzLxahOsgI9vLLZ//7uDi49Nbk4W0MakLLPZNogoLlPh6DrKDuLbZXQJRdSklxwSvSYO//EtQivUHGdv0Ad1IAcLbBM1JoTAIJcCRxVa5ZTo3ubkauK/wwP5Wzc/YshAtbr8VJkghGb8uMSafIJjJlJnnB9HsovdBKjVmdUrpWigI8NpzSUTRYto0+0wDTpAiZL8HiacKl+Mz/0UPyNSNTRglNjk7TPwTI4Ha6E9qirllFTTFZBy0KS5XIpS4QqEU8ch1sxrhr1CLzc+PuInmkj9Xv59SvAA8yrhwml1NFk4BR4N3dGy5JREACeLc2zsZH+QQMP/MBU2ZWWUkdnGnyhVRUlZ45HOYILg1ldS3Ld9E2VaFlTfxSkL7CRZWHxxH1wZeL9RvS+Ew==
*/