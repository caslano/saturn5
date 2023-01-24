//=======================================================================
// Copyright 2009 Trustees of Indiana University
// Author: Jeremiah Willcock
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_GRAPH_LOOKUP_EDGE_HPP
#define BOOST_GRAPH_LOOKUP_EDGE_HPP

#include <utility>
#include <boost/config.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/graph/graph_traits.hpp>

// lookup_edge: a function that acts like edge() but falls back to out_edges()
// and a search when edge() is not provided.

namespace boost
{

template < typename Graph >
std::pair< typename boost::graph_traits< Graph >::edge_descriptor, bool >
lookup_edge(typename boost::graph_traits< Graph >::vertex_descriptor src,
    typename boost::graph_traits< Graph >::vertex_descriptor tgt,
    const Graph& g,
    typename boost::enable_if< is_adjacency_matrix< Graph >, int >::type = 0)
{
    return edge(src, tgt, g);
}

template < typename Graph >
std::pair< typename boost::graph_traits< Graph >::edge_descriptor, bool >
lookup_edge(typename boost::graph_traits< Graph >::vertex_descriptor src,
    typename boost::graph_traits< Graph >::vertex_descriptor tgt,
    const Graph& g,
    typename boost::disable_if< is_adjacency_matrix< Graph >, int >::type = 0)
{
    typedef typename boost::graph_traits< Graph >::out_edge_iterator it;
    typedef typename boost::graph_traits< Graph >::edge_descriptor edesc;
    std::pair< it, it > oe = out_edges(src, g);
    for (; oe.first != oe.second; ++oe.first)
    {
        edesc e = *oe.first;
        if (target(e, g) == tgt)
            return std::make_pair(e, true);
    }
    return std::make_pair(edesc(), false);
}

}

#endif // BOOST_GRAPH_LOOKUP_EDGE_HPP

/* lookup_edge.hpp
Geq7NJL+U4r7kLQ2zWC6Q7FjUpIN84+WArzv45N2OEdfXDGd2KFWRL4dL0zQd1+YNDta2lWs4L3+uTsTmTZdpzbuX1FiayL0+EMelML0U4KMRRzPUCzfHw5bJvwk7lucrdXg+STyBBooHfMh9i+4Jkr2YGOR3SoS/XbNdYjHeGHqr3CtVJ411p2pxHxhuKGwBT41ud46YGa+sCbg9pJwoU15Uub1KnAJHxPJk8nqWfaKGetOGME+oQRfhlh+N/aPSj6QBvZRilJ9ZE/QEvi2tX7pk9ULUhnaE7gNYzAEzp7Oyjz1q9IM5JQt251TvoNEiCXnb99WmtCo0yBCXZsvJeEayfHb5GeX+O/6VS5VVuwIKRgkyWuqvesLiK7vfieyfB0XN/w9vQlUDYqVcTG2ESFUX/fKXJseXLgZ4P6d2TIY0o2tpyvxyLH37BTgiROHmh6Ga6PtwXYBjA9EGgjm5KiTPaDiRlDfbvgK6C6D6zXfbgPLH1cRfzEQI20+eIDeXLS5uupGn34nryGBV/E+uLd8bPtkg/HdNOLlSjG2qUuxSzFnZR5aJrEf+kkayS5mn0hEk0IM2cygph2Nbf85H+VsH9mhR0Tad16Km8gH+o7vPlu4S2SucaIsN2GQE8uZRIDZzXj/baj4Xz5GRLjCPzOSEBCchAtR8RFiYqSdWr57kfq4/5XYFOS+20Gy4igGhqXANvYrjO6zISzn
*/