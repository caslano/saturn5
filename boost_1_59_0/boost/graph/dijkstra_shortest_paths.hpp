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

#include BOOST_GRAPH_MPI_INCLUDE(<boost/graph/distributed/dijkstra_shortest_paths.hpp>)

#endif // BOOST_GRAPH_DIJKSTRA_HPP

/* dijkstra_shortest_paths.hpp
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
*/