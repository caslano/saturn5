// (C) Copyright 2007-2009 Andrew Sutton
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0 (See accompanying file
// LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_DEGREE_CENTRALITY_HPP
#define BOOST_GRAPH_DEGREE_CENTRALITY_HPP

#include <boost/graph/graph_concepts.hpp>
#include <boost/concept/assert.hpp>

namespace boost
{

template < typename Graph > struct degree_centrality_measure
{
    typedef typename graph_traits< Graph >::degree_size_type degree_type;
    typedef typename graph_traits< Graph >::vertex_descriptor vertex_type;
};

template < typename Graph >
struct influence_measure : public degree_centrality_measure< Graph >
{
    typedef degree_centrality_measure< Graph > base_type;
    typedef typename base_type::degree_type degree_type;
    typedef typename base_type::vertex_type vertex_type;

    inline degree_type operator()(vertex_type v, const Graph& g)
    {
        BOOST_CONCEPT_ASSERT((IncidenceGraphConcept< Graph >));
        return out_degree(v, g);
    }
};

template < typename Graph >
inline influence_measure< Graph > measure_influence(const Graph&)
{
    return influence_measure< Graph >();
}

template < typename Graph >
struct prestige_measure : public degree_centrality_measure< Graph >
{
    typedef degree_centrality_measure< Graph > base_type;
    typedef typename base_type::degree_type degree_type;
    typedef typename base_type::vertex_type vertex_type;

    inline degree_type operator()(vertex_type v, const Graph& g)
    {
        BOOST_CONCEPT_ASSERT((BidirectionalGraphConcept< Graph >));
        return in_degree(v, g);
    }
};

template < typename Graph >
inline prestige_measure< Graph > measure_prestige(const Graph&)
{
    return prestige_measure< Graph >();
}

template < typename Graph, typename Vertex, typename Measure >
inline typename Measure::degree_type degree_centrality(
    const Graph& g, Vertex v, Measure measure)
{
    BOOST_CONCEPT_ASSERT((DegreeMeasureConcept< Measure, Graph >));
    return measure(v, g);
}

template < typename Graph, typename Vertex >
inline typename graph_traits< Graph >::degree_size_type degree_centrality(
    const Graph& g, Vertex v)
{
    return degree_centrality(g, v, measure_influence(g));
}

// These are alias functions, intended to provide a more expressive interface.

template < typename Graph, typename Vertex >
inline typename graph_traits< Graph >::degree_size_type influence(
    const Graph& g, Vertex v)
{
    return degree_centrality(g, v, measure_influence(g));
}

template < typename Graph, typename Vertex >
inline typename graph_traits< Graph >::degree_size_type prestige(
    const Graph& g, Vertex v)
{
    return degree_centrality(g, v, measure_prestige(g));
}

template < typename Graph, typename CentralityMap, typename Measure >
inline void all_degree_centralities(
    const Graph& g, CentralityMap cent, Measure measure)
{
    BOOST_CONCEPT_ASSERT((VertexListGraphConcept< Graph >));
    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
    typedef typename graph_traits< Graph >::vertex_iterator VertexIterator;
    BOOST_CONCEPT_ASSERT((WritablePropertyMapConcept< CentralityMap, Vertex >));
    typedef typename property_traits< CentralityMap >::value_type Centrality;

    VertexIterator i, end;
    for (boost::tie(i, end) = vertices(g); i != end; ++i)
    {
        Centrality c = degree_centrality(g, *i, measure);
        put(cent, *i, c);
    }
}

template < typename Graph, typename CentralityMap >
inline void all_degree_centralities(const Graph& g, CentralityMap cent)
{
    all_degree_centralities(g, cent, measure_influence(g));
}

// More helper functions for computing influence and prestige.
// I hate the names of these functions, but influence and prestige
// don't pluralize too well.

template < typename Graph, typename CentralityMap >
inline void all_influence_values(const Graph& g, CentralityMap cent)
{
    all_degree_centralities(g, cent, measure_influence(g));
}

template < typename Graph, typename CentralityMap >
inline void all_prestige_values(const Graph& g, CentralityMap cent)
{
    all_degree_centralities(g, cent, measure_prestige(g));
}

} /* namespace boost */

#endif

/* degree_centrality.hpp
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
*/