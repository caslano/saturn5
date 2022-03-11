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