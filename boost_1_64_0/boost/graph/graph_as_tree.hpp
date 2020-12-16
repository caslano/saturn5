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
XkDTCc0+6GI7DPj7M/7wPJ82AhKKKN/4TQ0qzgkkx8TIK8+ILkjAmnCisnmV9OGjncRix895n8iFFfstE9HmiM16pibbyd5RNkotX8+NVJ3YvvA+eUFo9ARrbjRwU4faADIC3ffHPhf9WigcCAvp7qrlsR75AlxJ31KtJzxjRRXxYp1s7c/InIWthzK+COeS9v8E+dhB68/loHVBiX48TYzVgHzlx9UdKedSYxJMLkKsI/3vk42SDej9etbNwjv+RM2dZxV/uzOPGHYPEZOUTnyC3gRXDJf5Hx1xVzmOBeFRZPNGKu8XWCE9clybcFVTP7Jro9BfSBgXMiJcOrC4Tb5ltcG17auoWUsUZ9cuKcctnExCP25GI3pDr2W+alYXO8OK3U78m9brr/D8M5az7L2SdS/oDAOry3oCGPJK+95hbWkrizFHPMXJInVZ2sN/qxKhxceCBcS8rDN2peMXejhHgqftw8JEu05vkMZrXeukk7WdTLveMLYWHWFD3Sh/AeCwYl92a8hR9WJS8BXE2sonj17H8lWTUsLsD5JIkO+mu0nrHuIyyiwyINGJzyNe9njapdgjFdqgfnKsuZIjw1UM2PDX02PdY6/vYbFwJcoY9BnYzRD49SmtNu79HNkRRPeFmpx0alGh9zOU+mLenUGSTU/aebp7y/A3W8Ec5m6TMwF4HOBad28J6sS8SbmSxmEM8BRlDQXgFRkuY1Pe4PwjGz57XRaDuG/JbL4u87te4olQOOJ3OT06OIE7kIcHWiXSt4LdoHia5cij+urq/KxoehMxl7SxMM3FdOU4JleD9nchpqNyO87iS4CftCLUPjOZef0nyDv8zHcP1ImFSYtrf7H8ntZZ82plQGep6Ln7lBIoukuINlcZUJNwqSX0TA5abs/QqAvM0Gw94kyYL5xUnZ0oJDU0RreoKB+N3/3x72uZQT9ANb0CnHLsoCfELIYpvshLskwnxfaZOSGhOSDFs/tje+UdDc4OETKFRpMnbp2hmFTdSFtJvGKPhAvyWdBOYQjEPRGCvFI8e4MDziv5WIa2jM/jqZ0hR+HqlW5JN4kewfhdusgQDDloqOSOwtJ9VnerAKwVv6NbovCfVTHuERUmfR4HbAdu9j5MiEp//151plmE41zpa91VOiD9+RxqjiSAFzONVihh75wA2E+ydlEYKjhmeQ7bxLNLXWMh3HwTXlz4rPEquOTz/IoIESm7uPdCrygIAgvGFYET94BelfuusliijvyirTTIDM8IqHWQtmrXHqjyLxyp3iO+GELDhgmP+5HSU2tMNyAQqb6imJrmtJe4S7MSkse8D7VymGCCu0tZvXcHp+8RjY/OLNPt3rCkmxioCPZz7ujc3LriY1JVrw08/OStYWv8xU5zaxxWNSpPvMgPiPmNjxg5iAdg1r+Et+B1uEyUvL64cR/wtIGCrah8kp1885OO2CjPmrdMjoAlZBLJpRsHJZTmgbhAqt+Crab+TyHngaF7zfyO8sqH7BS1r33eX2C/duZa3ClExiMvfx4oudB4QaRpMQWPIUE+Ti9A+yK7NqLKKyOxtq0E+tJE10R/ji/Ce+JHjut4xWycADfZ86AsTdHOxT23g+giXXO9LqoPI5jfwpLGbumzjLVPRWDvYw5H+qbCjtdH5CgXr9ym2JkkrkHwLTMFSmj+QldmdNAcv/+Wb6+hU/xglzpK8+Ct11omlJc/28qfGSSsn1cheu1ttMJuWpugxB1mP6Ga33fj3phxHW2y6QmhEZsVIVFdHppZdma3Ln+rNuwz7deMhA2Egz9jTai7VlEUqlm96sm9gc/36RX4K7MjuYKyyDB147MCuQXrF2Miux6dMOnfYl09VY8=
*/