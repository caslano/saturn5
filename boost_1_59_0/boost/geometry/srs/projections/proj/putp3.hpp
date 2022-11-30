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
IqiuKJSLbqgr4d7ARZWaKTDjrlaz6eMuaRH2D31liGNzXJnH+0KQN/yjHSpO0KHGODVRZtvBSEMs4Isp9wbfEa2HUlomwPglJldzzkU7bvc26kpcUZ6ex3nwbwP6uYMkPO0d+a+ATueDeDKLZwRUs3lOaBVQilOeA5yfiws7n3kFVNX5fbyK/NUCLqQN9tp3nBqa6B+16fzcRmSqWlbQdWqm8EgaWIcTw6Oow8kypfMECJmYoRhGCeKXHoLXdibUwcYJEJODfptDEaLFkZARyhkQthIiBWklKSGrJ4TrrBiMneEcYYSVLZ6r6M3VutXDUsHiUXB8ReT65ZmrnKRZXPGE8EpGKFKPQ+oNwXrLIlgcAgGEfTx0KZFzXWZDu0+YBsJ9X3B1hgcfaH7GpQ3ZJDa61mIPWrTAfrOKLUyIDRPxWS+wJj3a9RmnUJn4mItZKK++gZ2XV/27YRRsWQClh4xJdxXQlo4vjn7uF27bGKDgdEZT+YthNe/kilJHLrRFUu0sYBSVsSZjQttUh9O2skQUppNLS58LhXI7oRWnKdPA8YYmMEHGEPedR3i5NZB42KuZpDC5BeAuRpf0RyNYdTNBtepbkXFs0WvFzwnHqjk1oTm2ueqvD2oBf4PWI202j/xppJam9Y6KlWJwi77V6lvsi/MS1Gr/X7tKfQsT8I6+t5FSRY1PtrqyoUSu3kHWogqxPl6uChuX4fNfRoXh4VBRG3ISjuEdXOo2K365yO/v39DsYlYVrVx6G5ywy0sKNomnuKvCibMSVIgnEQ3dv199/+wxa1QUnpLGuL1onua6vjvKClIjLbFzeDiUZ4OpFLMJX2fD8rJ/++HdMthuwbeYS8o6W8DXKh5ZLnB+FVM22mLJe6Jv4Yjbz/NHlYwzvn42PQh1xphYFS6ZLKNtcMjGgDijDTojXtR+c5Ic0+mPAe5euXynXAxZKleXOGcnKjHZ/c3cvnhnlB5yGiGz0ToXnQStRJpOxyavOnEE5iTFS0Nhx3Tmcn0ZJmMzmtlIUFLAesLFV++P+PRiSJw9c2ypAiPUdyey0TQiPv36k1vEkbhKWzoK9xnhmWot5HCow9XYBvI1+q+TTGGFuOn0MvXV64lBu+JfYCxiUfrUm7PhvbI2ZszKGyvEg+fhY/Di/MfEWqgWOhHFm3Ybky5zg9AZYcjqxK8lqPDo/sIg8jjL3hzR+dC/Zxsi1DszNcIdIcLxqU2eldATsjfYlhvlYohESnX8E/tnHhLJchVAQSr4SDseoqKbGaya/B1HxjCTEq/C1GH+ZkN8kAzzexC6QzyKGneF7x8KqTYvLOoGhd2cjkOnCAuHixTur5SyXV4TrvMMouITFM/VZGpB0K3pcK1YuDUHg2o5bcNdbZTtjthCNWT/zm7SAJF6mfTLgh1LqiEFb1trp1GpFb19mP2hZK6qvSw4OmdSnro+3r9KjmlF6lLg6b2mfTkTCdG+E65+Q3p6VEOsDpD3bMPJg3LlrQglCmqV9+KXDaVQi8oO70h7i4CkpIVtR2Rz6wuk4Lmxos8qQsmZx41CJC2maBvBCSr0Ruokn8KTGRUmWeCPeqTvEfhgcFvzgFGV4M8sw9OHxF3EaTMu+jdefRpBmf902OY7Hsvy0502bmmhecIeDcBEeacQy29cI01vk8HM+XRCR1CGLv8ghjk/VTPBLjcCW0h7lwoHFzWbdU96GkkZbE5e8cgCSWyVZeqxCGc9Q5SgtzwpabPhsjdqxfh2Gj1MDL9nipwmvH2ylfKnyGR+iGjCmvpXj+trUdWO10rIgwgS1N59PaU873Ra3Tem81Vcc3uWhN3SV/ejkaf68PEDuOtqKC8JoZDZnQXkQ6BxfUS/9uzfyMm/6bMQ0w7YMHMTFnGEYcG6Y6vnyS5POBh3CiRcnvEzJj1r0rg7IgP3U63xUrUTSjLFdMQS0La+TmE7QcsdujQaLFZta51KLi7oNMXG2bD7NL74X5HusWRfRHWqPstYpucHJd80N+UPbgL75wXyN41wVk/uM0Z+OIjTpljH70qx18y72DwjzfHbJPLfShq0xl/MDiWO82W3YFCK7fFdJTJIdZoxMr5YOkhH6XHQTIghp80Zva4mE0qus/H/UGa4W2RoXUrcbj9sBCZyQxA5S+Bx0PUAY7pJrsTo6l2nKxR3z1VWxLwHre7WBeU7a4g/oe9rZ1t7I69X+ec6rXUXanTDy4/y/F48QfZE2mFeC47yfHf48lm8JVa9Qxqpn+ElRIscl9TuVuu2cdCJ85893QSfjc1whQDDo5vn3vsQYp3e7tvnXuCaKF8rVyzoPnaO7TXDemdzzWWU3rXXe/Kstvd1uDPvEniDtNLj1WDxAty3qBG4L7+23ehma7FaGIvzfz0w6H5vh3Nm/pg9wfT+eDXwf7kG5vXOn05fcjsfnbZ+7hq0+L3MDwhIxvrQdriuZHT2GGW/fSCFR/fysb+b7jKPUFPpf7wd5wmxfkzurJ3ces32pLzNwzHbtNmPFn3slY4u5wJPqPMtDIAv1bCXAO9l87Me32ekWYFWgHc/SrWB50OLq8BKlZ/j/kj+KzOKP7DnWASzu/T6TeS4Q0NoqqsVGFxyrYAC/GF91Xu2tP/qmvVObeCjt6I3e2X3zf/yIc/m81YWsJzKvPO6FWB/5eqrU8LH0W0V/FHf4zu91K9o5y3gsyGbIeR3H2hNwC/wDkfiud3p/nAAF2nRWp3hu1dN8MmQw6Oz49jg+9bSyNXteffx9FQCPnA3ek4iyfYvtfJwOx/HfN76psfxxLjlfldBMCvwtPjrqbRWYOnJ42ygXFKhC2ggj0YU+T59Uo557eu65dz/2n3d430fE2l/8Xn51DLN6P9RZL2lZ7D1oPDxTu33FTgoKbTksSGUvT3HKuBterWVFbzic7lDvPMypiZJInBq92a5MXS0KG8A3NE/Z8hEEYOEdohXP6keUU5ZbSVdHuKtSFjV/qfKqEQXQaFW0a8Wlpm4TvfzK7Ixvmo1Y/OCN6N4ZAXWaE9ypnYl8m+R4m/uGW9O1zzPtjNdH7M7n3n+g+gqiM7vqzj2iS1czkRV5OWE3NUBXRdnP6ML+Yh1IDC6lArzQqxjmVCsMRlVHtVokr9T85TTjZnEhBSYq0LzOS117zSEd1PJRyNHXuIz4WdrltfJseUELrp3nRxNd4/r/L743Qw1dUJiiZrAjPci4VSGsqBHYzubkh+sHhibhGv/NnvQ8+KIvb7YJLhb19LpjSr+3pxb19w6uQJTVV2NtHlMVDpxpBBHI8bfsEN+Ff4qLgxaZMhZipjh0FMSNUG6P3gM6+abnal87MWCSEaCnSFn2ef9HLCzPze835ygvpp18n9yf6ZnMF3/8g10YiYcfsHhEfImQN9/bBn9XU5ME6Ha+B7ygQn2q5N63fNlFY8JFneIq+hIM6qNqNSCG7dyFP+V5Z3W7QOk/dtPdnuuGAnyX3Kmpdq9SpI4OLoMZaBtKK73sW4TqTeRdZ+f/RRrckw5/8JKid1fAhPTnXG/x5cHJsZ9Xd0f2HfegCD5Drt43bb9Sq5ZQANrHS4bXie8K4aArzYCm42KY4BRr/h0/AZMLnb4DadF4HRJ+52sisCl7HshfH3qd/eTtDxzKfYKymkERvq0ACP7DTwfFM5f+Wm5f6ka7gN+moj8IGSF9QiY1CuMepm8+Veu4rD1CznDWdEaY0psMUbV9F/fGXuIgafmdIGceiF+zlSxF6oPs/13UT+nxPBffat8XNlGgyirGT/ChnOyJGLsTg8lqMNujlGgpxwbjuMHflBBl1W1/2ElTZ+V1GP+LM/CPjYTKaPt5Hg5OiStHHu6qjKNVHAuma4bMt5z9U0o1Rip/ePSyOALU+f6jBh0FyUkT0hBOhYvRb8qf4EwMdl1zTGJYL0nrWQxaVOghSmkq6BYoRFeurDdV8wC5TnVwTlQlIrDFe1FeEY7S/FbQfjw31CPPRs6O/tV9gSj4e0fWhONMLFoISvuClsCubduRD5cDEPBFy/o34bpAsstoi/fjCypMWJLw3J9fRnQ8D4BFnbb48PTn4kv/oR0Hxv5knrebySA+KfOweqslaDjuV1LUfv8JeotMk6tFxuopL+aMcp29124ptQImLbmGr2vri+txT+Y2HXKQ8/zi7U3fIS/aW37zS3GMi0vJE24Geh+hdidEbrEV8PixNquv/kXuSH7fH8O8OO6u9kdEtMWd0FHwI5CW8sjYDgjI1HBfHoWBXy7uTZGL10zc9uPia+qcdfoRGqtOfV5KY7HoeP0WSCyb+jhCJFbse/89sgYzn17M1D8hFMf+h3wTs4jbKPPBV6cXrng4coa0o3PK1QRZ/ouLNzLo9O3S5lSzQ8xX3/LTRP+4rWMfdvrRD3oYQlnas3iwkvd3Mdk+xEySoUI2fFcKiUxx8274O62fUPaMdbheYaZpgVpXTQEZ3XSo4vKxs2ocPXgwX+i7y4aGbKkiXO5DE2Z/FvkLadYIRCj6/wGFbQkvb8hb55XuGf2Y9mMp1VUoLs7Fdgb4b8PXRKU+8IeUvqLZMSnWK+81H0SfgvFxfQIKSEyWpN3vRmus1IZ6qyTGdVdumHETDhLtwLpZEFpCb6usve6YqmtM9Wt+O+sp44WvU6gsNFpRduJJMOzabp9TIAfHTEnm55ysOXfKEIyyiDBsvhs3XO00aHX69G9E/c7ZygGw2ZMDIpEN/G2GH/OyCK4IcBPtoTAlnLS7YmIZEMS1/b1I0i5tNeYWQXa16z3Euw1xTjErRNfplUvxjfggaHNZ2qnAEv8B5tqovX+SdDW7EC3wZlGzI5PqpWFwmy6dK7tuM3l4NSpVaWJNaSWwwZMXvkFDaGFpEwiweGU7dr3gmV5okLihR5pP6o6Ns2KCPqipp59Um6NFmVRcrWcX3zvht+LGxL1SEb09fdQIEK6TTIr2sLnPxuH/ZfR0KVeFdGc4t3UFX5EDieiZ2DDqlFiT6H0/u1M9/hkNApD0J8UFa+mgxOTnr1FC20/PGvmpGb37v8LLMDkwBp9GQLwFTb0oVnnXKfNVDnPXIrF+sQsB82QVxmU+5VP6620kXZ/tP5E2q6D/Mfdzq/WXmm2kD3I9zUC8nDKfly2UIiTUmYNkwDiAAYs+dNmEjmk0Xt6GOs2BYvSyTm2CFkufKOUHSLwdLOMwlMsjT6T0uwhtn/7mCJyx1iKQMie9vS+1XQfajsJ73PKYqzvgtdKF1cGoIbt3TCSX7UtFeRzikX2uMbA0uhuk3qB3k+DMP+4FJRi7eYmAzrcPXkgzss7yfaRPV+v3lBB/3eU32KHhUdO7+JyJethlM8BE0YJowNdmxiUd9Mo/sYsD8svkjZ1bbB7m8trXTP8p2pxFNTN8eukFiA2qLR4zsz2W8rU4rs8G+4jmm8zH8hI6X//fXD5buZAKNvZEtmSXozTODyFw/a/Py0ctkYG84b0jAzGunSthnTGo/qVzudsAYsebOsczJ0pZneJEhmipRTFQ2eNPWwtxh7yP8lvmeusEBJYml+/C82qPeRmXbtyqSy5m12Mm66L//XCVlk61mx3eL0dYcB4buI6CgQiCRc6TMVeTGuPf8ojfNaeBLz1usT/o4WhiqDijPxqlZeGRbiZkXKIijr/pjf8x1j8iyYfpf6C7krRCUwwIpoAHbYLoiyywKXGvtzoUSUvb40fIofsje8lkAFWSDINc/G9oLKkOH+g9toKBqfEohPX8b65M8TReFlLnDyLr+VrFLp++pdwnBHm6boIKYbVZIzEiFMW5CIq3+T1hjD2fAxyxuaptsBOKQYrfJJofik1zomwzHL96occz/NXMSJVsnTkoX41+G/DUuLQw2jpGYrSvL+UyckJYKgJXDGO2iJAzcfk2n8HHK4YVC5vBCovbiggyIA8Te/Un3O8yA0+wI6ESjY8L6eDnu3JItkG+03iWkhevzt2jgXvvAdzgrjJP5HeF/GZz8gLuPJewM764ZTZTvKRcxUUYSF/2ITL1Bp1H+4LgaCdrL5gSJYcomjUMfuTz3ahx7clWAd/YHXTQArIP3gH4uzzNmt+8o1PCI+kcF9kjA9UO1tIKZWM3CUV4Hof7u6snBT3Q8ywV/APepgfC35b2DEZ3NSY62k7flhdjDPV6o5uBnDVXZC1sZ6gnWWh8dggOADS4/EB8VTJcP9Tr/vhLabHcq5XRcZ2dqO3kzlpp0WE+V/MD9KgH5D93o0cQj97uxcwzhHEQiB/4j6kjrdCGU9ou15ch1ukFe91ciQIcQWaqzNZqgG+7yjxm0yPQO9K1e8TBo3NsP8k+XFz1QHh45afTZs03LIvOffsc0NEEGe4tqVK4YtDsvtxHfbJfCHxiV3+eReOynUD+jTh2uu7hk8UC454O197+diwiwR0HyiU+8E0AZ6D5WxlR9FlUL4pNRFCfiOH/4jR//lb75BHbrdkrm2ZmlqcCSHaDmn+pxIT8vxuCmcTQUjOpkP5b9JOl5/EcAWXPavP9nFov4zEyHuSLc+m099W5FXD0WDeSsenlQM2measzVXFb7CFY55gOX58n3+sMQGGYsV3XsDQ85ljQEFM1dZJzEnhdvUloNGmiX4f/L7KecxCOfFTL4CiBOMwTvKpljQ9UymT7OrwIDGthzxRXDiRKPyLcNTu4eXdMQAlSljK0YJ0fc3Apt3iTTbAj7aFobsP9TUXKE1HGLZaQpfAgQcTrFqMFpWJU/rl9TRSUxhrJhnLjCSlarbQYQ12Xy4mazgwwd1Kzyo9CHuiNimYqLegZeQ2abTlXmJ7Y46o5HJzqJP+FvAv7fKyUSBfn1P+2Yd9qPOtCjluZQ2OGboz7gj7QVp5crxkA1t7+0IPcx7+afHiJNtidvAXdsoSAtuVkgZEbTEz22QQ3T9JVbplfTko03hK5pdQOSjvrXSzQUTz4x0FX2jyZOTYWzUInVbvkvYtUJWcro29xqulPW/H2jtTx/ACjsdiQOo/8VNTlYL/Fyvn0CQMoyvhsW3btu15x7Zt27Zt27Zt27bt+53/cHepLLJJPV3pqlSzZKR8D194oe+MKKJeUl/LaH8qiFtysKAW/NmFfC+M4ft8/xXAp/Q9G0Rdlvy5fTK818DH/DaRFKYTAOaX110HDuB2xw5chPWDDdiAwjUj2C/464Fz+RuUgpLH3/mK7PcgejCIixNiN5pCJo6xkAIOwXTM6aPO9C/qo+9A92fWkxr8iiEj+RPgVqowb5yQXxQ39dRyyScM7EUK9PvGibq+ulDkJYIjqGuOiLbO/phEKT82+Zs6toqjYsjmtgPv2q/+89igYJG7D9MVbW6qaaXy8GPt8BWjL0NNhawMm4u/B+zABF9f49GjdTjmF4CUDeBgycvupbbb7QrdrM29uqqqOsozboUM2bAwnI89sbNnWc/1ngI7pTZ6zikvEIW7tb75RY22Yr3v/kU2Z5S99roz8ORAnohwsM6Las0egpMDiMMGfI0AipEAw6UOETXzGUqW8J3Nz0DN85EHzVce7iJGorBEKB3HL5Rg+sbI5s2FDlkL2xJuLLLZ70zVixRGxW7zZkWlXi9LQGkBQTVfl2j9rcP70nu/eqti4fh9XIPtxl7be4e2/8w7+6AJgCOOR8Qw9h1Mv4BndwsbKQgEx948A/APg8UN
*/