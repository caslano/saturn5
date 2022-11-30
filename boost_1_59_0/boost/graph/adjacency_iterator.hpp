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

#include <iterator>
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
        typename std::iterator_traits< OutEdgeIter >::difference_type
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
        typename std::iterator_traits< InEdgeIter >::difference_type
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