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
veUW4i8BKn1K0wJbZMLWovvyfn/4Rr95S73df37l95l7ubff633ym2NVuv3ZsPyJ09pvXvfg3lE/xh/N837PfEqISl/Ratyx3E+65F8qjpry5NWzvgGN6H98+G/Je+/aunXMZzXXjt3wwftXft++l/vnvdwD7+1eeu/3w8+jenhw9PU553xXbJu3I/zM0e23HxbiT1RvP5x+3u/uefNXDnrrQm7R2OZnhDhB9RPSdHv7uwM/UpZ2i7MVdn3iWcyzcSo9tMv9fRJLffNOvfDUJ9sffHIX2pH6SczJvMDi64be9Ef/xeXNWmfeJ8QPRN+2ZtKIx3w+f/fglhY/rVu1ZIsQY6ge9h1/9OT3jQfNeTGp4thLXV9YIUQG5ScyKD/t2PBzJW2ar1k6d/YDXwuxifrt9c41zz8/LXpkzeYpT5xpPTZRiI4k/9zyuHvaHy79Yf4XW59asDX2Ie/38x+NUumP9kv/6odeiSfu+uRPL+cpeb8XYjy1e3lNyeKvz7d85cQdKU3ane3x7JXf57+Bxp1tS1F8s3kXekZfjA6LeGLi20IEk5x+cQUXbhg3ua19xuTAuZ8UnBACYkA/339Yk+mtVix/Jqr3Cv8zP34qRCbJGZiRF30256t2/uVNztzY7SLycwH8h+GEAA/mZvV5dT7cbnVtg7As0B82/e0Tpv2di78PMB3dUzxj/I0Z0vj7etAnAN+Guxf0wcA1cOtNf28y/b3B9HeiE2E2+FHW7sbf9F4qE/Kn+dMkSn+fDMJcJNS4fGcEsAncBDhfuN5cxlNCVKv4FtAGfBsYDHwH2BB4GtgY+C7wC+BFuASWd1qhtEjuOZY3Lwj8wBuBbYALgD2BNwEHAhcChwAXAccDFwMrgJuBVcD7gAuBy4A7gLcAnwYuBx4G3gr8A3AF8BzwNqANeVgJbAjcDGwEvA/YGrgamARcA8wCrgUWAu8GzgOuA97J8e7ieNuAG4G7gJuArwJBp/Lv0O8JAA7l8tNdElz+PJuoDgNOAnYDFgGvAU4B5gCnAscBi4HTgSXA5cBS4AZgOXA/cDrwU+AM4F+B1cCLwNlABWleD2wAnANsCZwLTALeCOwPBD/lN8rGNvbZrr+a3yT8HcT7gHfwQH4V8F1ge+BZYFfgh8BewE+AacBzwAzg539n797je6r/AI5/vruZbWYXG4YZ5m6MlksuGRsbs80ujNTMNjZmW9toQiSVXEpR6ZciFBX9ECWEhPaLsn4oSiGEyE9RUcrvdd7fz/d8zya/y//2eLx7Op/P53zO5fs5n3P5fjsfzMJ/YT5ewsn4I87En/BtvIJ7sDPrsQ+74VG8C09jd/wde6Bxsd1Tb0cv7IC9sQtG493YB/tjX0zCGEzBWMzGX232z/UqzsLfcDb+js/gdXwV/8Q3UDHfW2jDd9AFt6Er7kIP3Ic18BDWxBtYC0PYd7WxMfphJ/THLhiICVgH78EgzMG6WID1cAKG4BMYiiuwMb6NYcZ6YBNjuTr9FIajL59fCwzEltgCW2FbbGMsH9vi3RiBadgeh2MHHI+ROAM76fYxXel3eOt3iCcb24hluj1v1MfzO9gI38OWuBn74hYcjrtxtE7Pw/fxAdyOD+EOXIAf4Ou4Ez/Ej/RxNVLp90vjCr0eNTFNr0c65VrgEIzEDOyFWXp5ufgwDsNHcCwuwjH4Eubr5RQr/e5jXK+X4405ejmvUa4evo4d8Q2M09ODcS0aZdfp7V2PE/FNfBBX4zO4BpcZ+Xq5ycrxTmC2RS+3Bsbo5X5Mudq4F5vhp9gJ92M0VuJA/AyTjWld73EXx/t7SXO31zuMfx/Ux3d5Tftx/Qga9T2GvfEJHISzcSTOwTE4D8s=
*/