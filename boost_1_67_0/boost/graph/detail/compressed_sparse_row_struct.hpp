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