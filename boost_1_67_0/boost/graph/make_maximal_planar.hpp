//=======================================================================
// Copyright 2007 Aaron Windsor
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#ifndef __MAKE_MAXIMAL_PLANAR_HPP__
#define __MAKE_MAXIMAL_PLANAR_HPP__

#include <boost/config.hpp>
#include <boost/tuple/tuple.hpp> //for tie
#include <boost/graph/biconnected_components.hpp>
#include <boost/property_map/property_map.hpp>
#include <vector>
#include <iterator>
#include <algorithm>

#include <boost/graph/planar_face_traversal.hpp>
#include <boost/graph/planar_detail/add_edge_visitors.hpp>

namespace boost
{

template < typename Graph, typename VertexIndexMap, typename AddEdgeVisitor >
struct triangulation_visitor : public planar_face_traversal_visitor
{

    typedef typename graph_traits< Graph >::vertex_descriptor vertex_t;
    typedef typename graph_traits< Graph >::edge_descriptor edge_t;
    typedef typename graph_traits< Graph >::vertices_size_type v_size_t;
    typedef typename graph_traits< Graph >::degree_size_type degree_size_t;
    typedef typename graph_traits< Graph >::edge_iterator edge_iterator_t;
    typedef typename graph_traits< Graph >::vertex_iterator vertex_iterator_t;
    typedef
        typename graph_traits< Graph >::adjacency_iterator adjacency_iterator_t;
    typedef typename std::vector< vertex_t > vertex_vector_t;
    typedef typename std::vector< v_size_t > v_size_vector_t;
    typedef typename std::vector< degree_size_t > degree_size_vector_t;
    typedef iterator_property_map< typename v_size_vector_t::iterator,
        VertexIndexMap >
        vertex_to_v_size_map_t;
    typedef iterator_property_map< typename degree_size_vector_t::iterator,
        VertexIndexMap >
        vertex_to_degree_size_map_t;
    typedef typename vertex_vector_t::iterator face_iterator;

    triangulation_visitor(Graph& arg_g, VertexIndexMap arg_vm,
        AddEdgeVisitor arg_add_edge_visitor)
    : g(arg_g)
    , vm(arg_vm)
    , add_edge_visitor(arg_add_edge_visitor)
    , timestamp(0)
    , marked_vector(num_vertices(g), timestamp)
    , degree_vector(num_vertices(g), 0)
    , marked(marked_vector.begin(), vm)
    , degree(degree_vector.begin(), vm)
    {
        vertex_iterator_t vi, vi_end;
        for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
            put(degree, *vi, out_degree(*vi, g));
    }

    template < typename Vertex > void next_vertex(Vertex v)
    {
        // Self-loops will appear as consecutive vertices in the list of
        // vertices on a face. We want to skip these.
        if (!vertices_on_face.empty()
            && (vertices_on_face.back() == v || vertices_on_face.front() == v))
            return;

        vertices_on_face.push_back(v);
    }

    void end_face()
    {
        ++timestamp;

        if (vertices_on_face.size() <= 3)
        {
            // At most three vertices on this face - don't need to triangulate
            vertices_on_face.clear();
            return;
        }

        // Find vertex on face of minimum degree
        degree_size_t min_degree = num_vertices(g);
        typename vertex_vector_t::iterator min_degree_vertex_itr;
        face_iterator fi_end = vertices_on_face.end();
        for (face_iterator fi = vertices_on_face.begin(); fi != fi_end; ++fi)
        {
            degree_size_t deg = get(degree, *fi);
            if (deg < min_degree)
            {
                min_degree_vertex_itr = fi;
                min_degree = deg;
            }
        }

        // To simplify some of the manipulations, we'll re-arrange
        // vertices_on_face so that it still contains the same
        // (counter-clockwise) order of the vertices on this face, but now the
        // min_degree_vertex is the first element in vertices_on_face.
        vertex_vector_t temp_vector;
        std::copy(min_degree_vertex_itr, vertices_on_face.end(),
            std::back_inserter(temp_vector));
        std::copy(vertices_on_face.begin(), min_degree_vertex_itr,
            std::back_inserter(temp_vector));
        vertices_on_face.swap(temp_vector);

        // Mark all of the min degree vertex's neighbors
        adjacency_iterator_t ai, ai_end;
        for (boost::tie(ai, ai_end)
             = adjacent_vertices(vertices_on_face.front(), g);
             ai != ai_end; ++ai)
        {
            put(marked, *ai, timestamp);
        }

        typename vertex_vector_t::iterator marked_neighbor
            = vertices_on_face.end();

        // The iterator manipulations on the next two lines are safe because
        // vertices_on_face.size() > 3 (from the first test in this function)
        fi_end = prior(vertices_on_face.end());
        for (face_iterator fi
             = boost::next(boost::next(vertices_on_face.begin()));
             fi != fi_end; ++fi)
        {
            if (get(marked, *fi) == timestamp)
            {
                marked_neighbor = fi;
                break;
            }
        }

        if (marked_neighbor == vertices_on_face.end())
        {
            add_edge_range(vertices_on_face[0],
                boost::next(boost::next(vertices_on_face.begin())),
                prior(vertices_on_face.end()));
        }
        else
        {
            add_edge_range(vertices_on_face[1], boost::next(marked_neighbor),
                vertices_on_face.end());

            add_edge_range(*boost::next(marked_neighbor),
                boost::next(boost::next(vertices_on_face.begin())),
                marked_neighbor);
        }

        // reset for the next face
        vertices_on_face.clear();
    }

private:
    void add_edge_range(vertex_t anchor, face_iterator fi, face_iterator fi_end)
    {
        for (; fi != fi_end; ++fi)
        {
            vertex_t v(*fi);
            add_edge_visitor.visit_vertex_pair(anchor, v, g);
            put(degree, anchor, get(degree, anchor) + 1);
            put(degree, v, get(degree, v) + 1);
        }
    }

    Graph& g;
    VertexIndexMap vm;
    AddEdgeVisitor add_edge_visitor;
    v_size_t timestamp;
    vertex_vector_t vertices_on_face;
    v_size_vector_t marked_vector;
    degree_size_vector_t degree_vector;
    vertex_to_v_size_map_t marked;
    vertex_to_degree_size_map_t degree;
};

template < typename Graph, typename PlanarEmbedding, typename VertexIndexMap,
    typename EdgeIndexMap, typename AddEdgeVisitor >
void make_maximal_planar(Graph& g, PlanarEmbedding embedding, VertexIndexMap vm,
    EdgeIndexMap em, AddEdgeVisitor& vis)
{
    triangulation_visitor< Graph, VertexIndexMap, AddEdgeVisitor > visitor(
        g, vm, vis);
    planar_face_traversal(g, embedding, visitor, em);
}

template < typename Graph, typename PlanarEmbedding, typename VertexIndexMap,
    typename EdgeIndexMap >
void make_maximal_planar(
    Graph& g, PlanarEmbedding embedding, VertexIndexMap vm, EdgeIndexMap em)
{
    default_add_edge_visitor vis;
    make_maximal_planar(g, embedding, vm, em, vis);
}

template < typename Graph, typename PlanarEmbedding, typename VertexIndexMap >
void make_maximal_planar(Graph& g, PlanarEmbedding embedding, VertexIndexMap vm)
{
    make_maximal_planar(g, embedding, vm, get(edge_index, g));
}

template < typename Graph, typename PlanarEmbedding >
void make_maximal_planar(Graph& g, PlanarEmbedding embedding)
{
    make_maximal_planar(g, embedding, get(vertex_index, g));
}

} // namespace boost

#endif //__MAKE_MAXIMAL_PLANAR_HPP__

/* make_maximal_planar.hpp
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
*/