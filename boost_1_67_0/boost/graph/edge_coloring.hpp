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