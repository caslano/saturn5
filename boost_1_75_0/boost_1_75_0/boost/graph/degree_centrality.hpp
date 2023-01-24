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
cFUetocoK6qZRGMQRrWVT2KXKkZJS00rlQdpan/3gIaE7yKP2KhhWWgcQFX1JbnUfsLPvc3cMrZ/8UzYIwpSMfP85Q1Ui2C5gud13Z8FVWwUf0PRL5aYV9hSav+sLGIKjqaFMD8WA87+hk1pX6/BJRzlQyUphptibMTCGtIoAUnzcvyLGEsYDKGKzv/gvDef/IaSfTTNTTBemKrZOLAnoA39Ii7by9HuMzXBecpHu5u5ZKTg8lHJe6ROYWANOCRTfJFvHh3IDBe8uj8T7d39ioj3PDC/GPcOHk6CFXlO7V1k/qNKfRFL9/Ui5l/s7nTwh+rDv6t7fRkW0ZOdfdTN2YL+RfT3bjZb33abNzh6UVXKeq0t/8ngnB0DyNLFI7V37v/+quM4uwBOiN5xKe/15Tibmd+hwxsctah2s4k/WJ9yLf93MHnZ802t33xYTzR16gJjYUZ9DHIXVBhknScXlD8v7NrsTLnd9xEENH/2s6lbLk4FwQs/rzPncLB9WeKc+eIc+eLs3bfJbUGSQucT+W5cZxtTD2/gTI+Emp99IAQkJX5rszruV2rKXwood1pNet5X0xHTi0n4BCUD3dCPSZycDGB0nRQ0F7akopsCHF6icVg0nAOowPsqLJqallIwZ+ywLWtfZOG822zhZfbX0CuCu3iN83VyIZu9zAAChIMoW+C4THD/ijZcL4uBM1ng0pndyvtVelyN7tSe
*/