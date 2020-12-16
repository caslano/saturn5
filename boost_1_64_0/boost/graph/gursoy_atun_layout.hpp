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
lTN9zs5Z6MP193M1ZmnNPGHqu1Pp+ArmEaRZbr85ymrWeDJDgT6Fe/Za+BNf92sGu1e5S3ziibPr1rWzDMmNCVY13Am7jQI4umm/dU5cvooT0HGjVvvbhChvuN23K6yJNeNfZ4kdleiSE5Zxat0K7QNGT38iw22giy2hDElYCVZ7aV+dcO8yq0S+lXd/r9yb6asREWyv3c26tfTU1p6bagX53HOtbJw22PCqX6tVvxkpTd+Xe8e/UK0+uTxt29dd90LMxbXVr/VN5aFhO3yflS6gC3LrJVGqJEXruydGdUJVEpTZzJxeP+3iEj7K1t4S/ZtHY/QMIxPrC4m66nj8VQILGhHmiRe508UfspbvFvNtjKWNDIpmp+gaZywZfln9akm9Ghrs7vFeP/nZ1jI+vm8xD+PrJU2dkLejWd6jmTa3BXsqRrx3SkfPHvNqRFF3BLDrhdlW53JRcrySHHFhponRPp+cqpj3NACH3nWTYj5an/bmRse2yB2R+m405/fKzZjGufQvZs7ng0VnAnqcHwvdc761vN1+bAxtdsc0ZuIp8xGl09Un9j+TPr0bYGfKw/bx631jKkstBp2fuOcSPvUTUmpHGdOaGsVU5tv6N4Y5HZk3dFasIrPV2qEykSXy2dq1Dbu+QJKk+PiOxz5X30be8ZA85Qs8jzLMR2Su344U59d7R+UpeNEXXTZ5M++ajKKv3fHYo5LNbGb0u+SqW/nVzBzP+l+66tG/U032HmupZcDlD59YuBgUsH6HQA5V6OvAxR1Pbu85O4Q/S8V/5md/RPNAAnrnlZ4VtenojqNa0EOmm8QNa5zBzAoKUA0biVnxqOEza/9n1cyPq7btejJTF0S0B5Lkj4xfc3+RRzTJkP87OkYUCtmIW/EwsfofVzR+L9pLopabXxJ2awvPH5sSZCqQraqUVAiIe5xSVMUZ5/o1JpBUimlspSnORHrR2DFH6IwErnDQI/t39sS8H9pU+7pCV0iFriy9kophz2Wn6Be9aichJ6BpkvH1ifqLbxOWxwdSrJpEO/rQfVWOgup0idTKn9bYhBieMZpP5a+5eNG/L5ldFUAVztbQvSL1dzozUa+KEtceVC2Tk1W9rfiYOcST5HdfwpmJtIr6SplYqFjevxTi8Si86Riawuc8HmjDVfU18WVMVcan2U78JRnXzxPhn44WamlO3mC3unRdJ+ax8kR5jE0zTt3mwl5/Za74EzRvel+KyyUCL7EWayP9nO0Hc5JUohe8Mh5NrSGgQiAq9JEAs//tMobTnzBEbyDcwbAXlxDz+zEMt68geTzMMZREqIvQBWEcwmqEvQjXEFJYIOcjtEAYgTANYQnCBoSDB/wb+++jLKF/aZ/9JAvsPBCslki5ftlPXxGJu1ti75vvhfhpltj5B9GIv4iQ+DCfFOLTW2Hnp2dFfGOEJId58a2w82hA/+A+y381H4Ymdh4LHhfsfeoJUH/Ypx4r7wURcvz0DQhrP3SSX/ZDR7li51GgQHxZQ8zvR5A4jyt2Pgbcw3Ii8cBV7DwHEYiPuoHdL8bI8S6u2HkeA12x243wH2y3v9d+6jrY5TV2Q8YFEsdD2ikQ8eN0sPNZeLn9If8MVj+gkfgjNwgrX0Mb4k+4YY+vRcSndscej6yI79KJncdBEYlruUNY/aaL+IHuEFb/xLlj9zPpL/2clo7hUSSOTsfeD5zsP9Tev7ZrtS+Sz8YXwmrXXsTfRAgdrgt+GN+UEmlX5Dr0SJzHDzv/qJAfdv5Col/yAOj6YY9vC8TvbcLOg+Hlh52H5AgSj/PDzjtB+ss8rEZ+P3rY/34Q1vwk+2V+jvph50FcRHyUK3beDJQ/su74Y+fbZ0V8SX8=
*/