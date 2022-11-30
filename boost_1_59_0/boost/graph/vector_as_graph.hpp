//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Copyright 2006 The Trustees of Indiana University.
// Copyright (C) 2001 Vladimir Prus <ghost@cs.msu.su>
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek, Douglas Gregor
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

// The mutating functions (add_edge, etc.) were added by Vladimir Prus.

#ifndef BOOST_VECTOR_AS_GRAPH_HPP
#define BOOST_VECTOR_AS_GRAPH_HPP

#include <cassert>
#include <utility>
#include <vector>
#include <cstddef>
#include <iterator>
#include <boost/iterator/counting_iterator.hpp>
#include <boost/range/irange.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/properties.hpp>
#include <algorithm>

/*
  This module implements the VertexListGraph concept using a
  std::vector as the "back-bone" of the graph (the vector *is* the
  graph object). The edge-lists type of the graph is templated, so the
  user can choose any STL container, so long as the value_type of the
  container is convertible to the size_type of the vector. For now any
  graph properties must be stored seperately.

  This module requires the C++ compiler to support partial
  specialization for the graph_traits class, so this is not portable
  to VC++.

*/

namespace boost
{
namespace detail
{
    template < class EdgeList > struct val_out_edge_ret;
    template < class EdgeList > struct val_out_edge_iter;
    template < class EdgeList > struct val_edge;
}
}

namespace boost
{

struct vector_as_graph_traversal_tag : public vertex_list_graph_tag,
                                       public adjacency_graph_tag,
                                       public incidence_graph_tag
{
};

template < class EdgeList > struct graph_traits< std::vector< EdgeList > >
{
    typedef typename EdgeList::value_type V;
    typedef V vertex_descriptor;
    typedef typename detail::val_edge< EdgeList >::type edge_descriptor;
    typedef typename EdgeList::const_iterator adjacency_iterator;
    typedef
        typename detail::val_out_edge_iter< EdgeList >::type out_edge_iterator;
    typedef void in_edge_iterator;
    typedef void edge_iterator;
    typedef counting_iterator< V > vertex_iterator;
    typedef directed_tag directed_category;
    typedef allow_parallel_edge_tag edge_parallel_category;
    typedef vector_as_graph_traversal_tag traversal_category;
    typedef typename std::vector< EdgeList >::size_type vertices_size_type;
    typedef void edges_size_type;
    typedef typename EdgeList::size_type degree_size_type;
    static V null_vertex() { return V(-1); }
};
template < class EdgeList > struct edge_property_type< std::vector< EdgeList > >
{
    typedef void type;
};
template < class EdgeList >
struct vertex_property_type< std::vector< EdgeList > >
{
    typedef void type;
};
template < class EdgeList >
struct graph_property_type< std::vector< EdgeList > >
{
    typedef void type;
};
}

namespace boost
{

namespace detail
{

    // "val" is short for Vector Adjacency List

    template < class EdgeList > struct val_edge
    {
        typedef typename EdgeList::value_type V;
        typedef std::pair< V, V > type;
    };

    // need rewrite this using boost::iterator_adaptor
    template < class V, class Iter > class val_out_edge_iterator
    {
        typedef val_out_edge_iterator self;
        typedef std::pair< V, V > Edge;

    public:
        typedef std::input_iterator_tag iterator_category;
        typedef std::pair< V, V > value_type;
        typedef std::ptrdiff_t difference_type;
        typedef std::pair< V, V >* pointer;
        typedef const std::pair< V, V > reference;
        val_out_edge_iterator() {}
        val_out_edge_iterator(V s, Iter i) : _source(s), _iter(i) {}
        Edge operator*() const { return Edge(_source, *_iter); }
        self& operator++()
        {
            ++_iter;
            return *this;
        }
        self operator++(int)
        {
            self t = *this;
            ++_iter;
            return t;
        }
        bool operator==(const self& x) const { return _iter == x._iter; }
        bool operator!=(const self& x) const { return _iter != x._iter; }

    protected:
        V _source;
        Iter _iter;
    };

    template < class EdgeList > struct val_out_edge_iter
    {
        typedef typename EdgeList::value_type V;
        typedef typename EdgeList::const_iterator Iter;
        typedef val_out_edge_iterator< V, Iter > type;
    };

    template < class EdgeList > struct val_out_edge_ret
    {
        typedef typename val_out_edge_iter< EdgeList >::type IncIter;
        typedef std::pair< IncIter, IncIter > type;
    };

} // namesapce detail

template < class EdgeList, class Alloc >
typename detail::val_out_edge_ret< EdgeList >::type out_edges(
    typename EdgeList::value_type v, const std::vector< EdgeList, Alloc >& g)
{
    typedef typename detail::val_out_edge_iter< EdgeList >::type Iter;
    typedef typename detail::val_out_edge_ret< EdgeList >::type return_type;
    return return_type(Iter(v, g[v].begin()), Iter(v, g[v].end()));
}

template < class EdgeList, class Alloc >
typename EdgeList::size_type out_degree(
    typename EdgeList::value_type v, const std::vector< EdgeList, Alloc >& g)
{
    return g[v].size();
}

template < class EdgeList, class Alloc >
std::pair< typename EdgeList::const_iterator,
    typename EdgeList::const_iterator >
adjacent_vertices(
    typename EdgeList::value_type v, const std::vector< EdgeList, Alloc >& g)
{
    return std::make_pair(g[v].begin(), g[v].end());
}

// source() and target() already provided for pairs in graph_traits.hpp

template < class EdgeList, class Alloc >
std::pair< boost::counting_iterator< typename EdgeList::value_type >,
    boost::counting_iterator< typename EdgeList::value_type > >
vertices(const std::vector< EdgeList, Alloc >& v)
{
    typedef boost::counting_iterator< typename EdgeList::value_type > Iter;
    return std::make_pair(Iter(0), Iter(v.size()));
}

template < class EdgeList, class Alloc >
typename std::vector< EdgeList, Alloc >::size_type num_vertices(
    const std::vector< EdgeList, Alloc >& v)
{
    return v.size();
}

template < class EdgeList, class Allocator >
typename std::pair< typename detail::val_edge< EdgeList >::type, bool >
add_edge(typename EdgeList::value_type u, typename EdgeList::value_type v,
    std::vector< EdgeList, Allocator >& g)
{
    typedef typename detail::val_edge< EdgeList >::type edge_type;
    g[u].insert(g[u].end(), v);
    return std::make_pair(edge_type(u, v), true);
}

template < class EdgeList, class Allocator >
typename std::pair< typename detail::val_edge< EdgeList >::type, bool > edge(
    typename EdgeList::value_type u, typename EdgeList::value_type v,
    std::vector< EdgeList, Allocator >& g)
{
    typedef typename detail::val_edge< EdgeList >::type edge_type;
    typename EdgeList::iterator i = g[u].begin(), end = g[u].end();
    for (; i != end; ++i)
        if (*i == v)
            return std::make_pair(edge_type(u, v), true);
    return std::make_pair(edge_type(), false);
}

template < class EdgeList, class Allocator >
void remove_edge(typename EdgeList::value_type u,
    typename EdgeList::value_type v, std::vector< EdgeList, Allocator >& g)
{
    typename EdgeList::iterator i = std::remove(g[u].begin(), g[u].end(), v);
    if (i != g[u].end())
        g[u].erase(i, g[u].end());
}

template < class EdgeList, class Allocator >
void remove_edge(typename detail::val_edge< EdgeList >::type e,
    std::vector< EdgeList, Allocator >& g)
{
    typename EdgeList::value_type u, v;
    u = e.first;
    v = e.second;
    // FIXME: edge type does not fully specify the edge to be deleted
    typename EdgeList::iterator i = std::remove(g[u].begin(), g[u].end(), v);
    if (i != g[u].end())
        g[u].erase(i, g[u].end());
}

template < class EdgeList, class Allocator, class Predicate >
void remove_edge_if(Predicate p, std::vector< EdgeList, Allocator >& g)
{
    for (std::size_t u = 0; u < g.size(); ++u)
    {
        // Oops! gcc gets internal compiler error on compose_.......

        typedef typename EdgeList::iterator iterator;
        iterator b = g[u].begin(), e = g[u].end();

        if (!g[u].empty())
        {

            for (; b != e;)
            {
                if (p(std::make_pair(u, *b)))
                {
                    --e;
                    if (b == e)
                        break;
                    else
                        iter_swap(b, e);
                }
                else
                {
                    ++b;
                }
            }
        }

        if (e != g[u].end())
            g[u].erase(e, g[u].end());
    }
}

template < class EdgeList, class Allocator >
typename EdgeList::value_type add_vertex(std::vector< EdgeList, Allocator >& g)
{
    g.resize(g.size() + 1);
    return g.size() - 1;
}

template < class EdgeList, class Allocator >
void clear_vertex(
    typename EdgeList::value_type u, std::vector< EdgeList, Allocator >& g)
{
    g[u].clear();
    for (std::size_t i = 0; i < g.size(); ++i)
        remove_edge(i, u, g);
}

template < class EdgeList, class Allocator >
void remove_vertex(
    typename EdgeList::value_type u, std::vector< EdgeList, Allocator >& g)
{
    typedef typename EdgeList::iterator iterator;
    clear_vertex(u, g);
    g.erase(g.begin() + u);
    for (std::size_t i = 0; i < g.size(); ++i)
        for (iterator it = g[i].begin(); it != g[i].end(); ++it)
            // after clear_vertex *it is never equal to u
            if (*it > u)
                --*it;
}

template < typename EdgeList, typename Allocator >
struct property_map< std::vector< EdgeList, Allocator >, vertex_index_t >
{
    typedef identity_property_map type;
    typedef type const_type;
};

template < typename EdgeList, typename Allocator >
identity_property_map get(
    vertex_index_t, const std::vector< EdgeList, Allocator >&)
{
    return identity_property_map();
}

template < typename EdgeList, typename Allocator >
identity_property_map get(vertex_index_t, std::vector< EdgeList, Allocator >&)
{
    return identity_property_map();
}
} // namespace boost

#endif // BOOST_VECTOR_AS_GRAPH_HPP

/* vector_as_graph.hpp
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
*/