// Copyright 2004 The Trustees of Indiana University.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_BETWEENNESS_CENTRALITY_CLUSTERING_HPP
#define BOOST_GRAPH_BETWEENNESS_CENTRALITY_CLUSTERING_HPP

#include <boost/algorithm/minmax_element.hpp>
#include <boost/graph/betweenness_centrality.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/pending/indirect_cmp.hpp>
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
            = *boost::first_max_element(edges_iters.first, edges_iters.second, cmp);
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