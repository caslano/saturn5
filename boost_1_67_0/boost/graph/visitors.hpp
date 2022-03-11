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