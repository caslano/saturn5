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