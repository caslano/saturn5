// Copyright (C) 2007 Trustees of Indiana University

// Authors: Douglas Gregor
//          Andrew Lumsdaine

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/** @file graph_communicator.hpp
 *
 *  This header defines facilities to support MPI communicators with
 *  graph topologies, using the graph interface defined by the Boost
 *  Graph Library. One can construct a communicator whose topology is
 *  described by any graph meeting the requirements of the Boost Graph
 *  Library's graph concepts. Likewise, any communicator that has a
 *  graph topology can be viewed as a graph by the Boost Graph
 *  Library, permitting one to use the BGL's graph algorithms on the
 *  process topology.
 */
#ifndef BOOST_MPI_GRAPH_COMMUNICATOR_HPP
#define BOOST_MPI_GRAPH_COMMUNICATOR_HPP

#include <boost/mpi/communicator.hpp>
#include <vector>
#include <utility>

// Headers required to implement graph topologies
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>
#include <boost/iterator/counting_iterator.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/shared_array.hpp>
#include <boost/assert.hpp>

namespace boost { namespace mpi {

/**
 * @brief An MPI communicator with a graph topology.
 *
 * A @c graph_communicator is a communicator whose topology is
 * expressed as a graph. Graph communicators have the same
 * functionality as (intra)communicators, but also allow one to query
 * the relationships among processes. Those relationships are
 * expressed via a graph, using the interface defined by the Boost
 * Graph Library. The @c graph_communicator class meets the
 * requirements of the BGL Graph, Incidence Graph, Adjacency Graph,
 * Vertex List Graph, and Edge List Graph concepts.
 */
class BOOST_MPI_DECL graph_communicator : public communicator
{
  friend class communicator;

  /**
   * INTERNAL ONLY
   *
   * Construct a graph communicator given a shared pointer to the
   * underlying MPI_Comm. This operation is used for "casting" from a
   * communicator to a graph communicator.
   */
  explicit graph_communicator(const shared_ptr<MPI_Comm>& comm_ptr)
  {
#ifndef BOOST_DISABLE_ASSERTS
    int status;
    BOOST_MPI_CHECK_RESULT(MPI_Topo_test, ((MPI_Comm)*this, &status));
    BOOST_ASSERT(status == MPI_GRAPH);
#endif
    this->comm_ptr = comm_ptr;
  }

public:
  /**
   * Build a new Boost.MPI graph communicator based on the MPI
   * communicator @p comm with graph topology.
   *
   * @p comm may be any valid MPI communicator. If @p comm is
   * MPI_COMM_NULL, an empty communicator (that cannot be used for
   * communication) is created and the @p kind parameter is
   * ignored. Otherwise, the @p kind parameter determines how the
   * Boost.MPI communicator will be related to @p comm:
   *
   *   - If @p kind is @c comm_duplicate, duplicate @c comm to create
   *   a new communicator. This new communicator will be freed when
   *   the Boost.MPI communicator (and all copies of it) is
   *   destroyed. This option is only permitted if the underlying MPI
   *   implementation supports MPI 2.0; duplication of
   *   intercommunicators is not available in MPI 1.x.
   *
   *   - If @p kind is @c comm_take_ownership, take ownership of @c
   *   comm. It will be freed automatically when all of the Boost.MPI
   *   communicators go out of scope.
   *
   *   - If @p kind is @c comm_attach, this Boost.MPI communicator
   *   will reference the existing MPI communicator @p comm but will
   *   not free @p comm when the Boost.MPI communicator goes out of
   *   scope. This option should only be used when the communicator is
   *   managed by the user.
   */
  graph_communicator(const MPI_Comm& comm, comm_create_kind kind)
    : communicator(comm, kind)
  { 
#ifndef BOOST_DISABLE_ASSERTS
    int status;
    BOOST_MPI_CHECK_RESULT(MPI_Topo_test, ((MPI_Comm)*this, &status));
    BOOST_ASSERT(status == MPI_GRAPH);
#endif
  }

  /**
   *  Create a new communicator whose topology is described by the
   *  given graph. The indices of the vertices in the graph will be
   *  assumed to be the ranks of the processes within the
   *  communicator. There may be fewer vertices in the graph than
   *  there are processes in the communicator; in this case, the
   *  resulting communicator will be a NULL communicator.
   *
   *  @param comm The communicator that the new, graph communicator
   *  will be based on. 
   * 
   *  @param graph Any type that meets the requirements of the
   *  Incidence Graph and Vertex List Graph concepts from the Boost Graph
   *  Library. This structure of this graph will become the topology
   *  of the communicator that is returned.
   *
   *  @param reorder Whether MPI is permitted to re-order the process
   *  ranks within the returned communicator, to better optimize
   *  communication. If false, the ranks of each process in the
   *  returned process will match precisely the rank of that process
   *  within the original communicator.
   */
  template<typename Graph>
  explicit 
  graph_communicator(const communicator& comm, const Graph& graph, 
                     bool reorder = false);

  /**
   *  Create a new communicator whose topology is described by the
   *  given graph. The rank map (@p rank) gives the mapping from
   *  vertices in the graph to ranks within the communicator. There
   *  may be fewer vertices in the graph than there are processes in
   *  the communicator; in this case, the resulting communicator will
   *  be a NULL communicator.
   *
   *  @param comm The communicator that the new, graph communicator
   *  will be based on. The ranks in @c rank refer to the processes in
   *  this communicator.
   * 
   *  @param graph Any type that meets the requirements of the
   *  Incidence Graph and Vertex List Graph concepts from the Boost Graph
   *  Library. This structure of this graph will become the topology
   *  of the communicator that is returned.
   *
   *  @param rank This map translates vertices in the @c graph into
   *  ranks within the current communicator. It must be a Readable
   *  Property Map (see the Boost Property Map library) whose key type
   *  is the vertex type of the @p graph and whose value type is @c
   *  int.
   *
   *  @param reorder Whether MPI is permitted to re-order the process
   *  ranks within the returned communicator, to better optimize
   *  communication. If false, the ranks of each process in the
   *  returned process will match precisely the rank of that process
   *  within the original communicator.
   */
  template<typename Graph, typename RankMap>
  explicit 
  graph_communicator(const communicator& comm, const Graph& graph, 
                     RankMap rank, bool reorder = false);

protected:
  /**
   * INTERNAL ONLY
   *
   * Used by the constructors to create the new communicator with a
   * graph topology.
   */
  template<typename Graph, typename RankMap>
  void
  setup_graph(const communicator& comm, const Graph& graph, RankMap rank, 
              bool reorder);
};

/****************************************************************************
 *  Implementation Details                                                  *
 ****************************************************************************/

template<typename Graph>
graph_communicator::graph_communicator(const communicator& comm, 
                                       const Graph& graph, 
                                       bool reorder)
{
  this->setup_graph(comm, graph, get(vertex_index, graph), reorder);
}

template<typename Graph, typename RankMap>
graph_communicator::graph_communicator(const communicator& comm, 
                                       const Graph& graph, 
                                       RankMap rank, bool reorder)
{
  this->setup_graph(comm, graph, rank, reorder);
}


template<typename Graph, typename RankMap>
void
graph_communicator::setup_graph(const communicator& comm, const Graph& graph, 
                                RankMap rank, bool reorder)
{
  typedef typename graph_traits<Graph>::vertex_descriptor vertex_descriptor;

  // Build a mapping from ranks to vertices
  std::vector<vertex_descriptor> vertex_with_rank(num_vertices(graph));
  if (vertex_with_rank.empty())
    return;

  BGL_FORALL_VERTICES_T(v, graph, Graph)
    vertex_with_rank[get(rank, v)] = v;

  // Build the representation of the graph required by
  // MPI_Graph_create.
  std::vector<int> indices(num_vertices(graph));
  std::vector<int> edges;
  int nvertices = indices.size();
  for (int vertex_index = 0; vertex_index < nvertices; ++vertex_index) {
    vertex_descriptor v = vertex_with_rank[vertex_index];

    BGL_FORALL_OUTEDGES_T(v, e, graph, Graph)
      edges.push_back(get(rank, target(e, graph)));

    indices[vertex_index] = edges.size();
  }

  // Create the new communicator
  MPI_Comm newcomm;
  BOOST_MPI_CHECK_RESULT(MPI_Graph_create,
                         ((MPI_Comm)comm, 
                          nvertices,
                          detail::c_data(indices),
                          detail::c_data(edges),
                          reorder,
                          &newcomm));
  this->comm_ptr.reset(new MPI_Comm(newcomm), comm_free());
}

/****************************************************************************
 *  Communicator with Graph Topology as BGL Graph                           *
 ****************************************************************************/
namespace detail {
  /**
   *  INTERNAL ONLY
   *
   *  The iterator used to access the outgoing edges within a
   *  communicator's graph topology.
   */
  class comm_out_edge_iterator
    : public iterator_facade<comm_out_edge_iterator, 
                             std::pair<int, int>,
                             random_access_traversal_tag,
                             const std::pair<int, int>&, 
                             int>
  {
  public:
    comm_out_edge_iterator() { }

    comm_out_edge_iterator(int source, shared_array<int> neighbors, int index)
      : edge(source, -1), neighbors(neighbors), index(index) { }

  protected:
    friend class boost::iterator_core_access;

    const std::pair<int, int>& dereference() const
    {
      edge.second = neighbors[index];
      return edge;
    }

    bool equal(const comm_out_edge_iterator& other) const
    {
      return (edge.first == other.edge.first
              && index == other.index);
    }

    void increment() { ++index; }

    void decrement() { --index; }

    void advance(int n) { index += n; }

    int distance_to(const comm_out_edge_iterator& other) const
    {
      return other.index - index;
    }

    mutable std::pair<int, int> edge;
    shared_array<int> neighbors;
    int index;
  };

  /**
   *  INTERNAL ONLY
   *
   *  The iterator used to access the adjacent vertices within a
   *  communicator's graph topology.
   */
  class comm_adj_iterator
    : public iterator_facade<comm_adj_iterator, 
                             int,
                             random_access_traversal_tag,
                             int, 
                             int>
  {
  public:
    comm_adj_iterator() { }

    comm_adj_iterator(shared_array<int> neighbors, int index)
      : neighbors(neighbors), index(index) { }

  protected:
    friend class boost::iterator_core_access;

    int dereference() const { return neighbors[index]; }

    bool equal(const comm_adj_iterator& other) const
    {
      return (neighbors == other.neighbors
              && index == other.index);
    }

    void increment() { ++index; }

    void decrement() { --index; }

    void advance(int n) { index += n; }

    int distance_to(const comm_adj_iterator& other) const
    {
      return other.index - index;
    }

    shared_array<int> neighbors;
    int index;
  };

  /**
   *  INTERNAL ONLY
   *
   *  The iterator used to access the edges in a communicator's graph
   *  topology.
   */
  class comm_edge_iterator
    : public iterator_facade<comm_edge_iterator, 
                             std::pair<int, int>,
                             forward_traversal_tag,
                             const std::pair<int, int>&, 
                             int>
  {
  public:
    comm_edge_iterator() { }

    /// Constructor for a past-the-end iterator
    comm_edge_iterator(int nedges) : edge_index(nedges) { }

    comm_edge_iterator(shared_array<int> indices, shared_array<int> edges)
      : indices(indices), edges(edges), edge_index(0), edge(0, 0)
    { }

  protected:
    friend class boost::iterator_core_access;

    const std::pair<int, int>& dereference() const
    {
      while (edge_index == indices[edge.first])
        ++edge.first;
      edge.second = edges[edge_index];
      return edge;
    }

    bool equal(const comm_edge_iterator& other) const
    {
      return edge_index == other.edge_index;
    }

    void increment() 
    { 
      ++edge_index; 
    }

    shared_array<int> indices;
    shared_array<int> edges;
    int edge_index;
    mutable std::pair<int, int> edge;
  };

} // end namespace detail

// Incidence Graph requirements

/**
 * @brief Returns the source vertex from an edge in the graph topology
 * of a communicator.
 */
inline int source(const std::pair<int, int>& edge, const graph_communicator&)
{
  return edge.first;
}

/**
 * @brief Returns the target vertex from an edge in the graph topology
 * of a communicator.
 */
inline int target(const std::pair<int, int>& edge, const graph_communicator&)
{
  return edge.second;
}

/**
 * @brief Returns an iterator range containing all of the edges
 * outgoing from the given vertex in a graph topology of a
 * communicator.
 */
std::pair<detail::comm_out_edge_iterator, detail::comm_out_edge_iterator>
out_edges(int vertex, const graph_communicator& comm);


/**
 * @brief Returns the out-degree of a vertex in the graph topology of
 * a communicator.
 */
int out_degree(int vertex, const graph_communicator& comm);

// Adjacency Graph requirements

/**
 * @brief Returns an iterator range containing all of the neighbors of
 * the given vertex in the communicator's graph topology.
 */
std::pair<detail::comm_adj_iterator, detail::comm_adj_iterator>
adjacent_vertices(int vertex, const graph_communicator& comm);

// Vertex List Graph requirements

/**
 * @brief Returns an iterator range that contains all of the vertices
 * with the communicator's graph topology, i.e., all of the process
 * ranks in the communicator.
 */
inline std::pair<counting_iterator<int>, counting_iterator<int> >
vertices(const graph_communicator& comm)
{
  return std::make_pair(counting_iterator<int>(0),
                        counting_iterator<int>(comm.size()));
}

/**
 *  @brief Returns the number of vertices within the graph topology of
 *  the communicator, i.e., the number of processes in the
 *  communicator.
 */
inline int num_vertices(const graph_communicator& comm) { return comm.size(); }

// Edge List Graph requirements

/**
 * @brief Returns an iterator range that contains all of the edges
 * with the communicator's graph topology.
 */
std::pair<detail::comm_edge_iterator, detail::comm_edge_iterator>
edges(const graph_communicator& comm);

/**
 * @brief Returns the number of edges in the communicator's graph
 * topology.
 */
int num_edges(const graph_communicator& comm);

// Property Graph requirements

/**
 *  @brief Returns a property map that maps from vertices in a
 *  communicator's graph topology to their index values. 
 *
 *  Since the vertices are ranks in the communicator, the returned
 *  property map is the identity property map.
 */
inline identity_property_map get(vertex_index_t, const graph_communicator&)
{
  return identity_property_map();
}

/**
 * @brief Returns the index of a vertex in the communicator's graph
 * topology.
 *
 * Since the vertices are ranks in the communicator, this is the
 *  identity function.
 */
inline int get(vertex_index_t, const graph_communicator&, int vertex)
{
  return vertex;
}

} } // end namespace boost::mpi

namespace boost {

/**
 * @brief Traits structure that allows a communicator with graph
 * topology to be view as a graph by the Boost Graph Library.
 *
 * The specialization of @c graph_traits for an MPI communicator
 * allows a communicator with graph topology to be viewed as a
 * graph. An MPI communicator with graph topology meets the
 * requirements of the Graph, Incidence Graph, Adjacency Graph, Vertex
 * List Graph, and Edge List Graph concepts from the Boost Graph
 * Library.
 */
template<>
struct graph_traits<mpi::graph_communicator> {
  // Graph concept requirements
  typedef int                        vertex_descriptor;
  typedef std::pair<int, int>        edge_descriptor;
  typedef directed_tag               directed_category;
  typedef disallow_parallel_edge_tag edge_parallel_category;
  
  /**
   * INTERNAL ONLY
   */
  struct traversal_category
    : incidence_graph_tag, 
      adjacency_graph_tag, 
      vertex_list_graph_tag, 
      edge_list_graph_tag 
  { 
  };

  /**
   * @brief Returns a vertex descriptor that can never refer to any
   * valid vertex.
   */
  static vertex_descriptor null_vertex() { return -1; }

  // Incidence Graph requirements
  typedef mpi::detail::comm_out_edge_iterator out_edge_iterator;
  typedef int degree_size_type;

  // Adjacency Graph requirements
  typedef mpi::detail::comm_adj_iterator adjacency_iterator;

  // Vertex List Graph requirements
  typedef counting_iterator<int> vertex_iterator;
  typedef int                    vertices_size_type;

  // Edge List Graph requirements
  typedef mpi::detail::comm_edge_iterator edge_iterator;
  typedef int                             edges_size_type;
};

// Property Graph requirements

/**
 * INTERNAL ONLY
 */
template<>
struct property_map<mpi::graph_communicator, vertex_index_t>
{
  typedef identity_property_map type;
  typedef identity_property_map const_type;
};

} // end namespace boost



#endif // BOOST_MPI_GRAPH_COMMUNICATOR_HPP

/* graph_communicator.hpp
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
*/