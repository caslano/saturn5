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
s5K2gO5LgiJInGk6eWGA0b0MIp30NWUAMpVlWH1YzUSRfuACo3zPHtMhM/fX5APcb37uUTL++VPgivL0dmmvE4a4PR5MM/yX+LjlEfWZ2FxE0m+6MpQR2eZfy/k+S5ZMbFdBd9QkdvtEmrNlTAMGt7gkBjAURKEN3fzyZcrV67R7VaZ/4DUvPKQ7pljAdbs38GSVjHKxWLzLB+kLOXnXG6wtD8DwvCS6SnJWU8jUX0J7hoyAIoFdmvwiw9bIwKtDaILtMXeJg08Bg8eLstvzfRRsc18tVzdQDLqxU5Sf+WI+zdIKXAXkZsw5AWoMLI3SsjEiXiiZ17sXSG7kJkUvqX2WxkiOEYjwRRV+52ymH0IzzX2c7L+Di6ujJl0B17NcfZmdel4SIsMGiaUJrrqXzNiIAr1rx7XeKjFIROKUR6SjYTyVDPn1b4UJqv593hNqE0/mqi8IKssopopMKKl1/rNvq21PGzIrTOR4NOHugg81hcZ12xX1cDJUzkEGmhDA6OLhARzIbxtvPGd0Txsshpt/7RnvBV+EmuTQWrOiew8z6TfSHGUivzvS/A==
*/