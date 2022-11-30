// Copyright (C) 2007 Douglas Gregor 
// Copyright (C) 2007 Hartmut Kaiser

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// TODO:
//   - Cache (some) remote vertex names?
#ifndef BOOST_GRAPH_DISTRIBUTED_NAMED_GRAPH_HPP
#define BOOST_GRAPH_DISTRIBUTED_NAMED_GRAPH_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <boost/assert.hpp>
#include <boost/core/uncaught_exceptions.hpp>
#include <boost/graph/named_graph.hpp>
#include <boost/functional/hash.hpp>
#include <boost/variant.hpp>
#include <boost/graph/parallel/simple_trigger.hpp>
#include <boost/graph/parallel/process_group.hpp>
#include <boost/graph/parallel/detail/property_holders.hpp>

namespace boost { namespace graph { namespace distributed {

using boost::parallel::trigger_receive_context;
using boost::detail::parallel::pair_with_property;

/*******************************************************************
 * Hashed distribution of named entities                           *
 *******************************************************************/

template<typename T>
struct hashed_distribution
{
  template<typename ProcessGroup>
  hashed_distribution(const ProcessGroup& pg, std::size_t /*num_vertices*/ = 0)
    : n(num_processes(pg)) { }

  int operator()(const T& value) const 
  {
    return hasher(value) % n;
  }

  std::size_t n;
  hash<T> hasher;
};

/// Specialization for named graphs
template <typename InDistribution, typename VertexProperty, typename VertexSize,
          typename ProcessGroup,
          typename ExtractName 
            = typename internal_vertex_name<VertexProperty>::type>
struct select_distribution
{
private:
  /// The type used to name vertices in the graph
  typedef typename remove_cv<
            typename remove_reference<
              typename ExtractName::result_type>::type>::type
    vertex_name_type;

public:
  /**
   *  The @c type field provides a distribution object that maps
   *  vertex names to processors. The distribution object will be
   *  constructed with the process group over which communication will
   *  occur. The distribution object shall also be a function
   *  object mapping from the type of the name to a processor number
   *  in @c [0, @c p) (for @c p processors). By default, the mapping
   *  function uses the @c boost::hash value of the name, modulo @c p.
   */
  typedef typename mpl::if_<is_same<InDistribution, defaultS>,
                            hashed_distribution<vertex_name_type>,
                            InDistribution>::type 
    type;

  /// for named graphs the default type is the same as the stored distribution 
  /// type
  typedef type default_type;
};

/// Specialization for non-named graphs
template <typename InDistribution, typename VertexProperty, typename VertexSize,
          typename ProcessGroup>
struct select_distribution<InDistribution, VertexProperty, VertexSize, 
                           ProcessGroup, void>
{
  /// the distribution type stored in the graph for non-named graphs should be
  /// the variant_distribution type
  typedef typename mpl::if_<is_same<InDistribution, defaultS>,
                            boost::parallel::variant_distribution<ProcessGroup, 
                                                                  VertexSize>,
                            InDistribution>::type type;

  /// default_type is used as the distribution functor for the
  /// adjacency_list, it should be parallel::block by default
  typedef typename mpl::if_<is_same<InDistribution, defaultS>,
                            boost::parallel::block, type>::type
    default_type;
};


/*******************************************************************
 * Named graph mixin                                               *
 *******************************************************************/

/**
 * named_graph is a mixin that provides names for the vertices of a
 * graph, including a mapping from names to vertices. Graph types that
 * may or may not be have vertex names (depending on the properties
 * supplied by the user) should use maybe_named_graph.
 *
 * Template parameters:
 *
 *   Graph: the graph type that derives from named_graph
 *
 *   Vertex: the type of a vertex descriptor in Graph. Note: we cannot
 *   use graph_traits here, because the Graph is not yet defined.
 *
 *   VertexProperty: the type of the property stored along with the
 *   vertex.
 *
 *   ProcessGroup: the process group over which the distributed name
 *   graph mixin will communicate.
 */
template<typename Graph, typename Vertex, typename Edge, typename Config>
class named_graph
{
public:
  /// Messages passed within the distributed named graph
  enum message_kind {
    /**
     * Requests the addition of a vertex on a remote processor. The
     * message data is a @c vertex_name_type.
     */
    msg_add_vertex_name,

    /**
     * Requests the addition of a vertex on a remote processor. The
     * message data is a @c vertex_name_type. The remote processor
     * will send back a @c msg_add_vertex_name_reply message
     * containing the vertex descriptor.
     */
    msg_add_vertex_name_with_reply,

    /**
     * Requests the vertex descriptor corresponding to the given
     * vertex name. The remote process will reply with a 
     * @c msg_find_vertex_reply message containing the answer.
     */
    msg_find_vertex,

    /**
     * Requests the addition of an edge on a remote processor. The
     * data stored in these messages is a @c pair<source, target>@,
     * where @c source and @c target may be either names (of type @c
     * vertex_name_type) or vertex descriptors, depending on what
     * information we have locally.  
     */
    msg_add_edge_name_name,
    msg_add_edge_vertex_name,
    msg_add_edge_name_vertex,

    /**
     * These messages are identical to msg_add_edge_*_*, except that
     * the process actually adding the edge will send back a @c
     * pair<edge_descriptor,bool>
     */
    msg_add_edge_name_name_with_reply,
    msg_add_edge_vertex_name_with_reply,
    msg_add_edge_name_vertex_with_reply,

    /**
     * Requests the addition of an edge with a property on a remote
     * processor. The data stored in these messages is a @c
     * pair<vertex_property_type, pair<source, target>>@, where @c
     * source and @c target may be either names (of type @c
     * vertex_name_type) or vertex descriptors, depending on what
     * information we have locally.
     */
    msg_add_edge_name_name_with_property,
    msg_add_edge_vertex_name_with_property,
    msg_add_edge_name_vertex_with_property,

    /**
     * These messages are identical to msg_add_edge_*_*_with_property,
     * except that the process actually adding the edge will send back
     * a @c pair<edge_descriptor,bool>.
     */
    msg_add_edge_name_name_with_reply_and_property,
    msg_add_edge_vertex_name_with_reply_and_property,
    msg_add_edge_name_vertex_with_reply_and_property
  };

  /// The vertex descriptor type
  typedef Vertex vertex_descriptor;
  
  /// The edge descriptor type
  typedef Edge edge_descriptor;

  /// The vertex property type
  typedef typename Config::vertex_property_type vertex_property_type;
  
  /// The vertex property type
  typedef typename Config::edge_property_type edge_property_type;
  
  /// The type used to extract names from the property structure
  typedef typename internal_vertex_name<vertex_property_type>::type
    extract_name_type;

  /// The type used to name vertices in the graph
  typedef typename remove_cv<
            typename remove_reference<
              typename extract_name_type::result_type>::type>::type
    vertex_name_type;

  /// The type used to distribute named vertices in the graph
  typedef typename Config::distribution_type distribution_type;
  typedef typename Config::base_distribution_type base_distribution_type;

  /// The type used for communication in the distributed structure
  typedef typename Config::process_group_type process_group_type;

  /// Type used to identify processes
  typedef typename process_group_type::process_id_type process_id_type;

  /// a reference to this class, which is used for disambiguation of the 
  //  add_vertex function
  typedef named_graph named_graph_type;
  
  /// Structure returned when adding a vertex by vertex name
  struct lazy_add_vertex;
  friend struct lazy_add_vertex;

  /// Structure returned when adding an edge by vertex name
  struct lazy_add_edge;
  friend struct lazy_add_edge;

  /// Structure returned when adding an edge by vertex name with a property
  struct lazy_add_edge_with_property;
  friend struct lazy_add_edge_with_property;

  explicit named_graph(const process_group_type& pg);

  named_graph(const process_group_type& pg, const base_distribution_type& distribution);

  /// Set up triggers, but only for the BSP process group
  void setup_triggers();

  /// Retrieve the derived instance
  Graph&       derived()       { return static_cast<Graph&>(*this); }
  const Graph& derived() const { return static_cast<const Graph&>(*this); }

  /// Retrieve the process group
  process_group_type&       process_group()       { return process_group_; }
  const process_group_type& process_group() const { return process_group_; }

  // Retrieve the named distribution
  distribution_type&       named_distribution()       { return distribution_; }
  const distribution_type& named_distribution() const { return distribution_; }

  /// Notify the named_graph that we have added the given vertex. This
  /// is a no-op.
  void added_vertex(Vertex) { }

  /// Notify the named_graph that we are removing the given
  /// vertex. This is a no-op.
  template <typename VertexIterStability>
  void removing_vertex(Vertex, VertexIterStability) { }

  /// Notify the named_graph that we are clearing the graph
  void clearing_graph() { }

  /// Retrieve the owner of a given vertex based on the properties
  /// associated with that vertex. This operation just returns the
  /// number of the local processor, adding all vertices locally.
  process_id_type owner_by_property(const vertex_property_type&);

protected:
  void 
  handle_add_vertex_name(int source, int tag, const vertex_name_type& msg,
                         trigger_receive_context);

  vertex_descriptor 
  handle_add_vertex_name_with_reply(int source, int tag, 
                                    const vertex_name_type& msg,
                                    trigger_receive_context);

  boost::parallel::detail::untracked_pair<vertex_descriptor, bool>
  handle_find_vertex(int source, int tag, const vertex_name_type& msg,
                     trigger_receive_context);

  template<typename U, typename V>
  void handle_add_edge(int source, int tag, const boost::parallel::detail::untracked_pair<U, V>& msg,
                       trigger_receive_context);

  template<typename U, typename V>
  boost::parallel::detail::untracked_pair<edge_descriptor, bool> 
  handle_add_edge_with_reply(int source, int tag, const boost::parallel::detail::untracked_pair<U, V>& msg,
                             trigger_receive_context);

  template<typename U, typename V>
  void 
  handle_add_edge_with_property
    (int source, int tag, 
     const pair_with_property<U, V, edge_property_type>& msg,
     trigger_receive_context);

  template<typename U, typename V>
  boost::parallel::detail::untracked_pair<edge_descriptor, bool> 
  handle_add_edge_with_reply_and_property
    (int source, int tag, 
     const pair_with_property<U, V, edge_property_type>& msg,
     trigger_receive_context);

  /// The process group for this distributed data structure
  process_group_type process_group_;

  /// The distribution we will use to map names to processors
  distribution_type distribution_;
};

/// Helper macro containing the template parameters of named_graph
#define BGL_NAMED_GRAPH_PARAMS \
  typename Graph, typename Vertex, typename Edge, typename Config
/// Helper macro containing the named_graph<...> instantiation
#define BGL_NAMED_GRAPH \
  named_graph<Graph, Vertex, Edge, Config>

/**
 * Data structure returned from add_vertex that will "lazily" add the
 * vertex, either when it is converted to a @c vertex_descriptor or
 * when the most recent copy has been destroyed.
 */
template<BGL_NAMED_GRAPH_PARAMS>
struct BGL_NAMED_GRAPH::lazy_add_vertex
{
  /// Construct a new lazyily-added vertex
  lazy_add_vertex(named_graph& self, const vertex_name_type& name)
    : self(self), name(name), committed(false) { }

  /// Transfer responsibility for adding the vertex from the source of
  /// the copy to the newly-constructed opbject.
  lazy_add_vertex(const lazy_add_vertex& other)
    : self(other.self), name(other.name), committed(other.committed)
  {
    other.committed = true;
  }

  /// If the vertex has not been added yet, add it
  ~lazy_add_vertex();

  /// Add the vertex and return its descriptor. This conversion can
  /// only occur once, and only when this object is responsible for
  /// creating the vertex.
  operator vertex_descriptor() const { return commit(); }

  /// Add the vertex and return its descriptor. This can only be
  /// called once, and only when this object is responsible for
  /// creating the vertex.
  vertex_descriptor commit() const;

protected:
  named_graph&     self;
  vertex_name_type name;
  mutable bool     committed;
};

template<BGL_NAMED_GRAPH_PARAMS>
BGL_NAMED_GRAPH::lazy_add_vertex::~lazy_add_vertex()
{
  typedef typename BGL_NAMED_GRAPH::process_id_type process_id_type;

  /// If this vertex has already been created or will be created by
  /// someone else, or if someone threw an exception, we will not
  /// create the vertex now.
  if (committed || boost::core::uncaught_exceptions() > 0)
    return;

  committed = true;

  process_id_type owner = self.named_distribution()(name);
  if (owner == process_id(self.process_group()))
    /// Add the vertex locally
    add_vertex(self.derived().base().vertex_constructor(name), self.derived()); 
  else
    /// Ask the owner of the vertex to add a vertex with this name
    send(self.process_group(), owner, msg_add_vertex_name, name);
}

template<BGL_NAMED_GRAPH_PARAMS>
typename BGL_NAMED_GRAPH::vertex_descriptor
BGL_NAMED_GRAPH::lazy_add_vertex::commit() const
{
  typedef typename BGL_NAMED_GRAPH::process_id_type process_id_type;
  BOOST_ASSERT (!committed);
  committed = true;

  process_id_type owner = self.named_distribution()(name);
  if (owner == process_id(self.process_group()))
    /// Add the vertex locally
    return add_vertex(self.derived().base().vertex_constructor(name),
                      self.derived()); 
  else {
    /// Ask the owner of the vertex to add a vertex with this name
    vertex_descriptor result;
    send_oob_with_reply(self.process_group(), owner, 
                        msg_add_vertex_name_with_reply, name, result);
    return result;
  }
}

/**
 * Data structure returned from add_edge that will "lazily" add the
 * edge, either when it is converted to a @c
 * pair<edge_descriptor,bool> or when the most recent copy has been
 * destroyed.
 */
template<BGL_NAMED_GRAPH_PARAMS>
struct BGL_NAMED_GRAPH::lazy_add_edge 
{
  /// The graph's edge descriptor
  typedef typename graph_traits<Graph>::edge_descriptor edge_descriptor;

  /// Add an edge for the edge (u, v) based on vertex names
  lazy_add_edge(BGL_NAMED_GRAPH& self, 
                const vertex_name_type& u_name,
                const vertex_name_type& v_name) 
    : self(self), u(u_name), v(v_name), committed(false) { }

  /// Add an edge for the edge (u, v) based on a vertex descriptor and name
  lazy_add_edge(BGL_NAMED_GRAPH& self,
                vertex_descriptor u,
                const vertex_name_type& v_name)
    : self(self), u(u), v(v_name), committed(false) { }

  /// Add an edge for the edge (u, v) based on a vertex name and descriptor
  lazy_add_edge(BGL_NAMED_GRAPH& self,
                const vertex_name_type& u_name,
                vertex_descriptor v)
    : self(self), u(u_name), v(v), committed(false) { }

  /// Add an edge for the edge (u, v) based on vertex descriptors
  lazy_add_edge(BGL_NAMED_GRAPH& self,
                vertex_descriptor u,
                vertex_descriptor v)
    : self(self), u(u), v(v), committed(false) { }

  /// Copy a lazy_add_edge structure, which transfers responsibility
  /// for adding the edge to the newly-constructed object.
  lazy_add_edge(const lazy_add_edge& other)
    : self(other.self), u(other.u), v(other.v), committed(other.committed)
  {
    other.committed = true;
  }

  /// If the edge has not yet been added, add the edge but don't wait
  /// for a reply.
  ~lazy_add_edge();

  /// Returns commit().
  operator std::pair<edge_descriptor, bool>() const { return commit(); }

  // Add the edge. This operation will block if a remote edge is
  // being added.
  std::pair<edge_descriptor, bool> commit() const;

protected:
  BGL_NAMED_GRAPH& self;
  mutable variant<vertex_descriptor, vertex_name_type> u;
  mutable variant<vertex_descriptor, vertex_name_type> v;
  mutable bool committed;

private:
  // No copy-assignment semantics
  void operator=(lazy_add_edge&);
};

template<BGL_NAMED_GRAPH_PARAMS>
BGL_NAMED_GRAPH::lazy_add_edge::~lazy_add_edge()
{
  using boost::parallel::detail::make_untracked_pair;

  /// If this edge has already been created or will be created by
  /// someone else, or if someone threw an exception, we will not
  /// create the edge now.
  if (committed || boost::core::uncaught_exceptions() > 0)
    return;

  committed = true;

  if (vertex_name_type* v_name = boost::get<vertex_name_type>(&v)) {
    // We haven't resolved the target vertex to a descriptor yet, so
    // it must not be local. Send a message to the owner of the target
    // of the edge. If the owner of the target does not happen to own
    // the source, it will resolve the target to a vertex descriptor
    // and pass the message along to the owner of the source. 
    if (vertex_name_type* u_name = boost::get<vertex_name_type>(&u))
      send(self.process_group(), self.distribution_(*v_name),
           BGL_NAMED_GRAPH::msg_add_edge_name_name,
           make_untracked_pair(*u_name, *v_name));
    else
      send(self.process_group(), self.distribution_(*v_name),
           BGL_NAMED_GRAPH::msg_add_edge_vertex_name,
           make_untracked_pair(boost::get<vertex_descriptor>(u), *v_name));
  } else {
    if (vertex_name_type* u_name = boost::get<vertex_name_type>(&u))
      // We haven't resolved the source vertex to a descriptor yet, so
      // it must not be local. Send a message to the owner of the
      // source vertex requesting the edge addition.
      send(self.process_group(), self.distribution_(*u_name),
           BGL_NAMED_GRAPH::msg_add_edge_name_vertex,
           make_untracked_pair(*u_name, boost::get<vertex_descriptor>(v)));
    else
      // We have descriptors for both of the vertices, either of which
      // may be remote or local. Tell the owner of the source vertex
      // to add the edge (it may be us!).
      add_edge(boost::get<vertex_descriptor>(u), 
               boost::get<vertex_descriptor>(v), 
               self.derived());
  }
}

template<BGL_NAMED_GRAPH_PARAMS>
std::pair<typename graph_traits<Graph>::edge_descriptor, bool>
BGL_NAMED_GRAPH::lazy_add_edge::commit() const
{
  typedef typename BGL_NAMED_GRAPH::process_id_type process_id_type;
  using boost::parallel::detail::make_untracked_pair;

  BOOST_ASSERT(!committed);
  committed = true;

  /// The result we will return, if we are sending a message to
  /// request that someone else add the edge.
  boost::parallel::detail::untracked_pair<edge_descriptor, bool> result;

  /// The owner of the vertex "u"
  process_id_type u_owner;

  process_id_type rank = process_id(self.process_group());
  if (const vertex_name_type* u_name = boost::get<vertex_name_type>(&u)) {
    /// We haven't resolved the source vertex to a descriptor yet, so
    /// it must not be local. 
    u_owner = self.named_distribution()(*u_name);

    /// Send a message to the remote vertex requesting that it add the
    /// edge. The message differs depending on whether we have a
    /// vertex name or a vertex descriptor for the target.
    if (const vertex_name_type* v_name = boost::get<vertex_name_type>(&v))
      send_oob_with_reply(self.process_group(), u_owner,
                          BGL_NAMED_GRAPH::msg_add_edge_name_name_with_reply,
                          make_untracked_pair(*u_name, *v_name), result);
    else
      send_oob_with_reply(self.process_group(), u_owner,
                          BGL_NAMED_GRAPH::msg_add_edge_name_vertex_with_reply,
                          make_untracked_pair(*u_name, 
                                         boost::get<vertex_descriptor>(v)),
                          result);
  } else {
    /// We have resolved the source vertex to a descriptor, which may
    /// either be local or remote.
    u_owner 
      = get(vertex_owner, self.derived(),
            boost::get<vertex_descriptor>(u));
    if (u_owner == rank) {
      /// The source is local. If we need to, resolve the target vertex.
      if (const vertex_name_type* v_name = boost::get<vertex_name_type>(&v))
        v = add_vertex(*v_name, self.derived());

      /// Add the edge using vertex descriptors
      return add_edge(boost::get<vertex_descriptor>(u), 
                      boost::get<vertex_descriptor>(v), 
                      self.derived());
    } else {
      /// The source is remote. Just send a message to its owner
      /// requesting that the owner add the new edge, either directly
      /// or via the derived class's add_edge function.
      if (const vertex_name_type* v_name = boost::get<vertex_name_type>(&v))
        send_oob_with_reply
          (self.process_group(), u_owner,
           BGL_NAMED_GRAPH::msg_add_edge_vertex_name_with_reply,
           make_untracked_pair(boost::get<vertex_descriptor>(u), *v_name),
           result);
      else
        return add_edge(boost::get<vertex_descriptor>(u), 
                        boost::get<vertex_descriptor>(v), 
                        self.derived());
    }
  }

  // If we get here, the edge has been added remotely and "result"
  // contains the result of that edge addition.
  return result;
}

/**
 * Data structure returned from add_edge that will "lazily" add the
 * edge with a property, either when it is converted to a @c
 * pair<edge_descriptor,bool> or when the most recent copy has been
 * destroyed.
 */
template<BGL_NAMED_GRAPH_PARAMS>
struct BGL_NAMED_GRAPH::lazy_add_edge_with_property 
{
  /// The graph's edge descriptor
  typedef typename graph_traits<Graph>::edge_descriptor edge_descriptor;

  /// The Edge property type for our graph
  typedef typename Config::edge_property_type edge_property_type;
  
  /// Add an edge for the edge (u, v) based on vertex names
  lazy_add_edge_with_property(BGL_NAMED_GRAPH& self, 
                              const vertex_name_type& u_name,
                              const vertex_name_type& v_name,
                              const edge_property_type& property) 
    : self(self), u(u_name), v(v_name), property(property), committed(false)
  { 
  }

  /// Add an edge for the edge (u, v) based on a vertex descriptor and name
  lazy_add_edge_with_property(BGL_NAMED_GRAPH& self,
                vertex_descriptor u,
                const vertex_name_type& v_name,
                                  const edge_property_type& property)
    : self(self), u(u), v(v_name), property(property), committed(false) { }

  /// Add an edge for the edge (u, v) based on a vertex name and descriptor
  lazy_add_edge_with_property(BGL_NAMED_GRAPH& self,
                              const vertex_name_type& u_name,
                              vertex_descriptor v,
                              const edge_property_type& property)
    : self(self), u(u_name), v(v), property(property), committed(false) { }

  /// Add an edge for the edge (u, v) based on vertex descriptors
  lazy_add_edge_with_property(BGL_NAMED_GRAPH& self,
                              vertex_descriptor u,
                              vertex_descriptor v,
                              const edge_property_type& property)
    : self(self), u(u), v(v), property(property), committed(false) { }

  /// Copy a lazy_add_edge_with_property structure, which transfers
  /// responsibility for adding the edge to the newly-constructed
  /// object.
  lazy_add_edge_with_property(const lazy_add_edge_with_property& other)
    : self(other.self), u(other.u), v(other.v), property(other.property), 
      committed(other.committed)
  {
    other.committed = true;
  }

  /// If the edge has not yet been added, add the edge but don't wait
  /// for a reply.
  ~lazy_add_edge_with_property();

  /// Returns commit().
  operator std::pair<edge_descriptor, bool>() const { return commit(); }

  // Add the edge. This operation will block if a remote edge is
  // being added.
  std::pair<edge_descriptor, bool> commit() const;

protected:
  BGL_NAMED_GRAPH& self;
  mutable variant<vertex_descriptor, vertex_name_type> u;
  mutable variant<vertex_descriptor, vertex_name_type> v;
  edge_property_type property;
  mutable bool committed;

private:
  // No copy-assignment semantics
  void operator=(lazy_add_edge_with_property&);
};

template<BGL_NAMED_GRAPH_PARAMS>
BGL_NAMED_GRAPH::lazy_add_edge_with_property::~lazy_add_edge_with_property()
{
  using boost::detail::parallel::make_pair_with_property;

  /// If this edge has already been created or will be created by
  /// someone else, or if someone threw an exception, we will not
  /// create the edge now.
  if (committed || boost::core::uncaught_exceptions() > 0)
    return;

  committed = true;

  if (vertex_name_type* v_name = boost::get<vertex_name_type>(&v)) {
    // We haven't resolved the target vertex to a descriptor yet, so
    // it must not be local. Send a message to the owner of the target
    // of the edge. If the owner of the target does not happen to own
    // the source, it will resolve the target to a vertex descriptor
    // and pass the message along to the owner of the source. 
    if (vertex_name_type* u_name = boost::get<vertex_name_type>(&u))
      send(self.process_group(), self.distribution_(*v_name),
           BGL_NAMED_GRAPH::msg_add_edge_name_name_with_property,
           make_pair_with_property(*u_name, *v_name, property));
    else
      send(self.process_group(), self.distribution_(*v_name),
           BGL_NAMED_GRAPH::msg_add_edge_vertex_name_with_property,
           make_pair_with_property(boost::get<vertex_descriptor>(u), *v_name, 
                                   property));
  } else {
    if (vertex_name_type* u_name = boost::get<vertex_name_type>(&u))
      // We haven't resolved the source vertex to a descriptor yet, so
      // it must not be local. Send a message to the owner of the
      // source vertex requesting the edge addition.
      send(self.process_group(), self.distribution_(*u_name),
           BGL_NAMED_GRAPH::msg_add_edge_name_vertex_with_property,
           make_pair_with_property(*u_name, boost::get<vertex_descriptor>(v), 
                                   property));
    else
      // We have descriptors for both of the vertices, either of which
      // may be remote or local. Tell the owner of the source vertex
      // to add the edge (it may be us!).
      add_edge(boost::get<vertex_descriptor>(u), 
               boost::get<vertex_descriptor>(v), 
               property,
               self.derived());
  }
}

template<BGL_NAMED_GRAPH_PARAMS>
std::pair<typename graph_traits<Graph>::edge_descriptor, bool>
BGL_NAMED_GRAPH::lazy_add_edge_with_property::commit() const
{
  using boost::detail::parallel::make_pair_with_property;
  typedef typename BGL_NAMED_GRAPH::process_id_type process_id_type;
  BOOST_ASSERT(!committed);
  committed = true;

  /// The result we will return, if we are sending a message to
  /// request that someone else add the edge.
  boost::parallel::detail::untracked_pair<edge_descriptor, bool> result;

  /// The owner of the vertex "u"
  process_id_type u_owner;

  process_id_type rank = process_id(self.process_group());
  if (const vertex_name_type* u_name = boost::get<vertex_name_type>(&u)) {
    /// We haven't resolved the source vertex to a descriptor yet, so
    /// it must not be local. 
    u_owner = self.named_distribution()(*u_name);

    /// Send a message to the remote vertex requesting that it add the
    /// edge. The message differs depending on whether we have a
    /// vertex name or a vertex descriptor for the target.
    if (const vertex_name_type* v_name = boost::get<vertex_name_type>(&v))
      send_oob_with_reply
        (self.process_group(), u_owner,
         BGL_NAMED_GRAPH::msg_add_edge_name_name_with_reply_and_property,
         make_pair_with_property(*u_name, *v_name, property),
         result);
    else
      send_oob_with_reply
        (self.process_group(), u_owner,
         BGL_NAMED_GRAPH::msg_add_edge_name_vertex_with_reply_and_property,
         make_pair_with_property(*u_name, 
                                 boost::get<vertex_descriptor>(v),
                                 property),
         result);
  } else {
    /// We have resolved the source vertex to a descriptor, which may
    /// either be local or remote.
    u_owner 
      = get(vertex_owner, self.derived(),
            boost::get<vertex_descriptor>(u));
    if (u_owner == rank) {
      /// The source is local. If we need to, resolve the target vertex.
      if (const vertex_name_type* v_name = boost::get<vertex_name_type>(&v))
        v = add_vertex(*v_name, self.derived());

      /// Add the edge using vertex descriptors
      return add_edge(boost::get<vertex_descriptor>(u), 
                      boost::get<vertex_descriptor>(v), 
                      property,
                      self.derived());
    } else {
      /// The source is remote. Just send a message to its owner
      /// requesting that the owner add the new edge, either directly
      /// or via the derived class's add_edge function.
      if (const vertex_name_type* v_name = boost::get<vertex_name_type>(&v))
        send_oob_with_reply
          (self.process_group(), u_owner,
           BGL_NAMED_GRAPH::msg_add_edge_vertex_name_with_reply_and_property,
           make_pair_with_property(boost::get<vertex_descriptor>(u), *v_name,
                                   property),
           result);
      else
        return add_edge(boost::get<vertex_descriptor>(u), 
                        boost::get<vertex_descriptor>(v), 
                        property,
                        self.derived());
    }
  }

  // If we get here, the edge has been added remotely and "result"
  // contains the result of that edge addition.
  return result;
}

/// Construct the named_graph with a particular process group
template<BGL_NAMED_GRAPH_PARAMS>
BGL_NAMED_GRAPH::named_graph(const process_group_type& pg)
  : process_group_(pg, boost::parallel::attach_distributed_object()),
    distribution_(pg)
{
  setup_triggers();
}

/// Construct the named_graph mixin with a particular process group
/// and distribution function
template<BGL_NAMED_GRAPH_PARAMS>
BGL_NAMED_GRAPH::named_graph(const process_group_type& pg,
                             const base_distribution_type& distribution)
  : process_group_(pg, boost::parallel::attach_distributed_object()),
    distribution_(pg, distribution)
{
  setup_triggers();
}

template<BGL_NAMED_GRAPH_PARAMS>
void
BGL_NAMED_GRAPH::setup_triggers()
{
  using boost::graph::parallel::simple_trigger;

  simple_trigger(process_group_, msg_add_vertex_name, this,
                 &named_graph::handle_add_vertex_name);
  simple_trigger(process_group_, msg_add_vertex_name_with_reply, this,
                 &named_graph::handle_add_vertex_name_with_reply);
  simple_trigger(process_group_, msg_find_vertex, this, 
                 &named_graph::handle_find_vertex);
  simple_trigger(process_group_, msg_add_edge_name_name, this, 
                 &named_graph::template handle_add_edge<vertex_name_type, 
                                                        vertex_name_type>);
  simple_trigger(process_group_, msg_add_edge_name_name_with_reply, this,
                 &named_graph::template handle_add_edge_with_reply
                   <vertex_name_type, vertex_name_type>);
  simple_trigger(process_group_, msg_add_edge_name_vertex, this,
                 &named_graph::template handle_add_edge<vertex_name_type, 
                                                        vertex_descriptor>);
  simple_trigger(process_group_, msg_add_edge_name_vertex_with_reply, this,
                 &named_graph::template handle_add_edge_with_reply
                   <vertex_name_type, vertex_descriptor>);
  simple_trigger(process_group_, msg_add_edge_vertex_name, this,
                 &named_graph::template handle_add_edge<vertex_descriptor, 
                                                        vertex_name_type>);
  simple_trigger(process_group_, msg_add_edge_vertex_name_with_reply, this,
                 &named_graph::template handle_add_edge_with_reply
                   <vertex_descriptor, vertex_name_type>);
  simple_trigger(process_group_, msg_add_edge_name_name_with_property, this, 
                 &named_graph::
                   template handle_add_edge_with_property<vertex_name_type, 
                                                          vertex_name_type>);
  simple_trigger(process_group_, 
                 msg_add_edge_name_name_with_reply_and_property, this,
                 &named_graph::template handle_add_edge_with_reply_and_property
                   <vertex_name_type, vertex_name_type>);
  simple_trigger(process_group_, msg_add_edge_name_vertex_with_property, this,
                 &named_graph::
                   template handle_add_edge_with_property<vertex_name_type, 
                                                          vertex_descriptor>);
  simple_trigger(process_group_, 
                 msg_add_edge_name_vertex_with_reply_and_property, this,
                 &named_graph::template handle_add_edge_with_reply_and_property
                   <vertex_name_type, vertex_descriptor>);
  simple_trigger(process_group_, msg_add_edge_vertex_name_with_property, this,
                 &named_graph::
                   template handle_add_edge_with_property<vertex_descriptor, 
                                                          vertex_name_type>);
  simple_trigger(process_group_, 
                 msg_add_edge_vertex_name_with_reply_and_property, this,
                 &named_graph::template handle_add_edge_with_reply_and_property
                   <vertex_descriptor, vertex_name_type>);
}

/// Retrieve the vertex associated with the given name
template<BGL_NAMED_GRAPH_PARAMS>
optional<Vertex> 
find_vertex(typename BGL_NAMED_GRAPH::vertex_name_type const& name,
            const BGL_NAMED_GRAPH& g)
{
  typedef typename Graph::local_vertex_descriptor local_vertex_descriptor;
  typedef typename graph_traits<Graph>::vertex_descriptor vertex_descriptor;

  // Determine the owner of this name
  typename BGL_NAMED_GRAPH::process_id_type owner 
    = g.named_distribution()(name);

  if (owner == process_id(g.process_group())) {
    // The vertex is local, so search for a mapping here
    optional<local_vertex_descriptor> result 
      = find_vertex(name, g.derived().base());
    if (result)
      return Vertex(owner, *result);
    else
      return optional<Vertex>();
  }
  else {
    // Ask the ownering process for the name of this vertex
    boost::parallel::detail::untracked_pair<vertex_descriptor, bool> result;
    send_oob_with_reply(g.process_group(), owner, 
                        BGL_NAMED_GRAPH::msg_find_vertex, name, result);
    if (result.second)
      return result.first;
    else
      return optional<Vertex>();
  }
}

/// meta-function helping in figuring out if the given VertextProerty belongs to 
/// a named graph
template<typename VertexProperty>
struct not_is_named_graph
  : is_same<typename internal_vertex_name<VertexProperty>::type, void>
{};

/// Retrieve the vertex associated with the given name
template<typename Graph>
typename Graph::named_graph_type::lazy_add_vertex
add_vertex(typename Graph::vertex_name_type const& name,
           Graph& g, 
           typename disable_if<
              not_is_named_graph<typename Graph::vertex_property_type>, 
              void*>::type = 0)
{
  return typename Graph::named_graph_type::lazy_add_vertex(g, name);
}

/// Add an edge using vertex names to refer to the vertices
template<BGL_NAMED_GRAPH_PARAMS>
typename BGL_NAMED_GRAPH::lazy_add_edge
add_edge(typename BGL_NAMED_GRAPH::vertex_name_type const& u_name,
         typename BGL_NAMED_GRAPH::vertex_name_type const& v_name,
         BGL_NAMED_GRAPH& g)
{
  typedef typename BGL_NAMED_GRAPH::lazy_add_edge lazy_add_edge;
  typedef typename BGL_NAMED_GRAPH::process_id_type process_id_type;

  process_id_type rank = process_id(g.process_group());
  process_id_type u_owner = g.named_distribution()(u_name);
  process_id_type v_owner = g.named_distribution()(v_name);

  // Resolve local vertex names before building the "lazy" edge
  // addition structure.
  if (u_owner == rank && v_owner == rank)
    return lazy_add_edge(g, add_vertex(u_name, g), add_vertex(v_name, g));
  else if (u_owner == rank && v_owner != rank)
    return lazy_add_edge(g, add_vertex(u_name, g), v_name);
  else if (u_owner != rank && v_owner == rank)
    return lazy_add_edge(g, u_name, add_vertex(v_name, g));
  else
    return lazy_add_edge(g, u_name, v_name);
}

template<BGL_NAMED_GRAPH_PARAMS>
typename BGL_NAMED_GRAPH::lazy_add_edge
add_edge(typename BGL_NAMED_GRAPH::vertex_name_type const& u_name,
         typename BGL_NAMED_GRAPH::vertex_descriptor const& v,
         BGL_NAMED_GRAPH& g)
{
  // Resolve local vertex names before building the "lazy" edge
  // addition structure.
  typedef typename BGL_NAMED_GRAPH::lazy_add_edge lazy_add_edge;
  if (g.named_distribution()(u_name) == process_id(g.process_group()))
    return lazy_add_edge(g, add_vertex(u_name, g), v);
  else
    return lazy_add_edge(g, u_name, v);
}

template<BGL_NAMED_GRAPH_PARAMS>
typename BGL_NAMED_GRAPH::lazy_add_edge
add_edge(typename BGL_NAMED_GRAPH::vertex_descriptor const& u,
         typename BGL_NAMED_GRAPH::vertex_name_type const& v_name,
         BGL_NAMED_GRAPH& g)
{
  // Resolve local vertex names before building the "lazy" edge
  // addition structure.
  typedef typename BGL_NAMED_GRAPH::lazy_add_edge lazy_add_edge;
  if (g.named_distribution()(v_name) == process_id(g.process_group()))
    return lazy_add_edge(g, u, add_vertex(v_name, g));
  else
    return lazy_add_edge(g, u, v_name);
}

/// Add an edge using vertex names to refer to the vertices
template<BGL_NAMED_GRAPH_PARAMS>
typename BGL_NAMED_GRAPH::lazy_add_edge_with_property
add_edge(typename BGL_NAMED_GRAPH::vertex_name_type const& u_name,
         typename BGL_NAMED_GRAPH::vertex_name_type const& v_name,
         typename Graph::edge_property_type const& property,
         BGL_NAMED_GRAPH& g)
{
  typedef typename BGL_NAMED_GRAPH::lazy_add_edge_with_property lazy_add_edge;
  typedef typename BGL_NAMED_GRAPH::process_id_type process_id_type;

  process_id_type rank = process_id(g.process_group());
  process_id_type u_owner = g.named_distribution()(u_name);
  process_id_type v_owner = g.named_distribution()(v_name);

  // Resolve local vertex names before building the "lazy" edge
  // addition structure.
  if (u_owner == rank && v_owner == rank)
    return lazy_add_edge(g, add_vertex(u_name, g), add_vertex(v_name, g), 
                         property);
  else if (u_owner == rank && v_owner != rank)
    return lazy_add_edge(g, add_vertex(u_name, g), v_name, property);
  else if (u_owner != rank && v_owner == rank)
    return lazy_add_edge(g, u_name, add_vertex(v_name, g), property);
  else
    return lazy_add_edge(g, u_name, v_name, property);
}

template<BGL_NAMED_GRAPH_PARAMS>
typename BGL_NAMED_GRAPH::lazy_add_edge_with_property
add_edge(typename BGL_NAMED_GRAPH::vertex_name_type const& u_name,
         typename BGL_NAMED_GRAPH::vertex_descriptor const& v,
         typename Graph::edge_property_type const& property,
         BGL_NAMED_GRAPH& g)
{
  // Resolve local vertex names before building the "lazy" edge
  // addition structure.
  typedef typename BGL_NAMED_GRAPH::lazy_add_edge_with_property lazy_add_edge;
  if (g.named_distribution()(u_name) == process_id(g.process_group()))
    return lazy_add_edge(g, add_vertex(u_name, g), v, property);
  else
    return lazy_add_edge(g, u_name, v, property);
}

template<BGL_NAMED_GRAPH_PARAMS>
typename BGL_NAMED_GRAPH::lazy_add_edge_with_property
add_edge(typename BGL_NAMED_GRAPH::vertex_descriptor const& u,
         typename BGL_NAMED_GRAPH::vertex_name_type const& v_name,
         typename Graph::edge_property_type const& property,
         BGL_NAMED_GRAPH& g)
{
  // Resolve local vertex names before building the "lazy" edge
  // addition structure.
  typedef typename BGL_NAMED_GRAPH::lazy_add_edge_with_property lazy_add_edge;
  if (g.named_distribution()(v_name) == process_id(g.process_group()))
    return lazy_add_edge(g, u, add_vertex(v_name, g), property);
  else
    return lazy_add_edge(g, u, v_name, property);
}

template<BGL_NAMED_GRAPH_PARAMS>
typename BGL_NAMED_GRAPH::process_id_type 
BGL_NAMED_GRAPH::owner_by_property(const vertex_property_type& property)
{
  return distribution_(derived().base().extract_name(property));
}


/*******************************************************************
 * Message handlers                                                *
 *******************************************************************/

template<BGL_NAMED_GRAPH_PARAMS>
void 
BGL_NAMED_GRAPH::
handle_add_vertex_name(int /*source*/, int /*tag*/, 
                       const vertex_name_type& msg, trigger_receive_context)
{
  add_vertex(msg, derived());
}

template<BGL_NAMED_GRAPH_PARAMS>
typename BGL_NAMED_GRAPH::vertex_descriptor
BGL_NAMED_GRAPH::
handle_add_vertex_name_with_reply(int source, int /*tag*/, 
                                  const vertex_name_type& msg, 
                                  trigger_receive_context)
{
  return add_vertex(msg, derived());
}

template<BGL_NAMED_GRAPH_PARAMS>
boost::parallel::detail::untracked_pair<typename BGL_NAMED_GRAPH::vertex_descriptor, bool>
BGL_NAMED_GRAPH::
handle_find_vertex(int source, int /*tag*/, const vertex_name_type& msg, 
                   trigger_receive_context)
{
  using boost::parallel::detail::make_untracked_pair;

  optional<vertex_descriptor> v = find_vertex(msg, derived());
  if (v)
    return make_untracked_pair(*v, true);
  else
    return make_untracked_pair(graph_traits<Graph>::null_vertex(), false);
}

template<BGL_NAMED_GRAPH_PARAMS>
template<typename U, typename V>
void
BGL_NAMED_GRAPH::
handle_add_edge(int source, int /*tag*/, const boost::parallel::detail::untracked_pair<U, V>& msg, 
                trigger_receive_context)
{
  add_edge(msg.first, msg.second, derived());
}

template<BGL_NAMED_GRAPH_PARAMS>
template<typename U, typename V>
boost::parallel::detail::untracked_pair<typename BGL_NAMED_GRAPH::edge_descriptor, bool>
BGL_NAMED_GRAPH::
handle_add_edge_with_reply(int source, int /*tag*/, const boost::parallel::detail::untracked_pair<U, V>& msg,
                           trigger_receive_context)
{
  std::pair<typename BGL_NAMED_GRAPH::edge_descriptor, bool> p =
    add_edge(msg.first, msg.second, derived());
   return p;
}

template<BGL_NAMED_GRAPH_PARAMS>
template<typename U, typename V>
void 
BGL_NAMED_GRAPH::
handle_add_edge_with_property
  (int source, int tag, 
   const pair_with_property<U, V, edge_property_type>& msg,
   trigger_receive_context)
{
  add_edge(msg.first, msg.second, msg.get_property(), derived());
}

template<BGL_NAMED_GRAPH_PARAMS>
template<typename U, typename V>
boost::parallel::detail::untracked_pair<typename BGL_NAMED_GRAPH::edge_descriptor, bool>
BGL_NAMED_GRAPH::
handle_add_edge_with_reply_and_property
  (int source, int tag, 
   const pair_with_property<U, V, edge_property_type>& msg,
   trigger_receive_context)
{
  std:: pair<typename BGL_NAMED_GRAPH::edge_descriptor, bool> p =
    add_edge(msg.first, msg.second, msg.get_property(), derived());
  return p;
}

#undef BGL_NAMED_GRAPH
#undef BGL_NAMED_GRAPH_PARAMS

/*******************************************************************
 * Maybe named graph mixin                                         *
 *******************************************************************/

/**
 * A graph mixin that can provide a mapping from names to vertices,
 * and use that mapping to simplify creation and manipulation of
 * graphs. 
 */
template<typename Graph, typename Vertex, typename Edge, typename Config, 
  typename ExtractName 
    = typename internal_vertex_name<typename Config::vertex_property_type>::type>
struct maybe_named_graph 
  : public named_graph<Graph, Vertex, Edge, Config> 
{
private:
  typedef named_graph<Graph, Vertex, Edge, Config> inherited;
  typedef typename Config::process_group_type process_group_type;
  
public:
  /// The type used to distribute named vertices in the graph
  typedef typename Config::distribution_type distribution_type;
  typedef typename Config::base_distribution_type base_distribution_type;
  
  explicit maybe_named_graph(const process_group_type& pg) : inherited(pg) { }

  maybe_named_graph(const process_group_type& pg, 
                    const base_distribution_type& distribution)
    : inherited(pg, distribution) { }  

  distribution_type&       distribution()       { return this->distribution_; }
  const distribution_type& distribution() const { return this->distribution_; }
};

/**
 * A graph mixin that can provide a mapping from names to vertices,
 * and use that mapping to simplify creation and manipulation of
 * graphs. This partial specialization turns off this functionality
 * when the @c VertexProperty does not have an internal vertex name.
 */
template<typename Graph, typename Vertex, typename Edge, typename Config>
struct maybe_named_graph<Graph, Vertex, Edge, Config, void> 
{ 
private:
  typedef typename Config::process_group_type process_group_type;
  typedef typename Config::vertex_property_type vertex_property_type;
  
public:
  typedef typename process_group_type::process_id_type process_id_type;

  /// The type used to distribute named vertices in the graph
  typedef typename Config::distribution_type distribution_type;
  typedef typename Config::base_distribution_type base_distribution_type;

  explicit maybe_named_graph(const process_group_type&)  { }

  maybe_named_graph(const process_group_type& pg, 
                    const base_distribution_type& distribution) 
    : distribution_(pg, distribution) { }

  /// Notify the named_graph that we have added the given vertex. This
  /// is a no-op.
  void added_vertex(Vertex) { }

  /// Notify the named_graph that we are removing the given
  /// vertex. This is a no-op.
  template <typename VertexIterStability>
  void removing_vertex(Vertex, VertexIterStability) { }

  /// Notify the named_graph that we are clearing the graph
  void clearing_graph() { }

  /// Retrieve the owner of a given vertex based on the properties
  /// associated with that vertex. This operation just returns the
  /// number of the local processor, adding all vertices locally.
  process_id_type owner_by_property(const vertex_property_type&)
  {
    return process_id(pg);
  }

  distribution_type&       distribution()       { return distribution_; }
  const distribution_type& distribution() const { return distribution_; }

protected:
  /// The process group of the graph
  process_group_type pg;
  
  /// The distribution used for the graph
  distribution_type distribution_;
};

} } } // end namespace boost::graph::distributed

#endif // BOOST_GRAPH_DISTRIBUTED_NAMED_GRAPH_HPP

/* named_graph.hpp
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
*/