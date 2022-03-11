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