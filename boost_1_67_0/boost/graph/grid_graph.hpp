//=======================================================================
// Copyright 2009 Trustees of Indiana University.
// Authors: Michael Hansen, Andrew Lumsdaine
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_GRAPH_GRID_GRAPH_HPP
#define BOOST_GRAPH_GRID_GRAPH_HPP

#include <cmath>
#include <functional>
#include <numeric>

#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/limits.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>
#include <boost/iterator/counting_iterator.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/property_map/property_map.hpp>

#define BOOST_GRID_GRAPH_TEMPLATE_PARAMS \
    std::size_t DimensionsT, typename VertexIndexT, typename EdgeIndexT

#define BOOST_GRID_GRAPH_TYPE \
    grid_graph< DimensionsT, VertexIndexT, EdgeIndexT >

#define BOOST_GRID_GRAPH_TRAITS_T typename graph_traits< BOOST_GRID_GRAPH_TYPE >

namespace boost
{

// Class prototype for grid_graph
template < BOOST_GRID_GRAPH_TEMPLATE_PARAMS > class grid_graph;

//===================
// Index Property Map
//===================

template < typename Graph, typename Descriptor, typename Index >
struct grid_graph_index_map
{
public:
    typedef Index value_type;
    typedef Index reference_type;
    typedef reference_type reference;
    typedef Descriptor key_type;
    typedef readable_property_map_tag category;

    grid_graph_index_map() {}

    grid_graph_index_map(const Graph& graph) : m_graph(&graph) {}

    value_type operator[](key_type key) const
    {
        return (m_graph->index_of(key));
    }

    friend inline Index get(
        const grid_graph_index_map< Graph, Descriptor, Index >& index_map,
        const typename grid_graph_index_map< Graph, Descriptor,
            Index >::key_type& key)
    {
        return (index_map[key]);
    }

protected:
    const Graph* m_graph;
};

template < BOOST_GRID_GRAPH_TEMPLATE_PARAMS >
struct property_map< BOOST_GRID_GRAPH_TYPE, vertex_index_t >
{
    typedef grid_graph_index_map< BOOST_GRID_GRAPH_TYPE,
        BOOST_GRID_GRAPH_TRAITS_T::vertex_descriptor,
        BOOST_GRID_GRAPH_TRAITS_T::vertices_size_type >
        type;
    typedef type const_type;
};

template < BOOST_GRID_GRAPH_TEMPLATE_PARAMS >
struct property_map< BOOST_GRID_GRAPH_TYPE, edge_index_t >
{
    typedef grid_graph_index_map< BOOST_GRID_GRAPH_TYPE,
        BOOST_GRID_GRAPH_TRAITS_T::edge_descriptor,
        BOOST_GRID_GRAPH_TRAITS_T::edges_size_type >
        type;
    typedef type const_type;
};

//==========================
// Reverse Edge Property Map
//==========================

template < typename Descriptor > struct grid_graph_reverse_edge_map
{
public:
    typedef Descriptor value_type;
    typedef Descriptor reference_type;
    typedef reference_type reference;
    typedef Descriptor key_type;
    typedef readable_property_map_tag category;

    grid_graph_reverse_edge_map() {}

    value_type operator[](const key_type& key) const
    {
        return (value_type(key.second, key.first));
    }

    friend inline Descriptor get(
        const grid_graph_reverse_edge_map< Descriptor >& rev_map,
        const typename grid_graph_reverse_edge_map< Descriptor >::key_type& key)
    {
        return (rev_map[key]);
    }
};

template < BOOST_GRID_GRAPH_TEMPLATE_PARAMS >
struct property_map< BOOST_GRID_GRAPH_TYPE, edge_reverse_t >
{
    typedef grid_graph_reverse_edge_map<
        BOOST_GRID_GRAPH_TRAITS_T::edge_descriptor >
        type;
    typedef type const_type;
};

//=================
// Function Objects
//=================

namespace detail
{

    // vertex_at
    template < typename Graph > struct grid_graph_vertex_at
    {

        typedef typename graph_traits< Graph >::vertex_descriptor result_type;

        grid_graph_vertex_at() : m_graph(0) {}

        grid_graph_vertex_at(const Graph* graph) : m_graph(graph) {}

        result_type operator()(
            typename graph_traits< Graph >::vertices_size_type vertex_index)
            const
        {
            return (vertex(vertex_index, *m_graph));
        }

    private:
        const Graph* m_graph;
    };

    // out_edge_at
    template < typename Graph > struct grid_graph_out_edge_at
    {

    private:
        typedef
            typename graph_traits< Graph >::vertex_descriptor vertex_descriptor;

    public:
        typedef typename graph_traits< Graph >::edge_descriptor result_type;

        grid_graph_out_edge_at() : m_vertex(), m_graph(0) {}

        grid_graph_out_edge_at(
            vertex_descriptor source_vertex, const Graph* graph)
        : m_vertex(source_vertex), m_graph(graph)
        {
        }

        result_type operator()(
            typename graph_traits< Graph >::degree_size_type out_edge_index)
            const
        {
            return (out_edge_at(m_vertex, out_edge_index, *m_graph));
        }

    private:
        vertex_descriptor m_vertex;
        const Graph* m_graph;
    };

    // in_edge_at
    template < typename Graph > struct grid_graph_in_edge_at
    {

    private:
        typedef
            typename graph_traits< Graph >::vertex_descriptor vertex_descriptor;

    public:
        typedef typename graph_traits< Graph >::edge_descriptor result_type;

        grid_graph_in_edge_at() : m_vertex(), m_graph(0) {}

        grid_graph_in_edge_at(
            vertex_descriptor target_vertex, const Graph* graph)
        : m_vertex(target_vertex), m_graph(graph)
        {
        }

        result_type operator()(
            typename graph_traits< Graph >::degree_size_type in_edge_index)
            const
        {
            return (in_edge_at(m_vertex, in_edge_index, *m_graph));
        }

    private:
        vertex_descriptor m_vertex;
        const Graph* m_graph;
    };

    // edge_at
    template < typename Graph > struct grid_graph_edge_at
    {

        typedef typename graph_traits< Graph >::edge_descriptor result_type;

        grid_graph_edge_at() : m_graph(0) {}

        grid_graph_edge_at(const Graph* graph) : m_graph(graph) {}

        result_type operator()(
            typename graph_traits< Graph >::edges_size_type edge_index) const
        {
            return (edge_at(edge_index, *m_graph));
        }

    private:
        const Graph* m_graph;
    };

    // adjacent_vertex_at
    template < typename Graph > struct grid_graph_adjacent_vertex_at
    {

    public:
        typedef typename graph_traits< Graph >::vertex_descriptor result_type;

        grid_graph_adjacent_vertex_at(
            result_type source_vertex, const Graph* graph)
        : m_vertex(source_vertex), m_graph(graph)
        {
        }

        result_type operator()(
            typename graph_traits< Graph >::degree_size_type adjacent_index)
            const
        {
            return (target(
                out_edge_at(m_vertex, adjacent_index, *m_graph), *m_graph));
        }

    private:
        result_type m_vertex;
        const Graph* m_graph;
    };

} // namespace detail

//===========
// Grid Graph
//===========

template < std::size_t Dimensions, typename VertexIndex = std::size_t,
    typename EdgeIndex = VertexIndex >
class grid_graph
{

private:
    typedef boost::array< bool, Dimensions > WrapDimensionArray;
    grid_graph() {};

public:
    typedef grid_graph< Dimensions, VertexIndex, EdgeIndex > type;

    // sizes
    typedef VertexIndex vertices_size_type;
    typedef EdgeIndex edges_size_type;
    typedef EdgeIndex degree_size_type;

    // descriptors
    typedef boost::array< VertexIndex, Dimensions > vertex_descriptor;
    typedef std::pair< vertex_descriptor, vertex_descriptor > edge_descriptor;

    // vertex_iterator
    typedef counting_iterator< vertices_size_type > vertex_index_iterator;
    typedef detail::grid_graph_vertex_at< type > vertex_function;
    typedef transform_iterator< vertex_function, vertex_index_iterator >
        vertex_iterator;

    // edge_iterator
    typedef counting_iterator< edges_size_type > edge_index_iterator;
    typedef detail::grid_graph_edge_at< type > edge_function;
    typedef transform_iterator< edge_function, edge_index_iterator >
        edge_iterator;

    // out_edge_iterator
    typedef counting_iterator< degree_size_type > degree_iterator;
    typedef detail::grid_graph_out_edge_at< type > out_edge_function;
    typedef transform_iterator< out_edge_function, degree_iterator >
        out_edge_iterator;

    // in_edge_iterator
    typedef detail::grid_graph_in_edge_at< type > in_edge_function;
    typedef transform_iterator< in_edge_function, degree_iterator >
        in_edge_iterator;

    // adjacency_iterator
    typedef detail::grid_graph_adjacent_vertex_at< type >
        adjacent_vertex_function;
    typedef transform_iterator< adjacent_vertex_function, degree_iterator >
        adjacency_iterator;

    // categories
    typedef directed_tag directed_category;
    typedef disallow_parallel_edge_tag edge_parallel_category;
    struct traversal_category : virtual public incidence_graph_tag,
                                virtual public adjacency_graph_tag,
                                virtual public vertex_list_graph_tag,
                                virtual public edge_list_graph_tag,
                                virtual public bidirectional_graph_tag,
                                virtual public adjacency_matrix_tag
    {
    };

    static inline vertex_descriptor null_vertex()
    {
        vertex_descriptor maxed_out_vertex;
        std::fill(maxed_out_vertex.begin(), maxed_out_vertex.end(),
            (std::numeric_limits< vertices_size_type >::max)());

        return (maxed_out_vertex);
    }

    // Constructor that defaults to no wrapping for all dimensions.
    grid_graph(vertex_descriptor dimension_lengths)
    : m_dimension_lengths(dimension_lengths)
    {

        std::fill(m_wrap_dimension.begin(), m_wrap_dimension.end(), false);

        precalculate();
    }

    // Constructor that allows for wrapping to be specified for all
    // dimensions at once.
    grid_graph(vertex_descriptor dimension_lengths, bool wrap_all_dimensions)
    : m_dimension_lengths(dimension_lengths)
    {

        std::fill(m_wrap_dimension.begin(), m_wrap_dimension.end(),
            wrap_all_dimensions);

        precalculate();
    }

    // Constructor that allows for individual dimension wrapping to be
    // specified.
    grid_graph(
        vertex_descriptor dimension_lengths, WrapDimensionArray wrap_dimension)
    : m_dimension_lengths(dimension_lengths), m_wrap_dimension(wrap_dimension)
    {

        precalculate();
    }

    // Returns the number of dimensions in the graph
    inline std::size_t dimensions() const { return (Dimensions); }

    // Returns the length of dimension [dimension_index]
    inline vertices_size_type length(std::size_t dimension) const
    {
        return (m_dimension_lengths[dimension]);
    }

    // Returns a value indicating if dimension [dimension_index] wraps
    inline bool wrapped(std::size_t dimension) const
    {
        return (m_wrap_dimension[dimension]);
    }

    // Gets the vertex that is [distance] units ahead of [vertex] in
    // dimension [dimension_index].
    vertex_descriptor next(vertex_descriptor vertex,
        std::size_t dimension_index, vertices_size_type distance = 1) const
    {

        vertices_size_type new_position = vertex[dimension_index] + distance;

        if (wrapped(dimension_index))
        {
            new_position %= length(dimension_index);
        }
        else
        {
            // Stop at the end of this dimension if necessary.
            new_position = (std::min)(
                new_position, vertices_size_type(length(dimension_index) - 1));
        }

        vertex[dimension_index] = new_position;

        return (vertex);
    }

    // Gets the vertex that is [distance] units behind [vertex] in
    // dimension [dimension_index].
    vertex_descriptor previous(vertex_descriptor vertex,
        std::size_t dimension_index, vertices_size_type distance = 1) const
    {

        // We're assuming that vertices_size_type is unsigned, so we
        // need to be careful about the math.
        vertex[dimension_index] = (distance > vertex[dimension_index])
            ? (wrapped(dimension_index) ? (length(dimension_index)
                   - (distance % length(dimension_index)))
                                        : 0)
            : vertex[dimension_index] - distance;

        return (vertex);
    }

protected:
    // Returns the number of vertices in the graph
    inline vertices_size_type num_vertices() const { return (m_num_vertices); }

    // Returns the number of edges in the graph
    inline edges_size_type num_edges() const { return (m_num_edges); }

    // Returns the number of edges in dimension [dimension_index]
    inline edges_size_type num_edges(std::size_t dimension_index) const
    {
        return (m_edge_count[dimension_index]);
    }

    // Returns the index of [vertex] (See also vertex_at)
    vertices_size_type index_of(vertex_descriptor vertex) const
    {

        vertices_size_type vertex_index = 0;
        vertices_size_type index_multiplier = 1;

        for (std::size_t dimension_index = 0; dimension_index < Dimensions;
             ++dimension_index)
        {

            vertex_index += (vertex[dimension_index] * index_multiplier);
            index_multiplier *= length(dimension_index);
        }

        return (vertex_index);
    }

    // Returns the vertex whose index is [vertex_index] (See also
    // index_of(vertex_descriptor))
    vertex_descriptor vertex_at(vertices_size_type vertex_index) const
    {

        boost::array< vertices_size_type, Dimensions > vertex;
        vertices_size_type index_divider = 1;

        for (std::size_t dimension_index = 0; dimension_index < Dimensions;
             ++dimension_index)
        {

            vertex[dimension_index]
                = (vertex_index / index_divider) % length(dimension_index);

            index_divider *= length(dimension_index);
        }

        return (vertex);
    }

    // Returns the edge whose index is [edge_index] (See also
    // index_of(edge_descriptor)).  NOTE: The index mapping is
    // dependent upon dimension wrapping.
    edge_descriptor edge_at(edges_size_type edge_index) const
    {

        // Edge indices are sorted into bins by dimension
        std::size_t dimension_index = 0;
        edges_size_type dimension_edges = num_edges(0);

        while (edge_index >= dimension_edges)
        {
            edge_index -= dimension_edges;
            ++dimension_index;
            dimension_edges = num_edges(dimension_index);
        }

        vertex_descriptor vertex_source, vertex_target;
        bool is_forward
            = ((edge_index / (num_edges(dimension_index) / 2)) == 0);

        if (wrapped(dimension_index))
        {
            vertex_source = vertex_at(edge_index % num_vertices());
            vertex_target = is_forward
                ? next(vertex_source, dimension_index)
                : previous(vertex_source, dimension_index);
        }
        else
        {

            // Dimensions can wrap arbitrarily, so an index needs to be
            // computed in a more complex manner.  This is done by
            // grouping the edges for each dimension together into "bins"
            // and considering [edge_index] as an offset into the bin.
            // Each bin consists of two parts: the "forward" looking edges
            // and the "backward" looking edges for the dimension.

            edges_size_type vertex_offset
                = edge_index % num_edges(dimension_index);

            // Consider vertex_offset an index into the graph's vertex
            // space but with the dimension [dimension_index] reduced in
            // size by one.
            vertices_size_type index_divider = 1;

            for (std::size_t dimension_index_iter = 0;
                 dimension_index_iter < Dimensions; ++dimension_index_iter)
            {

                std::size_t dimension_length
                    = (dimension_index_iter == dimension_index)
                    ? length(dimension_index_iter) - 1
                    : length(dimension_index_iter);

                vertex_source[dimension_index_iter]
                    = (vertex_offset / index_divider) % dimension_length;

                index_divider *= dimension_length;
            }

            if (is_forward)
            {
                vertex_target = next(vertex_source, dimension_index);
            }
            else
            {
                // Shift forward one more unit in the dimension for backward
                // edges since the algorithm above will leave us one behind.
                vertex_target = vertex_source;
                ++vertex_source[dimension_index];
            }

        } // if (wrapped(dimension_index))

        return (std::make_pair(vertex_source, vertex_target));
    }

    // Returns the index for [edge] (See also edge_at)
    edges_size_type index_of(edge_descriptor edge) const
    {
        vertex_descriptor source_vertex = source(edge, *this);
        vertex_descriptor target_vertex = target(edge, *this);

        BOOST_ASSERT(source_vertex != target_vertex);

        // Determine the dimension where the source and target vertices
        // differ (should only be one if this is a valid edge).
        std::size_t different_dimension_index = 0;

        while (source_vertex[different_dimension_index]
            == target_vertex[different_dimension_index])
        {

            ++different_dimension_index;
        }

        edges_size_type edge_index = 0;

        // Offset the edge index into the appropriate "bin" (see edge_at
        // for a more in-depth description).
        for (std::size_t dimension_index = 0;
             dimension_index < different_dimension_index; ++dimension_index)
        {

            edge_index += num_edges(dimension_index);
        }

        // Get the position of both vertices in the differing dimension.
        vertices_size_type source_position
            = source_vertex[different_dimension_index];
        vertices_size_type target_position
            = target_vertex[different_dimension_index];

        // Determine if edge is forward or backward
        bool is_forward = true;

        if (wrapped(different_dimension_index))
        {

            // If the dimension is wrapped, an edge is going backward if
            // either A: its target precedes the source in the differing
            // dimension and the vertices are adjacent or B: its source
            // precedes the target and they're not adjacent.
            if (((target_position < source_position)
                    && ((source_position - target_position) == 1))
                || ((source_position < target_position)
                    && ((target_position - source_position) > 1)))
            {

                is_forward = false;
            }
        }
        else if (target_position < source_position)
        {
            is_forward = false;
        }

        // "Backward" edges are in the second half of the bin.
        if (!is_forward)
        {
            edge_index += (num_edges(different_dimension_index) / 2);
        }

        // Finally, apply the vertex offset
        if (wrapped(different_dimension_index))
        {
            edge_index += index_of(source_vertex);
        }
        else
        {
            vertices_size_type index_multiplier = 1;

            if (!is_forward)
            {
                --source_vertex[different_dimension_index];
            }

            for (std::size_t dimension_index = 0; dimension_index < Dimensions;
                 ++dimension_index)
            {

                edge_index
                    += (source_vertex[dimension_index] * index_multiplier);
                index_multiplier
                    *= (dimension_index == different_dimension_index)
                    ? length(dimension_index) - 1
                    : length(dimension_index);
            }
        }

        return (edge_index);
    }

    // Returns the number of out-edges for [vertex]
    degree_size_type out_degree(vertex_descriptor vertex) const
    {

        degree_size_type out_edge_count = 0;

        for (std::size_t dimension_index = 0; dimension_index < Dimensions;
             ++dimension_index)
        {

            // If the vertex is on the edge of this dimension, then its
            // number of out edges is dependent upon whether the dimension
            // wraps or not.
            if ((vertex[dimension_index] == 0)
                || (vertex[dimension_index] == (length(dimension_index) - 1)))
            {
                out_edge_count += (wrapped(dimension_index) ? 2 : 1);
            }
            else
            {
                // Next and previous edges, regardless or wrapping
                out_edge_count += 2;
            }
        }

        return (out_edge_count);
    }

    // Returns an out-edge for [vertex] by index. Indices are in the
    // range [0, out_degree(vertex)).
    edge_descriptor out_edge_at(
        vertex_descriptor vertex, degree_size_type out_edge_index) const
    {

        edges_size_type edges_left = out_edge_index + 1;
        std::size_t dimension_index = 0;
        bool is_forward = false;

        // Walks the out edges of [vertex] and accommodates for dimension
        // wrapping.
        while (edges_left > 0)
        {

            if (!wrapped(dimension_index))
            {
                if (!is_forward && (vertex[dimension_index] == 0))
                {
                    is_forward = true;
                    continue;
                }
                else if (is_forward
                    && (vertex[dimension_index]
                        == (length(dimension_index) - 1)))
                {
                    is_forward = false;
                    ++dimension_index;
                    continue;
                }
            }

            --edges_left;

            if (edges_left > 0)
            {
                is_forward = !is_forward;

                if (!is_forward)
                {
                    ++dimension_index;
                }
            }
        }

        return (std::make_pair(vertex,
            is_forward ? next(vertex, dimension_index)
                       : previous(vertex, dimension_index)));
    }

    // Returns the number of in-edges for [vertex]
    inline degree_size_type in_degree(vertex_descriptor vertex) const
    {
        return (out_degree(vertex));
    }

    // Returns an in-edge for [vertex] by index. Indices are in the
    // range [0, in_degree(vertex)).
    edge_descriptor in_edge_at(
        vertex_descriptor vertex, edges_size_type in_edge_index) const
    {

        edge_descriptor out_edge = out_edge_at(vertex, in_edge_index);
        return (
            std::make_pair(target(out_edge, *this), source(out_edge, *this)));
    }

    // Pre-computes the number of vertices and edges
    void precalculate()
    {
        m_num_vertices = std::accumulate(m_dimension_lengths.begin(),
            m_dimension_lengths.end(), vertices_size_type(1),
            std::multiplies< vertices_size_type >());

        // Calculate number of edges in each dimension
        m_num_edges = 0;

        for (std::size_t dimension_index = 0; dimension_index < Dimensions;
             ++dimension_index)
        {

            if (wrapped(dimension_index))
            {
                m_edge_count[dimension_index] = num_vertices() * 2;
            }
            else
            {
                m_edge_count[dimension_index]
                    = (num_vertices()
                          - (num_vertices() / length(dimension_index)))
                    * 2;
            }

            m_num_edges += num_edges(dimension_index);
        }
    }

    const vertex_descriptor m_dimension_lengths;
    WrapDimensionArray m_wrap_dimension;
    vertices_size_type m_num_vertices;

    boost::array< edges_size_type, Dimensions > m_edge_count;
    edges_size_type m_num_edges;

public:
    //================
    // VertexListGraph
    //================

    friend inline std::pair< typename type::vertex_iterator,
        typename type::vertex_iterator >
    vertices(const type& graph)
    {
        typedef typename type::vertex_iterator vertex_iterator;
        typedef typename type::vertex_function vertex_function;
        typedef typename type::vertex_index_iterator vertex_index_iterator;

        return (std::make_pair(
            vertex_iterator(vertex_index_iterator(0), vertex_function(&graph)),
            vertex_iterator(vertex_index_iterator(graph.num_vertices()),
                vertex_function(&graph))));
    }

    friend inline typename type::vertices_size_type num_vertices(
        const type& graph)
    {
        return (graph.num_vertices());
    }

    friend inline typename type::vertex_descriptor vertex(
        typename type::vertices_size_type vertex_index, const type& graph)
    {

        return (graph.vertex_at(vertex_index));
    }

    //===============
    // IncidenceGraph
    //===============

    friend inline std::pair< typename type::out_edge_iterator,
        typename type::out_edge_iterator >
    out_edges(typename type::vertex_descriptor vertex, const type& graph)
    {
        typedef typename type::degree_iterator degree_iterator;
        typedef typename type::out_edge_function out_edge_function;
        typedef typename type::out_edge_iterator out_edge_iterator;

        return (std::make_pair(out_edge_iterator(degree_iterator(0),
                                   out_edge_function(vertex, &graph)),
            out_edge_iterator(degree_iterator(graph.out_degree(vertex)),
                out_edge_function(vertex, &graph))));
    }

    friend inline typename type::degree_size_type out_degree(
        typename type::vertex_descriptor vertex, const type& graph)
    {
        return (graph.out_degree(vertex));
    }

    friend inline typename type::edge_descriptor out_edge_at(
        typename type::vertex_descriptor vertex,
        typename type::degree_size_type out_edge_index, const type& graph)
    {
        return (graph.out_edge_at(vertex, out_edge_index));
    }

    //===============
    // AdjacencyGraph
    //===============

    friend typename std::pair< typename type::adjacency_iterator,
        typename type::adjacency_iterator >
    adjacent_vertices(
        typename type::vertex_descriptor vertex, const type& graph)
    {
        typedef typename type::degree_iterator degree_iterator;
        typedef
            typename type::adjacent_vertex_function adjacent_vertex_function;
        typedef typename type::adjacency_iterator adjacency_iterator;

        return (std::make_pair(adjacency_iterator(degree_iterator(0),
                                   adjacent_vertex_function(vertex, &graph)),
            adjacency_iterator(degree_iterator(graph.out_degree(vertex)),
                adjacent_vertex_function(vertex, &graph))));
    }

    //==============
    // EdgeListGraph
    //==============

    friend inline typename type::edges_size_type num_edges(const type& graph)
    {
        return (graph.num_edges());
    }

    friend inline typename type::edge_descriptor edge_at(
        typename type::edges_size_type edge_index, const type& graph)
    {
        return (graph.edge_at(edge_index));
    }

    friend inline std::pair< typename type::edge_iterator,
        typename type::edge_iterator >
    edges(const type& graph)
    {
        typedef typename type::edge_index_iterator edge_index_iterator;
        typedef typename type::edge_function edge_function;
        typedef typename type::edge_iterator edge_iterator;

        return (std::make_pair(
            edge_iterator(edge_index_iterator(0), edge_function(&graph)),
            edge_iterator(edge_index_iterator(graph.num_edges()),
                edge_function(&graph))));
    }

    //===================
    // BiDirectionalGraph
    //===================

    friend inline std::pair< typename type::in_edge_iterator,
        typename type::in_edge_iterator >
    in_edges(typename type::vertex_descriptor vertex, const type& graph)
    {
        typedef typename type::in_edge_function in_edge_function;
        typedef typename type::degree_iterator degree_iterator;
        typedef typename type::in_edge_iterator in_edge_iterator;

        return (std::make_pair(in_edge_iterator(degree_iterator(0),
                                   in_edge_function(vertex, &graph)),
            in_edge_iterator(degree_iterator(graph.in_degree(vertex)),
                in_edge_function(vertex, &graph))));
    }

    friend inline typename type::degree_size_type in_degree(
        typename type::vertex_descriptor vertex, const type& graph)
    {
        return (graph.in_degree(vertex));
    }

    friend inline typename type::degree_size_type degree(
        typename type::vertex_descriptor vertex, const type& graph)
    {
        return (graph.out_degree(vertex) * 2);
    }

    friend inline typename type::edge_descriptor in_edge_at(
        typename type::vertex_descriptor vertex,
        typename type::degree_size_type in_edge_index, const type& graph)
    {
        return (graph.in_edge_at(vertex, in_edge_index));
    }

    //==================
    // Adjacency Matrix
    //==================

    friend std::pair< typename type::edge_descriptor, bool > edge(
        typename type::vertex_descriptor source_vertex,
        typename type::vertex_descriptor destination_vertex, const type& graph)
    {

        std::pair< typename type::edge_descriptor, bool > edge_exists
            = std::make_pair(
                std::make_pair(source_vertex, destination_vertex), false);

        for (std::size_t dimension_index = 0; dimension_index < Dimensions;
             ++dimension_index)
        {

            typename type::vertices_size_type dim_difference = 0;
            typename type::vertices_size_type source_dim
                = source_vertex[dimension_index],
                dest_dim = destination_vertex[dimension_index];

            dim_difference = (source_dim > dest_dim) ? (source_dim - dest_dim)
                                                     : (dest_dim - source_dim);

            if (dim_difference > 0)
            {

                // If we've already found a valid edge, this would mean that
                // the vertices are really diagonal across dimensions and
                // therefore not connected.
                if (edge_exists.second)
                {
                    edge_exists.second = false;
                    break;
                }

                // If the difference is one, the vertices are right next to
                // each other and the edge is valid.  The edge is still
                // valid, though, if the dimension wraps and the vertices
                // are on opposite ends.
                if ((dim_difference == 1)
                    || (graph.wrapped(dimension_index)
                        && (((source_dim == 0)
                                && (dest_dim
                                    == (graph.length(dimension_index) - 1)))
                            || ((dest_dim == 0)
                                && (source_dim
                                    == (graph.length(dimension_index) - 1))))))
                {

                    edge_exists.second = true;
                    // Stay in the loop to check for diagonal vertices.
                }
                else
                {

                    // Stop checking - the vertices are too far apart.
                    edge_exists.second = false;
                    break;
                }
            }

        } // for dimension_index

        return (edge_exists);
    }

    //=============================
    // Index Property Map Functions
    //=============================

    friend inline typename type::vertices_size_type get(vertex_index_t,
        const type& graph, typename type::vertex_descriptor vertex)
    {
        return (graph.index_of(vertex));
    }

    friend inline typename type::edges_size_type get(
        edge_index_t, const type& graph, typename type::edge_descriptor edge)
    {
        return (graph.index_of(edge));
    }

    friend inline grid_graph_index_map< type, typename type::vertex_descriptor,
        typename type::vertices_size_type >
    get(vertex_index_t, const type& graph)
    {
        return (grid_graph_index_map< type, typename type::vertex_descriptor,
            typename type::vertices_size_type >(graph));
    }

    friend inline grid_graph_index_map< type, typename type::edge_descriptor,
        typename type::edges_size_type >
    get(edge_index_t, const type& graph)
    {
        return (grid_graph_index_map< type, typename type::edge_descriptor,
            typename type::edges_size_type >(graph));
    }

    friend inline grid_graph_reverse_edge_map< typename type::edge_descriptor >
    get(edge_reverse_t, const type& graph)
    {
        return (
            grid_graph_reverse_edge_map< typename type::edge_descriptor >());
    }

    template < typename Graph, typename Descriptor, typename Index >
    friend struct grid_graph_index_map;

    template < typename Descriptor > friend struct grid_graph_reverse_edge_map;

}; // grid_graph

} // namespace boost

#undef BOOST_GRID_GRAPH_TYPE
#undef BOOST_GRID_GRAPH_TEMPLATE_PARAMS
#undef BOOST_GRID_GRAPH_TRAITS_T

#endif // BOOST_GRAPH_GRID_GRAPH_HPP

/* grid_graph.hpp
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
*/