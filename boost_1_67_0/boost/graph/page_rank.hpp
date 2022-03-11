// Copyright 2004-5 The Trustees of Indiana University.
// Copyright 2002 Brad King and Douglas Gregor

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine

#ifndef BOOST_GRAPH_PAGE_RANK_HPP
#define BOOST_GRAPH_PAGE_RANK_HPP

#include <boost/property_map/property_map.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/overloading.hpp>
#include <boost/graph/detail/mpi_include.hpp>
#include <vector>

namespace boost
{
namespace graph
{

    struct n_iterations
    {
        explicit n_iterations(std::size_t n) : n(n) {}

        template < typename RankMap, typename Graph >
        bool operator()(const RankMap&, const Graph&)
        {
            return n-- == 0;
        }

    private:
        std::size_t n;
    };

    namespace detail
    {
        template < typename Graph, typename RankMap, typename RankMap2 >
        void page_rank_step(const Graph& g, RankMap from_rank, RankMap2 to_rank,
            typename property_traits< RankMap >::value_type damping,
            incidence_graph_tag)
        {
            typedef typename property_traits< RankMap >::value_type rank_type;

            // Set new rank maps
            BGL_FORALL_VERTICES_T(v, g, Graph)
            put(to_rank, v, rank_type(1 - damping));

            BGL_FORALL_VERTICES_T(u, g, Graph)
            {
                rank_type u_rank_out
                    = damping * get(from_rank, u) / out_degree(u, g);
                BGL_FORALL_ADJ_T(u, v, g, Graph)
                put(to_rank, v, get(to_rank, v) + u_rank_out);
            }
        }

        template < typename Graph, typename RankMap, typename RankMap2 >
        void page_rank_step(const Graph& g, RankMap from_rank, RankMap2 to_rank,
            typename property_traits< RankMap >::value_type damping,
            bidirectional_graph_tag)
        {
            typedef
                typename property_traits< RankMap >::value_type damping_type;
            BGL_FORALL_VERTICES_T(v, g, Graph)
            {
                typename property_traits< RankMap >::value_type rank(0);
                BGL_FORALL_INEDGES_T(v, e, g, Graph)
                rank += get(from_rank, source(e, g))
                    / out_degree(source(e, g), g);
                put(to_rank, v, (damping_type(1) - damping) + damping * rank);
            }
        }
    } // end namespace detail

    template < typename Graph, typename RankMap, typename Done,
        typename RankMap2 >
    void page_rank(const Graph& g, RankMap rank_map, Done done,
        typename property_traits< RankMap >::value_type damping,
        typename graph_traits< Graph >::vertices_size_type n,
        RankMap2 rank_map2 BOOST_GRAPH_ENABLE_IF_MODELS_PARM(
            Graph, vertex_list_graph_tag))
    {
        typedef typename property_traits< RankMap >::value_type rank_type;

        rank_type initial_rank = rank_type(rank_type(1) / n);
        BGL_FORALL_VERTICES_T(v, g, Graph) put(rank_map, v, initial_rank);

        bool to_map_2 = true;
        while ((to_map_2 && !done(rank_map, g))
            || (!to_map_2 && !done(rank_map2, g)))
        {
            typedef typename graph_traits< Graph >::traversal_category category;

            if (to_map_2)
            {
                detail::page_rank_step(
                    g, rank_map, rank_map2, damping, category());
            }
            else
            {
                detail::page_rank_step(
                    g, rank_map2, rank_map, damping, category());
            }
            to_map_2 = !to_map_2;
        }

        if (!to_map_2)
        {
            BGL_FORALL_VERTICES_T(v, g, Graph)
            put(rank_map, v, get(rank_map2, v));
        }
    }

    template < typename Graph, typename RankMap, typename Done >
    void page_rank(const Graph& g, RankMap rank_map, Done done,
        typename property_traits< RankMap >::value_type damping,
        typename graph_traits< Graph >::vertices_size_type n)
    {
        typedef typename property_traits< RankMap >::value_type rank_type;

        std::vector< rank_type > ranks2(num_vertices(g));
        page_rank(g, rank_map, done, damping, n,
            make_iterator_property_map(ranks2.begin(), get(vertex_index, g)));
    }

    template < typename Graph, typename RankMap, typename Done >
    inline void page_rank(const Graph& g, RankMap rank_map, Done done,
        typename property_traits< RankMap >::value_type damping = 0.85)
    {
        page_rank(g, rank_map, done, damping, num_vertices(g));
    }

    template < typename Graph, typename RankMap >
    inline void page_rank(const Graph& g, RankMap rank_map)
    {
        page_rank(g, rank_map, n_iterations(20));
    }

    // TBD: this could be _much_ more efficient, using a queue to store
    // the vertices that should be reprocessed and keeping track of which
    // vertices are in the queue with a property map. Baah, this only
    // applies when we have a bidirectional graph.
    template < typename MutableGraph >
    void remove_dangling_links(
        MutableGraph& g BOOST_GRAPH_ENABLE_IF_MODELS_PARM(
            MutableGraph, vertex_list_graph_tag))
    {
        typename graph_traits< MutableGraph >::vertices_size_type old_n;
        do
        {
            old_n = num_vertices(g);

            typename graph_traits< MutableGraph >::vertex_iterator vi, vi_end;
            for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end;
                /* in loop */)
            {
                typename graph_traits< MutableGraph >::vertex_descriptor v
                    = *vi++;
                if (out_degree(v, g) == 0)
                {
                    clear_vertex(v, g);
                    remove_vertex(v, g);
                }
            }
        } while (num_vertices(g) < old_n);
    }

}
} // end namespace boost::graph

#include BOOST_GRAPH_MPI_INCLUDE(< boost / graph / distributed / page_rank.hpp >)

#endif // BOOST_GRAPH_PAGE_RANK_HPP

/* page_rank.hpp
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
*/