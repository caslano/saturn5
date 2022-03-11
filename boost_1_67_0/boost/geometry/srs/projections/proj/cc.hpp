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

#ifndef BOOST_GEOMETRY_PROJECTIONS_CC_HPP
#define BOOST_GEOMETRY_PROJECTIONS_CC_HPP

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
    namespace detail { namespace cc
    {

            static const double epsilon10 = 1.e-10;
            
            template <typename T, typename Parameters>
            struct base_cc_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T half_pi = detail::half_pi<T>();

                    if (fabs(fabs(lp_lat) - half_pi) <= epsilon10) {
                        BOOST_THROW_EXCEPTION( projection_exception(error_tolerance_condition) );
                    }
                    xy_x = lp_lon;
                    xy_y = tan(lp_lat);
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    lp_lat = atan(xy_y);
                    lp_lon = xy_x;
                }

                static inline std::string get_name()
                {
                    return "cc_spheroid";
                }

            };

            // Central Cylindrical
            template <typename Parameters>
            inline void setup_cc(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::cc
    #endif // doxygen

    /*!
        \brief Central Cylindrical projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Spheroid
        \par Example
        \image html ex_cc.gif
    */
    template <typename T, typename Parameters>
    struct cc_spheroid : public detail::cc::base_cc_spheroid<T, Parameters>
    {
        template <typename Params>
        inline cc_spheroid(Params const& , Parameters & par)
        {
            detail::cc::setup_cc(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_cc, cc_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(cc_entry, cc_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(cc_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(cc, cc_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_CC_HPP


/* cc.hpp
uWLxHoUZkCUWJ6kf2/UDp0Ej3DYpVyRgqaMPOG1lyYFeSQP9mjXQi61VwZRpNGXWyN7BxG9YkRiP4hg+B0naCFeNnrp4+ErFb2yyqWlCPmC5rB+4f1Bg9XdcuTd2VfKBwUCN4Wy60TbdqXaUi0PfZoTnpWWSQYVPoM/902w7a5hbWIN+p6o+kh5jKMm6lWlVEbEU973EI5xYF6/8up9/R67GFC5OrKZ7k8LOCc0sVM+rDqsAHvnyE6nRpu2KfJqsW63JmgxfdWtjeGnKUqLPbCDJJCbvHyooyMsemn3yB8mGOUUMFApEshuY0Oabeg0YYOtlV3/F94LXcI/vS7T/T1VZLpbEtJA8D040nIyGkp/8Jrm/4UrMvqBBt3aVeCoHSGOvV19St6+yxP9a5C5Rn50FOrLEN7so7J9Cx8MHqV0ygfpyvdWXq5J9KZFZNSrje6I3ncmPQD46+M3p03gNtfafVmv3YN5SDR6qSe27o6iAblZ/gyrc4OffkesSHW2kjlLdoDsECfL6W06DaqBI1euJPny2/Ku/7onU3o1WB65PkiKV8mXFIh5S8rs+bA3Jqb7rtcsHD6vCRLvIEVOz5VSi/fHU/t1W+8Vpo3t8UWp0XcnRYXLzrNFdqUZnTobzwyMuWepLDavT6occt/zL5BVzOsF6ZW7qO774nAU6itHslv9c9pX7G1tuntVI2blb7iFq4/8AAAD//6y9D3wU1bU4vptdkgWCu0CQKFFjDYgGLRpU1kUNhglRWNwQkgUlgbao6RZfY5nRWLKBdJLAeJmIghZbSvFJLG3tEwpqfCAGQkkQhKCpBok17Uvbm7fxGSSEBQLzPefc2T8BfL++z+fH58Nm5v4999xzz7977h1us1gqPs8y3HtSEy2WyltqjPLveug5eDOrTYG/LLnBUBzMaqydZ7VYZorMis/UOSnGopLifXYLL3nhtHGYGYWsJ199fMBSkHWiyO9+lUPLld+vOVG+1EPPwSWsqgv+spQN7D/zEuDhJzPU7zss+kzD06sMy2rM9oQrbdqDjpr+crfnTPAu9rMZWGquj9m36XYfKxzQZyQkaNKAR3KsGJ0jWq3YBBUXlTx2EADJagyd5sfqAJisRncV9T+hprH8Vg89B7/DXhT9/0z9/gyL+v1sS7bIqfhcfW03/LU0da+D2jQStWfKa2uSU11Zf4IOmeQoKGLH9WXpRZrEjTGbx4921TQ6ayoAIX49eLge/jGFq9Jhu/pUm109kKoHeyBNl3p89dHi1WlQnHk5onIN9JbVD415Djirp0C6etTQgh1asEsLdrp3IFTOOixf0+9c/RoU9og0/WV4ZiqNw77NI3HFpikdauNSX6QbZbhb6gpCapemdOaKahXvManD0+ys/hBqu4Ndzuq99NDprG7AtqGCxGwBS8DKDhm+aQjrZuwHhnRgaVGsZSYddic69WrMiy+unAgt4/P104ZH6qz8IWVZzCz5UWhFr1zqj7biYFKbO1eunD6onPKX0GSWk67yBLfUE8SeMgF5AWtoNJs1kUl96t4Ez97KEZlSmw/qjIZac6ctYt6BkqyPHuNFa+0WJABmFLGT6h4cskWxZzWWNLFanNiaxkoHuxpag0pmduUEVktYnMyO8BuexDKyQ69FdJQ0QQ9H+NGn8ZFXrYkQt9qTEiOJAnZc3RXtKOQv8oeGxw0I5l/fsRTI91IqkD9nKlbLK5/joYdgLmMEyJQq6PTlJwiSMQKSRSUwQhyg8gIMsAnyPQHK/wc8TobHPB88TABAQ228nRGgRX52Epczkf/NsJwneug5mG4OOLmBB36GrSjDZ4qsiuNZjYtgqK+wyFAHNTLh8kaQIUA7635GDEGsIZMZ5GMjgYUNK94f5eLX46RIjiyDndSU3Zq0QQvuVMND5RQ1PELOU8Ppco4aznjmHjU88dk7m6WNafNTXFpwsxZ8Uwtu1YJbdGkjjFALDvDHDcNwB7co31W9A4bu3cgLUgeMrMbu38Ia4YmQ6WmWe5nLz1qMl6ZBGnCFbh3X2xHOLxqGJm3zNCuLsxo1qQGacdZdtCAKyh/ySFuCM5h3s26vYqnMhpNXDghO1ZfBGm6l2WuNm72RTGrIhjagWkVj93vQiFa8s3s7/OXznz8NS7ih6oAdutWDjVS3MVKXKbvPtI87UXUAiUIPdlJupy9nUHaj7m3Iz/YVGMo29UC62uNiA1hsY73PUDbU8+kTBmAgOwEEdf9EAOY+NXxRvk0NG4hPq+xUwwnKLcy7m3svGEYoDZ7YyKwTsJo3AEUXAO0DiULupwOIj50RRA4bO2Cw4E6mbPNcdFbvB2RlnfCcd1b/Gp6YtJutboTp9RySEwt45q0DhueUPI4lFsCslJRpJUuNtdWI5UR2xFibik9JWf25Reyo9myZmZXEjppZB/iLjXYLrVNaTpPil1OxA4jurP5sapEWbIux2H3Ia2ZOUssdFmW0aCvDStQ75EapPZTULLVbEftpD50xDKUdKKAASSAFJcdoH7KJyYIXA4NuY6OJNXeYr5rUznInsezJpRl2mBRvR75R1scO+Yy5pczbBUwHWFCmtyNz76uZ+46F1bA9aAvY5wcsZ9p9uKaNMS0ApCr12kQrbHQgQ/f2xBpBeIiiJsMyXkSc6k0W4VSXy5jkAsBA0OHTpMPsOButA6vTgq3GS1OInN1SmzLULbU7q38H4wXyLIoh6RVMoVGynEn1zHuYjST6FQONjE/pKALQ/m+jY1KPTeoDXEEh1sIOUNljZzNbmMQ1b4/tiObtY952tfGiBniA1FbNG9aVHhbGrkNOWHBJ2ky7NtOhzUxmzVE8bHke8ZAsODagD+dXXqE29CFz8cvX8vfOApLmTGLhzPcobUwqQOMJVzyKie8hSfavSgAILPfTg1+rnEbE58uGBTFM0GEYaWbOJBAeCQELX9wHdHyUT/0CJLsLRBZQhwwYLR0CP8ivjWfTjTHbJox2LSrZ57AE7A1pe4Bznd8N/QPT6m1OlA+muFgtMrkso1kacBDnqLyrxnCu/gal5x4hmf+BvRJ31O0NDLn0ULO/ufYIkzwUVbSo+g6qju9O/TdUHRWuK1YnpeuQXueCvwekgSReMBqWb519CL0m8t8/dQFewzZ6HcI30muneLXziv824PWweLXxSVR3XgK9JvA9vdBpXY+FXq38LXydMwWeLfzLfYjKyWq3iz/4QJ/BdwNamvhTNTGZCFSbdQIwVTzg3kTiYpofdD6/h16Cj5hCZ9oGFBm4fH3T3NLAihGxV6D9HFG64gBIdId6YHKRLvX5eL4XZizbjkJen+FIIhWPf1Md0zWBgYFadjLrhNmzF3suNHv2RntWP0Bt06JkqMEBQ6Gej/D7DWSC8D7AkjAFIMlAlTYCytuL1LoWJDyhWvKfRvuFVWooyews1lqFSNNfwF9jbbkVBWMyW4WIhVz9BXqg9EElfZOAfd0uypmFKGkc1j4KNeEv/PK7vzYMH5DuKvgLKm4xkKeQzljuJJa48E/DgIrjMeEIJti+xgR5lKG4mAtTW7C5uSmhBNCGimnBQQNm+5/+DxV2YjkXDgdoLTVkU1uMaFfEl9lJd4lDfpLV0rJbKZbdEK3EESrwB6zc6AWRYcCrqS9kgL4wydQXMqJKB7MWGL7FkYXQsajmhJzMPzltt4Qc/Dr1tAG9arW41HGgJoOEnvmPQFr1Sw6rnFTEry44bSxgB0qKYxw0PU6GgIqODJTU9GBnjD2Oglbd6n74lZPYIX7XV4bhh7/vgJTMOuhmtHyrv0KJoeIIGY1Q8wKD69pqk0HEdKGIcTOkh6ALq86GJjQV36EBb5cccDNsXvk+rG/SCitzAAmPeOg5ONNU2Kc0ZDWSgFA6NakHGKYm9WlSWPCvPJaIaifhiKpVvK/OSjFU6tXo/ivqOaerYEXkOjIT3TkpMGezUj2zMpzVB6wR7q/lpLCcjHpV6gE7pM/ODmk5qbz3G5TjyO01qctDQK94MDruumdRmh4sf91D78FfRoyL1WwtLpuHpzdnO3D4mm+GKFJxrDsHKVptI83aWXczyqd+eFqdCU/NEsfihtIFePrnSaQwmAGssA4reL5xVmsWYddMQrXtG6eeAX8Za6Vut4NSttTUjJewXQKWVQ97vglOUYPc4lxzBtWSQu6h1pw6KndqxXa7oaSw1QjwQ7mGxE2YQ04xCJY342HPh0H7dC1vBmZ7dlDlOj92fIgfAShDS7KMrI/VI8ZM9zrTcv3Yufp5aN2zTvD3SuxYICd5LavCdjOnz8jzNFfY2Tcs/KAoV9EC5uuEiLX2cKyOfZuRPUNg5Vgvrbs6oAOhH2SbSIO8m/8B44GByosFMUK5IrU83SL79B326EQPNinGCVPjClnKtaaY03PSfaJBo8wUd1FZnKoKnSSQ0fAAir4fvkNKe8Te7YgtpHFIhH984AwIUlM5rQddtYO11BsvuRJQSwGVSpPamqXWN18b7YpAjMourE/Ud68AdEQVjgGdDR2LdCDlzgRV6rKpT/EE9akeOxY0xlSkj3b5dG8rf3ZZv8G8Haij8wf+rd8wtUGYyn5zHU70nKn4sZiO4JNiKgBi3b6NoUvDNyNiIbe7g+0gcb0dft7/VL+BZRgyazTWOyyiEkNWHUkQ6nOrOVRe/Gi/wf/4Nqm33FsZFVL5wJUUhx+QmTvZp8+azEMP9eEa1nIcLDdZy0lGnA24Sb1wvvAFKQE4TRpNFlgB+vJ0oa469FlTmFUvmjLXWNuC5XLTtJw0luvSckA92U918FdXUQvwCWWAdz4JioCKaoJPaAv8CKQEDCAJhvoA3/jaOUOvPUxVRMqTQIKRweuv4F+zxwgC9Ffw71ztl6jViyztlysxqzYjEcHAX1Y7MREtWE3FvyREmTQAq/tZDw02+GNWJwR0FSkCLtbCC34G04k2HHBFY24y84ar9jYQHFXN+NdvjjyWDimtNDthnaG2Yzzt4H3jQWSgQj0geqpY1b0V1iF/twItU0vDS88AkY/bAfCcBcuCASNdSWx/A7J9kK0O9b+s/OkPiLlVr4fWm3PTLJbJFpBYN4vHbKG6ZOtzUoCSh6tz0oaVtoOWGLqhdMky+JNqWiwgO3LTEqAqFCxtgQK8OA9mHzIbJ6Pl/uXMPkNtdvh1Kbl0N2T7mnNTx6M1U/Q8ZOxPRm+aT5+TzN+BgsybrO7t5bvu6gO7N5vfCQNAfdXS4KmD8cz6I4znONnaYOgOadh9Py4RpDeoyh9+4bQBC8bBn7oHGsqZzPL6wKiuOVh5L4ipeZ6zK3xPqNPKJyjpAasfKxU9S8U85X3BEc537eVU945bT5t1Z3rOVhyIUGQAcOZL0ef08nQAjf/ij7QGSv2WpJX8/pOnAOX2hmtOAIhbt9vR56X0urdvQ31sFCh7pQgnf3I2dCc5QtPZdDSkVO7y8SaAVG10LQAxGZige3s1ZYA/kAkQKL3qgd4i/jqOJOhYAGXAFk3ir0+B92Y+TnQfcDTIyMumbEc1HhU7U53LMvTcdJ+2h9ZLpV2rdDTnJpN8q0zTKl1aZaoxxoHcUXKQUqXRauQvkzGcyrxpgF2756icrNXmgVGl1c22I0GmMynDcxRymiGnbh6sM612PvwyCfhsiibWRR2uBE/zM6l+v1idPr5av4AKXKK2J7ZmIiVo0fInoiUw7zh337dlRqpLHv7FkI3w94vinpDti8KeL6Sez7u/7OzfP2P5/Wow1aVcowbTXMpoSBdd5ed/kZbBU4sugHRJT8fsjHQzG/sR2WcLLxh+fc7kwDDtmcX86ZsB2+2eLyuK9Bwr2IQOIMXJfPhtkIr2ARvpB/t0AJRLVNqBGyJ1XpfVZxQAOVPRtZlIdXMmg9FENnrvjCgVn74TZreOLDvtHWQj2jvIQJprffBL07GnAWdoD7rveO42mNT0qG226K1BthnonpXpWmWGVjlRq5zES9aIXnkVUATAid6jjz9H+ydm4Zww4u2fzfDaTCxwEvqf9rRSzx30206/qC401yKDWXgQS3RRai/99tAvMpo4+2vtygvx1lkVvDbXou1GHq49aOZpe9LpN41+0b7LOpif1ejzZ3081w//2BGo6uB3gpbKDvAcGHMTIOD5rwABJf8BC2wS1OB/nokacYvm7SU54mmRh/A/I7MbjeWjSvSDCQko0tU3VlsQt7Xofm5OnP0hGLZCm25Ihucm9B4GEv4TtKIV0NyLS3FeXiyD30cDtkVZ/bnae43oldS2owtG274af6uq6XcJ/ZbS71r6XU+/FfS7kn5lam83QlCFRlGJAJBZyaLSt7+JLP1+ZMATwCJaCABr96NX0THIain7ncVyuSmk56aCYjBjIikQ17lrESp5jDu3DAyhq4HXGi9VC6+gaQk5TNdD3VrSf+XrUBtYHH1NAr4GCXb1jbWkmNWtH1xs/aXFMAEG1DBR4FGA5gDUs0ZYL3Nk6FmgCp61qtXiAXUJJH69Fl3qKBF+8vFpI868ua91YarL4mdnlcnsEZnf/jtSCDOgaVfzqpUWsVTIfCPHZx6qDL/BdEvJIrT20L9RGrCjXAStbwlgx8c/fee00WQad9dt+16qi3zmRBjyg37jGSi45WYs+Aco6Cu1FIHY8i4HwRxesKDGkK8Hg/Sph8OowI5WP+hDy1oe1jwEG0JgFgnz+iZLgqVEo+YHm3PZhtUSMedmSpeZc75LN13AugebLlmTtrlLlsgOVoskFkpktUhwbATywuNc8EJN2u05JNuPN4YSju9t/xy54XTlOkz64ngo4Yv2z727O4aUzwB58+4v7RYoHYKML9rRSWs86zDGlN0IbD/YyJrHQ9MrnxuSp7ZczJatM9mcSdDIeGBrO3086biBTgm1MTGz2XScJQRtgYT5ICiE8oaK0rSZ2iakcHdJqfI4AK4sBuvOqnt35qOFV8aknZ4mZYi7uEEey+pwQej2PGst1vAEG1bYWLCB1eJq8DRVjrukAKtF4ekJr0hgYebdbavDxJANnb3SNs0BWr1WbheK/QPPomLviOA27xLc+tHL6AOj0HipB3eglpdZWM5S0OBBbclZSmRP1slUmGq7+oOlUGKJRZ+Vyk7qwRbUSfV1bVjoGz3YgBq+t1Mr5PUwRzvMOdpBc3TfoDlSOoCGLpmj72BSZI46zDka/QsgCm8nmHqsV0wUy0nPPKBZtQT+3Sw0QQrQmgKqn0yWOy3cRjkRjSXlCaZwxmhC1N0R5+iZ4/ln2ut9poFE3k0VWdJ7GQ4Yfdiq2KaHhqEPfch7Exy0w2Xkk5mjK1BbZ2ugbH0+mXD1xtrdaAu9cWc8IFMRkGCnriB2mNQOc1HPglxXED31oArnLMVp2aoM8gFPjPdgoP+CHVeXl1q0YJez5maalyUWZ811VoIIaKg9HyeljHnb9WWpLFGTOmsOAi15O+T5EU+31GOjYdtAke5hUjhT6tW8fZlSB1Hsc8ABfaD/k5N3NvAEZosNsx74mRihr4JJfSzYBR2ou5AYwWD+ORo+yxcCPDqRh+rlRoREruUb7kBssHsQF/uJoR01iiZrEheTYJM6yStNMCJg/wfs1+uz7PlgBHUVQXeEezCSDXmYAfNM7pOYi/0h+VvRy46DKpMa3SqVPYytJeeF54g83P10upxYxG++CPz6l8jOPX9xVt8CU+pelu6sTocH6Js7ILt7dALu++5oI8oiJzsObBe+40uW0ZwzjVxGu7B5Z80WRNYO2SpWVNWRlS5rtrF2LaaOLsJNipd6UTQSDeM27R+x5F3Irv0Ba+kCu7DaPxVE7veXeiIpaovVZ6aWStFih/gQ6BHsqa/vgbEw0SptU9qAdQWsvsBklAefGjuQpEUBvmTgNBiKOARYIR2Ao9YJhKOxon1yG0y+2XSoocwyh0+zCeb2MuTOzFz5jFb+mEEr39vu+fTSlZ+GSZGV326u/GtegclrMde81Je5F2jFvQNVCHmcoGuxtK3eXvWpvoRbvGEoELqBqZh4pt0nqO3SbQwwGjO9vYGUfAYroQWWca8YuK+IHxiIoClg5zfji0rzf0Ce5C5Ll29ms0q11SggjR1rCWGYy7cdO2uIR6h18vxpI7od3fw07tYG0ho2oLZ6bb1wpxQn456qJnW49+BYlKSsxm4kgVL84cn3m4pcO+irYF84ivj9/YaB2orxTB65unVvZ75WS2pVsJMiBbgW7GGu0gm41GDNLbZGNZVGZQQ08itTPQmtN5QObrSeNYx3ykiGYCHjHWTypT826YbUA7Qse7aQZWmKbHRenGUvmHrRGPW5dIvsZAdwt1LttPv4mXOArxdMfWg0ZY8485dx/eo/7EX8c8hcZMp3ZG4nuVKP3RMa70Mv1K4hgm/fRE6u6+LITHaJcgW0SQPpnwmwv7Xw+kGFF5U8FtV/RUNQ6h6qeEd8xQwTGrBFhatMy6sQSYGYryymohREm8s64WlyVvfjMp8PDOIry+BFUo1OInexAxQmUir5JkQUPQaMAv7vuxIs3a9bIsjwQ1WQlFDV+MzHs/4Q1bw+ebrfWLDA0ySPZi3NK5NtQuXj+dBY6AlRl4br4xffxEptv4FKm6ASawd17YR8o7GMcjshlzYGxOsxeAUGMSwKE4gEn0ZaM08C0GIbulknFoluCD0FBTGcDFLsoprzVUQCDtTUrz+LreO0lEBGMmUkFncnQTJWDaQ0FP4PLJC1r6E5x+5Ds1uvJQ5kfKbX7jcfcmMMW5kTnckZNJP3x8/kHQLotcTCvJ38+mLAQiL6UHDlYNbKqN+uk8+DXP7Va7H9aPTU3VUxHnnuSA0Kfep8t/0DC1QJuG76ErhqoSPr4E3NnuPyzeq5HHmIeu42JTU/v9SKriNpIH4Fhaao54rkoZ69gAwoNRRKJUCpUDtUhnrzI1m3U5YFs97HCAxykgWmNHyEbOO/NttBRHciz/CBUh6/5I0xU1BqC/sBTTn0OjRLbSRyypMVmxZsE7m0rZRuPmfDc4r5PBkDcbRgh7uyAjc4Ooio2m85g6YKa2dW5gGh7jOUNhBOuG/8890g8nxZJwpKc5BdPGMOFjT9v/4W9yRk9/xSuYSVT/Scl/1gIcy6nyyE2e5fo4UgzyjSvY1cf6zfQG0bdBiteICP//tFo9RAISJ1YhqZ5he+vgjT074a8tMgX8xWI38DqvKCzWTTIrXhKPxirrOwo3EmNjABBOQ=
*/