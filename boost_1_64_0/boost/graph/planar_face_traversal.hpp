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
vXblF+zKf1HpDFVu6mKs/2wXY/0gu/IIu/IYu/Isu/JxduWv2ZWvsivfa1d+yK78sl35j3blZcKN5b7hxvKmduWt7cr72ZUn25Xn25XPtCvfaFe+1a78c7vy03bl9+zKH9qVV+lqLK/V1Vje2a68u135CLvyMXblr9iVL7Mr32VXfrqrcX86b1f/oV19x27G8lrdjOX17cq725X3sisfY1e+oJtxeZbY1X/Prv4eu/LzduUiwthfo0i780Ok8fjeHGk8vt+PNB7fi7sb27/X3djerYexfcUexvZBUXbHY5Td8WhXnmVX7t/TOH7rnsbxF/c0jr+2p3H8CTHG9stjjO1vxRjbP44xtt/Qy7h8n/QyLt9nduU/2ZW/Fmcc//dxxvF9443jV483jv/nBGN7/97G9lm9je0n9Ta2f62v3fm3r9351678gl35/kS713eJxvE79TOOH9PPOH5hf7vrc39j+4YDjO3bDDC23zLIuHzHBxmX76Rd+R278tBk4/h9ko3jb0s2jr8n2Tj+iCHG/ucMMX53xV0htENOXOT9Um/Tw/Mfub0++aWF3b6+PyRjQGCJEI0DtPzr82qsaHho9MOXbq/bPWVd9XeEGGTS8rOLR824d7Pu0ZOLOldpcKnVfiEmyPq/f3nMqw3m7Rp6sdKjLfeCnuW35AInLX+i79KPPhoT0Lt47Yj3S+oNaMHfAWX9qmdSy2QO7jH1W/cZ2bXrxb7B52r9tfwdHaLuPmzT4uSSaxcPp5pSPxdilqOWX3ip37OvJ7/lMb3McZPf/Y27+UyK7Gf90qFxO51+urD3zTpPli+e9aYQtZ21/Enz+ma/0ezbjHe2Xe7x9rqJiULEPqPld41ODbiUeLeBe3aVkhdDH7D8q2S+w5sZNWtPvt864EGAT8X3U84JUVaO26FG+v0XBg4Ldhw3rMyka+knhWhdTsuvnLX088a7O4X7+Z/vF+b3wvtCnBda/rSNK05/fzgk5KXD8eMz5m+4LsTbct7yAmbfe6nX8v7T6/dd7d3c/TLv28v5eePd5Qe+PDbmwe98d1UIdvtzTyFMsp+bnWKqjA1aMG+ff9sF7iWP/8j7eXI5v/zdyaNP7r18d8Lc6pV2zBvgIkT7Klp+wIFJ8x7WStw7c3z3d2d8uO24EIVltfyPPcvvSWre/GB75+DWY6qF08dMWT8kZH3ClS9/9Y87+7sqcaurHBGio1zfMdXr1dhZafG7v0z4/awvZt+OEyJa7id+nmmRX/S6Pqp+4NLZkya8dY+/acn1ivn9pujvnrwTeeOt15Z5vB24Sohj1bT87S8vi5ly58CjQ7VSoh8+ip3C3zhdtfy2fw6qm3B/0swt3fr7X3edy98b1zto+V+9culop/SMNS/dmZiyveZmZ/YTOQ+PUzYMP1SlbpviPvvcPix+L1iIvXL5ne9W+nlUzPBB5zzqzs9+5SUv9mlZ/+CXiT9uznzm6pNFBV3O1dpxW4hbsv7gD3+3zvuM38buU64OynyQuEaIybL+2/0mJl53WbB+8qbyJcc3vHKI99bl8lcqODvZvaBkf9W3ssRb23w+EmKpnIfNa9Z3merk+LhTasu3Rv+h5RDq0w+7l/qbhBBBrM9LDubnhF3Fr4X5b6qtmK9g4j31cwdit/o5mTigfvYqw/vb6ufqZdhPVP8ldGZCDhVZ5oZRalze2swvj97oh76ozUd5nIp+OAcr4RKVXqrSlv4XXiu9/wDVfxXVfzXVf3XVf03Vfy3Zvzm9VKat/Xf8Y+n911H9B6n+66v+g1X/jVT/jWX/5vRSmZb9y21/U/W/U/Xvgm1V/02p54/N8BlsiTFaPZyLz+Eirb5Nf4U/lt5fB9U=
*/