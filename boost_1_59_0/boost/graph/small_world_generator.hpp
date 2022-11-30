// Copyright 2004 The Trustees of Indiana University.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_SMALL_WORLD_GENERATOR_HPP
#define BOOST_GRAPH_SMALL_WORLD_GENERATOR_HPP

#include <iterator>
#include <utility>
#include <boost/random/uniform_01.hpp>
#include <boost/random/uniform_int.hpp>

namespace boost
{

// Assumes undirected
template < typename RandomGenerator, typename Graph > class small_world_iterator
{
    typedef
        typename graph_traits< Graph >::vertices_size_type vertices_size_type;

public:
    typedef std::input_iterator_tag iterator_category;
    typedef std::pair< vertices_size_type, vertices_size_type > value_type;
    typedef const value_type& reference;
    typedef const value_type* pointer;
    typedef void difference_type;

    small_world_iterator() : gen(0) {}
    small_world_iterator(RandomGenerator& gen, vertices_size_type n,
        vertices_size_type k, double prob = 0.0, bool allow_self_loops = false)
    : gen(&gen)
    , n(n)
    , k(k)
    , prob(prob)
    , source(0)
    , target(allow_self_loops ? 0 : 1)
    , allow_self_loops(allow_self_loops)
    , current(0, allow_self_loops ? 0 : 1)
    {
    }

    reference operator*() const { return current; }
    pointer operator->() const { return &current; }

    small_world_iterator& operator++()
    {
        target = (target + 1) % n;
        if (target == (source + k / 2 + 1) % n)
        {
            ++source;
            if (allow_self_loops)
                target = source;
            else
                target = (source + 1) % n;
        }
        current.first = source;

        uniform_01< RandomGenerator, double > rand01(*gen);
        uniform_int< vertices_size_type > rand_vertex_gen(0, n - 1);
        double x = rand01();
        *gen = rand01.base(); // GRRRR
        if (x < prob)
        {
            vertices_size_type lower = (source + n - k / 2) % n;
            vertices_size_type upper = (source + k / 2) % n;
            do
            {
                current.second = rand_vertex_gen(*gen);
            } while ((current.second >= lower && current.second <= upper)
                || (upper < lower
                    && (current.second >= lower || current.second <= upper)));
        }
        else
        {
            current.second = target;
        }
        return *this;
    }

    small_world_iterator operator++(int)
    {
        small_world_iterator temp(*this);
        ++(*this);
        return temp;
    }

    bool operator==(const small_world_iterator& other) const
    {
        if (!gen && other.gen)
            return other == *this;
        else if (gen && !other.gen)
            return source == n;
        else if (!gen && !other.gen)
            return true;
        return source == other.source && target == other.target;
    }

    bool operator!=(const small_world_iterator& other) const
    {
        return !(*this == other);
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
    vertices_size_type k;
    double prob;
    vertices_size_type source;
    vertices_size_type target;
    bool allow_self_loops;
    value_type current;
};

} // end namespace boost

#endif // BOOST_GRAPH_SMALL_WORLD_GENERATOR_HPP

/* small_world_generator.hpp
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
*/