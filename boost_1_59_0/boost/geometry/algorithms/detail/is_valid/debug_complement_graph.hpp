// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, 2018, 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_DEBUG_COMPLEMENT_GRAPH_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_DEBUG_COMPLEMENT_GRAPH_HPP

#ifdef BOOST_GEOMETRY_TEST_DEBUG
#include <iostream>
#endif

#include <boost/geometry/algorithms/detail/is_valid/complement_graph.hpp>

namespace boost { namespace geometry
{

namespace detail { namespace is_valid
{


#ifdef BOOST_GEOMETRY_TEST_DEBUG
template <typename OutputStream, typename TurnPoint, typename CSTag>
inline void
debug_print_complement_graph(OutputStream& os,
                             complement_graph<TurnPoint, CSTag> const& graph)
{
    typedef typename complement_graph<TurnPoint>::vertex_handle vertex_handle;

    os << "num rings: " << graph.m_num_rings << std::endl;
    os << "vertex ids: {";
    for (vertex_handle it = graph.m_vertices.begin();
         it != graph.m_vertices.end(); ++it)
    {
        os << " " << it->id();
    }
    os << " }" << std::endl;        

    for (vertex_handle it = graph.m_vertices.begin();
         it != graph.m_vertices.end(); ++it)
    {
        os << "neighbors of " << it->id() << ": {";
        for (typename complement_graph
                 <
                     TurnPoint
                 >::neighbor_container::const_iterator
                 nit = graph.m_neighbors[it->id()].begin();
             nit != graph.m_neighbors[it->id()].end(); ++nit)
        {
            os << " " << (*nit)->id();
        }
        os << "}" << std::endl;        
    }
}
#else
template <typename OutputStream, typename TurnPoint, typename CSTag>
inline void debug_print_complement_graph(OutputStream&,
                                         complement_graph<TurnPoint, CSTag> const&)
{
}
#endif


}} // namespace detail::is_valid

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_COMPLEMENT_GRAPH_HPP

/* debug_complement_graph.hpp
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
*/