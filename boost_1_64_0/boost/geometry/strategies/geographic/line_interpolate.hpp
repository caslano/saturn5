// Boost.Geometry

// Copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle

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
    geographic()
        : m_spheroid()
    {}

    explicit geographic(Spheroid const& spheroid)
        : m_spheroid(spheroid)
    {}

    // point-point strategy getters
    struct distance_pp_strategy
    {
        typedef distance::geographic<FormulaPolicy, Spheroid, CalculationType> type;
    };

    inline typename distance_pp_strategy::type get_distance_pp_strategy() const
    {
        typedef typename distance_pp_strategy::type distance_type;
        return distance_type(m_spheroid);
    }

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
y+MdWR75sjzek+VxTpbHeVke78vyuCDL46Isjw/RvD/NvWG7nebzsj89KcfZU+iOp7Et5qKUw0WLqRxPnXK6yvlVN3TG7uiCj2JH7IHmcnzuUE57KaeDlNNRyvGUcjpZPhf+2Xa7P2dZzxpiLWyE2vr5s+32SmOkHd5YrI3jUFs/f7a9flavZBquBtpjTdSuu0rkPQud42W4bK/TsT7OxFYYiT0xCgdgNPrhLAzAGNSOAyW2z3u/lPn5lZz3XrWcfyW221t+IMNdREf8ELXzlBLbx/9n5Pj/rBz/j8vx/zk5/p+Q4//zcvw/iQY8hdr68Yup/Fk660fTqqb9YjNsiK7YBFtgBLqhuZwCKWe5Tjnu9FcH22ICPoLz0QMXYXspJ5+k/GoqZ5FcJyrzI8/cLlXOw8rR/2AojyOxIk5EO5yFlfExrILLsBoewpr4ItbCc1gbP8UH8Fu0xxJ0QKUSdbAK1sXm+BB2x3o4Eh0xEJ0wFB/GeKyP87EBauvNTdvbTwvZflrK9uOG2npz0/b2M1Da2w5CtVzUtrubto8LX8h29yU64FeW291N29eDn8n28zk2w8sWw7ncsr29XpLxfYz2+Alq53F3GG6vzJdMtMd9qJ3H3bLdHqORnDc2xkboYrFfTZHheuisp74yfRNRGW4qtsMA7IKBFvd3Cm7Z3s/ESTmzZT+TIPuZubKfmSf7mUTZz8yX/cwCNF8XBfxuKr9S+bLXRVcqmOr1HT6K32Nf/AF98EecjD/hHLyO6/AG5uDP+A6W4DX8BbX3Wf6w/TyhgRyPXeV43Bw9sCX2QzfU3sNhiZTH/jrLZ08FUzl7sTdmonZfgT5tbSd5sp98BWvhq+b2VvSUIsPxTgHDmeZVG1Rvh8r4amJ9rIW9sDYOQHuZbw5oxDo4Dx/CTVgPt6MjZuDD+DTWxzxsgFfRGf/AhliZyrhgI2yKntgMh6IrBmBznI0tMBlb4k50wyPYEd9GT/wYO+Hn2AVLsCvaK+95oRt2x174KI7HHhiBPTETe+Fb2Bu/QC+8hX2xtvK+FzbE/tgUB2BvHIijcRCG4WBcgENwPQ7FnTgMj6A35uJwvIAjsQB98AccheXtuLeBDjgGXXAsdsZxOADH4zicgAb0xTiciEtwEq7Gybgdp+AhnIpXMBB/wiAswWC0ZwUKxcY4DcfhdAzBGRiOEbgQZ+FaNOIBjMOPcQ4WYjz+gAnYujLbNQ7CBTgBH8NQXIgLcBFuxCW4F5fhSVyOL+JKLMYnsALrcTJWwdXYHNdgS1yHvfFJnIAbcRpuxlX4FK7Bbcr4MB3TcQfm4U58FXfJdpdKfKqbtp9fZbuzx2RzuxnluTbWQzd0RG90wvHYAA3ojOpnl+Lj2ATXY1Pchs3k+bkrHsLmmIst8SK64UfYCq+jO2rXbzVM9XPX2S88IPslR2yBTmi+75wvw1XWue/8q9xH+w3d8CZ64y0cj+VkusrjLKyA8VgJN2JVTMdquB+r41GsgSewJp7F2ngFH8Av0R7LK+cXaL6ucqllquconeuq6ZVN0zcDXTACH8FIfBSjZXnMsigv5Q7lGaW8OClvtpQXL+XNlfLmlc5/JsJUXled+b9AyluMHXGJDHec+MhwRpn/ynVPlgw3TM4nR2ArHIO9cSyOw3H4EvriBZyIn+AkLEA//AWnYEXlOTlWRX9sggHojoHogSFy/mbAvhiGozEcZ+B0jMIZqN0ft69o8/zktByPctEeX7Ro/+vDcLba9z9kJ+3QsDk6Ykd0Qu28j+Ftnd98K+1iC7EpXrO4XsiX4ZbrnJc0kPE2lvM3F+yOTXEwNsPx2AKDsCUuQjfL6x+Hijbb1zFqtXwH9MA6qN0=
*/