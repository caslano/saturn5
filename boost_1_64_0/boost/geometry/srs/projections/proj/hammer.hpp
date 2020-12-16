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

#ifndef BOOST_GEOMETRY_PROJECTIONS_HAMMER_HPP
#define BOOST_GEOMETRY_PROJECTIONS_HAMMER_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/pj_param.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace hammer
    {
            static const double epsilon = 1.0e-10;

            template <typename T>
            struct par_hammer
            {
                T w;
                T m, rm;
            };

            template <typename T, typename Parameters>
            struct base_hammer_spheroid
            {
                par_hammer<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    T cosphi, d;

                    d = sqrt(2./(1. + (cosphi = cos(lp_lat)) * cos(lp_lon *= this->m_proj_parm.w)));
                    xy_x = this->m_proj_parm.m * d * cosphi * sin(lp_lon);
                    xy_y = this->m_proj_parm.rm * d * sin(lp_lat);
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    T z;

                    z = sqrt(1. - 0.25*this->m_proj_parm.w*this->m_proj_parm.w*xy_x*xy_x - 0.25*xy_y*xy_y);
                    if (geometry::math::abs(2.*z*z-1.) < epsilon) {
                        lp_lon = HUGE_VAL;
                        lp_lat = HUGE_VAL;
                        BOOST_THROW_EXCEPTION( projection_exception(error_lat_or_lon_exceed_limit) );
                    } else {
                        lp_lon = aatan2(this->m_proj_parm.w * xy_x * z,2. * z * z - 1)/this->m_proj_parm.w;
                        lp_lat = aasin(z * xy_y);
                    }
                }

                static inline std::string get_name()
                {
                    return "hammer_spheroid";
                }

            };

            // Hammer & Eckert-Greifendorff
            template <typename Params, typename Parameters, typename T>
            inline void setup_hammer(Params const& params, Parameters& par, par_hammer<T>& proj_parm)
            {
                T tmp;

                if (pj_param_f<srs::spar::w>(params, "W", srs::dpar::w, tmp)) {
                    if ((proj_parm.w = fabs(tmp)) <= 0.)
                        BOOST_THROW_EXCEPTION( projection_exception(error_w_or_m_zero_or_less) );
                } else
                    proj_parm.w = .5;
                if (pj_param_f<srs::spar::m>(params, "M", srs::dpar::m, tmp)) {
                    if ((proj_parm.m = fabs(tmp)) <= 0.)
                        BOOST_THROW_EXCEPTION( projection_exception(error_w_or_m_zero_or_less) );
                } else
                    proj_parm.m = 1.;

                proj_parm.rm = 1. / proj_parm.m;
                proj_parm.m /= proj_parm.w;

                par.es = 0.;
            }

    }} // namespace detail::hammer
    #endif // doxygen

    /*!
        \brief Hammer & Eckert-Greifendorff projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
         - no inverse
        \par Projection parameters
         - W (real)
         - M (real)
        \par Example
        \image html ex_hammer.gif
    */
    template <typename T, typename Parameters>
    struct hammer_spheroid : public detail::hammer::base_hammer_spheroid<T, Parameters>
    {
        template <typename Params>
        inline hammer_spheroid(Params const& params, Parameters & par)
        {
            detail::hammer::setup_hammer(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_hammer, hammer_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(hammer_entry, hammer_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(hammer_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(hammer, hammer_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_HAMMER_HPP


/* hammer.hpp
lpRuniD97NtX1uNacXvpZccqjbLH9dK4P3Rp6PUg3HJYeIxyWGgoh7Os4ZaDotDP0RGV/MEZyhhWsXFiLoA8iNZipuVFawmwAxaVZfomizwztSdKT5a+w0LC9B0WUaGP3PFynN+IyQ5ONlpZU77oPRVXbzY4nMaMwAhuBN5dHqLzk2WDEVjLT+Mx3XsW7mBzkBtRr0o6RZZwRVncblq+X3hEV1cyW/yYnoRwqyeO6elgkTD9mJ4e+hAgx+zLX3++6YDe4ji+Trm1L1unrIw7tU556jn1nNxjvP8uU67FRap7M/X97mw+aVTQcoCYzVgMKloK6AU4mRI5N7o1hs46UNBORgymeLcDA2ek6PRE+p5z433c+Yxw5ivYfRinZ8r5itFJar5ih2mHs35emJ8R0vcE8y+77LCNOid8UW/j4H5CC2Z+G1i7kMRc7NAHc8lDH8n80AeDqUMfu7l9vmCxss8LlH1+wip3u8Tr/LF+dJVFF7a0crcdH/udl1iMKdhpN0wjiGsK5CYbOSCRJ7Pt91RoQQynFfGz+vr17WxFSQH9NcYz/cUSxJ2AEGcsMHGHfjkHeAMsc7GihPxsLaqmAm/veD/bipOv+i/5DJFvZtADkKkZhNUPuS8QMjYvX2BhiQ+WyreaJlT49pqmhNf0MzEU+VPNQK7K9zx+JkYHdNbPxOxX+SU3Ug2lzdx8I9VQ70gwIr/YSNWEX+xwxeNqI5VexK9osojPaabzZKuV0ms6EyNBrJLp14YUupScvaDqYtt86QZ8xDEF5vJuxipIYyzOp8mgXDHnchaXedFjIdQyDjJ7RybyST5VUrmspHJp1N4D36mtCCbruIMvRVh9H0h8YUeVWJKDPfyuFJ0vk8te9k/2rgQ8quoKzwoDCUxAlqAsgwSIgBoFbSJYJxrroFGjoI2VahSscWupJJhWlmCCJh1AVBSsYrFai9ZW1KqRWpu4EVzaiGuttdQuznRsRbFCXTL9zzn33vfezMuC3WzLfN+bd9+555577r6dc+6+yB4HMVlDcX50rTID0k6VGUCyVGZmWCoznHwtPVUmyb/5Zkr+Nc7k56SDnuTZYUOza40X+No1Xo4LOzRednsyNF5e89kb+bP40vUVmfBTn61y/qBQa7wA22i8wMup8WKSc44k57mbjMaLlZwZnUjO6oFW1LUnWqKVR2f2Cg6yFwjZhUx2uZPsHz4B2ZKBVhpUsXgyFWnyjCINuZL7D2Tac7RuCpKcZ7t5OTq9NORQrIml9slAIyC15x4VbKhPTDx0QB9u/Rqg65Z0mabXHmEp1OSqUi4ij9TZWnUj1pVOTixbJ2eSzlZ3nRx7BFatzjfMTDCaRqBem281Pq31FeW2oSz4z1GD6hxTW/YzjXSQyvYSeIevWAE1LrKG46kNJr+OZaiOsPYI02qLFOdG1jMP9XA/PUaSNm3tAFNNjz2MG+6c5Im5OiHFPmc/80OpQlNvdOlnvvsRqtAHOZnWjGhbtvZMDSNFlNocqxtQNVZXsn7NIXuN/YlE98Q6iu59Z3RTKbqrcpSNLDU32OShn9IDdapBTSU80HMZdTc5oL8Pa3H4GYZPzoV5Pgfeq66hX9ehUTIkJrKVffEdpxnTPF3jTTUkDaJcewOBU+syWFIfKFoCQGQkS1cI7QXEB5fHwYlTXQhgpeZb1+ztnfrQFRIMjJaEFgyyV+xkGPqY9lIML3/elzkNCYSveMTnYmQG8tYY5WX76CYTyq5GtNxAXdSIqm2eW2hKgZ8Vizc7ltojtKfPxXOU9vRne8q4otWGdkn9K7vBqA1Z9e/+3ah/fXEUkWXU50xnDeudZZ8sjSF4G0UOy7yPaazPFIlmznQzX8s=
*/