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
USfKzRPc32XFy1Z54+vH4BzwK/c3+T4/1LZqnbrarAv668M7R3HufqLPuzxrLQs1qq5Zvzm4s28mVpXOf5k7+meygwt0xpque7zPORXK4aX/TbbZpboVTwy4PU0XGNd1wijedb+EWQl5tVrr1QTp0CU/NJKEp5it3+qOkB8IrIDVn1ejan28rqVxvi4OeouiutRoNKnVSi03rF8/brdW0MR0Zf7qCz4vWKZZVJ/MYThdcf4SN/9+4WPt0y99rMvA/QbrqOh8uVeXFacsuXXlQRdLYXHx04kFRa7vd8sv198e+SVaaRBfkl9uzO+RX2buJ2DSOnl2u+jc0blSp+mevKBIu2iR0akulz5ei74NYn+t9/FwoufWqxn3CUOre85G9SDIW2ydm1RQlqcjMMH5RXmu1m8RjK8TtS5O8FWq1oq1K+FQasQen/ieqL/YGhOprFDt8WN7dFhj4rncmZMihveE1lnllerTwfIEl+2Ek4cm6986WXTpOVyno3DWCl2mx4YWD46xw2W7UMeO1uKrjPhl1mf9qLWINzVrr0W87nKsRRRJfJ3JOrdcnZJkklXPMqTZ+aNjdBRhx53K9Z8hDabwFEVDzR4dbp69PJSahfmVOjZHO+8QVLK8JDCHc2OS1jNtcTNIv8iZb5Xw/hxON4Qy4PJm238W5MVEOtfZTyTj094Ar5sG/YCsdcBj2+p43wXnlY4GXZaFC2TsPMId5OpxF86b2bgN83NCqRVOhbes0m55oOb6z45WqrfDT5rSMy/8nFE9p+ffWhr1ZJxqcdJgWelqWajXebDdx6yHNDnWqrAyCV5etLrA3VNcX9NQzUh0s/+EzjfKlhhaF1mayqZmPRt/nsVK3tWu2+C4/pzhw3n3JVsTbapv1HnO1As5vy3gb3xXV1t+yT+Z5Trf59iVIFsnly2Nylqyr6HVvdxnpCmUMRXO3V7sz6J157s31zfILjdX2aJedXgcytqPTvqnhWM1VofVmTOvpWTZ5aMmyWJMe30b5Zc+K1DyqTzqJji7wv/dKjXh1305OB8gW7ebFzgvu8jp0VkD0I+qiwOMLmgy2peS4pQuJmOa9ApXiz4BJHN4emTBXnVd9h4NMhIwr6d5JMjXn+vRqj/I0w6s1OMJHZfoFjN/3a1dLtnaWtNS3qRryp/dZ/U2T28E9EDQP7P9VCwC7UcuYxjv3E+ON3KB8UYuae7utvXOy5S6btTeJ2cr11RWzKg8zS2t0l8bjq2zKsNitOcBRm8KUv9ICjAFDrPHYorUO0HsBE0lBn0xO10nwwYGY8JmBlhtfOlmoEVFdbx0jLzFUMntn5jWnigzZyhta1hD/7DBHtfpQzaOh0qVG41v96wZxTkrmmttVrcW0ag7ibDK1m0M6u70dTo0G2s4fqHuGK1RV4VHibitGP12mXA6dfR7eUoPWtX5um8I9wwHhlNbJ4pOcp0oHwq14sG2f5w90xeowTn+U2GV+qiMDnSYtUU/zNqdzD6o6rRSxnc13i+ztp8nTHAMdDLYb1Sc+nRS6L2l1linx19LyC8sLZfdp6eukRE0K2S3xdYy1zZ+9Kym2mO3YrEfV9mhMMV2Ji2lru1Shc16/mWakS2l6gLnF+khwyqZHv2sZlrMnuVTaCtEV6vbitjrfbTb14xau9BjNcnvZ5nl1bPB7ITtm9Iyat9hq7ui3SKHeZprznFTsCXEOQXsUHtVXI95RalKNa/nYmTByalTJT4j0PXxYy7XzAyInhYSp6pyFD9f1moaN8huMUdDXwml1sDJ+h1Utf28nhyMelxLtElWhr3NwqopxOtBpSx212+Q3tnXhacLVF1Ap9sYPCwPhlBSuL7aOZH4Uc1K5Jg=
*/