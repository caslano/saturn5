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

#include BOOST_GRAPH_MPI_INCLUDE(<boost/graph/distributed/rmat_graph_generator.hpp>)

#endif // BOOST_GRAPH_RMAT_GENERATOR_HPP

/* rmat_graph_generator.hpp
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
*/