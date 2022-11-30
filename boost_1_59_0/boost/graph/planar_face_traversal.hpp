//=======================================================================
// Copyright (c) Aaron Windsor 2007
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef __PLANAR_FACE_TRAVERSAL_HPP__
#define __PLANAR_FACE_TRAVERSAL_HPP__

#include <vector>
#include <set>
#include <map>
#include <boost/next_prior.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>

namespace boost
{

struct planar_face_traversal_visitor
{
    void begin_traversal() {}

    void begin_face() {}

    template < typename Edge > void next_edge(Edge) {}

    template < typename Vertex > void next_vertex(Vertex) {}

    void end_face() {}

    void end_traversal() {}
};

template < typename Graph, typename PlanarEmbedding, typename Visitor,
    typename EdgeIndexMap >
void planar_face_traversal(const Graph& g, PlanarEmbedding embedding,
    Visitor& visitor, EdgeIndexMap em)
{
    typedef typename graph_traits< Graph >::vertex_descriptor vertex_t;
    typedef typename graph_traits< Graph >::edge_descriptor edge_t;
    typedef typename graph_traits< Graph >::vertex_iterator vertex_iterator_t;
    typedef typename graph_traits< Graph >::edge_iterator edge_iterator_t;
    typedef typename property_traits< PlanarEmbedding >::value_type
        embedding_value_t;
    typedef typename embedding_value_t::const_iterator embedding_iterator_t;

    typedef typename std::vector< std::set< vertex_t > >
        distinguished_edge_storage_t;
    typedef typename std::vector< std::map< vertex_t, edge_t > >
        distinguished_edge_to_edge_storage_t;

    typedef typename boost::iterator_property_map<
        typename distinguished_edge_storage_t::iterator, EdgeIndexMap >
        distinguished_edge_map_t;

    typedef typename boost::iterator_property_map<
        typename distinguished_edge_to_edge_storage_t::iterator, EdgeIndexMap >
        distinguished_edge_to_edge_map_t;

    distinguished_edge_storage_t visited_vector(num_edges(g));
    distinguished_edge_to_edge_storage_t next_edge_vector(num_edges(g));

    distinguished_edge_map_t visited(visited_vector.begin(), em);
    distinguished_edge_to_edge_map_t next_edge(next_edge_vector.begin(), em);

    vertex_iterator_t vi, vi_end;
    typename std::vector< edge_t >::iterator ei, ei_end;
    edge_iterator_t fi, fi_end;
    embedding_iterator_t pi, pi_begin, pi_end;

    visitor.begin_traversal();

    // Initialize the next_edge property map. This map is initialized from the
    // PlanarEmbedding so that get(next_edge, e)[v] is the edge that comes
    // after e in the clockwise embedding around vertex v.

    for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
    {
        vertex_t v(*vi);
        pi_begin = embedding[v].begin();
        pi_end = embedding[v].end();
        for (pi = pi_begin; pi != pi_end; ++pi)
        {
            edge_t e(*pi);
            std::map< vertex_t, edge_t > m = get(next_edge, e);
            m[v] = boost::next(pi) == pi_end ? *pi_begin : *boost::next(pi);
            put(next_edge, e, m);
        }
    }

    // Take a copy of the edges in the graph here, since we want to accomodate
    // face traversals that add edges to the graph (for triangulation, in
    // particular) and don't want to use invalidated edge iterators.
    // Also, while iterating over all edges in the graph, we single out
    // any self-loops, which need some special treatment in the face traversal.

    std::vector< edge_t > self_loops;
    std::vector< edge_t > edges_cache;
    std::vector< vertex_t > vertices_in_edge;

    for (boost::tie(fi, fi_end) = edges(g); fi != fi_end; ++fi)
    {
        edge_t e(*fi);
        edges_cache.push_back(e);
        if (source(e, g) == target(e, g))
            self_loops.push_back(e);
    }

    // Iterate over all edges in the graph
    ei_end = edges_cache.end();
    for (ei = edges_cache.begin(); ei != ei_end; ++ei)
    {

        edge_t e(*ei);
        vertices_in_edge.clear();
        vertices_in_edge.push_back(source(e, g));
        vertices_in_edge.push_back(target(e, g));

        typename std::vector< vertex_t >::iterator vi, vi_end;
        vi_end = vertices_in_edge.end();

        // Iterate over both vertices in the current edge
        for (vi = vertices_in_edge.begin(); vi != vi_end; ++vi)
        {

            vertex_t v(*vi);
            std::set< vertex_t > e_visited = get(visited, e);
            typename std::set< vertex_t >::iterator e_visited_found
                = e_visited.find(v);

            if (e_visited_found == e_visited.end())
                visitor.begin_face();

            while (e_visited.find(v) == e_visited.end())
            {
                visitor.next_vertex(v);
                visitor.next_edge(e);
                e_visited.insert(v);
                put(visited, e, e_visited);
                v = source(e, g) == v ? target(e, g) : source(e, g);
                e = get(next_edge, e)[v];
                e_visited = get(visited, e);
            }

            if (e_visited_found == e_visited.end())
                visitor.end_face();
        }
    }

    // Iterate over all self-loops, visiting them once separately
    // (they've already been visited once, this visitation is for
    // the "inside" of the self-loop)

    ei_end = self_loops.end();
    for (ei = self_loops.begin(); ei != ei_end; ++ei)
    {
        visitor.begin_face();
        visitor.next_edge(*ei);
        visitor.next_vertex(source(*ei, g));
        visitor.end_face();
    }

    visitor.end_traversal();
}

template < typename Graph, typename PlanarEmbedding, typename Visitor >
inline void planar_face_traversal(
    const Graph& g, PlanarEmbedding embedding, Visitor& visitor)
{
    planar_face_traversal(g, embedding, visitor, get(edge_index, g));
}

} // namespace boost

#endif //__PLANAR_FACE_TRAVERSAL_HPP__

/* planar_face_traversal.hpp
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
*/