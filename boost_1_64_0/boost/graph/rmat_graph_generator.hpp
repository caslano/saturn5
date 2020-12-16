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
sobixLBfj+Ok/H/vVOPQewLZL66fpYav9Gwj4v+R7b1PU/stzwGrqQzZ9jaKVicR4QK1WJQPFlnO3iRjnzJX/OhZTrL9W8afmr+itGNBVWlEZL7DtjvEWEW3ObyT0ky2G+WeXlng5rUMPEeAz2n9mdq7UWPWFS1Hntge7zYKT7U3VOqZ2xL7MK0vJUm9eKNehdDCcrifbXRy/zPZ13RRfddH3GvCemD+9wHPvWiIoIDqhbqNzBvZRqbO00ryzC/05HExzzjw7AYtyGfB1iCHb5BPW/yrpgt+G/CGUDgPudWI87AaJ3DBo55yV8PfDP7j8H+HcfQ93Jehmn+lx5r5A8LeRLt+Avcp3BOQO5Z5t+LvmxF+Ldw2/H0CtPuBx4E7gIfA/wDwWeBzcN3Bdwnuw3CN5xIQNPr7Y7Z3Oetn519HGPqEpsNeUUHz8SGP+fiIde4k2mAg5gvQaL4gWg1oaHeLru4pSdPGdSTLQzBo3M9YZhLxWvV6c+S8z33GY5+2kuYs1BNcFNwLcE+4MKfP1s7QFBRb9ml8V0MlpkG5T2Pexr+4T1N5A69XeYN4/pZxTXszPETMMNb0YOJ/3HPvJucHF4Wvg1+utfm0ZvF624XCr0Z5bXIf15Bou3gfocURpnvzr6Lw9SISfdJH0J7O6H9XsF/T7i6guvK6X+N24/WW8k7t04vbpzcbJ98KF8O4GTJqKI/VkwtKCyrwxOY2nsK0dsqI8txP63GwVnI5L5B/npgssJ7IvZhRF0NlnKZyfv2S/PNFGa0bqHOOw+aa5Tp8nvgWipnG+SSWFWdqq7yy6TjI4OT15CKFzxUTRKis+9HhZK+PnI304LPoueYetQF8L3v2lPmOmEP5/tVthfpC/RtjqYccN1p9ROrtxDQur2UstWqkCd7LY+k+uKfRVtVzuK2qfvmZR+PtJJzkx26W/C0FrJXL8cX91tpWMm68bKv7yL9MZCCmcYaCxwe30zbiWS4yuZ0KpZzm4NHPl+AoXV5Z+WxOa7gln/DLfHYR4cLHc6zKO13uJZ4lIh39LYDLwM9XNB8Gz+V00fZ2YdhK9on89WMOdWptRyDS4XY0xluVMd6obQfLsxOmsjId8eWzVF9u64+5rUfC1YcbCjcEjZ40V57TkWMyLzevsMBN00BtcyjVzXUUrzP3A12OS46Dq5EHX9RDPTi/K6gP0xxkmVcaxGrMNQ4h2gN3AE9jgtlkyj9qEVXBVwNZ+myeZU7fpOed+9Tr5F/vCJF7zvKCggqjrJfmqeEfyXcUgt5RGOFnb1TDv1X0PZ9jgep3i2i5/9HeUBXka++rzM+AxfP1MznwI257itsfcfX+plpOVr8LVZW5SwuwHBt7dc9zew3UerpBjf+Jshyh+nPjt5RGEHj4PB7xHPYJEHf76PeCnCGeJaIR+Cx7/IrZ8izi21RPd/hofplX4k+Ist5vkAl08bzpWQaai5hvANC4b4Dv71E3JqZ3PHOo/gPZj5aax+VBvM4xKqd+wkzIM2QfU173sR9PFBQnxse4y2gmXoIa+85WVCeN2K+IaarfcqfLpHw9z0mc5xlqhVu+2xnybq7mfQLLu4/8fiIee8tzGItxMdoa4WsPsi18ObAVrM4HBOMfn4ae78KM+bKM2iih1ndhTmARhffV9rCwH58CWjt+Pg+I1PZOO0O1M1ud8HcQEGH42/AHw83hOCH4uz7zqC6U/+4fYbmDibAXaGvhXoXrw/FfQOMdA9YwzwnT30cQFsbyeoN/AAowAdgPLonj38W4g+OsYf8yxu6EVrcebp0H/XU4lJvW4nJffS2+7N2yXCsmUz0OoTlrwi/cE5VpuieqWt4Tpc03Lst8fNk4pjg=
*/