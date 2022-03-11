// Boost.Geometry Index
//
// Spatial index distance predicates, calculators and checkers
// used in nearest query - specialized for envelopes
//
// Copyright (c) 2011-2015 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019.
// Modifications copyright (c) 2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_DISTANCE_PREDICATES_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_DISTANCE_PREDICATES_HPP

#include <boost/geometry/index/detail/algorithms/comparable_distance_near.hpp>
#include <boost/geometry/index/detail/algorithms/comparable_distance_far.hpp>
#include <boost/geometry/index/detail/algorithms/comparable_distance_centroid.hpp>
#include <boost/geometry/index/detail/algorithms/path_intersection.hpp>

#include <boost/geometry/index/detail/tags.hpp>

namespace boost { namespace geometry { namespace index { namespace detail {

// ------------------------------------------------------------------ //
// relations
// ------------------------------------------------------------------ //

template <typename T>
struct to_nearest
{
    to_nearest(T const& v) : value(v) {}
    T value;
};

template <typename T>
struct to_centroid
{
    to_centroid(T const& v) : value(v) {}
    T value;
};

template <typename T>
struct to_furthest
{
    to_furthest(T const& v) : value(v) {}
    T value;
};

// tags

struct to_nearest_tag {};
struct to_centroid_tag {};
struct to_furthest_tag {};

// ------------------------------------------------------------------ //
// relation traits and access
// ------------------------------------------------------------------ //

template <typename T>
struct relation
{
    typedef T value_type;
    typedef to_nearest_tag tag;
    static inline T const& value(T const& v) { return v; }
    static inline T & value(T & v) { return v; }
};

template <typename T>
struct relation< to_nearest<T> >
{
    typedef T value_type;
    typedef to_nearest_tag tag;
    static inline T const& value(to_nearest<T> const& r) { return r.value; }
    static inline T & value(to_nearest<T> & r) { return r.value; }
};

template <typename T>
struct relation< to_centroid<T> >
{
    typedef T value_type;
    typedef to_centroid_tag tag;
    static inline T const& value(to_centroid<T> const& r) { return r.value; }
    static inline T & value(to_centroid<T> & r) { return r.value; }
};

template <typename T>
struct relation< to_furthest<T> >
{
    typedef T value_type;
    typedef to_furthest_tag tag;
    static inline T const& value(to_furthest<T> const& r) { return r.value; }
    static inline T & value(to_furthest<T> & r) { return r.value; }
};

// ------------------------------------------------------------------ //

template
<
    typename G1, typename G2, typename Strategy,
    typename Tag1 = typename geometry::tag<G1>::type,
    typename Tag2 = typename geometry::tag<G2>::type
>
struct comparable_distance_call_base
{
    typedef typename geometry::default_comparable_distance_result
        <
            G1, G2
        >::type result_type;

    static inline result_type apply(G1 const& g1, G2 const& g2, Strategy const&)
    {
        return geometry::comparable_distance(g1, g2);
    }
};

template
<
    typename G1, typename G2, typename Strategy
>
struct comparable_distance_call_base<G1, G2, Strategy, point_tag, point_tag>
{
    typedef typename geometry::comparable_distance_result
        <
            G1, G2,
            typename Strategy::comparable_distance_point_point_strategy_type
        >::type result_type;

    static inline result_type apply(G1 const& g1, G2 const& g2, Strategy const& s)
    {
        return geometry::comparable_distance(g1, g2,
                s.get_comparable_distance_point_point_strategy());
    }
};

template
<
    typename G1, typename G2, typename Strategy
>
struct comparable_distance_call_base<G1, G2, Strategy, point_tag, box_tag>
{
    typedef typename geometry::comparable_distance_result
        <
            G1, G2,
            typename Strategy::comparable_distance_point_box_strategy_type
        >::type result_type;

    static inline result_type apply(G1 const& g1, G2 const& g2, Strategy const& s)
    {
        return geometry::comparable_distance(g1, g2,
                s.get_comparable_distance_point_box_strategy());
    }
};

template
<
    typename G1, typename G2, typename Strategy
>
struct comparable_distance_call_base<G1, G2, Strategy, segment_tag, point_tag>
{
    typedef typename geometry::comparable_distance_result
        <
            G1, G2,
            typename Strategy::comparable_distance_point_segment_strategy_type
        >::type result_type;

    static inline result_type apply(G1 const& g1, G2 const& g2, Strategy const& s)
    {
        return geometry::comparable_distance(g1, g2,
                s.get_comparable_distance_point_segment_strategy());
    }
};

template
<
    typename G1, typename G2, typename Strategy
>
struct comparable_distance_call_base<G1, G2, Strategy, segment_tag, box_tag>
{
    typedef typename geometry::comparable_distance_result
        <
            G1, G2,
            typename Strategy::comparable_distance_segment_box_strategy_type
        >::type result_type;

    static inline result_type apply(G1 const& g1, G2 const& g2, Strategy const& s)
    {
        return geometry::comparable_distance(g1, g2,
                s.get_comparable_distance_segment_box_strategy());
    }
};

template
<
    typename G1, typename G2, typename Strategy
>
struct comparable_distance_call_base<G1, G2, Strategy, segment_tag, segment_tag>
{
    typedef typename geometry::comparable_distance_result
        <
            G1, G2,
            typename Strategy::comparable_distance_point_segment_strategy_type
        >::type result_type;

    static inline result_type apply(G1 const& g1, G2 const& g2, Strategy const& s)
    {
        return geometry::comparable_distance(g1, g2,
                s.get_comparable_distance_point_segment_strategy());
    }
};

template
<
    typename G1, typename G2, typename Strategy
>
struct comparable_distance_call
    : comparable_distance_call_base<G1, G2, Strategy>
{};

template
<
    typename G1, typename G2
>
struct comparable_distance_call<G1, G2, default_strategy>
    : comparable_distance_call_base<G1, G2, default_strategy, void, void>
{};

// ------------------------------------------------------------------ //
// calculate_distance
// ------------------------------------------------------------------ //

template <typename Predicate, typename Indexable, typename Strategy, typename Tag>
struct calculate_distance
{
    BOOST_MPL_ASSERT_MSG((false), INVALID_PREDICATE_OR_TAG, (calculate_distance));
};

// this handles nearest() with default Point parameter, to_nearest() and bounds
template <typename PointRelation, typename Indexable, typename Strategy, typename Tag>
struct calculate_distance< predicates::nearest<PointRelation>, Indexable, Strategy, Tag>
{
    typedef detail::relation<PointRelation> relation;
    typedef comparable_distance_call
        <
            typename relation::value_type,
            Indexable,
            Strategy
        > call_type;
    typedef typename call_type::result_type result_type;

    static inline bool apply(predicates::nearest<PointRelation> const& p, Indexable const& i,
                             Strategy const& s, result_type & result)
    {
        result = call_type::apply(relation::value(p.point_or_relation), i, s);
        return true;
    }
};

template <typename Point, typename Indexable, typename Strategy>
struct calculate_distance< predicates::nearest< to_centroid<Point> >, Indexable, Strategy, value_tag>
{
    typedef Point point_type;
    typedef typename geometry::default_comparable_distance_result
        <
            point_type, Indexable
        >::type result_type;

    static inline bool apply(predicates::nearest< to_centroid<Point> > const& p, Indexable const& i,
                             Strategy const& , result_type & result)
    {
        result = index::detail::comparable_distance_centroid(p.point_or_relation.value, i);
        return true;
    }
};

template <typename Point, typename Indexable, typename Strategy>
struct calculate_distance< predicates::nearest< to_furthest<Point> >, Indexable, Strategy, value_tag>
{
    typedef Point point_type;
    typedef typename geometry::default_comparable_distance_result
        <
            point_type, Indexable
        >::type result_type;

    static inline bool apply(predicates::nearest< to_furthest<Point> > const& p, Indexable const& i,
                             Strategy const& , result_type & result)
    {
        result = index::detail::comparable_distance_far(p.point_or_relation.value, i);
        return true;
    }
};

template <typename SegmentOrLinestring, typename Indexable, typename Strategy, typename Tag>
struct calculate_distance< predicates::path<SegmentOrLinestring>, Indexable, Strategy, Tag>
{
    typedef typename index::detail::default_path_intersection_distance_type<
        Indexable, SegmentOrLinestring
    >::type result_type;

    static inline bool apply(predicates::path<SegmentOrLinestring> const& p, Indexable const& i,
                             Strategy const& , result_type & result)
    {
        return index::detail::path_intersection(i, p.geometry, result);
    }
};

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_RTREE_DISTANCE_PREDICATES_HPP

/* distance_predicates.hpp
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
*/