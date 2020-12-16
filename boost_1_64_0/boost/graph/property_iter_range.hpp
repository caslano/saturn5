
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
+owoER1NgQ7OTr/yrNfhrvOEif2npls1Ee5WxtTfPZC/EZnPNb31eako95NR6lehcrIvZ5Vnu++UyOUJ0eZILs9KORdlveXZLyx7iHzkp6xTg2avyTqzWGZLneycrGFC7bu8LpPH6lDTM3xK3kvtz+HfaXkusg95j+I5eTyX9dP3Rbvzs+rrVTmXUQ5jOE/4mFqYfNW5sdkVLb+HvNJ5qW2xRG6LOqKm7bHMUfu0Y1meY6kzWfbjI5crWbtvSK7bCC+ugVy75bEjAtT5NvCcLHMM5i7Nww7e3MP6ks25eWjmkGG5ooU612+Ux00K1zJvccd0i+cIuIkljgOEu5OH2OLkIHbgF05lxY+c4yI4PzGG3H9T5fjjXDbzgSkP57Lie8J8/bAsaznSWl3rvi+Xwe77A3xxu5zzKNFInV/d5PYv4+EpBosczhc9Tc+5BLs1EWlutcQczke7OHvdci8j5z6L+cyU4w02efDbWLCoZ6op++UKU2LOd2b+k7kq7hXNxK+ck7xNndka8nyt9qs/mi7x1Aov2Z8l7zx1wn1ajOX9V+0aJ9e3q83+Jq8c6VmZ7E/q2IuWdb4yvc1dYJZtfVouW23S5mPuhQuWfZtyfazbLOMpk7ZtS+j5ruynvhzL5K3OXfIpqEKeGwvUtWq7LBuXPYr/1f6m9qWvHPs5xqo8yzXpoMlVvC7HuEr9R3KMZxnDen4cmpUzagiJALVdJstz7O/Zkq6iHtFG5Mnxh6vxx8jxtVd8pNUcNJdz7qPmxCTmyXS0E88bdrKez+W5Qx5ClrlbLest5KgIFJa56i3H95b7/C5a7ZLLPNTLT19m1j0va2zq8PQ0y3G/DH+U9ZoZzg1yMFUniPEWyTrzZJ2Fsg5LxMXHMsdFhutP1lh5+VHt/Wm/TbbP8rLWyR6Sm5sxmiu8rHOTnD2yTorNHHON0SZZjbFSH0Ndf9QYfuo18iM5J90pKyuqE77qtYCznJfawkFU1F/XvivPKT2d2gpPJ8u+sFQeR8fETNFS+Kn9cZxcptVOEx2cedaB+frZQ59rV32fqSaPyQjRWFRQbdkjZV4/zuqxzvnOn8jz82jLfX/fmPfrOjJPZqp9cYLHclN9ngvgIYY7holLjn6m2s6xzsyRfN7uGrk8L1rnkf3Qdlu50dXbsk7uX821ZVudRescj85SW1u230LOl7J9lOG6yWzn8oN+3Twkl78xL/E3iSNikIPlGvkHmd+Ia+QW8RF3bWp9zqJdpuxzO31aXrukj5a/+6jlPoK5ss7b1FHXTHXtoEie6/qa2LNknW1e9zzcuQfvisjwdBaPPD1ErbLOom3ZcqKXF0+9J7xkfeu5qRrznKXmPk3mLXF0FyNNE0yfiz4OIcw45Wo7jJLlLzhWMHlQw1k8wUC2f3uHciLesZywnfucIaPNx5LahybIbd5UpVkbmXaQ6/iAehvl8j/vZf19i2NFrp95v4yS15cVzi1MB8VjU10R6XBf9HVsw/M4/HjNWUEMZG8d4+yr9mP+/iX3w69ZyvXyXFVIX3FyjOM221+babWN1fbrI4+VOvq5Y7lMO8nlFJQvl31M87LZT7RnjcvV9VXXnXbyeGlrChV39e+RsV3fTfTzreyno+znxUqW1wM8aF7tiyHU8aAs3k/uE/ryNZLrVVk/Dj+Ux2uiU5bIF++ZZjvI64X+eqi8HE8+w0eO10jO77Pm8fKyctJleTGpGbJ8mZfNtXUc/+mvBaJ/kK8FOLLLMnZVEUqJryzTrz2s7zqTdV7YfupCUE310Vj2sUNUp5dmzEUcMVo0leubqK4Fbr7yuGxpe0wtuiiXndr+XJnLyf4SyE+Wy7zPq6mbg4giBrk5cn8=
*/