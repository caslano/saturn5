// Copyright 2005-2009 The Trustees of Indiana University.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Jeremiah Willcock
//           Douglas Gregor
//           Andrew Lumsdaine

// Compressed sparse row graph type

#ifndef BOOST_GRAPH_COMPRESSED_SPARSE_ROW_GRAPH_HPP
#define BOOST_GRAPH_COMPRESSED_SPARSE_ROW_GRAPH_HPP

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
#include <boost/graph/detail/compressed_sparse_row_struct.hpp>
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
#include <boost/utility/enable_if.hpp>
#include <boost/graph/graph_selectors.hpp>
#include <boost/graph/detail/is_distributed_selector.hpp>
#include <boost/graph/properties.hpp>
#include <boost/static_assert.hpp>
#include <boost/functional/hash.hpp>
#include <boost/next_prior.hpp>
#include <boost/property_map/transform_value_property_map.hpp>
#include <boost/mpl/print.hpp>

namespace boost
{

// A tag type indicating that the graph in question is a compressed
// sparse row graph. This is an internal detail of the BGL.
struct csr_graph_tag;

// A type (edges_are_sorted_t) and a value (edges_are_sorted) used to indicate
// that the edge list passed into the CSR graph is already sorted by source
// vertex.
enum edges_are_sorted_t
{
    edges_are_sorted
};

// A type (edges_are_sorted_global_t) and a value (edges_are_sorted_global)
// used to indicate that the edge list passed into the CSR graph is already
// sorted by source vertex.
enum edges_are_sorted_global_t
{
    edges_are_sorted_global
};

// A type (edges_are_unsorted_t) and a value (edges_are_unsorted) used to
// indicate that the edge list passed into the CSR graph is not sorted by
// source vertex.  This version caches the edge information in memory, and thus
// requires only a single pass over the input data.
enum edges_are_unsorted_t
{
    edges_are_unsorted
};

// A type (edges_are_unsorted_multi_pass_t) and a value
// (edges_are_unsorted_multi_pass) used to indicate that the edge list passed
// into the CSR graph is not sorted by source vertex.  This version uses less
// memory but requires multi-pass capability on the iterators.
enum edges_are_unsorted_multi_pass_t
{
    edges_are_unsorted_multi_pass
};

// A type (edges_are_unsorted_multi_pass_global_t) and a value
// (edges_are_unsorted_multi_pass_global) used to indicate that the edge list
// passed into the CSR graph is not sorted by source vertex.  This version uses
// less memory but requires multi-pass capability on the iterators.  The
// global mapping and filtering is done here because it is often faster and it
// greatly simplifies handling of edge properties.
enum edges_are_unsorted_multi_pass_global_t
{
    edges_are_unsorted_multi_pass_global
};

// A type (construct_inplace_from_sources_and_targets_t) and a value
// (construct_inplace_from_sources_and_targets) used to indicate that mutable
// vectors of sources and targets (and possibly edge properties) are being used
// to construct the CSR graph.  These vectors are sorted in-place and then the
// targets and properties are swapped into the graph data structure.
enum construct_inplace_from_sources_and_targets_t
{
    construct_inplace_from_sources_and_targets
};

// A type (construct_inplace_from_sources_and_targets_global_t) and a value
// (construct_inplace_from_sources_and_targets_global) used to indicate that
// mutable vectors of sources and targets (and possibly edge properties) are
// being used to construct the CSR graph.  These vectors are sorted in-place
// and then the targets and properties are swapped into the graph data
// structure.  It is assumed that global indices (for distributed CSR) are
// used, and a map is required to convert those to local indices.  This
// constructor is intended for internal use by the various CSR graphs
// (sequential and distributed).
enum construct_inplace_from_sources_and_targets_global_t
{
    construct_inplace_from_sources_and_targets_global
};

// A type (edges_are_unsorted_global_t) and a value (edges_are_unsorted_global)
// used to indicate that the edge list passed into the CSR graph is not sorted
// by source vertex.  The data is also stored using global vertex indices, and
// must be filtered to choose only local vertices.  This constructor caches the
// edge information in memory, and thus requires only a single pass over the
// input data.  This constructor is intended for internal use by the
// distributed CSR constructors.
enum edges_are_unsorted_global_t
{
    edges_are_unsorted_global
};

/****************************************************************************
 * Local helper macros to reduce typing and clutter later on.               *
 ****************************************************************************/
#define BOOST_CSR_GRAPH_TEMPLATE_PARMS                                 \
    typename Directed, typename VertexProperty, typename EdgeProperty, \
        typename GraphProperty, typename Vertex, typename EdgeIndex
#define BOOST_CSR_GRAPH_TYPE                                             \
    compressed_sparse_row_graph< Directed, VertexProperty, EdgeProperty, \
        GraphProperty, Vertex, EdgeIndex >
#define BOOST_DIR_CSR_GRAPH_TEMPLATE_PARMS                                  \
    typename VertexProperty, typename EdgeProperty, typename GraphProperty, \
        typename Vertex, typename EdgeIndex
#define BOOST_DIR_CSR_GRAPH_TYPE                                          \
    compressed_sparse_row_graph< directedS, VertexProperty, EdgeProperty, \
        GraphProperty, Vertex, EdgeIndex >
#define BOOST_BIDIR_CSR_GRAPH_TEMPLATE_PARMS                                \
    typename VertexProperty, typename EdgeProperty, typename GraphProperty, \
        typename Vertex, typename EdgeIndex
#define BOOST_BIDIR_CSR_GRAPH_TYPE                                             \
    compressed_sparse_row_graph< bidirectionalS, VertexProperty, EdgeProperty, \
        GraphProperty, Vertex, EdgeIndex >

namespace detail
{
    template < typename T >
    struct default_construct_iterator
    : public boost::iterator_facade< default_construct_iterator< T >, T,
          boost::random_access_traversal_tag, const T& >
    {
        typedef boost::iterator_facade< default_construct_iterator< T >, T,
            std::random_access_iterator_tag, const T& >
            base_type;
        T saved_value;
        const T& dereference() const { return saved_value; }
        bool equal(default_construct_iterator /*i*/) const { return true; }
        void increment() {}
        void decrement() {}
        void advance(typename base_type::difference_type) {}
        typename base_type::difference_type distance_to(
            default_construct_iterator) const
        {
            return 0;
        }
    };

    template < typename Less > struct compare_first
    {
        Less less;
        compare_first(Less less = Less()) : less(less) {}
        template < typename Tuple >
        bool operator()(const Tuple& a, const Tuple& b) const
        {
            return less(a.template get< 0 >(), b.template get< 0 >());
        }
    };

    template < int N, typename Result > struct my_tuple_get_class
    {
        typedef const Result& result_type;
        template < typename Tuple > result_type operator()(const Tuple& t) const
        {
            return t.template get< N >();
        }
    };
}

/** Compressed sparse row graph.
 *
 * Vertex and EdgeIndex should be unsigned integral types and should
 * specialize numeric_limits.
 */
template < typename Directed = directedS, typename VertexProperty = no_property,
    typename EdgeProperty = no_property, typename GraphProperty = no_property,
    typename Vertex = std::size_t,
    typename EdgeIndex = Vertex >
class compressed_sparse_row_graph; // Not defined

template < typename VertexProperty, typename EdgeProperty,
    typename GraphProperty, typename Vertex, typename EdgeIndex >
class compressed_sparse_row_graph< directedS, VertexProperty, EdgeProperty,
    GraphProperty, Vertex, EdgeIndex >
: public detail::indexed_vertex_properties< BOOST_DIR_CSR_GRAPH_TYPE,
      VertexProperty, Vertex, typed_identity_property_map< Vertex > >
{
public:
    typedef detail::indexed_vertex_properties< compressed_sparse_row_graph,
        VertexProperty, Vertex, typed_identity_property_map< Vertex > >
        inherited_vertex_properties;

    // Some tests to prevent use of "void" is a property type (as was done in
    // some test cases):
    BOOST_STATIC_ASSERT((!is_same< VertexProperty, void >::value));
    BOOST_STATIC_ASSERT((!is_same< EdgeProperty, void >::value));
    BOOST_STATIC_ASSERT((!is_same< GraphProperty, void >::value));

public:
    // For Property Graph
    typedef GraphProperty graph_property_type;
    typedef typename lookup_one_property< GraphProperty, graph_bundle_t >::type
        graph_bundled;

    typedef detail::compressed_sparse_row_structure< EdgeProperty, Vertex,
        EdgeIndex >
        forward_type;

public:
    /* At this time, the compressed sparse row graph can only be used to
     * create directed and bidirectional graphs. In the future,
     * undirected CSR graphs will also be supported.
     */
    // BOOST_STATIC_ASSERT((is_same<Directed, directedS>::value));

    // Concept requirements:
    // For Graph
    typedef Vertex vertex_descriptor;
    typedef detail::csr_edge_descriptor< Vertex, EdgeIndex > edge_descriptor;
    typedef directed_tag directed_category;
    typedef allow_parallel_edge_tag edge_parallel_category;

    class traversal_category : public incidence_graph_tag,
                               public adjacency_graph_tag,
                               public vertex_list_graph_tag,
                               public edge_list_graph_tag
    {
    };

    static vertex_descriptor null_vertex() { return vertex_descriptor(-1); }

    // For VertexListGraph
    typedef counting_iterator< Vertex > vertex_iterator;
    typedef Vertex vertices_size_type;

    // For EdgeListGraph
    typedef EdgeIndex edges_size_type;

    // For IncidenceGraph
    typedef detail::csr_out_edge_iterator< compressed_sparse_row_graph >
        out_edge_iterator;
    typedef EdgeIndex degree_size_type;

    // For AdjacencyGraph
    typedef typename std::vector< Vertex >::const_iterator adjacency_iterator;

    // For EdgeListGraph
    typedef detail::csr_edge_iterator< compressed_sparse_row_graph >
        edge_iterator;

    // For BidirectionalGraph (not implemented)
    typedef void in_edge_iterator;

    // For internal use
    typedef csr_graph_tag graph_tag;

    typedef typename forward_type::inherited_edge_properties::edge_bundled
        edge_bundled;
    typedef
        typename forward_type::inherited_edge_properties::edge_push_back_type
            edge_push_back_type;
    typedef typename forward_type::inherited_edge_properties::edge_property_type
        edge_property_type;

    // Constructors

    // Default constructor: an empty graph.
    compressed_sparse_row_graph() : m_property() {}

    //  With numverts vertices
    compressed_sparse_row_graph(vertices_size_type numverts)
    : inherited_vertex_properties(numverts), m_forward(numverts)
    {
    }

    //  From number of vertices and unsorted list of edges
    template < typename MultiPassInputIterator >
    compressed_sparse_row_graph(edges_are_unsorted_multi_pass_t,
        MultiPassInputIterator edge_begin, MultiPassInputIterator edge_end,
        vertices_size_type numverts,
        const GraphProperty& prop = GraphProperty())
    : inherited_vertex_properties(numverts), m_property(prop)
    {
        m_forward.assign_unsorted_multi_pass_edges(edge_begin, edge_end,
            numverts, typed_identity_property_map< vertices_size_type >(),
            keep_all());
    }

    //  From number of vertices and unsorted list of edges, plus edge properties
    template < typename MultiPassInputIterator, typename EdgePropertyIterator >
    compressed_sparse_row_graph(edges_are_unsorted_multi_pass_t,
        MultiPassInputIterator edge_begin, MultiPassInputIterator edge_end,
        EdgePropertyIterator ep_iter, vertices_size_type numverts,
        const GraphProperty& prop = GraphProperty())
    : inherited_vertex_properties(numverts), m_forward(), m_property(prop)
    {
        m_forward.assign_unsorted_multi_pass_edges(edge_begin, edge_end,
            ep_iter, numverts,
            typed_identity_property_map< vertices_size_type >(), keep_all());
    }

    //  From number of vertices and unsorted list of edges, with filter and
    //  global-to-local map
    template < typename MultiPassInputIterator, typename GlobalToLocal,
        typename SourcePred >
    compressed_sparse_row_graph(edges_are_unsorted_multi_pass_global_t,
        MultiPassInputIterator edge_begin, MultiPassInputIterator edge_end,
        vertices_size_type numlocalverts, const GlobalToLocal& global_to_local,
        const SourcePred& source_pred,
        const GraphProperty& prop = GraphProperty())
    : inherited_vertex_properties(numlocalverts), m_forward(), m_property(prop)
    {
        m_forward.assign_unsorted_multi_pass_edges(
            edge_begin, edge_end, numlocalverts, global_to_local, source_pred);
    }

    //  From number of vertices and unsorted list of edges, plus edge
    //  properties, with filter and global-to-local map
    template < typename MultiPassInputIterator, typename EdgePropertyIterator,
        typename GlobalToLocal, typename SourcePred >
    compressed_sparse_row_graph(edges_are_unsorted_multi_pass_global_t,
        MultiPassInputIterator edge_begin, MultiPassInputIterator edge_end,
        EdgePropertyIterator ep_iter, vertices_size_type numlocalverts,
        const GlobalToLocal& global_to_local, const SourcePred& source_pred,
        const GraphProperty& prop = GraphProperty())
    : inherited_vertex_properties(numlocalverts), m_forward(), m_property(prop)
    {
        m_forward.assign_unsorted_multi_pass_edges(edge_begin, edge_end,
            ep_iter, numlocalverts, global_to_local, source_pred);
    }

    //  From number of vertices and sorted list of edges (new interface)
    template < typename InputIterator >
    compressed_sparse_row_graph(edges_are_sorted_t, InputIterator edge_begin,
        InputIterator edge_end, vertices_size_type numverts,
        edges_size_type numedges = 0,
        const GraphProperty& prop = GraphProperty())
    : m_property(prop)
    {
        m_forward.assign_from_sorted_edges(edge_begin, edge_end,
            typed_identity_property_map< vertices_size_type >(), keep_all(),
            numverts, numedges);
        inherited_vertex_properties::resize(numverts);
    }

    //  From number of vertices and sorted list of edges (new interface)
    template < typename InputIterator, typename EdgePropertyIterator >
    compressed_sparse_row_graph(edges_are_sorted_t, InputIterator edge_begin,
        InputIterator edge_end, EdgePropertyIterator ep_iter,
        vertices_size_type numverts, edges_size_type numedges = 0,
        const GraphProperty& prop = GraphProperty())
    : m_property(prop)
    {
        m_forward.assign_from_sorted_edges(edge_begin, edge_end, ep_iter,
            typed_identity_property_map< vertices_size_type >(), keep_all(),
            numverts, numedges);
        inherited_vertex_properties::resize(numverts);
    }

    //  From number of vertices and sorted list of edges, filtered and global
    //  (new interface)
    template < typename InputIterator, typename GlobalToLocal,
        typename SourcePred >
    compressed_sparse_row_graph(edges_are_sorted_global_t,
        InputIterator edge_begin, InputIterator edge_end,
        const GlobalToLocal& global_to_local, const SourcePred& source_pred,
        vertices_size_type numverts,
        const GraphProperty& prop = GraphProperty())
    : m_property(prop)
    {
        m_forward.assign_from_sorted_edges(
            edge_begin, edge_end, global_to_local, source_pred, numverts, 0);
        inherited_vertex_properties::resize(numverts);
    }

    //  From number of vertices and sorted list of edges (new interface)
    template < typename InputIterator, typename EdgePropertyIterator,
        typename GlobalToLocal, typename SourcePred >
    compressed_sparse_row_graph(edges_are_sorted_global_t,
        InputIterator edge_begin, InputIterator edge_end,
        EdgePropertyIterator ep_iter, const GlobalToLocal& global_to_local,
        const SourcePred& source_pred, vertices_size_type numverts,
        const GraphProperty& prop = GraphProperty())
    : m_property(prop)
    {
        m_forward.assign_from_sorted_edges(edge_begin, edge_end, ep_iter,
            global_to_local, source_pred, numverts, 0);
        inherited_vertex_properties::resize(numverts);
    }

    //  From number of vertices and mutable vectors of sources and targets;
    //  vectors are returned with unspecified contents but are guaranteed not to
    //  share storage with the constructed graph.
    compressed_sparse_row_graph(construct_inplace_from_sources_and_targets_t,
        std::vector< vertex_descriptor >& sources,
        std::vector< vertex_descriptor >& targets, vertices_size_type numverts,
        const GraphProperty& prop = GraphProperty())
    : inherited_vertex_properties(numverts), m_property(prop)
    {
        m_forward.assign_sources_and_targets_global(sources, targets, numverts,
            boost::typed_identity_property_map< vertices_size_type >());
    }

    //  From number of vertices and mutable vectors of sources and targets,
    //  expressed with global vertex indices; vectors are returned with
    //  unspecified contents but are guaranteed not to share storage with the
    //  constructed graph.  This constructor should only be used by the
    //  distributed CSR graph.
    template < typename GlobalToLocal >
    compressed_sparse_row_graph(
        construct_inplace_from_sources_and_targets_global_t,
        std::vector< vertex_descriptor >& sources,
        std::vector< vertex_descriptor >& targets,
        vertices_size_type numlocalverts, GlobalToLocal global_to_local,
        const GraphProperty& prop = GraphProperty())
    : inherited_vertex_properties(numlocalverts), m_property(prop)
    {
        m_forward.assign_sources_and_targets_global(
            sources, targets, numlocalverts, global_to_local);
    }

    //  From number of vertices and mutable vectors of sources, targets, and
    //  edge properties; vectors are returned with unspecified contents but are
    //  guaranteed not to share storage with the constructed graph.
    compressed_sparse_row_graph(construct_inplace_from_sources_and_targets_t,
        std::vector< vertex_descriptor >& sources,
        std::vector< vertex_descriptor >& targets,
        std::vector<
            typename forward_type::inherited_edge_properties::edge_bundled >&
            edge_props,
        vertices_size_type numverts,
        const GraphProperty& prop = GraphProperty())
    : inherited_vertex_properties(numverts), m_property(prop)
    {
        m_forward.assign_sources_and_targets_global(sources, targets,
            edge_props, numverts,
            boost::typed_identity_property_map< vertices_size_type >());
    }

    //  From number of vertices and mutable vectors of sources and targets and
    //  edge properties, expressed with global vertex indices; vectors are
    //  returned with unspecified contents but are guaranteed not to share
    //  storage with the constructed graph.  This constructor should only be
    //  used by the distributed CSR graph.
    template < typename GlobalToLocal >
    compressed_sparse_row_graph(
        construct_inplace_from_sources_and_targets_global_t,
        std::vector< vertex_descriptor >& sources,
        std::vector< vertex_descriptor >& targets,
        std::vector<
            typename forward_type::inherited_edge_properties::edge_bundled >&
            edge_props,
        vertices_size_type numlocalverts, GlobalToLocal global_to_local,
        const GraphProperty& prop = GraphProperty())
    : inherited_vertex_properties(numlocalverts), m_property(prop)
    {
        m_forward.assign_sources_and_targets_global(
            sources, targets, edge_props, numlocalverts, global_to_local);
    }

    //  From number of vertices and single-pass range of unsorted edges.  Data
    //  is cached in coordinate form before creating the actual graph.
    template < typename InputIterator >
    compressed_sparse_row_graph(edges_are_unsorted_t, InputIterator edge_begin,
        InputIterator edge_end, vertices_size_type numverts,
        const GraphProperty& prop = GraphProperty())
    : inherited_vertex_properties(numverts), m_property(prop)
    {
        std::vector< vertex_descriptor > sources, targets;
        boost::graph::detail::split_into_separate_coords(
            edge_begin, edge_end, sources, targets);
        m_forward.assign_sources_and_targets_global(sources, targets, numverts,
            boost::typed_identity_property_map< vertices_size_type >());
    }

    //  From number of vertices and single-pass range of unsorted edges and
    //  single-pass range of edge properties.  Data is cached in coordinate form
    //  before creating the actual graph.
    template < typename InputIterator, typename EdgePropertyIterator >
    compressed_sparse_row_graph(edges_are_unsorted_t, InputIterator edge_begin,
        InputIterator edge_end, EdgePropertyIterator ep_iter,
        vertices_size_type numverts,
        const GraphProperty& prop = GraphProperty())
    : inherited_vertex_properties(numverts), m_property(prop)
    {
        std::vector< vertex_descriptor > sources, targets;
        boost::graph::detail::split_into_separate_coords(
            edge_begin, edge_end, sources, targets);
        size_t numedges = sources.size();
        std::vector<
            typename forward_type::inherited_edge_properties::edge_bundled >
            edge_props(numedges);
        for (size_t i = 0; i < numedges; ++i)
        {
            edge_props[i] = *ep_iter++;
        }
        m_forward.assign_sources_and_targets_global(sources, targets,
            edge_props, numverts,
            boost::typed_identity_property_map< vertices_size_type >());
    }

    //  From number of vertices and single-pass range of unsorted edges.  Data
    //  is cached in coordinate form before creating the actual graph.  Edges
    //  are filtered and transformed for use in a distributed graph.
    template < typename InputIterator, typename GlobalToLocal,
        typename SourcePred >
    compressed_sparse_row_graph(edges_are_unsorted_global_t,
        InputIterator edge_begin, InputIterator edge_end,
        vertices_size_type numlocalverts, GlobalToLocal global_to_local,
        const SourcePred& source_pred,
        const GraphProperty& prop = GraphProperty())
    : inherited_vertex_properties(numlocalverts), m_property(prop)
    {
        std::vector< vertex_descriptor > sources, targets;
        boost::graph::detail::split_into_separate_coords_filtered(
            edge_begin, edge_end, sources, targets, source_pred);
        m_forward.assign_sources_and_targets_global(
            sources, targets, numlocalverts, global_to_local);
    }

    //  From number of vertices and single-pass range of unsorted edges and
    //  single-pass range of edge properties.  Data is cached in coordinate form
    //  before creating the actual graph.  Edges are filtered and transformed
    //  for use in a distributed graph.
    template < typename InputIterator, typename EdgePropertyIterator,
        typename GlobalToLocal, typename SourcePred >
    compressed_sparse_row_graph(edges_are_unsorted_global_t,
        InputIterator edge_begin, InputIterator edge_end,
        EdgePropertyIterator ep_iter, vertices_size_type numlocalverts,
        GlobalToLocal global_to_local, const SourcePred& source_pred,
        const GraphProperty& prop = GraphProperty())
    : inherited_vertex_properties(numlocalverts), m_property(prop)
    {
        std::vector< vertex_descriptor > sources, targets;
        std::vector< edge_bundled > edge_props;
        boost::graph::detail::split_into_separate_coords_filtered(edge_begin,
            edge_end, ep_iter, sources, targets, edge_props, source_pred);
        m_forward.assign_sources_and_targets_global(
            sources, targets, edge_props, numlocalverts, global_to_local);
    }

    //   Requires IncidenceGraph and a vertex index map
    template < typename Graph, typename VertexIndexMap >
    compressed_sparse_row_graph(const Graph& g, const VertexIndexMap& vi,
        vertices_size_type numverts, edges_size_type numedges)
    : m_property()
    {
        assign(g, vi, numverts, numedges);
        inherited_vertex_properties::resize(numverts);
    }

    //   Requires VertexListGraph and EdgeListGraph
    template < typename Graph, typename VertexIndexMap >
    compressed_sparse_row_graph(const Graph& g, const VertexIndexMap& vi)
    : m_property()
    {
        typename graph_traits< Graph >::edges_size_type numedges = num_edges(g);
        if (is_same< typename graph_traits< Graph >::directed_category,
                undirectedS >::value)
        {
            numedges *= 2; // Double each edge (actual doubling done by
                           // out_edges function)
        }
        vertices_size_type numverts = num_vertices(g);
        assign(g, vi, numverts, numedges);
        inherited_vertex_properties::resize(numverts);
    }

    // Requires vertex index map plus requirements of previous constructor
    template < typename Graph >
    explicit compressed_sparse_row_graph(const Graph& g) : m_property()
    {
        typename graph_traits< Graph >::edges_size_type numedges = num_edges(g);
        if (is_same< typename graph_traits< Graph >::directed_category,
                undirectedS >::value)
        {
            numedges *= 2; // Double each edge (actual doubling done by
                           // out_edges function)
        }
        assign(g, get(vertex_index, g), num_vertices(g), numedges);
    }

    // From any graph (slow and uses a lot of memory)
    //   Requires IncidenceGraph and a vertex index map
    //   Internal helper function
    //   Note that numedges must be doubled for undirected source graphs
    template < typename Graph, typename VertexIndexMap >
    void assign(const Graph& g, const VertexIndexMap& vi,
        vertices_size_type numverts, edges_size_type numedges)
    {
        m_forward.assign(g, vi, numverts, numedges);
        inherited_vertex_properties::resize(numverts);
    }

    // Requires the above, plus VertexListGraph and EdgeListGraph
    template < typename Graph, typename VertexIndexMap >
    void assign(const Graph& g, const VertexIndexMap& vi)
    {
        typename graph_traits< Graph >::edges_size_type numedges = num_edges(g);
        if (is_same< typename graph_traits< Graph >::directed_category,
                undirectedS >::value)
        {
            numedges *= 2; // Double each edge (actual doubling done by
                           // out_edges function)
        }
        vertices_size_type numverts = num_vertices(g);
        m_forward.assign(g, vi, numverts, numedges);
        inherited_vertex_properties::resize(numverts);
    }

    // Requires the above, plus a vertex_index map.
    template < typename Graph > void assign(const Graph& g)
    {
        typename graph_traits< Graph >::edges_size_type numedges = num_edges(g);
        if (is_same< typename graph_traits< Graph >::directed_category,
                undirectedS >::value)
        {
            numedges *= 2; // Double each edge (actual doubling done by
                           // out_edges function)
        }
        vertices_size_type numverts = num_vertices(g);
        m_forward.assign(g, get(vertex_index, g), numverts, numedges);
        inherited_vertex_properties::resize(numverts);
    }

    // Add edges from a sorted (smallest sources first) range of pairs and edge
    // properties
    template < typename BidirectionalIteratorOrig, typename EPIterOrig,
        typename GlobalToLocal >
    void add_edges_sorted_internal(BidirectionalIteratorOrig first_sorted,
        BidirectionalIteratorOrig last_sorted, EPIterOrig ep_iter_sorted,
        const GlobalToLocal& global_to_local)
    {
        m_forward.add_edges_sorted_internal(
            first_sorted, last_sorted, ep_iter_sorted, global_to_local);
    }

    template < typename BidirectionalIteratorOrig, typename EPIterOrig >
    void add_edges_sorted_internal(BidirectionalIteratorOrig first_sorted,
        BidirectionalIteratorOrig last_sorted, EPIterOrig ep_iter_sorted)
    {
        m_forward.add_edges_sorted_internal(first_sorted, last_sorted,
            ep_iter_sorted,
            typed_identity_property_map< vertices_size_type >());
    }

    // Add edges from a sorted (smallest sources first) range of pairs
    template < typename BidirectionalIteratorOrig >
    void add_edges_sorted_internal(BidirectionalIteratorOrig first_sorted,
        BidirectionalIteratorOrig last_sorted)
    {
        m_forward.add_edges_sorted_internal(first_sorted, last_sorted,
            detail::default_construct_iterator< edge_bundled >());
    }

    template < typename BidirectionalIteratorOrig, typename GlobalToLocal >
    void add_edges_sorted_internal_global(
        BidirectionalIteratorOrig first_sorted,
        BidirectionalIteratorOrig last_sorted,
        const GlobalToLocal& global_to_local)
    {
        m_forward.add_edges_sorted_internal(first_sorted, last_sorted,
            detail::default_construct_iterator< edge_bundled >(),
            global_to_local);
    }

    template < typename BidirectionalIteratorOrig, typename EPIterOrig,
        typename GlobalToLocal >
    void add_edges_sorted_internal_global(
        BidirectionalIteratorOrig first_sorted,
        BidirectionalIteratorOrig last_sorted, EPIterOrig ep_iter_sorted,
        const GlobalToLocal& global_to_local)
    {
        m_forward.add_edges_sorted_internal(
            first_sorted, last_sorted, ep_iter_sorted, global_to_local);
    }

    // Add edges from a range of (source, target) pairs that are unsorted
    template < typename InputIterator, typename GlobalToLocal >
    inline void add_edges_internal(InputIterator first, InputIterator last,
        const GlobalToLocal& global_to_local)
    {
        typedef compressed_sparse_row_graph Graph;
        typedef
            typename boost::graph_traits< Graph >::vertex_descriptor vertex_t;
        typedef std::vector< std::pair< vertex_t, vertex_t > > edge_vector_t;
        edge_vector_t new_edges(first, last);
        if (new_edges.empty())
            return;
        std::sort(new_edges.begin(), new_edges.end());
        this->add_edges_sorted_internal_global(
            new_edges.begin(), new_edges.end(), global_to_local);
    }

    template < typename InputIterator >
    inline void add_edges_internal(InputIterator first, InputIterator last)
    {
        this->add_edges_internal(
            first, last, typed_identity_property_map< vertices_size_type >());
    }

    // Add edges from a range of (source, target) pairs and edge properties that
    // are unsorted
    template < typename InputIterator, typename EPIterator,
        typename GlobalToLocal >
    inline void add_edges_internal(InputIterator first, InputIterator last,
        EPIterator ep_iter, EPIterator ep_iter_end,
        const GlobalToLocal& global_to_local)
    {
        typedef compressed_sparse_row_graph Graph;
        typedef
            typename boost::graph_traits< Graph >::vertex_descriptor vertex_t;
        typedef std::pair< vertex_t, vertex_t > vertex_pair;
        typedef std::vector< boost::tuple< vertex_pair, edge_bundled > >
            edge_vector_t;
        edge_vector_t new_edges(
            boost::make_zip_iterator(boost::make_tuple(first, ep_iter)),
            boost::make_zip_iterator(boost::make_tuple(last, ep_iter_end)));
        if (new_edges.empty())
            return;
        std::sort(new_edges.begin(), new_edges.end(),
            boost::detail::compare_first< std::less< vertex_pair > >());
        m_forward.add_edges_sorted_internal(
            boost::make_transform_iterator(new_edges.begin(),
                boost::detail::my_tuple_get_class< 0, vertex_pair >()),
            boost::make_transform_iterator(new_edges.end(),
                boost::detail::my_tuple_get_class< 0, vertex_pair >()),
            boost::make_transform_iterator(new_edges.begin(),
                boost::detail::my_tuple_get_class< 1, edge_bundled >()),
            global_to_local);
    }

    // Add edges from a range of (source, target) pairs and edge properties that
    // are unsorted
    template < typename InputIterator, typename EPIterator >
    inline void add_edges_internal(InputIterator first, InputIterator last,
        EPIterator ep_iter, EPIterator ep_iter_end)
    {
        this->add_edges_internal(first, last, ep_iter, ep_iter_end,
            typed_identity_property_map< vertices_size_type >());
    }

    using inherited_vertex_properties::operator[];

    // Directly access a edge or edge bundle
    edge_push_back_type& operator[](const edge_descriptor& v)
    {
        return m_forward.m_edge_properties[get(edge_index, *this, v)];
    }

    const edge_push_back_type& operator[](const edge_descriptor& v) const
    {
        return m_forward.m_edge_properties[get(edge_index, *this, v)];
    }

    // Directly access a graph bundle
    graph_bundled& operator[](graph_bundle_t) { return get_property(*this); }

    const graph_bundled& operator[](graph_bundle_t) const
    {
        return get_property(*this);
    }

    // private: non-portable, requires friend templates
    inherited_vertex_properties& vertex_properties() { return *this; }
    const inherited_vertex_properties& vertex_properties() const
    {
        return *this;
    }
    typename forward_type::inherited_edge_properties& edge_properties()
    {
        return m_forward;
    }
    const typename forward_type::inherited_edge_properties&
    edge_properties() const
    {
        return m_forward;
    }

    forward_type m_forward;
    GraphProperty m_property;
};

template < typename VertexProperty, typename EdgeProperty,
    typename GraphProperty, typename Vertex, typename EdgeIndex >
class compressed_sparse_row_graph< bidirectionalS, VertexProperty, EdgeProperty,
    GraphProperty, Vertex, EdgeIndex >
: public detail::indexed_vertex_properties< BOOST_BIDIR_CSR_GRAPH_TYPE,
      VertexProperty, Vertex, typed_identity_property_map< Vertex > >
{
public:
    typedef detail::indexed_vertex_properties< compressed_sparse_row_graph,
        VertexProperty, Vertex, typed_identity_property_map< Vertex > >
        inherited_vertex_properties;

public:
    // For Property Graph
    typedef GraphProperty graph_property_type;
    typedef typename lookup_one_property< GraphProperty, graph_bundle_t >::type
        graph_bundled;
    // typedef GraphProperty graph_property_type;

    typedef detail::compressed_sparse_row_structure< EdgeProperty, Vertex,
        EdgeIndex >
        forward_type;
    typedef EdgeIndex /* typename boost::mpl::if_c<boost::is_same<EdgeProperty,
                         boost::no_property>, boost::no_property, EdgeIndex> */
        backward_edge_property;
    typedef detail::compressed_sparse_row_structure< backward_edge_property,
        Vertex, EdgeIndex >
        backward_type;

public:
    // Concept requirements:
    // For Graph
    typedef Vertex vertex_descriptor;
    typedef detail::csr_edge_descriptor< Vertex, EdgeIndex > edge_descriptor;
    typedef bidirectional_tag directed_category;
    typedef allow_parallel_edge_tag edge_parallel_category;

    class traversal_category : public bidirectional_graph_tag,
                               public adjacency_graph_tag,
                               public vertex_list_graph_tag,
                               public edge_list_graph_tag
    {
    };

    static vertex_descriptor null_vertex() { return vertex_descriptor(-1); }

    // For VertexListGraph
    typedef counting_iterator< Vertex > vertex_iterator;
    typedef Vertex vertices_size_type;

    // For EdgeListGraph
    typedef EdgeIndex edges_size_type;

    // For IncidenceGraph
    typedef detail::csr_out_edge_iterator< compressed_sparse_row_graph >
        out_edge_iterator;
    typedef EdgeIndex degree_size_type;

    // For AdjacencyGraph
    typedef typename std::vector< Vertex >::const_iterator adjacency_iterator;

    // For EdgeListGraph
    typedef detail::csr_edge_iterator< compressed_sparse_row_graph >
        edge_iterator;

    // For BidirectionalGraph (not implemented)
    typedef detail::csr_in_edge_iterator< compressed_sparse_row_graph >
        in_edge_iterator;

    // For internal use
    typedef csr_graph_tag graph_tag;

    typedef typename forward_type::inherited_edge_properties::edge_bundled
        edge_bundled;
    typedef
        typename forward_type::inherited_edge_properties::edge_push_back_type
            edge_push_back_type;
    typedef typename forward_type::inherited_edge_properties::edge_property_type
        edge_property_type;

    // Constructors

    // Default constructor: an empty graph.
    compressed_sparse_row_graph() : m_property() {}

    //  With numverts vertices
    compressed_sparse_row_graph(vertices_size_type numverts)
    : inherited_vertex_properties(numverts)
    , m_forward(numverts)
    , m_backward(numverts)
    {
    }

private:
    void set_up_backward_property_links()
    {
        std::pair< edge_iterator, edge_iterator > e = edges(*this);
        m_backward.assign_unsorted_multi_pass_edges(
            detail::transpose_edges(detail::make_edge_to_index_pair_iter(
                *this, get(vertex_index, *this), e.first)),
            detail::transpose_edges(detail::make_edge_to_index_pair_iter(
                *this, get(vertex_index, *this), e.second)),
            boost::counting_iterator< EdgeIndex >(0),
            m_forward.m_rowstart.size() - 1,
            typed_identity_property_map< Vertex >(), keep_all());
    }

public:
    //  From number of vertices and unsorted list of edges
    template < typename MultiPassInputIterator >
    compressed_sparse_row_graph(edges_are_unsorted_multi_pass_t,
        MultiPassInputIterator edge_begin, MultiPassInputIterator edge_end,
        vertices_size_type numverts,
        const GraphProperty& prop = GraphProperty())
    : inherited_vertex_properties(numverts), m_property(prop)
    {
        m_forward.assign_unsorted_multi_pass_edges(edge_begin, edge_end,
            numverts, typed_identity_property_map< Vertex >(), keep_all());
        set_up_backward_property_links();
    }

    //  From number of vertices and unsorted list of edges, plus edge properties
    template < typename MultiPassInputIterator, typename EdgePropertyIterator >
    compressed_sparse_row_graph(edges_are_unsorted_multi_pass_t,
        MultiPassInputIterator edge_begin, MultiPassInputIterator edge_end,
        EdgePropertyIterator ep_iter, vertices_size_type numverts,
        const GraphProperty& prop = GraphProperty())
    : inherited_vertex_properties(numverts), m_forward(), m_property(prop)
    {
        m_forward.assign_unsorted_multi_pass_edges(edge_begin, edge_end,
            ep_iter, numverts, typed_identity_property_map< Vertex >(),
            keep_all());
        set_up_backward_property_links();
    }

    //  From number of vertices and unsorted list of edges, with filter and
    //  global-to-local map
    template < typename MultiPassInputIterator, typename GlobalToLocal,
        typename SourcePred >
    compressed_sparse_row_graph(edges_are_unsorted_multi_pass_global_t,
        MultiPassInputIterator edge_begin, MultiPassInputIterator edge_end,
        vertices_size_type numlocalverts, const GlobalToLocal& global_to_local,
        const SourcePred& source_pred,
        const GraphProperty& prop = GraphProperty())
    : inherited_vertex_properties(numlocalverts), m_forward(), m_property(prop)
    {
        m_forward.assign_unsorted_multi_pass_edges(
            edge_begin, edge_end, numlocalverts, global_to_local, source_pred);
        set_up_backward_property_links();
    }

    //  From number of vertices and unsorted list of edges, plus edge
    //  properties, with filter and global-to-local map
    template < typename MultiPassInputIterator, typename EdgePropertyIterator,
        typename GlobalToLocal, typename SourcePred >
    compressed_sparse_row_graph(edges_are_unsorted_multi_pass_global_t,
        MultiPassInputIterator edge_begin, MultiPassInputIterator edge_end,
        EdgePropertyIterator ep_iter, vertices_size_type numlocalverts,
        const GlobalToLocal& global_to_local, const SourcePred& source_pred,
        const GraphProperty& prop = GraphProperty())
    : inherited_vertex_properties(numlocalverts), m_forward(), m_property(prop)
    {
        m_forward.assign_unsorted_multi_pass_edges(edge_begin, edge_end,
            ep_iter, numlocalverts, global_to_local, source_pred);
        set_up_backward_property_links();
    }

    //   Requires IncidenceGraph and a vertex index map
    template < typename Graph, typename VertexIndexMap >
    compressed_sparse_row_graph(const Graph& g, const VertexIndexMap& vi,
        vertices_size_type numverts, edges_size_type numedges)
    : m_property()
    {
        assign(g, vi, numverts, numedges);
        inherited_vertex_properties::resize(numverts);
    }

    //   Requires VertexListGraph and EdgeListGraph
    template < typename Graph, typename VertexIndexMap >
    compressed_sparse_row_graph(const Graph& g, const VertexIndexMap& vi)
    : m_property()
    {
        typename graph_traits< Graph >::edges_size_type numedges = num_edges(g);
        if (is_same< typename graph_traits< Graph >::directed_category,
                undirectedS >::value)
        {
            numedges *= 2; // Double each edge (actual doubling done by
                           // out_edges function)
        }
        vertices_size_type numverts = num_vertices(g);
        assign(g, vi, numverts, numedges);
        inherited_vertex_properties::resize(numverts);
    }

    // Requires vertex index map plus requirements of previous constructor
    template < typename Graph >
    explicit compressed_sparse_row_graph(const Graph& g) : m_property()
    {
        typename graph_traits< Graph >::edges_size_type numedges = num_edges(g);
        if (is_same< typename graph_traits< Graph >::directed_category,
                undirectedS >::value)
        {
            numedges *= 2; // Double each edge (actual doubling done by
                           // out_edges function)
        }
        assign(g, get(vertex_index, g), num_vertices(g), numedges);
    }

    // From any graph (slow and uses a lot of memory)
    //   Requires IncidenceGraph and a vertex index map
    //   Internal helper function
    //   Note that numedges must be doubled for undirected source graphs
    template < typename Graph, typename VertexIndexMap >
    void assign(const Graph& g, const VertexIndexMap& vi,
        vertices_size_type numverts, edges_size_type numedges)
    {
        m_forward.assign(g, vi, numverts, numedges);
        inherited_vertex_properties::resize(numverts);
        set_up_backward_property_links();
    }

    // Requires the above, plus VertexListGraph and EdgeListGraph
    template < typename Graph, typename VertexIndexMap >
    void assign(const Graph& g, const VertexIndexMap& vi)
    {
        typename graph_traits< Graph >::edges_size_type numedges = num_edges(g);
        if (is_same< typename graph_traits< Graph >::directed_category,
                undirectedS >::value)
        {
            numedges *= 2; // Double each edge (actual doubling done by
                           // out_edges function)
        }
        vertices_size_type numverts = num_vertices(g);
        m_forward.assign(g, vi, numverts, numedges);
        inherited_vertex_properties::resize(numverts);
        set_up_backward_property_links();
    }

    // Requires the above, plus a vertex_index map.
    template < typename Graph > void assign(const Graph& g)
    {
        typename graph_traits< Graph >::edges_size_type numedges = num_edges(g);
        if (is_same< typename graph_traits< Graph >::directed_category,
                undirectedS >::value)
        {
            numedges *= 2; // Double each edge (actual doubling done by
                           // out_edges function)
        }
        vertices_size_type numverts = num_vertices(g);
        m_forward.assign(g, get(vertex_index, g), numverts, numedges);
        inherited_vertex_properties::resize(numverts);
        set_up_backward_property_links();
    }

    using inherited_vertex_properties::operator[];

    // Directly access a edge or edge bundle
    edge_push_back_type& operator[](const edge_descriptor& v)
    {
        return m_forward.m_edge_properties[get(edge_index, *this, v)];
    }

    const edge_push_back_type& operator[](const edge_descriptor& v) const
    {
        return m_forward.m_edge_properties[get(edge_index, *this, v)];
    }

    // private: non-portable, requires friend templates
    inherited_vertex_properties& vertex_properties() { return *this; }
    const inherited_vertex_properties& vertex_properties() const
    {
        return *this;
    }
    typename forward_type::inherited_edge_properties& edge_properties()
    {
        return m_forward;
    }
    const typename forward_type::inherited_edge_properties&
    edge_properties() const
    {
        return m_forward;
    }

    forward_type m_forward;
    backward_type m_backward;
    GraphProperty m_property;
};

// Construction functions
template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
inline Vertex add_vertex(BOOST_CSR_GRAPH_TYPE& g)
{
    add_vertex(g, typename BOOST_CSR_GRAPH_TYPE::vertex_bundled());
}

template < BOOST_DIR_CSR_GRAPH_TEMPLATE_PARMS >
inline Vertex add_vertex(BOOST_DIR_CSR_GRAPH_TYPE& g,
    typename BOOST_DIR_CSR_GRAPH_TYPE::vertex_bundled const& p)
{
    Vertex old_num_verts_plus_one = g.m_forward.m_rowstart.size();
    g.m_forward.m_rowstart.push_back(g.m_forward.m_rowstart.back());
    g.vertex_properties().push_back(p);
    return old_num_verts_plus_one - 1;
}

template < BOOST_BIDIR_CSR_GRAPH_TEMPLATE_PARMS >
inline Vertex add_vertex(BOOST_BIDIR_CSR_GRAPH_TYPE& g,
    typename BOOST_BIDIR_CSR_GRAPH_TYPE::vertex_bundled const& p)
{
    Vertex old_num_verts_plus_one = g.m_forward.m_rowstart.size();
    g.m_forward.m_rowstart.push_back(g.m_forward.m_rowstart.back());
    g.m_backward.m_rowstart.push_back(g.m_backward.m_rowstart.back());
    g.vertex_properties().push_back(p);
    return old_num_verts_plus_one - 1;
}

template < BOOST_DIR_CSR_GRAPH_TEMPLATE_PARMS >
inline Vertex add_vertices(
    typename BOOST_DIR_CSR_GRAPH_TYPE::vertices_size_type count,
    BOOST_DIR_CSR_GRAPH_TYPE& g)
{
    Vertex old_num_verts_plus_one = g.m_forward.m_rowstart.size();
    EdgeIndex numedges = g.m_forward.m_rowstart.back();
    g.m_forward.m_rowstart.resize(old_num_verts_plus_one + count, numedges);
    g.vertex_properties().resize(num_vertices(g));
    return old_num_verts_plus_one - 1;
}

// Add edges from a sorted (smallest sources first) range of pairs and edge
// properties
template < BOOST_DIR_CSR_GRAPH_TEMPLATE_PARMS,
    typename BidirectionalIteratorOrig, typename EPIterOrig >
void add_edges_sorted(BidirectionalIteratorOrig first_sorted,
    BidirectionalIteratorOrig last_sorted, EPIterOrig ep_iter_sorted,
    BOOST_DIR_CSR_GRAPH_TYPE& g)
{
    g.add_edges_sorted_internal(first_sorted, last_sorted, ep_iter_sorted);
}

// Add edges from a sorted (smallest sources first) range of pairs
template < BOOST_DIR_CSR_GRAPH_TEMPLATE_PARMS,
    typename BidirectionalIteratorOrig >
void add_edges_sorted(BidirectionalIteratorOrig first_sorted,
    BidirectionalIteratorOrig last_sorted, BOOST_DIR_CSR_GRAPH_TYPE& g)
{
    g.add_edges_sorted_internal(first_sorted, last_sorted);
}

template < BOOST_DIR_CSR_GRAPH_TEMPLATE_PARMS,
    typename BidirectionalIteratorOrig, typename EPIterOrig,
    typename GlobalToLocal >
void add_edges_sorted_global(BidirectionalIteratorOrig first_sorted,
    BidirectionalIteratorOrig last_sorted, EPIterOrig ep_iter_sorted,
    const GlobalToLocal& global_to_local, BOOST_DIR_CSR_GRAPH_TYPE& g)
{
    g.add_edges_sorted_internal_global(
        first_sorted, last_sorted, ep_iter_sorted, global_to_local);
}

// Add edges from a sorted (smallest sources first) range of pairs
template < BOOST_DIR_CSR_GRAPH_TEMPLATE_PARMS,
    typename BidirectionalIteratorOrig, typename GlobalToLocal >
void add_edges_sorted_global(BidirectionalIteratorOrig first_sorted,
    BidirectionalIteratorOrig last_sorted, const GlobalToLocal& global_to_local,
    BOOST_DIR_CSR_GRAPH_TYPE& g)
{
    g.add_edges_sorted_internal_global(
        first_sorted, last_sorted, global_to_local);
}

// Add edges from a range of (source, target) pairs that are unsorted
template < BOOST_DIR_CSR_GRAPH_TEMPLATE_PARMS, typename InputIterator,
    typename GlobalToLocal >
inline void add_edges_global(InputIterator first, InputIterator last,
    const GlobalToLocal& global_to_local, BOOST_DIR_CSR_GRAPH_TYPE& g)
{
    g.add_edges_internal(first, last, global_to_local);
}

// Add edges from a range of (source, target) pairs that are unsorted
template < BOOST_DIR_CSR_GRAPH_TEMPLATE_PARMS, typename InputIterator >
inline void add_edges(
    InputIterator first, InputIterator last, BOOST_DIR_CSR_GRAPH_TYPE& g)
{
    g.add_edges_internal(first, last);
}

// Add edges from a range of (source, target) pairs and edge properties that
// are unsorted
template < BOOST_DIR_CSR_GRAPH_TEMPLATE_PARMS, typename InputIterator,
    typename EPIterator >
inline void add_edges(InputIterator first, InputIterator last,
    EPIterator ep_iter, EPIterator ep_iter_end, BOOST_DIR_CSR_GRAPH_TYPE& g)
{
    g.add_edges_internal(first, last, ep_iter, ep_iter_end);
}

template < BOOST_DIR_CSR_GRAPH_TEMPLATE_PARMS, typename InputIterator,
    typename EPIterator, typename GlobalToLocal >
inline void add_edges_global(InputIterator first, InputIterator last,
    EPIterator ep_iter, EPIterator ep_iter_end,
    const GlobalToLocal& global_to_local, BOOST_DIR_CSR_GRAPH_TYPE& g)
{
    g.add_edges_internal(first, last, ep_iter, ep_iter_end, global_to_local);
}

// From VertexListGraph
template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
inline Vertex num_vertices(const BOOST_CSR_GRAPH_TYPE& g)
{
    return g.m_forward.m_rowstart.size() - 1;
}

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
std::pair< counting_iterator< Vertex >,
    counting_iterator< Vertex > > inline vertices(const BOOST_CSR_GRAPH_TYPE& g)
{
    return std::make_pair(counting_iterator< Vertex >(0),
        counting_iterator< Vertex >(num_vertices(g)));
}

// From IncidenceGraph
template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
inline Vertex source(typename BOOST_CSR_GRAPH_TYPE::edge_descriptor e,
    const BOOST_CSR_GRAPH_TYPE&)
{
    return e.src;
}

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
inline Vertex target(typename BOOST_CSR_GRAPH_TYPE::edge_descriptor e,
    const BOOST_CSR_GRAPH_TYPE& g)
{
    return g.m_forward.m_column[e.idx];
}

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
inline std::pair< typename BOOST_CSR_GRAPH_TYPE::out_edge_iterator,
    typename BOOST_CSR_GRAPH_TYPE::out_edge_iterator >
out_edges(Vertex v, const BOOST_CSR_GRAPH_TYPE& g)
{
    typedef typename BOOST_CSR_GRAPH_TYPE::edge_descriptor ed;
    typedef typename BOOST_CSR_GRAPH_TYPE::out_edge_iterator it;
    EdgeIndex v_row_start = g.m_forward.m_rowstart[v];
    EdgeIndex next_row_start = g.m_forward.m_rowstart[v + 1];
    return std::make_pair(it(ed(v, v_row_start)), it(ed(v, next_row_start)));
}

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
inline EdgeIndex out_degree(Vertex v, const BOOST_CSR_GRAPH_TYPE& g)
{
    EdgeIndex v_row_start = g.m_forward.m_rowstart[v];
    EdgeIndex next_row_start = g.m_forward.m_rowstart[v + 1];
    return next_row_start - v_row_start;
}

template < BOOST_BIDIR_CSR_GRAPH_TEMPLATE_PARMS >
inline std::pair< typename BOOST_BIDIR_CSR_GRAPH_TYPE::in_edge_iterator,
    typename BOOST_BIDIR_CSR_GRAPH_TYPE::in_edge_iterator >
in_edges(Vertex v, const BOOST_BIDIR_CSR_GRAPH_TYPE& g)
{
    typedef typename BOOST_BIDIR_CSR_GRAPH_TYPE::in_edge_iterator it;
    EdgeIndex v_row_start = g.m_backward.m_rowstart[v];
    EdgeIndex next_row_start = g.m_backward.m_rowstart[v + 1];
    return std::make_pair(it(g, v_row_start), it(g, next_row_start));
}

template < BOOST_BIDIR_CSR_GRAPH_TEMPLATE_PARMS >
inline EdgeIndex in_degree(Vertex v, const BOOST_BIDIR_CSR_GRAPH_TYPE& g)
{
    EdgeIndex v_row_start = g.m_backward.m_rowstart[v];
    EdgeIndex next_row_start = g.m_backward.m_rowstart[v + 1];
    return next_row_start - v_row_start;
}

// From AdjacencyGraph
template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
inline std::pair< typename BOOST_CSR_GRAPH_TYPE::adjacency_iterator,
    typename BOOST_CSR_GRAPH_TYPE::adjacency_iterator >
adjacent_vertices(Vertex v, const BOOST_CSR_GRAPH_TYPE& g)
{
    EdgeIndex v_row_start = g.m_forward.m_rowstart[v];
    EdgeIndex next_row_start = g.m_forward.m_rowstart[v + 1];
    return std::make_pair(g.m_forward.m_column.begin() + v_row_start,
        g.m_forward.m_column.begin() + next_row_start);
}

// Extra, common functions
template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
inline typename graph_traits< BOOST_CSR_GRAPH_TYPE >::vertex_descriptor vertex(
    typename graph_traits< BOOST_CSR_GRAPH_TYPE >::vertex_descriptor i,
    const BOOST_CSR_GRAPH_TYPE&)
{
    return i;
}

// edge() can be provided in linear time for the new interface

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
inline std::pair< typename BOOST_CSR_GRAPH_TYPE::edge_descriptor, bool > edge(
    Vertex i, Vertex j, const BOOST_CSR_GRAPH_TYPE& g)
{
    typedef typename BOOST_CSR_GRAPH_TYPE::out_edge_iterator out_edge_iter;
    std::pair< out_edge_iter, out_edge_iter > range = out_edges(i, g);
    for (; range.first != range.second; ++range.first)
    {
        if (target(*range.first, g) == j)
            return std::make_pair(*range.first, true);
    }
    return std::make_pair(
        typename BOOST_CSR_GRAPH_TYPE::edge_descriptor(), false);
}

// Find an edge given its index in the graph
template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
inline typename BOOST_CSR_GRAPH_TYPE::edge_descriptor edge_from_index(
    EdgeIndex idx, const BOOST_CSR_GRAPH_TYPE& g)
{
    typedef typename std::vector< EdgeIndex >::const_iterator row_start_iter;
    BOOST_ASSERT(idx < num_edges(g));
    row_start_iter src_plus_1 = std::upper_bound(
        g.m_forward.m_rowstart.begin(), g.m_forward.m_rowstart.end(), idx);
    // Get last source whose rowstart is at most idx
    // upper_bound returns this position plus 1
    Vertex src = (src_plus_1 - g.m_forward.m_rowstart.begin()) - 1;
    return typename BOOST_CSR_GRAPH_TYPE::edge_descriptor(src, idx);
}

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
inline EdgeIndex num_edges(const BOOST_CSR_GRAPH_TYPE& g)
{
    return g.m_forward.m_column.size();
}

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
std::pair< typename BOOST_CSR_GRAPH_TYPE::edge_iterator,
    typename BOOST_CSR_GRAPH_TYPE::edge_iterator >
edges(const BOOST_CSR_GRAPH_TYPE& g)
{
    typedef typename BOOST_CSR_GRAPH_TYPE::edge_iterator ei;
    typedef typename BOOST_CSR_GRAPH_TYPE::edge_descriptor edgedesc;
    if (g.m_forward.m_rowstart.size() == 1 || g.m_forward.m_column.empty())
    {
        return std::make_pair(ei(), ei());
    }
    else
    {
        // Find the first vertex that has outgoing edges
        Vertex src = 0;
        while (g.m_forward.m_rowstart[src + 1] == 0)
            ++src;
        return std::make_pair(
            ei(g, edgedesc(src, 0), g.m_forward.m_rowstart[src + 1]),
            ei(g, edgedesc(num_vertices(g), g.m_forward.m_column.size()), 0));
    }
}

// For Property Graph

// Graph properties
template < BOOST_CSR_GRAPH_TEMPLATE_PARMS, class Tag, class Value >
inline void set_property(BOOST_CSR_GRAPH_TYPE& g, Tag tag, const Value& value)
{
    get_property_value(g.m_property, tag) = value;
}

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS, class Tag >
inline typename graph_property< BOOST_CSR_GRAPH_TYPE, Tag >::type& get_property(
    BOOST_CSR_GRAPH_TYPE& g, Tag tag)
{
    return get_property_value(g.m_property, tag);
}

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS, class Tag >
inline const typename graph_property< BOOST_CSR_GRAPH_TYPE, Tag >::type&
get_property(const BOOST_CSR_GRAPH_TYPE& g, Tag tag)
{
    return get_property_value(g.m_property, tag);
}

template < typename G, typename Tag, typename Kind >
struct csr_property_map_helper
{
};
// Kind == void for invalid property tags, so we can use that to SFINAE out

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS, typename Tag >
struct csr_property_map_helper< BOOST_CSR_GRAPH_TYPE, Tag, vertex_property_tag >
{
    typedef vertex_all_t all_tag;
    typedef
        typename property_traits< typename property_map< BOOST_CSR_GRAPH_TYPE,
            vertex_all_t >::type >::key_type key_type;
    typedef VertexProperty plist_type;
    typedef typename property_map< BOOST_CSR_GRAPH_TYPE, vertex_all_t >::type
        all_type;
    typedef
        typename property_map< BOOST_CSR_GRAPH_TYPE, vertex_all_t >::const_type
            all_const_type;
    typedef transform_value_property_map<
        detail::lookup_one_property_f< plist_type, Tag >, all_type >
        type;
    typedef transform_value_property_map<
        detail::lookup_one_property_f< const plist_type, Tag >, all_const_type >
        const_type;
};

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS, typename Tag >
struct csr_property_map_helper< BOOST_CSR_GRAPH_TYPE, Tag, edge_property_tag >
{
    typedef edge_all_t all_tag;
    typedef
        typename property_traits< typename property_map< BOOST_CSR_GRAPH_TYPE,
            edge_all_t >::type >::key_type key_type;
    typedef EdgeProperty plist_type;
    typedef typename property_map< BOOST_CSR_GRAPH_TYPE, edge_all_t >::type
        all_type;
    typedef
        typename property_map< BOOST_CSR_GRAPH_TYPE, edge_all_t >::const_type
            all_const_type;
    typedef transform_value_property_map<
        detail::lookup_one_property_f< plist_type, Tag >, all_type >
        type;
    typedef transform_value_property_map<
        detail::lookup_one_property_f< const plist_type, Tag >, all_const_type >
        const_type;
};

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS, typename Tag >
struct csr_property_map_helper< BOOST_CSR_GRAPH_TYPE, Tag, graph_property_tag >
{
    typedef graph_all_t all_tag;
    typedef BOOST_CSR_GRAPH_TYPE* key_type;
    typedef GraphProperty plist_type;
    typedef typename property_map< BOOST_CSR_GRAPH_TYPE, graph_all_t >::type
        all_type;
    typedef
        typename property_map< BOOST_CSR_GRAPH_TYPE, graph_all_t >::const_type
            all_const_type;
    typedef transform_value_property_map<
        detail::lookup_one_property_f< plist_type, Tag >, all_type >
        type;
    typedef transform_value_property_map<
        detail::lookup_one_property_f< const plist_type, Tag >, all_const_type >
        const_type;
};

// disable_if isn't truly necessary but required to avoid ambiguity with
// specializations below
template < BOOST_CSR_GRAPH_TEMPLATE_PARMS, typename Tag >
struct property_map< BOOST_CSR_GRAPH_TYPE, Tag,
    typename disable_if< detail::is_distributed_selector< Vertex > >::type >
: csr_property_map_helper< BOOST_CSR_GRAPH_TYPE, Tag,
      typename detail::property_kind_from_graph< BOOST_CSR_GRAPH_TYPE,
          Tag >::type >
{
};

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS, typename Tag >
typename property_map< BOOST_CSR_GRAPH_TYPE, Tag >::type get(
    Tag tag, BOOST_CSR_GRAPH_TYPE& g)
{
    return typename property_map< BOOST_CSR_GRAPH_TYPE, Tag >::type(tag,
        get(typename property_map< BOOST_CSR_GRAPH_TYPE, Tag >::all_tag(), g));
}

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS, typename Tag >
typename property_map< BOOST_CSR_GRAPH_TYPE, Tag >::const_type get(
    Tag tag, const BOOST_CSR_GRAPH_TYPE& g)
{
    return typename property_map< BOOST_CSR_GRAPH_TYPE, Tag >::const_type(tag,
        get(typename property_map< BOOST_CSR_GRAPH_TYPE, Tag >::all_tag(), g));
}

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS, typename Tag >
typename property_traits<
    typename property_map< BOOST_CSR_GRAPH_TYPE, Tag >::type >::reference
get(Tag tag, BOOST_CSR_GRAPH_TYPE& g,
    typename property_map< BOOST_CSR_GRAPH_TYPE, Tag >::key_type k)
{
    typedef typename property_map< BOOST_CSR_GRAPH_TYPE, Tag >::all_tag all_tag;
    typedef
        typename property_map< BOOST_CSR_GRAPH_TYPE, all_tag >::type outer_pm;
    return lookup_one_property<
        typename property_traits< outer_pm >::value_type,
        Tag >::lookup(get(all_tag(), g, k), tag);
}

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS, typename Tag >
typename property_traits<
    typename property_map< BOOST_CSR_GRAPH_TYPE, Tag >::const_type >::reference
get(Tag tag, const BOOST_CSR_GRAPH_TYPE& g,
    typename property_map< BOOST_CSR_GRAPH_TYPE, Tag >::key_type k)
{
    typedef typename property_map< BOOST_CSR_GRAPH_TYPE, Tag >::all_tag all_tag;
    typedef typename property_map< BOOST_CSR_GRAPH_TYPE, all_tag >::const_type
        outer_pm;
    return lookup_one_property<
        const typename property_traits< outer_pm >::value_type,
        Tag >::lookup(get(all_tag(), g, k), tag);
}

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS, typename Tag >
void put(Tag tag, BOOST_CSR_GRAPH_TYPE& g,
    typename property_map< BOOST_CSR_GRAPH_TYPE, Tag >::key_type k,
    typename lookup_one_property<
        typename property_map< BOOST_CSR_GRAPH_TYPE, Tag >::plist_type,
        Tag >::type val)
{
    typedef typename property_map< BOOST_CSR_GRAPH_TYPE, Tag >::all_tag all_tag;
    lookup_one_property<
        typename property_map< BOOST_CSR_GRAPH_TYPE, Tag >::plist_type,
        Tag >::lookup(get(all_tag(), g, k), tag)
        = val;
}

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
struct property_map< BOOST_CSR_GRAPH_TYPE, vertex_index_t,
    typename disable_if< detail::is_distributed_selector< Vertex > >::type >
{
    typedef typed_identity_property_map< Vertex > type;
    typedef type const_type;
};

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
struct property_map< BOOST_CSR_GRAPH_TYPE, edge_index_t,
    typename disable_if< detail::is_distributed_selector< Vertex > >::type >
{
    typedef detail::csr_edge_index_map< Vertex, EdgeIndex > type;
    typedef type const_type;
};

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
struct property_map< BOOST_CSR_GRAPH_TYPE, vertex_all_t,
    typename disable_if< detail::is_distributed_selector< Vertex > >::type >
{
    typedef typename BOOST_CSR_GRAPH_TYPE::inherited_vertex_properties::
        vertex_map_type type;
    typedef typename BOOST_CSR_GRAPH_TYPE::inherited_vertex_properties::
        const_vertex_map_type const_type;
};

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
struct property_map< BOOST_CSR_GRAPH_TYPE, edge_all_t,
    typename disable_if< detail::is_distributed_selector< Vertex > >::type >
{
    typedef typename BOOST_CSR_GRAPH_TYPE::forward_type::
        inherited_edge_properties::edge_map_type type;
    typedef typename BOOST_CSR_GRAPH_TYPE::forward_type::
        inherited_edge_properties::const_edge_map_type const_type;
};

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
struct property_map< BOOST_CSR_GRAPH_TYPE, graph_all_t,
    typename disable_if< detail::is_distributed_selector< Vertex > >::type >
{
    typedef boost::ref_property_map< BOOST_CSR_GRAPH_TYPE*,
        typename BOOST_CSR_GRAPH_TYPE::graph_property_type >
        type;
    typedef boost::ref_property_map< BOOST_CSR_GRAPH_TYPE*,
        const typename BOOST_CSR_GRAPH_TYPE::graph_property_type >
        const_type;
};

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
inline typed_identity_property_map< Vertex > get(
    vertex_index_t, const BOOST_CSR_GRAPH_TYPE&)
{
    return typed_identity_property_map< Vertex >();
}

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
inline Vertex get(vertex_index_t, const BOOST_CSR_GRAPH_TYPE&, Vertex v)
{
    return v;
}

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
inline typed_identity_property_map< Vertex > get(
    vertex_index_t, BOOST_CSR_GRAPH_TYPE&)
{
    return typed_identity_property_map< Vertex >();
}

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
inline Vertex get(vertex_index_t, BOOST_CSR_GRAPH_TYPE&, Vertex v)
{
    return v;
}

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
inline typename property_map< BOOST_CSR_GRAPH_TYPE, edge_index_t >::const_type
get(edge_index_t, const BOOST_CSR_GRAPH_TYPE&)
{
    typedef
        typename property_map< BOOST_CSR_GRAPH_TYPE, edge_index_t >::const_type
            result_type;
    return result_type();
}

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
inline EdgeIndex get(edge_index_t, const BOOST_CSR_GRAPH_TYPE&,
    typename BOOST_CSR_GRAPH_TYPE::edge_descriptor e)
{
    return e.idx;
}

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
inline typename property_map< BOOST_CSR_GRAPH_TYPE, edge_index_t >::const_type
get(edge_index_t, BOOST_CSR_GRAPH_TYPE&)
{
    typedef
        typename property_map< BOOST_CSR_GRAPH_TYPE, edge_index_t >::const_type
            result_type;
    return result_type();
}

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
inline EdgeIndex get(edge_index_t, BOOST_CSR_GRAPH_TYPE&,
    typename BOOST_CSR_GRAPH_TYPE::edge_descriptor e)
{
    return e.idx;
}

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
inline typename property_map< BOOST_CSR_GRAPH_TYPE, vertex_all_t >::type get(
    vertex_all_t, BOOST_CSR_GRAPH_TYPE& g)
{
    return g.get_vertex_bundle(get(vertex_index, g));
}

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
inline typename property_map< BOOST_CSR_GRAPH_TYPE, vertex_all_t >::const_type
get(vertex_all_t, const BOOST_CSR_GRAPH_TYPE& g)
{
    return g.get_vertex_bundle(get(vertex_index, g));
}

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
inline VertexProperty& get(vertex_all_t, BOOST_CSR_GRAPH_TYPE& g, Vertex v)
{
    return get(vertex_all, g)[v];
}

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
inline const VertexProperty& get(
    vertex_all_t, const BOOST_CSR_GRAPH_TYPE& g, Vertex v)
{
    return get(vertex_all, g)[v];
}

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
inline void put(
    vertex_all_t, BOOST_CSR_GRAPH_TYPE& g, Vertex v, const VertexProperty& val)
{
    put(get(vertex_all, g), v, val);
}

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
inline typename property_map< BOOST_CSR_GRAPH_TYPE, edge_all_t >::type get(
    edge_all_t, BOOST_CSR_GRAPH_TYPE& g)
{
    return g.m_forward.get_edge_bundle(get(edge_index, g));
}

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
inline typename property_map< BOOST_CSR_GRAPH_TYPE, edge_all_t >::const_type
get(edge_all_t, const BOOST_CSR_GRAPH_TYPE& g)
{
    return g.m_forward.get_edge_bundle(get(edge_index, g));
}

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
inline EdgeProperty& get(edge_all_t, BOOST_CSR_GRAPH_TYPE& g,
    const typename BOOST_CSR_GRAPH_TYPE::edge_descriptor& e)
{
    return get(edge_all, g)[e];
}

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
inline const EdgeProperty& get(edge_all_t, const BOOST_CSR_GRAPH_TYPE& g,
    const typename BOOST_CSR_GRAPH_TYPE::edge_descriptor& e)
{
    return get(edge_all, g)[e];
}

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
inline void put(edge_all_t, BOOST_CSR_GRAPH_TYPE& g,
    const typename BOOST_CSR_GRAPH_TYPE::edge_descriptor& e,
    const EdgeProperty& val)
{
    put(get(edge_all, g), e, val);
}

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
inline typename property_map< BOOST_CSR_GRAPH_TYPE, graph_all_t >::type get(
    graph_all_t, BOOST_CSR_GRAPH_TYPE& g)
{
    return typename property_map< BOOST_CSR_GRAPH_TYPE, graph_all_t >::type(
        g.m_property);
}

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
inline typename property_map< BOOST_CSR_GRAPH_TYPE, graph_all_t >::const_type
get(graph_all_t, const BOOST_CSR_GRAPH_TYPE& g)
{
    return
        typename property_map< BOOST_CSR_GRAPH_TYPE, graph_all_t >::const_type(
            g.m_property);
}

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
inline GraphProperty& get(
    graph_all_t, BOOST_CSR_GRAPH_TYPE& g, BOOST_CSR_GRAPH_TYPE*)
{
    return g.m_property;
}

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
inline const GraphProperty& get(
    graph_all_t, const BOOST_CSR_GRAPH_TYPE& g, BOOST_CSR_GRAPH_TYPE*)
{
    return g.m_property;
}

template < BOOST_CSR_GRAPH_TEMPLATE_PARMS >
inline void put(graph_all_t, BOOST_CSR_GRAPH_TYPE& g, BOOST_CSR_GRAPH_TYPE*,
    const GraphProperty& val)
{
    g.m_property = val;
}

#undef BOOST_CSR_GRAPH_TYPE
#undef BOOST_CSR_GRAPH_TEMPLATE_PARMS
#undef BOOST_DIR_CSR_GRAPH_TYPE
#undef BOOST_DIR_CSR_GRAPH_TEMPLATE_PARMS
#undef BOOST_BIDIR_CSR_GRAPH_TYPE
#undef BOOST_BIDIR_CSR_GRAPH_TEMPLATE_PARMS

} // end namespace boost

#endif // BOOST_GRAPH_COMPRESSED_SPARSE_ROW_GRAPH_HPP

/* compressed_sparse_row_graph.hpp
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
*/