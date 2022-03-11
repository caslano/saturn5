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