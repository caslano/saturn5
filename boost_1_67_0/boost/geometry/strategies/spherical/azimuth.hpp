// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2016-2017 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_AZIMUTH_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_AZIMUTH_HPP


#include <boost/geometry/strategies/azimuth.hpp>
#include <boost/geometry/formulas/spherical.hpp>

#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_void.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace azimuth
{

template
<
    typename CalculationType = void
>
class spherical
{
public :

    inline spherical()
    {}

    template <typename T>
    inline void apply(T const& lon1_rad, T const& lat1_rad,
                      T const& lon2_rad, T const& lat2_rad,
                      T& a1, T& a2) const
    {
        compute<true, true>(lon1_rad, lat1_rad,
                            lon2_rad, lat2_rad,
                            a1, a2);
    }
    template <typename T>
    inline void apply(T const& lon1_rad, T const& lat1_rad,
                      T const& lon2_rad, T const& lat2_rad,
                      T& a1) const
    {
        compute<true, false>(lon1_rad, lat1_rad,
                             lon2_rad, lat2_rad,
                             a1, a1);
    }
    template <typename T>
    inline void apply_reverse(T const& lon1_rad, T const& lat1_rad,
                              T const& lon2_rad, T const& lat2_rad,
                              T& a2) const
    {
        compute<false, true>(lon1_rad, lat1_rad,
                             lon2_rad, lat2_rad,
                             a2, a2);
    }

private :

    template
    <
        bool EnableAzimuth,
        bool EnableReverseAzimuth,
        typename T
    >
    inline void compute(T const& lon1_rad, T const& lat1_rad,
                        T const& lon2_rad, T const& lat2_rad,
                        T& a1, T& a2) const
    {
        typedef typename boost::mpl::if_
            <
                boost::is_void<CalculationType>, T, CalculationType
            >::type calc_t;

        geometry::formula::result_spherical<calc_t>
            result = geometry::formula::spherical_azimuth
                     <
                        calc_t,
                        EnableReverseAzimuth
                     >(calc_t(lon1_rad), calc_t(lat1_rad),
                       calc_t(lon2_rad), calc_t(lat2_rad));

        if (EnableAzimuth)
        {
            a1 = result.azimuth;
        }
        if (EnableReverseAzimuth)
        {
            a2 = result.reverse_azimuth;
        }
    }
};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<spherical_equatorial_tag, CalculationType>
{
    typedef strategy::azimuth::spherical<CalculationType> type;
};

/*
template <typename CalculationType>
struct default_strategy<spherical_polar_tag, CalculationType>
{
    typedef strategy::azimuth::spherical<CalculationType> type;
};
*/
}

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

}} // namespace strategy::azimuth


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_SPHERICAL_AZIMUTH_HPP

/* azimuth.hpp
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
*/