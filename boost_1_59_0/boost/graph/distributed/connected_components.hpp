// Copyright (C) 2004-2006 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Nick Edmonds
//           Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_PARALLEL_CC_HPP
#define BOOST_GRAPH_PARALLEL_CC_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <boost/detail/is_sorted.hpp>
#include <boost/assert.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/property_map/parallel/caching_property_map.hpp>
#include <boost/graph/parallel/algorithm.hpp>
#include <boost/pending/indirect_cmp.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/overloading.hpp>
#include <boost/graph/distributed/concepts.hpp>
#include <boost/graph/parallel/properties.hpp>
#include <boost/graph/distributed/local_subgraph.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/parallel/process_group.hpp>
#include <boost/optional.hpp>
#include <functional>
#include <algorithm>
#include <vector>
#include <list>
#include <boost/graph/parallel/container_traits.hpp>
#include <boost/graph/iteration_macros.hpp>

#define PBGL_IN_PLACE_MERGE /* In place merge instead of sorting */
//#define PBGL_SORT_ASSERT    /* Assert sorted for in place merge */

/* Explicit sychronization in pointer doubling step? */
#define PBGL_EXPLICIT_SYNCH
//#define PBGL_CONSTRUCT_METAGRAPH
#ifdef PBGL_CONSTRUCT_METAGRAPH
#  define MAX_VERTICES_IN_METAGRAPH 10000
#endif

namespace boost { namespace graph { namespace distributed {
  namespace cc_detail {
    enum connected_components_message { 
      edges_msg, req_parents_msg, parents_msg, root_adj_msg
    };

    template <typename Vertex>
    struct metaVertex {
      metaVertex() {}
      metaVertex(const Vertex& v) : name(v) {}

      template<typename Archiver>
      void serialize(Archiver& ar, const unsigned int /*version*/)
      {
        ar & name;
      }

      Vertex name;
    };

#ifdef PBGL_CONSTRUCT_METAGRAPH
    // Build meta-graph on result of local connected components
    template <typename Graph, typename ParentMap, typename RootIterator,
              typename AdjacencyMap>
    void
    build_local_metagraph(const Graph& g, ParentMap p, RootIterator r,
                          RootIterator r_end, AdjacencyMap& adj)
    {
      // TODO: Static assert that AdjacencyMap::value_type is std::vector<vertex_descriptor>

      typedef typename boost::graph::parallel::process_group_type<Graph>::type
        process_group_type;
      typedef typename process_group_type::process_id_type process_id_type;

      typedef typename graph_traits<Graph>::vertex_descriptor vertex_descriptor;

      BOOST_STATIC_ASSERT((is_same<typename AdjacencyMap::mapped_type,
                                     std::vector<vertex_descriptor> >::value));

      using boost::graph::parallel::process_group;

      process_group_type pg = process_group(g);
      process_id_type id = process_id(pg);
      
      if (id != 0) {

        // Send component roots and their associated edges to P0
        for ( ; r != r_end; ++r ) {
          std::vector<vertex_descriptor> adjs(1, *r); // Root
          adjs.reserve(adjs.size() + adj[*r].size());
          for (typename std::vector<vertex_descriptor>::iterator iter = adj[*r].begin();
               iter != adj[*r].end(); ++iter)
            adjs.push_back(get(p, *iter)); // Adjacencies

          send(pg, 0, root_adj_msg, adjs); 
        }
      }
      
      synchronize(pg);

      if (id == 0) {
        typedef metaVertex<vertex_descriptor> VertexProperties;

        typedef boost::adjacency_list<vecS, vecS, undirectedS, 
          VertexProperties> metaGraph;
        typedef typename graph_traits<metaGraph>::vertex_descriptor 
          meta_vertex_descriptor;

        std::map<vertex_descriptor, meta_vertex_descriptor> vertex_map;
        std::vector<std::pair<vertex_descriptor, vertex_descriptor> > edges;

        // Receive remote roots and edges
        while (optional<std::pair<process_id_type, int> > m = probe(pg)) {
          BOOST_ASSERT(m->second == root_adj_msg);

          std::vector<vertex_descriptor> adjs;
          receive(pg, m->first, m->second, adjs);

          vertex_map[adjs[0]] = graph_traits<metaGraph>::null_vertex();
          for (typename std::vector<vertex_descriptor>::iterator iter 
                 = ++adjs.begin(); iter != adjs.end(); ++iter)
            edges.push_back(std::make_pair(adjs[0], *iter));
        }

        // Add local roots and edges
        for ( ; r != r_end; ++r ) {
          vertex_map[*r] = graph_traits<metaGraph>::null_vertex();
          edges.reserve(edges.size() + adj[*r].size());
          for (typename std::vector<vertex_descriptor>::iterator iter = adj[*r].begin();
               iter != adj[*r].end(); ++iter)
            edges.push_back(std::make_pair(*r, get(p, *iter)));
        } 

        // Build local meta-graph
        metaGraph mg;

        // Add vertices with property to map back to distributed graph vertex
        for (typename std::map<vertex_descriptor, meta_vertex_descriptor>::iterator
               iter = vertex_map.begin(); iter != vertex_map.end(); ++iter)
          vertex_map[iter->first] 
            = add_vertex(metaVertex<vertex_descriptor>(iter->first), mg);

        // Build meta-vertex map
        typename property_map<metaGraph, vertex_descriptor VertexProperties::*>::type 
          metaVertexMap = get(&VertexProperties::name, mg);

        typename std::vector<std::pair<vertex_descriptor, vertex_descriptor> >
          ::iterator edge_iter = edges.begin();
        for ( ; edge_iter != edges.end(); ++edge_iter)
          add_edge(vertex_map[edge_iter->first], vertex_map[edge_iter->second], mg);
        
        edges.clear();
  
        // Call connected_components on it
        typedef typename property_map<metaGraph, vertex_index_t>::type 
          meta_index_map_type;
        meta_index_map_type meta_index = get(vertex_index, mg);

        std::vector<std::size_t> mg_component_vec(num_vertices(mg));
        typedef iterator_property_map<std::vector<std::size_t>::iterator,
                                      meta_index_map_type>
        meta_components_map_type;
        meta_components_map_type mg_component(mg_component_vec.begin(),
                                              meta_index);
        std::size_t num_comp = connected_components(mg, mg_component);

        // Update Parent pointers
        std::vector<meta_vertex_descriptor> roots(num_comp, graph_traits<metaGraph>::null_vertex());

        BGL_FORALL_VERTICES_T(v, mg, metaGraph) {
          size_t component = get(mg_component, v);
          if (roots[component] == graph_traits<metaGraph>::null_vertex() ||
              get(meta_index, v) < get(meta_index, roots[component])) 
            roots[component] = v;
        }

        // Set all the local parent pointers
        BGL_FORALL_VERTICES_T(v, mg, metaGraph) {
          // Problem in value being put (3rd parameter)
          put(p, get(metaVertexMap, v), get(metaVertexMap, roots[get(mg_component, v)]));
        }
      }

      synchronize(p);
    }
#endif

    /* Function object used to remove internal vertices and vertices >
       the current vertex from the adjacent vertex lists at each
       root */
    template <typename Vertex, typename ParentMap>
    class cull_adjacency_list
    {
    public:
      cull_adjacency_list(const Vertex v, const ParentMap p) : v(v), p(p) {}
      bool operator() (const Vertex x) { return (get(p, x) == v || x == v); }

    private:
      const Vertex    v;
      const ParentMap p;
    };

    /* Comparison operator used to choose targets for hooking s.t. vertices 
       that are hooked to are evenly distributed across processors */
    template <typename OwnerMap, typename LocalMap>
    class hashed_vertex_compare
    {
    public:
      hashed_vertex_compare (const OwnerMap& o, const LocalMap& l)
        : owner(o), local(l) { }

      template <typename Vertex>
      bool operator() (const Vertex x, const Vertex y) 
      { 
        if (get(local, x) < get(local, y))
          return true;
        else if (get(local, x) == get(local, y))
          return (get(owner, x) < get(owner, y));
        return false;
      }

    private:
      OwnerMap   owner;
      LocalMap   local;
    };

#ifdef PBGL_EXPLICIT_SYNCH
    template <typename Graph, typename ParentMap, typename VertexList>
    void
    request_parent_map_entries(const Graph& g, ParentMap p,
                               std::vector<VertexList>& parent_requests)
    {
      typedef typename boost::graph::parallel::process_group_type<Graph>
        ::type process_group_type;
      typedef typename process_group_type::process_id_type process_id_type;

      typedef typename graph_traits<Graph>::vertex_descriptor
        vertex_descriptor;

      process_group_type pg = process_group(g);
      
      /*
        This should probably be send_oob_with_reply, especially when Dave 
        finishes prefetch-batching
      */

      // Send root requests
      for (process_id_type i = 0; i < num_processes(pg); ++i) {
        if (!parent_requests[i].empty()) {
          std::vector<vertex_descriptor> reqs(parent_requests[i].begin(),
                                              parent_requests[i].end());
          send(pg, i, req_parents_msg, reqs);
        }
      }
      
      synchronize(pg);
      
      // Receive root requests and reply to them
      while (optional<std::pair<process_id_type, int> > m = probe(pg)) {
        std::vector<vertex_descriptor> requests;
        receive(pg, m->first, m->second, requests);
        for (std::size_t i = 0; i < requests.size(); ++i)
          requests[i] = get(p, requests[i]);
        send(pg, m->first, parents_msg, requests);
      }
      
      synchronize(pg);
      
      // Receive requested parents
      std::vector<vertex_descriptor> responses;
      for (process_id_type i = 0; i < num_processes(pg); ++i) {
        if (!parent_requests[i].empty()) {
          receive(pg, i, parents_msg, responses);
          std::size_t parent_idx = 0;
          for (typename VertexList::iterator v = parent_requests[i].begin();
               v != parent_requests[i].end(); ++v, ++parent_idx)
            put(p, *v, responses[parent_idx]);
        }
      }
    }
#endif
    
    template<typename DistributedGraph, typename ParentMap>
    void
    parallel_connected_components(DistributedGraph& g, ParentMap p)
    {
      using boost::connected_components;

      typedef typename graph_traits<DistributedGraph>::adjacency_iterator
        adjacency_iterator;
      typedef typename graph_traits<DistributedGraph>::vertex_descriptor
        vertex_descriptor;

      typedef typename boost::graph::parallel::process_group_type<DistributedGraph>
        ::type process_group_type;
      typedef typename process_group_type::process_id_type process_id_type;

      using boost::graph::parallel::process_group;

      process_group_type pg = process_group(g);
      process_id_type id = process_id(pg);

      // TODO (NGE): Should old_roots, roots, and completed_roots be std::list
      adjacency_iterator av1, av2;
      std::vector<vertex_descriptor> old_roots;
      typename std::vector<vertex_descriptor>::iterator liter;
      typename std::vector<vertex_descriptor>::iterator aliter;
      typename std::map<vertex_descriptor,
                        std::vector<vertex_descriptor> > adj;

      typedef typename property_map<DistributedGraph, vertex_owner_t>::const_type
        OwnerMap;
      OwnerMap owner = get(vertex_owner, g);
      typedef typename property_map<DistributedGraph, vertex_local_t>::const_type
        LocalMap;
      LocalMap local = get(vertex_local, g);

      // We need to hold on to all of the parent pointers
      p.set_max_ghost_cells(0);

      //
      // STAGE 1 : Compute local components
      //
      local_subgraph<const DistributedGraph> ls(g);
      typedef typename property_map<local_subgraph<const DistributedGraph>,
                                    vertex_index_t>::type local_index_map_type;
      local_index_map_type local_index = get(vertex_index, ls);

      // Compute local connected components
      std::vector<std::size_t> ls_components_vec(num_vertices(ls));
      typedef iterator_property_map<std::vector<std::size_t>::iterator,
                                    local_index_map_type>
        ls_components_map_type;
      ls_components_map_type ls_component(ls_components_vec.begin(),
                                          local_index);
      std::size_t num_comp = connected_components(ls, ls_component);

      std::vector<vertex_descriptor> 
        roots(num_comp, graph_traits<DistributedGraph>::null_vertex());

      BGL_FORALL_VERTICES_T(v, g, DistributedGraph) {
        size_t component = get(ls_component, v);
        if (roots[component] == graph_traits<DistributedGraph>::null_vertex() ||
            get(local_index, v) < get(local_index, roots[component])) 
          roots[component] = v;
      }

      // Set all the local parent pointers
      BGL_FORALL_VERTICES_T(v, g, DistributedGraph) {
        put(p, v, roots[get(ls_component, v)]);
      }

      if (num_processes(pg) == 1) return;

      // Build adjacency list for all roots
      BGL_FORALL_VERTICES_T(v, g, DistributedGraph) {
        std::vector<vertex_descriptor>& my_adj = adj[get(p, v)];
        for (boost::tie(av1, av2) = adjacent_vertices(v, g);
             av1 != av2; ++av1) {
          if (get(owner, *av1) != id) my_adj.push_back(*av1);
        }
      }

      // For all vertices adjacent to a local vertex get p(v)
      for ( liter = roots.begin(); liter != roots.end(); ++liter ) {
        std::vector<vertex_descriptor>& my_adj = adj[*liter];
        for ( aliter = my_adj.begin(); aliter != my_adj.end(); ++aliter )
          request(p, *aliter);
      }
      synchronize(p);

      // Update adjacency list at root to make sure all adjacent
      // vertices are roots of remote components
      for ( liter = roots.begin(); liter != roots.end(); ++liter )
        {
          std::vector<vertex_descriptor>& my_adj = adj[*liter];
          for ( aliter = my_adj.begin(); aliter != my_adj.end(); ++aliter )
            *aliter = get(p, *aliter);

          my_adj.erase
            (std::remove_if(my_adj.begin(), my_adj.end(),
                       cull_adjacency_list<vertex_descriptor, 
                                           ParentMap>(*liter, p) ),
             my_adj.end());
          // This sort needs to be here to make sure the initial
          // adjacency list is sorted
          std::sort(my_adj.begin(), my_adj.end(), std::less<vertex_descriptor>());
          my_adj.erase(std::unique(my_adj.begin(), my_adj.end()), my_adj.end());
        }

      // Get p(v) for the new adjacent roots
      p.clear();
      for ( liter = roots.begin(); liter != roots.end(); ++liter ) {
        std::vector<vertex_descriptor>& my_adj = adj[*liter];
        for ( aliter = my_adj.begin(); aliter != my_adj.end(); ++aliter )
          request(p, *aliter);
      }
#ifdef PBGL_EXPLICIT_SYNCH
      synchronize(p);
#endif

      // Lastly, remove roots with no adjacent vertices, this is
      // unnecessary but will speed up sparse graphs
      for ( liter = roots.begin(); liter != roots.end(); /*in loop*/)
        {
          if ( adj[*liter].empty() )
            liter = roots.erase(liter);
          else
            ++liter;
        }

#ifdef PBGL_CONSTRUCT_METAGRAPH
      /* TODO: If the number of roots is sufficiently small, we can 
               use a 'problem folding' approach like we do in MST
               to gather all the roots and their adjacencies on one proc
               and solve for the connected components of the meta-graph */
      using boost::parallel::all_reduce;
      std::size_t num_roots = all_reduce(pg, roots.size(), std::plus<std::size_t>());
      if (num_roots < MAX_VERTICES_IN_METAGRAPH) {
        build_local_metagraph(g, p, roots.begin(), roots.end(), adj);
        
        // For each vertex in g, p(v) = p(p(v)), assign parent of leaf
        // vertices from first step to final parent
        BGL_FORALL_VERTICES_T(v, g, DistributedGraph) {
          put(p, v, get(p, get(p, v)));
        }
        
        synchronize(p);
        
        return;
      }
#endif

      //
      // Parallel Phase
      //

      std::vector<vertex_descriptor> completed_roots;
      hashed_vertex_compare<OwnerMap, LocalMap> v_compare(owner, local);
      bool any_hooked;
      vertex_descriptor new_root;

      std::size_t steps = 0;

      do {
        ++steps;

        // Pull in new parents for hooking phase
        synchronize(p);

        //
        // Hooking
        //
        bool hooked = false;
        completed_roots.clear();
        for ( liter = roots.begin(); liter != roots.end(); )
          {
            new_root = graph_traits<DistributedGraph>::null_vertex();
            std::vector<vertex_descriptor>& my_adj = adj[*liter];
            for ( aliter = my_adj.begin(); aliter != my_adj.end(); ++aliter )
              // try to hook to better adjacent vertex
              if ( v_compare( get(p, *aliter), *liter ) )
                new_root = get(p, *aliter);

            if ( new_root != graph_traits<DistributedGraph>::null_vertex() )
              {
                hooked = true;
                put(p, *liter, new_root);
                old_roots.push_back(*liter);
                completed_roots.push_back(*liter);
                liter = roots.erase(liter);
              }
            else
              ++liter;
          }

        //
        // Pointer jumping, perform until new roots determined
        //

        // TODO: Implement cycle reduction rules to reduce this from
        // O(n) to O(log n) [n = cycle length]
        bool all_done;
        std::size_t parent_root_count;

        std::size_t double_steps = 0;

        do {
          ++double_steps;
#ifndef PBGL_EXPLICIT_SYNCH
          // Get p(p(v)) for all old roots, and p(v) for all current roots
          for ( liter = old_roots.begin(); liter != old_roots.end(); ++liter )
            request(p, get(p, *liter));

          synchronize(p);
#else
          // Build root requests
          typedef std::set<vertex_descriptor> VertexSet;
          std::vector<VertexSet> parent_requests(num_processes(pg));
          for ( liter = old_roots.begin(); liter != old_roots.end(); ++liter )
            {
              vertex_descriptor p1 = *liter;
              if (get(owner, p1) != id) parent_requests[get(owner, p1)].insert(p1);
              vertex_descriptor p2 = get(p, p1);
              if (get(owner, p2) != id) parent_requests[get(owner, p2)].insert(p2);
            }

          request_parent_map_entries(g, p, parent_requests);
#endif
          // Perform a pointer jumping step on all old roots
          for ( liter = old_roots.begin(); liter != old_roots.end(); ++liter )
              put(p, *liter, get(p, get(p, *liter)));

          // make sure the parent of all old roots is itself a root
          parent_root_count = 0;
          for ( liter = old_roots.begin(); liter != old_roots.end(); ++liter )
            if ( get(p, *liter) == get(p, get(p, *liter)) )
              parent_root_count++;

          bool done = parent_root_count == old_roots.size();

          all_reduce(pg, &done, &done+1, &all_done,
                     std::logical_and<bool>());
        } while ( !all_done );
#ifdef PARALLEL_BGL_DEBUG
        if (id == 0) std::cerr << double_steps << " doubling steps.\n";
#endif
        //
        // Add adjacent vertices of just completed roots to adjacent
        // vertex list at new parent
        //
        typename std::vector<vertex_descriptor> outgoing_edges;
        for ( liter = completed_roots.begin(); liter != completed_roots.end();
              ++liter )
          {
            vertex_descriptor new_parent = get(p, *liter);

            if ( get(owner, new_parent) == id )
              {
                std::vector<vertex_descriptor>& my_adj = adj[new_parent];
                my_adj.reserve(my_adj.size() + adj[*liter].size());
                my_adj.insert( my_adj.end(),
                               adj[*liter].begin(), adj[*liter].end() );
#ifdef PBGL_IN_PLACE_MERGE
#ifdef PBGL_SORT_ASSERT
                BOOST_ASSERT(::boost::detail::is_sorted(my_adj.begin(),
                                                  my_adj.end() - adj[*liter].size(),
                                                  std::less<vertex_descriptor>()));
                BOOST_ASSERT(::boost::detail::is_sorted(my_adj.end() - adj[*liter].size(),
                                                  my_adj.end(),
                                                  std::less<vertex_descriptor>()));
#endif
                std::inplace_merge(my_adj.begin(),
                                   my_adj.end() - adj[*liter].size(),
                                   my_adj.end(),
                                   std::less<vertex_descriptor>());
#endif


              }
            else if ( adj[*liter].begin() != adj[*liter].end() )
              {
                outgoing_edges.clear();
                outgoing_edges.reserve(adj[*liter].size() + 1);
                // First element is the destination of the adjacency list
                outgoing_edges.push_back(new_parent);
                outgoing_edges.insert(outgoing_edges.end(),
                                      adj[*liter].begin(), adj[*liter].end() );
                send(pg, get(owner, new_parent), edges_msg, outgoing_edges);
                adj[*liter].clear();
              }
          }
        synchronize(pg);

        // Receive edges sent by remote nodes and add them to the
        // indicated vertex's adjacency list
        while (optional<std::pair<process_id_type, int> > m
               = probe(pg))
          {
            std::vector<vertex_descriptor> incoming_edges;
            receive(pg, m->first, edges_msg, incoming_edges);
            typename std::vector<vertex_descriptor>::iterator aviter
              = incoming_edges.begin();
            ++aviter;

            std::vector<vertex_descriptor>& my_adj = adj[incoming_edges[0]];

            my_adj.reserve(my_adj.size() + incoming_edges.size() - 1);
            my_adj.insert( my_adj.end(), aviter, incoming_edges.end() );

#ifdef PBGL_IN_PLACE_MERGE
            std::size_t num_incoming_edges = incoming_edges.size();
#ifdef PBGL_SORT_ASSERT
            BOOST_ASSERT(::boost::detail::is_sorted(my_adj.begin(),
                                              my_adj.end() - (num_incoming_edges-1),
                                              std::less<vertex_descriptor>()));
            BOOST_ASSERT(::boost::detail::is_sorted(my_adj.end() - (num_incoming_edges-1),
                                              my_adj.end(),
                                              std::less<vertex_descriptor>()));
#endif
            std::inplace_merge(my_adj.begin(),
                               my_adj.end() - (num_incoming_edges - 1),
                               my_adj.end(),
                               std::less<vertex_descriptor>());
#endif

          }


        // Remove any adjacent vertices that are in the same component
        // as a root from that root's list
        for ( liter = roots.begin(); liter != roots.end(); ++liter )
          {
            // We can probably get away without sorting and removing
            // duplicates Though sorting *may* cause root
            // determination to occur faster by choosing the root with
            // the most potential to hook to at each step
            std::vector<vertex_descriptor>& my_adj = adj[*liter];
            my_adj.erase
              (std::remove_if(my_adj.begin(), my_adj.end(),
                         cull_adjacency_list<vertex_descriptor,
                                             ParentMap>(*liter, p) ),
               my_adj.end());
#ifndef PBGL_IN_PLACE_MERGE
            std::sort(my_adj.begin(), my_adj.end(),
                 std::less<vertex_descriptor>() );
#endif
            my_adj.erase(std::unique(my_adj.begin(), my_adj.end()), my_adj.end());
          }

        // Reduce result of empty root list test
        all_reduce(pg, &hooked, &hooked+1, &any_hooked,
                   std::logical_or<bool>());
      } while ( any_hooked );
#ifdef PARALLEL_BGL_DEBUG
      if (id == 0) std::cerr << steps << " iterations.\n";
#endif
      //
      // Finalize
      //

      // For each vertex in g, p(v) = p(p(v)), assign parent of leaf
      // vertices from first step to final parent
      BGL_FORALL_VERTICES_T(v, g, DistributedGraph) {
        put(p, v, get(p, get(p, v)));
      }
      
      synchronize(p);
    }

  } // end namespace cc_detail

  template<typename Graph, typename ParentMap, typename ComponentMap>
  typename property_traits<ComponentMap>::value_type
  number_components_from_parents(const Graph& g, ParentMap p, ComponentMap c)
  {
    typedef typename graph_traits<Graph>::vertex_descriptor
      vertex_descriptor;
    typedef typename boost::graph::parallel::process_group_type<Graph>::type
      process_group_type;
    typedef typename property_traits<ComponentMap>::value_type
      ComponentMapType;

    process_group_type pg = process_group(g);

    /* Build list of roots */
    std::vector<vertex_descriptor> my_roots, all_roots;

    BGL_FORALL_VERTICES_T(v, g, Graph) {
      if( std::find( my_roots.begin(), my_roots.end(), get(p, v) )
          == my_roots.end() )
        my_roots.push_back( get(p, v) );
    }

    all_gather(pg, my_roots.begin(), my_roots.end(), all_roots);

    /* Number components */
    std::map<vertex_descriptor, ComponentMapType> comp_numbers;
    ComponentMapType c_num = 0;

    // Compute component numbers
    for (std::size_t i = 0; i < all_roots.size(); i++ )
      if ( comp_numbers.count(all_roots[i]) == 0 )
        comp_numbers[all_roots[i]] = c_num++;

    // Broadcast component numbers
    BGL_FORALL_VERTICES_T(v, g, Graph) {
      put( c, v, comp_numbers[get(p, v)] );
    }

    // Broadcast number of components
    if (process_id(pg) == 0) {
      typedef typename process_group_type::process_size_type
        process_size_type;
      for (process_size_type dest = 1, n = num_processes(pg);
           dest != n; ++dest)
        send(pg, dest, 0, c_num);
    }
    synchronize(pg);

    if (process_id(pg) != 0) receive(pg, 0, 0, c_num);

    synchronize(c);

    return c_num;
  }

  template<typename Graph, typename ParentMap>
  int
  number_components_from_parents(const Graph& g, ParentMap p, 
                                 dummy_property_map)
  {
    using boost::parallel::all_reduce;

    // Count local roots.
    int num_roots = 0;
    BGL_FORALL_VERTICES_T(v, g, Graph)
      if (get(p, v) == v) ++num_roots;
    return all_reduce(g.process_group(), num_roots, std::plus<int>());
  }

  template<typename Graph, typename ComponentMap, typename ParentMap>
  typename property_traits<ComponentMap>::value_type
  connected_components
    (const Graph& g, ComponentMap c, ParentMap p
     BOOST_GRAPH_ENABLE_IF_MODELS_PARM(Graph, distributed_graph_tag))
  {
    cc_detail::parallel_connected_components(g, p);
    return number_components_from_parents(g, p, c);
  }

  /* Construct ParentMap by default */
  template<typename Graph, typename ComponentMap>
  typename property_traits<ComponentMap>::value_type
  connected_components
    ( const Graph& g, ComponentMap c
      BOOST_GRAPH_ENABLE_IF_MODELS_PARM(Graph, distributed_graph_tag) )
  {
    typedef typename graph_traits<Graph>::vertex_descriptor vertex_descriptor;

    std::vector<vertex_descriptor> x(num_vertices(g));

    return connected_components
             (g, c,
              make_iterator_property_map(x.begin(), get(vertex_index, g)));
  }
} // end namespace distributed

using distributed::connected_components;
} // end namespace graph

using graph::distributed::connected_components;
} // end namespace boost

#endif // BOOST_GRAPH_PARALLEL_CC_HPP

/* connected_components.hpp
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
*/