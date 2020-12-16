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
ST7fByPh/TAO/hHGwwdhOfgQrAgfhlXho7A6fAzWgU/AenAvbAyfhK1UB/cC1blNg3+GXdTeXe2T4EE4G74Ar1D7XHgIPgFfhgfhEfgX+Ff4KjwK31Qd3K/h6/B7+Ibq4L4Jq8C3YCo8DuvCd2FH+Hc4Er4HM+D7cDZcDJfBJXAV/ATeBD+FN8PP4Vb4BdwGv4T3wq/gffAbeAB+C5+D38O34Gl4Av4TvgstBzrEkPIicxjehtXhCVgHXgubw6WwDVwG0+AKOASuhKPgKjgTroaL4Rq4FK6Fq6GH89wBI+BeGAkPwBh4DMbCEzAOvgvLwJMwHn4Fk2As9UQ5mAiTYV1YGbaEVWBnWA0OhdXhZFgD7oS14AOwNnwU1oGPw7rwBXg+fBk2gB/AhtAZQZsBRsNeMAVSxubVhvVhe9gADoIN4Uivf5gJG8Mc2ATOgi3gXNgSroGt4A2wNXwKNiX+/bAFfAe2gzUj+f6AdWFHmAY7wW6wJ+wB28F8db9G3ZfDNLgadoYbYBe4CfaC22BveBfsBnfBIfApOBQehBfBw3AEPAFHwi/hKOiK4rsFVoTpsBrMg3XgDNgFFsAesBAOgzPhVDgbzoCXwCvhZXAtnAM3wblwB1wI74PXwKNwKXwLLoPvwRXwU7gSnoLXwdLRlENYDl4PU+Aa2ATeBCfDjTAPboIz4Wa4DW6HD8Ad8FF4J9wH74bPwHvh1/B+eBo+AJ0x1EMwHj4Oy8G9sDrcB+vBJ2Ej+BTsDF+G2fAwzIFH4AwNPwveAa+A2+AC+DRcD5+Bt8Jn4Wb4HHwAHoKPwr/AffAofBMeh1/Av8FysTzPsB18F/aAf4d94AdwEPwQjoEn4Vz4D7gIfgnXwK/gZngK3gO/hX+E38En4ffwafgDfBOehh/CH+HX0HKSX3FUNzAVOmFn6IL9oAeOhBEwG0bCeTAKboLR8C4YC++HcfBRWArug2Xhi7A8fB9WgJ/BFOgs5ZMnQq88GVaDDWAq7ATPg91gJTgG1oK5sDZcBuvA3dBbX++BPLe6pri23bX9T/4ErSm+x8VzAR+BXtmjcCh8An4BD1jangSJOhco2etPww/iPFXhMJiq9tpq7w6Hw37wIjgOjoAT4Sh4ORwN58Ex8Co4Fl4DL4Yr4Dh4M8yC22A2vAtOgPvgJHhE43kdToHvwqnwe5gBS5Pm8ZofeZa2jyCfV3I9sTBLr6cd/pJgR9gIdoGdYDc4AfaCl8Lemu4L4VrYR9PZX9PZDz6k9vYBa7PXXMvcFsxAzCTMPMxKzDbMHsxBzDuYU5j4dWe2jnvNdT9vrstvbZ7Lb2WOyy+xfvuZ7i+Wts71k3Nbwsxn+U3OZfm157GU7C32y89XGXjccUZzVs5mvop/rspQyv88zHrMLsyBdSVzVEp+Jb//lZ8bM+EX0//PlJ3Mz9UcAGfoHABkoXMAnEX3AFSZU/X7ewwYzNeVLXf5dfzVQeMImQ/gLDofQGURIhvafQTC0iqLFFlX4yfKZ+/VvWsfI4sVWf8BxGZkcT5Z537d7fjjRTa4c/9udpoTgucbyDjl4YrUz1W91+NVfmKtMGRHkOWJDN2g3CzyFDnzAJxh5gE0S7LM+u+Vdf33pbH0hyjX43LoR+nm0btbrA6+0ccp4xQdfPIyVfVT/OH/ZNYVTxI/lcLq3Rv/uM/y6bFlpmfY44ojPbJ/oFlXu3W06E6hb1rT4dfhamWJLmiMrZOlY32qo1pZ3D+OSbbH37Jnp2cUTG8qSwkaXekJ4m9HTIzx19Xy681eKm7riMOsnTwzf1Z2um+ExTL67Z3EX4pnkzPPSnVXsapquo9LPjSIimTFhjx6rDY41roPRdwdut8i51s=
*/