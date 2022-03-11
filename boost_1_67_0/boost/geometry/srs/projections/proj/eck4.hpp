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

#ifndef BOOST_GEOMETRY_PROJECTIONS_ECK4_HPP
#define BOOST_GEOMETRY_PROJECTIONS_ECK4_HPP

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
    namespace detail { namespace eck4
    {

            static const double C_x = .42223820031577120149;
            static const double C_y = 1.32650042817700232218;
            static const double RC_y = .75386330736002178205;
            static const double C_p = 3.57079632679489661922;
            static const double RC_p = .28004957675577868795;
            static const double epsilon = 1e-7;
            static const int n_iter = 6;

            template <typename T, typename Parameters>
            struct base_eck4_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    T p, V, s, c;
                    int i;

                    p = C_p * sin(lp_lat);
                    V = lp_lat * lp_lat;
                    lp_lat *= 0.895168 + V * ( 0.0218849 + V * 0.00826809 );
                    for (i = n_iter; i ; --i) {
                        c = cos(lp_lat);
                        s = sin(lp_lat);
                        lp_lat -= V = (lp_lat + s * (c + 2.) - p) /
                            (1. + c * (c + 2.) - s * s);
                        if (fabs(V) < epsilon)
                            break;
                    }
                    if (!i) {
                        xy_x = C_x * lp_lon;
                        xy_y = lp_lat < 0. ? -C_y : C_y;
                    } else {
                        xy_x = C_x * lp_lon * (1. + cos(lp_lat));
                        xy_y = C_y * sin(lp_lat);
                    }
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    T c;

                    lp_lat = aasin(xy_y * RC_y);
                    lp_lon = xy_x / (C_x * (1. + (c = cos(lp_lat))));
                    lp_lat = aasin((lp_lat + sin(lp_lat) * (c + 2.)) * RC_p);
                }

                static inline std::string get_name()
                {
                    return "eck4_spheroid";
                }

            };

            // Eckert IV
            template <typename Parameters>
            inline void setup_eck4(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::eck4
    #endif // doxygen

    /*!
        \brief Eckert IV projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_eck4.gif
    */
    template <typename T, typename Parameters>
    struct eck4_spheroid : public detail::eck4::base_eck4_spheroid<T, Parameters>
    {
        template <typename Params>
        inline eck4_spheroid(Params const& , Parameters & par)
        {
            detail::eck4::setup_eck4(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_eck4, eck4_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(eck4_entry, eck4_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(eck4_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(eck4, eck4_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_ECK4_HPP


/* eck4.hpp
d+YLNDGlYvStvNouuGs4cHBAOUeHtdIIxEPm56vKTlWpMxFZvNqAeGgn/yyQ33C/3LSvovHhVrvis5051LjZdh01r19Bwya7ag92cmd9wZ0+YKJwv/hwplALvUK/Lcr6aV+uLSOt+8SLrM8y7i6iBjsuC7V/GDOURY2HSdCFuE1c+0bwkdvxoan4HhmumQjT7DxFs0NM+l1IupPET09B6KOXTv+vXoIDEZ8hTWJaJUKj/0aOn5Dh/L/7TK6M+Luv7nFsWyNuJD4fc4LwTxYfw2DHtqrBOv/y6WxLPwhvgWBDWK1oUyva1YqOTDBWtpRlwBvL4wyaoR00Q2rFDrXiFWMzu9aG6sCvti1WK7apFduJnBmj10L45MelfP5BpL9oIR42BgFrZxPaXxHLt5BNbRus3w1hsUb+FgercL6xnZmboWxTg88ayivxYL2h7GDfxLBEw+1iRFzxAfLbDSitzKH9D1S0eQp6R4RpUyu2lMZDW0qywJSJ7g6QcsoJHg2li7PrILKkPq40pLRXTdmpHRDLPjEYItNdsw/Sy6IZgWblRmlsatpFsp8arGen9OiQUpwENImzxdLYhD1DzxP/OJM0SpHDB6e7OVgWxBCrXGpF/Uu2BmAnmgPir3g26pyARaviI+vxkVvFM5NZN6mgS4gzhlInfjbZdAPcDJhVKhjcScuvXDw4k7q0dSIbtYgI/gAiGEqXkE4UbK0hD7Jx7vSvkxRwJw6ky7wb/8rgNmXbN55ljjGe/oI9FNJfsAMn/YXB4u3ykvg8h1iXjzhc+XsS/dbs8dCzJcQFY6lNLb06eO2kowFlnkCTckhg2ooIF6LK2DbznokPzBnTU5jaxhGtTND614Jbfe8E2mgLIQFdaDHEcmuNtKsEt8Vou9oWn55D7fUFvWzlmawhgKqLvUU7kKoTfqLECtt9nzFaS6C/KlfrN2PS9ClIZxQTPuo4cqnvpaIs7rbQy75gW/YbuRwbpgZfgc9psJ7zt2MOForX3wcqR5d1uZ0vG6zLH7+P41X+efoROEBJ4t74GcbdXXMr9YR+F+F3vvyN8b+D/mL8l2ihTm2Xr5E2VdqSh7BZB31tAWISciTtpU0GeNDEXIOv6DdAmP6IN/02ez+NxPN4w96IWQk2YVZofCrqwYGDHVS1L0R7Q5s2otJW6S0hOmsvNrCpNkfkyZbEuIfrvreEdApfqKsEi4dotCtimsErdmIF7chYQZDvCnUsHwiXKlSVBSQGumsRKSmXUO2feAlth0xH3P5rERB0E5F5qfjtFJqYJTQx6H53qvsJhMURRQVbeqYbMuPiaHZRxSz7GmlspMkr1MXBcw0qbRk8Ko1BIJrZetyMQ8YnlL3Eib9wCuCGlYCFE1+ezGoSuIMo9MHBiBei8PhgM3chbdcCWmm5n0NK3glph8vqxOzMfaRAKysslQDW5chNVq9O0WZCQW9SyxoQyLg0J9txdq+471SSzTO8v2SCI1isFOpFPNSSKWxkiiZyG908yS7tZMEWEnsZNttd22kz7yXS95ps0sGYA0M42moqx0vmyoh/6cEF51dGauqlvZZK5gQF7OIWHveSDN+wT29KGqbUc3/RWSOwjwSPR81o0kGIJs3zr3Yo04j1SXHFEnO4X51Wv6J3+RVPdJpf2YuEfHt7joLhBhv0Iu1RWGLj885Xf+b4dgGOkWlfa4AjsBOSar001GqN+ldJFPArXuU+bb1TL9UaAxeiKzN02TMnoUthKLPEutVFtCQsTGqPhRqe7mBq4JTCwAXlpQw5NfSPXJnot1mn/TzYpH9wOZSBCk+5titirF5IFLkKTlfioZPwlGQ0xADt72DHiGnVQvATDt9b3Z+zIYFAwAxeKuMON+/lfduZATscSmTpEbJYnRVjwEmwENEYcuYEXfZQQg55SVgNOVO4v1eYDa8z/WIP9GKckI7HHwA2o/W5yz/JTYdolJqoNMhiQzrgsW/Tfv3tIq0j5Rk2qPqcIT2+/RGp6q7letmDw2OF7dU2bOistEWgGD/zsEyWE8bFbLpIhUdUzq77B/azd4ssXfwVsflCnzznolVBivhGuqSRhigs41gZUGl6AhhPSI/CpmVIbJZ2PpZe5JOph+lNqeC9Ir6CSht6fsKWGXkIZHsYUPak1kQP+GNeqmXWdDXo0ccSK7BsLgD4LFdDHnHNjTTszWIlWmV5LcqGFj54fuXP0jWrVUSvtgwwEOtbxUq6Nt084c0n/GcYqGkC1mcvf0yrmCHfwTW/M4Wue+4kVtYXdCEtTPQ6LbZTH8W+yaOY5A0lge5/l76o1lA+1CeI63qISGN1JDajVC9KbXCYxbbKYh/w+C0qEldiOINt+jBYbqJ7s602uj/oVYbSAFwzax7MSzfeQJ9d5dTv4Ip/lLHiaj5h60VHpgUmjbG+xsRYp4bfhCnmzeulSebnc4DXKGfnnfPp2XnzfB8bNn45Ns17zRRFVdOVPBEUp2D5iV4bMU8FZj/Ephb25DsQBqNTXOL9M9iSYDXH0UTlxLrhbwP/9WqQVvExS0D25kghpdeknIpeSTkMl/6+NqB4v7+il1gQP0bCCHTcgQ/Y4KIS40ojGMY9D562kl+wz8ovPjplwFV61h/PQioEgcHGteVBSWN73DU/ZoeEFu+mER5LKm9nIb2rMdg9yMYDTQKn7uPz6l/LsYZRWhT8PclxjqlQpzCNodj1xjkjcE55h2RqaU45lEjKLj21iya7BH7YG3fBhiJKFufQTpGAXXHfNyx4nxazM+J7t0ur0g1XSzw0Z92uxTRud1/FZ7bsKk5D0Ne2PUc6WIlHpvFswr8y7DTWwsL5E7jCrnXqZWx4WaKtI92Hbv98TRIQs1F7WC82WcUC6iXst3z4SayiTYZZFZKA/a017D1eSZMo5lOFERjXZ3yTjwZe7BmNL5n+IVE6t1tdNdsWHcLmQqk769emRmK/zikErtXmLGTlS+5l112f2sueGn2Wj6iU2ys94r3fsaiSsJCUBpeUUGf2UD8taV8NOlc9u3eUB/xZfHmk3Vb9QEJ607SKOnYCTlQ/0AtH/2/DkGKnQTOxxzEu1bFeI3o7Fgo8QYl3jDe58Qw9aYUc3sl8MnyW1uai6UTkveLzE/BJZjWl7DrdC0r8/mIeL8lLx9ILRiihPCEeLOTJq8MuBOv3bSD9DWMsr8/vz+uTrthPIDqlMT8Jh4In3jeM6l/CndpW/UvkBoKL57WFsIhvhKVhz8ZdHMuSY9x/b/rnuvTP71gNjRqTcitDzemWxPr3DctprGN+nyH2jslIIQj/iK0bZSZAx+AGfXil+RqOHOHexadtDNFXcZCaeflK+DFgZ+gQlf3yiwCN2RGOP8mtXfchcQClU7/hkkO29p7sHaqBim/3KMgAd0h3ie6/nQKS3u4vWjypQ9xCDYiR6K7V/JSM5vW+yzT/4geZzc/IaL7s3zRP7aoZ7f6eahY/uxI+FIv+Zh79/QYnHfrNXO3NGTbkCyK1mO5Agij+Hy8rSO44uFm+RzhlLVaIn1P7TL68S7DQxF3XOsTBbnZUuVL77qN8RsH3jXAhs0FxqLrPDDSAs33mSb7Vuxsu6d39Vu+MiwLc6aOteE5R+ddTKY+af1XRFZepaOLFFV2TrkhS1nPxPsMip+UVxv3O9BhIPAttEx7KIkZ4HoMmRa/yP4fsgMrASgcUh4eTZmgsPlufkP3KQtoyh0O/CKSKJVPyWU3qFw4rK+8oZTPCAfE8lU3FDZfLoKtC6a01knO9fEKLPdVv4/77lu8Bi0O0QMqrJXMaz36YtIBSJsbLnOZ85iwuTyUzxO4mrelASQ8bi12ZQTnS9cVlreosFxhiwPxIvos3Mw7hFSctUvGzDUQY+ZW59Nv6/jQWvPYETCAR9o8J3moNnFjyVya1kHk5ny6B7z5aFqfS7ur1U2gKxIWrWSwZnz3s99KtsXDk3vtQEoxlyNf7DH0octN+vc8E/rw/5Q5HXZVn+MkqljHYh9hVtwRsa8UosC0SIsU/3GcNPhr0bwJgPgCi4Xmr5kgTmX6NoRRu3CfxPArohUyv3HIxaMxZc/kK8RrVJE5QxSmvGZOuIzRBn4PNBtT9uQzq9n+QlJFJMkDuUWkfdWsDSrHc5KUynGj9zZTYLKa+L9Po/kN+INwXxOHV+MCKjPyfkswtWjLCM9KkvDxFf+IXfsCZK1ems1XQlSuDAlcvN3eCnqU0U9bR6riRcD3G/P3415eerq7/zDDEkZGZp6utn6VPV5/+dQba4dS6RzAb73jlJgJlVGpTY7uTOKKE8GM6b0oT8vZ0UMf5vyWl6/Z/Ssb6lBy9B+UxXi+rWCRgJdj+xqYs6c9YHXPlRPPp3zwlDM/tT4acNaTRsVtir9LGayjt1py3UZlyaCM/ucKa6r3wEBGNQ86y8JTwypOj1+naH+uN6v5YIvph/NVHLS4QXqcGO/2xbmWgP9Yl422pnLum1ZaCPJpifctIzVMd6jA43pS+qZ0DszpJfKM57U1tv+EC+tBqONWtLopEjNsKlhZ4WPJG8FA6jmdS/NUWPm9oYNsnzgD2VuaESan1BTmXvbIXManTKllzrRByiJs4OMmVo3yDNrRAX3QlW+8s3ZTd5mnB3f9XFrRuNNPIbqZBsOl+eTZNAqfsKgQX6q2nJwTM7NeD7e7XQ227ujyDd4Ujq5CBhqvlKC9uWkZz9bx0gWhtfN1zII3XhvNCDXayVyrs2aZXaqgtw7DdKya6zmIRlsRD3SWQ8Dmhp9IV3yT70UnlGbC3feRZw8rw4K9IyJydEPtrtoLISOaViw9h/kCneaP2tFFaCiVNsiCSpSGEjpdZOidV5kTE0/9p8p6LGL8F6pP6xtQSlNtpuyRY+i3e/Lq1izTlSOuwkzrsfsq0aYllg0lq3ae7rePgBYMl7a0engbrLbG0dxJMnuTVab87x2ZdIBXuELqujp2Hx667BqkR8YGdNacNfEXr+j6gt0t+G7EYbpHxWhMHozvFkEKW0ZEEh+h/oDazSN3ERqdsDg12fhPOZCdqT7Th8Z9A8NozoMSwtqmd/vg+i/h2h0sWExnVfw1SstPmrvkpH4tKp00aB2CkMfwaJusJs69TzL5eS31NfeWjMwHUQoshmqctcZAIzqmkirUBCJaNh5wllTlwSGyVh+oQxittUnMtys2cLr0wg2PSFBdpo7BYDhg/6E5NqyRQmdDYShAMBjf2ysz5o+/68H700IKQsihgORyJT41OGunIgelZgUDwbrZSUip7L006Vek1Rq6GhYi7GS9rWpxx5Ap7OHJtTkOs+cgoFfMzboK7ZhNv6Hst/hEva1kMJATrnMgIT9KUvdbBbGYGP3nkw2eMWqjDF2rzERMJ9duDCXuoN7AnRuMQaKZ/90NFDTRHi7Qy4Svrqhxlf0cLdftCnYsBYU+iKcSf//5qBjTIh8dyrURilnOpjBJpFnknmLWsloRValHWVFNmGP+eITetLLpbHUYTJ75N8sAdGHhc3U0LU9KvCI9OytQj2S+ZKBySkNnFJHqNnMctcjMckWKvPIfEePTxl1vrkcjl1nrSEphdKa+zB/ptUB6IaCxSi5f1LzbCYY4QjIf62dY3LZepqOmKlDd8eUb4BcyqcnuS+wvWHGddG5e2953oNNWOEZpH6gWw0yB/rxFeQn9MT5jIEOkfntC+u05+8eCIVJS/MegsW+LgVSD6Pk7rPG2WzvNqB3Se9j+iPf0aCDfS1Gz6lt3XmUy5axVyjKlyjIqn3Ou+Ypab2pk0faIj4h4FugZEyggWLMaP3etiCTYuKb2ybwlif3xDTo2FmmZxx29Rb0XZEOhR+Ycz/GQqXbyXbGJWBFIP9koKZ1cUMTzjI9vDJrUdOAJnoA6adQTQTUWfx8gR/g4y/dK+UIewVlp+S5e+UHtM6bD8ShI91Ik2Fzqx8V1LPympjnkZ7GhI5mReh1arH/DSgvYuhlAOLuixNhwXR0sb4VXL01ksS1h7iGTJQ4n3YFPQNkGrX7qUJBZ2eTGi3+HxMUWCh7O2ni8RT73nK0lDX1IaFjeNQiIk/rTnUdVVeMU0UhQRkVr0ujiS8uYdyIkb2V+WmjOiHvOa97STX04aCOnI9fFyHlM5goEQwpzCmO5/fCP7lD3+ZShF+zN0/T2D4M4kle0qAYtwhDVtDe1DErvzsFS2x/Fx+6wMgVoclTSHbLo/6MplH6r3siWk6y066RDzqXJx02BM0YlDoJPZdfshc9w9KBMSAxvQcuhxg1ZEYLHUP+pjHIPgKyaNQKx48V2AY17OxEdyqBbbCcu1fh3b96IZ9r1pR6V9LzrYWF0E096HL7Fp77D2pyVSEHhuIbfQ6366YQbMieeiQ00JRaLxEAWH2cZ1txfRUIJEGeUK2kfzIhBV4HjNirX458FTsCNJ6XpXh9nsmMC+6BXEIPIYxWg2nwo6kWgF/iCKCJyKeplQTepBGq4rvyQzHhREJ2tKmz7BWAsf7L0jUsSz0qrcxNwDdkPglHKEPu+xivOW6dE9rj9lA971IdQX8YuBLMysghpW14eJGDcQDg+u4mNQDlo4zvNNlk6ducooGorhkpofM2fpJTBi2Yn3j2A0OrVN63g10PY0yniNgeLnjEjZAh/Lg3NmG0y038y5WJAhoX0LAkily4QUOokmOZEETbHo/qDPKDWTcKTp4OeHQAfbJB3IdL471IrtakVdY7CeTb1vIOMFk8PtIAd3zQWTZZrm9QlHLLapBtsl56QNmMljm2h8kcljn7+i011Tk+othOzV0qOhhrf6To6AN/XJKDCMBqQ1yuhXaHVOqrA8xidU/wkmvxwLrBiA7Ntzo0NLAevrgWV7agULaTnKd7RYJ93utbHpi8Ti26a8f4WHBzPCADd7xdoBkK+VW6i3PNs8FOKaInO2ZQqTtm5p9H9zALs2iPvbTnHI7xWG0iEldgRb/4BhLhvctWBy+q951rfL8dNv46W0L2Pc/v4uyK40TKMm7A8jVWU7IrtyWFnvND0qzymNEAw20Qdt3Cd1o8elbvSsL7hZU1pYPXrKF3yczxY2G8rjYnQFmxr+e0kfFIEMYQAAwSNxTh1rk44rHWEGQDIguTWItzf2sabxKdxfJe295UkapfD1EeHhjANEdOlDFuiswUpenTVYv/hbH2ARWjm7UodcU51pcg11lVjklxGtHJ7EoFCMhdRqhO+zCm/NdpqJtWxsZAJqVSu2kuRI+7O/goPCG7RQW2lpufiv70AtaDChCh5DWN1oLb80dcXFcGC0lArSAGpVRdYoReQYRdIZ965EU5doBVIpqMzJUAteWAZsmy00xSHGyZiLlcj7GOugJgZJ5yHeWYaYDJFV0KtIzWwiNXOvVDNLpZqZxlXtJCl1kIVcpBdRC4Umy9hxyOLFZij4ytxMsV9Ttuu3aFWIYUjxw2sinATRZHzfOHRZxtecPbujrsqa3Tf/wqeTJxEWeKbn1D8No26hHfGAq+puPkAscKxDAhuw8flx+OMEW8QqvHRGimGqcl4Ma2WviVrVQf38LthhYJ8yWKvY3PN5Zh8d8FAwci+G9vrDQXmSxzYIErwfP5hkit3KukVbyp5Yqiptcs8nQX8fzr0OuGsQaAzfqE4XWnPX3IayMxz4iQzzcBZuQvoapxpq0kItHHVkLB6v9apKJyTFz2wWmMwBMeKgeWrDo90hudRIaIOkQYHdSEjtVXZrQlbJInfwQpRnPHcPSRoZRz7FQ3CKdID2AHFWgZd9JwcgA8pJv6Vy0JLi/SXs7rOTWrGroe1qaAfw3+Xi2M6RTpv7edo7tVh7Jqh38X6qNLArOiLQCEQUyGImAmDxfi2/pKSEMaNY1wx2QgDPkFRXWxJIrMnmroVjfPEZ07AlwaOGltIsi7u7+oyemWjdXo6HHXbL/gWq7bk+x7o0x+GBDFf9O11Z4+DD5ev1rMO3ifl0BUCej6IYkjYGfMKQWKrX99qSEtUn42y3Mo8e3LskKY+/rdkZgSLlPDncRczNJWjkVjQBfUalPYPxsNcrj24GsqDWS0rBPYbSTs3NRf/yTT1O5tqNvwp2E4/VvcB5ykid9YXqqcTUEi3U4AvVlcCvp9lQ6gC1xN5LsfbiM36lw117jhZXzyf0j+jbf8rQ9gROyMAcU5B/tZW+7YqlS+l7aNuh9WXiORLRAlIpcIJEj9exRSqjyssvUjnkXPycTy8WcM0/zah5aWt6L+8w0yrsiw5q/C7OGXJM75Bh5VgZDA6G3apDBFf1GdTob+RKpuqkfO9CZcACOhGtqv4zb9lVg7VlRerPobzqlWJ75ymZ7KG55lND5udlh4kvTUhyooRWsacsaZSbSHKMsmQcDltQjYCT40Sq1v2c9H2ZGYHP7jf816cZp0HG63Up36LHUoYttqYMyx6rlNj9uDjYSWL3W8SOJLDpQ2BzrRdySeSWelCvTRw/dkqiidnoU+TelXGGGUTTlq3pxovEtrCUrE+8beq/HMjbJO4bz2Kr+Jxst262Y6SZqVMEvnveqP7l9Bw+DJ2BP435K+lxCgaderIKmDriG29LbGTLED6aer1qNtTEzT+61BD+HPj7ASqSkUQX9YprqEHLHL7pR5cEG2XBZ3jMJC+A54LCBx/qvo5K29IxtB7nwlmhkmUArKL7cJZkaHe5ziF5nD3WpdvtsW6crILYSsXAhYyLVosUef5NE0HRCyM4Tbnlh+ehOqaCEtjRXBmXeaOIbgx7HjWrcwsb5xZhmPQr+Eb114psdFMfqG3CbXgAsB+a0ForHaVGuJA4yAEx/F6SfWRPxJePWRZThCVjxC5CcV9rAVNwDA4KPmWG5bPx6KX90mmp+vf4CFv089pGblnFJNqHfGd2gYeIbx0S2QHwhtHdJ4npmzIzTJrqzMfAVcGUTqt7FoQ453wucsFVOEmXf1DqoGeP9hnXVJyPfxd959Rsbe/1sQI6VjvApowi2uaqOROkTbtdGViCMpF7OH7uOMpdIarezIoIpLWoyayCH1PZHlhNSsXbj51ni0u91i82HcUOP4c2d1KrXUgIBEH8m9RZbB3KYLBN8dBrJAl/QSX6VhqKj+kzuYGnzFh+0OvRt1JuBuMZv7E1Okqs/D0yHWitWoeYRBXASqrnl4qi17g/f6T2sVDFJOqB8Jzn1bJqO1SycZ00Pk+ew0Itj8fDnFURsNNiVB2xlXg=
*/