// Boost.Geometry

// Copyright (c) 2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_MEAN_RADIUS_HPP
#define BOOST_GEOMETRY_FORMULAS_MEAN_RADIUS_HPP

#include <boost/geometry/core/radius.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace formula_dispatch
{

template <typename ResultType, typename Geometry, typename Tag = typename tag<Geometry>::type>
struct mean_radius
    : not_implemented<Tag>
{};

template <typename ResultType, typename Geometry>
struct mean_radius<ResultType, Geometry, srs_sphere_tag>
{
    static inline ResultType apply(Geometry const& geometry)
    {
        return ResultType(get_radius<0>(geometry));
    }
};

template <typename ResultType, typename Geometry>
struct mean_radius<ResultType, Geometry, srs_spheroid_tag>
{
    static inline ResultType apply(Geometry const& geometry)
    {
        // (2*a + b) / 3
        return (ResultType(2) * ResultType(get_radius<0>(geometry))
                + ResultType(get_radius<2>(geometry)))
             / ResultType(3);
    }
};

} // namespace formula_dispatch
#endif // DOXYGEN_NO_DISPATCH

#ifndef DOXYGEN_NO_DETAIL
namespace formula
{

template <typename ResultType, typename Geometry>
inline ResultType mean_radius(Geometry const& geometry)
{
    return formula_dispatch::mean_radius<ResultType, Geometry>::apply(geometry);
}

} // namespace formula
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_FORMULAS_MEAN_RADIUS_HPP

/* mean_radius.hpp
6hW5paRvFwU7HbAjIe7DCnYpYHcBtpmCXU1xOxTsOsCKCsxleQPllVfBbqd82VrJlwcBm2SJ+ybF3UnB3gLsAJAbo2Ajy7i+kUrftFEZL/PJityoMp5X9yvY2DLuR5uCjSOsR8HqALsF0q1TsK3KeF49oWCTKd2vFayJ7PMr/u5Yxn2rVOR6ACsEH95Ryu0sinujgl1cxvumWxXsUsB2KDT3Oddk8PfBDDY/RvpuVrC3KQ82UbD3MvjxEWEdCvZpmb1Orihjdcjs708Z4pasw/PgY/LNpxWUaxCapnTGE3osFe9PhnT+MxWt6uqPRMNVtdW11TXdVQtT42tqJxncwMS6qlRvMKmHq5J6VA+mdJLQpkmdYX1hJ8XraOz0x+PRVGdLO/ysrauurakevxVjuiKxzhnxVHruxLrOAThC0Wr3XLhHHEt6qqs74X9Kl6zphJ+d7CEcnKtD2lddq96PzjjQONWLhKoTYbgLojSqPKswlcpVqq0zEgtF+8N6Nq2kbyW00MLm6Dnc58qqptY2t7e9vZm9jGDPD5o93lmANrW3BuZ4vBPGw28vPi9SRP0zfG5XU7uCeFsDTfPgEYCnMQAPaTxet8K1eRrhisPtTR7fNp2jwErVTMPOcCSVtuTNn8iczmikq7NTj/WwZwZVtYHazlEy+ZUmqIm8+DspA80SmzOhsmpRuK5mck1l1fQU+2caHIsrq2LxaLwnrmRG+7x2I1/xDE+1XN4APAANtMAPQNlz0yYP/oTZsZ89v5rtc2MOu+GBXKPLzzJ3ttfT2NrEfgWMny1NlVWtoHh+pLIqBHXhzzZUl7+5ZVojqx1GXrBq8hc0yOo5qnFKZ1sy3pMM9lVOi0T1VOWYgfqJm3fOicTC8UWpylmRdKoTnitPm9veNKuzrnpida2I3dnfN+rPaqitMWKBETXVtVvVTJxQXdPZH0qm/76SugmTmRJe1vB8J7+c3W+weW4Ajl3gCMKxFPqLLjj/43T+ib+kYlEkhg77oYnNhXZdoeWVF2jzwbod4eiEYyc4QnCs+AqeV2HZrgtjRQM87+5mnSzgowmvIDymLwp09Xd360kmALemsZgegvenFdb4JMXu20qJGyF1aBva9ZoUCns2JD7Rz+//BT6smOPsaZWKV5r1aSLtjQCHJoZpjyIsVsaxlJ6mdOkuH/zOJBMMhfQEFzGlWcptwZdJgNvyIiW0K3pHcY58Tiw2npPA0ygRf7TISyhs/jhP6t6MuB6wKxxMB1m6Ik83577a9Ar+4FKZdqq3Pw01KabaPZbr5s8NKGXBfV/Mdct4Mh+2MPJ+IK3i4wAPpCBz9NiEWk3auX4xf2pkehtn4lGfjT+hujanYZst5rF7g4s+OLzz4Or4zAMPvG7+FzsfvVSjkIOHOby2wwTnK4BOcIITnOAEJzjBCU5wghOc4AQn/EdCPhzztZwS9huej7E19qlO9lSmN5LqdCUSTfA8pLM5Do8NOv16X6IzGluwR/2EyfUT6xu2qpowYatJVXX1E6ZVTZ7Q0FDVOGFCbdP4yXWTXO7GvarTfQn27kGbWlIE70+eMlJcC9Zs3BrUNPmXB8b4Nq9s7IBFnPAHB87UtinRQovCq/JFBCzX0v/+y5SFaVgZU81UsPANHOvCsYStm8n55dZzPjnnIZ/3qeIz1vjpg/gZmhOc4AQnOMEJTnCCE5zgBCc4wQn/ypAPRznd/8PqLriPbmmCm92ERvfuq2lFK713ZyvZGLv033bvHo3EFtCde6lWX5KjKetx4PcowHK1wdbi8Hh5UgZjVgCWLzFThA2BK9AGWY8CfKGWYc0IBMatBmfcKRKKRvSY2G/C7SgijkCUX11g8OBmoZ4=
*/