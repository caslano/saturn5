// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2013 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013, 2014, 2016, 2017, 2019.
// Modifications copyright (c) 2013-2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGY_AGNOSTIC_POINT_IN_POLY_WINDING_HPP
#define BOOST_GEOMETRY_STRATEGY_AGNOSTIC_POINT_IN_POLY_WINDING_HPP


#include <boost/mpl/assert.hpp>

#include <boost/geometry/core/cs.hpp>
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
    BOOST_MPL_ASSERT_MSG(false,
                         NOT_IMPLEMENTED_FOR_THIS_COORDINATE_SYSTEM,
                         (CSTag));
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