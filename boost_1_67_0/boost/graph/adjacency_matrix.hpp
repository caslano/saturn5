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
gXVRn55GsiJcPWU9tCEcjlSGaECiexXZMGAiB/b7EvF+f6+ViqxIiW+1Uw+k71SPKy5nJG3vee/kZe/CXeE7Qcm2LzynteXEKRKpnGQNSWFVDLN51VZd4Xs7Ph930hOqybr5uy5Y6xLua8EtUOGdpbRy1l3FsiyXdHRHbE6lk2rRZ8RxNvyMDeDVNpyW3wok6HmUCUTBeDYqAH1naW7hkYHZDIANTBQT6XX4YPOlSRGfgg1CtjFFrQx/dRc1DSgwZdO9UY3xzxreJoF3l4B4iPa/6hEmI+cnQjYUVI1M2vN3Efwc+OAi+4vtTEzXFqyWJ3OvdNKM3M/J4X/1/TA1z9onOdafjXZlNv0TI0Tct5dZ1A+Yz6N++r5qeOiVJcLgnfuTdA6UpPYiQG5v0ntGmiFklvdcB/HeejJPzSn2as1xDxI8/gdmZRqiMWcFjAkGKyWGxpNWFmxKtRwaXTVcr01ioHMmSHsLgMuZu6ruLNdwl9S8ZkFx8XZ8ZRuBS1kcRqEAv/r9nqSR9vETNuqKQ/3wxbDliUWh2Cmum1nuw8yk9AeQsjvJ3mfONQCckNPZXPWpWX4q1KzN/DII4bWq0KlQH1bZRC+BZsnm9BHpZ49hqOXHzq6QHSsm/347jrHFa09i18+J5zArGJCqkcFQrPwMQu7ALMLvq2at7k8YfizWKwKricQLbKej2lt/s8h3Qeb30mcwBE8G++FnEUchrZ7+HQhxtsf1j1ejfmODLPcuk8ytxd8ghtpyzJ4SZHys8TJgLUFJfQ46+1hKTuH4djKF0k7Jeox+brupD4RSym60hqV37wtS+A0Mbc2fIr2sCNPX1uj6/AGp4pMsgKxaI+878Y7xQYIqllfP/TKW5XTucP7fMgYuW4a7mzqGpvTHz5shDhnzSZZxhfyqgq5dfrNF/u8mSdIFu6cHzL/HhV1Xkh40jccmpvK1WNSj/D5SEHm/xeV7WWmELAkjJikdx1YUqiUoitlcLpm1Wum3L6jTHFGj2Sz8HFD57kORYygJfY30k5pOScnT4Nyvr3CDijXMWPcuIkwy95Fa9EFKModE5j4Tvurbwjf7dbH6n7o1tQevOn/WgCOX4oyvFEyjT7uJmHbkx3rpUE5rECq/fl5AxPaXWOSaQTXl+WB6ZjdWoza0ZynIROqwRax2FfA1d4uQbCH0oH14pjikrVosXZCIWY7lxC88T77/0uaVISEdrymaaY6XmE18J3aCeMVOiFV+HZB+1uv8IT0tKbgj3b0M7vhDTYi+f3N5Nq5NY8dqHXfWyAOLzr/loRFhngHvgiDMd+5E967MiJ+KndWgTQNTRMRUj4AlakyRswoK5Qy1kiXAeuafRKpEZBl1Qq/etxyPo+/ad4J8CAB7+ddNxM80zas/tbvOzR959WxMz6nsf8zYQhZWvH48ICw3XUPMSz2NAj7gqwsvOBORw2N2iXYZR4VESi2AmbsniSZDz7Ul+w8ENGcLDn2LYDSGNm0faHEE1BBJRv/c0DgyCiaOlawrq+dC85uz3EysErjl4I/TrAUe6UbmompB8HbCFI5OfpfDBz67RSVdUkEecn9BKs3WpYWpejbwzaNaXh7PcFexS8MAToS/3OwUXvIOtmfjNTrYU9Yj9M6vPSdpTG7BZR+xHxQnG61seWaqKggxgZpVRYD5gV3LTX6krAUKUUZDi9hHWSrJZcWT0RlFm40J5YBolUqmsiH237pp6oUCa4Sn9N546hnKMaxn5eNc8XTZUAbZL3yMtbV/k6T6ZRIIVrL7Qt/6D7HLJP1pbW5v3t+RX+DAgsFDIMXAxCDEwMUg+8H6Id7BQiFDYcXBxKHEIcRhxMHFocUhxWEHwAagBiAGYAbAB6AHIAdgKcAooCggKGAowCmgKSApYIvBiqGKIYphisGLoYshi2FNwUyhTCFMYUzBTaFNIU1h98Be4Ifgh6CHkIcghxCHYIdQqcCo4KigqJCoIKgQqGCoUKjAqeCpoKmQqSCpEKlgqVBLwUrhSqFKkUohShFKYUpRSsFL4UuhS5FLIUsRS2FLUc3BzOHuEMfgxvDGoMawTngA+AA+ADSAGoAN4AIgA5gAxAAhACSAEoAJ4AAgAhgAhAABACyABoAL4AGgAlgAInM0192fgWBgb8GrwTTGIWCzfRDghsHQEF0QiFDekDhw1yiMaDuQOmR9NPWiwSxfAPgFwMjARMjA4OpFwVS/JsZfk74QaAhRMESoYCgcODBoRjQwAh0yMKQvoPMFRL76+sC/QlgcuGCwrxD9K8T4Cs2/QtqvbdWv7cIvIPo/AP8CmF8A5wvYfwHeL+D8BXa+QN8XEP1qCEb7AuhfwPQLUH0B2S8A+AJk/wPwL4DxBbC/gO0X4PwC1l9g7gsUfoG+/xv+vwHzC1h+AcYvoPMF6kPA3kJe2qN0NjFwT3WOm8brtuT/QUU+i9bimxWO5kAwvfKXTQwvsj+4Dnh9CqO68JGxk4g2vuXW/VNlFJbWe0XpjXfUT0caBmbfDYNX0nnYRE/nFHmkPrXq0gs7CVEOzNOo9QjFNkuL05aLWqJ8q2OI9easP4/xv2DR2QpS82c8talLeDa1TPcc/Yh8j1kU8rw1KwuyGwx1kH3pS6E7tahlV8K2DI/V9B9G95srYwFCX0gwRlV35H2fiXbK2PJWHByiOvFVzQI5zczkmjzWBSbdCXEDRGmp0OlqAumCx8u58DuR4l+ITl2Nt6GWeJ5QhZqVHC3STKmb1aBxCQ6jZ919DCxVcP+QjzdMGL4rnCp2keiKj+Ci3e7BgQMTgwu+mSLdtIAG9SfUzWsQchKDtO9IOIBxmlnYDoFVlU7yrKfeqLbb8W/hful9N7TnAp9L1KIfNe3ipJtY5PIntLh27mkx1Njc0NL7IyZ/qSYLuM7EeqsdsWW1ctIIUwuOzdPpcHd37abZ3Q79vZzI9i3yJLqrVIUcsvWbBLXbRutQlbA+qxvYhwj1Org2lxu4Cqe14wLUfBTWnLP70JCTrSY+MRNA4BhpovKcnkK6YKxyKq5oobLFAaK+I0MuDizOazZE6gXESYqUAo9hwaV2geRgSBN8to3RFMV6Lm86+jvIW/FFzI7fdu+MmwM4I0GAD6mjjB9ELPuiQm2Ki1NNtp5ISMC2I/aVIj+rC8ia0oYju2yqdl6Jgk2Bd42GKK72l3q7E++0eqPGxvLk/TwrmVcgwT/2Un5cf864x0Z5y6AkNqtl9a7lJCeiExGsl/wxR99FXzSqx16gqV1Cy9JBS1WzUWMN6CjcW/tk7h5+jKZNOdfwXwVq+nDrfEOUpj5VsqZOZolHveU5TZqhkK2AnrPzGYsxXdXBWllgkQ8f+CkxTjfuAkt5fprhYSAvdSi33IxcmHZurswBi4QdyyxXteKoFD45iqtdJC4V3odFbJiTmWFOmtBJh5or9ZvbJezPi3njR8EXfz7+x/bqmYidX3ZwV7VgBvd2nriWyDRidWp2pn9PaYRsh+rUShX8EvY09yjpElXDgnrV5IpsO5bsRW37MQ0ufxT5ENF7LDjl99hzOCsldQgXB4UK9jW8KF8ulKtypRwf/AW9FqBIUvZ4ivclZ9siGwulZ9hfu83UianpPsiJbdBAbLytnkdpScFfdbejmJ0rSpRZ7SGRXYq0/ys1Qz/iGWOdopLz+9PAKa/ZHD0OS/tZtQ/TWJYPqLaxyR7xN+Nqc7YAj4aOipwr/0jDVzdJzaIIufbdj45soGHVTZl6SZJypWEkmbB3s5UaZcgzPPx+TyKkwOJYvrOkBMZ7Vk5Q/DKMTQz5L0HfojEh6+B4+GAdHNShhY1HuUOgjFMAy/58u3Vjeh/XcB9nzzcJ8CAGT0KHyl4VLF5SEblFcxvoV1qHHRU5ae752YLZqNhAFMSttKGzQ0XUaff9gAT01q1yCaFXXn4DA5/KW5VO0vQSmsNvfSY9edLCi2TCyd+ikh1Olwf9vNmZ71VA2XQjKf2dq688Aa+NOO1XsmX+gfIhclTSTe3djYcj25tx8anCwZAXfSLbO8F13/xpXYh+XLHTxqGPG7d+jM7ZJnT7jqO2lji/fVHkyin4bmXbN9BvrZbV24OmUsZEsIsipl5N1L9SsrnPc0dYaUn0Bl1AvsFHF0c16RC0pxPa67uG4qeo5M3zRod5ThjKDQ0U+SuqHRMnPvkw1U8OP8D0ZnUqTGY48r5HMCWbvSKGUMhl3cY8M3B0uYjQxCmy607ORYE6RDbLA886doJVrpWzvRzj1yOoWPYCpfd4H7ibkmZ+r9Ssezo5lJsCDfNPuWpyoKzi00hRRiRq63b1ceqbiM8qQk4Z8JbnUlClgjnGm4wERJ0b0N0I9mT2wup6PN6VoXFFGr4ZeRJqIQsKb+Ou1c5MKH8N+sDYDUcpL3LKlzO+Rww8Qhgx6okzLHLf6GNy9STRW2JJzX/5/id7BW9BtdJH9Z7IaV7wsg6coW4EV4Uv6kKMldvRHT8QkUCfaxZ/gn5XAbOmtzgR1/ZwOQHXAms7Q3IQe12YJcKzEntH/9Syj7ekb45nyR2Vlx85pIkleIkLHAwVbxDwgNL1utwXIwFE1a/rkARfVZOAJ5FSueNyucL7Hf7p3kErExr+tIerLn5bAByZ2uKrXXHitEtMJgpQvgyKXozDO+W78X0J3lR+d/PKGCVH4Z3HOmgYCtwILGDYUWcBa7v5kG34Rx8ai0hjF1awqNvRG8lVVY7gRBRnNKZN8pgJQ40fgmUc15Y4JjLX4rMhqw++rkJXPKljqZ47sFjL+5Cf8/k3y5zfk7/EtswHdiVUvHv5/y/e1O15qdjS6HUhgyN8htvOM1csWfDShPhKj+s30BRbJvMmc7XfQSU/nty9T+IojXPe5TBt2s2iPyaExaE/Jm52krUHliq6hiGK/pKB89/mJ2nJOxTXSLB6Y3qEljxgafL3oipjYAENb3jyM1ALcCltP1vwLKKNIKnPteZCbbiWDNMWwRL7+GN0Oy+T/fe3V032ErxCKpjOUSRJozpxN9o+44H0dR6YP9jsO2MwLaOnWBzOPswjyrXjHM29YyC7cXaXn6oErtRaMDfxQnMj3W2GfJh/z68Oxs8/PhZTt/4R9n4DAQi9WSFzQ/I3rQUzRQmv5WrHDDQF54x8xS40diQk7hC3X9I5nh+fR0aAi6DjgbWX/biFX2eEgZlT69HekFHjoiNncSo2nkzDvEQ3P7x5/p4N0GINIHMne7oPFQr0K9omO7u1VqQZeCicg1K1bo2s0Av0vJV4aKZusxGH2XzQc/2fgqD87fVTy37ROEx0KrwV7I12v2lN8pfwYYEi0yqPHRZKXzbiDTJqnJVNixyowtgZaeadu1gpXBd9TX+8GeRg1reEqJEYqXaUvC4dp+CAE7hGK1UBNpqMuYtn2+gRJ9/2uxZxeB0hfNAz2VR26SM78zLc/5RtdjBXpsooqpzZe3bzypOYEoZ0ubgjuDRQQMkJ4x81ePFx0PgfrZP71dRrj454UwHrSxcqwVPuIVPkUweD+GR/GH8g3DhZDGAQmHr/vh7DRVojzODIQOHUCdiksVX9d5otKI+jW8zJja9VpuUgyxhDuINaxGBUN2yrqpU8Zj73r0fdU39MW+BHVCD+RcqQf94g9sN7xXZ0C0424uBSGtP65jCmaXdSbybJkIpgf0YmXRMlR+CMiDTRiv0BsQ3coCVrgsWEsB4y/Fm8nJJ1HtWy4ZDprdZfEOIVvgV/ogF0M2UxduKahvGZm/jDyHmIluknT5RaOchJBfD6S3jNtICab421rk7xcpfGp+0yeW/DTMompOLgl/zNgLtPfIJZy4WOfKSlkDvQxZdksiN4eEp5TSp7a/HgzpcJZ2yuI3g6nuXlxf5o2NayJGQo1WHh+PyuA+y3q85+7fNUYr7c3bh42xBjVHY06YCIHbzF81OLRddH/o5Ymhn0KA9nQL2lCMBSMWV7r51xP1WFUmd2+3yJOP/NinLJUb3NsTevL39jIcWq822lAS5gMNVRONpxx+Qpe1cy0Ux48vRgEXPlVlf56MXqw43CM73g7xRuwKDb0bCbVgnYorjWvhf6aqeo+GN1DFD3gSZJrs5j0It61c9pgObcuv/XcbSI2S+1Ge4X2GK3OKtqYcqJdh90/zPRJFvArpDsh3PO3O5HCBj3C25I5F8tcsN24zbZYzJtd8aFrOFBQz3So3GG2nLzLEb0tgOhWaYDnHh6KjEHi1sEL9gHPYJllasO54fTMTAnTj7a+lUDN+bqP05s6JQU4jGlTGIf0QsgsC5nFGdWugYbzSPv1AhEHVlKkI2LBMVqBD0pa9QQ8KIthRPn1AE8KJajkPyRrqw8i4XV7DSScIYmWhTBUoyTi7nwb+6LVITCYGfQssRpVGzPEATVDp2qjnsVty4VjaMYEVpxNcRQ+uPzikRXWeJ5PE98xK4Bz6tI8acOYasCCJ8kLwDGyik8pyDiotsMLPC7jOKHLgXpyjaNO/Jjg2zl8pH/D7fECxqmhO1wbnAb+yxgJ56eJ68e6gXY7dZbqkaFyKrluBVXJLyVhaRv6tb3p4PtgGfRznjQuw7Ow4oguJ1sRbN0iS1LRe58EPyqGGxsnerfsv38IhezXfHX0JtbpIVR19n50QVSnkyp6lgkDglWselw5V3zRQld1UhHTIEpXvhsnKQ/ueTsyEt3I+/LLVds7aQHzUClGvpQ7ndOldDmEp2EXCtXCwL2zInccoASjxSWH+fUSoqdNX7ZiQH7SZNa5W+cA0HRpHM6OXk5QJ9i/cM+4go0k22usSldSG2qtfS7LbHAE0oNG4oapct49doZRKe34iykQ8fiZmwC1VO3TRJpEBrFABLRzBqvUSmLYz62y5TKQwVUigXOQ1z6sxl6mUJ5Hcpn1GQM5skDf1NSoLD79iL9pUGh8c+EQ0esExRhHcoQI8LMdLY0XKsEHZo65T667HDZMhyBZo4Q6nGv4iDD731vqjwVPcV/J+ndS7e8FYxZGKhXLNWdAeQBkt+fhEW4eBDW+kfGv21huxpxeBd0We/aYFw1x5uehhAdwDGV/uFQukPNgvSnrqyWfl/RnrNWXiaZDRTbvFOFZSAmrWY8Rg6Ms0icoVmv9thWHD7XY1joNFURwIHxfEZMa0IuOsrQDCD8nWi9FCW6uzAhedrtpNLRg2vy8nOjBNmB6meguSaF2cZ99u6cGAAqZ7q5WZLhTWHZbQ0hs8MCyk6Narm5K+iugGSlnFvliSUGqeLbUWJVRiphtEBcCQSXzzvlCZO4UmmKtIiuGz0R5L9EdfsDGcs8yP4rYwMWFwkOuWl5agMGs7u5iBOzx4XPU92JZndGl6xsL4JbGfOkj3BbnRnn7uoHoqk0J2M1cZFWxpL55lSM/I0ZKWdBuVksbDJtQ1kk6by+VoZ2rcdyj+74F/ESI+GjPR3FOJzxRkr2St6Mt3nVxX0r4LVV4QXd+Md9DbC3qHoSN6ZqVNv52Y2u7vBYOluC8r2CyXPSsRqxYcGVDrxrUjclftB7PXEo9ZrIyXJmwS1gRjVHAq8/ZJO/P64YxBLynM/v/utO78/O0sh9WgM4Cn28Ah3URBbuM2Z6Z+Rld6wCVNIiv3rWOsJGdMcuxl5hUSeiFYHguIBGvw5Vz8O2Ek+iEJKyaihZZLydYE7krp5p1MBHUUTFqnPxdHqDC7NDL/PS61h1iqNhOUKLysSxolGr5WWvM2ZUbdTw4osd3Q7/mq8DP5TAMmcT7r7/NSl2NWC7bi6w6aMOuQY/nsjQ3tbOd3TOkMaZXgU6sbeBNQni+2D294zczMAYPzH38XB7DSc5DjIxKRNsFLfV1jj2b5ZKDtxvzTao1r9WyJEJpcSY88LPYvonpENKuURR1CcvH4fk340TK3xT7c+S4evQT1N8xO1J/Yvi23qVq+o4VnEqNhMS5ScyJ5YkfZWyqLgu7v6C/qV4QxinNl7t9Lj1v3D19UiUDBOZL/E49/9WdqHYq/r4MNuJiGwPXvJPeb+GuP6ONu6xQ/lQd5d92iRySvrm23JYmnACfc/iTEA0ZR5JXEMwFMktfE33hHhMdple+s5qKPQUzNfZiwN1cePNXvu4qZYw4ED9z4cL3oX6n4yaS0sPiuuKaXyqBqGMHdr6nBGdYENInU55NqnUlJvN1PoDkd0yE5KU6dv48iYbowFOzRZTaJipfZm5ru7UhQZuRW2e6mTZa+5OOfmp9LR+ibznilKqhv+RzX0aBhxkdnXmS7+QG2nDvIc7SjEj341CD4468g4mJiayluEhvYFzit+TScdpoVYzRmSNiGh2vyjNTlgsn/GvvD9zpll/w46lo2A1n1rQTp+GfhusCiRuOVpQxGb6ZNj9foiM3cxdglcuuQ/EVy83Vam51Odw8J3Y+F0Xnxy2X/o42chOrHnxS/AE+eZDLPQZ+62vlm67q1YP5zmQoBxgIzBhDlVzf4sq7/MAmeQPJ4X2TaISFkOCSweNoq6s7OwwRbDbsQhD/lfCv4GMac8b+u/dWK0VcZfFw72ltp3rqBZpcRU4lDGzEwrziJy/0smaqwrJYQ4eoFnTsnR5fHTzZByEySNnV8MK71YPxX6cyTe2pEK10WSKwYobncyAAI0tPiNqW0TfWkt5506Nfk3vHU0PpyKSEVwtIRrfhalhq71qtidHE8usJ/59eBmZdKRsPbrtZnCggU2XJcX6q4hin4rfHSPLGw9eZ7dH15AxrDylOxmRxf7TrOyTke9EIl4nUh+C74HuW/JQt4WsX0aYSmSy0u5oQ4AkGqjm+szW0LCcQvFefvBOfQNi0QCGfMpuAY0JyzJ3i7xHv/3edcLuQKkfdjW7N/yQeLt7zP6TyGnfIvHHQWIy/tyDIBwOXx19xKYU6se1qOUbrI8tsMJsIJEo0uPYbt0n4ZLJM/9T4/A5X1jMqby5fRQh3WdbaZokomYbl5hlQlkkHEvwcQDGySXciXsOh7xxbeqZpWSHgPmRwXiCtco1eCc0U5/01cEdc8QbHXiuINQUlRLVevLvj3Q4isN7ppqoNucMV5ZWWcl2l0wIr3ATIgm07UwkQ57bBylhnFzzxx29wd154OqawlW6NvvpYM5wOZCgyHwMRwt/wIMIXUwAmwidCGq/d1JxLq7Kv6xZUZG9kzPWe3m7Wee+Pbxbh4bg2i3b2OX7GEy55+MP1Q9NDsCCuR9/3dKTcQh0QA1gVe0=
*/