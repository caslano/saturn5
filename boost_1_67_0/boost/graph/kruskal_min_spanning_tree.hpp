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