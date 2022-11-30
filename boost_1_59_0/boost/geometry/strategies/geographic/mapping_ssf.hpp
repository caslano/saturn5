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

#include <boost/geometry/core/coordinate_promotion.hpp>
#include <boost/geometry/core/radius.hpp>

#include <boost/geometry/util/math.hpp>
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