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
7X/tlK2dMP41PahTFAlHC+okgizx2iVFT96VjKowjqgLuCyG4lawPcElaknLfy9HemP+YWfvZVQuhhZjUYnAgsCCxNIepO+Q7G5nbUHY0SjztKiiAXpp/1VePF4/MpmY/EPn8Lpu4aSj1ZIM2jLv9dJ07Tr1q/vDQq5JM4vYyne82Lw+ZK+R1Ik5QUDugrz5ATHa+yrWg8BTTT6bQA6oR2n1nZ3p9zDb1KKTb3kzqoXitNt40vw01/3iwZvtXcsY0dHuekgO8dFs7PIteNpBoLl9IG9gXyPfJUMQhdNLg55/ww3LvTLlTu3gcAVBN7D5V7wI+ludbnjIz/ht2a1lGA0+J4AHs2MWFfzVVJGKK9eItWyD3GNFPH957H75X0syQr9kZmG7EB2vfu7Ewkuj7miiuM/6E+4oI2fHXhtBQv/YgHZePZ5rvrkPwBrZuAZNKSYBVpNcFxO9mvRMltfuzl8eA7zeqyD4jxn8UisJuCXR6ZX09hMzPwwGnhqiHfb0b+eFD1JUYQzqnvpZLns1XOG7a9u8GclyA0tFPk9osWxfFbIcEOcNvR5vKvS8noCPebMc12Z669fYmpEbHIbeeqRMNH/7ZLtYA3CbjS+vQJjHIfc19w6aFzl+EJ3EoUiDwCbLe5rz3CS4tF7JCzgzOqJRzkI42QsxbjwZRHbmNP4DvFaWpkK6zXhrWYC3PE3GWFcDq2UKfNqYj2s7
*/