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
uyiZq/Q9KlGYy+iqju9ndOBBH+ry95NZLbcXa7kIIhnqkRC1uXJzxeOPNxwF8d65Zw9eCudAWpd2grKpfo041tntN3kG0iISFM5y1lhOYgk7hBBlcX6GpUu9AodUChxZJ1E5aaHLYlLd+SFC69F8VCTyQ/xY2XlnbYZ56SPEuA48RKVdwgYunoDtO7FPzyDC2cFW0fXy5H3SzxmkgW/dcjqzHQatXk7Al+sDWbwAdQPiuzYo+sBYMy248Qfles9AgTVRi7nqPK1vpT7H5oWhfENMRVcFscWHhfsN9hrTVWJYDm5GY7VcIT4Y6P3+/rDOw5qelZrOSBrCDQ9Awl8QoIXtHWr0H7ky0Wc4w4UWm0Qh9bl8+xdHLNeSPbuRYzq/6hLSzT/jPU4oUkU1Lf41tYTw+KCxIxvTSSiiabpIdOluczolXpaVY9vg0ysg7lB/e2wQEb06bIbzZQdcFCFRu9qNVo1l2t5zzkp7F0RUgzCabE7PwuGYBmUEHMCAFF2aOFiBhmTNFkcBh43azGSe9kqxXw66cGMd5Hk+BEss5TYfsFWc3fxnnYigsA==
*/