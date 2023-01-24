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
4i8kZaB541oudeXLYFRxjHenJ3t0KM/pKa6kZM8M/NhBUgqwdCWF00nYd/WEe5Vsf6KYgXncsQg8Ine6LNPzC4pompRveY9sIH+kSJO608M932L0KL4FIka50+WeEySbhESkSdYnRaxLHFnsTrqpmBjRSRJwR+EBhTycA1dbcMMLlCAJbyxwp0s9z1Byq88iF8Uo54NSLxoJsV2HnRZvV69QRBkOdReSxCJ7OlgsgJdJC+UpwdetYLAMA/9C4g93p0sgkE4C+LBRFvZ20sjGs/KRLa60CHzWBfbRYImaQ8gWXJIUL7MNE0rhGUtwpSiTn2FRjguXNLgPXjw56YDzbHsmfu65MSpbvLdeOVp80pUgN/TULMRPiLeQTVRYO4IENv5TIl4FKiY3nK+RXtyPImGHtVEkv/8v6HeEZ+Z454ejwIIQOpsinc3yrqPu/USM3sHNzpgW8TnxScN528vkLCZ9kCXPdje6zzf+MMI1vwfGGkO1bNkIYjh13oQLxlhpZk69sQfPV4et/R53vPExpefQT4GncMkphARYQDkbfOeFhENtMFam9l2Iy5Db4xu/HeVuqc+O9SSQfWP7WNCaEqQFuvczuY3bsTJTsBndAu4wekyR6F8nvtdfegEF2nBvfE0Wnjhq8VwiiPZmYE7Obbpj42P2g0obGpcHo6T3kXOWc3H3vRUfVDwu5H+m5N2/4713ve4TeAzPU05e
*/