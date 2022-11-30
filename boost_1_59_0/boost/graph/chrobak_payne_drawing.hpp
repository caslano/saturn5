//=======================================================================
// Copyright (c) Aaron Windsor 2007
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef __CHROBAK_PAYNE_DRAWING_HPP__
#define __CHROBAK_PAYNE_DRAWING_HPP__

#include <vector>
#include <list>
#include <stack>
#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>

namespace boost
{

namespace graph
{
    namespace detail
    {

        template < typename Graph, typename VertexToVertexMap,
            typename VertexTo1DCoordMap >
        void accumulate_offsets(
            typename graph_traits< Graph >::vertex_descriptor v,
            std::size_t offset, const Graph& g, VertexTo1DCoordMap x,
            VertexTo1DCoordMap delta_x, VertexToVertexMap left,
            VertexToVertexMap right)
        {
            typedef typename graph_traits< Graph >::vertex_descriptor
                vertex_descriptor;
            // Suggestion of explicit stack from Aaron Windsor to avoid system
            // stack overflows.
            typedef std::pair< vertex_descriptor, std::size_t > stack_entry;
            std::stack< stack_entry > st;
            st.push(stack_entry(v, offset));
            while (!st.empty())
            {
                vertex_descriptor v = st.top().first;
                std::size_t offset = st.top().second;
                st.pop();
                if (v != graph_traits< Graph >::null_vertex())
                {
                    x[v] += delta_x[v] + offset;
                    st.push(stack_entry(left[v], x[v]));
                    st.push(stack_entry(right[v], x[v]));
                }
            }
        }

    } /*namespace detail*/
} /*namespace graph*/

template < typename Graph, typename PlanarEmbedding, typename ForwardIterator,
    typename GridPositionMap, typename VertexIndexMap >
void chrobak_payne_straight_line_drawing(const Graph& g,
    PlanarEmbedding embedding, ForwardIterator ordering_begin,
    ForwardIterator ordering_end, GridPositionMap drawing, VertexIndexMap vm)
{

    typedef typename graph_traits< Graph >::vertex_descriptor vertex_t;
    typedef typename graph_traits< Graph >::vertex_iterator vertex_iterator_t;
    typedef typename PlanarEmbedding::value_type::const_iterator
        edge_permutation_iterator_t;
    typedef typename graph_traits< Graph >::vertices_size_type v_size_t;
    typedef std::vector< vertex_t > vertex_vector_t;
    typedef std::vector< v_size_t > vsize_vector_t;
    typedef std::vector< bool > bool_vector_t;
    typedef boost::iterator_property_map< typename vertex_vector_t::iterator,
        VertexIndexMap >
        vertex_to_vertex_map_t;
    typedef boost::iterator_property_map< typename vsize_vector_t::iterator,
        VertexIndexMap >
        vertex_to_vsize_map_t;
    typedef boost::iterator_property_map< typename bool_vector_t::iterator,
        VertexIndexMap >
        vertex_to_bool_map_t;

    vertex_vector_t left_vector(
        num_vertices(g), graph_traits< Graph >::null_vertex());
    vertex_vector_t right_vector(
        num_vertices(g), graph_traits< Graph >::null_vertex());
    vsize_vector_t seen_as_right_vector(num_vertices(g), 0);
    vsize_vector_t seen_vector(num_vertices(g), 0);
    vsize_vector_t delta_x_vector(num_vertices(g), 0);
    vsize_vector_t y_vector(num_vertices(g));
    vsize_vector_t x_vector(num_vertices(g), 0);
    bool_vector_t installed_vector(num_vertices(g), false);

    vertex_to_vertex_map_t left(left_vector.begin(), vm);
    vertex_to_vertex_map_t right(right_vector.begin(), vm);
    vertex_to_vsize_map_t seen_as_right(seen_as_right_vector.begin(), vm);
    vertex_to_vsize_map_t seen(seen_vector.begin(), vm);
    vertex_to_vsize_map_t delta_x(delta_x_vector.begin(), vm);
    vertex_to_vsize_map_t y(y_vector.begin(), vm);
    vertex_to_vsize_map_t x(x_vector.begin(), vm);
    vertex_to_bool_map_t installed(installed_vector.begin(), vm);

    v_size_t timestamp = 1;
    vertex_vector_t installed_neighbors;

    ForwardIterator itr = ordering_begin;
    vertex_t v1 = *itr;
    ++itr;
    vertex_t v2 = *itr;
    ++itr;
    vertex_t v3 = *itr;
    ++itr;

    delta_x[v2] = 1;
    delta_x[v3] = 1;

    y[v1] = 0;
    y[v2] = 0;
    y[v3] = 1;

    right[v1] = v3;
    right[v3] = v2;

    installed[v1] = installed[v2] = installed[v3] = true;

    for (ForwardIterator itr_end = ordering_end; itr != itr_end; ++itr)
    {
        vertex_t v = *itr;

        // First, find the leftmost and rightmost neighbor of v on the outer
        // cycle of the embedding.
        // Note: since we're moving clockwise through the edges adjacent to v,
        // we're actually moving from right to left among v's neighbors on the
        // outer face (since v will be installed above them all) looking for
        // the leftmost and rightmost installed neigbhors

        vertex_t leftmost = graph_traits< Graph >::null_vertex();
        vertex_t rightmost = graph_traits< Graph >::null_vertex();

        installed_neighbors.clear();

        vertex_t prev_vertex = graph_traits< Graph >::null_vertex();
        edge_permutation_iterator_t pi, pi_end;
        pi_end = embedding[v].end();
        for (pi = embedding[v].begin(); pi != pi_end; ++pi)
        {
            vertex_t curr_vertex
                = source(*pi, g) == v ? target(*pi, g) : source(*pi, g);

            // Skip any self-loops or parallel edges
            if (curr_vertex == v || curr_vertex == prev_vertex)
                continue;

            if (installed[curr_vertex])
            {
                seen[curr_vertex] = timestamp;

                if (right[curr_vertex] != graph_traits< Graph >::null_vertex())
                {
                    seen_as_right[right[curr_vertex]] = timestamp;
                }
                installed_neighbors.push_back(curr_vertex);
            }

            prev_vertex = curr_vertex;
        }

        typename vertex_vector_t::iterator vi, vi_end;
        vi_end = installed_neighbors.end();
        for (vi = installed_neighbors.begin(); vi != vi_end; ++vi)
        {
            if (right[*vi] == graph_traits< Graph >::null_vertex()
                || seen[right[*vi]] != timestamp)
                rightmost = *vi;
            if (seen_as_right[*vi] != timestamp)
                leftmost = *vi;
        }

        ++timestamp;

        // stretch gaps
        ++delta_x[right[leftmost]];
        ++delta_x[rightmost];

        // adjust offsets
        std::size_t delta_p_q = 0;
        vertex_t stopping_vertex = right[rightmost];
        for (vertex_t temp = right[leftmost]; temp != stopping_vertex;
             temp = right[temp])
        {
            delta_p_q += delta_x[temp];
        }

        delta_x[v] = ((y[rightmost] + delta_p_q) - y[leftmost]) / 2;
        y[v] = y[leftmost] + delta_x[v];
        delta_x[rightmost] = delta_p_q - delta_x[v];

        bool leftmost_and_rightmost_adjacent = right[leftmost] == rightmost;
        if (!leftmost_and_rightmost_adjacent)
            delta_x[right[leftmost]] -= delta_x[v];

        // install v
        if (!leftmost_and_rightmost_adjacent)
        {
            left[v] = right[leftmost];
            vertex_t next_to_rightmost;
            for (vertex_t temp = leftmost; temp != rightmost;
                 temp = right[temp])
            {
                next_to_rightmost = temp;
            }

            right[next_to_rightmost] = graph_traits< Graph >::null_vertex();
        }
        else
        {
            left[v] = graph_traits< Graph >::null_vertex();
        }

        right[leftmost] = v;
        right[v] = rightmost;
        installed[v] = true;
    }

    graph::detail::accumulate_offsets(
        *ordering_begin, 0, g, x, delta_x, left, right);

    vertex_iterator_t vi, vi_end;
    for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
    {
        vertex_t v(*vi);
        drawing[v].x = x[v];
        drawing[v].y = y[v];
    }
}

template < typename Graph, typename PlanarEmbedding, typename ForwardIterator,
    typename GridPositionMap >
inline void chrobak_payne_straight_line_drawing(const Graph& g,
    PlanarEmbedding embedding, ForwardIterator ord_begin,
    ForwardIterator ord_end, GridPositionMap drawing)
{
    chrobak_payne_straight_line_drawing(
        g, embedding, ord_begin, ord_end, drawing, get(vertex_index, g));
}

} // namespace boost

#endif //__CHROBAK_PAYNE_DRAWING_HPP__

/* chrobak_payne_drawing.hpp
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
*/