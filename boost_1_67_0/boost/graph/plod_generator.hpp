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