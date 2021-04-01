// Copyright (C) 2004-2008 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Nick Edmonds
//           Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_DISTRIBUTED_FILTERED_GRAPH_HPP
#define BOOST_DISTRIBUTED_FILTERED_GRAPH_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <boost/graph/parallel/process_group.hpp>
#include <boost/graph/filtered_graph.hpp>

namespace boost {
  namespace graph {
          namespace parallel {
      /// Retrieve the process group from a filtered graph
      template<typename Graph, typename EdgePredicate, typename VertexPredicate>
      struct process_group_type<filtered_graph<Graph, EdgePredicate, VertexPredicate> >
        : process_group_type<Graph> { };

      template<typename Graph, typename EdgePredicate, typename VertexPredicate>
      struct process_group_type<const filtered_graph<Graph, EdgePredicate, VertexPredicate> >
        : process_group_type<Graph> { };
    }

  }

  /// Retrieve the process group from a filtered graph
  template<typename Graph, typename EdgePredicate, typename VertexPredicate>
  inline typename graph::parallel::process_group_type<Graph>::type
  process_group(filtered_graph<Graph, EdgePredicate, VertexPredicate> const& g) {
    return process_group(g.m_g);
  }

  /// Forward vertex() to vertex() of the base graph 
  template <typename Graph, typename EdgePredicate, typename VertexPredicate>
  typename graph_traits<Graph>::vertex_descriptor
  vertex(typename graph_traits<Graph>::vertices_size_type i, 
         filtered_graph<Graph, EdgePredicate, VertexPredicate> const& g)
  { return vertex(i, g.m_g); }

}

#endif // BOOST_DISTRIBUTED_FILTERED_GRAPH_HPP

/* filtered_graph.hpp
Y96mw078WgFqcRE1KS1knkI4+qe39WpaRkOKZGh4HILOeB/m+ullxZ3jW5g+MjWtye+kUsbLDeD31zlAQfY3Qxxpue7m+q2FrriXt39+FShBb5isafxZ6WwmBVbCPiE23sbS2gm7MUcRedt4LEQI0pOv82DMImksu+spD1VpVgtCx9DbiKXhCYIEltHsNkN5zo6Q0MVzUCIAAYl9PxogEVci+tYzy7IK/8dvvh+kk0Rivp8JzCrRE+cIffMjPRTrUq7HWwHOIn/sfDU+fqGaPj6pa+dxFeOP1MGobKU8oYbWdoGviG8PGPzEyxUpnk/7p+IkjAOxpQ2Sk4Jb7AcaMPycT6EH33siFN9w9R7jkSkZrqVflip03JIhlvdCZoaEZiqAO2d+LzW1L9+PQIU++qKEGJIfLdPy+7fO9ME7lPmaDJ0GcNhf00WmBHRXQ1t18/YxgGwscN7PvfLMveAJodroUqSTHrKnx+PBaCm2qP9OqqbdT/SmsdiEQ6GksNqqdfQLEgKjTBdbElzgqfqETu+ThH5B77QjTZRkWozn+U4iN6dFun/uB3wwqA==
*/