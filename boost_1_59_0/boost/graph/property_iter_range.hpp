
// (C) Copyright Francois Faure, iMAGIS-GRAVIR / UJF, 2001.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Revision History:
// 03 May 2001   Jeremy Siek
//      Generalized the property map iterator and moved that
//      part to boost/property_map.hpp. Also modified to
//      differentiate between const/mutable graphs and
//      added a workaround to avoid partial specialization.

// 02 May 2001   Francois Faure
//     Initial version.

#ifndef BOOST_GRAPH_PROPERTY_ITER_RANGE_HPP
#define BOOST_GRAPH_PROPERTY_ITER_RANGE_HPP

#include <boost/property_map/property_map_iterator.hpp>
#include <boost/graph/properties.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/same_traits.hpp>

namespace boost
{

//======================================================================
// graph property iterator range

template < class Graph, class PropertyTag > class graph_property_iter_range
{
    typedef typename property_map< Graph, PropertyTag >::type map_type;
    typedef
        typename property_map< Graph, PropertyTag >::const_type const_map_type;
    typedef typename property_kind< PropertyTag >::type Kind;
    typedef typename mpl::if_c< is_same< Kind, vertex_property_tag >::value,
        typename graph_traits< Graph >::vertex_iterator,
        typename graph_traits< Graph >::edge_iterator >::type iter;

public:
    typedef typename property_map_iterator_generator< map_type, iter >::type
        iterator;
    typedef
        typename property_map_iterator_generator< const_map_type, iter >::type
            const_iterator;
    typedef std::pair< iterator, iterator > type;
    typedef std::pair< const_iterator, const_iterator > const_type;
};

namespace detail
{

    template < class Graph, class Tag >
    typename graph_property_iter_range< Graph, Tag >::type
    get_property_iter_range_kind(
        Graph& graph, const Tag& tag, const vertex_property_tag&)
    {
        typedef typename graph_property_iter_range< Graph, Tag >::iterator iter;
        return std::make_pair(iter(vertices(graph).first, get(tag, graph)),
            iter(vertices(graph).second, get(tag, graph)));
    }

    template < class Graph, class Tag >
    typename graph_property_iter_range< Graph, Tag >::const_type
    get_property_iter_range_kind(
        const Graph& graph, const Tag& tag, const vertex_property_tag&)
    {
        typedef typename graph_property_iter_range< Graph, Tag >::const_iterator
            iter;
        return std::make_pair(iter(vertices(graph).first, get(tag, graph)),
            iter(vertices(graph).second, get(tag, graph)));
    }

    template < class Graph, class Tag >
    typename graph_property_iter_range< Graph, Tag >::type
    get_property_iter_range_kind(
        Graph& graph, const Tag& tag, const edge_property_tag&)
    {
        typedef typename graph_property_iter_range< Graph, Tag >::iterator iter;
        return std::make_pair(iter(edges(graph).first, get(tag, graph)),
            iter(edges(graph).second, get(tag, graph)));
    }

    template < class Graph, class Tag >
    typename graph_property_iter_range< Graph, Tag >::const_type
    get_property_iter_range_kind(
        const Graph& graph, const Tag& tag, const edge_property_tag&)
    {
        typedef typename graph_property_iter_range< Graph, Tag >::const_iterator
            iter;
        return std::make_pair(iter(edges(graph).first, get(tag, graph)),
            iter(edges(graph).second, get(tag, graph)));
    }

} // namespace detail

//======================================================================
// get an iterator range of properties

template < class Graph, class Tag >
typename graph_property_iter_range< Graph, Tag >::type get_property_iter_range(
    Graph& graph, const Tag& tag)
{
    typedef typename property_kind< Tag >::type Kind;
    return detail::get_property_iter_range_kind(graph, tag, Kind());
}

template < class Graph, class Tag >
typename graph_property_iter_range< Graph, Tag >::const_type
get_property_iter_range(const Graph& graph, const Tag& tag)
{
    typedef typename property_kind< Tag >::type Kind;
    return detail::get_property_iter_range_kind(graph, tag, Kind());
}

} // namespace boost

#endif // BOOST_GRAPH_PROPERTY_ITER_RANGE_HPP

/* property_iter_range.hpp
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
*/