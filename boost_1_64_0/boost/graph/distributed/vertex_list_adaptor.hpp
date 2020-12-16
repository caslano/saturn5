// Copyright (C) 2004-2006 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine

#ifndef BOOST_VERTEX_LIST_ADAPTOR_HPP
#define BOOST_VERTEX_LIST_ADAPTOR_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <boost/graph/graph_traits.hpp>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/parallel/algorithm.hpp>
#include <boost/graph/parallel/container_traits.hpp>
#include <boost/property_map/vector_property_map.hpp>

namespace boost { namespace graph {

// --------------------------------------------------------------------------
// Global index map built from a distribution 
// --------------------------------------------------------------------------
template<typename Distribution, typename OwnerPropertyMap, 
         typename LocalPropertyMap>
class distribution_global_index_map
{
 public:
  typedef std::size_t value_type;
  typedef value_type reference;
  typedef typename property_traits<OwnerPropertyMap>::key_type key_type;
  typedef readable_property_map_tag category;

  distribution_global_index_map(const Distribution& distribution,
                                const OwnerPropertyMap& owner,
                                const LocalPropertyMap& local)
    : distribution_(distribution), owner(owner), local(local) { }

  Distribution distribution_;
  OwnerPropertyMap owner;
  LocalPropertyMap local;
};

template<typename Distribution, typename OwnerPropertyMap, 
         typename LocalPropertyMap>
inline 
typename distribution_global_index_map<Distribution, OwnerPropertyMap,
                                       LocalPropertyMap>::value_type
get(const distribution_global_index_map<Distribution, OwnerPropertyMap,
                                        LocalPropertyMap>& p,
    typename distribution_global_index_map<Distribution, OwnerPropertyMap,
                                           LocalPropertyMap>::key_type x)
{ 
  using boost::get;
  return p.distribution_.global(get(p.owner, x), get(p.local, x));
}

template<typename Graph, typename Distribution>
inline
distribution_global_index_map<
  Distribution, 
  typename property_map<Graph, vertex_owner_t>::const_type,
  typename property_map<Graph, vertex_local_t>::const_type>
make_distribution_global_index_map(const Graph& g, const Distribution& d)
{
  typedef distribution_global_index_map<
            Distribution, 
            typename property_map<Graph, vertex_owner_t>::const_type,
            typename property_map<Graph, vertex_local_t>::const_type> 
    result_type;
  return result_type(d, get(vertex_owner, g), get(vertex_local, g));
}

// --------------------------------------------------------------------------
// Global index map built from a distributed index map and list of vertices
// --------------------------------------------------------------------------
template<typename IndexMap>
class stored_global_index_map : public IndexMap
{
 public:
  typedef readable_property_map_tag category;

  stored_global_index_map(const IndexMap& index_map) : IndexMap(index_map) { 
    // When we have a global index, we need to always have the indices
    // of every key we've seen
    this->set_max_ghost_cells(0);
  }
};

// --------------------------------------------------------------------------
// Global index map support code
// --------------------------------------------------------------------------
namespace detail {
  template<typename PropertyMap, typename ForwardIterator>
  inline void 
  initialize_global_index_map(const PropertyMap&, 
                              ForwardIterator, ForwardIterator) 
  { }

  template<typename IndexMap, typename ForwardIterator>
  void 
  initialize_global_index_map(stored_global_index_map<IndexMap>& p,
                              ForwardIterator first, ForwardIterator last)
  {
    using std::distance;

    typedef typename property_traits<IndexMap>::value_type size_t;

    size_t n = distance(first, last);
    for (size_t i = 0; i < n; ++i, ++first) local_put(p, *first, i);
  }
}

// --------------------------------------------------------------------------
// Adapts a Distributed Vertex List Graph to a Vertex List Graph
// --------------------------------------------------------------------------
template<typename Graph, typename GlobalIndexMap>
class vertex_list_adaptor : public graph_traits<Graph>
{
  typedef graph_traits<Graph> inherited;

  typedef typename inherited::traversal_category base_traversal_category;
  
 public:
  typedef typename inherited::vertex_descriptor vertex_descriptor;
  typedef typename std::vector<vertex_descriptor>::iterator vertex_iterator;
  typedef typename std::vector<vertex_descriptor>::size_type
    vertices_size_type;

  struct traversal_category 
    : public virtual base_traversal_category,
      public virtual vertex_list_graph_tag {};

  vertex_list_adaptor(const Graph& g, 
                      const GlobalIndexMap& index_map = GlobalIndexMap())
    : g(&g), index_map(index_map)
  {
    using boost::vertices;

    all_vertices_.reset(new std::vector<vertex_descriptor>());
    all_gather(process_group(), vertices(g).first, vertices(g).second,
               *all_vertices_);
    detail::initialize_global_index_map(this->index_map, 
                                        all_vertices_->begin(),
                                        all_vertices_->end());
  }

  const Graph& base() const { return *g; }

  // --------------------------------------------------------------------------
  // Distributed Container
  // --------------------------------------------------------------------------
  typedef typename boost::graph::parallel::process_group_type<Graph>::type 
    process_group_type;

  process_group_type process_group() const 
  { 
    using boost::graph::parallel::process_group;
    return process_group(*g); 
  }

  std::pair<vertex_iterator, vertex_iterator> vertices() const
  { return std::make_pair(all_vertices_->begin(), all_vertices_->end()); }

  vertices_size_type num_vertices() const { return all_vertices_->size(); }

  GlobalIndexMap get_index_map() const { return index_map; }

 private:
  const Graph* g;
  GlobalIndexMap index_map;
  shared_ptr<std::vector<vertex_descriptor> > all_vertices_;
};

template<typename Graph, typename GlobalIndexMap>
inline vertex_list_adaptor<Graph, GlobalIndexMap>
make_vertex_list_adaptor(const Graph& g, const GlobalIndexMap& index_map)
{ return vertex_list_adaptor<Graph, GlobalIndexMap>(g, index_map); }

namespace detail {
  template<typename Graph>
  class default_global_index_map
  {
    typedef typename graph_traits<Graph>::vertices_size_type value_type;
    typedef typename property_map<Graph, vertex_index_t>::const_type local_map;

  public:
    typedef vector_property_map<value_type, local_map> distributed_map;
    typedef stored_global_index_map<distributed_map> type;
  };
}

template<typename Graph>
inline 
vertex_list_adaptor<Graph, 
                    typename detail::default_global_index_map<Graph>::type>
make_vertex_list_adaptor(const Graph& g)
{ 
  typedef typename detail::default_global_index_map<Graph>::type 
    GlobalIndexMap;
  typedef typename detail::default_global_index_map<Graph>::distributed_map
    DistributedMap;
  typedef vertex_list_adaptor<Graph, GlobalIndexMap> result_type;
  return result_type(g, 
                     GlobalIndexMap(DistributedMap(num_vertices(g), 
                                                   get(vertex_index, g))));
}

// --------------------------------------------------------------------------
// Incidence Graph
// --------------------------------------------------------------------------
template<typename Graph, typename GlobalIndexMap>
inline typename vertex_list_adaptor<Graph, GlobalIndexMap>::vertex_descriptor
source(typename vertex_list_adaptor<Graph, GlobalIndexMap>::edge_descriptor e,
       const vertex_list_adaptor<Graph, GlobalIndexMap>& g)
{ return source(e, g.base()); }

template<typename Graph, typename GlobalIndexMap>
inline typename vertex_list_adaptor<Graph, GlobalIndexMap>::vertex_descriptor
target(typename vertex_list_adaptor<Graph, GlobalIndexMap>::edge_descriptor e,
       const vertex_list_adaptor<Graph, GlobalIndexMap>& g)
{ return target(e, g.base()); }

template<typename Graph, typename GlobalIndexMap>
inline
std::pair<typename vertex_list_adaptor<Graph, GlobalIndexMap>::out_edge_iterator,
          typename vertex_list_adaptor<Graph, GlobalIndexMap>::out_edge_iterator>
out_edges(typename vertex_list_adaptor<Graph, GlobalIndexMap>::vertex_descriptor v,
          const vertex_list_adaptor<Graph, GlobalIndexMap>& g)
{ return out_edges(v, g.base()); }

template<typename Graph, typename GlobalIndexMap>
inline typename vertex_list_adaptor<Graph, GlobalIndexMap>::degree_size_type
out_degree(typename vertex_list_adaptor<Graph, GlobalIndexMap>::vertex_descriptor v,
          const vertex_list_adaptor<Graph, GlobalIndexMap>& g)
{ return out_degree(v, g.base()); }

// --------------------------------------------------------------------------
// Bidirectional Graph
// --------------------------------------------------------------------------
template<typename Graph, typename GlobalIndexMap>
inline
std::pair<typename vertex_list_adaptor<Graph, GlobalIndexMap>::in_edge_iterator,
          typename vertex_list_adaptor<Graph, GlobalIndexMap>::in_edge_iterator>
in_edges(typename vertex_list_adaptor<Graph, GlobalIndexMap>::vertex_descriptor v,
         const vertex_list_adaptor<Graph, GlobalIndexMap>& g)
{ return in_edges(v, g.base()); }

template<typename Graph, typename GlobalIndexMap>
inline typename vertex_list_adaptor<Graph, GlobalIndexMap>::degree_size_type
in_degree(typename vertex_list_adaptor<Graph, GlobalIndexMap>::vertex_descriptor v,
          const vertex_list_adaptor<Graph, GlobalIndexMap>& g)
{ return in_degree(v, g.base()); }

template<typename Graph, typename GlobalIndexMap>
inline typename vertex_list_adaptor<Graph, GlobalIndexMap>::degree_size_type
degree(typename vertex_list_adaptor<Graph, GlobalIndexMap>::vertex_descriptor v,
       const vertex_list_adaptor<Graph, GlobalIndexMap>& g)
{ return degree(v, g.base()); }

// --------------------------------------------------------------------------
// Adjacency Graph
// --------------------------------------------------------------------------
template<typename Graph, typename GlobalIndexMap>
inline
std::pair<typename vertex_list_adaptor<Graph, GlobalIndexMap>::adjacency_iterator,
          typename vertex_list_adaptor<Graph, GlobalIndexMap>::adjacency_iterator>
adjacent_vertices(typename vertex_list_adaptor<Graph, GlobalIndexMap>::vertex_descriptor v,
                  const vertex_list_adaptor<Graph, GlobalIndexMap>& g)
{ return adjacent_vertices(v, g.base()); }


// --------------------------------------------------------------------------
// Vertex List Graph
// --------------------------------------------------------------------------
template<typename Graph, typename GlobalIndexMap>
inline
std::pair<typename vertex_list_adaptor<Graph, GlobalIndexMap>::vertex_iterator,
          typename vertex_list_adaptor<Graph, GlobalIndexMap>::vertex_iterator>
vertices(const vertex_list_adaptor<Graph, GlobalIndexMap>& g)
{ return g.vertices(); }

template<typename Graph, typename GlobalIndexMap>
inline
typename vertex_list_adaptor<Graph, GlobalIndexMap>::vertices_size_type
num_vertices(const vertex_list_adaptor<Graph, GlobalIndexMap>& g)
{ return g.num_vertices(); }

// --------------------------------------------------------------------------
// Edge List Graph
// --------------------------------------------------------------------------
template<typename Graph, typename GlobalIndexMap>
inline
std::pair<typename vertex_list_adaptor<Graph, GlobalIndexMap>::edge_iterator,
          typename vertex_list_adaptor<Graph, GlobalIndexMap>::edge_iterator>
edges(const vertex_list_adaptor<Graph, GlobalIndexMap>& g)
{ return edges(g.base()); }

template<typename Graph, typename GlobalIndexMap>
inline
typename vertex_list_adaptor<Graph, GlobalIndexMap>::edges_size_type
num_edges(const vertex_list_adaptor<Graph, GlobalIndexMap>& g)
{ return num_edges(g.base()); }

// --------------------------------------------------------------------------
// Property Graph
// --------------------------------------------------------------------------
template<typename PropertyTag, typename Graph, typename GlobalIndexMap>
inline typename property_map<Graph, PropertyTag>::type
get(PropertyTag p, vertex_list_adaptor<Graph, GlobalIndexMap>& g)
{ return get(p, g.base()); }

template<typename PropertyTag, typename Graph, typename GlobalIndexMap>
inline typename property_map<Graph, PropertyTag>::const_type
get(PropertyTag p, const vertex_list_adaptor<Graph, GlobalIndexMap>& g)
{ return get(p, g.base()); }

template<typename PropertyTag, typename Graph, typename GlobalIndexMap>
inline typename property_traits<
                  typename property_map<Graph, PropertyTag>::type
                >::value_type
get(PropertyTag p, const vertex_list_adaptor<Graph, GlobalIndexMap>& g,
    typename property_traits<
               typename property_map<Graph, PropertyTag>::type
             >::key_type const& x)
{ return get(p, g.base(), x); }

template<typename PropertyTag, typename Graph, typename GlobalIndexMap>
inline void
put(PropertyTag p, vertex_list_adaptor<Graph, GlobalIndexMap>& g,
    typename property_traits<
               typename property_map<Graph, PropertyTag>::type
             >::key_type const& x,
    typename property_traits<
               typename property_map<Graph, PropertyTag>::type
             >::value_type const& v)
{ return put(p, g.base(), x, v); }

// --------------------------------------------------------------------------
// Property Graph: vertex_index property
// --------------------------------------------------------------------------
template<typename Graph, typename GlobalIndexMap>
inline GlobalIndexMap
get(vertex_index_t, const vertex_list_adaptor<Graph, GlobalIndexMap>& g)
{ return g.get_index_map(); }

template<typename Graph, typename GlobalIndexMap>
inline typename vertex_list_adaptor<Graph, GlobalIndexMap>::vertices_size_type
get(vertex_index_t, const vertex_list_adaptor<Graph, GlobalIndexMap>& g,
    typename vertex_list_adaptor<Graph, GlobalIndexMap>::vertex_descriptor x)
{ return get(g.get_index_map(), x); }

// --------------------------------------------------------------------------
// Adjacency Matrix Graph
// --------------------------------------------------------------------------
template<typename Graph, typename GlobalIndexMap>
std::pair<typename vertex_list_adaptor<Graph, GlobalIndexMap>::edge_descriptor,
          bool>
edge(typename vertex_list_adaptor<Graph, GlobalIndexMap>::vertex_descriptor u,
     typename vertex_list_adaptor<Graph, GlobalIndexMap>::vertex_descriptor v,
     vertex_list_adaptor<Graph, GlobalIndexMap>& g)
{ return edge(u, v, g.base()); }

} } // end namespace boost::graph

namespace boost {

// --------------------------------------------------------------------------
// Property Graph: vertex_index property
// --------------------------------------------------------------------------
template<typename Graph, typename GlobalIndexMap>
class property_map<vertex_index_t, 
                   graph::vertex_list_adaptor<Graph, GlobalIndexMap> >
{
public:
  typedef GlobalIndexMap type;
  typedef type const_type;
};

template<typename Graph, typename GlobalIndexMap>
class property_map<vertex_index_t, 
                   const graph::vertex_list_adaptor<Graph, GlobalIndexMap> >
{
public:
  typedef GlobalIndexMap type;
  typedef type const_type;
};

using graph::distribution_global_index_map;
using graph::make_distribution_global_index_map;
using graph::stored_global_index_map;
using graph::make_vertex_list_adaptor;
using graph::vertex_list_adaptor;

} // end namespace boost

#endif // BOOST_VERTEX_LIST_ADAPTOR_HPP

/* vertex_list_adaptor.hpp
XFQ8dpRje3uT9LMXvI3tKzwRW+Dqq0Kym/X9EKm/nzzEc/yVtLHXmyg+trB7I89zkubT6tif8S0btmPP1vt9QOL6JJ9oNQsMD6Ra1wbWkU/bxpTtfJ9gEzggYoO2HMq6sxI3qWS0HDP+cs7XJe8H1cuyyc7WvjQ6/L62K/I0NyCcg1YsVO48Yy+t3xQDRo0ay6g1bvwEKX8V0llSfjAn26TT39XozoPGDjZ2i3Woy2xJW1HGwXOlrsWhj4di1huecFlJsXnXNpcxLN20bTs59oXt24m/Ve5HUo3ImJwo/tIsHdfR5ctzmJ9Zzbo58E4gPWFfhRneMRkLrKpBn2+EMy7K2BN/XEyyQt+LxbxlbiTsTKkSNUbmc1G1rDfSWlhBlGOMl4ywt3t+yGjr6VC5i/1slaDno6orfK2tNvJsSqtLX3uiUgWru2+UL9f/bFI/+4yUudaBlI2eDWm59vHp2VaP9ALrqfTK1pH0PdbhjCKrf7CdfYaUYUsZD8lY/F3lNFbxuMFzsTcp4VTfucmv2fVSm1uTUitYs1O72N9VCHrqplf39AjO9jjfaPLOktdNZM3+rs9TFlr1+lhwFvPrVVDkeO8TeUfrOORik0zaAmmrDjlOX6CPTRg7cdCw4sGR+/s+nCjp6sl4/0CWnJe/KehDel8/e0G+ky0P76sssYlHbr5p3/CmWg97I+vYL5V7/EVOPHv/3aRJl/P9TtKYPioG/eqTkDTTJU01STNHyqEl+JA1tsOkiWebv564XMk/PKesNfcj40h7SVOYs6NC74rOeC4VkXLq29RM0jSIruugiO1XPR0DLn1M7KrT0nn/n0JoZ9VIG5fmsa4n3JFWxdibxluvP5HzuG3dnW/SI/IcdbMa6vrqz0gbb8j5HgX8K7xXreQb7Zw0v/VO2inWk+nfp76Sk6x5I+/2JMonr3kfXumtYrXxlmkTz3VX5xwnyHVfnlOW7b7MISJNI0lTomm0bSSRYws8SfrOH/mtL0vrpP2GI1lPnzSnh791XPdK77WsNRr9HUoLjY9ec72NfH+dwt+DxdjHbGTtldd8kbab8Gz4e76W9tkBkjY3IQXLnqvw7jTCPtm6z55s1/d+58ku8/uy0G7iW5kemTe1R9p+udSVBpQ19sVRb5St//i/snce8FEUawCfvZJcLhdyl0YILYQqXYpU6UU6UhWBECB0kgABQSwoIIKIigiKKKCgIohgRUXAjqKCWPApT1FRsSH6ULHB+993c7N3CWd5/f1+Rof/zbffzE7b2dndmW+kHwuY+tsh+U0w478EOT49o4+qmhEe/10mY6a3TN85Y2to3FKj1LPCUJ4Vyqsz3TnszdVMdeRj/9S4JPSCcf+ecUvpMd9u0v6J5OtB8iV9sxnrhuv7BPxOdNZHtYmpeRj1i7DFeeghKV/t5w4jeXdKHGs43k7Sd0HF8DO7R6+TaKTLqsNjku/E5aozewh9bFVy1mZWe091xDmFJ8or3Od5HWqs9zKeer1qgi67DVJf36R56F8vdhQ5nXEjXMXeMxybfM2sb5LKOir7e6t7/YnqPVx6IFEV4rYGyjIXuo36MSVLZacmq8GpK9Xf6OUdaT5VJc2rzk3rqm6HW9PS1P60ON2eLf2stcfpVU84dVlyTek56BHPaQVSX2NdHtWSnGS5MuznNT1+OZI61+qdkhG8NxrZXYxpBjp/cN0iNmLXhPpiXQd6j/Sd0ffYHeJPCI3dOf6Y1NH79nMb4cWGNL/q63vIQElvZ0dZniNH4K7EPY/7Vl3HPji8XHJUVvUdqVwz6JvrweeOJ88v8nyZ6KqsOrs2KMsdurcfI+535Ly7Kv6avVW/3KNqmLT3EH9A4rg=
*/