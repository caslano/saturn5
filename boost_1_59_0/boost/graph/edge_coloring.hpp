//=======================================================================
// Copyright 2013 Maciej Piechotka
// Authors: Maciej Piechotka
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#ifndef BOOST_GRAPH_EDGE_COLORING_HPP
#define BOOST_GRAPH_EDGE_COLORING_HPP

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/properties.hpp>
#include <algorithm>
#include <limits>
#include <vector>

/* This algorithm is to find coloring of an edges

   Reference:

   Misra, J., & Gries, D. (1992). A constructive proof of Vizing's
   theorem. In Information Processing Letters.
*/

namespace boost
{
namespace detail
{
    template < typename Graph, typename ColorMap >
    bool is_free(const Graph& g, ColorMap color,
        typename boost::graph_traits< Graph >::vertex_descriptor u,
        typename boost::property_traits< ColorMap >::value_type free_color)
    {
        typedef typename boost::property_traits< ColorMap >::value_type color_t;
        if (free_color == (std::numeric_limits< color_t >::max)())
            return false;
        BGL_FORALL_OUTEDGES_T(u, e, g, Graph)
        {
            if (get(color, e) == free_color)
            {
                return false;
            }
        }
        return true;
    }

    template < typename Graph, typename ColorMap >
    std::vector< typename boost::graph_traits< Graph >::vertex_descriptor >
    maximal_fan(const Graph& g, ColorMap color,
        typename boost::graph_traits< Graph >::vertex_descriptor x,
        typename boost::graph_traits< Graph >::vertex_descriptor y)
    {
        typedef
            typename boost::graph_traits< Graph >::vertex_descriptor vertex_t;
        std::vector< vertex_t > fan;
        fan.push_back(y);
        bool extended;
        do
        {
            extended = false;
            BGL_FORALL_OUTEDGES_T(x, e, g, Graph)
            {
                vertex_t v = target(e, g);
                if (is_free(g, color, fan.back(), get(color, e))
                    && std::find(fan.begin(), fan.end(), v) == fan.end())
                {
                    fan.push_back(v);
                    extended = true;
                }
            }
        } while (extended);
        return fan;
    }
    template < typename Graph, typename ColorMap >
    typename boost::property_traits< ColorMap >::value_type find_free_color(
        const Graph& g, ColorMap color,
        typename boost::graph_traits< Graph >::vertex_descriptor u)
    {
        typename boost::property_traits< ColorMap >::value_type c = 0;
        while (!is_free(g, color, u, c))
            c++;
        return c;
    }

    template < typename Graph, typename ColorMap >
    void invert_cd_path(const Graph& g, ColorMap color,
        typename boost::graph_traits< Graph >::vertex_descriptor x,
        typename boost::graph_traits< Graph >::edge_descriptor eold,
        typename boost::property_traits< ColorMap >::value_type c,
        typename boost::property_traits< ColorMap >::value_type d)
    {
        put(color, eold, d);
        BGL_FORALL_OUTEDGES_T(x, e, g, Graph)
        {
            if (get(color, e) == d && e != eold)
            {
                invert_cd_path(g, color, target(e, g), e, d, c);
                return;
            }
        }
    }

    template < typename Graph, typename ColorMap >
    void invert_cd_path(const Graph& g, ColorMap color,
        typename boost::graph_traits< Graph >::vertex_descriptor x,
        typename boost::property_traits< ColorMap >::value_type c,
        typename boost::property_traits< ColorMap >::value_type d)
    {
        BGL_FORALL_OUTEDGES_T(x, e, g, Graph)
        {
            if (get(color, e) == d)
            {
                invert_cd_path(g, color, target(e, g), e, d, c);
                return;
            }
        }
    }

    template < typename Graph, typename ColorMap, typename ForwardIterator >
    void rotate_fan(const Graph& g, ColorMap color,
        typename boost::graph_traits< Graph >::vertex_descriptor x,
        ForwardIterator begin, ForwardIterator end)
    {
        typedef typename boost::graph_traits< Graph >::edge_descriptor edge_t;
        if (begin == end)
        {
            return;
        }
        edge_t previous = edge(x, *begin, g).first;
        for (begin++; begin != end; begin++)
        {
            edge_t current = edge(x, *begin, g).first;
            put(color, previous, get(color, current));
            previous = current;
        }
    }

    template < typename Graph, typename ColorMap > class find_free_in_fan
    {
    public:
        find_free_in_fan(const Graph& graph, const ColorMap color,
            typename boost::property_traits< ColorMap >::value_type d)
        : graph(graph), color(color), d(d)
        {
        }
        bool operator()(
            const typename boost::graph_traits< Graph >::vertex_descriptor u)
            const
        {
            return is_free(graph, color, u, d);
        }

    private:
        const Graph& graph;
        const ColorMap color;
        const typename boost::property_traits< ColorMap >::value_type d;
    };
}

template < typename Graph, typename ColorMap >
typename boost::property_traits< ColorMap >::value_type color_edge(
    const Graph& g, ColorMap color,
    typename boost::graph_traits< Graph >::edge_descriptor e)
{
    typedef typename boost::graph_traits< Graph >::vertex_descriptor vertex_t;
    typedef typename boost::property_traits< ColorMap >::value_type color_t;
    typedef typename std::vector< vertex_t >::iterator fan_iterator;
    using namespace detail;
    vertex_t x = source(e, g), y = target(e, g);
    std::vector< vertex_t > fan = maximal_fan(g, color, x, y);
    color_t c = find_free_color(g, color, x);
    color_t d = find_free_color(g, color, fan.back());
    invert_cd_path(g, color, x, c, d);
    fan_iterator w = std::find_if(fan.begin(), fan.end(),
        find_free_in_fan< Graph, ColorMap >(g, color, d));
    rotate_fan(g, color, x, fan.begin(), w + 1);
    put(color, edge(x, *w, g).first, d);
    return (std::max)(c, d);
}

template < typename Graph, typename ColorMap >
typename boost::property_traits< ColorMap >::value_type edge_coloring(
    const Graph& g, ColorMap color)
{
    typedef typename boost::property_traits< ColorMap >::value_type color_t;
    BGL_FORALL_EDGES_T(e, g, Graph)
    {
        put(color, e, (std::numeric_limits< color_t >::max)());
    }
    color_t colors = 0;
    BGL_FORALL_EDGES_T(e, g, Graph)
    {
        colors = (std::max)(colors, color_edge(g, color, e) + 1);
    }
    return colors;
}
}

#endif

/* edge_coloring.hpp
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
*/