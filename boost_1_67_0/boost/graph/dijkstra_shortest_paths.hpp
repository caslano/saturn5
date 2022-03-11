//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//
//
// Revision History:
//   04 April 2001: Added named parameter variant. (Jeremy Siek)
//   01 April 2001: Modified to use new <boost/limits.hpp> header. (JMaddock)
//
#ifndef BOOST_GRAPH_DIJKSTRA_HPP
#define BOOST_GRAPH_DIJKSTRA_HPP

#include <functional>
#include <boost/limits.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/relax.hpp>
#include <boost/pending/indirect_cmp.hpp>
#include <boost/graph/exception.hpp>
#include <boost/graph/overloading.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/graph/detail/d_ary_heap.hpp>
#include <boost/graph/two_bit_color_map.hpp>
#include <boost/graph/detail/mpi_include.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/property_map/vector_property_map.hpp>
#include <boost/type_traits.hpp>
#include <boost/concept/assert.hpp>

#ifdef BOOST_GRAPH_DIJKSTRA_TESTING
#include <boost/pending/mutable_queue.hpp>
#endif // BOOST_GRAPH_DIJKSTRA_TESTING

namespace boost
{

/**
 * @brief Updates a particular value in a queue used by Dijkstra's
 * algorithm.
 *
 * This routine is called by Dijkstra's algorithm after it has
 * decreased the distance from the source vertex to the given @p
 * vertex. By default, this routine will just call @c
 * Q.update(vertex). However, other queues may provide more
 * specialized versions of this routine.
 *
 * @param Q             the queue that will be updated.
 * @param vertex        the vertex whose distance has been updated
 * @param old_distance  the previous distance to @p vertex
 */
template < typename Buffer, typename Vertex, typename DistanceType >
inline void dijkstra_queue_update(
    Buffer& Q, Vertex vertex, DistanceType old_distance)
{
    (void)old_distance;
    Q.update(vertex);
}

template < class Visitor, class Graph > struct DijkstraVisitorConcept
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
        vis.finish_vertex(u, g);
    }
    Visitor vis;
    Graph g;
    typename graph_traits< Graph >::vertex_descriptor u;
    typename graph_traits< Graph >::edge_descriptor e;
};

template < class Visitors = null_visitor >
class dijkstra_visitor : public bfs_visitor< Visitors >
{
public:
    dijkstra_visitor() {}
    dijkstra_visitor(Visitors vis) : bfs_visitor< Visitors >(vis) {}

    template < class Edge, class Graph > void edge_relaxed(Edge e, Graph& g)
    {
        invoke_visitors(this->m_vis, e, g, on_edge_relaxed());
    }
    template < class Edge, class Graph > void edge_not_relaxed(Edge e, Graph& g)
    {
        invoke_visitors(this->m_vis, e, g, on_edge_not_relaxed());
    }

private:
    template < class Edge, class Graph > void tree_edge(Edge u, Graph& g) {}
};
template < class Visitors >
dijkstra_visitor< Visitors > make_dijkstra_visitor(Visitors vis)
{
    return dijkstra_visitor< Visitors >(vis);
}
typedef dijkstra_visitor<> default_dijkstra_visitor;

namespace detail
{

    template < class UniformCostVisitor, class UpdatableQueue, class WeightMap,
        class PredecessorMap, class DistanceMap, class BinaryFunction,
        class BinaryPredicate >
    struct dijkstra_bfs_visitor
    {
        typedef typename property_traits< DistanceMap >::value_type D;
        typedef typename property_traits< WeightMap >::value_type W;

        dijkstra_bfs_visitor(UniformCostVisitor vis, UpdatableQueue& Q,
            WeightMap w, PredecessorMap p, DistanceMap d,
            BinaryFunction combine, BinaryPredicate compare, D zero)
        : m_vis(vis)
        , m_Q(Q)
        , m_weight(w)
        , m_predecessor(p)
        , m_distance(d)
        , m_combine(combine)
        , m_compare(compare)
        , m_zero(zero)
        {
        }

        template < class Edge, class Graph > void tree_edge(Edge e, Graph& g)
        {
            bool decreased = relax_target(e, g, m_weight, m_predecessor,
                m_distance, m_combine, m_compare);
            if (decreased)
                m_vis.edge_relaxed(e, g);
            else
                m_vis.edge_not_relaxed(e, g);
        }
        template < class Edge, class Graph > void gray_target(Edge e, Graph& g)
        {
            D old_distance = get(m_distance, target(e, g));

            bool decreased = relax_target(e, g, m_weight, m_predecessor,
                m_distance, m_combine, m_compare);
            if (decreased)
            {
                dijkstra_queue_update(m_Q, target(e, g), old_distance);
                m_vis.edge_relaxed(e, g);
            }
            else
                m_vis.edge_not_relaxed(e, g);
        }

        template < class Vertex, class Graph >
        void initialize_vertex(Vertex u, Graph& g)
        {
            m_vis.initialize_vertex(u, g);
        }
        template < class Edge, class Graph > void non_tree_edge(Edge, Graph&) {}
        template < class Vertex, class Graph >
        void discover_vertex(Vertex u, Graph& g)
        {
            m_vis.discover_vertex(u, g);
        }
        template < class Vertex, class Graph >
        void examine_vertex(Vertex u, Graph& g)
        {
            m_vis.examine_vertex(u, g);
        }
        template < class Edge, class Graph > void examine_edge(Edge e, Graph& g)
        {
            // Test for negative-weight edges:
            //
            // Reasons that other comparisons do not work:
            //
            // m_compare(e_weight, D(0)):
            //    m_compare only needs to work on distances, not weights, and
            //    those types do not need to be the same (bug 8398,
            //    https://svn.boost.org/trac/boost/ticket/8398).
            // m_compare(m_combine(source_dist, e_weight), source_dist):
            //    if m_combine is project2nd (as in prim_minimum_spanning_tree),
            //    this test will claim that the edge weight is negative whenever
            //    the edge weight is less than source_dist, even if both of
            //    those are positive (bug 9012,
            //    https://svn.boost.org/trac/boost/ticket/9012).
            // m_compare(m_combine(e_weight, source_dist), source_dist):
            //    would fix project2nd issue, but documentation only requires
            //    that m_combine be able to take a distance and a weight (in
            //    that order) and return a distance.

            // W e_weight = get(m_weight, e);
            // sd_plus_ew = source_dist + e_weight.
            // D sd_plus_ew = m_combine(source_dist, e_weight);
            // sd_plus_2ew = source_dist + 2 * e_weight.
            // D sd_plus_2ew = m_combine(sd_plus_ew, e_weight);
            // The test here is equivalent to e_weight < 0 if m_combine has a
            // cancellation law, but always returns false when m_combine is a
            // projection operator.
            if (m_compare(m_combine(m_zero, get(m_weight, e)), m_zero))
                boost::throw_exception(negative_edge());
            // End of test for negative-weight edges.

            m_vis.examine_edge(e, g);
        }
        template < class Edge, class Graph > void black_target(Edge, Graph&) {}
        template < class Vertex, class Graph >
        void finish_vertex(Vertex u, Graph& g)
        {
            m_vis.finish_vertex(u, g);
        }

        UniformCostVisitor m_vis;
        UpdatableQueue& m_Q;
        WeightMap m_weight;
        PredecessorMap m_predecessor;
        DistanceMap m_distance;
        BinaryFunction m_combine;
        BinaryPredicate m_compare;
        D m_zero;
    };

} // namespace detail

namespace detail
{
    template < class Graph, class IndexMap, class Value, bool KnownNumVertices >
    struct vertex_property_map_generator_helper
    {
    };

    template < class Graph, class IndexMap, class Value >
    struct vertex_property_map_generator_helper< Graph, IndexMap, Value, true >
    {
        typedef boost::iterator_property_map< Value*, IndexMap > type;
        static type build(const Graph& g, const IndexMap& index,
            boost::scoped_array< Value >& array_holder)
        {
            array_holder.reset(new Value[num_vertices(g)]);
            std::fill(array_holder.get(), array_holder.get() + num_vertices(g),
                Value());
            return make_iterator_property_map(array_holder.get(), index);
        }
    };

    template < class Graph, class IndexMap, class Value >
    struct vertex_property_map_generator_helper< Graph, IndexMap, Value, false >
    {
        typedef boost::vector_property_map< Value, IndexMap > type;
        static type build(const Graph& g, const IndexMap& index,
            boost::scoped_array< Value >& array_holder)
        {
            return boost::make_vector_property_map< Value >(index);
        }
    };

    template < class Graph, class IndexMap, class Value >
    struct vertex_property_map_generator
    {
        typedef boost::is_base_and_derived< boost::vertex_list_graph_tag,
            typename boost::graph_traits< Graph >::traversal_category >
            known_num_vertices;
        typedef vertex_property_map_generator_helper< Graph, IndexMap, Value,
            known_num_vertices::value >
            helper;
        typedef typename helper::type type;
        static type build(const Graph& g, const IndexMap& index,
            boost::scoped_array< Value >& array_holder)
        {
            return helper::build(g, index, array_holder);
        }
    };
}

namespace detail
{
    template < class Graph, class IndexMap, bool KnownNumVertices >
    struct default_color_map_generator_helper
    {
    };

    template < class Graph, class IndexMap >
    struct default_color_map_generator_helper< Graph, IndexMap, true >
    {
        typedef boost::two_bit_color_map< IndexMap > type;
        static type build(const Graph& g, const IndexMap& index)
        {
            size_t nv = num_vertices(g);
            return boost::two_bit_color_map< IndexMap >(nv, index);
        }
    };

    template < class Graph, class IndexMap >
    struct default_color_map_generator_helper< Graph, IndexMap, false >
    {
        typedef boost::vector_property_map< boost::two_bit_color_type,
            IndexMap >
            type;
        static type build(const Graph& g, const IndexMap& index)
        {
            return boost::make_vector_property_map< boost::two_bit_color_type >(
                index);
        }
    };

    template < class Graph, class IndexMap > struct default_color_map_generator
    {
        typedef boost::is_base_and_derived< boost::vertex_list_graph_tag,
            typename boost::graph_traits< Graph >::traversal_category >
            known_num_vertices;
        typedef default_color_map_generator_helper< Graph, IndexMap,
            known_num_vertices::value >
            helper;
        typedef typename helper::type type;
        static type build(const Graph& g, const IndexMap& index)
        {
            return helper::build(g, index);
        }
    };
}

// Call breadth first search with default color map.
template < class Graph, class SourceInputIter, class DijkstraVisitor,
    class PredecessorMap, class DistanceMap, class WeightMap, class IndexMap,
    class Compare, class Combine, class DistZero >
inline void dijkstra_shortest_paths_no_init(const Graph& g,
    SourceInputIter s_begin, SourceInputIter s_end, PredecessorMap predecessor,
    DistanceMap distance, WeightMap weight, IndexMap index_map, Compare compare,
    Combine combine, DistZero zero, DijkstraVisitor vis)
{
    typedef detail::default_color_map_generator< Graph, IndexMap >
        ColorMapHelper;
    typedef typename ColorMapHelper::type ColorMap;
    ColorMap color = ColorMapHelper::build(g, index_map);
    dijkstra_shortest_paths_no_init(g, s_begin, s_end, predecessor, distance,
        weight, index_map, compare, combine, zero, vis, color);
}

// Call breadth first search with default color map.
template < class Graph, class DijkstraVisitor, class PredecessorMap,
    class DistanceMap, class WeightMap, class IndexMap, class Compare,
    class Combine, class DistZero >
inline void dijkstra_shortest_paths_no_init(const Graph& g,
    typename graph_traits< Graph >::vertex_descriptor s,
    PredecessorMap predecessor, DistanceMap distance, WeightMap weight,
    IndexMap index_map, Compare compare, Combine combine, DistZero zero,
    DijkstraVisitor vis)
{
    dijkstra_shortest_paths_no_init(g, &s, &s + 1, predecessor, distance,
        weight, index_map, compare, combine, zero, vis);
}

// Call breadth first search
template < class Graph, class SourceInputIter, class DijkstraVisitor,
    class PredecessorMap, class DistanceMap, class WeightMap, class IndexMap,
    class Compare, class Combine, class DistZero, class ColorMap >
inline void dijkstra_shortest_paths_no_init(const Graph& g,
    SourceInputIter s_begin, SourceInputIter s_end, PredecessorMap predecessor,
    DistanceMap distance, WeightMap weight, IndexMap index_map, Compare compare,
    Combine combine, DistZero zero, DijkstraVisitor vis, ColorMap color)
{
    typedef indirect_cmp< DistanceMap, Compare > IndirectCmp;
    IndirectCmp icmp(distance, compare);

    typedef typename graph_traits< Graph >::vertex_descriptor Vertex;

    // Now the default: use a d-ary heap
    boost::scoped_array< std::size_t > index_in_heap_map_holder;
    typedef detail::vertex_property_map_generator< Graph, IndexMap,
        std::size_t >
        IndexInHeapMapHelper;
    typedef typename IndexInHeapMapHelper::type IndexInHeapMap;
    IndexInHeapMap index_in_heap
        = IndexInHeapMapHelper::build(g, index_map, index_in_heap_map_holder);
    typedef d_ary_heap_indirect< Vertex, 4, IndexInHeapMap, DistanceMap,
        Compare >
        MutableQueue;
    MutableQueue Q(distance, index_in_heap, compare);

    detail::dijkstra_bfs_visitor< DijkstraVisitor, MutableQueue, WeightMap,
        PredecessorMap, DistanceMap, Combine, Compare >
        bfs_vis(vis, Q, weight, predecessor, distance, combine, compare, zero);

    breadth_first_visit(g, s_begin, s_end, Q, bfs_vis, color);
}

// Call breadth first search
template < class Graph, class DijkstraVisitor, class PredecessorMap,
    class DistanceMap, class WeightMap, class IndexMap, class Compare,
    class Combine, class DistZero, class ColorMap >
inline void dijkstra_shortest_paths_no_init(const Graph& g,
    typename graph_traits< Graph >::vertex_descriptor s,
    PredecessorMap predecessor, DistanceMap distance, WeightMap weight,
    IndexMap index_map, Compare compare, Combine combine, DistZero zero,
    DijkstraVisitor vis, ColorMap color)
{
    dijkstra_shortest_paths_no_init(g, &s, &s + 1, predecessor, distance,
        weight, index_map, compare, combine, zero, vis, color);
}

// Initialize distances and call breadth first search with default color map
template < class VertexListGraph, class SourceInputIter, class DijkstraVisitor,
    class PredecessorMap, class DistanceMap, class WeightMap, class IndexMap,
    class Compare, class Combine, class DistInf, class DistZero, typename T,
    typename Tag, typename Base >
inline void dijkstra_shortest_paths(const VertexListGraph& g,
    SourceInputIter s_begin, SourceInputIter s_end, PredecessorMap predecessor,
    DistanceMap distance, WeightMap weight, IndexMap index_map, Compare compare,
    Combine combine, DistInf inf, DistZero zero, DijkstraVisitor vis,
    const bgl_named_params< T, Tag, Base >& BOOST_GRAPH_ENABLE_IF_MODELS_PARM(
        VertexListGraph, vertex_list_graph_tag))
{
    boost::two_bit_color_map< IndexMap > color(num_vertices(g), index_map);
    dijkstra_shortest_paths(g, s_begin, s_end, predecessor, distance, weight,
        index_map, compare, combine, inf, zero, vis, color);
}

// Initialize distances and call breadth first search with default color map
template < class VertexListGraph, class DijkstraVisitor, class PredecessorMap,
    class DistanceMap, class WeightMap, class IndexMap, class Compare,
    class Combine, class DistInf, class DistZero, typename T, typename Tag,
    typename Base >
inline void dijkstra_shortest_paths(const VertexListGraph& g,
    typename graph_traits< VertexListGraph >::vertex_descriptor s,
    PredecessorMap predecessor, DistanceMap distance, WeightMap weight,
    IndexMap index_map, Compare compare, Combine combine, DistInf inf,
    DistZero zero, DijkstraVisitor vis,
    const bgl_named_params< T, Tag, Base >& BOOST_GRAPH_ENABLE_IF_MODELS_PARM(
        VertexListGraph, vertex_list_graph_tag))
{
    dijkstra_shortest_paths(g, &s, &s + 1, predecessor, distance, weight,
        index_map, compare, combine, inf, zero, vis);
}

// Initialize distances and call breadth first search
template < class VertexListGraph, class SourceInputIter, class DijkstraVisitor,
    class PredecessorMap, class DistanceMap, class WeightMap, class IndexMap,
    class Compare, class Combine, class DistInf, class DistZero,
    class ColorMap >
inline void dijkstra_shortest_paths(const VertexListGraph& g,
    SourceInputIter s_begin, SourceInputIter s_end, PredecessorMap predecessor,
    DistanceMap distance, WeightMap weight, IndexMap index_map, Compare compare,
    Combine combine, DistInf inf, DistZero zero, DijkstraVisitor vis,
    ColorMap color)
{
    typedef typename property_traits< ColorMap >::value_type ColorValue;
    typedef color_traits< ColorValue > Color;
    typename graph_traits< VertexListGraph >::vertex_iterator ui, ui_end;
    for (boost::tie(ui, ui_end) = vertices(g); ui != ui_end; ++ui)
    {
        vis.initialize_vertex(*ui, g);
        put(distance, *ui, inf);
        put(predecessor, *ui, *ui);
        put(color, *ui, Color::white());
    }
    for (SourceInputIter it = s_begin; it != s_end; ++it)
    {
        put(distance, *it, zero);
    }

    dijkstra_shortest_paths_no_init(g, s_begin, s_end, predecessor, distance,
        weight, index_map, compare, combine, zero, vis, color);
}

// Initialize distances and call breadth first search
template < class VertexListGraph, class DijkstraVisitor, class PredecessorMap,
    class DistanceMap, class WeightMap, class IndexMap, class Compare,
    class Combine, class DistInf, class DistZero, class ColorMap >
inline void dijkstra_shortest_paths(const VertexListGraph& g,
    typename graph_traits< VertexListGraph >::vertex_descriptor s,
    PredecessorMap predecessor, DistanceMap distance, WeightMap weight,
    IndexMap index_map, Compare compare, Combine combine, DistInf inf,
    DistZero zero, DijkstraVisitor vis, ColorMap color)
{
    dijkstra_shortest_paths(g, &s, &s + 1, predecessor, distance, weight,
        index_map, compare, combine, inf, zero, vis, color);
}

// Initialize distances and call breadth first search
template < class VertexListGraph, class SourceInputIter, class DijkstraVisitor,
    class PredecessorMap, class DistanceMap, class WeightMap, class IndexMap,
    class Compare, class Combine, class DistInf, class DistZero >
inline void dijkstra_shortest_paths(const VertexListGraph& g,
    SourceInputIter s_begin, SourceInputIter s_end, PredecessorMap predecessor,
    DistanceMap distance, WeightMap weight, IndexMap index_map, Compare compare,
    Combine combine, DistInf inf, DistZero zero, DijkstraVisitor vis)
{
    dijkstra_shortest_paths(g, s_begin, s_end, predecessor, distance, weight,
        index_map, compare, combine, inf, zero, vis, no_named_parameters());
}

// Initialize distances and call breadth first search
template < class VertexListGraph, class DijkstraVisitor, class PredecessorMap,
    class DistanceMap, class WeightMap, class IndexMap, class Compare,
    class Combine, class DistInf, class DistZero >
inline void dijkstra_shortest_paths(const VertexListGraph& g,
    typename graph_traits< VertexListGraph >::vertex_descriptor s,
    PredecessorMap predecessor, DistanceMap distance, WeightMap weight,
    IndexMap index_map, Compare compare, Combine combine, DistInf inf,
    DistZero zero, DijkstraVisitor vis)
{
    dijkstra_shortest_paths(g, &s, &s + 1, predecessor, distance, weight,
        index_map, compare, combine, inf, zero, vis);
}

namespace detail
{

    // Handle defaults for PredecessorMap and
    // Distance Compare, Combine, Inf and Zero
    template < class VertexListGraph, class DistanceMap, class WeightMap,
        class IndexMap, class Params >
    inline void dijkstra_dispatch2(const VertexListGraph& g,
        typename graph_traits< VertexListGraph >::vertex_descriptor s,
        DistanceMap distance, WeightMap weight, IndexMap index_map,
        const Params& params)
    {
        // Default for predecessor map
        dummy_property_map p_map;

        typedef typename property_traits< DistanceMap >::value_type D;
        D inf = choose_param(get_param(params, distance_inf_t()),
            (std::numeric_limits< D >::max)());

        dijkstra_shortest_paths(g, s,
            choose_param(get_param(params, vertex_predecessor), p_map),
            distance, weight, index_map,
            choose_param(
                get_param(params, distance_compare_t()), std::less< D >()),
            choose_param(
                get_param(params, distance_combine_t()), std::plus< D >()),
            inf, choose_param(get_param(params, distance_zero_t()), D()),
            choose_param(get_param(params, graph_visitor),
                make_dijkstra_visitor(null_visitor())),
            params);
    }

    template < class VertexListGraph, class DistanceMap, class WeightMap,
        class IndexMap, class Params >
    inline void dijkstra_dispatch1(const VertexListGraph& g,
        typename graph_traits< VertexListGraph >::vertex_descriptor s,
        DistanceMap distance, WeightMap weight, IndexMap index_map,
        const Params& params)
    {
        // Default for distance map
        typedef typename property_traits< WeightMap >::value_type D;
        typename std::vector< D >::size_type n
            = is_default_param(distance) ? num_vertices(g) : 1;
        std::vector< D > distance_map(n);

        detail::dijkstra_dispatch2(g, s,
            choose_param(distance,
                make_iterator_property_map(
                    distance_map.begin(), index_map, distance_map[0])),
            weight, index_map, params);
    }
} // namespace detail

// Named Parameter Variant
template < class VertexListGraph, class Param, class Tag, class Rest >
inline void dijkstra_shortest_paths(const VertexListGraph& g,
    typename graph_traits< VertexListGraph >::vertex_descriptor s,
    const bgl_named_params< Param, Tag, Rest >& params)
{
    // Default for edge weight and vertex index map is to ask for them
    // from the graph.  Default for the visitor is null_visitor.
    detail::dijkstra_dispatch1(g, s, get_param(params, vertex_distance),
        choose_const_pmap(get_param(params, edge_weight), g, edge_weight),
        choose_const_pmap(get_param(params, vertex_index), g, vertex_index),
        params);
}

} // namespace boost

#include BOOST_GRAPH_MPI_INCLUDE(< boost / graph / distributed / dijkstra_shortest_paths.hpp >)

#endif // BOOST_GRAPH_DIJKSTRA_HPP

/* dijkstra_shortest_paths.hpp
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
*/