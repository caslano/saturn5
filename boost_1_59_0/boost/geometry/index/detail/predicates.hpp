// Boost.Geometry Index
//
// Spatial query predicates definition and checks.
//
// Copyright (c) 2011-2015 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019-2021.
// Modifications copyright (c) 2019-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_PREDICATES_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_PREDICATES_HPP

#include <tuple>
#include <type_traits>
//#include <utility>

#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/index/detail/tags.hpp>

#include <boost/geometry/strategies/default_strategy.hpp>

namespace boost { namespace geometry { namespace index { namespace detail {

namespace predicates {

// ------------------------------------------------------------------ //
// predicates
// ------------------------------------------------------------------ //

template <typename Fun, bool IsFunction = std::is_function<Fun>::value>
struct satisfies_impl
{
    satisfies_impl() : fun(nullptr) {}
    satisfies_impl(Fun f) : fun(f) {}
    Fun * fun;
};

template <typename Fun>
struct satisfies_impl<Fun, false>
{
    satisfies_impl() = default;
    satisfies_impl(Fun const& f) : fun(f) {}
    Fun fun;
};

template <typename Fun, bool Negated>
struct satisfies : satisfies_impl<Fun>
{
    using base_t = satisfies_impl<Fun>;

    satisfies() = default;
    satisfies(Fun const& f) : base_t(f) {}
    satisfies(base_t const& b) : base_t(b) {}
};

// ------------------------------------------------------------------ //

struct contains_tag {};
struct covered_by_tag {};
struct covers_tag {};
struct disjoint_tag {};
struct intersects_tag {};
struct overlaps_tag {};
struct touches_tag {};
struct within_tag {};

template <typename Geometry, typename Tag, bool Negated>
struct spatial_predicate
{
    spatial_predicate() {}
    spatial_predicate(Geometry const& g) : geometry(g) {}
    Geometry geometry;
};

// ------------------------------------------------------------------ //

// CONSIDER: separated nearest<> and path<> may be replaced by
//           nearest_predicate<Geometry, Tag>
//           where Tag = point_tag | path_tag
// IMPROVEMENT: user-defined nearest predicate allowing to define
//              all or only geometrical aspects of the search

template <typename PointOrRelation>
struct nearest
{
    nearest()
//        : count(0)
    {}
    nearest(PointOrRelation const& por, std::size_t k)
        : point_or_relation(por)
        , count(k)
    {}
    PointOrRelation point_or_relation;
    std::size_t count;
};

template <typename SegmentOrLinestring>
struct path
{
    path()
//        : count(0)
    {}
    path(SegmentOrLinestring const& g, std::size_t k)
        : geometry(g)
        , count(k)
    {}
    SegmentOrLinestring geometry;
    std::size_t count;
};

} // namespace predicates

// ------------------------------------------------------------------ //
// predicate_check
// ------------------------------------------------------------------ //

template <typename Predicate, typename Tag>
struct predicate_check
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Predicate or Tag.",
        Predicate, Tag);
};

// ------------------------------------------------------------------ //

template <typename Fun>
struct predicate_check<predicates::satisfies<Fun, false>, value_tag>
{
    template <typename Value, typename Indexable, typename Strategy>
    static inline bool apply(predicates::satisfies<Fun, false> const& p, Value const& v, Indexable const& , Strategy const&)
    {
        return p.fun(v);
    }
};

template <typename Fun>
struct predicate_check<predicates::satisfies<Fun, true>, value_tag>
{
    template <typename Value, typename Indexable, typename Strategy>
    static inline bool apply(predicates::satisfies<Fun, true> const& p, Value const& v, Indexable const& , Strategy const&)
    {
        return !p.fun(v);
    }
};

// ------------------------------------------------------------------ //

template <typename Tag>
struct spatial_predicate_call
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Tag.",
        Tag);
};

template <>
struct spatial_predicate_call<predicates::contains_tag>
{
    template <typename G1, typename G2, typename S>
    static inline bool apply(G1 const& g1, G2 const& g2, S const&)
    {
        return geometry::within(g2, g1);
    }
};

template <>
struct spatial_predicate_call<predicates::covered_by_tag>
{
    template <typename G1, typename G2, typename S>
    static inline bool apply(G1 const& g1, G2 const& g2, S const&)
    {
        return geometry::covered_by(g1, g2);
    }
};

template <>
struct spatial_predicate_call<predicates::covers_tag>
{
    template <typename G1, typename G2, typename S>
    static inline bool apply(G1 const& g1, G2 const& g2, S const&)
    {
        return geometry::covered_by(g2, g1);
    }
};

template <>
struct spatial_predicate_call<predicates::disjoint_tag>
{
    template <typename G1, typename G2, typename S>
    static inline bool apply(G1 const& g1, G2 const& g2, S const&)
    {
        return geometry::disjoint(g1, g2);
    }
};

// TEMP: used to implement CS-specific intersects predicate for certain
// combinations of geometries until umbrella strategies are implemented
template
<
    typename G1, typename G2,
    typename Tag1 = typename tag<G1>::type,
    typename Tag2 = typename tag<G2>::type
>
struct spatial_predicate_intersects
{
    template <typename S>
    static inline bool apply(G1 const& g1, G2 const& g2, S const&)
    {
        return geometry::intersects(g1, g2);
    }
};
// TEMP: used in within and relate
template <typename G1, typename G2>
struct spatial_predicate_intersects<G1, G2, box_tag, point_tag>
{
    static inline bool apply(G1 const& g1, G2 const& g2, default_strategy const&)
    {
        return geometry::intersects(g1, g2);
    }

    template <typename S>
    static inline bool apply(G1 const& g1, G2 const& g2, S const& s)
    {
        return geometry::intersects(g1, g2, s);
    }
};

template <>
struct spatial_predicate_call<predicates::intersects_tag>
{
    template <typename G1, typename G2, typename S>
    static inline bool apply(G1 const& g1, G2 const& g2, S const& s)
    {
        return spatial_predicate_intersects<G1, G2>::apply(g1, g2, s);
    }
};

template <>
struct spatial_predicate_call<predicates::overlaps_tag>
{
    template <typename G1, typename G2, typename S>
    static inline bool apply(G1 const& g1, G2 const& g2, S const&)
    {
        return geometry::overlaps(g1, g2);
    }
};

template <>
struct spatial_predicate_call<predicates::touches_tag>
{
    template <typename G1, typename G2, typename S>
    static inline bool apply(G1 const& g1, G2 const& g2, S const&)
    {
        return geometry::touches(g1, g2);
    }
};

template <>
struct spatial_predicate_call<predicates::within_tag>
{
    template <typename G1, typename G2, typename S>
    static inline bool apply(G1 const& g1, G2 const& g2, S const&)
    {
        return geometry::within(g1, g2);
    }
};

// ------------------------------------------------------------------ //

// spatial predicate
template <typename Geometry, typename Tag>
struct predicate_check<predicates::spatial_predicate<Geometry, Tag, false>, value_tag>
{
    typedef predicates::spatial_predicate<Geometry, Tag, false> Pred;

    template <typename Value, typename Indexable, typename Strategy>
    static inline bool apply(Pred const& p, Value const&, Indexable const& i, Strategy const& s)
    {
        return spatial_predicate_call<Tag>::apply(i, p.geometry, s);
    }
};

// negated spatial predicate
template <typename Geometry, typename Tag>
struct predicate_check<predicates::spatial_predicate<Geometry, Tag, true>, value_tag>
{
    typedef predicates::spatial_predicate<Geometry, Tag, true> Pred;

    template <typename Value, typename Indexable, typename Strategy>
    static inline bool apply(Pred const& p, Value const&, Indexable const& i, Strategy const& s)
    {
        return !spatial_predicate_call<Tag>::apply(i, p.geometry, s);
    }
};

// ------------------------------------------------------------------ //

template <typename DistancePredicates>
struct predicate_check<predicates::nearest<DistancePredicates>, value_tag>
{
    template <typename Value, typename Box, typename Strategy>
    static inline bool apply(predicates::nearest<DistancePredicates> const&, Value const&, Box const&, Strategy const&)
    {
        return true;
    }
};

template <typename Linestring>
struct predicate_check<predicates::path<Linestring>, value_tag>
{
    template <typename Value, typename Box, typename Strategy>
    static inline bool apply(predicates::path<Linestring> const&, Value const&, Box const&, Strategy const&)
    {
        return true;
    }
};

// ------------------------------------------------------------------ //
// predicates_check for bounds
// ------------------------------------------------------------------ //

template <typename Fun, bool Negated>
struct predicate_check<predicates::satisfies<Fun, Negated>, bounds_tag>
{
    template <typename Value, typename Box, typename Strategy>
    static bool apply(predicates::satisfies<Fun, Negated> const&, Value const&, Box const&, Strategy const&)
    {
        return true;
    }
};

// ------------------------------------------------------------------ //

// NOT NEGATED
// value_tag        bounds_tag
// ---------------------------
// contains(I,G)    covers(I,G)
// covered_by(I,G)  intersects(I,G)
// covers(I,G)      covers(I,G)
// disjoint(I,G)    !covered_by(I,G)
// intersects(I,G)  intersects(I,G)
// overlaps(I,G)    intersects(I,G)  - possibly change to the version without border case, e.g. intersects_without_border(0,0x1,1, 1,1x2,2) should give false
// touches(I,G)     intersects(I,G)
// within(I,G)      intersects(I,G)  - possibly change to the version without border case, e.g. intersects_without_border(0,0x1,1, 1,1x2,2) should give false

// spatial predicate - default
template <typename Geometry, typename Tag>
struct predicate_check<predicates::spatial_predicate<Geometry, Tag, false>, bounds_tag>
{
    typedef predicates::spatial_predicate<Geometry, Tag, false> Pred;

    template <typename Value, typename Indexable, typename Strategy>
    static inline bool apply(Pred const& p, Value const&, Indexable const& i, Strategy const& s)
    {
        return spatial_predicate_call<predicates::intersects_tag>::apply(i, p.geometry, s);
    }
};

// spatial predicate - contains
template <typename Geometry>
struct predicate_check<predicates::spatial_predicate<Geometry, predicates::contains_tag, false>, bounds_tag>
{
    typedef predicates::spatial_predicate<Geometry, predicates::contains_tag, false> Pred;

    template <typename Value, typename Indexable, typename Strategy>
    static inline bool apply(Pred const& p, Value const&, Indexable const& i, Strategy const& s)
    {
        return spatial_predicate_call<predicates::covers_tag>::apply(i, p.geometry, s);
    }
};

// spatial predicate - covers
template <typename Geometry>
struct predicate_check<predicates::spatial_predicate<Geometry, predicates::covers_tag, false>, bounds_tag>
{
    typedef predicates::spatial_predicate<Geometry, predicates::covers_tag, false> Pred;

    template <typename Value, typename Indexable, typename Strategy>
    static inline bool apply(Pred const& p, Value const&, Indexable const& i, Strategy const& s)
    {
        return spatial_predicate_call<predicates::covers_tag>::apply(i, p.geometry, s);
    }
};

// spatial predicate - disjoint
template <typename Geometry>
struct predicate_check<predicates::spatial_predicate<Geometry, predicates::disjoint_tag, false>, bounds_tag>
{
    typedef predicates::spatial_predicate<Geometry, predicates::disjoint_tag, false> Pred;

    template <typename Value, typename Indexable, typename Strategy>
    static inline bool apply(Pred const& p, Value const&, Indexable const& i, Strategy const& s)
    {
        return !spatial_predicate_call<predicates::covered_by_tag>::apply(i, p.geometry, s);
    }
};

// NEGATED
// value_tag        bounds_tag
// ---------------------------
// !contains(I,G)   TRUE
// !covered_by(I,G) !covered_by(I,G)
// !covers(I,G)     TRUE
// !disjoint(I,G)   !disjoint(I,G)
// !intersects(I,G) !covered_by(I,G)
// !overlaps(I,G)   TRUE
// !touches(I,G)    !intersects(I,G)
// !within(I,G)     !within(I,G)

// negated spatial predicate - default
template <typename Geometry, typename Tag>
struct predicate_check<predicates::spatial_predicate<Geometry, Tag, true>, bounds_tag>
{
    typedef predicates::spatial_predicate<Geometry, Tag, true> Pred;

    template <typename Value, typename Indexable, typename Strategy>
    static inline bool apply(Pred const& p, Value const&, Indexable const& i, Strategy const& s)
    {
        return !spatial_predicate_call<Tag>::apply(i, p.geometry, s);
    }
};

// negated spatial predicate - contains
template <typename Geometry>
struct predicate_check<predicates::spatial_predicate<Geometry, predicates::contains_tag, true>, bounds_tag>
{
    typedef predicates::spatial_predicate<Geometry, predicates::contains_tag, true> Pred;

    template <typename Value, typename Indexable, typename Strategy>
    static inline bool apply(Pred const& , Value const&, Indexable const&, Strategy const&)
    {
        return true;
    }
};

// negated spatial predicate - covers
template <typename Geometry>
struct predicate_check<predicates::spatial_predicate<Geometry, predicates::covers_tag, true>, bounds_tag>
{
    typedef predicates::spatial_predicate<Geometry, predicates::covers_tag, true> Pred;

    template <typename Value, typename Indexable, typename Strategy>
    static inline bool apply(Pred const& , Value const&, Indexable const&, Strategy const&)
    {
        return true;
    }
};

// negated spatial predicate - intersects
template <typename Geometry>
struct predicate_check<predicates::spatial_predicate<Geometry, predicates::intersects_tag, true>, bounds_tag>
{
    typedef predicates::spatial_predicate<Geometry, predicates::intersects_tag, true> Pred;

    template <typename Value, typename Indexable, typename Strategy>
    static inline bool apply(Pred const& p, Value const&, Indexable const& i, Strategy const& s)
    {
        return !spatial_predicate_call<predicates::covered_by_tag>::apply(i, p.geometry, s);
    }
};

// negated spatial predicate - overlaps
template <typename Geometry>
struct predicate_check<predicates::spatial_predicate<Geometry, predicates::overlaps_tag, true>, bounds_tag>
{
    typedef predicates::spatial_predicate<Geometry, predicates::overlaps_tag, true> Pred;

    template <typename Value, typename Indexable, typename Strategy>
    static inline bool apply(Pred const& , Value const&, Indexable const&, Strategy const&)
    {
        return true;
    }
};

// negated spatial predicate - touches
template <typename Geometry>
struct predicate_check<predicates::spatial_predicate<Geometry, predicates::touches_tag, true>, bounds_tag>
{
    typedef predicates::spatial_predicate<Geometry, predicates::touches_tag, true> Pred;

    template <typename Value, typename Indexable, typename Strategy>
    static inline bool apply(Pred const& p, Value const&, Indexable const& i, Strategy const&)
    {
        return !spatial_predicate_call<predicates::intersects_tag>::apply(i, p.geometry);
    }
};

// ------------------------------------------------------------------ //

template <typename DistancePredicates>
struct predicate_check<predicates::nearest<DistancePredicates>, bounds_tag>
{
    template <typename Value, typename Box, typename Strategy>
    static inline bool apply(predicates::nearest<DistancePredicates> const&, Value const&, Box const&, Strategy const&)
    {
        return true;
    }
};

template <typename Linestring>
struct predicate_check<predicates::path<Linestring>, bounds_tag>
{
    template <typename Value, typename Box, typename Strategy>
    static inline bool apply(predicates::path<Linestring> const&, Value const&, Box const&, Strategy const&)
    {
        return true;
    }
};

// ------------------------------------------------------------------ //
// predicates_length
// ------------------------------------------------------------------ //

template <typename T>
struct predicates_length
{
    static const std::size_t value = 1;
};

template <typename ...Ts>
struct predicates_length<std::tuple<Ts...>>
{
    static const std::size_t value = std::tuple_size<std::tuple<Ts...>>::value;
};

// ------------------------------------------------------------------ //
// predicates_element
// ------------------------------------------------------------------ //

template <std::size_t I, typename T>
struct predicates_element
{
    BOOST_GEOMETRY_STATIC_ASSERT((I < 1),
        "Invalid I index.",
        std::integral_constant<std::size_t, I>);

    typedef T type;
    static type const& get(T const& p) { return p; }
};

template <std::size_t I, typename ...Ts>
struct predicates_element<I, std::tuple<Ts...>>
{
    typedef std::tuple<Ts...> predicate_type;

    typedef typename std::tuple_element<I, predicate_type>::type type;
    static type const& get(predicate_type const& p) { return std::get<I>(p); }
};

// ------------------------------------------------------------------ //
// predicates_check
// ------------------------------------------------------------------ //

template <typename TuplePredicates, typename Tag, std::size_t First, std::size_t Last>
struct predicates_check_tuple
{
    template <typename Value, typename Indexable, typename Strategy>
    static inline bool apply(TuplePredicates const& p, Value const& v, Indexable const& i, Strategy const& s)
    {
        return predicate_check
                <
                    typename std::tuple_element<First, TuplePredicates>::type,
                    Tag
                >::apply(std::get<First>(p), v, i, s)
            && predicates_check_tuple<TuplePredicates, Tag, First+1, Last>::apply(p, v, i, s);
    }
};

template <typename TuplePredicates, typename Tag, std::size_t First>
struct predicates_check_tuple<TuplePredicates, Tag, First, First>
{
    template <typename Value, typename Indexable, typename Strategy>
    static inline bool apply(TuplePredicates const& , Value const& , Indexable const& , Strategy const& )
    {
        return true;
    }
};

template <typename Predicate, typename Tag, std::size_t First, std::size_t Last>
struct predicates_check_impl
{
    static const bool check = First < 1 && Last <= 1 && First <= Last;
    BOOST_GEOMETRY_STATIC_ASSERT((check),
        "Invalid First or Last index.",
        std::integer_sequence<std::size_t, First, Last>);

    template <typename Value, typename Indexable, typename Strategy>
    static inline bool apply(Predicate const& p, Value const& v, Indexable const& i, Strategy const& s)
    {
        return predicate_check<Predicate, Tag>::apply(p, v, i, s);
    }
};

template <typename ...Ts, typename Tag, std::size_t First, std::size_t Last>
struct predicates_check_impl<std::tuple<Ts...>, Tag, First, Last>
{
    typedef std::tuple<Ts...> predicates_type;

    static const std::size_t pred_len = std::tuple_size<predicates_type>::value;
    static const bool check = First < pred_len && Last <= pred_len && First <= Last;
    BOOST_GEOMETRY_STATIC_ASSERT((check),
        "Invalid First or Last index.",
        std::integer_sequence<std::size_t, First, Last>);

    template <typename Value, typename Indexable, typename Strategy>
    static inline bool apply(predicates_type const& p, Value const& v, Indexable const& i, Strategy const& s)
    {
        return predicates_check_tuple
                <
                    predicates_type,
                    Tag, First, Last
                >::apply(p, v, i, s);
    }
};

template <typename Tag, typename Predicates, typename Value, typename Indexable, typename Strategy>
inline bool predicates_check(Predicates const& p, Value const& v, Indexable const& i, Strategy const& s)
{
    return detail::predicates_check_impl
        <
            Predicates, Tag, 0, predicates_length<Predicates>::value
        >::apply(p, v, i, s);
}

// ------------------------------------------------------------------ //
// nearest predicate helpers
// ------------------------------------------------------------------ //

// predicates_is_nearest

template <typename P>
struct predicates_is_distance
{
    static const std::size_t value = 0;
};

template <typename DistancePredicates>
struct predicates_is_distance< predicates::nearest<DistancePredicates> >
{
    static const std::size_t value = 1;
};

template <typename Linestring>
struct predicates_is_distance< predicates::path<Linestring> >
{
    static const std::size_t value = 1;
};

// predicates_count_nearest

template <typename T>
struct predicates_count_distance
{
    static const std::size_t value = predicates_is_distance<T>::value;
};

template <typename Tuple, std::size_t N>
struct predicates_count_distance_tuple
{
    static const std::size_t value =
        predicates_is_distance<typename std::tuple_element<N-1, Tuple>::type>::value
        + predicates_count_distance_tuple<Tuple, N-1>::value;
};

template <typename Tuple>
struct predicates_count_distance_tuple<Tuple, 1>
{
    static const std::size_t value =
        predicates_is_distance<typename std::tuple_element<0, Tuple>::type>::value;
};

template <typename ...Ts>
struct predicates_count_distance<std::tuple<Ts...>>
{
    static const std::size_t value = predicates_count_distance_tuple<
        std::tuple<Ts...>,
        std::tuple_size<std::tuple<Ts...>>::value
    >::value;
};

// predicates_find_nearest

template <typename T>
struct predicates_find_distance
{
    static const std::size_t value = predicates_is_distance<T>::value ? 0 : 1;
};

template <typename Tuple, std::size_t N>
struct predicates_find_distance_tuple
{
    static const bool is_found = predicates_find_distance_tuple<Tuple, N-1>::is_found
                                || predicates_is_distance<typename std::tuple_element<N-1, Tuple>::type>::value;

    static const std::size_t value = predicates_find_distance_tuple<Tuple, N-1>::is_found ?
        predicates_find_distance_tuple<Tuple, N-1>::value :
        (predicates_is_distance<typename std::tuple_element<N-1, Tuple>::type>::value ?
            N-1 : std::tuple_size<Tuple>::value);
};

template <typename Tuple>
struct predicates_find_distance_tuple<Tuple, 1>
{
    static const bool is_found = predicates_is_distance<typename std::tuple_element<0, Tuple>::type>::value;
    static const std::size_t value = is_found ? 0 : std::tuple_size<Tuple>::value;
};

template <typename ...Ts>
struct predicates_find_distance<std::tuple<Ts...>>
{
    static const std::size_t value = predicates_find_distance_tuple<
        std::tuple<Ts...>,
        std::tuple_size<std::tuple<Ts...>>::value
    >::value;
};

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_PREDICATES_HPP

/* predicates.hpp
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
*/