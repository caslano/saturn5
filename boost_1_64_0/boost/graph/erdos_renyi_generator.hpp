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
H3QesPvNCO6zttv947Q4/ePUUP+oQuPDCvxh/GbGh1H4DuQM+J3gbpHB+YEeMO2zGe8NeuFEzvTC+en/THnrvDxkd8D3Xv7+7I7dPDfeKyeeP5vt8pbxGRP+vbK/+nEf5ofh48U3cwfxhc8C35orMjgvB894w8zLte2IHd+eHfY4JCU0Dtlm7C/4HXb5SYVXn6VfQE6AzwFXIdNIt6jgYL1OZ5zQAd+tpW839YAZnxu7qR9+CBnx0hOcdEWYB19h14sscDVyGuGPgncg94HvACeVkp+h+bFb0c+A773CrhczTb2w2+GJVjss8gq73VBXvrfy1vU5we/Drh9dX2LXu77Pxa53Q/Dx6lfS57U09nsErJrtdjsLnnbYtNsln7fLeZo1rhb5ebsdbgNvFxlMzw7wvcjJXn8BVl+w2/mI4GB+jd/LfvO9tGe1Tvu6M5Su8D07w/nDOHHnGO0ZvJnnwL1qtuOnvkx7LjKYfpngRSKD6VcEbkBO9tJbcLBdiYTalZ3op8J3gqkf1G9/XN/7ZTv/+8HqGru8RMA5yBQvnNe8v3zbm/yi/4lbb+L3S/HzSzXb/c/Or1CuQ/WmC578NenQA38v0qQbOFxvhr5ip0/6XqZP19dIB3APOAncBx4f5/l+9N47Br/2/vKDdGe9KXZ7VUs+ke6Ei3SPm092+qbErj8m3Ye98F9np3tEcLD+pMWpP+mh+pPDc1M992DaTzPei15n17eJcerbpFB9285zk+F3gvuQU7z2RXCwfkZM/bTLTdJezvP/r5WfcH2u6xxVHrBTYtfzjs7Y9bm7M3Z97u+MXZ9H4Mlfvx/8OnYdcoKX/uDtyDT4DjDl1pSrPnjWZ/316K/b+T7J5HvcckL7YrfXmd+w25dInPZl6l6Wk3j5lXWjPR7OvvH9jfNzb7T7gyLwmchE/K8CM840+VIHH0Wa9WjwDuQUL1/ArDeZ/OqG70Wa/PLei5wIPwyO3GT3xxmCg+PeyaFxb2ux3Z7k4L5BZJBvA+9ARrzwg/uR+3jlBPwscrqX7+A3RQbXo9XNzOMjZ+I+E5yNzIDPARch94Mvudmen9wfvkrzIgts+73zZrsdOyBOO5ayl+UzPK7u/n7s8Xa/w+/F+mO1l1+4P7zblTXwWeASZK0XfvA25EYvv8Bh+7EbfjcyEX4QPPEHlCP4CHiRyGA/mwtuRY6Hbxcc3pfiyO4fvLf0HLoldnqm3hovPd+b/1m3vj/76CpkAu1J0a12P5to+lm7PUwO2SmUQ9MvRG/99/rTscKbNMZ4J/Iju11MDsUjG/14bz4PXIJM8eofuB2ZCr8d3Is041KwarbbxWF40slfj70t/v6CcH7qcN/276VfVk+ovwEXIc38C7h1FB/uh5iX6bHLx3hTPuzylBLHTkr9N8tNvPhOvN2ObwY4PJ+bFY1Xvv699A7Xr3be34FMZN/OTnA/0tjD4CGRwfQeBk+/g/TGn0xwLjLFyzdwe2icvx2+C2n2FYD7kWnwg2B1Z2g+AZyLnOi9F9yONPMV4D7kZM9/cOpd9ngjA5yDjMAXgeuQpt8HdyOnwfeCR5D7wKf+hHYBOd3LRzDz3mbeuB1eNdvzYL3wQyKD/fUIOOOnSPgscAHSjAfArcj94dt/aq+HHkD57YLvRx4IPwAeQR4En3o3+YU8GL5EcHB+/pA469qZ8O24H4GfFWfe/tDQvH0nzx0m/zY7/oMHkIdTnofAqb2uPMKbnwTnII+EzwXXIY+Cj4KvRWbBd/Xa6yxHE6++Xnu/4jHwg577M+19aCPwkZ+5cjbuM8A5yDnwuafjP/xc4lsEjiLnwbeDb0Vmw/eCh5Dz8X8YnHmPvX8gC1yCPA4=
*/