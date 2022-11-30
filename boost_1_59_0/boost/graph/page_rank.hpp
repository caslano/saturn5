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

#include BOOST_GRAPH_MPI_INCLUDE(<boost/graph/distributed/page_rank.hpp>)

#endif // BOOST_GRAPH_PAGE_RANK_HPP

/* page_rank.hpp
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
*/