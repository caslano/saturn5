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