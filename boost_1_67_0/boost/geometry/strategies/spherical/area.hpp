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
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
*/