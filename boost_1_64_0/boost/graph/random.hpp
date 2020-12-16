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
hSlavzgc38FRuA1zsRDH43acjDtwKr6Hs/F9XIC7cDHuxtfxQ1yJe3At7sN1uB834wHcgh/hu3gId+LHuBsP4x48ggfwGH6Mn+Ix/Aw/w8/xSyzGM3gCv8GT+B2e0uYFz+AP+BVex3N4B7/BB3gBH+K3aHLgnIve+AesiJexGn6PQXgFG+JVDMNr2BV/xBi8jgn4JxyENzAFb+FIvI3ZeBcn4D1tfvEBzsJfcD0+xEIUJtYTHfACOuL36Iw30AXvohs+Qnd0cDQ/O7A8lkV/LIf10AcbYQVshhUxDJ/BwVgVM7AGzsaauBhr41oMxA1YF3diPXwfg3E/NsBD2Ag/w8ba8mM7vIwd8LqjeX904vy9AmvhKgzENdgICzAE38A2uA7b4gYMx43YDZvQXyw2xThsjv0wFAdgS0zBVpiGbXCUk/m4mIidSb+EXXAGdsW3MRXfxTTch+n4MQ7DY+inbQf0xz86mZ8xeR+X4QN8HZ04x2dQ7oEj0BdHYmXMxGqYhQ0xB7thLvbHPByB3fAFjMAp2BNfxWhtO2AMbsJeuA3j8Qj2xtPYR5tvTMQb2B9vq/QDldZOWAPRFQdhddSeoRmKS7T5xmTyo3AI9sIUHILPYzqOx/E4AV/AibgCJ2vziFPx9zgNP8FZ+DnOxgs4Hy/hAryGC7XlxNfwV1yKTq7MK3rjcqyNK7EersZQVd4aC7ATrsMeuB6zcSNOwk04B7dgAW7VtjNuw2NYiH/AnXgV39OWB9/He/h7fIS70NWN8x/64F6sjPuwLe7HcDyIg/AQpuFhHIFHcBwexWl4DOfhp7gaj+Ob+BkW4kl8D0/hETyNX+JX+A2excv4NT7Ec+jrzvkOq+AXWAuLMRBLsC1exDC8jN3we8zAH3A8XsXJeA3n4nVcin/CVXgLj+BtbbviAzyLP+O3+Is2j/gQb+IjvItP0Ed7s0u7PqMDVkdHDEEnfA6dsavK741u2BfdcQB6YA6WwUnoiVNUeo5Kv4xlcbVKr1XpDeiDF9AXr2AFdC7DcY5l0R8rogcGYGWsotLVVbqOSrfBKtgVq+IQrIkjsBbmY21cjv3xTRyAb+FA3IqD8AMcjMcwCc9hMl7CIfgTpuB9TMUnmIYunpyv0AuHoh8Ow2o4HOtgBjbCEdgCR2IHzMQIHIWDcTQmYxb+DutiPgbhDKyH72B9LMJg/Awb4lfYGO9iCJYry3kZq2ELDMWW2ANb41B8DsdjIs7EpvgqNtPmB9tiIbbDvdgBD2BH/A7D8Cp2wkfYGV28OL/jMxiOdbAbhmMkxmF3HIA9MBej8HnsifMxDpdgPG7C3rgfY9C7nHl+eE6jvM+vQSc+gUckEtnELKKA2EUUE1cJLjzyfkB/bE5EEWnEJGIhsYkoIk4RV4mHRIUu5vvrGmBp99XdJaaR34U62Yn/2D11QQT30v3X76Ozu4fu/+LeuX/2vrn/xT1zNvfK/Vv3yf2d++Oedm/cP31f3D97T9xT7of71++F++0+OMt9cP/wPXD/6P1v/41736LU/W/zbO6BS+7COZFYTPz277d/v/377d9v/37799u/3/799u//458TMfS/dv9/em5uUkaa+QkA//4zAAKr2z8DQObZPwOAPLtnAKg8B2F7b6s131HY3sdq7cNJ1Rc2ec6WujZ5LvqzAqx5rjKPO3pt8tyE+T5cWst7ZQNLuVe2j829snylk/y3ivAnFhF1aVd4ykGYeIRX1pC0JDXN+uevTXz+2u4+WVW/jv75dpNQf2RXdcoLS50Ama5E+phMjyVtvX/E9jPdX8vyXPk5T/dq8nOe+n0YD2WZL3NeVr+36YTMGyeCyW3DrFfjc2MsrvwM1W1f3r8=
*/