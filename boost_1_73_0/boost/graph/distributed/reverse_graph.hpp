// Copyright (C) 2005-2006 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Nick Edmonds
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_DISTRIBUTED_REVERSE_GRAPH_HPP
#define BOOST_GRAPH_DISTRIBUTED_REVERSE_GRAPH_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <boost/graph/reverse_graph.hpp>
#include <boost/graph/parallel/container_traits.hpp>

namespace boost {
  namespace graph {
    namespace parallel {
      /// Retrieve the process group from a reverse graph
      template<typename Graph, typename GraphRef>
      struct process_group_type<reverse_graph<Graph, GraphRef> >
        : process_group_type<Graph> { };
    }

  }

  /// Retrieve the process group from a reverse graph
  template<typename Graph, typename GraphRef>
  inline typename graph::parallel::process_group_type<Graph>::type
  process_group(reverse_graph<Graph, GraphRef> const& g) {
    return process_group(g.m_g);
  }
} // namespace boost

#endif

/* reverse_graph.hpp
IgpJMn0Jn21lrQPs77w8i7AiO3KS3pVEp+dwn+bQxowueeHBgwaA4cyDci6knC8gp17q5rtyBhU3IOcmd04/5WyknLslJ3Op6crp55x+yrnEnTNAOXPWI+ceycn6+B1ZiZwBzhmgnNPcOb2Ucynl/L3k5H6vdeX0ck4v5fS4c/ooZzPlfFHnxHj/hCunj3OyWqvRcOUcRznHkErzD5KTVf4nuXKO45zjKOeX3DnHGOGzrBWU
*/