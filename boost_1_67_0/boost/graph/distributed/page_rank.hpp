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