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
R7gKM/FFzMLtmI2vYw7ewHN4C89jefL0CdbHi+iJn2EwXsII/AKNeBkT8CuchldxOn6LT+B3uBBv4BH8Ed/DX/As3sQc/A0/x9/xB/wDb2Fpyr2BjHHXFsuhD96HfbE8DsAKOBIfwHCsgmvQGddhNXwZq+MrWANfw1q4F+vgPqyHh9ADr7Afxip9jWx9jNK/5HoycYq4TlS8Qv0h/IlQYhqxlthH5BKmk0Ajwp8IJWjMKf2ktmVb+jwd4b83bWf5PgX1r1L1h1L6Oh0jcombSr+n/40+T/+E/k7F7ev0V/Vz+if3cUr9qqSfU1H7Od3rPk5plH0GcYK4QpS5StkR/kQoMZ/IIDIJh6/JP+FPGImVxF7iClHtG8qbiCYWEZuIY8Ql4uY3DiWfkk/Jp+RT8in5lHxKPiWfv/FThhj31zz/zxNlyUmJSeZH/+/62f/fq/K7zHwtpfj3sPXv/du/t61/77n497z17/EX/5kG/WcC7N/D1n8Gwt6zDsW/513cZyP0nwWx94xC8Z8R0X/Gwt4zE8V/hkD/2Y7iP9Og/6yG/WcU1pYu/JoM13P0r7vYv+Yi11v+e9da7uV1lnt5jaW411duEu2KcE3ln3It5fqQe3sNRXX9RLl2orpuonPN5N5dL1FdK/mbr5PINZKST8mn5FPyKfmUfEo+JZ//uc9f+/s/KcXy8//uf//f5LeT9KPkuRPpi2QaXxo/xBhTn45PlP7hQ3sPHdpv0ED6UcXEJVn7I80vpD/ShUvSHykhwdyvIo3p91n6BRkdpN9HOvKiIaal8Lf0OyLoc8fflj5LZZU+TKWdt8mYvBvx+89YPlr7ixhdzH02WE1L3wlCWcdO8mziKsKNWEZMYB3XXtZdR3rCG83rGFDIWAJB6GbuFxKprFOwbZ20/ebkO562slD3b5R89ndkudgbTdsi9Es7+ZxgmBobH1WEPk1lnddfUW8PH53tEZBve3jYtoeqP4r+NSP71yD0ryXZu3ZT/GtDxb12oH+tx961g+Jf0ynuNRH9a2f3rt9Pcfv36F8DKn6/H/1rPcW/5qV/rcfetcV71x8owM00/buO33aaNsfZ6aMFvkOHVPjSy9IfJaOUHCPl2HmFv4fy3xus73KS58+9sQH6YFP0RW/shf7oh8Hoj8nYGx/FvpiGAbgF+2M2DsDzGIgXcCBWIhOD0AUHYzUchjE4HONwJM7FYHwSR2EGjsZcfBg/xTH4OY7F3/ARdGCdQrAxhuJgDMMROA6DMRyNGIHJaMDVGIlHMQrfw2g8iePxC5yAVzEWu1OvJ6IPxmEwxuNYnITbMQF3YTK+h5PxFE5B01jwKdgEH8Wu+Dg+gtMxHFNN+cOZuBhn4XJ8At/FuXgCF+CnuBCv4iKsW5ZjEzbEJdgSl+IQTMORuAxH4QqchStxHqZjOj6Db+FqPILPYRauwdv4PDpSn9ZiTVyHdXE9dsEN2B03Ygr+Cx/FLXgUt+IxfBk/wFfwQ8xQ+u3IeQ9X6Ty32VLqbVtsj+1wOLbHUdgRjdgJZ2NnXIxdcBl2RXmnoPW8xfmMdPK9U3CPpPMG1sM3sRHuw264H73xCA7DdyT9dzEOj2Ei/hufwuP4Jr6HB/EEHsaTeBbfxxz8AH/DU1iffH2IDfE0NsaPsBtmYg88g36Yjb0xB7eVXEv+v7yWXGYw3ym5lvw/cS1520+UH3H9J4eST8nnb/n8tb//GVjhHt3/v0472Pqbk/dL80HOz87i1prsN6eU35xhzJcUEmFIDCcPCSytaGPfVQT209MsJ8/fqfK3C79JJ1j+u1HgwI4dHWTaONu0DtZpo2zT2lunBdmmtbNO66tM6+BlnfagbZqndVpn27Q=
*/