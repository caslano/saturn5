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
l+Kyox9l9G8tsWwX1oLg0tWCSkdBfo+UJvQYDApUtXgmVnQGulz4oCXuNoaDfEBFdfEktDv4TJ3pAuXPfl/eU6iiS39TZ2cXcxXy3XCA2lVylnPFBUGsvCLcaS14LBfdSpK/UOb/eV48hefFbOSoZCw6ybmYSkPH+rx9RPnREFV2rD17a1OaIeZDoI9ZdKve5OA8nKsPkCX7GpTGXOKYFbx8q/j21k1XYM7Rdwf3HvTnRA5dPv0Ayv2VBHN1ZMRWahb5nnyASzS9R/AB3k3De0yf4Ipa3XfjOuScnK4/lOyHwRM2DiZewkGq4VLKCbwxXoO8U+TZQtTFLIhcO3rxrpP8Nv7L5ez5/bs4/9+j+fAezcQAtn2ZKsLqQDx1YTZxTjD2Qa0c2vQwvkcrna++1kY/zCCtkuSDmoqT13z2SL7JpbmGi85yZk/uoXeOMH1inSNrNbSE0y5Agqjzp6RT3bjr4CCnA6c+aF2mIIrDBoZ3JCwChO+XAtH3KpQA6jQ+tIFTsVT/VOXrWQiP7ng4KHihXOuLEM6E/C5oQ13xsAhYUmgpOL4bYjEBTpvwnQsuhZdeLLF4mHWppQAtTTAHrThd5xIM9eHHEpjH7YuzE1g/jtutVuO4CKAlqHL16+/anV7jpP/uU/+4fnb2
*/