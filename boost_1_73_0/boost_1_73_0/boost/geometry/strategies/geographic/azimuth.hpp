// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2016-2017 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_AZIMUTH_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_AZIMUTH_HPP


#include <boost/geometry/srs/spheroid.hpp>

#include <boost/geometry/strategies/azimuth.hpp>
#include <boost/geometry/strategies/geographic/parameters.hpp>

#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_void.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace azimuth
{

template
<
    typename FormulaPolicy = strategy::andoyer,
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
class geographic
{
public :

    typedef Spheroid model_type;

    inline geographic()
        : m_spheroid()
    {}

    explicit inline geographic(Spheroid const& spheroid)
        : m_spheroid(spheroid)
    {}

    inline model_type const& model() const
    {
        return m_spheroid;
    }

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

    template <
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

        typedef typename FormulaPolicy::template inverse
        <
            calc_t,
            false,
            EnableAzimuth,
            EnableReverseAzimuth,
            false,
            false
        > inverse_type;
        typedef typename inverse_type::result_type inverse_result;
        inverse_result i_res = inverse_type::apply(calc_t(lon1_rad), calc_t(lat1_rad),
                                                   calc_t(lon2_rad), calc_t(lat2_rad),
                                                   m_spheroid);
        if (EnableAzimuth)
        {
            a1 = i_res.azimuth;
        }
        if (EnableReverseAzimuth)
        {
            a2 = i_res.reverse_azimuth;
        }
    }

    Spheroid m_spheroid;
};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<geographic_tag, CalculationType>
{
    typedef strategy::azimuth::geographic
        <
            strategy::andoyer,
            srs::spheroid<double>,
            CalculationType
        > type;
};

}

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

}} // namespace strategy::azimuth


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_AZIMUTH_HPP

/* azimuth.hpp
yDRrC3ieB5Y1l949rlddgrKGCJzywN9kfSXnLa6fdj50umcdwfbKHPXDZW5padPS4dxB4zVVwmJp/6fa+2GQhfvDobMtSPycnHyKriHODz6O4294hrLYpy7PjZKnhKFHmfF9+kMKHQ+n41kod43HeE4wAxv4VJy1s9LhblXu/xV2xEzUZ3Qy/byz9dPPCzauqXy89LqBkyocAFKhi10SKMCbKy80Xzx6kLBG8kkPLm7P3zxvWrvgyIuGMLaSBzwrzk/lzKIGWQfTy1rlobd8jcd8wuvK5JeRygj5rrosgS8FXw2b+AmbkSqTBwp1iSKwQ4UK+KNRHEcgQhb/pfi3zA7i+WmyT80ihkU4VhajWXAYi4CdPLG24kZC3jGgij4tUrmfED+l+wktu7LEnkLdOtpS8vY5DsFMA84Zchs7ZZnDhfmpKq5L7/L3YrzEczXe5y70f9hfyv6SJOEDGbqYlVqbC7mpOsHl8ic1RYjx8xU7msgY5XbJFfwPz6/MUBk/wvBnkykHVhdSfiUGapBqPebUMi8qhomj8JanWMg4yIw5Xz5ZADAE/DekDkRs6FTb+JOVXlW+95UVvDfPm/gFPQkxIDXF+NOwk6dFdnE5ABzOTaaRDaRi1ZEQNaGLagpIy8XmWFRULuZYFb5m
*/