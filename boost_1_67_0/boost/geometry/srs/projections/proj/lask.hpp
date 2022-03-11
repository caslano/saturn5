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

#ifndef BOOST_GEOMETRY_PROJECTIONS_LASK_HPP
#define BOOST_GEOMETRY_PROJECTIONS_LASK_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace lask
    {

            static const double a10 = 0.975534;
            static const double a12 = -0.119161;
            static const double a32 = -0.0143059;
            static const double a14 = -0.0547009;
            static const double b01 = 1.00384;
            static const double b21 = 0.0802894;
            static const double b03 = 0.0998909;
            static const double b41 = 0.000199025;
            static const double b23 = -0.0285500;
            static const double b05 = -0.0491032;

            template <typename T, typename Parameters>
            struct base_lask_spheroid
            {
                // FORWARD(s_forward)  sphere
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    T l2, p2;

                    l2 = lp_lon * lp_lon;
                    p2 = lp_lat * lp_lat;
                    xy_x = lp_lon * (a10 + p2 * (a12 + l2 * a32 + p2 * a14));
                    xy_y = lp_lat * (b01 + l2 * (b21 + p2 * b23 + l2 * b41) +
                               p2 * (b03 + p2 * b05));
                }

                static inline std::string get_name()
                {
                    return "lask_spheroid";
                }

            };

            // Laskowski
            template <typename Parameters>
            inline void setup_lask(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::lask
    #endif // doxygen

    /*!
        \brief Laskowski projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Miscellaneous
         - Spheroid
         - no inverse
        \par Example
        \image html ex_lask.gif
    */
    template <typename T, typename Parameters>
    struct lask_spheroid : public detail::lask::base_lask_spheroid<T, Parameters>
    {
        template <typename Params>
        inline lask_spheroid(Params const& , Parameters & par)
        {
            detail::lask::setup_lask(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_F(srs::spar::proj_lask, lask_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_F(lask_entry, lask_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(lask_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(lask, lask_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_LASK_HPP


/* lask.hpp
bfzXhQaj/OAmZ/YgDyyhKlD0n44INMR6oCbgBPGKEr31Q3NSBZseFniBYsBaYBbwAjOuZwNO7nxAg14OIinLGcCCixBJFxSrwYRdw28ibJ1CHLS1UNYJ0q7qT6cr5JCe84ZCvdRSbsVZ7mwRkomSbBkR7BR5DO6a5PiOt+XJm7kpLg+sd7sQP8qFCp6xe0ezXvt65qHaXQDzVALeYhNkR3OzuLLjFpneBBKDUBAT/PKNk/gOijKqcgEkQEp3JMrBKbNQJZ084DVw4+QBGT2G8HkXPsobed5GFNXFWO5lS125EmHzJNuR3mZJqhu2NKWSXOT8l8OaiyJsEKtziR/Xniha4ULhSh0vUGiw5OpwJ/6YOGAOKoSA/BlDF+sIpeXm9gLL4hDFTnA5crS7z+f12zsYkTtgZ+KJc5OEUHxlgJow4y+cbFgoMrBNi/nHZF41iN14jUp57y0O1DmMenDq/y2zDxCB0hBRRn8PokhlUYXMWzfcSWAYK/IMS1Xx5RonNiTKciEmKl3jA/ch762hUV6ejU81Nv3maIvDusSnuIiIUquIlMOLb5SrNrA7w8ZGvi7aAEkCk1AvnnD0xu8psuLZFiyLxG9n/IS1U6aJ4gNgKcrkNySyUSrtDsky7q0ClYBTUSB9q5hP8CrVaZSJAiVDx5QNT2hzbEgOnBPm8/iTl1s3mS6j59gtKr40IPnaowmGA+eAP6m1X+uEwGpmT8CEa2lsRMbXHzNGPy7RVHD3Apel7jV7sVknLeRkwOIV0rCgzucEyGXPiPVJk6Mh4iNOUsKyLaEBXegK5fcmzG1BSNZuYg+TyNlnAnHSNjA1gE0YvQcJgmB8sUbDlsPrWDYjBbcQDEsB7z0CZxKdhDlUD2YMfj+HDF/Ek+9JBa20arKJEz8D463sLWj9IJL9g7+jqEb5lscj/Qj/tNpfrG3ZaaZXwUHWgrQgyidOAZ0eKQLiWZxF8lal3XLvGEnyE1LNTCUlhyibQjFeA2+uya/xGBTzNgnPkq3eXIYy7bnnoBHEDLwhnNd1Xcpsi6kqmqAAcWAMoEwpq0OoNQMmeGS3o+1GvscXaAPGCi79ip8Pr/ooHRT1BmN5z8d8C5HdWLrgE6wu6rt7JxDFxQcMRAVZHRNUAA2iPqyhOaevPoY02FaNl97eQBGUAI4n+hGWnChux01ely84QMmM3GJXsiN3ypPowDnaSXJanlonOnaQ09OgP4ZK0KY7vmshMwxMoXbf0zzvb9oILGMHasGHQ3H2G88s1iFwmlCyI3Gil+pgHOelPR5MyKY/LiUuS3ZqSsSmP7bI8MhI0Y7R2Q2MauVnQBaGgS2PN3BMDrlXq9SH/+KkMDrGDADDI54fI86IP02rPcs4BYgEMpEA0d0ZTHsFEH6Ewxra9zAjYWrC41G+mDbMlwNtAX21ENG6kgcM1u4W7GpO6hL0bknpEuR+IXAPfrm2uwG73sHdgt0YEvuLjlz/ojnwduzmqqYO7Oa23WO7ebg5zHm/4Jd38L+q6zpndos57L/6R+R27OrfDmwV0FIn9nI0nsHt/Ki9ue38zj3WgEsYxsq7ErmLGBpcI/GzGFHmjP3zqo/bvbJoKcwUHbCN5cMQt34YrPfBfxhqlxYsgDjwBnQBslzrTDs/Qmyo+DcoyYbXExyELm2qUacg12pnj31L+7vBxq1yMafloTkpxrgcs1uUZEMbyY5BCbapQHzpmkrLXQHn7hpweWnIXpuXmnEXyeE9Owuz/PGN3/L9v0sNocH2kry2nVbavC11qWxp9G2OxRoKMWCWbBKXZczpbnmyDcdHgBKcBGOlTYlZgh2qUHWAldSnXKVbYbRHJNitr5Hcr82yiAc8PLIXJ8BLDOK/gff82y953tCBMdFl82ujcNtPClKtaDyF/cQQSQ3Mo99+Y4aGXiwdn7dbHS/fNsvySaQQYK5U5fbyxnAj8LbVLb12xjXPHRm/5bGQd3LZQgCXKmdUGj7ssecX0SiViLnIddKeSGcTdQT3PJFv4RJIYgWsgxgNKYm2NHw4/5WeVa0JYIEuUi5p6HNGFr9qYZ7XqJG1C9StDKIy+vemqh65UA/ho+aht1JFYQQQPVEcPKg0U+hw7hvnZ3K35ZCdb9dcu+uXSnK4D0azdCBPgGRtRR8JZU2LOcGpm4ihOXe/yCR+HDVROiQq/iAp+RndCKWyTVBK2o4m7v4mgvohuk9hmWoGasPdvCIxRPCFfufBwZBx5C/4CwqUAWwziOqR3fj2S1LQIW+XSkgHtDpIQCR9URYez0NUzVFXD+gLeKYhL39el0c8qk08biD4jiXuSSOEBBu8o5TGBEdi3L3T4VaLb61ZVSQgjZUMI1LeJ6eMpyLpS0bKlwx7KxllpzDgVauDSHwTigIVv3F/9YEfa796ZukIKbNjIg4shZxkO3TAIt+62wwVTihh/4Ak9RCsY8ymxUWvsTOZE+KDzbK2LDS4LgoowAZlUgRz7NZqV7PkrqYFWQc6pOtNhXp5zSD/yO57gUAbbJt4/qJPL5tDNH0ma56ja4mqk+IsLVH73kbRxTFPrIBTeVU+M75tEvyaMkWf2D30iKqX7hRpUpw0KW59kYm5SwukwlbWJB+/fbIgNCp/pRYJdCl7oKm3HvJmNNIiFHq4/cRsh40Vb1QDHTIx4HFmricP70R5XCAHvH1LEuSQN53vW0AzM4bSbr2JjzsGTK+BiygSVHrEjFS5NTMYN9aEYiYvo5nJsLUwKJehP1KP+ADN4URnEScb6PQ7TRlX7/d5CNtc4Fp4nPK544L6Y4OsEEQgQdLYR4JkEnBsa0/vcycMNgOIys8Ad+iDEt6SJd06EviXtRV2BxJEAAk+k6C9arwY9xj5t9DCKAobPJA3jF7taCIWdwFIwBHgyxkhmwWL7S/iARUDJaSTKdoLRvTQy/0uu2Nv0Mi9LZd4+SWcwYR0JGyJ7nbRoNeSdSAO3XJxAUcPdIJWf8oZtfg5xOuDfy2ozL1f6VJaV41zjagvEOkZpDmkMXBjgrWszD/eyNafvOlEz19KIEt+HNaSS05abUzCeHuWF8uRFmj0BC+sMpTKQVfDugzwV0gyVvjBWIDmy4c2WHyF3laQG6B2UjbQA1VxitcXDWmYtrkforPtPiupnDEihATm06KgPoS3fFwenrgt9Iy87pos8AokQSQZE0ROk9juOAb8cisO6v+LwKC9w18gqr8nvJI/kVCJOQLPJAEnASXwpEuhVJUAbvMFnLOsgvED3eMKIA8r9JXT8Js9bkFZtQuMiQPZeKUf9hfShLFbYZDDbLDDgxt3EQBJasS/I6Y10EyUjrdYfOF8Qlzj6632vQmTIF0OI6CBfqgjb8xB/IWljVPsZsL8wu5fByCXN7nvnhLmdGQo8KEJ3gVrx9mjgKpFao6FCjdtgZEDaEfdC4h0mmv1HZe8GSOBT5XEA5yYl6r+FbZx2ciYgg6+zqwNEAF+EIdoevkszIJ0p+V6fqSI84bWHtfJInD8dQYiCiTwJReB6+ef6KHIMjQsOrLONCGXeAk2oSTVDFPy841QzrFY+JkiqRJQgk1KJDzrFnswXn+kRTGiHpx2AXstdOQ0sS0fjCXPXmhrhkvPO7owMHU9o3V+BXLve8T4Rdbof5zZnF7xydFrCjXnsyMMOuhhNlxTQYu09bhBy4HIPdZDmokwDvplwwMDhUkWDUu2azo3oenJRegtW+YOmU1h5GVCG7glFmMQA2OwAi1iRP5v3P/VK7ldPXDdQH/XjLEbaOglM2UqfMZHezK1w+ie9piKyxCS5rhyW+KGk1K9jLAjVKm2hHliJsmJmldill71n9ZkwqdtqYWadcJUqtNbXN7du8wIz/Mzh1JqO3Qx1Vy8uSpl16j6sRV+LxWq71tlytN+VdJaeN3k2l/B5Hm/6sHsr4byrzDN+qDawRxcN9nH/Fb5RXr8lYDd0BV6zEZ0yiTDMuyd+Ekkup+CgxG9R05Vgw+u+lryyb/qZXkk591XJLvDpLY4BZs/2y1RPhbI9RDHcAo9AhhtIRAFeC4IbRA+v7RJm/wUtQmReSmQoCGoxJuWuS+vrzR93cqI1O4IEyaG+sI/2rjy30eY10Uy2kU73OgUmzjgNqDFhsY60hnW2eeahFyxZOfnjwMwuxlVpu94wpQMYJETQxYN1Flv3YhivwcmD/6eWkCXskOHgyU9eFgXOklwOADPExLgL/eo2PasDlBpXe+dCEMkfBBpofZAxGkQhTuMdZC6B4NPb3JAMaAR3pBPAQdeUOY1duYuXcArcHdMkHMIokqEDmEAuVDEL2mmBWkEDQGWYKQchC9wdRwpD10wOfCVb2aA7cA0LOcH7BgmXSg+wX6ADoxZ8mD6bvM8b4D8yOUnD6SZ9r5i5O9u/CA3yH3ZAI3KOw9pJXLuj9gC0yfgDKiLLwP2s/vYrtpbX4AKIBLqNJb8lP8YQJmM2pQoOUD1O/ajPoM2xJfyWOAjpAkUgTGAImgTMCioa9SdiL9AGqDTuSLbsd+gcP4MPF7i5y/ilS3AP+mBn0EsPBj3dxICz4AMQMbPgdxbCBPkkWDJtusDtPP/njVe52fm0+9SAOHBJ7tKdlAEGnI2G+QVAE549nWzbErsT1ucJUonuLZ4m+KyRWlsrvhp1kwZQGqC8lnjGXR7J6oQeazNBZCqIIvvEFdxN1+a59k+9Gmzu/R0yua7lQWRfneD994COJ4RSzHlbwyz7rn04VgOiQWoAXUpopwiwgmmGwARnlH/40/cjANwM3LFhhe18GHLRwZ49gjJDHTmpF12c9kvYAAHNrX0Dvzr9FlQRsRRihIbHwwyjAT84P8ULsREy9H0Ji0V/+MXkAfIAqPgLv6eI6DOOaVftM5C6E6DX2iS9PscShKoCw49oTIsgEYKF4Jrksd/zGb5j0uLBHkGVBEjolnQhkL/K2o9GbV5HmdAV3JLn+wF7F4M4fedwbpN3IPhwtW6GaSXD6sH+i4dvulHQmPow/geS7TrGFgL8owavsltk2teasy6Pl9juxu2/JQf4xd+yTO495ds3hNY0jyr2H6EVbvdsyiqB5VdHo0eKIaof1wWZa7kuBfXPge3lQLt/BtgG8RixYKT6ed6VFvJ5AuaEpPMROovP3QrMvLiZ4eixqr3tG+OfVE+t4dd9vczFRobUYab72XV+I0xs31ICPUMBaa5Ap11Uch+VvgXyRPMGjPgbJAABCacsTxYlT2STP0WTTR4NiYiPpJnp73ddUtxrZDw+S09XhdvRG6W91mYm9Oq8xDKJPFiQFIIAvDLA9VjVHIrfogB531vY66/bgHqmhSr9mRV1WyT4ZpzS+34a1zc/Qv44lWvL7Ie3oKEpC9kxI8gkpTGzxduQqP7xqlbHArceA1OM9KSYAAtC0T45QtLxYRSOwJ9VPvdDzJfwsxVHKpPCVSFvn+P307abU+NWh1NkwENQh1gIC5WmDhJo8x/uglGfHCLiPRxBUFDVYf4FJf4oHRSVc+9eDcnlETz6zZvXVpPW71tmcRnfM/mURwovixxkpKivuv2b1FtCpQMoBt/LyCRTVJ7LHQ7sdk1JCUG+aukWO8OEhk1+KazXZKz89LogurkLE3nb3237WPGAcYE/WEQort7VejozxM+BuqDToWehjuG9uFPoa+PFw6kl547k9uSokwP0AHYAOxAOfIp1kFzslOC8+cRhEhych1PXaM4+VwoH864/O+XsGIYXr2dSA/PcPVYRJOlwKcbZ1WRVWfnFy+snvgMDsYcbURhSOyKymub/ovpHk6XQI5xCno4hfEqZW4i9HpVSAvjBky4JpRBBmNWRsAAdrP4rmgNitB5nxZLt94OWNiL52Wf8R8lQvwYHVgRC8MF9z/OxBG1dsynq9GXqbbzmtuaa6+UhiREMJhkqjVsGjGoENFjhuxmiBrYDmLN/Bj/i/OU5ywP33d8O4Hoy6UmYVK7MUkqe9h2Uxhj2ZY3JWDemsMvTH4/A19+YDbs/0iHMsJXf/FDxVsgE5wEhAjr5R6FAssoG0dNo7igGho5ydftyojc4nPfH6l81+pGUegWM/DUu1IY4ehMnQVrjstzTC/YIB5ygVuia2dRKgbwlylJRtS0fz6KchRokfkE+Ol6ter+K34/J1QKFVMxPFRwPIpBsYtTi6lzD5TqFlR4DGtcItquo9owgiXgBvD0oFDG+o7gjnO2ICEADfBoTX/esHDkCYPGLjZpvjtM9bLsP5GYGBkkV3LKvItLkUHYSUiKHCSj7FDSoCZdg6CupRDTukeg8SCMuCfkpMkYUeUyxlz6Fw+ooxb9dio8DXo79DjoDY4NuA427jEpDYue35C1JITqDJiLQ2RZAEfiSaCojPTxIGrIasPv63tAIK87i5a7bWLFrrAW2GkCoa3TrTcT9nlihXbtL9lde/I2f3YQORDCUh6XkBUWMRZUNrV5lp67X7Mfau5hjfFRnWFdMGdz4BNHHwKdZSV6WStAuUBhyoDqkJ1wPfQ1Ke3vrNDNj8+lEfcbSAEvsjog07yHCkV6BSUBS+AfgXANpUhDC3JesDXehQKhXpqLYAJr1lS8O8bipUs2/duVy1Vgv9Utrw695DFR37iDSiH5AthOA5b+30B1j/fPTPVeP0WtgA1pNYgLdz4xAKv4dnhffdxS1fqrpb1cckd4AAk+CW1gjPeOae3riHAyb0AjgCtZQujFzr5i4akqfgDqs2zQhrQintD9pg4JGOC2cUAIcJIcoT9Ul4cEVKAPKsHEC2Q/NaAeDoV9yorMbTvb/BSJJMEEyATDpH84gzHoqcshMzqz6R1JQDSgHaxBnKWPe9Xh2QVxcAuANiAfan+aoL2uEf7Hm8Us7oZDnZ7SVb4uVkhHEeA3fj9KQ012y5CNu0WCyjDf3mGAPmY/GhsxfcOIyR5pqFc3GbItyAIbQix8PvhayAkVmybfI2QZXgS46KTIkoAKANEpQOlk9Cq7BPD9DRSjW1mY2hzfm0AMx2KwyOcwzjbCNrcsl3/YVpXqgZ0SqJN1iQ6rEzwvQvgV0zAtq/awYxNkxydllGOTNwEYVrE0Rojbf5QwXmm2ZS+eabQoXfxVZ8uuwCWVpEEesakI/CwRrheuH4JpRvu30c9xkxySZFBgimwRdvAmOZ/ApJ3EHH0rAuTJc/RUaCZUCSrBR3cCJwm9UpJykGU7NvmXKej0jfDTPOQ7/CK3a5DQdI2u08kH33Nn3zyGD6Ki5P4H9BOvtfyrb20Mv7AmRc3cpC8IuZ7JE6c+iet7n+j/fZOffWPtj4KOFNIBVa8GpGaPVz4BEfNWh7wANwPNU/mXkhqvTWo5UQWuJRF+etJ6XmPrSevlDVpPDEJ3p0139ltHLvHqSdfanbQUC00eE58yKJy/nwL+dxFSLfhTrbX6WK2V9hhFrMQMINsjm19L9PT6OJ2fxj9gSWTE5gs4A/w0CIBm8n3Gg53Yldcu3GH+z9yboC7HfPOMPs882B5Xn0oj9ZW8WsUdoqoNrF4pj2eudCJTCtAduBKcxRCgqTWQyJ2/QW6nsD/3QJVWT5t6vdfbmJRZ1jUVijIX4FKm/oYnIIeWk0oIeuRSPhWKehWaxC824vfJPKhPf2LWp0dzotizJym1V7O7t9hEcQFeDZ9m53pua+c9tRrTPBJIHvmx4IBVg/Jt06ABlqbwg1mXh0uBh7wRRhtrNrWQiJRg7S19kDwD3Il6vOvZPG75vA9FiG9LPu4X8Mod/b7P7yoicnZJamTyIBLBueeWHFHzGwEKYMH9+z82EUsw7Nu57xIG3D7gLCgLK/7VvqVfI9oPk2HcDRzjH6Q5/++RWU2QnxGtjXhz0OQfJo3jAFUJ/lWanWQUYmNAggsyoPP1eNf3DueYywnnKDUsyDMQAetvm0WoUzf1KpZXPt82Qa2mvqEFKeunj14l468ldCwYsbzPCcdE+Sr8/0bSJYvmCMMCESJLHrm3kgT+piKh8wfCP6cBytl4y7xbzlU1QGbUpU0rAWsA3GNyr3TDr8zLvrkoKqFdXi7a4zPB7cKmqFIMCDPImf9+z6cmtz3TngVPNEccbC+CGUHPAKFm0Ny6mpLF6WnUQlDiXxMvVCEKkQmkzqfM/t012VBMZw1sReY3QTl/kUmw0IaQIJGc0Hi43+Qz3Qos6gnObRKuSyRnSkCxdOBOTLFkBptsEPoEQuK0p7MmtGTOWAJ8KQgOCW0m/DQGXV6qnAhyTbBa3sDSgxvhXg3NEsRsztY9MHj9XtEWxAPlQLpo4a9Kyn2/O/7rUmR59DqiMhrRIXP6ph6mmxKSoz52W7zXLzjrN6WgwAeFPRuymd31ZyL2Mv7A5WqXu8dXEfTwQZEI2yEmce3RFHdTc8vv0kFE7V8AwL+ZoWIyBfqV2gphc9xdjcJ0bE+xHuE5JT9m+a/tmuq4u8G+ysraqXocvBeCryhfoyF/8t5HsEzrPQhK+z3Iz+YYemN7Ev0pMOVxDMzRq6pQwx/FG2jk53oK5enymjYuancVeqrjEyTpdurKxI68tmdvWv+MtEWdsz8a0E/6aO037QD23vfvCNK4mI4Lgekpdk8nETZND7r3DSCPNsDNzUje8N48OBedGGkWOA5E5K7PBovDPcNmNSfXI0x7P1e2TvG1z9KUqJ9nlvb2uHTwvrtks+gXTg+yIG4tD3KG3//zOshQ3spjcxIOSLMMafACZHwxEsfsmWFps27k6AZgnPYGs2cVkP50oHciOE+CGk/WnCS+5MWY+p8uuZfck8vvttOIQQZ8UCrB2c6UWI68eW/ZXZyFgrznL/qeTMAvaYVubPR/3DztVLN97wbfIAZ8ATVE9S3A9UAC1AG3QOV60wHtXEB9gPN1sQDJAE8ogbm4AXWAGIB7KAA9ovnu4HtCAM8AH0Bn5EDfXADBAFuQBsCS11AogYG4AXYAuQD1IP2JRA4m4Hum9u3FAH4HQ6UJb8oynkZylB+n4gLiGxAuOfGyUFj81SKZgVHAVmzCkI+lVHJjZIBJUOMM+F4S8X705+svvHEwrNlVZR7S27x4JB0Elg9mVcugdFcAF/Kb7YDxqmllMkcwhVgIqF5Nri+A5naW1GGKVV4Sb8y8CIstyF+b/dm0/9llOCfdaBJyxpKpRvDlfNRLSqH5j9sKqTTIRrBknprdxYDNSe5Mc9p/CjNSoE/sdQCUAVQ/m/GtmbvCLo/y304=
*/