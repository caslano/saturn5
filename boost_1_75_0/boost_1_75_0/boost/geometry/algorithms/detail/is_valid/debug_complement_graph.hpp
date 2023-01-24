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
yZhiqJRuxbhOfRs3C+VU+YOcPVBb8Mn0jgoF2apHQl/LyBZmfd0GSfjOrE9Di8Ej1CA/KeskBWV0paCMRhvKCFhRRp/7gmvQMWDvt9Ey7DrIz0P2g+cIKYPCD20NK7DygVADRTiKygU7ZjjHmC7Nzh67Q4Lqvx7k9MzfwDP+EU2+KWgQ2FnfoFt17+bqp671uAbIh0SstOAyZYdZKhDygJ6tVPyCqrB7BsZFZDKN9wzUPcLzawXPHY8QOkU/TwhyYSF+54B0gxn1eNbgbdJ9WHRiOV08CrtqnuABamUWbBd2YmpfJO2VBO2VBu2VCu01HmUAThW5RYTn+9oj/H6Ds+AZ8ah230CULHKlYQiHKHXW7fhI6BHvwlKNnCPdKCjZ0o1mVIOhT6Usgd/LDv1Zze2EVqlUp9xH+eDwbGd8u/mNj/J1aRF4lj+qrX385gFLO2DYc4W7zLgI+QXKq79CAlr0DKInwoax+BB82icS2/jgOfmodh+GKcrGsGs1JHeXJGyAwVAD43IewHkoG+rgxvwcwNoXTe3R/e8xfj9DMniyHtPkg0K5RmKDtqDrMGwRleJkjN3i19grPYDFjWgpVkSHRGTL6f0DCtD3I5E1zM7zGh/jd24sAs/yx0j99YavU7ZTlKcaVWJFGPZMcM9jfA48DJ7nIuWrG1K+kG0XpLdV3C7liAuFLlQnKCJMCOf3oE1hjjlgjjkCo5Hj
*/