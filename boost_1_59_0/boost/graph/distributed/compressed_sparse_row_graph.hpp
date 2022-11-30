// Copyright (C) 2006 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Jeremiah Willcock
//           Andrew Lumsdaine

// Distributed compressed sparse row graph type

#ifndef BOOST_GRAPH_DISTRIBUTED_CSR_HPP
#define BOOST_GRAPH_DISTRIBUTED_CSR_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <boost/assert.hpp>
#include <boost/graph/compressed_sparse_row_graph.hpp>
#include <boost/graph/distributed/selector.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/graph/distributed/concepts.hpp>
#include <boost/graph/parallel/properties.hpp>
#include <boost/graph/parallel/distribution.hpp>
#include <boost/property_map/parallel/local_property_map.hpp>
#include <boost/property_map/parallel/distributed_property_map.hpp>

namespace boost {

// Distributed and sequential inplace ctors have the same signature so
// we need a separate tag for distributed inplace ctors
enum distributed_construct_inplace_from_sources_and_targets_t 
  {distributed_construct_inplace_from_sources_and_targets};

// The number of bits we reserve for the processor ID. 
// DPG TBD: This is a hack. It will eventually be a run-time quantity.
static const int processor_bits = 8;

// Tag class for a distributed CSR graph
struct distributed_csr_tag
  : public virtual distributed_graph_tag,
    public virtual distributed_vertex_list_graph_tag,
    public virtual distributed_edge_list_graph_tag,
    public virtual incidence_graph_tag,
    public virtual adjacency_graph_tag {};

template<typename VertexProperty, typename EdgeProperty,
         typename GraphProperty, typename ProcessGroup, typename InVertex,
         typename InDistribution, typename InEdgeIndex>
class compressed_sparse_row_graph<
         directedS, VertexProperty, EdgeProperty, GraphProperty,
         distributedS<ProcessGroup, InVertex, InDistribution>,
         InEdgeIndex>
{
  typedef compressed_sparse_row_graph self_type;

 private:
  /**
   *  Determine the type used to represent vertices in the graph. If
   *  the user has overridden the default, use the user's
   *  parameter. Otherwise, fall back to std::size_t.
   */
  typedef typename mpl::if_<is_same<InVertex, defaultS>,
                            std::size_t,
                            InVertex>::type Vertex;

  /**
   *  Determine the type used to represent edges in the graph. If
   *  the user has overridden the default (which is to be the same as
   *  the distributed vertex selector type), use the user's
   *  parameter. Otherwise, fall back to the value of @c Vertex.
   */
  typedef typename mpl::if_<is_same<InEdgeIndex,
                                    distributedS<ProcessGroup, InVertex,
                                                 InDistribution> >,
                            Vertex,
                            InEdgeIndex>::type EdgeIndex;

 public:
  /**
   * The type of the CSR graph that will be stored locally.
   */
  typedef compressed_sparse_row_graph<directedS, VertexProperty, EdgeProperty,
                                      GraphProperty, Vertex, EdgeIndex>
    base_type;

  // -----------------------------------------------------------------
  // Graph concept requirements
  typedef Vertex vertex_descriptor;
  typedef typename graph_traits<base_type>::edge_descriptor edge_descriptor;
  typedef directed_tag directed_category;
  typedef allow_parallel_edge_tag edge_parallel_category;
  typedef distributed_csr_tag traversal_category;
  static vertex_descriptor null_vertex();

  // -----------------------------------------------------------------
  // Distributed Vertex List Graph concept requirements
  typedef Vertex vertices_size_type;
  class vertex_iterator;

  // -----------------------------------------------------------------
  // Distributed Edge List Graph concept requirements
  typedef EdgeIndex edges_size_type;
  class edge_iterator;

  // -----------------------------------------------------------------
  // Incidence Graph concept requirements
  typedef typename graph_traits<base_type>::out_edge_iterator
    out_edge_iterator;
  typedef typename graph_traits<base_type>::degree_size_type
    degree_size_type;

  // -----------------------------------------------------------------
  // Adjacency Graph concept requirements
  typedef typename graph_traits<base_type>::adjacency_iterator
    adjacency_iterator;

  // Note: This graph type does not model Bidirectional Graph.
  // However, this typedef is required to satisfy graph_traits.
  typedef void in_edge_iterator;

  // -----------------------------------------------------------------
  // Distributed Container concept requirements
  typedef ProcessGroup process_group_type;
  typedef boost::parallel::variant_distribution<process_group_type, Vertex>
    distribution_type;

  // -----------------------------------------------------------------
  // Workarounds
  // NOTE: This graph type does not have old-style graph properties. It only
  // accepts bundles.
  typedef no_property vertex_property_type;
  typedef no_property edge_property_type;
  typedef no_property graph_property_type;
  typedef typename mpl::if_<is_void<VertexProperty>,
                            void****,
                            VertexProperty>::type vertex_bundled;
  typedef typename mpl::if_<is_void<EdgeProperty>,
                            void****,
                            EdgeProperty>::type edge_bundled;
  typedef typename mpl::if_<is_void<GraphProperty>,
                            void****,
                            GraphProperty>::type graph_bundled;

  // -----------------------------------------------------------------
  // Useful types
  typedef typename ProcessGroup::process_id_type process_id_type;

  // -----------------------------------------------------------------
  // Graph constructors
  compressed_sparse_row_graph(const ProcessGroup& pg = ProcessGroup())
    : m_process_group(pg), m_distribution(parallel::block(pg, 0)) {}

  compressed_sparse_row_graph(const GraphProperty& prop,
                              const ProcessGroup& pg = ProcessGroup())
    : m_process_group(pg), m_distribution(parallel::block(pg, 0)) {}

  compressed_sparse_row_graph(vertices_size_type numverts,
                              const ProcessGroup& pg = ProcessGroup())
    : m_process_group(pg), m_distribution(parallel::block(pg, 0)),
      m_base(numverts) 
  {}

  compressed_sparse_row_graph(vertices_size_type numverts,
                              const GraphProperty& prop,
                              const ProcessGroup& pg = ProcessGroup())
    : m_process_group(pg), m_distribution(parallel::block(pg, 0)),
      m_base(numverts) 
  {}

  template <typename Distribution>
  compressed_sparse_row_graph(vertices_size_type numverts,
                              const ProcessGroup& pg,
                              const Distribution& dist)
    : m_process_group(pg), m_distribution(dist), m_base(numverts) {}

  template <typename Distribution>
  compressed_sparse_row_graph(vertices_size_type numverts,
                              const GraphProperty& prop,
                              const ProcessGroup& pg,
                              const Distribution& dist)
    : m_process_group(pg), m_distribution(dist), m_base(numverts) {}

  template <typename InputIterator>
  compressed_sparse_row_graph(edges_are_unsorted_t,
                              InputIterator edge_begin, InputIterator edge_end,
                              vertices_size_type numverts,
                              const ProcessGroup& pg = ProcessGroup(),
                              const GraphProperty& prop = GraphProperty());

  template <typename InputIterator, typename Distribution>
  compressed_sparse_row_graph(edges_are_unsorted_t,
                              InputIterator edge_begin, InputIterator edge_end,
                              vertices_size_type numverts,
                              const ProcessGroup& pg,
                              const Distribution& dist,
                              const GraphProperty& prop = GraphProperty());

  template <typename InputIterator, typename EdgePropertyIterator>
  compressed_sparse_row_graph(edges_are_unsorted_t,
                              InputIterator edge_begin, InputIterator edge_end,
                              EdgePropertyIterator ep_iter,
                              vertices_size_type numverts,
                              const ProcessGroup& pg = ProcessGroup(),
                              const GraphProperty& prop = GraphProperty());

  template <typename InputIterator, typename EdgePropertyIterator,
            typename Distribution>
  compressed_sparse_row_graph(edges_are_unsorted_t,
                              InputIterator edge_begin, InputIterator edge_end,
                              EdgePropertyIterator ep_iter,
                              vertices_size_type numverts,
                              const ProcessGroup& pg,
                              const Distribution& dist,
                              const GraphProperty& prop = GraphProperty());

  template <typename InputIterator>
  compressed_sparse_row_graph(edges_are_sorted_t,
                              InputIterator edge_begin, InputIterator edge_end,
                              vertices_size_type numverts,
                              edges_size_type numedges = 0,
                              const ProcessGroup& pg = ProcessGroup(),
                              const GraphProperty& prop = GraphProperty());

  template <typename InputIterator, typename Distribution>
  compressed_sparse_row_graph(edges_are_sorted_t,
                              InputIterator edge_begin, InputIterator edge_end,
                              vertices_size_type numverts,
                              const ProcessGroup& pg,
                              const Distribution& dist,
                              const GraphProperty& prop = GraphProperty());

  template <typename InputIterator, typename EdgePropertyIterator>
  compressed_sparse_row_graph(edges_are_sorted_t,
                              InputIterator edge_begin, InputIterator edge_end,
                              EdgePropertyIterator ep_iter,
                              vertices_size_type numverts,
                              edges_size_type numedges = 0,
                              const ProcessGroup& pg = ProcessGroup(),
                              const GraphProperty& prop = GraphProperty());

  template <typename InputIterator, typename EdgePropertyIterator,
            typename Distribution>
  compressed_sparse_row_graph(edges_are_sorted_t,
                              InputIterator edge_begin, InputIterator edge_end,
                              EdgePropertyIterator ep_iter,
                              vertices_size_type numverts,
                              const ProcessGroup& pg,
                              const Distribution& dist,
                              const GraphProperty& prop = GraphProperty());

  template <typename MultiPassInputIterator>
  compressed_sparse_row_graph(edges_are_unsorted_multi_pass_t,
                              MultiPassInputIterator edge_begin, 
                              MultiPassInputIterator edge_end,
                              vertices_size_type numverts,
                              const ProcessGroup& pg = ProcessGroup(),
                              const GraphProperty& prop = GraphProperty());

  template <typename MultiPassInputIterator, typename Distribution>
  compressed_sparse_row_graph(edges_are_unsorted_multi_pass_t,
                              MultiPassInputIterator edge_begin, 
                              MultiPassInputIterator edge_end,
                              vertices_size_type numverts,
                              const ProcessGroup& pg,
                              const Distribution& dist,
                              const GraphProperty& prop = GraphProperty());

  template <typename MultiPassInputIterator, typename EdgePropertyIterator>
  compressed_sparse_row_graph(edges_are_unsorted_multi_pass_t,
                              MultiPassInputIterator edge_begin, 
                              MultiPassInputIterator edge_end,
                              EdgePropertyIterator ep_iter,
                              vertices_size_type numverts,
                              const ProcessGroup& pg = ProcessGroup(),
                              const GraphProperty& prop = GraphProperty());

  template <typename MultiPassInputIterator, typename EdgePropertyIterator,
            typename Distribution>
  compressed_sparse_row_graph(edges_are_unsorted_multi_pass_t,
                              MultiPassInputIterator edge_begin, 
                              MultiPassInputIterator edge_end,
                              EdgePropertyIterator ep_iter,
                              vertices_size_type numverts,
                              const ProcessGroup& pg,
                              const Distribution& dist,
                              const GraphProperty& prop = GraphProperty());

  template <typename Source>
  compressed_sparse_row_graph(distributed_construct_inplace_from_sources_and_targets_t,
                              std::vector<Source>& sources,
                              std::vector<vertex_descriptor>& targets,
                              vertices_size_type numverts,
                              const ProcessGroup& pg = ProcessGroup(),
                              const GraphProperty& prop = GraphProperty());

  template <typename Distribution, typename Source> 
  compressed_sparse_row_graph(distributed_construct_inplace_from_sources_and_targets_t,
                              std::vector<Source>& sources,
                              std::vector<vertex_descriptor>& targets,
                              vertices_size_type numverts,
                              const ProcessGroup& pg,
                              const Distribution& dist,
                              const GraphProperty& prop = GraphProperty());

  template <typename Source>
  compressed_sparse_row_graph(distributed_construct_inplace_from_sources_and_targets_t,
                              std::vector<Source>& sources,
                              std::vector<vertex_descriptor>& targets,
                              std::vector<edge_bundled>& edge_props,
                              vertices_size_type numverts,
                              const ProcessGroup& pg = ProcessGroup(),
                              const GraphProperty& prop = GraphProperty());

  template <typename Distribution, typename Source>
  compressed_sparse_row_graph(distributed_construct_inplace_from_sources_and_targets_t,
                              std::vector<Source>& sources,
                              std::vector<vertex_descriptor>& targets,
                              std::vector<edge_bundled>& edge_props,
                              vertices_size_type numverts,
                              const ProcessGroup& pg,
                              const Distribution& dist,
                              const GraphProperty& prop = GraphProperty());

  template<typename InputIterator>
  compressed_sparse_row_graph(InputIterator edge_begin, InputIterator edge_end,
                              vertices_size_type numverts,
                              const ProcessGroup& pg = ProcessGroup(),
                              const GraphProperty& prop = GraphProperty());

  template<typename InputIterator, typename EdgePropertyIterator>
  compressed_sparse_row_graph(InputIterator edge_begin, InputIterator edge_end,
                              EdgePropertyIterator ep_iter,
                              vertices_size_type numverts,
                              const ProcessGroup& pg = ProcessGroup(),
                              const GraphProperty& prop = GraphProperty());

  template<typename InputIterator, typename Distribution>
  compressed_sparse_row_graph(InputIterator edge_begin, InputIterator edge_end,
                              vertices_size_type numverts,
                              const ProcessGroup& pg,
                              const Distribution& dist,
                              const GraphProperty& prop = GraphProperty());

  template<typename InputIterator, typename EdgePropertyIterator, 
           typename Distribution>
  compressed_sparse_row_graph(InputIterator edge_begin, InputIterator edge_end,
                              EdgePropertyIterator ep_iter,
                              vertices_size_type numverts,
                              const ProcessGroup& pg,
                              const Distribution& dist,
                              const GraphProperty& prop = GraphProperty());

  base_type&       base()       { return m_base; }
  const base_type& base() const { return m_base; }

  process_group_type process_group() const { return m_process_group.base(); }

  distribution_type&       distribution()       { return m_distribution; }
  const distribution_type& distribution() const { return m_distribution; }

  // Directly access a vertex or edge bundle
  vertex_bundled& operator[](vertex_descriptor v)
  {
    return get(vertex_bundle, *this, v);
  }

  const vertex_bundled& operator[](vertex_descriptor v) const
  {
    return get(vertex_bundle, *this, v);
  }

  edge_bundled& operator[](edge_descriptor e)
  {
    return get(edge_bundle, *this, e);
  }

  const edge_bundled& operator[](edge_descriptor e) const
  {
    return get(edge_bundle, *this, e);
  }

  // Create a vertex descriptor from a process ID and a local index.
  vertex_descriptor 
  make_vertex_descriptor(process_id_type p, vertex_descriptor v) const
  {
    vertex_descriptor vertex_local_index_bits = 
      sizeof(vertex_descriptor) * CHAR_BIT - processor_bits;
    return v | ((vertex_descriptor)p << vertex_local_index_bits);
  }

  // Convert a local vertex descriptor into a global vertex descriptor
  vertex_descriptor local_to_global_vertex(vertex_descriptor v) const
  {
    return make_vertex_descriptor(process_id(m_process_group), v);
  }

  // Structural modification
  vertex_descriptor add_vertex()
  {
    typename graph_traits<base_type>::vertex_descriptor v 
      = boost::add_vertex(m_base);

    return make_vertex_descriptor(process_id(m_process_group), v);
  }

  vertex_descriptor add_vertex(const vertex_bundled& p)
  {
    typename graph_traits<base_type>::vertex_descriptor v 
      = boost::add_vertex(m_base, p);

    return make_vertex_descriptor(process_id(m_process_group), v);
  }

  vertex_descriptor add_vertices(vertices_size_type count)
  {
    typename graph_traits<base_type>::vertex_descriptor v 
      = boost::add_vertices(count, m_base);

    return make_vertex_descriptor(process_id(m_process_group), v);
  }

  template <typename InputIterator>
  void 
  add_edges(InputIterator first, InputIterator last)
  { boost::add_edges_global(first, last, get(vertex_local, *this), m_base); }

  template <typename InputIterator, typename EdgePropertyIterator>
  void 
  add_edges(InputIterator first, InputIterator last,
            EdgePropertyIterator ep_iter,
            EdgePropertyIterator ep_iter_end)
  { boost::add_edges_global(first, last, ep_iter, ep_iter_end, 
                            get(vertex_local, *this), m_base); }

  template <typename InputIterator>
  void 
  add_edges_sorted(InputIterator first, InputIterator last)
  { boost::add_edges_sorted_global(first, last, 
                                   get(vertex_local, *this), m_base); }

  template <typename InputIterator, typename EdgePropertyIterator>
  void 
  add_edges_sorted(InputIterator first_sorted, InputIterator last_sorted,
                   EdgePropertyIterator ep_iter_sorted)
  { boost::add_edges_sorted_global(first_sorted, last_sorted, ep_iter_sorted, 
                                   get(vertex_local, *this), m_base); }

 protected:
  ProcessGroup m_process_group;
  distribution_type m_distribution;
  base_type m_base;
};

/** @brief Helper macro containing the template parameters for the
 *   distributed CSR graph.
 *
 *  This macro contains all of the template parameters needed for the
 *  distributed compressed_sparse_row graph type. It is used to reduce
 *  the amount of typing required to declare free functions for this
 *  graph type.
 */
#define BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS                          \
  typename VertexProperty, typename EdgeProperty,    \
  typename GraphProperty, typename ProcessGroup, typename InVertex,     \
  typename InDistribution, typename InEdgeIndex

/** @brief Helper macro containing the typical instantiation of the
 *   distributed CSR graph.
 *
 *  This macro contains an instantiation of the distributed CSR graph
 *  type using the typical template parameters names (e.g., those
 *  provided by the macro @c
 *  BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS). It is used to reduce
 *  the amount of typing required to declare free functions for this
 *  graph type.
 */
#define BOOST_DISTRIB_CSR_GRAPH_TYPE                            \
  compressed_sparse_row_graph<                                  \
    directedS, VertexProperty, EdgeProperty, GraphProperty,      \
    distributedS<ProcessGroup, InVertex, InDistribution>,       \
    InEdgeIndex>

// -----------------------------------------------------------------
// Graph concept operations
template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_descriptor
BOOST_DISTRIB_CSR_GRAPH_TYPE::null_vertex()
{
  return graph_traits<base_type>::null_vertex();
}

// -----------------------------------------------------------------
// Incidence Graph concept operations
template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_descriptor
source(typename BOOST_DISTRIB_CSR_GRAPH_TYPE::edge_descriptor e,
       const BOOST_DISTRIB_CSR_GRAPH_TYPE&)
{ return e.src; }

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_descriptor
target(typename BOOST_DISTRIB_CSR_GRAPH_TYPE::edge_descriptor e,
       const BOOST_DISTRIB_CSR_GRAPH_TYPE& g)
{ return target(e, g.base()); }

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline std::pair<typename BOOST_DISTRIB_CSR_GRAPH_TYPE::out_edge_iterator,
                 typename BOOST_DISTRIB_CSR_GRAPH_TYPE::out_edge_iterator>
out_edges(typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_descriptor u,
          const BOOST_DISTRIB_CSR_GRAPH_TYPE& g)
{
  typedef typename BOOST_DISTRIB_CSR_GRAPH_TYPE::edges_size_type
    edges_size_type;
  typedef typename BOOST_DISTRIB_CSR_GRAPH_TYPE::edge_descriptor ed;
  typedef typename BOOST_DISTRIB_CSR_GRAPH_TYPE::out_edge_iterator it;
  edges_size_type u_local = get(vertex_local, g, u);
  edges_size_type u_row_start = g.base().m_forward.m_rowstart[u_local];
  edges_size_type next_row_start = g.base().m_forward.m_rowstart[u_local + 1];
  return std::make_pair(it(ed(u, u_row_start)),
                        it(ed(u, (std::max)(u_row_start, next_row_start))));
}

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline typename BOOST_DISTRIB_CSR_GRAPH_TYPE::degree_size_type
out_degree(typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_descriptor u,
           const BOOST_DISTRIB_CSR_GRAPH_TYPE& g)
{
  return out_degree(get(vertex_local, g, u), g.base());
}

// -----------------------------------------------------------------
// DistributedGraph concept requirements
template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
void synchronize(const BOOST_DISTRIB_CSR_GRAPH_TYPE& g)
{
  synchronize(g.process_group());
}

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS> 
ProcessGroup
process_group(const BOOST_DISTRIB_CSR_GRAPH_TYPE& g)
{ return g.process_group(); }


// -----------------------------------------------------------------
// Adjacency Graph concept requirements
template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline std::pair<typename BOOST_DISTRIB_CSR_GRAPH_TYPE::adjacency_iterator,
                 typename BOOST_DISTRIB_CSR_GRAPH_TYPE::adjacency_iterator>
adjacent_vertices(typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_descriptor u,
                  const BOOST_DISTRIB_CSR_GRAPH_TYPE& g)
{
  return adjacent_vertices(get(vertex_local, g, u), g.base());
}

// -----------------------------------------------------------------
// Distributed Vertex List Graph concept operations
template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
class BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_iterator
  : public iterator_adaptor<vertex_iterator,
                            counting_iterator<Vertex>,
                            Vertex,
                            random_access_traversal_tag,
                            Vertex>
{
  typedef iterator_adaptor<vertex_iterator,
                           counting_iterator<Vertex>,
                           Vertex,
                           random_access_traversal_tag,
                           Vertex> inherited;
 public:
  vertex_iterator() {}

  explicit vertex_iterator(Vertex v, const self_type* graph)
    : inherited(counting_iterator<Vertex>(v)), graph(graph) { }

  Vertex dereference() const
  {
    return graph->local_to_global_vertex(*(this->base_reference()));
  }

  friend class iterator_core_access;

 private:
  const self_type* graph;
};

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline typename BOOST_DISTRIB_CSR_GRAPH_TYPE::degree_size_type
num_vertices(const BOOST_DISTRIB_CSR_GRAPH_TYPE& g)
{
  return num_vertices(g.base());
}

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline std::pair<typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_iterator,
                 typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_iterator>
vertices(const BOOST_DISTRIB_CSR_GRAPH_TYPE& g)
{
  typedef typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_iterator
    vertex_iterator;
  return std::make_pair(vertex_iterator(0, &g),
                        vertex_iterator(num_vertices(g), &g));
}

// -----------------------------------------------------------------
// Distributed Edge List Graph concept operations
template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
class BOOST_DISTRIB_CSR_GRAPH_TYPE::edge_iterator
{
 public:
  typedef std::forward_iterator_tag iterator_category;
  typedef edge_descriptor value_type;

  typedef const edge_descriptor* pointer;

  typedef edge_descriptor reference;
  typedef typename int_t<CHAR_BIT * sizeof(EdgeIndex)>::fast difference_type;

  edge_iterator() : graph(0), current_edge(), end_of_this_vertex(0) {}

  edge_iterator(const compressed_sparse_row_graph& graph,
                edge_descriptor current_edge,
                EdgeIndex end_of_this_vertex)
    : graph(&graph), local_src(current_edge.src), current_edge(current_edge),
      end_of_this_vertex(end_of_this_vertex)
  {
    // The edge that comes in has a local source vertex. Make it global.
    current_edge.src = graph.local_to_global_vertex(current_edge.src);
  }

  // From InputIterator
  reference operator*() const { return current_edge; }
  pointer operator->() const { return &current_edge; }

  bool operator==(const edge_iterator& o) const {
    return current_edge == o.current_edge;
  }
  bool operator!=(const edge_iterator& o) const {
    return current_edge != o.current_edge;
  }

  edge_iterator& operator++()
  {
    ++current_edge.idx;
    while (current_edge.idx == end_of_this_vertex && local_src < num_vertices(*graph)-1) {
      ++local_src;
      current_edge.src = graph->local_to_global_vertex(local_src);
      end_of_this_vertex = graph->base().m_forward.m_rowstart[local_src + 1];
    }
    return *this;
  }

  edge_iterator operator++(int) {
    edge_iterator temp = *this;
    ++*this;
    return temp;
  }

 private:
  const compressed_sparse_row_graph* graph;
  EdgeIndex local_src;
  edge_descriptor current_edge;
  EdgeIndex end_of_this_vertex;
};

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline typename BOOST_DISTRIB_CSR_GRAPH_TYPE::edges_size_type
num_edges(const BOOST_DISTRIB_CSR_GRAPH_TYPE& g)
{
  return g.base().m_forward.m_column.size();
}

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
std::pair<typename BOOST_DISTRIB_CSR_GRAPH_TYPE::edge_iterator,
          typename BOOST_DISTRIB_CSR_GRAPH_TYPE::edge_iterator>
edges(const BOOST_DISTRIB_CSR_GRAPH_TYPE& g)
{
  typedef typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_descriptor Vertex;
  typedef typename BOOST_DISTRIB_CSR_GRAPH_TYPE::edge_iterator ei;
  typedef typename BOOST_DISTRIB_CSR_GRAPH_TYPE::edge_descriptor edgedesc;
  if (g.base().m_forward.m_rowstart.size() == 1 ||
      g.base().m_forward.m_column.empty()) {
    return std::make_pair(ei(), ei());
  } else {
    // Find the first vertex that has outgoing edges
    Vertex src = 0;
    while (g.base().m_forward.m_rowstart[src + 1] == 0) ++src;
    return std::make_pair(ei(g, edgedesc(src, 0), g.base().m_forward.m_rowstart[src + 1]),
                          ei(g, edgedesc(num_vertices(g), g.base().m_forward.m_column.size()), 0));
  }
}

// -----------------------------------------------------------------
// Graph constructors

// Returns true if a vertex belongs to a process according to a distribution
template <typename OwnerMap, typename ProcessId>
struct local_vertex {

  local_vertex(OwnerMap owner, ProcessId id) 
    : owner(owner), id(id) {}

  template <typename Vertex>
  bool operator()(Vertex x) 
  { return get(owner, x) == id; }

  template <typename Vertex>
  bool operator()(Vertex x) const
  { return get(owner, x) == id; }

private:
  OwnerMap owner;
  ProcessId id;
};

// Returns true if a vertex belongs to a process according to a distribution
template <typename OwnerMap, typename ProcessId>
struct local_edge {

  local_edge(OwnerMap owner, ProcessId id) 
    : owner(owner), id(id) {}

  template <typename Vertex>
  bool operator()(std::pair<Vertex, Vertex>& x) 
  { return get(owner, x.first) == id; }

  template <typename Vertex>
  bool operator()(const std::pair<Vertex, Vertex>& x) const
  { return get(owner, x.first) == id; }

private:
  OwnerMap owner;
  ProcessId id;
};

// Turns an index iterator into a vertex iterator
template<typename IndexIterator, typename Graph>
class index_to_vertex_iterator {
  
public:
  typedef std::input_iterator_tag iterator_category;
  typedef typename graph_traits<Graph>::vertex_descriptor Vertex;
  typedef std::pair<Vertex, Vertex> value_type;
  typedef const value_type& reference;
  typedef const value_type* pointer;
  typedef void difference_type;

  index_to_vertex_iterator(IndexIterator index,
                           const Graph& g) 
    : index(index), g(g), current(to_edge(*index)) {}

  reference operator*() { current = to_edge(*index); return current; }
  pointer operator->() { current = to_edge(*index); return &current; }

  index_to_vertex_iterator& operator++()
  {
    ++index;
    return *this;
  }

  index_to_vertex_iterator operator++(int)
  {
    index_to_vertex_iterator temp(*this);
    ++(*this);
    return temp;
  }

  bool operator==(const index_to_vertex_iterator& other) const
  { return index == other.index; }
  
  bool operator!=(const index_to_vertex_iterator& other) const
  { return !(*this == other); }

private:
  value_type to_edge(const typename std::iterator_traits<IndexIterator>::value_type& x)
  { return std::make_pair(vertex(x.first, g), vertex(x.second, g)); }

  IndexIterator index;
  const Graph& g;  
  value_type current;
};

template <typename Distribution, typename Graph>
struct index_to_vertex_func {

  typedef typename boost::graph_traits<Graph>::vertex_descriptor vertex_descriptor;
  typedef typename boost::graph_traits<Graph>::vertices_size_type vertices_size_type;
  typedef std::pair<vertex_descriptor, vertex_descriptor> result_type;
  typedef std::pair<vertices_size_type, vertices_size_type> base_iterator_type;

  index_to_vertex_func(const Distribution& dist, const Graph& g)
    : dist(dist), g(g) {}


  result_type operator()(const base_iterator_type& p) const 
  {
    return std::make_pair(vertex(p.first, g), vertex(p.second, g));
  }

private:
  const Distribution& dist;
  const Graph& g;
};

// NGE: This method only works with iterators that have a difference_type,
// the index_to_vertex_iterator class above is retained for compatibility
// with BGL generators which have no difference_type
template <typename IndexIterator, typename Distribution, typename Graph>
boost::transform_iterator<index_to_vertex_func<Distribution, Graph>, IndexIterator>
make_index_to_vertex_iterator(IndexIterator it, const Distribution& dist, 
                              const Graph& g) {
  return boost::make_transform_iterator(
    it, index_to_vertex_func<Distribution, Graph>(dist, g));
}

// Forward declaration of csr_vertex_owner_map
template<typename ProcessID, typename Key> class csr_vertex_owner_map;

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
template<typename InputIterator>
BOOST_DISTRIB_CSR_GRAPH_TYPE::
compressed_sparse_row_graph(edges_are_unsorted_t,
                            InputIterator edge_begin, InputIterator edge_end,
                            vertices_size_type numverts,
                            const ProcessGroup& pg,
                            const GraphProperty& prop)
  : m_process_group(pg),
    m_distribution(parallel::block(m_process_group, numverts)),
    m_base(edges_are_unsorted_global,
           index_to_vertex_iterator<InputIterator, BOOST_DISTRIB_CSR_GRAPH_TYPE>(edge_begin, *this),
           index_to_vertex_iterator<InputIterator, BOOST_DISTRIB_CSR_GRAPH_TYPE>(edge_end, *this),
           m_distribution.block_size(process_id(m_process_group), numverts),
           get(vertex_local, *this),
           local_vertex<csr_vertex_owner_map<process_id_type, vertex_descriptor>, 
                        process_id_type> (get(vertex_owner, *this), process_id(pg)),
           prop)
{ }

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
template <typename InputIterator, typename Distribution>
BOOST_DISTRIB_CSR_GRAPH_TYPE::
compressed_sparse_row_graph(edges_are_unsorted_t,
                            InputIterator edge_begin, InputIterator edge_end,
                            vertices_size_type numverts,
                            const ProcessGroup& pg,
                            const Distribution& dist,
                            const GraphProperty& prop)
  : m_process_group(pg),
    m_distribution(dist),
    m_base(edges_are_unsorted_global,
           index_to_vertex_iterator<InputIterator, BOOST_DISTRIB_CSR_GRAPH_TYPE>(edge_begin, *this),
           index_to_vertex_iterator<InputIterator, BOOST_DISTRIB_CSR_GRAPH_TYPE>(edge_end, *this),
           m_distribution.block_size(process_id(m_process_group), numverts),
           get(vertex_local, *this),
           local_vertex<csr_vertex_owner_map<process_id_type, vertex_descriptor>, 
                        process_id_type> (get(vertex_owner, *this), process_id(pg)),
           prop)
{ }

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
template<typename InputIterator, typename EdgePropertyIterator>
BOOST_DISTRIB_CSR_GRAPH_TYPE::
compressed_sparse_row_graph(edges_are_unsorted_t,
                            InputIterator edge_begin, InputIterator edge_end,
                            EdgePropertyIterator ep_iter,
                            vertices_size_type numverts,
                            const ProcessGroup& pg,
                            const GraphProperty& prop)
  : m_process_group(pg),
    m_distribution(parallel::block(m_process_group, numverts)),
    m_base(edges_are_unsorted_global,
           index_to_vertex_iterator<InputIterator, BOOST_DISTRIB_CSR_GRAPH_TYPE>(edge_begin, *this),
           index_to_vertex_iterator<InputIterator, BOOST_DISTRIB_CSR_GRAPH_TYPE>(edge_end, *this),
           ep_iter,
           m_distribution.block_size(process_id(m_process_group), numverts),
           get(vertex_local, *this),
           local_vertex<csr_vertex_owner_map<process_id_type, vertex_descriptor>, 
                        process_id_type> (get(vertex_owner, *this), process_id(pg)),
           prop)
{ }

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
template <typename InputIterator, typename EdgePropertyIterator,
          typename Distribution>
BOOST_DISTRIB_CSR_GRAPH_TYPE::
compressed_sparse_row_graph(edges_are_unsorted_t,
                            InputIterator edge_begin, InputIterator edge_end,
                            EdgePropertyIterator ep_iter,
                            vertices_size_type numverts,
                            const ProcessGroup& pg,
                            const Distribution& dist,
                            const GraphProperty& prop)
  : m_process_group(pg),
    m_distribution(dist),
    m_base(edges_are_unsorted_global,
           index_to_vertex_iterator<InputIterator, BOOST_DISTRIB_CSR_GRAPH_TYPE>(edge_begin, *this),
           index_to_vertex_iterator<InputIterator, BOOST_DISTRIB_CSR_GRAPH_TYPE>(edge_end, *this),
           ep_iter,
           m_distribution.block_size(process_id(m_process_group), numverts),
           get(vertex_local, *this),
           local_vertex<csr_vertex_owner_map<process_id_type, vertex_descriptor>, 
                        process_id_type> (get(vertex_owner, *this), process_id(pg)),
           prop)
{ }

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
template<typename InputIterator>
BOOST_DISTRIB_CSR_GRAPH_TYPE::
compressed_sparse_row_graph(edges_are_sorted_t,
                            InputIterator edge_begin, InputIterator edge_end,
                            vertices_size_type numverts,
                            edges_size_type numedges, // This is not used as there is no appropriate BGL ctor
                            const ProcessGroup& pg,
                            const GraphProperty& prop)
  : m_process_group(pg),
    m_distribution(parallel::block(m_process_group, numverts)),
    m_base(edges_are_sorted_global,
           index_to_vertex_iterator<InputIterator, BOOST_DISTRIB_CSR_GRAPH_TYPE>(edge_begin, *this),
           index_to_vertex_iterator<InputIterator, BOOST_DISTRIB_CSR_GRAPH_TYPE>(edge_end, *this),
           get(vertex_local, *this),
           local_vertex<csr_vertex_owner_map<process_id_type, vertex_descriptor>, 
                        process_id_type> (get(vertex_owner, *this), process_id(pg)),
           m_distribution.block_size(process_id(m_process_group), numverts),
           prop)
{ }

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
template <typename InputIterator, typename Distribution>
BOOST_DISTRIB_CSR_GRAPH_TYPE::
compressed_sparse_row_graph(edges_are_sorted_t,
                            InputIterator edge_begin, InputIterator edge_end,
                            vertices_size_type numverts,
                            const ProcessGroup& pg,
                            const Distribution& dist,
                            const GraphProperty& prop)
  : m_process_group(pg),
    m_distribution(dist),
    m_base(edges_are_sorted_global,
           index_to_vertex_iterator<InputIterator, BOOST_DISTRIB_CSR_GRAPH_TYPE>(edge_begin, *this),
           index_to_vertex_iterator<InputIterator, BOOST_DISTRIB_CSR_GRAPH_TYPE>(edge_end, *this),
           get(vertex_local, *this),
           local_vertex<csr_vertex_owner_map<process_id_type, vertex_descriptor>, 
                        process_id_type> (get(vertex_owner, *this), process_id(pg)),
           m_distribution.block_size(process_id(m_process_group), numverts),
           prop)
{ }

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
template<typename InputIterator, typename EdgePropertyIterator>
BOOST_DISTRIB_CSR_GRAPH_TYPE::
compressed_sparse_row_graph(edges_are_sorted_t,
                            InputIterator edge_begin, InputIterator edge_end,
                            EdgePropertyIterator ep_iter,
                            vertices_size_type numverts,
                            edges_size_type numedges, // This is not used as there is no appropriate BGL ctor
                            const ProcessGroup& pg,
                            const GraphProperty& prop)
  : m_process_group(pg),
    m_distribution(parallel::block(m_process_group, numverts)),
    m_base(edges_are_sorted_global,
           index_to_vertex_iterator<InputIterator, BOOST_DISTRIB_CSR_GRAPH_TYPE>(edge_begin, *this),
           index_to_vertex_iterator<InputIterator, BOOST_DISTRIB_CSR_GRAPH_TYPE>(edge_end, *this),
           ep_iter,
           get(vertex_local, *this),
           local_vertex<csr_vertex_owner_map<process_id_type, vertex_descriptor>, 
                        process_id_type> (get(vertex_owner, *this), process_id(pg)),
           m_distribution.block_size(process_id(m_process_group), numverts),
           prop)
{ }

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
template<typename InputIterator, typename EdgePropertyIterator,
         typename Distribution>
BOOST_DISTRIB_CSR_GRAPH_TYPE::
compressed_sparse_row_graph(edges_are_sorted_t,
                            InputIterator edge_begin, InputIterator edge_end,
                            EdgePropertyIterator ep_iter,
                            vertices_size_type numverts,
                            const ProcessGroup& pg,
                            const Distribution& dist,
                            const GraphProperty& prop)
  : m_process_group(pg),
    m_distribution(dist),
    m_base(edges_are_sorted_global,
           index_to_vertex_iterator<InputIterator, BOOST_DISTRIB_CSR_GRAPH_TYPE>(edge_begin, *this),
           index_to_vertex_iterator<InputIterator, BOOST_DISTRIB_CSR_GRAPH_TYPE>(edge_end, *this),
           ep_iter,
           get(vertex_local, *this),
           local_vertex<csr_vertex_owner_map<process_id_type, vertex_descriptor>, 
                        process_id_type> (get(vertex_owner, *this), process_id(pg)),
           m_distribution.block_size(process_id(m_process_group), numverts),
           prop)
{ }

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
template<typename MultiPassInputIterator>
BOOST_DISTRIB_CSR_GRAPH_TYPE::
compressed_sparse_row_graph(edges_are_unsorted_multi_pass_t,
                            MultiPassInputIterator edge_begin, 
                            MultiPassInputIterator edge_end,
                            vertices_size_type numverts,
                            const ProcessGroup& pg,
                            const GraphProperty& prop)
  : m_process_group(pg),
    m_distribution(parallel::block(m_process_group, numverts)),
    m_base(edges_are_unsorted_multi_pass_global,
           make_index_to_vertex_iterator(edge_begin, parallel::block(m_process_group, numverts), *this),
           make_index_to_vertex_iterator(edge_end, parallel::block(m_process_group, numverts), *this),
           m_distribution.block_size(process_id(m_process_group), numverts),
           get(vertex_local, *this),
           local_vertex<csr_vertex_owner_map<process_id_type, vertex_descriptor>, 
                        process_id_type> (get(vertex_owner, *this), process_id(pg)),
           prop)
{ }

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
template <typename MultiPassInputIterator, typename Distribution>
BOOST_DISTRIB_CSR_GRAPH_TYPE::
compressed_sparse_row_graph(edges_are_unsorted_multi_pass_t,
                            MultiPassInputIterator edge_begin, 
                            MultiPassInputIterator edge_end,
                            vertices_size_type numverts,
                            const ProcessGroup& pg,
                            const Distribution& dist,
                            const GraphProperty& prop)
  : m_process_group(pg),
    m_distribution(dist),
    m_base(edges_are_unsorted_multi_pass_global,
           make_index_to_vertex_iterator(edge_begin, parallel::block(m_process_group, numverts), *this),
           make_index_to_vertex_iterator(edge_end, parallel::block(m_process_group, numverts), *this),
           m_distribution.block_size(process_id(m_process_group), numverts),
           get(vertex_local, *this),
           local_vertex<csr_vertex_owner_map<process_id_type, vertex_descriptor>, 
                        process_id_type> (get(vertex_owner, *this), process_id(pg)),
           prop)
{ }


template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
template<typename MultiPassInputIterator, typename EdgePropertyIterator>
BOOST_DISTRIB_CSR_GRAPH_TYPE::
compressed_sparse_row_graph(edges_are_unsorted_multi_pass_t,
                            MultiPassInputIterator edge_begin, 
                            MultiPassInputIterator edge_end,
                            EdgePropertyIterator ep_iter,
                            vertices_size_type numverts,
                            const ProcessGroup& pg,
                            const GraphProperty& prop)
  : m_process_group(pg),
    m_distribution(parallel::block(m_process_group, numverts)),
    m_base(edges_are_unsorted_multi_pass_global,
           make_index_to_vertex_iterator(edge_begin, parallel::block(m_process_group, numverts), *this),
           make_index_to_vertex_iterator(edge_end, parallel::block(m_process_group, numverts), *this),
           ep_iter,
           m_distribution.block_size(process_id(m_process_group), numverts),
           get(vertex_local, *this),
           local_vertex<csr_vertex_owner_map<process_id_type, vertex_descriptor>, 
                        process_id_type> (get(vertex_owner, *this), process_id(pg)),
           prop)
{ }

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
template <typename MultiPassInputIterator, typename EdgePropertyIterator,
          typename Distribution>
BOOST_DISTRIB_CSR_GRAPH_TYPE::
compressed_sparse_row_graph(edges_are_unsorted_multi_pass_t,
                            MultiPassInputIterator edge_begin, 
                            MultiPassInputIterator edge_end,
                            EdgePropertyIterator ep_iter,
                            vertices_size_type numverts,
                            const ProcessGroup& pg,
                            const Distribution& dist,
                            const GraphProperty& prop)
  : m_process_group(pg),
    m_distribution(dist),
    m_base(edges_are_unsorted_multi_pass_global,
           make_index_to_vertex_iterator(edge_begin, parallel::block(m_process_group, numverts), *this),
           make_index_to_vertex_iterator(edge_end, parallel::block(m_process_group, numverts), *this),
           ep_iter,
           m_distribution.block_size(process_id(m_process_group), numverts),
           get(vertex_local, *this),
           local_vertex<csr_vertex_owner_map<process_id_type, vertex_descriptor>, 
                        process_id_type> (get(vertex_owner, *this), process_id(pg)),
           prop)
{ }

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
template<typename Source>
BOOST_DISTRIB_CSR_GRAPH_TYPE::
compressed_sparse_row_graph(distributed_construct_inplace_from_sources_and_targets_t,
                            std::vector<Source>& sources,
                            std::vector<vertex_descriptor>& targets,
                            vertices_size_type numverts,
                            const ProcessGroup& pg,
                            const GraphProperty& prop)
  : m_process_group(pg),
    m_distribution(parallel::block(m_process_group, numverts)),
    m_base(m_distribution.block_size(process_id(m_process_group), numverts))
{ 
  // Convert linear indices to global indices
  for (edges_size_type i = 0; i < sources.size(); ++i) {
    sources[i] = m_distribution.local(sources[i]);
    targets[i] = make_vertex_descriptor(m_distribution(targets[i]), 
                                        m_distribution.local(targets[i]));
  }

  m_base.assign_sources_and_targets_global(
    sources, targets, m_distribution.block_size(process_id(m_process_group), numverts),
    identity_property_map());

  // TODO: set property on m_base?
}

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
template <typename Distribution, typename Source> 
BOOST_DISTRIB_CSR_GRAPH_TYPE::
compressed_sparse_row_graph(distributed_construct_inplace_from_sources_and_targets_t,
                            std::vector<Source>& sources,
                            std::vector<vertex_descriptor>& targets,
                            vertices_size_type numverts,
                            const ProcessGroup& pg,
                            const Distribution& dist,
                            const GraphProperty& prop)
  : m_process_group(pg),
    m_distribution(dist),
    m_base(m_distribution.block_size(process_id(m_process_group), numverts))
{ 
  // Convert linear indices to global indices
  for (edges_size_type i = 0; i < sources.size(); ++i) {
    sources[i] = m_distribution.local(sources[i]);
    targets[i] = make_vertex_descriptor(m_distribution(targets[i]), 
                                        m_distribution.local(targets[i]));
  }

  m_base.assign_sources_and_targets_global(
    sources, targets, m_distribution.block_size(process_id(m_process_group), numverts),
    identity_property_map());

  // TODO: set property on m_base?
}

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
template<typename Source>
BOOST_DISTRIB_CSR_GRAPH_TYPE::
compressed_sparse_row_graph(distributed_construct_inplace_from_sources_and_targets_t,
                            std::vector<Source>& sources,
                            std::vector<vertex_descriptor>& targets,
                            std::vector<edge_bundled>& edge_props,
                            vertices_size_type numverts,
                            const ProcessGroup& pg,
                            const GraphProperty& prop)
  : m_process_group(pg),
    m_distribution(parallel::block(m_process_group, numverts)),
    m_base(m_distribution.block_size(process_id(m_process_group), numverts))
{ 
  // Convert linear indices to global indices
  for (edges_size_type i = 0; i < sources.size(); ++i) {
    sources[i] = m_distribution.local(sources[i]);
    targets[i] = make_vertex_descriptor(m_distribution(targets[i]), 
                                        m_distribution.local(targets[i]));
  }

  m_base.assign_sources_and_targets_global(
    sources, targets, edge_props, 
    m_distribution.block_size(process_id(m_process_group), numverts),
    identity_property_map());

  // TODO: set property on m_base?
}

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
template <typename Distribution, typename Source> 
BOOST_DISTRIB_CSR_GRAPH_TYPE::
compressed_sparse_row_graph(distributed_construct_inplace_from_sources_and_targets_t,
                            std::vector<Source>& sources,
                            std::vector<vertex_descriptor>& targets,
                            std::vector<edge_bundled>& edge_props,
                            vertices_size_type numverts,
                            const ProcessGroup& pg,
                            const Distribution& dist,
                            const GraphProperty& prop)
  : m_process_group(pg),
    m_distribution(dist),
    m_base(m_distribution.block_size(process_id(m_process_group), numverts))
{ 
  // Convert linear indices to global indices
  for (edges_size_type i = 0; i < sources.size(); ++i) {
    sources[i] = m_distribution.local(sources[i]);
    targets[i] = make_vertex_descriptor(m_distribution(targets[i]), 
                                        m_distribution.local(targets[i]));
  }

  m_base.assign_sources_and_targets_global(
    sources, targets, edge_props, 
    m_distribution.block_size(process_id(m_process_group), numverts),
    identity_property_map());

  // TODO: set property on m_base?
}

//
// Old (untagged) ctors, these default to the unsorted sequential ctors
//
template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
template<typename InputIterator>
BOOST_DISTRIB_CSR_GRAPH_TYPE::
compressed_sparse_row_graph(InputIterator edge_begin, InputIterator edge_end,
                            vertices_size_type numverts,
                            const ProcessGroup& pg,
                            const GraphProperty& prop)
  : m_process_group(pg),
    m_distribution(parallel::block(m_process_group, numverts)),
    m_base(edges_are_unsorted_global,
           index_to_vertex_iterator<InputIterator, BOOST_DISTRIB_CSR_GRAPH_TYPE>(edge_begin, *this),
           index_to_vertex_iterator<InputIterator, BOOST_DISTRIB_CSR_GRAPH_TYPE>(edge_end, *this),
           m_distribution.block_size(process_id(m_process_group), numverts),
           get(vertex_local, *this),
           local_vertex<csr_vertex_owner_map<process_id_type, vertex_descriptor>, 
                        process_id_type> (get(vertex_owner, *this), process_id(pg)),
           prop)
           
{
}

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
template<typename InputIterator, typename EdgePropertyIterator>
BOOST_DISTRIB_CSR_GRAPH_TYPE::
compressed_sparse_row_graph(InputIterator edge_begin, InputIterator edge_end,
                            EdgePropertyIterator ep_iter,
                            vertices_size_type numverts,
                            const ProcessGroup& pg,
                            const GraphProperty& prop)
  : m_process_group(pg),

    m_distribution(parallel::block(m_process_group, numverts)),
    m_base(edges_are_unsorted_global,
           index_to_vertex_iterator<InputIterator, BOOST_DISTRIB_CSR_GRAPH_TYPE>(edge_begin, *this),
           index_to_vertex_iterator<InputIterator, BOOST_DISTRIB_CSR_GRAPH_TYPE>(edge_end, *this),
           ep_iter,
           m_distribution.block_size(process_id(m_process_group), numverts),
           get(vertex_local, *this),
           local_vertex<csr_vertex_owner_map<process_id_type, vertex_descriptor>, 
                        process_id_type> (get(vertex_owner, *this), process_id(pg)),
           prop)
{
}

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
template<typename InputIterator, typename Distribution>
BOOST_DISTRIB_CSR_GRAPH_TYPE::
compressed_sparse_row_graph(InputIterator edge_begin, InputIterator edge_end,
                            vertices_size_type numverts,
                            const ProcessGroup& pg,
                            const Distribution& dist,
                            const GraphProperty& prop)
  : m_process_group(pg),
    m_distribution(dist),
    m_base(edges_are_unsorted_global,
           index_to_vertex_iterator<InputIterator, BOOST_DISTRIB_CSR_GRAPH_TYPE>(edge_begin, *this),
           index_to_vertex_iterator<InputIterator, BOOST_DISTRIB_CSR_GRAPH_TYPE>(edge_end, *this),
           m_distribution.block_size(process_id(m_process_group), numverts),
           get(vertex_local, *this),
           local_vertex<csr_vertex_owner_map<process_id_type, vertex_descriptor>, 
                        process_id_type> (get(vertex_owner, *this), process_id(pg)),
           prop)
{
}

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
template<typename InputIterator, typename EdgePropertyIterator, 
         typename Distribution>
BOOST_DISTRIB_CSR_GRAPH_TYPE::
compressed_sparse_row_graph(InputIterator edge_begin, InputIterator edge_end,
                            EdgePropertyIterator ep_iter,
                            vertices_size_type numverts,
                            const ProcessGroup& pg,
                            const Distribution& dist,
                            const GraphProperty& prop)
  : m_process_group(pg),
    m_distribution(dist),
    m_base(edges_are_unsorted_global,
           index_to_vertex_iterator<InputIterator, BOOST_DISTRIB_CSR_GRAPH_TYPE>(edge_begin, *this),
           index_to_vertex_iterator<InputIterator, BOOST_DISTRIB_CSR_GRAPH_TYPE>(edge_end, *this),
           m_distribution.block_size(process_id(m_process_group), numverts),
           get(vertex_local, *this),
           local_vertex<csr_vertex_owner_map<process_id_type, vertex_descriptor>, 
                        process_id_type> (get(vertex_owner, *this), process_id(pg)),
           prop)
{
}

// -----------------------------------------------------------------
// Vertex Global Property Map
template<typename ProcessID, typename Key>
class csr_vertex_global_map
{
 public:
  // -----------------------------------------------------------------
  // Readable Property Map concept requirements
  typedef std::pair<ProcessID, Key> value_type;
  typedef value_type reference;
  typedef Key key_type;
  typedef readable_property_map_tag category;
};

template<typename ProcessID, typename Key>
inline std::pair<ProcessID, Key>
get(csr_vertex_global_map<ProcessID, Key>,
    typename csr_vertex_global_map<ProcessID, Key>::key_type k)
{
  const int local_index_bits = sizeof(Key) * CHAR_BIT - processor_bits;
  const Key local_index_mask = Key(-1) >> processor_bits;

  return std::pair<ProcessID, Key>(k >> local_index_bits,
                                   k & local_index_mask);
}

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
class property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, vertex_global_t>
{
 public:
  typedef csr_vertex_global_map<
            typename ProcessGroup::process_id_type,
            typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_descriptor> type;
  typedef type const_type;
};

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline
typename property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, vertex_global_t>::type
get(vertex_global_t, BOOST_DISTRIB_CSR_GRAPH_TYPE& g)
{
  typedef typename property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, vertex_global_t>
    ::type result_type;
  return result_type();
}

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline
std::pair<typename ProcessGroup::process_id_type,
          typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_descriptor>
get(vertex_global_t, BOOST_DISTRIB_CSR_GRAPH_TYPE& g,
    typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_descriptor k)
{
  return get(vertex_global, 
             const_cast<const BOOST_DISTRIB_CSR_GRAPH_TYPE&>(g), 
             k);
}

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline
typename property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, vertex_global_t>::const_type
get(vertex_global_t, const BOOST_DISTRIB_CSR_GRAPH_TYPE& g)
{
  typedef typename property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, vertex_global_t>
    ::const_type result_type;
  return result_type();
}

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline
std::pair<typename ProcessGroup::process_id_type,
          typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_descriptor>
get(vertex_global_t, const BOOST_DISTRIB_CSR_GRAPH_TYPE& g,
    typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_descriptor k)
{
  typedef typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_descriptor
    vertex_descriptor;
  typedef std::pair<typename ProcessGroup::process_id_type, vertex_descriptor>
    result_type;
  const int local_index_bits = 
    sizeof(vertex_descriptor) * CHAR_BIT - processor_bits;
  const vertex_descriptor local_index_mask = 
    vertex_descriptor(-1) >> processor_bits;

  return result_type(k >> local_index_bits, k & local_index_mask);
}

// -----------------------------------------------------------------
// Extra, common functions
template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_descriptor
vertex(typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertices_size_type i,
       const BOOST_DISTRIB_CSR_GRAPH_TYPE& g)
{
  return g.make_vertex_descriptor(g.distribution()(i), 
                                  g.distribution().local(i));
}

// Unlike for an adjacency_matrix, edge_range and edge take lg(out_degree(i))
// time
template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline std::pair<typename BOOST_DISTRIB_CSR_GRAPH_TYPE::out_edge_iterator,
                 typename BOOST_DISTRIB_CSR_GRAPH_TYPE::out_edge_iterator>
edge_range(typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_descriptor i,
           typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_descriptor j,
           const BOOST_DISTRIB_CSR_GRAPH_TYPE& g)
{
  typedef typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_descriptor Vertex;
  typedef typename BOOST_DISTRIB_CSR_GRAPH_TYPE::edges_size_type EdgeIndex;
  typedef typename std::vector<Vertex>::const_iterator adj_iter;
  typedef typename BOOST_DISTRIB_CSR_GRAPH_TYPE::out_edge_iterator out_edge_iter;
  typedef typename BOOST_DISTRIB_CSR_GRAPH_TYPE::edge_descriptor edge_desc;
  std::pair<adj_iter, adj_iter> raw_adjacencies = adjacent_vertices(i, g);
  std::pair<adj_iter, adj_iter> adjacencies =
    std::equal_range(raw_adjacencies.first, raw_adjacencies.second, j);
  EdgeIndex idx_begin = adjacencies.first - g.base().m_forward.m_column.begin();
  EdgeIndex idx_end = adjacencies.second - g.base().m_forward.m_column.begin();
  return std::make_pair(out_edge_iter(edge_desc(i, idx_begin)),
                        out_edge_iter(edge_desc(i, idx_end)));
}

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline std::pair<typename BOOST_DISTRIB_CSR_GRAPH_TYPE::edge_descriptor, bool>
edge(typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_descriptor i,
     typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_descriptor j,
     const BOOST_DISTRIB_CSR_GRAPH_TYPE& g)
{
  typedef typename BOOST_DISTRIB_CSR_GRAPH_TYPE::out_edge_iterator out_edge_iter;
  std::pair<out_edge_iter, out_edge_iter> range = edge_range(i, j, g);
  if (range.first == range.second)
    return std::make_pair(typename BOOST_DISTRIB_CSR_GRAPH_TYPE::edge_descriptor(),
                          false);
  else
    return std::make_pair(*range.first, true);
}

// A helper that turns requests for property maps for const graphs
// into property maps for non-const graphs.
template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS, typename Property>
class property_map<const BOOST_DISTRIB_CSR_GRAPH_TYPE, Property>
{
 public:
  typedef typename property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, Property>
    ::const_type type;
  typedef type const_type;
};

// -----------------------------------------------------------------
// Structural modifiers

#if 0
template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_descriptor
add_vertex(BOOST_DISTRIB_CSR_GRAPH_TYPE& g)
{ return g.add_vertex(); }

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_descriptor
add_vertex(const typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_bundled& p, 
           BOOST_DISTRIB_CSR_GRAPH_TYPE& g)
{ return g.add_vertex(p); }

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_descriptor
add_vertices(typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertices_size_type count, 
             BOOST_DISTRIB_CSR_GRAPH_TYPE& g)
{ return g.add_vertices(count); }

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS, typename InputIterator>
void 
add_edges(InputIterator first, InputIterator last,
          BOOST_DISTRIB_CSR_GRAPH_TYPE& g)
{ g.add_edges(first, last); }

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS, typename InputIterator, 
         typename EdgePropertyIterator>
void 
add_edges(InputIterator first, InputIterator last,
          EdgePropertyIterator ep_iter,
          EdgePropertyIterator ep_iter_end,
          BOOST_DISTRIB_CSR_GRAPH_TYPE& g)
{ return g.add_edges(first, last, ep_iter, ep_iter_end); }

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS, typename InputIterator>
void 
add_edges_sorted(InputIterator first, InputIterator last,
                 BOOST_DISTRIB_CSR_GRAPH_TYPE& g)
{ return g.add_edges_sorted(first, last); }

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS, typename InputIterator, 
         typename EdgePropertyIterator>
void 
add_edges_sorted(InputIterator first_sorted, InputIterator last_sorted,
                 EdgePropertyIterator ep_iter_sorted,
                 BOOST_DISTRIB_CSR_GRAPH_TYPE& g)
{ g.add_edges_sorted(first_sorted, last_sorted, ep_iter_sorted); }
#endif

// -----------------------------------------------------------------
// Vertex Owner Property Map
template<typename ProcessID, typename Key>
class csr_vertex_owner_map
{
 public:
  // -----------------------------------------------------------------
  // Readable Property Map concept requirements
  typedef ProcessID value_type;
  typedef value_type reference;
  typedef Key key_type;
  typedef readable_property_map_tag category;
};

template<typename ProcessID, typename Key>
inline ProcessID
get(csr_vertex_owner_map<ProcessID, Key> pm,
    typename csr_vertex_owner_map<ProcessID, Key>::key_type k)
{
  const int local_index_bits = sizeof(Key) * CHAR_BIT - processor_bits;
  return k >> local_index_bits;
}

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
class property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, vertex_owner_t>
{
 public:
  typedef csr_vertex_owner_map<
            typename ProcessGroup::process_id_type,
            typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_descriptor> type;
  typedef type const_type;
};

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline
typename property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, vertex_owner_t>::type
get(vertex_owner_t, BOOST_DISTRIB_CSR_GRAPH_TYPE& g)
{
  typedef typename property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, vertex_owner_t>
    ::type result_type;
  return result_type();
}

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline typename ProcessGroup::process_id_type
get(vertex_owner_t, BOOST_DISTRIB_CSR_GRAPH_TYPE& g,
    typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_descriptor k)
{
  return get(vertex_owner, 
             const_cast<const BOOST_DISTRIB_CSR_GRAPH_TYPE&>(g),
             k);
}

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline
typename property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, vertex_owner_t>::const_type
get(vertex_owner_t, const BOOST_DISTRIB_CSR_GRAPH_TYPE& g)
{
  typedef typename property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, vertex_owner_t>
    ::const_type result_type;
  return result_type();
}

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline typename ProcessGroup::process_id_type
get(vertex_owner_t, const BOOST_DISTRIB_CSR_GRAPH_TYPE& g,
    typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_descriptor k)
{
  typedef typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_descriptor
    vertex_descriptor;
  const int local_index_bits = 
    sizeof(vertex_descriptor) * CHAR_BIT - processor_bits;
  return k >> local_index_bits;
}

// -----------------------------------------------------------------
// Vertex Local Property Map
template<typename Key>
class csr_vertex_local_map
{
 public:
  // -----------------------------------------------------------------
  // Readable Property Map concept requirements
  typedef Key value_type;
  typedef value_type reference;
  typedef Key key_type;
  typedef readable_property_map_tag category;
};

template<typename Key>
inline Key
get(csr_vertex_local_map<Key> pm,
    typename csr_vertex_local_map<Key>::key_type k)
{
  const Key local_index_mask = Key(-1) >> processor_bits;
  return k & local_index_mask;
}

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
class property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, vertex_local_t>
{
 public:
  typedef csr_vertex_local_map<
            typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_descriptor> type;
  typedef type const_type;
};

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline
typename property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, vertex_local_t>::type
get(vertex_local_t, BOOST_DISTRIB_CSR_GRAPH_TYPE& g)
{
  typedef typename property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, vertex_local_t>
    ::type result_type;
  return result_type();
}

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_descriptor
get(vertex_local_t, BOOST_DISTRIB_CSR_GRAPH_TYPE& g,
    typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_descriptor k)
{
  return get(vertex_local, 
             const_cast<const BOOST_DISTRIB_CSR_GRAPH_TYPE&>(g),
             k);
}

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline
typename property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, vertex_local_t>::const_type
get(vertex_local_t, const BOOST_DISTRIB_CSR_GRAPH_TYPE& g)
{
  typedef typename property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, vertex_local_t>
    ::const_type result_type;
  return result_type();
}

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_descriptor
get(vertex_local_t, const BOOST_DISTRIB_CSR_GRAPH_TYPE& g,
    typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_descriptor k)
{
  typedef typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_descriptor 
    vertex_descriptor;
  const vertex_descriptor local_index_mask = 
    vertex_descriptor(-1) >> processor_bits;
  return k & local_index_mask;
}

// -----------------------------------------------------------------
// Vertex Index Property Map
template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
class property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, vertex_index_t>
{
  typedef typename property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, 
                                vertex_global_t>::const_type
    global_map;
  typedef typename BOOST_DISTRIB_CSR_GRAPH_TYPE::process_group_type
    process_group_type;

  typedef property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, vertex_local_t> local;

public:
  typedef local_property_map<process_group_type, 
                             global_map, 
                             typename local::type> type;
  typedef local_property_map<process_group_type, 
                             global_map, 
                             typename local::const_type> const_type;
};

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline
typename property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, vertex_index_t>::type
get(vertex_index_t, BOOST_DISTRIB_CSR_GRAPH_TYPE& g)
{
  typedef typename property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, vertex_index_t>
    ::type result_type;

  return result_type(g.process_group(), get(vertex_global, g),
                     get(vertex_local, g));
}

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertices_size_type
get(vertex_index_t, BOOST_DISTRIB_CSR_GRAPH_TYPE& g,
    typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_descriptor k)
{
  return get(vertex_local, g, k);
}

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline
typename property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, vertex_index_t>::const_type
get(vertex_index_t, const BOOST_DISTRIB_CSR_GRAPH_TYPE& g)
{
  typedef typename property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, vertex_index_t>
    ::const_type result_type;
  return result_type(g.process_group(), get(vertex_global, g),
                     get(vertex_local, g));
}

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertices_size_type
get(vertex_index_t, const BOOST_DISTRIB_CSR_GRAPH_TYPE& g,
    typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_descriptor k)
{
  return get(vertex_local, g, k);
}

// -----------------------------------------------------------------
// Vertex Local Index Property Map
template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
class property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, vertex_local_index_t>
  : public property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, vertex_local_t> { };

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline
typename property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, vertex_local_index_t>::type
get(vertex_local_index_t, BOOST_DISTRIB_CSR_GRAPH_TYPE& g)
{
  return get(vertex_local, g);
}

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertices_size_type
get(vertex_local_index_t, BOOST_DISTRIB_CSR_GRAPH_TYPE& g,
    typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_descriptor k)
{
  return get(vertex_local, g, k);
}

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline
typename property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, vertex_local_index_t>::const_type
get(vertex_local_index_t, const BOOST_DISTRIB_CSR_GRAPH_TYPE& g)
{
  return get(vertex_local, g);
}

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertices_size_type
get(vertex_local_index_t, const BOOST_DISTRIB_CSR_GRAPH_TYPE& g,
    typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_descriptor k)
{
  return get(vertex_local, g, k);
}

// -----------------------------------------------------------------
// Edge Global Property Map
template<typename ProcessID, typename Vertex, typename EdgeIndex>
class csr_edge_global_map
{
 public:
  // -----------------------------------------------------------------
  // Readable Property Map concept requirements
  typedef detail::csr_edge_descriptor<Vertex, EdgeIndex> key_type;
  typedef std::pair<ProcessID, detail::csr_edge_descriptor<Vertex, EdgeIndex> > value_type;
  typedef value_type reference;
  typedef readable_property_map_tag category;
};

template<typename ProcessID, typename Vertex, typename EdgeIndex>
inline std::pair<ProcessID, detail::csr_edge_descriptor<Vertex, EdgeIndex> >
get(csr_edge_global_map<ProcessID, Vertex, EdgeIndex> pm,
    typename csr_edge_global_map<ProcessID, Vertex, EdgeIndex>::key_type k)
{
  const int local_index_bits = sizeof(Vertex) * CHAR_BIT - processor_bits;
  const Vertex local_index_mask = Vertex(-1) >> processor_bits;
  return std::pair<ProcessID, detail::csr_edge_descriptor<Vertex, EdgeIndex> >
           ((k.src >> local_index_bits),
            detail::csr_edge_descriptor<Vertex, EdgeIndex>(k.src & local_index_mask, k.idx));
}

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
class property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, edge_global_t>
{
 public:
  typedef csr_edge_global_map<
            typename ProcessGroup::process_id_type,
            typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_descriptor,
            typename BOOST_DISTRIB_CSR_GRAPH_TYPE::edges_size_type> type;
  typedef type const_type;
};

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline
typename property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, edge_global_t>::type
get(edge_global_t, BOOST_DISTRIB_CSR_GRAPH_TYPE& g)
{
  typedef typename property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, edge_global_t>
    ::type result_type;
  return result_type();
}

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline
std::pair<typename ProcessGroup::process_id_type,
          typename BOOST_DISTRIB_CSR_GRAPH_TYPE::base_type::edge_descriptor>
get(edge_global_t, BOOST_DISTRIB_CSR_GRAPH_TYPE& g,
    typename BOOST_DISTRIB_CSR_GRAPH_TYPE::edge_descriptor k)
{
  return get(edge_global, 
             const_cast<const BOOST_DISTRIB_CSR_GRAPH_TYPE&>(g),
             k);
}

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline
typename property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, edge_global_t>::const_type
get(edge_global_t, const BOOST_DISTRIB_CSR_GRAPH_TYPE& g)
{
  typedef typename property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, edge_global_t>
    ::const_type result_type;
  return result_type();
}

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline
std::pair<typename ProcessGroup::process_id_type,
          typename BOOST_DISTRIB_CSR_GRAPH_TYPE::base_type::edge_descriptor>
get(edge_global_t, const BOOST_DISTRIB_CSR_GRAPH_TYPE& g,
    typename BOOST_DISTRIB_CSR_GRAPH_TYPE::edge_descriptor k)
{
  typedef typename BOOST_DISTRIB_CSR_GRAPH_TYPE::vertex_descriptor
    vertex_descriptor;

  const int local_index_bits = 
    sizeof(vertex_descriptor) * CHAR_BIT - processor_bits;
  const typename BOOST_DISTRIB_CSR_GRAPH_TYPE::edges_size_type local_index_mask =
    typename BOOST_DISTRIB_CSR_GRAPH_TYPE::edges_size_type(-1) >> processor_bits;
  
  typedef std::pair<typename ProcessGroup::process_id_type,
                    typename BOOST_DISTRIB_CSR_GRAPH_TYPE::base_type::edge_descriptor>
    result_type;

  return result_type(k.src >> local_index_bits,
                     typename BOOST_DISTRIB_CSR_GRAPH_TYPE::base_type::edge_descriptor
                       (k.src & local_index_mask, k.idx));
}

// -----------------------------------------------------------------
// Edge Index Property Map
template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
class property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, edge_index_t>
{
   typedef typename property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, edge_global_t>
    ::type global_map;

 public:
  typedef local_property_map<
            typename BOOST_DISTRIB_CSR_GRAPH_TYPE::process_group_type,
            global_map,
            typename property_map<typename BOOST_DISTRIB_CSR_GRAPH_TYPE::base_type, edge_index_t>::type
          > type;
  typedef type const_type;
};

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline
typename property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, edge_index_t>::type
get(edge_index_t, BOOST_DISTRIB_CSR_GRAPH_TYPE& g)
{
  typedef typename property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, edge_index_t>
    ::type result_type;
  return result_type(g.process_group(), get(edge_global, g),
                     get(edge_index, g.base()));
}

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline typename BOOST_DISTRIB_CSR_GRAPH_TYPE::edges_size_type
get(edge_index_t, BOOST_DISTRIB_CSR_GRAPH_TYPE& g,
    typename BOOST_DISTRIB_CSR_GRAPH_TYPE::edge_descriptor k)
{
  return k.idx;
}

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline
typename property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, edge_index_t>::const_type
get(edge_index_t, const BOOST_DISTRIB_CSR_GRAPH_TYPE& g)
{
  typedef typename property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, edge_index_t>
    ::const_type result_type;
  return result_type(g.process_group(), get(edge_global, g),
                     get(edge_index, g.base()));
}

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS>
inline typename BOOST_DISTRIB_CSR_GRAPH_TYPE::edges_size_type
get(edge_index_t, const BOOST_DISTRIB_CSR_GRAPH_TYPE& g,
    typename BOOST_DISTRIB_CSR_GRAPH_TYPE::edge_descriptor k)
{
  return k.idx;
}

template <BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS, typename Tag>
class property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, Tag> {
  typedef BOOST_DISTRIB_CSR_GRAPH_TYPE graph_type;
  typedef typename graph_type::process_group_type process_group_type;
  typedef typename graph_type::base_type base_graph_type;
  typedef typename property_map<base_graph_type, Tag>::type
    local_pmap;
  typedef typename property_map<base_graph_type, Tag>::const_type
    local_const_pmap;

  typedef graph_traits<graph_type> traits;
  typedef typename graph_traits<base_graph_type>::vertex_descriptor local_vertex;
  typedef typename property_traits<local_pmap>::key_type local_key_type;

  typedef typename property_traits<local_pmap>::value_type value_type;

  typedef typename property_map<graph_type, vertex_global_t>::const_type
    vertex_global_map;
  typedef typename property_map<graph_type, edge_global_t>::const_type
    edge_global_map;

  typedef typename mpl::if_<is_same<typename detail::property_kind_from_graph<base_graph_type, Tag>::type,
                                    vertex_property_tag>,
                            vertex_global_map, edge_global_map>::type
    global_map;

public:
  typedef ::boost::parallel::distributed_property_map<
            process_group_type, global_map, local_pmap> type;

  typedef ::boost::parallel::distributed_property_map<
            process_group_type, global_map, local_const_pmap> const_type;
};

template <BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS, typename Tag>
typename property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, Tag>::type
get(Tag tag, BOOST_DISTRIB_CSR_GRAPH_TYPE& g)
{
  typedef BOOST_DISTRIB_CSR_GRAPH_TYPE Graph;
  typedef typename property_map<Graph, Tag>::type result_type;
  typedef typename property_traits<result_type>::value_type value_type;
  typedef typename property_reduce<Tag>::template apply<value_type>
    reduce;

  typedef typename mpl::if_<is_same<typename detail::property_kind_from_graph<Graph, Tag>::type,
                                    vertex_property_tag>,
                            vertex_global_t, edge_global_t>::type
    global_map_t;

  return result_type(g.process_group(), get(global_map_t(), g),
                     get(tag, g.base()), reduce());
}

template<BOOST_DISTRIB_CSR_GRAPH_TEMPLATE_PARMS, typename Tag>
typename property_map<BOOST_DISTRIB_CSR_GRAPH_TYPE, Tag>::const_type
get(Tag tag, const BOOST_DISTRIB_CSR_GRAPH_TYPE& g)
{
  typedef BOOST_DISTRIB_CSR_GRAPH_TYPE Graph;
  typedef typename property_map<Graph, Tag>::const_type result_type;
  typedef typename property_traits<result_type>::value_type value_type;
  typedef typename property_reduce<Tag>::template apply<value_type>
    reduce;

  typedef typename property_traits<result_type>::key_type descriptor;
  typedef typename graph_traits<Graph>::vertex_descriptor vertex_descriptor;
  typedef typename mpl::if_<is_same<descriptor, vertex_descriptor>,
                            vertex_global_t, edge_global_t>::type
    global_map_t;

  return result_type(g.process_group(), get(global_map_t(), g),
                     get(tag, g.base()), reduce());
}

namespace mpi {
  template<typename Vertex, typename EdgeIndex>
  struct is_mpi_datatype<boost::detail::csr_edge_descriptor<Vertex, EdgeIndex> >
    : mpl::true_ { };
}

namespace serialization {
  template<typename Vertex, typename EdgeIndex>
  struct is_bitwise_serializable<boost::detail::csr_edge_descriptor<Vertex, EdgeIndex> >
    : mpl::true_ { };

  template<typename Vertex, typename EdgeIndex>
  struct implementation_level<boost::detail::csr_edge_descriptor<Vertex, EdgeIndex> >
   : mpl::int_<object_serializable> {} ;

  template<typename Vertex, typename EdgeIndex>
  struct tracking_level<boost::detail::csr_edge_descriptor<Vertex, EdgeIndex> >
   : mpl::int_<track_never> {} ;

}

} // end namespace boost

#endif // BOOST_GRAPH_DISTRIBUTED_CSR_HPP

/* compressed_sparse_row_graph.hpp
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
*/