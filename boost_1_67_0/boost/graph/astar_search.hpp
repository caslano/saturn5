

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