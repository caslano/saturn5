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
8gRNgg7fwg+oYd95Yroz5viLznkYVmMXvo6a3ff8b5kvCCdcQosw/dXh92/khPdDMoYy7kZCzttYauRsAAIISqTAdH9EI/XGvpz10r6pn4WFCuomOntu8lgqxmOWxlVKw/WPCp4uG0l/ib3zPOwyKNnRuvz7tn3qkzAiXusHR49xZvgkahp8UsHVEQOUwDR6OZw4Wwo5RAWsA+SNNWl51/b4/r4kmv2RH3xhs/8NA1nu4k/WoBNI+PYrqkTjSUb29RX6kUnF77sB4HSqHNoCzT6TGilxlATDqQaJWYJyZD/ed4Ox2ePbVQDwyqRuGlyksuGgVFzvs1DLcjNNpEnQ/x0M+FaT2EUi1fAbGMcdX3EDD6dD80np5hGTcw+Z4owIGq1n8i3JqiMmXC9QOTelZyf/RqxRPe3/O6CgW+3UpE2t1SCLgsKIIQZdOPdiv2WJqaivD8McbOVx0HiZh7uZVDbON+BXy3d+zABVp9DUXA9XYapr/dh1ft+cOPWk2CqHsImY9TaeRMPFZp5MqxQnZpkSgTK1qa1O5KxINt/80/xrLKPMQTYeEaoDFw==
*/