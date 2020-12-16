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
Fkn6DCtTjl1jX2wf1r4wcU/Yx1cQK6OWHsbAiujDiUhNmT4t2eortsQrqZ/atZK2ZMI4c8843iH3jL7UJSNSxkmUcW+ojKTpQyNlvEwZ0WlKnPN0/jXnWbPdfZ7bnfM0LX2eGppmNWnuD6XxXvu7VH9CqvekVL8/VC7pPfDKdILmydQ8h8nzQChP8rXzU70ZVqTsq0uVXSc9UvbMP0vZJ/9y2Z3SI2Vfl57qDbrKNu3D8Xy5thm5kTSvlUpzu5OmQek0Q+y+YiP6jtqTvQuNvV3c4LbFu8TIY/0XrdOynHWFHFu0PwaRwTXKtXAd4X6Nb6N2fO+pLd9bHLOPjHj2e8GbovwgrSdvPtwQJKgt3YXK95BtJCyJkr3P8SbNc53KCZJmM/IthK3aLo9Ezkt4PCOc5gMtbxvcTthBWE/cWoLKhXMi9vH2L9vXLd3j2Ndl7ojYlzUz9msfbzcyY0v3pJE1NfZw8x2ZsYe7xZGZ8q5zZMYe7ipHZuzhJjoyY9c3ypGZugwyslxj13e+IzN2fRUdmamz7chMnQ9vMzJT5+2OzNR5jSMzdX7VkTlrJjkyU+eF29y2iHc7MlPnOY6shbm2HW5bRL6zRRZ6k2MLKLaBjLExtoGNt7ttA/vbbtvAYbbbr9NUY99n/h4R+Xd/w6/THinD+Y7Czk++a/jOQT5a0l2PnHczx9HfIBnyfuxVTeQIwzKgaUuQxU/H+05lE5BJfeTdVkHro+888RF1nLyXeO9VCR/n7InxGWV8Ws7LtmR7zMNzpRzHOdI/ke8APmaHlFjmuw+Z/t2g34earo7znSTH13mWWwGztpttvkn5bcrkaWp+S2ojx5M9t1mh1d3OVLltbRZ5XTsDSxKvsZOX8qRO2fobx6mS7gbPfVZdbLjaWlmeTjpfJ3KuE8zvaGvluHLU73r8TqF1G27SN5HrGcNxKzm+wrOM/4MmD38XhZsBWX5GV9LVtyJ57Rj/iXukvtJRTNomsWmlTzltxX0cPkbaoAtp75F0NT1Nubbn7LamjJalyuAanPo5v1GY9K1KpZ9s/g5GFv29pPfIK3ZvT/JlM82U0aFUGVOjyzDfUsi07atLGffR2qNNGd1iy5DnJM2UIX+Mm7S9S6WdU+o3glr6PdVB0rTm18ZKsvrkTNpqBf3vU6urWcty06ehNM+Sf4F+k2tf4K/RRCzgxL+mkb1lV+a3hoCdzC9EPfmrJknqWNvY4Dt/218u5VblmUqXOtYkzvlWdf72qA+flrJXMWPsXFea7HAaPf9Bfic6g5qlcgeqYTfYl28ZeW8SnHfuEsKHwdh37c6gEz+LsDjdid+gjAn6Pm0S317dzCez09UOWmUdIH0WGc+3yrqZdDyjKuttxlh51tRvXkQW9SyZ8VXHY5WVmPPos6Fjppapfd2M567xUMdjlUf1U+RzjFz7HrKayGpL2RSs6eqbsZf7FUfm2HfHsxf+7eyCj9V+vGw78WO3By/TXvjvsFP2iH3354+lv/BtvzObXLjoqgW9zlmQG8++O5698G9n3/1b2bmXbQ9+7Pbvx+r77ljtvn8r++44dvdx7b6/FR97ssnfcf3hnYQHovbvjdqfH7V/X9T+V/KDruq5VIdX06b+7B/1h8vvHGWXXRf2gbnw4qg18J6G/eHLcCDcBAep/fVgmK721VVgCcyG4+DxcDysAyfCxnASzFU76zPhZbCV2ll3gFNgZ7Wz7gmvhhfCaXAQnA5Hqr11CbwWToYz4RR4HZwGZ8Eb1H76Zjhb7aiHwTfgcPgunAN3wlvgHngb3BdlV30HPAzvhN/Au+D38G74E7wXejy0OwzAB2AqnG85a+AdBx+CNeHDsAFcBE+Gi2E=
*/