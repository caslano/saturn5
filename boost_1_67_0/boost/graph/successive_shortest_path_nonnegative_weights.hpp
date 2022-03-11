//=======================================================================
// Copyright 2013 University of Warsaw.
// Authors: Piotr Wygocki
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//
// This algorithm is described in "Network Flows: Theory, Algorithms, and
// Applications"
// by Ahuja, Magnanti, Orlin.

#ifndef BOOST_GRAPH_SUCCESSIVE_SHORTEST_PATH_HPP
#define BOOST_GRAPH_SUCCESSIVE_SHORTEST_PATH_HPP

#include <numeric>

#include <boost/property_map/property_map.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/pending/indirect_cmp.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/detail/augment.hpp>

namespace boost
{

namespace detail
{

    template < class Graph, class Weight, class Distance, class Reversed >
    class MapReducedWeight
    : public put_get_helper< typename property_traits< Weight >::value_type,
          MapReducedWeight< Graph, Weight, Distance, Reversed > >
    {
        typedef graph_traits< Graph > gtraits;

    public:
        typedef boost::readable_property_map_tag category;
        typedef typename property_traits< Weight >::value_type value_type;
        typedef value_type reference;
        typedef typename gtraits::edge_descriptor key_type;
        MapReducedWeight(const Graph& g, Weight w, Distance d, Reversed r)
        : g_(g), weight_(w), distance_(d), rev_(r)
        {
        }

        reference operator[](key_type v) const
        {
            return get(distance_, source(v, g_)) - get(distance_, target(v, g_))
                + get(weight_, v);
        }

    private:
        const Graph& g_;
        Weight weight_;
        Distance distance_;
        Reversed rev_;
    };

    template < class Graph, class Weight, class Distance, class Reversed >
    MapReducedWeight< Graph, Weight, Distance, Reversed > make_mapReducedWeight(
        const Graph& g, Weight w, Distance d, Reversed r)
    {
        return MapReducedWeight< Graph, Weight, Distance, Reversed >(
            g, w, d, r);
    }

} // detail

template < class Graph, class Capacity, class ResidualCapacity, class Reversed,
    class Pred, class Weight, class Distance, class Distance2,
    class VertexIndex >
void successive_shortest_path_nonnegative_weights(const Graph& g,
    typename graph_traits< Graph >::vertex_descriptor s,
    typename graph_traits< Graph >::vertex_descriptor t, Capacity capacity,
    ResidualCapacity residual_capacity, Weight weight, Reversed rev,
    VertexIndex index, Pred pred, Distance distance, Distance2 distance_prev)
{
    filtered_graph< const Graph, is_residual_edge< ResidualCapacity > > gres
        = detail::residual_graph(g, residual_capacity);
    typedef typename graph_traits< Graph >::edge_descriptor edge_descriptor;

    BGL_FORALL_EDGES_T(e, g, Graph)
    {
        put(residual_capacity, e, get(capacity, e));
    }

    BGL_FORALL_VERTICES_T(v, g, Graph) { put(distance_prev, v, 0); }

    while (true)
    {
        BGL_FORALL_VERTICES_T(v, g, Graph) { put(pred, v, edge_descriptor()); }
        dijkstra_shortest_paths(gres, s,
            weight_map(
                detail::make_mapReducedWeight(gres, weight, distance_prev, rev))
                .distance_map(distance)
                .vertex_index_map(index)
                .visitor(make_dijkstra_visitor(
                    record_edge_predecessors(pred, on_edge_relaxed()))));

        if (get(pred, t) == edge_descriptor())
        {
            break;
        }

        BGL_FORALL_VERTICES_T(v, g, Graph)
        {
            put(distance_prev, v, get(distance_prev, v) + get(distance, v));
        }

        detail::augment(g, s, t, pred, residual_capacity, rev);
    }
}

// in this namespace argument dispatching tak place
namespace detail
{

    template < class Graph, class Capacity, class ResidualCapacity,
        class Weight, class Reversed, class Pred, class Distance,
        class Distance2, class VertexIndex >
    void successive_shortest_path_nonnegative_weights_dispatch3(const Graph& g,
        typename graph_traits< Graph >::vertex_descriptor s,
        typename graph_traits< Graph >::vertex_descriptor t, Capacity capacity,
        ResidualCapacity residual_capacity, Weight weight, Reversed rev,
        VertexIndex index, Pred pred, Distance dist, Distance2 dist_pred)
    {
        successive_shortest_path_nonnegative_weights(g, s, t, capacity,
            residual_capacity, weight, rev, index, pred, dist, dist_pred);
    }

    // setting default distance map
    template < class Graph, class Capacity, class ResidualCapacity,
        class Weight, class Reversed, class Pred, class Distance,
        class VertexIndex >
    void successive_shortest_path_nonnegative_weights_dispatch3(Graph& g,
        typename graph_traits< Graph >::vertex_descriptor s,
        typename graph_traits< Graph >::vertex_descriptor t, Capacity capacity,
        ResidualCapacity residual_capacity, Weight weight, Reversed rev,
        VertexIndex index, Pred pred, Distance dist, param_not_found)
    {
        typedef typename property_traits< Weight >::value_type D;

        std::vector< D > d_map(num_vertices(g));

        successive_shortest_path_nonnegative_weights(g, s, t, capacity,
            residual_capacity, weight, rev, index, pred, dist,
            make_iterator_property_map(d_map.begin(), index));
    }

    template < class Graph, class P, class T, class R, class Capacity,
        class ResidualCapacity, class Weight, class Reversed, class Pred,
        class Distance, class VertexIndex >
    void successive_shortest_path_nonnegative_weights_dispatch2(Graph& g,
        typename graph_traits< Graph >::vertex_descriptor s,
        typename graph_traits< Graph >::vertex_descriptor t, Capacity capacity,
        ResidualCapacity residual_capacity, Weight weight, Reversed rev,
        VertexIndex index, Pred pred, Distance dist,
        const bgl_named_params< P, T, R >& params)
    {
        successive_shortest_path_nonnegative_weights_dispatch3(g, s, t,
            capacity, residual_capacity, weight, rev, index, pred, dist,
            get_param(params, vertex_distance2));
    }

    // setting default distance map
    template < class Graph, class P, class T, class R, class Capacity,
        class ResidualCapacity, class Weight, class Reversed, class Pred,
        class VertexIndex >
    void successive_shortest_path_nonnegative_weights_dispatch2(Graph& g,
        typename graph_traits< Graph >::vertex_descriptor s,
        typename graph_traits< Graph >::vertex_descriptor t, Capacity capacity,
        ResidualCapacity residual_capacity, Weight weight, Reversed rev,
        VertexIndex index, Pred pred, param_not_found,
        const bgl_named_params< P, T, R >& params)
    {
        typedef typename property_traits< Weight >::value_type D;

        std::vector< D > d_map(num_vertices(g));

        successive_shortest_path_nonnegative_weights_dispatch3(g, s, t,
            capacity, residual_capacity, weight, rev, index, pred,
            make_iterator_property_map(d_map.begin(), index),
            get_param(params, vertex_distance2));
    }

    template < class Graph, class P, class T, class R, class Capacity,
        class ResidualCapacity, class Weight, class Reversed, class Pred,
        class VertexIndex >
    void successive_shortest_path_nonnegative_weights_dispatch1(Graph& g,
        typename graph_traits< Graph >::vertex_descriptor s,
        typename graph_traits< Graph >::vertex_descriptor t, Capacity capacity,
        ResidualCapacity residual_capacity, Weight weight, Reversed rev,
        VertexIndex index, Pred pred, const bgl_named_params< P, T, R >& params)
    {
        successive_shortest_path_nonnegative_weights_dispatch2(g, s, t,
            capacity, residual_capacity, weight, rev, index, pred,
            get_param(params, vertex_distance), params);
    }

    // setting default predecessors map
    template < class Graph, class P, class T, class R, class Capacity,
        class ResidualCapacity, class Weight, class Reversed,
        class VertexIndex >
    void successive_shortest_path_nonnegative_weights_dispatch1(Graph& g,
        typename graph_traits< Graph >::vertex_descriptor s,
        typename graph_traits< Graph >::vertex_descriptor t, Capacity capacity,
        ResidualCapacity residual_capacity, Weight weight, Reversed rev,
        VertexIndex index, param_not_found,
        const bgl_named_params< P, T, R >& params)
    {
        typedef typename graph_traits< Graph >::edge_descriptor edge_descriptor;
        std::vector< edge_descriptor > pred_vec(num_vertices(g));

        successive_shortest_path_nonnegative_weights_dispatch2(g, s, t,
            capacity, residual_capacity, weight, rev, index,
            make_iterator_property_map(pred_vec.begin(), index),
            get_param(params, vertex_distance), params);
    }

} // detail

template < class Graph, class P, class T, class R >
void successive_shortest_path_nonnegative_weights(Graph& g,
    typename graph_traits< Graph >::vertex_descriptor s,
    typename graph_traits< Graph >::vertex_descriptor t,
    const bgl_named_params< P, T, R >& params)
{

    return detail::successive_shortest_path_nonnegative_weights_dispatch1(g, s,
        t,
        choose_const_pmap(get_param(params, edge_capacity), g, edge_capacity),
        choose_pmap(get_param(params, edge_residual_capacity), g,
            edge_residual_capacity),
        choose_const_pmap(get_param(params, edge_weight), g, edge_weight),
        choose_const_pmap(get_param(params, edge_reverse), g, edge_reverse),
        choose_const_pmap(get_param(params, vertex_index), g, vertex_index),
        get_param(params, vertex_predecessor), params);
}

template < class Graph >
void successive_shortest_path_nonnegative_weights(Graph& g,
    typename graph_traits< Graph >::vertex_descriptor s,
    typename graph_traits< Graph >::vertex_descriptor t)
{
    bgl_named_params< int, buffer_param_t > params(0);
    successive_shortest_path_nonnegative_weights(g, s, t, params);
}

} // boost
#endif /* BOOST_GRAPH_SUCCESSIVE_SHORTEST_PATH_HPP */

/* successive_shortest_path_nonnegative_weights.hpp
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
*/