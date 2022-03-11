// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// Copyright (c) 2016-2018 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_AREA_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_AREA_HPP


#include <boost/geometry/srs/spheroid.hpp>

#include <boost/geometry/formulas/area_formulas.hpp>
#include <boost/geometry/formulas/authalic_radius_sqr.hpp>
#include <boost/geometry/formulas/eccentricity_sqr.hpp>

#include <boost/geometry/strategies/area.hpp>
#include <boost/geometry/strategies/geographic/parameters.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace area
{

/*!
\brief Geographic area calculation
\ingroup strategies
\details Geographic area calculation by trapezoidal rule plus integral
         approximation that gives the ellipsoidal correction
\tparam FormulaPolicy Formula used to calculate azimuths
\tparam SeriesOrder The order of approximation of the geodesic integral
\tparam Spheroid The spheroid model
\tparam CalculationType \tparam_calculation
\author See
- Danielsen JS, The area under the geodesic. Surv Rev 30(232): 61–66, 1989
- Charles F.F Karney, Algorithms for geodesics, 2011 https://arxiv.org/pdf/1109.4448.pdf

\qbk{
[heading See also]
\* [link geometry.reference.algorithms.area.area_2_with_strategy area (with strategy)]
\* [link geometry.reference.srs.srs_spheroid srs::spheroid]
}
*/
template
<
    typename FormulaPolicy = strategy::andoyer,
    std::size_t SeriesOrder = strategy::default_order<FormulaPolicy>::value,
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
class geographic
{
    // Switch between two kinds of approximation(series in eps and n v.s.series in k ^ 2 and e'^2)
    static const bool ExpandEpsN = true;
    // LongSegment Enables special handling of long segments
    static const bool LongSegment = false;

    //Select default types in case they are not set

public:
    template <typename Geometry>
    struct result_type
        : strategy::area::detail::result_type
            <
                Geometry,
                CalculationType
            >
    {};

protected :
    struct spheroid_constants
    {
        typedef typename boost::mpl::if_c
            <
                boost::is_void<CalculationType>::value,
                typename geometry::radius_type<Spheroid>::type,
                CalculationType
            >::type calc_t;

        Spheroid m_spheroid;
        calc_t const m_a2;  // squared equatorial radius
        calc_t const m_e2;  // squared eccentricity
        calc_t const m_ep2; // squared second eccentricity
        calc_t const m_ep;  // second eccentricity
        calc_t const m_c2;  // squared authalic radius

        inline spheroid_constants(Spheroid const& spheroid)
            : m_spheroid(spheroid)
            , m_a2(math::sqr(get_radius<0>(spheroid)))
            , m_e2(formula::eccentricity_sqr<calc_t>(spheroid))
            , m_ep2(m_e2 / (calc_t(1.0) - m_e2))
            , m_ep(math::sqrt(m_ep2))
            , m_c2(formula_dispatch::authalic_radius_sqr
                    <
                        calc_t, Spheroid, srs_spheroid_tag
                    >::apply(m_a2, m_e2))
        {}
    };

public:
    template <typename Geometry>
    class state
    {
        friend class geographic;

        typedef typename result_type<Geometry>::type return_type;

    public:
        inline state()
            : m_excess_sum(0)
            , m_correction_sum(0)
            , m_crosses_prime_meridian(0)
        {}

    private:
        inline return_type area(spheroid_constants const& spheroid_const) const
        {
            return_type result;

            return_type sum = spheroid_const.m_c2 * m_excess_sum
                   + spheroid_const.m_e2 * spheroid_const.m_a2 * m_correction_sum;

            // If encircles some pole
            if (m_crosses_prime_meridian % 2 == 1)
            {
                std::size_t times_crosses_prime_meridian
                        = 1 + (m_crosses_prime_meridian / 2);

                result = return_type(2.0)
                         * geometry::math::pi<return_type>()
                         * spheroid_const.m_c2
                         * return_type(times_crosses_prime_meridian)
                         - geometry::math::abs(sum);

                if (geometry::math::sign<return_type>(sum) == 1)
                {
                    result = - result;
                }

            }
            else
            {
                result = sum;
            }

            return result;
        }

        return_type m_excess_sum;
        return_type m_correction_sum;

        // Keep track if encircles some pole
        std::size_t m_crosses_prime_meridian;
    };

public :
    explicit inline geographic(Spheroid const& spheroid = Spheroid())
        : m_spheroid_constants(spheroid)
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
                    typename result_type<Geometry>::type,
                    SeriesOrder, ExpandEpsN
                > area_formulas;

            typename area_formulas::return_type_ellipsoidal result =
                     area_formulas::template ellipsoidal<FormulaPolicy::template inverse>
                                             (p1, p2, m_spheroid_constants);

            st.m_excess_sum += result.spherical_term;
            st.m_correction_sum += result.ellipsoidal_term;

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
        return st.area(m_spheroid_constants);
    }

private:
    spheroid_constants m_spheroid_constants;

};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{


template <>
struct default_strategy<geographic_tag>
{
    typedef strategy::area::geographic<> type;
};

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

}

}} // namespace strategy::area




}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_AREA_HPP

/* area.hpp
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
*/