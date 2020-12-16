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
rtZprWzTulinNbRN62ydVss2rZN1mrNtmrIe5W3TlPX480NlmrIeP9umKetxVZnWXlmPT2zTlPU4bZumrMdR2zRlPd6wTVPWY7ttmrIeL9qmKeuxyjZNWY+FtmnKeky3TWM9LNccEpRpXua/I5W/Pc1/j1b+7mr+e6Dydxfz372Uvzub/+6i/N1JxgSxXluZHBabbFCN0WSUcdCeknqN1GvOT5n263VIbHxcVDHqdqsz6rq9LctWt5/OUuqnUr5LsrT1/YksbX2flqWt74lZ2vo+Pktb38OytPU9OEtb3wdlaet7nyxtfe+Zpa3vnbK09b1llra+N8jS1nfXLG19r5Clre9/ZGrr+41MbX2/nKmt7x9nauv7+5na+n44U1vfX8vU1vctmdr6/nymtr4vz1TX97mZ6vr+aKa6vsdlquv7uEx1fR+RWXh9fzDfuH99CSawH1jqe9DZfPU9aarRUIzjeGH7WcR9+ulm6KVbzP1MJ23VeK2hjMNmthTfFS+YrmllK2mbTpqSbFGuk1YE2pc5tv34aI6y3yl1br9tmlLndtumKXVuq22a7Riboz0GPJOjPQak5WiPAfNytMeA6TnaY0ByjvYYEJujPQaE52iPAaNztMeAwTnaY0DvHO0xwCtHewxonaM9BtTP0R4DqudojwH352iPAb9na48B32drjwFfZGuPATnZ2mPAyWztMeBQtvYY8Gq29hiwOVt7DFgj06zHgGXyt/UY8IT8bT0GTJW/rceAicrfneWeiP54lBGV7NT9c6q6r9rlijYOruwDuXn2gVydfSBXZx/I1dkHcnX2gVydfSBXZx/I1dkHcnX2gVydfSBXZx/I1dkHcnX2gVydfSBXZx/I1dkHcnX2gVydfSBXZx/I1dkHcnX2gXM6+8A5nX3gnM4+cE5nHzinsw+c09kHzunsA+d09gGZpuwD8reyD/C3ah/gb9U+cM7uPlC0+1C695vs39/Rv/9y7+5P6d83uXfjZhX3fse9uq+kf5/o3o0Dp38/0f79LP37OPbvc+nfnyr+/Tv9+1D271slupmmxw8b+eqCx/c/W63l0LQ//wjKKP59zBt8v5mj/FaX3+57iQb8t7tpgoxn4oyXsA9exiF4BR/Bqzgev8HJeA1n4XVcgjdwNf6IG/Fn3Ik38QDewuN4G8/gH/gZkqHUa1AKb2EZLEeeymEVLI81sALWx4rYAitjR3TCHuiCvbEaDkRXHIk1MBRrYQy6YwLWxcfQA+dgA3wSGyHrwvgm8htQfhNSXoxfxb9LeTXle87YDPtgCxyCrfARbIPjsR1Oxg44CzvhEuyCq9ETN2I33Ik98AA+iMfRB89gL/wM/fEa9sFbGCDl1R9dMBBr40BshEHYGodgFxyG3jgCAzAYB+NoHI1jMBwfwVgMxWQch9MxAudhJKZhND6N49Eyfpj8lsC+xN5844edlXqWjc3xY+yAudgdP8FeeBGty8soYHnvyfJOYHN8X5Z3CrvjaVleJt5AykPa/aybbNemed5t8aiMR/YYeuA0bIXTcSym8r8YnIXJOAdn4lxcjPPxGVyIL+Ei3IFLcD+m4b9xOWbhSvwUV+G3mI6/4mos6yjjhOHzWAfXYnNcj51xI/riZuyP23AobscxmIEG3IlxuBun4GuYintxAb6By3EfPosHcAMexJfxML6GR/AtPIpH8Vjecj1nv1ybS7m2QA9sia2wNY7FthiD7TEZO+LMPPcNu+Iz6IUvYXfcgT1xP3rjv9EXs9APP8Xe+C32xV+xn5TrAHTGh7AOBmFzHIqdcQT64ijsjw/jUByLYzAEDRiGcRiOU9CAqRiFCzAGl+MEfBYn4gaMx5dxEr6Gifg=
*/