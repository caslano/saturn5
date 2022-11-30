// Boost.Geometry (aka GGL, Generic Geometry Library)
// This file is manually converted from PROJ4

// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2018.
// Modifications copyright (c) 2017-2018, Oracle and/or its affiliates.
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

/* meridional distance for ellipsoid and inverse
**	8th degree - accurate to < 1e-5 meters when used in conjunction
**		with typical major axis values.
**	Inverse determines phi to EPS (1e-11) radians, about 1e-6 seconds.
*/

#ifndef BOOST_GEOMETRY_PROJECTIONS_PJ_MLFN_HPP
#define BOOST_GEOMETRY_PROJECTIONS_PJ_MLFN_HPP


#include <cstdlib>

#include <boost/geometry/srs/projections/exception.hpp>
#include <boost/geometry/srs/projections/impl/pj_strerrno.hpp>
#include <boost/geometry/util/math.hpp>


namespace boost { namespace geometry { namespace projections {

namespace detail {

template <typename T>
struct en
{
    static const std::size_t size = 5;

    T const& operator[](size_t i) const { return data[i]; }
    T & operator[](size_t i) { return data[i]; }

private:
    T data[5];
};

template <typename T>
inline en<T> pj_enfn(T const& es)
{
    static const T C00 = 1.;
    static const T C02 = .25;
    static const T C04 = .046875;
    static const T C06 = .01953125;
    static const T C08 = .01068115234375;
    static const T C22 = .75;
    static const T C44 = .46875;
    static const T C46 = .01302083333333333333;
    static const T C48 = .00712076822916666666;
    static const T C66 = .36458333333333333333;
    static const T C68 = .00569661458333333333;
    static const T C88 = .3076171875;

    T t;
    detail::en<T> en;

    {
        en[0] = C00 - es * (C02 + es * (C04 + es * (C06 + es * C08)));
        en[1] = es * (C22 - es * (C04 + es * (C06 + es * C08)));
        en[2] = (t = es * es) * (C44 - es * (C46 + es * C48));
        en[3] = (t *= es) * (C66 - es * C68);
        en[4] = t * es * C88;
    }
    
    return en;
}

template <typename T>
inline T pj_mlfn(T const& phi, T sphi, T cphi, detail::en<T> const& en)
{
    cphi *= sphi;
    sphi *= sphi;
    return(en[0] * phi - cphi * (en[1] + sphi*(en[2]
        + sphi*(en[3] + sphi*en[4]))));
}

template <typename T>
inline T pj_inv_mlfn(T const& arg, T const& es, detail::en<T> const& en)
{
    static const T EPS = 1e-11;
    static const int MAX_ITER = 10;

    T s, t, phi, k = 1./(1.-es);
    int i;

    phi = arg;
    for (i = MAX_ITER; i ; --i) { /* rarely goes over 2 iterations */
        s = sin(phi);
        t = 1. - es * s * s;
        phi -= t = (pj_mlfn(phi, s, cos(phi), en) - arg) * (t * sqrt(t)) * k;
        if (geometry::math::abs(t) < EPS)
            return phi;
    }
    BOOST_THROW_EXCEPTION( projection_exception(error_non_conv_inv_meri_dist) );
    return phi;
}

} // namespace detail
}}} // namespace boost::geometry::projections

#endif

/* pj_mlfn.hpp
xo+GUJzDeEkS9N4ShCOrwlScEPBR6rzQPJ31wJb6DKi4Cb6LZxYG2lu6dhd8l4Kf4n+TRtonlDshYRdG/xp0HrsDdvMukowvemfp5qy7VtTeLYE1NCrekomheWZVzJ1votwOC2oblHCthDYq4Tcm75P1ylr5otoqNlXt3tC9XjTDGbFlGMVE5qZGrzQ9k36YTctUMnPcwT3hU/DZK7i2WomIsZSLkcTPEyiXOAHLIMXUxo6hn2MVTkcXMxZYVx0V7m2+bdHXCz45XliYz4t1CiinmeVav1yYrD4kLjcuuuvVVEYFIIbZrMk2EH21nskKnBzgNbSH6GGZw2PT6afOvvLojRtL/0POudYSwi2cfFmXhLMXQYgeQISgQjE4bG2kh3h1XR1TzvQFIgMM+fS3l8ffUXF1my+xheovQaiXmAMQ7PgTFapG0nJLXQnrupoU1BRQHDCI9FHgRmwomucShkb3B4aKAkL57jeVQVJoYWQP0OBrn51u3BEhZ3/iUDmXQkskjmtVb2afZDkne9vbzYNcfo/zvhzznbxxvPjw5NLIBux2hGTcC8ZBSNcvShRxBGPMxPAJUy24meAp4oAqaHa0xZqJA8RAnmO4S4NN954XKX1eG9iDTXOzK1PqcWOVo0wUKWVpFKERyFRIVHPIhKSDh8YSuKKhHsRQpLVVw/4FKRCeKRQt1eOW8UFpEAZPeBO7whfmGjPnlS/v/LJYbYk3Uc0MXNVVZMD31NYIG+92RcnNIFNtDLRged0lNGKROH66Rg4T6BTEKIF3perYqoREzTShu8dni0iLPzNcpdxgV0SK68ZPAjEeIpG4TFGQIWvLdmIcJPj40kanOrtmtWXIDzMt4WlN3G/8gSfknKevnQmRKnsVQYOp8R0hX2SoSiETGzgiJpRM52JVQhrNAflRrui23PmiXseerPCbG4NBGLJq7oszwhYFDokKNELkO8C950UfnH60eERMM+tovhNAgN2qAYDNTpxg3swKs0NfmiUVmWB10Tz9eS+3OG3RHLhV/FdYVzLWXgXTcK0SsOGYs51cOEKPgf3XXiF8/PrgzSoJVwHp59jwzj5cUtHzO6Xs/R0yRK+ayQJp+ZKkEgOlCCdeHU6JW88lZFoofMeoZ04E0IIImxRcxRCA/czr8V6bxDtYl5rq5ZOqKwXhFLMcqA0Mpe+qETQSDJ4n9+62EXry6295dgQSlTVZwxByqG6efNN2abVzX5zDdfruegcPt9eJAYPtVktwf7NrLz5yXvXEF35qMZc81Q5Kuw/5+z27gu8244BtpfQN1V09qqwvs9hgoHF7Vrk/QH848SNPDpTva6eJaKsHebTzwJEvY4ZZFw9yzrHCdQA99+FEI7SrQe/E50LFN0vpIKF34gtvOljER14bbV4SwlJg5kG6ABnYxCFCJJIDgSU91KPotNF6n6pjtxWwaVTJ2AUl+fXrF/ylZFe+4JUDOXQd57+5HncWMLxrvvWtE8KdHy9xWOG//+YnGS75UCL2QvgGZnuZddvEj4roFqZUawtfpzhRNJ0CEa7PXpgS6sODOHXFCxgqfLVlDUkWMnD1pLl99tx/aGmXl76sJMaaAgoxlTJ+gJSSCDW79G0lxhdfcrSiNNf6+wjf3i98eUk2/CqZSEyxMidYZX7cd9XCimxOmrMDdbwIYjgA/jI5AXoveBHgmNbIQLJFdXsVEj4OSdxznH554phk9EBbr771EmZ9m76Pez1bqQqnj5ssQfgseXxQUt09y2l+wy+7qwh73D0flcfiEt+VEJmRyHKOTHWaZMPnXIc6JkR+dOHuCFA/1xchbnbhyftRU47WebE/aJNj3wJUB5Wh1V0CLwF5DuNjimXLTifL//mqNa/dvAP0x5/lfq/gExNWlUmHt5iV0PpL8ZK0CG50LPM475BrythcDwkxjgHYSSKlQImgggsN0owUtL0qLbTrEM4inx9INVVwmghhX5xCCYWZJuodSakYm6FGyWq8VGbZTMycX5KqmMxNBMFaOonEfUaWV2LTlo6IIMGJQZwTej+DDJ+Lt1gfLYoRgjYC7V1G67LVhcfGkEdUfUpbmLdcL14+v8bDA/FPuAiDG+AA2Gzcf/zT4pzqwrgNb9YsalzP4/sNGzHP5xaWdBx9UlCBrnMjvKG+HrYipWkTloKbij/wMgF9bn7lLgQyVcrIsTLh1BXEO4z85Xe9ysZph4UmDFaHDNfKwYlkgYyiQMKiPw9CFl/yrAs/XU/AZ/7X7aJfM1YlP57MTd/mPjvn/mijT/y1okU/5Ubvub75T/yIyQRzPwlBEP1P/DDBl778Kble1WxK/K5rej+Dqij5rc/P+zA8mhulfuc3EywCA5Xdr+UTFhijFrfXZ6Fh5qyJZj23nYTSsUpX3OrzeH9uICtAmZhoE8xaZSaQ8zs3S5+SYCAhrSUow1S9evnTbUa24w2fQHPI3zzBiic2K4RAju5KzmaX/0rsckf5LF38+9NOzn8s9YTBskmc4Oy3GcvU6ppjXXZCOAXbOYIGeqSfND+DkuoYWVaAC3mN/M8JEGBt+0Pqtn27WOqRmG42/pP+VHx/cwSWufxD5+hkr70kW+2QLWHoGTPDmFtSben4xlJs9eQ0FJOWHL1oG9IrSi/4B0VLopZQA2ZqYIUGdABpuiWikZNDG8184tiGNMsWUDIqYXyNJotWVGZBSxCZZNK+BZFetUZgRQd6uiHB7J3snjTlAov7eC+UxDqC3p41YSFrA1n4Xo1+jsNYQY5GMkVhYR/HbUsN8agrmCSkyH0IBJKE05MWQdUui78EsxogMikJsu2OxdImLzZ0tu7vnSpjO9N+pY+TaZ865yuULT7RMTHFjEUWDFppo6QRmEV/h5Gk0FTwXNE4rMpN9NFWH8C0rqz0blvBgTOhNu/ploQn0jQsn+VmVOQoA66UEZYFLzn3eRagbGH4jlDGT5/sN4qXJYrivmfJ37k3IB/yEZvqS5etQXHv+1gF4HE9w5EZAssbwE8g3W9Jp2PXWR/4utk0cvJFHzGk1JrXKBMANghp109Jln0cWH4H+cpZdOCULBSzTyHty7ZaSzNvwg4GsPg+ToacKQtNYrwZ6anPJhQ9aMkGT6HoHYYJ5Ip+pOgX9ot77yEbKE5KD7txMG9alU00XBDfTtzwGd2ri5VPMDUzLdvaFSRjKv2EoPbuzcMYQ0hGJRJIxqjoueP+O6ymK03MQP2mD4jFesEh+fOhwhoeOBwt58k4G2yVaz5xKj9u57vs+++4KJuxbkeH2lzj3sdthjb0Cw7KbvR4U9cXidh/2md/zXabr8flYp2zyFdO64ThT+//SKQzh4tYWIVEyU3KcHs5YVFeoA2CuME1bgafOI91buSBP7a82mX9bHkf3VwT7DfUGSACipgIaiagnqKMY4EO+34GAa29gixJDSof+CY1MEhm/5GsYBVQ8uT+SrJ6+jsw9gosun/5d4pTuozvXQslBUZ64PMG/iqeIZlBjVosORfyFVwTXPnm+lNapMngzk4+1AqKwDVa5xxNIoEJgN9mZRuBWq6EzY8T1z812d5cnxQ2AXS4qBIf/4ojWN45yJf0TWkmuU9PuIw+1S+vTl2DEVFMsgWuMLdQODvAY5DrzgWKcMZccEVm+6Ux7TTT0B6/b54gGD/3Ry8x3isDtkfVxfrp4f6fKj69YZgothgC2bY7/NsbOhpLh03SXRJFIzW4JFxEL7AaLFNkVVDH/TJVcori5jzKQOVL0O34CPEkAc9Vmrjzgss+zK5xRBJ211SuNikIdU0PDhl1jeuo5t3EXgi4wjvsz+dWkL0vH0UCqjxsytkTNHT+MibOYtpuqilfmgMjP2QaqbVlmjMOe+2EllXFO2KWma0mj9hw+RLkyW1zwgYreOtWO69ZjUjlgXMnk21Jqj9yminkSYjpmg7lG+2eVOPdDjSOR9SulPSxeY7TMzLzawqXhzaYpLU86n4xZhet7LrcgW35vBuVxXw8tz15/RY5C40rum9J+NptCjNmbfhvKNj59BjPZShjAeXDfUfPvqFHW9OnQfBWU3OshnjAbL3l1jlDehxOpZA9M/5Ggmhm8OOTQNH9Qzt9tuLMMBqev4igOZbwhRHUsQIcWmzDKJw8hntCwYelRtMo0EPEp5XXDCAPCctgdDu01JPchGi+bAHQFGzydrONKKxbSKsAT4aeOjJ44h7I9f7qIlQD7YKyZNmk4CPw6L8tODN0JnsLNVYhPxj2r5R97YoE9UfHuKsEApiKKshlFwSDefS1b20uC9eE7usA4tZfKuWIHMgU4wJ++p636l/fKa4KYGsF+KM9bXdXgqH4SmtlN4NpsYfiGjREKS6rDfyyed5yjVIHa4+SYOs/cv1YivZoYShj+OB6MiYMpj+pwzBiz5X8dZonu9JWWFZ/j+c/YK4+hqgDsayqT9B8n00I4XpNeKd8SdONNL7dtuhCcRkyATEK4AB6bcierBLm4q5HBzvB4VPMZ53f07Tr+T9tMjO+BEtEf6YWJn8+jjLr+XevfkJKb5/95wGYOiE2K+Bg8iBcbWPn+riAoqF9bodziL5gvJ3twO8WgDpvOrVB8xnnYCbkaH7IQ8BAqNKI8JhmbFUxmVylki/7SzW+T/QrD/31dl7ecvVVsFeoTd9yMcP+uJUd+l8Tw3yl/RFnf0ZjrnOBHL5B7KuF5eWTKWz3BJYJRblHAHu7uLJqgTDqZds7+Fp9ZF7W9FJ3yVmBoSODJzGGkvOW3RXpR0/hMK6EjdSqrVlP8jgY+VtaqVDO0wlGSRfiZDGcwtQ1PhU8+1VhpGQ6NtSa2t7ZVMPx+KwAi+Lv60axqBDKBFff9sBTG9gxiYsPtcQ2r90lyUpbQ7J54SUs9GS+/si8tLUeQjtScu8/fVnRMYofOjj5Oc857gU1loJWVqWmapBt6vANIT2f7J84cbVrnN92XiU91Y5+IBmBuG/m6tTY0abJG7R1xso8LivwVpQf4tSVSdG/6Ae/6JY2Ds2C9rD1qTLZtNTxSHYTfEYruuzTTf1PmdDDHljqO6jjJkSDuQeWHy+GHTD4rZz0wlVLWuX9bxWFzBjKt4aZ9tKf4oclMLVnCcvqfQLQqDechkZ93D/bi3AbEF2Q/ZsxE8Rnrf5wJjSdyaqDDJ74tYg60a84MUKX9q41PDNS0kher8D7TW0CynjD7BvRtxXf2AALJr6jSWDWsuqxAeyinKRLYSy8X3ORrD7JClR8sN4fpa0aj5rvIbTib3baZNelVtg7VTRn2JPNjLCLnnbIlzvzQUc/vklHP1tuFxW289ljKDLN2WhxVh8/uCi57C1hi9DusFfMS2z5BQYJKuDvW165VtzV7kvPtjEh/j0YSSEfxGSBUKzAtx8nAghWYgj5dhoyjB77w/83UDVOBgz5ZiHEizlMUTP6+hBjiR/X18z5SFTbkilQT3jT5Isx26FWpiQwMLIDSZ0DpIKbATjLY+wEvasYTsBG9cQXYmtgJo4xVVralFl/0S4iFBOu19s/8TqMZpgamAx/vlE1v/24MGiaveZE3NRjCsLMdo9vV6Jwx0bJNb53pgRpbkNFGVT1TU9GOrKjXno1hu5zbcggstt1C89890jX/hUp6JkppBlS4Fca3TnW9EQYKr46NoR6lksaThoy/FOWuU9JTwiuPGpbRSCBBQdTpbWFDqpb34mbhQjmr5UEYDCcQiygRvrts8jQ10NYse+GSQKufcLWSfz2EUfqbhygBjdeMJfPmpyY/L+VpY6bToDDGfWyoWRJwIjqCpAC49fCKDamlTzAu+2j4OkE27v8I6rhLLKRtdHzAAUs+tOXiKoRKko/ZRTVhJaVlyu2zHXUfEUwcwpapsMHHyoLKq2YpKoiAV113sl1IkljR/vbMSb6LEc+3eNIu9xjSzYmTIQ2xHevPHyWComCkfFHYHIiuzJBBN9bHx7tX+Z7faM8iT09AF8f/j5Oa7Y9oPPAeSJIqB+7y0VAWGKM2ijK6E1RFcyDOxgMuECCXzrB0SCI46okvJQmXvSCOfeD1jDAwd6h1LRf40Sws5QrhIP4uPWzHS0lJh3TEXuni+Kb9Qsje0bEm4B93rKp9Rfh+ffGexS+LnxbtvTM0OfDDCJ8Ovc14PcQ1S9D2uUmtJyVOvfNQ26+ZtABZHKjOg99QWt8boghaSeF0A1SbQZKxpBPCUaK8I3ND54EKWAGW4b1nhleioiukeSb5wSvNjySXStOBDVM6hzMG0KG6yjQYTv53+M7abknz/mqqO++//u6CigOngCfxHOm2ZtthQyX81LDY0O21NsY5KZ146fPSkOyHCS05SimqVSrcwgu6Jad2y62oBZ1WN0hcwZt91S6K22Megatjx0GXUDMPEsZ0FIfv//ximC7GomUUXFEMEwXADFNgbJyu/GcH1KFmZWzH+M5n4ljQuGiFtmxQQCxFmxYMKBlUO1H53YD0BWLm1A7ScPjhYYfIiduaJjKs3be4jKKy+xG43H0uXC6evHa6aC5xrJihDirMRxfV+gM62AFqTGrtjlgQNsFg30jw3QrgvE1wDMtcxTGiPNyxUaxd/8z2zpzS+jzJPaMt7DLtKs5Vub5Z0qqtV6G+CkHKRp0hta/kBDe2KNLN1s7rBcReaNynZWmHeIQ3/JfA7lrCkMLpktFX5t+MgbUKA7AoFSthsAII9e7IVcNMIa5fzspL/1jiMwEsHZlUja8VqWM6gvxCqlXhru7KKf4IOC2JzYeR+OHodbGLOCncg3tP3VV3CAFGHTvWgMwuoWHetGBEjINVZIjtFYesXFavm695riw3gvI2SeOx2r1S60LnLHWVFO2zmuB3H/JOfhDvMnfDQ7+2xhNEAhGWzlqLtwxbh/2cs0bA3+bDh7l81ZMTnc0YpRqE3yX6QFCX/j3jfv1K5U++zpQcHFypLk8EN0BasmBCII/OimQyN/MYxiOmoN0nvvRjAOqb4ehlBLklRI4YUyQAnBENHlPoYyfUmoZBKdaUhlUSPQZP0AKO58cBLwKgkGgWdvLgbF8eOsRIBfI/HyexfvA7yi+W+n7QgQ51klDFVBxhPAENGgDEfbASrH7EnmGBsC/gWfLUnuAES79USJ1c1opxL6BnVdfeuUgFFEOjhG6qEQVnrIkGRap5f66SuGwz5Rw0GliY8b54yOKNcHmePvsSaeElz+dDjSGRK5hST6xRGv5yEYBqarIKPJqSR9YfzKPDunNdUuWmvG4J7miyLshJZcl21wEZEqhOGNG/Rbi/YOqPx9mLf6FL7YVD/QFxBOqPsxXSDuT7xdJ9sH9ZX8GNWrADhQhY0KpGNCQMPjw5767+zHcdPF3zblk4ArbG9C1+L7F6svQBvp8V4XgqA4fWkqN8kdZswN/JCFf4X/wGz4XcD6E/n87nM1ra4Cy1NyYKcsUGKprACwYLBLrA2F1XtAAxgKRGSK1/2+JBlGizEhHvYKAmdAKqVg4wVFnUc23R82zekbJ1vcJex+dJARJCUWh3KAfK2Vcl9xoFkIQ6GGa0/2ZGvLUm9/M/Trbeear5yXLeYbX3K3GTNOAJivJAXYuZlya6g53S5J0GqdsKBpJiuf747sZLzfmIPgIeFcjPeAg+pqvedkMxYK0wEzbl6vTzdOU72CllhwZMnGL/Rbw
*/