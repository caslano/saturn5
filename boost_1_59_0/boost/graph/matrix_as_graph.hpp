//
//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//
#ifndef BOOST_GRAPH_MATRIX2GRAPH_HPP
#define BOOST_GRAPH_MATRIX2GRAPH_HPP

#include <utility>
#include <cstddef>
#include <iterator>
#include <boost/config.hpp>
#include <boost/operators.hpp>
#include <boost/pending/detail/int_iterator.hpp>
#include <boost/graph/graph_traits.hpp>

namespace boost
{

template < class Iter, class Vertex > class matrix_adj_iterator;

template < class Iter, class Vertex > class matrix_incidence_iterator;

}

#define BOOST_GRAPH_ADAPT_MATRIX_TO_GRAPH(Matrix)                             \
    namespace boost                                                           \
    {                                                                         \
        template <> struct graph_traits< Matrix >                             \
        {                                                                     \
            typedef Matrix::OneD::const_iterator Iter;                        \
            typedef Matrix::size_type V;                                      \
            typedef V vertex_descriptor;                                      \
            typedef Iter E;                                                   \
            typedef E edge_descriptor;                                        \
            typedef boost::matrix_incidence_iterator< Iter, V >               \
                out_edge_iterator;                                            \
            typedef boost::matrix_adj_iterator< Iter, V > adjacency_iterator; \
            typedef Matrix::size_type size_type;                              \
            typedef boost::int_iterator< size_type > vertex_iterator;         \
                                                                              \
            friend std::pair< vertex_iterator, vertex_iterator > vertices(    \
                const Matrix& g)                                              \
            {                                                                 \
                typedef vertex_iterator VIter;                                \
                return std::make_pair(VIter(0), VIter(g.nrows()));            \
            }                                                                 \
                                                                              \
            friend std::pair< out_edge_iterator, out_edge_iterator >          \
            out_edges(V v, const Matrix& g)                                   \
            {                                                                 \
                typedef out_edge_iterator IncIter;                            \
                return std::make_pair(                                        \
                    IncIter(g[v].begin()), IncIter(g[v].end()));              \
            }                                                                 \
            friend std::pair< adjacency_iterator, adjacency_iterator >        \
            adjacent_vertices(V v, const Matrix& g)                           \
            {                                                                 \
                typedef adjacency_iterator AdjIter;                           \
                return std::make_pair(                                        \
                    AdjIter(g[v].begin()), AdjIter(g[v].end()));              \
            }                                                                 \
            friend vertex_descriptor source(E e, const Matrix& g)             \
            {                                                                 \
                return e.row();                                               \
            }                                                                 \
            friend vertex_descriptor target(E e, const Matrix& g)             \
            {                                                                 \
                return e.column();                                            \
            }                                                                 \
            friend size_type num_vertices(const Matrix& g)                    \
            {                                                                 \
                return g.nrows();                                             \
            }                                                                 \
            friend size_type num_edges(const Matrix& g) { return g.nnz(); }   \
            friend size_type out_degree(V i, const Matrix& g)                 \
            {                                                                 \
                return g[i].nnz();                                            \
            }                                                                 \
        };                                                                    \
    }

namespace boost
{

template < class Iter, class Vertex > class matrix_adj_iterator
{
    typedef matrix_adj_iterator self;

public:
    typedef std::input_iterator_tag iterator_category;
    typedef Vertex value_type;
    typedef std::ptrdiff_t difference_type;
    typedef Vertex* pointer;
    typedef Vertex& reference;
    matrix_adj_iterator() {}
    matrix_adj_iterator(Iter i) : _iter(i) {}
    matrix_adj_iterator(const self& x) : _iter(x._iter) {}
    self& operator=(const self& x)
    {
        _iter = x._iter;
        return *this;
    }
    Vertex operator*() { return _iter.column(); }
    self& operator++()
    {
        ++_iter;
        return *this;
    }
    self operator++(int)
    {
        self t = *this;
        ++_iter;
        return t;
    }
    bool operator==(const self& x) const { return _iter == x._iter; }
    bool operator!=(const self& x) const { return _iter != x._iter; }

protected:
    Iter _iter;
};

template < class Iter, class Vertex > class matrix_incidence_iterator
{
    typedef matrix_incidence_iterator self;

public:
    typedef std::input_iterator_tag iterator_category;
    typedef Iter value_type;
    typedef std::ptrdiff_t difference_type;
    typedef Iter* pointer;
    typedef Iter& reference;
    matrix_incidence_iterator() {}
    matrix_incidence_iterator(Iter i) : _iter(i) {}
    matrix_incidence_iterator(const self& x) : _iter(x._iter) {}
    self& operator=(const self& x)
    {
        _iter = x._iter;
        return *this;
    }
    Iter operator*() { return _iter; }
    self& operator++()
    {
        ++_iter;
        return *this;
    }
    self operator++(int)
    {
        self t = *this;
        ++_iter;
        return t;
    }
    bool operator==(const self& x) const { return _iter == x._iter; }
    bool operator!=(const self& x) const { return _iter != x._iter; }

protected:
    Iter _iter;
};

} /* namespace boost */

#endif /* BOOST_GRAPH_MATRIX2GRAPH_HPP*/

/* matrix_as_graph.hpp
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
*/