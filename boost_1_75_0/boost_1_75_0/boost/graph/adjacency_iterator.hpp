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
4DKLD3t+Mg+dK1WtQvzdZdLcZXlt0YELGbdMrA6p3tzaZXZs2iSkVxL9+LR/pgheIl9960NwVlDwEgIJKJwu4RakhcRK2IpsJfFTtdj+NlkluuU6e+CggyWb6LkA5RzgHTFDm2AejAffULTHXTNSpLClaFhy01in4snYxcmjjGRrGSFBjfe1surEUD5H1ub3B7q1OIaiSgSjNvaqF8ZGmX3RAsA0ymNI5Cn+cq/Axlc7NHmdTWq53mMVkwtZV02YXMPbL8tljyrv4s4I6zkzCsUBmaYb/vPosJjk3uw+f8kOBLe4ulI3AdYrouD+o5f6EdUaG8U/mdrrGrFRy9xPWbUwmO1v8glSy1xoOAdhuGLnT1mef0gBYcTcSRZX+sD4mDvP7LvGi+hHCg+p8B164nTaM0jVjxzs24SqCQdl3QRmuNVr3wGIhI2ND+uVbeuVr1nZnW9k8xjmQUFzSKBVvxEi7yBlJWAAJ1SKB2dHk8z21/b92xvH2AvVpw8QV/Ck2ECv4vmpm2FUl00lXvRDTC5qNixuY5qZg10v/It5WWnRwEr+9BXEY+Mf0xfAAet5Zax1/dAfmDwqir7z0lkbmr9xaF4PufUCqoBLuy53PkvMT/Qdmm6XjwZ3hunPtQX+8JIR4SDJ2/QL2VCHM4VDttOeYvPOg6suTwAq5jBWSVQ37i8DXSe36VKU6SlMT0N1GzAxiUEt079XWRzC
*/