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