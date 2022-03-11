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