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

#ifndef BOOST_GEOMETRY_PROJECTIONS_EQC_HPP
#define BOOST_GEOMETRY_PROJECTIONS_EQC_HPP

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
    namespace detail { namespace eqc
    {
            template <typename T>
            struct par_eqc
            {
                T rc;
            };

            template <typename T, typename Parameters>
            struct base_eqc_spheroid
            {
                par_eqc<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    xy_x = this->m_proj_parm.rc * lp_lon;
                    xy_y = lp_lat - par.phi0;
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    lp_lon = xy_x / this->m_proj_parm.rc;
                    lp_lat = xy_y + par.phi0;
                }

                static inline std::string get_name()
                {
                    return "eqc_spheroid";
                }

            };

            // Equidistant Cylindrical (Plate Caree)
            template <typename Params, typename Parameters, typename T>
            inline void setup_eqc(Params const& params, Parameters& par, par_eqc<T>& proj_parm)
            {
                proj_parm.rc = cos(pj_get_param_r<T, srs::spar::lat_ts>(params, "lat_ts", srs::dpar::lat_ts));
                if (proj_parm.rc <= 0.)
                    BOOST_THROW_EXCEPTION( projection_exception(error_lat_ts_larger_than_90) );
                par.es = 0.;
            }

    }} // namespace detail::eqc
    #endif // doxygen

    /*!
        \brief Equidistant Cylindrical (Plate Caree) projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Spheroid
        \par Projection parameters
         - lat_ts: Latitude of true scale (degrees)
         - lat_0: Latitude of origin
        \par Example
        \image html ex_eqc.gif
    */
    template <typename T, typename Parameters>
    struct eqc_spheroid : public detail::eqc::base_eqc_spheroid<T, Parameters>
    {
        template <typename Params>
        inline eqc_spheroid(Params const& params, Parameters & par)
        {
            detail::eqc::setup_eqc(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_eqc, eqc_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(eqc_entry, eqc_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(eqc_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(eqc, eqc_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_EQC_HPP


/* eqc.hpp
d3kNX3WgH2Mg3joYvFHsAx0CnH2n1cP4ZvF143BsZva+pI/ATsYhfnyEgtjs7R0JPuvau1HnLOVSguJ/bFyRAp3A3g3eudD56fx0fjo/nZ/OT+en89P56fx0fjo/nZ//sc+Lev/By0nsq2LP5dyZ7HnOMfspgj0Lb46J7XnZNCa276VbD/YP9Gh/b0KvHuH+hH49Wt/bMZhncg/MMP4eQRrVo+39MFfit49mj0rO1uz54lzjgumc5TwD/539/dP3BG8sZ3U41+o9zL5oFqOTiWuk4yNfwpnhTyZytuEU8t/vqYGvg8e5Hu8T4iucyX1wHDEFytvmYPaReOxrPY9zpGvYt8Wem8PYI1ExCL+9hDNq7JnM3YE9ZuQ/5Hq3zf1T0z9jH1Mx+8R6OALvX0/PscDZ62T2FTGGmq5m71NA03KLrjuSL4s02v+7R9jm3gPo37Wc5VvAPqEziN2w/75gJPED4j3DphDT+Q3ncShT9qeoR8f2+ph9UbIP0ft8KJy95UM96ml/39luxDXiGJfZjrvF+49a36vV+h6km25hf91ljF87Y/fx+8TRajmrzL7ukm7su1vltckvdQnscVvDOxo2Eivc5LZZ9tOcNUx8ExlYx166u9h7lcV+Tuo6/FPideUt+W1PPdayvg3fcf7mFNfEoLr2Ie7q3wvAd/9ZfPvr5/ur4CxfPDGoV/sDP489D9sTWyIG9ecBlPMaMcqB0Eexb58yexCD6vx0fjo/nZ/OT+en89P56fx0fjo//x2f/VS4V3Ul6dJtOYfKenwW/q3/+S0bau9fwnnPG3mGv+t/ZvEoi3XqH1jHz3f4e2vW2llj/mYh50fjgI9nvfpT/xwbvkI65+2f9fd7AQPvTdaO38WfqFyBz5DH86HsH97A+9PwL67oSlmLWeM+gzqreI9cHGX2xL8oYU8wDVyyK/kW4cv05e80/Iwkzq3y/GF/3+Zo8KeFsYL1e1POeOq81/dBKKsLexu6hHtCJ5DiSadsxfk6l/Jpzxc8+8ajzC7UDWwJv1c74d7k1eBdoehvV37j05R2BZ/nz42lLV2pl/yDtqUd4FzrUaYibU355D1S+QkckW70vzOoa3Z4jmIb/r7SoQ4fn3SUE+7LP4Z0LOk40vGkExzqIK0jnUQ62QnrOJV0Gul0h3pJZ5LOIp3tQAcSpFXnkM51wr3v55P+SLqAdCHpItLFpEtI+5AWk5aQlpL2/kc799RDRwAFQLi2bdu2bdu2bSN16tR2atu2bSO1PUn7H5omM7nf233a7J5NNnsW1VAHdVEP9dEADdEIjdEETdEMzdECLdEKrdEGbdEO7dEBHdEJndEFXdEN3QP+OfY90Qu90Qd90Q/9MQADMQiDMQT7sQqrsQZrsQ7rsQEbsQmbsQVbse3v+8k7sBO7sBt7MBTDMByREBlREBXREB1JEBOxEBtxEBfxEB8JkBCJkBgxkBTJkBwpkBKpkBppkBbpkB4ZkBGZkBlZkBXZkB05kBO5kBt5kBf5kB8FUBCFUBhFUBTFUBwlUBKlUBplUBblUB4VUBGVUBlVUBURwSkeIBRC/93pCYtwCA8uGR4f8D9EQuS/Oy9REQ3REQMxEQuxEQdxEQ/xkQAJkQiJkQRJkQzJ/86rlEiF1H/3cdIiHdIjAzIiEzIjC7IiG7IjB3IiF3L/3fHJi3wBOHYogIIo9HfnpgiKohiKowRKohRKowzKohzKowIq/t2HqYwqqIpqqI4aqIlaqI06qPt3FtdHAzREIzRGEzRFMzRHC7REK7RGG7RFO7RHB3REJ3RGF3T9O+O7owd6ohd6ow/6oh/6YwAGYhAGYwiGYhiG/51rIzASozAaYzAW4wL8mYc=
*/