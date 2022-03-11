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

#ifndef BOOST_GEOMETRY_PROJECTIONS_WINK1_HPP
#define BOOST_GEOMETRY_PROJECTIONS_WINK1_HPP

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
    namespace detail { namespace wink1
    {

            template <typename T>
            struct par_wink1
            {
                T    cosphi1;
            };

            template <typename T, typename Parameters>
            struct base_wink1_spheroid
            {
                par_wink1<T> m_proj_parm;

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    xy_x = .5 * lp_lon * (this->m_proj_parm.cosphi1 + cos(lp_lat));
                    xy_y = lp_lat;
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    lp_lat = xy_y;
                    lp_lon = 2. * xy_x / (this->m_proj_parm.cosphi1 + cos(lp_lat));
                }

                static inline std::string get_name()
                {
                    return "wink1_spheroid";
                }

            };

            // Winkel I
            template <typename Params, typename Parameters, typename T>
            inline void setup_wink1(Params const& params, Parameters& par, par_wink1<T>& proj_parm)
            {
                proj_parm.cosphi1 = cos(pj_get_param_r<T, srs::spar::lat_ts>(params, "lat_ts", srs::dpar::lat_ts));
                par.es = 0.;
            }

    }} // namespace detail::wink1
    #endif // doxygen

    /*!
        \brief Winkel I projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Projection parameters
         - lat_ts: Latitude of true scale (degrees)
        \par Example
        \image html ex_wink1.gif
    */
    template <typename T, typename Parameters>
    struct wink1_spheroid : public detail::wink1::base_wink1_spheroid<T, Parameters>
    {
        template <typename Params>
        inline wink1_spheroid(Params const& params, Parameters & par)
        {
            detail::wink1::setup_wink1(params, par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_wink1, wink1_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(wink1_entry, wink1_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(wink1_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(wink1, wink1_entry)
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_WINK1_HPP


/* wink1.hpp
46EsW3+MDi8FzsyR8x4FET2UIMWQgBBLOK6WE6Zjrtut/gQNUYA/GbSPOf5anmUOPhH9OZDccniXxcTk8J305ro7EEvtgpyYMwmrgd0oh1zfmLmMAbolKqVK3YZIa9k/+lSfjZ5xt2A5R82w06JrJc0lvUf4g+lkKGNPYzyL4CeS1tnkT1DBflIG65aTagTyVxvkzdcOiVG8ur2Z4xpFiYGNtgjRhKeiB9Eo2IpNIh351Beorp2oHQ7y43Tv+j2k6/MEooQC1pTux07x80GPGrZtv8XTbxTkaXUP9n+VL6nidEVgCmHIorMyeyQvRMji7b37il+aR3Ns7hGARkpGSQUAsf3zf30AIM8JBKiIhCiMKkyMvu2/hjNDI0MKiWtLeRGxCnmJj4E94g9AAOB0//0LOJggIDg49i/hYP8AEZiz9wGBOP4EBv8GfxBw4ec3d7/5p1Nv8n8GN2P+/sMgMPgvCY4CA/8KRHZ+AujD5Bd/kn/edrlIAAgkDrDxBx8JYeIgIL9Pk/7g6zUX/s/d8C7Xlhn6l3XNoe19OPxySdIcbAIL8O5HVZjVr79+2PtIXfiT1aj9f+LSAcr6mVwMPXLb94TojbqjVyoYp7fxKUdS6UPtOB42Lz6/4iRS5ZCN23yghYbyCfe8Gx/mTRSFG+ufyOIvmo/D635wfrh6/vej0iHBgvDyOoLLvzJDejzszfgi/f2Yd/q6mRXz/MtshrQyB71dLAqMD9pHTNgm70KrPTnDpr41/DVHF1vDe2Jhe/h7BU1+ZfuMgvJehCwM69F2/JuZY/P6Ql3HX637Hq2bJ3Z3zUlLrx2/GXffuu4mtM6P8ldhvFpvPSgWcsKid2UWvtNtJYuYfSg3t79iz0xsGVF4cUbCrtzLrrozSwBNRp1NveH5N17+xO2ZtNkf4oH9wFc5HKvfylv3ipiweqMra/3I1i/tYXpP6Y7ouf8eD3fmmlSfNR0oZtcuSPqb/SOadn6MfWk7LptuAuPwZNE3FGHmYsv7zExhJ3exBkxDr/dORkO3Llx9Yq1iz2l/npnds3EypZkZ7dR/feGo0ML2Cj0AjHN3+aHc/q6ffGZIcC2gsV3c49waZj/HJk0XE3f/e5gjpz/SUiQhmrrI6gcHnUkvwGfAbm21Bt6hJsMeUckOY1sp7d9lPYAedWy/rXnEEO/eGxbkt7X0it8IyNg9ez4brKTbZY5aG6EifRfn+B7vABdNHwDA1PeCAjJK9942qeUKT/Qka4zsUYAzi3E6fdPstVWhBqPoH6mlkGMrx+Ga4LCLINDP+ZMAArN0kht23/2/Gsih5E2V398lY+6o3pv4yB/vIWvKFCsC4DzndoKcn662Q+uNtB2r9jTx1Sg91fC2lSlBF7H5J/3rI8rOdlVLtUtXL/R0vRQBw2CiMAHvk2z1dCQ78wKLfgdDEvN57Fh6NpUz1BybnIwTaHGeYtXMLTlvQaqInGvUMS3iEQzZLGSKbGjKatr98QcC2VyK8Lg4Lq4fyjtgkSXXfKVeaDoes5ievW4VjreRiPzbGW5t+oy63kGb3WkcvTZxVTbUCFuz1Xha+xRqnfEEQUyzY2x2Kf1GTM3OVdvXcmVPvk8olrfDaiqvlIPxO057S+qxbChEZGl0Z43931QX274hvdi55KjuLOoty9r1NShZMCtLdu51iftbj+U7XChZMEmTLI/XjOK2qvXkDLNGchBccS+Uyf8AsHiKRBZ+w4sPG3+9PCcmMYQM/aiGtsaOr8CNrjXv1Y5eGrK/ms254I/tWVz1L+arFlrqh9fwySyXK7NXE96Y5aZB9mHnM+9DwPDq1lb4wkB7NrEn/TMEPZWNAqu2TvbIHKeqPcoJL+tMe9Tb17CFFr/WCEX7skUM91EwTNuL1zlNasvfJ0ZZAW5/Yc26uYWxlerbVQvMaNS4tKq7sAQsnyNqYW5QVFFiXf9jB+AzjOjpUtLXF/dQSI70nxFmVvrb2o59q7v+NZ1PlT7e7h77ZEWo/vzsxug6uR0fxf1W+sryxNXe8l29bJ/b/9igxU4XnNgHP8y2xprG1kpl+cXGgJgKT0w9TrxO90VJdaWRFgvJo0HFDPBM9Hj2v1eI7j5ltvzRGHcUEySNtLvyLj5ynP/5xKuoiYz3tXZzdcGOimIAxFNPVSvUP5xXvgUzOSXCvaark193pbEta5EcWv7h31Wi6703cimGFlxwj2obyW1T3S4mt3LzgDg2vnPl3XQQ78cImD5+3v6mTx2vTJxSkSJAxmPaTZBrKT+9AnCjD8wA2uqezaPW4UOo73QKp9VY3LTd9kp6OuTNOh5c4K1YCzv/PKRDYd57fATio60al9c+BBtKPy94fZJWGQcc/iCloKdAsxyQ7qXXG2x9z2Zv2F1Hxx1v0kgi+2hly5ekMCBVKEdDpPUv86xV/Vfibz+b5hsGsyL89Htn1DyNunDtcq5T5f207UimfT2xXbxeuw+1C+fxRMgbxOtzVBbSaxmTO7ydl+wgBpmvmg4U3NdGcu6qSnhb4mDYe9/znH+sHXp684/1mXSZzLUzOjnRNe0/x909WlO7qtSBDYv2dJhv4tLVYJbqn0Bzkzys//mk0SgJOaKo7yTt8agRTWb6/QE5qFzsTDo6jFEVzijgp6hewNIkFj/Cpd3LHIIL2vovgS345Cm4dS3Zo/T3rdV+aHXdD/2v930tGjcyXa0F8AW2rH44rVh2pwxWU/b7iqhw7FZy9EmimXkg4Y4BnUx5m7+qQiA15z2p+f1Ax9slbRk6qJNcuEO0d9e0+Y55uLxiGV5ShnMX/vkeLEo6xUIvi6MJplyyiXtHVHvLqrt/ddYpO3O3HaBPJuf+9wiZQWaOJiO3tztyM9GD2n9+2QnkXCXlK7FZIeEDk81nZRLvypYpYbinkMgC057DXyGpxJrPq2pshQ/mIP6D7eGOc+j2xQ4PaMHQFrj/vW4RXGHXdjL7os7ksZrd68WWMbsf0Fgho8bVbhwXxEPJ3PrW2SP8R/9dn8t/I9nXk6f3x/421NAHofqkCODfusLS6l3Iaf8EQ4NHov1JgkUdHUkbqlnUcGTJH3rxsWj9y9DJgB546kYatMbpS4SfKOXj4g5M3YBlkdL7yvwObC0D67pvMaycpKCWYz5fklGiZ72V3ichc+8QV9E+2K41p3yIscOG6BFjjOQ641yzL3rdu/n+V1lL6v8pXGz1czlL2TLx+Ku6IegsjVux+Fwn1N7pPvNXTYH/VabHuvqZpHnlyKyONSrL5emB5ZOPfpEvHoaiMMramwN8nJiD/ry6c353+rYLj9+dSUqIVHMsEs+W1wNd/X1oCOl5umgHU1I1vbL1jlM1HuQD3Q1fV7XVfvQupyThweIiaTtk/21eStu/jH7NPwxq/Qf/s+62TP8PHN/2MMEvcT/JjQW7PhgYEKiZkREgmRITkn8MZvvGz4x9fwYBcJjoSdoMFd9nyxhx5TUqlSjMAcAuiyv6ap3rfIZilkR9PK6TRENYSb4ZHOdop9FxPROZL/HdP5H07957vUD3SBqUhykRHQRDajsErYTF5vtvscBgj9oVPvr0SqOFW3uMF9QEgNlouRJ9e2+8Li4M6gin+TgyLYq2puxfld3nW81Ivw0NYaUIKyirJIOISceAGrGxFX4TpJMUXcyHtIi8fqhlxRozv4cxYv2TzCRWJGW6YONPaI5NycP28PkodGyThzNff3SOQk3k6xCwmSEbVDHYsEHyHXWWMzucHkQ4a6lWPUFdKyeq3KXCfE/xw5w82KGqKNBfMMcCvLxCmUamSYS5es+jwvRxwjxZG4+pI580CxcvC3QPiFZPjQp9/LjjmE8gNSxca8TmmaO4WLhtZE/0BRBNnJLKqRgu+wy/dLBW+lsNR/k7IphuSsakcmGh937So50x2CutOdJmneZvZYLLtxhtZQg60YN9JHM8DYxt5fUFLccHizUYYl24eqvJWfl+vS//KMW3isRByZqlTQkZovPxyYxOOOw25HEwOi3rVj2PstNfbl5jElnq0xulMWnXoG84gL7TCPeq0Ut3SsvM4hI2RjekWZJqibaFmz8OXcRtoxZ+ZvmqgdpC+CP349cB+2CfQJGYm0UOLYzy4EJrxtQH5haap+21UbYlcVmlEjN1NZ0P6GIDYQx5Lyo34qRRPxq9VRpdhHjM0HEXHI37Z+FUcCtXNEw2bnfxOn84lzoPObsix/ME73j7nTh0Xgme+cxRvDl+C9byGcfWhEyQcww8NCuQaKF9G1vZd5J81hoJNcnVh6uJQ6Utu55Iy0VbCO9ofbngtUGVrdws4mRUHC/hJl4/X2h9yWLrot8E61sRAuxrhJ6gdzOb3cZjmxu6782VzkTO5aNcVEmSU3c2sISl9nW05bK2I8YqauQxR8ss0rQ0pL/DcWOvkO8tKSa9dSTDSJme8RXSR7K+H98Y2WmW9psv9zoQniVnQuHh6WZLGSVIXztsKL+1WjmHFGZmN/X+zg5Lmn54qoWwLnZXI/4ARFoYwPoTOpxhGswPP7wP+SNzqCCsrRBpJr87NDINB4sHUANKaO5I0e9Qtu77oIURY2CSy/VB1EkE7bAHuZjt+rnPvWTp3AsfyP/oN5z9bOqLyZdScqVdqnEHhSIIDh5yMJ1vqohhJoRTNtHzdkaBs9exRh+m0qDpiGBW9RPao2UEnhtFyJlBcPtmRf4iRoEQP+lBrIIXeDBA4AlFyoTKKMs/0UqEKZBFwrzijG+BYtIchh5OFFuoosl1pRS3RWxR9CEOz0qnanZ7lYYO0L+bOH1K3PgGta2ol+KHPLYpEooORqEzZFHsyxR9R3/bIzfzZNaLb9QR8Uixg879htoE23J36LA5VJEeCY5+OZRmQ9jESqcWkZpgzXuqhNjBpARTRE5oRTkipCM9ozj2cx7lYioC0aTE7uFriG8qE0kNTQs1iHf5uwOzButCON/cTJ34PkoH8g/mWZmNm89wouYWkUCwxKwH/FJaKetvCSchfkggiLCnOVuUT5yS3c4kKWnVOx/UlDWVCYdnr8NIDywzDlyXKQzIk0nPbWeKO+x/l13dihPr0xcsG5zNunCfswUOBYiFgR3APOagmElpK+7XcpedgWJ8TjQ2659j7kAvEe1jwcwiajYQ/UPILdeK6yqcZbie59kSl0yus1Fo1iQ/MLMqiZt75rFH5jPd8GF6+KO6RZghnY0cdho/+bNHpYaJ+1FZ1ft6YkeJ4LBIXIK/EGFIGfrOPaTqEYdZ2FiefT9J7K0e+4CwsfExgnvRaoX2yzAZSubxAbQIzdh/GAwe/BU6cYCop2bS8FIwzs9OqHbQ7QilIN0nR2JSb6SHhPowRXWcSskJIeQjJolzDOwZkZqay1YB93AQwm9lYpdzkPgXpsNcL9HIvPyJ2lNfg8sdx9VziiRB2UsUA+oLfuYRlzyYw1iKUGOcStiM0uOwHz2gDpvvYR+Ki6pPTOWoEkHiNZ64S3XVrLR1gRkZ1TKdoChTlFKMlLjUxG0r8lmmRlNX3iUxSR3liMnM8aQtp7ZSHJ3CyRGHmwJ16ZpG7KCadtYMh4ZiDl4J8yj+jGoKWgvFNw3x6sAXeeAkI9Exr0KonPUSxXkoaEdZ3EMx/W6Er6NKvEYLYuBsNVmFkeaw7JX/8MHtzYJrjvgzr/ubzgo999xKkSdsneNw3TsFxGlbakPWM3SR1xWqTepJMX5st1y/vu6Nv2lFIQjVcXhzg/NDYPLUVVx0/E906H9tMGcdGLD/Pl3JM3xJSVYEVhLNXhR1l0tJU8FHMDASocORDTJQFF0ojzaQDJV4MvRtHqiFCdFJe/bt5Hny89JmaigSWcXevMh7uxu14LZPIr6oH5h95PLgLGNMo/TJ2qOneB+FY209RR1XCdhfWYApUCO5mnzSkmHF0iiSyWDcvXIWx9spURvfD1IO71lkB37ryQVU9D0fLX/wSXPqJc54mpjLTcP1vBOmqHQNFSlExpqPb0spJzZY0iN6XXLXtorjxGOnfOR1UxqQkTJF4GoSoqP7BDwj6J4B1n+YAFJIMmqfCg7QPJ5iRxn6wS9NOkFlVTSVZL3XXHBCiM9SiV6/PX+AopOpuvrbphYd7C4sSZT6eVAno0kNsk6er0Rhpa8RTj6bFxvNUH4OaaVBRTV2Vf+SfTptvmnR7MhNiOlpQGyYcJls/StAarQq6kF5oQWvCX72xY7QUxB8aSilzraZ3KBMwZrFpHEJRItiMg7TKmBFO6WEPzw/ssTU+31EYqLYHGMKn3yNO4IeA3UxbQg8JHJwmoyp/YJrE2k37K0TBUzFspPjOyaOKzYl1BVVTU0LSTtmah16onT/0w3V9yYOLKq5OwvmCxrONJL/PRpNYfWCi8Ds6zy2jMRycn1XvmPRtx+e0E6SpWgx+KsCuOjvv3Bu/wE+venGnpnev14oIx6XvgHxcTMVAXBGkqZVXaFuMRW0YVgs2aYly58MjcAxStoyVnVHjle+FioSJ1A5i8x+z9YTd7qr5VP6WGk6ZRLNaJjeSFHgEmP7oB+GZIucWur7bWWgoNxNCcYSOnqgSZBR2fJ0RqXYtGmt559U28l4aj/J71nC+U2ft+El2J/nafMbBETrXwttWFBLvTj7fjAVrjJYe9KX6xuY6woS8wmi8oTzuijKGX+wriCydzBCJtKwrv9v/VsubpnrJzavSOIecCfesyKtmMaH2/ZBzudpRZfRdMqbau6Zrcm1lwhtj8omWeaWNx0m/oQjv3pe/5VXQ93X39NJNC/h6gkw6TzayyYoXUQhN9K464pJ8CIWTddR439l11j/56DO3d+bbv9mx+r1Jt5ImkniMSPoQRrShjJ5VCCj6XcGR3m8nuao+WjB/4uLcuoP82PFPNusHh62fysp8b+37X3gHssJ6aYrznVGxMB6Up1kWyW2WUplNHwAYYkp9FHEFcepOODabMeVJmY6hz4/mIJFg6lS2jnHAhs1lFj6m1eJovU/r1SYv8ELSdL4qnvl/6F5Lv2Gv7JWz4OKRoQ7W5geSKrjkjCDR5P0903ctpnJqZVNv1mp6BZ5sQu6YDCoCEXPy6MbmF4G9Gkp6ZscuObmBhFOUnuqN5bq/RRMMi2o9ErvNqhxecJ7JR5xXGXFm5FH1lTazawaRit5w4iqjAnSzW5Hh4lTIj6vvjLz+vNCUMyNdUWvUGEg2n4O5cQOsqh0MMD+UqUxS2Oo/W4fbDf4Kb+5CYZyW3o9xYBJr7FnsJgz2ZKwVAOpJYmCM0rcMEPbHWuBtZQzwkdRjbCRPsp5P/JnUOCn/qMQZNm0ejt3Cypjq0eORoqtb3qxMXVwwtlzRmpnR5EFUnv0Jp8NjIH7w2559PDzUuVv0xgM7ra8nRg/V/8p//wfLyce8sZsJH9ZOFdlsxkvXAwYu4Bu2iz92B0fYUH9OIUFRy4PZ+V+a5CFcZqD7D6pziTxIHp/tkblECehpaR4t1Y72nJ2POyQ+WWhzPaPxSKQjvPY+yfmm329yx+pvZuytKdCzrpxpe2rTsJzHm3gJ//J8Qw0Purouo0n/PJPGV31kJHf/XIFklJ9zkmOVVEeTOgpOSRe0odmUnGlDVeqSOzwOg3//Np/5BziPlWaJkQOnE8rsoOpdmd4oZ+XA4H/xKu564ZnAWxJL0anX1zkIkWYgy18Q+5gJaQrkWFdxnNPb1L3xhvvT2p4cgfi8YseXkwRaR55lDZem7H/rtWJvqaCeIfH6HPpxPWpHuxzAwmIdfnbSqj4TAys1tXTMaqVEp/gtBBy0nmgIgD+x9cc52tjyOIYfE7mj6r9LOGwV1hrb0P4eyTBei0k6tBOsFrdszjF6ZU4/PJgSfcvSXzAu6nhJUklk0eIR4UKAegkv1V6JgAmyHVypxxxciqT/BDiDoX6zY/GnAWBf6xBqECfkW3ns7oOmSgvoDlxDx1Kj9/GOXEpUJVU4MecQ2hSmP2Cc/HI+/lp+bKaf/fjV6+s5DUshhAV3L/KnipThxlHiaFNMWEdOJU0voVv+2dB3hrMon7Dvuj/qPp0Hw8IpfIAITCQ7E9Uf36JSkdiRAqigkbfwCI4KihIQoBk+aQbGZVbzpdgDKdmdVm0d8KEO/sO0P6HLvgt0EaG9sO2yM+meI2ywSpli8GMTqS9YbJlYDThYqlr1AmMsY3UhBOr1Jame0wbqfdAV6hyWywB3cA2tXAqEIlcJb7Pa/hV0YX8gP/S7pLoC0wNuHK2K92EU5QxqRS3fqNaTz9N/Bv/Utx+b7cRTU8aGf4mg6WYs4FgHs1k27Bb4HaMDgIC3yN28XpirC8ICQim6P61sbx3YkJ6qLWFVu/sK1RJFq+AhGCP4Fa4L/QAbg2Mt7JXBxuTHk1gVA2nnn6kc0h31CrBpueJVdypQkBfh0V/HvyaXznEaw+SimSsrNuassxz8rU3RAgykAFwHfR/icUJCcoI+uuq0u1NkLAfnpgKDzw3J9h3WnYa35cfV0zsqafWs6FKhaRkQT0Fwve4nGjlh0rxjTQSFLKJlMCZ4zLjlRgKqV6FqhkntgsjvXd5ojdJJ3XSHAvCEumi+5hizOGbUP1f7L8w34F7UdM9qHbQ+xSPJYyUGtswg9rqvIW9kcSne8IhAsXgwZyeJwpJQwkUpp0tJP/KpCDTgcVJrSygaeKei7dGmT13SQGWm0lwAX0tPbV/PP0UuamQSp0mFQP8zpO32ira+6I7OAIFdfqFEOolY1pd+v8TKbqsFF7Qd2umFBSQ7wW+rOEPKA8u4ET4gYo3NpaG9cV4QklXRqzi8SiqE7EBI6h8rZ7aiCn+ZOIY886SumOHAMEqrPlUmL0o2Kv3Kio6g+AhIkbiDkxhRCQFY5AMfqhqwtUOYRNmbRoXX2Y+tKI3IzCgnZhuK4JUlNRypQpKCk81gMJqx74hzbzRKc/l8nJtc9fhY56mNp2rf5dD0FfKXXuvxL7OgfugN4BCFyNQSco/8nbrumkIl4CrrKe+fK0HU8CtxczNu2wCN82kr91P29/R6cnipoGMCUucj2guwVk6RACNK/Fh5cyj5qp0sSOIU7/qE5X4aOaTBDQa1g31+HtyeCnX7tyeDj7Ye65eb7PmlKV8h74213heIoHE4kWoUVlfqmlvVM0UXZpRvEeCocpw1z6iMjYLVw+skqDdnX25njTiFwhxSCLWbb2zyZ1sUDQTUS7RKQaiH7ZogC4=
*/