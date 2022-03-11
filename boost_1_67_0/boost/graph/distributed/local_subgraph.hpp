// Copyright (C) 2004-2006 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_LOCAL_SUBGRAPH_HPP
#define BOOST_GRAPH_LOCAL_SUBGRAPH_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/filtered_graph.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/graph/parallel/container_traits.hpp>

namespace boost {

namespace graph { namespace detail {
  // Optionally, virtually derive from a base class
  template<bool Derive, typename Base> struct derive_from_if;
  template<typename Base> struct derive_from_if<true, Base> : virtual Base {};
  template<typename Base> struct derive_from_if<false, Base> {};

  template<typename NewBase, typename Tag, typename OldBase = NewBase>
  struct derive_from_if_tag_is : 
    derive_from_if<(is_base_and_derived<OldBase, Tag>::value
                    || is_same<OldBase, Tag>::value), 
                   NewBase>
  {
  };
} } // end namespace graph::detail

template<typename DistributedGraph>
class is_local_edge
{
public:
  typedef bool result_type;
  typedef typename graph_traits<DistributedGraph>::edge_descriptor
    argument_type;

  is_local_edge() : g(0) {}
  is_local_edge(DistributedGraph& g) : g(&g), owner(get(vertex_owner, g)) {}

  // Since either the source or target vertex must be local, the
  // equivalence of their owners indicates a local edge.
  result_type operator()(const argument_type& e) const
  { return get(owner, source(e, *g)) == get(owner, target(e, *g)); }

private:
  DistributedGraph* g;
  typename property_map<DistributedGraph, vertex_owner_t>::const_type owner;
};

template<typename DistributedGraph>
class is_local_vertex
{
public:
  typedef bool result_type;
  typedef typename graph_traits<DistributedGraph>::vertex_descriptor
    argument_type;

  is_local_vertex() : g(0) {}
  is_local_vertex(DistributedGraph& g) : g(&g), owner(get(vertex_owner, g)) { }

  // Since either the source or target vertex must be local, the
  // equivalence of their owners indicates a local edge.
  result_type operator()(const argument_type& v) const
  { 
    return get(owner, v) == process_id(process_group(*g)); 
  }

private:
  DistributedGraph* g;
  typename property_map<DistributedGraph, vertex_owner_t>::const_type owner;
};

template<typename DistributedGraph>
class local_subgraph 
  : public filtered_graph<DistributedGraph, 
                          is_local_edge<DistributedGraph>,
                          is_local_vertex<DistributedGraph> >
{
  typedef filtered_graph<DistributedGraph, 
                         is_local_edge<DistributedGraph>,
                         is_local_vertex<DistributedGraph> >
    inherited;
  typedef typename graph_traits<DistributedGraph>::traversal_category
    inherited_category;
  
public:
  struct traversal_category :
    graph::detail::derive_from_if_tag_is<incidence_graph_tag, 
                                         inherited_category>,
    graph::detail::derive_from_if_tag_is<adjacency_graph_tag, 
                                         inherited_category>,
    graph::detail::derive_from_if_tag_is<vertex_list_graph_tag, 
                                         inherited_category>,
    graph::detail::derive_from_if_tag_is<edge_list_graph_tag, 
                                         inherited_category>,
    graph::detail::derive_from_if_tag_is<vertex_list_graph_tag, 
                                         inherited_category,
                                         distributed_vertex_list_graph_tag>,
    graph::detail::derive_from_if_tag_is<edge_list_graph_tag, 
                                         inherited_category,
                                         distributed_edge_list_graph_tag>
  { };

  local_subgraph(DistributedGraph& g) 
    : inherited(g, 
                is_local_edge<DistributedGraph>(g),
                is_local_vertex<DistributedGraph>(g)), 
      g(g) 
  {
  }

  // Distributed Container
  typedef typename boost::graph::parallel::process_group_type<DistributedGraph>::type
    process_group_type;

  process_group_type&       process_group()       
  { 
    using boost::graph::parallel::process_group;
    return process_group(g); 
  }
  const process_group_type& process_group() const 
  { 
    using boost::graph::parallel::process_group;
    return boost::graph::parallel::process_group(g); 
  }
  
  DistributedGraph&         base()               { return g; }
  const DistributedGraph&   base() const         { return g; }

private:
  DistributedGraph& g;
};

template<typename DistributedGraph, typename PropertyTag>
class property_map<local_subgraph<DistributedGraph>, PropertyTag>
  : public property_map<DistributedGraph, PropertyTag> { };

template<typename DistributedGraph, typename PropertyTag>
class property_map<local_subgraph<const DistributedGraph>, PropertyTag>
{
 public:
  typedef typename property_map<DistributedGraph, PropertyTag>::const_type
    type;
  typedef type const_type;
};

template<typename PropertyTag, typename DistributedGraph>
inline typename property_map<local_subgraph<DistributedGraph>, PropertyTag>::type
get(PropertyTag p, local_subgraph<DistributedGraph>& g)
{ return get(p, g.base()); }

template<typename PropertyTag, typename DistributedGraph>
inline typename property_map<local_subgraph<DistributedGraph>, PropertyTag>
  ::const_type
get(PropertyTag p, const local_subgraph<DistributedGraph>& g)
{ return get(p, g.base()); } 

template<typename DistributedGraph>
inline local_subgraph<DistributedGraph> 
make_local_subgraph(DistributedGraph& g)
{ return local_subgraph<DistributedGraph>(g); }

} // end namespace boost

#endif // BOOST_GRAPH_LOCAL_SUBGRAPH_HPP

/* local_subgraph.hpp
+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
*/