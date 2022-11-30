// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2013 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2020.
// Modifications copyright (c) 2013-2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGY_AGNOSTIC_POINT_IN_POLY_WINDING_HPP
#define BOOST_GEOMETRY_STRATEGY_AGNOSTIC_POINT_IN_POLY_WINDING_HPP


#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/cartesian/point_in_poly_winding.hpp>
#include <boost/geometry/strategies/side.hpp>
#include <boost/geometry/strategies/spherical/point_in_poly_winding.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace within
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


template
<
    typename Point,
    typename PointOfSegment,
    typename CalculationType,
    typename CSTag = typename tag_cast
                        <
                            typename cs_tag<Point>::type,
                            spherical_tag
                        >::type
>
struct winding_base_type
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this coordinate system.",
        Point, PointOfSegment, CSTag);
};

template <typename Point, typename PointOfSegment, typename CalculationType>
struct winding_base_type<Point, PointOfSegment, CalculationType, cartesian_tag>
{
    typedef within::cartesian_winding<void, void, CalculationType> type;
};

template <typename Point, typename PointOfSegment, typename CalculationType>
struct winding_base_type<Point, PointOfSegment, CalculationType, spherical_tag>
{
    typedef within::detail::spherical_winding_base
        <
            typename strategy::side::services::default_strategy
                <
                    typename cs_tag<Point>::type
                >::type,
            CalculationType
        > type;
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


/*!
\brief Within detection using winding rule. Side strategy used internally is
       choosen based on Point's coordinate system.
\ingroup strategies
\tparam Point \tparam_point
\tparam PointOfSegment \tparam_segment_point
\tparam CalculationType \tparam_calculation

\qbk{
[heading See also]
[link geometry.reference.algorithms.within.within_3_with_strategy within (with strategy)]
}
 */
template
<
    typename Point,
    typename PointOfSegment = Point,
    typename CalculationType = void
>
class winding
    : public within::detail::winding_base_type
        <
            Point, PointOfSegment, CalculationType
        >::type
{
    typedef typename within::detail::winding_base_type
        <
            Point, PointOfSegment, CalculationType
        >::type base_t;

public:
    winding() {}

    template <typename Model>
    explicit winding(Model const& model)
        : base_t(model)
    {}
};


}} // namespace strategy::within


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGY_AGNOSTIC_POINT_IN_POLY_WINDING_HPP

/* point_in_poly_winding.hpp
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
*/