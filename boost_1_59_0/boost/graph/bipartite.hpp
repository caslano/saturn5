/**
 *
 * Copyright (c) 2010 Matthias Walter (xammy@xammy.homelinux.net)
 *
 * Authors: Matthias Walter
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 */

#ifndef BOOST_GRAPH_BIPARTITE_HPP
#define BOOST_GRAPH_BIPARTITE_HPP

#include <utility>
#include <vector>
#include <exception>
#include <boost/graph/properties.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/one_bit_color_map.hpp>

namespace boost
{

namespace detail
{

    /**
     * The bipartite_visitor_error is thrown if an edge cannot be colored.
     * The witnesses are the edges incident vertices.
     */

    template < typename Vertex >
    struct BOOST_SYMBOL_VISIBLE bipartite_visitor_error : std::exception
    {
        std::pair< Vertex, Vertex > witnesses;

        bipartite_visitor_error(Vertex a, Vertex b) : witnesses(a, b) {}

        const char* what() const throw() { return "Graph is not bipartite."; }
    };

    /**
     * Functor which colors edges to be non-monochromatic.
     */

    template < typename PartitionMap > struct bipartition_colorize
    {
        typedef on_tree_edge event_filter;

        bipartition_colorize(PartitionMap partition_map)
        : partition_map_(partition_map)
        {
        }

        template < typename Edge, typename Graph >
        void operator()(Edge e, const Graph& g)
        {
            typedef typename graph_traits< Graph >::vertex_descriptor
                vertex_descriptor_t;
            typedef color_traits<
                typename property_traits< PartitionMap >::value_type >
                color_traits;

            vertex_descriptor_t source_vertex = source(e, g);
            vertex_descriptor_t target_vertex = target(e, g);
            if (get(partition_map_, source_vertex) == color_traits::white())
                put(partition_map_, target_vertex, color_traits::black());
            else
                put(partition_map_, target_vertex, color_traits::white());
        }

    private:
        PartitionMap partition_map_;
    };

    /**
     * Creates a bipartition_colorize functor which colors edges
     * to be non-monochromatic.
     *
     * @param partition_map Color map for the bipartition
     * @return The functor.
     */

    template < typename PartitionMap >
    inline bipartition_colorize< PartitionMap > colorize_bipartition(
        PartitionMap partition_map)
    {
        return bipartition_colorize< PartitionMap >(partition_map);
    }

    /**
     * Functor which tests an edge to be monochromatic.
     */

    template < typename PartitionMap > struct bipartition_check
    {
        typedef on_back_edge event_filter;

        bipartition_check(PartitionMap partition_map)
        : partition_map_(partition_map)
        {
        }

        template < typename Edge, typename Graph >
        void operator()(Edge e, const Graph& g)
        {
            typedef typename graph_traits< Graph >::vertex_descriptor
                vertex_descriptor_t;

            vertex_descriptor_t source_vertex = source(e, g);
            vertex_descriptor_t target_vertex = target(e, g);
            if (get(partition_map_, source_vertex)
                == get(partition_map_, target_vertex))
                throw bipartite_visitor_error< vertex_descriptor_t >(
                    source_vertex, target_vertex);
        }

    private:
        PartitionMap partition_map_;
    };

    /**
     * Creates a bipartition_check functor which raises an error if a
     * monochromatic edge is found.
     *
     * @param partition_map The map for a bipartition.
     * @return The functor.
     */

    template < typename PartitionMap >
    inline bipartition_check< PartitionMap > check_bipartition(
        PartitionMap partition_map)
    {
        return bipartition_check< PartitionMap >(partition_map);
    }

    /**
     * Find the beginning of a common suffix of two sequences
     *
     * @param sequence1 Pair of bidirectional iterators defining the first
     * sequence.
     * @param sequence2 Pair of bidirectional iterators defining the second
     * sequence.
     * @return Pair of iterators pointing to the beginning of the common suffix.
     */

    template < typename BiDirectionalIterator1,
        typename BiDirectionalIterator2 >
    inline std::pair< BiDirectionalIterator1, BiDirectionalIterator2 >
    reverse_mismatch(
        std::pair< BiDirectionalIterator1, BiDirectionalIterator1 > sequence1,
        std::pair< BiDirectionalIterator2, BiDirectionalIterator2 > sequence2)
    {
        if (sequence1.first == sequence1.second
            || sequence2.first == sequence2.second)
            return std::make_pair(sequence1.first, sequence2.first);

        BiDirectionalIterator1 iter1 = sequence1.second;
        BiDirectionalIterator2 iter2 = sequence2.second;

        while (true)
        {
            --iter1;
            --iter2;
            if (*iter1 != *iter2)
            {
                ++iter1;
                ++iter2;
                break;
            }
            if (iter1 == sequence1.first)
                break;
            if (iter2 == sequence2.first)
                break;
        }

        return std::make_pair(iter1, iter2);
    }

}

/**
 * Checks a given graph for bipartiteness and fills the given color map with
 * white and black according to the bipartition. If the graph is not
 * bipartite, the contents of the color map are undefined. Runs in linear
 * time in the size of the graph, if access to the property maps is in
 * constant time.
 *
 * @param graph The given graph.
 * @param index_map An index map associating vertices with an index.
 * @param partition_map A color map to fill with the bipartition.
 * @return true if and only if the given graph is bipartite.
 */

template < typename Graph, typename IndexMap, typename PartitionMap >
bool is_bipartite(
    const Graph& graph, const IndexMap index_map, PartitionMap partition_map)
{
    /// General types and variables
    typedef
        typename property_traits< PartitionMap >::value_type partition_color_t;
    typedef
        typename graph_traits< Graph >::vertex_descriptor vertex_descriptor_t;

    /// Declare dfs visitor
    //    detail::empty_recorder recorder;
    //    typedef detail::bipartite_visitor <PartitionMap,
    //    detail::empty_recorder> dfs_visitor_t; dfs_visitor_t dfs_visitor
    //    (partition_map, recorder);

    /// Call dfs
    try
    {
        depth_first_search(graph,
            vertex_index_map(index_map).visitor(make_dfs_visitor(
                std::make_pair(detail::colorize_bipartition(partition_map),
                    std::make_pair(detail::check_bipartition(partition_map),
                        put_property(partition_map,
                            color_traits< partition_color_t >::white(),
                            on_start_vertex()))))));
    }
    catch (const detail::bipartite_visitor_error< vertex_descriptor_t >&)
    {
        return false;
    }

    return true;
}

/**
 * Checks a given graph for bipartiteness.
 *
 * @param graph The given graph.
 * @param index_map An index map associating vertices with an index.
 * @return true if and only if the given graph is bipartite.
 */

template < typename Graph, typename IndexMap >
bool is_bipartite(const Graph& graph, const IndexMap index_map)
{
    typedef one_bit_color_map< IndexMap > partition_map_t;
    partition_map_t partition_map(num_vertices(graph), index_map);

    return is_bipartite(graph, index_map, partition_map);
}

/**
 * Checks a given graph for bipartiteness. The graph must
 * have an internal vertex_index property. Runs in linear time in the
 * size of the graph, if access to the property maps is in constant time.
 *
 * @param graph The given graph.
 * @return true if and only if the given graph is bipartite.
 */

template < typename Graph > bool is_bipartite(const Graph& graph)
{
    return is_bipartite(graph, get(vertex_index, graph));
}

/**
 * Checks a given graph for bipartiteness and fills a given color map with
 * white and black according to the bipartition. If the graph is not
 * bipartite, a sequence of vertices, producing an odd-cycle, is written to
 * the output iterator. The final iterator value is returned. Runs in linear
 * time in the size of the graph, if access to the property maps is in
 * constant time.
 *
 * @param graph The given graph.
 * @param index_map An index map associating vertices with an index.
 * @param partition_map A color map to fill with the bipartition.
 * @param result An iterator to write the odd-cycle vertices to.
 * @return The final iterator value after writing.
 */

template < typename Graph, typename IndexMap, typename PartitionMap,
    typename OutputIterator >
OutputIterator find_odd_cycle(const Graph& graph, const IndexMap index_map,
    PartitionMap partition_map, OutputIterator result)
{
    /// General types and variables
    typedef
        typename property_traits< PartitionMap >::value_type partition_color_t;
    typedef
        typename graph_traits< Graph >::vertex_descriptor vertex_descriptor_t;
    typedef typename graph_traits< Graph >::vertex_iterator vertex_iterator_t;
    vertex_iterator_t vertex_iter, vertex_end;

    /// Declare predecessor map
    typedef std::vector< vertex_descriptor_t > predecessors_t;
    typedef iterator_property_map< typename predecessors_t::iterator, IndexMap,
        vertex_descriptor_t, vertex_descriptor_t& >
        predecessor_map_t;

    predecessors_t predecessors(
        num_vertices(graph), graph_traits< Graph >::null_vertex());
    predecessor_map_t predecessor_map(predecessors.begin(), index_map);

    /// Initialize predecessor map
    for (boost::tie(vertex_iter, vertex_end) = vertices(graph);
         vertex_iter != vertex_end; ++vertex_iter)
    {
        put(predecessor_map, *vertex_iter, *vertex_iter);
    }

    /// Call dfs
    try
    {
        depth_first_search(graph,
            vertex_index_map(index_map).visitor(make_dfs_visitor(
                std::make_pair(detail::colorize_bipartition(partition_map),
                    std::make_pair(detail::check_bipartition(partition_map),
                        std::make_pair(
                            put_property(partition_map,
                                color_traits< partition_color_t >::white(),
                                on_start_vertex()),
                            record_predecessors(
                                predecessor_map, on_tree_edge())))))));
    }
    catch (const detail::bipartite_visitor_error< vertex_descriptor_t >& error)
    {
        typedef std::vector< vertex_descriptor_t > path_t;

        path_t path1, path2;
        vertex_descriptor_t next, current;

        /// First path
        next = error.witnesses.first;
        do
        {
            current = next;
            path1.push_back(current);
            next = predecessor_map[current];
        } while (current != next);

        /// Second path
        next = error.witnesses.second;
        do
        {
            current = next;
            path2.push_back(current);
            next = predecessor_map[current];
        } while (current != next);

        /// Find beginning of common suffix
        std::pair< typename path_t::iterator, typename path_t::iterator >
            mismatch = detail::reverse_mismatch(
                std::make_pair(path1.begin(), path1.end()),
                std::make_pair(path2.begin(), path2.end()));

        /// Copy the odd-length cycle
        result = std::copy(path1.begin(), mismatch.first + 1, result);
        return std::reverse_copy(path2.begin(), mismatch.second, result);
    }

    return result;
}

/**
 * Checks a given graph for bipartiteness. If the graph is not bipartite, a
 * sequence of vertices, producing an odd-cycle, is written to the output
 * iterator. The final iterator value is returned. Runs in linear time in the
 * size of the graph, if access to the property maps is in constant time.
 *
 * @param graph The given graph.
 * @param index_map An index map associating vertices with an index.
 * @param result An iterator to write the odd-cycle vertices to.
 * @return The final iterator value after writing.
 */

template < typename Graph, typename IndexMap, typename OutputIterator >
OutputIterator find_odd_cycle(
    const Graph& graph, const IndexMap index_map, OutputIterator result)
{
    typedef one_bit_color_map< IndexMap > partition_map_t;
    partition_map_t partition_map(num_vertices(graph), index_map);

    return find_odd_cycle(graph, index_map, partition_map, result);
}

/**
 * Checks a given graph for bipartiteness. If the graph is not bipartite, a
 * sequence of vertices, producing an odd-cycle, is written to the output
 * iterator. The final iterator value is returned. The graph must have an
 * internal vertex_index property. Runs in linear time in the size of the
 * graph, if access to the property maps is in constant time.
 *
 * @param graph The given graph.
 * @param result An iterator to write the odd-cycle vertices to.
 * @return The final iterator value after writing.
 */

template < typename Graph, typename OutputIterator >
OutputIterator find_odd_cycle(const Graph& graph, OutputIterator result)
{
    return find_odd_cycle(graph, get(vertex_index, graph), result);
}
}

#endif /// BOOST_GRAPH_BIPARTITE_HPP

/* bipartite.hpp
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
*/