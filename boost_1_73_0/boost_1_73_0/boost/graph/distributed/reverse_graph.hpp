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
WbKIxJnDUq07O2w3/+CRobqVY5Q9wvyq2bxmbAnCGAfSOc+vemcXnbw7fcnMtDOrkMMiNvsdmYViolZeB6J8q123jERdZ0FguIkGNSZxlWQ8tLDWYe0V6K+PsP6z6GtPP2NLPnku5yTO9vTPtrIWByr4J0moIi1NZ1WM3jiFUdaJnNtKh2f2lz/MieQVO2pvGmd1ZbWUxNYFj2RcyJx9bu5i3p0E7yb4yZS5FLsJgGF4vKEqqAx3QdIjZrQwy+SrDonuY+QxS+8WcS1dWbXWpJs1zYbeauulF2wrjNKS/Uxv2c33uTbG1qYbtWQjOEbis2ieFvyz6F64kAVl8bMzOH3z/Oq8wMKacErWM6NAxyr0ExWxKBsuC3N8n/GqpjfsnX3X6X2F8dC/8NEJo5DybUqmaGTRVrXN8NON9Z0HjgWZsVohlbVGyT/Ao5UymHVpT9hQ8HLEWJV1CfGQr8zc8hN+zgNjHvEw3VmeIi3jtSrTVNKeBs3CEkVPTn6Mo7XGOHrwGIbzofoouxKHsjpoxt+DSqKtg73hl1jlUljlDVh9kLfS3MrcWjumJ4v8VrntzfJbV211a91nvgrRfroJYZ2NsVQ7iDBe1UQTDh7c+qKKkTSX5WyUU2HNdErj5uCw191n3Zswwnrm6l6A
*/