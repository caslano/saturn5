// Boost.Geometry

// Copyright (c) 2017-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DENSIFY_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DENSIFY_HPP


#include <boost/geometry/algorithms/detail/convert_point_to_point.hpp>
#include <boost/geometry/algorithms/detail/signed_size_type.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/srs/spheroid.hpp>
#include <boost/geometry/strategies/densify.hpp>
#include <boost/geometry/strategies/geographic/parameters.hpp>
#include <boost/geometry/util/select_most_precise.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace densify
{


/*!
\brief Densification of geographic segment.
\ingroup strategies
\tparam FormulaPolicy The geodesic formulas used internally.
\tparam Spheroid The spheroid model.
\tparam CalculationType \tparam_calculation

\qbk{
[heading See also]
\* [link geometry.reference.algorithms.densify.densify_4_with_strategy densify (with strategy)]
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
    geographic()
        : m_spheroid()
    {}

    explicit geographic(Spheroid const& spheroid)
        : m_spheroid(spheroid)
    {}

    template <typename Point, typename AssignPolicy, typename T>
    inline void apply(Point const& p0, Point const& p1, AssignPolicy & policy, T const& length_threshold) const
    {
        typedef typename AssignPolicy::point_type out_point_t;
        typedef typename select_most_precise
            <
                typename coordinate_type<Point>::type,
                typename coordinate_type<out_point_t>::type,
                CalculationType
            >::type calc_t;

        typedef typename FormulaPolicy::template direct<calc_t, true, false, false, false> direct_t;
        typedef typename FormulaPolicy::template inverse<calc_t, true, true, false, false, false> inverse_t;

        typename inverse_t::result_type
            inv_r = inverse_t::apply(get_as_radian<0>(p0), get_as_radian<1>(p0),
                                     get_as_radian<0>(p1), get_as_radian<1>(p1),
                                     m_spheroid);

        BOOST_GEOMETRY_ASSERT(length_threshold > T(0));

        signed_size_type n = signed_size_type(inv_r.distance / length_threshold);
        if (n <= 0)
            return;

        calc_t step = inv_r.distance / (n + 1);

        calc_t current = step;
        for (signed_size_type i = 0 ; i < n ; ++i, current += step)
        {
            typename direct_t::result_type
                dir_r = direct_t::apply(get_as_radian<0>(p0), get_as_radian<1>(p0),
                                        current, inv_r.azimuth,
                                        m_spheroid);

            out_point_t p;
            set_from_radian<0>(p, dir_r.lon2);
            set_from_radian<1>(p, dir_r.lat2);
            geometry::detail::conversion::point_to_point
                <
                    Point, out_point_t,
                    2, dimension<out_point_t>::value
                >::apply(p0, p);

            policy.apply(p);
        }
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
    typedef strategy::densify::geographic<> type;
};


} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::densify


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DENSIFY_HPP

/* densify.hpp
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
*/