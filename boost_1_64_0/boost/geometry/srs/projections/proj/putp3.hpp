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

#ifndef BOOST_GEOMETRY_PROJECTIONS_PUTP3_HPP
#define BOOST_GEOMETRY_PROJECTIONS_PUTP3_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace putp3
    {

            static const double C = 0.79788456;
            static const double RPISQ = 0.1013211836;

            template <typename T>
            struct par_putp3
            {
                T    A;
            };

            template <typename T, typename Parameters>
            struct base_putp3_spheroid
            {
                par_putp3<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    xy_x = C * lp_lon * (1. - this->m_proj_parm.A * lp_lat * lp_lat);
                    xy_y = C * lp_lat;
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    lp_lat = xy_y / C;
                    lp_lon = xy_x / (C * (1. - this->m_proj_parm.A * lp_lat * lp_lat));
                }

                static inline std::string get_name()
                {
                    return "putp3_spheroid";
                }

            };


            // Putnins P3
            template <typename Parameters, typename T>
            inline void setup_putp3(Parameters& par, par_putp3<T>& proj_parm)
            {
                proj_parm.A = 4. * RPISQ;
                
                par.es = 0.;
            }

            // Putnins P3'
            template <typename Parameters, typename T>
            inline void setup_putp3p(Parameters& par, par_putp3<T>& proj_parm)
            {
                proj_parm.A = 2. * RPISQ;
                
                par.es = 0.;
            }

    }} // namespace detail::putp3
    #endif // doxygen

    /*!
        \brief Putnins P3 projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_putp3.gif
    */
    template <typename T, typename Parameters>
    struct putp3_spheroid : public detail::putp3::base_putp3_spheroid<T, Parameters>
    {
        template <typename Params>
        inline putp3_spheroid(Params const& , Parameters & par)
        {
            detail::putp3::setup_putp3(par, this->m_proj_parm);
        }
    };

    /*!
        \brief Putnins P3' projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_putp3p.gif
    */
    template <typename T, typename Parameters>
    struct putp3p_spheroid : public detail::putp3::base_putp3_spheroid<T, Parameters>
    {
        template <typename Params>
        inline putp3p_spheroid(Params const& , Parameters & par)
        {
            detail::putp3::setup_putp3p(par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_putp3, putp3_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_putp3p, putp3p_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(putp3_entry, putp3_spheroid)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(putp3p_entry, putp3p_spheroid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(putp3_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(putp3, putp3_entry)
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(putp3p, putp3p_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_PUTP3_HPP


/* putp3.hpp
by3SbWW9b0gtl/E7LuNXVMYtehnHYhn93BZXVoUscsxb+wdmLzk3kuctpt/OwAylEIx9sai59jiX4qZS8vThrTsXStloysdYKmYWScyE3zeUDwQb7Su9CZUiEV1e7BkvScGW/Fo6AdwJLFRSE5T+R06fJtJLjdUivZTTn+P0czkdyrqL05k86ytBQMaMi3ncfKIu47nbaK2L5sXWc/4uqvwxkD8v9hJHN94gix1C0TUcbdwgS+tL0bUcvQOiuW8zIZpnc2/4YpPX+cxLBm4z3p2/vxGkcsh0Lrn458ENf/6/hPf/5iXs7z9hGfcZ0xWL3OJS/q/G0SrUS9uRR9yIqBMfrFu4xW1SPnZlVTL52OgLHLboPXmrtuB6tUXfqio/bmyCfKz2JusW/V/jWnxudtxfP3lrE/vryefwulIwxmF//S33+85pal15VVX93jHNnpdzx5iLyveMpprQeHQ0Y8Y0Lx8LB9V3RSho7p57nJ9MPvZRkba/bsPD0IYqMUOvxJ9G28/LGQy9q1zur03gZaNt5+XALOv+euRYub9uLPyv7K/t9PTM3AT52EQekO/LFD1tU82rLTTlY1PGOMznEuG/kTK30TPPKbTKx7LPS5SP9TjPKh/74lyviO8wJlE+xmQ8NGiVj/199MGcWVtML7PmNCcfO/Nch355m/vlkamKzv+k+mXy2QnysYk3W+n8b+e0mM6b9/9f2QS9zxjN9H7RWQ70voqb8NF1it5fU034/VnN0nv0LJPe/8ho7ic0Hh3NZWc1Lx874hx1nm4hR/Cdo9F7LVeiC1Vihl6J90bZ6X0TQxtTJL2bwKtG2ej9DxVWej9mnKT3wKifBb1vmJ2wfmZz6zKmKHp/RTVvR4GzfIy7tdAonJ4gH+vJ6J4vlZ1lYqtkbF0SV+NN6Qd5SHS0x3y/ggVkrIoEZQFVbhrtQJXjuK6BUkWVm1Vl3zozQUAWvMFKla+OOghmk+D/qiJRX29pZgvlY/tuaoKeHx/F9Dz/DAd6PoYb3+FaRc91qvF/OaNZ+dj0M0x6HsBoXr2G6FlHc9cZzcvHCkcfLD2vGKXR88lciRFUiRl6JTLPsMvHhjN09jVyiprAu0fa5GM9rrfS89tnSnoeNvK/RM/qPZGGmf+B90QKcL9rnXSq+Bu4eFK3sPoMkN9syurHv2FlnXIqTCmqMM9SP32YD2/3dYugZ6rI0AFiNEO/kH5qZlu/EJ+aoXHytt5jUeSqNCgU1jHHXC3AzGor/uawc2gwQE0TTnjOx7k12NeXTSpyqQzhAz6CAT8EqAZstuxnAHVMDslIQHu0jAzXvwgeGFIZuZ/mZ5fPTif79xtpKrA4QUmxquCLh7UfsAWrpCxKHwpEqP37PGakZyrm+0offNanTxylxRTPA6VpvAbmbLVq8yrt14ps+ai7VEuj/1imYeoVddf0iqQeag5BqaeESNNoajdKDTznglCEjC/z+dGm+POkvFmeb76KsyDtHg8XHGYFRLGuLkh7CvKwRsl8qqnxfhla3FAffmKRvfAMFN9C5Y3nIX/rvfi4q8W9yNM9mnJ5HMcqcNPY9Uc1fMrCeE5LDDKJsvDMlojq3wLBzf+UMUKBkgfY1uQLpiud8oi5KNPCAx8WwefuqWRVdQ4resk3tEtxYSrhdYifEf++Ue20Gss7KzsO1wBlPNcJ01izKV28Gdbid0Qc2iM4eYAYHJenBPsbku03x15P3cAHutOj2h6Mj5tD3Xz+vwKXbrLfeck8/w/HPRgbGJnGMxMnW7wBzSQkwxnJCELynUtDkslIbhBiWG95Hq/lz0d5c7QJ/spboNMZzw+Xs885Dc+mPMJzvBS1Ku817PMkMOdFlz0=
*/