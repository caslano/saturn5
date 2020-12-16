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
vTmT60M30s30BfomHcr1GuBfvywujy6gK+kVWVxOFreXXm3qxfp3jOEz9Dn6Mr2XbnwkX7XR4s/T/Wj//AU5LPdFri99zdj653okvIz59j0Sv43xmYzfnGuc92h+E2/9G875pz/SM76c8TPpS/75zL+A8YcYn8jwLoYHMt1WhhvUmp7xHobzGS5geBw9iM7k/El0PB3xyHbszuF+pJvo03QbfYG+Qu/ket9h+AEdyuX3o9cxPt9fz3QC3ZfezfUKZ7mD6Hg61V+f9Al/PdJDmL89p+f23eJ8F+PL6Fg6mL7PdFvoFfT6R9rBxkfKn/lIOJ/HcxodR8fQwfS1qaxneh+9iV5MV9IF9CR6KN2P7pzC/oS+TLfQR+h99A768N9CzHrQF+lbYlMxxn1pOz2WnkrPoN30MnojvZM+SJ+gz9PtdCcd/nfjgfRIOpFOpbPp6XQZ7aYX0avpzfROupFupi/RHXRwp3E/eigdRyfRafR0tS6fXqHW5dL76ZP0BbqDDv2HcTQ9hB5HT6Zn0nPohfQ6eg99gr5Id9DBD4yH0xm0k26gD9LN9CX6Fh3Yxf1Ex9OpdD5dTi/q4nrS27q4vvRhuoW+Qt+n+9l4/NKT6ALaSa+ht9P76RP0WdpHBwcYR9GD6Xg6LYDLoSvpFfQmeg/dRLfR1+j7dHQg+wd6Mj2TXkBvoHfTTfRZ+gp9lw4OYvn0cHocnUznB7G+6GX0piBuB30oiPVGtwVxe+j7dL9g45F0Kj2ddtOr6e30Ibo1mOXSd+nQEG4HPZaeTBfSTnoRvYbeQh+kW0O4HPoOHRzK8ZeOpSfQOXQpvZheT2+l99CH6TP0JfoW/YDu+5ixnY6nJ9Mz6Ep6Ib2O3kzvpQ/RrfQlup2+S0eEcZyl4+lUuoB20avpPfQRuo2+Rgf24vFDx9HJdC5dTi+iG+j99Dn6Kn1bbAYG1hs9iB5JJ9H5tIfeSO+gD9ItdDsd2pvnw/RwOomeSk+n3fQiej29nT5Et9JX6U46OoLXF3QqnUeX08vobfRBuoW+Rgf2Yf3TSfRUeg69ht5Nn6DP0lfoO3REX9YznUHPpGvpdfQeupm+THfS0ZFsd3QanU9X0svorfQB+iR9ke6gg6N4vkWPopPpAtpDN9C76GP0OfombXuc7YIeSafSM+haeg29md5Hn6Ev0R10Jx3Wj+2ajqWT6Gy6mF6k1uXQu+gjdBt9mb5Fh76L7YROovPouXQDvZtupi/Q7XRgNPcrPZyeTM+ka+mN9D66jb5D2/qzPHoUnUoX0E56Pb2DPkifpi/S9/zlDuB+pNPoPLqMXkivo3fSh+gW+hJ9m35AR7yb1yf0ODqbnkG76aX0RnoPfYy+QN+mH9ARMbwuoMfS2XQpXUs30Nvp/fQxuo2+Rt+lQ99jHEUPpIfScfRUOp8uo+fSK+iN9C76IH2SbqUv0jfp8IE8zukEtS6XLqUX0avprfR++gjdQl+lO+mBT3C/0Zl0Ie2kF9Jr6G30PvoY3UbfpIMHcTl0LD2BzqMr6WX0JnoXfZhupX207b3GdnoCPZ320OvoLfQe+hh9ib5H9x3M45xOpsvoNfQ2+hB9hm6nA9/HfpUeSSfTBXQZvYBuoPfSJ+hz9E061M52QsfTGfQM2k0vozfRB+mT9CX6Jh34JNefjqWT6Ex6Ju2kF9Mb6T30CfoCfYeOGML6ppPoHLqSXklvpw/SLfRVOvgptjs6ic6nXfQaejO9k95HH6PbaB8dOpT9Ap1K59ML6R30QbqJbqOv0LfpqGFsJ/QkOpcuoxfQ69W6HLqRbqXb6Qd01HCuNz2BLqA99Bp6O91In6U76NARrGc6gc6kZ9KL6A30bvoIfZY=
*/