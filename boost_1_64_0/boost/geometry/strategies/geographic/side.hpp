// Boost.Geometry

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014-2019.
// Modifications copyright (c) 2014-2019 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_HPP
#define BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_HPP

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/core/radius.hpp>

#include <boost/geometry/formulas/spherical.hpp>

#include <boost/geometry/srs/spheroid.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/promote_floating_point.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>

#include <boost/geometry/strategies/geographic/disjoint_segment_box.hpp>
#include <boost/geometry/strategies/geographic/envelope.hpp>
#include <boost/geometry/strategies/geographic/parameters.hpp>
#include <boost/geometry/strategies/side.hpp>
#include <boost/geometry/strategies/spherical/point_in_point.hpp>
//#include <boost/geometry/strategies/concepts/side_concept.hpp>


namespace boost { namespace geometry
{


namespace strategy { namespace side
{


/*!
\brief Check at which side of a segment a point lies
         left of segment (> 0), right of segment (< 0), on segment (0)
\ingroup strategies
\tparam FormulaPolicy Geodesic solution formula policy.
\tparam Spheroid Reference model of coordinate system.
\tparam CalculationType \tparam_calculation

\qbk{
[heading See also]
[link geometry.reference.srs.srs_spheroid srs::spheroid]
}
 */
template
<
    typename FormulaPolicy = strategy::andoyer,
    typename Spheroid = srs::spheroid<double>,
    typename CalculationType = void
>
class geographic
{
public:
    typedef geographic_tag cs_tag;

    typedef strategy::envelope::geographic
        <
            FormulaPolicy,
            Spheroid,
            CalculationType
        > envelope_strategy_type;

    inline envelope_strategy_type get_envelope_strategy() const
    {
        return envelope_strategy_type(m_model);
    }

    typedef strategy::disjoint::segment_box_geographic
        <
            FormulaPolicy,
            Spheroid,
            CalculationType
        > disjoint_strategy_type;

    inline disjoint_strategy_type get_disjoint_strategy() const
    {
        return disjoint_strategy_type(m_model);
    }

    typedef strategy::within::spherical_point_point equals_point_point_strategy_type;
    static inline equals_point_point_strategy_type get_equals_point_point_strategy()
    {
        return equals_point_point_strategy_type();
    }

    geographic()
    {}

    explicit geographic(Spheroid const& model)
        : m_model(model)
    {}

    template <typename P1, typename P2, typename P>
    inline int apply(P1 const& p1, P2 const& p2, P const& p) const
    {
        typedef typename promote_floating_point
            <
                typename select_calculation_type_alt
                    <
                        CalculationType,
                        P1, P2, P
                    >::type
            >::type calc_t;

        typedef typename FormulaPolicy::template inverse
                    <calc_t, false, true, false, false, false> inverse_formula;

        calc_t a1p = azimuth<calc_t, inverse_formula>(p1, p, m_model);
        calc_t a12 = azimuth<calc_t, inverse_formula>(p1, p2, m_model);

        return formula::azimuth_side_value(a1p, a12);
    }

    Spheroid const& model() const
    {
        return m_model;
    }

private:
    template <typename ResultType,
              typename InverseFormulaType,
              typename Point1,
              typename Point2,
              typename ModelT>
    static inline ResultType azimuth(Point1 const& point1, Point2 const& point2,
                                     ModelT const& model)
    {
        return InverseFormulaType::apply(get_as_radian<0>(point1),
                                         get_as_radian<1>(point1),
                                         get_as_radian<0>(point2),
                                         get_as_radian<1>(point2),
                                         model).azimuth;
    }

    Spheroid m_model;
};


}} // namespace strategy::side


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_GEOGRAPHIC_SIDE_HPP

/* side.hpp
f092UrrFGoxG08ypL9OQoi0zQ0wM/1a/O5Ca9i33AEWWvifQgtSStofJPDjMTlPqaHuGMQq1vm626ivjGSjjGSyfi9ZQxuNENjKeAnU8d10wf2pcOTKuyuZXa2Wa7LfKuO6wQMvJdMEdxzVUxuVqpz9dLvcwLtOk3dt87C7jWyLju1XeNL4SVKbNR8ZXZmO6x+XUS8q/amN68rfbKP9PLJ/OMg6+z0T96Sfj6CXjKGd6nquUFxEeFBMYk+CvrLj3VHaxRVt7+/JFfUc6x7mtTn7BqcfqagW/8+B6cV2le/0XE5NvNvM9tTx+6JFlzx8+y/3oSkr3Gzeqb858ZPWSHm8kxdbr9DkP4I7XUbo3vBBcI2LqsMWfVFsW7drKZyf7Ewel+77tu/svtqv4e9/gLvsjP+8SSB0eVLrv3hQ6Osfu2sendrX4Y8v6Fbt4rq72P/X5eRn2F+rtHbro6pSIEl8eJs5Qyx84Irj+Zd/iNtWinQse61TCA/dcO6X7rMatXHIc1x/5NeHZFe+s/HG0+j1OdB/5bOaIT/84OOT7/RtTqx9ovlV9bEX3jAsPdFtacfitQS0eOPVWi89eVz7vTq3P0conWvZc/WunrVUPTBy75U2e46r1rLArvKnrghvd6pfUd3jomSBePqWNBN09PHaP/fK935xGX5znPHqb8xn2Iw8p3Xv87NZy7I3E5VmDJjkVVnniMcpR+z8wca5vYeXVuxdkPlhwds/aPO5lq/P5vXnnXv/j+prihCcaOx5LnlxZ/f4Yulc87RASNKvtji0Hjk74venZYNpBqPV5ds2sJ9skHw/9zPFW1nW3Jp7q55fQvbeL4cZ8v2nuFWdPq5H4tYFGnc3V7h+svfx6X0P49oU/zQ062nQfy7CrOj9fqfngSX9Pz5d7VXLvNqvRgAbq5yPSfcnep97/4jUPj4WvjYkPX7WnkHZ66njr1QwZ8s6owpmtm29amZiw/zrzrbLSfW6dTS+9NKv+uPwd058paDWZB7Hu6nQd6+1dfLN753Mbvv7steDywW8z/9Xle/PSS1U3L1iYMujDG4Hhk5sX0D5L7V6Y7PJU27zImwt/zHhuUUZjGty9p9YnOn/msutFLV8/t66fc5vLXVnumepyPP7usQu/NRg07xWvmHde9Xx5NfsRdbkb66+8vnDUlklLW0/YZu9Z7QrrlaPSfUtUvQMVVzYY8YvXseLl1T5hOZra4MkxRo49VytYt8E7Km1zn0YXfAZb4UnsiKdwAp7GqfgSJmIeLsZX8Wl8DU/iG/g7vokVGN/b2B/fwcHSNnc4vqc9E5fjixx3qJ/VM/HZ9FcLk+SZ+yJ0xsXYBJdYvssi5TSUcizbcsdJfx7lZN+PlaU/q898oT/FlVgJH9fKJ1ttl79M+uNWuux/2S/L/GZ/xTtk8tk3Mj0uWB+bYEt0RU9siX2wFY7AtjgZO2AYemIcdsJF2BnXYBdMw664D7vhM9gdX8ZHMR974MfYE7/BXvgzeqEddeyDDtgfG+FgdEdv7IrD0QdH4BT0wek4ChfhaNyCY3AvjsUcHIcv4nh8GwPwHAbjRQxX6oWR+DVG4U8YjSU4q3Q5cPyxvRwelv4oX44hHFukP8s2dKtkOazBepiCTrgWm+KT6I6b0QO3YjfMxF64H69WNM04Z3KnNhl+0dyfJ8kki1wkxcRpFs8oiLS3kLYWWjsL2ljotq2Q9hR6bShstp3Q2ktkk4ukbPsIq7YRVu0irNo+WLV5uGNbB2nnUKZ9Q5l2DSXEui2DdTsG6zYM+u0XzpMSYt0+QWubIO0StDYJWluEEuIxQq/dgXV7g0wibQvKtCuIJub2BHlEvx3B7W0I7t5+wKI=
*/