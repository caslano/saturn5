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
                          &indices[0],
                          edges.empty()? (int*)0 : &edges[0],
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