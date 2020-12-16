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
ak9Q2e5qRldt1bTV3JXOCdAhc1mStCyuuLXpIiuW8Mhyyfc0IZyFQ7QwmuICwttdeFLGhxsB8sTQjn4wdsKsEa6iUGjEvbONFD+33JldD4EHEGh2ACzUIv+kQHYR0oYQN2oBwDYCGgEQXpd7Nirn+Yo6VZhGc0QyoMKIqiq3qtVX1xtYVtbSY5z2GKb4e9htvnuVbcOVfK2q0R3ARb8H1aqmNvPn6dx4JeCWhWZLC/Udq68k7MVk3aOmPtSIk5A2f3MkZPIh7O7oQi2i9FkR5dDQwmtEOAp8uvwN3kNbSY/JFZjHr1WTRgabw66119DVkFqsBbdZJc+6kmELKko5r7OAawrtOEyI6/MCugOjNTP0QYOPgWVPPCx7msKyJ0EseyrTj+c/morRr2V8rlTMTBYq0lsAp6Q+GJyHYTEHhxDGUeOUGXcNgq3TxGmYZQchMWINuTFi09uWO3btKmw4uD2qtcZqAjFaIpABLzImlqtjnbpc/b68ha7hLHi/Q1NlRxtZADfXOysshEfzXY8E5nWiF8EUXZqbiA+kGY/g7HgCUm/Ss4TJdjnVi85zKKdVjw+w3B50OxU+vrUtMbXaakEdTtv496+bFXSEQoRymfi1JamvdfS5RA1BSvGTdS0DBnUS2bky0n8pejfkxN8unVR+OAQqc+jRrHts+Rl/tZCPmhoklKYN22QVmPYoIIiqHy3aqvSgtLb0cAJ+/mo1N+a+QokmqkJWQQ+zzlXiHOgytbZoSH9VemNw1POQqAdbKG2HX8PmIDZ4h54DvEVLdsXKQIeuXqcCxKVCMb7S6bka2V/cXoT2oZbdk9lRVwuL4BFKTXjYgoP02HI3DIagCTs6sy7T9VTP1NPq/ic9DEe0azwdo7IPo0fIx+3TEt5VQmvj6HO4aEonR/ZR+gWCc6BjzeEuyLUm1Ay16RiVVf+ieDJr746kcMqizJw6QMzC6J4DehM6rRN3U+YmCB1TOiZlNcaaw5RON2QxFabxZ8iFm+v1fMhfJXom8++tdRtmpzkUEekaU1tw6pO2fU9H2yh+MJCtU0t5s6UnWI9kzAPNkUYDOe6ExFWComfDSqLwHXVFedc2zSwuQTeYX5NfENI+dpKhFlrclan6r7q/i/dbZ6BnL1zi4vpHh8iMb8tMa8aXvyCK8n+sOO39K9VpZ9qXutroN6EoTnsDBVMAx890/BjH8LJfWkwQb6a8/Yw3tcA+gze0QEbOxOsujViiP6UaMACvSxQCaSOkFK+FCklwyk9TDSjD6wKNNQqvixSnSH8cilqm4eMD/ikBf+uAv23AnxDwXxfwtw/4fwz45wX8cNKxMeCPD/ibBvwpAf+sgH9XwL8o4O8S8I8J+GMD/jkBP3x0FAb8dQP+VwL+/QH/goB/S8DfJ+DPCPjzAv6SgH8HspINXf+MgD9xun868sRHo4C/WXFaRxKsOK1Ifw7qzxL+mD3AaxBZVKosJjUWDqu98kZqeC5+j5zmohkkd7jarZVVVrPVl1iKKJjolIPiNawVqEmduQLVzT3tiRhayyTtwTrUxj0Re5kxK2QVGAeVi1aU16RHDACCPYFq9sUbikHSmZvWYa1okdndxj6o2B8R+1JiX20HLRHlZb7IoPJozn/soC816EkG/cKgY59FgjpqgpkM2signZ9J9g5Zf18H6FUYSktnF0iblwovrmk/mjcTXg9wb6chmdkNzN+aycHlTCHbjSzWLMkAkmWUmD8gNDiaaT8hUIyS69/J5N43g6BgcD1XrodpttLjfEvoYkLTFbqA0C8IfYnQJIGmlZnvEvQ0QQkAYZkcuGViIfUAfNdN/Ddn5wIXVVbH8eG5iCisoZFrNuv6YE2JRTM=
*/