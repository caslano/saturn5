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
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
*/