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
FzdW8z5nszr6u0uD7PXP1lt7XfWuf65tirW19bX2ndA/4J3QpljtX/FWSsrWifW2P7Jk4FMFDaek1b4T+l96JzTo6HdCcg9fzt9T8Y/w/V3H/P2evl+0/uYdku2XcPsy+qI4mZMjm3yToCWsD0+G0bA7PB72gw2hHBfMg43gItgEvgibwe9hCxip+xJgfdgbNoB9dPywB+wIT4OJsKeOH/aCA42dTu8U++wpz+mS3k78nQX19iyH1xW+aOY0vQTHw1fhZLgLToevmblfr5u5X3vgNfAtqPPkbfg03AuJU+YAvQD/AN+A70OkPjBzkj40c8E+guSJ2ge7wI9hD/gJHGDmDg01c4dGw891uswcomL4BTwPfgkvMu5LjPty+EfzDZSv4WYzx2kb/BbuNPG8Df8MP4VH4OfwOxhNfv1g5iYFyM8TzFyk9mYu0qmwrsnn4oC5Z5dnDDefR/L3DPz1NpB4ToRnwFZwmJmzl2rmiKXBFeYdYqV5h/gSnAN1e1MI39W/A/fDufAgLDX5WAZJu7ybC5o5dFFmDl0feL7Jz3L+DTHv6EaYOXQL4cVwCVwO7zPvDh+AV5j8uxI+BCvMO79VZi7edfA1eL2Z85UHPzZz+w6Yd4yfOe7xBAPu8cXBtWau182wDbzFzPWqhGfD2807wTE6f+BYuAhmwUvhOHgjHA/vgNlwAzwTfggnwz/BHBgRdOcc1ofTYE+YC3vDmXAQvBNOhethMbwHzoP3wgvhffp34QPwCrgRXgsfhNfDX8I1cBN8Ej4Mfwcfgs8Z9w74CNwLH4VNI9xv8bSGT8KOcCvsB3+tzw/8jc4P+BTMhdvgXPi0Pt463Aevct+RboDb0B50CEVfS58RGoSyUTFajirRFrQbHURRnMDWaACaiMrQKrQJ7UQHUQwntwtKQwVoJVqPtqG9SK2mvUID0ES0GK1Bm9Er6BBqfANtFMpGi9GqG37aOtu1721r39vWvretfW/73/LeNi3s3e2GG4gLvXKDqt1qt9rtP3yLQJP/We//y0r/7nf/+h19Uevwd/nGz77Lt37h7/LxC3+X79lGi39qut/vePEbPS7L5xcjflnJ2VlenI3ELyMpM1PCW/+m4j8kKSMpK8Xvf4LxH5aaluz3byb+49Kzxo7LzEoean+zufiPGuq33VlX+43PyRmWOjbTl5YXjX/G6LTUIWd6/i+F/MeNzRidmcxvuf4vG//xyWNTh52Zk540Klm1NPteqbpvaHJG1eN41exPyspKJZgNt6tquJTRmVlV4n2t6v7kUUmpaURr07S76v7UDOXF/brZlzo8ffTY5JwhY1OzUlm70e5/I7Q/M3Nc8ljGZiQPGZnpi/tNdz8B09ydvrj3hO/LYVFI3/63quStDW73v232J2dnYJCaZQztb78TSlt6Supgdiele/v2hu0blZRh971r9mX3SuyXk5k1NnVIlv3N9+xvZiWnD00eSuKr5OUfzP5xmcmcwLSspEwvve9XPZ6MsanpWf7j+cDdb/IiMzMnM3W4f/+HZr8pr6Yoevs/Mvszx6VmJQ/O6d6jb87o9DTvmPcdtd9L98dh+/r18OL9JJTupLFZqUn6XCVR8bz9+83+9NGcwCx3d6Zv/wG73xyaW3xVG7P/06rlL2lcVkpOWvL45DSfzWfGhhIyegJZNzqbApE8NivTVz8+D9XRtCTJl2a8Kyhu7Xb8BPVcnpy83ILigvzSMhlTRJjqxxQdn6BUfzPuZGNdJVsXx32nmwCvJ9zBC9xxJyW5epU8GZvjvqBiC72nc+z7SjsOxYQ72Y6FiC/X7sNeGPtuz7yftWHa2vezjSRMlBN65+jIO0dvPESM7I90tDvDhm8=
*/