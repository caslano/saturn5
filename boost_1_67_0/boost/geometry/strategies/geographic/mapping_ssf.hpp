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
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
*/