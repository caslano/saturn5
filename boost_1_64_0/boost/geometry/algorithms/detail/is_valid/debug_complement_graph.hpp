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
+5oSttWuTw9SHlvfjQob0xN/eVQe1v6ai4m4sbuxrLfvU5kGNxd06roUjswBjlU3LbTOfCYk/3FvprarIhi2usY82Y/rN79WdvYTXnZ0goJovnPePOYQuRmKNAC3FOVsDPzDS7RgefYYym04mTEl8v13D4fjo5OnPvQ1dKJSzGGzJGiOpeOKCdSgqBI7gsNetA07vO0aWfIeQxdbpFlmFA+NTk4TEW2eE7J872aHOqdXb2wjeaLYpvMLq8icutN+xWq0fniADEekL8E+9Aay/Eih7T6dHQFTxTg0V3H6IHEWVemPWVM5b4TIadF8yWEAwuly9cqjvyJGD1o3zTsAtMZCRORAKZQ0Seciz8QO/wjbJxRpGo7d/5yjoJWzokNDeYCoYZLUxf8bPhEamBpYx/ZU66Qe18coiHX0d5m0B//s8Oe0zjjRKDQ7uI66MpibCO7WWws2GU3CIyCnfGpY6YV2nZoa8GncmhF3USAgqFYtTNkCUi0JDzRnkb/jN/f1Dj2r8xg71sS3PkYcLDLyso419vUFzq2Upqrq23slD+y/D7Z2Ovv4BirvCg==
*/