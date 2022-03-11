// Boost.Geometry Index
//
// Spatial query predicates
//
// Copyright (c) 2011-2018 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019.
// Modifications copyright (c) 2019 Oracle and/or its affiliates.
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
nearest(Geometry const& geometry, unsigned k)
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
path(SegmentOrLinestring const& linestring, unsigned k)
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
boost::tuples::cons<
    Pred1,
    boost::tuples::cons<Pred2, boost::tuples::null_type>
>
operator&&(Pred1 const& p1, Pred2 const& p2)
{
    /*typedef typename boost::mpl::if_c<is_predicate<Pred1>::value, Pred1, Pred1 const&>::type stored1;
    typedef typename boost::mpl::if_c<is_predicate<Pred2>::value, Pred2, Pred2 const&>::type stored2;*/
    namespace bt = boost::tuples;

    return
    bt::cons< Pred1, bt::cons<Pred2, bt::null_type> >
        ( p1, bt::cons<Pred2, bt::null_type>(p2, bt::null_type()) );
}

template <typename Head, typename Tail, typename Pred> inline
typename geometry::tuples::push_back<
    boost::tuples::cons<Head, Tail>, Pred
>::type
operator&&(boost::tuples::cons<Head, Tail> const& t, Pred const& p)
{
    //typedef typename boost::mpl::if_c<is_predicate<Pred>::value, Pred, Pred const&>::type stored;
    namespace bt = boost::tuples;

    return
    geometry::tuples::push_back<
        bt::cons<Head, Tail>, Pred
    >::apply(t, p);
}
    
}} // namespace detail::predicates

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_PREDICATES_HPP

/* predicates.hpp
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
*/