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
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
*/