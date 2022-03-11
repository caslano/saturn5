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