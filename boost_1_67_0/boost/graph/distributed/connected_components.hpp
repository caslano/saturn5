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