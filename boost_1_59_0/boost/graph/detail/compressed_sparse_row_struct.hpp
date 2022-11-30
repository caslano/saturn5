// Copyright 2005-2009 The Trustees of Indiana University.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Jeremiah Willcock
//           Douglas Gregor
//           Andrew Lumsdaine

// Compressed sparse row graph type internal structure

#ifndef BOOST_GRAPH_COMPRESSED_SPARSE_ROW_STRUCT_HPP
#define BOOST_GRAPH_COMPRESSED_SPARSE_ROW_STRUCT_HPP

#ifndef BOOST_GRAPH_COMPRESSED_SPARSE_ROW_GRAPH_HPP
#error This file should only be included from boost/graph/compressed_sparse_row_graph.hpp
#endif

#include <vector>
#include <utility>
#include <algorithm>
#include <climits>
#include <boost/assert.hpp>
#include <iterator>
#if 0
#include <iostream> // For some debugging code below
#endif
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/filtered_graph.hpp> // For keep_all
#include <boost/graph/detail/indexed_properties.hpp>
#include <boost/graph/detail/histogram_sort.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/iterator/counting_iterator.hpp>
#include <boost/iterator/reverse_iterator.hpp>
#include <boost/iterator/zip_iterator.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/integer.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/mpl/if.hpp>
#include <boost/graph/graph_selectors.hpp>
#include <boost/static_assert.hpp>
#include <boost/functional/hash.hpp>

namespace boost
{

namespace detail
{
    // Forward declaration of CSR edge descriptor type, needed to pass to
    // indexed_edge_properties.
    template < typename Vertex, typename EdgeIndex > class csr_edge_descriptor;

    // Add edge_index property map
    template < typename Vertex, typename EdgeIndex > struct csr_edge_index_map
    {
        typedef EdgeIndex value_type;
        typedef EdgeIndex reference;
        typedef csr_edge_descriptor< Vertex, EdgeIndex > key_type;
        typedef readable_property_map_tag category;
    };

    template < typename Vertex, typename EdgeIndex >
    inline EdgeIndex get(const csr_edge_index_map< Vertex, EdgeIndex >&,
        const csr_edge_descriptor< Vertex, EdgeIndex >& key)
    {
        return key.idx;
    }

    /** Compressed sparse row graph internal structure.
     *
     * Vertex and EdgeIndex should be unsigned integral types and should
     * specialize numeric_limits.
     */
    template < typename EdgeProperty, typename Vertex = std::size_t,
        typename EdgeIndex = Vertex >
    class compressed_sparse_row_structure
    : public detail::indexed_edge_properties<
          compressed_sparse_row_structure< EdgeProperty, Vertex, EdgeIndex >,
          EdgeProperty, csr_edge_descriptor< Vertex, EdgeIndex >,
          csr_edge_index_map< Vertex, EdgeIndex > >
    {
    public:
        typedef detail::indexed_edge_properties<
            compressed_sparse_row_structure< EdgeProperty, Vertex, EdgeIndex >,
            EdgeProperty, csr_edge_descriptor< Vertex, EdgeIndex >,
            csr_edge_index_map< Vertex, EdgeIndex > >
            inherited_edge_properties;

        typedef Vertex vertices_size_type;
        typedef Vertex vertex_descriptor;
        typedef EdgeIndex edges_size_type;

        static vertex_descriptor null_vertex() { return vertex_descriptor(-1); }

        std::vector< EdgeIndex > m_rowstart;
        std::vector< Vertex > m_column;

        compressed_sparse_row_structure(Vertex numverts = 0)
        : m_rowstart(numverts + 1, EdgeIndex(0)), m_column()
        {
        }

        //  Rebuild graph from number of vertices and multi-pass unsorted list
        //  of edges (filtered using source_pred and mapped using
        //  global_to_local)
        template < typename MultiPassInputIterator, typename GlobalToLocal,
            typename SourcePred >
        void assign_unsorted_multi_pass_edges(MultiPassInputIterator edge_begin,
            MultiPassInputIterator edge_end, vertices_size_type numlocalverts,
            const GlobalToLocal& global_to_local, const SourcePred& source_pred)
        {
            m_rowstart.clear();
            m_rowstart.resize(numlocalverts + 1, 0);
            typedef std::pair< vertices_size_type, vertices_size_type >
                edge_type;
            typedef boost::transform_iterator<
                boost::graph::detail::project1st< edge_type >,
                MultiPassInputIterator >
                source_iterator;
            typedef boost::transform_iterator<
                boost::graph::detail::project2nd< edge_type >,
                MultiPassInputIterator >
                target_iterator;
            source_iterator sources_begin(
                edge_begin, boost::graph::detail::project1st< edge_type >());
            source_iterator sources_end(
                edge_end, boost::graph::detail::project1st< edge_type >());
            target_iterator targets_begin(
                edge_begin, boost::graph::detail::project2nd< edge_type >());
            target_iterator targets_end(
                edge_end, boost::graph::detail::project2nd< edge_type >());

            boost::graph::detail::count_starts(sources_begin, sources_end,
                m_rowstart.begin(), numlocalverts, source_pred,
                boost::make_property_map_function(global_to_local));

            m_column.resize(m_rowstart.back());
            inherited_edge_properties::resize(m_rowstart.back());

            boost::graph::detail::histogram_sort(sources_begin, sources_end,
                m_rowstart.begin(), numlocalverts, targets_begin,
                m_column.begin(), source_pred,
                boost::make_property_map_function(global_to_local));
        }

        //  Rebuild graph from number of vertices and multi-pass unsorted list
        //  of edges and their properties (filtered using source_pred and mapped
        //  using global_to_local)
        template < typename MultiPassInputIterator,
            typename EdgePropertyIterator, typename GlobalToLocal,
            typename SourcePred >
        void assign_unsorted_multi_pass_edges(MultiPassInputIterator edge_begin,
            MultiPassInputIterator edge_end, EdgePropertyIterator ep_iter,
            vertices_size_type numlocalverts,
            const GlobalToLocal& global_to_local, const SourcePred& source_pred)
        {
            m_rowstart.clear();
            m_rowstart.resize(numlocalverts + 1, 0);
            typedef std::pair< vertices_size_type, vertices_size_type >
                edge_type;
            typedef boost::transform_iterator<
                boost::graph::detail::project1st< edge_type >,
                MultiPassInputIterator >
                source_iterator;
            typedef boost::transform_iterator<
                boost::graph::detail::project2nd< edge_type >,
                MultiPassInputIterator >
                target_iterator;
            source_iterator sources_begin(
                edge_begin, boost::graph::detail::project1st< edge_type >());
            source_iterator sources_end(
                edge_end, boost::graph::detail::project1st< edge_type >());
            target_iterator targets_begin(
                edge_begin, boost::graph::detail::project2nd< edge_type >());
            target_iterator targets_end(
                edge_end, boost::graph::detail::project2nd< edge_type >());

            boost::graph::detail::count_starts(sources_begin, sources_end,
                m_rowstart.begin(), numlocalverts, source_pred,
                boost::make_property_map_function(global_to_local));

            m_column.resize(m_rowstart.back());
            inherited_edge_properties::resize(m_rowstart.back());

            boost::graph::detail::histogram_sort(sources_begin, sources_end,
                m_rowstart.begin(), numlocalverts, targets_begin,
                m_column.begin(), ep_iter, inherited_edge_properties::begin(),
                source_pred,
                boost::make_property_map_function(global_to_local));
        }

        //  Assign from number of vertices and sorted list of edges
        template < typename InputIterator, typename GlobalToLocal,
            typename SourcePred >
        void assign_from_sorted_edges(InputIterator edge_begin,
            InputIterator edge_end, const GlobalToLocal& global_to_local,
            const SourcePred& source_pred, vertices_size_type numlocalverts,
            edges_size_type numedges_or_zero)
        {
            m_column.clear();
            m_column.reserve(numedges_or_zero);
            m_rowstart.resize(numlocalverts + 1);
            EdgeIndex current_edge = 0;
            Vertex current_vertex_plus_one = 1;
            m_rowstart[0] = 0;
            for (InputIterator ei = edge_begin; ei != edge_end; ++ei)
            {
                if (!source_pred(ei->first))
                    continue;
                Vertex src = get(global_to_local, ei->first);
                Vertex tgt = ei->second;
                for (; current_vertex_plus_one != src + 1;
                     ++current_vertex_plus_one)
                    m_rowstart[current_vertex_plus_one] = current_edge;
                m_column.push_back(tgt);
                ++current_edge;
            }

            // The remaining vertices have no edges
            for (; current_vertex_plus_one != numlocalverts + 1;
                 ++current_vertex_plus_one)
                m_rowstart[current_vertex_plus_one] = current_edge;

            // Default-construct properties for edges
            inherited_edge_properties::resize(m_column.size());
        }

        //  Assign from number of vertices and sorted list of edges
        template < typename InputIterator, typename EdgePropertyIterator,
            typename GlobalToLocal, typename SourcePred >
        void assign_from_sorted_edges(InputIterator edge_begin,
            InputIterator edge_end, EdgePropertyIterator ep_iter,
            const GlobalToLocal& global_to_local, const SourcePred& source_pred,
            vertices_size_type numlocalverts, edges_size_type numedges_or_zero)
        {
            // Reserving storage in advance can save us lots of time and
            // memory, but it can only be done if we have forward iterators or
            // the user has supplied the number of edges.
            edges_size_type numedges = numedges_or_zero;
            if (numedges == 0)
            {
                numedges = boost::graph::detail::reserve_count_for_single_pass(
                    edge_begin, edge_end);
            }
            m_column.clear();
            m_column.reserve(numedges_or_zero);
            inherited_edge_properties::clear();
            inherited_edge_properties::reserve(numedges_or_zero);
            m_rowstart.resize(numlocalverts + 1);
            EdgeIndex current_edge = 0;
            Vertex current_vertex_plus_one = 1;
            m_rowstart[0] = 0;
            for (InputIterator ei = edge_begin; ei != edge_end; ++ei, ++ep_iter)
            {
                if (!source_pred(ei->first))
                    continue;
                Vertex src = get(global_to_local, ei->first);
                Vertex tgt = ei->second;
                for (; current_vertex_plus_one != src + 1;
                     ++current_vertex_plus_one)
                    m_rowstart[current_vertex_plus_one] = current_edge;
                m_column.push_back(tgt);
                inherited_edge_properties::push_back(*ep_iter);
                ++current_edge;
            }

            // The remaining vertices have no edges
            for (; current_vertex_plus_one != numlocalverts + 1;
                 ++current_vertex_plus_one)
                m_rowstart[current_vertex_plus_one] = current_edge;
        }

        // Replace graph with sources and targets given, sorting them in-place,
        // and using the given global-to-local property map to get local indices
        // from global ones in the two arrays.
        template < typename GlobalToLocal >
        void assign_sources_and_targets_global(
            std::vector< vertex_descriptor >& sources,
            std::vector< vertex_descriptor >& targets,
            vertices_size_type numverts, GlobalToLocal global_to_local)
        {
            BOOST_ASSERT(sources.size() == targets.size());
            // Do an in-place histogram sort (at least that's what I think it
            // is) to sort sources and targets
            m_rowstart.clear();
            m_rowstart.resize(numverts + 1);
            boost::graph::detail::count_starts(sources.begin(), sources.end(),
                m_rowstart.begin(), numverts, keep_all(),
                boost::make_property_map_function(global_to_local));
            boost::graph::detail::histogram_sort_inplace(sources.begin(),
                m_rowstart.begin(), numverts, targets.begin(),
                boost::make_property_map_function(global_to_local));
            // Now targets is the correct vector (properly sorted by source) for
            // m_column
            m_column.swap(targets);
            inherited_edge_properties::resize(m_rowstart.back());
        }

        // Replace graph with sources and targets and edge properties given,
        // sorting them in-place, and using the given global-to-local property
        // map to get local indices from global ones in the two arrays.
        template < typename GlobalToLocal >
        void assign_sources_and_targets_global(
            std::vector< vertex_descriptor >& sources,
            std::vector< vertex_descriptor >& targets,
            std::vector< typename inherited_edge_properties::edge_bundled >&
                edge_props,
            vertices_size_type numverts, GlobalToLocal global_to_local)
        {
            BOOST_ASSERT(sources.size() == targets.size());
            BOOST_ASSERT(sources.size() == edge_props.size());
            // Do an in-place histogram sort (at least that's what I think it
            // is) to sort sources and targets
            m_rowstart.clear();
            m_rowstart.resize(numverts + 1);
            boost::graph::detail::count_starts(sources.begin(), sources.end(),
                m_rowstart.begin(), numverts, keep_all(),
                boost::make_property_map_function(global_to_local));
            boost::graph::detail::histogram_sort_inplace(sources.begin(),
                m_rowstart.begin(), numverts, targets.begin(),
                edge_props.begin(),
                boost::make_property_map_function(global_to_local));
            // Now targets is the correct vector (properly sorted by source) for
            // m_column, and edge_props for m_edge_properties
            m_column.swap(targets);
            this->m_edge_properties.swap(edge_props);
        }

        // From any graph (slow and uses a lot of memory)
        //   Requires IncidenceGraph and a vertex index map
        //   Internal helper function
        //   Note that numedges must be doubled for undirected source graphs
        template < typename Graph, typename VertexIndexMap >
        void assign(const Graph& g, const VertexIndexMap& vi,
            vertices_size_type numverts, edges_size_type numedges)
        {
            m_rowstart.resize(numverts + 1);
            m_column.resize(numedges);
            inherited_edge_properties::resize(numedges);
            EdgeIndex current_edge = 0;
            typedef typename boost::graph_traits< Graph >::vertex_descriptor
                g_vertex;
            typedef typename boost::graph_traits< Graph >::out_edge_iterator
                g_out_edge_iter;

            std::vector< g_vertex > ordered_verts_of_g(numverts);
            BGL_FORALL_VERTICES_T(v, g, Graph)
            {
                ordered_verts_of_g[get(vertex_index, g, v)] = v;
            }
            for (Vertex i = 0; i != numverts; ++i)
            {
                m_rowstart[i] = current_edge;
                g_vertex v = ordered_verts_of_g[i];
                g_out_edge_iter ei, ei_end;
                for (boost::tie(ei, ei_end) = out_edges(v, g); ei != ei_end;
                     ++ei)
                {
                    m_column[current_edge++] = get(vi, target(*ei, g));
                }
            }
            m_rowstart[numverts] = current_edge;
        }

        // Add edges from a sorted (smallest sources first) range of pairs and
        // edge properties
        template < typename BidirectionalIteratorOrig, typename EPIterOrig,
            typename GlobalToLocal >
        void add_edges_sorted_internal(BidirectionalIteratorOrig first_sorted,
            BidirectionalIteratorOrig last_sorted, EPIterOrig ep_iter_sorted,
            const GlobalToLocal& global_to_local)
        {
            typedef boost::reverse_iterator< BidirectionalIteratorOrig >
                BidirectionalIterator;
            typedef boost::reverse_iterator< EPIterOrig > EPIter;
            // Flip sequence
            BidirectionalIterator first(last_sorted);
            BidirectionalIterator last(first_sorted);
            typedef Vertex vertex_num;
            typedef EdgeIndex edge_num;
            edge_num new_edge_count = std::distance(first, last);

            EPIter ep_iter(ep_iter_sorted);
            std::advance(ep_iter, -(std::ptrdiff_t)new_edge_count);
            edge_num edges_added_before_i
                = new_edge_count; // Count increment to add to rowstarts
            m_column.resize(m_column.size() + new_edge_count);
            inherited_edge_properties::resize(
                inherited_edge_properties::size() + new_edge_count);
            BidirectionalIterator current_new_edge = first,
                                  prev_new_edge = first;
            EPIter current_new_edge_prop = ep_iter;
            for (vertex_num i_plus_1 = m_rowstart.size() - 1; i_plus_1 > 0;
                 --i_plus_1)
            {
                vertex_num i = i_plus_1 - 1;
                prev_new_edge = current_new_edge;
                // edges_added_to_this_vertex = #mbrs of new_edges with first ==
                // i
                edge_num edges_added_to_this_vertex = 0;
                while (current_new_edge != last)
                {
                    if (get(global_to_local, current_new_edge->first) != i)
                        break;
                    ++current_new_edge;
                    ++current_new_edge_prop;
                    ++edges_added_to_this_vertex;
                }
                edges_added_before_i -= edges_added_to_this_vertex;
                // Invariant: edges_added_before_i = #mbrs of new_edges with
                // first < i
                edge_num old_rowstart = m_rowstart[i];
                edge_num new_rowstart = m_rowstart[i] + edges_added_before_i;
                edge_num old_degree = m_rowstart[i + 1] - m_rowstart[i];
                edge_num new_degree = old_degree + edges_added_to_this_vertex;
                // Move old edges forward (by #new_edges before this i) to make
                // room new_rowstart > old_rowstart, so use copy_backwards
                if (old_rowstart != new_rowstart)
                {
                    std::copy_backward(m_column.begin() + old_rowstart,
                        m_column.begin() + old_rowstart + old_degree,
                        m_column.begin() + new_rowstart + old_degree);
                    inherited_edge_properties::move_range(
                        old_rowstart, old_rowstart + old_degree, new_rowstart);
                }
                // Add new edges (reversed because current_new_edge is a
                // const_reverse_iterator)
                BidirectionalIterator temp = current_new_edge;
                EPIter temp_prop = current_new_edge_prop;
                for (; temp != prev_new_edge; ++old_degree)
                {
                    --temp;
                    --temp_prop;
                    m_column[new_rowstart + old_degree] = temp->second;
                    inherited_edge_properties::write_by_index(
                        new_rowstart + old_degree, *temp_prop);
                }
                m_rowstart[i + 1] = new_rowstart + new_degree;
                if (edges_added_before_i == 0)
                    break; // No more edges inserted before this point
                // m_rowstart[i] will be fixed up on the next iteration (to
                // avoid changing the degree of vertex i - 1); the last
                // iteration never changes it (either because of the condition
                // of the break or because m_rowstart[0] is always 0)
            }
        }
    };

    template < typename Vertex, typename EdgeIndex > class csr_edge_descriptor
    {
    public:
        Vertex src;
        EdgeIndex idx;

        csr_edge_descriptor(Vertex src, EdgeIndex idx) : src(src), idx(idx) {}
        csr_edge_descriptor() : src(0), idx(0) {}

        bool operator==(const csr_edge_descriptor& e) const
        {
            return idx == e.idx;
        }
        bool operator!=(const csr_edge_descriptor& e) const
        {
            return idx != e.idx;
        }
        bool operator<(const csr_edge_descriptor& e) const
        {
            return idx < e.idx;
        }
        bool operator>(const csr_edge_descriptor& e) const
        {
            return idx > e.idx;
        }
        bool operator<=(const csr_edge_descriptor& e) const
        {
            return idx <= e.idx;
        }
        bool operator>=(const csr_edge_descriptor& e) const
        {
            return idx >= e.idx;
        }

        template < typename Archiver >
        void serialize(Archiver& ar, const unsigned int /*version*/)
        {
            ar& src& idx;
        }
    };

    // Common out edge and edge iterators
    template < typename CSRGraph >
    class csr_out_edge_iterator
    : public iterator_facade< csr_out_edge_iterator< CSRGraph >,
          typename CSRGraph::edge_descriptor, std::random_access_iterator_tag,
          const typename CSRGraph::edge_descriptor&,
          typename int_t< CHAR_BIT
              * sizeof(typename CSRGraph::edges_size_type) >::fast >
    {
    public:
        typedef typename CSRGraph::edges_size_type EdgeIndex;
        typedef typename CSRGraph::edge_descriptor edge_descriptor;
        typedef typename int_t< CHAR_BIT * sizeof(EdgeIndex) >::fast
            difference_type;

        csr_out_edge_iterator() {}
        // Implicit copy constructor OK
        explicit csr_out_edge_iterator(edge_descriptor edge) : m_edge(edge) {}

    public: // GCC 4.2.1 doesn't like the private-and-friend thing
        // iterator_facade requirements
        const edge_descriptor& dereference() const { return m_edge; }

        bool equal(const csr_out_edge_iterator& other) const
        {
            return m_edge == other.m_edge;
        }

        void increment() { ++m_edge.idx; }
        void decrement() { --m_edge.idx; }
        void advance(difference_type n) { m_edge.idx += n; }

        difference_type distance_to(const csr_out_edge_iterator& other) const
        {
            return other.m_edge.idx - m_edge.idx;
        }

        edge_descriptor m_edge;

        friend class boost::iterator_core_access;
    };

    template < typename CSRGraph >
    class csr_edge_iterator
    : public iterator_facade< csr_edge_iterator< CSRGraph >,
          typename CSRGraph::edge_descriptor, boost::forward_traversal_tag,
          typename CSRGraph::edge_descriptor >
    {
    private:
        typedef typename CSRGraph::edge_descriptor edge_descriptor;
        typedef typename CSRGraph::edges_size_type EdgeIndex;

    public:
        csr_edge_iterator()
        : rowstart_array(0)
        , current_edge()
        , end_of_this_vertex(0)
        , total_num_edges(0)
        {
        }

        csr_edge_iterator(const CSRGraph& graph, edge_descriptor current_edge,
            EdgeIndex end_of_this_vertex)
        : rowstart_array(&graph.m_forward.m_rowstart[0])
        , current_edge(current_edge)
        , end_of_this_vertex(end_of_this_vertex)
        , total_num_edges(num_edges(graph))
        {
        }

    public: // See above
        friend class boost::iterator_core_access;

        edge_descriptor dereference() const { return current_edge; }

        bool equal(const csr_edge_iterator& o) const
        {
            return current_edge == o.current_edge;
        }

        void increment()
        {
            ++current_edge.idx;
            if (current_edge.idx == total_num_edges)
                return;
            while (current_edge.idx == end_of_this_vertex)
            {
                ++current_edge.src;
                end_of_this_vertex = rowstart_array[current_edge.src + 1];
            }
        }

        const EdgeIndex* rowstart_array;
        edge_descriptor current_edge;
        EdgeIndex end_of_this_vertex;
        EdgeIndex total_num_edges;
    };

    // Only for bidirectional graphs
    template < typename CSRGraph >
    class csr_in_edge_iterator
    : public iterator_facade< csr_in_edge_iterator< CSRGraph >,
          typename CSRGraph::edge_descriptor, boost::forward_traversal_tag,
          typename CSRGraph::edge_descriptor >
    {
    public:
        typedef typename CSRGraph::edges_size_type EdgeIndex;
        typedef typename CSRGraph::edge_descriptor edge_descriptor;

        csr_in_edge_iterator() : m_graph(0) {}
        // Implicit copy constructor OK
        csr_in_edge_iterator(
            const CSRGraph& graph, EdgeIndex index_in_backward_graph)
        : m_index_in_backward_graph(index_in_backward_graph), m_graph(&graph)
        {
        }

    public: // See above
        // iterator_facade requirements
        edge_descriptor dereference() const
        {
            return edge_descriptor(
                m_graph->m_backward.m_column[m_index_in_backward_graph],
                m_graph->m_backward
                    .m_edge_properties[m_index_in_backward_graph]);
        }

        bool equal(const csr_in_edge_iterator& other) const
        {
            return m_index_in_backward_graph == other.m_index_in_backward_graph;
        }

        void increment() { ++m_index_in_backward_graph; }
        void decrement() { --m_index_in_backward_graph; }
        void advance(std::ptrdiff_t n) { m_index_in_backward_graph += n; }

        std::ptrdiff_t distance_to(const csr_in_edge_iterator& other) const
        {
            return other.m_index_in_backward_graph - m_index_in_backward_graph;
        }

        EdgeIndex m_index_in_backward_graph;
        const CSRGraph* m_graph;

        friend class boost::iterator_core_access;
    };

    template < typename A, typename B > struct transpose_pair
    {
        typedef std::pair< B, A > result_type;
        result_type operator()(const std::pair< A, B >& p) const
        {
            return result_type(p.second, p.first);
        }
    };

    template < typename Iter > struct transpose_iterator_gen
    {
        typedef typename std::iterator_traits< Iter >::value_type vt;
        typedef typename vt::first_type first_type;
        typedef typename vt::second_type second_type;
        typedef transpose_pair< first_type, second_type > transpose;
        typedef boost::transform_iterator< transpose, Iter > type;
        static type make(Iter it) { return type(it, transpose()); }
    };

    template < typename Iter >
    typename transpose_iterator_gen< Iter >::type transpose_edges(Iter i)
    {
        return transpose_iterator_gen< Iter >::make(i);
    }

    template < typename GraphT, typename VertexIndexMap >
    class edge_to_index_pair
    {
        typedef typename boost::graph_traits< GraphT >::vertices_size_type
            vertices_size_type;
        typedef typename boost::graph_traits< GraphT >::edge_descriptor
            edge_descriptor;

    public:
        typedef std::pair< vertices_size_type, vertices_size_type > result_type;

        edge_to_index_pair() : g(0), index() {}
        edge_to_index_pair(const GraphT& g, const VertexIndexMap& index)
        : g(&g), index(index)
        {
        }

        result_type operator()(edge_descriptor e) const
        {
            return result_type(
                get(index, source(e, *g)), get(index, target(e, *g)));
        }

    private:
        const GraphT* g;
        VertexIndexMap index;
    };

    template < typename GraphT, typename VertexIndexMap >
    edge_to_index_pair< GraphT, VertexIndexMap > make_edge_to_index_pair(
        const GraphT& g, const VertexIndexMap& index)
    {
        return edge_to_index_pair< GraphT, VertexIndexMap >(g, index);
    }

    template < typename GraphT >
    edge_to_index_pair< GraphT,
        typename boost::property_map< GraphT,
            boost::vertex_index_t >::const_type >
    make_edge_to_index_pair(const GraphT& g)
    {
        typedef typename boost::property_map< GraphT,
            boost::vertex_index_t >::const_type VertexIndexMap;
        return edge_to_index_pair< GraphT, VertexIndexMap >(
            g, get(boost::vertex_index, g));
    }

    template < typename GraphT, typename VertexIndexMap, typename Iter >
    boost::transform_iterator< edge_to_index_pair< GraphT, VertexIndexMap >,
        Iter >
    make_edge_to_index_pair_iter(
        const GraphT& g, const VertexIndexMap& index, Iter it)
    {
        return boost::transform_iterator<
            edge_to_index_pair< GraphT, VertexIndexMap >, Iter >(
            it, edge_to_index_pair< GraphT, VertexIndexMap >(g, index));
    }

} // namespace detail

template < typename Vertex, typename EdgeIndex >
struct hash< detail::csr_edge_descriptor< Vertex, EdgeIndex > >
{
    std::size_t operator()(
        detail::csr_edge_descriptor< Vertex, EdgeIndex > const& x) const
    {
        std::size_t hash = hash_value(x.src);
        hash_combine(hash, x.idx);
        return hash;
    }
};

} // namespace boost

#endif // BOOST_GRAPH_COMPRESSED_SPARSE_ROW_STRUCT_HPP

/* compressed_sparse_row_struct.hpp
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
*/