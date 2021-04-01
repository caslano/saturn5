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
GT6+Vc0NoplTUi3uuAW5T0uVyjpF8rNMzKNzvql5FKhZJPK9kDBsJXXnNd6hcWZXgVdgRzujvnNmSPMG3IZfWQg2gyk9lLoa/NCsw2aFASJm/COTfgX05RYfDivAF4mkurcn0Htxsbp+mzZs6JxKgSzoYdvJMLXSFhItuM2CAIV1h5ys49PeMDaN6ScVU+6Sql9X+y/jOFQ2I7Wst0UZRNf/91FCGnAiiax28uk5qQr/28bhsgKYx3PFyvhgJqvR7kUi+o/RRxR9s8td8kZJNv85ggaz+ZHr0NgdeM3mr03R/dv1Zh4pii30fNtRM0JK2lczcpHXJxWE3KExQob+r8Wun3SrHj/KT07AqUKfSCBlyQojwnLkR2AtLlM7oedB4g9n1MfuEp+pU6hzxdCYe988CwEHFymorxKgsRigraku2X14kIbXOeJE91xsgE4Fs+m/6hvQ6sUHgYSVwYdcP7cVkITsLmNV4ttZA54t1SvuJAMIGXvGDEL6TdCdwmmevFvN5/AhIp5OhaukVCcpsfgzc1Ap6Q535yfG8BMekR5uBcjqEZxezgsW5w==
*/