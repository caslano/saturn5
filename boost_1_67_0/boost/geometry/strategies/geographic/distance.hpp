// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2016 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014-2018.
// Modifications copyright (c) 2014-2018 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISTANCE_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISTANCE_HPP


#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/core/radius.hpp>

#include <boost/geometry/formulas/andoyer_inverse.hpp>
#include <boost/geometry/formulas/meridian_inverse.hpp>
#include <boost/geometry/formulas/flattening.hpp>

#include <boost/geometry/srs/spheroid.hpp>

#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/geographic/parameters.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/normalize_spheroidal_coordinates.hpp>
#include <boost/geometry/util/promote_floating_point.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>

#include <boost/geometry/geometries/point_xy.hpp>

namespace boost { namespace geometry
{

namespace strategy { namespace distance
{

/*!
\brief Distance calculation for geographic coordinates on a spheroid
\ingroup strategies
\tparam FormulaPolicy Formula used to calculate azimuths
\tparam Spheroid The spheroid model
\tparam CalculationType \tparam_calculation

\qbk{
[heading See also]
\* [link geometry.reference.algorithms.distance.distance_3_with_strategy distance (with strategy)]
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
public :
    template <typename Point1, typename Point2>
    struct calculation_type
        : promote_floating_point
          <
              typename select_calculation_type
                  <
                      Point1,
                      Point2,
                      CalculationType
                  >::type
          >
    {};

    typedef Spheroid model_type;

    inline geographic()
        : m_spheroid()
    {}

    explicit inline geographic(Spheroid const& spheroid)
        : m_spheroid(spheroid)
    {}

    template <typename CT>
    static inline CT apply(CT lon1, CT lat1, CT lon2, CT lat2,
                           Spheroid const& spheroid)
    {
        typedef typename formula::meridian_inverse
                <
                CT, strategy::default_order<FormulaPolicy>::value
                > meridian_inverse;

        typename meridian_inverse::result res =
                 meridian_inverse::apply(lon1, lat1, lon2, lat2, spheroid);

        if (res.meridian)
        {
            return res.distance;
        }

        return FormulaPolicy::template inverse
                <
                    CT, true, false, false, false, false
                >::apply(lon1, lat1, lon2, lat2, spheroid).distance;
    }

    template <typename Point1, typename Point2>
    inline typename calculation_type<Point1, Point2>::type
    apply(Point1 const& point1, Point2 const& point2) const
    {
        typedef typename calculation_type<Point1, Point2>::type CT;

        CT lon1 = get_as_radian<0>(point1);
        CT lat1 = get_as_radian<1>(point1);
        CT lon2 = get_as_radian<0>(point2);
        CT lat2 = get_as_radian<1>(point2);

        return apply(lon1, lat1, lon2, lat2, m_spheroid);
    }

    inline Spheroid const& model() const
    {
        return m_spheroid;
    }

private :
    Spheroid m_spheroid;
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template
<
    typename FormulaPolicy,
    typename Spheroid,
    typename CalculationType
>
struct tag<geographic<FormulaPolicy, Spheroid, CalculationType> >
{
    typedef strategy_tag_distance_point_point type;
};


template
<
    typename FormulaPolicy,
    typename Spheroid,
    typename CalculationType,
    typename P1,
    typename P2
>
struct return_type<geographic<FormulaPolicy, Spheroid, CalculationType>, P1, P2>
    : geographic<FormulaPolicy, Spheroid, CalculationType>::template calculation_type<P1, P2>
{};


template
<
    typename FormulaPolicy,
    typename Spheroid,
    typename CalculationType
>
struct comparable_type<geographic<FormulaPolicy, Spheroid, CalculationType> >
{
    typedef geographic<FormulaPolicy, Spheroid, CalculationType> type;
};


template
<
    typename FormulaPolicy,
    typename Spheroid,
    typename CalculationType
>
struct get_comparable<geographic<FormulaPolicy, Spheroid, CalculationType> >
{
    static inline geographic<FormulaPolicy, Spheroid, CalculationType>
        apply(geographic<FormulaPolicy, Spheroid, CalculationType> const& input)
    {
        return input;
    }
};

template
<
    typename FormulaPolicy,
    typename Spheroid,
    typename CalculationType,
    typename P1,
    typename P2
>
struct result_from_distance<geographic<FormulaPolicy, Spheroid, CalculationType>, P1, P2>
{
    template <typename T>
    static inline typename return_type<geographic<FormulaPolicy, Spheroid, CalculationType>, P1, P2>::type
        apply(geographic<FormulaPolicy, Spheroid, CalculationType> const& , T const& value)
    {
        return value;
    }
};


template <typename Point1, typename Point2>
struct default_strategy<point_tag, point_tag, Point1, Point2, geographic_tag, geographic_tag>
{
    typedef strategy::distance::geographic
                <
                    strategy::andoyer,
                    srs::spheroid
                        <
                            typename select_coordinate_type<Point1, Point2>::type
                        >
                > type;
};


} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::distance


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_DISTANCE_HPP

/* distance.hpp
dEHnkOScxbkLxW9yajLEOXG0+CsxeaJNTI6xSaJaqFpP/Yf9BXBDoOVT+VTewZ49TpzRy/5hwZahYX1PMgEl6dFxt/hwXLSY2mtqkG4zUlSGmGcUbZMfFW1xj0rRardQhBbnxxkF7UEdYgP0AEnGDFt+X54HOlkqT8Epvm6cUeE01drcD8fpl/4VU6DUZHEBLa42wFo4pnHr4u6QHeFmR9wdhXe67ykUDf8U5sQZhFQDt+6feoodl6dBkD78TxqWUg0sRmhV4rCXCkiSYEAxMJcak2epSOKlz+hxDKxRTDOIjxoS02g2TEHa9LT3Vj9Z4fRFqQER+3qEFlL0wlOGjDTbguyc7IUAUrmpJgg/bnpqaoWTcqwE7GPeWhSnhynobykppqjpJZMoimVa74+zi/o4O9dRbOf8xe6lcTSb7C3arqGCde///6nLeH8Fdd9dcRno+XLYXkoImcJ2HYrsQd4TTaV19fOm0n/tcf53FPdn+FFam3BNltNfbj28CAkDN51KwFFHS9/NlOUS91TI1El/gi4XNtYAb9jxe0I3Tmds8J3+We1A5QlSSrCypmQXPq5J6UobSguhlWXWgHj5d2VDyWy0zBqlV5WY2rDSlFZKh2YlndKQ0m4fN50WoE923ukd2NpmQhgjPY7r7pcdC+/vczwIYRPzgUfgCyDD+w5Utos8NgqAj2VjgK5hwMHUkwI05HuRSrT+ncCjBgrfC+3ab+kstgNhmGCf3lnsSPG9F5qOSQm+3UoLeuQKYQt6gXACiz7dilS5/fpUiCMJXXNP+/A8CPvuUErrSGnboNJJaunC8Pbhj0MYdtjOFVA6RdhZCI9unkCWva7XzdLuwwjQXbtKnjVoHLSbNbqLNuzadTpns5t04N6J80i3KQ1sThkBsLBJdx9G2mxYnHvastk7EjJ+thw3UAMWQF3EpyywABv6ZBkWAIlybVe6XbSMsIstAUCwN9hLP5GL7UJOn2gxiDk080ZLlGC5IuR0tz3d7dOdttBQV8U/mfz9WKwgtVFF7hc96lPlDp3FAbRfB7D4073vOP9nyjtOKuRPAlKzF/LwGUjDlvGJjWBecOvA532Ib8c0GEPTL7SZZKlwnguph8yuC+PX+utiGc0Q/WG9ydeGbncR1Ln/2sB250B8QUi7i36hXaxX8gvtroM6z4e0i5j1BsT3D2oby2mHaBvrIqPJSs/cPFJcF2d0nXCs2vw7javbkSH2QE705giuTjOt2jHO5XEM3xyuRCJdHvZS7sLFJk+NklTHet3r5c1LtK5zjsmYpJ1Wy36wOVkHtWI222WuChIcX/rKTR6otrnaa0WePFOGSI1Yj9//Pf1yPyQvrHG/EYdzAPpJmTybgTmliy1VHcii6J5qhIJjzOZIrloz7RPHMVejI01JZH1RLVliTdXXxsyoFjHyQ7mvb71YJfaYPtF16i5zF2WuUzYdM9Vx1frSs5RGU8pOvAUfjpP40LB06bcoqbC1uYsXwtzFh3qn1TjuhTn+OO1rx20w9++qJCMkjYGkdkgKh6Rm3wu5i5UxP9QH9eBxTXn04kOU0+o1S2VA491zI6hsgEMeRD64b+A6vwbrt04eiM9bIP68rKwv5g+1B7AO9wxN1WuOQMgxTP6dXkLOiP00Q8obc36OUwehLWlQX34SLyd9HfyFvrDOf7N+3ijkbAP4EXfeJi6KW1Bv2XcrgLfesh/brLccVB7vKw9CINyWfWK8uCZmqZnIG45R6Zn5lC3vzzC2TKnix2FU7kKuj3IkuFNibZLtagQeEcaKKbHTE+5OyWQNYkocJIxKl5t8w8WUibZMydQDLKyWzqfElGjpFETEk+JjevH3tFgAMl3cIhDkuSZKfMIIQqD8RDQKUIPmIyIdzRTZaL7bcQdXRFOMa+PzWoorMkLoDxBKZA3MBgECmcDkkMxOux77NMBeAGkMa2Mtx3jIyqfkKftAgpDH9I7c4+Q9jGvsRS2llsrxnVCfnXbmR09auljFdTAgYd8itvS0cTXG+JMmz6PiSe4rHcPvh2Wr8mkdtKBxz9I/wvofE6u5r4qrpAjHA+64uJDx25liDXySjfgVi18J+JWEXzb8ehy/VruFEgB4KtvEn3DcIVZXSXpHJFZ1zzKmst3cVwzAudrUVvU99jke+pzN+rkOHTt74QJl+OnAF7irHcym2zsBFFncdJwogOjkj1qKb3PcLtbY+qfvh+mLfh6k96OQLdaDvJdTUzY+OZW94nvL5EnynVTazBQvmtrMlxjX3kItlZUInGfjQQiZGhNzjHZhBLOjKjnRComHIFG0GriqPu7yTcym5zF6FMow/G4MXjad6GEN3JVha3O46gS7MBIIVgqeXcw5dMHXJg88GO45KGkXNJxXy1Rq7OI4KGYXIiDK1WvNlwu+N3lwlNUGigwNegNxH2akyDZw8JNzarjqLN/ropwpTzlIpnmHEabZyXczrmvXgbRbl1tTpkmezV7xJgO7VZqx0C/1FBlUFDB5Ei2GwomilQ5ZPy6RcgxLghGbLYaCi9CJJ5ap9HhHhMFywf806mn4n0atgX/ceEsp5f8OKpayqv+xwZRn1H+KpN9F0u9SU7Zvt1FW8kxWnw9Ty6gn4fM09QR8F5C0udQqqnBQ2jwo5YD0QEo6PFdDSmipZIqlfgufNZCOdWZDeIXaL4ZXQjml79VQfjnk4RiXQPhJCvUzMyD/CYixJC1QbwnU609RxktRyhgpShlXYDyBMVCU0rfyXKn28wzJX03GqvQb6BPLLSHl0uHpgDoFALUl6hhmkNH2x+fDaLHEmpC0LGhnKZlhf+p8KBUat8KYV4bUSSdjC40vIXNR+sP62A9FKW0H2gu0g2NV5paaOu3pp6etIdq1pfB3R6wV/mIx8Az8UVbrXUuX3gUByLdZqe3J8Hl42ZPL8K3omDZ3VWEwPA+1fRBMX7baEUhMZn/LrnFQ22ezK0gbs9mVy/CZvLpg+QoIWIkxDOC07IkCdkmBUmbJShKEfihon4J2sU0K2qKgHfispKxLnqGgDXgWUFCXgjpU+hIHW7B0CWljRsFyEpqfxxasUdOyli1duUyNzGeVkHXVSpKQzqrPJQ4K6lJQj4LyFJTDMhTkw87OzJLH2GDXylP2ww4W/dKve2U87pNN/NxKIELymBWQvxg3MxSXGiFbyf0UcpVUZV8D7aqbYaCAzIwUaWGEmKQXZuihAJ7xpSqoJsygxdQVkJOaJ8zViyPMwztmVzgZ3vwiNDRDbw67w4rRexuAdMygu5NWa1kPl7paC61qfAcC9CHvsQPvBM7neGYXVsQZ3fCJ74BDPDmw/8bSa/pIsJyzCcskmfWLlt56S28fDsDid1s6lYN8jWg9Z/pUCsOz0lZgLubhWJXhFx2KoC7VSF9BeeRXe38HrM9D1wzij2kHUVCwJ1poxvUqDP8gihUkyj0PUabSQovDY7DBSn0yU2k13FzVqPLG6e8jn8hk+FfNMAGWRlBeeZ+Qc76Rcf0IwfiLUG0E508uGMb5H2M2/vZ6KNkEVLo/6bsrMkqhduBeYXZzk+MoU9nAVFbHVwV4sGiJzoSlUDl4lDvAwTUQAqLLbBgBAZvKwf3jB3FwXE73PR8lwIJwD0Cthqe0lHyvPOZhQIWQMrJSRB6TBOmqJPFfrs9/WpxOVTmSvVjR86SpnVppvtFhzO8wnVjQc9GMExn1PQD8basB8A9hiVGTh+sDzjwcgpn5dCgTxjXt9mopmESWWKfIG7e/i6e2+Kb4j9PEarGBOwvyBp0A8oakdQwXxwrj3IV6d7E+lb2ULR7nzhZXfR/hyLEzq8LhMxfEjFWZIGasykUxIwI+81DyyELJYzEkrbKD5LFqJUgeqwpB8li1fjVk/BalkVUojaxFaaR4tfsASiPuD/F7NvtXmKJFPF71vR6Wd7R7gtJXcYS70OguNs5mf+TOMo44sarKO2CAs9hLZPSOYZvDyyJmzJzF9izIXdy/WnYxw8BU0nZoPdJu/thh4Dxa3w/2RKNDa/IERbfoSCgKaOlhykpghwc4PqCntKAHmb4iIGaZuhFzLnYDOfBno2Qz+1tFsoESnZxfdlzynTlkxF1irmK45Ke11KHHw9XYJ4BOXEOgLTuOjfMnFJyH72lrPgZuz0kJamZaGhzBs8QiHBC/HKQK7GrFixRBZ0c0fGuZLYuUeByz7VEMLeulQI6mFzKV96VngjQjpQJRy87mPewFO9d3J+M6NA0GwvXFM65/TqPUjbHkOg2GjIzr+z+R0aEMZRQy/GJLpjQfEDQbJ3Wr2WJcM42zRtOJOb0M5/sTbtxeQD+jrkGAQOV90J/vaH7yAru5jtno/hOs6oxXYV7jmY2bIQLbkvtRuxvIxnaIfQDNFu/WM/wpaGe3hh3LdWgZ/n2IwFiHJbK9zCaMAARyF+L8V4+nqG5LNJQJn4Zt9S5WqQquklHVenzUh5vZqMIvPxLzaOkzmWzxoOz9Vaicf5dCJXaKASrxpqjK+a9BwK2/N0Ao5o3sJxTxNYyrJBLAJ8F+eQJOQfX8+1dl+TZA4W7eD6GSev4cPHBzMa7HoaR3aQRFmU54RQgzlVWcFMu4/qpVWnCJJACAAbGUwrafUHN41zAIuLFF2uschit3+XbGxUK2yDdB6lOeSKay0f0w3SSQuDd9WGAIANo0GJl4GAcCmLM1BWL5Ce4KCeJizTyi8eYOY0zOZs944yAbSUQpHgYJOOWMmJ6WCZ7snqabLYZs39PqZsL9kOleLTNvs9G6i4JCuwvDdAC/aKrwca4ohnI8lp5lPro2UWw57nPsESxGbplRI9awOncKVLNE6ywG0Z+ldIHI6bjVGa0rihaKDGINwL6wHgTwhQjnIsRySuxhv4OavnNive87aeFlmOdo6C+wuZlKI9BX5Ae3izmwzc3iJTsvO0aJx3Crx3B1IOWPgK3PdsKuh8JQkm1XRHyFbsPeDEcuZqR04VS41qi3WCxh+DclgbIhJZ4cO9W2IIKm7ktIyLLBQsbGoqKRoh/Pexz+KMq52gl/NJSgIiiahgcN/xG0QlfOGxVlOjDmXjjmsIbuGYakLMY1xQ8LMEPfx5Q98ysNJY5AWgCHknAtbKvFuaZPF0pP+GVZRfPuJEOSI5xz4vHShvj4Gq5b9iFZJTOuon8CnwrPqZHMUKmeGovn+JdejaCm7twPS+yIFPl98OQeX30NNrj3qYgAYum9k4JhjXc0hEtJGOmxVw/RYTsx6r0MUOLq9cLhDsSf4l7hcJOCWMKX4cG2enYSLPwUU3Z1QZDyVoUraMveOrB2l1r7dVIbY7J3RzgidtcgxMa49/fhysbxz3Jkcf48xwzOvwLW1r+W4ReHB8YMQKe8NtLhAyvYcbpLajLsQ6HCg82YgmM1em8LhmO9E0jz4Zz/XnaSnVuvvYcFvNGr1UuC1btAaOL8JqXM3UqZXVhGLgY2rpRpImWWMq56EljOuD4ggVWMq4IEWJCtSMAJNIAEFjCu/8HArtcIyH6HYSnZYYyvcWTDhwaawF/F0VbF1vMv4kKh3cyNO1uZQBJH4Em5d/ZeRRsVEAhhZycEBf48fDPuExokUlgGrUXeO6BADyETCQAy1qSCwXf763OeqHAKPFb1ZrvgCOLd4lJoElr34qsd23Asqwi0ImBBTd0zFHITK1Q0Y39kgQX+DcS5h8r4Bni6+d3wbRPJo45vxIHK+/Yi1yf5NjePo7ZJyUjtao285xlGqDgISb4Iu0DylBLKuIQKnJLXB0ASI4I4BURkmpiqBwZvUiaGuMB8CFDCOo5RL8VX1/PNKui8/0ug3Uyg/QqEQ6Ztk74ZAzvLy5OVWcZs2UACv2W2PofcBddzvR5TVgLvgEXlnwgbRPVpQvXz9UGsBGB7F0JUvC84XOl3KWGE3Nq0gdqxDoNd5JEe24VwH60EhfB6/mBg1AbcHhFilp6rp73J0CA71s4R+v5bNkdZXWKPTEsk4fXhyt4pJbiB0uX6+8QKklKXAwUzpTtAqskW+FoFfsZQ+IotvkilSayIgKYFfjtmzOwV+Of7l1WuQIRkPiBTl0nzyhQh5zwphrXSbdKErghKrMCZcrUTS79F+gIbWMFbllFbS5fmfB9BZWcH5zWa7w7J/CvJLDHfyY5UYQvzSFFQPd37ECxQfsICwJkjOFDCkzlPGsSP4qh2tiDenMC9QQbYXQUUlflwZq9Pz1TO7H3J24VZCrn5lQ65oSNKrCuZmgArDlGZYJJIYCSTbVVHJXiXQs7rtv5NUwPLkh/vfQtkgfxY799uQ4LWDhn5sQrnnSfdiecXle8yfAHU97K6AKP23TS4eN/lkOKuYXoiBm7VwNPXLFfg0kkbfFBkVy3B5jQAiDT1pyALeOGlCKrk8H6S1wNNDR9X7nwGPmuHlzvfgU+Osdy5HD774LMb0gmzKT3v1AdMwMi1gDMRxmVqA3EURWK3ezfZj+39W37n++TbT76byHdXEOrCzoPkG3ecVNcJXzsuYv1XIJ64E1thXCkwOtT/meEJDNt0QthJdsDO8+Qbp6eQPLv5Ezigw+TytQt1lxTYqAR6XZE7ucOOBHXTppsIw2A+KJFGlDvhuMN84KqmmXJnfkSVX/+YwCOtNVevjZPj+K4xMHEymTQF7P2kQloP7DRbJK0DgxAImtsBNUaLO7AFUeFoDd5VaGdTAB3KbJVtHOTo2zuRo8MhTeF4AqHmAtniigQn8ARehCIIZBS+DYTvLWW23aBFn4lt6wNsK0mhN5G4QUlCTxXyKob/XAkbMfwJDqRe310Vy/D6a2T/AuIzrlX/kuWX+jfCKP5E8Qhmy5k4IgVuOBUXYBAUEH7xitjCak2yulsZ9/xcDdVPcMSaqHo4BAHKuCuuQhfeZsRncoTpTjEkZYqdYgRgkSOSexZlbcsEmMBtIC4aKGbbbg2R5oWI3MaaR+zcVMoRAVIa38b+FE821HG/wsK4wwdJ13wEViAj253kmPAmEgCGnw7D3a1h+A1w2tkNZ4TSXlwZhGf84fPkm0CVbLHdBjjiycy2pajuqWgha4h4KBI8dBPaASwJl026j5hrifydDZv1L104kGZlIDfiQAhy8m3M1tEYO9w5mN0F+BzywyzbI1KulrA4gd9CaC6z9W6gxHLFG4SykP4J/kk0HC51h7FQNt9WvFdF8nXDg7L9pwQmZM8zrhwE+o+Y4l/NbPUtguOctIbhMy7hrHCVuKsyG/YeiimICirD7pfFcNgMv2SdcsS8M0jmQjhmPqqxUdamZKvBJtZIdsAfzkJruQeQLunf1JIFLW7jHoQB3Q6lvfil8AAFwHJFZwiYyTQ/v4ZCrPd6WdWRc+dj07NMbfkRJk+2u+ickNNxqRx1+66RTnIWBCJEm0EgQjoxFpLqLecfQlGIlQS2Yzq08iCzCdN1HsFyTmZj3JYO5Qxvk24mjMco+s2XHDfK1nNM2eW12GZHWYwMpQYkiPW5ixeqgjfUDz1iZpDDZDQ5OWSiu02Uh50szokzQtgA5+aLYgt62MCzU6zpWQrpDWIdPnXHfTMhvAhS5sehQYo+7j3edvz74y1RjWxXzyWxE0pFQ4mH44w93+qOF4wwQ7m1dAFjhrKFw+bGQ8aE+XHRpjYI0RAy9HzR08J9QYkfiyfFVuwnt9pIBc4cKsFGSG3aT1EEiushMPUGxjWc16Juw23tlBJ9uK6diQuiGf76ybgXEcDhzIERdoGeCgd9fjpUMnmSchEgZMvLhHbxnuJw3PiOeJFQoZcetWWlS16UkaoShJ1biAwhXuEuJzLbCmIpqmzEXN+Hbh7pQ3zdDJW2EIZL6DvBDcY1BjallwOSeyOhg95y+NoOApYnSrVTXg9hvRp+ISTshjCthreGhLeFhLeHhJ8LCf8hJPzHkPB+bX+4IiSs6BFq8um8juvLnVLYebI1OL+GcT32MgBLNgM5bIKNzfmBFl2DoUsnvgG4EUVzqMFIbuI97Oy8aABDvkYSUOeXLXaaexhXC9TODFSwzcUKerUC42rI1FJZmVILKS+PmQwZQjg3Vy9LT0AvsFZSpQ/99PpUm26L+gzE7Y6/O1WVlwHGPGUPpSK49CtyqAxavlDVla9qA6S1iCl+rtaANII/OVjj9Xn+cOnL76F6jTxlfnDAYmfQQvY4RL1fn4P1fISyUI9Sc+F7DmWi7qZ+TT0MoTnI0Q3Sy6QNgO3USQDbNyGW57yhHOpHY3MsXT9j0e6JwNDtNAB6prA+Wli/um5jA1ROqdv4CIqD9TPyPNAjjCce20KdmFyYJ4/JgwZUjas0D76gs0gsIBSBgGMQZqyAxaBfR8U8hOXCFdL9COBADfS4lBZ//+/guov9uzMQ/sMNqiwF+3AK9oyKvCz5lLgJnQRRo/UOHmA2HVRje0lsvxr7XxLzqLFiiLkX2+otNB7eSp/1ex6pcLK3cM/2AhtK+w4ob41RttLsN+KmZigQhq3Y5FNEwSHqQFb5DGK+pu3hJSUbS0pBQjDqNpZs3FASHRZmsVh4Ho86CQkltpIyODRNvm2qLauEikBlh81WBk3FTi4pK0Fx/fG8x/Py8mg6wrl69drVq3+m5xiKdkcDuhYArhQZkR6Zryq0+9OCQbS7VFaI95ECVLo9SKj3REK9Y4BQ2eQMGrmmJRqI9+3mGmZLO5QjNPtvBYOI+N8DCaIlmlBxtBUkTqTZRKC/qsYoXcwx2DkzlSX6HamqXvgB8Xj8IIcA0WpArZKRqRyJz5uYyol0/BeOt4idNpqr1zKV40BYQX1SM2qsANr1Pn9gZ8HavJulpdCufaKHpbkrw5hNhyAhaJYGdPsmxAo9llihw9EKXac1Xyz4PjenmlbJeZGxXzVdlKWopoleehtyTktAt6laWBjXYSC4ivJz801IJEI14TQZciP7r3gLfdyfGlA2I7+giWbqvSZLhZNxfbE7oJ56EloTR6ARpkorjFicG2CNisI0baqGEjMMopWWrUbHGJwLoNxwu1kLk67SctVa37eQyFRGxlcFxpGBSxCdmQWSk2sM1OdPMK6XWEQTQl22suhIwLgisGmrERWMz2FuNcgxjOumYzCci/E/MZWGcGBSynQc4fMcukdYH0iOYaZGSMZ2Xr5PQ6mKPmWSSAsy3ZZem0rT/votmvSQpqHh/hix6gX0yjQWGPYNIYg1Aa5KTEZnUCoDOrwEKjQGISs2hcA=
*/