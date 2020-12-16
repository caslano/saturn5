// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// Copyright (c) 2016-2018 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_AREA_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_AREA_HPP


#include <boost/geometry/formulas/area_formulas.hpp>
#include <boost/geometry/srs/sphere.hpp>
#include <boost/geometry/strategies/area.hpp>
#include <boost/geometry/strategies/spherical/get_radius.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace area
{


/*!
\brief Spherical area calculation
\ingroup strategies
\details Calculates area on the surface of a sphere using the trapezoidal rule
\tparam RadiusTypeOrSphere \tparam_radius_or_sphere
\tparam CalculationType \tparam_calculation

\qbk{
[heading See also]
[link geometry.reference.algorithms.area.area_2_with_strategy area (with strategy)]
}
*/
template
<
    typename RadiusTypeOrSphere = double,
    typename CalculationType = void
>
class spherical
{
    // Enables special handling of long segments
    static const bool LongSegment = false;

public:
    template <typename Geometry>
    struct result_type
        : strategy::area::detail::result_type
            <
                Geometry,
                CalculationType
            >
    {};

    template <typename Geometry>
    class state
    {
        friend class spherical;

        typedef typename result_type<Geometry>::type return_type;

    public:
        inline state()
            : m_sum(0)
            , m_crosses_prime_meridian(0)
        {}

    private:
        template <typename RadiusType>
        inline return_type area(RadiusType const& r) const
        {
            return_type result;
            return_type radius = r;

            // Encircles pole
            if(m_crosses_prime_meridian % 2 == 1)
            {
                size_t times_crosses_prime_meridian
                        = 1 + (m_crosses_prime_meridian / 2);

                result = return_type(2)
                         * geometry::math::pi<return_type>()
                         * times_crosses_prime_meridian
                         - geometry::math::abs(m_sum);

                if(geometry::math::sign<return_type>(m_sum) == 1)
                {
                    result = - result;
                }

            } else {
                result =  m_sum;
            }

            result *= radius * radius;

            return result;
        }

        return_type m_sum;

        // Keep track if encircles some pole
        size_t m_crosses_prime_meridian;
    };

public :

    // For backward compatibility reasons the radius is set to 1
    inline spherical()
        : m_radius(1.0)
    {}

    template <typename RadiusOrSphere>
    explicit inline spherical(RadiusOrSphere const& radius_or_sphere)
        : m_radius(strategy_detail::get_radius
                    <
                        RadiusOrSphere
                    >::apply(radius_or_sphere))
    {}

    template <typename PointOfSegment, typename Geometry>
    inline void apply(PointOfSegment const& p1,
                      PointOfSegment const& p2,
                      state<Geometry>& st) const
    {
        if (! geometry::math::equals(get<0>(p1), get<0>(p2)))
        {
            typedef geometry::formula::area_formulas
                <
                    typename result_type<Geometry>::type
                > area_formulas;

            st.m_sum += area_formulas::template spherical<LongSegment>(p1, p2);

            // Keep track whenever a segment crosses the prime meridian
            if (area_formulas::crosses_prime_meridian(p1, p2))
            {
                st.m_crosses_prime_meridian++;
            }
        }
    }

    template <typename Geometry>
    inline typename result_type<Geometry>::type
        result(state<Geometry> const& st) const
    {
        return st.area(m_radius);
    }

private :
    typename strategy_detail::get_radius
        <
            RadiusTypeOrSphere
        >::type m_radius;
};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{


template <>
struct default_strategy<spherical_equatorial_tag>
{
    typedef strategy::area::spherical<> type;
};

// Note: spherical polar coordinate system requires "get_as_radian_equatorial"
template <>
struct default_strategy<spherical_polar_tag>
{
    typedef strategy::area::spherical<> type;
};

} // namespace services

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::area




}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_SPHERICAL_AREA_HPP

/* area.hpp
RZSM3XAV9sTVsj9bg5MwRY6Xa3EVrsO1+CQewfX4DG7QzqvlnjJ+qHPcni6f2RSBbXAmtsdI7IFROAijcSbG4jw04nycg09gvNRnHj6FibgVH8PtuAj34GI8iUvxPHIsku+plPvE6CzL0fJ7KlPprwFuxuaYJucXO7AT7pT67sJ+mIE+uBun4B6chntxFmbiAtwn9d+PG/CA1PsQfoWHsSb1ycb/snfncVHUfQDHUfHIA4EUUFHxyBMVb7zxJkXFW9MEBBQUYYUlUVHRMG/DM0szKlMq8/GqKK0orcisqKzHq8LU8ikrMi1L0+czs9+d3WFnZbF6Xs8f8vLrG2Zn5vebmd/MzszO77t34x6siXvRF/fhBXfnuXsqcSJlQmuOn2b8Ld+R5DTHwEWneXscvwspbM7fn8Mnc66zPD7G32OUfRv5fGrYfWfRKML4e4pKzuuT39v13D7yXUTyPUSlz/NzkNB935ALOX/6KSfSmPV/lv/H9h1Bf+37gVz5biBXvxdI8jbYfRfQ35cjKICQ7/3R5QraWYp8QVd7O80ZVKp8Qdr39RATaR+ZRA6RT1wgPLnoCiYmEplENpFHXCDcfuM7OYgQIpLIILKJPOIiUekq3y1ChBEJxEoih8gnzhGVfuc7QohwwkRkEfuJo8QFouofvE6MItKILcRh4hzhfu1OHos7P3d+7vzc+bnzc+fn//HnH+7/Tzeuv97/35oPn/Mz7qHFSCJzpV5mHjWNZrTk2BTlWUh9Ony3Jky3w5fpeml5AdRuZRHmqMkJsfIH4zVkvBzGK1Lmbz+e5ZFRS58mxtnHWrpgG4dybWO04PVUxjunve5QyYikxOhYNynvWcrLCDGs14yoaMs4zzFO1njr/GLip8ammLUSZT7PK8tnPJ/paTLOTsYJ6m04TlSqOU5dtheU+rSzlkUVIkzTY2dHxMfIPHid817711Nio5UVnRI/J1bWzy7GManlSBlRCfFkaNfWXyoG3Kduw/gUpfiYiNjEaGaWMl17vbHudV6T1xvK682KvU4lLSPwYx0nUDeOuozaON48f5uKfUeMDx81LGLY0L791RwRv3jZckSElpdnGSpyTSW+o6zDFtxvkD6894aH9h8RERObEp0cb//MXQ4678tVFbhWCmI+dn/nyN/ePIX9cqD6e+OwofSxlWHbbcOCrMM2aMPadbEOy7QNC7YOS7EN62wdNtk2rJN12HDbsI7WYT1swzpYn8XdjavVZ+tk95Fn5HLRZHkuO3WKDMvD4s/cbbI9Dx2bLMPStGFsbilnKVqeQ4xKmKpuZsu4Gdq4UanWOmXpxqVJyfD1uuEyb9a5Mn2a2tanJCXzJKh1Pivtx1ebjcPzhMxbnifUhqm7mS7vxOnyjn1s8/klpH3x9kNWjxjX+3rZ5TDQnrlspg4z0bfa8kxsrFoGn0P46vulR1aw5Tz1JgYTR5R93qFOU2PNll2GznUlP3vsIc9MSpvgb/vn8eN1ff6v29XBV+pwlF+KDOswOd6cUvJzrFKeVr6PtY9jBdmOMh95Lpt66XN39JG6ZVaU+7+yfsbK+onsYFQ3Ob6xhlzp3+DKOrLWo2ol4+1UaFQPeU/4O+th3VbpUg8PojxRjfjAl3p1NKpHfIwr31uilFfJVr6ufbrdZbzcJqPyeGv7J5bZJHUIkGWuT3yorHvDOijPR/+1ZT4n5YXJMg+U8jw7GZUn/T1c+D4VydujlWm/jKOk/38XKbODdT07lBmfEhEVGxXjwrPkxfZB6Usu+7yUd5aZ++CXWEB5eXblDRsSHhEVE2N/JienOa73JZbtGQNaX+K+3pa+D/Z5O0yWYZTkpt/20ve/umx7D+Jj6hnQRV8=
*/