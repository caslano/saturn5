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
sdShWcC15oDaGdSV+LMCf8u24mi4Xwfi+CKQdQkypJxugQvsBPeaATqP/ycpZ1BgILYzZfkG8EgZRYF4vvHbWmX7xu/PUX3Je3qgtF+DoI57O+V+8QTYGbrGxy/cQ7cdh+jyR35GHrQcteT4l/tmWT4Otnxh+qap32ci68n7JedX10/9EAwcI2VLf9I8O/ytrSE+ly8CPVfiwbAfjkzXeR7yHvBuouxo3wiOX4T98kz9TL7Sz+UczWdsJ6ROmTpuRdK1tm4k3QqrrHXmK8ONUv5pVrQ/BHlOXGUctkfgv6DPMfovIF3MWgKfqt2C49PA8WGwn9BL7SMuUn6m8Z/DLwgHCAfFp0Hs/peSLhwOqbyfrk1wmP0jwV9eq51AepefBD0v+xq3RHmU8A3hW8KfCPeacuL7T/guKCHaj4Lk/V7Dnwk/BH+9f4TBXzr2HD/tc9tufLfPbbtxZJ/bduPAPrftxt59btuNnfvcthtb97ltN97b57bdeHmf23Zj2T637cYjjsxcx7373LYbA42spRxn74+13WjAcbTtxtR9f79vha2/0rdCGvL1jlzStY1jr+H4UtDxBNkwI5PnuZTPhUv+IVuN/zefC43EJiPp3JITL3zn82ZtrzjrB++87Uf//2wyyn0uuH0uXKY+Fy6HleEUmAWvhDnwKlgHXg0bwKmwCZwGT4PTYUc4Aw6G18Kr4Ex4DbwOfgX3+/RvlMjfRuzczb7MW1dfCzVhO1gLdoEN4AXwEtgdTocF8EG1FXkV9oJbYG+4Aw5UG5HBcB8cojYiQ+FXcDj8AY6AP8JRMF1tRnSNBGMzkhW1RsJ4WANOgnXUdqSe2o40VNuRk9R25BTHF4PYjjSH02BLtR05C86A58CZsB3sDvvCvnAIHEu7DYeXQII1Dl4Gx8NpcAK8AU6Ci9VXwxPwd3AZvBFuhHPgJ/B2eADOhT/DO6FPbUcy4QJYQ21HToSPwLPhYtgNLoGD4ONwBHwCXg+fhrfAZfAO+CxcCp+HH6iNyEfwVXgAvga/ga/DH+EbMCnKZuQFmAlfhDXgS7AhXAFPUduRZmo7cgFcAwerDclVcBOcCTfDG2EF2ucBmAYXwwz4JAzCF2AV+AbMhFtgNtwFj4PfwOrwe5gDK9JXa8BK8HjYANaEjeEJsA2sBdvD2rAfrAMHwLrwUngivALWV1uQBnAubAgfg43gy7AJXA9PhZt0zYV9cBs8DD+GP6jtiu0PH1eDn8AGcC88Ge6DeXA/7Aw/g93hAdgXHoTF8Es4Bh6Cl8PD8Gr4DbwW/hneD/8CV8Af4Sb4E9wCLV173gsPQx/8E0yAf4HNYALvtNNhGjwDZsEzYWN4FjwTng07wzxYBFvDy2EbOBe2hQthR/gCPB+uhZ3hh7AQfgZ7QK+uQR+EfeGJsB88FRbB1rA/7AAHwM5wIBwEB8OxsBhOgkPgtXAYvBEOh3PhCHgvHAUXwkkw9VesjT74ba81hTCb0Gqc4+Pi3rfLbXr+12x6yn1cHLtdT7mPi/9+254VjGXr3y637ynfyrfyrXz7T9z+ufP/h46f8Bv5/r/ApftH5tb9I4vV/aepzCOyNiaNz9GvG5mj21eZ0e0XdGzfhb8RVRZwzYVHbnT7PfO7d2zXx8jNXH2c/It9gSNPLWU3kK3yClHyoo6du3WKqk+aXltvpxyds8/s/rzunNdJmy7ytvmte7Q3aStHrgdE1RFK2o7t8wtUnoi8bBuD1UHL6LtbVbFkm5PM375K9N388R/Wd9MD4vu51zm8o3aIb/KA6r8178nEh/2uPynHK40uaLikb2F0SlU+Dh3fYEt69gZKfEDTM2v2Q9HxavrI8U1uvwDUJ4vyJko=
*/