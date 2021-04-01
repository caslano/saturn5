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
rIcJC0qkQQ4+jHjb8snYGNXowahCFuTZ5TAhnvifFMEqMloj9JWZwCSgSn39SL/nD+BiNPEM8YelB9bLMHtkAEMVHK/AWHHRI8g/VEqnVFra0A5cT8URS8fvm0LnF10yp+WOTu/dL3gRvW7+aGWXxPTusNRX3LzEZ3AXJmBgpdpdyHsK7Jl8StWJ9AC468zknVHwKqjv0nOBVbFZJ7fCza+8GxunVVvAbnvrPkPwYjz4XuOACC7q4rlVwk7Uzf5tfKIp+h156yLwp0NeqbiG4GTDlj8b8Gun4cqSExotWiXkmeJZw2KxJaIZw81QDGbnaVigaE4WSMiI1VSQqPjA7pqC81e7gw9aargwFmxfjiLVyNcPS2ZLv2QexczvTUF0i4oFvKi02zLbsEJJFA2joFhUTaFIsoDvF2GO28GWlmChIAo+gKNhEhKcpUN+TGrA+gcZ38V8oIBi4Db++nsF3Djor63fNlexQXxF2WyHbYPQBk+QRYlVGYYhVzmaxA5V2fIFxrU/glJOjYwwOHNktZzbTGzCT3huAoTxO7+H2PmONrAnClTUQwUOrw==
*/