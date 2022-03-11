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
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
*/