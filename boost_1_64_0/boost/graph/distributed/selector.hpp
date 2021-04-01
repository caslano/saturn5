// Copyright (C) 2006 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_DISTRIBUTED_SELECTOR_HPP
#define BOOST_GRAPH_DISTRIBUTED_SELECTOR_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <boost/graph/detail/is_distributed_selector.hpp>

namespace boost { 

  /* The default local selector for a distributedS selector. */
  struct defaultS {};

  /**
   * Selector that specifies that the graph should be distributed
   * among different processes organized based on the given process
   * group.
   */
  template<typename ProcessGroup, typename LocalS = defaultS,
           typename DistributionS = defaultS>
  struct distributedS 
  {
    typedef ProcessGroup process_group_type;
    typedef LocalS local_selector;
    typedef DistributionS distribution;
  };

  namespace detail {
    template<typename ProcessGroup, typename LocalS, typename DistributionS>
    struct is_distributed_selector<distributedS<ProcessGroup, LocalS, DistributionS> >: mpl::true_ {};
  }

}

#endif // BOOST_GRAPH_DISTRIBUTED_SELECTOR_HPP

/* selector.hpp
CSUwLFhS4eokVht929Jraf90fv2L9EUYGG2ENf+7i2msQgaHmZJX4b9niOA1wq/+/UM0f/BUfUb1AZFh0aqAC67BaNPJ/5K/Bb92HPtLm1dF5epwvmg1Iarx/plgJlJKXylSKm2HTC96O4rvKlVWyMDronWUJ7oIxjUhMSbSPUnRMQrijP7wME+CMdmRhMYTgSbSzD7TsXsa8wD0o9tVGp6g7qXUJ0PJCGV7lM9W4rpxeBEnqKee26UqgRo0vSz5gr9x/zoMT4+vsZq3924Og+GcL07PeIUroKm09rVWOUHl+kpwGJD5zePyOv42MTHAflnHRiSmz2m8pnjHMA4BPUU3P4o1+C8HZyHc04PdAy39nPzmZqw9P4+R0Aer9FRNs7vGioVuKdYiNI3ip8t+ylVVdukX8FMiYrK65P0XZVXlKrRWBhKtRhzU+8XpYXPtHy7DDoYLnlFfAmU7HMk35rJd/sBd3awwMyYqh6vCSbLGve/zf0+zewXP95gFLyW96jyrVQA8mph93C/TFh54OnBWhgiNITEyu7+u5fWhKJ5O56wXb7tivX7TAQ==
*/