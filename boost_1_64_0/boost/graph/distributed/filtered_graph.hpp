// Copyright (C) 2004-2008 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Nick Edmonds
//           Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_DISTRIBUTED_FILTERED_GRAPH_HPP
#define BOOST_DISTRIBUTED_FILTERED_GRAPH_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <boost/graph/parallel/process_group.hpp>
#include <boost/graph/filtered_graph.hpp>

namespace boost {
  namespace graph {
          namespace parallel {
      /// Retrieve the process group from a filtered graph
      template<typename Graph, typename EdgePredicate, typename VertexPredicate>
      struct process_group_type<filtered_graph<Graph, EdgePredicate, VertexPredicate> >
        : process_group_type<Graph> { };

      template<typename Graph, typename EdgePredicate, typename VertexPredicate>
      struct process_group_type<const filtered_graph<Graph, EdgePredicate, VertexPredicate> >
        : process_group_type<Graph> { };
    }

  }

  /// Retrieve the process group from a filtered graph
  template<typename Graph, typename EdgePredicate, typename VertexPredicate>
  inline typename graph::parallel::process_group_type<Graph>::type
  process_group(filtered_graph<Graph, EdgePredicate, VertexPredicate> const& g) {
    return process_group(g.m_g);
  }

  /// Forward vertex() to vertex() of the base graph 
  template <typename Graph, typename EdgePredicate, typename VertexPredicate>
  typename graph_traits<Graph>::vertex_descriptor
  vertex(typename graph_traits<Graph>::vertices_size_type i, 
         filtered_graph<Graph, EdgePredicate, VertexPredicate> const& g)
  { return vertex(i, g.m_g); }

}

#endif // BOOST_DISTRIBUTED_FILTERED_GRAPH_HPP

/* filtered_graph.hpp
kfvDdpewC6TM+R7rAj13X8LmV5X8c9d1xvDUlrX+6KJ+1ry9W+KtY1UVv7R5Ur32fs5Unsk8zFFWab7cwbOle8MMFf/DIgLuZy5plRvq15uaKn46Rmgdyk+mZZs6tKrkW4SpF2qKfbWLu+Py5/UeuS6XZcchk8ZNHB0kTEVxz5HrnjA9Pct2PyzXUU7tvBnO0z1L7L1RTP/4OvG7Hb273tZITHUt3xtFbqF5VddqQQ06FC6Em3UP20kpEs9kLt3szWPfQ25futTRyKSu0fIS5f7Q2VvCX+lPd95Uk+6a5wWnO0fsLcR/rt9/pn2dC4KvU++f0UfTdMj7w55DLnGmSJrrIvfuFevdW3ZSDO8qMiTO0y/OzXHRfWgT1d9Sv7/obmH97MLP1CSvnwvC+jmMnxyvn9h5W0L2xVU/dWPpy/TtndshwI/5vqD+Cno/95Oy7jb5MUjsUUFx5mmc7KPbLFw8XSRcxL+NZzXxTPOmP2r+dSF7/6qfPbH+a5x/abhr/MH2syfAj5b90LQdkLTE+vriNY4mcZoW1/wjcZ7oONdVz8d5osLsDaxhRhBmujdMzAJ3nKtU0b2BTfrm4G+j3O+r/+73s6+In422nzfC+XkaP7lJ4udwUT9vYm9lEUd8UR3F4L1V8gh/CZwBC2C+jgMVqBw79MkKOZ6MmamcpZytvATzQoLv+NKA48vMsdl7RZiYYJ+rbIIZjzLmcuTz4Rw4BreV8RjRlzxzXce0GtzbAHvlGrbuY6+qfv3E5ma9mg62zOzT0saWmXVyWtoys65NQ1tm9Bur2rImftk/zzPr6bT1y+pWN7I2ojeNLEf9FUydnJee512apMBKQV45UJ41eSIvyAKCiBv1le3mW45G3ErjdrS6Gas7Yz1L/zcydTMyqZtV19If1tTLIq9rdDC1ntTxqDW+dFnUuWJ/T+05am8t10R/u9rTq/vsY8sFt+W2JVrym41jHeV1hNkl93XezEI+L7Ny5f0ZtAaIttnUXz3zLfSa2Ps5Ojsi8CPvYOwS3B4fFj/NjQ7xCbF3c7S39aSx6zeW6n+/IX4udHR16No4Jp6G9ho86GBnZU/3BhM/g4yfNvIuWexAbn/D5Obm2brfpWrKO8fxlVWt6P5kZt2vjySu9o5mDrfWffodF6Dz3UPieZu9LApMOu8WWTn1gwa92A+ySsr8YseZU6EdP3kXULc2kbClzLdJB7F/SBu3Dn6Qmfhj5L25voyv3rsFE+dqGBdFWSr6LvD7O4CfW73+YmbF8RkWUt/Wxk6VLXXJYrNWlzkWU0Xbjr1+Ysw71TfmLc9qnVrSbtDnV9fdcZh1U+SZuQQ7ZQm7lCWRzUPmiNe1n3T8lnusbU1TFsRvqhkPt58hX95RT6YEPxPtdQG9jjhWgTXhHfhpUst+JibkZEwkGUXLq/leHyd+v9XnxB+2ib9dzrHEoHso+t0pe1oeB4i9qiNc2R5o4mwZUF5R31D3ZDhW3COIw+9egPp+Yba/PJWHg8RPeUcz7m2s3NszN2faR2DfI7v+Iw+Q+fIgWfoIit634HuyVDezq+OilwpWgLdzT/Jq2/dEW5jF1VPqr72pc3aK/e/Ol5wee22tIm1U7ouGq+WrP8Lc74Em/rqmHlwv9q+df3NGh6+fTLjmZo/ASnW99kw5H2OMoXslanvrJQm3w+lvZ111vtQLIX0M0vaFjcTdqXZm44i9b4B/vRda16XUkf4qp4P1MHc4clSOg8g7OlOQNnFGBO2hWBDw3b9X/CVLuL7Y75D0fuysSI/Jq06XhgttN02xw0m9v0XCfeZ8BskxJ+k37TrTRpcy9o74u9VpX88lNPzs+n27uH/ofMXp1ms2fWM=
*/