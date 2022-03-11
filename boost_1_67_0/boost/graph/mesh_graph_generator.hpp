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