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

#ifndef BOOST_GEOMETRY_PROJECTIONS_CRAST_HPP
#define BOOST_GEOMETRY_PROJECTIONS_CRAST_HPP

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>

namespace boost { namespace geometry
{

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace crast
    {

            static const double XM = 0.97720502380583984317;
            static const double RXM = 1.02332670794648848847;
            static const double YM = 3.06998012383946546542;
            static const double RYM = 0.32573500793527994772;
            //static const double third = 0.333333333333333333;

            template <typename T, typename Parameters>
            struct base_crast_spheroid
            {
                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(Parameters const& , T const& lp_lon, T lp_lat, T& xy_x, T& xy_y) const
                {
                    static const T third = detail::third<T>();

                    lp_lat *= third;
                    xy_x = XM * lp_lon * (2. * cos(lp_lat + lp_lat) - 1.);
                    xy_y = YM * sin(lp_lat);
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(Parameters const& , T const& xy_x, T const& xy_y, T& lp_lon, T& lp_lat) const
                {
                    static const T third = detail::third<T>();

                    lp_lat = 3. * asin(xy_y * RYM);
                    lp_lon = xy_x * RXM / (2. * cos((lp_lat + lp_lat) * third) - 1);
                }

                static inline std::string get_name()
                {
                    return "crast_spheroid";
                }

            };

            // Craster Parabolic (Putnins P4)
            template <typename Parameters>
            inline void setup_crast(Parameters& par)
            {
                par.es = 0.;
            }

    }} // namespace detail::crast
    #endif // doxygen

    /*!
        \brief Craster Parabolic (Putnins P4) projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_crast.gif
    */
    template <typename T, typename Parameters>
    struct crast_spheroid : public detail::crast::base_crast_spheroid<T, Parameters>
    {
        template <typename Params>
        inline crast_spheroid(Params const& , Parameters & par)
        {
            detail::crast::setup_crast(par);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION_FI(srs::spar::proj_crast, crast_spheroid)

        // Factory entry(s)
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_ENTRY_FI(crast_entry, crast_spheroid)
        
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_BEGIN(crast_init)
        {
            BOOST_GEOMETRY_PROJECTIONS_DETAIL_FACTORY_INIT_ENTRY(crast, crast_entry);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_CRAST_HPP


/* crast.hpp
uDksfeZ09GMWDIdIbDq+RXWPak5OCkhvQIl0Ghry6BUrGLMa51O1aeKSVaOc+Ko1OKupF5z092k2YfDDbLqdgWAxkkb9kjSHCsMLKaNeUqORYuzNeNzCOdnNeaNb/qoJkA+Vj3pYVvlhrWzyhkOxK3DJi84zOfH/8dP8uRBxd5d4L1PkczZ/98VFPj5FmZlXU+ipJby828ir00ZWdtFkUib7R9wB2QuoYxzmGSngcV/rhJyQGF3mxuem9l/iJtLUHeiTzVApYBPCIFsiY9FsWnjmbdttE95UBvy/g5sJgN93yMpg3kAvpxvmoKViVpoAbnp1LYvt0hsX84kbtXIbDsbJ65yWu2uAQgxLI1eBR9cwy8DyL5M4kqH5OKlDhjGSJpuIVcqvK3j5y3rqbW57+wkNRQZzWarxU64gDATzD5D0A2/iaAxhAgAKxcEOZh7+jWdCD3plHMpZ7geOFCVCJMu9/oIvcwN1J45nZehrNXBHvF5pl8rA8xkumcYauJiEWkXwxmPqpf7LZMybYs2ZDmpr4+IpW1A0CKymJqnOcL+iBEkMqCzQncZLZGOB17IvMLPt2b3mWc3QHPI7u662TqJliu8U1MY7FrNno9z40PK9xNoAbMoM/Fb0XmNUSdp5t1vEWSLjLvVh9w3zoRXjjhV51plA3VgKhHJl5N6aexQy7HbEGlnU6Un5F6CW8nQQvwnTF5/dRuYkdQ3la8oLnZdbeAbteeCMpRT84F1vxHJYtnpotvpH2PJpYtFjq31s5ebDyKwF6Si86g7w4Tl/lcVvqMD16LkkFyOfhJ4OmJ4LLgjQSirawdTHr065c6+Fft0GosGos5SiZSgSUIJMqpyCPRilhn9WX2og/cj+fVDQ8RiUFHKgjiIsXZbEWLqrQI4L50kTe7BAmxVFES0YHrwVyBjNjBq18fNWGAx59UteOubgCUA6NlieWvAquL+jbui5Hhp75S0eOpQgKU/pAY5jCULklBTayyuCXbi3ur2oebIOYMpP1doINJtvVKCwXDaC0LWvuYudARLlaRBCoXxniE1R35pZxHKi72b2AVk1cDtnVbfFinaMZ7ejaMT9O5AeXeNuXzHvGN8VZlBZHT/fi2Jin/xaME3rBiANBY962nG90XJ+mGoxnkm2pxW5w5UsLbsn2IfYrKhBpK4fFtuL+B4E6pwok6YThLH//q1nRfKVxYaUnlCNruOlQcRyCLss6zkZqU0fGv3MpIc7GhU3RkspmZLhok/eWiWzxRNEc1rrLSZVZzSQEtkEQLGa+MXaCdPPtQiIBkPQlVLaQD7Do1jB9MVYHBXi8dVWdpLngYklbhxTAxaMHJata0/Y+2zKIdyGOMzSHb1sBGe4I/Nz33bhdUrhfpXwbGgEO5l5x3KAmW1KigKGCF/PdJAryfo9Sdh/EmydvLq/jPG5PhO9M1V7xEN2oo4I8lFd1tSMpC5L0o9/MsGdOi3Egh33ONONDFaxrvjGfqV5OqR8MShvJGaDcLH+upzwh39x1hmw+GMi21OnimfbUWyCWjckpfS2i/W4tvaQxVkCLcVheF0T8eipGRBwKCiyWnOSDenIMeLqtxVw00STsCD+zHHImNT6Wbg3oXpzxVOTsE4Vgxm3nFVRy2A2dHbRbenw0gMO+XhJXNW40IS0GDaXm7HYQDqBGCyB/0vq9z8Vxw6tE1USJ7A4lRMSDV66jo+hpzZdkIx1GsMUxHa3LmfElcf7p2/K3nOHNnW2BvepVB1UmW/DEkE1kKwABL5AKZdtGzstXzOMvqc+ZJX+b1yrDjifUYx2dFqLKdQ6Io+0nrTIpQWJ+BIwYoIhgLwEQrWkBwxYC7hCSbjTwNANh/wgC1dUik6I/eeBoI6TlyFTwO4jy1kx0r9eloW6Xm8+ACex+mrnSiRJ0W2PhhmYnuvSpYC5BX052eBsH7SMDU0GwR8UDOpr/pbxctB26QtLg4E3DejttjEU8VdUEyr4HKEg4p+SOtczq+J/FhjRXqSPtyeftaV1a3JdO5Crd9ferwXm6gNa7n1kM8ZYis6T1RipmKwo19h0URXcPAh7t75AD5G4PevLQfsFLumAewEtnBk6j+sUeA9FR+xa8Xa6SkUc1eYpiMgxhq01miaMRKkt97m3bXd+xVhgksed1h8gGs12e0LySPOyibP6crOBqUbtVg/B+LPyWb4qV8/eEwx8XbgYpUT4ZEUxVfUAzD9H7bP6JSn/cQ8DDTneo3YcLJTI+yEVcQ8Xbu2kejo/+0OiIQaXglrRZPghkmoo4jX/TcWg62c1QFF1G88jt2D+zVGxfK2g63PMuKutJGT5Y6nU6/T3bhfF+PJdZ/WILy5IfN0+sYjI+Lkouk8ktwXkyMjyU6jj2B0CoI8hIi+J4iMM/K76ht+dE5jVYUJ7EZoYsxEICjpXNTxQu+RC8odn8HXc+9FZ42qGajJe7uy/wdjCdHSzeNH3/3rh9SgYaSJUxwqHHaekJ6Aay6Au6K8Tw5t4o/qKVxvPg1H8FK3frfLCOhgzOYrPg/1oc+Jm+iNQtZZ2bUWsIwB/vJNA0Lb/Af3Ht1s663+rBO2aXikiGNX8XxIEFLKBMYjTP8Bs9bL9djRSYVj6oT3MHZrKo7kuTjEaEeIkyuyVYuJ2394GPTOMws+E+hCK3emDKShZrnSEZobhlvgrst7Z7japFyWvlp291COao8UiW9aMCslu1KTyEDjBx1xzB6vEsHHVEH//ub0mSDZ7deoEboODcX2l2OWwoipJ3uA04GOswuDHkcWbgfzlxgOgWTwp3Kwf0gRzuKEHB9lzp96Ih9gvXA/604ZjY7YELnfrYwSbnF5upmYKVFzKCGiYxIWdZIxMoafw9iwr7bxN5ukjrrAumUfWzlaAOlOuRC5W1N4o7eaMXSS16qDkDO8agyA6dxFQz9BYgAJE7P6FgI4eMPn5OrNLiYdht2LajQsuQ8XkJqvSyVU5vSNOgE/2eI2dSHs3Vtym2apRa2bIAI8NH61f2dEtmVRAlZLszICIYGZkxOEbhOaoYi0xTJUyJMsIneywlYjTd01CsUjnDFIgdLF8WZcAZAd0w91/oZVHl1v7ohMQrhpirZWW7jS4nwxVLJFR/jTpZ3DyKnBhYOMr1M3EsxFFMIkXK4pHWd9f3KfjDnW2pwo7W3CBJqG8+FyXPmYKbdBYbkxLMWdKmiNdysB9baOtJ8QK5+GOKHavfAKnyeqE2Ejf0AIXAS6CXLxmR51rXWxHNBNaxTE81u5b1jLWyFxZUMa0uGfGsFtqKao64jN6aQt9uA2TLgSxcxI0snGSW+41Unt1FXPaunpZuNwZ+NHA446esgT5OlU/aKvbhjNygt65XqyiJ6iH0zg+GUpSYDoOVDz8kNBl+1jSxVELDHiM0kPK+p/xab2CyiRlGJfgDF74eXcd0SIRG8hbgGhqJf7WPssE3R/ESGzvbGm1/FmiDo0Axv7aIfsvgBGVu90IVANPhYcNcpEa3ADrmiKtvnouGUJ1O8MmUBMyjD2+nXtdMYzqbpfSR0va7MAXVWFVRV2Lhxng5+ngqigABlU2OT/4GHlIHo8o1lckubBRyPbJZS8jJH4czFEejCkHtbsZjQTMFgUHT2G5V6Xw0Al81mj4O3kJrQGi4xUQWlrjmTHWja1yGEqqWXjuEV4RwHENwDrLOQBkZrpKBMAnotY+sIaP1AB24LSAPvp0eMdKYhfSXmHjeu/HfnzGMuOMDH41n9eoGg5sKjRMShoZObpAWbPdp1VoA+TWPrI+SYbybpQvIiHhCKTqEUn9I9gO5ExRbchXuBE8gvskTe+sXooQQw+x+UxSECH+WlqLbPrG0/e3rxFZrK30gUjnBzMzj3c3X55Op3vqh9ulBzPDOm6v+W2Te+X2qbWD9k1A1SMly2vNWOJ+WTReWm4V+UxZfLJv9SfxwGL9vysF2DkSM7iNzXc0faVaHPobbonVndhn6OgKxKnw1Qa83wmr4O1idHlZQy1kt7Zp80+NaotdUcgASRsQxf71Elva8dipofejLkCRzYh2CJSwhThrmBhQhx8byvbnA5MyHU57xxQdTYcmVDobdw9TSmll4vm8iUXoJgojJlHqD2oclNNM+8FE6MVf+RqscH6iQQFdJaF1s9PfK0dpJEMfhkfxB1jslDYGi1KYapJBlBbE1NVL/Z45Q92Zva4nMolZuLFD3cQUnCIL6tkomsjZxJQNknu+EBYHrnmntH1qDrCu+wy5t+z60m/VYnjDQ4LB3clpbJxUu5LzZNXx4rhfeFfLBilsyCWCn4hO1H27MAZXaDIe1bCjXaZwV5cCxKTdfVsmVi1FI4Nbg0y2Q5TtjzB0xOUPk2+XVhQSrvCiCTETMXnFQAwKv2MqiDJYL7Mw/zygpoZYWuHzV2uAybEDP0jGpZAn3wpYu9HJkuTgVe74MVQVST8O0wQ0/S3ftM5EmQo8HPrqnomZ5zPYrkV4WiP/NpyqWUtEwDrllf+IBMeozcPbD6NY441C0H3TIRKY7lSUFrA8lVc/FYwAl8reOynH2MbeFeMepRsoOQ470FaEHJbYu9crH32R+9uueOpUgtYtbLuRm5OJd0Wv872aAnR/vNcpiZCPxMmeVZqHESx+9m008rURiSs6cT+G8oqhnIE/Dtc/PM+wVxYG4R6fyOcyqzqrLlLD1V2WEF6W+kY73VCfmGOYwyWp7vvFnj40xlWmuZOTpxa6GolI2QbEtH1cpGKT1iDRbYqswA0Kmu2npR5Y7PCo04vcyUWl/gtKtCyXATMosqRSLnavXItQdWjqU0NYIECXaAmIkxn810HGsiAAnkyJkSsGht1iqIwTzfBQrUtQN/7ljs5JchAP2WIYSdE4TGPk8fBdgC7wDCFJ68Dfo4Tt+huF0k5897HoC46JQOE8fSUhGXG3H1hKjXeNGp4kdQ34Iw37fXfQ49nr8ZWkK5njqWDvxEpnUz6tAsFfAHu//smYNGzIL3le+Esv7OBTtJqBQ4373s5eb0cRUqeW8aYnwJqkMTEhFCOV9eMh+/Y3UJIwOspYRkb+QuzAJy8i2TG7hd+jkZ0Q3OzfUWZgoFi9wybOnsUbYjc2dnr4Y7eIReikwf9d4TQSmbz4T3t6sbXbbwf6fzjatN5lJdS/QuSBERvv8VjTy13p8QcwZ25+/F0PKBZIOwsD618n9HGQ5hW6WfsBOzI+RIOgCkh7vgFM1Ts0kcMmxlVpUQE5XLyTpLbxZi0loY0HlEJJMOYPdrnI4oxQj/onmPhrc5RLmYMfggFIcvnw1oAjZWtyaT/EAL8S0VYxIZQaDN2uDskPZZ1tArpFdJeysLwIEDthkQ/jwkVDtcbFbGkBnTy0+RaIelA5ZEUAPMNssbWr7yhYmPgK5J+2Sb24MukWNb/gkUMrI25yX/OohvfaHhQJi0YTlFFGYDaaR5xhJq8cFS23pJPH2BoPOzwIlrbVF98Eg8U3GTjxOCaAfBD0+oXM0P+QPoFRWC8SPapWDNQ8SVUq+eHsqN3Bu8KnzvZdgr803hvozQuhPfueW7MWNgFVi79B0XgeOImuv4w2uvCUYOIihu3IVzV9VqkmaFafjRI8/2NxjY7N9O/1aHIHvnlXfeC9We+W4jQpfHy9+whR9kCFH4j46Gz3RiUkcNNdBo41Z7oQguDXeErUr9Vdfj/QSKUYCJRwokBYm3AH9sqAcd2BfO8wQ5dI3QGapYt7/zQqTGOHp1vUQKZC3JpV/hfRkeoQ633nUhumldIA4kIkG3+9ZYFymO0cpk71ft4IAHKI88is48gDnhwP0CKuc1fEnzIx4z4z+RhImUyyRnd//2gxRGtav2+CAQxXnQz4uB36JNfT3v7ZXV8D5cN5tcnpD4UjZII7o8FOg7QF2gZvG8i+Hyle4ZE4otaNMW4V21FaGjCrJTTHAE6GKlK274XWY3V8zRsEo5/NdKmf/XOPWZMoFdPIoJu0Hj7svGLDPswKIuXTlH2SF+obvoj+QthQcfT7jIaYNJ/8dHFOHpcHoC1MgOlJhDRiHgF8J2jMZ1tGbzzfyTBgZg8Sd8PUg2npN5kUIfVj1RZVexfNX4hqekuC9sYuDSnoR/OgYOi9n0LLmpqqzg9mI3u7r3qX+wsb0gI94g49cJj6SwQCgt04y5wmws3r6efi8QJ8DMPWL4P2ecfwqUo5Msc4O4iyKo42aURc+h/wbxas+Xh5WZlhwJ0Fg0ZBclodzX9R57TXqrPpIvEJJ29eOUq5/9IVZKrYmzo4WjuMxetnq6R8Z2nXrVzDHpngHvQQsI2SrW1hpHIFsw4lvOthJd1KsXZReL+WpPYPYTtp+Mz4f8LXUFx+VsEPE0NE3d7l65p403tSQWUCagDLMI9yzHipyhD/i3FPymMwVd10qvmJfPFhKLRAk7sLkTcImD3Bd6QvU6rYgoYSAKGvFzZTFn5NEoQ3XXsr//Q0mF1OacAk26AeKiO3W/7QhCzoMkkQcN0lclrF7bPj80Totw3BFY6q4Ee9tI7r6LDUsNqbXUCQNSagTimfbhn2IYmbb3RnYAbGD0vnFHJbEORQOQDsYY/KHFEU5CRpWZQtHZ1N1UzPTTTtxQa2djGK609B3DDPCjOnaujTxcZXlc0HueRHpZGT/tlRi7wehEk9mZz3QlbRa6l5t86YrXlnYsktbJ4TRXT00sygV348xhQybf9OwAdr0Gg/VMoFv9MuGq6mfBunU0tqps4nsNdICrekWFQqiVIY7PNSLij6Mhr+CgswFFSgH4w7toHIhkMquM1xpld4gVHuzyx+2TwWaubX6dG87rUeh7X0HUmgXv65L2uaSlpc/plMZuxXrEfsr9LQupvQsLRfu1qrBgCqDycgQ1CM6TDkTDKxgsGb/sexKkrc0qs/C1iNJcq1uHR2ZyyZUXjqOMSNeEJIi33abxuDY3Lkx8YrLZFkOjLE8Yrk7kSUPWYuo4Q7hRKfWZhsWyuMZ3GUm/JhdF6EsM3YgQ/SjKPWZ7qp0FaRps8LfXAJdDn/vmENzoJTt429ekEILAeJ71ASj+xbRUc5ezjwc09HDHmsejtXTmjn/KM7Td1aMj0sKFNr8bySwLa2ZK8eJkwBvglu36uaHQT1xu1L1JjWymVh7nO4zeXGroLPR6lZkfYEKYEq4fx2uxyJrP6DEAzlZCgh9V/490HtLX5YJBp9hWSBqPMi1FbPjjxMe+K7ToYvLAzkIiU3i2/2id75ixlVaue35r+R9AOcSNJlotgp31e5FvjdlFqV1I85V6UsrEFoJtBxx3feSMSvMXAo+13jBkibADU25aKDcTHTHtmyX17PvN6yu6n4dKeZjkEEScQUpiQWnXWcsHWgjgZJiUontTavaKpsHDRFriHJ3q/u6BzgmQ42ldXkjSODqjYAXGMyd62sSt3iEMCNXnz92OmFL2wWk8J/yNDO+kPhalybUxPwuGetLYYV8dmDRM27sstF01rvVLROTC+3Mlw5naGUof9eFfrhKNrEE9UYy5mZlvmAuvGL5dSy0PuLUA+CPmgVJFHFsOYm2BsF6HlqurjzgOcV2A78Yk9bjqRC03yBl1uhLoQjTyXT0C/RM5rQPEJn/mE3PTwjmlRj6DKwpmHFF0RbS2EfT3vloqqfvra32gLkqNE5U2vOcD0pO1Gnz3ioZJ5NpIT5Auu92gV6KNRCXGQwIdCwozyjJPT15sf/nl4HjghWwX6VKjD10rMNdq+Ro9+h46NCtxL22MtsnKmxUbDN4r3/M9pmm+vYds7bZVfOivbtBVqMP0xuAC37fn2BO7sZlrTql3KsmBMvKig4kMwrZpuUOdFTRtRfkKpsgvpZ1iyefqPlf8IH9qiC2bfhilrsThDThBGgkCvEDrSaGOwHhFymx8kgxGZ9YHM1DMLOd/vRDTo6V2hMkIuzbh4LruI4dQVZHLx7v9vNd1GQO+2tuVkMpKzf96LVLRq5xlE0OF0TykDNsmpKNea6pMgwdcjp7FjVfCXXiqRx12Bw9pkyaDGevn1cYL26XrBcL/45rwNm5VrtXnM0K6FOGckRUQa+w51oPqncp5ejCFE3amvM+DeYsu8R1uWufVa0LOJsUQ2K4ckJnFsEMioywX27gv6acu5P1TfPqI6Z2wJxZtwsrbyiEK+mHWPFGbIR8k/aw6BirrMWKIJ4l+WecC8zgx9sIcUmJzXDLf9ZwiHfkgo2f8eqcAiVAJt7DXGtcsYDpbTSFFeowTPt156ziSYcF9ZLa/1QwhyeWQaqSjLrtgJIiotrdRbR25l49zb05wl69EBGPzvicc1tQ9wNjlpycX2SyvqKzYWNfQk3PYML6HXGZzZ9Q+UFjjpxOZtt1t/E5QWP152f/wLTiQ9/OcKqkyJ0wylzHi2bYdSlB/z6TOm2OCNAVyziceqHvxHkc5aXT9uchDTo9t7NZlJLAwuX89ZE2jpeMwzhw/Gb13rukZPFF41XTXtwkIHuDUKWExK+OuPX2KqeAJEh9idR4Blm0v+kI3X2k3gD7r+UkoAZmMS5IDL4M78R7mnrUbdl1tdO4I9hTDaKULTjRG7Rk668HYhAiIsxecHBaDDD68FqKFD5C6jQ6o4X+jpVesjar/VQyDsZ4vS6R8SrwtYCTZZs/gcGm1RFS4pJIr1JdB4e40WMEUG8XRYH7fFBbYcusCbVOzslx/7bqdEtKps0/pNz2yXdFkLCrDDFYMbcCElo8i9cc8IMiXfoZvTFAfZ74+XwXvjiYAbnr41NpCZ7HZsAtIzhJ9LIiv9K/VDk3Y5ZSCdJ3AWJvsc4nCfya+7T5MnTIjJGoyoEeV+mSQoHdXJfMmpMdHxRcidpFeI+Z/PHaJQgzFiuxQq0n9lV3rkvnE1EfJJ8T2+HlB7weyULUgL5v/PmdkDJp3wEEvkEV1gPbreI7512dAI9tELbwPl+O/n9JduuZYXFMh8JHl7GbtV4XcHHUkkaTGmuRM8j3T2hA8sBf65Xq9GcXUPUEgL3pR0eT38hgj74FAuDezWMGI1U9O6Jjd07b0Qr4eZ2p1djncvhuWjeon34fQ6jr22E0FHTzpgcnpDfF5Yx9DXV1Q+BzpPfFWHUpKiYo5ksgMCrrGApIEWxGDINBKxuyL/5RgRsbepKIZhlrYBDlIuV86cp0MKFc7WYs8+0cJvDgPMwRIjy8FXUC+2ya1g7y45EPqbz9P71W+Ll2dE=
*/