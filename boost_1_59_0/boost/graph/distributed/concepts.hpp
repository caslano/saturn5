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
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
*/