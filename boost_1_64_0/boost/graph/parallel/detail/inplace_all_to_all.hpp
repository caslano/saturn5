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
q2U9TszM5g2hjtqA2ziz1D46OUruIys8uFjrUg3TQC+LPpL+2LjP5TezxyUvyhbNbyXSRghQ42JDc+3/t91aq37posddt/CeCbX8K0XLsLLhOqfhgzXWcTpJD9dRhst1n/70TJfp76nL9tbneuMlXdXmXqe5PQMiw+hnDkgXeaeZOkaPlPlpqK8b9Zfh2tq81Hn63CVbylw3C9PWOIL18Shd/04fLfNd3ezB9p9r3K/e4+Rc3kGyvN3rRescaKUM24xWqF0fg1vLd9n1++t0XSmLwLovfbSM/15bsLU/6PFuUusswgjW6+ctyQvW9y6Eync3MXlPk896OUbN4yQZdjjX56LZi3sY141aPudT949rGPoZoelSJtoWqT/nWFk4Q7p+GStlats6sO+Gkz9b9s3Cc+r7PM6Fqqp0NWUCVnG5DlRL3U+d8A91PevV7Zwom/zJcg1d72OSn4PsL+Rb+4s8F4aVoiVfVqzco2yNQ7Zz3U+O+zFD2gkvyTwbRnt1fv+uR7raGt2OcDvf3znVkH9diZJES2Iu9cxqmZ/cyePSOcvPHDHZ9ayfIrr/BVqP2Vb94RyurK4/3pQ0dw5Lu1hfE7b6FZbPaxlhavvqoscRZd23VeR9FFyX1eUaqzS9E0u6tHXe4vG+0HS3YUi7DUM/j5SrG+nsl/Luz89MWRdqOcjx2+o3Kcatzec+H9Lu05/paZX1cxWj/Rg3hpuX2/QoPzF+wfx3o1ssCDrz94/cK2hz5H+x8NxHbUakr5rx29Rhr1XaZOd+0nKO/A7dh8ecS75aKyi7/JnHGt58jw3T7sifNv/B7LX1v0nftv18ly3rpiazPPwd+VMjl+7b93BM36NrRr9+psbARtz/EuPIr3BieEjGQ10e/yZodnaVGkksq0PRjvwdrbtevdWs0WfP/ue7g8PN4Z9wri7l1y8d2Wun/89fv/NStdvLl8x5yTCmSP4bzzy8uNb83SO/K/PX1mvx99DT16pijvwWN+Kr97k+7cmtHQdEXyw27zH1vLq5/1jyT5syyl24vWh1u68q77hC/SbzZXspvVKV6debxtyMiSj9+rCv2A/8HPmt40Zcf3TQqJp+k0aFTPvPiM84p5Tyxx757KPb1565OmVexTI75g8MYDqJcHPnOw0+zI+L+abW8Ml7fnv1yyiOreUd+Q+9/ci68BNRLz8w88LgjJvJtB/myPjzz/W/5/mUzcFPhBwyo66//CbXycIc+R+EltwzpEGD/a3sNZs+HNue7+xe1pEfFZra+UjPi2Pvrbp07rQpm69xziDzNevlFz7//mBCwoyDvXPSn95wkeUs+X8P25B2oHz1Zkf7vRv49tFdNbmWKNNjv1rm97E90gZ/FVz96eyFMzg5eVLyExLW9/nh2J/RvU4+Ur7Xi+ULuIdZpvPhijXidpZZ8uofU96Yc2TulV48lyTrd+2ry98/9q+Hbz4SubtUzcAb3XhWx3Tk93hjY/dvb2/rfGnzc8uCt1SlTbxUpn/TqvXtHvf3+7vN8MabM882Hsr9ZpJ/6/S+wOenz8jr+OX1oekDq57hWoiMZ0LM3Gszei4f8MS9D74Y3iDoPPWsrPeL8+NeqH0g89aMK+venLmu4jZ+Y5Ly2UfHzr52ufpHny1qW77WuSZsn61kvmLenzb/VuXkd57MeeDV2W9vP0R9L8tnS/+pyRcDFqyfvrHkmUMbFh7gWWnyQf75RbAdsz8wmfQ3bP1tuOT7W3/L/QO5TEdFg/Fbf8t5JvUKZ9eFfUjvxaUGw7n8vdL6m+u9sr3KsO/qv/nc+i7p7zPJZP2zHt5Xf/dj239P/f09f7N5M6x67zWyKGQ6ArAFIW11uUWZaUM=
*/