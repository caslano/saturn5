// Copyright (C) 2005-2008 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_DISTRIBUTED_BOMAN_ET_AL_GRAPH_COLORING_HPP
#define BOOST_GRAPH_DISTRIBUTED_BOMAN_ET_AL_GRAPH_COLORING_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/parallel/algorithm.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/parallel/process_group.hpp>
#include <functional>
#include <vector>
#include <utility>
#include <boost/graph/iteration_macros.hpp>
#include <boost/optional.hpp>
#include <boost/assert.hpp>
#include <boost/graph/parallel/container_traits.hpp>
#include <boost/graph/properties.hpp>

#ifdef PBGL_ACCOUNTING
#  include <boost/graph/accounting.hpp>
#endif // PBGL_ACCOUNTING

namespace boost { namespace graph { namespace distributed {

/**************************************************************************
 * This source file implements the distributed graph coloring algorithm   *
 * by Boman et al in:                                                     *
 *                                                                        *
 *   Erik G. Boman, Doruk Bozdag, Umit Catalyurek, Assefaw H. Gebremedhin,*
 *   and Fredrik Manne. A Scalable Parallel Graph Coloring Algorithm for  *
 *   Distributed Memory Computers. [unpublished preprint?]                *
 *                                                                        *
 **************************************************************************/

#ifdef PBGL_ACCOUNTING
struct boman_et_al_graph_coloring_stats_t
{
  /* The size of the blocks to step through (i.e., the parameter s). */
  std::size_t block_size;
  
  /* Total wall-clock time used by the algorithm.*/
  accounting::time_type execution_time;

  /* The number of conflicts that occurred during execution. */
  std::size_t conflicts;

  /* The number of supersteps. */
  std::size_t supersteps;

  /* The number of colors used. */
  std::size_t num_colors;

  template<typename OutputStream>
  void print(OutputStream& out)
  {
    out << "Problem = \"Coloring\"\n"
        << "Algorithm = \"Boman et al\"\n"
        << "Function = boman_et_al_graph_coloring\n"
        << "(P) Block size = " << block_size << "\n"
        << "Wall clock time = " << accounting::print_time(execution_time) 
        << "\nConflicts = " << conflicts << "\n"
        << "Supersteps = " << supersteps << "\n"
        << "(R) Colors = " << num_colors << "\n";
  }
};

static boman_et_al_graph_coloring_stats_t boman_et_al_graph_coloring_stats;
#endif

namespace detail {
  template<typename T>
  struct graph_coloring_reduce
  {
    BOOST_STATIC_CONSTANT(bool, non_default_resolver = true);

    template<typename Key>
    T operator()(const Key&) const { return (std::numeric_limits<T>::max)(); }

    template<typename Key> T operator()(const Key&, T, T y) const { return y; }
  };
}

template<typename Color>
struct first_fit_color
{
  template<typename T>
  Color operator()(const std::vector<T>& marked, T marked_true)
  {
    Color k = 0;
    while (k < (Color)marked.size() && marked[k] == marked_true)
      ++k;
    return k;
  }
};

template<typename DistributedGraph, typename ColorMap, typename ChooseColor,
         typename VertexOrdering, typename VertexIndexMap>
typename property_traits<ColorMap>::value_type
boman_et_al_graph_coloring
  (const DistributedGraph& g,
   ColorMap color,
   typename graph_traits<DistributedGraph>::vertices_size_type s,
   ChooseColor choose_color,
   VertexOrdering ordering, VertexIndexMap vertex_index)
{
  using namespace boost::graph::parallel;
  using boost::parallel::all_reduce;

  typename property_map<DistributedGraph, vertex_owner_t>::const_type
    owner = get(vertex_owner, g);

  typedef typename process_group_type<DistributedGraph>::type 
    process_group_type;
  typedef typename process_group_type::process_id_type process_id_type;
  typedef typename graph_traits<DistributedGraph>::vertex_descriptor Vertex;
  typedef typename graph_traits<DistributedGraph>::vertices_size_type 
    vertices_size_type;
  typedef typename property_traits<ColorMap>::value_type color_type;
  typedef unsigned long long iterations_type;
  typedef typename std::vector<Vertex>::iterator vertex_set_iterator;
  typedef std::pair<Vertex, color_type> message_type;

#ifdef PBGL_ACCOUNTING
  boman_et_al_graph_coloring_stats.block_size = s;
  boman_et_al_graph_coloring_stats.execution_time = accounting::get_time();
  boman_et_al_graph_coloring_stats.conflicts = 0;
  boman_et_al_graph_coloring_stats.supersteps = 0;
#endif

  // Initialize color map
  color_type no_color = (std::numeric_limits<color_type>::max)();
  BGL_FORALL_VERTICES_T(v, g, DistributedGraph)
    put(color, v, no_color);
  color.set_reduce(detail::graph_coloring_reduce<color_type>());
  
  // Determine if we'll be using synchronous or asynchronous communication.
  typedef typename process_group_type::communication_category
    communication_category;
  static const bool asynchronous = 
    is_convertible<communication_category, boost::parallel::immediate_process_group_tag>::value;
  process_group_type pg = process_group(g);

  // U_i <- V_i
  std::vector<Vertex> vertices_to_color(vertices(g).first, vertices(g).second);

  iterations_type iter_num = 1, outer_iter_num = 1;
  std::vector<iterations_type> marked;
  std::vector<iterations_type> marked_conflicting(num_vertices(g), 0);
  std::vector<bool> sent_to_processors;

  std::size_t rounds = vertices_to_color.size() / s 
    + (vertices_to_color.size() % s == 0? 0 : 1);
  rounds = all_reduce(pg, rounds, boost::parallel::maximum<std::size_t>());

#ifdef PBGL_GRAPH_COLORING_DEBUG
  std::cerr << "Number of rounds = " << rounds << std::endl;
#endif

  while (rounds > 0) {
    if (!vertices_to_color.empty()) {
      // Set of conflicting vertices
      std::vector<Vertex> conflicting_vertices;

      vertex_set_iterator first = vertices_to_color.begin();
      while (first != vertices_to_color.end()) {
        // For each subset of size s (or smaller for the last subset)
        vertex_set_iterator start = first;
        for (vertices_size_type counter = s; 
             first != vertices_to_color.end() && counter > 0;
             ++first, --counter) {
          // This vertex hasn't been sent to anyone yet
          sent_to_processors.assign(num_processes(pg), false);
          sent_to_processors[process_id(pg)] = true;

          // Mark all of the colors that we see
          BGL_FORALL_OUTEDGES_T(*first, e, g, DistributedGraph) {
            color_type k = get(color, target(e, g));
            if (k != no_color) {
              if (k >= (color_type)marked.size()) marked.resize(k + 1, 0);
              marked[k] = iter_num;
            }
          }

          // Find a color for this vertex
          put(color, *first, choose_color(marked, iter_num));

#ifdef PBGL_GRAPH_COLORING_DEBUG
          std::cerr << "Chose color " << get(color, *first) << " for vertex "
                    << *first << std::endl;
#endif

          // Send this vertex's color to the owner of the edge target.
          BGL_FORALL_OUTEDGES_T(*first, e, g, DistributedGraph) {
            if (!sent_to_processors[get(owner, target(e, g))]) {
              send(pg, get(owner, target(e, g)), 17, 
                   message_type(source(e, g), get(color, source(e, g))));
              sent_to_processors[get(owner, target(e, g))] = true;
            }
          }

          ++iter_num;
        }

        // Synchronize for non-immediate process groups.
        if (!asynchronous) { 
          --rounds;
          synchronize(pg);
        }

        // Receive boundary colors from other processors
        while (optional<std::pair<process_id_type, int> > stp = probe(pg)) {
          BOOST_ASSERT(stp->second == 17);
          message_type msg;
          receive(pg, stp->first, stp->second, msg);
          cache(color, msg.first, msg.second);
#ifdef PBGL_GRAPH_COLORING_DEBUG
          std::cerr << "Cached color " << msg.second << " for vertex " 
                    << msg.first << std::endl;
#endif
        }

        // Compute the set of conflicting vertices
        // [start, first) contains all vertices in this subset
        for (vertex_set_iterator vi = start; vi != first; ++vi) {
          Vertex v = *vi;
          BGL_FORALL_OUTEDGES_T(v, e, g, DistributedGraph) {
            Vertex w = target(e, g);
            if (get(owner, w) != process_id(pg) // boundary vertex
                && marked_conflicting[get(vertex_index, v)] != outer_iter_num
                && get(color, v) == get(color, w)
                && ordering(v, w)) {
              conflicting_vertices.push_back(v);
              marked_conflicting[get(vertex_index, v)] = outer_iter_num;
              put(color, v, no_color);
#ifdef PBGL_GRAPH_COLORING_DEBUG
              std::cerr << "Vertex " << v << " has a conflict with vertex "
                        << w << std::endl;
#endif
              break;
            }
          }
        }

#ifdef PBGL_ACCOUNTING
        boman_et_al_graph_coloring_stats.conflicts += 
          conflicting_vertices.size();
#endif
      }

      if (asynchronous) synchronize(pg);
      else {
        while (rounds > 0) {
          synchronize(pg);
          --rounds;
        }
      }
      conflicting_vertices.swap(vertices_to_color);
      ++outer_iter_num;
    } else {
      if (asynchronous) synchronize(pg);
      else {
        while (rounds > 0) {
          synchronize(pg);
          --rounds;
        }
      }
    }

    // Receive boundary colors from other processors
    while (optional<std::pair<process_id_type, int> > stp = probe(pg)) {
      BOOST_ASSERT(stp->second == 17);
      message_type msg;
      receive(pg, stp->first, stp->second, msg);
      cache(color, msg.first, msg.second);
    }

    rounds = vertices_to_color.size() / s 
      + (vertices_to_color.size() % s == 0? 0 : 1);
    rounds = all_reduce(pg, rounds, boost::parallel::maximum<std::size_t>());

#ifdef PBGL_ACCOUNTING
    ++boman_et_al_graph_coloring_stats.supersteps;
#endif
  }

  // Determine the number of colors used.
  color_type num_colors = 0;
  BGL_FORALL_VERTICES_T(v, g, DistributedGraph) {
    color_type k = get(color, v);
    BOOST_ASSERT(k != no_color);
    if (k != no_color) {
      if (k >= (color_type)marked.size()) marked.resize(k + 1, 0); // TBD: perf?
      if (marked[k] != iter_num) {
        marked[k] = iter_num;
        ++num_colors;
      }
    }
  }

  num_colors = 
    all_reduce(pg, num_colors, boost::parallel::maximum<color_type>());


#ifdef PBGL_ACCOUNTING
  boman_et_al_graph_coloring_stats.execution_time = 
    accounting::get_time() - boman_et_al_graph_coloring_stats.execution_time;
  
  boman_et_al_graph_coloring_stats.conflicts = 
    all_reduce(pg, boman_et_al_graph_coloring_stats.conflicts,
               std::plus<color_type>());
  boman_et_al_graph_coloring_stats.num_colors = num_colors;
#endif

  return num_colors;
}


template<typename DistributedGraph, typename ColorMap, typename ChooseColor, 
         typename VertexOrdering>
inline typename property_traits<ColorMap>::value_type
boman_et_al_graph_coloring
  (const DistributedGraph& g, ColorMap color,
   typename graph_traits<DistributedGraph>::vertices_size_type s,
   ChooseColor choose_color, VertexOrdering ordering)
{
  return boman_et_al_graph_coloring(g, color, s, choose_color, ordering, 
                                    get(vertex_index, g));
}

template<typename DistributedGraph, typename ColorMap, typename ChooseColor>
inline typename property_traits<ColorMap>::value_type
boman_et_al_graph_coloring
  (const DistributedGraph& g,
   ColorMap color,
   typename graph_traits<DistributedGraph>::vertices_size_type s,
   ChooseColor choose_color)
{
  typedef typename graph_traits<DistributedGraph>::vertex_descriptor
    vertex_descriptor;
  return boman_et_al_graph_coloring(g, color, s, choose_color,
                                    std::less<vertex_descriptor>());
}

template<typename DistributedGraph, typename ColorMap>
inline typename property_traits<ColorMap>::value_type
boman_et_al_graph_coloring
  (const DistributedGraph& g,
   ColorMap color,
   typename graph_traits<DistributedGraph>::vertices_size_type s = 100)
{
  typedef typename property_traits<ColorMap>::value_type Color;
  return boman_et_al_graph_coloring(g, color, s, first_fit_color<Color>());
}

} } } // end namespace boost::graph::distributed

namespace boost { namespace graph {
using distributed::boman_et_al_graph_coloring;
} } // end namespace boost::graph

#endif // BOOST_GRAPH_DISTRIBUTED_BOMAN_ET_AL_GRAPH_COLORING_HPP

/* boman_et_al_graph_coloring.hpp
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
*/