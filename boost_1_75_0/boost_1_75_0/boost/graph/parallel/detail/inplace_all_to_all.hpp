// Copyright 2005 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine

#ifndef BOOST_GRAPH_PARALLEL_INPLACE_ALL_TO_ALL_HPP
#define BOOST_GRAPH_PARALLEL_INPLACE_ALL_TO_ALL_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

//
// Implements the inplace all-to-all communication algorithm.
//
#include <vector>
#include <iterator>

namespace boost { namespace parallel { 

template<typename ProcessGroup, typename T>
// where {LinearProcessGroup<ProcessGroup>, MessagingProcessGroup<ProcessGroup>}
void 
inplace_all_to_all(ProcessGroup pg, 
                   const std::vector<std::vector<T> >& outgoing,
                   std::vector<std::vector<T> >& incoming)
{
  typedef typename std::vector<T>::size_type size_type;

  typedef typename ProcessGroup::process_size_type process_size_type;
  typedef typename ProcessGroup::process_id_type process_id_type;

  process_size_type p = num_processes(pg);

  // Make sure there are no straggling messages
  synchronize(pg);

  // Send along the count (always) and the data (if count > 0)
  for (process_id_type dest = 0; dest < p; ++dest) {
    if (dest != process_id(pg)) {
      send(pg, dest, 0, outgoing[dest].size());
      if (!outgoing[dest].empty())
        send(pg, dest, 1, &outgoing[dest].front(), outgoing[dest].size());
    }
  }

  // Make sure all of the data gets transferred
  synchronize(pg);

  // Receive the sizes and data
  for (process_id_type source = 0; source < p; ++source) {
    if (source != process_id(pg)) {
      size_type size;
      receive(pg, source, 0, size);
      incoming[source].resize(size);
      if (size > 0)
        receive(pg, source, 1, &incoming[source].front(), size);
    } else if (&incoming != &outgoing) {
      incoming[source] = outgoing[source];
    }
  }
}

template<typename ProcessGroup, typename T>
// where {LinearProcessGroup<ProcessGroup>, MessagingProcessGroup<ProcessGroup>}
void 
inplace_all_to_all(ProcessGroup pg, std::vector<std::vector<T> >& data)
{
  inplace_all_to_all(pg, data, data);
}

} } // end namespace boost::parallel

#endif // BOOST_GRAPH_PARALLEL_INPLACE_ALL_TO_ALL_HPP

/* inplace_all_to_all.hpp
+f2Uf65vtcxbVsjDg7hQfxxon5W6Om/Q6BA/4/AHPeA5dXSiai7TBrstZJvZNIaemzlgM9sScEoylDbJEanri9WtGJE+g2ylMjcu9TQkvsiMY3VTj1r9Q2a5RkmrgEBKLS0urna/y+OXjD76MFnMR1llsEnFs1c8Gm/5vJiJ3jtjD2W2HmVJvfE9ZfUN9kxlJ4Zf2zoPKMdfYdrZAYEf9ZkPko1GulIvOpUXi7CS3IS/uGAlHTjl6TCzennwotCrZEZE8dkP5A0yw7uxaQGFHPA//OOrZkoOU2qJOlS7launDg6v9UnAKcm17B3hHlvEh2NeaF6R63nSxdJ50iXH5NglEgwd6WXb8jACPQpnMpf7Y8HSTAGDQRLL0es4ZCj7BMsp/MR5DStcY3cDPcmNvmL7B38RQvIHLruyw+ijFCA8fxLn3CDNFXyzWuqwY50m3SjXcBzYmOER8hwJluc6lT5yud3hnyA9ZVuYVBYlrkV3jkCYkH8bWlSkOnj3/ttzuDfL/q7ueAMXWWbXF9F2CynOa7kW0wkSoTbwhM496isccu/s7uX+3m6Ievryyf4etclU5vT49h5mGu4vAUsa/obURXLUfsZEfZBQRGe51TU79NmLTVhmTEJOHFYersQ9MCeHeQ5TuGZQ/5SW0bkvGWFAAXxrk1FOVZ+PUKyTQxuRkMGwWBFuQ6wrVMIiaPBapRPGQ0K2TkSn0vHH
*/