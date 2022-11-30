//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_GRAPH_PROPERTIES_HPP
#define BOOST_GRAPH_PROPERTIES_HPP

#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <boost/pending/property.hpp>
#include <boost/detail/workaround.hpp>

// Include the property map library and extensions in the BGL.
#include <boost/property_map/property_map.hpp>
#include <boost/graph/property_maps/constant_property_map.hpp>
#include <boost/graph/property_maps/null_property_map.hpp>

#include <boost/graph/graph_traits.hpp>
#include <boost/type_traits.hpp>
#include <boost/limits.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/if.hpp>

namespace boost
{

enum default_color_type
{
    white_color,
    gray_color,
    green_color,
    red_color,
    black_color
};

template < class ColorValue > struct color_traits
{
    static default_color_type white() { return white_color; }
    static default_color_type gray() { return gray_color; }
    static default_color_type green() { return green_color; }
    static default_color_type red() { return red_color; }
    static default_color_type black() { return black_color; }
};

// These functions are now obsolete, replaced by color_traits.
inline default_color_type white(default_color_type) { return white_color; }
inline default_color_type gray(default_color_type) { return gray_color; }
inline default_color_type green(default_color_type) { return green_color; }
inline default_color_type red(default_color_type) { return red_color; }
inline default_color_type black(default_color_type) { return black_color; }

struct graph_property_tag
{
};
struct vertex_property_tag
{
};
struct edge_property_tag
{
};

// See examples/edge_property.cpp for how to use this.
#define BOOST_INSTALL_PROPERTY(KIND, NAME)                \
    template <> struct property_kind< KIND##_##NAME##_t > \
    {                                                     \
        typedef KIND##_property_tag type;                 \
    }

#define BOOST_DEF_PROPERTY(KIND, NAME)        \
    enum KIND##_##NAME##_t { KIND##_##NAME }; \
    BOOST_INSTALL_PROPERTY(KIND, NAME)

// These three are defined in boost/pending/property.hpp
BOOST_INSTALL_PROPERTY(vertex, all);
BOOST_INSTALL_PROPERTY(edge, all);
BOOST_INSTALL_PROPERTY(graph, all);
BOOST_DEF_PROPERTY(vertex, index);
BOOST_DEF_PROPERTY(vertex, index1);
BOOST_DEF_PROPERTY(vertex, index2);
BOOST_DEF_PROPERTY(vertex, root);
BOOST_DEF_PROPERTY(edge, index);
BOOST_DEF_PROPERTY(edge, name);
BOOST_DEF_PROPERTY(edge, weight);
BOOST_DEF_PROPERTY(edge, weight2);
BOOST_DEF_PROPERTY(edge, color);
BOOST_DEF_PROPERTY(vertex, name);
BOOST_DEF_PROPERTY(graph, name);
BOOST_DEF_PROPERTY(vertex, distance);
BOOST_DEF_PROPERTY(vertex, distance2);
BOOST_DEF_PROPERTY(vertex, color);
BOOST_DEF_PROPERTY(vertex, degree);
BOOST_DEF_PROPERTY(vertex, in_degree);
BOOST_DEF_PROPERTY(vertex, out_degree);
BOOST_DEF_PROPERTY(vertex, current_degree);
BOOST_DEF_PROPERTY(vertex, priority);
BOOST_DEF_PROPERTY(vertex, discover_time);
BOOST_DEF_PROPERTY(vertex, finish_time);
BOOST_DEF_PROPERTY(vertex, predecessor);
BOOST_DEF_PROPERTY(vertex, rank);
BOOST_DEF_PROPERTY(vertex, centrality);
BOOST_DEF_PROPERTY(vertex, lowpoint);
BOOST_DEF_PROPERTY(vertex, potential);
BOOST_DEF_PROPERTY(vertex, update);
BOOST_DEF_PROPERTY(vertex, underlying);
BOOST_DEF_PROPERTY(edge, reverse);
BOOST_DEF_PROPERTY(edge, capacity);
BOOST_DEF_PROPERTY(edge, flow);
BOOST_DEF_PROPERTY(edge, residual_capacity);
BOOST_DEF_PROPERTY(edge, centrality);
BOOST_DEF_PROPERTY(edge, discover_time);
BOOST_DEF_PROPERTY(edge, update);
BOOST_DEF_PROPERTY(edge, finished);
BOOST_DEF_PROPERTY(edge, underlying);
BOOST_DEF_PROPERTY(graph, visitor);

// These tags are used for property bundles
// These three are defined in boost/pending/property.hpp
BOOST_INSTALL_PROPERTY(graph, bundle);
BOOST_INSTALL_PROPERTY(vertex, bundle);
BOOST_INSTALL_PROPERTY(edge, bundle);

// These tags are used to denote the owners and local descriptors
// for the vertices and edges of a distributed graph.
BOOST_DEF_PROPERTY(vertex, global);
BOOST_DEF_PROPERTY(vertex, owner);
BOOST_DEF_PROPERTY(vertex, local);
BOOST_DEF_PROPERTY(edge, global);
BOOST_DEF_PROPERTY(edge, owner);
BOOST_DEF_PROPERTY(edge, local);
BOOST_DEF_PROPERTY(vertex, local_index);
BOOST_DEF_PROPERTY(edge, local_index);

#undef BOOST_DEF_PROPERTY

namespace detail
{

    template < typename G, typename Tag >
    struct property_kind_from_graph : property_kind< Tag >
    {
    };

#ifndef BOOST_GRAPH_NO_BUNDLED_PROPERTIES
    template < typename G, typename R, typename T >
    struct property_kind_from_graph< G, R T::* >
    {
        typedef typename boost::mpl::if_<
            boost::is_base_of< T, typename vertex_bundle_type< G >::type >,
            vertex_property_tag,
            typename boost::mpl::if_<
                boost::is_base_of< T, typename edge_bundle_type< G >::type >,
                edge_property_tag,
                typename boost::mpl::if_<
                    boost::is_base_of< T,
                        typename graph_bundle_type< G >::type >,
                    graph_property_tag, void >::type >::type >::type type;
    };
#endif

    struct dummy_edge_property_selector
    {
        template < class Graph, class Property, class Tag > struct bind_
        {
            typedef identity_property_map type;
            typedef identity_property_map const_type;
        };
    };
    struct dummy_vertex_property_selector
    {
        template < class Graph, class Property, class Tag > struct bind_
        {
            typedef identity_property_map type;
            typedef identity_property_map const_type;
        };
    };

} // namespace detail

// Graph classes can either partially specialize property_map
// or they can specialize these two selector classes.
template < class GraphTag > struct edge_property_selector
{
    typedef detail::dummy_edge_property_selector type;
};

template < class GraphTag > struct vertex_property_selector
{
    typedef detail::dummy_vertex_property_selector type;
};

namespace detail
{

    template < typename A > struct return_void
    {
        typedef void type;
    };

    template < typename Graph, typename Enable = void > struct graph_tag_or_void
    {
        typedef void type;
    };

    template < typename Graph >
    struct graph_tag_or_void< Graph,
        typename return_void< typename Graph::graph_tag >::type >
    {
        typedef typename Graph::graph_tag type;
    };

    template < class Graph, class PropertyTag >
    struct edge_property_map
    : edge_property_selector< typename graph_tag_or_void< Graph >::type >::
          type::template bind_< Graph,
              typename edge_property_type< Graph >::type, PropertyTag >
    {
    };
    template < class Graph, class PropertyTag >
    struct vertex_property_map
    : vertex_property_selector< typename graph_tag_or_void< Graph >::type >::
          type::template bind_< Graph,
              typename vertex_property_type< Graph >::type, PropertyTag >
    {
    };
} // namespace detail

template < class Graph, class Property, class Enable = void >
struct property_map
: mpl::if_< is_same< typename detail::property_kind_from_graph< Graph,
                         Property >::type,
                edge_property_tag >,
      detail::edge_property_map< Graph, Property >,
      detail::vertex_property_map< Graph, Property > >::type
{
};

// shortcut for accessing the value type of the property map
template < class Graph, class Property > class property_map_value
{
    typedef typename property_map< Graph, Property >::const_type PMap;

public:
    typedef typename property_traits< PMap >::value_type type;
};

template < class Graph, class Property > class graph_property
{
public:
    typedef typename property_value<
        typename boost::graph_property_type< Graph >::type, Property >::type
        type;
};

template < typename Graph >
struct vertex_property : vertex_property_type< Graph >
{
};
template < typename Graph > struct edge_property : edge_property_type< Graph >
{
};

template < typename Graph >
class degree_property_map
: public put_get_helper< typename graph_traits< Graph >::degree_size_type,
      degree_property_map< Graph > >
{
public:
    typedef typename graph_traits< Graph >::vertex_descriptor key_type;
    typedef typename graph_traits< Graph >::degree_size_type value_type;
    typedef value_type reference;
    typedef readable_property_map_tag category;
    degree_property_map(const Graph& g) : m_g(g) {}
    value_type operator[](const key_type& v) const { return degree(v, m_g); }

private:
    const Graph& m_g;
};
template < typename Graph >
inline degree_property_map< Graph > make_degree_map(const Graph& g)
{
    return degree_property_map< Graph >(g);
}

//========================================================================
// Iterator Property Map Generating Functions contributed by
// Kevin Vanhorn. (see also the property map generating functions
// in boost/property_map/property_map.hpp)

#if !defined(BOOST_NO_STD_ITERATOR_TRAITS)
// A helper function for creating a vertex property map out of a
// random access iterator and the internal vertex index map from a
// graph.
template < class PropertyGraph, class RandomAccessIterator >
inline iterator_property_map< RandomAccessIterator,
    typename property_map< PropertyGraph, vertex_index_t >::type,
    typename std::iterator_traits< RandomAccessIterator >::value_type,
    typename std::iterator_traits< RandomAccessIterator >::reference >
make_iterator_vertex_map(RandomAccessIterator iter, const PropertyGraph& g)
{
    return make_iterator_property_map(iter, get(vertex_index, g));
}

// Use this next function when vertex_descriptor is known to be an
// integer type, with values ranging from 0 to num_vertices(g).
//
template < class RandomAccessIterator >
inline iterator_property_map< RandomAccessIterator, identity_property_map,
    typename std::iterator_traits< RandomAccessIterator >::value_type,
    typename std::iterator_traits< RandomAccessIterator >::reference >
make_iterator_vertex_map(RandomAccessIterator iter)
{
    return make_iterator_property_map(iter, identity_property_map());
}
#endif

template < class PropertyGraph, class RandomAccessContainer >
inline iterator_property_map< typename RandomAccessContainer::iterator,
    typename property_map< PropertyGraph, vertex_index_t >::type,
    typename RandomAccessContainer::value_type,
    typename RandomAccessContainer::reference >
make_container_vertex_map(RandomAccessContainer& c, const PropertyGraph& g)
{
    BOOST_ASSERT(c.size() >= num_vertices(g));
    return make_iterator_vertex_map(c.begin(), g);
}

template < class RandomAccessContainer >
inline iterator_property_map< typename RandomAccessContainer::iterator,
    identity_property_map, typename RandomAccessContainer::value_type,
    typename RandomAccessContainer::reference >
make_container_vertex_map(RandomAccessContainer& c)
{
    return make_iterator_vertex_map(c.begin());
}

// NOTE: These functions are declared, but never defined since they need to
// be overloaded by graph implementations. However, we need them to be
// declared for the functions below.
template < typename Graph, typename Tag >
typename graph_property< Graph, graph_bundle_t >::type& get_property(
    Graph& g, Tag);

template < typename Graph, typename Tag >
typename graph_property< Graph, graph_bundle_t >::type const& get_property(
    Graph const& g, Tag);

#ifndef BOOST_GRAPH_NO_BUNDLED_PROPERTIES
// NOTE: This operation is a simple adaptor over the overloaded get_property
// operations.
template < typename Graph >
inline typename graph_property< Graph, graph_bundle_t >::type& get_property(
    Graph& g)
{
    return get_property(g, graph_bundle);
}

template < typename Graph >
inline typename graph_property< Graph, graph_bundle_t >::type const&
get_property(const Graph& g)
{
    return get_property(g, graph_bundle);
}
#endif

} // namespace boost

#endif /* BOOST_GRAPH_PROPERTIES_HPP */

/* properties.hpp
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
*/