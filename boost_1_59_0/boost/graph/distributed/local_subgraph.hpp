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
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
*/