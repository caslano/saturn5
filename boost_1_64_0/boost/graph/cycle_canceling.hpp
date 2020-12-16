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
L14zvZfcyP9up/f08d/N48RjyPbOtP8NEeSm5Km0MQ1yHsyc9HwwSk8fYB0VKbIe7TbdhcVV0nIuEbPdm3vesfBm/NIu9chOmrryAOUCfeG7yX0QWeSrtDZWY+Nqsm19juhMW+4u194/q/zW1CZdo+Dh5whWvs3a/XnXV4QyJPY8//T8Wb3PYEv4eWiftyU9lznJOXC9ep3NnMuUVnNrshkv9kp/QA6HFc9kpZTzwfzQSPTd9+eKlvPmr2T8jqRsCXafX6U7QuKjnAfbZ7mrxLyyTIJG03eaw9S9e/vflqc72jtNeRIPn+24Z8K+X1mMuMWSmzW953GIlYDrfETeXWKr17o65hG9pbkdHqT0NvdeLfmt/h7+TVIuxvXUfue23naIv0Q8KBcR9chrcq857cHQvbOJaY91ULUqirlf6cLJgNppVVm36Jv78CWZvd5JcptvA8UjzJX2xlLp/dfyW/RlucgdEWtfuJjipbb0WfP+8lWTOWHNcyaZXi8znsj3KM5Te/X79PBTSa1Nx+jWi1uJHvvp7n21QVRk575enPAmc2zy+tzn69RI9L/C2lvACQ9rtVQSPo4FNEml7Tc3/5yIO5aE5X486dsHgkGJ77MlTtq/Vr62U0vb0Fv9qbWFbLKo5Lw89oWzr++6fNG3JukTz7z3iQe3m2i59skFlMgHia32Y6RYeP3jAMbrm073Jn3ZSzIosbGcG3OqzThrI/dOyqFGKMyLKq2St6jSKrmLZD8qv0NP54d1RpIlBETdae0E7HDM05kDiez9x/Z32PgixQQr9YFdGInCwiDjsDDISAQlErIX1xUGvW5Co+U63oVVpT9xA3+rguJBpf7AsQcrvPKjf5u9Wzgpe0sl5zgkou/yVjw+hDcQpJf7WpFKuokC+OYOA1F73JlUhSPKWHe9irjtZ26ypG192Zi+ccTsyJRTEezznSkTsH7nFg+SUpDCsR2ucI1/Mlnepx01OU+5NxnbwvVRK9nZfXSsl4apQxsMhHILIl90Ub2MoX2khgjFhfzUK1oVlJJo20vE5Kz0dh49596XKvXDLWrlTY3zhY7bwPGifXpgEA0aj0aOj+3OxMwdL94DRjkWze6A7bN0BxwncrrTyKr3UgCNrZt4C4lPOKt97EizXvF/k15Vgf8onYIpp31e0sx8fYGj+Gg3HKix/Ge2C2LIe9P7E9jkZgz4LiwURlecU5fhWbIU4l107fMRU/z23Wwd0CvstLV6hBPeWXlVi0XnFSg9fewzpa3Lhxfe71Tbg5GWoDEx95ukl8TSN5Q3CHE+aNI69o7dxPmmX4vdiJiNsO9NF1Vw4/oGRsl9bii/qA22Q4WddbDPTQfmy0U5+9WOV0oOWLYX0NfrTrdMPzoXjWmPF7tw/T6rRerLXoQKxEg+p5c9PDhHMCN9qJtOQ6anSS8u1SM9vMlp7zNydr+liIufDnMu0a9exS8RXP1p8dZ5x3WYn9zaS//yXkk6s/112nBckGQ2DWTYNyZO6yqwka0aG8JOHfi8FFo5a/A5r85q13B5K7ruIl5lckDbkOQIvrhSL5BKLDFx91KoHaVTK+VINFE4v5/TBlL2dKmzCp22nC5vwf6eKNT6eEcpSeIv4q39UB5/evpMWCgg5jfKAKyLXV4Kw3hLDmXGM5muasn2Vv5+qSscU0bSTtjYG2H6Une8mPPaPx11/e2RdiSbNNLFphW/xSDLe0l5sXKrVYco9jxpdIP0SFcvb9qY6pTpngkH8gxiCcQuEcFK67YVvRFW/7YShNELVppiZvQ8/rtKRLZSQPv/JuHTb+h4QXHlcffi/huU7Ze+1HMuKDNSJPONxgmppB4mSG/VPgx4jgyPIB0=
*/