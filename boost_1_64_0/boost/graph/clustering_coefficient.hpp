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
S9LD5rjfH7oQ2+hru4syEvZaWpPFUN/F4TPeUTkwpzFGPAdpBunaFkjmlKMcaMeKXGl+KONBtmI8bMFk0kXNDRA4ExLyWJuVhnOc8k48cijcUOQBMcHwjwmAXwieDLLY7p8NtSH3EJTA+zRTZiR6B0nWb1+0mrhgsR+2Q3aEF91mGn+0Qb/SuRKSf7KsQKi7kJFBfej5AnnpKFL2cEO302JLO37btHN1F0mUOeixhkKN89rxauE+BxdKkQVe2VhZFwwiG9Yov5i7TFwZu3ovDN/erX7xm4TxG8RLOdNS8IcaoxvN5wjhiIXfmgO+zIH2bcoFqZwtvNCarDi0NztR/pmzYqjTpHzleQVPkqxkfuw0GxgpKlVRVbKsy5smJ5qIJt76kJfuHGF9tJiinVgveDLZLsPv8uGsfDl1u7WanIc4b26+YPCdJTHxmpHdtVjwvVq2a4yP+BRd2xQWd3hYLCWBnfC2nQOEesuNLxZNyLtqEmcWSO7Iq6Kxim2ehBFG67gnu9T/Old7buiX+YlYChnv/VUaxSnzrzhc4vcYaEOGVxeO2mfJO0N3AvKJBsJVNW6S8wlipOHkprXp6XQV92kETuGxA7By3Ino/aCwrpH0bfJ36qgbetZI48kXAN320fPFkir98lo4L293JfIA0+vfD3jQuwFwYpG2F5u3ou+UUs9wI4RwUTcIZdXL4TLJzZb3oTjrvUP8eGJxuJ8RnadsuvMSAkTmPJNePlXYBP54p30CvUpFk0j/WKaNnk0Wl1eZqWSx/RT1DLf85vXg9utPN8N8do46B+rw+OmmLzf1nRUlJ/WbS/W1JnckvXalAo10QQnLMjMG/Z8qgO7vz1L9869Gw1uxOVu1RsW/oTMgxjv8Gg+Faxxp73ul0dj3ie56/wXGKGXzlD586oMuA0aPwRjeNGWBdMX3V1m+e4FK+veDNeogrkWwaVTPremlot3Wyi5P30PXRvrdvRgxjifCHfRYZMOrS9A5x5cNcM+oo184gRHuMsc4glLAzkniMNIvhre5Pqnl0jtRuL1nGAm8pLxgehTD/ZTc5XuyiY5olOV8KieaZ4edbNO+m/xuNfaZQHQLZ6vnPbXHEiMjseXtyoLo5my2sAtzXd65AF4m4F095JhJvFjWZd4BZtfdtKS+izC62b4QOYbZAp7NWaLgiBx+0IsrsQa2OJ9f1e1IIzBgqE8P4qS8NxNZCyrxUsPhrCaeFreIp/e7rgkIpE+Ybr+HMK6GFio8jkXEYz0HcMSjyg9rpzIic8ZFUjSVePpmCaTqxPlEDEjV80vBWJRD6nsh5VNTsK5sKRYyp95rPAUVElYWPJNCjfs5+kIWB8ljnF9Kx4LX1bWfqQcq7TA5FxsILH0eT3tWrmX/ivuitJ+IS4cX3jXAEjjVVFKUjtp1WryVe39SWakm7Exe5CJccfOq4T1YxSEW6R3cH2S4hHdiQ4mFeNFgchKfcQ67+EhDb/REQmnT3q8KZ3ST/Pf5EFMK70rj4ln+Cn19jhmbrRr817wMmsa7u9SMV44/yuHnbbRvB6MFSpdZh8lGJbuY9S4FLjq/q9oaOodV/o1ld65MM1yJeQHrPNfdXtmow1AY/nSK1d3oyhJ69StfHh/WDEM7ydiPdiF80PkYpyRbgOednvh3SJOrWguVl07PTkhO/VLM5udifcpwkfDxaI5kZhEJ+rE7GFxZl+peTyUj8FcKMfbuts1hrzdqiWQ7bgXv7vJiNHIT/6b5zJCyaLJiasrBki6eMtHtxPZYWk8tj97Q7wzJerktWU8lZE2F9XAnDjvo+BkVwtXGt72Dp6ImS/p/gcIgXX+x//L2nNP51TPZxTXMXyga+0NK3pE=
*/