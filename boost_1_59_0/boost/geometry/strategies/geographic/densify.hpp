// Boost.Geometry

// Copyright (c) 2017-2021, Oracle and/or its affiliates.

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

    inline Spheroid const& model() const
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