//=======================================================================
// Copyright 2001 University of Notre Dame.
// Copyright 2006 Trustees of Indiana University
// Authors: Jeremy G. Siek and Douglas Gregor <dgregor@cs.indiana.edu>
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_ADJACENCY_MATRIX_HPP
#define BOOST_ADJACENCY_MATRIX_HPP

#include <boost/config.hpp>
#include <vector>
#include <memory>
#include <iterator>
#include <boost/assert.hpp>
#include <boost/limits.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_mutability_traits.hpp>
#include <boost/graph/graph_selectors.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/graph/adjacency_iterator.hpp>
#include <boost/graph/detail/edge.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/filter_iterator.hpp>
#include <boost/range/irange.hpp>
#include <boost/graph/properties.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/property_map/transform_value_property_map.hpp>
#include <boost/property_map/function_property_map.hpp>

namespace boost
{

namespace detail
{

    template < class Directed, class Vertex >
    class matrix_edge_desc_impl : public edge_desc_impl< Directed, Vertex >
    {
        typedef edge_desc_impl< Directed, Vertex > Base;

    public:
        matrix_edge_desc_impl() {}
        matrix_edge_desc_impl(
            bool exists, Vertex s, Vertex d, const void* ep = 0)
        : Base(s, d, ep), m_exists(exists)
        {
        }
        bool exists() const { return m_exists; }

    private:
        bool m_exists;
    };

    struct does_edge_exist
    {
        template < class Edge > bool operator()(const Edge& e) const
        {
            return e.exists();
        }
    };

    // Note to self... The int for get_edge_exists and set_edge exist helps
    // make these calls unambiguous.
    template < typename EdgeProperty >
    bool get_edge_exists(
        const std::pair< bool, EdgeProperty >& stored_edge, int)
    {
        return stored_edge.first;
    }
    template < typename EdgeProperty >
    void set_edge_exists(
        std::pair< bool, EdgeProperty >& stored_edge, bool flag, int)
    {
        stored_edge.first = flag;
    }

    template < typename EdgeProxy >
    bool get_edge_exists(const EdgeProxy& edge_proxy, ...)
    {
        return edge_proxy;
    }
    template < typename EdgeProxy >
    EdgeProxy& set_edge_exists(EdgeProxy& edge_proxy, bool flag, ...)
    {
        edge_proxy = flag;
        return edge_proxy; // just to avoid never used warning
    }

    // NOTE: These functions collide with the get_property function for
    // accessing bundled graph properties. Be excplicit when using them.
    template < typename EdgeProperty >
    const EdgeProperty& get_edge_property(
        const std::pair< bool, EdgeProperty >& stored_edge)
    {
        return stored_edge.second;
    }
    template < typename EdgeProperty >
    EdgeProperty& get_edge_property(
        std::pair< bool, EdgeProperty >& stored_edge)
    {
        return stored_edge.second;
    }

    template < typename StoredEdgeProperty, typename EdgeProperty >
    inline void set_edge_property(
        std::pair< bool, StoredEdgeProperty >& stored_edge,
        const EdgeProperty& ep, int)
    {
        stored_edge.second = ep;
    }

    inline const no_property& get_edge_property(const char&)
    {
        static no_property s_prop;
        return s_prop;
    }
    inline no_property& get_edge_property(char&)
    {
        static no_property s_prop;
        return s_prop;
    }
    template < typename EdgeProxy, typename EdgeProperty >
    inline void set_edge_property(EdgeProxy, const EdgeProperty&, ...)
    {
    }

    //=======================================================================
    // Directed Out Edge Iterator

    template < typename VertexDescriptor, typename MatrixIter,
        typename VerticesSizeType, typename EdgeDescriptor >
    struct dir_adj_matrix_out_edge_iter
    : iterator_adaptor< dir_adj_matrix_out_edge_iter< VertexDescriptor,
                            MatrixIter, VerticesSizeType, EdgeDescriptor >,
          MatrixIter, EdgeDescriptor, use_default, EdgeDescriptor,
          std::ptrdiff_t >
    {
        typedef iterator_adaptor<
            dir_adj_matrix_out_edge_iter< VertexDescriptor, MatrixIter,
                VerticesSizeType, EdgeDescriptor >,
            MatrixIter, EdgeDescriptor, use_default, EdgeDescriptor,
            std::ptrdiff_t >
            super_t;

        dir_adj_matrix_out_edge_iter() {}

        dir_adj_matrix_out_edge_iter(const MatrixIter& i,
            const VertexDescriptor& src, const VerticesSizeType& n)
        : super_t(i), m_src(src), m_targ(0), m_n(n)
        {
        }

        void increment()
        {
            ++this->base_reference();
            ++m_targ;
        }

        inline EdgeDescriptor dereference() const
        {
            return EdgeDescriptor(get_edge_exists(*this->base(), 0), m_src,
                m_targ, &get_edge_property(*this->base()));
        }
        VertexDescriptor m_src, m_targ;
        VerticesSizeType m_n;
    };

    //=======================================================================
    // Directed In Edge Iterator

    template < typename VertexDescriptor, typename MatrixIter,
        typename VerticesSizeType, typename EdgeDescriptor >
    struct dir_adj_matrix_in_edge_iter
    : iterator_adaptor< dir_adj_matrix_in_edge_iter< VertexDescriptor,
                            MatrixIter, VerticesSizeType, EdgeDescriptor >,
          MatrixIter, EdgeDescriptor, use_default, EdgeDescriptor,
          std::ptrdiff_t >
    {
        typedef iterator_adaptor<
            dir_adj_matrix_in_edge_iter< VertexDescriptor, MatrixIter,
                VerticesSizeType, EdgeDescriptor >,
            MatrixIter, EdgeDescriptor, use_default, EdgeDescriptor,
            std::ptrdiff_t >
            super_t;

        dir_adj_matrix_in_edge_iter() {}

        dir_adj_matrix_in_edge_iter(const MatrixIter& i, const MatrixIter& last,
            const VertexDescriptor& tgt, const VerticesSizeType& n)
        : super_t(i), m_last(last), m_src(0), m_targ(tgt), m_n(n)
        {
        }

        void increment()
        {
            if (VerticesSizeType(m_last - this->base_reference()) >= m_n)
            {
                this->base_reference() += m_n;
                ++m_src;
            }
            else
            {
                this->base_reference() = m_last;
            }
        }

        inline EdgeDescriptor dereference() const
        {
            return EdgeDescriptor(get_edge_exists(*this->base(), 0), m_src,
                m_targ, &get_edge_property(*this->base()));
        }
        MatrixIter m_last;
        VertexDescriptor m_src, m_targ;
        VerticesSizeType m_n;
    };

    //=======================================================================
    // Undirected Out Edge Iterator

    template < typename VertexDescriptor, typename MatrixIter,
        typename VerticesSizeType, typename EdgeDescriptor >
    struct undir_adj_matrix_out_edge_iter
    : iterator_adaptor< undir_adj_matrix_out_edge_iter< VertexDescriptor,
                            MatrixIter, VerticesSizeType, EdgeDescriptor >,
          MatrixIter, EdgeDescriptor, use_default, EdgeDescriptor,
          std::ptrdiff_t >
    {
        typedef iterator_adaptor<
            undir_adj_matrix_out_edge_iter< VertexDescriptor, MatrixIter,
                VerticesSizeType, EdgeDescriptor >,
            MatrixIter, EdgeDescriptor, use_default, EdgeDescriptor,
            std::ptrdiff_t >
            super_t;

        undir_adj_matrix_out_edge_iter() {}

        undir_adj_matrix_out_edge_iter(const MatrixIter& i,
            const VertexDescriptor& src, const VerticesSizeType& n)
        : super_t(i), m_src(src), m_inc(src), m_targ(0), m_n(n)
        {
        }

        void increment()
        {
            if (m_targ < m_src) // first half
            {
                ++this->base_reference();
            }
            else if (m_targ < m_n - 1)
            { // second half
                ++m_inc;
                this->base_reference() += m_inc;
            }
            else
            { // past-the-end
                this->base_reference() += m_n - m_src;
            }
            ++m_targ;
        }

        inline EdgeDescriptor dereference() const
        {
            return EdgeDescriptor(get_edge_exists(*this->base(), 0), m_src,
                m_targ, &get_edge_property(*this->base()));
        }

        VertexDescriptor m_src, m_inc, m_targ;
        VerticesSizeType m_n;
    };

    //=======================================================================
    // Undirected In Edge Iterator

    template < typename VertexDescriptor, typename MatrixIter,
        typename VerticesSizeType, typename EdgeDescriptor >
    struct undir_adj_matrix_in_edge_iter
    : iterator_adaptor< undir_adj_matrix_in_edge_iter< VertexDescriptor,
                            MatrixIter, VerticesSizeType, EdgeDescriptor >,
          MatrixIter, EdgeDescriptor, use_default, EdgeDescriptor,
          std::ptrdiff_t >
    {
        typedef iterator_adaptor<
            undir_adj_matrix_in_edge_iter< VertexDescriptor, MatrixIter,
                VerticesSizeType, EdgeDescriptor >,
            MatrixIter, EdgeDescriptor, use_default, EdgeDescriptor,
            std::ptrdiff_t >
            super_t;

        undir_adj_matrix_in_edge_iter() {}

        undir_adj_matrix_in_edge_iter(const MatrixIter& i,
            const VertexDescriptor& src, const VerticesSizeType& n)
        : super_t(i), m_src(src), m_inc(src), m_targ(0), m_n(n)
        {
        }

        void increment()
        {
            if (m_targ < m_src) // first half
            {
                ++this->base_reference();
            }
            else if (m_targ < m_n - 1)
            { // second half
                ++m_inc;
                this->base_reference() += m_inc;
            }
            else
            { // past-the-end
                this->base_reference() += m_n - m_src;
            }
            ++m_targ;
        }

        inline EdgeDescriptor dereference() const
        {
            return EdgeDescriptor(get_edge_exists(*this->base(), 0), m_targ,
                m_src, &get_edge_property(*this->base()));
        }

        VertexDescriptor m_src, m_inc, m_targ;
        VerticesSizeType m_n;
    };

    //=======================================================================
    // Edge Iterator

    template < typename Directed, typename MatrixIter,
        typename VerticesSizeType, typename EdgeDescriptor >
    struct adj_matrix_edge_iter
    : iterator_adaptor< adj_matrix_edge_iter< Directed, MatrixIter,
                            VerticesSizeType, EdgeDescriptor >,
          MatrixIter, EdgeDescriptor, use_default, EdgeDescriptor,
          std::ptrdiff_t >
    {
        typedef iterator_adaptor< adj_matrix_edge_iter< Directed, MatrixIter,
                                      VerticesSizeType, EdgeDescriptor >,
            MatrixIter, EdgeDescriptor, use_default, EdgeDescriptor,
            std::ptrdiff_t >
            super_t;

        adj_matrix_edge_iter() {}

        adj_matrix_edge_iter(const MatrixIter& i, const MatrixIter& start,
            const VerticesSizeType& n)
        : super_t(i), m_start(start), m_src(0), m_targ(0), m_n(n)
        {
        }

        void increment()
        {
            increment_dispatch(this->base_reference(), Directed());
        }

        void increment_dispatch(MatrixIter& i, directedS)
        {
            ++i;
            if (m_targ == m_n - 1)
            {
                m_targ = 0;
                ++m_src;
            }
            else
            {
                ++m_targ;
            }
        }

        void increment_dispatch(MatrixIter& i, undirectedS)
        {
            ++i;
            if (m_targ == m_src)
            {
                m_targ = 0;
                ++m_src;
            }
            else
            {
                ++m_targ;
            }
        }

        inline EdgeDescriptor dereference() const
        {
            return EdgeDescriptor(get_edge_exists(*this->base(), 0), m_src,
                m_targ, &get_edge_property(*this->base()));
        }

        MatrixIter m_start;
        VerticesSizeType m_src, m_targ, m_n;
    };

} // namespace detail

//=========================================================================
// Adjacency Matrix Traits
template < typename Directed = directedS > class adjacency_matrix_traits
{
    typedef typename Directed::is_directed_t is_directed;

public:
    // The bidirectionalS tag is not allowed with the adjacency_matrix
    // graph type. Instead, use directedS, which also provides the
    // functionality required for a Bidirectional Graph (in_edges,
    // in_degree, etc.).
    BOOST_STATIC_ASSERT(!(is_same< Directed, bidirectionalS >::value));

    typedef typename mpl::if_< is_directed, bidirectional_tag,
        undirected_tag >::type directed_category;

    typedef disallow_parallel_edge_tag edge_parallel_category;

    typedef std::size_t vertex_descriptor;

    typedef detail::matrix_edge_desc_impl< directed_category,
        vertex_descriptor >
        edge_descriptor;
};

struct adjacency_matrix_class_tag
{
};

struct adj_matrix_traversal_tag : public virtual adjacency_matrix_tag,
                                  public virtual vertex_list_graph_tag,
                                  public virtual incidence_graph_tag,
                                  public virtual adjacency_graph_tag,
                                  public virtual edge_list_graph_tag
{
};

//=========================================================================
// Adjacency Matrix Class
template < typename Directed = directedS, typename VertexProperty = no_property,
    typename EdgeProperty = no_property, typename GraphProperty = no_property,
    typename Allocator = std::allocator< bool > >
class adjacency_matrix
{
    typedef adjacency_matrix self;
    typedef adjacency_matrix_traits< Directed > Traits;

public:
    // The bidirectionalS tag is not allowed with the adjacency_matrix
    // graph type. Instead, use directedS, which also provides the
    // functionality required for a Bidirectional Graph (in_edges,
    // in_degree, etc.).
    BOOST_STATIC_ASSERT(!(is_same< Directed, bidirectionalS >::value));

    typedef GraphProperty graph_property_type;
    typedef typename lookup_one_property< GraphProperty, graph_bundle_t >::type
        graph_bundled;

    typedef VertexProperty vertex_property_type;
    typedef
        typename lookup_one_property< VertexProperty, vertex_bundle_t >::type
            vertex_bundled;

    typedef EdgeProperty edge_property_type;
    typedef typename lookup_one_property< EdgeProperty, edge_bundle_t >::type
        edge_bundled;

public: // should be private
    typedef
        typename mpl::if_< typename has_property< edge_property_type >::type,
            std::pair< bool, edge_property_type >, char >::type StoredEdge;
#if defined(BOOST_NO_STD_ALLOCATOR)
    typedef std::vector< StoredEdge > Matrix;
#else
#if defined(BOOST_NO_CXX11_ALLOCATOR)
    typedef typename Allocator::template rebind< StoredEdge >::other Alloc;
#else
    typedef typename std::allocator_traits< Allocator >::template rebind_alloc<
        StoredEdge >
        Alloc;
#endif
    typedef std::vector< StoredEdge, Alloc > Matrix;
#endif
    typedef typename Matrix::iterator MatrixIter;
    typedef typename Matrix::size_type size_type;

public:
    // Graph concept required types
    typedef typename Traits::vertex_descriptor vertex_descriptor;
    typedef typename Traits::edge_descriptor edge_descriptor;
    typedef typename Traits::directed_category directed_category;
    typedef typename Traits::edge_parallel_category edge_parallel_category;
    typedef adj_matrix_traversal_tag traversal_category;

    static vertex_descriptor null_vertex()
    {
        return (std::numeric_limits< vertex_descriptor >::max)();
    }

    // private: if friends worked, these would be private

    typedef detail::dir_adj_matrix_out_edge_iter< vertex_descriptor, MatrixIter,
        size_type, edge_descriptor >
        DirOutEdgeIter;

    typedef detail::undir_adj_matrix_out_edge_iter< vertex_descriptor,
        MatrixIter, size_type, edge_descriptor >
        UnDirOutEdgeIter;

    typedef typename mpl::if_< typename Directed::is_directed_t, DirOutEdgeIter,
        UnDirOutEdgeIter >::type unfiltered_out_edge_iter;

    typedef detail::dir_adj_matrix_in_edge_iter< vertex_descriptor, MatrixIter,
        size_type, edge_descriptor >
        DirInEdgeIter;

    typedef detail::undir_adj_matrix_in_edge_iter< vertex_descriptor,
        MatrixIter, size_type, edge_descriptor >
        UnDirInEdgeIter;

    typedef typename mpl::if_< typename Directed::is_directed_t, DirInEdgeIter,
        UnDirInEdgeIter >::type unfiltered_in_edge_iter;

    typedef detail::adj_matrix_edge_iter< Directed, MatrixIter, size_type,
        edge_descriptor >
        unfiltered_edge_iter;

public:
    // IncidenceGraph concept required types
    typedef filter_iterator< detail::does_edge_exist, unfiltered_out_edge_iter >
        out_edge_iterator;

    typedef size_type degree_size_type;

    // BidirectionalGraph required types
    typedef filter_iterator< detail::does_edge_exist, unfiltered_in_edge_iter >
        in_edge_iterator;

    // AdjacencyGraph required types
    typedef typename adjacency_iterator_generator< self, vertex_descriptor,
        out_edge_iterator >::type adjacency_iterator;

    // VertexListGraph required types
    typedef size_type vertices_size_type;
    typedef integer_range< vertex_descriptor > VertexList;
    typedef typename VertexList::iterator vertex_iterator;

    // EdgeListGraph required types
    typedef size_type edges_size_type;
    typedef filter_iterator< detail::does_edge_exist, unfiltered_edge_iter >
        edge_iterator;

    // PropertyGraph required types
    typedef adjacency_matrix_class_tag graph_tag;

    // Constructor required by MutableGraph
    adjacency_matrix(
        vertices_size_type n_vertices, const GraphProperty& p = GraphProperty())
    : m_matrix(Directed::is_directed ? (n_vertices * n_vertices)
                                     : (n_vertices * (n_vertices + 1) / 2))
    , m_vertex_set(0, n_vertices)
    , m_vertex_properties(n_vertices)
    , m_num_edges(0)
    , m_property(p)
    {
    }

    template < typename EdgeIterator >
    adjacency_matrix(EdgeIterator first, EdgeIterator last,
        vertices_size_type n_vertices, const GraphProperty& p = GraphProperty())
    : m_matrix(Directed::is_directed ? (n_vertices * n_vertices)
                                     : (n_vertices * (n_vertices + 1) / 2))
    , m_vertex_set(0, n_vertices)
    , m_vertex_properties(n_vertices)
    , m_num_edges(0)
    , m_property(p)
    {
        for (; first != last; ++first)
        {
            add_edge(first->first, first->second, *this);
        }
    }

    template < typename EdgeIterator, typename EdgePropertyIterator >
    adjacency_matrix(EdgeIterator first, EdgeIterator last,
        EdgePropertyIterator ep_iter, vertices_size_type n_vertices,
        const GraphProperty& p = GraphProperty())
    : m_matrix(Directed::is_directed ? (n_vertices * n_vertices)
                                     : (n_vertices * (n_vertices + 1) / 2))
    , m_vertex_set(0, n_vertices)
    , m_vertex_properties(n_vertices)
    , m_num_edges(0)
    , m_property(p)
    {
        for (; first != last; ++first, ++ep_iter)
        {
            add_edge(first->first, first->second, *ep_iter, *this);
        }
    }

#ifndef BOOST_GRAPH_NO_BUNDLED_PROPERTIES
    // Directly access a vertex or edge bundle
    vertex_bundled& operator[](vertex_descriptor v)
    {
        return get(vertex_bundle, *this, v);
    }

    const vertex_bundled& operator[](vertex_descriptor v) const
    {
        return get(vertex_bundle, *this, v);
    }

    edge_bundled& operator[](edge_descriptor e)
    {
        return get(edge_bundle, *this, e);
    }

    const edge_bundled& operator[](edge_descriptor e) const
    {
        return get(edge_bundle, *this, e);
    }

    graph_bundled& operator[](graph_bundle_t) { return get_property(*this); }

    const graph_bundled& operator[](graph_bundle_t) const
    {
        return get_property(*this);
    }
#endif

    // private: if friends worked, these would be private

    typename Matrix::const_reference get_edge(
        vertex_descriptor u, vertex_descriptor v) const
    {
        if (Directed::is_directed)
            return m_matrix[u * m_vertex_set.size() + v];
        else
        {
            if (v > u)
                std::swap(u, v);
            return m_matrix[u * (u + 1) / 2 + v];
        }
    }
    typename Matrix::reference get_edge(
        vertex_descriptor u, vertex_descriptor v)
    {
        if (Directed::is_directed)
            return m_matrix[u * m_vertex_set.size() + v];
        else
        {
            if (v > u)
                std::swap(u, v);
            return m_matrix[u * (u + 1) / 2 + v];
        }
    }

    Matrix m_matrix;
    VertexList m_vertex_set;
    std::vector< vertex_property_type > m_vertex_properties;
    size_type m_num_edges;
    graph_property_type m_property;
};

//=========================================================================
// Functions required by the AdjacencyMatrix concept

template < typename D, typename VP, typename EP, typename GP, typename A >
std::pair< typename adjacency_matrix< D, VP, EP, GP, A >::edge_descriptor,
    bool >
edge(typename adjacency_matrix< D, VP, EP, GP, A >::vertex_descriptor u,
    typename adjacency_matrix< D, VP, EP, GP, A >::vertex_descriptor v,
    const adjacency_matrix< D, VP, EP, GP, A >& g)
{
    bool exists = detail::get_edge_exists(g.get_edge(u, v), 0);
    typename adjacency_matrix< D, VP, EP, GP, A >::edge_descriptor e(
        exists, u, v, &detail::get_edge_property(g.get_edge(u, v)));
    return std::make_pair(e, exists);
}

//=========================================================================
// Functions required by the IncidenceGraph concept

// O(1)
template < typename VP, typename EP, typename GP, typename A >
std::pair<
    typename adjacency_matrix< directedS, VP, EP, GP, A >::out_edge_iterator,
    typename adjacency_matrix< directedS, VP, EP, GP, A >::out_edge_iterator >
out_edges(
    typename adjacency_matrix< directedS, VP, EP, GP, A >::vertex_descriptor u,
    const adjacency_matrix< directedS, VP, EP, GP, A >& g_)
{
    typedef adjacency_matrix< directedS, VP, EP, GP, A > Graph;
    Graph& g = const_cast< Graph& >(g_);
    typename Graph::vertices_size_type offset = u * g.m_vertex_set.size();
    typename Graph::MatrixIter f = g.m_matrix.begin() + offset;
    typename Graph::MatrixIter l = f + g.m_vertex_set.size();
    typename Graph::unfiltered_out_edge_iter first(f, u, g.m_vertex_set.size()),
        last(l, u, g.m_vertex_set.size());
    detail::does_edge_exist pred;
    typedef typename Graph::out_edge_iterator out_edge_iterator;
    return std::make_pair(out_edge_iterator(pred, first, last),
        out_edge_iterator(pred, last, last));
}

// O(1)
template < typename VP, typename EP, typename GP, typename A >
std::pair<
    typename adjacency_matrix< undirectedS, VP, EP, GP, A >::out_edge_iterator,
    typename adjacency_matrix< undirectedS, VP, EP, GP, A >::out_edge_iterator >
out_edges(
    typename adjacency_matrix< undirectedS, VP, EP, GP, A >::vertex_descriptor
        u,
    const adjacency_matrix< undirectedS, VP, EP, GP, A >& g_)
{
    typedef adjacency_matrix< undirectedS, VP, EP, GP, A > Graph;
    Graph& g = const_cast< Graph& >(g_);
    typename Graph::vertices_size_type offset = u * (u + 1) / 2;
    typename Graph::MatrixIter f = g.m_matrix.begin() + offset;
    typename Graph::MatrixIter l = g.m_matrix.end();

    typename Graph::unfiltered_out_edge_iter first(f, u, g.m_vertex_set.size()),
        last(l, u, g.m_vertex_set.size());

    detail::does_edge_exist pred;
    typedef typename Graph::out_edge_iterator out_edge_iterator;
    return std::make_pair(out_edge_iterator(pred, first, last),
        out_edge_iterator(pred, last, last));
}

// O(N)
template < typename D, typename VP, typename EP, typename GP, typename A >
typename adjacency_matrix< D, VP, EP, GP, A >::degree_size_type out_degree(
    typename adjacency_matrix< D, VP, EP, GP, A >::vertex_descriptor u,
    const adjacency_matrix< D, VP, EP, GP, A >& g)
{
    typename adjacency_matrix< D, VP, EP, GP, A >::degree_size_type n = 0;
    typename adjacency_matrix< D, VP, EP, GP, A >::out_edge_iterator f, l;
    for (boost::tie(f, l) = out_edges(u, g); f != l; ++f)
        ++n;
    return n;
}

// O(1)
template < typename D, typename VP, typename EP, typename GP, typename A,
    typename Dir, typename Vertex >
typename adjacency_matrix< D, VP, EP, GP, A >::vertex_descriptor source(
    const detail::matrix_edge_desc_impl< Dir, Vertex >& e,
    const adjacency_matrix< D, VP, EP, GP, A >&)
{
    return e.m_source;
}

// O(1)
template < typename D, typename VP, typename EP, typename GP, typename A,
    typename Dir, typename Vertex >
typename adjacency_matrix< D, VP, EP, GP, A >::vertex_descriptor target(
    const detail::matrix_edge_desc_impl< Dir, Vertex >& e,
    const adjacency_matrix< D, VP, EP, GP, A >&)
{
    return e.m_target;
}

//=========================================================================
// Functions required by the BidirectionalGraph concept

// O(1)
template < typename VP, typename EP, typename GP, typename A >
std::pair<
    typename adjacency_matrix< directedS, VP, EP, GP, A >::in_edge_iterator,
    typename adjacency_matrix< directedS, VP, EP, GP, A >::in_edge_iterator >
in_edges(
    typename adjacency_matrix< directedS, VP, EP, GP, A >::vertex_descriptor u,
    const adjacency_matrix< directedS, VP, EP, GP, A >& g_)
{
    typedef adjacency_matrix< directedS, VP, EP, GP, A > Graph;
    Graph& g = const_cast< Graph& >(g_);
    typename Graph::MatrixIter f = g.m_matrix.begin() + u;
    typename Graph::MatrixIter l = g.m_matrix.end();
    typename Graph::unfiltered_in_edge_iter first(
        f, l, u, g.m_vertex_set.size()),
        last(l, l, u, g.m_vertex_set.size());
    detail::does_edge_exist pred;
    typedef typename Graph::in_edge_iterator in_edge_iterator;
    return std::make_pair(in_edge_iterator(pred, first, last),
        in_edge_iterator(pred, last, last));
}

// O(1)
template < typename VP, typename EP, typename GP, typename A >
std::pair<
    typename adjacency_matrix< undirectedS, VP, EP, GP, A >::in_edge_iterator,
    typename adjacency_matrix< undirectedS, VP, EP, GP, A >::in_edge_iterator >
in_edges(
    typename adjacency_matrix< undirectedS, VP, EP, GP, A >::vertex_descriptor
        u,
    const adjacency_matrix< undirectedS, VP, EP, GP, A >& g_)
{
    typedef adjacency_matrix< undirectedS, VP, EP, GP, A > Graph;
    Graph& g = const_cast< Graph& >(g_);
    typename Graph::vertices_size_type offset = u * (u + 1) / 2;
    typename Graph::MatrixIter f = g.m_matrix.begin() + offset;
    typename Graph::MatrixIter l = g.m_matrix.end();

    typename Graph::unfiltered_in_edge_iter first(f, u, g.m_vertex_set.size()),
        last(l, u, g.m_vertex_set.size());

    detail::does_edge_exist pred;
    typedef typename Graph::in_edge_iterator in_edge_iterator;
    return std::make_pair(in_edge_iterator(pred, first, last),
        in_edge_iterator(pred, last, last));
}

// O(N)
template < typename D, typename VP, typename EP, typename GP, typename A >
typename adjacency_matrix< D, VP, EP, GP, A >::degree_size_type in_degree(
    typename adjacency_matrix< D, VP, EP, GP, A >::vertex_descriptor u,
    const adjacency_matrix< D, VP, EP, GP, A >& g)
{
    typename adjacency_matrix< D, VP, EP, GP, A >::degree_size_type n = 0;
    typename adjacency_matrix< D, VP, EP, GP, A >::in_edge_iterator f, l;
    for (boost::tie(f, l) = in_edges(u, g); f != l; ++f)
        ++n;
    return n;
}

//=========================================================================
// Functions required by the AdjacencyGraph concept

template < typename D, typename VP, typename EP, typename GP, typename A >
std::pair< typename adjacency_matrix< D, VP, EP, GP, A >::adjacency_iterator,
    typename adjacency_matrix< D, VP, EP, GP, A >::adjacency_iterator >
adjacent_vertices(
    typename adjacency_matrix< D, VP, EP, GP, A >::vertex_descriptor u,
    const adjacency_matrix< D, VP, EP, GP, A >& g_)
{
    typedef adjacency_matrix< D, VP, EP, GP, A > Graph;
    const Graph& cg = static_cast< const Graph& >(g_);
    Graph& g = const_cast< Graph& >(cg);
    typedef typename Graph::adjacency_iterator adjacency_iterator;
    typename Graph::out_edge_iterator first, last;
    boost::tie(first, last) = out_edges(u, g);
    return std::make_pair(
        adjacency_iterator(first, &g), adjacency_iterator(last, &g));
}

//=========================================================================
// Functions required by the VertexListGraph concept

template < typename D, typename VP, typename EP, typename GP, typename A >
std::pair< typename adjacency_matrix< D, VP, EP, GP, A >::vertex_iterator,
    typename adjacency_matrix< D, VP, EP, GP, A >::vertex_iterator >
vertices(const adjacency_matrix< D, VP, EP, GP, A >& g_)
{
    typedef adjacency_matrix< D, VP, EP, GP, A > Graph;
    Graph& g = const_cast< Graph& >(g_);
    return std::make_pair(g.m_vertex_set.begin(), g.m_vertex_set.end());
}

template < typename D, typename VP, typename EP, typename GP, typename A >
typename adjacency_matrix< D, VP, EP, GP, A >::vertices_size_type num_vertices(
    const adjacency_matrix< D, VP, EP, GP, A >& g)
{
    return g.m_vertex_set.size();
}

//=========================================================================
// Functions required by the EdgeListGraph concept

template < typename D, typename VP, typename EP, typename GP, typename A >
std::pair< typename adjacency_matrix< D, VP, EP, GP, A >::edge_iterator,
    typename adjacency_matrix< D, VP, EP, GP, A >::edge_iterator >
edges(const adjacency_matrix< D, VP, EP, GP, A >& g_)
{
    typedef adjacency_matrix< D, VP, EP, GP, A > Graph;
    Graph& g = const_cast< Graph& >(g_);

    typename Graph::unfiltered_edge_iter first(
        g.m_matrix.begin(), g.m_matrix.begin(), g.m_vertex_set.size()),
        last(g.m_matrix.end(), g.m_matrix.begin(), g.m_vertex_set.size());
    detail::does_edge_exist pred;
    typedef typename Graph::edge_iterator edge_iterator;
    return std::make_pair(
        edge_iterator(pred, first, last), edge_iterator(pred, last, last));
}

// O(1)
template < typename D, typename VP, typename EP, typename GP, typename A >
typename adjacency_matrix< D, VP, EP, GP, A >::edges_size_type num_edges(
    const adjacency_matrix< D, VP, EP, GP, A >& g)
{
    return g.m_num_edges;
}

//=========================================================================
// Functions required by the MutableGraph concept

// O(1)
template < typename D, typename VP, typename EP, typename GP, typename A,
    typename EP2 >
std::pair< typename adjacency_matrix< D, VP, EP, GP, A >::edge_descriptor,
    bool >
add_edge(typename adjacency_matrix< D, VP, EP, GP, A >::vertex_descriptor u,
    typename adjacency_matrix< D, VP, EP, GP, A >::vertex_descriptor v,
    const EP2& ep, adjacency_matrix< D, VP, EP, GP, A >& g)
{
    typedef typename adjacency_matrix< D, VP, EP, GP, A >::edge_descriptor
        edge_descriptor;
    if (detail::get_edge_exists(g.get_edge(u, v), 0) == false)
    {
        ++(g.m_num_edges);
        detail::set_edge_property(g.get_edge(u, v), EP(ep), 0);
        detail::set_edge_exists(g.get_edge(u, v), true, 0);
        return std::make_pair(edge_descriptor(true, u, v,
                                  &detail::get_edge_property(g.get_edge(u, v))),
            true);
    }
    else
        return std::make_pair(edge_descriptor(true, u, v,
                                  &detail::get_edge_property(g.get_edge(u, v))),
            false);
}
// O(1)
template < typename D, typename VP, typename EP, typename GP, typename A >
std::pair< typename adjacency_matrix< D, VP, EP, GP, A >::edge_descriptor,
    bool >
add_edge(typename adjacency_matrix< D, VP, EP, GP, A >::vertex_descriptor u,
    typename adjacency_matrix< D, VP, EP, GP, A >::vertex_descriptor v,
    adjacency_matrix< D, VP, EP, GP, A >& g)
{
    EP ep;
    return add_edge(u, v, ep, g);
}

// O(1)
template < typename D, typename VP, typename EP, typename GP, typename A >
void remove_edge(
    typename adjacency_matrix< D, VP, EP, GP, A >::vertex_descriptor u,
    typename adjacency_matrix< D, VP, EP, GP, A >::vertex_descriptor v,
    adjacency_matrix< D, VP, EP, GP, A >& g)
{
    // Don'remove the edge unless it already exists.
    if (detail::get_edge_exists(g.get_edge(u, v), 0))
    {
        --(g.m_num_edges);
        detail::set_edge_exists(g.get_edge(u, v), false, 0);
    }
}

// O(1)
template < typename D, typename VP, typename EP, typename GP, typename A >
void remove_edge(
    typename adjacency_matrix< D, VP, EP, GP, A >::edge_descriptor e,
    adjacency_matrix< D, VP, EP, GP, A >& g)
{
    remove_edge(source(e, g), target(e, g), g);
}

template < typename D, typename VP, typename EP, typename GP, typename A >
inline typename adjacency_matrix< D, VP, EP, GP, A >::vertex_descriptor
add_vertex(adjacency_matrix< D, VP, EP, GP, A >& g)
{
    // UNDER CONSTRUCTION
    BOOST_ASSERT(false);
    return *vertices(g).first;
}

template < typename D, typename VP, typename EP, typename GP, typename A,
    typename VP2 >
inline typename adjacency_matrix< D, VP, EP, GP, A >::vertex_descriptor
add_vertex(const VP2& /*vp*/, adjacency_matrix< D, VP, EP, GP, A >& g)
{
    // UNDER CONSTRUCTION
    BOOST_ASSERT(false);
    return *vertices(g).first;
}

template < typename D, typename VP, typename EP, typename GP, typename A >
inline void remove_vertex(
    typename adjacency_matrix< D, VP, EP, GP, A >::vertex_descriptor /*u*/,
    adjacency_matrix< D, VP, EP, GP, A >& /*g*/)
{
    // UNDER CONSTRUCTION
    BOOST_ASSERT(false);
}

// O(V)
template < typename VP, typename EP, typename GP, typename A >
void clear_vertex(
    typename adjacency_matrix< directedS, VP, EP, GP, A >::vertex_descriptor u,
    adjacency_matrix< directedS, VP, EP, GP, A >& g)
{
    typename adjacency_matrix< directedS, VP, EP, GP, A >::vertex_iterator vi,
        vi_end;
    for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
        remove_edge(u, *vi, g);
    for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
        remove_edge(*vi, u, g);
}

// O(V)
template < typename VP, typename EP, typename GP, typename A >
void clear_vertex(
    typename adjacency_matrix< undirectedS, VP, EP, GP, A >::vertex_descriptor
        u,
    adjacency_matrix< undirectedS, VP, EP, GP, A >& g)
{
    typename adjacency_matrix< undirectedS, VP, EP, GP, A >::vertex_iterator vi,
        vi_end;
    for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
        remove_edge(u, *vi, g);
}

//=========================================================================
// Functions required by the PropertyGraph concept

template < typename D, typename VP, typename EP, typename GP, typename A,
    typename Prop, typename Kind >
struct adj_mat_pm_helper;

template < typename D, typename VP, typename EP, typename GP, typename A,
    typename Prop >
struct adj_mat_pm_helper< D, VP, EP, GP, A, Prop, vertex_property_tag >
{
    typedef typename graph_traits<
        adjacency_matrix< D, VP, EP, GP, A > >::vertex_descriptor arg_type;
    typedef typed_identity_property_map< arg_type > vi_map_type;
    typedef iterator_property_map< typename std::vector< VP >::iterator,
        vi_map_type >
        all_map_type;
    typedef iterator_property_map< typename std::vector< VP >::const_iterator,
        vi_map_type >
        all_map_const_type;
    typedef transform_value_property_map<
        detail::lookup_one_property_f< VP, Prop >, all_map_type >
        type;
    typedef transform_value_property_map<
        detail::lookup_one_property_f< const VP, Prop >, all_map_const_type >
        const_type;
    typedef typename property_traits< type >::reference single_nonconst_type;
    typedef typename property_traits< const_type >::reference single_const_type;

    static type get_nonconst(adjacency_matrix< D, VP, EP, GP, A >& g, Prop prop)
    {
        return type(
            prop, all_map_type(g.m_vertex_properties.begin(), vi_map_type()));
    }

    static const_type get_const(
        const adjacency_matrix< D, VP, EP, GP, A >& g, Prop prop)
    {
        return const_type(prop,
            all_map_const_type(g.m_vertex_properties.begin(), vi_map_type()));
    }

    static single_nonconst_type get_nonconst_one(
        adjacency_matrix< D, VP, EP, GP, A >& g, Prop prop, arg_type v)
    {
        return lookup_one_property< VP, Prop >::lookup(
            g.m_vertex_properties[v], prop);
    }

    static single_const_type get_const_one(
        const adjacency_matrix< D, VP, EP, GP, A >& g, Prop prop, arg_type v)
    {
        return lookup_one_property< const VP, Prop >::lookup(
            g.m_vertex_properties[v], prop);
    }
};

template < typename D, typename VP, typename EP, typename GP, typename A,
    typename Tag >
struct adj_mat_pm_helper< D, VP, EP, GP, A, Tag, edge_property_tag >
{
    typedef typename graph_traits<
        adjacency_matrix< D, VP, EP, GP, A > >::edge_descriptor edge_descriptor;

    template < typename IsConst > struct lookup_property_from_edge
    {
        Tag tag;
        lookup_property_from_edge(Tag tag) : tag(tag) {}
        typedef typename boost::mpl::if_< IsConst, const EP, EP >::type
            ep_type_nonref;
        typedef ep_type_nonref& ep_type;
        typedef typename lookup_one_property< ep_type_nonref, Tag >::type&
            result_type;
        result_type operator()(edge_descriptor e) const
        {
            return lookup_one_property< ep_type_nonref, Tag >::lookup(
                *static_cast< ep_type_nonref* >(e.get_property()), tag);
        }
    };

    typedef function_property_map<
        lookup_property_from_edge< boost::mpl::false_ >,
        typename graph_traits<
            adjacency_matrix< D, VP, EP, GP, A > >::edge_descriptor >
        type;
    typedef function_property_map<
        lookup_property_from_edge< boost::mpl::true_ >,
        typename graph_traits<
            adjacency_matrix< D, VP, EP, GP, A > >::edge_descriptor >
        const_type;
    typedef edge_descriptor arg_type;
    typedef
        typename lookup_property_from_edge< boost::mpl::false_ >::result_type
            single_nonconst_type;
    typedef typename lookup_property_from_edge< boost::mpl::true_ >::result_type
        single_const_type;

    static type get_nonconst(adjacency_matrix< D, VP, EP, GP, A >& g, Tag tag)
    {
        return type(tag);
    }

    static const_type get_const(
        const adjacency_matrix< D, VP, EP, GP, A >& g, Tag tag)
    {
        return const_type(tag);
    }

    static single_nonconst_type get_nonconst_one(
        adjacency_matrix< D, VP, EP, GP, A >& g, Tag tag, edge_descriptor e)
    {
        return lookup_one_property< EP, Tag >::lookup(
            *static_cast< EP* >(e.get_property()), tag);
    }

    static single_const_type get_const_one(
        const adjacency_matrix< D, VP, EP, GP, A >& g, Tag tag,
        edge_descriptor e)
    {
        return lookup_one_property< const EP, Tag >::lookup(
            *static_cast< const EP* >(e.get_property()), tag);
    }
};

template < typename D, typename VP, typename EP, typename GP, typename A,
    typename Tag >
struct property_map< adjacency_matrix< D, VP, EP, GP, A >, Tag >
: adj_mat_pm_helper< D, VP, EP, GP, A, Tag,
      typename detail::property_kind_from_graph<
          adjacency_matrix< D, VP, EP, GP, A >, Tag >::type >
{
};

template < typename D, typename VP, typename EP, typename GP, typename A,
    typename Tag >
typename property_map< adjacency_matrix< D, VP, EP, GP, A >, Tag >::type get(
    Tag tag, adjacency_matrix< D, VP, EP, GP, A >& g)
{
    return property_map< adjacency_matrix< D, VP, EP, GP, A >,
        Tag >::get_nonconst(g, tag);
}

template < typename D, typename VP, typename EP, typename GP, typename A,
    typename Tag >
typename property_map< adjacency_matrix< D, VP, EP, GP, A >, Tag >::const_type
get(Tag tag, const adjacency_matrix< D, VP, EP, GP, A >& g)
{
    return property_map< adjacency_matrix< D, VP, EP, GP, A >, Tag >::get_const(
        g, tag);
}

template < typename D, typename VP, typename EP, typename GP, typename A,
    typename Tag >
typename property_map< adjacency_matrix< D, VP, EP, GP, A >,
    Tag >::single_nonconst_type
get(Tag tag, adjacency_matrix< D, VP, EP, GP, A >& g,
    typename property_map< adjacency_matrix< D, VP, EP, GP, A >, Tag >::arg_type
        a)
{
    return property_map< adjacency_matrix< D, VP, EP, GP, A >,
        Tag >::get_nonconst_one(g, tag, a);
}

template < typename D, typename VP, typename EP, typename GP, typename A,
    typename Tag >
typename property_map< adjacency_matrix< D, VP, EP, GP, A >,
    Tag >::single_const_type
get(Tag tag, const adjacency_matrix< D, VP, EP, GP, A >& g,
    typename property_map< adjacency_matrix< D, VP, EP, GP, A >, Tag >::arg_type
        a)
{
    return property_map< adjacency_matrix< D, VP, EP, GP, A >,
        Tag >::get_const_one(g, tag, a);
}

template < typename D, typename VP, typename EP, typename GP, typename A,
    typename Tag >
void put(Tag tag, adjacency_matrix< D, VP, EP, GP, A >& g,
    typename property_map< adjacency_matrix< D, VP, EP, GP, A >, Tag >::arg_type
        a,
    typename property_map< adjacency_matrix< D, VP, EP, GP, A >,
        Tag >::single_const_type val)
{
    property_map< adjacency_matrix< D, VP, EP, GP, A >, Tag >::get_nonconst_one(
        g, tag, a)
        = val;
}

// O(1)
template < typename D, typename VP, typename EP, typename GP, typename A,
    typename Tag, typename Value >
inline void set_property(
    adjacency_matrix< D, VP, EP, GP, A >& g, Tag tag, const Value& value)
{
    get_property_value(g.m_property, tag) = value;
}

template < typename D, typename VP, typename EP, typename GP, typename A,
    typename Tag >
inline
    typename graph_property< adjacency_matrix< D, VP, EP, GP, A >, Tag >::type&
    get_property(adjacency_matrix< D, VP, EP, GP, A >& g, Tag tag)
{
    return get_property_value(g.m_property, tag);
}

template < typename D, typename VP, typename EP, typename GP, typename A,
    typename Tag >
inline const typename graph_property< adjacency_matrix< D, VP, EP, GP, A >,
    Tag >::type&
get_property(const adjacency_matrix< D, VP, EP, GP, A >& g, Tag tag)
{
    return get_property_value(g.m_property, tag);
}

//=========================================================================
// Vertex Property Map

template < typename D, typename VP, typename EP, typename GP, typename A >
struct property_map< adjacency_matrix< D, VP, EP, GP, A >, vertex_index_t >
{
    typedef
        typename adjacency_matrix< D, VP, EP, GP, A >::vertex_descriptor Vertex;
    typedef typed_identity_property_map< Vertex > type;
    typedef type const_type;
};

template < typename D, typename VP, typename EP, typename GP, typename A >
typename property_map< adjacency_matrix< D, VP, EP, GP, A >,
    vertex_index_t >::const_type
get(vertex_index_t, adjacency_matrix< D, VP, EP, GP, A >&)
{
    return typename property_map< adjacency_matrix< D, VP, EP, GP, A >,
        vertex_index_t >::const_type();
}

template < typename D, typename VP, typename EP, typename GP, typename A >
typename adjacency_matrix< D, VP, EP, GP, A >::vertex_descriptor get(
    vertex_index_t, adjacency_matrix< D, VP, EP, GP, A >&,
    typename adjacency_matrix< D, VP, EP, GP, A >::vertex_descriptor v)
{
    return v;
}

template < typename D, typename VP, typename EP, typename GP, typename A >
typename property_map< adjacency_matrix< D, VP, EP, GP, A >,
    vertex_index_t >::const_type
get(vertex_index_t, const adjacency_matrix< D, VP, EP, GP, A >&)
{
    return typename property_map< adjacency_matrix< D, VP, EP, GP, A >,
        vertex_index_t >::const_type();
}

template < typename D, typename VP, typename EP, typename GP, typename A >
typename adjacency_matrix< D, VP, EP, GP, A >::vertex_descriptor get(
    vertex_index_t, const adjacency_matrix< D, VP, EP, GP, A >&,
    typename adjacency_matrix< D, VP, EP, GP, A >::vertex_descriptor v)
{
    return v;
}

//=========================================================================
// Other Functions

template < typename D, typename VP, typename EP, typename GP, typename A >
typename adjacency_matrix< D, VP, EP, GP, A >::vertex_descriptor vertex(
    typename adjacency_matrix< D, VP, EP, GP, A >::vertices_size_type n,
    const adjacency_matrix< D, VP, EP, GP, A >&)
{
    return n;
}

template < typename D, typename VP, typename EP, typename GP, typename A >
struct graph_mutability_traits< adjacency_matrix< D, VP, EP, GP, A > >
{
    typedef mutable_edge_property_graph_tag category;
};

} // namespace boost

#endif // BOOST_ADJACENCY_MATRIX_HPP

/* adjacency_matrix.hpp
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
*/