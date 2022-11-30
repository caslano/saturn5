

//
//=======================================================================
// Copyright (c) 2004 Kristopher Beevers
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//

#ifndef BOOST_GRAPH_ASTAR_SEARCH_HPP
#define BOOST_GRAPH_ASTAR_SEARCH_HPP

#include <functional>
#include <vector>
#include <boost/limits.hpp>
#include <boost/throw_exception.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/relax.hpp>
#include <boost/graph/exception.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/detail/d_ary_heap.hpp>
#include <boost/graph/property_maps/constant_property_map.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/property_map/vector_property_map.hpp>
#include <boost/property_map/function_property_map.hpp>
#include <boost/concept/assert.hpp>

namespace boost
{

template < class Heuristic, class Graph > struct AStarHeuristicConcept
{
    void constraints()
    {
        BOOST_CONCEPT_ASSERT((CopyConstructibleConcept< Heuristic >));
        h(u);
    }
    Heuristic h;
    typename graph_traits< Graph >::vertex_descriptor u;
};

template < class Graph, class CostType > class astar_heuristic
{
public:
    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
    typedef Vertex argument_type;
    typedef CostType result_type;
    astar_heuristic() {}
    CostType operator()(Vertex u) { return static_cast< CostType >(0); }
};

template < class Visitor, class Graph > struct AStarVisitorConcept
{
    void constraints()
    {
        BOOST_CONCEPT_ASSERT((CopyConstructibleConcept< Visitor >));
        vis.initialize_vertex(u, g);
        vis.discover_vertex(u, g);
        vis.examine_vertex(u, g);
        vis.examine_edge(e, g);
        vis.edge_relaxed(e, g);
        vis.edge_not_relaxed(e, g);
        vis.black_target(e, g);
        vis.finish_vertex(u, g);
    }
    Visitor vis;
    Graph g;
    typename graph_traits< Graph >::vertex_descriptor u;
    typename graph_traits< Graph >::edge_descriptor e;
};

template < class Visitors = null_visitor >
class astar_visitor : public bfs_visitor< Visitors >
{
public:
    astar_visitor() {}
    astar_visitor(Visitors vis) : bfs_visitor< Visitors >(vis) {}

    template < class Edge, class Graph >
    void edge_relaxed(Edge e, const Graph& g)
    {
        invoke_visitors(this->m_vis, e, g, on_edge_relaxed());
    }
    template < class Edge, class Graph >
    void edge_not_relaxed(Edge e, const Graph& g)
    {
        invoke_visitors(this->m_vis, e, g, on_edge_not_relaxed());
    }

private:
    template < class Edge, class Graph > void tree_edge(Edge e, const Graph& g)
    {
    }
    template < class Edge, class Graph >
    void non_tree_edge(Edge e, const Graph& g)
    {
    }
};
template < class Visitors >
astar_visitor< Visitors > make_astar_visitor(Visitors vis)
{
    return astar_visitor< Visitors >(vis);
}
typedef astar_visitor<> default_astar_visitor;

namespace detail
{

    template < class AStarHeuristic, class UniformCostVisitor,
        class UpdatableQueue, class PredecessorMap, class CostMap,
        class DistanceMap, class WeightMap, class ColorMap,
        class BinaryFunction, class BinaryPredicate >
    struct astar_bfs_visitor
    {

        typedef typename property_traits< CostMap >::value_type C;
        typedef typename property_traits< ColorMap >::value_type ColorValue;
        typedef color_traits< ColorValue > Color;
        typedef
            typename property_traits< DistanceMap >::value_type distance_type;

        astar_bfs_visitor(AStarHeuristic h, UniformCostVisitor vis,
            UpdatableQueue& Q, PredecessorMap p, CostMap c, DistanceMap d,
            WeightMap w, ColorMap col, BinaryFunction combine,
            BinaryPredicate compare, C zero)
        : m_h(h)
        , m_vis(vis)
        , m_Q(Q)
        , m_predecessor(p)
        , m_cost(c)
        , m_distance(d)
        , m_weight(w)
        , m_color(col)
        , m_combine(combine)
        , m_compare(compare)
        , m_zero(zero)
        {
        }

        template < class Vertex, class Graph >
        void initialize_vertex(Vertex u, const Graph& g)
        {
            m_vis.initialize_vertex(u, g);
        }
        template < class Vertex, class Graph >
        void discover_vertex(Vertex u, const Graph& g)
        {
            m_vis.discover_vertex(u, g);
        }
        template < class Vertex, class Graph >
        void examine_vertex(Vertex u, const Graph& g)
        {
            m_vis.examine_vertex(u, g);
        }
        template < class Vertex, class Graph >
        void finish_vertex(Vertex u, const Graph& g)
        {
            m_vis.finish_vertex(u, g);
        }
        template < class Edge, class Graph >
        void examine_edge(Edge e, const Graph& g)
        {
            if (m_compare(get(m_weight, e), m_zero))
                BOOST_THROW_EXCEPTION(negative_edge());
            m_vis.examine_edge(e, g);
        }
        template < class Edge, class Graph >
        void non_tree_edge(Edge, const Graph&)
        {
        }

        template < class Edge, class Graph >
        void tree_edge(Edge e, const Graph& g)
        {
            using boost::get;
            bool m_decreased = relax(e, g, m_weight, m_predecessor, m_distance,
                m_combine, m_compare);

            if (m_decreased)
            {
                m_vis.edge_relaxed(e, g);
                put(m_cost, target(e, g),
                    m_combine(
                        get(m_distance, target(e, g)), m_h(target(e, g))));
            }
            else
                m_vis.edge_not_relaxed(e, g);
        }

        template < class Edge, class Graph >
        void gray_target(Edge e, const Graph& g)
        {
            using boost::get;
            bool m_decreased = relax(e, g, m_weight, m_predecessor, m_distance,
                m_combine, m_compare);

            if (m_decreased)
            {
                put(m_cost, target(e, g),
                    m_combine(
                        get(m_distance, target(e, g)), m_h(target(e, g))));
                m_Q.update(target(e, g));
                m_vis.edge_relaxed(e, g);
            }
            else
                m_vis.edge_not_relaxed(e, g);
        }

        template < class Edge, class Graph >
        void black_target(Edge e, const Graph& g)
        {
            using boost::get;
            bool m_decreased = relax(e, g, m_weight, m_predecessor, m_distance,
                m_combine, m_compare);

            if (m_decreased)
            {
                m_vis.edge_relaxed(e, g);
                put(m_cost, target(e, g),
                    m_combine(
                        get(m_distance, target(e, g)), m_h(target(e, g))));
                m_Q.push(target(e, g));
                put(m_color, target(e, g), Color::gray());
                m_vis.black_target(e, g);
            }
            else
                m_vis.edge_not_relaxed(e, g);
        }

        AStarHeuristic m_h;
        UniformCostVisitor m_vis;
        UpdatableQueue& m_Q;
        PredecessorMap m_predecessor;
        CostMap m_cost;
        DistanceMap m_distance;
        WeightMap m_weight;
        ColorMap m_color;
        BinaryFunction m_combine;
        BinaryPredicate m_compare;
        C m_zero;
    };

} // namespace detail

template < typename VertexListGraph, typename AStarHeuristic,
    typename AStarVisitor, typename PredecessorMap, typename CostMap,
    typename DistanceMap, typename WeightMap, typename ColorMap,
    typename VertexIndexMap, typename CompareFunction, typename CombineFunction,
    typename CostInf, typename CostZero >
inline void astar_search_no_init(const VertexListGraph& g,
    typename graph_traits< VertexListGraph >::vertex_descriptor s,
    AStarHeuristic h, AStarVisitor vis, PredecessorMap predecessor,
    CostMap cost, DistanceMap distance, WeightMap weight, ColorMap color,
    VertexIndexMap index_map, CompareFunction compare, CombineFunction combine,
    CostInf /*inf*/, CostZero zero)
{
    typedef typename graph_traits< VertexListGraph >::vertex_descriptor Vertex;
    typedef boost::vector_property_map< std::size_t, VertexIndexMap >
        IndexInHeapMap;
    IndexInHeapMap index_in_heap(index_map);
    typedef d_ary_heap_indirect< Vertex, 4, IndexInHeapMap, CostMap,
        CompareFunction >
        MutableQueue;
    MutableQueue Q(cost, index_in_heap, compare);

    detail::astar_bfs_visitor< AStarHeuristic, AStarVisitor, MutableQueue,
        PredecessorMap, CostMap, DistanceMap, WeightMap, ColorMap,
        CombineFunction, CompareFunction >
        bfs_vis(h, vis, Q, predecessor, cost, distance, weight, color, combine,
            compare, zero);

    breadth_first_visit(g, s, Q, bfs_vis, color);
}

namespace graph_detail
{
    template < typename A, typename B > struct select1st
    {
        typedef std::pair< A, B > argument_type;
        typedef A result_type;
        A operator()(const std::pair< A, B >& p) const { return p.first; }
    };
}

template < typename VertexListGraph, typename AStarHeuristic,
    typename AStarVisitor, typename PredecessorMap, typename CostMap,
    typename DistanceMap, typename WeightMap, typename CompareFunction,
    typename CombineFunction, typename CostInf, typename CostZero >
inline void astar_search_no_init_tree(const VertexListGraph& g,
    typename graph_traits< VertexListGraph >::vertex_descriptor s,
    AStarHeuristic h, AStarVisitor vis, PredecessorMap predecessor,
    CostMap cost, DistanceMap distance, WeightMap weight,
    CompareFunction compare, CombineFunction combine, CostInf /*inf*/,
    CostZero zero)
{
    typedef typename graph_traits< VertexListGraph >::vertex_descriptor Vertex;
    typedef typename property_traits< DistanceMap >::value_type Distance;
    typedef d_ary_heap_indirect< std::pair< Distance, Vertex >, 4,
        null_property_map< std::pair< Distance, Vertex >, std::size_t >,
        function_property_map< graph_detail::select1st< Distance, Vertex >,
            std::pair< Distance, Vertex > >,
        CompareFunction >
        MutableQueue;
    MutableQueue Q(make_function_property_map< std::pair< Distance, Vertex > >(
                       graph_detail::select1st< Distance, Vertex >()),
        null_property_map< std::pair< Distance, Vertex >, std::size_t >(),
        compare);

    vis.discover_vertex(s, g);
    Q.push(std::make_pair(get(cost, s), s));
    while (!Q.empty())
    {
        Vertex v;
        Distance v_rank;
        boost::tie(v_rank, v) = Q.top();
        Q.pop();
        vis.examine_vertex(v, g);
        BGL_FORALL_OUTEDGES_T(v, e, g, VertexListGraph)
        {
            Vertex w = target(e, g);
            vis.examine_edge(e, g);
            Distance e_weight = get(weight, e);
            if (compare(e_weight, zero))
                BOOST_THROW_EXCEPTION(negative_edge());
            bool decreased
                = relax(e, g, weight, predecessor, distance, combine, compare);
            combine(get(distance, v), e_weight);
            if (decreased)
            {
                vis.edge_relaxed(e, g);
                Distance w_rank = combine(get(distance, w), h(w));
                put(cost, w, w_rank);
                vis.discover_vertex(w, g);
                Q.push(std::make_pair(w_rank, w));
            }
            else
            {
                vis.edge_not_relaxed(e, g);
            }
        }
        vis.finish_vertex(v, g);
    }
}

// Non-named parameter interface
template < typename VertexListGraph, typename AStarHeuristic,
    typename AStarVisitor, typename PredecessorMap, typename CostMap,
    typename DistanceMap, typename WeightMap, typename VertexIndexMap,
    typename ColorMap, typename CompareFunction, typename CombineFunction,
    typename CostInf, typename CostZero >
inline void astar_search(const VertexListGraph& g,
    typename graph_traits< VertexListGraph >::vertex_descriptor s,
    AStarHeuristic h, AStarVisitor vis, PredecessorMap predecessor,
    CostMap cost, DistanceMap distance, WeightMap weight,
    VertexIndexMap index_map, ColorMap color, CompareFunction compare,
    CombineFunction combine, CostInf inf, CostZero zero)
{

    typedef typename property_traits< ColorMap >::value_type ColorValue;
    typedef color_traits< ColorValue > Color;
    typename graph_traits< VertexListGraph >::vertex_iterator ui, ui_end;
    for (boost::tie(ui, ui_end) = vertices(g); ui != ui_end; ++ui)
    {
        put(color, *ui, Color::white());
        put(distance, *ui, inf);
        put(cost, *ui, inf);
        put(predecessor, *ui, *ui);
        vis.initialize_vertex(*ui, g);
    }
    put(distance, s, zero);
    put(cost, s, h(s));

    astar_search_no_init(g, s, h, vis, predecessor, cost, distance, weight,
        color, index_map, compare, combine, inf, zero);
}

// Non-named parameter interface
template < typename VertexListGraph, typename AStarHeuristic,
    typename AStarVisitor, typename PredecessorMap, typename CostMap,
    typename DistanceMap, typename WeightMap, typename CompareFunction,
    typename CombineFunction, typename CostInf, typename CostZero >
inline void astar_search_tree(const VertexListGraph& g,
    typename graph_traits< VertexListGraph >::vertex_descriptor s,
    AStarHeuristic h, AStarVisitor vis, PredecessorMap predecessor,
    CostMap cost, DistanceMap distance, WeightMap weight,
    CompareFunction compare, CombineFunction combine, CostInf inf,
    CostZero zero)
{

    typename graph_traits< VertexListGraph >::vertex_iterator ui, ui_end;
    for (boost::tie(ui, ui_end) = vertices(g); ui != ui_end; ++ui)
    {
        put(distance, *ui, inf);
        put(cost, *ui, inf);
        put(predecessor, *ui, *ui);
        vis.initialize_vertex(*ui, g);
    }
    put(distance, s, zero);
    put(cost, s, h(s));

    astar_search_no_init_tree(g, s, h, vis, predecessor, cost, distance, weight,
        compare, combine, inf, zero);
}

// Named parameter interfaces
template < typename VertexListGraph, typename AStarHeuristic, typename P,
    typename T, typename R >
void astar_search(const VertexListGraph& g,
    typename graph_traits< VertexListGraph >::vertex_descriptor s,
    AStarHeuristic h, const bgl_named_params< P, T, R >& params)
{
    using namespace boost::graph::keywords;
    typedef bgl_named_params< P, T, R > params_type;
    BOOST_GRAPH_DECLARE_CONVERTED_PARAMETERS(params_type, params)

    // Distance type is the value type of the distance map if there is one,
    // otherwise the value type of the weight map.
    typedef
        typename boost::detail::override_const_property_result< arg_pack_type,
            boost::graph::keywords::tag::weight_map, edge_weight_t,
            VertexListGraph >::type weight_map_type;
    typedef typename boost::property_traits< weight_map_type >::value_type D;
    const D inf = arg_pack[_distance_inf || detail::get_max< D >()];
    const D zero_actual = D();
    const D zero_d = arg_pack[_distance_zero | zero_actual];
    null_visitor null_vis;
    astar_visitor< null_visitor > default_visitor(null_vis);
    typename boost::parameter::binding< arg_pack_type,
        boost::graph::keywords::tag::visitor, dummy_property_map& >::type vis
        = arg_pack[_visitor | default_visitor];
    dummy_property_map dummy_prop;
    typename boost::parameter::binding< arg_pack_type,
        boost::graph::keywords::tag::predecessor_map,
        dummy_property_map& >::type pred_map
        = arg_pack[_predecessor_map | dummy_prop];
    boost::detail::make_property_map_from_arg_pack_gen<
        boost::graph::keywords::tag::rank_map, D >
        rank_map_gen(zero_actual);
    typename boost::detail::map_maker< VertexListGraph, arg_pack_type,
        boost::graph::keywords::tag::rank_map, D >::map_type r_map
        = rank_map_gen(g, arg_pack);
    boost::detail::make_property_map_from_arg_pack_gen<
        boost::graph::keywords::tag::distance_map, D >
        dist_map_gen(zero_actual);
    typename boost::detail::map_maker< VertexListGraph, arg_pack_type,
        boost::graph::keywords::tag::distance_map, D >::map_type dist_map
        = dist_map_gen(g, arg_pack);
    weight_map_type w_map = detail::override_const_property(
        arg_pack, _weight_map, g, edge_weight);
    typename boost::detail::override_const_property_result< arg_pack_type,
        boost::graph::keywords::tag::vertex_index_map, vertex_index_t,
        VertexListGraph >::type v_i_map
        = detail::override_const_property(
            arg_pack, _vertex_index_map, g, vertex_index);
    typename boost::detail::map_maker< VertexListGraph, arg_pack_type,
        boost::graph::keywords::tag::color_map,
        boost::default_color_type >::map_type c_map
        = boost::detail::make_color_map_from_arg_pack(g, arg_pack);
    std::less< D > default_compare;
    typename boost::parameter::binding< arg_pack_type,
        boost::graph::keywords::tag::distance_compare, std::less< D >& >::type
        dist_comp
        = arg_pack[_distance_compare | default_compare];
    closed_plus< D > default_combine(inf);
    typename boost::parameter::binding< arg_pack_type,
        boost::graph::keywords::tag::distance_combine, closed_plus< D >& >::type
        dist_comb
        = arg_pack[_distance_combine | default_combine];
    astar_search(g, s, h, vis, pred_map, r_map, dist_map, w_map, v_i_map, c_map,
        dist_comp, dist_comb, inf, zero_d);
}

template < typename VertexListGraph, typename AStarHeuristic, typename P,
    typename T, typename R >
void astar_search_tree(const VertexListGraph& g,
    typename graph_traits< VertexListGraph >::vertex_descriptor s,
    AStarHeuristic h, const bgl_named_params< P, T, R >& params)
{
    using namespace boost::graph::keywords;
    typedef bgl_named_params< P, T, R > params_type;
    BOOST_GRAPH_DECLARE_CONVERTED_PARAMETERS(params_type, params)

    // Distance type is the value type of the distance map if there is one,
    // otherwise the value type of the weight map.
    typedef
        typename boost::detail::override_const_property_result< arg_pack_type,
            boost::graph::keywords::tag::weight_map, edge_weight_t,
            VertexListGraph >::type weight_map_type;
    typedef typename boost::property_traits< weight_map_type >::value_type D;
    const D inf = arg_pack[_distance_inf || detail::get_max< D >()];
    const D zero_actual = D();
    const D zero_d = arg_pack[_distance_zero | zero_actual];
    null_visitor null_vis;
    astar_visitor< null_visitor > default_visitor(null_vis);
    typename boost::parameter::binding< arg_pack_type,
        boost::graph::keywords::tag::visitor, dummy_property_map& >::type vis
        = arg_pack[_visitor | default_visitor];
    dummy_property_map dummy_prop;
    typename boost::parameter::binding< arg_pack_type,
        boost::graph::keywords::tag::predecessor_map,
        dummy_property_map& >::type pred_map
        = arg_pack[_predecessor_map | dummy_prop];
    boost::detail::make_property_map_from_arg_pack_gen<
        boost::graph::keywords::tag::rank_map, D >
        rank_map_gen(zero_actual);
    typename boost::detail::map_maker< VertexListGraph, arg_pack_type,
        boost::graph::keywords::tag::rank_map, D >::map_type r_map
        = rank_map_gen(g, arg_pack);
    boost::detail::make_property_map_from_arg_pack_gen<
        boost::graph::keywords::tag::distance_map, D >
        dist_map_gen(zero_actual);
    typename boost::detail::map_maker< VertexListGraph, arg_pack_type,
        boost::graph::keywords::tag::distance_map, D >::map_type dist_map
        = dist_map_gen(g, arg_pack);
    weight_map_type w_map = detail::override_const_property(
        arg_pack, _weight_map, g, edge_weight);
    std::less< D > default_compare;
    typename boost::parameter::binding< arg_pack_type,
        boost::graph::keywords::tag::distance_compare, std::less< D >& >::type
        dist_comp
        = arg_pack[_distance_compare | default_compare];
    closed_plus< D > default_combine(inf);
    typename boost::parameter::binding< arg_pack_type,
        boost::graph::keywords::tag::distance_combine, closed_plus< D >& >::type
        dist_comb
        = arg_pack[_distance_combine | default_combine];
    astar_search_tree(g, s, h, vis, pred_map, r_map, dist_map, w_map, dist_comp,
        dist_comb, inf, zero_d);
}

template < typename VertexListGraph, typename AStarHeuristic, typename P,
    typename T, typename R >
void astar_search_no_init(const VertexListGraph& g,
    typename graph_traits< VertexListGraph >::vertex_descriptor s,
    AStarHeuristic h, const bgl_named_params< P, T, R >& params)
{
    using namespace boost::graph::keywords;
    typedef bgl_named_params< P, T, R > params_type;
    BOOST_GRAPH_DECLARE_CONVERTED_PARAMETERS(params_type, params)
    typedef
        typename boost::detail::override_const_property_result< arg_pack_type,
            boost::graph::keywords::tag::weight_map, edge_weight_t,
            VertexListGraph >::type weight_map_type;
    typedef typename boost::property_traits< weight_map_type >::value_type D;
    const D inf = arg_pack[_distance_inf || detail::get_max< D >()];
    const D zero_actual = D();
    const D zero_d = arg_pack[_distance_zero | zero_actual];
    null_visitor null_vis;
    astar_visitor< null_visitor > default_visitor(null_vis);
    typename boost::parameter::binding< arg_pack_type,
        boost::graph::keywords::tag::visitor, dummy_property_map& >::type vis
        = arg_pack[_visitor | default_visitor];
    dummy_property_map dummy_prop;
    typename boost::parameter::binding< arg_pack_type,
        boost::graph::keywords::tag::predecessor_map,
        dummy_property_map& >::type pred_map
        = arg_pack[_predecessor_map | dummy_prop];
    boost::detail::make_property_map_from_arg_pack_gen<
        boost::graph::keywords::tag::rank_map, D >
        rank_map_gen(zero_actual);
    typename boost::detail::map_maker< VertexListGraph, arg_pack_type,
        boost::graph::keywords::tag::rank_map, D >::map_type r_map
        = rank_map_gen(g, arg_pack);
    boost::detail::make_property_map_from_arg_pack_gen<
        boost::graph::keywords::tag::distance_map, D >
        dist_map_gen(zero_actual);
    typename boost::detail::map_maker< VertexListGraph, arg_pack_type,
        boost::graph::keywords::tag::distance_map, D >::map_type dist_map
        = dist_map_gen(g, arg_pack);
    weight_map_type w_map = detail::override_const_property(
        arg_pack, _weight_map, g, edge_weight);
    typename boost::detail::map_maker< VertexListGraph, arg_pack_type,
        boost::graph::keywords::tag::color_map,
        boost::default_color_type >::map_type c_map
        = boost::detail::make_color_map_from_arg_pack(g, arg_pack);
    typename boost::detail::override_const_property_result< arg_pack_type,
        boost::graph::keywords::tag::vertex_index_map, vertex_index_t,
        VertexListGraph >::type v_i_map
        = detail::override_const_property(
            arg_pack, _vertex_index_map, g, vertex_index);
    std::less< D > default_compare;
    typename boost::parameter::binding< arg_pack_type,
        boost::graph::keywords::tag::distance_compare, std::less< D >& >::type
        dist_comp
        = arg_pack[_distance_compare | default_compare];
    closed_plus< D > default_combine(inf);
    typename boost::parameter::binding< arg_pack_type,
        boost::graph::keywords::tag::distance_combine, closed_plus< D >& >::type
        dist_comb
        = arg_pack[_distance_combine | default_combine];
    astar_search_no_init(g, s, h, vis, pred_map, r_map, dist_map, w_map, c_map,
        v_i_map, dist_comp, dist_comb, inf, zero_d);
}

template < typename VertexListGraph, typename AStarHeuristic, typename P,
    typename T, typename R >
void astar_search_no_init_tree(const VertexListGraph& g,
    typename graph_traits< VertexListGraph >::vertex_descriptor s,
    AStarHeuristic h, const bgl_named_params< P, T, R >& params)
{
    using namespace boost::graph::keywords;
    typedef bgl_named_params< P, T, R > params_type;
    BOOST_GRAPH_DECLARE_CONVERTED_PARAMETERS(params_type, params)
    typedef
        typename boost::detail::override_const_property_result< arg_pack_type,
            boost::graph::keywords::tag::weight_map, edge_weight_t,
            VertexListGraph >::type weight_map_type;
    typedef typename boost::property_traits< weight_map_type >::value_type D;
    const D inf = arg_pack[_distance_inf || detail::get_max< D >()];
    const D zero_actual = D();
    const D zero_d = arg_pack[_distance_zero | zero_actual];
    null_visitor null_vis;
    astar_visitor< null_visitor > default_visitor(null_vis);
    typename boost::parameter::binding< arg_pack_type,
        boost::graph::keywords::tag::visitor, dummy_property_map& >::type vis
        = arg_pack[_visitor | default_visitor];
    dummy_property_map dummy_prop;
    typename boost::parameter::binding< arg_pack_type,
        boost::graph::keywords::tag::predecessor_map,
        dummy_property_map& >::type pred_map
        = arg_pack[_predecessor_map | dummy_prop];
    boost::detail::make_property_map_from_arg_pack_gen<
        boost::graph::keywords::tag::rank_map, D >
        rank_map_gen(zero_actual);
    typename boost::detail::map_maker< VertexListGraph, arg_pack_type,
        boost::graph::keywords::tag::rank_map, D >::map_type r_map
        = rank_map_gen(g, arg_pack);
    boost::detail::make_property_map_from_arg_pack_gen<
        boost::graph::keywords::tag::distance_map, D >
        dist_map_gen(zero_actual);
    typename boost::detail::map_maker< VertexListGraph, arg_pack_type,
        boost::graph::keywords::tag::distance_map, D >::map_type dist_map
        = dist_map_gen(g, arg_pack);
    weight_map_type w_map = detail::override_const_property(
        arg_pack, _weight_map, g, edge_weight);
    std::less< D > default_compare;
    typename boost::parameter::binding< arg_pack_type,
        boost::graph::keywords::tag::distance_compare, std::less< D >& >::type
        dist_comp
        = arg_pack[_distance_compare | default_compare];
    closed_plus< D > default_combine(inf);
    typename boost::parameter::binding< arg_pack_type,
        boost::graph::keywords::tag::distance_combine, closed_plus< D >& >::type
        dist_comb
        = arg_pack[_distance_combine | default_combine];
    astar_search_no_init_tree(g, s, h, vis, pred_map, r_map, dist_map, w_map,
        dist_comp, dist_comb, inf, zero_d);
}

} // namespace boost

#endif // BOOST_GRAPH_ASTAR_SEARCH_HPP

/* astar_search.hpp
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
*/