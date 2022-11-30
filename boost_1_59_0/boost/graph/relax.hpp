//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek,
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#ifndef BOOST_GRAPH_RELAX_HPP
#define BOOST_GRAPH_RELAX_HPP

#include <functional>
#include <boost/limits.hpp> // for numeric limits
#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>

namespace boost
{

// The following version of the plus functor prevents
// problems due to overflow at positive infinity.

template < class T > struct closed_plus
{
    const T inf;

    closed_plus() : inf((std::numeric_limits< T >::max)()) {}
    closed_plus(T inf) : inf(inf) {}

    T operator()(const T& a, const T& b) const
    {
        using namespace std;
        if (a == inf)
            return inf;
        if (b == inf)
            return inf;
        return a + b;
    }
};

template < class Graph, class WeightMap, class PredecessorMap,
    class DistanceMap, class BinaryFunction, class BinaryPredicate >
bool relax(typename graph_traits< Graph >::edge_descriptor e, const Graph& g,
    const WeightMap& w, PredecessorMap& p, DistanceMap& d,
    const BinaryFunction& combine, const BinaryPredicate& compare)
{
    typedef typename graph_traits< Graph >::directed_category DirCat;
    bool is_undirected = is_same< DirCat, undirected_tag >::value;
    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
    Vertex u = source(e, g), v = target(e, g);
    typedef typename property_traits< DistanceMap >::value_type D;
    typedef typename property_traits< WeightMap >::value_type W;
    const D d_u = get(d, u);
    const D d_v = get(d, v);
    const W& w_e = get(w, e);

    // The seemingly redundant comparisons after the distance puts are to
    // ensure that extra floating-point precision in x87 registers does not
    // lead to relax() returning true when the distance did not actually
    // change.
    if (compare(combine(d_u, w_e), d_v))
    {
        put(d, v, combine(d_u, w_e));
        if (compare(get(d, v), d_v))
        {
            put(p, v, u);
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (is_undirected && compare(combine(d_v, w_e), d_u))
    {
        put(d, u, combine(d_v, w_e));
        if (compare(get(d, u), d_u))
        {
            put(p, u, v);
            return true;
        }
        else
        {
            return false;
        }
    }
    else
        return false;
}

template < class Graph, class WeightMap, class PredecessorMap,
    class DistanceMap, class BinaryFunction, class BinaryPredicate >
bool relax_target(typename graph_traits< Graph >::edge_descriptor e,
    const Graph& g, const WeightMap& w, PredecessorMap& p, DistanceMap& d,
    const BinaryFunction& combine, const BinaryPredicate& compare)
{
    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
    typedef typename property_traits< DistanceMap >::value_type D;
    typedef typename property_traits< WeightMap >::value_type W;
    const Vertex u = source(e, g);
    const Vertex v = target(e, g);
    const D d_u = get(d, u);
    const D d_v = get(d, v);
    const W& w_e = get(w, e);

    // The seemingly redundant comparisons after the distance puts are to
    // ensure that extra floating-point precision in x87 registers does not
    // lead to relax() returning true when the distance did not actually
    // change.
    if (compare(combine(d_u, w_e), d_v))
    {
        put(d, v, combine(d_u, w_e));
        if (compare(get(d, v), d_v))
        {
            put(p, v, u);
            return true;
        }
    }
    return false;
}

template < class Graph, class WeightMap, class PredecessorMap,
    class DistanceMap >
bool relax(typename graph_traits< Graph >::edge_descriptor e, const Graph& g,
    WeightMap w, PredecessorMap p, DistanceMap d)
{
    typedef typename property_traits< DistanceMap >::value_type D;
    typedef closed_plus< D > Combine;
    typedef std::less< D > Compare;
    return relax(e, g, w, p, d, Combine(), Compare());
}

} // namespace boost

#endif /* BOOST_GRAPH_RELAX_HPP */

/* relax.hpp
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
*/