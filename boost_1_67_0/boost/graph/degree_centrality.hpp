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