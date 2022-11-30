// Copyright (C) 2004-2008 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_DISTRIBUTED_DFS_HPP
#define BOOST_GRAPH_DISTRIBUTED_DFS_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/overloading.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/distributed/concepts.hpp>
#include <boost/static_assert.hpp>
#include <boost/assert.hpp>
#include <boost/graph/parallel/process_group.hpp>
#include <boost/graph/parallel/container_traits.hpp>

namespace boost {
  namespace graph { namespace distributed { namespace detail {
    template<typename DistributedGraph, typename ColorMap, typename ParentMap,
             typename ExploreMap, typename VertexIndexMap, typename DFSVisitor>
    class parallel_dfs
    {
      typedef typename graph_traits<DistributedGraph>::vertex_iterator
        vertex_iterator;
      typedef typename graph_traits<DistributedGraph>::vertex_descriptor
        vertex_descriptor;
      typedef typename graph_traits<DistributedGraph>::out_edge_iterator
        out_edge_iterator;

      typedef typename boost::graph::parallel::process_group_type<DistributedGraph>
        ::type process_group_type;
      typedef typename process_group_type::process_id_type process_id_type;

      /**
       * The first vertex in the pair is the local node (i) and the
       * second vertex in the pair is the (possibly remote) node (j).
       */
      typedef boost::parallel::detail::untracked_pair<vertex_descriptor, vertex_descriptor> vertex_pair;

      typedef typename property_traits<ColorMap>::value_type color_type;
      typedef color_traits<color_type> Color;

      // Message types
      enum { discover_msg = 10, return_msg = 50, visited_msg = 100 , done_msg = 150};
        

    public:
      parallel_dfs(const DistributedGraph& g, ColorMap color,
                   ParentMap parent, ExploreMap explore,
                   VertexIndexMap index_map, DFSVisitor vis)
        : g(g), color(color), parent(parent), explore(explore),
          index_map(index_map), vis(vis), pg(process_group(g)),
          owner(get(vertex_owner, g)), next_out_edge(num_vertices(g))
      { }

      void run(vertex_descriptor s)
      {
        vertex_iterator vi, vi_end;
        for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi) {
          put(color, *vi, Color::white());
          put(parent, *vi, *vi); 
          put(explore, *vi, *vi);
          next_out_edge[get(index_map, *vi)] = out_edges(*vi, g).first;
          vis.initialize_vertex(*vi, g);
        }

        vis.start_vertex(s, g);
        
        if (get(owner, s) == process_id(pg)) {
          send_oob(pg, get(owner, s), discover_msg, vertex_pair(s, s));
        }
        
        bool done = false;
        while (!done) {
          std::pair<process_id_type, int> msg = *pg.poll(true);

          switch (msg.second) {
          case discover_msg:
            {
              vertex_pair p;
              receive_oob(pg, msg.first, msg.second, p);

              if (p.first != p.second) {
                // delete j from nomessage(j)
                if (get(color, p.second) != Color::black())
                  local_put(color, p.second, Color::gray());

                if (recover(p)) break;
              }

              if (get(color, p.first) == Color::white()) {
                put(color, p.first, Color::gray());
                put(parent, p.first, p.second);

                vis.discover_vertex(p.first, g);

                if (shift_center_of_activity(p.first)) break;
                
                out_edge_iterator ei, ei_end;
                for (boost::tie(ei,ei_end) = out_edges(p.first, g); ei != ei_end; ++ei)
                {
                  // Notify everyone who may not know that the source
                  // vertex has been visited. They can then mark the
                  // corresponding color map entry gray.
                  if (get(parent, p.first) != target(*ei, g)
                      && get(explore, p.first) != target(*ei, g)) {
                    vertex_pair visit(target(*ei, g), p.first);
                    
                    send_oob(pg, get(owner, target(*ei, g)), visited_msg, visit);
                  }
                }
              }
            }
            break;
            
          case visited_msg:
            {
              vertex_pair p;
              receive_oob(pg, msg.first, msg.second, p);
              
              // delete j from nomessage(j)
              if (get(color, p.second) != Color::black())
                local_put(color, p.second, Color::gray());

              recover(p);
            }
            break;
            
          case return_msg:
            {
              vertex_pair p;
              receive_oob(pg, msg.first, msg.second, p);
              
              // delete j from nomessage(i)
              local_put(color, p.second, Color::black());

              shift_center_of_activity(p.first);
            }
            break;
            
          case done_msg:
            {
              receive_oob(pg, msg.first, msg.second, done);

              // Propagate done message downward in tree
              done = true;
              process_id_type id = process_id(pg);
              process_id_type left = 2*id + 1;
              process_id_type right = left + 1;
              if (left < num_processes(pg))
                send_oob(pg, left, done_msg, done);
              if (right < num_processes(pg))
                send_oob(pg, right, done_msg, done);
            }
            break;

          default:
            BOOST_ASSERT(false);
          }
        }
      }
      
    private:
      bool recover(const vertex_pair& p)
      {
        if (get(explore, p.first) == p.second) {
          return shift_center_of_activity(p.first);
        }
        else
          return false;
      }
      
      bool shift_center_of_activity(vertex_descriptor i)
      {
        for (out_edge_iterator ei = next_out_edge[get(index_map, i)],
                               ei_end = out_edges(i, g).second;
             ei != ei_end; ++ei) {
          vis.examine_edge(*ei, g);

          vertex_descriptor k = target(*ei, g);
          color_type target_color = get(color, k);
          if (target_color == Color::black()) vis.forward_or_cross_edge(*ei, g);
          else if (target_color == Color::gray()) vis.back_edge(*ei, g);
          else {
            put(explore, i, k);
            vis.tree_edge(*ei, g);
            vertex_pair p(k, i);
            send_oob(pg, get(owner, k), discover_msg, p);
            next_out_edge[get(index_map, i)] = ++ei;
            return false;
          } 
        }

        next_out_edge[get(index_map, i)] = out_edges(i, g).second;
        put(explore, i, i);
        put(color, i, Color::black());
        vis.finish_vertex(i, g);
          
        if (get(parent, i) == i) {
          send_oob(pg, 0, done_msg, true);
          return true;
        }
        else {
          vertex_pair ret(get(parent, i), i);
          send_oob(pg, get(owner, ret.first), return_msg, ret);
        }
        return false;
      }

      const DistributedGraph& g; 
      ColorMap color;
      ParentMap parent; 
      ExploreMap explore;
      VertexIndexMap index_map;
      DFSVisitor vis;
      process_group_type pg;
      typename property_map<DistributedGraph, vertex_owner_t>::const_type owner;
      std::vector<out_edge_iterator> next_out_edge; 
    };
  } // end namespace detail

  template<typename DistributedGraph, typename ColorMap, typename ParentMap,
           typename ExploreMap, typename VertexIndexMap, typename DFSVisitor>
  void
  tsin_depth_first_visit
    (const DistributedGraph& g,
     typename graph_traits<DistributedGraph>::vertex_descriptor s,
     DFSVisitor vis, ColorMap color, ParentMap parent, ExploreMap explore, 
     VertexIndexMap index_map)
  {
    typedef typename graph_traits<DistributedGraph>::directed_category
      directed_category;
    BOOST_STATIC_ASSERT(
      (is_convertible<directed_category, undirected_tag>::value));

    set_property_map_role(vertex_color, color);
    graph::distributed::detail::parallel_dfs
      <DistributedGraph, ColorMap, ParentMap, ExploreMap, VertexIndexMap, 
       DFSVisitor> do_dfs(g, color, parent, explore, index_map, vis);
    do_dfs.run(s);

    using boost::graph::parallel::process_group;
    synchronize(process_group(g));
  }
    
  template<typename DistributedGraph, typename DFSVisitor, 
           typename VertexIndexMap>
  void
  tsin_depth_first_visit
    (const DistributedGraph& g,
     typename graph_traits<DistributedGraph>::vertex_descriptor s,
     DFSVisitor vis,
     VertexIndexMap index_map)
  {
    typedef typename graph_traits<DistributedGraph>::vertex_descriptor
      vertex_descriptor;

    std::vector<default_color_type> colors(num_vertices(g));
    std::vector<vertex_descriptor> parent(num_vertices(g));
    std::vector<vertex_descriptor> explore(num_vertices(g));
    tsin_depth_first_visit
      (g, s,
       vis,
       make_iterator_property_map(colors.begin(), index_map),
       make_iterator_property_map(parent.begin(), index_map),
       make_iterator_property_map(explore.begin(), index_map),
       index_map);
  }

  template<typename DistributedGraph, typename DFSVisitor, 
           typename VertexIndexMap>
  void
  tsin_depth_first_visit
    (const DistributedGraph& g,
     typename graph_traits<DistributedGraph>::vertex_descriptor s,
     DFSVisitor vis)
  {
    tsin_depth_first_visit(g, s, vis, get(vertex_index, g));
  }
} // end namespace distributed

using distributed::tsin_depth_first_visit;

} // end namespace graph

template<typename DistributedGraph, typename DFSVisitor>
void
depth_first_visit
  (const DistributedGraph& g,
   typename graph_traits<DistributedGraph>::vertex_descriptor s,
   DFSVisitor vis)
{
  graph::tsin_depth_first_visit(g, s, vis, get(vertex_index, g));
}

} // end namespace boost

#endif // BOOST_GRAPH_DISTRIBUTED_DFS_HPP

/* depth_first_search.hpp
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
*/