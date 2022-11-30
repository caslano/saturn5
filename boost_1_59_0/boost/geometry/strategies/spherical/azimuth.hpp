// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2016-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_AZIMUTH_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_AZIMUTH_HPP


#include <type_traits>

#include <boost/geometry/formulas/spherical.hpp>

#include <boost/geometry/strategies/azimuth.hpp>

#include <boost/geometry/util/select_most_precise.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace azimuth
{

template <typename CalculationType = void>
class spherical
{
public:
    template <typename T1, typename T2>
    struct result_type
        : geometry::select_most_precise
              <
                  T1, T2, CalculationType
              >
    {};

    template <typename T1, typename T2, typename Result>
    static inline void apply(T1 const& lon1_rad, T1 const& lat1_rad,
                             T2 const& lon2_rad, T2 const& lat2_rad,
                             Result& a1, Result& a2)
    {
        compute<true, true>(lon1_rad, lat1_rad,
                            lon2_rad, lat2_rad,
                            a1, a2);
    }
    template <typename T1, typename T2, typename Result>
    static inline void apply(T1 const& lon1_rad, T1 const& lat1_rad,
                             T2 const& lon2_rad, T2 const& lat2_rad,
                             Result& a1)
    {
        compute<true, false>(lon1_rad, lat1_rad,
                             lon2_rad, lat2_rad,
                             a1, a1);
    }
    template <typename T1, typename T2, typename Result>
    static inline void apply_reverse(T1 const& lon1_rad, T1 const& lat1_rad,
                                     T2 const& lon2_rad, T2 const& lat2_rad,
                                     Result& a2)
    {
        compute<false, true>(lon1_rad, lat1_rad,
                             lon2_rad, lat2_rad,
                             a2, a2);
    }

private:
    template
    <
        bool EnableAzimuth,
        bool EnableReverseAzimuth,
        typename T1, typename T2, typename Result
    >
    static inline void compute(T1 const& lon1_rad, T1 const& lat1_rad,
                               T2 const& lon2_rad, T2 const& lat2_rad,
                               Result& a1, Result& a2)
    {
        typedef typename result_type<T1, T2>::type calc_t;

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

template <>
struct default_strategy<spherical_equatorial_tag>
{
    typedef strategy::azimuth::spherical<> type;
};

}

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

}} // namespace strategy::azimuth


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_SPHERICAL_AZIMUTH_HPP

/* azimuth.hpp
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
*/