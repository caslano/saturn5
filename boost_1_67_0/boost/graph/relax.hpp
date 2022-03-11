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
+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
*/