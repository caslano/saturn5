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
POQuTfPPh3/Blu85zI32X50MKnse4CbMKqDjOe4UiTs8CSewNaOnCUzQHv2IsaUICVsWTb6CgpyaG/H2klD9tfHFDHeC8tzPcv04lGXgaxepMKkMswsQpg4hF+z4OY/lRYMzzN9e9X/sDj36fvX2rTesjI41lJ62lwnHStv53Gu9ubXSTaEk4ypPK+/yaGtBXhnmbTBPjeOKw26VanNuOuZW83LRWmTJQvL+YQqayYWGY4ljKTkRIs+sXgYAbEA7ArQM5ZiSw/2sI659cGEz5CospDGlMujl5kah9BMTc1Kw0k7gZn1UheBANKzJaPe1SLZJk4Xz6BcUJxTYVmkUlEADnQLs5c3WW9yABI2ikr9DmWHeOtotSuo9JHfdR9VVsQ9A/X31VdUabA/DDe4uk25jIL4OijMC+gqxuB052nCLsBqybwjat4btzwLuG0P3LcB7tgq/P8OXfVqnYqr8HdDh6L8rNb7PahxPvGrW0poI1XWF8PmYBYCEsTcwUOp83Kq01QKGeCoFWMPzFGTRD5XvfAsgkiILPgZDR5KOR2BQtcrTWb8wq5z6deaEWysFW0rRHSxHBpY1ftGY/m6m2IAhrPJ2Vm19LArgiKibiyME6xxB3r0AsDwJPjcbHz9+pB1VlUoijxtKRxQ3
*/