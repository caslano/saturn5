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
gkBwQbDFyg9H/x+a6yUr64LQhJ1FYiDyXnoH3n0Q3bHWdNnRxk59qw+hZ7wstbOkjjzPokOyF2Sfy5kaR3824NDXWWJOjNRGbrVtjw2MyzK/R6eROV/G9YWjw9Ax3y5eZmm/Aq70foVp0s123wxzth20k/mdm/eAhKpkotfO71nMDemntOo+vnd/Mb9X75D5BEkvaTgc/TvadI5fpdw6g+YyPnViUQjQZLfM4MjiPrsIOsGyu4d95/BTxp74zc1miBTqK0ZcGOy+KAYt6ecKtDpY8cJVzU04ll0awmfPkdNCjt9RsNKn5VOv0PXX+Oynvyj9acs2/UnM3XmqdG+ebcZPZcbrrTgwu8tjVqL7D3B8GGaHaWZ/z/L/+TvUkvkeslVoWa7oHyAz/jyazS0NLTPf9cbGPxV/fsMnf7b7+f947vCLtJWGOqls1qjP1DsZMbP2VW5P6tGvMduxtLYyKadxYAJdL4/HaMOqprRWFY92mL4OH/033fEB1p6/5agq3amYvVXG3nuKclUZmNabHQqpg9BbavR2wF2uuqsC6h497J+9hGkB76AXCnV2bUGaQV2o1aubI7M3r14l+ePR05oPuPVu0/aOu/TWi9tTbj1xO+DWk/1RX3friX+DLr2w+PewW0/sDbn0ImLvMbee2BuGXvClPlUlN8xYZXjIr6ievXPnzmjHFm3vUJ7lNpHqnG1FWV1z6d0m/qn3OPQilr1Cl55lrxR6pfOgt8MKNziQp8LaTsxSx6HWBZH5UiNp+aU8NUkZPWmSvg49R/7VSl/iSp56vMfoWd+OtOWrwT9DT2vpdGwpUIPToO7g0dJ7CtTXZ0AdFws3/Js8J0+Nq52lxvmCKh9bJnY9maOGtf4MvyrxlRu1b1K+mhQdpSbhLKlJzaPi5eNz1fjLRSqvtlCtRHj78CxDWuAzOZd68nS/GnPQH9L+rNT+jMtV46JFalxNfrx8Qq6aECmAH/kquB6ydD2ir/3I86u8y4Wivms9/KK/HrXLjW9aoZoGf6dFwNoCNa2mNG75k6/C2Ju7H8/DdGfU2t3YHDW2I3fIj4/uyktyVcnVXJUXGYWJdJyjg6f0Hrh5WqF6WrRYjflBngqk8hHfgJhtxDP1HvHTrdbSEv4o2Fewr6JQaz/hzvbXhD3gb3OEfTlPDWxW6pd49qXDjoxC2PkIu1iHLWZFL0J9ZthuNcOGPwpuVMqEbftLd061b2KumthcNFgQzw+VTw2oqfDjFvhRdq5ElSDf85DvpbNxvgOeSe8V9y61b3qhmp7CEy1Q05Gf02vGDkn6R/NV6XjkG559p7Q7VEq3HstWMcoWyldilM43ec/QQtQfPO9keLaabpDfk1D+dHm01KOhLlGTDkKt44N3n464T4df0xNjh3zY61qOcMoRTjn0ypvHD5cNlcZ9ZT5VVo8y//QiNbn2rWqy705VPBwYKowXtOWHrToRzIX53AI13lehCoby4rltOWF/yDIL+dL16FbUo3WmHoX80F+MsKKLEGYVwqxU5XBvhWq79Y1BHWn2hybPylNjfd0qN57TZvzOgR9VBSjTn1TTfA8oZ5xCebo++XVdCvnG56nxr0PMBi235YV+VXiuVIXxXq/H8/BhpOGMfDXjaqEamxqD/Bwt+ofxPHZY0tet1pIOdhX8ULCvYN/hF943H+/6RpU/ZKWElUYMN3WnisPD03jWvU/8dqklby4jX1LIF+Th9Oaxw5LnyMswhMRH8eylO6PW7nT8a4vVjGakX9uYsFVnUDZTKJsb0EfHc4bunOrJCwpQNjahbLxATfI1q1FM+z1+yiOEO645Pz55Jn7D/3EH8+PafJ2WV2Voe5vzhnWqlr+oUL0=
*/