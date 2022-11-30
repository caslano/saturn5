// Copyright 2004, 2005 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Nick Edmonds
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_MESH_GENERATOR_HPP
#define BOOST_GRAPH_MESH_GENERATOR_HPP

#include <iterator>
#include <utility>
#include <boost/assert.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost
{

template < typename Graph > class mesh_iterator
{
    typedef typename graph_traits< Graph >::directed_category directed_category;
    typedef
        typename graph_traits< Graph >::vertices_size_type vertices_size_type;

    BOOST_STATIC_CONSTANT(bool,
        is_undirected
        = (is_base_and_derived< undirected_tag, directed_category >::value
            || is_same< undirected_tag, directed_category >::value));

public:
    typedef std::input_iterator_tag iterator_category;
    typedef std::pair< vertices_size_type, vertices_size_type > value_type;
    typedef const value_type& reference;
    typedef const value_type* pointer;
    typedef void difference_type;

    mesh_iterator() : x(0), y(0), done(true) {}

    // Vertices are numbered in row-major order
    // Assumes directed
    mesh_iterator(
        vertices_size_type x, vertices_size_type y, bool toroidal = true)
    : x(x)
    , y(y)
    , n(x * y)
    , source(0)
    , target(1)
    , current(0, 1)
    , toroidal(toroidal)
    , done(false)
    {
        BOOST_ASSERT(x > 1 && y > 1);
    }

    reference operator*() const { return current; }
    pointer operator->() const { return &current; }

    mesh_iterator& operator++()
    {
        if (is_undirected)
        {
            if (!toroidal)
            {
                if (target == source + 1)
                    if (source < x * (y - 1))
                        target = source + x;
                    else
                    {
                        source++;
                        target = (source % x) < x - 1 ? source + 1 : source + x;
                        if (target > n)
                            done = true;
                    }
                else if (target == source + x)
                {
                    source++;
                    target = (source % x) < x - 1 ? source + 1 : source + x;
                }
            }
            else
            {
                if (target == source + 1 || target == source - (source % x))
                    target = (source + x) % n;
                else if (target == (source + x) % n)
                {
                    if (source == n - 1)
                        done = true;
                    else
                    {
                        source++;
                        target = (source % x) < (x - 1) ? source + 1
                                                        : source - (source % x);
                    }
                }
            }
        }
        else
        { // Directed
            if (!toroidal)
            {
                if (target == source - x)
                    target = source % x > 0 ? source - 1 : source + 1;
                else if (target == source - 1)
                    if ((source % x) < (x - 1))
                        target = source + 1;
                    else if (source < x * (y - 1))
                        target = source + x;
                    else
                    {
                        done = true;
                    }
                else if (target == source + 1)
                    if (source < x * (y - 1))
                        target = source + x;
                    else
                    {
                        source++;
                        target = source - x;
                    }
                else if (target == source + x)
                {
                    source++;
                    target = (source >= x) ? source - x : source - 1;
                }
            }
            else
            {
                if (source == n - 1 && target == (source + x) % n)
                    done = true;
                else if (target == source - 1 || target == source + x - 1)
                    target = (source + x) % n;
                else if (target == source + 1
                    || target == source - (source % x))
                    target = (source - x + n) % n;
                else if (target == (source - x + n) % n)
                    target = (source % x > 0) ? source - 1 : source + x - 1;
                else if (target == (source + x) % n)
                {
                    source++;
                    target = (source % x) < (x - 1) ? source + 1
                                                    : source - (source % x);
                }
            }
        }

        current.first = source;
        current.second = target;

        return *this;
    }

    mesh_iterator operator++(int)
    {
        mesh_iterator temp(*this);
        ++(*this);
        return temp;
    }

    bool operator==(const mesh_iterator& other) const
    {
        return done == other.done;
    }

    bool operator!=(const mesh_iterator& other) const
    {
        return !(*this == other);
    }

private:
    vertices_size_type x, y;
    vertices_size_type n;
    vertices_size_type source;
    vertices_size_type target;
    value_type current;
    bool toroidal;
    bool done;
};

} // end namespace boost

#endif // BOOST_GRAPH_MESH_GENERATOR_HPP

/* mesh_graph_generator.hpp
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
*/