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
sRYekvX/MLbBbByBRzAAczAIn0bzfdgiKb9O+bL3Yc9UN9X/DWyHb+JoPIvq8wYMxLdxAb6DKzAfd+O7eBjfw7N4Di/g+/gJfoBf4EWsxvg/xFr4Ecp9a/k+SPYROvetH5DlY4/N0QHbYh3shnVxKD6EvuiI/uiEwfgwJmB9nI/OmIoN8Rg2wuPYGE2fSyXf44jLdT6X6mOZX59hM/wcB+Nl9MYrOB6/xBD8WvZ738h+7xouwu/QfD+nSMbno9N+6UdpX3AdXfFn9MAS7IO/YhD+hhF4E+fgLVyFv+Mm/AMPYjmm82kojxexIhagnbyvVQmV7a0yPoBV0RGrYVesjsOwBsr6Jd/HyDqic59/n7z3sR+b4wHsiVk4Bg9iCB7CCDyMkXgE4/EoJuExXIE5+Dg+i8fwOD6PJ/AVfB5fx5Mo+1/5HkW2aZ39b6Hsf7/HRvgDumExdsfrOBVvYBj+jMlYgin4K27D3/AE3sLT+DvK/RD5DkWmiZRpZ11J2megM36LrbAQu+A17IffYSgW4WP4I6ZiMe7FG5iFP2v33bXvM2R8Ou89yn33K1gdv0BTe0Yiw7F9l2nPWJ3pssMaWBtrYmOsha2wNnriA9gL7XEIOuAYrCPz80GZn3UxFh/C+VgPV6AjrkMn3Ir15fjWALX2NWNN9Vyic791vTxv2YBNcCO2w004CVNxGm7GWNyCczANH8OtaDovkO8sxAU65wWNqslzHWyJLtgOm6AXNsVB2AwT0BXN9c+Vct/RqX9F+Vw/O3TBqlJuNSm3OgZiDZyBtfFVfBDfwLoynvzy2ncIap/PwXrFvUzTeLxlf+aDLXAUeuF4HIK+OAonyn7ND5/EQDyAQfgyBuN/0IA/4TT8DcOwIuOKxgY4CztgDPbEWByCcRiIszEe5+BijMc1OBf34jx8ARPxdZyP53GhMn5chF/iEryGS7EEl6PSvm8FOuAT6ITJ2AzXYDvciJ0wFYfjZpyEWzAMn8I4TMNVuBU34DZMw+24FzPwKGbiKdyHZ3A/nsMD+Alm4dd4EK/jIVQ21MNYE49iczyGvTAH5fMKzN81yL2ksp9X8IrsT15DdzyDPfB1HIZv4Dg8i8fwHTyN+XgZ38Vv8BzewPN4Cy+gchz/AO3xQ3TBj7AFXsIO+DGOx09xMn6m7Zfkewexqs5+6Q9536gc23kVKI+m6xb53kDsqXPd8qOcz/0k52/F2BWvo3n4XD/b7WVL5PsEfsH2+Bt2xJsoxxHzd/txj67scaSpvGfdCt2wtZyntEEv9MC92F7ONzrgJeyI17AL1qTc7jgSH8Vw7CXjZ17Ld/exDko71cbK/kG24w7y+XQdsT56oh92xijsgvE4CNXjNF7EEfg7jsRGlDUa3XA8dsAJ2B19cSpOxGD0w4U4BVNwKm5HfzyNAfgNBuNNjMUHqLcRO2IcdsJ4DMAEnIZzMQrnYwKuwiRcjetwDW7EFMvPy5bv4WtK8itYr0/15Dm+IzZEJ9SuN2W4QJ39+nZ5TpGO9XEHOuNO7IK7cABmoB/uRq39SJDt9iMsL9pv0A0bYWVsilWwM1bFkOrUg4KMJJNcJDX7sN6SaOLJTW9fkkSyyHlyldwk9twIdyM+xEiUCqWiMxoTmG8Mn0Vq9mXdJEs+pI4YQFL4fyKeIYXErh/TR7czxJXfe5B4kk5OkiK6V53LvoHfr5ISUrc/5dLNm7j1p2wSTZJJBommeyrJ4/crpJjUHUC/pAc5OZfpnSsPyPh7PXHidzeSrfSDFzEAb6L9QOpGvIgPWUL3aEwlmSSDv89iEXEaxLTwdwEpl8hwJIPp748BpMcg1muSRFIU6ZaO2eQ8KSaZdDtLag5mvSM=
*/