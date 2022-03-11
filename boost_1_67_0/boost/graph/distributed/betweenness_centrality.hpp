// Copyright 2004 The Trustees of Indiana University.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_PARALLEL_BRANDES_BETWEENNESS_CENTRALITY_HPP
#define BOOST_GRAPH_PARALLEL_BRANDES_BETWEENNESS_CENTRALITY_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

// #define COMPUTE_PATH_COUNTS_INLINE

#include <boost/graph/betweenness_centrality.hpp>
#include <boost/graph/overloading.hpp>
#include <boost/graph/distributed/concepts.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/config.hpp>
#include <boost/assert.hpp>

// For additive_reducer
#include <boost/graph/distributed/distributed_graph_utility.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/named_function_params.hpp>

#include <boost/property_map/parallel/distributed_property_map.hpp>
#include <boost/graph/distributed/detail/dijkstra_shortest_paths.hpp>
#include <boost/tuple/tuple.hpp>

// NGE - Needed for minstd_rand at L807, should pass vertex list
//       or generator instead 
#include <boost/random/linear_congruential.hpp>

#include <algorithm>
#include <stack>
#include <vector>

// Appending reducer
template <typename T>
struct append_reducer {
  BOOST_STATIC_CONSTANT(bool, non_default_resolver = true);
      
  template<typename K>
  T operator()(const K&) const { return T(); }
      
  template<typename K>
  T operator()(const K&, const T& x, const T& y) const 
  { 
    T z(x.begin(), x.end());
    for (typename T::const_iterator iter = y.begin(); iter != y.end(); ++iter)
      if (std::find(z.begin(), z.end(), *iter) == z.end())
        z.push_back(*iter);
    
    return z;
  }
};

namespace boost {

  namespace serialization {

    // TODO(nge): Write generalized serialization for tuples
    template<typename Archive, typename T1, typename T2, typename T3, 
             typename T4>
    void serialize(Archive & ar,
                   boost::tuple<T1,T2,T3, T4>& t,
                   const unsigned int)
    {
      ar & boost::tuples::get<0>(t);
      ar & boost::tuples::get<1>(t);
      ar & boost::tuples::get<2>(t);
      ar & boost::tuples::get<3>(t);
    }

  } // serialization

  template <typename OwnerMap, typename Tuple>
  class get_owner_of_first_tuple_element {

  public:
    typedef typename property_traits<OwnerMap>::value_type owner_type;
    
    get_owner_of_first_tuple_element(OwnerMap owner) : owner(owner) { }

    owner_type get_owner(Tuple t) { return get(owner, boost::tuples::get<0>(t)); }

  private:
    OwnerMap owner;
  };

  template <typename OwnerMap, typename Tuple>
  typename get_owner_of_first_tuple_element<OwnerMap, Tuple>::owner_type
  get(get_owner_of_first_tuple_element<OwnerMap, Tuple> o, Tuple t)
  { return o.get_owner(t); } 

  template <typename OwnerMap>
  class get_owner_of_first_pair_element {

  public:
    typedef typename property_traits<OwnerMap>::value_type owner_type;
    
    get_owner_of_first_pair_element(OwnerMap owner) : owner(owner) { }

    template <typename Vertex, typename T>
    owner_type get_owner(std::pair<Vertex, T> p) { return get(owner, p.first); }

  private:
    OwnerMap owner;
  };

  template <typename OwnerMap, typename Vertex, typename T>
  typename get_owner_of_first_pair_element<OwnerMap>::owner_type
  get(get_owner_of_first_pair_element<OwnerMap> o, std::pair<Vertex, T> p)
  { return o.get_owner(p); } 

  namespace graph { namespace parallel { namespace detail {

  template<typename DistanceMap, typename IncomingMap>
  class betweenness_centrality_msg_value
  {
    typedef typename property_traits<DistanceMap>::value_type distance_type;
    typedef typename property_traits<IncomingMap>::value_type incoming_type;
    typedef typename incoming_type::value_type incoming_value_type;

  public:
    typedef std::pair<distance_type, incoming_value_type> type;
    
    static type create(distance_type dist, incoming_value_type source)
    { return std::make_pair(dist, source); }
  };


  /************************************************************************/
  /* Delta-stepping Betweenness Centrality                                */
  /************************************************************************/

  template<typename Graph, typename DistanceMap, typename IncomingMap, 
           typename EdgeWeightMap, typename PathCountMap
#ifdef COMPUTE_PATH_COUNTS_INLINE
           , typename IsSettledMap, typename VertexIndexMap
#endif
           >
  class betweenness_centrality_delta_stepping_impl { 
    // Could inherit from delta_stepping_impl to get run() method
    // but for the time being it's just reproduced here

    typedef typename graph_traits<Graph>::vertex_descriptor Vertex;
    typedef typename graph_traits<Graph>::degree_size_type Degree;
    typedef typename property_traits<EdgeWeightMap>::value_type Dist;
    typedef typename property_traits<IncomingMap>::value_type IncomingType;
    typedef typename boost::graph::parallel::process_group_type<Graph>::type 
      ProcessGroup;
    
    typedef std::list<Vertex> Bucket;
    typedef typename Bucket::iterator BucketIterator;
    typedef typename std::vector<Bucket*>::size_type BucketIndex;

    typedef betweenness_centrality_msg_value<DistanceMap, IncomingMap> 
      MessageValue;
    
    enum { 
      // Relax a remote vertex. The message contains a pair<Vertex,
      // MessageValue>, the first part of which is the vertex whose
      // tentative distance is being relaxed and the second part
      // contains either the new distance (if there is no predecessor
      // map) or a pair with the distance and predecessor.
      msg_relax 
    };

  public:

    // Must supply delta, ctor that guesses delta removed 
    betweenness_centrality_delta_stepping_impl(const Graph& g,
                                               DistanceMap distance, 
                                               IncomingMap incoming,
                                               EdgeWeightMap weight,
                                               PathCountMap path_count,
#ifdef COMPUTE_PATH_COUNTS_INLINE
                                               IsSettledMap is_settled,
                                               VertexIndexMap vertex_index,
#endif
                                               Dist delta);
    
    void run(Vertex s);

  private:
    // Relax the edge (u, v), creating a new best path of distance x.
    void relax(Vertex u, Vertex v, Dist x);

    // Synchronize all of the processes, by receiving all messages that
    // have not yet been received.
    void synchronize()
    {
      using boost::parallel::synchronize;
      synchronize(pg);
    }
    
    // Setup triggers for msg_relax messages
    void setup_triggers()
    {
      using boost::parallel::simple_trigger;
      simple_trigger(pg, msg_relax, this, 
                     &betweenness_centrality_delta_stepping_impl::handle_msg_relax);
    }

    void handle_msg_relax(int /*source*/, int /*tag*/,
                          const std::pair<Vertex, typename MessageValue::type>& data,
                          boost::parallel::trigger_receive_context)
    { relax(data.second.second, data.first, data.second.first); }

    const Graph& g;
    IncomingMap incoming;
    DistanceMap distance;
    EdgeWeightMap weight;
    PathCountMap path_count;
#ifdef COMPUTE_PATH_COUNTS_INLINE
    IsSettledMap is_settled;
    VertexIndexMap vertex_index;
#endif
    Dist delta;
    ProcessGroup pg;
    typename property_map<Graph, vertex_owner_t>::const_type owner;
    typename property_map<Graph, vertex_local_t>::const_type local;
    
    // A "property map" that contains the position of each vertex in
    // whatever bucket it resides in.
    std::vector<BucketIterator> position_in_bucket;
    
    // Bucket data structure. The ith bucket contains all local vertices
    // with (tentative) distance in the range [i*delta,
    // (i+1)*delta). 
    std::vector<Bucket*> buckets;
    
    // This "dummy" list is used only so that we can initialize the
    // position_in_bucket property map with non-singular iterators. This
    // won't matter for most implementations of the C++ Standard
    // Library, but it avoids undefined behavior and allows us to run
    // with library "debug modes".
    std::list<Vertex> dummy_list;
    
    // A "property map" that states which vertices have been deleted
    // from the bucket in this iteration.
    std::vector<bool> vertex_was_deleted;
  };

  template<typename Graph, typename DistanceMap, typename IncomingMap, 
           typename EdgeWeightMap, typename PathCountMap
#ifdef COMPUTE_PATH_COUNTS_INLINE
           , typename IsSettledMap, typename VertexIndexMap
#endif
           >
  betweenness_centrality_delta_stepping_impl<
    Graph, DistanceMap, IncomingMap, EdgeWeightMap, PathCountMap
#ifdef COMPUTE_PATH_COUNTS_INLINE
           , IsSettledMap, VertexIndexMap
#endif
    >::
  betweenness_centrality_delta_stepping_impl(const Graph& g,
                                             DistanceMap distance,
                                             IncomingMap incoming,
                                             EdgeWeightMap weight,
                                             PathCountMap path_count,
#ifdef COMPUTE_PATH_COUNTS_INLINE
                                             IsSettledMap is_settled,
                                             VertexIndexMap vertex_index,
#endif
                                             Dist delta)
    : g(g),
      incoming(incoming),
      distance(distance),
      weight(weight),
      path_count(path_count),
#ifdef COMPUTE_PATH_COUNTS_INLINE
      is_settled(is_settled),
      vertex_index(vertex_index),
#endif
      delta(delta),
      pg(boost::graph::parallel::process_group_adl(g), boost::parallel::attach_distributed_object()),
      owner(get(vertex_owner, g)),
      local(get(vertex_local, g))

  { setup_triggers(); }

  template<typename Graph, typename DistanceMap, typename IncomingMap, 
           typename EdgeWeightMap, typename PathCountMap
#ifdef COMPUTE_PATH_COUNTS_INLINE
           , typename IsSettledMap, typename VertexIndexMap
#endif
           >
  void
  betweenness_centrality_delta_stepping_impl<
    Graph, DistanceMap, IncomingMap, EdgeWeightMap, PathCountMap
#ifdef COMPUTE_PATH_COUNTS_INLINE
           , IsSettledMap, VertexIndexMap
#endif
    >::
  run(Vertex s)
  {
    typedef typename boost::graph::parallel::process_group_type<Graph>::type 
      process_group_type;
    typename process_group_type::process_id_type id = process_id(pg);

    Dist inf = (std::numeric_limits<Dist>::max)();
    
    // None of the vertices are stored in the bucket.
    position_in_bucket.clear();
    position_in_bucket.resize(num_vertices(g), dummy_list.end());
    
    // None of the vertices have been deleted
    vertex_was_deleted.clear();
    vertex_was_deleted.resize(num_vertices(g), false);
    
    // No path from s to any other vertex, yet
    BGL_FORALL_VERTICES_T(v, g, Graph)
      put(distance, v, inf);
    
    // The distance to the starting node is zero
    if (get(owner, s) == id) 
      // Put "s" into its bucket (bucket 0)
      relax(s, s, 0);
    else
      // Note that we know the distance to s is zero
      cache(distance, s, 0);
    
#ifdef COMPUTE_PATH_COUNTS_INLINE
    // Synchronize here to deliver initial relaxation since we don't
    // synchronize at the beginning of the inner loop any more
    synchronize(); 

    // Incoming edge count map is an implementation detail and should
    // be freed as soon as possible so build it here
    typedef typename graph_traits<Graph>::edges_size_type edges_size_type;

    std::vector<edges_size_type> incoming_edge_countS(num_vertices(g));
    iterator_property_map<typename std::vector<edges_size_type>::iterator, VertexIndexMap> 
      incoming_edge_count(incoming_edge_countS.begin(), vertex_index);
#endif

    BucketIndex max_bucket = (std::numeric_limits<BucketIndex>::max)();
    BucketIndex current_bucket = 0;
    do {
#ifdef COMPUTE_PATH_COUNTS_INLINE
      // We need to clear the outgoing map after every bucket so just build it here
      std::vector<IncomingType> outgoingS(num_vertices(g));
      IncomingMap outgoing(outgoingS.begin(), vertex_index);
      
      outgoing.set_reduce(append_reducer<IncomingType>());
#else
      // Synchronize with all of the other processes.
      synchronize();
#endif    
  
      // Find the next bucket that has something in it.
      while (current_bucket < buckets.size() 
             && (!buckets[current_bucket] || buckets[current_bucket]->empty()))
        ++current_bucket;
      if (current_bucket >= buckets.size())
        current_bucket = max_bucket;
      
      // Find the smallest bucket (over all processes) that has vertices
      // that need to be processed.
      using boost::parallel::all_reduce;
      using boost::parallel::minimum;
      current_bucket = all_reduce(pg, current_bucket, minimum<BucketIndex>());
      
      if (current_bucket == max_bucket)
        // There are no non-empty buckets in any process; exit. 
        break;
      
      // Contains the set of vertices that have been deleted in the
      // relaxation of "light" edges. Note that we keep track of which
      // vertices were deleted with the property map
      // "vertex_was_deleted".
      std::vector<Vertex> deleted_vertices;
      
      // Repeatedly relax light edges
      bool nonempty_bucket;
      do {
        // Someone has work to do in this bucket.
        
        if (current_bucket < buckets.size() && buckets[current_bucket]) {
          Bucket& bucket = *buckets[current_bucket];
          // For each element in the bucket
          while (!bucket.empty()) {
            Vertex u = bucket.front();
            
            // Remove u from the front of the bucket
            bucket.pop_front();
            
            // Insert u into the set of deleted vertices, if it hasn't
            // been done already.
            if (!vertex_was_deleted[get(local, u)]) {
              vertex_was_deleted[get(local, u)] = true;
              deleted_vertices.push_back(u);
            }
            
            // Relax each light edge. 
            Dist u_dist = get(distance, u);
            BGL_FORALL_OUTEDGES_T(u, e, g, Graph)
              if (get(weight, e) <= delta) // light edge 
                relax(u, target(e, g), u_dist + get(weight, e));
          }
        }

        // Synchronize with all of the other processes.
        synchronize();
        
        // Is the bucket empty now?
        nonempty_bucket = (current_bucket < buckets.size() 
                           && buckets[current_bucket]
                           && !buckets[current_bucket]->empty());
      } while (all_reduce(pg, nonempty_bucket, std::logical_or<bool>()));
      
      // Relax heavy edges for each of the vertices that we previously
      // deleted.
      for (typename std::vector<Vertex>::iterator iter = deleted_vertices.begin();
           iter != deleted_vertices.end(); ++iter) {
        // Relax each heavy edge. 
        Vertex u = *iter;
        Dist u_dist = get(distance, u);
        BGL_FORALL_OUTEDGES_T(u, e, g, Graph)
          if (get(weight, e) > delta) // heavy edge
            relax(u, target(e, g), u_dist + get(weight, e)); 

#ifdef COMPUTE_PATH_COUNTS_INLINE
        // Set outgoing paths
        IncomingType in = get(incoming, u);
        for (typename IncomingType::iterator pred = in.begin(); pred != in.end(); ++pred) 
          if (get(owner, *pred) == id) {
            IncomingType x = get(outgoing, *pred);
            if (std::find(x.begin(), x.end(), u) == x.end())
              x.push_back(u);
            put(outgoing, *pred, x);
          } else {
            IncomingType in;
            in.push_back(u);
            put(outgoing, *pred, in);
          }

        // Set incoming edge counts
        put(incoming_edge_count, u, in.size());
#endif
      }

#ifdef COMPUTE_PATH_COUNTS_INLINE
      synchronize();  // Deliver heavy edge relaxations and outgoing paths

      // Build Queue
      typedef typename property_traits<PathCountMap>::value_type PathCountType;
      typedef std::pair<Vertex, PathCountType> queue_value_type;
      typedef typename property_map<Graph, vertex_owner_t>::const_type OwnerMap;
      typedef typename get_owner_of_first_pair_element<OwnerMap> IndirectOwnerMap;

      typedef boost::queue<queue_value_type> local_queue_type;
      typedef boost::graph::distributed::distributed_queue<process_group_type,
                                                           IndirectOwnerMap,
                                                           local_queue_type> dist_queue_type;

      IndirectOwnerMap indirect_owner(owner);
      dist_queue_type Q(pg, indirect_owner);

      // Find sources to initialize queue
      BGL_FORALL_VERTICES_T(v, g, Graph) {
        if (get(is_settled, v) && !(get(outgoing, v).empty())) {
          put(incoming_edge_count, v, 1); 
          Q.push(std::make_pair(v, 0)); // Push this vertex with no additional path count
        }
      }

      // Set path counts for vertices in this bucket
      while (!Q.empty()) {
        queue_value_type t = Q.top(); Q.pop();
        Vertex v = t.first;
        PathCountType p = t.second;

        put(path_count, v, get(path_count, v) + p);
        put(incoming_edge_count, v, get(incoming_edge_count, v) - 1);

        if (get(incoming_edge_count, v) == 0) {
          IncomingType out = get(outgoing, v);
          for (typename IncomingType::iterator iter = out.begin(); iter != out.end(); ++iter)
            Q.push(std::make_pair(*iter, get(path_count, v)));
        }
      }

      // Mark the vertices in this bucket settled 
      for (typename std::vector<Vertex>::iterator iter = deleted_vertices.begin();
           iter != deleted_vertices.end(); ++iter) 
        put(is_settled, *iter, true);

      // No need to clear path count map as it is never read/written remotely
      // No need to clear outgoing map as it is re-alloced every bucket 
#endif
      
      // Go to the next bucket: the current bucket must already be empty.
      ++current_bucket;
    } while (true);
    
    // Delete all of the buckets.
    for (typename std::vector<Bucket*>::iterator iter = buckets.begin();
         iter != buckets.end(); ++iter) {
      if (*iter) {
        delete *iter;
        *iter = 0;
      }
    }
  }
        
  template<typename Graph, typename DistanceMap, typename IncomingMap, 
           typename EdgeWeightMap, typename PathCountMap
#ifdef COMPUTE_PATH_COUNTS_INLINE
           , typename IsSettledMap, typename VertexIndexMap
#endif
           >
  void
  betweenness_centrality_delta_stepping_impl<
    Graph, DistanceMap, IncomingMap, EdgeWeightMap, PathCountMap
#ifdef COMPUTE_PATH_COUNTS_INLINE
           , IsSettledMap, VertexIndexMap
#endif
    >::
  relax(Vertex u, Vertex v, Dist x)
  {

    if (x <= get(distance, v)) {
      
      // We're relaxing the edge to vertex v.
      if (get(owner, v) == process_id(pg)) {
        if (x < get(distance, v)) {
          // Compute the new bucket index for v
          BucketIndex new_index = static_cast<BucketIndex>(x / delta);
        
          // Make sure there is enough room in the buckets data structure.
          if (new_index >= buckets.size()) buckets.resize(new_index + 1, 0);
        
          // Make sure that we have allocated the bucket itself.
          if (!buckets[new_index]) buckets[new_index] = new Bucket;
          
          if (get(distance, v) != (std::numeric_limits<Dist>::max)()
              && !vertex_was_deleted[get(local, v)]) {
            // We're moving v from an old bucket into a new one. Compute
            // the old index, then splice it in.
            BucketIndex old_index 
              = static_cast<BucketIndex>(get(distance, v) / delta);
            buckets[new_index]->splice(buckets[new_index]->end(),
                                       *buckets[old_index],
                                       position_in_bucket[get(local, v)]);
          } else {
            // We're inserting v into a bucket for the first time. Put it
            // at the end.
            buckets[new_index]->push_back(v);
          }
          
          // v is now at the last position in the new bucket
          position_in_bucket[get(local, v)] = buckets[new_index]->end();
          --position_in_bucket[get(local, v)];
          
          // Update tentative distance information and incoming, path_count
          if (u != v) put(incoming, v, IncomingType(1, u));
          put(distance, v, x);
        }        // u != v covers initial source relaxation and self-loops
        else if (x == get(distance, v) && u != v) {

          // Add incoming edge if it's not already in the list
          IncomingType in = get(incoming, v);
          if (std::find(in.begin(), in.end(), u) == in.end()) {
            in.push_back(u);
            put(incoming, v, in);
          }
        }
      } else {
        // The vertex is remote: send a request to the vertex's owner
        send(pg, get(owner, v), msg_relax, 
             std::make_pair(v, MessageValue::create(x, u)));

        // Cache tentative distance information
        cache(distance, v, x);
      }
    }
  }

  /************************************************************************/
  /* Shortest Paths function object for betweenness centrality            */
  /************************************************************************/

  template<typename WeightMap>
  struct brandes_shortest_paths {
    typedef typename property_traits<WeightMap>::value_type weight_type;

    brandes_shortest_paths() 
      : weight(1), delta(0)  { }
    brandes_shortest_paths(weight_type delta) 
      : weight(1), delta(delta)  { }
    brandes_shortest_paths(WeightMap w) 
      : weight(w), delta(0)  { }
    brandes_shortest_paths(WeightMap w, weight_type delta) 
      : weight(w), delta(delta)  { }

    template<typename Graph, typename IncomingMap, typename DistanceMap,
             typename PathCountMap
#ifdef COMPUTE_PATH_COUNTS_INLINE
             , typename IsSettledMap, typename VertexIndexMap
#endif

             > 
    void 
    operator()(Graph& g, 
               typename graph_traits<Graph>::vertex_descriptor s,
               IncomingMap incoming,
               DistanceMap distance,
               PathCountMap path_count
#ifdef COMPUTE_PATH_COUNTS_INLINE
               , IsSettledMap is_settled,
               VertexIndexMap vertex_index 
#endif
               )
    {  
      // The "distance" map needs to act like one, retrieving the default
      // value of infinity.
      set_property_map_role(vertex_distance, distance);
      
      // Only calculate delta the first time operator() is called
      // This presumes g is the same every time, but so does the fact
      // that we're reusing the weight map
      if (delta == 0)
        set_delta(g);
      
      // TODO (NGE): Restructure the code so we don't have to construct
      //             impl every time?
      betweenness_centrality_delta_stepping_impl<
          Graph, DistanceMap, IncomingMap, WeightMap, PathCountMap
#ifdef COMPUTE_PATH_COUNTS_INLINE
          , IsSettledMap, VertexIndexMap
#endif
            >
        impl(g, distance, incoming, weight, path_count, 
#ifdef COMPUTE_PATH_COUNTS_INLINE
             is_settled, vertex_index, 
#endif
             delta);

      impl.run(s);
    }

  private:

    template <typename Graph>
    void
    set_delta(const Graph& g)
    {
      using boost::parallel::all_reduce;
      using boost::parallel::maximum;
      using std::max;

      typedef typename graph_traits<Graph>::degree_size_type Degree;
      typedef weight_type Dist;

      // Compute the maximum edge weight and degree
      Dist max_edge_weight = 0;
      Degree max_degree = 0;
      BGL_FORALL_VERTICES_T(u, g, Graph) {
        max_degree = max BOOST_PREVENT_MACRO_SUBSTITUTION (max_degree, out_degree(u, g));
        BGL_FORALL_OUTEDGES_T(u, e, g, Graph)
          max_edge_weight = max BOOST_PREVENT_MACRO_SUBSTITUTION (max_edge_weight, get(weight, e));
      }
      
      max_edge_weight = all_reduce(process_group(g), max_edge_weight, maximum<Dist>());
      max_degree = all_reduce(process_group(g), max_degree, maximum<Degree>());
      
      // Take a guess at delta, based on what works well for random
      // graphs.
      delta = max_edge_weight / max_degree;
      if (delta == 0)
        delta = 1;
    }

    WeightMap     weight;
    weight_type   delta;
  };

  // Perform a single SSSP from the specified vertex and update the centrality map(s)
  template<typename Graph, typename CentralityMap, typename EdgeCentralityMap,
           typename IncomingMap, typename DistanceMap, typename DependencyMap, 
           typename PathCountMap, 
#ifdef COMPUTE_PATH_COUNTS_INLINE
           typename IsSettledMap,
#endif 
           typename VertexIndexMap, typename ShortestPaths> 
  void
  do_brandes_sssp(const Graph& g, 
                  CentralityMap centrality,     
                  EdgeCentralityMap edge_centrality_map,
                  IncomingMap incoming,
                  DistanceMap distance,
                  DependencyMap dependency,
                  PathCountMap path_count, 
#ifdef COMPUTE_PATH_COUNTS_INLINE
                  IsSettledMap is_settled,
#endif 
                  VertexIndexMap vertex_index,
                  ShortestPaths shortest_paths,
                  typename graph_traits<Graph>::vertex_descriptor s)
  {
    using boost::detail::graph::update_centrality;      
    using boost::graph::parallel::process_group;

    typedef typename graph_traits<Graph>::vertex_descriptor vertex_descriptor;
    typedef typename graph_traits<Graph>::edges_size_type edges_size_type;

    typedef typename property_traits<IncomingMap>::value_type incoming_type;
    typedef typename property_traits<DistanceMap>::value_type distance_type;
    typedef typename property_traits<DependencyMap>::value_type dependency_type;
    typedef typename property_traits<PathCountMap>::value_type path_count_type;

    typedef typename incoming_type::iterator incoming_iterator;

    typedef typename property_map<Graph, vertex_owner_t>::const_type OwnerMap;
    OwnerMap owner = get(vertex_owner, g);

    typedef typename boost::graph::parallel::process_group_type<Graph>::type 
      process_group_type;
    process_group_type pg = process_group(g);
    typename process_group_type::process_id_type id = process_id(pg);

    // TODO: Is it faster not to clear some of these maps?
    // Initialize for this iteration
    distance.clear();
    incoming.clear();
    path_count.clear();
    dependency.clear();
    BGL_FORALL_VERTICES_T(v, g, Graph) {
      put(path_count, v, 0);
      put(dependency, v, 0);
    }

    if (get(owner, s) == id) {
      put(incoming, s, incoming_type());
#ifdef COMPUTE_PATH_COUNTS_INLINE
      put(path_count, s, 1);
      put(is_settled, s, true);
#endif
    }

    // Execute the shortest paths algorithm. This will be either
    // a weighted or unweighted customized breadth-first search,
    shortest_paths(g, s, incoming, distance, path_count
#ifdef COMPUTE_PATH_COUNTS_INLINE
                   , is_settled, vertex_index
#endif 
                   );

#ifndef COMPUTE_PATH_COUNTS_INLINE

    //
    // TODO: Optimize case where source has no out-edges
    //
 
    // Count of incoming edges to tell when all incoming edges have been relaxed in 
    // the induced shortest paths DAG 
    std::vector<edges_size_type> incoming_edge_countS(num_vertices(g));
    iterator_property_map<typename std::vector<edges_size_type>::iterator, VertexIndexMap> 
      incoming_edge_count(incoming_edge_countS.begin(), vertex_index);

    BGL_FORALL_VERTICES_T(v, g, Graph) {
      put(incoming_edge_count, v, get(incoming, v).size());
    }

    if (get(owner, s) == id) {
      put(incoming_edge_count, s, 1);
      put(incoming, s, incoming_type());
    }

    std::vector<incoming_type> outgoingS(num_vertices(g));
    iterator_property_map<typename std::vector<incoming_type>::iterator, VertexIndexMap> 
      outgoing(outgoingS.begin(), vertex_index);

    outgoing.set_reduce(append_reducer<incoming_type>());

    // Mark forward adjacencies in DAG of shortest paths

    // TODO: It's possible to do this using edge flags but it's not currently done this way
    //       because during traversal of the DAG we would have to examine all out edges
    //       which would lead to more memory accesses and a larger cache footprint.
    //
    //       In the bidirectional graph case edge flags would be an excellent way of marking
    //       edges in the DAG of shortest paths  
    BGL_FORALL_VERTICES_T(v, g, Graph) {
      incoming_type i = get(incoming, v);
      for (typename incoming_type::iterator iter = i.begin(); iter != i.end(); ++iter) {
        if (get(owner, *iter) == id) {
          incoming_type x = get(outgoing, *iter);
          if (std::find(x.begin(), x.end(), v) == x.end())
            x.push_back(v);
          put(outgoing, *iter, x);
        } else {
          incoming_type in;
          in.push_back(v);
          put(outgoing, *iter, in);
        }
      }
    }

    synchronize(pg);

    // Traverse DAG induced by forward edges in dependency order and compute path counts
    {
      typedef std::pair<vertex_descriptor, path_count_type> queue_value_type;
      typedef get_owner_of_first_pair_element<OwnerMap> IndirectOwnerMap;

      typedef boost::queue<queue_value_type> local_queue_type;
      typedef boost::graph::distributed::distributed_queue<process_group_type,
                                                           IndirectOwnerMap,
                                                           local_queue_type> dist_queue_type;

      IndirectOwnerMap indirect_owner(owner);
      dist_queue_type Q(pg, indirect_owner);

      if (get(owner, s) == id)
        Q.push(std::make_pair(s, 1));

      while (!Q.empty()) {
        queue_value_type t = Q.top(); Q.pop();
        vertex_descriptor v = t.first;
        path_count_type p = t.second;

        put(path_count, v, get(path_count, v) + p);
        put(incoming_edge_count, v, get(incoming_edge_count, v) - 1);

        if (get(incoming_edge_count, v) == 0) {
          incoming_type out = get(outgoing, v);
          for (typename incoming_type::iterator iter = out.begin(); iter != out.end(); ++iter)
            Q.push(std::make_pair(*iter, get(path_count, v)));
        }
      }
    }

#endif // COMPUTE_PATH_COUNTS_INLINE

    //
    // Compute dependencies 
    //    


    // Build the distributed_queue
    // Value type consists of 1) target of update 2) source of update
    // 3) dependency of source 4) path count of source
    typedef boost::tuple<vertex_descriptor, vertex_descriptor, dependency_type, path_count_type>
      queue_value_type;
    typedef get_owner_of_first_tuple_element<OwnerMap, queue_value_type> IndirectOwnerMap;

    typedef boost::queue<queue_value_type> local_queue_type;
    typedef boost::graph::distributed::distributed_queue<process_group_type,
                                                         IndirectOwnerMap,
                                                         local_queue_type> dist_queue_type;

    IndirectOwnerMap indirect_owner(owner);
    dist_queue_type Q(pg, indirect_owner);

    // Calculate number of vertices each vertex depends on, when a vertex has been pushed
    // that number of times then we will update it
    // AND Request path counts of sources of incoming edges
    std::vector<dependency_type> dependency_countS(num_vertices(g), 0);
    iterator_property_map<typename std::vector<dependency_type>::iterator, VertexIndexMap> 
      dependency_count(dependency_countS.begin(), vertex_index);

    dependency_count.set_reduce(boost::graph::distributed::additive_reducer<dependency_type>());

    path_count.set_max_ghost_cells(0);

    BGL_FORALL_VERTICES_T(v, g, Graph) {
      if (get(distance, v) < (std::numeric_limits<distance_type>::max)()) {
        incoming_type el = get(incoming, v);
        for (incoming_iterator vw = el.begin(); vw != el.end(); ++vw) {
          if (get(owner, *vw) == id)
            put(dependency_count, *vw, get(dependency_count, *vw) + 1);
          else {
            put(dependency_count, *vw, 1);

            // Request path counts
            get(path_count, *vw); 
          }

          // request() doesn't work here, perhaps because we don't have a copy of this 
          // ghost cell already?
        }
      }
    }

    synchronize(pg);

    // Push vertices with non-zero distance/path count and zero dependency count
    BGL_FORALL_VERTICES_T(v, g, Graph) {
      if (get(distance, v) < (std::numeric_limits<distance_type>::max)()
          && get(dependency_count, v) == 0) 
        Q.push(boost::make_tuple(v, v, get(dependency, v), get(path_count, v)));
    }

    dependency.set_max_ghost_cells(0);
    while(!Q.empty()) {

      queue_value_type x = Q.top(); Q.pop();
      vertex_descriptor w = boost::tuples::get<0>(x);
      vertex_descriptor source = boost::tuples::get<1>(x);
      dependency_type dep = boost::tuples::get<2>(x);
      path_count_type pc = boost::tuples::get<3>(x);

      cache(dependency, source, dep);
      cache(path_count, source, pc);

      if (get(dependency_count, w) != 0)
        put(dependency_count, w, get(dependency_count, w) - 1);

      if (get(dependency_count, w) == 0) { 

        // Update dependency and centrality of sources of incoming edges
        incoming_type el = get(incoming, w);
        for (incoming_iterator vw = el.begin(); vw != el.end(); ++vw) {
          vertex_descriptor v = *vw;

          BOOST_ASSERT(get(path_count, w) != 0);

          dependency_type factor = dependency_type(get(path_count, v))
            / dependency_type(get(path_count, w));
          factor *= (dependency_type(1) + get(dependency, w));
          
          if (get(owner, v) == id)
            put(dependency, v, get(dependency, v) + factor);
          else
            put(dependency, v, factor);
          
          update_centrality(edge_centrality_map, v, factor);
        }
        
        if (w != s)
          update_centrality(centrality, w, get(dependency, w));

        // Push sources of edges in incoming edge list
        for (incoming_iterator vw = el.begin(); vw != el.end(); ++vw)
          Q.push(boost::make_tuple(*vw, w, get(dependency, w), get(path_count, w)));
      }
    }
  }

  template<typename Graph, typename CentralityMap, typename EdgeCentralityMap,
           typename IncomingMap, typename DistanceMap, typename DependencyMap, 
           typename PathCountMap, typename VertexIndexMap, typename ShortestPaths, 
           typename Buffer>
  void 
  brandes_betweenness_centrality_impl(const Graph& g, 
                                      CentralityMap centrality,     
                                      EdgeCentralityMap edge_centrality_map,
                                      IncomingMap incoming,
                                      DistanceMap distance,
                                      DependencyMap dependency,
                                      PathCountMap path_count, 
                                      VertexIndexMap vertex_index,
                                      ShortestPaths shortest_paths,
                                      Buffer sources)
  {
    using boost::detail::graph::init_centrality_map;
    using boost::detail::graph::divide_centrality_by_two;       
    using boost::graph::parallel::process_group;
    
    typedef typename graph_traits<Graph>::vertex_descriptor vertex_descriptor;

    typedef typename property_traits<DistanceMap>::value_type distance_type;
    typedef typename property_traits<DependencyMap>::value_type dependency_type;

    // Initialize centrality
    init_centrality_map(vertices(g), centrality);
    init_centrality_map(edges(g), edge_centrality_map);

    // Set the reduction operation on the dependency map to be addition
    dependency.set_reduce(boost::graph::distributed::additive_reducer<dependency_type>()); 
    distance.set_reduce(boost::graph::distributed::choose_min_reducer<distance_type>());

    // Don't allow remote procs to write incoming or path_count maps
    // updating them is handled inside the betweenness_centrality_queue
    incoming.set_consistency_model(0);
    path_count.set_consistency_model(0);

    typedef typename boost::graph::parallel::process_group_type<Graph>::type 
      process_group_type;
    process_group_type pg = process_group(g);

#ifdef COMPUTE_PATH_COUNTS_INLINE
    // Build is_settled maps
    std::vector<bool> is_settledS(num_vertices(g));
    typedef iterator_property_map<std::vector<bool>::iterator, VertexIndexMap> 
      IsSettledMap;

    IsSettledMap is_settled(is_settledS.begin(), vertex_index);
#endif

    if (!sources.empty()) {
      // DO SSSPs
      while (!sources.empty()) {
        do_brandes_sssp(g, centrality, edge_centrality_map, incoming, distance,
                        dependency, path_count, 
#ifdef COMPUTE_PATH_COUNTS_INLINE
                        is_settled,
#endif 
                        vertex_index, shortest_paths, sources.top());
        sources.pop();
      }
    } else { // Exact Betweenness Centrality
      typedef typename graph_traits<Graph>::vertices_size_type vertices_size_type;
      vertices_size_type n = num_vertices(g);
      n = boost::parallel::all_reduce(pg, n, std::plus<vertices_size_type>());
      
      for (vertices_size_type i = 0; i < n; ++i) {
        vertex_descriptor v = vertex(i, g);

        do_brandes_sssp(g, centrality, edge_centrality_map, incoming, distance,
                        dependency, path_count, 
#ifdef COMPUTE_PATH_COUNTS_INLINE
                        is_settled,
#endif 
                        vertex_index, shortest_paths, v);
      }
    }

    typedef typename graph_traits<Graph>::directed_category directed_category;
    const bool is_undirected = 
      is_convertible<directed_category*, undirected_tag*>::value;
    if (is_undirected) {
      divide_centrality_by_two(vertices(g), centrality);
      divide_centrality_by_two(edges(g), edge_centrality_map);
    }
  }

  template<typename Graph, typename CentralityMap, typename EdgeCentralityMap,
           typename IncomingMap, typename DistanceMap, typename DependencyMap, 
           typename PathCountMap, typename VertexIndexMap, typename ShortestPaths,
           typename Stack>
  void
  do_sequential_brandes_sssp(const Graph& g, 
                             CentralityMap centrality,     
                             EdgeCentralityMap edge_centrality_map,
                             IncomingMap incoming,
                             DistanceMap distance,
                             DependencyMap dependency,
                             PathCountMap path_count, 
                             VertexIndexMap vertex_index,
                             ShortestPaths shortest_paths,
                             Stack& ordered_vertices,
                             typename graph_traits<Graph>::vertex_descriptor v)
  {
    using boost::detail::graph::update_centrality;

    typedef typename graph_traits<Graph>::vertex_descriptor vertex_descriptor;

    // Initialize for this iteration
    BGL_FORALL_VERTICES_T(w, g, Graph) {
      // put(path_count, w, 0);
      incoming[w].clear();
      put(dependency, w, 0);
    }

    put(path_count, v, 1);
    incoming[v].clear();

    // Execute the shortest paths algorithm. This will be either
    // Dijkstra's algorithm or a customized breadth-first search,
    // depending on whether the graph is weighted or unweighted.
    shortest_paths(g, v, ordered_vertices, incoming, distance,
                   path_count, vertex_index);
    
    while (!ordered_vertices.empty()) {
      vertex_descriptor w = ordered_vertices.top();
      ordered_vertices.pop();
      
      typedef typename property_traits<IncomingMap>::value_type
            incoming_type;
      typedef typename incoming_type::iterator incoming_iterator;
      typedef typename property_traits<DependencyMap>::value_type 
        dependency_type;
      
      for (incoming_iterator vw = incoming[w].begin();
           vw != incoming[w].end(); ++vw) {
        vertex_descriptor v = source(*vw, g);
        dependency_type factor = dependency_type(get(path_count, v))
          / dependency_type(get(path_count, w));
        factor *= (dependency_type(1) + get(dependency, w));
        put(dependency, v, get(dependency, v) + factor);
        update_centrality(edge_centrality_map, *vw, factor);
      }
      
      if (w != v) {
        update_centrality(centrality, w, get(dependency, w));
      }
    }
  }

  // Betweenness Centrality variant that duplicates graph across processors
  // and parallizes SSSPs
  // This function expects a non-distributed graph and property-maps
  template<typename ProcessGroup, typename Graph, 
           typename CentralityMap, typename EdgeCentralityMap,
           typename IncomingMap, typename DistanceMap, 
           typename DependencyMap, typename PathCountMap,
           typename VertexIndexMap, typename ShortestPaths,
           typename Buffer>
  void
  non_distributed_brandes_betweenness_centrality_impl(const ProcessGroup& pg,
                                                      const Graph& g,
                                                      CentralityMap centrality,
                                                      EdgeCentralityMap edge_centrality_map,
                                                      IncomingMap incoming, // P
                                                      DistanceMap distance,         // d
                                                      DependencyMap dependency,     // delta
                                                      PathCountMap path_count,      // sigma
                                                      VertexIndexMap vertex_index,
                                                      ShortestPaths shortest_paths,
                                                      Buffer sources)
  {
    using boost::detail::graph::init_centrality_map;
    using boost::detail::graph::divide_centrality_by_two;       
    using boost::graph::parallel::process_group;

    typedef typename graph_traits<Graph>::vertex_descriptor vertex_descriptor;

    typedef ProcessGroup process_group_type;

    typename process_group_type::process_id_type id = process_id(pg);
    typename process_group_type::process_size_type p = num_processes(pg);

    // Initialize centrality
    init_centrality_map(vertices(g), centrality);
    init_centrality_map(edges(g), edge_centrality_map);

    std::stack<vertex_descriptor> ordered_vertices;

    if (!sources.empty()) {
      std::vector<vertex_descriptor> local_sources;

      for (int i = 0; i < id; ++i) if (!sources.empty()) sources.pop();
      while (!sources.empty()) {
        local_sources.push_back(sources.top());

        for (int i = 0; i < p; ++i) if (!sources.empty()) sources.pop();
      }

      // DO SSSPs
      for(size_t i = 0; i < local_sources.size(); ++i)
        do_sequential_brandes_sssp(g, centrality, edge_centrality_map, incoming,
                                   distance, dependency, path_count, vertex_index,
                                   shortest_paths, ordered_vertices, local_sources[i]);

    } else { // Exact Betweenness Centrality
      typedef typename graph_traits<Graph>::vertices_size_type vertices_size_type;
      vertices_size_type n = num_vertices(g);
      
      for (vertices_size_type i = id; i < n; i += p) {
        vertex_descriptor v = vertex(i, g);

        do_sequential_brandes_sssp(g, centrality, edge_centrality_map, incoming,
                                   distance, dependency, path_count, vertex_index,
                                   shortest_paths, ordered_vertices, v);
      }
    }

    typedef typename graph_traits<Graph>::directed_category directed_category;
    const bool is_undirected = 
      is_convertible<directed_category*, undirected_tag*>::value;
    if (is_undirected) {
      divide_centrality_by_two(vertices(g), centrality);
      divide_centrality_by_two(edges(g), edge_centrality_map);
    }

    // Merge the centrality maps by summing the values at each vertex)
    // TODO(nge): this copy-out, reduce, copy-in is lame
    typedef typename property_traits<CentralityMap>::value_type centrality_type;
    typedef typename property_traits<EdgeCentralityMap>::value_type edge_centrality_type;

    std::vector<centrality_type> centrality_v(num_vertices(g));
    std::vector<edge_centrality_type> edge_centrality_v;
    edge_centrality_v.reserve(num_edges(g));

    BGL_FORALL_VERTICES_T(v, g, Graph) {
      centrality_v[get(vertex_index, v)] = get(centrality, v);
    }
    
    // Skip when EdgeCentralityMap is a dummy_property_map
    if (!is_same<EdgeCentralityMap, dummy_property_map>::value) {
      BGL_FORALL_EDGES_T(e, g, Graph) {
        edge_centrality_v.push_back(get(edge_centrality_map, e));
      }
      // NGE: If we trust that the order of elements in the vector isn't changed in the
      //      all_reduce below then this method avoids the need for an edge index map
    }

    using boost::parallel::all_reduce;

    all_reduce(pg, &centrality_v[0], &centrality_v[centrality_v.size()],
               &centrality_v[0], std::plus<centrality_type>());

    if (edge_centrality_v.size()) 
      all_reduce(pg, &edge_centrality_v[0], &edge_centrality_v[edge_centrality_v.size()],
                 &edge_centrality_v[0], std::plus<edge_centrality_type>());

    BGL_FORALL_VERTICES_T(v, g, Graph) {
      put(centrality, v, centrality_v[get(vertex_index, v)]);
    }

    // Skip when EdgeCentralityMap is a dummy_property_map
    if (!is_same<EdgeCentralityMap, dummy_property_map>::value) {
      int i = 0;
      BGL_FORALL_EDGES_T(e, g, Graph) {
        put(edge_centrality_map, e, edge_centrality_v[i]);
        ++i;
      }
    }
  }

} } } // end namespace graph::parallel::detail

template<typename Graph, typename CentralityMap, typename EdgeCentralityMap,
         typename IncomingMap, typename DistanceMap, typename DependencyMap, 
         typename PathCountMap, typename VertexIndexMap, typename Buffer>
void 
brandes_betweenness_centrality(const Graph& g, 
                               CentralityMap centrality,
                               EdgeCentralityMap edge_centrality_map,
                               IncomingMap incoming, 
                               DistanceMap distance, 
                               DependencyMap dependency,     
                               PathCountMap path_count,   
                               VertexIndexMap vertex_index,
                               Buffer sources,
                               typename property_traits<DistanceMap>::value_type delta
                               BOOST_GRAPH_ENABLE_IF_MODELS_PARM(Graph,distributed_graph_tag))
{
  typedef typename property_traits<DistanceMap>::value_type distance_type;
  typedef static_property_map<distance_type> WeightMap;

  graph::parallel::detail::brandes_shortest_paths<WeightMap> 
    shortest_paths(delta);

  graph::parallel::detail::brandes_betweenness_centrality_impl(g, centrality, 
                                                               edge_centrality_map,
                                                               incoming, distance,
                                                               dependency, path_count,
                                                               vertex_index, 
                                                               shortest_paths,
                                                               sources);
}

template<typename Graph, typename CentralityMap, typename EdgeCentralityMap, 
         typename IncomingMap, typename DistanceMap, typename DependencyMap, 
         typename PathCountMap, typename VertexIndexMap, typename WeightMap, 
         typename Buffer>    
void 
brandes_betweenness_centrality(const Graph& g, 
                               CentralityMap centrality,
                               EdgeCentralityMap edge_centrality_map,
                               IncomingMap incoming, 
                               DistanceMap distance, 
                               DependencyMap dependency,
                               PathCountMap path_count, 
                               VertexIndexMap vertex_index,
                               Buffer sources,
                               typename property_traits<WeightMap>::value_type delta,
                               WeightMap weight_map
                               BOOST_GRAPH_ENABLE_IF_MODELS_PARM(Graph,distributed_graph_tag))
{
  graph::parallel::detail::brandes_shortest_paths<WeightMap> shortest_paths(weight_map, delta);

  graph::parallel::detail::brandes_betweenness_centrality_impl(g, centrality, 
                                                               edge_centrality_map,
                                                               incoming, distance,
                                                               dependency, path_count,
                                                               vertex_index, 
                                                               shortest_paths,
                                                               sources);
}

namespace graph { namespace parallel { namespace detail {
  template<typename Graph, typename CentralityMap, typename EdgeCentralityMap,
           typename WeightMap, typename VertexIndexMap, typename Buffer>
  void 
  brandes_betweenness_centrality_dispatch2(const Graph& g,
                                           CentralityMap centrality,
                                           EdgeCentralityMap edge_centrality_map,
                                           WeightMap weight_map,
                                           VertexIndexMap vertex_index,
                                           Buffer sources,
                                           typename property_traits<WeightMap>::value_type delta)
  {
    typedef typename graph_traits<Graph>::degree_size_type degree_size_type;
    typedef typename graph_traits<Graph>::vertex_descriptor vertex_descriptor;
    typedef typename mpl::if_c<(is_same<CentralityMap, 
                                        dummy_property_map>::value),
                                         EdgeCentralityMap, 
                               CentralityMap>::type a_centrality_map;
    typedef typename property_traits<a_centrality_map>::value_type 
      centrality_type;

    typename graph_traits<Graph>::vertices_size_type V = num_vertices(g);

    std::vector<std::vector<vertex_descriptor> > incoming(V);
    std::vector<centrality_type> distance(V);
    std::vector<centrality_type> dependency(V);
    std::vector<degree_size_type> path_count(V);

    brandes_betweenness_centrality(
      g, centrality, edge_centrality_map,
      make_iterator_property_map(incoming.begin(), vertex_index),
      make_iterator_property_map(distance.begin(), vertex_index),
      make_iterator_property_map(dependency.begin(), vertex_index),
      make_iterator_property_map(path_count.begin(), vertex_index),
      vertex_index, unwrap_ref(sources), delta,
      weight_map);
  }
  
  // TODO: Should the type of the distance and dependency map depend on the 
  //       value type of the centrality map?
  template<typename Graph, typename CentralityMap, typename EdgeCentralityMap,
           typename VertexIndexMap, typename Buffer>
  void 
  brandes_betweenness_centrality_dispatch2(const Graph& g,
                                           CentralityMap centrality,
                                           EdgeCentralityMap edge_centrality_map,
                                           VertexIndexMap vertex_index,
                                           Buffer sources,
                                           typename graph_traits<Graph>::edges_size_type delta)
  {
    typedef typename graph_traits<Graph>::degree_size_type degree_size_type;
    typedef typename graph_traits<Graph>::edges_size_type edges_size_type;
    typedef typename graph_traits<Graph>::vertex_descriptor vertex_descriptor;

    typename graph_traits<Graph>::vertices_size_type V = num_vertices(g);
    
    std::vector<std::vector<vertex_descriptor> > incoming(V);
    std::vector<edges_size_type> distance(V);
    std::vector<edges_size_type> dependency(V);
    std::vector<degree_size_type> path_count(V);

    brandes_betweenness_centrality(
      g, centrality, edge_centrality_map,
      make_iterator_property_map(incoming.begin(), vertex_index),
      make_iterator_property_map(distance.begin(), vertex_index),
      make_iterator_property_map(dependency.begin(), vertex_index),
      make_iterator_property_map(path_count.begin(), vertex_index),
      vertex_index, unwrap_ref(sources), delta); 
  }

  template<typename WeightMap>
  struct brandes_betweenness_centrality_dispatch1
  {
    template<typename Graph, typename CentralityMap, typename EdgeCentralityMap, 
             typename VertexIndexMap, typename Buffer>
    static void 
    run(const Graph& g, CentralityMap centrality, EdgeCentralityMap edge_centrality_map, 
        VertexIndexMap vertex_index, Buffer sources,
        typename property_traits<WeightMap>::value_type delta, WeightMap weight_map) 
    {
      boost::graph::parallel::detail::brandes_betweenness_centrality_dispatch2(
       g, centrality, edge_centrality_map, weight_map, vertex_index, sources, delta);
    }
  };

  template<>
  struct brandes_betweenness_centrality_dispatch1<boost::param_not_found> 
  {
    template<typename Graph, typename CentralityMap, typename EdgeCentralityMap, 
             typename VertexIndexMap, typename Buffer>
    static void 
    run(const Graph& g, CentralityMap centrality, EdgeCentralityMap edge_centrality_map, 
        VertexIndexMap vertex_index, Buffer sources,
        typename graph_traits<Graph>::edges_size_type delta,
        boost::param_not_found)
    {
      boost::graph::parallel::detail::brandes_betweenness_centrality_dispatch2(
       g, centrality, edge_centrality_map, vertex_index, sources, delta);
    }
  };

} } } // end namespace graph::parallel::detail

template<typename Graph, typename Param, typename Tag, typename Rest>
void 
brandes_betweenness_centrality(const Graph& g, 
                               const bgl_named_params<Param,Tag,Rest>& params
                               BOOST_GRAPH_ENABLE_IF_MODELS_PARM(Graph,distributed_graph_tag))
{
  typedef bgl_named_params<Param,Tag,Rest> named_params;

  typedef queue<typename graph_traits<Graph>::vertex_descriptor> queue_t;
  queue_t q;

  typedef typename get_param_type<edge_weight_t, named_params>::type ew_param;
  typedef typename detail::choose_impl_result<mpl::true_, Graph, ew_param, edge_weight_t>::type ew;
  graph::parallel::detail::brandes_betweenness_centrality_dispatch1<ew>::run(
    g, 
    choose_param(get_param(params, vertex_centrality), 
                 dummy_property_map()),
    choose_param(get_param(params, edge_centrality), 
                 dummy_property_map()),
    choose_const_pmap(get_param(params, vertex_index), g, vertex_index),
    choose_param(get_param(params, buffer_param_t()), boost::ref(q)),
    choose_param(get_param(params, lookahead_t()), 0),
    choose_const_pmap(get_param(params, edge_weight), g, edge_weight));
}

template<typename Graph, typename CentralityMap>
void 
brandes_betweenness_centrality(const Graph& g, CentralityMap centrality
                               BOOST_GRAPH_ENABLE_IF_MODELS_PARM(Graph,distributed_graph_tag))
{
  typedef queue<typename graph_traits<Graph>::vertex_descriptor> queue_t;
  queue_t q;

  boost::graph::parallel::detail::brandes_betweenness_centrality_dispatch2(
    g, centrality, dummy_property_map(), get(vertex_index, g), boost::ref(q), 0);
}

template<typename Graph, typename CentralityMap, typename EdgeCentralityMap>
void 
brandes_betweenness_centrality(const Graph& g, CentralityMap centrality,
                               EdgeCentralityMap edge_centrality_map
                               BOOST_GRAPH_ENABLE_IF_MODELS_PARM(Graph,distributed_graph_tag))
{
  typedef queue<int> queue_t;
  queue_t q;

  boost::graph::parallel::detail::brandes_betweenness_centrality_dispatch2(
    g, centrality, edge_centrality_map, get(vertex_index, g), boost::ref(q), 0);
}
  
template<typename ProcessGroup, typename Graph, typename CentralityMap, 
         typename EdgeCentralityMap, typename IncomingMap, typename DistanceMap, 
         typename DependencyMap, typename PathCountMap, typename VertexIndexMap, 
         typename Buffer>
void 
non_distributed_brandes_betweenness_centrality(const ProcessGroup& pg,
                                               const Graph& g, 
                                               CentralityMap centrality,
                                               EdgeCentralityMap edge_centrality_map,
                                               IncomingMap incoming, 
                                               DistanceMap distance, 
                                               DependencyMap dependency,     
                                               PathCountMap path_count,      
                                               VertexIndexMap vertex_index,
                                               Buffer sources)
{
  detail::graph::brandes_unweighted_shortest_paths shortest_paths;
  
  graph::parallel::detail::non_distributed_brandes_betweenness_centrality_impl(pg, g, centrality, 
                                                                               edge_centrality_map,
                                                                               incoming, distance,
                                                                               dependency, path_count,
                                                                               vertex_index, 
                                                                               shortest_paths,
                                                                               sources);
}
  
template<typename ProcessGroup, typename Graph, typename CentralityMap, 
         typename EdgeCentralityMap, typename IncomingMap, typename DistanceMap, 
         typename DependencyMap, typename PathCountMap, typename VertexIndexMap, 
         typename WeightMap, typename Buffer>
void 
non_distributed_brandes_betweenness_centrality(const ProcessGroup& pg,
                                               const Graph& g, 
                                               CentralityMap centrality,
                                               EdgeCentralityMap edge_centrality_map,
                                               IncomingMap incoming, 
                                               DistanceMap distance, 
                                               DependencyMap dependency,
                                               PathCountMap path_count, 
                                               VertexIndexMap vertex_index,
                                               WeightMap weight_map,
                                               Buffer sources)
{
  detail::graph::brandes_dijkstra_shortest_paths<WeightMap> shortest_paths(weight_map);

  graph::parallel::detail::non_distributed_brandes_betweenness_centrality_impl(pg, g, centrality, 
                                                                               edge_centrality_map,
                                                                               incoming, distance,
                                                                               dependency, path_count,
                                                                               vertex_index, 
                                                                               shortest_paths,
                                                                               sources);
}

namespace detail { namespace graph {
  template<typename ProcessGroup, typename Graph, typename CentralityMap, 
           typename EdgeCentralityMap, typename WeightMap, typename VertexIndexMap,
           typename Buffer>
  void 
  non_distributed_brandes_betweenness_centrality_dispatch2(const ProcessGroup& pg,
                                                           const Graph& g,
                                                           CentralityMap centrality,
                                                           EdgeCentralityMap edge_centrality_map,
                                                           WeightMap weight_map,
                                                           VertexIndexMap vertex_index,
                                                           Buffer sources)
  {
    typedef typename graph_traits<Graph>::degree_size_type degree_size_type;
    typedef typename graph_traits<Graph>::edge_descriptor edge_descriptor;
    typedef typename mpl::if_c<(is_same<CentralityMap, 
                                        dummy_property_map>::value),
                                         EdgeCentralityMap, 
                               CentralityMap>::type a_centrality_map;
    typedef typename property_traits<a_centrality_map>::value_type 
      centrality_type;

    typename graph_traits<Graph>::vertices_size_type V = num_vertices(g);
    
    std::vector<std::vector<edge_descriptor> > incoming(V);
    std::vector<centrality_type> distance(V);
    std::vector<centrality_type> dependency(V);
    std::vector<degree_size_type> path_count(V);

    non_distributed_brandes_betweenness_centrality(
      pg, g, centrality, edge_centrality_map,
      make_iterator_property_map(incoming.begin(), vertex_index),
      make_iterator_property_map(distance.begin(), vertex_index),
      make_iterator_property_map(dependency.begin(), vertex_index),
      make_iterator_property_map(path_count.begin(), vertex_index),
      vertex_index, weight_map, unwrap_ref(sources));
  }
  

  template<typename ProcessGroup, typename Graph, typename CentralityMap, 
           typename EdgeCentralityMap, typename VertexIndexMap, typename Buffer>
  void 
  non_distributed_brandes_betweenness_centrality_dispatch2(const ProcessGroup& pg,
                                                           const Graph& g,
                                                           CentralityMap centrality,
                                                           EdgeCentralityMap edge_centrality_map,
                                                           VertexIndexMap vertex_index,
                                                           Buffer sources)
  {
    typedef typename graph_traits<Graph>::degree_size_type degree_size_type;
    typedef typename graph_traits<Graph>::edge_descriptor edge_descriptor;
    typedef typename mpl::if_c<(is_same<CentralityMap, 
                                        dummy_property_map>::value),
                                         EdgeCentralityMap, 
                               CentralityMap>::type a_centrality_map;
    typedef typename property_traits<a_centrality_map>::value_type 
      centrality_type;

    typename graph_traits<Graph>::vertices_size_type V = num_vertices(g);
    
    std::vector<std::vector<edge_descriptor> > incoming(V);
    std::vector<centrality_type> distance(V);
    std::vector<centrality_type> dependency(V);
    std::vector<degree_size_type> path_count(V);

    non_distributed_brandes_betweenness_centrality(
      pg, g, centrality, edge_centrality_map,
      make_iterator_property_map(incoming.begin(), vertex_index),
      make_iterator_property_map(distance.begin(), vertex_index),
      make_iterator_property_map(dependency.begin(), vertex_index),
      make_iterator_property_map(path_count.begin(), vertex_index),
      vertex_index, unwrap_ref(sources));
  }

  template<typename WeightMap>
  struct non_distributed_brandes_betweenness_centrality_dispatch1
  {
    template<typename ProcessGroup, typename Graph, typename CentralityMap, 
             typename EdgeCentralityMap, typename VertexIndexMap, typename Buffer>
    static void 
    run(const ProcessGroup& pg, const Graph& g, CentralityMap centrality, 
        EdgeCentralityMap edge_centrality_map, VertexIndexMap vertex_index,
        Buffer sources, WeightMap weight_map)
    {
      non_distributed_brandes_betweenness_centrality_dispatch2(pg, g, centrality, edge_centrality_map,
                                                               weight_map, vertex_index, sources);
    }
  };

  template<>
  struct non_distributed_brandes_betweenness_centrality_dispatch1<param_not_found>
  {
    template<typename ProcessGroup, typename Graph, typename CentralityMap, 
             typename EdgeCentralityMap, typename VertexIndexMap, typename Buffer>
    static void 
    run(const ProcessGroup& pg, const Graph& g, CentralityMap centrality, 
        EdgeCentralityMap edge_centrality_map, VertexIndexMap vertex_index,
        Buffer sources, param_not_found)
    {
      non_distributed_brandes_betweenness_centrality_dispatch2(pg, g, centrality, edge_centrality_map,
                                                               vertex_index, sources);
    }
  };

} } // end namespace detail::graph

template<typename ProcessGroup, typename Graph, typename Param, typename Tag, typename Rest>
void 
non_distributed_brandes_betweenness_centrality(const ProcessGroup& pg, const Graph& g, 
                                               const bgl_named_params<Param,Tag,Rest>& params)
{
  typedef bgl_named_params<Param,Tag,Rest> named_params;

  typedef queue<int> queue_t;
  queue_t q;

  typedef typename get_param_type<edge_weight_t, named_params>::type ew_param;
  typedef typename detail::choose_impl_result<mpl::true_, Graph, ew_param, edge_weight_t>::type ew;
  detail::graph::non_distributed_brandes_betweenness_centrality_dispatch1<ew>::run(
    pg, g, 
    choose_param(get_param(params, vertex_centrality), 
                 dummy_property_map()),
    choose_param(get_param(params, edge_centrality), 
                 dummy_property_map()),
    choose_const_pmap(get_param(params, vertex_index), g, vertex_index),
    choose_param(get_param(params, buffer_param_t()),  boost::ref(q)),
    choose_const_pmap(get_param(params, edge_weight), g, edge_weight));
}

template<typename ProcessGroup, typename Graph, typename CentralityMap>
void 
non_distributed_brandes_betweenness_centrality(const ProcessGroup& pg, const Graph& g, 
                                               CentralityMap centrality)
{
  typedef queue<int> queue_t;
  queue_t q;

  detail::graph::non_distributed_brandes_betweenness_centrality_dispatch2(
    pg, g, centrality, dummy_property_map(), get(vertex_index, g), boost::ref(q));
}

template<typename ProcessGroup, typename Graph, typename CentralityMap, 
         typename Buffer>
void 
non_distributed_brandes_betweenness_centrality(const ProcessGroup& pg, const Graph& g, 
                                               CentralityMap centrality, Buffer sources)
{
  detail::graph::non_distributed_brandes_betweenness_centrality_dispatch2(
    pg, g, centrality, dummy_property_map(), get(vertex_index, g), sources);
}

template<typename ProcessGroup, typename Graph, typename CentralityMap, 
         typename EdgeCentralityMap, typename Buffer>
void 
non_distributed_brandes_betweenness_centrality(const ProcessGroup& pg, const Graph& g, 
                                               CentralityMap centrality,
                                               EdgeCentralityMap edge_centrality_map, 
                                               Buffer sources)
{
  detail::graph::non_distributed_brandes_betweenness_centrality_dispatch2(
    pg, g, centrality, edge_centrality_map, get(vertex_index, g), sources);
}

// Compute the central point dominance of a graph.
// TODO: Make sure central point dominance works in parallel case
template<typename Graph, typename CentralityMap>
typename property_traits<CentralityMap>::value_type
central_point_dominance(const Graph& g, CentralityMap centrality
                        BOOST_GRAPH_ENABLE_IF_MODELS_PARM(Graph,distributed_graph_tag))
{
  using std::max;

  typedef typename graph_traits<Graph>::vertex_iterator vertex_iterator;
  typedef typename property_traits<CentralityMap>::value_type centrality_type;
  typedef typename graph_traits<Graph>::vertices_size_type vertices_size_type;

  typedef typename boost::graph::parallel::process_group_type<Graph>::type 
    process_group_type;
  process_group_type pg = boost::graph::parallel::process_group(g);

  vertices_size_type n = num_vertices(g);

  using boost::parallel::all_reduce;  
  n = all_reduce(pg, n, std::plus<vertices_size_type>());

  // Find max centrality
  centrality_type max_centrality(0);
  vertex_iterator v, v_end;
  for (boost::tie(v, v_end) = vertices(g); v != v_end; ++v) {
    max_centrality = (max)(max_centrality, get(centrality, *v));
  }

  // All reduce to get global max centrality
  max_centrality = all_reduce(pg, max_centrality, boost::parallel::maximum<centrality_type>());

  // Compute central point dominance
  centrality_type sum(0);
  for (boost::tie(v, v_end) = vertices(g); v != v_end; ++v) {
    sum += (max_centrality - get(centrality, *v));
  }

  sum = all_reduce(pg, sum, std::plus<centrality_type>());

  return sum/(n-1);
}

} // end namespace boost

#endif // BOOST_GRAPH_PARALLEL_BRANDES_BETWEENNESS_CENTRALITY_HPP

/* betweenness_centrality.hpp
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
*/