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
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
*/