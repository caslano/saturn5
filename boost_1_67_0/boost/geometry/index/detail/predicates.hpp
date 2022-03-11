// Boost.Geometry Index
//
// Spatial query predicates definition and checks.
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

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_PREDICATES_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_PREDICATES_HPP

//#include <utility>

#include <boost/mpl/assert.hpp>
#include <boost/tuple/tuple.hpp>

#include <boost/geometry/index/detail/tags.hpp>

namespace boost { namespace geometry { namespace index { namespace detail {

namespace predicates {

// ------------------------------------------------------------------ //
// predicates
// ------------------------------------------------------------------ //

template <typename Fun, bool IsFunction>
struct satisfies_impl
{
    satisfies_impl() : fun(NULL) {}
    satisfies_impl(Fun f) : fun(f) {}
    Fun * fun;
};

template <typename Fun>
struct satisfies_impl<Fun, false>
{
    satisfies_impl() {}
    satisfies_impl(Fun const& f) : fun(f) {}
    Fun fun;
};

template <typename Fun, bool Negated>
struct satisfies
    : satisfies_impl<Fun, ::boost::is_function<Fun>::value>
{
    typedef satisfies_impl<Fun, ::boost::is_function<Fun>::value> base;

    satisfies() {}
    satisfies(Fun const& f) : base(f) {}
    satisfies(base const& b) : base(b) {}
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
    nearest(PointOrRelation const& por, unsigned k)
        : point_or_relation(por)
        , count(k)
    {}
    PointOrRelation point_or_relation;
    unsigned count;
};

template <typename SegmentOrLinestring>
struct path
{
    path()
//        : count(0)
    {}
    path(SegmentOrLinestring const& g, unsigned k)
        : geometry(g)
        , count(k)
    {}
    SegmentOrLinestring geometry;
    unsigned count;
};

} // namespace predicates

// ------------------------------------------------------------------ //
// predicate_check
// ------------------------------------------------------------------ //

template <typename Predicate, typename Tag>
struct predicate_check
{
    BOOST_MPL_ASSERT_MSG(
        (false),
        NOT_IMPLEMENTED_FOR_THIS_PREDICATE_OR_TAG,
        (predicate_check));
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
    BOOST_MPL_ASSERT_MSG(false, NOT_IMPLEMENTED_FOR_THIS_TAG, (Tag));
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
    static inline bool apply(G1 const& g1, G2 const& g2, S const& )
    {
        return geometry::intersects(g1, g2, typename S::covered_by_point_box_strategy_type());
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
    static const unsigned value = 1;
};

//template <typename F, typename S>
//struct predicates_length< std::pair<F, S> >
//{
//    static const unsigned value = 2;
//};

//template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
//struct predicates_length< boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> >
//{
//    static const unsigned value = boost::tuples::length< boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> >::value;
//};

template <typename Head, typename Tail>
struct predicates_length< boost::tuples::cons<Head, Tail> >
{
    static const unsigned value = boost::tuples::length< boost::tuples::cons<Head, Tail> >::value;
};

// ------------------------------------------------------------------ //
// predicates_element
// ------------------------------------------------------------------ //

template <unsigned I, typename T>
struct predicates_element
{
    BOOST_MPL_ASSERT_MSG((I < 1), INVALID_INDEX, (predicates_element));
    typedef T type;
    static type const& get(T const& p) { return p; }
};

//template <unsigned I, typename F, typename S>
//struct predicates_element< I, std::pair<F, S> >
//{
//    BOOST_MPL_ASSERT_MSG((I < 2), INVALID_INDEX, (predicates_element));
//
//    typedef F type;
//    static type const& get(std::pair<F, S> const& p) { return p.first; }
//};
//
//template <typename F, typename S>
//struct predicates_element< 1, std::pair<F, S> >
//{
//    typedef S type;
//    static type const& get(std::pair<F, S> const& p) { return p.second; }
//};
//
//template <unsigned I, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
//struct predicates_element< I, boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> >
//{
//    typedef boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> predicate_type;
//
//    typedef typename boost::tuples::element<I, predicate_type>::type type;
//    static type const& get(predicate_type const& p) { return boost::get<I>(p); }
//};

template <unsigned I, typename Head, typename Tail>
struct predicates_element< I, boost::tuples::cons<Head, Tail> >
{
    typedef boost::tuples::cons<Head, Tail> predicate_type;

    typedef typename boost::tuples::element<I, predicate_type>::type type;
    static type const& get(predicate_type const& p) { return boost::get<I>(p); }
};

// ------------------------------------------------------------------ //
// predicates_check
// ------------------------------------------------------------------ //

//template <typename PairPredicates, typename Tag, unsigned First, unsigned Last>
//struct predicates_check_pair {};
//
//template <typename PairPredicates, typename Tag, unsigned I>
//struct predicates_check_pair<PairPredicates, Tag, I, I>
//{
//    template <typename Value, typename Indexable>
//    static inline bool apply(PairPredicates const& , Value const& , Indexable const& )
//    {
//        return true;
//    }
//};
//
//template <typename PairPredicates, typename Tag>
//struct predicates_check_pair<PairPredicates, Tag, 0, 1>
//{
//    template <typename Value, typename Indexable>
//    static inline bool apply(PairPredicates const& p, Value const& v, Indexable const& i)
//    {
//        return predicate_check<typename PairPredicates::first_type, Tag>::apply(p.first, v, i);
//    }
//};
//
//template <typename PairPredicates, typename Tag>
//struct predicates_check_pair<PairPredicates, Tag, 1, 2>
//{
//    template <typename Value, typename Indexable>
//    static inline bool apply(PairPredicates const& p, Value const& v, Indexable const& i)
//    {
//        return predicate_check<typename PairPredicates::second_type, Tag>::apply(p.second, v, i);
//    }
//};
//
//template <typename PairPredicates, typename Tag>
//struct predicates_check_pair<PairPredicates, Tag, 0, 2>
//{
//    template <typename Value, typename Indexable>
//    static inline bool apply(PairPredicates const& p, Value const& v, Indexable const& i)
//    {
//        return predicate_check<typename PairPredicates::first_type, Tag>::apply(p.first, v, i)
//            && predicate_check<typename PairPredicates::second_type, Tag>::apply(p.second, v, i);
//    }
//};

template <typename TuplePredicates, typename Tag, unsigned First, unsigned Last>
struct predicates_check_tuple
{
    template <typename Value, typename Indexable, typename Strategy>
    static inline bool apply(TuplePredicates const& p, Value const& v, Indexable const& i, Strategy const& s)
    {
        return predicate_check
                <
                    typename boost::tuples::element<First, TuplePredicates>::type,
                    Tag
                >::apply(boost::get<First>(p), v, i, s)
            && predicates_check_tuple<TuplePredicates, Tag, First+1, Last>::apply(p, v, i, s);
    }
};

template <typename TuplePredicates, typename Tag, unsigned First>
struct predicates_check_tuple<TuplePredicates, Tag, First, First>
{
    template <typename Value, typename Indexable, typename Strategy>
    static inline bool apply(TuplePredicates const& , Value const& , Indexable const& , Strategy const& )
    {
        return true;
    }
};

template <typename Predicate, typename Tag, unsigned First, unsigned Last>
struct predicates_check_impl
{
    static const bool check = First < 1 && Last <= 1 && First <= Last;
    BOOST_MPL_ASSERT_MSG((check), INVALID_INDEXES, (predicates_check_impl));

    template <typename Value, typename Indexable, typename Strategy>
    static inline bool apply(Predicate const& p, Value const& v, Indexable const& i, Strategy const& s)
    {
        return predicate_check<Predicate, Tag>::apply(p, v, i, s);
    }
};

//template <typename Predicate1, typename Predicate2, typename Tag, size_t First, size_t Last>
//struct predicates_check_impl<std::pair<Predicate1, Predicate2>, Tag, First, Last>
//{
//    BOOST_MPL_ASSERT_MSG((First < 2 && Last <= 2 && First <= Last), INVALID_INDEXES, (predicates_check_impl));
//
//    template <typename Value, typename Indexable>
//    static inline bool apply(std::pair<Predicate1, Predicate2> const& p, Value const& v, Indexable const& i)
//    {
//        return predicate_check<Predicate1, Tag>::apply(p.first, v, i)
//            && predicate_check<Predicate2, Tag>::apply(p.second, v, i);
//    }
//};
//
//template <
//    typename T0, typename T1, typename T2, typename T3, typename T4,
//    typename T5, typename T6, typename T7, typename T8, typename T9,
//    typename Tag, unsigned First, unsigned Last
//>
//struct predicates_check_impl<
//    boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>,
//    Tag, First, Last
//>
//{
//    typedef boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> predicates_type;
//
//    static const unsigned pred_len = boost::tuples::length<predicates_type>::value;
//    BOOST_MPL_ASSERT_MSG((First < pred_len && Last <= pred_len && First <= Last), INVALID_INDEXES, (predicates_check_impl));
//
//    template <typename Value, typename Indexable>
//    static inline bool apply(predicates_type const& p, Value const& v, Indexable const& i)
//    {
//        return predicates_check_tuple<
//            predicates_type,
//            Tag, First, Last
//        >::apply(p, v, i);
//    }
//};

template <typename Head, typename Tail, typename Tag, unsigned First, unsigned Last>
struct predicates_check_impl<
    boost::tuples::cons<Head, Tail>,
    Tag, First, Last
>
{
    typedef boost::tuples::cons<Head, Tail> predicates_type;

    static const unsigned pred_len = boost::tuples::length<predicates_type>::value;
    static const bool check = First < pred_len && Last <= pred_len && First <= Last;
    BOOST_MPL_ASSERT_MSG((check), INVALID_INDEXES, (predicates_check_impl));

    template <typename Value, typename Indexable, typename Strategy>
    static inline bool apply(predicates_type const& p, Value const& v, Indexable const& i, Strategy const& s)
    {
        return predicates_check_tuple<
            predicates_type,
            Tag, First, Last
        >::apply(p, v, i, s);
    }
};

template <typename Tag, unsigned First, unsigned Last, typename Predicates, typename Value, typename Indexable, typename Strategy>
inline bool predicates_check(Predicates const& p, Value const& v, Indexable const& i, Strategy const& s)
{
    return detail::predicates_check_impl<Predicates, Tag, First, Last>
        ::apply(p, v, i, s);
}

// ------------------------------------------------------------------ //
// nearest predicate helpers
// ------------------------------------------------------------------ //

// predicates_is_nearest

template <typename P>
struct predicates_is_distance
{
    static const unsigned value = 0;
};

template <typename DistancePredicates>
struct predicates_is_distance< predicates::nearest<DistancePredicates> >
{
    static const unsigned value = 1;
};

template <typename Linestring>
struct predicates_is_distance< predicates::path<Linestring> >
{
    static const unsigned value = 1;
};

// predicates_count_nearest

template <typename T>
struct predicates_count_distance
{
    static const unsigned value = predicates_is_distance<T>::value;
};

//template <typename F, typename S>
//struct predicates_count_distance< std::pair<F, S> >
//{
//    static const unsigned value = predicates_is_distance<F>::value
//                                + predicates_is_distance<S>::value;
//};

template <typename Tuple, unsigned N>
struct predicates_count_distance_tuple
{
    static const unsigned value =
        predicates_is_distance<typename boost::tuples::element<N-1, Tuple>::type>::value
        + predicates_count_distance_tuple<Tuple, N-1>::value;
};

template <typename Tuple>
struct predicates_count_distance_tuple<Tuple, 1>
{
    static const unsigned value =
        predicates_is_distance<typename boost::tuples::element<0, Tuple>::type>::value;
};

//template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
//struct predicates_count_distance< boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> >
//{
//    static const unsigned value = predicates_count_distance_tuple<
//        boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>,
//        boost::tuples::length< boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> >::value
//    >::value;
//};

template <typename Head, typename Tail>
struct predicates_count_distance< boost::tuples::cons<Head, Tail> >
{
    static const unsigned value = predicates_count_distance_tuple<
        boost::tuples::cons<Head, Tail>,
        boost::tuples::length< boost::tuples::cons<Head, Tail> >::value
    >::value;
};

// predicates_find_nearest

template <typename T>
struct predicates_find_distance
{
    static const unsigned value = predicates_is_distance<T>::value ? 0 : 1;
};

//template <typename F, typename S>
//struct predicates_find_distance< std::pair<F, S> >
//{
//    static const unsigned value = predicates_is_distance<F>::value ? 0 :
//                                    (predicates_is_distance<S>::value ? 1 : 2);
//};

template <typename Tuple, unsigned N>
struct predicates_find_distance_tuple
{
    static const bool is_found = predicates_find_distance_tuple<Tuple, N-1>::is_found
                                || predicates_is_distance<typename boost::tuples::element<N-1, Tuple>::type>::value;

    static const unsigned value = predicates_find_distance_tuple<Tuple, N-1>::is_found ?
        predicates_find_distance_tuple<Tuple, N-1>::value :
        (predicates_is_distance<typename boost::tuples::element<N-1, Tuple>::type>::value ?
            N-1 : boost::tuples::length<Tuple>::value);
};

template <typename Tuple>
struct predicates_find_distance_tuple<Tuple, 1>
{
    static const bool is_found = predicates_is_distance<typename boost::tuples::element<0, Tuple>::type>::value;
    static const unsigned value = is_found ? 0 : boost::tuples::length<Tuple>::value;
};

//template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
//struct predicates_find_distance< boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> >
//{
//    static const unsigned value = predicates_find_distance_tuple<
//        boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>,
//        boost::tuples::length< boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> >::value
//    >::value;
//};

template <typename Head, typename Tail>
struct predicates_find_distance< boost::tuples::cons<Head, Tail> >
{
    static const unsigned value = predicates_find_distance_tuple<
        boost::tuples::cons<Head, Tail>,
        boost::tuples::length< boost::tuples::cons<Head, Tail> >::value
    >::value;
};

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_PREDICATES_HPP

/* predicates.hpp
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
*/