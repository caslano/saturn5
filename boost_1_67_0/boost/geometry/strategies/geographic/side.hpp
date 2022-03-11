// Boost.Geometry

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014-2019.
// Modifications copyright (c) 2014-2019 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_HPP

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/core/radius.hpp>

#include <boost/geometry/formulas/spherical.hpp>

#include <boost/geometry/srs/spheroid.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/promote_floating_point.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>

#include <boost/geometry/strategies/geographic/disjoint_segment_box.hpp>
#include <boost/geometry/strategies/geographic/envelope.hpp>
#include <boost/geometry/strategies/geographic/parameters.hpp>
#include <boost/geometry/strategies/side.hpp>
#include <boost/geometry/strategies/spherical/point_in_point.hpp>
//#include <boost/geometry/strategies/concepts/side_concept.hpp>


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

    typedef strategy::envelope::geographic
        <
            FormulaPolicy,
            Spheroid,
            CalculationType
        > envelope_strategy_type;

    inline envelope_strategy_type get_envelope_strategy() const
    {
        return envelope_strategy_type(m_model);
    }

    typedef strategy::disjoint::segment_box_geographic
        <
            FormulaPolicy,
            Spheroid,
            CalculationType
        > disjoint_strategy_type;

    inline disjoint_strategy_type get_disjoint_strategy() const
    {
        return disjoint_strategy_type(m_model);
    }

    typedef strategy::within::spherical_point_point equals_point_point_strategy_type;
    static inline equals_point_point_strategy_type get_equals_point_point_strategy()
    {
        return equals_point_point_strategy_type();
    }

    geographic()
    {}

    explicit geographic(Spheroid const& model)
        : m_model(model)
    {}

    template <typename P1, typename P2, typename P>
    inline int apply(P1 const& p1, P2 const& p2, P const& p) const
    {
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