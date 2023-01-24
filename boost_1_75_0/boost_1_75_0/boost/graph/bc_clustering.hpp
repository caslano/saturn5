// Copyright 2004 The Trustees of Indiana University.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_BETWEENNESS_CENTRALITY_CLUSTERING_HPP
#define BOOST_GRAPH_BETWEENNESS_CENTRALITY_CLUSTERING_HPP

#include <boost/graph/betweenness_centrality.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/pending/indirect_cmp.hpp>
#include <algorithm>
#include <vector>
#include <boost/property_map/property_map.hpp>

namespace boost
{

/** Threshold termination function for the betweenness centrality
 * clustering algorithm.
 */
template < typename T > struct bc_clustering_threshold
{
    typedef T centrality_type;

    /// Terminate clustering when maximum absolute edge centrality is
    /// below the given threshold.
    explicit bc_clustering_threshold(T threshold)
    : threshold(threshold), dividend(1.0)
    {
    }

    /**
     * Terminate clustering when the maximum edge centrality is below
     * the given threshold.
     *
     * @param threshold the threshold value
     *
     * @param g the graph on which the threshold will be calculated
     *
     * @param normalize when true, the threshold is compared against the
     * normalized edge centrality based on the input graph; otherwise,
     * the threshold is compared against the absolute edge centrality.
     */
    template < typename Graph >
    bc_clustering_threshold(T threshold, const Graph& g, bool normalize = true)
    : threshold(threshold), dividend(1.0)
    {
        if (normalize)
        {
            typename graph_traits< Graph >::vertices_size_type n
                = num_vertices(g);
            dividend = T((n - 1) * (n - 2)) / T(2);
        }
    }

    /** Returns true when the given maximum edge centrality (potentially
     * normalized) falls below the threshold.
     */
    template < typename Graph, typename Edge >
    bool operator()(T max_centrality, Edge, const Graph&)
    {
        return (max_centrality / dividend) < threshold;
    }

protected:
    T threshold;
    T dividend;
};

/** Graph clustering based on edge betweenness centrality.
 *
 * This algorithm implements graph clustering based on edge
 * betweenness centrality. It is an iterative algorithm, where in each
 * step it compute the edge betweenness centrality (via @ref
 * brandes_betweenness_centrality) and removes the edge with the
 * maximum betweenness centrality. The @p done function object
 * determines when the algorithm terminates (the edge found when the
 * algorithm terminates will not be removed).
 *
 * @param g The graph on which clustering will be performed. The type
 * of this parameter (@c MutableGraph) must be a model of the
 * VertexListGraph, IncidenceGraph, EdgeListGraph, and Mutable Graph
 * concepts.
 *
 * @param done The function object that indicates termination of the
 * algorithm. It must be a ternary function object thats accepts the
 * maximum centrality, the descriptor of the edge that will be
 * removed, and the graph @p g.
 *
 * @param edge_centrality (UTIL/OUT) The property map that will store
 * the betweenness centrality for each edge. When the algorithm
 * terminates, it will contain the edge centralities for the
 * graph. The type of this property map must model the
 * ReadWritePropertyMap concept. Defaults to an @c
 * iterator_property_map whose value type is
 * @c Done::centrality_type and using @c get(edge_index, g) for the
 * index map.
 *
 * @param vertex_index (IN) The property map that maps vertices to
 * indices in the range @c [0, num_vertices(g)). This type of this
 * property map must model the ReadablePropertyMap concept and its
 * value type must be an integral type. Defaults to
 * @c get(vertex_index, g).
 */
template < typename MutableGraph, typename Done, typename EdgeCentralityMap,
    typename VertexIndexMap >
void betweenness_centrality_clustering(MutableGraph& g, Done done,
    EdgeCentralityMap edge_centrality, VertexIndexMap vertex_index)
{
    typedef typename property_traits< EdgeCentralityMap >::value_type
        centrality_type;
    typedef typename graph_traits< MutableGraph >::edge_iterator edge_iterator;
    typedef
        typename graph_traits< MutableGraph >::edge_descriptor edge_descriptor;

    if (has_no_edges(g))
        return;

    // Function object that compares the centrality of edges
    indirect_cmp< EdgeCentralityMap, std::less< centrality_type > > cmp(
        edge_centrality);

    bool is_done;
    do
    {
        brandes_betweenness_centrality(g,
            edge_centrality_map(edge_centrality)
                .vertex_index_map(vertex_index));
        std::pair< edge_iterator, edge_iterator > edges_iters = edges(g);
        edge_descriptor e
            = *max_element(edges_iters.first, edges_iters.second, cmp);
        is_done = done(get(edge_centrality, e), e, g);
        if (!is_done)
            remove_edge(e, g);
    } while (!is_done && !has_no_edges(g));
}

/**
 * \overload
 */
template < typename MutableGraph, typename Done, typename EdgeCentralityMap >
void betweenness_centrality_clustering(
    MutableGraph& g, Done done, EdgeCentralityMap edge_centrality)
{
    betweenness_centrality_clustering(
        g, done, edge_centrality, get(vertex_index, g));
}

/**
 * \overload
 */
template < typename MutableGraph, typename Done >
void betweenness_centrality_clustering(MutableGraph& g, Done done)
{
    typedef typename Done::centrality_type centrality_type;
    std::vector< centrality_type > edge_centrality(num_edges(g));
    betweenness_centrality_clustering(g, done,
        make_iterator_property_map(edge_centrality.begin(), get(edge_index, g)),
        get(vertex_index, g));
}

} // end namespace boost

#endif // BOOST_GRAPH_BETWEENNESS_CENTRALITY_CLUSTERING_HPP

/* bc_clustering.hpp
mOSdTySf6npYXFyN6HtPytdvS3mm179xR9oTyX9Sit+V/kzlb8L7oy75adHan4Wo7sT0/R7Jf9pJkp9kPPBM5W/df/iZ2n/7wWPPtP/tPHL8ieWnRE+FnSunsuepO4mkz+KRyiVKi9bBrpVa2L1CfBZ7/GSd8g9vWQ/p65fCtmWzIC4qDFbrx8LSqcNg4cSBrDwV62KpUmrdyipH8aNE6E2lrZomtG1m9lO4fuEa6bromqlt6Tvp6EIrpkEqnktEvHtOnnqm7U/z+bNs/305p59p++9H3+ZZtj/5V8+y/WuSn7rup19EPtGg9m8/rCrfNH80SJQ9eyhk63vDyand4MT37SHzu3/BsX4BcOybP8PRns2fCrmTX2lcDfa9K6FiTzRU7F4OZalLoWzXYrDtWADWbfPAsmUuWAyRULwpHIrifoCCDdPgUcxUeLB2ItxbFQr5K76Hu8tGw50lw+H2oqFwc8EguDF/AFyP6gfX5vSBa5EhkDtLU7f8dJK/jMkvTVnE3ru3bpsPPMovQflFmyKgKH4GFGzUwaP1JH8S3Fs9HvKjx0KeTP6tBYPhJpPfF+X3hmuzUX5kzfKfpf296dkkuY9kfOa/Bzf/2a4zBcfXPjjuMfr0beiHx2/bBUH/T8Xv2gWz7wbg8dv2b+EY+Q+W79vubdZXt63B8TE/Dw6eOQ/7T52DvVmnYU9WNq6FT+Ja+AhsyTgAhvR9
*/