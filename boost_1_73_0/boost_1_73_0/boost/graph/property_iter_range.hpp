
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
XXBKmlKTQ2omH4gHvu449E0MyNdRNr5s4G8xc1T15jqin/z+2+fiQCTADSQL6q4DjwGSXeV7gMPO9o/8w+5x53llCdSkOdsedE76ow61AIVH/mH/rHdQ0t1pZ3DSHZIO86DT63YO3H2+G3ShRcSDnf2RuwjiUH+/3zucdWUR97ja+/ud4VB0V7EKp+19WKcezWP4fjjqnLg7/q+z/qjtd37a73QO5PjdPR90h2/9QyBpJb3SirWPB532wXtosDscDdcuMBcraRBIC+1AB1Dre2dTOHhoZDDoD0QbgNsC4KNk6XMgy1cM6FtWXegFQLsIx0pZGqYpnmcLlJFKVAAwnJQ+6swB1s9vhPo8nnrBchkGSbAYk2pdWfQYE1gzp+nAxHudath/LAyp8H80UdA4RVHuXc0EZLUkHH94xs09QhPrakGqVLZ7l48C5BeC2/5+//hup0W0B2DeGZVPbr9/dnwAlBFOQg/OSnlDpG52r8/ZyO8f+icwsMH7tSMZdnpuoMcXBmQ52jjqD0dvO+/9bq/rOtZmoWH3Ta+00OnZ6+PuPhY76w06+/03ve5/O7FJsfiPnUH3sFtydE87nYF/2IbdOfC54H4bGbPyOZ22h8N3/QHM/afT7qCk2eP+m26vAgcZSzzqnnRgU0on
*/