//=======================================================================
// Copyright 2013 University of Warsaw.
// Authors: Piotr Wygocki
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//
//
// This algorithm is described in "Network Flows: Theory, Algorithms, and
// Applications"
// by Ahuja, Magnanti, Orlin.

#ifndef BOOST_GRAPH_CYCLE_CANCELING_HPP
#define BOOST_GRAPH_CYCLE_CANCELING_HPP

#include <numeric>

#include <boost/property_map/property_map.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/pending/indirect_cmp.hpp>
#include <boost/graph/bellman_ford_shortest_paths.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/detail/augment.hpp>
#include <boost/graph/find_flow_cost.hpp>

namespace boost
{

namespace detail
{

    template < typename PredEdgeMap, typename Vertex >
    class RecordEdgeMapAndCycleVertex
    : public bellman_visitor<
          edge_predecessor_recorder< PredEdgeMap, on_edge_relaxed > >
    {
        typedef edge_predecessor_recorder< PredEdgeMap, on_edge_relaxed >
            PredRec;

    public:
        RecordEdgeMapAndCycleVertex(PredEdgeMap pred, Vertex& v)
        : bellman_visitor< PredRec >(PredRec(pred)), m_v(v), m_pred(pred)
        {
        }

        template < typename Graph, typename Edge >
        void edge_not_minimized(Edge e, const Graph& g) const
        {
            typename graph_traits< Graph >::vertices_size_type n
                = num_vertices(g) + 1;

            // edge e is not minimized but does not have to be on the negative
            // weight cycle to find vertex on negative wieight cycle we move n+1
            // times backword in the PredEdgeMap graph.
            while (n > 0)
            {
                e = get(m_pred, source(e, g));
                --n;
            }
            m_v = source(e, g);
        }

    private:
        Vertex& m_v;
        PredEdgeMap m_pred;
    };

} // detail

template < class Graph, class Pred, class Distance, class Reversed,
    class ResidualCapacity, class Weight >
void cycle_canceling(const Graph& g, Weight weight, Reversed rev,
    ResidualCapacity residual_capacity, Pred pred, Distance distance)
{
    typedef filtered_graph< const Graph, is_residual_edge< ResidualCapacity > >
        ResGraph;
    ResGraph gres = detail::residual_graph(g, residual_capacity);

    typedef graph_traits< ResGraph > ResGTraits;
    typedef graph_traits< Graph > GTraits;
    typedef typename ResGTraits::edge_descriptor edge_descriptor;
    typedef typename ResGTraits::vertex_descriptor vertex_descriptor;

    typename GTraits::vertices_size_type N = num_vertices(g);

    BGL_FORALL_VERTICES_T(v, g, Graph)
    {
        put(pred, v, edge_descriptor());
        put(distance, v, 0);
    }

    vertex_descriptor cycleStart;
    while (!bellman_ford_shortest_paths(gres, N,
        weight_map(weight).distance_map(distance).visitor(
            detail::RecordEdgeMapAndCycleVertex< Pred, vertex_descriptor >(
                pred, cycleStart))))
    {

        detail::augment(
            g, cycleStart, cycleStart, pred, residual_capacity, rev);

        BGL_FORALL_VERTICES_T(v, g, Graph)
        {
            put(pred, v, edge_descriptor());
            put(distance, v, 0);
        }
    }
}

// in this namespace argument dispatching takes place
namespace detail
{

    template < class Graph, class P, class T, class R, class ResidualCapacity,
        class Weight, class Reversed, class Pred, class Distance >
    void cycle_canceling_dispatch2(const Graph& g, Weight weight, Reversed rev,
        ResidualCapacity residual_capacity, Pred pred, Distance dist,
        const bgl_named_params< P, T, R >& params)
    {
        cycle_canceling(g, weight, rev, residual_capacity, pred, dist);
    }

    // setting default distance map
    template < class Graph, class P, class T, class R, class Pred,
        class ResidualCapacity, class Weight, class Reversed >
    void cycle_canceling_dispatch2(Graph& g, Weight weight, Reversed rev,
        ResidualCapacity residual_capacity, Pred pred, param_not_found,
        const bgl_named_params< P, T, R >& params)
    {
        typedef typename property_traits< Weight >::value_type D;

        std::vector< D > d_map(num_vertices(g));

        cycle_canceling(g, weight, rev, residual_capacity, pred,
            make_iterator_property_map(d_map.begin(),
                choose_const_pmap(
                    get_param(params, vertex_index), g, vertex_index)));
    }

    template < class Graph, class P, class T, class R, class ResidualCapacity,
        class Weight, class Reversed, class Pred >
    void cycle_canceling_dispatch1(Graph& g, Weight weight, Reversed rev,
        ResidualCapacity residual_capacity, Pred pred,
        const bgl_named_params< P, T, R >& params)
    {
        cycle_canceling_dispatch2(g, weight, rev, residual_capacity, pred,
            get_param(params, vertex_distance), params);
    }

    // setting default predecessors map
    template < class Graph, class P, class T, class R, class ResidualCapacity,
        class Weight, class Reversed >
    void cycle_canceling_dispatch1(Graph& g, Weight weight, Reversed rev,
        ResidualCapacity residual_capacity, param_not_found,
        const bgl_named_params< P, T, R >& params)
    {
        typedef typename graph_traits< Graph >::edge_descriptor edge_descriptor;
        std::vector< edge_descriptor > p_map(num_vertices(g));

        cycle_canceling_dispatch2(g, weight, rev, residual_capacity,
            make_iterator_property_map(p_map.begin(),
                choose_const_pmap(
                    get_param(params, vertex_index), g, vertex_index)),
            get_param(params, vertex_distance), params);
    }

} // detail

template < class Graph, class P, class T, class R >
void cycle_canceling(Graph& g, const bgl_named_params< P, T, R >& params)
{
    cycle_canceling_dispatch1(g,
        choose_const_pmap(get_param(params, edge_weight), g, edge_weight),
        choose_const_pmap(get_param(params, edge_reverse), g, edge_reverse),
        choose_pmap(get_param(params, edge_residual_capacity), g,
            edge_residual_capacity),
        get_param(params, vertex_predecessor), params);
}

template < class Graph > void cycle_canceling(Graph& g)
{
    bgl_named_params< int, buffer_param_t > params(0);
    cycle_canceling(g, params);
}

}

#endif /* BOOST_GRAPH_CYCLE_CANCELING_HPP */

/* cycle_canceling.hpp
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
*/