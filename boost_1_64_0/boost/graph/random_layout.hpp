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
FKzqTlRcl5SlEAB8fBVGRDGdNZiXDuSs62Urpop7toJ72Kaa1A4XHvTni6pF1ZZW425OhML/S9vQaFTxtdx3XkpoKYrA/dS84OFlH8NpBodAP1oYnV3e6aYiK9AARK1pkF/azvmyqBK4kck4PaEj1qc1Q/VR+VVrKVATn4zRTUTVfqoViKlwUCFQR+y2FTjFi9HPhSODzRssX5Xf9N0hm/njdJxIOeuYEn8zrw6I6uz1Fnks/P6fa+hGsfLm5s19rUB1B6enA1cpVcBTTdXdUBvtii2sU9f8bncd4EL/3/ac17cNXV4YPnA5N+jnT08SSEZDVkb9SrU3pkltH23p3F3Tsww0uxmkaiwjC8xYE0Fw1WS8hC6ObwNH4f4Y+NAvRJqobmQqsglLQnqK1gnnCHjbTgnfv7BakVar3K77v79v4TdTDPKy9nPKpQK/4KeC6qsMtxesgtE06RXsvhjEelH52SvjzBFzrZxdMtJpjFNKNt9ILN+Biw5p5o0Jl09GKVk9VHQ6tSHPMKlBP0FjNTCnP6AwfYHhyXvHzPg+P8GXeayZa8Fr8u6xdA==
*/