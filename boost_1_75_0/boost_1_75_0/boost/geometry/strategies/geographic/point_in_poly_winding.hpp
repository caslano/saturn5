// Boost.Geometry

// Copyright (c) 2017, 2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGY_GEOGRAPHIC_POINT_IN_POLY_WINDING_HPP
#define BOOST_GEOMETRY_STRATEGY_GEOGRAPHIC_POINT_IN_POLY_WINDING_HPP


#include <boost/geometry/strategies/geographic/side.hpp>
#include <boost/geometry/strategies/spherical/point_in_poly_winding.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace within
{


/*!
\brief Within detection using winding rule in geographic coordinate system.
\ingroup strategies
\tparam Point \tparam_point
\tparam PointOfSegment \tparam_segment_point
\tparam FormulaPolicy Geodesic formula policy
\tparam Spheroid Spheroid model
\tparam CalculationType \tparam_calculation

\qbk{
[heading See also]
[link geometry.reference.algorithms.within.within_3_with_strategy within (with strategy)]
}
 */
template
<
    typename Point = void, // for backward compatibility
    typename PointOfSegment = Point, // for backward compatibility
    typename FormulaPolicy = strategy::andoyer,
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
class geographic_winding
    : public within::detail::spherical_winding_base
        <
            side::geographic<FormulaPolicy, Spheroid, CalculationType>,
            CalculationType
        >
{
    typedef within::detail::spherical_winding_base
        <
            side::geographic<FormulaPolicy, Spheroid, CalculationType>,
            CalculationType
        > base_t;

public:
    geographic_winding()
    {}

    explicit geographic_winding(Spheroid const& model)
        : base_t(model)
    {}

    Spheroid const& model() const
    {
        return base_t::m_side_strategy.model();
    }
};


}} // namespace strategy::within


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGY_GEOGRAPHIC_POINT_IN_POLY_WINDING_HPP

/* point_in_poly_winding.hpp
pduszJFOkcPGs4UHRs1wwPz2yfVDEpkZKzagaxQNEGjgY7O3YooHyBh/SR9pxAF6L2W4nBGx1/f+GG19BnY8HQApA4kcGHPjdM4tfhLs7ZYNDVKvF+SSZL+Mwafv7u2we2T4ZvAr5dcxK+PU3KcPqdepG18vnSJIjhg2EVpcyuV3hWj+FFoskpeOKXZUCzhTsE3VjSQ6S/bN9iV+PNb+XLKN891IbhU/RFloPQvqAvOCSeQf8p+29okORikqJl0+gvovNsDgIeQvK6jnhPNtzIzRezAQbmcI+vVX+0dcgF1ARpD9R01/4bQQN6o0sDA/ih7+Bvzy5vHbavQWNfke/OMW96VQem8bYSCoh4JFtZMQXMJ2YyRtWoD4dd8Dgi9A6mEdBTvmcSJ8rPW4J4WA8THApAhfg2CnG8CEX+Wz8Y77jmLQEC5lNuxXqo09uLCOurHt6L5ww5W8Ybm9zaKWmNeM8AsQOxw4MA+A/BvhRX1fGsv723Upxv+b8GpZ2Js5/fuKanvCvzqnrCb21dLodDKodJKwLNRSqFR7SonTquF9UN/+FJdGPp9CtFaU0YPV+dTb1E0Tq7lEmFuVAEnyJzzNFGzhPEQZh5Bw63xOybfoXSgmjBbYN7mcClkCGo0cTpucVeT1Mhf/z6PGsf1bkxSbkLIbpK/8teygo6CZj2a3Z62gzqNWoyCfhZUqcqJSet8abSUuCwf5EJlp
*/