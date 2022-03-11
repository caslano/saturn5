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