// Boost.Geometry

// Copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_LINE_INTERPOLATE_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_LINE_INTERPOLATE_HPP

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/formulas/interpolate_point_spherical.hpp>
#include <boost/geometry/srs/spheroid.hpp>
#include <boost/geometry/strategies/line_interpolate.hpp>
#include <boost/geometry/strategies/spherical/distance_haversine.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace line_interpolate
{


/*!
\brief Interpolate point on a spherical segment.
\ingroup strategies
\tparam CalculationType \tparam_calculation
\tparam DistanceStrategy The underlying point-point distance strategy

\qbk{
[heading See also]
\* [link geometry.reference.algorithms.line_interpolate.line_interpolate_4_with_strategy line_interpolate (with strategy)]
}

 */
template
<
    typename CalculationType = void,
    typename DistanceStrategy = distance::haversine<double, CalculationType>
>
class spherical
{
public:

    typedef typename DistanceStrategy::radius_type radius_type;

    inline spherical()
    {}

    explicit inline spherical(typename DistanceStrategy::radius_type const& r)
        : m_strategy(r)
    {}

    inline spherical(DistanceStrategy const& s)
        : m_strategy(s)
    {}

    // point-point strategy getters
    struct distance_pp_strategy
    {
        typedef DistanceStrategy type;
    };

    inline typename distance_pp_strategy::type get_distance_pp_strategy() const
    {
        return m_strategy;
    }

    template <typename Point, typename Fraction, typename Distance>
    inline void apply(Point const& p0,
                      Point const& p1,
                      Fraction const& fraction,
                      Point & p,
                      Distance const&) const
    {
        typedef typename select_calculation_type_alt
        <
            CalculationType,
            Point
        >::type calc_t;

        formula::interpolate_point_spherical<calc_t> formula;

        calc_t angle01;
        formula.compute_angle(p0, p1, angle01);
        formula.compute_axis(p0, angle01);

        calc_t a = angle01 * fraction;
        formula.compute_point(a, p);
    }
private :
    DistanceStrategy m_strategy;
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template <>
struct default_strategy<spherical_equatorial_tag>
{
    typedef strategy::line_interpolate::spherical<> type;
};


} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::line_interpolate


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_SPHERICAL_LINE_INTERPOLATE_HPP

/* line_interpolate.hpp
h5L2ryd9n+dNoUIS7xxUPcfcCR1YUxmOVjOKI7QLT0XMUBMw0GEY2/57hLsimK62F0gakQOEt74SBSvkypCQzt99J+hiO9Qh5WFbZdhuSxQZlfjIKzWmtY+cLwCjOqCzhaUNOKSahemX995jSMvLnqQgHcdre2HI+ZnlfsDv3AInqb5Y7AVk0V9v1aFVo/cAW/MlerAGHJkr1RnfqW9hzk5R74TDU1c8I/TX7E93MuvE5+ukJi41weV6vpxbcTAFtGz6nyTIOOWQZydX8LWaea33Pc4dqTGNfPY3pd0vlcDS9bokAX9XGy+bx9ek3ScjVyTfU6i0WJpNCL3iNeoVh7ugRFkrppPTOFXaknRPaBoG7K2Lzuf/SFwPelYb1fxNH//8/+vjf19eIe7q7OJgp27m4cLxTwi2sdUbcc1t9FFL/gZgnWj5YSjHQ6fNfu7EJFtK62R4M7c0oZPRwMp0Q+cpUdO1UeIOjSwk55XTlYWb0NKl7jdtzaH9+ija/Tq7RRSrzU75RgrJ7R/ZJopVHLgm4ko6iK1X7NgEB05uHNBJsLV/i+IJAO+se+ZkOB9OZmR4u5/HIdymlPyQRU9Imck3YRIpbWq2fzTXcM7FF2gHiB9A8aMkytruze5jMHvRhdJbXb0obP64zl5GuRVFnXld9SIzIKWP2ajZCaUe/TuW7YslVNiR3/kzZdzJRF3TT9Vi0ZbP377Rvisb
*/