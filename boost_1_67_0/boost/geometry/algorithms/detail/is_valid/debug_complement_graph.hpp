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