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
MBDdLqDC8r/aMlEs8XatsQzkyv76tgxgb8vAYvK5Y91QGWgXHWx5dBkI1f+/sHcl4FEUWbh6jlwzOSEHAUKAcAWEEG45DDeBBIb7JglJIIFAQg5uNCLIJRpOURCjgICiRtdzFxVPEI9FVwEVFZFdUdEFRQXP/ft1dXVPz0xmZoU9Gb7iT716VV39v6rq7uqq1y397P/xRrsLXj3bX2/vUcGMfhsQGsvI7V2jt3cF9s67v3ZQ3ztOutnaPhSD/fsUI45/mh3lAqmawvbII/y+xSJ+iuITeboow2NbiAN+QHmmi7ahlNmax0UZbm04Bvpfk35/+ob5tkCcVxC3mT3VxV5RiJuZ0rZMCGY/fAXo7RfjZD/BS222E/uGOobiP/5thtYc81ABB51nJe6QsrjvUzKg7votx0V/5fojxX7fHRS3SWYJe1KEzwAUp/hQLVTzDhF5h4j9xFspXkeySkHOeakOZTlF5XyfqsjbV+wD3UDx+lK4JMZ4Yc/hQj9N+GatoniCFCaF6PSHCv+naym9sRQrWfT7jVCOzqeNRezz5v6NNL8ag6B/E+n2FPlTDPmPI7+7Nin2Hxn0T3L9/ETXPecOpqQ9rPgdmJpFX+lX0lCOsF8Qmz4UV3rR/5qVyOUvddrPs5yOeT2L1+3nMZPeA6wJXtruZOJ+Dj+yCx0nxcO3AyKBB6jMr2CxXYoMMTM/diP0/yboE4HQu5bvVQ2MJUSpCjZUv3/vxRdiNveFSHsbqfwIed9hivAZg3TUm/cXZQx8yqLuKdS1U552QKQZ2yH2HYqyplP8iIgPpT54XMS1tgE57Gjom1zuAMK2+n2Moo/DrpBzu2rjAS+f6uTkJySNb2yotqPdcdyClJoS0b/JUYirn5A+dH1vVCrrnQuJ5/ZLKCM/ScHNMVrkYYVatrljAN8Hycu8hcVwu/Yj3a0WO+tmXmj+xo3vkD6016olHeOzEPU+/Pq5cnxSgI11D1DGCFG2uC9fRTpjpE7sG3FPgJGruKIkD4OVdm2JBD5LunZRr3F0vGuC2rNo6zhrjQn1UPrNHFn+i020aT7GxfCx4leqQ6T9JwkjhWU+1b9G5ojynbNFiXyl2GRJu7jEs8Uf6Jid4eUj3qSewwGSdTQFs+Ym1Z9DByrrhC2Gl2X0jdKE99f6pPeO+TXsq78Ei3eQHmfdTPWxxjtN3K8OpfJD3PmRpbHyKNknWoqiOEZv0r/Wcj/8zKu+Ci7SOcfa3e1JrAusS3lut5rYbdYw7muiz3zyJavoCL5Tg7awkkCNW/JhIvYU/o3OZ5VUn42UjPWPQl3GyW2ZdOpZ77Mk0lg9ifst6cyv/wMVTlh73Lt1R+iPfjARYRrCHMQXYdRbyepgPWRd9gr/dg7uC3i5TUxW7CzR/BtofTKen1dUKbWPEAvG8q/wRJsS0IzaQD/o2KgMi13kx/jKb6LEXs2viMt860zpARYLxuieQ/Czx+2za+sK2v9q/ivbj9p9x+I5p12pTd8bsJG9jfXqNqxpfsNi9KuBXsZi+HUsgOq3zmTHdSxTqmFaPfGlleLSMsbrWSBfu+fJuhOsodhRccpUYooiuVrPNtCz0nmnIY+ZyrXb3fn0EHtxRRqGm7nUksV1pzMdC8/Wcly0wdAgK1ZPHzeVmUZYH6G+kY3cXehYx238HhI/9HOdv+0LxG99e6jJRFyOjKHzE75VzlN6gl3rW3w8BlF0/rxfhNFxPjH3B0+HTO77R5SxDH6+ldo1ltqA/h43gmzWUuyz7UG2nW8491vh7eakeYHlbTbCahPfJmlNdTqtjTH8/ndasTbGbF1APl5M8axCjDHPkuyCyc4+NKk+S9pRWSdtWp+elTMfVZU=
*/