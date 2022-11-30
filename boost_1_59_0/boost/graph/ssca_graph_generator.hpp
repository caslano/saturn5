// Copyright 2004, 2005 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Nick Edmonds
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_SSCA_GENERATOR_HPP
#define BOOST_GRAPH_SSCA_GENERATOR_HPP

#include <iterator>
#include <utility>
#include <vector>
#include <queue>
#include <boost/config.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/type_traits/is_same.hpp>

enum Direction
{
    FORWARD = 1,
    BACKWARD = 2,
    BOTH = FORWARD | BACKWARD
};

namespace boost
{

// This generator generates graphs according to the method specified
// in SSCA 1.1.  Current versions of SSCA use R-MAT graphs

template < typename RandomGenerator, typename Graph > class ssca_iterator
{
    typedef typename graph_traits< Graph >::directed_category directed_category;
    typedef
        typename graph_traits< Graph >::vertices_size_type vertices_size_type;

public:
    typedef std::input_iterator_tag iterator_category;
    typedef std::pair< vertices_size_type, vertices_size_type > value_type;
    typedef const value_type& reference;
    typedef const value_type* pointer;
    typedef void difference_type;

    // No argument constructor, set to terminating condition
    ssca_iterator() : gen(), verticesRemaining(0) {}

    // Initialize for edge generation
    ssca_iterator(RandomGenerator& gen, vertices_size_type totVertices,
        vertices_size_type maxCliqueSize, double probUnidirectional,
        int maxParallelEdges, double probIntercliqueEdges)
    : gen(&gen)
    , totVertices(totVertices)
    , maxCliqueSize(maxCliqueSize)
    , probUnidirectional(probUnidirectional)
    , maxParallelEdges(maxParallelEdges)
    , probIntercliqueEdges(probIntercliqueEdges)
    , currentClique(0)
    , verticesRemaining(totVertices)
    {
        cliqueNum = std::vector< int >(totVertices, -1);
        current = std::make_pair(0, 0);
    }

    reference operator*() const { return current; }
    pointer operator->() const { return &current; }

    ssca_iterator& operator++()
    {
        BOOST_USING_STD_MIN();
        while (values.empty() && verticesRemaining > 0)
        { // If there are no values left, generate a new clique
            uniform_int< vertices_size_type > clique_size(1, maxCliqueSize);
            uniform_int< vertices_size_type > rand_vertex(0, totVertices - 1);
            uniform_int< int > num_parallel_edges(1, maxParallelEdges);
            uniform_int< short > direction(0, 1);
            uniform_01< RandomGenerator > prob(*gen);
            std::vector< vertices_size_type > cliqueVertices;

            cliqueVertices.clear();
            vertices_size_type size = min BOOST_PREVENT_MACRO_SUBSTITUTION(
                clique_size(*gen), verticesRemaining);
            while (cliqueVertices.size() < size)
            {
                vertices_size_type v = rand_vertex(*gen);
                if (cliqueNum[v] == -1)
                {
                    cliqueNum[v] = currentClique;
                    cliqueVertices.push_back(v);
                    verticesRemaining--;
                }
            } // Nick: This is inefficient when only a few vertices remain...
              //       I should probably just select the remaining vertices
              //       in order when only a certain fraction remain.

            typename std::vector< vertices_size_type >::iterator first, second;
            for (first = cliqueVertices.begin(); first != cliqueVertices.end();
                 ++first)
                for (second = first + 1; second != cliqueVertices.end();
                     ++second)
                {
                    Direction d;
                    int edges;

                    d = prob() < probUnidirectional
                        ? (direction(*gen) == 0 ? FORWARD : BACKWARD)
                        : BOTH;

                    if (d & FORWARD)
                    {
                        edges = num_parallel_edges(*gen);
                        for (int i = 0; i < edges; ++i)
                            values.push(std::make_pair(*first, *second));
                    }

                    if (d & BACKWARD)
                    {
                        edges = num_parallel_edges(*gen);
                        for (int i = 0; i < edges; ++i)
                            values.push(std::make_pair(*second, *first));
                    }
                }

            if (verticesRemaining == 0)
            {
                // Generate interclique edges
                for (vertices_size_type i = 0; i < totVertices; ++i)
                {
                    double p = probIntercliqueEdges;
                    for (vertices_size_type d = 2; d < totVertices / 2;
                         d *= 2, p /= 2)
                    {
                        vertices_size_type j = (i + d) % totVertices;
                        if (cliqueNum[j] != cliqueNum[i] && prob() < p)
                        {
                            int edges = num_parallel_edges(*gen);
                            for (int i = 0; i < edges; ++i)
                                values.push(std::make_pair(i, j));
                        }
                    }
                }
            }

            currentClique++;
        }

        if (!values.empty())
        { // If we're not done return a value
            current = values.front();
            values.pop();
        }

        return *this;
    }

    ssca_iterator operator++(int)
    {
        ssca_iterator temp(*this);
        ++(*this);
        return temp;
    }

    bool operator==(const ssca_iterator& other) const
    {
        return verticesRemaining == other.verticesRemaining && values.empty()
            && other.values.empty();
    }

    bool operator!=(const ssca_iterator& other) const
    {
        return !(*this == other);
    }

private:
    // Parameters
    RandomGenerator* gen;
    vertices_size_type totVertices;
    vertices_size_type maxCliqueSize;
    double probUnidirectional;
    int maxParallelEdges;
    double probIntercliqueEdges;

    // Internal data structures
    std::vector< int > cliqueNum;
    std::queue< value_type > values;
    int currentClique;
    vertices_size_type verticesRemaining;
    value_type current;
};

} // end namespace boost

#endif // BOOST_GRAPH_SSCA_GENERATOR_HPP

/* ssca_graph_generator.hpp
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
*/