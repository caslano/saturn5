// Boost.Geometry - gis-projections (based on PROJ4)

// Copyright (c) 2008-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2018, 2019.
// Modifications copyright (c) 2017-2019, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file is converted from PROJ4, http://trac.osgeo.org/proj
// PROJ4 is originally written by Gerald Evenden (then of the USGS)
// PROJ4 is maintained by Frank Warmerdam
// PROJ4 is converted to Boost.Geometry by Barend Gehrels

// Last updated version of proj: 5.0.0

// Original copyright notice:

// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef BOOST_GEOMETRY_PROJECTIONS_NELL_H_HPP
#define BOOST_GEOMETRY_PROJECTIONS_NELL_H_HPP

#include <boost/geometry/util/math.hpp>

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace nell_h
    {

            static const int n_iter = 9;
            static const double epsilon = 1e-7;

            template <typename T, typename Parameters>
            struct base_nell_h_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    xy_x = 0.5 * lp_lon * (1. + cos(lp_lat));
                    xy_y = 2.0 * (lp_lat - tan(0.5 *lp_lat));
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T half_pi = detail::half_pi<T>();

                    T V, c, p;
                    int i;

                    p = 0.5 * xy_y;
                    for (i = n_iter; i ; --i) {
                        c = cos(0.5 * lp_lat);
                        lp_lat -= V = (lp_lat - tan(lp_lat/2) - p)/(1. - 0.5/(c*c));
                        if (fabs(V) < epsilon)
                            break;
                    }
                    if (!i) {
                        lp_lat = p < 0. ? -half_pi : half_pi;
                        lp_lon = 2. * xy_x;
                    } else
                        lp_lon = 2. * xy_x / (1. + cos(lp_lat));
                }

                static inline std::string get_name()
                {
                    return "nell_h_spheroid";
                }

            };

            // Nell-Hammer
            template <typename Parameters>
            inline void setup_nell_h(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::nell_h
    #endif // doxygen

    /*!
        \brief Nell-Hammer projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_nell_h.gif
    */
    template <typename T, typename Parameters>
    struct nell_h_spheroid : public detail::nell_h::base_nell_h_spheroid<T, Parameters>
    {
        template <typename Params>
        inline nell_h_spheroid(Params const& , Parameters & par)
        {
            detail::nell_h::setup_nell_h(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_nell_h, nell_h_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(nell_h_entry, nell_h_spheroid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(nell_h_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(nell_h, nell_h_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_NELL_H_HPP


/* nell_h.hpp
1RieRnk1MZ59ONjpp2CbcEd39VEhY9q//3a+kXcpuzqGi1x3316jtcU2+bM9KnryPEqpjDqrUjsnQbYt0HWCIePJsWqmopR2zCbwRmfTMPQPsgH2exyGfq5W8YsLaT86w42WjzbiPq/+xrwOqRb8gQYouwtpk5f4qhLG7onuKUz3B0T3X+wdCXiUxXWvwCYSdsOZcrkg6oqoEagGQdlgxEWDhkONBxoFbVDUIAliBQwGNBhQFEQ8alGw0nohWlxQMRGQgNQCXrReKGj/dBXvmlowfcfM/P/8+ye7wdja7+t+H+SfmTdvzvdm5s17b+7Q8R7OeB9DBPPHI8KZR2GeYZznSsqT6dbyfHmYz1UPqlgo9mG2diqArS1E9jX4MLsifAgA1f1aaVQ8gr25Anbn9BPBdlowEvGY32FXIX+XNi5Ub0DNy8sXOXFdpLXmzcN9yl4g6jXtBeAbHedgswq5WYtOYw85WrO6HYacdzS3aApAEC7j6j7UQ/O8qqpBLG2hWwZzRc2NTUiH8mCSI644abGim2DsjI6sV3vVQyTW9D0MuZ66TVk55IXkxXAIgT/BBWK42ai8bJmcjcmbMfmhsNnmCrfZZvxGoIc9Kq4myICVtX6hXH4X69+MI/W9rv/y8dq9QxlVLR8NDYIpxYo2tCg/BL0Nxgs0R0q4M0fkY2c+pHfmn3rjHMEaDjzSrGGppYalooZ4shXvExujDxdeEFQPRqAH6ezIGyIqdwqX+9qpWO5XernnYLk7+AIlE1H+0JdRRhXKKKDcpbSiGWU5o7yRUH6to/QgylnIWDbOlw4fGRcLDRsErkJszQDZQm0zlMOboT9A88itfTsBVWp/myjLeKfoQKPsLsMkjwcQQUQFl3JQFYUEGnTxPu2s3qSvlCvSdmFaSKQN4LQecgNvTetCaTd1ozRaGNCjQHumttkYZIL4bCTxHXhi2gKJ12MmoI4iS6Wo+keADhrhR8F4Dg7BGh6ChjwH0rzpUJ8o/DjY9Q2s+f9rbz/pT9vvhDYk1XdZPsZchOVevj3QnZUPYiwvkinoo/OmgtXSq2gn1mz5h3H5alVWO4HLQ2JhTuH+4f3RwvziWT/x6GuH2bbqE3vQy9OFeWv/6MepmjYKIKq38/X6Z0A8gl/NBmh5UIrht1jen4NcyGeHqQl+njplPgi4+eIhi3KSvm7VF5D5YNSVnN+75t7cBThVRDZE7IaIDansfwqd9z98GnttnDC7S0U/aiqjMjdQE3rpkyWaTbgOpn0LXbb2LcX9cxL7v7NNLVW5ThbKdbJQWydR6VmtkpjmN2aeAbktWx54YQtf3BL2mHBolq/7f9SW9Q1OxgmwFidAppoAv+nmcx30Fbyjvmh7bpSw/RmyroN6Qt0LFYZVnerUi0UfNw/FOr2GdZqv6pTOdTqSZqRcOfGGRbszW+huobawg/3nWTr9Kiby50OZfpvZ/3NWLddvD026/3ecOnQSawH8yqbh1dSqGsWXuJ1phm83Te1+6JnonuPoqOn808umves8ym70fchhPJbta7ndnaU+DQVcn+qetvpck2J93Ko+Z2F9uh98ffj98wIbK/ihhxg85/tclfG4AvuhlziTOvkCmpT50Z4zTVxSDvNVd9v6VQKt1CDe6p6qjlIC/+PyyPJ7XUB1aLs8wUNbwu/q7Px8e1J+ruWP2fPXYP4k9u9nWOp/tqp/QUTUP4m8t4yzWyS8Lr4y86V4G9xEU3I8LaPf3Kbgbc3dOJLqm7C7uKqbmGPJ7RXnVZEcJaX9Tixhv+MIzmhJrpKSfsUPUWoFr3ENoWnE/p9nG6zKE5D9Z+Fp4B216c7oROz/eMuGZChAIALe6cyujUA4n48=
*/