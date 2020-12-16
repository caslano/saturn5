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
johj10ckSzW40rwZmYzLUBzG6WTJUTeOza6bLFVHx7Fno5OlczG4nsUmS2lxxezxuBbS6XrFbHz8Sunz+j1Zmwa3S6817MnCEjZIexv1hI+8TdKqxj3Z643XS9Oa9mR7m26R0pv1ZLc02yS1atGTFbVYIp1v2S0otX127N2DurNTgxazvPR0di3fz/rKUPm8V0dFsjnSHumo+TbrHKlp4PMsKChGah+81nzGfoCdCv2K/S1sKBsYfsk0JaoZm8D3ii+hffEfRoexrewBeDiJgS/BROtEtsq6nbUK6GtZF2JmW0NasrdCmkj17OVsp32teQzslA3PTpsjQk0PRtWX3qnTnIXUDcF+nOXSX+BzKJXvqd3gIP8p0J5vvd56A4sIaM1KAxpIHwTmm/vaJrHHbdkszf6SaXh4kRRP9THmecHa17bQGuVk91ml+j33q3MVn3Ry27ghVtWRfZ/MytN/b+ZcOt0jkE+qmrjafVdWIn2YJGvbZRHbR/cTjHxZ4t6C+/Rr3619N0V2LpTSIUvt2oHrfaaTpXLZPk3WpRuXOXSyzlzWWyfryGWddDL1GN/ZNVkKl32uyTqrx3g5XJN15b4JMY9HsvzZeaSzjpdfXFKOmy3FN9e5OOEHDT60FNlFyLZEcNlc8kdGvqngbwgyZ79VCeCvXyJj1SMkZmLor+j3FaVz88uyphaWcx/oVSh/GeXV/CNFIV9/5NszXM4HR58dUknWJx7PpCcYM8syppQ/AHqJVD75I8kpz8lSXIYypfxJwo+a5mMphpd/ksrPpQNwv2vwreTmXDooeQYhDxPH4ucAeTrkaSTP0+Tcx+lmXhbOXZzbYOhXqufWvjMdt9ri5ripTJz3AfW8O5AdyI9SMekrvpVwPPKf9APJhGccyj8Ex6tSj5fakXjLgIx9iDL1diF/xVQW+fJZS2VpPn5ieFmHBG8ojGl1fEqpI8R0/uSvZz2VofnxwbmSn56LJNf58OHlZ8rly+UIe9L5ku+ZS5SHtKn8NMh+VMoXpcSjjKEow2Fsc7w9pMSJYwsfNWHch+z+KFleQvUYhjLOyGXQ97aycFLcV6vST1hRrBK/O97Zd+wLiOt9x8bUd/Yd2xRxvS++vyOuzx/VwDn/NMT1+csQ1+e/7h/s3Ql0TXcewPH/y56ISIKI1FaEEEsssdUWhIRIIgliTWRBCIkkFKOa2veqUmqN1toqKdqhtURpLdU2aqkqbQxVpjp2o61lvvf//u++d9/I7DPnzDl1zs8n//3e/91eXt69r6qxfUpVY/v3qxrbH6xqbO9V3di+aXVj++nVje0XVTe2f7mGsf32Gsb2Ls8a25d/1tj+u2eN7R1qGtv3qWlsn1rT2L5xLWP7uFrG9htqGdvvqGVs/2JtY/s3ahvb369tbO8YaGz/RaCx/e1AY/uudYzt4+sY21eva2zfqa6x/Wt1je3frGtsnxVkbL8oyNj+SpCx/Z0gY/v99eyefVzP2L5FfWP7zvWN7csF2+0/wcb2M4KN7V8NNrZPamBsP6WBsf2ZBsb2lxoY229raGz/JWnb9nUaGds3a2Rs/6SRsX3Nxsb24xob209tbGwfE2JsnxNibP9JiLH9yRBj+zVN7M4fTezOH03tzh9Nje27NTO2H9bM2P6DZsb2h5sZ299qbnf+CTW23x9qbH881Nj+VAtj+3stjO3XtjS239rS2P7tVnbbr5Wx/Yutje3ntTa2n9vG7vxD2rZ90nPG9pnPGduPbGt3/LQ1tm/bztg+sp2xfff2dtu/vbF99Q7G9g1I27YP7mh3/upobP+ko7G9Z5ixvXMnY/vATsb2hzsZ25/qZHf+6Gx8tvfLKn1C1X/Nrvx9u/I=
*/