// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2011-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014, 2017.
// Modifications copyright (c) 2014-2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_MAPPING_SSF_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_MAPPING_SSF_HPP


#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/core/radius.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/promote_floating_point.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>

#include <boost/geometry/strategies/side.hpp>
#include <boost/geometry/strategies/spherical/ssf.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace side
{


// An enumeration type defining types of mapping of geographical
// latitude to spherical latitude.
// See: http://en.wikipedia.org/wiki/Great_ellipse
//      http://en.wikipedia.org/wiki/Latitude#Auxiliary_latitudes
enum mapping_type { mapping_geodetic, mapping_reduced, mapping_geocentric };


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename Spheroid, mapping_type Mapping>
struct mapper
{
    explicit inline mapper(Spheroid const& /*spheroid*/) {}

    template <typename CalculationType>
    static inline CalculationType const& apply(CalculationType const& lat)
    {
        return lat;
    }
};

template <typename Spheroid>
struct mapper<Spheroid, mapping_reduced>
{
    typedef typename promote_floating_point
        <
            typename radius_type<Spheroid>::type
        >::type fraction_type;

    explicit inline mapper(Spheroid const& spheroid)
    {
        fraction_type const a = geometry::get_radius<0>(spheroid);
        fraction_type const b = geometry::get_radius<2>(spheroid);
        b_div_a = b / a;
    }

    template <typename CalculationType>
    inline CalculationType apply(CalculationType const& lat) const
    {
        return atan(static_cast<CalculationType>(b_div_a) * tan(lat));
    }

    fraction_type b_div_a;
};

template <typename Spheroid>
struct mapper<Spheroid, mapping_geocentric>
{
    typedef typename promote_floating_point
        <
            typename radius_type<Spheroid>::type
        >::type fraction_type;

    explicit inline mapper(Spheroid const& spheroid)
    {
        fraction_type const a = geometry::get_radius<0>(spheroid);
        fraction_type const b = geometry::get_radius<2>(spheroid);
        sqr_b_div_a = b / a;
        sqr_b_div_a *= sqr_b_div_a;
    }

    template <typename CalculationType>
    inline CalculationType apply(CalculationType const& lat) const
    {
        return atan(static_cast<CalculationType>(sqr_b_div_a) * tan(lat));
    }

    fraction_type sqr_b_div_a;
};

}
#endif // DOXYGEN_NO_DETAIL


/*!
\brief Check at which side of a geographical segment a point lies
         left of segment (> 0), right of segment (< 0), on segment (0).
         The check is performed by mapping the geographical coordinates
         to spherical coordinates and using spherical_side_formula.
\ingroup strategies
\tparam Spheroid The reference spheroid model
\tparam Mapping The type of mapping of geographical to spherical latitude
\tparam CalculationType \tparam_calculation
 */
template <typename Spheroid,
          mapping_type Mapping = mapping_geodetic,
          typename CalculationType = void>
class mapping_spherical_side_formula
{

public :
    inline mapping_spherical_side_formula()
        : m_mapper(Spheroid())
    {}

    explicit inline mapping_spherical_side_formula(Spheroid const& spheroid)
        : m_mapper(spheroid)
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
            >::type calculation_type;

        calculation_type lon1 = get_as_radian<0>(p1);
        calculation_type lat1 = m_mapper.template apply<calculation_type>(get_as_radian<1>(p1));
        calculation_type lon2 = get_as_radian<0>(p2);
        calculation_type lat2 = m_mapper.template apply<calculation_type>(get_as_radian<1>(p2));
        calculation_type lon = get_as_radian<0>(p);
        calculation_type lat = m_mapper.template apply<calculation_type>(get_as_radian<1>(p));

        return detail::spherical_side_formula(lon1, lat1, lon2, lat2, lon, lat);
    }

private:
    side::detail::mapper<Spheroid, Mapping> const m_mapper;
};

// The specialization for geodetic latitude which can be used directly
template <typename Spheroid,
          typename CalculationType>
class mapping_spherical_side_formula<Spheroid, mapping_geodetic, CalculationType>
{

public :
    inline mapping_spherical_side_formula() {}
    explicit inline mapping_spherical_side_formula(Spheroid const& /*spheroid*/) {}

    template <typename P1, typename P2, typename P>
    static inline int apply(P1 const& p1, P2 const& p2, P const& p)
    {
        return spherical_side_formula<CalculationType>::apply(p1, p2, p);
    }
};

}} // namespace strategy::side

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_MAPPING_SSF_HPP

/* mapping_ssf.hpp
R6Gjrfsvh2W4bGyLR2S4M8S+jmy/cv+snnIdI8N1l/ckemBr7ImPYi/sh71xLHrhdOyDMdgXE3AA7sKBeBAHYQ4OxVdwGF7AUViHSkzC1eiHGTgFX8cAPIeBeAWD8DqGYHnqbUDz86X0uqbpmajzfKlA2kt8ho3wc2yNl9ETr+BQ/ALH4pdovr9h/1BFm+/LvCrvy7yG3fEMBuPrGINv4EZ8E7fiW5iF7+AhzEdze48iGc+3Ou093OU+SgfshR2xH3bDCdgdA7E3xqAXLsQ+qD4/x2dxCL6KQ/EMjsAPcCR+iT6W1x2OFW2+JzBI3r8ZjF1wCGr3nWS453Xm1zfy/ss1nIlFGIc/4Dz8EVfiT/J8qFieD93AZ/BnNC/vACfby/trWd7fyPL+VpZ3oSzva7K8v5Pl/T2arw/ypdwTOs9NSh4wTfct7KVumKbtuQKGYiWMxGr4OFbH1VgLt2NtzEZ7fBod8Ee5Jsx92DTe6jLeCugs431D2rO/jdp2T/+22vfXl/deGmADdEYZjn/aHq6xDOciwzXRhiP1ba8P78h7I/nYBd9Fc7vbJBlul06720XK835cLNeFS7AlLsNuuAL74Eo04OM4DZNxAa7Cdbgat2AKbsO1aD5e+zSoaPO9lf/IeyuX0A0/xm74CQ7FT3EkFqB2/S/leejNd2kX1gDd0RllOP6wPd+frGWa7+tlPm5Abb472x7fHLmvFY/umIDa9d4dhlsuw62Q4R63fA+Z4Wy9p9JO2tc+go+iB2rT19D29A2U4+ogVN9XR2367jCcnww3RYabajFcAMPZfA9ClkMFWQ4VUTv+y3D1dIZzlPdUnPAhfBi15c5wtu5PVqpkGq4yOmEVNO/XC2S4L3X26/tk/d8v5ysHcSIewhmYjbF4BDfhUXwKc/AoPo0v4jP4Mj6Lb+FxvITP42d4ErXl1Nj2+c+nMr8L5PznM8vlxHC23rd5T/ZP57Axnrc4bwqQ4RbqnDe9WkGOn9gMz+AgfAOH4VmchG/J/ZZ3MBHzUbsf4mJ7eTaR5dlUlmczNF+Xechw3+lclw1Tns+hNzbGEdgRR2If9MGROBr9cQxG4ThMxPH4OE7A7TgJD+NkfBn98BxOwS/QH7/GANTW7ya21+8qsv1Wle23Gmrr9x2GqyHbRU3ZLmqhdp+Z4Wy1c/9FniP8ig3xN1lfb2JnvIXaetLU5vgp1DT+8uiOFVDbXzW1vX3tlOW4C50wA83bV0pT29vXetm+Nkh9U2X72izb11OyfaXJ9rVVtq/tsn2ly/a1Q7avnbJ97ZLta7dsX3vQvF5lNzPV5xed9WqoXM+NxkY4BvviWPTGCTgJfTEeJ+Mi9JPr/imYhv6YgwH4DAbi6xiMb2IIfo8GLMZpqLV/ca1o872qA3I/75DcPzyM/fAoxuExud+Zg+b3GrKbm8r7ndz+XkMjWU8by37BBVtgU+yNzTAYXXE6tsA12BI3oRu+iK3wA2yN/0F3/BjbYDG2xV+wHWrvTbYw1auWzvrkLve/22BNbIuyHTBy03CNdLaDNfJ8LAXr4lpsgE9iQ1yP2nbQ0vb91p9k/MVYC6/L+DOJjwzXVq7r6yjrp/n4K/eLHkE39JD1pr3cL/JEA3bCWdgZN2AX3I7d8RT2xNewF76LvfFD9MLPsA/+hP2wBvXoj7VwALrhIIv1Kd+t9H5ILrFcny6WM61PH+LD+BG2w//gALyE3siylPlPWpnKG6Qz/3PKy/s2qD6fw0fwOPbF5/BHLCHpUs4UmY9K/4Xm8x9p37cS6+MT2AyTsQ2uwk6YgqNxLU7AJzEM1+NS3ICrcCOuw1TcgZtxH27BQ5iG7+FW/AK34zVMx+9xJ1Y=
*/