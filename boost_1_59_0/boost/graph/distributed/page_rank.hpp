// Copyright (C) 2004-2006 The Trustees of Indiana University.
// Copyright (C) 2002 Brad King and Douglas Gregor

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
//           Brian Barrett
#ifndef BOOST_PARALLEL_GRAPH_PAGE_RANK_HPP
#define BOOST_PARALLEL_GRAPH_PAGE_RANK_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <boost/assert.hpp>
#include <boost/graph/overloading.hpp>
#include <boost/graph/page_rank.hpp>
#include <boost/graph/distributed/concepts.hpp>
#include <boost/property_map/parallel/distributed_property_map.hpp>
#include <boost/property_map/parallel/caching_property_map.hpp>
#include <boost/graph/parallel/algorithm.hpp>
#include <boost/graph/parallel/container_traits.hpp>

// #define WANT_MPI_ONESIDED 1

namespace boost { namespace graph { namespace distributed {

namespace detail {
#ifdef WANT_MPI_ONESIDED
  template<typename Graph, typename RankMap, typename owner_map_t>
  void page_rank_step(const Graph& g, RankMap from_rank, MPI_Win to_win, 
                      typename property_traits<RankMap>::value_type damping,
                      owner_map_t owner)
  {
    typedef typename property_traits<RankMap>::value_type rank_type;
    int me, ret;
    MPI_Comm_rank(MPI_COMM_WORLD, &me);

    // MPI_Accumulate is not required to store the value of the data
    // being sent, only the address.  The value of the memory location
    // must not change until the end of the access epoch, meaning the
    // call to MPI_Fence.  We therefore store the updated value back
    // into the from_rank map before the accumulate rather than using
    // a temporary.  We're going to reset the values in the from_rank
    // before the end of page_rank_step() anyway, so this isn't a huge
    // deal.  But MPI-2 One-sided is an abomination.
    BGL_FORALL_VERTICES_T(u, g, Graph) {
      put(from_rank, u, (damping * get(from_rank, u) / out_degree(u, g)));
      BGL_FORALL_ADJ_T(u, v, g, Graph) {
        ret = MPI_Accumulate(&(from_rank[u]),
                             1, MPI_DOUBLE,
                             get(owner, v), local(v), 
                             1, MPI_DOUBLE, MPI_SUM, to_win);
        BOOST_ASSERT(MPI_SUCCESS == ret);
      }
    }
    MPI_Win_fence(0, to_win);

    // Set new rank maps for the other map.  Do this now to get around
    // the stupid synchronization rules of MPI-2 One-sided
    BGL_FORALL_VERTICES_T(v, g, Graph) put(from_rank, v, rank_type(1 - damping));
  }
#endif

  template<typename T>
  struct rank_accumulate_reducer {
    BOOST_STATIC_CONSTANT(bool, non_default_resolver = true);

    template<typename K>
    T operator()(const K&) const { return T(0); }

    template<typename K>
    T operator()(const K&, const T& x, const T& y) const { return x + y; }
  };
} // end namespace detail

template<typename Graph, typename RankMap, typename Done, typename RankMap2>
void
page_rank_impl(const Graph& g, RankMap rank_map, Done done, 
               typename property_traits<RankMap>::value_type damping,
               typename graph_traits<Graph>::vertices_size_type n,
               RankMap2 rank_map2)
{
  typedef typename property_traits<RankMap>::value_type rank_type;

  int me;
  MPI_Comm_rank(MPI_COMM_WORLD, &me);

  typename property_map<Graph, vertex_owner_t>::const_type
    owner = get(vertex_owner, g);
  (void)owner;

  typedef typename boost::graph::parallel::process_group_type<Graph>
    ::type process_group_type;
  typedef typename process_group_type::process_id_type process_id_type;

  process_group_type pg = process_group(g);
  process_id_type id = process_id(pg);

  BOOST_ASSERT(me == id);

  rank_type initial_rank = rank_type(rank_type(1) / n);
  BGL_FORALL_VERTICES_T(v, g, Graph) put(rank_map, v, initial_rank);

#ifdef WANT_MPI_ONESIDED

  BOOST_ASSERT(sizeof(rank_type) == sizeof(double));

  bool to_map_2 = true;
  MPI_Win win, win2;

  MPI_Win_create(&(rank_map[*(vertices(g).first)]), 
                 sizeof(double) * num_vertices(g),
                 sizeof(double), 
                 MPI_INFO_NULL, MPI_COMM_WORLD, &win);
  MPI_Win_set_name(win, "rank_map_win");
  MPI_Win_create(&(rank_map2[*(vertices(g).first)]), 
                 sizeof(double) * num_vertices(g),
                 sizeof(double), 
                 MPI_INFO_NULL, MPI_COMM_WORLD, &win2);
  MPI_Win_set_name(win, "rank_map2_win");

  // set initial rank maps for the first iteration...
  BGL_FORALL_VERTICES_T(v, g, Graph) put(rank_map2, v, rank_type(1 - damping));

  MPI_Win_fence(0, win);
  MPI_Win_fence(0, win2);

  while ((to_map_2 && !done(rank_map, g)) ||
         (!to_map_2 && !done(rank_map2, g))) {
    if (to_map_2) {
      graph::distributed::detail::page_rank_step(g, rank_map, win2, damping, owner);
      to_map_2 = false;
    } else {
      graph::distributed::detail::page_rank_step(g, rank_map2, win, damping, owner);
      to_map_2 = true;
    }
  }
  synchronize(boost::graph::parallel::process_group(g));

  MPI_Win_free(&win);
  MPI_Win_free(&win2);

#else  
  // The ranks accumulate after each step.
  rank_map.set_reduce(detail::rank_accumulate_reducer<rank_type>());
  rank_map2.set_reduce(detail::rank_accumulate_reducer<rank_type>());
  rank_map.set_consistency_model(boost::parallel::cm_flush | boost::parallel::cm_reset);
  rank_map2.set_consistency_model(boost::parallel::cm_flush | boost::parallel::cm_reset);

  bool to_map_2 = true;
  while ((to_map_2 && !done(rank_map, g)) ||
         (!to_map_2 && !done(rank_map2, g))) {
    /**
     * PageRank can implemented slightly more efficiently on a
     * bidirectional graph than on an incidence graph. However,
     * distributed PageRank requires that we have the rank of the
     * source vertex available locally, so we force the incidence
     * graph implementation, which pushes rank from source to
     * target.
     */
    typedef incidence_graph_tag category;
    if (to_map_2) {
      graph::detail::page_rank_step(g, rank_map, rank_map2, damping,
                                    category());
      to_map_2 = false;
    } else {
      graph::detail::page_rank_step(g, rank_map2, rank_map, damping,
                                    category());
      to_map_2 = true;
    }
    using boost::graph::parallel::process_group;
    synchronize(process_group(g));
  }

  rank_map.reset();
#endif
      
  if (!to_map_2)
    BGL_FORALL_VERTICES_T(v, g, Graph) put(rank_map, v, get(rank_map2, v));
}

template<typename Graph, typename RankMap, typename Done, typename RankMap2>
void
page_rank(const Graph& g, RankMap rank_map, Done done, 
          typename property_traits<RankMap>::value_type damping,
          typename graph_traits<Graph>::vertices_size_type n,
          RankMap2 rank_map2
          BOOST_GRAPH_ENABLE_IF_MODELS_PARM(Graph, distributed_graph_tag)) 
{
  (page_rank_impl)(g, rank_map, done, damping, n, rank_map2);
}

template<typename MutableGraph>
void
remove_dangling_links(MutableGraph& g
                      BOOST_GRAPH_ENABLE_IF_MODELS_PARM(MutableGraph, 
                                                        distributed_graph_tag))
{
  typename graph_traits<MutableGraph>::vertices_size_type old_n;
  do {
    old_n = num_vertices(g);

    typename graph_traits<MutableGraph>::vertex_iterator vi, vi_end;
    for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; /* in loop */) {
      typename graph_traits<MutableGraph>::vertex_descriptor v = *vi++;
      if (out_degree(v, g) == 0) {
        clear_vertex(v, g);
        remove_vertex(v, g);
      }
    }
  } while (num_vertices(g) < old_n);
}

} // end namespace distributed

using distributed::page_rank;
using distributed::remove_dangling_links;

} } // end namespace boost::graph

#endif // BOOST_PARALLEL_GRAPH_PAGE_RANK_HPP

/* page_rank.hpp
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
*/