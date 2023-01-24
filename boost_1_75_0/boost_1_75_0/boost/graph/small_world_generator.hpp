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
xktTWFv/B4oomumEMhV18shbu4otVaqKDgzturVawzHIXGbF11dy+v7QITkCTcysnxZMsvLRpmlJ01i437HkKUl25kvkTRh65CB0Rlo3jfW67+BFggfJRtZ7tzFL2doeQ0a/WCOixEkTlZN+b+FEIcKL4VLdcsDBI0iURClBm6kXUmTSopEF6r1klhpmdo17pbF+z4UHGhOG+PeZw/n3hQ7toGpijqR/mBhYf1es/cE4znm54jNxIW8hU6osu+NA94GrwCsIARJSjIZDyGqhLWQ8xvAr5aYet4T7NpwgnQLXF49/W7oSmxHHInxTR4CUc4SCyjpj2vtr/zF8CPc8geKPj9QV0u/7k8glqsUUqeI5ItQmb7vlpnMn8Xftf0/Cz330d+s1hyv/80PE0DUxowljUrAbvuLd1PO02PzmjuadpcH4ghNi5jYVNXju+qaBa4BA2iyD4ztaKMf36cic4GN0F8uXyuqp53LHtQ7HFf/T7tb6zp87K2wvoNNi/Xy8BcSmOmCiQ6Z+HSmzucBqv120p8b+AWBfjmwEGhZWuGb0upFeFSgYZndybKYBqDScnErTYp4b3HW+qnDE69meVLLmHctWE8ldWojj/qZhnc3c/2Vt8155qlUKMvT58KNDton8Snl4Q58XIdD+maAf2tZugu/+uWuBJWGo2e5ow/O5JWK124euvQGVX2zNFn/H5ey40wVoH7KcC3Hs
*/