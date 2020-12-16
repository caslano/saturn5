// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2016-2017 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_AZIMUTH_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_AZIMUTH_HPP


#include <boost/geometry/strategies/azimuth.hpp>
#include <boost/geometry/formulas/spherical.hpp>

#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_void.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace azimuth
{

template
<
    typename CalculationType = void
>
class spherical
{
public :

    inline spherical()
    {}

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

    template
    <
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

        geometry::formula::result_spherical<calc_t>
            result = geometry::formula::spherical_azimuth
                     <
                        calc_t,
                        EnableReverseAzimuth
                     >(calc_t(lon1_rad), calc_t(lat1_rad),
                       calc_t(lon2_rad), calc_t(lat2_rad));

        if (EnableAzimuth)
        {
            a1 = result.azimuth;
        }
        if (EnableReverseAzimuth)
        {
            a2 = result.reverse_azimuth;
        }
    }
};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<spherical_equatorial_tag, CalculationType>
{
    typedef strategy::azimuth::spherical<CalculationType> type;
};

/*
template <typename CalculationType>
struct default_strategy<spherical_polar_tag, CalculationType>
{
    typedef strategy::azimuth::spherical<CalculationType> type;
};
*/
}

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

}} // namespace strategy::azimuth


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_SPHERICAL_AZIMUTH_HPP

/* azimuth.hpp
T7ZEkLrpXWjv3rLtU7y0MnXr5rSUWU/2r1rEJ8r7hGOZBuvGtZzU1vekMOnTX02WryrxqbLdDcqKj7n9ZbOuzzwpryfhLe3t38r7jUF5rM5S5Yb6zFdf5iApc6LkA2gnZbYiTjBuQbEyU9iGhivUhbZu7TfBtYD0KUtR33PctGFJCTER6nBdH+LT1Yzzqnh2pW7/YF4VrR+u9OO/IPl2zuJpZXtYyieRWvT0iJRUvrZssry7qR0uXN7/rnha14fleDDOPr+YnENJf57kVC48qLXapyRYq7MUznaZ3E76mxR7TXqjqOc5b3bV9wX6odjf9brp/x5o+1u3XSKlX35r2S7NiWR+Keou/V5ZIqUDmyvfY1XsGDOj+HedXZayPpf98GNCyTsf1EMp65YXtiXuG3LeI8c8OXpa24rBcW+Q1CnG0/j7tkJ6llgny8W2C+vFvs9PgPSlXybrO1P6WZos5U3V+vtEJVivQEvs86Pv96pOpR5SfOR48bKX5EOLpdOmjG/rryOl2J1Tf6W20yhlJcoxVJ8H4LC8TxwivmbcgF5q3RMSIqJMlBETEcf7ZineHwrV8tSJtBxhb1qOcanJyZZhftp45qj4BH3fsHBvJ/UKKVYvZdL/Qb36WNeX1Ku3tK3u0t4Deqv1ctawXMohY9+mAqX/fAO17nJ8U45tva39Ue0v2VNNpemLGlZT+qIWKzPboMzzlLnboMySjx/6MrM8pcxix3D3Go59e7/hj0KDMrXOvS6Ua79cK2s49u0dVJP/+hiUYUpNiXNh/gbLpe1rq7XrV33bCajpWI8L/BJiVA/e0Ol4alK/8uM26+Mj9cn1tB4nuatZbN2sr2m8zTMM65SUbL7Nuuhyovg4rofvlHamL5PTGvVmgsvl7fNy3Ba8R8i20NdhpY/jcl+kDkWOdaDVlbzM1uNv37sd17WWY8CgzCJf5tDXsczUGSWXaV3uH32N9+elvo7r+RK/hDuUp3Vpd7nMfQb92VO8Hfqza8te1c94m2cZ1IU98LbqUdI2T/dzXP+/UIcChzqoLf226mC//t2lD39zwodoTFzx5b9+DuUpvY5LlU/Ats3t+yrr83a0sy631KMBUZkIIPoo50NaPdRb+RxtSn4ftV77h6jtPEr921P7e7Lu+qyD9K9fLMufQfxGvU1SbkpCe7VkdS934f1RrpV069tD3xdd8nxo54Zmlsnh/og+t1ZiYvH3pA7+cl1RjvsleBZ/V/bT/lJv7QMHzkESZkdw8q9tu7gSzulM2vm/zCI+Rh2eZnBvWBmeYXD/Vu4lG94fzjK8P8w9am15lVQm5oQU6f+ebT9+knIJwwklhSjrKEebRl1Cdfzd2jDrqOrNSLWMXN35VYTJemzI051PqcNlOzmeewXJMPtztGDLMJmeeerzH8Uqd5FiZZ7h2rgJUSlm6euuDUuMTZNhdvfPTMWvabLq8R8/eWzsADyA15jec1Dx7U+yk4TYaLN8KORKnjgfqWOQ5ToyypozrCHDx2nLxOE/ImlKxNTkpFSTNnN1/Udq20v3eZHkw3F4TW0wtXXtzv5zKss80wzmScORzyb028NHdw2rfAKlzkcd3kE/nHnYthXzkDYfoW5sD92963i51tNPz3KpwwP1w9VlklwM2npU5yr5TIPZf1eyDX9TrhuUbYb1dLmbo6xZuSyFyOs1DF5XC5N9xd9oehZSec3P4DVWjNKudG0rOED5X+nLKN+1in8q54BhTtqW/OlKvsfa0q6vWD9TkZtA1uULLda+tFnLtOG3aFvjbtG2Im/RtuKM25YcC7V2kST7gRwLjY8jGQbHEX2uJJmPevrEcV93nJcc8br75l281oVZ2scNX/0=
*/