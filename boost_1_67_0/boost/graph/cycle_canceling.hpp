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