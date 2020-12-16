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
reLsuzRJLy/RvXdczSVMA/uOq6O435cw+2IUW0FR0ex5xdIemTCDxWYl7W5Dlaza+9dDs3OeLhWbqZyLUyXuWFyHxK8ReXxWbAN9eTHvhi6GF5r3S8vgRWip+Mnf1j837qeMUeKdTbl5T1JS4r7/sGMF7HkR/xTrb/Pevhd5UPzd/PWvyVhZT7G5/bWd4WR4A+Wi9VJ/uZiRPyu3tCw0LsmRc5VfWDyvzJYH1/5Ue+5GiTvD8cqDG4ctDzbM6eLOwj1J3AOlPFwgY5/m2PfHGda+v313epYbXn5jZ5xrn8OKj/Ny3TBjbJg+drzUBHEP9t7z2zA5dj3apvjOELu+EveEE4ydlDRly1aW2Ix0fO/n54f2x8MWF+r9x6k4cfOr4p7IPUOilMeHWyi2afNmzuQmxbx7ToRxNj6SNEvOry2Hj8tvplGLEpQ+hjjFZvJWjsDE0xoOpFweD2MT+Lsxz2AxxMPfd8FBjV02SnD3D8Y9Ls7lS/KO1C2bg6BsNaxpmijlypFyyvGFyqmUu3J93mW/lBUpo8tjQmXUlgexrcCPc46/nHOxXY0f5xU/77ziL3lE3uHv5V0z/FtLXDZumx/+tY3bRSvZvkYdpG+efCFg5YX+8l5YVDg91ze2ZVp+WakdY2lshxo3Z/Qi7a5b7TqKX4rtOa7b2vaTuJMkb+W3bJlqKPtHGXfIvpvYn9nKlBfvHIu/LSumnCTA3fK7m1UWZa0l5SASvzMbKdUp1j2/a8w57hJrzrM69nnuq7zzLGmy59k/D8/NJ/wkbaTXPUdh56DYlKnOAfccNIG36HNwkf8czJ2XW7KQuEx7I2sq50zLL7LXIGM/yrgd9b2460je6PcENbY9NuxY1x0WVle4sDbIXrPeFbsP3WuSjSfJ91vFRQX50xeGwoyxNgNtu/W2uN9z4mz5KiwyRc4/dpFw3jjEcv+YX7nuebaJYbbLzbGvba3YykpzSnLn+tut58T2M2kDz5Bz4aY5Rz9o+a6/u8WuoR2PGH+xdj+o4quW3ZyppYXdcdixiW9KuI+lXWwdadfDtu38+mXuGqRxFK+C0Ds1CdNTxYufeJpzst25R22QMS7F+L0sft9I2ivl+OaUzsrJn1Nckl9Iltj7kR1id1jScIWkdWrBrCJlrwO7ZP8BJ6z+2PFrt0sam9trfZYce5TSYw/1d6lTGtIWUT6CS/tHBqLj40JjGdvHufUqzuZtUf4MyVgvXz9a5tbpsHyVsS4ziUe3G78nngTib4pOQM3QThLWAP/m/N0CxaATUUvUCjVGrdFJqI0Zs1KB2vL3WtOun0z4Lj9h3KIZf2jab1v3zPjD6tvwYnV0G77A2tp6If7lts3wl32uD9ZfyriNl3Jk0lH1/mViYyVbQoDjhofJ319xYDsv9rclJbmlxcx/z3Xr0PPu+Peiwpm2LTH2Hew5+kbcH/ruX0pzp5d589ZH2jDtbNtwSNxf+sJw+c4vzLX3MDZMT9sWRFyi3e/4wki7J7dv0n7YMKf725ippaVVxy13VK6df6zz8dY+v3B27kKvvQizXRDW3vnHJb4h6WvKHXXAhu9rw3ttky+f8mcV5pb40zYozH65P23umGprmxJmW6FUdW2rtc8Is+e1mb1mKDcvdcG19T5GjudVye/NUgFs2bBtR6TYvCQ2l1obufuzbWjUJW7bNJn6Gq+fD/i99gnUL9QBdUSdUGd0CuqCTkVdUTeUiLqjHug01BP1Qr1RH9QXrfgJcxhC11/KNPXDLdPxVcYT23Lr1mnrb8tmWJ225U/8i62/v8z567UpW6ZOh9f/5dbOLRf2fs/6y/l37/eqaSuo6/YZtqypkk2/U29l+JJ+hr3UX9c=
*/