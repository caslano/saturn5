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
seamzLvJhgceEXC2TZ74A3CfEdPc9taGGRFBlLACCrYYG5WqBS+atkHI1l6j0duCE1UYchqyuURloP+TG5Q52gmaBc94hvEAh0/7B0f9VhcOFEhlyEvqXs0WTHjEsKWBASiMxlv0ZkFK0uiaaC/U+2Rp7YVrLkhCqiKGFgPcr11Pn3bqVukmrVfZ+Bu3N4UfYj4VksfN/vnp8fhgeDga94eD14eno6PhYNRCyWLaxGB78hg22Sb89BNF3iO8ud4kCBhaBr0K7Lyt5ub+JmxTlw51R1X8yFO7fr0QJkpwphb8jbekTOrx0J8DB++t2CRgTz0WBazvsThgBx7jATv02DRgzzw2C9hzjyUBe+ExEbAjj70P2EuPXQbslcfSgB17LAvYHx6TARt4TAVs6LE8YCce+xCwPz1WBOzUYzpgI4+ZgJ15rAzYucfmAXvtsUXA3njsKmB/eWwZsAuPXQfsrWU36PASk3ujsSJC7jVuGl/KCTZ93JsTXJL5xpxwX+76D1lh388Kb+/OCuw2K+zfmxX2A80yT+tPAzbxWD9gkccOAhZ77DBg3GPPAjb12POAzTz2ImCJx44CJjz2MmDvPfYqYJceOw5Y6rE/ApZ5bBAw6bFhwJTHTgKWe+zPgH3w2GnACo+NAqY9dhYw
*/