// Copyright 2004, 2005 The Trustees of Indiana University.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Jeremiah Willcock
//           Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_ERDOS_RENYI_GENERATOR_HPP
#define BOOST_GRAPH_ERDOS_RENYI_GENERATOR_HPP

#include <boost/assert.hpp>
#include <iterator>
#include <utility>
#include <boost/shared_ptr.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/random/geometric_distribution.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/config/no_tr1/cmath.hpp>
#include <boost/iterator/iterator_facade.hpp>

namespace boost
{

template < typename RandomGenerator, typename Graph >
class erdos_renyi_iterator
: public iterator_facade< erdos_renyi_iterator< RandomGenerator, Graph >,
      std::pair< typename graph_traits< Graph >::vertices_size_type,
          typename graph_traits< Graph >::vertices_size_type >,
      std::input_iterator_tag,
      const std::pair< typename graph_traits< Graph >::vertices_size_type,
          typename graph_traits< Graph >::vertices_size_type >& >
{
    typedef typename graph_traits< Graph >::directed_category directed_category;
    typedef
        typename graph_traits< Graph >::vertices_size_type vertices_size_type;
    typedef typename graph_traits< Graph >::edges_size_type edges_size_type;

    BOOST_STATIC_CONSTANT(bool,
        is_undirected
        = (is_base_of< undirected_tag, directed_category >::value));

public:
    erdos_renyi_iterator() : gen(), n(0), edges(0), allow_self_loops(false) {}
    erdos_renyi_iterator(RandomGenerator& gen, vertices_size_type n,
        double fraction = 0.0, bool allow_self_loops = false)
    : gen(&gen)
    , n(n)
    , edges(edges_size_type(fraction * n * n))
    , allow_self_loops(allow_self_loops)
    {
        if (is_undirected)
            edges = edges / 2;
        next();
    }

    erdos_renyi_iterator(RandomGenerator& gen, vertices_size_type n,
        edges_size_type m, bool allow_self_loops = false)
    : gen(&gen), n(n), edges(m), allow_self_loops(allow_self_loops)
    {
        next();
    }

    const std::pair< vertices_size_type, vertices_size_type >&
    dereference() const
    {
        return current;
    }

    void increment()
    {
        --edges;
        next();
    }

    bool equal(const erdos_renyi_iterator& other) const
    {
        return edges == other.edges;
    }

private:
    void next()
    {
        uniform_int< vertices_size_type > rand_vertex(0, n - 1);
        current.first = rand_vertex(*gen);
        do
        {
            current.second = rand_vertex(*gen);
        } while (current.first == current.second && !allow_self_loops);
    }

    RandomGenerator* gen;
    vertices_size_type n;
    edges_size_type edges;
    bool allow_self_loops;
    std::pair< vertices_size_type, vertices_size_type > current;
};

template < typename RandomGenerator, typename Graph >
class sorted_erdos_renyi_iterator
: public iterator_facade< sorted_erdos_renyi_iterator< RandomGenerator, Graph >,
      std::pair< typename graph_traits< Graph >::vertices_size_type,
          typename graph_traits< Graph >::vertices_size_type >,
      std::input_iterator_tag,
      const std::pair< typename graph_traits< Graph >::vertices_size_type,
          typename graph_traits< Graph >::vertices_size_type >& >
{
    typedef typename graph_traits< Graph >::directed_category directed_category;
    typedef
        typename graph_traits< Graph >::vertices_size_type vertices_size_type;
    typedef typename graph_traits< Graph >::edges_size_type edges_size_type;

    BOOST_STATIC_CONSTANT(bool,
        is_undirected
        = (is_base_of< undirected_tag, directed_category >::value));

public:
    sorted_erdos_renyi_iterator()
    : gen()
    , rand_vertex(0.5)
    , n(0)
    , allow_self_loops(false)
    , src((std::numeric_limits< vertices_size_type >::max)())
    , tgt_index(vertices_size_type(-1))
    , prob(.5)
    {
    }

    // NOTE: The default probability has been changed to be the same as that
    // used by the geometic distribution. It was previously 0.0, which would
    // cause an assertion.
    sorted_erdos_renyi_iterator(RandomGenerator& gen, vertices_size_type n,
        double prob = 0.5, bool loops = false)
    : gen()
    , rand_vertex(1. - prob)
    , n(n)
    , allow_self_loops(loops)
    , src(0)
    , tgt_index(vertices_size_type(-1))
    , prob(prob)
    {
        this->gen.reset(new uniform_01< RandomGenerator* >(&gen));

        if (prob == 0.0)
        {
            src = (std::numeric_limits< vertices_size_type >::max)();
            return;
        }
        next();
    }

    const std::pair< vertices_size_type, vertices_size_type >&
    dereference() const
    {
        return current;
    }

    bool equal(const sorted_erdos_renyi_iterator& o) const
    {
        return src == o.src && tgt_index == o.tgt_index;
    }

    void increment() { next(); }

private:
    void next()
    {
        // In order to get the edges from the generator in sorted order, one
        // effective (but slow) procedure would be to use a
        // bernoulli_distribution for each legal (src, tgt_index) pair.  Because
        // of the O(|V|^2) cost of that, a geometric distribution is used.  The
        // geometric distribution tells how many times the
        // bernoulli_distribution would need to be run until it returns true.
        // Thus, this distribution can be used to step through the edges
        // which are actually present.
        BOOST_ASSERT(src != (std::numeric_limits< vertices_size_type >::max)()
            && src != n);
        while (src != n)
        {
            vertices_size_type increment = rand_vertex(*gen);
            size_t tgt_index_limit
                = (is_undirected ? src + 1 : n) + (allow_self_loops ? 0 : -1);
            if (tgt_index + increment >= tgt_index_limit)
            {
                // Overflowed this source; go to the next one and try again.
                ++src;
                // This bias is because the geometric distribution always
                // returns values >=1, and we want to allow 0 as a valid target.
                tgt_index = vertices_size_type(-1);
                continue;
            }
            else
            {
                tgt_index += increment;
                current.first = src;
                current.second = tgt_index
                    + (!allow_self_loops && !is_undirected && tgt_index >= src
                            ? 1
                            : 0);
                break;
            }
        }
        if (src == n)
            src = (std::numeric_limits< vertices_size_type >::max)();
    }

    shared_ptr< uniform_01< RandomGenerator* > > gen;
    geometric_distribution< vertices_size_type > rand_vertex;
    vertices_size_type n;
    bool allow_self_loops;
    vertices_size_type src, tgt_index;
    std::pair< vertices_size_type, vertices_size_type > current;
    double prob;
};

} // end namespace boost

#endif // BOOST_GRAPH_ERDOS_RENYI_GENERATOR_HPP

/* erdos_renyi_generator.hpp
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
*/