// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2016-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_AZIMUTH_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_AZIMUTH_HPP


#include <type_traits>

#include <boost/geometry/srs/spheroid.hpp>

#include <boost/geometry/strategies/azimuth.hpp>
#include <boost/geometry/strategies/geographic/parameters.hpp>

#include <boost/geometry/util/select_most_precise.hpp>


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
public:
    template <typename T1, typename T2>
    struct result_type
        : geometry::select_most_precise
              <
                  T1, T2, CalculationType
              >
    {};

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

    template <typename T1, typename T2, typename Result>
    inline void apply(T1 const& lon1_rad, T1 const& lat1_rad,
                      T2 const& lon2_rad, T2 const& lat2_rad,
                      Result& a1, Result& a2) const
    {
        compute<true, true>(lon1_rad, lat1_rad,
                            lon2_rad, lat2_rad,
                            a1, a2);
    }
    template <typename T1, typename T2, typename Result>
    inline void apply(T1 const& lon1_rad, T1 const& lat1_rad,
                      T2 const& lon2_rad, T2 const& lat2_rad,
                      Result& a1) const
    {
        compute<true, false>(lon1_rad, lat1_rad,
                             lon2_rad, lat2_rad,
                             a1, a1);
    }
    template <typename T1, typename T2, typename Result>
    inline void apply_reverse(T1 const& lon1_rad, T1 const& lat1_rad,
                              T2 const& lon2_rad, T2 const& lat2_rad,
                              Result& a2) const
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
        typename T1, typename T2, typename Result
    >
    inline void compute(T1 const& lon1_rad, T1 const& lat1_rad,
                        T2 const& lon2_rad, T2 const& lat2_rad,
                        Result& a1, Result& a2) const
    {
        typedef typename result_type<T1, T2>::type calc_t;

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

template <>
struct default_strategy<geographic_tag>
{
    typedef strategy::azimuth::geographic
        <
            strategy::andoyer,
            srs::spheroid<double>
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