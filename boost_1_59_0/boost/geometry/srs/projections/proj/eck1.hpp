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

#ifndef BOOST_GEOMETRY_PROJECTIONS_ECK1_HPP
#define BOOST_GEOMETRY_PROJECTIONS_ECK1_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace eck1
    {

            static const double FC = .92131773192356127802;
            static const double RP = .31830988618379067154;

            template <typename T, typename Parameters>
            struct base_eck1_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    xy_x = FC * lp_lon * (1. - RP * fabs(lp_lat));
                    xy_y = FC * lp_lat;
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    lp_lat = xy_y / FC;
                    lp_lon = xy_x / (FC * (1. - RP * fabs(lp_lat)));
                }

                static inline std::string get_name()
                {
                    return "eck1_spheroid";
                }

            };

            // Eckert I
            template <typename Parameters>
            inline void setup_eck1(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::eck1
    #endif // doxygen

    /*!
        \brief Eckert I projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_eck1.gif
    */
    template <typename T, typename Parameters>
    struct eck1_spheroid : public detail::eck1::base_eck1_spheroid<T, Parameters>
    {
        template <typename Params>
        inline eck1_spheroid(Params const& , Parameters & par)
        {
            detail::eck1::setup_eck1(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_eck1, eck1_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(eck1_entry, eck1_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(eck1_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(eck1, eck1_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_ECK1_HPP


/* eck1.hpp
Qy4eERMGd8un6NmThnbez3BoofR0t9Qv/SNyvyKZ3dUucRlJn9GbBO19Pm2kesjzkTQf1SZb3Pea/ehMn3Y9v9yShoo4urm+hdJNRn2bDuM0ozSBPvgpovJJP20zh1adMhpQog0JyXWE7oyCtLViLoHXvDrYGFSurxDEi9CRRVkFbr0GfRv3xQPGXoAf93J9axSWZZ/q0wbcIMc4lhMPmYSqNThHa6NDmRbU0WRvheJMy6bX4sT9ztcS1FNgL515K0zt5xq4hfAHryXwYWEDPnYdvzXJX4lBW1+Nq6GZbKKAOmhf0OXeJwzSsiAqdkYsOFehqyR+EFNNqqeeXaJFAQLR/TIWI5nDQL2SgdwyoLyyHIh937knBU2ubEFDM2z3N8btdApd2T6yrwgaqoQumBOIfvzANImuPLgK4fLBNRuuCrjms2mPp6AZ0zWhVytQ3lHrohBjlxW67PA2F34dVIHaPnmGa9rkQleeYYYry1DoclLxsJ9Kh428yRVI08aLyYZSMHTUs5yznFWNUaomy/jVwAvPnizP509oFTRlsryYP2GEq6mT5SX8yZnTQ7SyEfWLZuLRV3VIrsIjQuimw0eBuQZ3SsusgY2HDE8AZH4WwT6izhZGImPbQ0Yekwwafw/cBw1Ukt+fBDA28THKNBvI5Jw9rOdng6I8leuHWYfoUI5v3srqXAP3soU0bSDoCG2bZkgMSbKaTkvRgCmgvYFpdae+F/InLbMbiYfn8F7AAwT0EYyzPgd9zAfKeSr2+I9JPpVLgskGypcLWIlouEdbldWzsZJWaHdS9AUqVFwSazPUWgGFNFAjeLnhOyAfNZG/oCU7JbFpKpWtNxBKGIGawXg48Nxs2tf4Som7XLZtji+sKQO312weYgPu7CHj+nDa/M2o0nvNHvrJndqMP9Nm0E/eevop3AQ/cuVUIAvRlkIpcoUb+nW35HJZtvb/F7uddIS3rIlz19gO0hFO0Ane9HWfxmQlKaiFWuSMB+M203H+oJ5hvC5qpnNQtBS2Fb+UuVTDQu1plBfojvdcOu4Qh6v5TuRlEOEO2jBqXKiigzxKZAz6/ilxaZJDNcQtb7T1S0iO4xh8+IrVBXI0fhAHDb+E3iBzoPlEci7dzv4QShF8VYgT2YQ7iSjoJZ4mWayjR8x5huoxn02DDD8/RJ8t3/X5+e//vOn7P7885HNctnAIiXNlH/DvZR0saoyJFDr2fZ9AgjLN1jNNMcUy/fncmcbv41KMsq0owngwNZa1et/ZRBhJWTv3oiaTBW6Vok524z5k1BcO0VmVu5cM7BaLKcQzl4AcAtqXlD037KV2o8i3GkPeESeMz6HZLjuOLm4WGFuL1DQPQmrynwQI7m6O4DLv4gjOIlDAvzVpOsqc7cqG7WcK7YCFriWoaa4aZvGRR8fj27AYytIDWaj0+/aS3trvEcc3aaJDXd6JjiRGqGs4cXZzlmKNpCjXNx0Rnep6fPcmIt1K9y1jxPPUHUA2j0GabnJ7vjI8pyfyuyRQrOpGx/UDgS25G327DhMX6uRoKw5hAEu0DIbuwS1uDiXsvndPaMg9zE0XSFlxJvxSYEFrYxHGXTJidEU0QdiGsnDIWsVeehd70nUtfpac0J9CZUWn7BTU2+KQLiFI38YhXaJDGuP+phNkIpuhoBrmTk1B0YyWE24ki0riaxtdSMopr7mwR+zue0gvt0ZVHiE/+KhSXKPzAzVAiY/v8VoM4gj0ol+Vhu6y/wl8KhVeB4VHfgF5HdSImvjoWBsDaQNRHG0seHWfBqXkibj9ZgGczcb2mfRl+VvH8UuKtbHcgKjSYhKrBuoHsla9Fql27UOF7901AwTwhwBDuyCez7cDtG6dfie03xhB7waDylhCZQzKr4oup5omL3Hl4YQqotiaQEpmLkEWgKbyfeMgC3Hrm94+zvusmACgosvehTbE8DUPUKUTUWXObiUtP3Jezu58d4ll6U/lXId0JxnSe8KCg/hGpQStkkvM+M8y0BZiI0YkwZ34iBHodQmoJzYZ5qjsQce+QJXIuQJQwHqrzodWdd3LG0IvDLFmfmJMEbqeP41+giw2MSv2/eOt+vcd8D2np2sdpNiCw1ROsswdV8F2uLIDqKozolUOOwP0djdkiozDYWbGNSkCsQs/PX5aI010QNzCz1K4QXrNyfH1w4PjKZNlC1phLQoAVCv8A8bUWUCCYF25Si2QTIVAB5ZhndA8d/VJYPqSpkcu2uKz8maofoJa67JQZHm/nnsxWwhzxw983MivTms5PQg9QBSuJe4f10C+bLimwDU1NuA2whU33GcUEiYsYplZkIvoCo74q17d+XOMhDpFy9wwclGNn3VjZM92lvaBUSgn/fkNV1JM0tk+nuppSAVL6nkuGZXuCRrYmzzL++8PrYxvH1COi31eAzRgfFUpNxAccnGYfriFhsnFxmNzgUjGl5PgJbf7j7LRcN/VgxpPuHBX8TnjA+xV7YC5k+XZvywj/jYrdlcyzvPe8hT1PUoRXZaiRj0n4PmE58Oxu+WPz+Q3k/H9DJfPs19KQ5wUSTO+p8x2ZW0vwOhtzDqKtHqGBzBqbR67SzuO1gV2jOw6TVA/UrhduUeEIWxchmTcDQ02GPQZsMra5A6DaFFHyv9rAqyXz1E4bKbo3MbaeDUmNqglKBa8Jqcn5wBKApDHlFvsTT3SBHdF/8pUt6PWUESFDbtJbjF7ZlqWHkesiiI0dT4AGQn1Gpw22UitEwkgb3XhwQdU8W9k8DPIU8DBoBl/1ah20O/L6fH7Q3zwYJIuocAzIW7k7uPxWZ+B4cUQszDQNhIfrCGd67PUBo2bATNummevOF5tJGCoI/0qR7PGqB9t1GwA12kwWQdlR4KEV/IMVVJT5MfJxb7+yoAgz3VDsdIPcB/QBJXD2Yi+NHSQz0enBr9EPACA4OVsgnIiGO0Wd1EHTe/MTdAVmJ1jr6DZee17xiHdiM/NWcuNAsevAfiZBhBcfFqLz88nmvX5uXL5wPxsah6Yn/fxe8I59zTrOKdMMwjbFgN33uXoGyirLFZWTkJZ7oSyrkgoa0KsrBQoi3bKpl3xI4YqVgMPpEutPuTaykNqAYXx6u2cwnCdjRjqRAAGLPnTYujgX5GI6WbTvxV0CurKXd9HfFGm3+mZ/jeeqe+v58x0z191iq0dKbZDp2JZt/317BRb7MSJMk/FRHWOnCPK+LDXjEIa9wK7dJN7IRNvcC/slXKrzNOA/SwDlPwtV9iNknEyuqPGCPHcUlm5Hn1dWJCkxedc+IiFT/srqbaT8qRdGCQosmnV1IIXdxLViH7k4WnYXxH2g821bIlNrttJ/eV51DRqoF+zofExtkXetQfPyfHQHBK/iaWf5aBEByDDNFMwTVmU/bI3Bjp55/dBnTJ908Yz7YtnKjt3ph1tvOllFFP+ivgoX7Dz+4eKMjdhjUVRoJJTlxBHG+DyK2Css0Jle9j1X1LAHZuaLu/q9lf1ehbVBAAsRJq/Anm5vOpskNUrcPEKoGl6BSj+4g1c2qY38Ltz/2sH79ugAuy8gKvbvo99oAKe3TG0egfP/dWOc1b/k7NXn8ULeGXHOau/hAqwUwE2KgBnO5bh5GX8NFaG7TvL+KT1u8pw8TIuP3cZG1vP2pFsXkBX6zk7soAKcFIBWXojHOhJVeeoURDCC9sQKyzrOwuztQ4dlKk898LWcw7KgRbKPZD1Gp51Yus5l8pjg7Pm8qys5ZxZ57cMbfM0nvtPLeds87iWs8I/jxdwZ8s54X9sO1Ufk33YtyFWxQ9XDOQdPD0K1Wjk6HcV+ND2s7aohLfo4PZztujWsxcwgxfwq3MXkLF9KER9PHfF9nNCdM+2obln89xjzp177bazNr6CF3B42zkbX3qW6ufz3E9uS66+uSKuxdM8bfNg3Rjdgvyl/ShA39l8e83Z5HP8C5v53vdJ6cIGTNQ15b0kgXu+MzZnHHKd+RQexcXkQ3iyg7kXdN3wfly8Fk+eUbUKSCA2u1QQug6f5Xu62t711gb4uPp9YZA08f8BvYyo3IlGAIBDS829D3iT5dU/niZpGyCQIClWrVI0sE662dmqrQEtlpQiFNNWElBbmH+wy3w3lKStkyI1FHn2GEWHe32dczp101emOEHqBCyCbRGGnTJEYcoG6t2l24p2ELTt8z2fcz9Jk1Dd3t/7+17Xt9fV5Mn93P//nPuc+z7nc/5w7JQmher5RZ0ZG16lqtvPPyWP+fLZNCIXvinKC7j6SVifM/OJjcxh2JIqS3hWtzmQHrIYSVTOHeycyexhyk3BnfmGwCXwc0D0Z9Yb5lDu55Q4LciuD+ZQ0A5zyGKOTKBAY3BsYqAlJaMdRbU96/77qJZ01aubMBUeqvH6B4GVWJcttcYdzKoExquZ9EajN7FAIJjMLanLDs7F/Xu0ylvDL5XaaCxR0IHXNkbjlHXJHYqMTfhpSYsZjtgjkyluwJb0Milu7lCMFxpxsh/GXH3yNXAVx4SlL8YaRF/7OnrHiW7TE82KJ9r5rxNd9prOihwDK/LL47Gka18bWVXJr9W/+mQCQl+TMfHkapkxFa+PpHodr099n03P7eoXOAGB6AB2GrepwIYmSS+bVVJxjHU2ZIXZZsBUtlvmBk+yYiVsJ0lGq/GJcgnXutq5jjJ39bFEOSuSoY5TgHJFgrrrYIMTdzOqudMPQLFsSAHAHxMHgPJHb0pucDrvOAwh71FoFK20oh4PSLQR2+o1Eki0Qr+PmedcKNrtn2h4urZjtXM9FZsmxm44Cri4dUYJmueAEHH4eRYoPGpFP9K7ukgU3gFtEApDZgs9AkCBejKjWmpVGyx+zeP1aVnH2FbaLu48ToJIwHmtuMbIGXugBEEiMy/Ku2QB2SSFcM8mWKTfx71PQsl53tixZ6qSWWzc5zmt4opXj2vh+e3it4K9rKkLHAw3ZfeI8UOsf2ahWXDPqzwLkJvjtHkw//bWYciBWTXeBMQBjxzywkPbjUSRSmot0uELhpAv+NCTuWLll7hFtpt0zMYc+rcrK5xWoCEGygCJkeblk+BcafaUud0A6Khvn6A8jIHz1YwaVlBzQjfXofad/PCcEy2ffPm6dndLB2u1pW9Po/jUXRWyCx3chcX/DUhRQOHFek8qjZ3WXTFp43Coo527bEwb1koSIJhXXM4qBy0ari6oG/eJ736qMfPXzEyW2APZOYr+FEVtUgiR0GrynsbQ9vcftTaJCT9kM+POjHWv4kbILEmxXZlvCc2xAvk19F2KMN/SOdPCugfzLcp34C5n91Klwj65cgAqW9As6Q/PpzInR45qnRmBV7E1iad/mKgPw/jQ/EpM+dVRHQlcOJ9DApS9OOWy562vBQTvTEOa0w1IW7U7jYUAp3U1WVZeqI5dXac2te4OjFLHe7Rl1KdnYK7NN6tpJJnQ7nFOqMKqKQVE8+mbUjE4bblFKaCPxSl7qw7fWm4JjAOWBvCRkWu1GemSksvOSVGz0xVyfa7llsD5IHxlZqqLkqHONcN2zmNhFTizcl5kqTIpciNlU+K2rlwYb8JodbwXWNJUIFLPNcud2Y5ktKuVW0ptL7rtnnC53UNjIp9n06LKuYJh15XZVmUSoIN32ZXZ5ohRHcKEuH549iWhCqHjmZdAL38FTMTMos40zGsaxp7aXx/VUjAcihgEnif+lb8++jVD6Z/etgSeuQduY9222c5QGx9d2lY3mQwG3VNqZZc4dZZUQfNCNb2XftDDXtYt++gsaTetXsMXcF3V2rpH5HHcNLiuIPK4DTPO3Y7H3/JjFx5/TY+svdljBzhasEs8spUWSqnd66lPPwI9t3aPuG8ScSOLC1oPBV5WTTVAvsJntuLeBQhRNY3PzSq3VlGgVQtuFSsrjQZU5CWo/RCdb/1PRKGJ8tB9ummkbfU1eJrtDP8UGmbV4QVHqpWNiK6OCS/org6vyecreb499tSQ/KcXdpIP6aigHD3gE0NMWb5bv6PYa4hdO0MbZSv0FK31KEW8vq8HZvdtsAXANSt0vMd+Q0KNsdH5mgLe67ZS+Hi0gWtBMUtTcwoO52SO5bRzamJORfGcOucZDTDHD69ZyJfjWWvPhjHBEQqoHw7QXilivSbtlQI2zdTWtcvxq1NNcJPsyeNpMY+ZyXPULiwY9sqJ4Cc4mPslnz8t+qB3PR0f9G1Pxwf9t/y4q+dcJL/GWb8JiMdPfwrln11sh1G5Vzz/NMzP9ur398FdUgqP94gV74gz3sWhmHS02XPVtXXwRx3azld8gQnxd0Xxd2wO+/5UkyH+Lo+1GrR161GhWBF2vB7vN3jozUN4ozXkxtQJWCXBEtd5yIMjVPGP10ywaV2y1WRgzKcC6BSjiEJttk9btzYOHJDURc88Fe+iR5+Kd9EDTwFuXwx+b2Tl9iNg35peAs8nxEcfxxi3t1/6Op6PE5Xpic75JJbo0X+daNxLOqMowCje+Wks6eKXvk7y4qTvboTkJWIzZ0z6bfFTIbW8P8kWWynvrxvG40ZibeNXngTq2QcoBpwV0/ZS3q/rndMDTDPwevvGkS6gk3K4eCNrxYbLB1RLPXC8Pdp42bqWjSMIpuocGtBa7QlohsTAQjqwi7feqoOFHAFKx+EXj+uOaKWBPvecmhZD/1i3inUMJdLJWRv5iFScvJU3a0B+zO0Y1NpmiRQ8vxhTwvX+EZWgNgj1lXlSZbSlA8sbWkqVfc+IN+nt4tNaHjt05QxKKAq+H6VvVr7YncrnxbnGI8wCWdAmaUVPE2j0YyClp/FdJKSLxDHuY+7n0hfjvORXj8SzL+j5j1HLd4Xn79I8SyLjkrLTjwLFC193YsB53fACT7vC3VX4k0K/3T9EvIJ+7vX0C/9y1mcjSga7aHHq31aZ+NaUCtTjJqxtCgzRVt4yPA02iD/+huYfDPi62UTZIlpbJCdc2c3b5opQzKpvq0ectWQwZntnZIIdvlnaoBmFVgKTNP0nzfBdVdw/N8gwsWsG8DHXKrXHOmlrgS5vNmy7Si0kweohbS//lS21EjLddjmE/L1sgreVTfDO+gWJH5XdsHDraMEi3yBW/EZOzutu4cmpT+CkTBO64KM51AV33ZzYBe9sSOmCe1YldcGd9yR0wcTF8S4wLfaldMIXxSN2wkK9E16fHusEpXlghA7YFEntgK0lqR2Q/Xi8A95cJTvgrg2yAxbdPFIHcKZfscAOPi8XWMmG+AKzJmtonXVTDKXm72+fkig1nRnW30EKyA3Ql7LSqazMU1bmKysL/CZlZZGyslhZOV00PP+xVjLDvFhtCl6qziidgOvF+v3E5732CKWq0d6rZ6OhXgqpeWr1TMBpP7V2JlxyIg0Icf3aOGguiQnNNyVvM8DXmATEn5nFwTNbZ04PjiNWEzYM6SRUGSJjC9sjo0LfLTK04efwkpZxppDYZzhdP9SJ05kZ90Hr7njhIX+aUlek1BUrddO195a2tt85OjR/elpofrExMt5vlEEWCjJSUJqWZXcwXj/U6Nlc5+mzoTT60zKjoaSuyNa6GdzHjDwKfM3Ayn0DrNLfQO9dbout9WFG76ofZQSQnRF7PYmiTg8wwoMOvIBeuSceFnBDzJ5hpJiB2hnp+PLOSMPXNTPM+KqA9VRohTPnnMAM
*/