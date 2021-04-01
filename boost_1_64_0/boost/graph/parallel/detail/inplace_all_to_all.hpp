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
ArrziJ1GgGzZKv/HQL0O+x8/damYuygE7cuCs743JGJZMUu5jn4Ucc1s3YmL2Npg/rLGQQYJPZYY+4OwXiCtupCpMn99rFUucTKej+brClQMUSBweEVgZKJO08ra5ZZ9Y6Hha1b5+OdfrW63w+4y+Hfv+CVaxxdjjMmAL+JxmsP8WkQW9B8OMNMDzOIE81z8IzSRcSHeVU02vPISU5qKSP+xs3rVoIhOrHsRBUbOdOgWOX6GguRvsURQXudcMx7SNodcQ+GDSRrDim2+4STjGay4LaUif7b+0VfuGOtT2IybA8B80XdHmTDLbK1SZglTJbf0iAUOF8yeTmRxox0UDxqQE3TkMe0ulYm1jccQgRsmmWavwtAmddSYRSQsiGSG9Dzn1gFFzhmQQe5X3MNqCgUHmgh92u5gZtPgwmJRKMgfJc+fBF+jLSvaRM9wcOKdZUDglJRWaJwoYpUV9pVt/VrSq2LFpX26NYnrvG5wfNb+6hRpkK7D5C5Q9/1iSc63jvKcV3F5dWOMChgI05QkYZZ6ue3qjF9o/YAyMw1fllE1D8ZSx7W/XmvY0Q==
*/