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
#include <boost/bind.hpp>

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