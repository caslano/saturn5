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