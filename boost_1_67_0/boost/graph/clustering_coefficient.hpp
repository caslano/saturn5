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