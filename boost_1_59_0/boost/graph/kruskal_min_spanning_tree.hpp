//
//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//
#ifndef BOOST_GRAPH_MST_KRUSKAL_HPP
#define BOOST_GRAPH_MST_KRUSKAL_HPP

/*
 *Minimum Spanning Tree
 *         Kruskal Algorithm
 *
 *Requirement:
 *      undirected graph
 */

#include <vector>
#include <queue>
#include <functional>

#include <boost/property_map/property_map.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/pending/disjoint_sets.hpp>
#include <boost/pending/indirect_cmp.hpp>
#include <boost/concept/assert.hpp>

namespace boost
{

// Kruskal's algorithm for Minimum Spanning Tree
//
// This is a greedy algorithm to calculate the Minimum Spanning Tree
// for an undirected graph with weighted edges. The output will be a
// set of edges.
//

namespace detail
{

    template < class Graph, class OutputIterator, class Rank, class Parent,
        class Weight >
    void kruskal_mst_impl(const Graph& G, OutputIterator spanning_tree_edges,
        Rank rank, Parent parent, Weight weight)
    {
        if (num_vertices(G) == 0)
            return; // Nothing to do in this case
        typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
        typedef typename graph_traits< Graph >::edge_descriptor Edge;
        BOOST_CONCEPT_ASSERT((VertexListGraphConcept< Graph >));
        BOOST_CONCEPT_ASSERT((EdgeListGraphConcept< Graph >));
        BOOST_CONCEPT_ASSERT((OutputIteratorConcept< OutputIterator, Edge >));
        BOOST_CONCEPT_ASSERT((ReadWritePropertyMapConcept< Rank, Vertex >));
        BOOST_CONCEPT_ASSERT((ReadWritePropertyMapConcept< Parent, Vertex >));
        BOOST_CONCEPT_ASSERT((ReadablePropertyMapConcept< Weight, Edge >));
        typedef typename property_traits< Weight >::value_type W_value;
        typedef typename property_traits< Rank >::value_type R_value;
        typedef typename property_traits< Parent >::value_type P_value;
        BOOST_CONCEPT_ASSERT((ComparableConcept< W_value >));
        BOOST_CONCEPT_ASSERT((ConvertibleConcept< P_value, Vertex >));
        BOOST_CONCEPT_ASSERT((IntegerConcept< R_value >));

        disjoint_sets< Rank, Parent > dset(rank, parent);

        typename graph_traits< Graph >::vertex_iterator ui, uiend;
        for (boost::tie(ui, uiend) = vertices(G); ui != uiend; ++ui)
            dset.make_set(*ui);

        typedef indirect_cmp< Weight, std::greater< W_value > > weight_greater;
        weight_greater wl(weight);
        std::priority_queue< Edge, std::vector< Edge >, weight_greater > Q(wl);
        /*push all edge into Q*/
        typename graph_traits< Graph >::edge_iterator ei, eiend;
        for (boost::tie(ei, eiend) = edges(G); ei != eiend; ++ei)
            Q.push(*ei);

        while (!Q.empty())
        {
            Edge e = Q.top();
            Q.pop();
            Vertex u = dset.find_set(source(e, G));
            Vertex v = dset.find_set(target(e, G));
            if (u != v)
            {
                *spanning_tree_edges++ = e;
                dset.link(u, v);
            }
        }
    }

} // namespace detail

// Named Parameters Variants

template < class Graph, class OutputIterator >
inline void kruskal_minimum_spanning_tree(
    const Graph& g, OutputIterator spanning_tree_edges)
{
    typedef typename graph_traits< Graph >::vertices_size_type size_type;
    typedef typename graph_traits< Graph >::vertex_descriptor vertex_t;
    if (num_vertices(g) == 0)
        return; // Nothing to do in this case
    typename graph_traits< Graph >::vertices_size_type n = num_vertices(g);
    std::vector< size_type > rank_map(n);
    std::vector< vertex_t > pred_map(n);

    detail::kruskal_mst_impl(g, spanning_tree_edges,
        make_iterator_property_map(
            rank_map.begin(), get(vertex_index, g), rank_map[0]),
        make_iterator_property_map(
            pred_map.begin(), get(vertex_index, g), pred_map[0]),
        get(edge_weight, g));
}

template < class Graph, class OutputIterator, class P, class T, class R >
inline void kruskal_minimum_spanning_tree(const Graph& g,
    OutputIterator spanning_tree_edges,
    const bgl_named_params< P, T, R >& params)
{
    typedef typename graph_traits< Graph >::vertices_size_type size_type;
    typedef typename graph_traits< Graph >::vertex_descriptor vertex_t;
    if (num_vertices(g) == 0)
        return; // Nothing to do in this case
    typename graph_traits< Graph >::vertices_size_type n;
    n = is_default_param(get_param(params, vertex_rank)) ? num_vertices(g) : 1;
    std::vector< size_type > rank_map(n);
    n = is_default_param(get_param(params, vertex_predecessor))
        ? num_vertices(g)
        : 1;
    std::vector< vertex_t > pred_map(n);

    detail::kruskal_mst_impl(g, spanning_tree_edges,
        choose_param(get_param(params, vertex_rank),
            make_iterator_property_map(rank_map.begin(),
                choose_pmap(get_param(params, vertex_index), g, vertex_index),
                rank_map[0])),
        choose_param(get_param(params, vertex_predecessor),
            make_iterator_property_map(pred_map.begin(),
                choose_const_pmap(
                    get_param(params, vertex_index), g, vertex_index),
                pred_map[0])),
        choose_const_pmap(get_param(params, edge_weight), g, edge_weight));
}

} // namespace boost

#endif // BOOST_GRAPH_MST_KRUSKAL_HPP

/* kruskal_min_spanning_tree.hpp
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
*/