// Copyright (C) 2004-2006 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine

/**
 * This header implements four distributed algorithms to compute
 * the minimum spanning tree (actually, minimum spanning forest) of a
 * graph. All of the algorithms were implemented as specified in the
 * paper by Dehne and Gotz:
 *
 *   Frank Dehne and Silvia Gotz. Practical Parallel Algorithms for Minimum
 *   Spanning Trees. In Symposium on Reliable Distributed Systems,
 *   pages 366--371, 1998.
 *
 * There are four algorithm variants implemented.
 */

#ifndef BOOST_DEHNE_GOTZ_MIN_SPANNING_TREE_HPP
#define BOOST_DEHNE_GOTZ_MIN_SPANNING_TREE_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>
#include <vector>
#include <boost/graph/parallel/algorithm.hpp>
#include <boost/limits.hpp>
#include <utility>
#include <boost/pending/disjoint_sets.hpp>
#include <boost/pending/indirect_cmp.hpp>
#include <boost/property_map/parallel/caching_property_map.hpp>
#include <boost/graph/vertex_and_edge_range.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/iterator/counting_iterator.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/graph/parallel/container_traits.hpp>
#include <boost/graph/parallel/detail/untracked_pair.hpp>
#include <cmath>

namespace boost { namespace graph { namespace distributed {

namespace detail {
  /**
   * Binary function object type that selects the (edge, weight) pair
   * with the minimum weight. Used within a Boruvka merge step to select
   * the candidate edges incident to each supervertex.
   */
  struct smaller_weighted_edge
  {
    template<typename Edge, typename Weight>
    std::pair<Edge, Weight>
    operator()(const std::pair<Edge, Weight>& x,
               const std::pair<Edge, Weight>& y) const
    { return x.second < y.second? x : y; }
  };

  /**
   * Unary predicate that determines if the source and target vertices
   * of the given edge have the same representative within a disjoint
   * sets data structure. Used to indicate when an edge is now a
   * self-loop because of supervertex merging in Boruvka's algorithm.
   */
  template<typename DisjointSets, typename Graph>
  class do_has_same_supervertex
  {
  public:
    typedef typename graph_traits<Graph>::edge_descriptor edge_descriptor;

    do_has_same_supervertex(DisjointSets& dset, const Graph& g)
      : dset(dset), g(g) { }

    bool operator()(edge_descriptor e)
    { return dset.find_set(source(e, g)) == dset.find_set(target(e, g));    }

  private:
    DisjointSets&  dset;
    const Graph&   g;
  };

  /**
   * Build a @ref do_has_same_supervertex object.
   */
  template<typename DisjointSets, typename Graph>
  inline do_has_same_supervertex<DisjointSets, Graph>
  has_same_supervertex(DisjointSets& dset, const Graph& g)
  { return do_has_same_supervertex<DisjointSets, Graph>(dset, g); }

  /** \brief A single distributed Boruvka merge step.
   *
   * A distributed Boruvka merge step involves computing (globally)
   * the minimum weight edges incident on each supervertex and then
   * merging supervertices along these edges. Once supervertices are
   * merged, self-loops are eliminated.
   *
   * The set of parameters passed to this algorithm is large, and
   * considering this algorithm in isolation there are several
   * redundancies. However, the more asymptotically efficient
   * distributed MSF algorithms require mixing Boruvka steps with the
   * merging of local MSFs (implemented in
   * merge_local_minimum_spanning_trees_step): the interaction of the
   * two algorithms mandates the addition of these parameters.
   *
   * \param pg The process group over which communication should be
   * performed. Within the distributed Boruvka algorithm, this will be
   * equivalent to \code process_group(g); however, in the context of
   * the mixed MSF algorithms, the process group @p pg will be a
   * (non-strict) process subgroup of \code process_group(g).
   *
   * \param g The underlying graph on which the MSF is being
   * computed. The type of @p g must model DistributedGraph, but there
   * are no other requirements because the edge and (super)vertex
   * lists are passed separately.
   *
   * \param weight_map Property map containing the weights of each
   * edge. The type of this property map must model
   * ReadablePropertyMap and must support caching.
   *
   * \param out An output iterator that will be written with the set
   * of edges selected to build the MSF. Every process within the
   * process group @p pg will receive all edges in the MSF.
   *
   * \param dset Disjoint sets data structure mapping from vertices in
   * the graph @p g to their representative supervertex.
   *
   * \param supervertex_map Mapping from supervertex descriptors to
   * indices.
   *
   * \param supervertices A vector containing all of the
   * supervertices. Will be modified to include only the remaining
   * supervertices after merging occurs.
   *
   * \param edge_list The list of edges that remain in the graph. This
   * list will be pruned to remove self-loops once MSF edges have been
   * found.
   */
  template<typename ProcessGroup, typename Graph, typename WeightMap,
           typename OutputIterator, typename RankMap, typename ParentMap,
           typename SupervertexMap, typename Vertex, typename EdgeList>
  OutputIterator
  boruvka_merge_step(ProcessGroup pg, const Graph& g, WeightMap weight_map,
                     OutputIterator out,
                     disjoint_sets<RankMap, ParentMap>& dset,
                     SupervertexMap supervertex_map,
                     std::vector<Vertex>& supervertices,
                     EdgeList& edge_list)
  {
    typedef typename graph_traits<Graph>::vertex_descriptor
                                                           vertex_descriptor;
    typedef typename graph_traits<Graph>::vertices_size_type
                                                           vertices_size_type;
    typedef typename graph_traits<Graph>::edge_descriptor  edge_descriptor;
    typedef typename EdgeList::iterator                    edge_iterator;
    typedef typename property_traits<WeightMap>::value_type
                                                           weight_type;
    typedef boost::parallel::detail::untracked_pair<edge_descriptor, 
                                       weight_type>        w_edge;
    typedef typename property_traits<SupervertexMap>::value_type
                                                           supervertex_index;

    smaller_weighted_edge min_edge;
    weight_type inf = (std::numeric_limits<weight_type>::max)();

    // Renumber the supervertices
    for (std::size_t i = 0; i < supervertices.size(); ++i)
      put(supervertex_map, supervertices[i], i);

    // BSP-B1: Find local minimum-weight edges for each supervertex
    std::vector<w_edge> candidate_edges(supervertices.size(),
                                        w_edge(edge_descriptor(), inf));
    for (edge_iterator ei = edge_list.begin(); ei != edge_list.end(); ++ei) {
      weight_type w = get(weight_map, *ei);
      supervertex_index u =
        get(supervertex_map, dset.find_set(source(*ei, g)));
      supervertex_index v =
        get(supervertex_map, dset.find_set(target(*ei, g)));

      if (u != v) {
        candidate_edges[u] = min_edge(candidate_edges[u], w_edge(*ei, w));
        candidate_edges[v] = min_edge(candidate_edges[v], w_edge(*ei, w));
      }
    }

    // BSP-B2 (a): Compute global minimum edges for each supervertex
    all_reduce(pg,
               &candidate_edges[0],
               &candidate_edges[0] + candidate_edges.size(),
               &candidate_edges[0], min_edge);

    // BSP-B2 (b): Use the edges to compute sequentially the new
    // connected components and emit the edges.
    for (vertices_size_type i = 0; i < candidate_edges.size(); ++i) {
      if (candidate_edges[i].second != inf) {
        edge_descriptor e = candidate_edges[i].first;
        vertex_descriptor u = dset.find_set(source(e, g));
        vertex_descriptor v = dset.find_set(target(e, g));
        if (u != v) {
          // Emit the edge, but cache the weight so everyone knows it
          cache(weight_map, e, candidate_edges[i].second);
          *out++ = e;

          // Link the two supervertices
          dset.link(u, v);

          // Whichever vertex was reparented will be removed from the
          // list of supervertices.
          vertex_descriptor victim = u;
          if (dset.find_set(u) == u) victim = v;
          supervertices[get(supervertex_map, victim)] =
            graph_traits<Graph>::null_vertex();
        }
      }
    }

    // BSP-B3: Eliminate self-loops
    edge_list.erase(std::remove_if(edge_list.begin(), edge_list.end(),
                                   has_same_supervertex(dset, g)),
                    edge_list.end());

    // TBD: might also eliminate multiple edges between supervertices
    // when the edges do not have the best weight, but this is not
    // strictly necessary.

    // Eliminate supervertices that have been absorbed
    supervertices.erase(std::remove(supervertices.begin(),
                                    supervertices.end(),
                                    graph_traits<Graph>::null_vertex()),
                        supervertices.end());

    return out;
  }

  /**
   * An edge descriptor adaptor that reroutes the source and target
   * edges to different vertices, but retains the original edge
   * descriptor for, e.g., property maps. This is used when we want to
   * turn a set of edges in the overall graph into a set of edges
   * between supervertices.
   */
  template<typename Graph>
  struct supervertex_edge_descriptor
  {
    typedef supervertex_edge_descriptor self_type;
    typedef typename graph_traits<Graph>::vertex_descriptor Vertex;
    typedef typename graph_traits<Graph>::edge_descriptor Edge;

    Vertex source;
    Vertex target;
    Edge e;

    operator Edge() const { return e; }

    friend inline bool operator==(const self_type& x, const self_type& y)
    { return x.e == y.e; }

    friend inline bool operator!=(const self_type& x, const self_type& y)
    { return x.e != y.e; }
  };

  template<typename Graph>
  inline typename supervertex_edge_descriptor<Graph>::Vertex
  source(supervertex_edge_descriptor<Graph> se, const Graph&)
  { return se.source; }

  template<typename Graph>
  inline typename supervertex_edge_descriptor<Graph>::Vertex
  target(supervertex_edge_descriptor<Graph> se, const Graph&)
  { return se.target; }

  /**
   * Build a supervertex edge descriptor from a normal edge descriptor
   * using the given disjoint sets data structure to identify
   * supervertex representatives.
   */
  template<typename Graph, typename DisjointSets>
  struct build_supervertex_edge_descriptor
  {
    typedef typename graph_traits<Graph>::vertex_descriptor Vertex;
    typedef typename graph_traits<Graph>::edge_descriptor   Edge;

    typedef Edge argument_type;
    typedef supervertex_edge_descriptor<Graph> result_type;

    build_supervertex_edge_descriptor() : g(0), dsets(0) { }

    build_supervertex_edge_descriptor(const Graph& g, DisjointSets& dsets)
      : g(&g), dsets(&dsets) { }

    result_type operator()(argument_type e) const
    {
      result_type result;
      result.source = dsets->find_set(source(e, *g));
      result.target = dsets->find_set(target(e, *g));
      result.e = e;
      return result;
    }

  private:
    const Graph* g;
    DisjointSets* dsets;
  };

  template<typename Graph, typename DisjointSets>
  inline build_supervertex_edge_descriptor<Graph, DisjointSets>
  make_supervertex_edge_descriptor(const Graph& g, DisjointSets& dsets)
  { return build_supervertex_edge_descriptor<Graph, DisjointSets>(g, dsets); }

  template<typename T>
  struct identity_function
  {
    typedef T argument_type;
    typedef T result_type;

    result_type operator()(argument_type x) const { return x; }
  };

  template<typename Graph, typename DisjointSets, typename EdgeMapper>
  class is_not_msf_edge
  {
    typedef typename graph_traits<Graph>::vertex_descriptor Vertex;
    typedef typename graph_traits<Graph>::edge_descriptor Edge;

  public:
    is_not_msf_edge(const Graph& g, DisjointSets dset, EdgeMapper edge_mapper)
      : g(g), dset(dset), edge_mapper(edge_mapper) { }

    bool operator()(Edge e)
    {
      Vertex u = dset.find_set(source(edge_mapper(e), g));
      Vertex v = dset.find_set(target(edge_mapper(e), g));
      if (u == v) return true;
      else {
        dset.link(u, v);
        return false;
      }
    }

  private:
    const Graph& g;
    DisjointSets dset;
    EdgeMapper edge_mapper;
  };

  template<typename Graph, typename ForwardIterator, typename EdgeList,
           typename EdgeMapper, typename RankMap, typename ParentMap>
  void
  sorted_mutating_kruskal(const Graph& g,
                          ForwardIterator first_vertex,
                          ForwardIterator last_vertex,
                          EdgeList& edge_list, EdgeMapper edge_mapper,
                          RankMap rank_map, ParentMap parent_map)
  {
    typedef disjoint_sets<RankMap, ParentMap> DisjointSets;

    // Build and initialize disjoint-sets data structure
    DisjointSets dset(rank_map, parent_map);
    for (ForwardIterator v = first_vertex; v != last_vertex; ++v)
      dset.make_set(*v);

    is_not_msf_edge<Graph, DisjointSets, EdgeMapper>
      remove_non_msf_edges(g, dset, edge_mapper);
    edge_list.erase(std::remove_if(edge_list.begin(), edge_list.end(),
                                   remove_non_msf_edges),
                    edge_list.end());
  }

  /**
   * Merge local minimum spanning forests from p processes into
   * minimum spanning forests on p/D processes (where D is the tree
   * factor, currently fixed at 3), eliminating unnecessary edges in
   * the process.
   *
   * As with @ref boruvka_merge_step, this routine has many
   * parameters, not all of which make sense within the limited
   * context of this routine. The parameters are required for the
   * Boruvka and local MSF merging steps to interoperate.
   *
   * \param pg The process group on which local minimum spanning
   * forests should be merged. The top (D-1)p/D processes will be
   * eliminated, and a new process subgroup containing p/D processors
   * will be returned. The value D is a constant factor that is
   * currently fixed to 3.
   *
   * \param g The underlying graph whose MSF is being computed. It must model
   * the DistributedGraph concept.
   *
   * \param first_vertex Iterator to the first vertex in the graph
   * that should be considered. While the local MSF merging algorithm
   * typically operates on the entire vertex set, within the hybrid
   * distributed MSF algorithms this will refer to the first
   * supervertex.
   *
   * \param last_vertex The past-the-end iterator for the vertex list.
   *
   * \param edge_list The list of local edges that will be
   * considered. For the p/D processes that remain, this list will
   * contain edges in the MSF known to the vertex after other
   * processes' edge lists have been merged. The edge list must be
   * sorted in order of increasing weight.
   *
   * \param weight Property map containing the weights of each
   * edge. The type of this property map must model
   * ReadablePropertyMap and must support caching.
   *
   * \param global_index Mapping from vertex descriptors to a global
   * index. The type must model ReadablePropertyMap.
   *
   * \param edge_mapper A function object that can remap edge descriptors
   * in the edge list to any alternative edge descriptor. This
   * function object will be the identity function when a pure merging
   * of local MSFs is required, but may be a mapping to a supervertex
   * edge when the local MSF merging occurs on a supervertex
   * graph. This function object saves us the trouble of having to
   * build a supervertex graph adaptor.
   *
   * \param already_local_msf True when the edge list already
   * constitutes a local MSF. If false, Kruskal's algorithm will first
   * be applied to the local edge list to select MSF edges.
   *
   * \returns The process subgroup containing the remaining p/D
   * processes. If the size of this process group is greater than one,
   * the MSF edges contained in the edge list do not constitute an MSF
   * for the entire graph.
   */
  template<typename ProcessGroup, typename Graph, typename ForwardIterator,
           typename EdgeList, typename WeightMap, typename GlobalIndexMap,
           typename EdgeMapper>
  ProcessGroup
  merge_local_minimum_spanning_trees_step(ProcessGroup pg,
                                          const Graph& g,
                                          ForwardIterator first_vertex,
                                          ForwardIterator last_vertex,
                                          EdgeList& edge_list,
                                          WeightMap weight,
                                          GlobalIndexMap global_index,
                                          EdgeMapper edge_mapper,
                                          bool already_local_msf)
  {
    typedef typename ProcessGroup::process_id_type process_id_type;
    typedef typename EdgeList::value_type edge_descriptor;
    typedef typename property_traits<WeightMap>::value_type weight_type;
    typedef typename graph_traits<Graph>::vertex_descriptor vertex_descriptor;

    // The tree factor, often called "D"
    process_id_type const tree_factor = 3;
    process_id_type num_procs = num_processes(pg);
    process_id_type id = process_id(pg);
    process_id_type procs_left = (num_procs + tree_factor - 1) / tree_factor;
    std::size_t n = std::size_t(last_vertex - first_vertex);

    if (!already_local_msf) {
      // Compute local minimum spanning forest. We only care about the
      // edges in the MSF, because only edges in the local MSF can be in
      // the global MSF.
      std::vector<std::size_t> ranks(n);
      std::vector<vertex_descriptor> parents(n);
      detail::sorted_mutating_kruskal
        (g, first_vertex, last_vertex,
         edge_list, edge_mapper,
         make_iterator_property_map(ranks.begin(), global_index),
         make_iterator_property_map(parents.begin(), global_index));
    }

    typedef std::pair<edge_descriptor, weight_type> w_edge;

    // Order edges based on their weights.
    indirect_cmp<WeightMap, std::less<weight_type> > cmp_edge_weight(weight);

    if (id < procs_left) {
      // The p/D processes that remain will receive local MSF edges from
      // D-1 other processes.
      synchronize(pg);
      for (process_id_type from_id = procs_left + id; from_id < num_procs;
           from_id += procs_left) {
        std::size_t num_incoming_edges;
        receive(pg, from_id, 0, num_incoming_edges);
        if (num_incoming_edges > 0) {
          std::vector<w_edge> incoming_edges(num_incoming_edges);
          receive(pg, from_id, 1, &incoming_edges[0], num_incoming_edges);

          edge_list.reserve(edge_list.size() + num_incoming_edges);
          for (std::size_t i = 0; i < num_incoming_edges; ++i) {
            cache(weight, incoming_edges[i].first, incoming_edges[i].second);
            edge_list.push_back(incoming_edges[i].first);
          }
          std::inplace_merge(edge_list.begin(),
                             edge_list.end() - num_incoming_edges,
                             edge_list.end(),
                             cmp_edge_weight);
        }
      }

      // Compute the local MSF from union of the edges in the MSFs of
      // all children.
      std::vector<std::size_t> ranks(n);
      std::vector<vertex_descriptor> parents(n);
      detail::sorted_mutating_kruskal
        (g, first_vertex, last_vertex,
         edge_list, edge_mapper,
         make_iterator_property_map(ranks.begin(), global_index),
         make_iterator_property_map(parents.begin(), global_index));
    } else {
      // The (D-1)p/D processes that are dropping out of further
      // computations merely send their MSF edges to their parent
      // process in the process tree.
      send(pg, id % procs_left, 0, edge_list.size());
      if (edge_list.size() > 0) {
        std::vector<w_edge> outgoing_edges;
        outgoing_edges.reserve(edge_list.size());
        for (std::size_t i = 0; i < edge_list.size(); ++i) {
          outgoing_edges.push_back(std::make_pair(edge_list[i],
                                                  get(weight, edge_list[i])));
        }
        send(pg, id % procs_left, 1, &outgoing_edges[0],
             outgoing_edges.size());
      }
      synchronize(pg);
    }

    // Return a process subgroup containing the p/D parent processes
    return process_subgroup(pg,
                            make_counting_iterator(process_id_type(0)),
                            make_counting_iterator(procs_left));
  }
} // end namespace detail

// ---------------------------------------------------------------------
// Dense Boruvka MSF algorithm
// ---------------------------------------------------------------------
template<typename Graph, typename WeightMap, typename OutputIterator,
         typename VertexIndexMap, typename RankMap, typename ParentMap,
         typename SupervertexMap>
OutputIterator
dense_boruvka_minimum_spanning_tree(const Graph& g, WeightMap weight_map,
                                    OutputIterator out,
                                    VertexIndexMap index_map,
                                    RankMap rank_map, ParentMap parent_map,
                                    SupervertexMap supervertex_map)
{
  using boost::graph::parallel::process_group;

  typedef typename graph_traits<Graph>::traversal_category traversal_category;

  BOOST_STATIC_ASSERT((is_convertible<traversal_category*,
                                      vertex_list_graph_tag*>::value));

  typedef typename graph_traits<Graph>::vertices_size_type vertices_size_type;
  typedef typename graph_traits<Graph>::vertex_descriptor  vertex_descriptor;
  typedef typename graph_traits<Graph>::vertex_iterator    vertex_iterator;
  typedef typename graph_traits<Graph>::edge_descriptor    edge_descriptor;

  // Don't throw away cached edge weights
  weight_map.set_max_ghost_cells(0);

  // Initialize the disjoint sets structures
  disjoint_sets<RankMap, ParentMap> dset(rank_map, parent_map);
  vertex_iterator vi, vi_end;
  for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
    dset.make_set(*vi);

  std::vector<vertex_descriptor> supervertices;
  supervertices.assign(vertices(g).first, vertices(g).second);

  // Use Kruskal's algorithm to find the minimum spanning forest
  // considering only the local edges. The resulting edges are not
  // necessarily going to be in the final minimum spanning
  // forest. However, any edge not part of the local MSF cannot be a
  // part of the global MSF, so we should have eliminated some edges
  // from consideration.
  std::vector<edge_descriptor> edge_list;
  kruskal_minimum_spanning_tree
    (make_vertex_and_edge_range(g, vertices(g).first, vertices(g).second,
                                edges(g).first, edges(g).second),
     std::back_inserter(edge_list),
     boost::weight_map(weight_map).
     vertex_index_map(index_map));

  // While the number of supervertices is decreasing, keep executing
  // Boruvka steps to identify additional MSF edges. This loop will
  // execute log |V| times.
  vertices_size_type old_num_supervertices;
  do {
    old_num_supervertices = supervertices.size();
    out = detail::boruvka_merge_step(process_group(g), g,
                                     weight_map, out,
                                     dset, supervertex_map, supervertices,
                                     edge_list);
  } while (supervertices.size() < old_num_supervertices);

  return out;
}

template<typename Graph, typename WeightMap, typename OutputIterator,
         typename VertexIndex>
OutputIterator
dense_boruvka_minimum_spanning_tree(const Graph& g, WeightMap weight_map,
                                    OutputIterator out, VertexIndex i_map)
{
  typedef typename graph_traits<Graph>::vertex_descriptor vertex_descriptor;

  std::vector<std::size_t> ranks(num_vertices(g));
  std::vector<vertex_descriptor> parents(num_vertices(g));
  std::vector<std::size_t> supervertices(num_vertices(g));

  return dense_boruvka_minimum_spanning_tree
           (g, weight_map, out, i_map,
            make_iterator_property_map(ranks.begin(), i_map),
            make_iterator_property_map(parents.begin(), i_map),
            make_iterator_property_map(supervertices.begin(), i_map));
}

template<typename Graph, typename WeightMap, typename OutputIterator>
OutputIterator
dense_boruvka_minimum_spanning_tree(const Graph& g, WeightMap weight_map,
                                    OutputIterator out)
{
  return dense_boruvka_minimum_spanning_tree(g, weight_map, out,
                                             get(vertex_index, g));
}

// ---------------------------------------------------------------------
// Merge local MSFs MSF algorithm
// ---------------------------------------------------------------------
template<typename Graph, typename WeightMap, typename OutputIterator,
         typename GlobalIndexMap>
OutputIterator
merge_local_minimum_spanning_trees(const Graph& g, WeightMap weight,
                                   OutputIterator out,
                                   GlobalIndexMap global_index)
{
  using boost::graph::parallel::process_group_type;
  using boost::graph::parallel::process_group;

  typedef typename graph_traits<Graph>::traversal_category traversal_category;

  BOOST_STATIC_ASSERT((is_convertible<traversal_category*,
                                      vertex_list_graph_tag*>::value));

  typedef typename graph_traits<Graph>::edge_descriptor edge_descriptor;

  // Don't throw away cached edge weights
  weight.set_max_ghost_cells(0);

  // Compute the initial local minimum spanning forests
  std::vector<edge_descriptor> edge_list;
  kruskal_minimum_spanning_tree
    (make_vertex_and_edge_range(g, vertices(g).first, vertices(g).second,
                                edges(g).first, edges(g).second),
     std::back_inserter(edge_list),
     boost::weight_map(weight).vertex_index_map(global_index));

  // Merge the local MSFs from p processes into p/D processes,
  // reducing the number of processes in each step. Continue looping
  // until either (a) the current process drops out or (b) only one
  // process remains in the group. This loop will execute log_D p
  // times.
  typename process_group_type<Graph>::type pg = process_group(g);
  while (pg && num_processes(pg) > 1) {
    pg = detail::merge_local_minimum_spanning_trees_step
           (pg, g, vertices(g).first, vertices(g).second,
            edge_list, weight, global_index,
            detail::identity_function<edge_descriptor>(), true);
  }

  // Only process 0 has the entire edge list, so emit it to the output
  // iterator.
  if (pg && process_id(pg) == 0) {
    out = std::copy(edge_list.begin(), edge_list.end(), out);
  }

  synchronize(process_group(g));
  return out;
}

template<typename Graph, typename WeightMap, typename OutputIterator>
inline OutputIterator
merge_local_minimum_spanning_trees(const Graph& g, WeightMap weight,
                                   OutputIterator out)
{
  return merge_local_minimum_spanning_trees(g, weight, out,
                                            get(vertex_index, g));
}

// ---------------------------------------------------------------------
// Boruvka-then-merge MSF algorithm
// ---------------------------------------------------------------------
template<typename Graph, typename WeightMap, typename OutputIterator,
         typename GlobalIndexMap, typename RankMap, typename ParentMap,
         typename SupervertexMap>
OutputIterator
boruvka_then_merge(const Graph& g, WeightMap weight, OutputIterator out,
                   GlobalIndexMap index, RankMap rank_map,
                   ParentMap parent_map, SupervertexMap supervertex_map)
{
  using std::log;
  using boost::graph::parallel::process_group_type;
  using boost::graph::parallel::process_group;

  typedef typename graph_traits<Graph>::traversal_category traversal_category;

  BOOST_STATIC_ASSERT((is_convertible<traversal_category*,
                                      vertex_list_graph_tag*>::value));

  typedef typename graph_traits<Graph>::vertices_size_type vertices_size_type;
  typedef typename graph_traits<Graph>::vertex_descriptor  vertex_descriptor;
  typedef typename graph_traits<Graph>::vertex_iterator    vertex_iterator;
  typedef typename graph_traits<Graph>::edge_descriptor    edge_descriptor;

  // Don't throw away cached edge weights
  weight.set_max_ghost_cells(0);

  // Compute the initial local minimum spanning forests
  std::vector<edge_descriptor> edge_list;
  kruskal_minimum_spanning_tree
    (make_vertex_and_edge_range(g, vertices(g).first, vertices(g).second,
                                edges(g).first, edges(g).second),
     std::back_inserter(edge_list),
     boost::weight_map(weight).
     vertex_index_map(index));

  // Initialize the disjoint sets structures for Boruvka steps
  disjoint_sets<RankMap, ParentMap> dset(rank_map, parent_map);
  vertex_iterator vi, vi_end;
  for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
    dset.make_set(*vi);

  // Construct the initial set of supervertices (all vertices)
  std::vector<vertex_descriptor> supervertices;
  supervertices.assign(vertices(g).first, vertices(g).second);

  // Continue performing Boruvka merge steps until the number of
  // supervertices reaches |V| / (log_D p)^2.
  const std::size_t tree_factor = 3; // TBD: same as above! should be param
  double log_d_p = log((double)num_processes(process_group(g)))
                 / log((double)tree_factor);
  vertices_size_type target_supervertices =
    vertices_size_type(num_vertices(g) / (log_d_p * log_d_p));
  vertices_size_type old_num_supervertices;
  while (supervertices.size() > target_supervertices) {
    old_num_supervertices = supervertices.size();
    out = detail::boruvka_merge_step(process_group(g), g,
                                     weight, out, dset,
                                     supervertex_map, supervertices,
                                     edge_list);
    if (supervertices.size() == old_num_supervertices)
      return out;
  }

  // Renumber the supervertices
  for (std::size_t i = 0; i < supervertices.size(); ++i)
    put(supervertex_map, supervertices[i], i);

  // Merge local MSFs on the supervertices. (D-1)p/D processors drop
  // out each iteration, so this loop executes log_D p times.
  typename process_group_type<Graph>::type pg = process_group(g);
  bool have_msf = false;
  while (pg && num_processes(pg) > 1) {
    pg = detail::merge_local_minimum_spanning_trees_step
           (pg, g, supervertices.begin(), supervertices.end(),
            edge_list, weight, supervertex_map,
            detail::make_supervertex_edge_descriptor(g, dset),
            have_msf);
    have_msf = true;
  }

  // Only process 0 has the complete list of _supervertex_ MST edges,
  // so emit those to the output iterator. This is not the complete
  // list of edges in the MSF, however: the Boruvka steps in the
  // beginning of the algorithm emitted any edges used to merge
  // supervertices.
  if (pg && process_id(pg) == 0)
    out = std::copy(edge_list.begin(), edge_list.end(), out);

  synchronize(process_group(g));
  return out;
}

template<typename Graph, typename WeightMap, typename OutputIterator,
         typename GlobalIndexMap>
inline OutputIterator
boruvka_then_merge(const Graph& g, WeightMap weight, OutputIterator out,
                    GlobalIndexMap index)
{
  typedef typename graph_traits<Graph>::vertex_descriptor vertex_descriptor;
  typedef typename graph_traits<Graph>::vertices_size_type vertices_size_type;
  std::vector<vertices_size_type> ranks(num_vertices(g));
  std::vector<vertex_descriptor> parents(num_vertices(g));
  std::vector<vertices_size_type> supervertex_indices(num_vertices(g));

  return boruvka_then_merge
           (g, weight, out, index,
            make_iterator_property_map(ranks.begin(), index),
            make_iterator_property_map(parents.begin(), index),
            make_iterator_property_map(supervertex_indices.begin(), index));
}

template<typename Graph, typename WeightMap, typename OutputIterator>
inline OutputIterator
boruvka_then_merge(const Graph& g, WeightMap weight, OutputIterator out)
{ return boruvka_then_merge(g, weight, out, get(vertex_index, g)); }

// ---------------------------------------------------------------------
// Boruvka-mixed-merge MSF algorithm
// ---------------------------------------------------------------------
template<typename Graph, typename WeightMap, typename OutputIterator,
         typename GlobalIndexMap, typename RankMap, typename ParentMap,
         typename SupervertexMap>
OutputIterator
boruvka_mixed_merge(const Graph& g, WeightMap weight, OutputIterator out,
                    GlobalIndexMap index, RankMap rank_map,
                    ParentMap parent_map, SupervertexMap supervertex_map)
{
  using boost::graph::parallel::process_group_type;
  using boost::graph::parallel::process_group;

  typedef typename graph_traits<Graph>::traversal_category traversal_category;

  BOOST_STATIC_ASSERT((is_convertible<traversal_category*,
                                      vertex_list_graph_tag*>::value));

  typedef typename graph_traits<Graph>::vertices_size_type vertices_size_type;
  typedef typename graph_traits<Graph>::vertex_descriptor  vertex_descriptor;
  typedef typename graph_traits<Graph>::vertex_iterator    vertex_iterator;
  typedef typename graph_traits<Graph>::edge_descriptor    edge_descriptor;

  // Don't throw away cached edge weights
  weight.set_max_ghost_cells(0);

  // Initialize the disjoint sets structures for Boruvka steps
  disjoint_sets<RankMap, ParentMap> dset(rank_map, parent_map);
  vertex_iterator vi, vi_end;
  for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
    dset.make_set(*vi);

  // Construct the initial set of supervertices (all vertices)
  std::vector<vertex_descriptor> supervertices;
  supervertices.assign(vertices(g).first, vertices(g).second);

  // Compute the initial local minimum spanning forests
  std::vector<edge_descriptor> edge_list;
  kruskal_minimum_spanning_tree
    (make_vertex_and_edge_range(g, vertices(g).first, vertices(g).second,
                                edges(g).first, edges(g).second),
     std::back_inserter(edge_list),
     boost::weight_map(weight).
     vertex_index_map(index));

  if (num_processes(process_group(g)) == 1) {
    return std::copy(edge_list.begin(), edge_list.end(), out);
  }

  // Like the merging local MSFs algorithm and the Boruvka-then-merge
  // algorithm, each iteration of this loop reduces the number of
  // processes by a constant factor D, and therefore we require log_D
  // p iterations. Note also that the number of edges in the edge list
  // decreases geometrically, giving us an efficient distributed MSF
  // algorithm.
  typename process_group_type<Graph>::type pg = process_group(g);
  vertices_size_type old_num_supervertices;
  while (pg && num_processes(pg) > 1) {
    // A single Boruvka step. If this doesn't change anything, we're done
    old_num_supervertices = supervertices.size();
    out = detail::boruvka_merge_step(pg, g, weight, out, dset,
                                     supervertex_map, supervertices,
                                     edge_list);
    if (old_num_supervertices == supervertices.size()) {
      edge_list.clear();
      break;
    }

    // Renumber the supervertices
    for (std::size_t i = 0; i < supervertices.size(); ++i)
      put(supervertex_map, supervertices[i], i);

    // A single merging of local MSTs, which reduces the number of
    // processes we're using by a constant factor D.
    pg = detail::merge_local_minimum_spanning_trees_step
           (pg, g, supervertices.begin(), supervertices.end(),
            edge_list, weight, supervertex_map,
            detail::make_supervertex_edge_descriptor(g, dset),
            true);

  }

  // Only process 0 has the complete edge list, so emit it for the
  // user. Note that list edge list only contains the MSF edges in the
  // final supervertex graph: all of the other edges were used to
  // merge supervertices and have been emitted by the Boruvka steps,
  // although only process 0 has received the complete set.
  if (pg && process_id(pg) == 0)
    out = std::copy(edge_list.begin(), edge_list.end(), out);

  synchronize(process_group(g));
  return out;
}

template<typename Graph, typename WeightMap, typename OutputIterator,
         typename GlobalIndexMap>
inline OutputIterator
boruvka_mixed_merge(const Graph& g, WeightMap weight, OutputIterator out,
                    GlobalIndexMap index)
{
  typedef typename graph_traits<Graph>::vertex_descriptor vertex_descriptor;
  typedef typename graph_traits<Graph>::vertices_size_type vertices_size_type;
  std::vector<vertices_size_type> ranks(num_vertices(g));
  std::vector<vertex_descriptor> parents(num_vertices(g));
  std::vector<vertices_size_type> supervertex_indices(num_vertices(g));

  return boruvka_mixed_merge
           (g, weight, out, index,
            make_iterator_property_map(ranks.begin(), index),
            make_iterator_property_map(parents.begin(), index),
            make_iterator_property_map(supervertex_indices.begin(), index));
}

template<typename Graph, typename WeightMap, typename OutputIterator>
inline OutputIterator
boruvka_mixed_merge(const Graph& g, WeightMap weight, OutputIterator out)
{ return boruvka_mixed_merge(g, weight, out, get(vertex_index, g)); }

} // end namespace distributed

using distributed::dense_boruvka_minimum_spanning_tree;
using distributed::merge_local_minimum_spanning_trees;
using distributed::boruvka_then_merge;
using distributed::boruvka_mixed_merge;

} } // end namespace boost::graph


#endif // BOOST_DEHNE_GOTZ_MIN_SPANNING_TREE_HPP

/* dehne_gotz_min_spanning_tree.hpp
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
*/