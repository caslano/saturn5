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

#ifndef BOOST_GEOMETRY_PROJECTIONS_BOGGS_HPP
#define BOOST_GEOMETRY_PROJECTIONS_BOGGS_HPP

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
    namespace detail { namespace boggs
    {

            static const int n_iter = 20;
            static const double epsilon = 1e-7;
            static const double FXC = 2.00276;
            static const double FXC2 = 1.11072;
            static const double FYC = 0.49931;

            template <typename T, typename Parameters>
            struct base_boggs_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T half_pi = detail::half_pi<T>();
                    static const T pi = detail::pi<T>();
                    static const T root_two = boost::math::constants::root_two<T>();

                    T theta, th1, c;
                    int i;

                    theta = lp_lat;
                    if (fabs(fabs(lp_lat) - half_pi) < epsilon)
                        xy_x = 0.;
                    else {
                        c = sin(theta) * pi;
                        for (i = n_iter; i; --i) {
                            theta -= th1 = (theta + sin(theta) - c) /
                                (1. + cos(theta));
                            if (fabs(th1) < epsilon) break;
                        }
                        theta *= 0.5;
                        xy_x = FXC * lp_lon / (1. / cos(lp_lat) + FXC2 / cos(theta));
                    }
                    xy_y = FYC * (lp_lat + root_two * sin(theta));
                }

                static inline std::string get_name()
                {
                    return "boggs_spheroid";
                }

            };

            // Boggs Eumorphic
            template <typename Parameters>
            inline void setup_boggs(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::boggs
    #endif // doxygen

    /*!
        \brief Boggs Eumorphic projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - no inverse
         - Spheroid
        \par Example
        \image html ex_boggs.gif
    */
    template <typename T, typename Parameters>
    struct boggs_spheroid : public detail::boggs::base_boggs_spheroid<T, Parameters>
    {
        template <typename Params>
        inline boggs_spheroid(Params const& , Parameters & par)
        {
            detail::boggs::setup_boggs(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_boggs, boggs_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(boggs_entry, boggs_spheroid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(boggs_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(boggs, boggs_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_BOGGS_HPP


/* boggs.hpp
0SYTM8v3zgSe2GRO3iVy4UaaECa7NzrMxbGb34YC8t6RxE25LiTy2g6OSdHZ/kZIuHi/Rt8t1B9jS+YeR24KV0UyMT1I2/8op467jqPtOguwqD8mtb7VLOnOE6zojMivC1nZ2CG1HUtWK0aCrmNdXFSz2bKzPLGjxLGb67Y1Mb4gPEjX3tEseWxcTpDcUMOgjuu5PUxqg13TncXYlMtskGT+xtrs8QJXfjdqUncdAFj4nI78KaDNiwfNRWOIN9aS6w7ArnuP8uven5oixm41iKDpNAnvLreWN/aQeMEyZ/vcMxU3z5XxvVLhhLTtbX5SI5mf2CdH7smylSRs4H4B9e19y9qkXBQIPHksx75b5cCFbrD2pSQIx2XkDenfedfk1OF2as5itsMbmgfBkPuwcn3lu1lumzZPF9CmrWTaTuDOlfPqSae5a78JnTah57Fb2Y6I/cz5CVmYX1Exb2GlPnWiMKStKs9xzw6a7LPgu0qnHZNn7O2Y5Jlfd0w+cMOm18a01U76yOQsgs6+ySoW186jStI7wB7UWNkQYEH7RU59e5/MKAACcat7F+c45wzMo2SJNw3GpcXrbAMnhfeXOv1yF8zKiKTdgRLPfDfPl38hxWI/76C0+HEYoUs5JPEGw7PTTZ2QWyeq7l3GO1txIS0hhH84JsAnFd8msjIWdtptjy83PqRtzOLWBeCaO98W1/q5Lm5nrD0aT8p2fZC9kJhCPzbItnqw900SL9Dep2/TPW84IVi3C5ZTKUwCV+H/R1xcfAiTG7X8udzBUS8g1Ddvmn4dMTx6Nf5N0s/HtO+OyXas7+AF0yHIV9nkWUkfNae7HrHfiZyQJv8N/0BHWE3RvTnSJucXZVzSEcHvSVyjxXXu/s2UcF0d48BXcfaQ9DMIzdEU2q0Iop3AlO9l0IYbT9s+2gxcH0o2r5g6Z1nTxdnyPqhfUz+Ab7hL2AD3vrXGdcagy6yXb+vab5K58TlwOUYj75ZVXdoqRm9Di3mWFwbp8jTyIO4+mDVsSuJZPjm/exueOy43ZzDOmVdAHsBdf5kDsOPvzAm6O2HP52yCTxix4BMxnrQx/8ocAafHsOI1sYargbswe88DWEH10vKikPxC1qHRWrGOR4JjWEQ96KGfJwdDvidsae3Kt8uvbrwiaXp0jtuOl7ynmuPWFzrNGYd9kDbczM8knY711yXlupf0I9a6cBqS4zshx73r5iV5XYxdxHa27smGhmod3H5/n/QVgIjz3j2ez460NUMHmX+ZaXhe5H2sbjzVji9tzsf2N9JfKwai3rFUSoXMptoto79wS/LszkRzL48zXZYX/uDTsKKoupInhKsry4rtkS8rH2cKOpcsqYGgaGCLltQPZxu+9fNBlpbm+7wmicPo5Rqdq+ZZVBOaX1Zd455jOd/y+uKCshptJjSGzXEmeSxXBkkNYh0vlDhqcDIfOciB6ePPUWX2LY9eLOtbocSGBYxBOnr2BQwxlksMrswL2e/8pcAa1PEv7oCmvntZZ55l5P8MQty+0ahfpsON1sWV4Y23o+0bEriTAnH1cfyuKW7T8o6KGKe9HSD6vjxQR0rsJF9d4be1yRzXlRJPK5NIQ73z1tFVSZy85Iuu1gjaNbg6iWeBzptR8i4gLzdoa2P54U858oyehVs7dq1o3/g2tv0bBAwxMJq5MeWs8Y3ded6ggyhsyE2iLZmytHdTJFy/LVFv+5O8cktQf7ZKap+3dqOdvEcraWvpZ+mfwLm9G459h8Ti3CFxsHDJhoSODcARpyDtet2bI95EBDmh6HtqBz0a1twv1mWdwQvMeQp5us/H22RuNDHX+wW+86SS5Sl5b9A/UyD82mR9KzniLXA=
*/