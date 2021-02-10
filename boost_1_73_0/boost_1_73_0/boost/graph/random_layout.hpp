// Copyright 2004 The Trustees of Indiana University.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_RANDOM_LAYOUT_HPP
#define BOOST_GRAPH_RANDOM_LAYOUT_HPP

#include <boost/graph/graph_traits.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_01.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/mpl/if.hpp>
#include <boost/graph/iteration_macros.hpp>

namespace boost
{

template < typename Topology, typename Graph, typename PositionMap >
void random_graph_layout(
    const Graph& g, PositionMap position_map, const Topology& topology)
{
    BGL_FORALL_VERTICES_T(v, g, Graph)
    {
        put(position_map, v, topology.random_point());
    }
}

} // end namespace boost

#endif // BOOST_GRAPH_RANDOM_LAYOUT_HPP

/* random_layout.hpp
BYiMCzudt9/9Rbm4qWeNj62bpuW1Br1+9xd44TXk8xXA7Xd/8bPmTVMoRus2RM3wCLnyJmsyiaUfBewi7Oh5eBPD7uXTTlFpQT/ZpR6kggx2FfAUepLjNrP1RHidA4sepmmQ3CgPORQU0Dcc4Ect4KK4ggJt6wsoHjWC1nlr3Jo0Db0KOuei1x960cD8YfWajXEzX4lJy3sC/y8s5tpGYV/sNrVPlfug41PcXm1c+j7J/UF/yr950+gjuvjDesLGnM/CuQ6M0FLKUiCKH+yaQ7t0HS2++0sFkAqqBCTtYHjUfttRi2Jr3gCTJtlqacGbeInm6PQSiBW9VtNweQQpp8EyX0HCSaoKAMlqhip3Td+2Hu0TYWNBMA2zPejpZxbSUMOQlx3+omkKr8OH6MSaXnEgBRyKaHpD642jBUE6QMMCkGhdS1dbDt1IEtWKy5VWy+Y9on9fej1S/mJRpG7JOP8OWBqdMUU7BPr4TFhOPEMETcJ5nIVIfV4WdxU6gjeSQyBXAXpT013L+jzgMbToCw6waQyZUcZLr7ij+0ed/bekODsbdIw6CPovvSdCDQV7rqYjNxa3Vo72kdcGZuqcCBDs8DS6QM4qXmWIjq4vMQ4oFuI44rBFyJCAJhrkuC7DBINmZFvvzAqTGJBf
*/