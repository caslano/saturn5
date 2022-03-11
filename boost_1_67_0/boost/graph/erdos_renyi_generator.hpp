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