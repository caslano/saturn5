//
//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//
#ifndef BOOST_GRAPH_GRAPH_AS_TREE_HPP
#define BOOST_GRAPH_GRAPH_AS_TREE_HPP

#include <vector>
#include <boost/config.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/tree_traits.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/visitors.hpp>

namespace boost
{

template < class Graph, class Node, class ChIt, class Derived >
class graph_as_tree_base
{
    typedef Derived Tree;

public:
    typedef Node node_descriptor;
    typedef ChIt children_iterator;

    graph_as_tree_base(Graph& g, Node root) : _g(g), _root(root) {}

    friend Node root(const Tree& t) { return t._root; }

    template < class N >
    friend std::pair< ChIt, ChIt > children(N n, const Tree& t)
    {
        return adjacent_vertices(n, t._g);
    }

    template < class N > friend Node parent(N n, const Tree& t)
    {
        return boost::get(t.parent_pa(), n);
    }

    Graph& _g;
    Node _root;
};

struct graph_as_tree_tag
{
};

template < class Graph, class ParentMap,
    class Node = typename graph_traits< Graph >::vertex_descriptor,
    class ChIt = typename graph_traits< Graph >::adjacency_iterator >
class graph_as_tree : public graph_as_tree_base< Graph, Node, ChIt,
                          graph_as_tree< Graph, ParentMap, Node, ChIt > >
{
    typedef graph_as_tree self;
    typedef graph_as_tree_base< Graph, Node, ChIt, self > super;

public:
    graph_as_tree(Graph& g, Node root) : super(g, root) {}

    graph_as_tree(Graph& g, Node root, ParentMap p) : super(g, root), _p(p)
    {
        breadth_first_search(g, root,
            visitor(make_bfs_visitor(
                record_predecessors(p, boost::on_tree_edge()))));
    }
    ParentMap parent_pa() const { return _p; }
    typedef graph_as_tree_tag graph_tag; // for property_map
protected:
    ParentMap _p;
};

namespace detail
{

    struct graph_as_tree_vertex_property_selector
    {
        template < typename GraphAsTree, typename Property, typename Tag >
        struct bind_
        {
            typedef typename GraphAsTree::base_type Graph;
            typedef property_map< Graph, Tag > PMap;
            typedef typename PMap::type type;
            typedef typename PMap::const_type const_type;
        };
    };

    struct graph_as_tree_edge_property_selector
    {
        template < typename GraphAsTree, typename Property, typename Tag >
        struct bind_
        {
            typedef typename GraphAsTree::base_type Graph;
            typedef property_map< Graph, Tag > PMap;
            typedef typename PMap::type type;
            typedef typename PMap::const_type const_type;
        };
    };

} // namespace detail

template <> struct vertex_property_selector< graph_as_tree_tag >
{
    typedef detail::graph_as_tree_vertex_property_selector type;
};

template <> struct edge_property_selector< graph_as_tree_tag >
{
    typedef detail::graph_as_tree_edge_property_selector type;
};

template < typename Graph, typename P, typename N, typename C,
    typename Property >
typename property_map< Graph, Property >::type get(
    Property p, graph_as_tree< Graph, P, N, C >& g)
{
    return get(p, g._g);
}

template < typename Graph, typename P, typename N, typename C,
    typename Property >
typename property_map< Graph, Property >::const_type get(
    Property p, const graph_as_tree< Graph, P, N, C >& g)
{
    const Graph& gref = g._g; // in case GRef is non-const
    return get(p, gref);
}

template < typename Graph, typename P, typename N, typename C,
    typename Property, typename Key >
typename property_traits<
    typename property_map< Graph, Property >::const_type >::value_type
get(Property p, const graph_as_tree< Graph, P, N, C >& g, const Key& k)
{
    return get(p, g._g, k);
}

template < typename Graph, typename P, typename N, typename C,
    typename Property, typename Key, typename Value >
void put(Property p, const graph_as_tree< Graph, P, N, C >& g, const Key& k,
    const Value& val)
{
    put(p, g._g, k, val);
}

} // namespace boost

#endif //  BOOST_GRAPH_GRAPH_AS_TREE_HPP

/* graph_as_tree.hpp
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
*/