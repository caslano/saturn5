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