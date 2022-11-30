// Boost.Geometry

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014-2021.
// Modifications copyright (c) 2014-2021 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_HPP

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_promotion.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/core/radius.hpp>

#include <boost/geometry/formulas/spherical.hpp>

#include <boost/geometry/srs/spheroid.hpp>

//#include <boost/geometry/strategies/concepts/side_concept.hpp>
#include <boost/geometry/strategies/geographic/disjoint_segment_box.hpp>
#include <boost/geometry/strategies/geographic/parameters.hpp>
#include <boost/geometry/strategies/side.hpp>
#include <boost/geometry/strategies/spherical/point_in_point.hpp>

#include <boost/geometry/strategy/geographic/envelope.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>

namespace boost { namespace geometry
{


namespace strategy { namespace side
{


/*!
\brief Check at which side of a segment a point lies
         left of segment (> 0), right of segment (< 0), on segment (0)
\ingroup strategies
\tparam FormulaPolicy Geodesic solution formula policy.
\tparam Spheroid Reference model of coordinate system.
\tparam CalculationType \tparam_calculation

\qbk{
[heading See also]
[link geometry.reference.srs.srs_spheroid srs::spheroid]
}
 */
template
<
    typename FormulaPolicy = strategy::andoyer,
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
class geographic
{
public:
    typedef geographic_tag cs_tag;

    geographic() = default;

    explicit geographic(Spheroid const& model)
        : m_model(model)
    {}

    template <typename P1, typename P2, typename P>
    inline int apply(P1 const& p1, P2 const& p2, P const& p) const
    {
        typedef strategy::within::spherical_point_point equals_point_point_strategy_type;
        if (equals_point_point_strategy_type::apply(p, p1)
            || equals_point_point_strategy_type::apply(p, p2)
            || equals_point_point_strategy_type::apply(p1, p2))
        {
            return 0;
        }

        typedef typename promote_floating_point
            <
                typename select_calculation_type_alt
                    <
                        CalculationType,
                        P1, P2, P
                    >::type
            >::type calc_t;

        typedef typename FormulaPolicy::template inverse
                    <calc_t, false, true, false, false, false> inverse_formula;

        calc_t a1p = azimuth<calc_t, inverse_formula>(p1, p, m_model);
        calc_t a12 = azimuth<calc_t, inverse_formula>(p1, p2, m_model);

        return formula::azimuth_side_value(a1p, a12);
    }

    Spheroid const& model() const
    {
        return m_model;
    }

private:
    template <typename ResultType,
              typename InverseFormulaType,
              typename Point1,
              typename Point2,
              typename ModelT>
    static inline ResultType azimuth(Point1 const& point1, Point2 const& point2,
                                     ModelT const& model)
    {
        return InverseFormulaType::apply(get_as_radian<0>(point1),
                                         get_as_radian<1>(point1),
                                         get_as_radian<0>(point2),
                                         get_as_radian<1>(point2),
                                         model).azimuth;
    }

    Spheroid m_model;
};


}} // namespace strategy::side


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_HPP

/* side.hpp
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
*/