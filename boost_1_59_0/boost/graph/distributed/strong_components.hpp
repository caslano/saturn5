// Copyright (C) 2004-2008 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Nick Edmonds
//           Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_DISTRIBUTED_SCC_HPP
#define BOOST_GRAPH_DISTRIBUTED_SCC_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

// #define PBGL_SCC_DEBUG

#include <boost/assert.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/property_map/parallel/distributed_property_map.hpp>
#include <boost/property_map/parallel/caching_property_map.hpp>
#include <boost/graph/parallel/algorithm.hpp>
#include <boost/graph/parallel/process_group.hpp>
#include <boost/graph/distributed/queue.hpp>
#include <boost/graph/distributed/filtered_graph.hpp>
#include <boost/pending/indirect_cmp.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/overloading.hpp>
#include <boost/graph/distributed/concepts.hpp>
#include <boost/graph/distributed/local_subgraph.hpp>
#include <boost/graph/parallel/properties.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/random.hpp>
#include <boost/graph/distributed/reverse_graph.hpp>
#include <boost/optional.hpp>
#include <boost/graph/distributed/detail/filtered_queue.hpp>
#include <boost/graph/distributed/adjacency_list.hpp>
#ifdef PBGL_SCC_DEBUG
  #include <iostream>
  #include <cstdlib>
  #include <iomanip>
  #include <sys/time.h>
  #include <boost/graph/distributed/graphviz.hpp> // for ostringstream
#endif
#include <vector>
#include <map>
#include <boost/graph/parallel/container_traits.hpp>

#ifdef PBGL_SCC_DEBUG
#  include <boost/graph/accounting.hpp>
#endif /* PBGL_SCC_DEBUG */

// If your graph is likely to have large numbers of small strongly connected
// components then running the sequential SCC algorithm on the local subgraph
// and filtering components with no remote edges may increase performance
// #define FILTER_LOCAL_COMPONENTS

namespace boost { namespace graph { namespace distributed { namespace detail {

template<typename vertex_descriptor>
struct v_sets{
  std::vector<vertex_descriptor> pred, succ, intersect, ps_union;
};

/* Serialize vertex set */
template<typename Graph>
void
marshal_set( std::vector<std::vector<typename graph_traits<Graph>::vertex_descriptor> > in,
             std::vector<typename graph_traits<Graph>::vertex_descriptor>& out )
{
  for( std::size_t i = 0; i < in.size(); ++i ) {
    out.insert( out.end(), graph_traits<Graph>::null_vertex() );
    out.insert( out.end(), in[i].begin(), in[i].end() );
  }
}

/* Un-serialize vertex set */
template<typename Graph>
void
unmarshal_set( std::vector<typename graph_traits<Graph>::vertex_descriptor> in,
               std::vector<std::vector<typename graph_traits<Graph>::vertex_descriptor> >& out )
{
  typedef typename graph_traits<Graph>::vertex_descriptor vertex_descriptor;

  while( !in.empty() ) {
    typename std::vector<vertex_descriptor>::iterator end 
      = std::find( in.begin(), in.end(), graph_traits<Graph>::null_vertex() );

    if( end == in.begin() )
      in.erase( in.begin() );
    else {
      out.push_back(std::vector<vertex_descriptor>());
      out[out.size() - 1].insert( out[out.size() - 1].end(), in.begin(), end );
      in.erase( in.begin(), end );
    }
  }
}

/* Determine if vertex is in subset */
template <typename Set>
struct in_subset {
  in_subset() : m_s(0) { }
  in_subset(const Set& s) : m_s(&s) { }

  template <typename Elt>
  bool operator()(const Elt& x) const {
    return ((*m_s).find(x) != (*m_s).end());
  }

private:
  const Set* m_s;
};

template<typename T>
struct vertex_identity_property_map
  : public boost::put_get_helper<T, vertex_identity_property_map<T> >
{
  typedef T key_type;
  typedef T value_type;
  typedef T reference;
  typedef boost::readable_property_map_tag category;

  inline value_type operator[](const key_type& v) const { return v; }
  inline void clear() { }
};

template <typename T>
inline void synchronize( vertex_identity_property_map<T> & ) { }

/* BFS visitor for SCC */
template<typename Graph, typename SourceMap>
struct scc_discovery_visitor : bfs_visitor<>
{
  scc_discovery_visitor(SourceMap& sourceM)
    : sourceM(sourceM) {}

  template<typename Edge>
  void tree_edge(Edge e, const Graph& g)
  {
    put(sourceM, target(e,g), get(sourceM, source(e,g)));
  }

 private:
  SourceMap& sourceM;
};

} } } } /* End namespace boost::graph::distributed::detail */

namespace boost { namespace graph { namespace distributed {
    enum fhp_message_tags { fhp_edges_size_msg, fhp_add_edges_msg, fhp_pred_size_msg, 
                            fhp_pred_msg, fhp_succ_size_msg, fhp_succ_msg };

    template<typename Graph, typename ReverseGraph,
             typename VertexComponentMap, typename IsoMapFR, typename IsoMapRF,
             typename VertexIndexMap>
    void
    fleischer_hendrickson_pinar_strong_components(const Graph& g,
                                                  VertexComponentMap c,
                                                  const ReverseGraph& gr,
                                                  IsoMapFR fr, IsoMapRF rf,
                                                  VertexIndexMap vertex_index_map)
    {
      typedef typename graph_traits<Graph>::vertex_iterator vertex_iterator;
      typedef typename graph_traits<Graph>::vertex_descriptor vertex_descriptor;
      typedef typename graph_traits<ReverseGraph>::vertex_iterator rev_vertex_iterator;
      typedef typename graph_traits<ReverseGraph>::vertex_descriptor rev_vertex_descriptor;
      typedef typename boost::graph::parallel::process_group_type<Graph>::type
        process_group_type;
      typedef typename process_group_type::process_id_type process_id_type;
      typedef iterator_property_map<typename std::vector<vertex_descriptor>::iterator,
                                    VertexIndexMap> ParentMap;
      typedef iterator_property_map<typename std::vector<default_color_type>::iterator,
                                    VertexIndexMap> ColorMap;
      typedef iterator_property_map<typename std::vector<vertex_descriptor>::iterator,
                                    VertexIndexMap> Rev_ParentMap;
      typedef std::vector<std::pair<vertex_descriptor, vertex_descriptor> > VertexPairVec;

      typedef typename property_map<Graph, vertex_owner_t>::const_type
        OwnerMap;

      OwnerMap owner = get(vertex_owner, g);

      using boost::graph::parallel::process_group;
      process_group_type pg = process_group(g);
      process_id_type id = process_id(pg);
      int num_procs = num_processes(pg);
      int n = 0;

      int my_n = num_vertices(g);
      all_reduce(pg, &my_n, &my_n+1, &n, std::plus<int>());

      //
      // Initialization
      //

#ifdef PBGL_SCC_DEBUG
  accounting::time_type start = accounting::get_time();
#endif

      vertex_iterator vstart, vend;
      rev_vertex_iterator rev_vstart, rev_vend;
      std::vector<std::vector<vertex_descriptor> > vertex_sets, new_vertex_sets;

      vertex_sets.push_back(std::vector<vertex_descriptor>());

      // Remove vertices that do not have at least one in edge and one out edge
      new_vertex_sets.push_back(std::vector<vertex_descriptor>());
      for( boost::tie(vstart, vend) = vertices(g); vstart != vend; vstart++ )
        if( out_degree( get(fr, *vstart), gr) > 0 && out_degree(*vstart, g) > 0 )
          new_vertex_sets[0].push_back( *vstart );

      // Perform sequential SCC on local subgraph, filter all components with external
      // edges, mark remaining components and remove them from vertex_sets
#ifdef FILTER_LOCAL_COMPONENTS  
      // This doesn't actually speed up SCC in connected graphs it seems, but it does work
      // and may help in the case where there are lots of small strong components.
      {
        local_subgraph<const Graph> ls(g);
        typedef typename property_map<local_subgraph<const Graph>, vertex_index_t>::type
          local_index_map_type;
        local_index_map_type local_index = get(vertex_index, ls);

        std::vector<int> ls_components_vec(num_vertices(ls));
        typedef iterator_property_map<std::vector<int>::iterator, local_index_map_type>
          ls_components_map_type;
        ls_components_map_type ls_component(ls_components_vec.begin(), local_index);
        int num_comp = boost::strong_components(ls, ls_component);

        // Create map of components
        std::map<int, std::vector<vertex_descriptor> > local_comp_map;
        typedef typename graph_traits<local_subgraph<const Graph> >::vertex_iterator ls_vertex_iterator;
        ls_vertex_iterator vstart, vend;
        for( boost::tie(vstart,vend) = vertices(ls); vstart != vend; vstart++ )
          local_comp_map[get(ls_component, *vstart)].push_back( *vstart );

        // Filter components that have no non-local edges
        typedef typename graph_traits<Graph>::adjacency_iterator adjacency_iterator;
        typedef typename graph_traits<ReverseGraph>::adjacency_iterator rev_adjacency_iterator;
        adjacency_iterator abegin, aend;
        rev_adjacency_iterator rev_abegin, rev_aend;
        for( std::size_t i = 0; i < num_comp; ++i ) {
          bool local = true;
          for( std::size_t j = 0; j < local_comp_map[i].size(); j++ ) {
            for( boost::tie(abegin,aend) = adjacent_vertices(local_comp_map[i][j], g);
                 abegin != aend; abegin++ )
              if( get(owner, *abegin) != id ) {
                local = false;
                break;
              }

            if( local )
              for( boost::tie(rev_abegin,rev_aend) = adjacent_vertices(get(fr, local_comp_map[i][j]), gr);
                   rev_abegin != rev_aend; rev_abegin++ )
                if( get(owner, *rev_abegin) != id ) {
                  local = false;
                  break;
                }

            if( !local ) break;
          }

          if( local ) // Mark and remove from new_vertex_sets
            for( std::size_t j = 0; j < local_comp_map[i].size(); j++ ) {
              put( c, local_comp_map[i][j], local_comp_map[i][0] );
              typename std::vector<vertex_descriptor>::iterator pos =
                std::find(new_vertex_sets[0].begin(), new_vertex_sets[0].end(), local_comp_map[i][j]);
              if( pos != new_vertex_sets[0].end() )
                new_vertex_sets[0].erase(pos);
            }
        }
      }
#endif // FILTER_LOCAL_COMPONENTS

      all_gather( pg, new_vertex_sets[0].begin(), new_vertex_sets[0].end(), vertex_sets[0] );
      new_vertex_sets.clear();

#ifdef PBGL_SCC_DEBUG
  accounting::time_type end = accounting::get_time();
  if(id == 0)
    std::cerr << "Trim local SCCs time = " << accounting::print_time(end - start) << " seconds.\n";
#endif

      if( vertex_sets[0].empty() ) return;

      //
      // Recursively determine SCCs
      //

#ifdef PBGL_SCC_DEBUG
  int iterations = 0;
#endif

      // Only need to be able to map starting vertices for BFS from now on
      fr.clear();

      do {

#ifdef PBGL_SCC_DEBUG
  if(id == 0) {
    printf("\n\nIteration %d:\n\n", iterations++);

    if( iterations > 1 ) {
      end = accounting::get_time();
      std::cerr << "Running main loop destructors time = " << accounting::print_time(end - start) << " seconds.\n";
    }

    start = accounting::get_time();
  }
#endif

        // Get forward->reverse mappings for BFS start vertices
       for (std::size_t i = 0; i < vertex_sets.size(); ++i)
          get(fr, vertex_sets[i][0]);
        synchronize(fr);

        // Determine local vertices to start BFS from
        std::vector<vertex_descriptor> local_start;
        for( std::size_t i = id; i < vertex_sets.size(); i += num_procs )
          local_start.push_back(vertex_sets[i][0]);

        if( local_start.empty() )
          local_start.push_back(vertex_sets[0][0]);


        // Make filtered graphs
        typedef std::set<vertex_descriptor> VertexSet;
        typedef std::set<rev_vertex_descriptor> Rev_VertexSet;

        VertexSet filter_set_g;
        Rev_VertexSet filter_set_gr;
        typename VertexSet::iterator fs;

        int active_vertices = 0;
        for (std::size_t i = 0; i < vertex_sets.size(); i++)
          active_vertices += vertex_sets[i].size();

        // This is a completely random bound
        if ( active_vertices < 0.05*n ) {
          // TODO: This set insertion is ridiculously inefficient, make it an in-place-merge?
          for (std::size_t i = 0; i < vertex_sets.size(); i++)
            filter_set_g.insert(vertex_sets[i].begin(), vertex_sets[i].end());

          for (fs = filter_set_g.begin(); fs != filter_set_g.end(); ++fs )
            filter_set_gr.insert(get(fr, *fs));
        }

        filtered_graph<const Graph, keep_all, detail::in_subset<VertexSet> >
          fg(g, keep_all(), detail::in_subset<VertexSet>(filter_set_g));

        filtered_graph<const ReverseGraph, keep_all, detail::in_subset<VertexSet> >
          fgr(gr, keep_all(), detail::in_subset<VertexSet>(filter_set_gr));

        // Add additional starting vertices to BFS queue
        typedef filtered_queue<queue<vertex_descriptor>, boost::detail::has_not_been_seen<VertexIndexMap> >
          local_queue_type;
        typedef boost::graph::distributed::distributed_queue<process_group_type, OwnerMap, local_queue_type>
          queue_t;

        typedef typename property_map<ReverseGraph, vertex_owner_t>::const_type
          RevOwnerMap;

        typedef filtered_queue<queue<rev_vertex_descriptor>, boost::detail::has_not_been_seen<VertexIndexMap> >
          rev_local_queue_type;
        typedef boost::graph::distributed::distributed_queue<process_group_type, RevOwnerMap, rev_local_queue_type>
          rev_queue_t;

        queue_t Q(process_group(g),
                  owner,
                  make_filtered_queue(queue<vertex_descriptor>(),
                                      boost::detail::has_not_been_seen<VertexIndexMap>
                                      (num_vertices(g), vertex_index_map)),
                  false);

        rev_queue_t Qr(process_group(gr),
                       get(vertex_owner, gr),
                       make_filtered_queue(queue<rev_vertex_descriptor>(),
                                           boost::detail::has_not_been_seen<VertexIndexMap>
                                           (num_vertices(gr), vertex_index_map)),
                       false);

        for( std::size_t i = 1; i < local_start.size(); ++i ) {
          Q.push(local_start[i]);
          Qr.push(get(fr, local_start[i]));
        }

#ifdef PBGL_SCC_DEBUG
  end = accounting::get_time();
  if(id == 0)
    std::cerr << "  Initialize BFS time = " << accounting::print_time(end - start) << " seconds.\n";
  start = accounting::get_time();
#endif

#ifdef PBGL_SCC_DEBUG
  accounting::time_type start2 = accounting::get_time();
#endif

        // Forward BFS
        std::vector<default_color_type> color_map_s(num_vertices(g));
        ColorMap color_map(color_map_s.begin(), vertex_index_map);
        std::vector<vertex_descriptor> succ_map_s(num_vertices(g), graph_traits<Graph>::null_vertex());
        ParentMap succ_map(succ_map_s.begin(), vertex_index_map);

        for( std::size_t i = 0; i < vertex_sets.size(); ++i )
          put(succ_map, vertex_sets[i][0], vertex_sets[i][0]);

#ifdef PBGL_SCC_DEBUG
  accounting::time_type end2 = accounting::get_time();
  if(id == 0)
    std::cerr << "  Initialize forward BFS time = " << accounting::print_time(end2 - start2) << " seconds.\n";
#endif

        if (active_vertices < 0.05*n)
          breadth_first_search(fg, local_start[0], Q,
                               detail::scc_discovery_visitor<filtered_graph<const Graph, keep_all,
                                                                            detail::in_subset<VertexSet> >, ParentMap>
                               (succ_map),
                               color_map);
        else
          breadth_first_search(g, local_start[0], Q,
                               detail::scc_discovery_visitor<const Graph, ParentMap>(succ_map),
                               color_map);

#ifdef PBGL_SCC_DEBUG
  start2 = accounting::get_time();
#endif

        // Reverse BFS
        color_map.clear(); // reuse color map since g and gr have same vertex index
        std::vector<vertex_descriptor> pred_map_s(num_vertices(gr), graph_traits<Graph>::null_vertex());
        Rev_ParentMap pred_map(pred_map_s.begin(), vertex_index_map);

        for( std::size_t i = 0; i < vertex_sets.size(); ++i )
          put(pred_map, get(fr, vertex_sets[i][0]), vertex_sets[i][0]);

#ifdef PBGL_SCC_DEBUG
  end2 = accounting::get_time();
  if(id == 0)
    std::cerr << "  Initialize reverse BFS time = " << accounting::print_time(end2 - start2) << " seconds.\n";
#endif

        if (active_vertices < 0.05*n)
          breadth_first_search(fgr, get(fr, local_start[0]),
                               Qr,
                               detail::scc_discovery_visitor<filtered_graph<const ReverseGraph, keep_all,
                                                                            detail::in_subset<Rev_VertexSet> >, Rev_ParentMap>
                               (pred_map),
                               color_map);
        else
          breadth_first_search(gr, get(fr, local_start[0]),
                               Qr,
                               detail::scc_discovery_visitor<const ReverseGraph, Rev_ParentMap>(pred_map),
                               color_map);

#ifdef PBGL_SCC_DEBUG
  end = accounting::get_time();
  if(id == 0)
    std::cerr << "  Perform forward and reverse BFS time = " << accounting::print_time(end - start) << " seconds.\n";
  start = accounting::get_time();
#endif

        // Send predecessors and successors discovered by this proc to the proc responsible for
        // this BFS tree
        typedef struct detail::v_sets<vertex_descriptor> Vsets;
        std::map<vertex_descriptor, Vsets> set_map;

        std::map<vertex_descriptor, int> dest_map;

        std::vector<VertexPairVec> successors(num_procs);
        std::vector<VertexPairVec> predecessors(num_procs);

        // Calculate destinations for messages
        for (std::size_t i = 0; i < vertex_sets.size(); ++i)
          dest_map[vertex_sets[i][0]] = i % num_procs;

        for( boost::tie(vstart, vend) = vertices(g); vstart != vend; vstart++ ) {
          vertex_descriptor v = get(succ_map, *vstart);
          if( v != graph_traits<Graph>::null_vertex() ) {
            if (dest_map[v] == id)
              set_map[v].succ.push_back(*vstart);
            else
              successors[dest_map[v]].push_back( std::make_pair(v, *vstart) );
          }
        }

        for( boost::tie(rev_vstart, rev_vend) = vertices(gr); rev_vstart != rev_vend; rev_vstart++ ) {
          vertex_descriptor v = get(pred_map, *rev_vstart);
          if( v != graph_traits<Graph>::null_vertex() ) {
            if (dest_map[v] == id)
              set_map[v].pred.push_back(get(rf, *rev_vstart));
            else
              predecessors[dest_map[v]].push_back( std::make_pair(v, get(rf, *rev_vstart)) );
          }
        }

        // Send predecessor and successor messages
        for (process_id_type i = 0; i < num_procs; ++i) {
          if (!successors[i].empty()) {
            send(pg, i, fhp_succ_size_msg, successors[i].size());
            send(pg, i, fhp_succ_msg, &successors[i][0], successors[i].size());
          }
          if (!predecessors[i].empty()) {
            send(pg, i, fhp_pred_size_msg, predecessors[i].size());
            send(pg, i, fhp_pred_msg, &predecessors[i][0], predecessors[i].size());
          }
        }
        synchronize(pg);

        // Receive predecessor and successor messages and handle them
        while (optional<std::pair<process_id_type, int> > m = probe(pg)) {
          BOOST_ASSERT(m->second == fhp_succ_size_msg || m->second == fhp_pred_size_msg);
          std::size_t num_requests;
          receive(pg, m->first, m->second, num_requests);
          VertexPairVec requests(num_requests);
          if (m->second == fhp_succ_size_msg) {
            receive(pg, m->first, fhp_succ_msg, &requests[0],
                    num_requests);

            std::map<vertex_descriptor, int> added;
            for (std::size_t i = 0; i < requests.size(); ++i) {
              set_map[requests[i].first].succ.push_back(requests[i].second);
              added[requests[i].first]++;
            }

            // If order of vertex traversal in vertices() is std::less<vertex_descriptor>,
            // then the successor sets will be in order
            for (std::size_t i = 0; i < local_start.size(); ++i)
              if (added[local_start[i]] > 0)
                  std::inplace_merge(set_map[local_start[i]].succ.begin(),
                                     set_map[local_start[i]].succ.end() - added[local_start[i]],
                                     set_map[local_start[i]].succ.end(),
                                     std::less<vertex_descriptor>());

          } else {
            receive(pg, m->first, fhp_pred_msg, &requests[0],
                    num_requests);

            std::map<vertex_descriptor, int> added;
            for (std::size_t i = 0; i < requests.size(); ++i) {
              set_map[requests[i].first].pred.push_back(requests[i].second);
              added[requests[i].first]++;
            }

            if (boost::is_same<detail::vertex_identity_property_map<vertex_descriptor>, IsoMapRF>::value)
              for (std::size_t i = 0; i < local_start.size(); ++i)
                if (added[local_start[i]] > 0)
                  std::inplace_merge(set_map[local_start[i]].pred.begin(),
                                     set_map[local_start[i]].pred.end() - added[local_start[i]],
                                     set_map[local_start[i]].pred.end(),
                                     std::less<vertex_descriptor>());
          }
        }

#ifdef PBGL_SCC_DEBUG
  end = accounting::get_time();
  if(id == 0)
    std::cerr << "  All gather successors and predecessors time = " << accounting::print_time(end - start) << " seconds.\n";
  start = accounting::get_time();
#endif

        //
        // Filter predecessor and successor sets and perform set arithmetic
        //
        new_vertex_sets.clear();

        if( std::size_t(id) < vertex_sets.size() ) { //If this proc has one or more unique starting points

          for( std::size_t i = 0; i < local_start.size(); ++i ) {

            vertex_descriptor v = local_start[i];

            // Replace this sort with an in-place merges during receive step if possible
            if (!boost::is_same<detail::vertex_identity_property_map<vertex_descriptor>, IsoMapRF>::value) 
              std::sort(set_map[v].pred.begin(), set_map[v].pred.end(), std::less<vertex_descriptor>());

            // Limit predecessor and successor sets to members of the original set
            std::vector<vertex_descriptor> temp;

            std::set_intersection( vertex_sets[id + i*num_procs].begin(), vertex_sets[id + i*num_procs].end(),
                                   set_map[v].pred.begin(), set_map[v].pred.end(),
                                   back_inserter(temp),
                                   std::less<vertex_descriptor>());
            set_map[v].pred.clear();
            std::swap(set_map[v].pred, temp);

            std::set_intersection( vertex_sets[id + i*num_procs].begin(), vertex_sets[id + i*num_procs].end(),
                                   set_map[v].succ.begin(), set_map[v].succ.end(),
                                   back_inserter(temp),
                                   std::less<vertex_descriptor>());
            set_map[v].succ.clear();
            std::swap(set_map[v].succ, temp);

            // Intersection(pred, succ)
            std::set_intersection(set_map[v].pred.begin(), set_map[v].pred.end(),
                                    set_map[v].succ.begin(), set_map[v].succ.end(),
                                    back_inserter(set_map[v].intersect),
                                    std::less<vertex_descriptor>());

            // Union(pred, succ)
            std::set_union(set_map[v].pred.begin(), set_map[v].pred.end(),
                           set_map[v].succ.begin(), set_map[v].succ.end(),
                           back_inserter(set_map[v].ps_union),
                           std::less<vertex_descriptor>());

            new_vertex_sets.push_back(std::vector<vertex_descriptor>());
            // Original set - Union(pred, succ)
            std::set_difference(vertex_sets[id + i*num_procs].begin(), vertex_sets[id + i*num_procs].end(),
                                set_map[v].ps_union.begin(), set_map[v].ps_union.end(),
                                back_inserter(new_vertex_sets[new_vertex_sets.size() - 1]),
                                std::less<vertex_descriptor>());

            set_map[v].ps_union.clear();

            new_vertex_sets.push_back(std::vector<vertex_descriptor>());
            // Pred - Intersect(pred, succ)
            std::set_difference(set_map[v].pred.begin(), set_map[v].pred.end(),
                                set_map[v].intersect.begin(), set_map[v].intersect.end(),
                                back_inserter(new_vertex_sets[new_vertex_sets.size() - 1]),
                                std::less<vertex_descriptor>());

            set_map[v].pred.clear();

            new_vertex_sets.push_back(std::vector<vertex_descriptor>());
            // Succ - Intersect(pred, succ)
            std::set_difference(set_map[v].succ.begin(), set_map[v].succ.end(),
                                set_map[v].intersect.begin(), set_map[v].intersect.end(),
                                back_inserter(new_vertex_sets[new_vertex_sets.size() - 1]),
                                std::less<vertex_descriptor>());

            set_map[v].succ.clear();

            // Label SCC just identified with the 'first' vertex in that SCC
            for( std::size_t j = 0; j < set_map[v].intersect.size(); j++ )
              put(c, set_map[v].intersect[j], set_map[v].intersect[0]);

            set_map[v].intersect.clear();
          }
        }

#ifdef PBGL_SCC_DEBUG
  end = accounting::get_time();
  if(id == 0)
    std::cerr << "  Perform set arithemetic time = " << accounting::print_time(end - start) << " seconds.\n";
  start = accounting::get_time();
#endif

        // Remove sets of size 1 from new_vertex_sets
        typename std::vector<std::vector<vertex_descriptor> >::iterator vviter;
        for( vviter = new_vertex_sets.begin(); vviter != new_vertex_sets.end(); /*in loop*/ )
          if( (*vviter).size() < 2 )
            vviter = new_vertex_sets.erase( vviter );
          else
            vviter++;

        // All gather new sets and recur (gotta marshal and unmarshal sets first)
        vertex_sets.clear();
        std::vector<vertex_descriptor> serial_sets, all_serial_sets;
        detail::marshal_set<Graph>( new_vertex_sets, serial_sets );
        all_gather( pg, serial_sets.begin(), serial_sets.end(), all_serial_sets );
        detail::unmarshal_set<Graph>( all_serial_sets, vertex_sets );

#ifdef PBGL_SCC_DEBUG
  end = accounting::get_time();
  if(id == 0) {
    std::cerr << "  Serialize and gather new vertex sets time = " << accounting::print_time(end - start) << " seconds.\n\n\n";

    printf("Vertex sets: %d\n", (int)vertex_sets.size() );
    for( std::size_t i = 0; i < vertex_sets.size(); ++i )
      printf("  %d: %d\n", i, (int)vertex_sets[i].size() );
  }
  start = accounting::get_time();
#endif

        // HACK!?!  --  This would be more properly implemented as a topological sort
        // Remove vertices without an edge to another vertex in the set and an edge from another
        // vertex in the set
       typedef typename graph_traits<Graph>::out_edge_iterator out_edge_iterator;
       out_edge_iterator estart, eend;
       typedef typename graph_traits<ReverseGraph>::out_edge_iterator r_out_edge_iterator;
       r_out_edge_iterator restart, reend;
       for (std::size_t i = 0; i < vertex_sets.size(); ++i) {
         std::vector<vertex_descriptor> new_set;
         for (std::size_t j = 0; j < vertex_sets[i].size(); ++j) {
           vertex_descriptor v = vertex_sets[i][j];
           if (get(owner, v) == id) {
             boost::tie(estart, eend) = out_edges(v, g);
             while (estart != eend && find(vertex_sets[i].begin(), vertex_sets[i].end(),
                                           target(*estart,g)) == vertex_sets[i].end()) estart++;
             if (estart != eend) {
               boost::tie(restart, reend) = out_edges(get(fr, v), gr);
               while (restart != reend && find(vertex_sets[i].begin(), vertex_sets[i].end(),
                                               get(rf, target(*restart,gr))) == vertex_sets[i].end()) restart++;
               if (restart != reend)
                 new_set.push_back(v);
             }
           }
         }
         vertex_sets[i].clear();
         all_gather(pg, new_set.begin(), new_set.end(), vertex_sets[i]);
         std::sort(vertex_sets[i].begin(), vertex_sets[i].end(), std::less<vertex_descriptor>());
       }
#ifdef PBGL_SCC_DEBUG
  end = accounting::get_time();
  if(id == 0)
    std::cerr << "  Trim vertex sets time = " << accounting::print_time(end - start) << " seconds.\n\n\n";
  start = accounting::get_time();
#endif

      } while ( !vertex_sets.empty() );


      // Label vertices not in a SCC as their own SCC
      for( boost::tie(vstart, vend) = vertices(g); vstart != vend; vstart++ )
        if( get(c, *vstart) == graph_traits<Graph>::null_vertex() )
          put(c, *vstart, *vstart);

      synchronize(c);
    }

    template<typename Graph, typename ReverseGraph, typename IsoMap>
    void
    build_reverse_graph( const Graph& g, ReverseGraph& gr, IsoMap& fr, IsoMap& rf )
    {
      typedef typename graph_traits<Graph>::vertex_iterator vertex_iterator;
      typedef typename graph_traits<Graph>::vertex_descriptor vertex_descriptor;
      typedef typename graph_traits<Graph>::out_edge_iterator out_edge_iterator;
      typedef typename boost::graph::parallel::process_group_type<Graph>::type process_group_type;
      typedef typename process_group_type::process_id_type process_id_type;
      typedef std::vector<std::pair<vertex_descriptor, vertex_descriptor> > VertexPairVec;

      typename property_map<Graph, vertex_owner_t>::const_type
        owner = get(vertex_owner, g);

      process_group_type pg = process_group(g);
      process_id_type id = process_id(pg);

      int n;
      vertex_iterator vstart, vend;
      int num_procs = num_processes(pg);

      vertex_descriptor v;
      out_edge_iterator oestart, oeend;
      for( boost::tie(vstart, vend) = vertices(g); vstart != vend; vstart++ )
        {
          v = add_vertex(gr);
          put(fr, *vstart, v);
          put(rf, v, *vstart);
        }

      gr.distribution() = g.distribution();

      int my_n = num_vertices(g);
      all_reduce(pg, &my_n, &my_n+1, &n, std::plus<int>());

      for (int i = 0; i < n; ++i)
        get(fr, vertex(i,g));
      synchronize(fr);

      // Add edges to gr
      std::vector<std::pair<vertex_descriptor, vertex_descriptor> > new_edges;
      for( boost::tie(vstart, vend) = vertices(g); vstart != vend; vstart++ )
        for( boost::tie(oestart, oeend) = out_edges(*vstart, g); oestart != oeend; oestart++ )
          new_edges.push_back( std::make_pair(get(fr, target(*oestart,g)), get(fr, source(*oestart, g))) );

      std::vector<VertexPairVec> edge_requests(num_procs);

      typename std::vector<std::pair<vertex_descriptor, vertex_descriptor> >::iterator iter;
      for( iter = new_edges.begin(); iter != new_edges.end(); iter++ ) {
        std::pair<vertex_descriptor, vertex_descriptor> p1 = *iter;
        if( get(owner,  p1.first ) == id )
          add_edge( p1.first, p1.second, gr );
        else
          edge_requests[get(owner, p1.first)].push_back(p1);
      }
      new_edges.clear();

      // Send edge addition requests
      for (process_id_type p = 0; p < num_procs; ++p) {
        if (!edge_requests[p].empty()) {
          VertexPairVec reqs(edge_requests[p].begin(), edge_requests[p].end());
          send(pg, p, fhp_edges_size_msg, reqs.size());
          send(pg, p, fhp_add_edges_msg, &reqs[0], reqs.size());
        }
      }
      synchronize(pg);

      // Receive edge addition requests and handle them
      while (optional<std::pair<process_id_type, int> > m = probe(pg)) {
        BOOST_ASSERT(m->second == fhp_edges_size_msg);
        std::size_t num_requests;
        receive(pg, m->first, m->second, num_requests);
        VertexPairVec requests(num_requests);
        receive(pg, m->first, fhp_add_edges_msg, &requests[0],
                num_requests);
        for( std::size_t i = 0; i < requests.size(); ++i )
          add_edge( requests[i].first, requests[i].second, gr );
      }
          synchronize(gr);
    }

    template<typename Graph, typename VertexComponentMap, typename ComponentMap>
    typename property_traits<ComponentMap>::value_type
    number_components(const Graph& g, VertexComponentMap r, ComponentMap c)
    {
      typedef typename boost::graph::parallel::process_group_type<Graph>::type process_group_type;
      typedef typename graph_traits<Graph>::vertex_iterator vertex_iterator;
      typedef typename graph_traits<Graph>::vertex_descriptor vertex_descriptor;
      typedef typename property_traits<ComponentMap>::value_type ComponentMapType;
      std::vector<vertex_descriptor> my_roots, all_roots;
      vertex_iterator vstart, vend;

      for( boost::tie(vstart, vend) = vertices(g); vstart != vend; vstart++ )
        if( find( my_roots.begin(), my_roots.end(), get(r, *vstart) ) == my_roots.end() )
          my_roots.push_back( get(r, *vstart) );

      all_gather( process_group(g), my_roots.begin(), my_roots.end(), all_roots );

      /* Number components */
      std::map<vertex_descriptor, ComponentMapType> comp_numbers;
      ComponentMapType c_num = 0;

      // Compute component numbers
      for (std::size_t i = 0; i < all_roots.size(); ++i )
        if ( comp_numbers.count(all_roots[i]) == 0 )
          comp_numbers[all_roots[i]] = c_num++;

      // Broadcast component numbers
      for( boost::tie(vstart, vend) = vertices(g); vstart != vend; vstart++ )
        put( c, *vstart, comp_numbers[get(r,*vstart)] );

      // Broadcast number of components
      if (process_id(process_group(g)) == 0) {
        typedef typename process_group_type::process_size_type
          process_size_type;
        for (process_size_type dest = 1, n = num_processes(process_group(g));
              dest != n; ++dest)
          send(process_group(g), dest, 0, c_num);
      }

      synchronize(process_group(g));

      if (process_id(process_group(g)) != 0) receive(process_group(g), 0, 0, c_num);

      synchronize(c);
      return c_num;
    }


    template<typename Graph, typename ComponentMap, typename VertexComponentMap,
             typename VertexIndexMap>
    typename property_traits<ComponentMap>::value_type
    fleischer_hendrickson_pinar_strong_components_impl
      (const Graph& g,
       ComponentMap c,
       VertexComponentMap r,
       VertexIndexMap vertex_index_map,
       incidence_graph_tag)
    {
      typedef typename graph_traits<Graph>::vertex_descriptor vertex_descriptor;
      typedef iterator_property_map<typename std::vector<vertex_descriptor>::iterator,
                                    VertexIndexMap> IsoMap;
      typename boost::graph::parallel::process_group_type<Graph>::type pg = process_group(g);

#ifdef PBGL_SCC_DEBUG
  accounting::time_type start = accounting::get_time();
#endif

      typedef adjacency_list<listS,
                             distributedS<typename boost::graph::parallel::process_group_type<Graph>::type, vecS>,
                             directedS > ReverseGraph;

      ReverseGraph gr(0, pg);
      std::vector<vertex_descriptor> fr_s(num_vertices(g));
      std::vector<vertex_descriptor> rf_s(num_vertices(g));
      IsoMap fr(fr_s.begin(), vertex_index_map);  // fr = forward->reverse
      IsoMap rf(rf_s.begin(), vertex_index_map); // rf = reverse->forward

      build_reverse_graph(g, gr, fr, rf);

#ifdef PBGL_SCC_DEBUG
  accounting::time_type end = accounting::get_time();
  if(process_id(process_group(g)) == 0)
    std::cerr << "Reverse graph initialization time = " << accounting::print_time(end - start) << " seconds.\n";
#endif

  fleischer_hendrickson_pinar_strong_components(g, r, gr, fr, rf, 
                                                vertex_index_map);

      typename property_traits<ComponentMap>::value_type c_num = number_components(g, r, c);

      return c_num;
    }

    template<typename Graph, typename ComponentMap, typename VertexComponentMap,
             typename VertexIndexMap>
    typename property_traits<ComponentMap>::value_type
    fleischer_hendrickson_pinar_strong_components_impl
      (const Graph& g,
       ComponentMap c,
       VertexComponentMap r,
       VertexIndexMap vertex_index_map,
       bidirectional_graph_tag)
    {
      typedef typename graph_traits<Graph>::vertex_descriptor vertex_descriptor;

      reverse_graph<Graph> gr(g);
      detail::vertex_identity_property_map<vertex_descriptor> fr, rf;

      fleischer_hendrickson_pinar_strong_components(g, r, gr, fr, rf, 
                                                    vertex_index_map);

      typename property_traits<ComponentMap>::value_type c_num
        = number_components(g, r, c);

      return c_num;
    }

    template<typename Graph, typename ComponentMap, typename VertexIndexMap>
    inline typename property_traits<ComponentMap>::value_type
    fleischer_hendrickson_pinar_strong_components
      (const Graph& g,
       ComponentMap c,
       VertexIndexMap vertex_index_map)
    {
      typedef typename graph_traits<Graph>::vertex_descriptor
        vertex_descriptor;
      typedef iterator_property_map<typename std::vector<vertex_descriptor>::iterator,
                                    VertexIndexMap> VertexComponentMap;
      typename boost::graph::parallel::process_group_type<Graph>::type pg 
        = process_group(g);

      if (num_processes(pg) == 1) {
        local_subgraph<const Graph> ls(g);
        return boost::strong_components(ls, c);
      }

      // Create a VertexComponentMap for intermediate labeling of SCCs
      std::vector<vertex_descriptor> r_s(num_vertices(g), graph_traits<Graph>::null_vertex());
      VertexComponentMap r(r_s.begin(), vertex_index_map);

      return fleischer_hendrickson_pinar_strong_components_impl
               (g, c, r, vertex_index_map,
                typename graph_traits<Graph>::traversal_category());
    }

    template<typename Graph, typename ComponentMap>
    inline typename property_traits<ComponentMap>::value_type
    fleischer_hendrickson_pinar_strong_components(const Graph& g,
                                                  ComponentMap c)
    {
      return fleischer_hendrickson_pinar_strong_components(g, c, get(vertex_index, g));
    }

}  // end namespace distributed

using distributed::fleischer_hendrickson_pinar_strong_components;

} // end namespace graph

template<class Graph, class ComponentMap, class P, class T, class R>
inline typename property_traits<ComponentMap>::value_type
strong_components
 (const Graph& g, ComponentMap comp,
  const bgl_named_params<P, T, R>&
  BOOST_GRAPH_ENABLE_IF_MODELS_PARM(Graph, distributed_graph_tag))
{
  return graph::fleischer_hendrickson_pinar_strong_components(g, comp);
}

template<class Graph, class ComponentMap>
inline typename property_traits<ComponentMap>::value_type
strong_components
 (const Graph& g, ComponentMap comp
  BOOST_GRAPH_ENABLE_IF_MODELS_PARM(Graph, distributed_graph_tag))
{
  return graph::fleischer_hendrickson_pinar_strong_components(g, comp);
}

} /* end namespace boost */

#endif // BOOST_GRAPH_DISTRIBUTED_SCC_HPP

/* strong_components.hpp
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
*/