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
fzzNNjqxFlq7lp1qJolcDySQVMLPUhb38Fd4tnklWDzy5jzKKmoGz/rgwl+3rw0LoTOEcPxumsRjcjimqOzUnNJAiXE/8iXxhowFTAlGSrz66xZ0639rC5Py+/ZC6rqrAmm+FYRxw9xhWDB7mP4pt/Hg5hUVTKw7mGpHHNJ7HHFb7As1oe7tEk4vHaifgtMM1NMR9XJWPBxUPXgqDNZvqV2dzLEGdsMQbwNTl36Z4y0Fn5G6zn2gZN2DykfIO96IdJXsJga+fOPiAUBT0fbUutskQSprRY7zbbbCrbWnrI7Wsbf4ZLeWZXRpp9JrLPZzcdNijknPp9QtGXq9xLN5S34tfp8r2FYZz+iyKq9eoPaA1eib+0ltkHxvDbzlavgJIalxrHxM0Cfo9NxW6YuGEBdQOkAAfTif/fY12GAXGCpsj4hfcuB2Noj32k5uoRSdcJcI7PklpF60ByddHoEXZCSJaAfhohsb9wGDfrx0IxzYU19AX168P80aVx5Y2qne1+u9ghO8Xeoo6WV82BvRpnfmvAHyG+1Cscgnni883pk/5M/ypRwrIICcz5vbw6HpDN70NLhP6X2jr0amoFoyCun52Y8maPAJQDtDxKcIWNpJ8In2NsI0KxEB/HsahOVnOtHm/0Xmd//195HgP6n5371OAclLnuLQ5hhHB0pUJuSfUqRmtCYJYWDl8f40RtkSCZayt1SWMss0MpXs
*/