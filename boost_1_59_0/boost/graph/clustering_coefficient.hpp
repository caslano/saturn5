// (C) Copyright 2007-2009 Andrew Sutton
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0 (See accompanying file
// LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_CLUSTERING_COEFFICIENT_HPP
#define BOOST_GRAPH_CLUSTERING_COEFFICIENT_HPP

#include <boost/next_prior.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/graph/lookup_edge.hpp>
#include <boost/concept/assert.hpp>

namespace boost
{
namespace detail
{
    template < class Graph >
    inline typename graph_traits< Graph >::degree_size_type possible_edges(
        const Graph& g, std::size_t k, directed_tag)
    {
        BOOST_CONCEPT_ASSERT((GraphConcept< Graph >));
        typedef typename graph_traits< Graph >::degree_size_type T;
        return T(k) * (T(k) - 1);
    }

    template < class Graph >
    inline typename graph_traits< Graph >::degree_size_type possible_edges(
        const Graph& g, size_t k, undirected_tag)
    {
        // dirty little trick...
        return possible_edges(g, k, directed_tag()) / 2;
    }

    // This template matches directedS and bidirectionalS.
    template < class Graph >
    inline typename graph_traits< Graph >::degree_size_type count_edges(
        const Graph& g, typename graph_traits< Graph >::vertex_descriptor u,
        typename graph_traits< Graph >::vertex_descriptor v, directed_tag)

    {
        BOOST_CONCEPT_ASSERT((AdjacencyMatrixConcept< Graph >));
        return (lookup_edge(u, v, g).second ? 1 : 0)
            + (lookup_edge(v, u, g).second ? 1 : 0);
    }

    // This template matches undirectedS
    template < class Graph >
    inline typename graph_traits< Graph >::degree_size_type count_edges(
        const Graph& g, typename graph_traits< Graph >::vertex_descriptor u,
        typename graph_traits< Graph >::vertex_descriptor v, undirected_tag)
    {
        BOOST_CONCEPT_ASSERT((AdjacencyMatrixConcept< Graph >));
        return lookup_edge(u, v, g).second ? 1 : 0;
    }
}

template < typename Graph, typename Vertex >
inline typename graph_traits< Graph >::degree_size_type
num_paths_through_vertex(const Graph& g, Vertex v)
{
    BOOST_CONCEPT_ASSERT((AdjacencyGraphConcept< Graph >));
    typedef typename graph_traits< Graph >::directed_category Directed;
    typedef
        typename graph_traits< Graph >::adjacency_iterator AdjacencyIterator;

    // TODO: There should actually be a set of neighborhood functions
    // for things like this (num_neighbors() would be great).

    AdjacencyIterator i, end;
    boost::tie(i, end) = adjacent_vertices(v, g);
    std::size_t k = std::distance(i, end);
    return detail::possible_edges(g, k, Directed());
}

template < typename Graph, typename Vertex >
inline typename graph_traits< Graph >::degree_size_type num_triangles_on_vertex(
    const Graph& g, Vertex v)
{
    BOOST_CONCEPT_ASSERT((IncidenceGraphConcept< Graph >));
    BOOST_CONCEPT_ASSERT((AdjacencyGraphConcept< Graph >));
    typedef typename graph_traits< Graph >::degree_size_type Degree;
    typedef typename graph_traits< Graph >::directed_category Directed;
    typedef
        typename graph_traits< Graph >::adjacency_iterator AdjacencyIterator;

    // TODO: I might be able to reduce the requirement from adjacency graph
    // to incidence graph by using out edges.

    Degree count(0);
    AdjacencyIterator i, j, end;
    for (boost::tie(i, end) = adjacent_vertices(v, g); i != end; ++i)
    {
        for (j = boost::next(i); j != end; ++j)
        {
            count += detail::count_edges(g, *i, *j, Directed());
        }
    }
    return count;
} /* namespace detail */

template < typename T, typename Graph, typename Vertex >
inline T clustering_coefficient(const Graph& g, Vertex v)
{
    T zero(0);
    T routes = T(num_paths_through_vertex(g, v));
    return (routes > zero) ? T(num_triangles_on_vertex(g, v)) / routes : zero;
}

template < typename Graph, typename Vertex >
inline double clustering_coefficient(const Graph& g, Vertex v)
{
    return clustering_coefficient< double >(g, v);
}

template < typename Graph, typename ClusteringMap >
inline typename property_traits< ClusteringMap >::value_type
all_clustering_coefficients(const Graph& g, ClusteringMap cm)
{
    BOOST_CONCEPT_ASSERT((VertexListGraphConcept< Graph >));
    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
    typedef typename graph_traits< Graph >::vertex_iterator VertexIterator;
    BOOST_CONCEPT_ASSERT((WritablePropertyMapConcept< ClusteringMap, Vertex >));
    typedef typename property_traits< ClusteringMap >::value_type Coefficient;

    Coefficient sum(0);
    VertexIterator i, end;
    for (boost::tie(i, end) = vertices(g); i != end; ++i)
    {
        Coefficient cc = clustering_coefficient< Coefficient >(g, *i);
        put(cm, *i, cc);
        sum += cc;
    }
    return sum / Coefficient(num_vertices(g));
}

template < typename Graph, typename ClusteringMap >
inline typename property_traits< ClusteringMap >::value_type
mean_clustering_coefficient(const Graph& g, ClusteringMap cm)
{
    BOOST_CONCEPT_ASSERT((VertexListGraphConcept< Graph >));
    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
    typedef typename graph_traits< Graph >::vertex_iterator VertexIterator;
    BOOST_CONCEPT_ASSERT((ReadablePropertyMapConcept< ClusteringMap, Vertex >));
    typedef typename property_traits< ClusteringMap >::value_type Coefficient;

    Coefficient cc(0);
    VertexIterator i, end;
    for (boost::tie(i, end) = vertices(g); i != end; ++i)
    {
        cc += get(cm, *i);
    }
    return cc / Coefficient(num_vertices(g));
}

} /* namespace boost */

#endif

/* clustering_coefficient.hpp
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
*/