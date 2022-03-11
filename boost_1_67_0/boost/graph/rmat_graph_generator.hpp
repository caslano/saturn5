// Copyright 2004, 2005 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Nick Edmonds
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_RMAT_GENERATOR_HPP
#define BOOST_GRAPH_RMAT_GENERATOR_HPP

#include <math.h>
#include <iterator>
#include <utility>
#include <vector>
#include <queue>
#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/assert.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_01.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/detail/mpi_include.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/type_traits/is_same.hpp>
// #include <boost/test/floating_point_comparison.hpp>

using boost::shared_ptr;
using boost::uniform_01;

// Returns floor(log_2(n)), and -1 when n is 0
template < typename IntegerType > inline int int_log2(IntegerType n)
{
    int l = 0;
    while (n > 0)
    {
        ++l;
        n >>= 1;
    }
    return l - 1;
}

struct keep_all_edges
{
    template < typename T > bool operator()(const T&, const T&) { return true; }
};

template < typename Distribution, typename ProcessId > struct keep_local_edges
{

    keep_local_edges(const Distribution& distrib, const ProcessId& id)
    : distrib(distrib), id(id)
    {
    }

    template < typename T > bool operator()(const T& x, const T& y)
    {
        return distrib(x) == id || distrib(y) == id;
    }

private:
    const Distribution& distrib;
    const ProcessId& id;
};

template < typename RandomGenerator, typename T >
void generate_permutation_vector(
    RandomGenerator& gen, std::vector< T >& vertexPermutation, T n)
{
    using boost::uniform_int;

    vertexPermutation.resize(n);

    // Generate permutation map of vertex numbers
    uniform_int< T > rand_vertex(0, n - 1);
    for (T i = 0; i < n; ++i)
        vertexPermutation[i] = i;

    // Can't use std::random_shuffle unless we create another (synchronized)
    // PRNG
    for (T i = 0; i < n; ++i)
        std::swap(vertexPermutation[i], vertexPermutation[rand_vertex(gen)]);
}

template < typename RandomGenerator, typename T >
std::pair< T, T > generate_edge(
    shared_ptr< uniform_01< RandomGenerator > > prob, T n, unsigned int SCALE,
    double a, double b, double c, double d)
{
    T u = 0, v = 0;
    T step = n / 2;
    for (unsigned int j = 0; j < SCALE; ++j)
    {
        double p = (*prob)();

        if (p < a)
            ;
        else if (p >= a && p < a + b)
            v += step;
        else if (p >= a + b && p < a + b + c)
            u += step;
        else
        { // p > a + b + c && p < a + b + c + d
            u += step;
            v += step;
        }

        step /= 2;

        // 0.2 and 0.9 are hardcoded in the reference SSCA implementation.
        // The maximum change in any given value should be less than 10%
        a *= 0.9 + 0.2 * (*prob)();
        b *= 0.9 + 0.2 * (*prob)();
        c *= 0.9 + 0.2 * (*prob)();
        d *= 0.9 + 0.2 * (*prob)();

        double S = a + b + c + d;

        a /= S;
        b /= S;
        c /= S;
        // d /= S;
        // Ensure all values add up to 1, regardless of floating point errors
        d = 1. - a - b - c;
    }

    return std::make_pair(u, v);
}

namespace boost
{

/*
  Chakrabarti's R-MAT scale free generator.

  For all flavors of the R-MAT iterator a+b+c+d must equal 1 and for the
  unique_rmat_iterator 'm' << 'n^2'.  If 'm' is too close to 'n^2' the
  generator may be unable to generate sufficient unique edges

  To get a true scale free distribution {a, b, c, d : a > b, a > c, a > d}
*/

template < typename RandomGenerator, typename Graph > class rmat_iterator
{
    typedef typename graph_traits< Graph >::directed_category directed_category;
    typedef
        typename graph_traits< Graph >::vertices_size_type vertices_size_type;
    typedef typename graph_traits< Graph >::edges_size_type edges_size_type;

public:
    typedef std::input_iterator_tag iterator_category;
    typedef std::pair< vertices_size_type, vertices_size_type > value_type;
    typedef const value_type& reference;
    typedef const value_type* pointer;
    typedef std::ptrdiff_t difference_type; // Not used

    // No argument constructor, set to terminating condition
    rmat_iterator() : gen(), edge(0) {}

    // Initialize for edge generation
    rmat_iterator(RandomGenerator& gen, vertices_size_type n, edges_size_type m,
        double a, double b, double c, double d, bool permute_vertices = true)
    : gen()
    , n(n)
    , a(a)
    , b(b)
    , c(c)
    , d(d)
    , edge(m)
    , permute_vertices(permute_vertices)
    , SCALE(int_log2(n))

    {
        this->gen.reset(new uniform_01< RandomGenerator >(gen));

        // BOOST_ASSERT(boost::test_tools::check_is_close(a + b + c +
        // d, 1., 1.e-5));

        if (permute_vertices)
            generate_permutation_vector(gen, vertexPermutation, n);

        // TODO: Generate the entire adjacency matrix then "Clip and flip" if
        // undirected graph

        // Generate the first edge
        vertices_size_type u, v;
        boost::tie(u, v) = generate_edge(this->gen, n, SCALE, a, b, c, d);

        if (permute_vertices)
            current
                = std::make_pair(vertexPermutation[u], vertexPermutation[v]);
        else
            current = std::make_pair(u, v);

        --edge;
    }

    reference operator*() const { return current; }
    pointer operator->() const { return &current; }

    rmat_iterator& operator++()
    {
        vertices_size_type u, v;
        boost::tie(u, v) = generate_edge(this->gen, n, SCALE, a, b, c, d);

        if (permute_vertices)
            current
                = std::make_pair(vertexPermutation[u], vertexPermutation[v]);
        else
            current = std::make_pair(u, v);

        --edge;

        return *this;
    }

    rmat_iterator operator++(int)
    {
        rmat_iterator temp(*this);
        ++(*this);
        return temp;
    }

    bool operator==(const rmat_iterator& other) const
    {
        return edge == other.edge;
    }

    bool operator!=(const rmat_iterator& other) const
    {
        return !(*this == other);
    }

private:
    // Parameters
    shared_ptr< uniform_01< RandomGenerator > > gen;
    vertices_size_type n;
    double a, b, c, d;
    int edge;
    bool permute_vertices;
    int SCALE;

    // Internal data structures
    std::vector< vertices_size_type > vertexPermutation;
    value_type current;
};

// Sorted version for CSR
template < typename T > struct sort_pair
{
    bool operator()(const std::pair< T, T >& x, const std::pair< T, T >& y)
    {
        if (x.first == y.first)
            return x.second > y.second;
        else
            return x.first > y.first;
    }
};

template < typename RandomGenerator, typename Graph,
    typename EdgePredicate = keep_all_edges >
class sorted_rmat_iterator
{
    typedef typename graph_traits< Graph >::directed_category directed_category;
    typedef
        typename graph_traits< Graph >::vertices_size_type vertices_size_type;
    typedef typename graph_traits< Graph >::edges_size_type edges_size_type;

public:
    typedef std::input_iterator_tag iterator_category;
    typedef std::pair< vertices_size_type, vertices_size_type > value_type;
    typedef const value_type& reference;
    typedef const value_type* pointer;
    typedef std::ptrdiff_t difference_type; // Not used

    // No argument constructor, set to terminating condition
    sorted_rmat_iterator()
    : gen(), values(sort_pair< vertices_size_type >()), done(true)
    {
    }

    // Initialize for edge generation
    sorted_rmat_iterator(RandomGenerator& gen, vertices_size_type n,
        edges_size_type m, double a, double b, double c, double d,
        bool permute_vertices = true, EdgePredicate ep = keep_all_edges())
    : gen()
    , permute_vertices(permute_vertices)
    , values(sort_pair< vertices_size_type >())
    , done(false)

    {
        // BOOST_ASSERT(boost::test_tools::check_is_close(a + b + c +
        // d, 1., 1.e-5));

        this->gen.reset(new uniform_01< RandomGenerator >(gen));

        std::vector< vertices_size_type > vertexPermutation;
        if (permute_vertices)
            generate_permutation_vector(gen, vertexPermutation, n);

        // TODO: "Clip and flip" if undirected graph
        int SCALE = int_log2(n);

        for (edges_size_type i = 0; i < m; ++i)
        {

            vertices_size_type u, v;
            boost::tie(u, v) = generate_edge(this->gen, n, SCALE, a, b, c, d);

            if (permute_vertices)
            {
                if (ep(vertexPermutation[u], vertexPermutation[v]))
                    values.push(std::make_pair(
                        vertexPermutation[u], vertexPermutation[v]));
            }
            else
            {
                if (ep(u, v))
                    values.push(std::make_pair(u, v));
            }
        }

        current = values.top();
        values.pop();
    }

    reference operator*() const { return current; }
    pointer operator->() const { return &current; }

    sorted_rmat_iterator& operator++()
    {
        if (!values.empty())
        {
            current = values.top();
            values.pop();
        }
        else
            done = true;

        return *this;
    }

    sorted_rmat_iterator operator++(int)
    {
        sorted_rmat_iterator temp(*this);
        ++(*this);
        return temp;
    }

    bool operator==(const sorted_rmat_iterator& other) const
    {
        return values.empty() && other.values.empty() && done && other.done;
    }

    bool operator!=(const sorted_rmat_iterator& other) const
    {
        return !(*this == other);
    }

private:
    // Parameters
    shared_ptr< uniform_01< RandomGenerator > > gen;
    bool permute_vertices;

    // Internal data structures
    std::priority_queue< value_type, std::vector< value_type >,
        sort_pair< vertices_size_type > >
        values;
    value_type current;
    bool done;
};

// This version is slow but guarantees unique edges
template < typename RandomGenerator, typename Graph,
    typename EdgePredicate = keep_all_edges >
class unique_rmat_iterator
{
    typedef typename graph_traits< Graph >::directed_category directed_category;
    typedef
        typename graph_traits< Graph >::vertices_size_type vertices_size_type;
    typedef typename graph_traits< Graph >::edges_size_type edges_size_type;

public:
    typedef std::input_iterator_tag iterator_category;
    typedef std::pair< vertices_size_type, vertices_size_type > value_type;
    typedef const value_type& reference;
    typedef const value_type* pointer;
    typedef std::ptrdiff_t difference_type; // Not used

    // No argument constructor, set to terminating condition
    unique_rmat_iterator() : gen(), done(true) {}

    // Initialize for edge generation
    unique_rmat_iterator(RandomGenerator& gen, vertices_size_type n,
        edges_size_type m, double a, double b, double c, double d,
        bool permute_vertices = true, EdgePredicate ep = keep_all_edges())
    : gen(), done(false)

    {
        // BOOST_ASSERT(boost::test_tools::check_is_close(a + b + c +
        // d, 1., 1.e-5));

        this->gen.reset(new uniform_01< RandomGenerator >(gen));

        std::vector< vertices_size_type > vertexPermutation;
        if (permute_vertices)
            generate_permutation_vector(gen, vertexPermutation, n);

        int SCALE = int_log2(n);

        std::map< value_type, bool > edge_map;

        edges_size_type edges = 0;
        do
        {
            vertices_size_type u, v;
            boost::tie(u, v) = generate_edge(this->gen, n, SCALE, a, b, c, d);

            // Lowest vertex number always comes first
            // (this means we don't have to worry about i->j and j->i being in
            // the edge list)
            if (u > v && is_same< directed_category, undirected_tag >::value)
                std::swap(u, v);

            if (edge_map.find(std::make_pair(u, v)) == edge_map.end())
            {
                edge_map[std::make_pair(u, v)] = true;

                if (permute_vertices)
                {
                    if (ep(vertexPermutation[u], vertexPermutation[v]))
                        values.push_back(std::make_pair(
                            vertexPermutation[u], vertexPermutation[v]));
                }
                else
                {
                    if (ep(u, v))
                        values.push_back(std::make_pair(u, v));
                }

                edges++;
            }
        } while (edges < m);
        // NGE - Asking for more than n^2 edges will result in an infinite loop
        // here
        //       Asking for a value too close to n^2 edges may as well

        current = values.back();
        values.pop_back();
    }

    reference operator*() const { return current; }
    pointer operator->() const { return &current; }

    unique_rmat_iterator& operator++()
    {
        if (!values.empty())
        {
            current = values.back();
            values.pop_back();
        }
        else
            done = true;

        return *this;
    }

    unique_rmat_iterator operator++(int)
    {
        unique_rmat_iterator temp(*this);
        ++(*this);
        return temp;
    }

    bool operator==(const unique_rmat_iterator& other) const
    {
        return values.empty() && other.values.empty() && done && other.done;
    }

    bool operator!=(const unique_rmat_iterator& other) const
    {
        return !(*this == other);
    }

private:
    // Parameters
    shared_ptr< uniform_01< RandomGenerator > > gen;

    // Internal data structures
    std::vector< value_type > values;
    value_type current;
    bool done;
};

// This version is slow but guarantees unique edges
template < typename RandomGenerator, typename Graph,
    typename EdgePredicate = keep_all_edges >
class sorted_unique_rmat_iterator
{
    typedef typename graph_traits< Graph >::directed_category directed_category;
    typedef
        typename graph_traits< Graph >::vertices_size_type vertices_size_type;
    typedef typename graph_traits< Graph >::edges_size_type edges_size_type;

public:
    typedef std::input_iterator_tag iterator_category;
    typedef std::pair< vertices_size_type, vertices_size_type > value_type;
    typedef const value_type& reference;
    typedef const value_type* pointer;
    typedef std::ptrdiff_t difference_type; // Not used

    // No argument constructor, set to terminating condition
    sorted_unique_rmat_iterator()
    : gen(), values(sort_pair< vertices_size_type >()), done(true)
    {
    }

    // Initialize for edge generation
    sorted_unique_rmat_iterator(RandomGenerator& gen, vertices_size_type n,
        edges_size_type m, double a, double b, double c, double d,
        bool bidirectional = false, bool permute_vertices = true,
        EdgePredicate ep = keep_all_edges())
    : gen()
    , bidirectional(bidirectional)
    , values(sort_pair< vertices_size_type >())
    , done(false)

    {
        // BOOST_ASSERT(boost::test_tools::check_is_close(a + b + c +
        // d, 1., 1.e-5));

        this->gen.reset(new uniform_01< RandomGenerator >(gen));

        std::vector< vertices_size_type > vertexPermutation;
        if (permute_vertices)
            generate_permutation_vector(gen, vertexPermutation, n);

        int SCALE = int_log2(n);

        std::map< value_type, bool > edge_map;

        edges_size_type edges = 0;
        do
        {

            vertices_size_type u, v;
            boost::tie(u, v) = generate_edge(this->gen, n, SCALE, a, b, c, d);

            if (bidirectional)
            {
                if (edge_map.find(std::make_pair(u, v)) == edge_map.end())
                {
                    edge_map[std::make_pair(u, v)] = true;
                    edge_map[std::make_pair(v, u)] = true;

                    if (ep(u, v))
                    {
                        if (permute_vertices)
                        {
                            values.push(std::make_pair(
                                vertexPermutation[u], vertexPermutation[v]));
                            values.push(std::make_pair(
                                vertexPermutation[v], vertexPermutation[u]));
                        }
                        else
                        {
                            values.push(std::make_pair(u, v));
                            values.push(std::make_pair(v, u));
                        }
                    }

                    ++edges;
                }
            }
            else
            {
                // Lowest vertex number always comes first
                // (this means we don't have to worry about i->j and j->i being
                // in the edge list)
                if (u > v
                    && is_same< directed_category, undirected_tag >::value)
                    std::swap(u, v);

                if (edge_map.find(std::make_pair(u, v)) == edge_map.end())
                {
                    edge_map[std::make_pair(u, v)] = true;

                    if (permute_vertices)
                    {
                        if (ep(vertexPermutation[u], vertexPermutation[v]))
                            values.push(std::make_pair(
                                vertexPermutation[u], vertexPermutation[v]));
                    }
                    else
                    {
                        if (ep(u, v))
                            values.push(std::make_pair(u, v));
                    }

                    ++edges;
                }
            }

        } while (edges < m);
        // NGE - Asking for more than n^2 edges will result in an infinite loop
        // here
        //       Asking for a value too close to n^2 edges may as well

        current = values.top();
        values.pop();
    }

    reference operator*() const { return current; }
    pointer operator->() const { return &current; }

    sorted_unique_rmat_iterator& operator++()
    {
        if (!values.empty())
        {
            current = values.top();
            values.pop();
        }
        else
            done = true;

        return *this;
    }

    sorted_unique_rmat_iterator operator++(int)
    {
        sorted_unique_rmat_iterator temp(*this);
        ++(*this);
        return temp;
    }

    bool operator==(const sorted_unique_rmat_iterator& other) const
    {
        return values.empty() && other.values.empty() && done && other.done;
    }

    bool operator!=(const sorted_unique_rmat_iterator& other) const
    {
        return !(*this == other);
    }

private:
    // Parameters
    shared_ptr< uniform_01< RandomGenerator > > gen;
    bool bidirectional;

    // Internal data structures
    std::priority_queue< value_type, std::vector< value_type >,
        sort_pair< vertices_size_type > >
        values;
    value_type current;
    bool done;
};

} // end namespace boost

#include BOOST_GRAPH_MPI_INCLUDE(< boost / graph / distributed / rmat_graph_generator.hpp >)

#endif // BOOST_GRAPH_RMAT_GENERATOR_HPP

/* rmat_graph_generator.hpp
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
*/