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