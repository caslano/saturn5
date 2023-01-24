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
P87nk+YM5f9sAP92yv/VG/Bv+ETI10LdVuq2Ubf9k2vz51OuUf/2gPq30/q3/zr/2yifGdRVU9dM3cTr8C9Mu0b9A/i3U/6v3oB/DeVzP3Wd1HVT98lr8D8D4SnzhspbxFm/vC0+S+t/9tf5hx4X8o2j7s3Hh/JD+/ChzKH81gXwa6X8nr0Bv5cpnzeo+/Y1+GH9snOG8usL4Bf7lYAv/erX+cVSPsnUzbhO/d7LHcqv5Cs/vx2UX+0N+NVQPvdT13kNfu0QDl84lF9bAL+orwV8zw34naR8zlK38zr8frkGv+Sv/fw2Un65X99g3vmUzjvUfejTa/P7YdFQfrsD+DEdVO9vwE9G+YRTN/I6/L7MG8pvaoefXzXlp+34dX4WyieJuumfXrk2+fOnfnv+2atoBdKUMv71xrs1N17f7Ovwr2+O07J2XKOsvt/5nf34UIdZ840QH0IhGcKLAWoBGmpgXTENygJgAT8LUA+wEdJeBHgL4EOA4wDffyNwCIIWlMCoVlGzbMkyq21GUXk5M7vSbrVVFpTPs9ZY7UxGgb2wJLWqyFFunbkiWfBcGZlWUGFlMq329Gp7aVVlzezK4iomq2rp0nJrjq3Ubs2qSnfYqx32xNJyaw1DoiBinnUpRmApquVCvWdY4rLtK6qt+aVAITZ2sO7YhvgU/s2JH8RjeASNlzBBdejKD13ZbigT+JXddRcYeQiNYzH8
*/