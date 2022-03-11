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