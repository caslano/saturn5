// Copyright (C) 2004-2006 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine

//
// Distributed graph concepts and helpers
//

#ifndef BOOST_GRAPH_DISTRIBUTED_CONCEPTS_HPP
#define BOOST_GRAPH_DISTRIBUTED_CONCEPTS_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <boost/version.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/concept/assert.hpp>

#if BOOST_VERSION >= 103500
#  include <boost/concept/detail/concept_def.hpp>
#endif

namespace boost { 

#if BOOST_VERSION >= 103500
  namespace concepts {
#endif

#if BOOST_VERSION < 103500

template <class G>
struct DistributedVertexListGraphConcept
{
  typedef typename graph_traits<G>::vertex_iterator vertex_iterator;
  typedef typename graph_traits<G>::vertices_size_type vertices_size_type;
  typedef typename graph_traits<G>::traversal_category
    traversal_category;
  void constraints() {
    BOOST_CONCEPT_ASSERT(( GraphConcept<G> ));
    BOOST_CONCEPT_ASSERT(( MultiPassInputIteratorConcept<vertex_iterator> ));
    BOOST_CONCEPT_ASSERT(( ConvertibleConcept<traversal_category,
      distributed_vertex_list_graph_tag> ));

#ifdef BOOST_VECTOR_AS_GRAPH_GRAPH_ADL_HACK
    // dwa 2003/7/11 -- This clearly shouldn't be necessary, but if
    // you want to use vector_as_graph, it is!  I'm sure the graph
    // library leaves these out all over the place.  Probably a
    // redesign involving specializing a template with a static
    // member function is in order :(
    using boost::vertices;
#endif      
    p = vertices(g);
    v = *p.first;
    const_constraints(g);
  }
  void const_constraints(const G& cg) {
#ifdef BOOST_VECTOR_AS_GRAPH_GRAPH_ADL_HACK
    // dwa 2003/7/11 -- This clearly shouldn't be necessary, but if
    // you want to use vector_as_graph, it is!  I'm sure the graph
    // library leaves these out all over the place.  Probably a
    // redesign involving specializing a template with a static
    // member function is in order :(
    using boost::vertices;
#endif 
    
    p = vertices(cg);
    v = *p.first;
    V = num_vertices(cg);
  }
  std::pair<vertex_iterator,vertex_iterator> p;
  typename graph_traits<G>::vertex_descriptor v;
  G g;
  vertices_size_type V;
};

template <class G>
struct DistributedEdgeListGraphConcept
{
  typedef typename graph_traits<G>::edge_descriptor edge_descriptor;
  typedef typename graph_traits<G>::edge_iterator edge_iterator;
  typedef typename graph_traits<G>::edges_size_type edges_size_type;
  typedef typename graph_traits<G>::traversal_category
    traversal_category;
  void constraints() {
    BOOST_CONCEPT_ASSERT(( GraphConcept<G> ));
    BOOST_CONCEPT_ASSERT(( MultiPassInputIteratorConcept<edge_iterator> ));
    BOOST_CONCEPT_ASSERT(( DefaultConstructibleConcept<edge_descriptor> ));
    BOOST_CONCEPT_ASSERT(( EqualityComparableConcept<edge_descriptor> ));
    BOOST_CONCEPT_ASSERT(( AssignableConcept<edge_descriptor> ));
    BOOST_CONCEPT_ASSERT(( ConvertibleConcept<traversal_category,
      distributed_edge_list_graph_tag> ));

    p = edges(g);
    e = *p.first;
    u = source(e, g);
    v = target(e, g);
    const_constraints(g);
  }
  void const_constraints(const G& cg) {
    p = edges(cg);
    E = num_edges(cg);
    e = *p.first;
    u = source(e, cg);
    v = target(e, cg);
  }
  std::pair<edge_iterator,edge_iterator> p;
  typename graph_traits<G>::vertex_descriptor u, v;
  typename graph_traits<G>::edge_descriptor e;
  edges_size_type E;
  G g;
};
#else
  BOOST_concept(DistributedVertexListGraph,(G))
    : Graph<G>
  {
    typedef typename graph_traits<G>::vertex_iterator vertex_iterator;
    typedef typename graph_traits<G>::vertices_size_type vertices_size_type;
    typedef typename graph_traits<G>::traversal_category
      traversal_category;
    ~DistributedVertexListGraph() {
      BOOST_CONCEPT_ASSERT((MultiPassInputIterator<vertex_iterator>));
      BOOST_CONCEPT_ASSERT((Convertible<traversal_category,
        distributed_vertex_list_graph_tag>));

#ifdef BOOST_VECTOR_AS_GRAPH_GRAPH_ADL_HACK
      // dwa 2003/7/11 -- This clearly shouldn't be necessary, but if
      // you want to use vector_as_graph, it is!  I'm sure the graph
      // library leaves these out all over the place.  Probably a
      // redesign involving specializing a template with a static
      // member function is in order :(
      using boost::vertices;
#endif      
      p = vertices(g);
      v = *p.first;
      const_constraints(g);
    }
    void const_constraints(const G& cg) {
#ifdef BOOST_VECTOR_AS_GRAPH_GRAPH_ADL_HACK
      // dwa 2003/7/11 -- This clearly shouldn't be necessary, but if
      // you want to use vector_as_graph, it is!  I'm sure the graph
      // library leaves these out all over the place.  Probably a
      // redesign involving specializing a template with a static
      // member function is in order :(
      using boost::vertices;
#endif 
      
      p = vertices(cg);
      v = *p.first;
      V = num_vertices(cg);
    }
    std::pair<vertex_iterator,vertex_iterator> p;
    typename graph_traits<G>::vertex_descriptor v;
    G g;
    vertices_size_type V;
  };

  BOOST_concept(DistributedEdgeListGraph,(G))
    : Graph<G>
  {
    typedef typename graph_traits<G>::edge_descriptor edge_descriptor;
    typedef typename graph_traits<G>::edge_iterator edge_iterator;
    typedef typename graph_traits<G>::edges_size_type edges_size_type;
    typedef typename graph_traits<G>::traversal_category
      traversal_category;
    ~DistributedEdgeListGraph() {
      BOOST_CONCEPT_ASSERT((MultiPassInputIterator<edge_iterator>));
      BOOST_CONCEPT_ASSERT((DefaultConstructible<edge_descriptor>));
      BOOST_CONCEPT_ASSERT((EqualityComparable<edge_descriptor>));
      BOOST_CONCEPT_ASSERT((Assignable<edge_descriptor>));
      BOOST_CONCEPT_ASSERT((Convertible<traversal_category,
        distributed_edge_list_graph_tag>));

      p = edges(g);
      e = *p.first;
      u = source(e, g);
      v = target(e, g);
      const_constraints(g);
    }
    void const_constraints(const G& cg) {
      p = edges(cg);
      E = num_edges(cg);
      e = *p.first;
      u = source(e, cg);
      v = target(e, cg);
    }
    std::pair<edge_iterator,edge_iterator> p;
    typename graph_traits<G>::vertex_descriptor u, v;
    typename graph_traits<G>::edge_descriptor e;
    edges_size_type E;
    G g;
  };
#endif

#if BOOST_VERSION >= 103500
  } // end namespace concepts

  using concepts::DistributedVertexListGraphConcept;
  using concepts::DistributedEdgeListGraphConcept;
#endif
} // end namespace boost

#if BOOST_VERSION >= 103500
#  include <boost/concept/detail/concept_undef.hpp>
#endif

#endif // BOOST_GRAPH_DISTRIBUTED_CONCEPTS_HPP

/* concepts.hpp
tz6I/RUg9leA2F8HxMnwdHB5NjtYicIjyVhFwIrQmnjhAATqc5zc8vOenM8MTNZniG/CxdcKT7oJMBewM8t4eoxDtoT+BKdQ5KbrTUYCAyDges/qwRzrqzsptV0zDwVihKLAOjyauHAe+piO45MBU/gFZM37mxW7tCkq4Afkp3zTMXS7ETgLSglVhR8ZOYfxPHkEFo6NxSa7cxDGJc4Dv+vWuzv4PZbn9E2eBPpmcViEXoSpNnZjQbosonpv3L3Ake68jKKOJj0LHfRPNPh94basMtf102w9TIEDBDdhTLEo5wp+zm00+jDCadX1LUvxSwZNC6mWlSEQUb6VOb7rkL3uYZ2+3Pe1KWxRTjltW4YPd1gfZhpT8y5N80BhPiv3cGq0wBlNlNhqwrErY3WU8ovhzAWFAIqgk2Zw9NldP6c5kj4MVNGAXxcQ7SLVzRw8REMNd4GhP3eMNAemA9QwcCXVSCEi3LHbEs0OSws4hpOnBby+YzEJS/fguBTALU37F6N0YdUUUKUcM7pd5ihsYjgZndjy1rjbMrb3K9Uj96muwiLvF1EOOCPNXS9KVT0YXVm/zHjFRMZZ48lseEBuFzRGxwSxWWLcpS4nkQXFa4Nh7IPaB4OCV/3klSP4zjfYM8bz2z5gU/7e4uv+
*/