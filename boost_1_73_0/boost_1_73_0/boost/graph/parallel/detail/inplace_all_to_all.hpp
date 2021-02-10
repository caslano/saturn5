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
XVWAhxNg1Odu+gEHtpZhSPM2cuPaYJ5oDxgeTZLhak3TMb3haag6SipuoWoqXJzJuif4BBA6uqzYcfxsy5Ma0gtWd3bo57o3xYSx2xFMtpJXv+Z0yM81z48ZSp0DuX6h4sLmAqshFNekdbRj+EWbb90pmQ0ADt7kS5wB6L5gRm96l5cKsVUCueC1yWMfqrwnQcrphH0vn9wHTTaxae4rbGxtECd2IWoEptoCCurverUyC9HiqYWumo1WOX3iK/HdlPbi/CVf/da4pGamL/qJ/bImRWn1UMjpXMspxqJqR6jKyFTg2NP2uA1q2dhpv4WKuNGvnd/9WAw6o0tciRegDuQXEq6MrZDSBSXNaNweX43yeWGhV8jPbLXck8vrN2m+xCJsrta/m/XjysXJcN3QD6qG9D+io3wNTAl/3OHhbj30zT4cKJN46d/NLAdCKDJUAXrCMyYnrcruyFIi11Zxgy25FmnCC9arweA0l/TyaMLKGsPu28Gb7umxQXdTo80ns4ajUZKYWsmzCwcQiu2ShR1Wj2G3PRr0nav+6LLbgXWhe2qvT3mzaLKErYNy+UiBsn1iFbc7uqbRN913ncHF5XBw0Rt1VzW7SIKPSrHD1D1JPAeV0ntI2532Zk3jCfev02L77Kx33qNlt/O6
*/