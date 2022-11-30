// Copyright 2010 The Trustees of Indiana University.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Jeremiah Willcock
//           Andrew Lumsdaine

#ifndef BOOST_GRAPH_LOOP_ERASED_RANDOM_WALK_HPP
#define BOOST_GRAPH_LOOP_ERASED_RANDOM_WALK_HPP

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/random.hpp>
#include <boost/next_prior.hpp>
#include <vector>
#include <boost/assert.hpp>

namespace boost
{

struct BOOST_SYMBOL_VISIBLE loop_erased_random_walk_stuck
: public std::exception
{
    virtual ~loop_erased_random_walk_stuck() throw() {}
    inline virtual const char* what() const throw()
    {
        return "Loop-erased random walk found a vertex with no out-edges";
    }
};

// Do a loop-erased random walk from vertex s to any vertex colored black (or
// actually any color other than white or gray) in the color map.  The color
// white is for vertices that are not part of the path, while gray is for
// those that are on the path (for cycle detection).  The vector path is used
// for temporary storage and as the result of the algorithm; while all
// elements of the path except the last have their colors set to gray upon
// return.  Vertex s must start off colored white.
//
// Useful references:
// http://everything2.com/title/loop-erased+random+walk
// Wikipedia page on "Loop-Erased Random Walk"

template < typename Graph, typename ColorMap, typename NextEdge >
void loop_erased_random_walk(const Graph& g,
    typename boost::graph_traits< Graph >::vertex_descriptor s,
    NextEdge next_edge, ColorMap color,
    std::vector< typename boost::graph_traits< Graph >::vertex_descriptor >&
        path)
{
    typedef typename boost::graph_traits< Graph >::vertex_descriptor
        vertex_descriptor;
    typedef
        typename boost::graph_traits< Graph >::edge_descriptor edge_descriptor;
    typedef typename boost::property_traits< ColorMap >::value_type color_t;
    typedef boost::color_traits< color_t > color_gen;

    BOOST_ASSERT(get(color, s) == color_gen::white());
    path.clear();
    path.push_back(s);
    put(color, s, color_gen::gray());
    while (true)
    {
        edge_descriptor e = next_edge(s, g);
        vertex_descriptor t = target(e, g);
        color_t t_color = get(color, t);
        if (t_color == color_gen::white())
        {
            path.push_back(t);
            put(color, t, color_gen::gray());
            s = t;
        }
        else if (t_color == color_gen::gray())
        {
            // Found a loop; delete from path from the first occurrence of t to
            // the end, coloring vertices white.
            typename std::vector< vertex_descriptor >::iterator it
                = std::find(path.begin(), path.end(), t);
            BOOST_ASSERT(it != path.end());
            ++it;
            for (typename std::vector< vertex_descriptor >::iterator j = it;
                 j != path.end(); ++j)
            {
                put(color, *j, color_gen::white());
            }
            path.erase(it, path.end());
            s = t;
        }
        else
        {
            // Done
            path.push_back(t);
            break;
        }
    }
}

template < typename Graph, typename Gen > class unweighted_random_out_edge_gen
{
    Gen& gen;

    typedef boost::graph_traits< Graph > gt;

public:
    unweighted_random_out_edge_gen(Gen& gen) : gen(gen) {}

    typename gt::edge_descriptor operator()(
        typename gt::vertex_descriptor src, const Graph& g) const
    {
        if (out_degree(src, g) == 0)
            throw loop_erased_random_walk_stuck();
        return boost::random_out_edge(g, src, gen);
    }
};

template < typename Graph, typename WeightMap, typename Gen >
class weighted_random_out_edge_gen
{
    WeightMap weight;
    Gen& gen;

    typedef boost::graph_traits< Graph > gt;

public:
    weighted_random_out_edge_gen(const WeightMap& weight, Gen& gen)
    : weight(weight), gen(gen)
    {
    }

    typename gt::edge_descriptor operator()(
        typename gt::vertex_descriptor src, const Graph& g) const
    {
        if (out_degree(src, g) == 0)
            throw loop_erased_random_walk_stuck();
        return boost::weighted_random_out_edge(g, src, weight, gen);
    }
};
}

#endif // BOOST_GRAPH_LOOP_ERASED_RANDOM_WALK_HPP

/* loop_erased_random_walk.hpp
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
*/