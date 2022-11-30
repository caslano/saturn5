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