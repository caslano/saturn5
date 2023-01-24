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
RheZ3OlQ7Ocjhq3hj5IAqiHJ4M2p8w9HCzUqxJvViQVcAxHtplcYxJqtvs/PUCAL37a/kICp/rV9q+TGXG3R3fIVtzG3vmJcUyL3jGXs7Ds3TP1vQosI7x5SvNYYp327SLwwA77x9w3Lca8iK9l/uS2eCzwOPpjfqUr3lwTkDwDnvgR8CPL/eiyFyXGk1qQhO/js+fFjId39cQhdhagI4qEZ7kbQrNKcSQcWVOObJQoQwvimQnuVYYcPGbp3C+p2Glr9MVPjTrShSN+R/OaIhf+dwXmfbiPGWeWh8JNZk3rDL6sjpSPekqMp83N43++kP0Sknk34ceXq0/JD/m4TSMMt726RUiaLWWcpb8snFmbMbkOrfWZfasVElL621hlb+BF2gpaOdOYvy/mOsgue0vhc2xt04lUg3FD0Jo1FfdNdZtU3LeM3yy6SqwedbxQQu9++CDyRBpDlwOA743vpXnD+VvE3qweUks32TCcc4j5pPfHMc04nsBGuX9v6TxZrldiLFObPTvXuoEFzXnNfQ16TDYuWbrYreIyT32hb0KzWwuUTfbrrvgVP3zE/TtefDU3pRFSLpaXsle9Zc9eQNFIkbWtX0uOIUVHJvWd1QTm4yecSW2lCOPuY7rIuTh8/fgpJ1BuKlx5n0ZupWU+iz57lEiPOLvQoDYcQ5PCxjEvYcdETZAux3bUpD/maDYWXK1ghX/mvFij6qK7E
*/