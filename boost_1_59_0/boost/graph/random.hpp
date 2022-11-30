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
#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x581))
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
#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x581))
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