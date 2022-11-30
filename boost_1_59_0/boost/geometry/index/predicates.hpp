// Boost.Geometry Index
//
// Spatial query predicates
//
// Copyright (c) 2011-2018 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019-2021.
// Modifications copyright (c) 2019-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_PREDICATES_HPP
#define BOOST_GEOMETRY_INDEX_PREDICATES_HPP

#include <boost/geometry/index/detail/predicates.hpp>
#include <boost/geometry/util/tuples.hpp>

/*!
\defgroup predicates Predicates (boost::geometry::index::)
*/

namespace boost { namespace geometry { namespace index {

/*!
\brief Generate \c contains() predicate.

Generate a predicate defining Value and Geometry relationship. With this
predicate query returns indexed Values that contain passed Geometry.
Value is returned by the query if <tt>bg::within(Geometry, Indexable)</tt>
returns <tt>true</tt>.

\par Example
\verbatim
bgi::query(spatial_index, bgi::contains(box), std::back_inserter(result));
\endverbatim

\ingroup predicates

\tparam Geometry    The Geometry type.

\param g            The Geometry object.
*/
template <typename Geometry> inline
detail::predicates::spatial_predicate<Geometry, detail::predicates::contains_tag, false>
contains(Geometry const& g)
{
    return detail::predicates::spatial_predicate
                <
                    Geometry,
                    detail::predicates::contains_tag,
                    false
                >(g);
}

/*!
\brief Generate \c covered_by() predicate.

Generate a predicate defining Value and Geometry relationship. With this
predicate query returns indexed Values that are covered by passed Geometry.
Value is returned by the query if <tt>bg::covered_by(Indexable, Geometry)</tt>
returns <tt>true</tt>.

\par Example
\verbatim
bgi::query(spatial_index, bgi::covered_by(box), std::back_inserter(result));
\endverbatim

\ingroup predicates

\tparam Geometry    The Geometry type.

\param g            The Geometry object.
*/
template <typename Geometry> inline
detail::predicates::spatial_predicate<Geometry, detail::predicates::covered_by_tag, false>
covered_by(Geometry const& g)
{
    return detail::predicates::spatial_predicate
                <
                    Geometry,
                    detail::predicates::covered_by_tag,
                    false
                >(g);
}

/*!
\brief Generate \c covers() predicate.

Generate a predicate defining Value and Geometry relationship. With this
predicate query returns indexed Values that cover passed Geometry.
Value is returned by the query if <tt>bg::covered_by(Geometry, Indexable)</tt>
returns <tt>true</tt>.

\par Example
\verbatim
bgi::query(spatial_index, bgi::covers(box), std::back_inserter(result));
\endverbatim

\ingroup predicates

\tparam Geometry    The Geometry type.

\param g            The Geometry object.
*/
template <typename Geometry> inline
detail::predicates::spatial_predicate<Geometry, detail::predicates::covers_tag, false>
covers(Geometry const& g)
{
    return detail::predicates::spatial_predicate
                <
                    Geometry,
                    detail::predicates::covers_tag,
                    false
                >(g);
}

/*!
\brief Generate \c disjoint() predicate.

Generate a predicate defining Value and Geometry relationship. With this
predicate query returns indexed Values that are disjoint with passed Geometry.
Value is returned by the query if <tt>bg::disjoint(Indexable, Geometry)</tt>
returns <tt>true</tt>.

\par Example
\verbatim
bgi::query(spatial_index, bgi::disjoint(box), std::back_inserter(result));
\endverbatim

\ingroup predicates

\tparam Geometry    The Geometry type.

\param g            The Geometry object.
*/
template <typename Geometry> inline
detail::predicates::spatial_predicate<Geometry, detail::predicates::disjoint_tag, false>
disjoint(Geometry const& g)
{
    return detail::predicates::spatial_predicate
                <
                    Geometry,
                    detail::predicates::disjoint_tag,
                    false
                >(g);
}

/*!
\brief Generate \c intersects() predicate.

Generate a predicate defining Value and Geometry relationship. With this
predicate query returns indexed Values that intersect passed Geometry.
Value is returned by the query if <tt>bg::intersects(Indexable, Geometry)</tt>
returns <tt>true</tt>.

\par Example
\verbatim
bgi::query(spatial_index, bgi::intersects(box), std::back_inserter(result));
bgi::query(spatial_index, bgi::intersects(ring), std::back_inserter(result));
bgi::query(spatial_index, bgi::intersects(polygon), std::back_inserter(result));
\endverbatim

\ingroup predicates

\tparam Geometry    The Geometry type.

\param g            The Geometry object.
*/
template <typename Geometry> inline
detail::predicates::spatial_predicate<Geometry, detail::predicates::intersects_tag, false>
intersects(Geometry const& g)
{
    return detail::predicates::spatial_predicate
                <
                    Geometry,
                    detail::predicates::intersects_tag,
                    false
                >(g);
}

/*!
\brief Generate \c overlaps() predicate.

Generate a predicate defining Value and Geometry relationship. With this
predicate query returns indexed Values that overlap passed Geometry.
Value is returned by the query if <tt>bg::overlaps(Indexable, Geometry)</tt>
returns <tt>true</tt>.

\par Example
\verbatim
bgi::query(spatial_index, bgi::overlaps(box), std::back_inserter(result));
\endverbatim

\ingroup predicates

\tparam Geometry    The Geometry type.

\param g            The Geometry object.
*/
template <typename Geometry> inline
detail::predicates::spatial_predicate<Geometry, detail::predicates::overlaps_tag, false>
overlaps(Geometry const& g)
{
    return detail::predicates::spatial_predicate
                <
                    Geometry,
                    detail::predicates::overlaps_tag,
                    false
                >(g);
}

#ifdef BOOST_GEOMETRY_INDEX_DETAIL_EXPERIMENTAL

/*!
\brief Generate \c touches() predicate.

Generate a predicate defining Value and Geometry relationship. With this
predicate query returns indexed Values that touch passed Geometry.
Value is returned by the query if <tt>bg::touches(Indexable, Geometry)</tt>
returns <tt>true</tt>.

\ingroup predicates

\tparam Geometry    The Geometry type.

\param g            The Geometry object.
*/
template <typename Geometry> inline
detail::predicates::spatial_predicate<Geometry, detail::predicates::touches_tag, false>
touches(Geometry const& g)
{
    return detail::predicates::spatial_predicate
                <
                    Geometry,
                    detail::predicates::touches_tag,
                    false
                >(g);
}

#endif // BOOST_GEOMETRY_INDEX_DETAIL_EXPERIMENTAL

/*!
\brief Generate \c within() predicate.

Generate a predicate defining Value and Geometry relationship. With this
predicate query returns indexed Values that are within passed Geometry.
Value is returned by the query if <tt>bg::within(Indexable, Geometry)</tt>
returns <tt>true</tt>.

\par Example
\verbatim
bgi::query(spatial_index, bgi::within(box), std::back_inserter(result));
\endverbatim

\ingroup predicates

\tparam Geometry    The Geometry type.

\param g            The Geometry object.
*/
template <typename Geometry> inline
detail::predicates::spatial_predicate<Geometry, detail::predicates::within_tag, false>
within(Geometry const& g)
{
    return detail::predicates::spatial_predicate
                <
                    Geometry,
                    detail::predicates::within_tag,
                    false
                >(g);
}

/*!
\brief Generate satisfies() predicate.

A wrapper around user-defined UnaryPredicate checking if Value should be returned by spatial query.

\par Example
\verbatim
bool is_red(Value const& v) { return v.is_red(); }

struct is_red_o {
template <typename Value> bool operator()(Value const& v) { return v.is_red(); }
}

// ...

rt.query(index::intersects(box) && index::satisfies(is_red),
std::back_inserter(result));

rt.query(index::intersects(box) && index::satisfies(is_red_o()),
std::back_inserter(result));

#ifndef BOOST_NO_CXX11_LAMBDAS
rt.query(index::intersects(box) && index::satisfies([](Value const& v) { return v.is_red(); }),
std::back_inserter(result));
#endif
\endverbatim

\ingroup predicates

\tparam UnaryPredicate  A type of unary predicate function or function object.

\param pred             The unary predicate function or function object.
*/
template <typename UnaryPredicate> inline
detail::predicates::satisfies<UnaryPredicate, false>
satisfies(UnaryPredicate const& pred)
{
    return detail::predicates::satisfies<UnaryPredicate, false>(pred);
}

/*!
\brief Generate nearest() predicate.

When nearest predicate is passed to the query, k-nearest neighbour search will be performed.
\c nearest() predicate takes a \c Geometry from which distances to \c Values are calculated
and the maximum number of \c Values that should be returned. Internally
boost::geometry::comparable_distance() is used to perform the calculation.

\par Example
\verbatim
bgi::query(spatial_index, bgi::nearest(pt, 5), std::back_inserter(result));
bgi::query(spatial_index, bgi::nearest(pt, 5) && bgi::intersects(box), std::back_inserter(result));
bgi::query(spatial_index, bgi::nearest(box, 5), std::back_inserter(result));
\endverbatim

\warning
Only one \c nearest() predicate may be used in a query.

\ingroup predicates

\param geometry     The geometry from which distance is calculated.
\param k            The maximum number of values to return.
*/
template <typename Geometry> inline
detail::predicates::nearest<Geometry>
nearest(Geometry const& geometry, std::size_t k)
{
    return detail::predicates::nearest<Geometry>(geometry, k);
}

#ifdef BOOST_GEOMETRY_INDEX_DETAIL_EXPERIMENTAL

/*!
\brief Generate path() predicate.

When path predicate is passed to the query, the returned values are k values along the path closest to
its begin. \c path() predicate takes a \c Segment or a \c Linestring defining the path and the maximum
number of \c Values that should be returned.

\par Example
\verbatim
bgi::query(spatial_index, bgi::path(segment, 5), std::back_inserter(result));
bgi::query(spatial_index, bgi::path(linestring, 5) && bgi::intersects(box), std::back_inserter(result));
\endverbatim

\warning
Only one distance predicate (\c nearest() or \c path()) may be used in a query.

\ingroup predicates

\param linestring   The path along which distance is calculated.
\param k            The maximum number of values to return.
*/
template <typename SegmentOrLinestring> inline
detail::predicates::path<SegmentOrLinestring>
path(SegmentOrLinestring const& linestring, std::size_t k)
{
    return detail::predicates::path<SegmentOrLinestring>(linestring, k);
}

#endif // BOOST_GEOMETRY_INDEX_DETAIL_EXPERIMENTAL

namespace detail { namespace predicates {

// operator! generators

template <typename Fun, bool Negated> inline
satisfies<Fun, !Negated>
operator!(satisfies<Fun, Negated> const& p)
{
    return satisfies<Fun, !Negated>(p);
}

template <typename Geometry, typename Tag, bool Negated> inline
spatial_predicate<Geometry, Tag, !Negated>
operator!(spatial_predicate<Geometry, Tag, Negated> const& p)
{
    return spatial_predicate<Geometry, Tag, !Negated>(p.geometry);
}

// operator&& generators

template <typename Pred1, typename Pred2> inline
std::tuple<Pred1, Pred2>
operator&&(Pred1 const& p1, Pred2 const& p2)
{
    /*typedef std::conditional_t<is_predicate<Pred1>::value, Pred1, Pred1 const&> stored1;
    typedef std::conditional_t<is_predicate<Pred2>::value, Pred2, Pred2 const&> stored2;*/
    return std::tuple<Pred1, Pred2>(p1, p2);
}

template <typename ...Preds, typename Pred> inline
typename geometry::tuples::push_back
    <
        std::tuple<Preds...>, Pred
    >::type
operator&&(std::tuple<Preds...> const& t, Pred const& p)
{
    //typedef std::conditional_t<is_predicate<Pred>::value, Pred, Pred const&> stored;
    return geometry::tuples::push_back
            <
                std::tuple<Preds...>, Pred
            >::apply(t, p);
}
    
}} // namespace detail::predicates

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_PREDICATES_HPP

/* predicates.hpp
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
*/