//=======================================================================
// Copyright (c) Aaron Windsor 2007
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef __PLANAR_CANONICAL_ORDERING_HPP__
#define __PLANAR_CANONICAL_ORDERING_HPP__

#include <vector>
#include <list>
#include <boost/config.hpp>
#include <boost/next_prior.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>

namespace boost
{

namespace detail
{
    enum planar_canonical_ordering_state
    {
        PCO_PROCESSED,
        PCO_UNPROCESSED,
        PCO_ONE_NEIGHBOR_PROCESSED,
        PCO_READY_TO_BE_PROCESSED
    };
}

template < typename Graph, typename PlanarEmbedding, typename OutputIterator,
    typename VertexIndexMap >
void planar_canonical_ordering(const Graph& g, PlanarEmbedding embedding,
    OutputIterator ordering, VertexIndexMap vm)
{

    typedef typename graph_traits< Graph >::vertex_descriptor vertex_t;
    typedef typename graph_traits< Graph >::edge_descriptor edge_t;
    typedef
        typename graph_traits< Graph >::adjacency_iterator adjacency_iterator_t;
    typedef typename property_traits< PlanarEmbedding >::value_type
        embedding_value_t;
    typedef typename embedding_value_t::const_iterator embedding_iterator_t;
    typedef iterator_property_map< typename std::vector< vertex_t >::iterator,
        VertexIndexMap >
        vertex_to_vertex_map_t;
    typedef iterator_property_map<
        typename std::vector< std::size_t >::iterator, VertexIndexMap >
        vertex_to_size_t_map_t;

    std::vector< vertex_t > processed_neighbor_vector(num_vertices(g));
    vertex_to_vertex_map_t processed_neighbor(
        processed_neighbor_vector.begin(), vm);

    std::vector< std::size_t > status_vector(
        num_vertices(g), detail::PCO_UNPROCESSED);
    vertex_to_size_t_map_t status(status_vector.begin(), vm);

    std::list< vertex_t > ready_to_be_processed;

    vertex_t first_vertex = *vertices(g).first;
    vertex_t second_vertex = first_vertex;
    adjacency_iterator_t ai, ai_end;
    for (boost::tie(ai, ai_end) = adjacent_vertices(first_vertex, g);
         ai != ai_end; ++ai)
    {
        if (*ai == first_vertex)
            continue;
        second_vertex = *ai;
        break;
    }

    ready_to_be_processed.push_back(first_vertex);
    status[first_vertex] = detail::PCO_READY_TO_BE_PROCESSED;
    ready_to_be_processed.push_back(second_vertex);
    status[second_vertex] = detail::PCO_READY_TO_BE_PROCESSED;

    while (!ready_to_be_processed.empty())
    {
        vertex_t u = ready_to_be_processed.front();
        ready_to_be_processed.pop_front();

        if (status[u] != detail::PCO_READY_TO_BE_PROCESSED
            && u != second_vertex)
            continue;

        embedding_iterator_t ei, ei_start, ei_end;
        embedding_iterator_t next_edge_itr, prior_edge_itr;

        ei_start = embedding[u].begin();
        ei_end = embedding[u].end();
        prior_edge_itr = prior(ei_end);
        while (source(*prior_edge_itr, g) == target(*prior_edge_itr, g))
            prior_edge_itr = prior(prior_edge_itr);

        for (ei = ei_start; ei != ei_end; ++ei)
        {

            edge_t e(*ei); // e = (u,v)
            next_edge_itr
                = boost::next(ei) == ei_end ? ei_start : boost::next(ei);
            vertex_t v = source(e, g) == u ? target(e, g) : source(e, g);

            vertex_t prior_vertex = source(*prior_edge_itr, g) == u
                ? target(*prior_edge_itr, g)
                : source(*prior_edge_itr, g);
            vertex_t next_vertex = source(*next_edge_itr, g) == u
                ? target(*next_edge_itr, g)
                : source(*next_edge_itr, g);

            // Need prior_vertex, u, v, and next_vertex to all be
            // distinct. This is possible, since the input graph is
            // triangulated. It'll be true all the time in a simple
            // graph, but loops and parallel edges cause some complications.
            if (prior_vertex == v || prior_vertex == u)
            {
                prior_edge_itr = ei;
                continue;
            }

            // Skip any self-loops
            if (u == v)
                continue;

            // Move next_edge_itr (and next_vertex) forwards
            // past any loops or parallel edges
            while (next_vertex == v || next_vertex == u)
            {
                next_edge_itr = boost::next(next_edge_itr) == ei_end
                    ? ei_start
                    : boost::next(next_edge_itr);
                next_vertex = source(*next_edge_itr, g) == u
                    ? target(*next_edge_itr, g)
                    : source(*next_edge_itr, g);
            }

            if (status[v] == detail::PCO_UNPROCESSED)
            {
                status[v] = detail::PCO_ONE_NEIGHBOR_PROCESSED;
                processed_neighbor[v] = u;
            }
            else if (status[v] == detail::PCO_ONE_NEIGHBOR_PROCESSED)
            {
                vertex_t x = processed_neighbor[v];
                // are edges (v,u) and (v,x) adjacent in the planar
                // embedding? if so, set status[v] = 1. otherwise, set
                // status[v] = 2.

                if ((next_vertex == x
                        && !(first_vertex == u && second_vertex == x))
                    || (prior_vertex == x
                        && !(first_vertex == x && second_vertex == u)))
                {
                    status[v] = detail::PCO_READY_TO_BE_PROCESSED;
                }
                else
                {
                    status[v] = detail::PCO_READY_TO_BE_PROCESSED + 1;
                }
            }
            else if (status[v] > detail::PCO_ONE_NEIGHBOR_PROCESSED)
            {
                // check the two edges before and after (v,u) in the planar
                // embedding, and update status[v] accordingly

                bool processed_before = false;
                if (status[prior_vertex] == detail::PCO_PROCESSED)
                    processed_before = true;

                bool processed_after = false;
                if (status[next_vertex] == detail::PCO_PROCESSED)
                    processed_after = true;

                if (!processed_before && !processed_after)
                    ++status[v];

                else if (processed_before && processed_after)
                    --status[v];
            }

            if (status[v] == detail::PCO_READY_TO_BE_PROCESSED)
                ready_to_be_processed.push_back(v);

            prior_edge_itr = ei;
        }

        status[u] = detail::PCO_PROCESSED;
        *ordering = u;
        ++ordering;
    }
}

template < typename Graph, typename PlanarEmbedding, typename OutputIterator >
void planar_canonical_ordering(
    const Graph& g, PlanarEmbedding embedding, OutputIterator ordering)
{
    planar_canonical_ordering(g, embedding, ordering, get(vertex_index, g));
}

} // namespace boost

#endif //__PLANAR_CANONICAL_ORDERING_HPP__

/* planar_canonical_ordering.hpp
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
*/