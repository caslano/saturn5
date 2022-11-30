// Boost.Geometry

// Copyright (c) 2018-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_LINE_INTERPOLATE_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_LINE_INTERPOLATE_HPP

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/srs/spheroid.hpp>
#include <boost/geometry/strategies/line_interpolate.hpp>
#include <boost/geometry/strategies/geographic/parameters.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace line_interpolate
{


/*!
\brief Interpolate point on a geographic segment.
\ingroup strategies
\tparam FormulaPolicy The geodesic formulas used internally.
\tparam Spheroid The spheroid model.
\tparam CalculationType \tparam_calculation

\qbk{
[heading See also]
\* [link geometry.reference.algorithms.line_interpolate.line_interpolate_4_with_strategy line_interpolate (with strategy)]
\* [link geometry.reference.srs.srs_spheroid srs::spheroid]
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
    geographic() = default;

    explicit geographic(Spheroid const& spheroid)
        : m_spheroid(spheroid)
    {}

    template <typename Point, typename Fraction, typename Distance>
    inline void apply(Point const& p0,
                      Point const& p1,
                      Fraction const& fraction, //fraction of segment
                      Point & p,
                      Distance const& distance) const
    {
        typedef typename select_calculation_type_alt
            <
                CalculationType,
                Point
            >::type calc_t;

        typedef typename FormulaPolicy::template inverse
                <calc_t, false, true, false, false, false> inverse_t;

        calc_t azimuth = inverse_t::apply(get_as_radian<0>(p0), get_as_radian<1>(p0),
                                          get_as_radian<0>(p1), get_as_radian<1>(p1),
                                          m_spheroid).azimuth;

        typedef typename FormulaPolicy::template direct
                <calc_t, true, false, false, false> direct_t;

        typename direct_t::result_type
        dir_r = direct_t::apply(get_as_radian<0>(p0), get_as_radian<1>(p0),
                                distance * fraction, azimuth,
                                m_spheroid);

        set_from_radian<0>(p, dir_r.lon2);
        set_from_radian<1>(p, dir_r.lat2);
    }

    inline Spheroid model() const
    {
        return m_spheroid;
    }

private:
    Spheroid m_spheroid;
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template <>
struct default_strategy<geographic_tag>
{
    typedef strategy::line_interpolate::geographic<> type;
};


} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::line_interpolate


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_LINE_INTERPOLATE_HPP

/* line_interpolate.hpp
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
*/