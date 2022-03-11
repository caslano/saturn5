//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Copyright (C) Vladimir Prus 2003
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#ifndef BOOST_GRAPH_RANDOM_HPP
#define BOOST_GRAPH_RANDOM_HPP

#include <boost/graph/graph_traits.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>

#include <boost/pending/property.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/next_prior.hpp>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/copy.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_convertible.hpp>

#include <iostream>
#include <boost/assert.hpp>

namespace boost
{

// grab a random vertex from the graph's vertex set
template < class Graph, class RandomNumGen >
typename graph_traits< Graph >::vertex_descriptor random_vertex(
    Graph& g, RandomNumGen& gen)
{
    if (num_vertices(g) > 1)
    {
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x581))
        std::size_t n = std::random(num_vertices(g));
#else
        uniform_int<> distrib(0, num_vertices(g) - 1);
        variate_generator< RandomNumGen&, uniform_int<> > rand_gen(
            gen, distrib);
        std::size_t n = rand_gen();
#endif
        typename graph_traits< Graph >::vertex_iterator i = vertices(g).first;
        return *(boost::next(i, n));
    }
    else
        return *vertices(g).first;
}

template < class Graph, class RandomNumGen >
typename graph_traits< Graph >::edge_descriptor random_edge(
    Graph& g, RandomNumGen& gen)
{
    if (num_edges(g) > 1)
    {
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x581))
        typename graph_traits< Graph >::edges_size_type n
            = std::random(num_edges(g));
#else
        uniform_int<> distrib(0, num_edges(g) - 1);
        variate_generator< RandomNumGen&, uniform_int<> > rand_gen(
            gen, distrib);
        typename graph_traits< Graph >::edges_size_type n = rand_gen();
#endif
        typename graph_traits< Graph >::edge_iterator i = edges(g).first;
        return *(boost::next(i, n));
    }
    else
        return *edges(g).first;
}

template < typename Graph, typename RandomNumGen >
typename graph_traits< Graph >::edge_descriptor random_out_edge(Graph& g,
    typename graph_traits< Graph >::vertex_descriptor src, RandomNumGen& gen)
{
    typedef typename graph_traits< Graph >::degree_size_type degree_size_type;
    typedef boost::uniform_int< degree_size_type > ui_type;
    ui_type ui(0, out_degree(src, g) - 1);
    boost::variate_generator< RandomNumGen&, ui_type > variate(gen, ui);
    typename graph_traits< Graph >::out_edge_iterator it
        = out_edges(src, g).first;
    std::advance(it, variate());
    return *it;
}

template < typename Graph, typename WeightMap, typename RandomNumGen >
typename graph_traits< Graph >::edge_descriptor weighted_random_out_edge(
    Graph& g, typename graph_traits< Graph >::vertex_descriptor src,
    WeightMap weight, RandomNumGen& gen)
{
    typedef typename property_traits< WeightMap >::value_type weight_type;
    weight_type weight_sum(0);
    BGL_FORALL_OUTEDGES_T(src, e, g, Graph) { weight_sum += get(weight, e); }
    typedef boost::uniform_real<> ur_type;
    ur_type ur(0, weight_sum);
    boost::variate_generator< RandomNumGen&, ur_type > variate(gen, ur);
    weight_type chosen_weight = variate();
    BGL_FORALL_OUTEDGES_T(src, e, g, Graph)
    {
        weight_type w = get(weight, e);
        if (chosen_weight < w)
        {
            return e;
        }
        else
        {
            chosen_weight -= w;
        }
    }
    BOOST_ASSERT(false); // Should not get here
    return typename graph_traits< Graph >::edge_descriptor();
}

namespace detail
{
    class dummy_property_copier
    {
    public:
        template < class V1, class V2 >
        void operator()(const V1&, const V2&) const
        {
        }
    };
}

template < typename MutableGraph, class RandNumGen >
void generate_random_graph1(MutableGraph& g,
    typename graph_traits< MutableGraph >::vertices_size_type V,
    typename graph_traits< MutableGraph >::vertices_size_type E,
    RandNumGen& gen, bool allow_parallel = true, bool self_edges = false)
{
    typedef graph_traits< MutableGraph > Traits;
    typedef typename Traits::edge_descriptor edge_t;
    typedef typename Traits::vertices_size_type v_size_t;
    typedef typename Traits::edges_size_type e_size_t;
    typedef typename Traits::vertex_descriptor vertex_descriptor;

    // When parallel edges are not allowed, we create a new graph which
    // does not allow parallel edges, construct it and copy back.
    // This is not efficient if 'g' already disallow parallel edges,
    // but that's task for later.
    if (!allow_parallel)
    {

        typedef
            typename boost::graph_traits< MutableGraph >::directed_category dir;
        typedef typename mpl::if_< is_convertible< dir, directed_tag >,
            directedS, undirectedS >::type select;
        adjacency_list< setS, vecS, select > g2;
        generate_random_graph1(g2, V, E, gen, true, self_edges);

        copy_graph(g2, g,
            vertex_copy(detail::dummy_property_copier())
                .edge_copy(detail::dummy_property_copier()));
    }
    else
    {

        for (v_size_t i = 0; i < V; ++i)
            add_vertex(g);

        e_size_t not_inserted_counter
            = 0; /* Number of edge insertion failures */
        e_size_t num_vertices_squared = num_vertices(g) * num_vertices(g);
        for (e_size_t j = 0; j < E; /* Increment in body */)
        {
            vertex_descriptor a = random_vertex(g, gen), b;
            do
            {
                b = random_vertex(g, gen);
            } while (self_edges == false && a == b);
            edge_t e;
            bool inserted;
            boost::tie(e, inserted) = add_edge(a, b, g);
            if (inserted)
            {
                ++j;
            }
            else
            {
                ++not_inserted_counter;
            }
            if (not_inserted_counter >= num_vertices_squared)
            {
                return; /* Rather than looping forever on complete graph */
            }
        }
    }
}

template < typename MutableGraph, class RandNumGen >
void generate_random_graph(MutableGraph& g,
    typename graph_traits< MutableGraph >::vertices_size_type V,
    typename graph_traits< MutableGraph >::vertices_size_type E,
    RandNumGen& gen, bool allow_parallel = true, bool self_edges = false)
{
    generate_random_graph1(g, V, E, gen, allow_parallel, self_edges);
}

template < typename MutableGraph, typename RandNumGen,
    typename VertexOutputIterator, typename EdgeOutputIterator >
void generate_random_graph(MutableGraph& g,
    typename graph_traits< MutableGraph >::vertices_size_type V,
    typename graph_traits< MutableGraph >::vertices_size_type E,
    RandNumGen& gen, VertexOutputIterator vertex_out,
    EdgeOutputIterator edge_out, bool self_edges = false)
{
    typedef graph_traits< MutableGraph > Traits;
    typedef typename Traits::vertices_size_type v_size_t;
    typedef typename Traits::edges_size_type e_size_t;
    typedef typename Traits::vertex_descriptor vertex_t;
    typedef typename Traits::edge_descriptor edge_t;

    for (v_size_t i = 0; i < V; ++i)
        *vertex_out++ = add_vertex(g);

    e_size_t not_inserted_counter = 0; /* Number of edge insertion failures */
    e_size_t num_vertices_squared = num_vertices(g) * num_vertices(g);
    for (e_size_t j = 0; j < E; /* Increment in body */)
    {
        vertex_t a = random_vertex(g, gen), b;
        do
        {
            b = random_vertex(g, gen);
        } while (self_edges == false && a == b);
        edge_t e;
        bool inserted;
        boost::tie(e, inserted) = add_edge(a, b, g);
        if (inserted)
        {
            *edge_out++ = std::make_pair(source(e, g), target(e, g));
            ++j;
        }
        else
        {
            ++not_inserted_counter;
        }
        if (not_inserted_counter >= num_vertices_squared)
        {
            return; /* Rather than looping forever on complete graph */
        }
    }
}

namespace detail
{

    template < class Property, class G, class RandomGenerator >
    void randomize_property(
        G& g, RandomGenerator& rg, Property, vertex_property_tag)
    {
        typename property_map< G, Property >::type pm = get(Property(), g);
        typename graph_traits< G >::vertex_iterator vi, ve;
        for (boost::tie(vi, ve) = vertices(g); vi != ve; ++vi)
        {
            pm[*vi] = rg();
        }
    }

    template < class Property, class G, class RandomGenerator >
    void randomize_property(
        G& g, RandomGenerator& rg, Property, edge_property_tag)
    {
        typename property_map< G, Property >::type pm = get(Property(), g);
        typename graph_traits< G >::edge_iterator ei, ee;
        for (boost::tie(ei, ee) = edges(g); ei != ee; ++ei)
        {
            pm[*ei] = rg();
        }
    }
}

template < class Property, class G, class RandomGenerator >
void randomize_property(G& g, RandomGenerator& rg)
{
    detail::randomize_property(
        g, rg, Property(), typename property_kind< Property >::type());
}

}

#include <boost/graph/iteration_macros_undef.hpp>

#endif

/* random.hpp
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
*/