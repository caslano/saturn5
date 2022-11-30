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
+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
*/