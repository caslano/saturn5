// Copyright 2004 The Trustees of Indiana University.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Jeremiah Willcock
//           Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_GURSOY_ATUN_LAYOUT_HPP
#define BOOST_GRAPH_GURSOY_ATUN_LAYOUT_HPP

// Gürsoy-Atun graph layout, based on:
// "Neighbourhood Preserving Load Balancing: A Self-Organizing Approach"
// in 6th International Euro-Par Conference Munich, Germany, August 29 –
// September 1, 2000 Proceedings, pp 234-241
// https://doi.org/10.1007/3-540-44520-X_32

#include <boost/config/no_tr1/cmath.hpp>
#include <boost/throw_exception.hpp>
#include <boost/assert.hpp>
#include <vector>
#include <exception>
#include <algorithm>

#include <boost/graph/visitors.hpp>
#include <boost/graph/properties.hpp>
#include <boost/random/uniform_01.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/topology.hpp>

namespace boost
{

namespace detail
{

    struct over_distance_limit : public std::exception
    {
    };

    template < typename PositionMap, typename NodeDistanceMap,
        typename Topology, typename Graph >
    struct update_position_visitor
    {
        typedef typename Topology::point_type Point;
        PositionMap position_map;
        NodeDistanceMap node_distance;
        const Topology& space;
        Point input_vector;
        double distance_limit;
        double learning_constant;
        double falloff_ratio;

        typedef boost::on_examine_vertex event_filter;

        typedef
            typename graph_traits< Graph >::vertex_descriptor vertex_descriptor;

        update_position_visitor(PositionMap position_map,
            NodeDistanceMap node_distance, const Topology& space,
            const Point& input_vector, double distance_limit,
            double learning_constant, double falloff_ratio)
        : position_map(position_map)
        , node_distance(node_distance)
        , space(space)
        , input_vector(input_vector)
        , distance_limit(distance_limit)
        , learning_constant(learning_constant)
        , falloff_ratio(falloff_ratio)
        {
        }

        void operator()(vertex_descriptor v, const Graph&) const
        {
#ifndef BOOST_NO_STDC_NAMESPACE
            using std::pow;
#endif

            if (get(node_distance, v) > distance_limit)
                BOOST_THROW_EXCEPTION(over_distance_limit());
            Point old_position = get(position_map, v);
            double distance = get(node_distance, v);
            double fraction
                = learning_constant * pow(falloff_ratio, distance * distance);
            put(position_map, v,
                space.move_position_toward(
                    old_position, fraction, input_vector));
        }
    };

    template < typename EdgeWeightMap > struct gursoy_shortest
    {
        template < typename Graph, typename NodeDistanceMap,
            typename UpdatePosition >
        static inline void run(const Graph& g,
            typename graph_traits< Graph >::vertex_descriptor s,
            NodeDistanceMap node_distance, UpdatePosition& update_position,
            EdgeWeightMap weight)
        {
            boost::dijkstra_shortest_paths(g, s,
                weight_map(weight).visitor(boost::make_dijkstra_visitor(
                    std::make_pair(boost::record_distances(
                                       node_distance, boost::on_edge_relaxed()),
                        update_position))));
        }
    };

    template <> struct gursoy_shortest< dummy_property_map >
    {
        template < typename Graph, typename NodeDistanceMap,
            typename UpdatePosition >
        static inline void run(const Graph& g,
            typename graph_traits< Graph >::vertex_descriptor s,
            NodeDistanceMap node_distance, UpdatePosition& update_position,
            dummy_property_map)
        {
            boost::breadth_first_search(g, s,
                visitor(boost::make_bfs_visitor(
                    std::make_pair(boost::record_distances(
                                       node_distance, boost::on_tree_edge()),
                        update_position))));
        }
    };

} // namespace detail

template < typename VertexListAndIncidenceGraph, typename Topology,
    typename PositionMap, typename Diameter, typename VertexIndexMap,
    typename EdgeWeightMap >
void gursoy_atun_step(const VertexListAndIncidenceGraph& graph,
    const Topology& space, PositionMap position, Diameter diameter,
    double learning_constant, VertexIndexMap vertex_index_map,
    EdgeWeightMap weight)
{
#ifndef BOOST_NO_STDC_NAMESPACE
    using std::exp;
    using std::pow;
#endif

    typedef
        typename graph_traits< VertexListAndIncidenceGraph >::vertex_iterator
            vertex_iterator;
    typedef
        typename graph_traits< VertexListAndIncidenceGraph >::vertex_descriptor
            vertex_descriptor;
    typedef typename Topology::point_type point_type;
    vertex_iterator i, iend;
    std::vector< double > distance_from_input_vector(num_vertices(graph));
    typedef boost::iterator_property_map< std::vector< double >::iterator,
        VertexIndexMap, double, double& >
        DistanceFromInputMap;
    DistanceFromInputMap distance_from_input(
        distance_from_input_vector.begin(), vertex_index_map);
    std::vector< double > node_distance_map_vector(num_vertices(graph));
    typedef boost::iterator_property_map< std::vector< double >::iterator,
        VertexIndexMap, double, double& >
        NodeDistanceMap;
    NodeDistanceMap node_distance(
        node_distance_map_vector.begin(), vertex_index_map);
    point_type input_vector = space.random_point();
    vertex_descriptor min_distance_loc
        = graph_traits< VertexListAndIncidenceGraph >::null_vertex();
    double min_distance = 0.0;
    bool min_distance_unset = true;
    for (boost::tie(i, iend) = vertices(graph); i != iend; ++i)
    {
        double this_distance = space.distance(get(position, *i), input_vector);
        put(distance_from_input, *i, this_distance);
        if (min_distance_unset || this_distance < min_distance)
        {
            min_distance = this_distance;
            min_distance_loc = *i;
        }
        min_distance_unset = false;
    }
    BOOST_ASSERT(!min_distance_unset); // Graph must have at least one vertex
    boost::detail::update_position_visitor< PositionMap, NodeDistanceMap,
        Topology, VertexListAndIncidenceGraph >
        update_position(position, node_distance, space, input_vector, diameter,
            learning_constant, exp(-1. / (2 * diameter * diameter)));
    std::fill(
        node_distance_map_vector.begin(), node_distance_map_vector.end(), 0);
    try
    {
        typedef detail::gursoy_shortest< EdgeWeightMap > shortest;
        shortest::run(
            graph, min_distance_loc, node_distance, update_position, weight);
    }
    catch (const detail::over_distance_limit&)
    {
        /* Thrown to break out of BFS or Dijkstra early */
    }
}

template < typename VertexListAndIncidenceGraph, typename Topology,
    typename PositionMap, typename VertexIndexMap, typename EdgeWeightMap >
void gursoy_atun_refine(const VertexListAndIncidenceGraph& graph,
    const Topology& space, PositionMap position, int nsteps,
    double diameter_initial, double diameter_final,
    double learning_constant_initial, double learning_constant_final,
    VertexIndexMap vertex_index_map, EdgeWeightMap weight)
{
#ifndef BOOST_NO_STDC_NAMESPACE
    using std::exp;
    using std::pow;
#endif

    typedef
        typename graph_traits< VertexListAndIncidenceGraph >::vertex_iterator
            vertex_iterator;
    vertex_iterator i, iend;
    double diameter_ratio = (double)diameter_final / diameter_initial;
    double learning_constant_ratio
        = learning_constant_final / learning_constant_initial;
    std::vector< double > distance_from_input_vector(num_vertices(graph));
    typedef boost::iterator_property_map< std::vector< double >::iterator,
        VertexIndexMap, double, double& >
        DistanceFromInputMap;
    DistanceFromInputMap distance_from_input(
        distance_from_input_vector.begin(), vertex_index_map);
    std::vector< int > node_distance_map_vector(num_vertices(graph));
    typedef boost::iterator_property_map< std::vector< int >::iterator,
        VertexIndexMap, double, double& >
        NodeDistanceMap;
    NodeDistanceMap node_distance(
        node_distance_map_vector.begin(), vertex_index_map);
    for (int round = 0; round < nsteps; ++round)
    {
        double part_done = (double)round / (nsteps - 1);
        // fprintf(stderr, "%2d%% done\n", int(rint(part_done * 100.)));
        int diameter = (int)(diameter_initial * pow(diameter_ratio, part_done));
        double learning_constant = learning_constant_initial
            * pow(learning_constant_ratio, part_done);
        gursoy_atun_step(graph, space, position, diameter, learning_constant,
            vertex_index_map, weight);
    }
}

template < typename VertexListAndIncidenceGraph, typename Topology,
    typename PositionMap, typename VertexIndexMap, typename EdgeWeightMap >
void gursoy_atun_layout(const VertexListAndIncidenceGraph& graph,
    const Topology& space, PositionMap position, int nsteps,
    double diameter_initial, double diameter_final,
    double learning_constant_initial, double learning_constant_final,
    VertexIndexMap vertex_index_map, EdgeWeightMap weight)
{
    typedef
        typename graph_traits< VertexListAndIncidenceGraph >::vertex_iterator
            vertex_iterator;
    vertex_iterator i, iend;
    for (boost::tie(i, iend) = vertices(graph); i != iend; ++i)
    {
        put(position, *i, space.random_point());
    }
    gursoy_atun_refine(graph, space, position, nsteps, diameter_initial,
        diameter_final, learning_constant_initial, learning_constant_final,
        vertex_index_map, weight);
}

template < typename VertexListAndIncidenceGraph, typename Topology,
    typename PositionMap, typename VertexIndexMap >
void gursoy_atun_layout(const VertexListAndIncidenceGraph& graph,
    const Topology& space, PositionMap position, int nsteps,
    double diameter_initial, double diameter_final,
    double learning_constant_initial, double learning_constant_final,
    VertexIndexMap vertex_index_map)
{
    gursoy_atun_layout(graph, space, position, nsteps, diameter_initial,
        diameter_final, learning_constant_initial, learning_constant_final,
        vertex_index_map, dummy_property_map());
}

template < typename VertexListAndIncidenceGraph, typename Topology,
    typename PositionMap >
void gursoy_atun_layout(const VertexListAndIncidenceGraph& graph,
    const Topology& space, PositionMap position, int nsteps,
    double diameter_initial, double diameter_final = 1.0,
    double learning_constant_initial = 0.8,
    double learning_constant_final = 0.2)
{
    gursoy_atun_layout(graph, space, position, nsteps, diameter_initial,
        diameter_final, learning_constant_initial, learning_constant_final,
        get(vertex_index, graph));
}

template < typename VertexListAndIncidenceGraph, typename Topology,
    typename PositionMap >
void gursoy_atun_layout(const VertexListAndIncidenceGraph& graph,
    const Topology& space, PositionMap position, int nsteps)
{
#ifndef BOOST_NO_STDC_NAMESPACE
    using std::sqrt;
#endif

    gursoy_atun_layout(
        graph, space, position, nsteps, sqrt((double)num_vertices(graph)));
}

template < typename VertexListAndIncidenceGraph, typename Topology,
    typename PositionMap >
void gursoy_atun_layout(const VertexListAndIncidenceGraph& graph,
    const Topology& space, PositionMap position)
{
    gursoy_atun_layout(graph, space, position, num_vertices(graph));
}

template < typename VertexListAndIncidenceGraph, typename Topology,
    typename PositionMap, typename P, typename T, typename R >
void gursoy_atun_layout(const VertexListAndIncidenceGraph& graph,
    const Topology& space, PositionMap position,
    const bgl_named_params< P, T, R >& params)
{
#ifndef BOOST_NO_STDC_NAMESPACE
    using std::sqrt;
#endif

    std::pair< double, double > diam(sqrt(double(num_vertices(graph))), 1.0);
    std::pair< double, double > learn(0.8, 0.2);
    gursoy_atun_layout(graph, space, position,
        choose_param(get_param(params, iterations_t()), num_vertices(graph)),
        choose_param(get_param(params, diameter_range_t()), diam).first,
        choose_param(get_param(params, diameter_range_t()), diam).second,
        choose_param(get_param(params, learning_constant_range_t()), learn)
            .first,
        choose_param(get_param(params, learning_constant_range_t()), learn)
            .second,
        choose_const_pmap(get_param(params, vertex_index), graph, vertex_index),
        choose_param(get_param(params, edge_weight), dummy_property_map()));
}

} // namespace boost

#endif // BOOST_GRAPH_GURSOY_ATUN_LAYOUT_HPP

/* gursoy_atun_layout.hpp
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
*/