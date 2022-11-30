// Boost.Geometry (aka GGL, Generic Geometry Library)
// This file is manually converted from PROJ4

// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file is converted from PROJ4, http://trac.osgeo.org/proj
// PROJ4 is originally written by Gerald Evenden (then of the USGS)
// PROJ4 is maintained by Frank Warmerdam
// PROJ4 is converted to Geometry Library by Barend Gehrels (Geodan, Amsterdam)

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

#ifndef BOOST_GEOMETRY_PROJECTIONS_PROJ_MDIST_HPP
#define BOOST_GEOMETRY_PROJECTIONS_PROJ_MDIST_HPP


#include <boost/geometry/srs/projections/exception.hpp>
#include <boost/geometry/srs/projections/impl/pj_strerrno.hpp>
#include <boost/geometry/util/math.hpp>


namespace boost { namespace geometry { namespace projections
{
namespace detail
{
    template <typename T>
    struct mdist
    {
        static const int static_size = 20;

        T es;
        T E;
        T b[static_size];
        int nb;
    };

    template <typename T>
    inline bool proj_mdist_ini(T const& es, mdist<T>& b)
    {
        T numf, numfi, twon1, denf, denfi, ens, t, twon;
        T den, El, Es;
        T E[mdist<T>::static_size];
        int i, j;

        /* generate E(e^2) and its terms E[] */
        ens = es;
        numf = twon1 = denfi = 1.;
        denf = 1.;
        twon = 4.;
        Es = El = E[0] = 1.;
        for (i = 1; i < mdist<T>::static_size ; ++i)
        {
            numf *= (twon1 * twon1);
            den = twon * denf * denf * twon1;
            t = numf/den;
            E[i] = t * ens;
            Es -= E[i];
            ens *= es;
            twon *= 4.;
            denf *= ++denfi;
            twon1 += 2.;
            if (Es == El) /* jump out if no change */
                break;
            El = Es;
        }
        b.nb = i - 1;
        b.es = es;
        b.E = Es;
        /* generate b_n coefficients--note: collapse with prefix ratios */
        b.b[0] = Es = 1. - Es;
        numf = denf = 1.;
        numfi = 2.;
        denfi = 3.;
        for (j = 1; j < i; ++j)
        {
            Es -= E[j];
            numf *= numfi;
            denf *= denfi;
            b.b[j] = Es * numf / denf;
            numfi += 2.;
            denfi += 2.;
        }
        return true;
    }

    template <typename T>
    inline T proj_mdist(T const& phi, T const& sphi, T const& cphi, mdist<T> const& b)
    {
        T sc, sum, sphi2, D;
        int i;

        sc = sphi * cphi;
        sphi2 = sphi * sphi;
        D = phi * b.E - b.es * sc / sqrt(1. - b.es * sphi2);
        sum = b.b[i = b.nb];
        while (i) sum = b.b[--i] + sphi2 * sum;
        return(D + sc * sum);
    }

    template <typename T>
    inline T proj_inv_mdist(T const& dist, mdist<T> const& b)
    {
        static const T TOL = 1e-14;
        T s, t, phi, k;
        int i;

        k = 1./(1.- b.es);
        i = mdist<T>::static_size;
        phi = dist;
        while ( i-- ) {
            s = sin(phi);
            t = 1. - b.es * s * s;
            phi -= t = (proj_mdist(phi, s, cos(phi), b) - dist) *
                (t * sqrt(t)) * k;
            if (geometry::math::abs(t) < TOL) /* that is no change */
                return phi;
        }
            /* convergence failed */
        BOOST_THROW_EXCEPTION( projection_exception(error_non_conv_inv_meri_dist) );
    }
} // namespace detail

}}} // namespace boost::geometry::projections

#endif

/* proj_mdist.hpp
oEYgimSM0SXsj0BvXOGE4li0MLC4JZSHQtGyN80jrXSnnDcyawOHSKVNMqK6lve1NhiFQxc3DbeOZlZPUnJPHW6dhTWOuzN0fWw/qbjKrt3fvW+/RfbWU22kqLH3RqerWYsOVhMe1ltDWhjEQueY//XVVr8u4l62rPt/0dlz+X/EQVSsPHYdR/5DOaG613DryLdB/5E98JN9DwP/KKbm5ILETdgLWAy1/MDt1orV33Pjw9rKztG2jeDl80sjm9QlQxpImEIqGunB5/Rrbo806Nxzh1/s82JdOKQqhkXdNHdw+xFxmzV3AKf/pC/ajpEJ8eVO+uczkfbcBdbzYNjn5iO9dIdlIRzTujf3/b79nfuj/9LV9JBLkiPcqQ5Aw9kFY0M6f5t4/ppEteP7iLdiTXSn5y0Eo+VQJzU1BF/EWojk54R3yJhSTPxRLg2jJJj8jy0ISztN2TIh3CcYZYjnmliyy7MNE7UyxrpezSLgFr41CQgJcqSpT+Axzk1IKnWpxhluhHGQBpX4PVeFIXDZk6KXUastL+357otp0a/Q6Qu250la8rf2t9kEBp4ljhKSwKKkinMY2N0ReTr13EiMszx63kImJWyG20fsFHm+Ez/g1vSNpxjUsxYQNXerszrObU1qBzJtUhCbAGwErhytnIRTMUROL66YFz7tJaivOKuhznjwoepSyBqYFII5vynBtVkZQCkZ65ZJ7D/De3K8xv+4/glajsS5xzO3abMoJiNJNw6ovvfWdO6jLCt80ZmZqeumVz7pfzS5FKirrUkTsvn99pkw7UuY7nkGjqH654hevlwUWoWopFKurkbVrjiKMU5u0/VlHwSDX+XyOSxg6ZUsZ4f0dnZl3DRYshC4sBaap8eY/Pf+DI6e6wj6X0iWTRSFTCJL1hP3ih4MORh8zQwb9rEOXra/D0Wn2HzXO5hE+1jRvhCrFqrxtZkNT+9eunKKFLYgDgA79humpbpsQjYrEpMIWhwPrSXc3ELCgEii4urbliLmVHjYO1frb95/97kiTURab0eR957rz345CS3aUTO5KVDcVtSGDZ6+Fmygxb6kISSPZfeaY7UqmeUlUYGq62JMT/Wo9LZkrUchyLsaaFLwFGuY+mm+/mL0ua1D/aIotK+TvdfnIB7CEpmXKehbhqiycPlC+6NIy9YRXO8XnBEZ7gJuGxbqsLqBJuDtnmnZDWZkjnk+GSQA8vH/1kXhMwAUiQ7DEYsVYH5D1tZjRgV3XMhNZq6e6VGm6uwL6NJDiKFnzWEzEpTh5GxhC47M0Qud/pP3VefZpVQKrDojUwqcBkemHKDmEDQiTQCu0CYEfxGAuwTMaMzxheUsT2NbtpoYaMWPJQWvBPgvuwrCvmZmrCHkVyP0KIAo9J5M1yrZqNQryF/Oukoc+3TPY/6Zuggenlhd4juh0YaR11ngC9Btf9WStPxNFU8CmA/QOLQXOf4k7dJCP8p0i8i0DrSRt8d0jpi7o886TW+WI3egKAPf3UIglAsRSCFsXU34bG9Q7ELrjKUcth2pwQayWHRT7ciBrVkV+EJJxJ9d2ITVx+EoTSCg70GPBTJiWTkszYDtH8ptJiqFxuv7xdxJWn2pZYMN6Km7um9FqGOqkRyW2bORu/BwfZX0hEidPwoHQyVi6icCkthHCep2IGao5akw6tI93i9uhaNKN6K7EUuau5WZVuIaT+SehooZnJZo0jmTEY3o7NyR4Awkb6WnI7g7bDbLd8rOv28QXfkXEw8t9165lkLlyvsEktMzN2lrbtXQMRP0R4CD/qoFVOUsHXTvHEykKlCTYDiVbbnz5CI73kfaFdVLVVRQwu+uuSI1uo7odem4uJAY/KmcRhk3dlhR9lIQZcUpelGppLpbs9KlsMExBh0SO/WO+SgLBcva9RbnNWwJUerRSUW1davFhUS6R8XMtKoiJKR09ZsnR1UVUdiVs5R/J9FnD14n5WWZM2GYmnplnKlrwLXLk5SPrN4cdQZv2JHb629i1154voSnrn667+nMkvqJjdJ2rCge+QA0NeWE26w1BX899iZbhWBjSJcS1iYc+G+JLIvyIaBENH/ttSSPI4tXTddq2furAfAHePEu2Fj9y8KtJWL4j4/56do+B6wuzRidHNfKDQrdNL+CikWrbx+3EqMgPqU9MM9POKIccUktig5p4ERn1TYa6+AvhJy5sgYtLWsR9f69eOn9rsUBnfD7ermhnbDiAQcuLj2iO371qNBicEXLJ42z6h7PJoIt3oqmG254cqYyG5+uetYWMnugMgU+vpqwInTgRogxw40zkld3/9T8f4nNy60wWpYI5Kf4/dYMzlhpC7JQ4cBuhVpsdPkiXRnIjyveWB+aZWG8wdy+eaK9Wrq3EiCJs3Shi4Y/Q2+AkeJvukv3mVNVdOAV+P8FrDr/GFbUDTgM/jvXi0Ztd0YhA+HSD8wB7+ccaTSMT4MDro1NvjQAcjayh6DIpNSxHci6lpTbjMUAJeFJ3PFGl4vScF1s6KtozfzGKp9hSj/+KZw0HMBiPPVanqiyL5GQlhcLvgCzuJAodiaTU3Q3QCGEgT3Mpivl1LWmq+ShnA5JIdOh+YhexHf8hEkhjuW3FkjnquJR1UPj5SY46h1WjpksAFsgSMmZvhnNsXKHdx3HP3CytcdwHF87Z8fibB50y3Q5Lq6/FUCaVhuLABFj1AU430RP10BPp1Lj+7hUTIbeBfQ2hZMZ7QvkVuqooaoHCj3JELMeZgXUNTmxyo4PzmobGLVly9broLWvSkuCl++nBW8TdD0PZgeosggu0lKpFLdd76xSr/RG6tQNjipxTCZeH3UWqZdMs7hMDL+x3mcKQrvCm4NxoIIAzFiIuOcJybVxF3Fgxe881RhZ9dg7Bhe6XqlTpgn+NKBHHcB6bSQ3YhG8bLq9bOX7z5PnK2Ggvs2LRJRFckeAonquIzo+NdQCrL9kQTs5n134Oor4P5OVLiAtPAm711TYIxeCz1H0c+NnjuJ5WnrPPAF6qLGJqvP6NFq8hAm2fdVf/+lSH+LbivymHkYyLTeW0RPuxLZYPkaqJMQo+kaKrB3wmqGgHBv/sP7h8ULQ6wEUXgZJRLuYd9kHbrEHbrMHbrQvJCRtEDT/uMPbtXN3NE2QN1wXAmAi7uQOtBLB7lRtAXn3GBVheQxkrXxylMbWwSWjBlJxa4exGr/hneK01UN07dRw2hhHMdDLzeZqRLcko0yyTYw+QDS3pIOF27YKlZD1wwMtP5cekv+A6p0Z2YEBjc9GzDP/+8q0bBj06WB8pGymCNNO82JMjZiST5XexhUJ0h+DVZr35dWBf34OaEM+UuB9aY0Ft6bMKAoVFHbT6PEMhtpS+22AUdhqktVBRYpal+rJtV4kSct3QGo0B/TuBOSTpOOm6vwuAjzmUGfjw7ML3+in8fFWMfPQX8IZ/vCP4XUwTgcoQmYapMXLYQjYMWUBOHkDMMgtNmYCkM15FqvptrHaJoBwFWovUSAv/rRvpBcm0qU/Z6B8twhE9S88gIgyeaoEFOX24TjI5PqyoWBh/ZpMWoZkxuK2PsldbYUl1yBQdfjG2f/hjfkQF2G6/eHiAsUtuScEIjiJ6a/j7jA3DAH1W0KtwCAexXANOy5MKRoYWufb1y73R6fn+u9BU8GbiN4WNswfSCZ+Sqx4EnEBdzDTk5Gi81kMsg5y5XdWc6lEQVkdTxJeU5S1YB/04BTRB2FVSIJ8A8izQv4Hr1GZNDwkqM78WYpjTChheVmNbqF1cez2cCUzP6jzk6k8EB6lDBbiEDjyqEdZKxVH/v5onc0WN3Oyl/pCQRojYrLlfLjXAmlcwLG/v3dFvPe2mJ14jx9yPXgH6MqDs9mLZjH0Dm/7g78uzOUV5ZY/B5+d2JsrKM8drvVSfNhBLuBH/B4Y1hBUF9qkPvEu/iene0BOTGTPK9fKZfmkT2+qUBkBknqZaNsGP9t+y786BfRDY+EHXLy2enGz/WBawRr2Athzv4E7/fQeCfEfGDdC0EU5HGFPgzL9OklSJjSw0sprf26imfvxnaGUM8SF+jTUdciGPyJd2RDXIw77ME4fiBqQMLuEqbAoK3mNTZZCo/VERPs13lfv7Ssg5veRTUMCFsacMQl6xkZyARTT+5NvLM9YfLaizA+3AazcHC22pxVIjAWZQqs2HExA8+tNkqNijGJ7ykWfLMLxPrOjH20JDZaUVIq1XrOduHAN2Qg8rbNAPYFPv9ZeKK0UnE1s0cr60n0pAsZo7hezgSsxT4LwVjMVT7Y+cI0OdQpj9RFV9ZA+IK44J+pjBHVcUwv3eE044LdwbjAYT7UfaC4D7tClnRq28bsajN11VvdQv9dqNcDukgPCt1+LcF+aFskblKTfP5+9kLCqIXyfA/ZMl87VHjEBhCgPhSMjcXn7TCMzdm/sR6eg86E8n+4EZ6WNJn6CHBvi0I0i3ME4mkC5Z3J30NEcGdG7nKbfsG5nLNS2HPEHnQhaP4LU9Q6iMtLlJD8QrtnXbzIq8bZBa6iM88ZkoPeJXE93uQGw+13Epm+MxopXv2VG8s+VEqwyk9ZZ1vZoX9Y8ZLTQrZ24bThLfPb4KXE2cDFFFCYopw1Q7KQzFNJUSSUsOQlCFG4BQ/aqBff47whm0INv1+5Nf0yBMNWsYoKhlVEwgymhDSBK2Bt0C7EUVUYRLTm0FdXpu0vk7qEv+G6pmaGDT7nLwClX7NCH+rgeS6LM0xIgU26KsMMBkctQtSeN3aB0B1qU3aDvV8PRWK1x95a5I1Nov3JgkyCLwR9CGp0YaEe+aIL8sZKWLXugSOE4+2+P4dMj64+u/wx+wcKAwOiz7hcwN27Q6KCZjeepVJl49LEPzQmBM7LgL8GOx2OGrnHfudu/ac7c4Sgidlw4qK1HvVOY/jUpGZTSj2ha5IWlvl8QCEgKkg4bHHPgQbfhFv3GEfFte6cPZYyuuE52nuCHg4rXdfCCqLwpKWO5Gkcuh54A+AalFQAp/j6rvrsA/XpmNA/g8FkhlIbMYdU472LxZZl903kW3JSkNho+B42LvXMPqdwrWGJ5PPQ31Y4TYUvkM5gKKrNmdXgDuDNeknQZkfq7iZEE9lQ/YrcTYqyt9gZoyVj8I2PZSsTmy6KSgc3LwZk+mdEFmhH978wNNWVDAEQyB7rOe3ghgmcoG5lFtzuj59NgVK/woEWAHKdXAlu4Wn/m9odPCUgs/1Ic2Nkn+MfzOK0+FWJgeIgLoOMe6u+lLoCHvuvfOmZmSUe9yDrxa/F8yTb2qx1fhMeQLS7UCMQWn0NUz0J4oPo27yuaF3cxBV7jlLXEy25UcplxPbhKtVFfByraQMWSKdriFfJ1yb3TUB2QL947bYB+jMsU/4M1s5Klm5f39AORW/Gj4LQIiO5+Hb+zGJndJt9D2+uYQordD3Hx2/HxgbEEcGSYMOI1pwJ1fB4WXpQj1qWGZh51y9ZDHyjGi3xlfV185vVL+bLJzk/pj8MQ4FjXlTd2TOwtrOrxAbZYKJ4Oj6+ON0Y9EAWHCjioDYag0p286KVS7ux1PQOP3q9x/6Qw5vMPEJAKoKdawsMTulfY8b2aF/juW0Xug1/EOhYByB4pr1g0jSWPxU6jdsQaIS5J0GMff/+Af/6L6CTtdRgrcCPXshF8HFYHnogAPP6JabGyGINJF2DwVGpMWgcQ09J7966/4rB/sjqnrNK4OND+CoZLoqzF0NS57+2xfn2ZOnj0VxOqS+s+LC5LihAhqf0Z03EIE2n0dD18JwZ2YJwunHB86yNqoQNOb4qa4g++ZlAESx/S3EAeygIPKe4bbq7yEeuSMNV/gIuDLf9tCV3nWD/enzQCUN8a/vqzokFupEb4Y8UREHNNlt5LxQfOFgiE9vt3QMoNVKzwrT4gXDTYSvzHPoBMVOWcLur6li3S1S1AtmQHaICAvjxW28/KhyM7wR/SCUu2ohtyrQmwIqe0Y4X9JE/6j3NIsGetsvZE9KKn9IbAtCGvDy7Lqe+VBF8ctjAEYkjwM/pfPd2EKpquOEAKqpJpHLllPC9rg1jStUv8Oivhr3sJfAmwszygd8ijAInKkH3NLU4Phv0jdROqVMbeCHA5FfimnS1YdvKs3J58b2dc1ExRrN7AJfQ4H7w2HzTqWFghWANmsL6jA1SMSVUDCqLBd/nSi2H9YB1/gLe9PYRErx7nDkvFK5IGQyZcNKBTy33brN0JoTiBdIpwLHuN9ulBz/DJvc290KMpaES/4LT1gsOLn3wSVAQrH39hpj8ghC64100Tc+PhtwCMa/hMnNLx1dTdyfSUfXB6msoEAPSqMo8FPVOXQnS7OXNqHT9sksmj6lCl5U/N9kM6Fjf356/IiucBc0tUzigRtT/8GC5iYvwZwh2GGNopBybRlVEPqcHx1HkegSwcXpSoF8mTwEjPB6iSKX9XKeftrvcTKpRI7MJ+077yWVF6Kdv32ly9Reu3UYz+xkrOp4NjnN4w+Zv74vFPUwiZmxq1LJ10+nbqtAPZGv/M6Jlchj4FCKrqPxeJjmd9rh43NsolbY8SV885InlNuD0wReaecg8IELV95chMhkvmGfK3vvkBPk7A6ihDTs+MaPnzRq/34NldKf98TtaR/x4i/BZoEsPmhz2qNzBTFCslMofGfibO7GNAmMtmCZXP5vOEjHnntgdQEMM+b2QZRFE/GJSyp7rYR84c9XrNdumKTtcV1BL5pZGmN+SQxfZFaRcKN6EObPEKUU1kHsjfFVS0KXRuk3Q8Eremc/OSJoUXd4fFlwX1msPDXoRHDfxwLxv4+ufwgcBQ0SmiGsOpUMiGE6DGp68VlAdLgC2hfRzZGafmS7IEnyMcpt2v9cPTcmXIj9tDPGwJl3C7k9VjaZxTgU4zz1lOLCSXq3k85hdMra/XJbSrE6STsCf2XU4XPBCcUy3t11ZjXOZExiiufuHuNynuhQpM5vKkZv1jH0P9b173h77kDQt2Kc9HKVsY6sgHVGn60BKsD1UmLORax+Q5/muXcZr1FyNaSojPX8SDgYeYeJunBsRl784yyctTmQvZfIJC0uRaTvSr4o13l0mOFWq+nDZ7C3LoGr62l46VExBWs1CEcxWZY3aYGuybr/EN5Mf+lvLIkntJQ9RY2tCGDCflSaIeLuxmT/Dy9gNRrSJOCdM4pgJ2+/aFsHDcYgXTbQnMJjYNEyi0+E8zD0hdfUNukN5Wg3GdrnabqpZladbmvzGDtijqPEV7qWckAajmhkbh9pRp97BK76uviRUSQSHKZLi9gMiPV67h0ALs81O3q2mSugkJeUnxQJzEjY4rgAr6PunsRVeC9Fl6061OLbLZIWULA4NFNnJaPH/jd1Quc5BbCW/tAa9z2KXUZoRxwUHI12z8okrsEvaNgSIGlswZIBXQsGR2QtHLMtD/qKkeoM0y5+MKL/Q8hpBek+ZiCMxwTHbe8nlVi44tVTqEVdLwSWac2OixbaC3YiGcgBhA66PdfnKKWyyaS9HFXXherPL2DyyJd0fuBEf48Jc+ZCeVwkjZhLi3gm1JLCIA1+bx8w3I73YgN3RiPsAjNx/aOdwbjngHCFL+U08okCRkX80G4Bweu/dq9xBB98649UeK3WtPR+zVQAaZwm0jloRqUi+SQkdDLCJJ
*/