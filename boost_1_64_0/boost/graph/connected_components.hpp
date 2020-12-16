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
fGrnkSoAQUMEliDVknEEZRhvHkhXy0AueH0V/BsTng7TBElmlL8h2sYvpaUNIkmw6+KtQjF34UvtEZ4a1RNPfnLTNLmoELEu3rLrrI0Ligfdol/cQG6gfWWZkEFiRPuDF/inxsMuKK7nU7S8jMCQ7+q4FU72bqxWTBg//K1DFW2qnotw6g82AN1c4eiAScl3Gd/XpZM1Mn/NTi/jdNiUOyZFxGhorh7LnoZvLhxOqU93wLyCgxEIBIzz89kQB3YRvAdEshg3yVgH7w9KEevBpjN617P5z0EXmexgXkrP6Ai6FOxMkWy+ldKXHBycLy7tvX8TyhBtfC6F79645/fsfF02cymysRFbp+kpvv5cjPc15IctdcpPkLa3Yy6gA36hC6XIArHx2VwLMqWTaKibeD09zo395wg/mJ5DigmSESOroIK7Gq7Jl/XRylLPaWbQVWg3hNkWoT6RBJbjx2M2JkM9Zey/yr9ziJMdWa3gdYZAwifmGHzUC1Cdz3t+woYjS09CKKXwtATwMvkFFAMEYbsvxaexI1qFCgm5lGNgdrX9ij9ucAUTat0XevTob65KxCwDu8px7TcoWZjjKqrsGTBNZAtpuN5oytFr82Xn8OTIY687G5FBDlsiPEFv63fhnZdV8gBzX5M9+vtxP9Y3ZogTg4fxZBHc7YBtRtcZc9W9r+hSFg4YA8TmvaiF5l2VUrp6DIP7FNh/6vhGInbqGE/mXWQ4zWmkruc33TBMf/LBHQhi6VuYMXZgvOx0a128dsjxx6UG6+i5PVpZsXj2PNHe35emeNr47qKY06kdluubpw2mq7S7GaXrILvZjNK7DNbAbWiSwW0th0OSjGsUjPsdiAQSh7N86Q28VPfe0dMoyM0s8mMhE575RzYzAGY/E7Y1kjt9oxCD5QyOF0kfDaido1lER1BcEThvhNCFH08ubqUotUKams+kf6Xn9XC6/756xMt5wewcVOahXLVU5Sk2PDqnSMdlFWhod9QIsbRXC3odwxTAhTNKHbiHNzhdTg+Mv0nZZC11FgLyH8rg2kNJWysQikt9VFLSWVZEa9//pahOCtB2k9HdzzOEIzbH3ZSuTDL9XQ/SeZI7J+yNZMh1as4jUQDmtkq5MmE51O92ScbY5b30MBcrZ7Y4V5U4LjxLc+V5huSXnDc4d/24213ky9FTPOMPsFVpZ6uu3VvKi3nj03x0xvd7XBwIR/xp/4WXuRLFwBg1RiS1BJ7zNpx45Nx5dIPz2BN3TRRrXCENCIG7TBeVzWSEFitQCW716OkOfPaWB5zycfXk+WzY+oDTsHz1cxfgLUUVfJYDEq4L8Qb8rV6usTc88qXlihU1lNEnF7X5LtXZZEBme4Dcg+gJDxP4pVTJz8G1uDYwHK0BjRSOPH8Q72PhUINqYRi9Cij5ItQDjynUZHPz/Q2YaG27ni8ivxKygr7lgf2rs9cuz82wPPuu4AOuUj6eBaWOISynvimL57F1rB0cIz4xf2mcdF5mlfAYGv1V3bFq+Z/crjWK2VRNL9Q2ImECGBormrgi+AKnGjDz0xanIr2rxuIaI0HQ09+UJ+cTvlUTiW/cppT4uhnBC+fSK2eTEQ6M+GwFbLflF9+IvsyOnIV/Ae0/8YUHm2HKq+FY767yNIr3Td0sPSrtLjCNsbr4P/b30f9RPMQf5D5UnXfENPLee2JVTh3eFdP159Q/FkWPnuJFVaThnt4zz1GZAl7jdfGZjqQCa7I2Kma0f5iRzGQWUTFBRvIaTZzGjPvAs0wiHP9Vn8MZ01RBgPE4mT7Vr3QCwhcSrfobouM3VTmNeT4a53OBnfUxjtlOfX1UQB/Wt91EFo7q7EqGFbpGeO7CmUI=
*/