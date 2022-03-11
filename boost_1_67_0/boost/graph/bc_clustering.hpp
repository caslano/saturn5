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
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
*/