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
rU1bbJkuK+gvh1ZCgEpU30/6CFgsNjGSTAxqb113tTGIpG1oczDk8UKsSeikC/Vgna4Qgc3vqw77Ww7Z0Wtr8d7/hxiDdY8R7uIyOKZCTyY+54BJyJP1xWVA6VF0A9mbWaieoVbO5JQJj3KJpD/ExnVL8vNt/eCEedG8jGGbKWa4i+C9GrQhgjlWeeMW6h7yBoFQ8KDIUl7dALAbKIYcHgRkTdOZgrFkM8/PNs64UwnqBVCi0eC9WhWidnUvKGD/qal7M6xxl5hbsBPWTrqy6MDSaARItlHYi4TXLHQt1qRgUiP4H0CstWp2IEO38X+i83INgAG7/jxLejQ8H+PzsjV9aAKiVMLCdeYf+4x3x7ePV3tiomnKud2zn85GaT5pg+R5LAfcSO/xlg1qipNhHsSGXBJjW9waGG3Kj4dLsYfSY8fLd5unnrsgvGW/I+irfK3PJGO+/2qLD+H26DgDSZceFKKWqY+3apM7Gj7PTXn3N72Y3bAJaS0974sU8s+noBYwE0uvwVIZIe9t3SPVUQqhvSXEq2RbWqE6VEz4wwHRPERkNzXR1y09tQ==
*/