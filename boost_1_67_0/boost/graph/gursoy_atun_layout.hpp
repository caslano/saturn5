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