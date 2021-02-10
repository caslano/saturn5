//=======================================================================
// Copyright 2002 Indiana University.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_ADJACENCY_ITERATOR_HPP
#define BOOST_ADJACENCY_ITERATOR_HPP

#include <boost/detail/iterator.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/graph/graph_traits.hpp>

namespace boost
{

template < class Graph, class Vertex, class OutEdgeIter, class Difference >
struct adjacency_iterator
: iterator_adaptor<
      adjacency_iterator< Graph, Vertex, OutEdgeIter, Difference >, OutEdgeIter,
      Vertex, use_default, Vertex, Difference >
{
    typedef iterator_adaptor<
        adjacency_iterator< Graph, Vertex, OutEdgeIter, Difference >,
        OutEdgeIter, Vertex, use_default, Vertex, Difference >
        super_t;

    inline adjacency_iterator() {}
    inline adjacency_iterator(OutEdgeIter const& i, const Graph* g)
    : super_t(i), m_g(g)
    {
    }

    inline Vertex dereference() const { return target(*this->base(), *m_g); }

    const Graph* m_g;
};

template < class Graph,
    class Vertex = typename graph_traits< Graph >::vertex_descriptor,
    class OutEdgeIter = typename graph_traits< Graph >::out_edge_iterator >
class adjacency_iterator_generator
{
    typedef
        typename boost::detail::iterator_traits< OutEdgeIter >::difference_type
            difference_type;

public:
    typedef adjacency_iterator< Graph, Vertex, OutEdgeIter, difference_type >
        type;
};

template < class Graph, class Vertex, class InEdgeIter, class Difference >
struct inv_adjacency_iterator
: iterator_adaptor<
      inv_adjacency_iterator< Graph, Vertex, InEdgeIter, Difference >,
      InEdgeIter, Vertex, use_default, Vertex, Difference >
{
    typedef iterator_adaptor<
        inv_adjacency_iterator< Graph, Vertex, InEdgeIter, Difference >,
        InEdgeIter, Vertex, use_default, Vertex, Difference >
        super_t;

    inline inv_adjacency_iterator() {}
    inline inv_adjacency_iterator(InEdgeIter const& i, const Graph* g)
    : super_t(i), m_g(g)
    {
    }

    inline Vertex dereference() const { return source(*this->base(), *m_g); }

    const Graph* m_g;
};

template < class Graph,
    class Vertex = typename graph_traits< Graph >::vertex_descriptor,
    class InEdgeIter = typename graph_traits< Graph >::in_edge_iterator >
class inv_adjacency_iterator_generator
{
    typedef
        typename boost::detail::iterator_traits< InEdgeIter >::difference_type
            difference_type;

public:
    typedef inv_adjacency_iterator< Graph, Vertex, InEdgeIter, difference_type >
        type;
};

} // namespace boost

#endif // BOOST_DETAIL_ADJACENCY_ITERATOR_HPP

/* adjacency_iterator.hpp
VfdcbdQly8U8rD/vdfvrSD+710vLFMiP7ivgXyH+/hn9OAldatq70Dxd+kIzOkX/pJiJa9pAYglra1wqbW5llKw2LCLY16LiRblPFWY7IM0DfsBNtdGj9q0eYZpHb0HlBg75Qb2tLolGVOGSHefRDPvyRZWtWJ0keQWrnfKkXh8p+6Rcs/alcmpSDdqh+1LbWmV7r0iUvPfp6ze7zWqRUEXw5vl6rv9ty1Rk52jzeLJbCU11VqprKyi/UIuXmUhHu/V5SSIdPV8iRexdUbRfTA1EidJ6W7C03v5qpVV9Zu+B8FE88gA+hvYoFvWsPFj1YktIj1qvQtkx6qA4ODo43C03uN65piSgQcWric3NrTIM9sC9JQOHewtQk1kpBbSPirOodCP3W8Hw3j1nfMsHuAoH53t4y0u5nIZJv4OD+pf4pR18PW7s0EAt0M0+K9tCpQqPXu5EzbPy0045EGsTveD5VfcLynRXpWFG00dp4IYyJPmrii0K7LUvCGkvl6H5I5gd/xdbFAVzWFAzDJi8V5rplWKRPF5SV45m63Fgnh8WnzCgylBEKpXou7U6hfuZOGa7djQ6LPVsszcamwR/lxtLqZ8w5ECzHgb14fITh12AWfjqi4jdgDlrQZIiONmJzsfkeJESK1JZCpeY
*/