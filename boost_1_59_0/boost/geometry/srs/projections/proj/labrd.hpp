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

#ifndef BOOST_GEOMETRY_PROJECTIONS_LABRD_HPP
#define BOOST_GEOMETRY_PROJECTIONS_LABRD_HPP

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
    namespace detail { namespace labrd
    {
            static const double epsilon = 1.e-10;

            template <typename T>
            struct par_labrd
            {
                T    Az, kRg, p0s, A, C, Ca, Cb, Cc, Cd;
            };

            template <typename T, typename Parameters>
            struct base_labrd_ellipsoid
            {
                par_labrd<T> m_proj_parm;

                // FORWARD(e_forward)
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& par, T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T fourth_pi = detail::fourth_pi<T>();

                    T V1, V2, ps, sinps, cosps, sinps2, cosps2;
                    T I1, I2, I3, I4, I5, I6, x2, y2, t;

                    V1 = this->m_proj_parm.A * log( tan(fourth_pi + .5 * lp_lat) );
                    t = par.e * sin(lp_lat);
                    V2 = .5 * par.e * this->m_proj_parm.A * log ((1. + t)/(1. - t));
                    ps = 2. * (atan(exp(V1 - V2 + this->m_proj_parm.C)) - fourth_pi);
                    I1 = ps - this->m_proj_parm.p0s;
                    cosps = cos(ps);    cosps2 = cosps * cosps;
                    sinps = sin(ps);    sinps2 = sinps * sinps;
                    I4 = this->m_proj_parm.A * cosps;
                    I2 = .5 * this->m_proj_parm.A * I4 * sinps;
                    I3 = I2 * this->m_proj_parm.A * this->m_proj_parm.A * (5. * cosps2 - sinps2) / 12.;
                    I6 = I4 * this->m_proj_parm.A * this->m_proj_parm.A;
                    I5 = I6 * (cosps2 - sinps2) / 6.;
                    I6 *= this->m_proj_parm.A * this->m_proj_parm.A *
                        (5. * cosps2 * cosps2 + sinps2 * (sinps2 - 18. * cosps2)) / 120.;
                    t = lp_lon * lp_lon;
                    xy_x = this->m_proj_parm.kRg * lp_lon * (I4 + t * (I5 + t * I6));
                    xy_y = this->m_proj_parm.kRg * (I1 + t * (I2 + t * I3));
                    x2 = xy_x * xy_x;
                    y2 = xy_y * xy_y;
                    V1 = 3. * xy_x * y2 - xy_x * x2;
                    V2 = xy_y * y2 - 3. * x2 * xy_y;
                    xy_x += this->m_proj_parm.Ca * V1 + this->m_proj_parm.Cb * V2;
                    xy_y += this->m_proj_parm.Ca * V2 - this->m_proj_parm.Cb * V1;
                }

                // INVERSE(e_inverse)  ellipsoid & spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& par, T xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T fourth_pi = detail::fourth_pi<T>();

                    /* t = 0.0 optimization is to avoid a false positive cppcheck warning */
                    /* (cppcheck git beaf29c15867984aa3c2a15cf15bd7576ccde2b3). Might no */
                    /* longer be necessary with later versions. */
                    T x2, y2, V1, V2, V3, V4, t = 0.0, t2, ps, pe, tpe, s;
                    T I7, I8, I9, I10, I11, d, Re;
                    int i;

                    x2 = xy_x * xy_x;
                    y2 = xy_y * xy_y;
                    V1 = 3. * xy_x * y2 - xy_x * x2;
                    V2 = xy_y * y2 - 3. * x2 * xy_y;
                    V3 = xy_x * (5. * y2 * y2 + x2 * (-10. * y2 + x2 ));
                    V4 = xy_y * (5. * x2 * x2 + y2 * (-10. * x2 + y2 ));
                    xy_x += - this->m_proj_parm.Ca * V1 - this->m_proj_parm.Cb * V2 + this->m_proj_parm.Cc * V3 + this->m_proj_parm.Cd * V4;
                    xy_y +=   this->m_proj_parm.Cb * V1 - this->m_proj_parm.Ca * V2 - this->m_proj_parm.Cd * V3 + this->m_proj_parm.Cc * V4;
                    ps = this->m_proj_parm.p0s + xy_y / this->m_proj_parm.kRg;
                    pe = ps + par.phi0 - this->m_proj_parm.p0s;

                    for ( i = 20; i; --i) {
                        V1 = this->m_proj_parm.A * log(tan(fourth_pi + .5 * pe));
                        tpe = par.e * sin(pe);
                        V2 = .5 * par.e * this->m_proj_parm.A * log((1. + tpe)/(1. - tpe));
                        t = ps - 2. * (atan(exp(V1 - V2 + this->m_proj_parm.C)) - fourth_pi);
                        pe += t;
                        if (fabs(t) < epsilon)
                            break;
                    }

                    t = par.e * sin(pe);
                    t = 1. - t * t;
                    Re = par.one_es / ( t * sqrt(t) );
                    t = tan(ps);
                    t2 = t * t;
                    s = this->m_proj_parm.kRg * this->m_proj_parm.kRg;
                    d = Re * par.k0 * this->m_proj_parm.kRg;
                    I7 = t / (2. * d);
                    I8 = t * (5. + 3. * t2) / (24. * d * s);
                    d = cos(ps) * this->m_proj_parm.kRg * this->m_proj_parm.A;
                    I9 = 1. / d;
                    d *= s;
                    I10 = (1. + 2. * t2) / (6. * d);
                    I11 = (5. + t2 * (28. + 24. * t2)) / (120. * d * s);
                    x2 = xy_x * xy_x;
                    lp_lat = pe + x2 * (-I7 + I8 * x2);
                    lp_lon = xy_x * (I9 + x2 * (-I10 + x2 * I11));
                }

                static inline std::string get_name()
                {
                    return "labrd_ellipsoid";
                }

            };

            // Laborde
            template <typename Params, typename Parameters, typename T>
            inline void setup_labrd(Params const& params, Parameters const& par, par_labrd<T>& proj_parm)
            {
                static const T fourth_pi = detail::fourth_pi<T>();

                T Az, sinp, R, N, t;

                Az = pj_get_param_r<T, srs::spar::azi>(params, "azi", srs::dpar::azi);
                sinp = sin(par.phi0);
                t = 1. - par.es * sinp * sinp;
                N = 1. / sqrt(t);
                R = par.one_es * N / t;
                proj_parm.kRg = par.k0 * sqrt( N * R );
                proj_parm.p0s = atan( sqrt(R / N) * tan(par.phi0) );
                proj_parm.A = sinp / sin(proj_parm.p0s);
                t = par.e * sinp;
                proj_parm.C = .5 * par.e * proj_parm.A * log((1. + t)/(1. - t)) +
                    - proj_parm.A * log( tan(fourth_pi + .5 * par.phi0))
                    + log( tan(fourth_pi + .5 * proj_parm.p0s));
                t = Az + Az;
                proj_parm.Ca = (1. - cos(t)) * ( proj_parm.Cb = 1. / (12. * proj_parm.kRg * proj_parm.kRg) );
                proj_parm.Cb *= sin(t);
                proj_parm.Cc = 3. * (proj_parm.Ca * proj_parm.Ca - proj_parm.Cb * proj_parm.Cb);
                proj_parm.Cd = 6. * proj_parm.Ca * proj_parm.Cb;
            }

    }} // namespace detail::labrd
    #endif // doxygen

    /*!
        \brief Laborde projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Spheroid
         - Special for Madagascar
        \par Projection parameters
         - no_rot: No rotation (boolean)
         - azi: Azimuth (or Gamma) (degrees)
        \par Example
        \image html ex_labrd.gif
    */
    template <typename T, typename Parameters>
    struct labrd_ellipsoid : public detail::labrd::base_labrd_ellipsoid<T, Parameters>
    {
        template <typename Params>
        inline labrd_ellipsoid(Params const& params, Parameters const& par)
        {
            detail::labrd::setup_labrd(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_labrd, labrd_ellipsoid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(labrd_entry, labrd_ellipsoid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(labrd_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(labrd, labrd_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_LABRD_HPP


/* labrd.hpp
oyr3mia0DnsjLjnXm+AdWHNsGGbOxYi7cbpvbECYKeejRJTYhNAqwZznxkDX114I9ppTp3u+hrfCs3JPZyGBAtT2pNr7hhnywckUi8Mz+8ROh4CtsyE+6TDVWBlOxfHLYq/HhYtzk7zRDguBydJYVProa/pvf2fvf4i6CXOylSCy8rNxaJCOtPNdqEmdcfNdR4yPAZKXg4cK1r6863bzsbyFHa9sWiAOCbv44I7nwBa/mhPDODLuoqZMLsNxG0zLsUM1WtgGqo+jIukVMukO556LkrbtPUF8UlV9X7L7kexAh1FfiKb3IU7MR+/XhLzl9L+zI/pQixKXB3rDjI6GCJ+99RT4PMdPUwGDT7shSMzD/BsEvz0y3WtJdQ4ijhcf1qK8E1qLI3CIlUOzmwRVsFhmSSuhMWiWQ4qkPuiHLyOxpJuejg6D7DL9Ke+0R5yqOitD4Qr0L9oooW3iK7JnYHzRIGuM2ETwY/Sv32s6tnllOX1DgFqLf9tEHTnRx66DiniKOBEoQRO9Z1d/1ahd0O65bhIA710ZkP1I8O6+c/4YtTMco6Zy7gNXrygtT0k4sqHtZqH2yT8Nx1NvtU87oMrB3UvvagiMoQRFKPh5k73VQIpfkdGTd3ewMB4/wCzKv+kdAsHM9MYxQMehHd2Q40EVjKNjFPyvbc/pD1rWr+HfiICLvRmpBry5KJgs1fUqIJcFYcKCN8x00dUq/D7mLZkSkT4qrBJHKPg4laQVpnFk+AtJGQUEfTXWVxDF7Ym3CXXFZYwoqoithvgMWV7difzlYS2FghswzXwuhUAdQoYr58uMxGmS/GPxSBgFBGk8WnVAji9SjR6UKv7YXToz3DRRWhSCqEzGhUDHfXs3CMXsckd/v+3sckI2xbPV9HKdMVHbx19cfmoNKbfdLjIA7xIk+9b/dEsg3f/+Ydy7k+iTAWGVVQDOSiUC4mUVAGjH9r9cWPrTJJn0V6X4Y8G/V/xn2bFO+ItRAl5xAMSyVAL+MquAeht3AtWDBPDJXCDUlw+cxUpxzbCHVqfjagat/f23k+ZQV0ZftwilWIgkmZvoRvtrZoiKXj08TvS/+HysnW/eXPKyRgB43GHOuPCUBnys9fI0hhV+3cgyVmL5piXRCw+poOyUiYEVRjd2/LHMBLo/NYy/qi5bYdegcNwPS/GPQmifKRud8FSn3QFcEpR6y+laEX8Lg85wplpEMffBKeE6V2VZlJHSpQMy2xhfjO8HfiCKv3+K2uYZ6mZUI10HlBw2tQMc6O2ViNHPi+/CBlsUhHJ93bKU3iAjK4nBDyGQQsE3e7UmgucJ8tkimcvP6dT6QZbPeit/gO711B39GqgoINjzqhnrBi4IkiTpu1eSLNcBfNmRsfweDJsVR4wxEq8GOt6S4Ukl5/c0G0ddRvsvH0+hRUckNoGmXEwJxflZSlt+48jTWoO/fGJOQrCmRBAnn/+2iK4K4TKOyQSxPB0R87EqN48FYDGdUKlcDBnfSnGFunTgbbwcuxrAo4+SUk1VcpM5mWCldD5eCraKYfmsznO4Iq4BoUzC4BKND0LJr6NHZuR1+e8uUXgHGqOQ/+qabUX8+dRvnPTiPqeAwO46o4xG8NZbDPRC0X9a9QU83zUM2rEY6DhdxxJfy3UK/88EGuZirwr0sYOHcdwQRPxIzBKfzo88qFsEkPHIiCUe7jZFAFcOAubDn3J8Am8CvwcyvswLFqJrO33hakTnFqNzKkaNX4enVAikYO8uCcHzMXY+fmxy5V63WQ/0I/m/eYAt8dPw7kFnzycg4/WqArv/ZDBSysiorh0rXWPfTqL5agA+9n1Z4lu3jFN3igE6/lRZUnvMK/5ljMAzShwcGBRgvlVZhhZnYpVb/soAtviUYq5I99ZT2utLK/l7d1SIgBQfiUS8uYcyk4aFPnPvGS25Qhn9mWxoDjRvQNykNpNoDHTe9CvNkHnUUMpCmlhYAen6VCLa/5LSZ10oLWML1E4FYCUi+++Af1dJwNwLXTDqy0K8o/zz7TTrP5xu+D7sn5aRhuRx4tOrUiqAnk1bjYyfgK7IKq/Psu0oPR3Qa5YKljYbJwUZRzix7G7AKquGordV9nfeW6g17OjdaRTVrsX8xH452xIquu2974IUvOMkK+QkpT/GABnfw1rm73267/Qny6wEqNDbNNoFfGwJQjTmFZqVAYfR2Cw1XaRjqYPJNstT8992qh2LpxfKe0apKM5pQGeUAWQRWCPaHam5/OuNb6UUbkH4s4G8elrXVc8L82qrYg8ywU6R5tdmV/zuawspbT/Kws0C4K+BfpN0zA8dKffPtJeJMfB4KjF0GERlPJ6uKSBw+7mphBQf4oBQnIs3Q8Hv46gBdWww9ek/k1Dz/z5TYZn8s657CRgyXHqfj9/a/ENWrPYbP7HsgMYx4rxmdAKWIcO7O8tq3FV+E07uUes0pcHoaI0ddSF7yPg130vmLeneaoZ1shdFJuFonqbmfaWHkR8dH0+oFhsTdcTQrK2T64pNvXuHqjpiahY8UMDmqRj008CViosAQ2VwdYw2hWX9eUW9LB5kMYtz60VgW4+onZYplUUWnLpkUE2L3l4cfuoK5l2y9Xa4s6RXWciP+oe6NFd8K9hwAkzfVlywue2LA2/RJTG7zU8KqGmiGLKwDd/TETjqLvrQUDePz+LHnjpW56YPZgUd1SP4ZM42In6jN3lk5moxF/GQZLfjjAPMtgFt5nIM/d65JekUnGBD6xmzxqN6dKmTw+tKrQ12CAG5eWQr9+m7Wq2RPt+ByrW7wZI5pE5puUq929reVN3eHUKYdjUsynVrX3C/7e1bkOOr4TlMAYIzmUXCTY85Pu6SGAyo9v6hWB7V72URQmbJLMq1l7/wrGtF8JDL6TEMQ7Nlxy7cfLHwRUkdK16wtgdQgKUrQDI6MERynEFHv12abwWsJGv0hBgEMvrnqU91V0Nfn7DTRoQpMEz8sC2ilCO1PKgmeeluFDFLMX2qWzlbox1MFH3QewDDfLdP0v4PHqM2NIZ4iq7lHt14+D7pYx2pGbMHMAn61KWqbdagL4P1FlZPtemte0A5aCbkOfMQQZtviX8N3wo3AkyyA4mfdCOGSBlzHeHp2+9ArVnfz5IWtbcalpaGsv+QBI1mmNTZARw2onTj6lN+j0Sl/x/GDOdmjLBxqmRLqLBF5wvj5NGgeaD8YsWwaahTm/5UApCPRHJOwARRVJSALQin2ZmguUgzx3aEY/VKsrpFJS3v7EnzVzMRdTrX61wUTfeFZQJr4QYeYLqqlnDLCiE4fC0QhuG69d+e5jvIQAuRhZpYLVtb4Qgb37RkN0Azg5haaZ4/RswLmpa7ww8YBISxMcEE9xwYg8nJr9FRYru2/sTSIGozFk/NLHJdmY4SN0JKxgEM9Gv5fu8DXNPHLRP96qzGqwkzEo59TMgzKINxBP1zQi3KrlSf29vJoHRqKksPmyUMeyt+rUQVlwpP9JQlKtQKLbM4j8eJ05unExTdtCR6NAPf8Grkzbtsh9iAo3Nb+qUkaJKJnIu/8rPJJzt1ya+LU9SykBK6z55eFzVzJ5+hkM7RJefmAtBqfW5tRi5VdJ+fFb0FyPc5dXvhFNgI8Alevzq/H7bo/UfzEMZ8NHvjmSDUXElhNANOKguWNeov2Kx1/WNtejgl1W9ABPNDN1Wsdjc+/aqOadwgQ11W71AM+qt013ICdnthPhN974lM9J8s0lFfCBViVvm2RUs45iK4n025vQjENasBQSxlIzsPfDJ5AXWqvHyIn02ykfVV4EOtP0LeLglijuHwFMPuZWBDO9QoZrIqSoXMVawCVwsUG4iO/CiUkZ3MlezfakVjg92t49oKrOfaI3wRzR3nJgjfvEphmYJxNxluyz0fv/vzADZOktnF9VZAXhyXnAY6MVgMXV83ID8bQbmUHMFGNlJ1Vao1oD70hw2bTqTvJ9l6CaSDh9yg/SQx74W4KYEVr+r4KTYdswrnlxEbqjQHp2kDJ+H7ES/bHOqyUX4+HdO0c2V5WluKHoYJHjqslKEVgnVHjQLVC6rlnd7u9sAXkc+6X/uuZciUwMwAEvspOFI+uxpNmhOh55kKFgRwb73mAD9tGe+nPt6uCpXRPF8m13SGlUxKbkF1B2vFoPPMUlqWTh8DaXf1XrPzOrLfkZOlTh9Qakw0ED76gnmt26U/eGN+ESD0OwQiGwt7kCBliX+CQ545p7uHfA8zAZ9sgQjQgWLjOfY4tHaGa5HU3QRzpzOtw9JuB+KqF+XkLOhfBMJpPy51g+ltcEp0wEbbRnVq7Z76BOV7NhNbEklFY+O/xpU3OmoulO5P1kyXVkYm+1LgJm2T2yKCLUGd0CeIpPIihiwFdxYPiNCr1Z/GoWBIsdTbuiIMh3WXR/0u9a2R7WjShlHB0raH7vWZRn2SG/YOM0l59IbmidaQfBAoEKnYgDWQtzCICEPbTCuk5g59nytue+vf/S4Ygt4hy5nmpo3K3V0SzgZH/FLiWqC++KuxGRsOfppzuFK7qCZvBorSIlwaN5oGlNSVGtZbRUOnwxXoRk8dMDzAx5cLpUfr1D+6G6/+//+tnSxjYlqCkb6IdLu8QBgmlVO9ASKTvSF0kt8aQhZ8mlgQsRp9CXmvhN1ICG9gP34LeqziWee7Wa+Dxnf+bqmszVFP4TDJUpBcglLy/QkfgRkwKNch0M2fAEN/0uOqbe46iSnJ/KbHG89JdVbXq+bHrKZnTfcsu6W419nbNtxmmVWdokduSc5vZVFWCbPCaKuC8KmLO2jCjh3K1iHfJVk9LtJzsDWMrTjygF8pUqsTQhl2g7d6PkwHJQCEQrYiod3aNT0CakPURvSCQd9ZDjxWXeGC0BLY1rpWt0DjruwB1GZTDH5KAL8guMXkdFU1XTKLsKYI6/rTSljdk0PcOA1i3+brqpu/tqVQ0S9fsG+OAiSEAEPxqjIZlPGQZ9ZJiizowZXYr8WcFMG4Y5Hw9/TcB7bpDOHyccfQ5thfaHUDjI1bOFS4394uYX/GyiI1gaCbW1HChGLROR56KZaSqzB4AZTA3Qez2m2rxfJr5QXM/04CrLc50N4q7Yjqyvj3I7Lh4k2ynp7myIu8t3tFKQse+d8FzjV4wrI1aKSGSAQgCenukR1sUkVhnyle0zs1tf34c6tFeB1tqpiJGLs8OTleYL2dshC7Rfsh8/2vbb+RdENcDc+JFewVdd8nvGkBm+mTqEiYsccQFqoL8+sng98TeI73MPBrg5liAr+2oySbRDNnRlR8Ys93ck+SSKIYXDfCh/l3lVJb+NxihPI0qylX3VvsOVwH5fMOcTxceqgxamkQKedpqnW8nBg0gkXXQw0v/6Fnv/7yBvYC8hi4+OfrnGVKT13UcqxpsfkwmvPRTrqdZAORmPfw4/WS+0KHtqOEGW/cOPP9QScEBF6NcVekCkJaV2Kq8MXBHEOWsUP4Wrg/z7dyg1TGrGWDWdOCnmwjgXvpFu+wJuI4JawMDW0cD4tJk4NAlkXBdfhGnXsfco9CF1tjamjo89yrxAlgkqxn9DjjEh+HcTciXW40tkPm+sUoW5PY6ojaPpcfaNSUtOlEYaphjhkBll+ig08y7OgtZCNrm1LX888KMYBqJ0teaLztrSlUBLuKnq2Lqv6LVmYiEJdzJjORTBkUSqSIq1vxB2mDmGZ7Voaz7EL5naukijuNL2ZMmx3loc8uAl2yZFhDPhTSIUP7+lt1TY8Mk3BRD/VitpGHVUa98J7EYV8KC6CYXRZD8dsLMZj4wCYEn2KvoD4n0T20olvTpY1fWWcjdZSooA6SmIqhXclmYo3ioaEHlMd6/V3vs8v45cIAyc85dcTTIbKyR4hKQmkfCzmR31dr0+TjAkvDYvODJG5J4nOp4kXEsaQ5l6yE7QVzDI2KuQDIOheJGQrDQTkxBrDhgClRDUwWJzec+u4N/vWZfwydsQRI9CHLO/gho+RUfEMmdD9SMeLa1vXhl+0FxqF/yuM0/bRBg5UHocVU13Lil0BC9Fm8SonQW474aZiJ4PLWUC7HOsteW0jJnSA240gY4aHJVos/l4kEvtVsogeK7MWZ52sGdLoHUoYEyPxg7j4dkmNLPYhg/Om5Omu7E3VXo+vl4UkcxYmTYuJUSsMeNXK07eUL8rYabb1dQIxhOqgxcy+omh0q64snX0nIredWzyFBWvPpEnhWUlGeKCkf41JGXOjqimLxk3L7aNivwJQWNUq+aGuf53tcLFzfrZLJO94XMy+hBFnzDAvQlWj4HebK24k7YeHI7gWF8wRf1DrniJBh3/MrhmUtSJDvrivD/mD+Wb2AnIxJUCxtgAqN4iZpg76GNGi5BJ+tB/9ZRYFsiK2o3XZmr/qKSGwnPw+6dPbT16z3SPaX4jLHnjh7i0sEz3L52LpFKW7vVH3lxmOr+0u+9kGxrVaKXN1S8TKdCSvHW/aAvkyh0Z8ZUIKz7PB0xPdHtuDxtwUNwoiYQGrIzAAsrkOTyoMPe3AxMrJkqg67v6ZcYo+TonUrJeta+9ChlzE2dfi/xutX3saOwtaq11+Y4HnPRa8qnssfVX2BdYqfZfiUKmATVXUHQfNQQ/UOP05yKbxvBQ3tnc8oWoovRetFEFdDptvSmR3edt4ohbxE/p+8YheHzNaoFE9Oz240jDLOAifaGAyPNh8hYtnHv8sWYrt427MZ4pGDY9KC0mNNnjk52F3RShNjiPkNWJWZH4CrBmj2YDv+Qy9MxK4W4si+wH825MbkT5dofkBe2artLAhsbxw3maNE+tVMDFU8y3B5Src9KYuPAtjGM1ANf9j2SFM0S+1VFYqeLvaIYkhb/eK0HENmEQZARfQMmCfRofhxRXn0pMS99W9H0oeVV/rcyzK1C9u+Y1rO0R1ntNhLxNgWQ+PwnGixCpx6u3Bg9iSFyDn6BJSDKe/W81TM54v7QbuePPXwrtKTxjeG7gaMQcUkepQHOylygG87Kc7uxhXhBs+LufsTgvH2ZU2LJ8Mbsxvh5XKOrnES1oRJyeVmCR2iJTGcrs9ESakmgb8yQoMdB1YQhGVA5rNsBNHFZGgFRtiB3GbZ5fiXhx1ixYsRwWe2BbmdGvjYiLGAH+xc+yIjbxYmrBJv8/5hpV0lp3EWEKZWbw+iGaiVZZ2jxrneWwhZ8ZvB4ESG6h7UvYL/4jtptO0RC6hoGet8M0zgWGWwYw6E7UFRy1TnB/bkyAA4gcayjWMkgBhGstVzgqNHQHMDkNiz0saI0VAo4YgQUXwZ856qyZp5z4I0ts+yOW+den8gYuY+tl6CHPvv/ZNwRPtWb6w9omBD7gP9ftf3h49uimfluJx8Z1GU4lF3Md98TkGm4ZT7/zQSjv+8BV/8fuvGwFp+55AbqFc3u2wnuf00oOPw1rWJ389rPmHJ1soYTyZkZ9QIq/NYAQNwZi1qLTstjzO6VMSMzArl7tppBuhOcOc/m16fmdaW7kzlngN/ZksfAncS5a2KFKsMXoXp1IEtYeIpqbYD+58pdesXYJy0iTM8qsyHC5/XZF5S3XACTeTy2uueolmc8t4PDvZH1mzPa/reMe9x/+mmFecFR+yWerpuhgPimGcZOWtu3+Mrmo6hVf2FXToVxN6+X56b2lKN1D1pJYLe
*/