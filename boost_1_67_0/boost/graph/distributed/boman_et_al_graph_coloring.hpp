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