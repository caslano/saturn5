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

#ifndef BOOST_GEOMETRY_PROJECTIONS_PUTP2_HPP
#define BOOST_GEOMETRY_PROJECTIONS_PUTP2_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/impl/aasincos.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace putp2
    {

            static const double C_x = 1.89490;
            static const double C_y = 1.71848;
            static const double C_p = 0.6141848493043784;
            static const double epsilon = 1e-10;
            static const int n_iter = 10;
            //static const double third_pi = 1.0471975511965977;

            template <typename T, typename Parameters>
            struct base_putp2_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T third_pi = detail::third_pi<T>();

                    T p, c, s, V;
                    int i;

                    p = C_p * sin(lp_lat);
                    s = lp_lat * lp_lat;
                    lp_lat *= 0.615709 + s * ( 0.00909953 + s * 0.0046292 );
                    for (i = n_iter; i ; --i) {
                        c = cos(lp_lat);
                        s = sin(lp_lat);
                        lp_lat -= V = (lp_lat + s * (c - 1.) - p) /
                            (1. + c * (c - 1.) - s * s);
                        if (fabs(V) < epsilon)
                            break;
                    }
                    if (!i)
                        lp_lat = lp_lat < 0 ? - third_pi : third_pi;
                    xy_x = C_x * lp_lon * (cos(lp_lat) - 0.5);
                    xy_y = C_y * sin(lp_lat);
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    T c;

                    lp_lat = aasin(xy_y / C_y);
                    lp_lon = xy_x / (C_x * ((c = cos(lp_lat)) - 0.5));
                    lp_lat = aasin((lp_lat + sin(lp_lat) * (c - 1.)) / C_p);
                }

                static inline std::string get_name()
                {
                    return "putp2_spheroid";
                }

            };

            // Putnins P2
            template <typename Parameters>
            inline void setup_putp2(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::putp2
    #endif // doxygen

    /*!
        \brief Putnins P2 projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_putp2.gif
    */
    template <typename T, typename Parameters>
    struct putp2_spheroid : public detail::putp2::base_putp2_spheroid<T, Parameters>
    {
        template <typename Params>
        inline putp2_spheroid(Params const& , Parameters & par)
        {
            detail::putp2::setup_putp2(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_putp2, putp2_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(putp2_entry, putp2_spheroid)

        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(putp2_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(putp2, putp2_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_PUTP2_HPP


/* putp2.hpp
QyNpPq72l3P+cphYM0ag7tvb3O+LwYMdxbn5tLNfE48F+qQy+CsVLmnJ+rbqfwRH5irVqk+2CLJoJWjxldRjlK9wDyaUCMoCsVXzzFDVqsmKdUVNZZRlmh5/K0/IFUgryRgp1NAVx5i7fvvVTS1Kdaa8/rJcxHI4dnrmGOEGp6Ke+W/GKmM92WlUqZr7sM15skLB89YlbyKzXPGy9Scfc6ZamddsinxK2XGGToLApdeEFx+QbwhpeUOWLTCpNAEzVyLWQ1mpzOmO3WlkoQUzt4XotqhA8/DAagNfUUfBY91pKOlPUEpSKaMFP1DB4+5/Vy0PD8bdRxb6EBShJfnLaXR5PL9x71tdhJTWk+eqYtVm8y9V6j9HaeC416YZztLPnangH54r73sJOyUbFKJzK+8Xvj51SvZFZPBJSEhdm3MmJ1Rc1xknh//+9ee12jXGZLKjSVRmW635/gH054w/8/NQ2z/l+Yb9M+BEiOLVYH7Mc+3NmS7IIMtz+rohLrErbXZjqbDMi9xBk+/PokpeP0hN2nfKyovcLxuS1vezOg97mGtMNSQghIVqlEXhI1zg/r7x5SgNLYq+JoD1fy9SE91brRrB3vhexkIThyEAQXT60nX3ouPZjlR5nKH8dd6Dv9bjBto7vfJThtDwW0OqO1AgqsM9hQ4+DQeUEzBLvEqVDucfRQmkYVLCihw5tKpjM1zp04fpRMJBrEe76FONYFpHZmDAswsXXelHDRZAbmnlDfPIcJ9wY/tTDbPz7FLAs3qN5lJA0j/w6Ibl1k3zUGIIoHi4ehK1p+aE3Ak9CRdgRaiNpNl8LLg2vzyBC3jFv4izbI8oylOguH388c6Jfed33jeTokdq9042VMsMfzvMJ+LzJY/LyPeVdzVPRFcI4XwW/lawb6uHdCj8GuFWa9PX2B1qGX2PqI6NRHjDkDg9wHUelq/hog7HDja6OWuu9Kvjp9B6/C2xQwy6wQ3LXXddrLUBtZ8xZONIHu4qH/HfZghXGKhL4SBCPETHO3FSieu9q9M9zBVHvqvR/RuPh6QnO1LmoskvTkUk4o12WJc1w0+zQJrXUxsseZiPoPH/pfT2QiaO8zsxaDRErrwpzcIlvrDpn9WBDFdz0A3v4n5s+MrcDeOnb/NC1AoQ5IeNEyd5yBHVn3qNJ3C4u6jqP4UF3uzPr1735j7v2bahxfWbzMP5Vt4X5ExGpRyUcdB7Bo4jBg8J5DFevhyL6L4rRyj2Yudy5ewdGxO1WsSJ9oYV8zAbrl0eXdaKKrl4k0iQTLMyf4UF1+p2NWyYnfmP3t0Yl0g27I+gWsPsNmICv1HbttpVxjHH5fi3Or0ZpM2wtz+jGsfDAu1dqyZ8zHO9odDUf2ugXnN/edxbBl4D2jEpd4wIrnQIg0cL4kbjcZ3r8LOfOx0+rl1w8+65qWVSBcwBbK1JuMO3e4HWt57RukwYnH969zk3V9j1/46nuvjfe8yPHw5XxHT1FfnhmcMI4MXkfupE8L2FtLZyPXqllVRv50wvO79x6XyMmJ8n9q55AcD7i4mS1vofj+rqpXszWjdAwSfx6EzHQrfoNqT7P3UoK0hjXU9blj04Ckdbp6bL2O9rjc/PFrhozxaKBhezM10reZFbH5sbOVMbfEllRCOCJ1F4HPthVvqmnVYoVeAcrkYdLntphhpZ4trgnWss+ohDeKTgbGypd1DGmJ1i9n/yKsjRe8i0lo7mo72qHw93t3e1zT551PcFkJwCsM9xVilZ2sw9HG59LlF1RQ0fh00b0cIWdiO/Vf3zqMdjW68XvzT98edcsvAkqRXwDapyJWn6hUdezkjpOuDz81+g0AJI/xcy8Bzw3ZmP81qedOZnTV7YUsyQA+/mrBGD7XYkowxy7+cT7AHbxRtTPQvrBdAf8suhBsDt+//1a/ACKA66w56KDX0Dq6kssAeLkV8co5GQ3a+vXKjnw4v4tsZ5nf0Fc6Ivf5CH+HAMNMxI/XBDjjSdUuWkdBuxRUEhgk/KDzUqWSiRX1ewwAiEFPULK1mAmqaIKUdIRobksCIwk5h/fHs67t7yvVZw/5ez4Oi83OPd+nb5fOn3dtn65vvWfdy1/4HfOqkhc9f9ajz2TJG08TXJJNki2TrZPtk52V35Bj4HjpuEjnZH11ycR6JdAijBk3aQOxv6aXDnC/xx+HY/cGO8jkKLxOl6KQRVI5H5m7Q63TX1upCByAThOs8D+oH95Awm9UiLjmnHmgKo/2a9ep2w85vOubY1+50YWF3y49mrd37HcxSg573t6cFqQKRf0Eo6XUjy5Zlumh1gz3H7I2RwBwnmsPNn4vVIVH7vsCISg3H5Y+bTwywNygtVr87ZpIRawweOkNCruKD/GVR9UQRKMA72xwjoh1Baqg+z7+e0kPzf2laIxIPOX7Wpfvv2U+4jpKXPPw3y+OBcNX61D9qDYoB0NkbvvikUO+dMLR/byBJSr3Hsl7RUOzfyfiYfw3M79nB3wNEwU+DITnrvl3ff05fnmtQD4+65I8pxGN5YZlHYn8EE+eagqMynC5zqoyd3BDPQyA4FyaQBdJsGxOVgUxzN3la8H9o/aJtPNgRZ0AHW1tWePYtR8+BAvUgaDW6vyBshRvo68J6lxD9j8jhrpj+9dmw2qd7gp18SKHUGJLJv6pePEPbx5PNBCmEf/Ds+hZpoYBECYUg0+EfM4UpdDqPmtSfNTCHMTvvmPYRUnLAX0V1uuMu3f6yabyV/nVXi/bH8hKYYtNhdA7zvPCGKBuM35/5ISHGsZpqbv3zf19xGlKIn5TjA5UNrk0iMspb3re+5e4WCI8L/tSOuQoT5RQyJXD1YhAPmSRa3KpSxb20Eh2Cz4WGYfwIZ+cqGWt5DaHYR3hbyAcpX4OQ+EF1oxyZYx0fgy1raizcRn0F5bcGnqBJ3zOPi9ZKaNQ+CGrcSgGHjMxB0WiRYswa7ZjGSRo+NirnNLJc6PkuV2InIkFRx4wyjM/t7rR37m94zhJDiihVH5W/pAe9EjcmZit9rmS0FUOdr/DqzR2vtS/w394qBeZUaB7hnv6XASbhmZyqO2qcbsICbwk615ThC1quweVPeuvTfm/lhxYTv5QVEMbdN9MmDy01cf6d6f4ya2SVO/+/ydHSwDaoIWoflgPcU36zhkWZO6PDs5wUI9GVcD4WvtmLaPRsqS91aG179do6qDU2U+P59UaQiWBWtvD72LHAG8S14O9zl6RgIUqojiM0NfTOJHwUJ3scffZ8u2PGGWYJmO3wJVvX7wBnXM5D3IxPd6htlJN2lLCLY/fDidxfWgvnNyOgi8Lu8FlUoId8egmSWCEZfxAv9yuK7PawZ9tGTHJtenLm6ekAeQYaPvpaAH5m/djpoic1TrF0MKMYj7ineLg4U57GrqOue9HTJHQcQJskmKyarJGsk6yQbJO8/T9a7q/n5JR7oo9Arq73DJTm7GCzCOK3CqHYEyKxg3SMFB+JfLTXp79oi/tvqZvheGvQBvYmZ8MWJG+aOG8aJh2McNGB/cD9acg+02r2klVJUpEdnP7y5VxHfV5qoH7Ul4RrT/o1tU1E79/vbeelvgvPOsxrebeXemtZ6x/dULzmPOE/NMBZ42bM2Dea8PPuAqpxXRRYq83sklMake5TGHGdrNPbZGjeu7Fp73UiEa1a0ya+wRtJEVZ0UfpwaVD2lGN5yfr9iXCP8yloJekNftCIFqMIxZ83QNQK7y9iEdOj2FWmHFBdz2OibMmvWy9dr1ms6dgcZH/N/mZi8hP0/xR8ILy+2Yu9Sl8wAQSLHoAOfY59j3VHR6caweYce232Z/6eW1qcbxTf3r3QjeWrPKonboBfcJ8/eJ+Hjzd/ubFRdrdP3cbL3w7z392GyUXnDR92IhRO6kfdd3EJCvqf3mEI7oBSOaz7is2y2aHM5D/sZ55D+2YaX9siDHjnCoBORLiiGkt4lLyk7kcnf4RErHAq5AmcLV6HZ6C8rBaGAjjR3RvFZXeYF4i+aRY91LRlLdkaDd8jBVnOCpafrxAG85h1V1lJrCDRbUG72KEwIB/JdJU7mhysJd9rK29UovwvXv1rFIbqzBZ57wgE4rbu/HEEEesQ8qiS9tnugtdatBqkVdbuqlxIJqbiYsHOI996QmPebmZuH8cLcu7xTGrzEMaVrvzu+/F2z9SPhdYnIANCPuwv2Jr7XpO0e2M+nRX97l8nfEqJp3Fo1t/GudyPREIT3pZvdw7hzXgi35PLYZhjPSr1rgh3j89GdyoI5cF4YjVOM8qxbFCWGQPQEatnaeb3O3VpF1oS5oE16NhYxLoSuHy+i0TGqPeDiOK8YVq1qxwusqi8WtqI8fY35Jv9/d0jnxb0Uhq2QPP8FUhrX8XGTwu6l6Qc/QySu8GU2zLuTXSBV1yg/Q9bwzeS3V/iAMvtUAouQhm0XLrZngoxxSorcOBZ6YIsb8bDEwtHVStM9Hnmr8kJJqVHXbP/VW1A2C9qk+Y1uacbrfc77XV4C6C4Lf3FyfQrr0V+/pnqhp2RLK0iwfP63Cr/EIY+KQUkTqy0e+/qX9qtm7X7DWtiFxMGwZkLLnuB1v74YDu2mDblYpReKPjQI0Pm3gcq2TBhd2rlCb8g4zFjzoH2+WG67VIebFgvAzMDQ7abcjc8kuqLwQFLw68w7wlfCHRwHB98daOuft66BQzcuSp5Ds7GZI4kPgsNxiQ70lp8dSC4C9V7e9EDqluFBQ2t8hprAcOk47rzDlp3BXY2vHkPZodpoWCFC07vW8F26Txj0ndHJl7D6R8Ii2hAGWNr0gx/R/fp2wfJBuvJSdVyLvzRjHssJXpIWRkJb8ivfYU/Y/AzQfOebTE6oQ+wLmRvpcU41G88QTSQptnDlqW4+EMnnSdDE/xERt/IZtq2iKcevpfxxOekAkHFR0H8jliomF5jPIeq/fO+HHDQz+66fFrAKL/nasTCvOkKGFS3JG/RMQvjlh4fsb5pfI8uaP7CiH+e/5ffXyz3diIW/peLE+clG1XSi4M7uQwgEi2pZdpH85He4bcLAS5Q3DBLFHEQz7YRDk0M+luDj9yKA8gTsPeIztcf3NZKEwCujvAQ0oHmQ4/yyi0aVWXrktDHV4eOEWS3B4VuqV3GE+s7hLeEUjJmha/fFC3ci5nI81vVEkOIEOsirz7qN8Dt32usV0WYS32I+HNSqSFdTK7pgPRQq7vYoaUIhr5Pq8y+pxojBkbDnbb78H4tTpV1C3AmyMWbg1mTgCbLcrcXKdQhByWk4IVgyL37rz9QZhX1GtpCkHgg2eePlF/ynbinB57CIP9LOa61nTc8erctvB/dFRGe64aasG6EorWOU+u+vPkSA4eUNhgJUCacklsLlSQ8XXxNzp6RddGtMTJvkQTimpZJpNh8vahaBUgu2BDU7apitD38ntYuDMRnXhOmUA8/hxIGR3S6FG6aXfmAy1Ggp3wfCr2WGMYqkejl2cb+AWGm4a8KTqKKgU0OqjKsTyGnIu+ID5TmXBiH02BC4jqTTL5a0VH9+M4VeKowkngbmWjJQIf6it8TJF4PZykQNK0wQk1CTQP1qvCRnalFCDsFhuXdDoROCRLlgNDfFiy7mBuirimYZo3QYc0A4W4yAK4zkwzQqOQxKNT/ibbA3dkCW/HMCL9TugCIdJbabC5gH3Hobue0+WOCiTk/QcGtYYoWO7ov2zEUVX4qB+ONULMUVGqLURAt+jmPQ3g5u/o1sHcEiRuIY//f+t+llWIQhoPF1EJO8CraCx491PmsYEaVSm2DZEDcwXhndvtOoo//AKIjh4NdXo78ADQMX96JBpIJTGD1hvzoopmleI7YZOykahqB4E1dNH9poBJF7GtY0qWn4R4sf4yFaPAlyo8E2GN+HN09exHZuEhi0pn5xafEQUvEmE6QITyGj/nztkw1F1RIIUm8Q0nHXVU6KFmxz/50XG3TJvC4ItVfp8RaCA2kP4wZVxkJQXrLn/I2iPaec1ipT1sQEEUqmeIlJFhVKrHAvbbSQPToqEKYATownfigggSgivHCre17zhexfmtW3237A/BW6bk6QydpP1/PiZAw1mjIhcoxYc83wsd9mTOxrAiykv9pfN16Ix2GF6xyR50Y9aNoJdbuIdcRyzm9EEBVNw+vjmP+JBVM5mbzBSRqmCS9rZa8J7oZhRuhm0C3sNVPiwa0btxp+HZOqA9DAHy8iIsShpSl7WallKeOh5w9qSTxxgQqaxE0r11Gd+dfHcZL1FznH4EUwC6MmAzCjlbvjacoObfzS9wJUoqQL0eMoXmkhNs6B2gi4+PShAnpeDgxInQ5mGwNOMJChh7Vquh9DMfoGT327q7tidnLh2LkXLTr4xPliYQ9l3vT5IZkymGvv2U58awKJLQDE3yma8cGib2KuB6QchEsJ4VUeL9TnZGHp5GSW4+qaQ5Wdp3uGe8XNDNzKjCgiifT5mTAWq4eBfcobw/UkvwY+EE9UlcuSnJTy17Hi49GJiUm6LA6MOX8WWD6gxBxKSAj/g/vxby/o4j6ZJ5OOqWHQGFHOhRZ+jSp9jBx7eURoir0z/01JrQ6p+rs7a4e/g71bFx9XIkHSryjgQFOhDpXg1ovfl2U2zv6YX/HP3ISnCE+j3Psib0+xBa/k5z+6IXASac/5KpAe3ITyTDr+HjOIG6l9fzKD9Jh8comcJg0jaFpMYF/AiZg9Zw5ld/T8uiLcF9kE00POp54dBmNYqxmdqjUTcrv7ImYnFI3SHIg9AxsRDmtLwRXtrLRacGIZXHYr+VT2EbQa0hLq9KtOiJM/s7ihuPBRnFmwoT8+Cp/k37yqDCvHSYs6O/uPU8MCtAsb46eCTAc2PSacOqLakPkxsSBUt6l/9TovRZfoBsj8FbA6uv5S9JWNlzAi6A4SiNYUb/SmbujVZczGLikldRMrmhUTvyl/xHJo+yrQTVLO6Dc003CnmLmqZOLMb+iMFy+WX8iZ3II3shkTn5Ie+pqxW2YTjp6Y0n9lVvCcV1XGVf0nvrmPUxUn2rGp0AtYDwkiNpZMEf+5lJWsIyWVxQ8N2nIfgxW6ckdae+N1zeVu19CFoiJfz5FDfriKR2/FtK8LaX3w24VVFpmwMq0QoSBXUuIt2HB5Vo642IWmiIsEJH6ZPZn8wvbum0r4x4ZpNyL+qdI29k3tJ3NrAuRjhdcahSgNavrHGkaZF07hGa3EEplZUVBkxGB0gxXMbgaUNIToeI6ygJ6GeNZ2loMZ7eCPVExP5Ha2jt3MvcEFSi9aM4uzn55FuIqd+5lk7lHEnGXqAbJWKfMrOQojIQI29j+6dRa/QXf8oJczSG3cm4uiRcXMQJ8W2zPLZyoQ18P4Qb6wQYKGwt2cE+1CCiWu/i0NWkYibMoxVC7LltaBB0LlymviwA6yx4uiJzXYRanHi/DlrJzfQADV5zF5UAMt7zz1i4mU8JEytvme+3Il0xSka3H3Ymg7hg/jz/So+yUsc5UgSPXFxTE6mY2xL28n3/RLqAvlJBHwZsf9/MQY82SkR2tO6iG/bV4y1TqJIMBRYXE3KXQ1+x0t4USJbTao6FcU4MiqmlJ3KcRCic3WqwxjPCPKsuYkk//gz5SXDIrVTfadiHJUCmtxnnfQCjnAlChkxj6N/TA3ZY5JSIFN
*/