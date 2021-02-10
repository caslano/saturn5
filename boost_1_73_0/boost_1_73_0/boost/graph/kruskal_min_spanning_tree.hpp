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
Et1X9K7awdONBv2WQQplKy9M7vzYBrO9jiMWz0uSu2kOcN85e7U9g6Rw2D05GR8NBxdvjwwdWWlFuaWGgT6vHffnW2F+TjuoWHt0QY6cOUlQN+6XViUE0cS0R8GEAi5oK1KBDTaYv8jJamJL5m1vRQm2IIjlDSkvyhf6xR99oUtBUYRFTrUrLo60XBagtLdfEL7YpZajkkUwggv0GiSdeBWy9+xIusoqf1s8a/Fi/BMAPfdCcmGJVuQ6cjmPJjd4Uoex7eI5usxP6PgO2wMpcMehgHTiAfhoGRGjcJ5R7Wf8mzKbYNKTYD7H8HT0lYGfeCSG3iFYj0PEVZiymFuSrQ42sQAhGfuGsd550Cw2cskmK0wcc+UFMAH0hsEWObiPHVe86b3uQpIP7zPgVR2mS9NiPqdagX0Bqyj0+b5Ah3W9TWCi5HTvbBFbXKpysf/3nSVyybU5qhnjSIEVrwT1xh8/Hh4PR+PRoPeuP/5ZcmCFtGdCpOugv37mjBL6dy7CcxrELjpcyXqJ799AQQEEkIL67w4vznoCGLoTAZRyF8kVPmZo8vl38QOM4s5/Fvt0zKuQ8fJebhsKgOJ4/7yNTzp8FSzBKPKZtAdPt8NpD+aU+gdBnMjNlZUI/Y+p3HcCMiTmmqUMDUELVUA9
*/