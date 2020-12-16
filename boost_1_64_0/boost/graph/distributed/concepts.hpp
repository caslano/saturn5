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
90s5hzsTk03fbzIPpHF8z9B9CtHbgd6Y7jIvIzG4rSB7i3h4iM48JLtF51GvfZ5ymhLudTPuKMf6g6SRpHvJj+FVY4q2N+s4jj0vtnPHwjFMONX4FvG7S/rtEu1+am4BZcK0/zMH+sIzGXWoYvoKKUbXvy3WaF/x5fKC2+UbBksfy7SXj4k/zn9dhN8px/3SGzmnkPm4btozua4nE3k2M94o7b55p+3VQ/qIsfWsrtFXRJexlkTXtF6PHuEKvNP+2Ffa5oh597X0OdtV4l8e2yqmyNoSE2d9gasdG2+lxzJeqO/kuf19Ovcw4nezGfOzwsb8BpHWR3KePb3vlpoQU1ZkjKgNRYb1ox1vMrU+XyKa54nkazm53jT8LSQ/+ifq/mH86b48hKcS3lrCeyfa+8lJB3tqUVCa5w+SvoHJ83GD7Dw/QfgVkkaZ4HI5IXu6XTBraf+opZTxA9Gl2BWgvrs6oxVlrL+5v7W+9hx0pYgOuS86bWNTqQfz3Jmu77X8byTVq+Q4pRID/WqOQ4OtZY70P5A8eyBR+6gmX6cEzY0f2lvmqcaXto6VTtbryRfZpHimUjA3ME3Sa4JuTTlejhzvctMPsfsWayXe1Z7lvGuIzNzf+yjTN0k6i9GrK+lcGlQXpLaY/qU9v5t7U1QwNStX1qaQ+AvgcxL/ZW/4e3iNwL5p6bJvY1Rlvrx2sVqxW3iGJz5qEG+jhJu25UNPAj2AJtZ72IrWZX3q6qzxPM3q6O7APNq+ksebSfkxycM3Ex36VeY99JXe9hpIq5Anmzz3FcnRgWechC9HX8ustlmSj/69CQlrINc3PDG4PdFqLzpxbt4tRKdLUDmljKqSlA/SGS46DRJD+t1at+OGyJimlYpVZ4quA1A4SO67O9cagy3iISvNnWrGr+qLfg1m76HLr+fTpb2MzWLlni3sAXqLa5Irjl2wZ3tqW+tpp6+MesiVHlMtpH92uTS5/vMrRvKmnN9j3iTNW62/krPyfqX51LmSxvfVnikSX+6zJe3LbK+dB7TZkgf2s+t6udeLPS9bT7tTwp8tXGMs5z3Lne2R9hD9lXJOfyVNMw+6IJD76Ej/5knR2e6176E2O4EySjpNRWeg/cwx71b28zt6oD1HfBf+FyTOnyTdWv48k05QcJzzJU68WevgW4lzs9YFLQd6Hlvhs1J+X0nU7yDyfhJc/2f0kT5C6dJMoZGyhSxG0rw2rA3UvojGe13Oo4r66XXIc8ftv7eE50kalYPqeJFU8kD8dj2l7VK/eZZI/EzCH5P4b3pNW0Adz8opLNJ3K5Mfm6XMlpbyMl/rnV3esHPI0fxQ/bly3slynL3498pxVnntsT8e6jr2V0PL0F3SZ5oVN8S6jXakq2tOdG1rW/Rq94Vanh6WNu7FuDiu/xysf6fRlrztetm6151Bv4Vsjxpm3RlV29oStckdNmZu1ud7Q+7ThWXrWl9F1Yh+2toXneyuGXcxa3StcnUq/Z6ngegF+lmNvAtpvYZGxVmTYxpae2PirVvjLrTuSqhk7SwbI3kxnbSD7l+g52Dy/8L00H5DlvhjJV/2EL5M8uUTb/iYfA19dp30x4+pxArZM92rrY89w63yMQlybOy4zbt3nL57t9Q+QSnJq2rkVSpt74XYAC/CDryHa4g70/1cVGX3X2O6MbcsERsDjxUTl6h7AfMdR8pXDVdl2uxuMu5IeqYPMFC/owTaqWjZ35g+sPw11T6RyPjFnx1P1xY5Ivl/W9CzcnJIm33QZeentlMh+fmsXNf56qdGpfufB/IcIfw6yU93UHswlRU7sO/hV/AYVZWqgfpm17UTvrTw1dLvS+/Jufby0jqXTivd3708oY0=
*/