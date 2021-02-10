// Copyright 2004-2006 The Trustees of Indiana University.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_PLOD_GENERATOR_HPP
#define BOOST_GRAPH_PLOD_GENERATOR_HPP

#include <iterator>
#include <utility>
#include <boost/random/uniform_int.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/graph/graph_traits.hpp>
#include <vector>
#include <map>
#include <boost/config/no_tr1/cmath.hpp>
#include <boost/mpl/if.hpp>

namespace boost
{
template < typename RandomGenerator > class out_directed_plod_iterator
{
public:
    typedef std::forward_iterator_tag iterator_category;
    typedef std::pair< std::size_t, std::size_t > value_type;
    typedef const value_type& reference;
    typedef const value_type* pointer;
    typedef std::ptrdiff_t difference_type;

    out_directed_plod_iterator() : gen(0), at_end(true) {}

    out_directed_plod_iterator(RandomGenerator& gen, std::size_t n,
        double alpha, double beta, bool allow_self_loops)
    : gen(&gen)
    , n(n)
    , alpha(alpha)
    , beta(beta)
    , allow_self_loops(allow_self_loops)
    , at_end(false)
    , degree(0)
    , current(0, 0)
    {
        using std::pow;

        uniform_int< std::size_t > x(0, n - 1);
        std::size_t xv = x(gen);
        degree = (xv == 0 ? 0 : std::size_t(beta * pow(xv, -alpha)));
    }

    reference operator*() const { return current; }
    pointer operator->() const { return &current; }

    out_directed_plod_iterator& operator++()
    {
        using std::pow;

        uniform_int< std::size_t > x(0, n - 1);

        // Continue stepping through source nodes until the
        // (out)degree is > 0
        while (degree == 0)
        {
            // Step to the next source node. If we've gone past the
            // number of nodes we're responsible for, we're done.
            if (++current.first >= n)
            {
                at_end = true;
                return *this;
            }

            std::size_t xv = x(*gen);
            degree = (xv == 0 ? 0 : std::size_t(beta * pow(xv, -alpha)));
        }

        do
        {
            current.second = x(*gen);
        } while (current.first == current.second && !allow_self_loops);
        --degree;

        return *this;
    }

    out_directed_plod_iterator operator++(int)
    {
        out_directed_plod_iterator temp(*this);
        ++(*this);
        return temp;
    }

    bool operator==(const out_directed_plod_iterator& other) const
    {
        return at_end == other.at_end;
    }

    bool operator!=(const out_directed_plod_iterator& other) const
    {
        return !(*this == other);
    }

private:
    RandomGenerator* gen;
    std::size_t n;
    double alpha;
    double beta;
    bool allow_self_loops;
    bool at_end;
    std::size_t degree;
    value_type current;
};

template < typename RandomGenerator > class undirected_plod_iterator
{
    typedef std::vector< std::pair< std::size_t, std::size_t > > out_degrees_t;

public:
    typedef std::input_iterator_tag iterator_category;
    typedef std::pair< std::size_t, std::size_t > value_type;
    typedef const value_type& reference;
    typedef const value_type* pointer;
    typedef std::ptrdiff_t difference_type;

    undirected_plod_iterator()
    : gen(0), out_degrees(), degrees_left(0), allow_self_loops(false)
    {
    }

    undirected_plod_iterator(RandomGenerator& gen, std::size_t n, double alpha,
        double beta, bool allow_self_loops = false)
    : gen(&gen)
    , n(n)
    , out_degrees(new out_degrees_t)
    , degrees_left(0)
    , allow_self_loops(allow_self_loops)
    {
        using std::pow;

        uniform_int< std::size_t > x(0, n - 1);
        for (std::size_t i = 0; i != n; ++i)
        {
            std::size_t xv = x(gen);
            std::size_t degree
                = (xv == 0 ? 0 : std::size_t(beta * pow(xv, -alpha)));
            if (degree == 0)
                degree = 1;
            else if (degree >= n)
                degree = n - 1;
            out_degrees->push_back(std::make_pair(i, degree));
            degrees_left += degree;
        }

        next();
    }

    reference operator*() const { return current; }
    pointer operator->() const { return &current; }

    undirected_plod_iterator& operator++()
    {
        next();
        return *this;
    }

    undirected_plod_iterator operator++(int)
    {
        undirected_plod_iterator temp(*this);
        ++(*this);
        return temp;
    }

    bool operator==(const undirected_plod_iterator& other) const
    {
        return degrees_left == other.degrees_left;
    }

    bool operator!=(const undirected_plod_iterator& other) const
    {
        return !(*this == other);
    }

private:
    void next()
    {
        std::size_t source, target;
        while (true)
        {
            /* We may get to the point where we can't actually find any
               new edges, so we just add some random edge and set the
               degrees left = 0 to signal termination. */
            if (out_degrees->size() < 2)
            {
                uniform_int< std::size_t > x(0, n - 1);
                current.first = x(*gen);
                do
                {
                    current.second = x(*gen);
                } while (current.first == current.second && !allow_self_loops);
                degrees_left = 0;
                out_degrees->clear();
                return;
            }

            uniform_int< std::size_t > x(0, out_degrees->size() - 1);

            // Select source vertex
            source = x(*gen);
            if ((*out_degrees)[source].second == 0)
            {
                (*out_degrees)[source] = out_degrees->back();
                out_degrees->pop_back();
                continue;
            }

            // Select target vertex
            target = x(*gen);
            if ((*out_degrees)[target].second == 0)
            {
                (*out_degrees)[target] = out_degrees->back();
                out_degrees->pop_back();
                continue;
            }
            else if (source != target
                || (allow_self_loops && (*out_degrees)[source].second > 2))
            {
                break;
            }
        }

        // Update degree counts
        --(*out_degrees)[source].second;
        --degrees_left;
        --(*out_degrees)[target].second;
        --degrees_left;
        current.first = (*out_degrees)[source].first;
        current.second = (*out_degrees)[target].first;
    }

    RandomGenerator* gen;
    std::size_t n;
    shared_ptr< out_degrees_t > out_degrees;
    std::size_t degrees_left;
    bool allow_self_loops;
    value_type current;
};

template < typename RandomGenerator, typename Graph >
class plod_iterator
: public mpl::if_<
      is_convertible< typename graph_traits< Graph >::directed_category,
          directed_tag >,
      out_directed_plod_iterator< RandomGenerator >,
      undirected_plod_iterator< RandomGenerator > >::type
{
    typedef typename mpl::if_<
        is_convertible< typename graph_traits< Graph >::directed_category,
            directed_tag >,
        out_directed_plod_iterator< RandomGenerator >,
        undirected_plod_iterator< RandomGenerator > >::type inherited;

public:
    plod_iterator() : inherited() {}

    plod_iterator(RandomGenerator& gen, std::size_t n, double alpha,
        double beta, bool allow_self_loops = false)
    : inherited(gen, n, alpha, beta, allow_self_loops)
    {
    }
};

} // end namespace boost

#endif // BOOST_GRAPH_PLOD_GENERATOR_HPP

/* plod_generator.hpp
tzwLjOXw0j/CorIZX9+cOIGHkI5u73RwgKlmG5qz/kXRgDSFYMIG2z8YMiw+FzLoQi9fRq8iM6ZC0V7FvhJ9q2werEcRpOScoH3luKRyw9INnuSAyZG/xEj4qcI44Vc/Ez4rSTqF5YS17fOi8sEc1REahwojqUtIaM+FS8aKLHst35OkDVI4jNKdwyElYm2x+7VwQVVVbzFTahQKn5LL1Wzmx8qRFX6i5yW1KH27k1DMUZblQnjWQZPcpSswyRX15PgNwvz7/hDFAO6f7UlO6QcW92LUF1VxDf8/UEsDBAoAAAAIAC1nSlKQJyd31FkAAL3HAQAeAAkAY3VybC1tYXN0ZXIvbGliL3Zzc2gvbGlic3NoMi5jVVQFAAG2SCRg7X1rd9vGteh3/QpIXbFJh5IfbXN67Ni5tERZvJZIHZKK45NmYUEkKOGIJFgAtKye+P72ux8zg5nBAAQlOXVSs41FAvOePfu99zx+dH+fLe+Rt/bj038+fOAv1ThN4v8Jx5m7tO//6vH/oNbf4e+6Th57eZVf/aa3vsqvXoOq+KKX7/G776/r6O84NvznMdb8u49f4QlUw5r78fImiS4uM6+x3/Se/ud//s3b9Z49efa05R0EiyicecMsXJyHyUXL+35CT/7PZfDx414a
*/