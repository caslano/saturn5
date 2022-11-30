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

#include BOOST_GRAPH_MPI_INCLUDE(<boost/graph/distributed/connected_components.hpp>)

#endif // BOOST_GRAPH_CONNECTED_COMPONENTS_HPP

/* connected_components.hpp
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
*/