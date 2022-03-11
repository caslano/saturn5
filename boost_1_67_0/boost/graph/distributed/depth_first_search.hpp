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