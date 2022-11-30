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
3FEy3yR/Cj6G9ZIYAIngRaWqn2XIw6IGQCjNynpgZYObnGWoC/rrJF6idzmktotH9MJ4KccXBDXESj+oTdZzTQlFP0rwMFrCoNs99H1oYRNq8irQHmUPFrf5d5iudAN93/Y0ufXlu/9sJ/Tcreb7vF+BSwFhCIHTxz2xP+bQuOo6F0FoBlisznNYWeuLsuoO3JbMZWJwYCeAxMWJe4XWufQe6FdWpSBzCIr0PMf8y8AHhj+GWAOwBXo9TjxSc2evyW4r2UOvJF5iYZrI6N8+ceSVYmk8bIdqv169MHl048Jr1rnfdIhKwEq2Y6xHuEfVDi39DOsLxvXNcBItAU4uSQoNAuhK1BdpV5Gykwqi4fRbk+bxFiYStuQXyAjhdj+QrCSbs1d0LqnwjoolxBPBjTbF9rnLwKAfLb8kFN4GQB4FkkiAdWtFcd7+NIEflQGQpEnkAizhCl69pUQBE6XdcAkH2ppl/C6uR3bVRaOXQY/qwiduAGhtpRqVbENOF7gvKo0Xz7Lh9W4cJwY540xts0X1jeMZVd1hR69ZdtQZtktL6aRmpVNlZeXDbJhvI+OLmeuISWcnkY2ndmM2AyRo9bN6FFB21L6aHYvUk+7BKajT0JxtTqQKUOF/9tGj1J67cAdqZ8ZXJix0Nlg0Veuq/BNIChArFzpA6jfesBOyhkUnQaSOXBhPiY3nTq/kjaSesNjJ5Nb43uaI7OYkYMpbYkVv+KiLjHDDeoBArIPJFXoddtiQI7l3I6pZ049q0ukIutVgyxYEDCWU1d+Ejv8p4MMdaTyM7Zr30Bg+keUFLNIuHBQBn1c2W9U8zyawt1YJTSxLFDqci8gjypKW99hxagNS4YZVwZZ+yQpDDLwVRWP1Z3Zn394JDn5aNGWpjAS1dEQQ907E1tDezhbYAlB/lHBwsKFVpxtQO0V6z0d605xqkb3xwYgpehvMEtUdLZalFYXwrLDHqJb7Znznbwmr/smBVmChHrs1z6cvIIkWFdGB8H8jloq84bwSl5Z850NYkviAGhVAmM2cnF0aGIU1NZukMlCLSIrikvh/pOqGR5G1gZzngaCEc7hN6sMzNwbzAqNfsj/CITOkFw3qQI37k96W+5rPN6xbij1Vg/jfDP/tvOV8HOpC2dzcvLyRS+dsnmw63nC/bDpOc/uaud8ueL37gsWriLtmNZ4azm/KKnIWrKDyWkFaqdji0V/5UpTxoqWpbXrQpMnc51pe0dFwqFTpQ4oxhyw7XJ30ZuM2LbgnLELiIbwOnd8by4WwBwgzZKiiBcSC/Eht6chSVye6GxNdbuEztn2Gadjtz9mSzrdGE1U/T++/f/O6pEPfRuN2pewY2RSw2orMlyYo+nso3Kd8QARmEUNHkID5Rm8LTPBv+K3y3VUChAvAsQ2SfGruSuQvax0C/sWAlAK17N8QTqAZPi+r3OpeDPDJfQ3sbw5d24huIh70FN7AaOPwUtM6k49FysZdtWTopeGZsiUWtx3DyN7JkIgB5yVMMFyW7rg5DOO4XNKzUt9VfT5hoj4/BD7uXrCS433aa/zKi7XK425+5vYv00KftCU2X7/ijPc6LcydwID0V/Uu8cDSM1184f2QlHa8RmsDYV7UjOMYC9QRuJ+Pn8xJnItXUBKqEaL+dnIJQI3NSoHEk9+iqL2+SKckYIT9OuXFwbsr2xUdU0+CdpIg9IWbYfmX8PH8uOHj6El9Dt+Fw6Sue3YqBJOe5JnEbwpep5h0fvmnsKJlfcsrYbSpvlqwi5tQgnPva8qos+oqM55aHRvYt39iJHCIbGJmrepi3Zgnu2LRxp7WAG/IeICjOzF8TYN737mzfguVbo5w7Wt4/ZSrcOcu7B/cwzWUibwvkkDVSZxL7QKlDlaI/r0W4N2uDX0ywTeqp8ssERD0mAzVhTbCmdF1srAQAUO6+TCt6WfMKFpMXPn7moNS7V6DjYi7LJMgdYOjWpKwto1CgPf7s/w4HNTNp9NAxS0nyVTV4WvgcdOA4dkE5MU6DfDh6l7dsuh34lXtsvNMPZtfdB5syHoKRgCjWgq+dZienxTZ+c7CyUXJfSjTJiVxYjauRRkjCI3CxLnBm1KDMcUr7LmNteW/uTAn7qEnb/+6R2qY9xspjw/Kc8h9SKfbJM3KmqR0QcGDQEPZ6lCMP2gwggsBLG/U1H58mQAj9WqNQELakHd20hwwFWh7NtnfTEVPZoFSi+7SqruSBPr1zaJsOtb4bHO84hPuScSQRk9KbllHKcdykWs0jl7z3fJozxGWMhYa0OwLz859yo+b7+PYjqePau85qFqoHNK0IIfB8KrpdJGR07f6WgUpe6+tMIE7ZF6N1B+6wRui3AAVN2GCP0GMk1cgFhqTiep9zLdnThftzJ/6lc44p3ROHp3OW9RcMg9l9RzEVzDTQq6rEJLF+IypuTE0qqYG4U1wm4Snw+fQIJWv+wW0NnUJcRqFCOlbIKSlX2iFoeiSznmg+TvbIgXC5GqhOyXDPj0RPiPu84G146Z7Tbo0g5Uf7BAGnhlNODnPPplZMic+UqeJnnIUg5d3WIPCUu1MAFoLzWlAieYaSprUY1M7pv/6dPX08G0aNDtZaLfgm0qPuiYhc7jI3CzVV4IPd8VXM+bqtTrtgVLYBFwxCzZ80WSXk5dF85CDZXSNv65dcpq4Llx9p/Gq65pv8v41L9z/eKQNsA8mNThkEsoFv9afwCQSWIisj5JN3/ssBySKXz6G1TMmqKqvVOEezwPpXuvB2uQd2CMl6LzOnpwbN7rB3L7xrcH3zL0QONQgHMDTKjzMbmsFVTz2DBs5izHhoR/n08cv4NXYnF3S8I5H/PQD5odvjfyRLmjyRuSoYEBrwYUxYo9djPhsgeipY8okeN/lyocl6PjesZfdDqNU4pgd8nkvap0TGvngSqy860R4wOqKXlBfOGRRXjiUmQ0QNUeh79pr+REgoma30W5J/hKj7yqlnHPSCsgWC026Ubv/k3fScbnzlG4Dfs3Syjo0LkyRXByfX/dnz+tkIrdXNGXiMLmHU+8olx02JjVBMURUaiwXQ3xqmFS3ASFyLAr/nUkDoeMRHo56ceqviloTowEr1hyld8yFMZRt5ZAbxSYlEvzPgz+TbkwrgDkLRuceS+T6VrZ+yVw4BTamqYrW2nnHYGGDvTO2t/Lxu5xWm1NlY75Nq5p7RbzM8XAQzBwq+7u0weTbC4PhcsoJIVmMv/61x5liTAmijsefcPLhm08lpB9H2/52FItxlqgs2TMBfcwjffiPIS4ONNCf0oad8Dv/EA6qO+LSeJb+ugG4Ah37LpJaDeum5CyYxiAb9dupSYh7IyE8uSIY2diuLkHN+MhJ1hGdTyWiPFlzJvujmXOruKxpDhQiDeSuIMveU9XaveMFPsEq4MEsasDDZmTpj9CmsA/aRuBZp09J7B88nAFLyneIf+j1QQciu2w4bBZDVc3ogF7Abk1DdxazdxqPhGRwihozZ27honKQkvsj+riLZg+RUeto/uuUutF5JomlXU2xcpHDcp5y/UjXSlleveYD3I3NVahajWJZGfJC7dQb8ILjBURNL6Btu+KKT4VCwmPIzcRG3a9LCA9KIEYa3+VED6lobjlCJ9ziS1eORDXXpEbT763XzPs99YbMgevuPwyQDTp+L/w0U5Kt45NNlYO6H0xG6NQ2UzBGc4L0KTE0Mf2Vx/1/7rC7d3amAAgs99NbM4aOngLFaokxdcT0NhkoQ+yrB928WfU/h3rO0DkxDrToEdBNR+hpBh6n5uh5gO7n6a+l9D5XYQ9VxkkJD8wdjSOzUdEbqUUSYDUcw6UsIy4agB0FW9ICjAuJEf5Rki5u7Sc8NaKoZhq9/5HzZRYJEPeNyFapF4/qGiGk2LvD4Upyrymw4nOavDjLUroudXMD34nY6dWEoEVWhwdlwGdJGhrOpB75CKTBvBkSwLupcqvh0py8LYpiRTvQdmqplMoRwod6rPu+fJMHqRcuWTKcISP11Op0bLj0+svxo1/5UH0y16Zu1cUZzKUUNzJ3PHd4J2RQT+ub06VpsDGcLH2xpX28+zHI+m4QZJAYNM/JniwXJpRzMM+9RgIObDiYukDchv2TQZxqmShCd5KC0DH1gRqtJ9/DA7Tw4NDivZm1al3fHU4S3JQ+pGjKJlv9OvQtS3csTIRoWYEkX0imEAbv1jpAEPmKDtsSK7r8IR1vgOz7Oa1tCL13z9/SOme1C1c646zwJwfJ+jG30FIZlRtZJ0kS8xDI4vGqhhx5iUQiI5GW2O7knuIL3qIZq7+ay9V1uH4kfOPHlRT3SNFzC+RmgpSb1AGvWtFlZ4hVquNd7DpuyvmvGJJjdGnQxArQVw8gddCQOnHQpziel2Rb0la1ThglBk/p1t4tgHfZXqQ+x9n9wNXr9TOB2NDKwxenhtdFCktz0AbgYIsrBUhHQeJPfrwTYtf+Z7RH2xzlJvnGxdLHTaZbSGOS4TNjhpffvbvBZT5//0CZst2wOpK8PDFvhNEQF10GlJITKm0awvn00f22MxbMfqQrScTMnTbyvaQMAtipH02HWljPO3cSN0nb3+fHSistChX1oI8NL+MU70S6DGj/O1ZjDGhLIAwb+7AcpBqpdtggc+pOxO/OnTG/AKRRmCoXdLHrU0RnjLp77nxAPDjIV5RycCys956GXnS4Jh4/zb6arXDmgwfEP7nWuQJsqOG01Mb5wi5bHByi5jSDedrEg9fAQ580SDxQJ2GW0v5uzGPuDCKSvNMg1MKci1EaapxGImt0Y+uyRB5lm8eoM1F9oYCkkYGvWsYVCCuIOToeuuZ2ECCs7WVlboB4q9CwlVJNTKCBj1lvX87QNnqCX+x3KO+rPX9d/uFhra5zisBB560b9GUXgLlYmFrpCWKgYa7mREFBX1ZBe+t9SIX7ZzOdAQvmClvp4aU/+j+lJYA/x7qPAWsmIeChL9Ob673D7nw7Q0ttRpzpZZmajhpAALgx4nIR92X++YRDkBow4gjT3QUUAFFwFEWUXOpbFqsFfjDU++ExAVmdSOy1EQPskA7gfnia05thss83S6A9qNgNWny7XnFHSVPmHhZupaYSiuGk/KLVkTR9JvFJht1PaWFre7edOe3xjjXE2ItKJ6MXsjt4A8+ZRhdhHf24QhMjCffBJkqN9A46+ZxzK1+U0EoOIhNAMUShGcKbd8uWE49fuVIWaTyCjBuE93wDLd59AHg89O53F9n/TmUK/7hZQDz4u+C7UfPzfNG42moTd7Cek8JBE2Xu1zbLTMou0dgOHc+kjT2MH/rGcsbS3sTSjP3CUgydyAJI+JkarpmBOHCY9f7uUMlBLf9RH7NeJG5G+W6b+LgzPy9CNUJ/EAxBGpejButyrs5iwM6BNR17AoeF5LaMkZhy4GJ47nBYQpJygGtowM7Wbv1vlYPY/gWd5JrGBrETQtoGZH0/1SNSoCt4gM1AnjQWXdtA3icuRS3ppvAuf7OcNoJn9UXR0dI1PLmzn73Z/jYaojhV2Fk26mkQK+EypHj0y/Asd0tFtsFxnVfby3iGbFSxAAQ8G6f2CobQF51idmCESWUiGbKD7Z5ih9S4VrLhs0Vy0lIs6+n7kaPreX3emwI0kcCbG/pYKacwGuMVTMLdW21B0yV8qgbOIq/CoET3noI8hJ5eG4YIOr3wVUPcC4lci0r77b4zbdHR5o40v5drHdlsya6Q/g1mzil6EE3IKfa5WDzExYmpcYUWRPordbabE3OdES3AZUHMjKp8CEy6JhUalDSRYYfkeg+Rxx8a9US+ksO9vUPoyjKw8p/p4AnnvliwEO3AUsi6joePXHxOwitUSGtBis2MGNvJS+RWYDuw1prT1rl+TE0WnmjfcbKIoOuwwvyd4NQCUkWp0jGZyqs/V34bxXhlp5BsrQdddjrWfv7Zvu5szvfIihM4MX3tITQlxN5Nf9Ba9twLiHhKj5QoiZXb/gndXJguTYy40pZI46lO5HKmj5uo5M8L1rQZUT27Cdn8/HrhSgmv9Jdc66JT4IORW/PAvgoQLNbXP+mfgv4LJ2pTGgXhARifZiKstQaqsDX6Nu5uQMzG9xi3h4oziPb07VW/wYYL23CSnGQkHHdC45bR2UnJbte9+tScQropGHFQKASiRLLupkWjXG0qSwxCWI14/powdf5e62ZNHbFev+jblDZsCut0vPMpp1Ce8co5oBgB6pOx8DqlFq6W/LdjJkGq4T/04/v25yLJ/Ex16EVgXfAHzZmJkPT1Qe5Unxz5xV3hRge0BaXHZbzuXDrUI/FQslnx4cyWFgKwoQSNi/oMbp1BEWtVuAsOEo4YtA3YQgiXzYChwoThsgbLVNNBPClp255DZyHkNJVP/8xZfSqopmZX45g+woNnZCftcFG/Befmc7FuR8Ji9YilN79OttJgkXI5Gvwk9cgrsNfWwRvDJeyT7wGnvt1LvIt43L5F5h8Hh0gDP0lKzCHhBlF9/jwM+t9vtP6dZcmtAfpat87PGEa13dMLZc8fuK1wq4ehzd2xRtQwSx4wgdisdIlYmaSzuDdApOZ5Yr5e9A84a5kz7T5iD9rsbixnttnhPhuTQXPECU4w81XNEGi0JwufnQJTwAc6WMu2LNoi6nZBk14n6mzntnEtnTicQ1Pr2Ull2kEocTcFv3u5hrYSHTJW0UIdMlbUWougVLWXVtVyj6DUtUchrxYYUi5slQi+Gm4EgXvT2Mp3ihRMd4seyvNpFONENkVOlEEsOL0fRBf+sBGiWhhbzrbfFd8HqD6Kx9uTzU39aUzz8RKNdPyhKmrnK9MJESNNDeygScx2uHGOqBC3p1bWshEx99+/t7ZT/lvdFmHpMtbdqyYjGrmgXfnFUJnTf4azl/ZSswVXhGiVKWP6QJljRIKuFrjwFk2VXMngIL37/OXRMgogdPG2fyPuP1m0/eErvFXrW1ydu53jI/IwUX79rwBPt+pi5Nvi3+veW9IBq5QCe/O/kuDFKFbHSKsnZq6Br0LVT/+kA7sh/AvG7Ngn8zuHofgERntntfJeplm08GBZ74coUhO3fecDKCLm2uXNBvj9iIxwL2PpcwnObHjlvJUZ+/DItbwVe29TiKRXx/4jz7ou0gYuca36ckEprx5Z0gsNW723isCZNKB0hgrgPyjVpJNyW+R2CCtgY37zNCdPua+xO3OdzTTYdVnM7boSwjkPhfX1tYWUctArOnBensm50HQNaOAzoPX9Ts03nEaFwEGYFSZw2SiCEMNEXZqXs/84T7+4nHXUxzr8qZZCkqRsjI0xuGNXwqFqnMhRgg2Yu+B11IlV7ncU7Hm/lE+YEailUEJ29h7mZ7ekyZ9YVKDnbfM6UjFXn/RAKKrNK5hAbpS1YQuFHHHbnAUFiy5NpTMn+JDxapcQwQWe0vLqLCRTJ0gSiUCy8ggUZxErZKbu3TI5udNIthCb7VAZXfW4zlp8kFLX5TE3taslBvbjjbctzlZbKmQP+rc+RM6gnBQYgs68oDynoeTDzd5bfsYEXh732z/9qJ/p+uEC5QdntjCvYHcsrJSWgeHB1Ylxir+x7b7qKORDrKjc8Xda/J6TKmFKjiCmiUwjGUtPg0xe65gozfNYFwQ85ytr0AUF3/pks3AeS9tW0dP44CxP
*/