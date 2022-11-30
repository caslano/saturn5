//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//
// Revision History:
//   01 April 2001: Modified to use new <boost/limits.hpp> header. (JMaddock)
//
#ifndef BOOST_GRAPH_GRAPH_SEARCH_VISITORS_HPP
#define BOOST_GRAPH_GRAPH_SEARCH_VISITORS_HPP

#include <iosfwd>
#include <boost/config.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/limits.hpp>

namespace boost
{

// This is a bit more convenient than std::numeric_limits because
// you don't have to explicitly provide type T.
template < class T > inline T numeric_limits_max(T)
{
    return (std::numeric_limits< T >::max)();
}

//========================================================================
// Event Tags

namespace detail
{
    // For partial specialization workaround
    enum event_visitor_enum
    {
        on_no_event_num,
        on_initialize_vertex_num,
        on_start_vertex_num,
        on_discover_vertex_num,
        on_finish_vertex_num,
        on_examine_vertex_num,
        on_examine_edge_num,
        on_tree_edge_num,
        on_non_tree_edge_num,
        on_gray_target_num,
        on_black_target_num,
        on_forward_or_cross_edge_num,
        on_back_edge_num,
        on_finish_edge_num,
        on_edge_relaxed_num,
        on_edge_not_relaxed_num,
        on_edge_minimized_num,
        on_edge_not_minimized_num
    };

    template < typename Event, typename Visitor >
    struct functor_to_visitor : Visitor
    {
        typedef Event event_filter;
        functor_to_visitor(const Visitor& visitor) : Visitor(visitor) {}
    };

} // namespace detail

struct on_no_event
{
    enum
    {
        num = detail::on_no_event_num
    };
};

struct on_initialize_vertex
{
    enum
    {
        num = detail::on_initialize_vertex_num
    };
};
struct on_start_vertex
{
    enum
    {
        num = detail::on_start_vertex_num
    };
};
struct on_discover_vertex
{
    enum
    {
        num = detail::on_discover_vertex_num
    };
};
struct on_examine_vertex
{
    enum
    {
        num = detail::on_examine_vertex_num
    };
};
struct on_finish_vertex
{
    enum
    {
        num = detail::on_finish_vertex_num
    };
};

struct on_examine_edge
{
    enum
    {
        num = detail::on_examine_edge_num
    };
};
struct on_tree_edge
{
    enum
    {
        num = detail::on_tree_edge_num
    };
};
struct on_non_tree_edge
{
    enum
    {
        num = detail::on_non_tree_edge_num
    };
};
struct on_gray_target
{
    enum
    {
        num = detail::on_gray_target_num
    };
};
struct on_black_target
{
    enum
    {
        num = detail::on_black_target_num
    };
};
struct on_forward_or_cross_edge
{
    enum
    {
        num = detail::on_forward_or_cross_edge_num
    };
};
struct on_back_edge
{
    enum
    {
        num = detail::on_back_edge_num
    };
};
struct on_finish_edge
{
    enum
    {
        num = detail::on_finish_edge_num
    };
};

struct on_edge_relaxed
{
    enum
    {
        num = detail::on_edge_relaxed_num
    };
};
struct on_edge_not_relaxed
{
    enum
    {
        num = detail::on_edge_not_relaxed_num
    };
};
struct on_edge_minimized
{
    enum
    {
        num = detail::on_edge_minimized_num
    };
};
struct on_edge_not_minimized
{
    enum
    {
        num = detail::on_edge_not_minimized_num
    };
};

//========================================================================
// base_visitor and null_visitor

// needed for MSVC workaround
template < class Visitor > struct base_visitor
{
    typedef on_no_event event_filter;
    template < class T, class Graph > void operator()(T, Graph&) {}
};

struct null_visitor : public base_visitor< null_visitor >
{
    typedef on_no_event event_filter;
    template < class T, class Graph > void operator()(T, Graph&) {}
};

//========================================================================
// The invoke_visitors() function

namespace detail
{
    template < class Visitor, class T, class Graph >
    inline void invoke_dispatch(Visitor& v, T x, Graph& g, mpl::true_)
    {
        v(x, g);
    }

    template < class Visitor, class T, class Graph >
    inline void invoke_dispatch(Visitor&, T, Graph&, mpl::false_)
    {
    }
} // namespace detail

template < class Visitor, class Rest, class T, class Graph, class Tag >
inline void invoke_visitors(
    std::pair< Visitor, Rest >& vlist, T x, Graph& g, Tag tag)
{
    typedef typename Visitor::event_filter Category;
    typedef typename is_same< Category, Tag >::type IsSameTag;
    detail::invoke_dispatch(vlist.first, x, g, IsSameTag());
    invoke_visitors(vlist.second, x, g, tag);
}
template < class Visitor, class T, class Graph, class Tag >
inline void invoke_visitors(Visitor& v, T x, Graph& g, Tag)
{
    typedef typename Visitor::event_filter Category;
    typedef typename is_same< Category, Tag >::type IsSameTag;
    detail::invoke_dispatch(v, x, g, IsSameTag());
}

//========================================================================
// predecessor_recorder

template < class PredecessorMap, class Tag >
struct predecessor_recorder
: public base_visitor< predecessor_recorder< PredecessorMap, Tag > >
{
    typedef Tag event_filter;
    predecessor_recorder(PredecessorMap pa) : m_predecessor(pa) {}
    template < class Edge, class Graph > void operator()(Edge e, const Graph& g)
    {
        put(m_predecessor, target(e, g), source(e, g));
    }
    PredecessorMap m_predecessor;
};
template < class PredecessorMap, class Tag >
predecessor_recorder< PredecessorMap, Tag > record_predecessors(
    PredecessorMap pa, Tag)
{
    return predecessor_recorder< PredecessorMap, Tag >(pa);
}

//========================================================================
// edge_predecessor_recorder

template < class PredEdgeMap, class Tag >
struct edge_predecessor_recorder
: public base_visitor< edge_predecessor_recorder< PredEdgeMap, Tag > >
{
    typedef Tag event_filter;
    edge_predecessor_recorder(PredEdgeMap pa) : m_predecessor(pa) {}
    template < class Edge, class Graph > void operator()(Edge e, const Graph& g)
    {
        put(m_predecessor, target(e, g), e);
    }
    PredEdgeMap m_predecessor;
};
template < class PredEdgeMap, class Tag >
edge_predecessor_recorder< PredEdgeMap, Tag > record_edge_predecessors(
    PredEdgeMap pa, Tag)
{
    return edge_predecessor_recorder< PredEdgeMap, Tag >(pa);
}

//========================================================================
// distance_recorder

template < class DistanceMap, class Tag >
struct distance_recorder
: public base_visitor< distance_recorder< DistanceMap, Tag > >
{
    typedef Tag event_filter;
    distance_recorder(DistanceMap pa) : m_distance(pa) {}
    template < class Edge, class Graph > void operator()(Edge e, const Graph& g)
    {
        typename graph_traits< Graph >::vertex_descriptor u = source(e, g),
                                                          v = target(e, g);
        put(m_distance, v, get(m_distance, u) + 1);
    }
    DistanceMap m_distance;
};
template < class DistanceMap, class Tag >
distance_recorder< DistanceMap, Tag > record_distances(DistanceMap pa, Tag)
{
    return distance_recorder< DistanceMap, Tag >(pa);
}

//========================================================================
// time_stamper

template < class TimeMap, class TimeT, class Tag >
struct time_stamper : public base_visitor< time_stamper< TimeMap, TimeT, Tag > >
{
    typedef Tag event_filter;
    time_stamper(TimeMap pa, TimeT& t) : m_time_pa(pa), m_time(t) {}
    template < class Vertex, class Graph >
    void operator()(Vertex u, const Graph&)
    {
        put(m_time_pa, u, ++m_time);
    }
    TimeMap m_time_pa;
    TimeT& m_time;
};
template < class TimeMap, class TimeT, class Tag >
time_stamper< TimeMap, TimeT, Tag > stamp_times(
    TimeMap pa, TimeT& time_counter, Tag)
{
    return time_stamper< TimeMap, TimeT, Tag >(pa, time_counter);
}

//========================================================================
// property_writer

template < class PA, class OutputIterator, class Tag >
struct property_writer
: public base_visitor< property_writer< PA, OutputIterator, Tag > >
{
    typedef Tag event_filter;

    property_writer(PA pa, OutputIterator out) : m_pa(pa), m_out(out) {}

    template < class T, class Graph > void operator()(T x, Graph&)
    {
        *m_out++ = get(m_pa, x);
    }
    PA m_pa;
    OutputIterator m_out;
};
template < class PA, class OutputIterator, class Tag >
property_writer< PA, OutputIterator, Tag > write_property(
    PA pa, OutputIterator out, Tag)
{
    return property_writer< PA, OutputIterator, Tag >(pa, out);
}

//========================================================================
// property_put

/**
 * Functor which just sets a given value to a vertex or edge in a property map.
 */

template < typename PropertyMap, typename EventTag > struct property_put
{
    typedef EventTag event_filter;

    property_put(PropertyMap property_map,
        typename property_traits< PropertyMap >::value_type value)
    : property_map_(property_map), value_(value)
    {
    }

    template < typename VertexOrEdge, typename Graph >
    void operator()(VertexOrEdge v, const Graph&)
    {
        put(property_map_, v, value_);
    }

private:
    PropertyMap property_map_;
    typename property_traits< PropertyMap >::value_type value_;
};

/**
 * Creates a property_put functor which just sets a given value to a vertex or
 * edge.
 *
 * @param property_map Given writeable property map
 * @param value Fixed value of the map
 * @param tag Event Filter
 * @return The functor.
 */

template < typename PropertyMap, typename EventTag >
inline property_put< PropertyMap, EventTag > put_property(
    PropertyMap property_map,
    typename property_traits< PropertyMap >::value_type value, EventTag)
{
    return property_put< PropertyMap, EventTag >(property_map, value);
}

#define BOOST_GRAPH_EVENT_STUB(Event, Kind)                                 \
    typedef ::boost::Event Event##_type;                                    \
    template < typename Visitor >                                           \
    Kind##_visitor< std::pair<                                              \
        detail::functor_to_visitor< Event##_type, Visitor >, Visitors > >   \
        do_##Event(Visitor visitor)                                         \
    {                                                                       \
        typedef std::pair<                                                  \
            detail::functor_to_visitor< Event##_type, Visitor >, Visitors > \
            visitor_list;                                                   \
        typedef Kind##_visitor< visitor_list > result_type;                 \
        return result_type(visitor_list(visitor, m_vis));                   \
    }

} /* namespace boost */

#endif

/* visitors.hpp
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
*/