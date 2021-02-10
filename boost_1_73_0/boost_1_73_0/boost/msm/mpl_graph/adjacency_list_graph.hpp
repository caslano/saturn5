// Copyright 2008-2010 Gordon Woodhull
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_MPL_GRAPH_ADJACENCY_LIST_GRAPH_HPP_INCLUDED
#define BOOST_MSM_MPL_GRAPH_ADJACENCY_LIST_GRAPH_HPP_INCLUDED

// graph implementation based on an adjacency list
// sequence< pair< source_vertex, sequence< pair<edge, target_vertex> > > >

// adjacency_list_graph labels such a sequence as manipulable by the metafunctions
// in the corresponding implementation header detail/adjacency_list_graph.ipp
// to produce the metadata structures needed by mpl_graph.hpp 

// the public interface
#include <boost/msm/mpl_graph/mpl_graph.hpp>

// the implementation
#include <boost/msm/mpl_graph/detail/adjacency_list_graph.ipp>

namespace boost {
namespace msm {
namespace mpl_graph {
   
template<typename AdjacencyList>
struct adjacency_list_graph {
    typedef detail::adjacency_list_tag representation;
    typedef AdjacencyList data;
};

}
}
}

#endif // BOOST_MSM_MPL_GRAPH_ADJACENCY_LIST_GRAPH_HPP_INCLUDED

/* adjacency_list_graph.hpp
CgAAAAgALWdKUrOiebkkAgAAnwMAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q5NjVVVAUAAbZIJGCNU91u2jAUvreUdzijqgrSQrRuq1jmRo0oqEhQWEkn7aoy8cmwmtiRbaC8T/cKewFebE4I0Em72FWcz+f7Oeck1KKxKTMYESpkptzjGbcbpbmJyHySzMjo9p7Q4ATSYF9HzsgZzFGvUftGcCRUY5lvXYGpwbTgEenHsxgqmcdk2HPUN1c0aOproX4uUNpGKK1fjkoRMYUtj2yHZ8jsSqNLI7gk7zZCfrx09yfYMS3KdUTG/ad4PL5G+fQ477oQfq+C+smP2eAvsBLfM2ipMV1i+hyREnUO/mT0oXcfhmMmf1adX+fN4X1/ejuYDxLwES64QGjdI3IDDGpJyFXKcmyByKCdp+0Drd3Q2p1OB6RjrWzm91qdrxcuxMkbqGQF7ncAG2GXxzGCWZWl0hb8xmjh1sfBoOSoHS/YE6mxXMiIDLUqQuAiy1C7qXokUSEwqewStUc8slB861X978tpqoqCSb4fehgE53fTeTKaheeV/2z6kARfrj6D7xdM5L5OSwsusyirjd3gCyvKHLtO41CROXuI12b3KjlzAW52v3avu99dg+C70Tnjo6E7
*/