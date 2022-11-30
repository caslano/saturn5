// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// Copyright (c) 2016-2020 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGY_SPHERICAL_AREA_HPP
#define BOOST_GEOMETRY_STRATEGY_SPHERICAL_AREA_HPP


#include <boost/geometry/formulas/area_formulas.hpp>
#include <boost/geometry/srs/sphere.hpp>
#include <boost/geometry/strategy/area.hpp>
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
    typedef typename strategy_detail::get_radius
        <
            RadiusTypeOrSphere
        >::type radius_type;

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

    srs::sphere<radius_type> model() const
    {
        return srs::sphere<radius_type>(m_radius);
    }

private :
    radius_type m_radius;
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

#endif // BOOST_GEOMETRY_STRATEGY_SPHERICAL_AREA_HPP

/* area.hpp
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
*/