// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// Copyright (c) 2016-2020 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGY_GEOGRAPHIC_AREA_HPP
#define BOOST_GEOMETRY_STRATEGY_GEOGRAPHIC_AREA_HPP


#include <type_traits>

#include <boost/geometry/srs/spheroid.hpp>

#include <boost/geometry/formulas/area_formulas.hpp>
#include <boost/geometry/formulas/authalic_radius_sqr.hpp>
#include <boost/geometry/formulas/eccentricity_sqr.hpp>

#include <boost/geometry/strategy/area.hpp>
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
    // Area formula is implemented for a maximum series order 5
    static constexpr auto SeriesOrderNorm = SeriesOrder > 5 ? 5 : SeriesOrder;

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
        typedef std::conditional_t
            <
                std::is_void<CalculationType>::value,
                typename geometry::radius_type<Spheroid>::type,
                CalculationType
            > calc_t;

        Spheroid m_spheroid;
        calc_t const m_a2;  // squared equatorial radius
        calc_t const m_e2;  // squared eccentricity
        calc_t const m_ep2; // squared second eccentricity
        calc_t const m_ep;  // second eccentricity
        calc_t const m_c2;  // squared authalic radius
        calc_t const m_f;   // the flattening
        calc_t m_coeffs_var[((SeriesOrderNorm+2)*(SeriesOrderNorm+1))/2];

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
            , m_f(formula::flattening<calc_t>(spheroid))
        {
            typedef geometry::formula::area_formulas
                <
                    calc_t, SeriesOrderNorm, ExpandEpsN
                > area_formulas;

            calc_t const n = m_f / (calc_t(2) - m_f);

            // Generate and evaluate the polynomials on n
            // to get the series coefficients (that depend on eps)
            area_formulas::evaluate_coeffs_n(n, m_coeffs_var);
        }
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

            return_type const spherical_term = spheroid_const.m_c2 * m_excess_sum;
            return_type const ellipsoidal_term = spheroid_const.m_e2
                * spheroid_const.m_a2 * m_correction_sum;

            // ignore ellipsoidal term if is large (probably from an azimuth
            // inaccuracy)
            return_type sum = math::abs(ellipsoidal_term/spherical_term) > 0.01
                ? spherical_term : spherical_term + ellipsoidal_term;

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
        using CT = typename result_type<Geometry>::type;

        // if the segment in not on a meridian
        if (! geometry::math::equals(get<0>(p1), get<0>(p2)))
        {
            typedef geometry::formula::area_formulas
                <
                    CT, SeriesOrderNorm, ExpandEpsN
                > area_formulas;

            // Keep track whenever a segment crosses the prime meridian
            if (area_formulas::crosses_prime_meridian(p1, p2))
            {
                st.m_crosses_prime_meridian++;
            }

            // if the segment in not on equator
            if (! (geometry::math::equals(get<1>(p1), 0)
                && geometry::math::equals(get<1>(p2), 0)))
            {
                auto result = area_formulas::template ellipsoidal
                    <
                        FormulaPolicy::template inverse
                    >(p1, p2, m_spheroid_constants);

                st.m_excess_sum += result.spherical_term;
                st.m_correction_sum += result.ellipsoidal_term;
            }
        }
    }

    template <typename Geometry>
    inline typename result_type<Geometry>::type
        result(state<Geometry> const& st) const
    {
        return st.area(m_spheroid_constants);
    }

    Spheroid model() const
    {
        return m_spheroid_constants.m_spheroid;
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

#endif // BOOST_GEOMETRY_STRATEGY_GEOGRAPHIC_AREA_HPP

/* area.hpp
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
*/