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

#ifndef BOOST_GEOMETRY_PROJECTIONS_FAHEY_HPP
#define BOOST_GEOMETRY_PROJECTIONS_FAHEY_HPP

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
    namespace detail { namespace fahey
    {

            static const double tolerance = 1e-6;

            template <typename T, typename Parameters>
            struct base_fahey_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T const& lp_lat, T& xy_x, T& xy_y) const
                {
                    xy_x = tan(0.5 * lp_lat);
                    xy_y = 1.819152 * xy_x;
                    xy_x = 0.819152 * lp_lon * asqrt(1 - xy_x * xy_x);
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T xy_y, T& lp_lon, T& lp_lat) const
                {
                    xy_y /= 1.819152;
                    lp_lat = 2. * atan(xy_y);
                    xy_y = 1. - xy_y * xy_y;
                    lp_lon = fabs(xy_y) < tolerance ? 0. : xy_x / (0.819152 * sqrt(xy_y));
                }

                static inline std::string get_name()
                {
                    return "fahey_spheroid";
                }

            };

            // Fahey
            template <typename Parameters>
            inline void setup_fahey(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::fahey
    #endif // doxygen

    /*!
        \brief Fahey projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_fahey.gif
    */
    template <typename T, typename Parameters>
    struct fahey_spheroid : public detail::fahey::base_fahey_spheroid<T, Parameters>
    {
        template <typename Params>
        inline fahey_spheroid(Params const& , Parameters & par)
        {
            detail::fahey::setup_fahey(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_fahey, fahey_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(fahey_entry, fahey_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(fahey_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(fahey, fahey_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_FAHEY_HPP


/* fahey.hpp
gcSary/Y5hCxivkKD9glzmHvkWhY6oD/wh/T7ypFPOeejK75DN8k6YtnY5OvSSX+25Ks0qFO0nHXiFM4U/SQkuOyjJY2OCVMHS0pvlxeq9SvXClna3kooqW7iKhbT5eYPkhf0l10lSnsPNRZ2afcM+YNiJP7OXKgpx68PH5zZuoxoJIM6bTcERm/W6RsUjg+bBZQcjAznXglrC74rtK+fCTVXCuF9vbDIjLOUZgjZIsF1ofAmmhWsKiPPgF5en6JgLdPTCv9d7Y5f8Amr7vDXvArUPkWFutWJGXHBzWr2Fj3BdoW1GTP+LzPMLlyP8UXETElBFFXFHlwKdM23WadcmfSMJJXTbwISLGnC3tdBEB/TaBsUAOrzKQoMwDPzk8+gpmLq+MCDnbzKWfUzRV1PAuWvZGXh8faTj6topQPmG+neq/+HHsnBn0fWsvcE95d4c+Eop9FGc853WinGf2KeFfi7WDqN0+10TehXivNHztbjWRIjSjKri8pNbpWuzDAM32PsMR72wqtap/Z7UBAVjVcw9qBA6cN1tsWC/ea/18fceGd5/qGlt1v7yhJDp4Qez+UD+hkK9nCScZ26PKmoOfdqClCofF+zayrgNb9IlxU9TlLtUPBcna1qj5Hm7Ve6FVUBx2IgjkLuPX3dYT9R0IoBDKVbOikBkOrkrmFWrBQrMqyXhyLEb5PrRdqgzB/wen5KhbZXDW4flEpGXbGGT4ni/TUOZ5Q8X+mo7kJAg2q0qX0JUNCQjeQDGZcblgVj7TjsFkx7Hkvtnp77OxzQbA8WVsCSl2Apr9gcNofI2B8A2A24jZ7hW7Ap3DPlnkXmdhvGNhvl2NFYHwx7HefP7DSnyNgduhT2YnnkSP8fPQH5s2lL8TfZOI1gDaF8O8wu8X7y3D70CMPlGc9TrzXMT7YEwGVjIc2svg0wuUkdC22Z/CysOIMV16vJAgHuxOMZWuOACct1z1DiMo8vO5m1vYR3MtrtdWkTjbqARcBCRdeEnR4DCq7dh4XDDG03mhbIjH2z908bHma4rZAvaoGQZnuNznQemB+BNaRsmGNcMauvZBxM4O4o+PdSPaHJ2Znx8VcLAR+t00hQVHxeRzwwZ5TL+wXEUWCw6m9AaE+P6VUZlt2u9SiGVQAFbBXaPPhfIfHNmkAuQrUVLXzKoe545YstW+Q7jIx1oMekgaRtf0oaAdY0j/U6XAz1mM3FOQOfbPhS3uv4J1MUxnT5NOcPWg61xN1Zut8xOF37ut0G0Zf58+4Sbhe095poGidoIUW/9B8j0MvaK2QcnozM1v5d98JKSYQk/FTopzRjVO3B3LGYeS8lovg0q74dDYuqrTVYofhXOr6G2IaKMnUFV/pq06Nz+9ta4Qgc2YPY777rn1GPq6y3esTOrdmjVK3+8mMP4BmmK8Ut/mVsvA7TtauapfE0KJQTrI6798Z3HI26sx6JhVSCiaVQt5pz5lUc7zU2RRq7vZCw/p44HnZGTAYjKuOumdbI0cHXDOb2wmZTQoAhy86GXmzN5mVpB+NRLku9zV3LNFRlN1/4B2UjWHoZofqfrq2mQZxa3O/COI7foDdAln1/IJ8+ep3e2T2ZQF53ZoJb24EuRasDmStgFPrq+dsxnCqsBKDLc3m9N4EWuaX43pOQoUfeZgUcsQMyjnDqH5TbTak1fWmqes4Zo8ORRsYh0SXcxcXJM1TPMkOdnPLT6vSj2xorC2/mWceV9E2eEd8HXFt5oab6LcWSXOaw6qgMJEG+hbo6y4OrAw9HdpWxGEHbGeIThjwPcTpbghIaEIU0Keb2i59GAa09bxd1HS0x+W2QNeN6evT0xGl3DnQUQBd6h7Q3nmrNo9p36+/PACG3CG4vItrHuK6DXry9Gyp0mDWnvS0pq43s3n0dDvTDuhi1lfpRKLfs7h7dFtR7R8WeNt+icl6R8yjQ2nBMIlr2tEWlbf+ejEasvVrWCzGszkrmXlP6OHjPDLwf57Hk2ZEkw3t8i20qt5Jctj6BGRPOSLSAkTHFPyx3hQqWy1qWCIaSo8M2z669LAWjF1KIK86P+E82fOmTTyZPdkihVEoI2/Rty3Q7wIFZwsUG0esELMQwSsI5H5BbJ8aW2540wlL3teO1wNr/92/dgvQD78O2RuaA219bQS/G7YIPW8I0aIvpj84hsW94wcMXc33s/puMAwpzO5mR7x+bXgm8INZeOGqSMFud1P04YuDusTj2xEefqcnwWk5vjzswgTJluH0unu9FhQJB/xy4Uz3hTNEZWLgGgBkcSZw3mHbNjYMy37kLFOZsX9JfaDMdfXc6jzwvt1DgPOnC3UrTqeGTvLGvSMfVy6ETCV9pxtD0cBU9OAdgReXVaikV2DJ5A6HtpsPPRMyz/pJaTmd21SMrrakHZcvhzueVH+Fa1Vtvb6j+4LgJLic1Lu7bzsxNZgp5QNb5xWKFqwP5sDp48hKtxu2DAihNu84+frB40TlIjnWYUzaoR+ZsbFNH9CNkRa/VYcZPIbQ5OsDxhfvMGzNJ8fPQjksNdkZ+rCwbj3k5PRDOTyboxl+5k2j7Mh8pmKT0Y6Q6jhzvJGZ95vSkB0ueeZlf6xA5IgTfDWJoY9j370vQqxDTO6NCwHrvk0v9NyWHkqcEwh4+2wvTlaiTSgQRbsBvWinUs2WJV7+XLtVNUh1hmYM2659GOldr8ZoARyNyMPcsBNCN68pd8Z/Wg1vnQqagb5ekEYi6yTam5imT4M4wg419QUB0mP7GITSe+zx663xDPbZycxUtz04vlbfJ+NzsReQTGr//Ma9sN0pKK9uvEmbiItipAkiYbAaxOXN62HjVkmDWyGQBVWGIxNhUpCufcw7NdFecGJYIEmEApSG5jettqiVH9C2tKRuSk2qloUJUkAKMRJRQVBtqLlymWOLZ8CHZ7nyWuYyM+e9/Pr62tKmp3e/rpv61nSvbFjyQrMJPxM7w5KldTTGo1dEX5hUk2dUk4BHDJrB5vb7Exe73ZD3uFH1dnJc+32XYYDT7JCqwF4mk92qgmUwQkrK+trTPm/XtBGT8cDsrmI27vOkWmGN53DI90ysNrvebxovWyoqy+GBcf1LfqXQTRppR2Ko1AeimOJAGDqGyVc9gUrqSMYZVTUBaxfY9nwCu8wwbeGet3RX8az3305GdCdE1xnCNcyj6yGjHYc2osyps5IkmFxcGhcFqNGv1SeG1zpQB83VIu41v6UXdV8MOXxTTbCucc5gw1/3Hn7svijDgI+QwUXD1ifxoboGWk3PrPx1Kz8RZ5kYIq/CTRUfC1p2geb48aoiJb4PkdYWLs9uxTaZSnO+3JfcIuu1bZJy2ifXt/6iTm8BfPdN3M0dfW2+k/fNHUIIQW0J8HGGc+CggN7cbEv9aI35oc33pT7bBftoDfyZLvTVzffVzfPFt8E4ljlHBPs0nVT3RTD0fHysWxDSov2eiPZqalvDyOe26qIjZBIDSiYepX4OUPIXBEA4ppSxwRLxiZsQgoyn4kui4ZvJQy7YOfZ6Y8ju4S5hLqNniwsnSKFxheR3emU11HuVjBxKQxJ79lCJxv38VTY3zV2zjH9hnqe8ByO1iAwLQj7C/uGs173/St/bImSPf1ypomSLedw/gJHfXkn+tDYhaK3i0vlPPfq4mS18p0FNc93AEFpJtWMxuu0rYulhE3ICkdFmhptflq7qnUGdW3bI8Efkg0lb6Ji6WG+j5L5E+yLp8RXtiqZc60UkyEic75cVs4QhUnSQ1z4qvMnV1aBEXVH3yMIrqr5pORMQRps93D8/FfWMWbtpTrCYzE9Suzqmuii1vDxV4uN0AI6mLSfER3/CQVAIHcOC7Zpxrow5XlLhcWadZF5ryUg+20lr+nrXVBNur3PEkaHW/ailqbvJBCt2AuO/waSaaLXAdpuLY5v6+8DG3MTWea0uncc473eupQKT/2479erc6ierVbvh92GXaLLPD/nsXwwDUe2y8X28UvopLLMMFxicEopX7c+/Vc6zVc4R0ZPY3j94tO4AgdLwBzGiUuqQXjnVOSkO64uEZuE/Poe8p15ZtcAWqfi7wT5acL6XkezBgRScV72TBpz5486kAgYnmQv3DhunDr7ZBxwXUQjz1kH1ScicsccdHT62Wd4ujH9SAMQqCCfQYzwSwQUN0t4uUj2jmhiI/pmrHiPiwPrzqr1cKLO6/zt546Pv/xUTJWJV+9a/Fz5A+JRKY/nvQvXgZWvxSU6rUecOombVvLNVdw/tuQNTpKioUSwEUhDgVonJwcZS/Mgf5RSFAeVUgICEx15ABy0Bg7GFgQRG2SzfEOk/jqm1lWtRWfqlsudRZySz1iNN7mP3ErnrpYvLdszxVzxEXia38XozOLqx5Zr/aOvn7E2rftpe96tTDhcvF4qB6flL8CFLd2hcao3oDI0A5DtGgWCaD9QBXTZwMOSQu3zobgpU6KNW1wWOAhTqQ9wC1tVs9s/P1DwMxfTPULqxbmmKXX1M5J4P+19R6K0zszQoZs4bSwiqucXK8pFVnzCgBV0iAWN9RLxuRWNWIOip1Bi2PGZs3pOVh31j01DqNa0v0jJYOX72KmQuOyhyR1iUTovpDYH/NVqy7XDOUM9sja1WLrUt+m0g13aG+W43ZJ0+xISn5cAhYzKULcOn51XxG6nRdVHhSthp8Nc6F2pDz3sIrLEJR+lRbRPqdMe7+6w5ubrlmM13Zn4k7YvOsFik8gFUkQnzRuuV6nuQGhsjFrqviljuKrZeJGx7/HC9XH1+2TTnaabqLlXnV/3ubld0lmm+Pnv7tIJF/Ox2NBOtV3+frTj+zN6umDtZmiB2oHbesgxaMjkJedQaGONKg4YTkZZIyOPeqOHgbtYH/Ist4aN2ucvwHY/pfsfE7Zy4UKvqGXzrPVd/1F5V92EY6gEs45C4G0QTxn5Duh/7HErlT2G539YpCE8xLOpsoJIkT357CITw3zyoDy8A11cB1PdvJ1NTjsBmUneG923SOVA9f7JEtpwFsEEl7yyfAE4yDiLOiSzcTmLPY13q5/3JcnAfOpBAgc9+6DpOWNNyReDM5xL7T0W0limzSnn3G+igmFV5tWJG7d3LNnnsnaqrwTLzhdL9HomUJgcrBG35gg4xZGa/7U6e3PD1dB0Jlphw24y0Wesm3qgdiGrVzbfaPiYytyRa8mGSQWCJw/B19pf8ueXD5oRbPU15RCwbGtFPvx1VcRERtwWh9IdXN4jSooow9qgqI/e+Hm3kl+LSjLgZMO4gdW8gvVNC7KdYdMZojgbphsEaXtE3/C7fN/JcIDkqXAcMVBkNsqB1bo5RZBqiLBjMiHb5gw96QwOspnybWvRd7qV1NqrKz+RwJKcxZM0ZDwDzZi0vX2dFI6uTv9Y4W0JPmf3XRjPVzqy43SOd/WJZ8lFEYinj0fxJZusl+YlTrAnRYP/tpWHaJNiw++m0sMvE6ZOqukiWZSr0lTua2YnaIUszxM99Dw1WKQ0Uk65yKhA3mFlDOgtzrdY/7OiqrOYr7CRRWp3r13WVNWE5Wquvl1TdSZSJQ9gXljT/VsrpYS7MV+J6Qo0Se0UE15wG0slhvFELB6gogMY5lwYVrTXIgya0V1dYQVElrgmKC7QmaxuZFtVlVL3TGtBNgKAhdam4MePqC3wx7/MHO0QIe1oX8ad554v1tHdWTZSLfyTEkm5sT969dW+6VjdTnxgvy1lK22DpN0vCwDOIC4P4n1cTcBzkRTEZwUT7LhBj4eOp2brKexaCrQ0fcXy3EJCbnNftre46dCKSxQ1rH3uh4s601z3XjQ+X+C18CNdSPFnDRG35zBDznHQKLjo9az9pZ2DPguFDBNnKZP/7zQef78W21u/S7avGGM3u1zUmdO2x5ZuHAE4nm/PndNiVN6mspwi/oIF3ILcCzKsdu2FqZ9oFK2ZTgy13OASQuFMpku3eUJZ/+HgSNcW/qobFl8psE6UQYOKbvl3/IkFgdMRMEphQPuRHloGs0jVeZyTNBB3+vOmqyGTua43ATHQM+oBaAyrJWgm6AHByzUi/wwivuWjUPgiVtLmN3SzG6LqhC02wqnbYmQKX7A4yVKzByYGCeuTlMNMyKN/c3yOgaF9wlwan2SzbvdwUp9u7ZBDOwptCSfuDXBfsUJdL64tCm81f9xW7rkpaLIiezzEGBfHep/Vms20Sq881KZhOAupVoW1YKgPkLqqdd3BxPflrbzc5eVw3p1Q8w9HNAga1NuB9KkYn+j1d9/2bV6HgchhbGlegWy1qyjnDrp7EcnfxbBjsKmFloljRjXtS4BttYUE4LeXSSQAVrFA/ScEn1aK0F7GffvBCHN5DwtSz5w1rgrocVOQwq/8+4EWLPoR95aixoar+/ZOqncf96CIU87TbiTOFHQAA3eS15Btyw83Nn8aGcigP3Q0prSonwVywvtdSvQsyhdV7DhjltXSpW6KEm8njNAmTnI3QffC/otJiIRnsGQuNJhL7RrCy4m87hYkhRHo6grhlLy5nUNkS4eie0E8sdCzFaVwH/VDiMYlVL8doHE4kPoCNsyrJKPXDhXGMlEDk6ulNp6udv5kKD9sli6y5IR4hvLxlMYmSEUI662eJ9GL81prou52kL4H5ylBF16hgROk8SPyvnpFex2h9NoEmii79CJW7/2HOnFPjyJF6qwPmmnlwWLDfGOD23aayzfZ4DaY2vYNkVXL6c/xDQee4BAK42x8mgv+axZoP7waIun+QFrdcqlHm2L58sVnNytPv38H+eBNPQq51mML1eju8wtBR4bAN15MS4XriZ1r4+0MlLUzMhe1zXYWOonP9gN9mhNVciW7jdJy2lyqZAdUwvLFByFuF9JB0xO03Fst6Jb4+dvniAAMPtzCdKAjEouBUzza+znSEYyXoKbkaLYeyoyA004KGXfNyQG+uXLNe0XLA4akSLcbbMiZwCe2W3/BAHCBJTJj5wzGrqpRnfe/Bcv1RZa9zsVdzMD9QBtnLDguBrgb1peld73PZbtypaEibqURtVsVKb7pnMvS3cSgnTBh+8/ft14mvtHgnPUO74vOH+EX+7rVf++lNkkp5EZvLx1dYnCfjtO6BYkil8+pSCYfaCg7iLL/Vs0iuajZGzXrD0CmsmKUGJ6DjNheMBNwJeSpC7TONT8nKB3E7DkQ9K/MnNKfOr2C11vyEZfMDFyaG8qsFv3Y/9BgldhHjtfgN+JLdyYZgW0Tqkjl1Kjk2XeCSusKVcRC3To+JyGd0y39anjHIpIcbpivejOFBruOQGTkxlQmmMKbJq+mE5yESca8PHU0UMif9CY6DeYQG7pTShWXa+CiGDwiA0r7Kt2g1PKKP2lXrzaFZHztN3TLGiDQ/hZV+djDKW4QieIiz97ZEhmJTMOzGa8+A9SE+6Cud0Mojr1F9v4/fPMwJacHuCicVD6/m7AuVQBYtB/PCN+JOb4mRn7AevkTCnYx5HwhkM1Lhy9+nzZiyByLTJsaljCD1n9kta6xsXITD9El4fI3h5CHL6tfQdtvBXOfrN+p8SKsZaO1JMIYox5scuQ1dsy9ElUPhPKEKN11zi/2TMyLAP4n63nEx0msUvvgBWPjSXMS86EjH9I6XFi0pElmJKjdBuQdKawo63VOl0SEwTkka+Bi37ifHe5cVSp00jER1FKr92iHdQ+XscQQoPKfuJf+gjQ9nFDT3pLX8gQbPrJpNF4iJgQ+xHb7EbAuB/1naXaT3e8OmA3pqh5ispnIF8sLW9AnPcOHhxKR3t2kQ62y33+1N8lXi29gh1MH7HCCGYdt0dqSF0EWNlzM5bORlu4cb/3dsswVlenF8M+BgetWjc6AJZpX8wby1m9rWO3qYvzMgyIU9aEDp3DhulpfztCGlJUOOziYtkCm1FT5JhukX2icQOSVGwCTsGo1OWyOrs9W3n+ECNc0Ujt40Hpn2SQ/QAK32uiEwVqlzs65wAqRHXKcPtwGDrPCg48m10v8PdZuc+qMg+HEMVSYOdbv31TvV9FSwkW9Pw0vUW345nBv/Rl8NqBFuhNcCmRt/v2P7u5qNK6EYYfKnwCYDtnLfRJ23uoq9m6ZF7RnUr2ZoIcIV/wCdq66wDMlX986PKaEi/TmMZxKJeCqVi2XDLIaKzjhlvDMvKnWyre66xC8Gdo59qidavL1wpxmmH5k5EBgW8wPAVhceyvmwsgQurPU8VdhZqZyPalmmuCPwWfiCdOjNHt9EIPVA2QYycwq/+nBAxY8mK/Rb8TvugEyBDcrogAzjugxYvOwAnVL1SRxgMdjrd8VbGMuTUKI6De1Mggmzd9MFMVFBIX8WOHXeKWkm+dYFAfoOf6lgpF8fk22zsDg6sI7Tp6jMHqH0ffBnpB/mQytjleOs71SEKlSO/lipvdiQAn82+g4/S3/htnsKndXFRKGD6IQi3fGE4pb8p2T35KVrqUXVbdUynzCoOyCkPgrk2kqPrFKYZCZhy5prVMGa5XwTKVNJynygd291j8hlsIE39K+lgtKlJP061rH4XSqh0mvSg+0YjRr3Iv4kOSDv8YqWUUN6A8D6bVgCOJVMyrNjcG4+jKQJQTh1JDEk50+vRv6wq0uNU02U/mQoKihG5mJI13uAatJnBEcWPLcb4xhuPVrmL/pfaDwixcXyfitvqXc82esb3iSJ+JnVTkLIza8+UM6E5vPVEE2ppdViOUodP/fQCWM7iNKbolhGcgFFbl8wyXIQ9fCM7eOfcH/KvWl+yA3sxs9KGf+cEluNm7nzzPe3ePx0pypyYGSiXTDcB7cBJt32207clnh9v1mePlVJpph4rhe4V+TnrMSKiGj+6Gl8FcKbwyh1/LJElUj6SikfFaSck5OcCWpsmoWX2djI7futZwk/mLaavbPBsd9jX9mQlo6X4U5rXoVMmkXCIkCaROv6ivsJyfvgHxuORov4sB87RmlYGrpED7rTvh6d2/OW0/HM39929PXzX27/9hBj4YIDC+i7QrE3cwJlMRLa4OdBTgLpN22k6c8umXLvN4xTLlGDxwxO6akMincPYWZdW2GYgJnIsd3q+rbnub/6fLiAXiWUmgd2lRv/Gr/YincSzgllVkc2TkDy2sF18ui4VBApKiXWfPqPSFbuamHCWy9cZDZ/bGvwervnuD0LfJsYsxFhh7XOPEarrA0sfSy1wCy9eqwQ0ajn+fQN+qHFlwWq3Mo=
*/