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
3sr6yuOM7iQZT0Z3ls+ma+QdGh4ao3vF9ZX3s8p7UNX628nMJGd5/7GPebt/lrUMMkK3u3TIlu1xSC3Xv5PkHSbv1udK3jNI5/TbXiNv6Ro6OMj43jvS2KlQ9rfH90oZpJ9ZeQ9r2b8h65PZJ22U+fiolZX3wPoPq4+hDFmPRrIebrIeAZ9nWQ9V6XMyluv3Vo6hgdJeIEDyHkDard+GGnlLO4psbzPTflOPl3xe8nSXPOtInm5faOXJm3zjWtMp0hg6C3v1/DOPmwAH7fwjreZvaEegFOBVzyPzNgz81zAtJ5WVuKfz+u2etQxKY55XzddZadOj9MkmbQmy9EmoHJNxUr4eOqlL5ZiMTMtSPtk6clD+iWMyc/+4SJ/+ZUkFpG69qK/X0jLbOfm37e1n3CzBw4aMCYsxb8yir11f3q4rs24tUVTGOJbfOWVtd6KcKzPyZh3n+xLlcjqglCsq2tCJNH2TZfP8zGzbNFWjLc9TK/klWsnPPywiW9tfI0/l3JyTL+u2v6xfx4OZef657S7t6ZRrifY2N/WF6ydjq+8uxPmKa/AK5fE0licowtCRvOEQVM7LPQVe3EddSgFTX7g/faNTtfdJK6Au29ECSp9y4yOlv8RT/E45l6SOP8fvxuTJbBfGekh/j8S2mtoL6f/E7yvx+wxluUPZhuzC4FGRMeP9h0UNGT4qODzGkE+K0vdfJAtU+prjd9IPuiF7yqTq+85wZyNtkizGGlD3Myvj8Vv2CanZL666bZLkGaBui2Qssz6W0MnUh3VxVd+PwcZOGZlKq/rio6fCYaHjjEeQZf/BMRExyu9zF53PwXOWbTeenz85xL6TZcWZPj8qUnaB1CvKfPYFJXbxCPPJOoSY1j8iKNjUV6LHX4yfOSj9z7p+rVP1T3tDfj4kP286rv779hM66T9XPS7CVTmek+ScXkiaW4xr37em9oBSk+b4PFb3M8vxhhrjsCvn1nHp1zwXZXbHG5RjLOm+qSxygo+P4bg1lCfjJf0/nkPOLUO/0p/9olP1K63/3bbvjL8z9EYv5btvUR881anPudLSV3FMHuk3MjbI3/gX0zgArnnU1zanXObXNrk3U34XGRw8UhkXQLOf6jk6i36q1WNiWY7bYfh5g/z8gr6kOa+yjuHhi5ZjeCSik/HaFKju8159H1la1Ze/2d6S8yWD4424dPoRYL+e0Wn1ZRolY1aY9fU70qKP6aDoGDmXMpc5g2WOZGGNGewXLMaKCdKPgE9H24Ztb2o3mUf5m/4PSl/frsrv1XnscDS2Xyp6yVTuPZjXWPeGRliUqSnHc3Bu2jGlm8oUYNq2fGWM8SeXoVHytzD13yhUbHCYbLc95N2Q5emP5yd/NeV/FI+7SD0j+ZuXIaSIscyzr5nmSVOXWaljgr4zfuYpf9P/XO6iTtXn9rqL6r/3vqz++1352Ul+LnlN+bx6LBbpk18fH+yK7viLC/+5bXGeh2enjayqTaz0aavuvz1e+ZlDANX9xzOGEPVb5jGdqL5uRYQFKeeJcu4o30FN55tmO2JndXvZkTHK/XDW/rgbqu99Ddsv8I5O+sc1/qy7q/75k3vGnz1d1PfKe2T7DpY6vR/pFp9JfKhT90Fu+g7jPyYyiKv+y+/V5F45Sz+2QPmz1ukbihln/tGB/YwHcAK/c3qklEXu1w3VhCH/fC8ZO+A+Sh/X1KvKvpc6Nev9kSu/O515f+SvjM+j2t6VVPVpdGRYKIMCclyY7oAs70PCLced0LwvUd87cPzJPZfcr6i/AynHlNxnyLmfyoonss0K6fvFeWKqS3y17zGk723lfsmirqbXdobrMh+r4rZL1vvElros94lKPTHlsXI=
*/