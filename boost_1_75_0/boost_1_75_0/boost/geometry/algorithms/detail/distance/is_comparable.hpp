// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHS_DETAIL_DISTANCE_IS_COMPARABLE_HPP
#define BOOST_GEOMETRY_ALGORITHS_DETAIL_DISTANCE_IS_COMPARABLE_HPP

#include <boost/type_traits/is_same.hpp>

#include <boost/geometry/strategies/distance.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{


// metafunction to determine is a strategy is comparable or not
template <typename Strategy>
struct is_comparable
    : boost::is_same
        <
            Strategy,
            typename strategy::distance::services::comparable_type
              <
                  Strategy
              >::type
        >
{};


}} // namespace detail::distance
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHS_DETAIL_DISTANCE_IS_COMPARABLE_HPP

/* is_comparable.hpp
WK4mEGvUD2vUg+z8XPyi8IscCZUfQ3nkomkLSkv5gbN4vVRsDifHlgNjyKFkF3F6zTz/1E8uWpR60F056KxR2IkvShdkt9SqNKpNWoX+ovGZOxt7vO79xovqCub0TUE7qTd0wAi4Yyrng7+SgXzzJ6T54uPTfGm1af0EjtCHcIONCshn16BCXjHlyDbSiSfT32Up1jzRuQzCV9h3h0CFtOJl9DuUftVw+pWk/x8Nl+pUX814Ocx3JAPOjRFwbsSRPQf0fPjaRhozfA9U1r5i4sDXFbb+F+Q15Qi+SNYBUz2JxWkw29NK5IuvQL60pT1sT+3w8z+5qP4bKo++GkbHXzXzn17BZVacqGnhqIRbdKSbmVAFiJpN15XmSiSfYhYrgRxGii02UiCNpJEeoO5WFJblvmGilBCe5BS/ammIBYwb/Mu2f+vTbR4gIoz8CrGHbrZhw3DvfzVlrx2JfwLro15pzcR4JnlLeU1dri3Xa4wV7rDRpq0Nbgh/mvt2XhqOlEWfyr/dFassKIstzS+NjY2+WwTsXFG2Kz450Vx8IbneVVpZtrO8pGxheU2ytHRsSaB4ajxZmB8NRAK57qCHgsD5xnsT2njlEJpWRIUCv6YHg2E9109x1fP1gmi+v0hP6rSU6closZ5AOQX90A3xN9ENaa/2mgt86Z/D6KRE8c+hsv3Ppj9Pm4Cxpa9KmDCU1/EUl9QgvwQcC10T
*/