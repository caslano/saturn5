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
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
*/