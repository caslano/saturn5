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
q0lL7TaaGXz0cYvanLma31NJ7l3HdVGx7POUSJaXGi/lw8/ACuiZx2ck/6ZD+KDvv7X75zL5bKWGztD0fUSAyu7AXX5W3FVxP7OoZ0HbySeuX5xz0vyz2dFVrRlpka/G1Lon268Xr6H1xwS1XtzxpH6vXIH0nlTetTS3VDrUmZ145mg1nt3Tco3y+flZO+X7q8M4Fxv3dy/Q/KSn6StokT5aPUeQ9xSZmi7H4bk0N5TQ+cNghBxc8XwfqH2j8h2ZRf3fCORVKteXslxqj6VkEmD3bZL5hGQmJPK/NYF3QUKtfmboSw9RvU1FTY2EfTHPfPEY9SXHakui9UtbEiuJeMmaEd2dzUdYGd2fvRZt6ZbEZdUc+B3rRs+4C7EWFHQdtd+tKWPZ3mh7zAB2dswyS05cNrshbn3s1JRiVkGy4qONuSRb5OiNp65Z1pHsZ9ZCtjFyIkuN6s9qox6z9o8dYmmK68EWxeWw/vFZrDF+GNsTXxRzQcoY9mhKLKtL5XO53rdRCeo+eQb5tzCur2V8zBOx2QJX+4cpXXrh/iD3DvR8dRvVWaQ+htWzH30dtp76ajrl+RPijz5OcS2PvgYS44WeOx4kmX2G9qJfyeCrNXEfAnKUZPZSn0+SZzqtfv0+cuvTtJbg/YPiHT3PGWjV3gUR61bjPiZS7n0ccszEUPxDPIO04zS7l9pb6etzfQ2h37P97c7PppHsZTipONdC5VRrXLGH3ZCkreNcobaAm/UW+3lpY4W0cZl1VWQu0+zME+PTi1lHlf0Y3UNcTOt3DTt4vNLShU206GsUnkOvr08pT5x6v6TPVh4fLc4hlY46SxSbbNH3Theq91X6U/p4GdfkuyCurY/drS3BkKqLJJ5OIzlG2exL2ESK6zaFnxnybAQn2krHT7eK5x9pLFK+c0N1HjL2g8HbIINYR2V2UNpwVeY5ZC/6xPaT9XoeyV8V9Qe2NpLWFWpsjEnoxV6O+zpuItXNVmoTr7hfWMLbb7OV9mxKrinownGudn85yE6UP1mfGvcCnb9GprCbI8lnVaYEFqfqrYl0b+pEt/7sp1XV21ukN071qQ8pfoOMt6+rkP7sQM3Vu0l+BdJPQ6/ozi5CW8ep5wxeliTlKmmtMYsVMJvYk3RaxhPbbxrlPR26RPv5KX7cmsz+bO2qzpaacbiktyEjme9s09jdNvJFjcGu5MuQHlQPTdq9Ge9qtKt74xxxzYu0r1V1sm6neHadpPZPIVrgUtvKs6uVVG85mLWz8XbddWyYhfeFcvtE6O8+CHsVVEpCwmX74/C8hRf3OeDibFC8T2Ycs4s3UjvT8xlNxzjouIPriL1sh6bjWeBGmQsgc00aZOKXDlJ2wmSWQuZKLpOwNKUzPQ/oehZ2pmeXrscTrqc3yYgPOK7iMrZlBxMiIxNsGfif+wl5K/hPExHC9PZHnmU8T9xypuldFKZ3ptK7fBjp7XNqvZfqeicqvWEyqyGzitdxl5tWdGb7FcjcxWVsN12aEBmTYBt4atsHkKfagTwxN31hxBOH4F1EXqbklc9r9jaE5c3VZR7tTGYmZFZT31ipyv28lJkScY6dA4uR3oT70N3g9yDci3Cf4Hr8FPweTVaL/0D+QnL7+BlJHV3rvElyv+Rzedp/IHDbNckn9+9clH+3dp0IPIyvAb+f1wHFRbgWYQbCXTJ+g/YuHWSWgy9GWJJoeL9E5l1hyP85sF9I7BCuD4fJ/N0u3t1NQfkGgQ+xi/dYhhIX6alJgnc3vPN3SPLPEkX4GcICyP8CZbwR4SaEmxFWIjyFtJflO8K7iQvbb4I3Gq6z5DPmGQgzKU2U4w9Iv4XeTxXXt8rr28BvR7hDxr3gQ1M=
*/