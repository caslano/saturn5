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
xHgRcyuAHiAZYDFAJcB9AA8DPAGwDeBdgP0ApwC6AfoBxkwQMdEALEAiwEKAcoCHAZ4FeA3gXYAWgDYAD0A/wBhomygAJUA8QDaADeDtSSKmAWALwHqAaoBsAD3AbQDjAUIADgKcAGgH6AEYAJBGAt1IoX5F0M42gJUA6wCeA3gVYAfA+wAHAb4FGAAIh7aeAZAIkAaQC1AMYAd4AODfAfYA4GXjJQALAeYBGAFuA4gEuAvopAHEAnAAUwEiAWTIA+p1HuBbgFMARwD2AmwH2AywAWA3wKO07GD71cHaHN/qrRsOIAN4GgCvtsZ0G+TrhvJ8cZPoN3n4TR6GyENuECxSZpVX1VjvtK5gHsFQerW1EgJxzIaAUA7zFIbmOqy2FdkF5Q5rQm0cwzx9dVwOwyzDuIRKRwVgYablV4RzmBW+MEGJY+67IpzDrMVwWpW9tHjFrJKCyqVYMJLErAsoD1J2XRHOYR4bLA0uz0gVmI1Xx0EJN11Zasj1zJUxkCcuPjsuYzbPkcUiUyEm68XyqsJ7rEXx1kKbtcJaaWeYewPjZ1cOxlshvtReWlBeep91FiwGSwsLyjOthbh0ZG4RxVvLrfYh8bGiBKR1dTRzhJllsxbYrbiSjGP+IU6xFiwbgsw8ypBOTC6oLIIF57lgsgQli8/IkPIau63cWgn1TBUnWwuq48qhwMy7QUlWe4atqtBaU4OxDLMSY4QF
*/