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
nLe/Su1aA4b9nFtvhPEt7+exX/orxdd6M/My14qJdCZk4Oqkj+2gOtYL0wm2llREFhoLyhiTFyqd6YDLB5jvHeI61E2uHqkavxrDEWfTUFsIjFpNXI29icTx+jOyLlIlinHVoOGH9sYwXRR7pHLkcrQ5pAUbKvZ6tY+D1RS3wsipSEZIRmF/yzqvIo+3xrgYQxCaNk1Vg2sn4sQ8Hr/EzJFnz+7R5EyAT97qeiz4J5it48pKS5C3tyEBnNTPrr8CMvy4TjFDvMcd66F3TZB9aKQ7UB2k51HPSInzhNefa2VR5SWwYvuYW1O97OfSPIv9FGiiAZoiO189eNPH463pwPINPe+Mc6tSHw+LkNWoI4/fyPWp10pJgPj8O6hsuWmQ7Az9zbQjS7a+3SLgrE126ju6961H4qRamx/wvOf3Vc4j0IRF5fzOUhX4Mu2fcrR4jKeUm4LX5LVE9sZC2qTTLIRi6qsVRfQpfy/Bx42jN+79Pib7GqB3x9jUOlg0vdoQ8bXHdRLsXxX80/tQrBGndbiyQ9ciMzMWX6PC0yursqre3XAhxLqEVk51udtjXmwVnkm7gOvd2sdgw4tqMDvpXQ3TTXONfGyxNOVOqpGckqH8Fk0WMYZ5m69WFqnWxEynctGMtsX6/kpilNs5qTXwu3xEUUdOjZ88MG+2o8S37ru5iUlGUUNl9065kd6ogU0/RYSivGwmic4KXuBR
*/