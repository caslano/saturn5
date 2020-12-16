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

#ifndef BOOST_GEOMETRY_PROJECTIONS_ZPOLY1_HPP
#define BOOST_GEOMETRY_PROJECTIONS_ZPOLY1_HPP


#include <boost/geometry/srs/projections/impl/projects.hpp>


namespace boost { namespace geometry { namespace projections { namespace detail {

    /* evaluate complex polynomial */

    /* note: coefficients are always from C_1 to C_n
    **    i.e. C_0 == (0., 0)
    **    n should always be >= 1 though no checks are made
    */
    template <typename T>
    inline pj_complex<T>
    pj_zpoly1(pj_complex<T> z, const pj_complex<T> *C, int n)
    {
        pj_complex<T> a;
        T t;

        a = *(C += n);
        while (n-- > 0)
        {
            a.r = (--C)->r + z.r * (t = a.r) - z.i * a.i;
            a.i = C->i + z.r * a.i + z.i * t;
        }
        a.r = z.r * (t = a.r) - z.i * a.i;
        a.i = z.r * a.i + z.i * t;
        return a;
    }

    /* evaluate complex polynomial and derivative */
    template <typename T>
    inline pj_complex<T>
    pj_zpolyd1(pj_complex<T> z, const pj_complex<T> *C, int n, pj_complex<T> *der)
    {
        T t;
        bool first = true;

        pj_complex<T> a = *(C += n);
        pj_complex<T> b = a;
        while (n-- > 0)
        {
            if (first)
            {
                first = false;
            }
            else
            {
                b.r = a.r + z.r * (t = b.r) - z.i * b.i;
                b.i = a.i + z.r * b.i + z.i * t;
            }
            a.r = (--C)->r + z.r * (t = a.r) - z.i * a.i;
            a.i = C->i + z.r * a.i + z.i * t;
        }
        b.r = a.r + z.r * (t = b.r) - z.i * b.i;
        b.i = a.i + z.r * b.i + z.i * t;
        a.r = z.r * (t = a.r) - z.i * a.i;
        a.i = z.r * a.i + z.i * t;
        *der = b;
        return a;
    }

}}}} // namespace boost::geometry::projections::detail

#endif

/* pj_zpoly1.hpp
Q89t9T05hvfwXUazPozjtg+IIw9CP88lD01O/JCTkEXa/Rk9vRZdPmsavuu3jAMZHNJOPpJ94+HfsNbY0nvQnTOfQK9tg7/5BeOBRnf+Xu03ed6O6L+BT9MGOZSc1cjQXHKQE8AfDe9ip7fFL1uwFtvyMPPExz4JXt+KutU/4T8XMR582BfwKTNvI2bBJykeSoz4GrmLn/GXKskjonM+JLY9EJ9um434wazJDZPJAxwFr7AOz3zEGuC3bf06ubd9sYU56Lh9sc87o7ORyaGsRckV5AHJDeaiG7dG78yejQ+9K3Mn7uyCRrG/UrYtMvVX9CA++PbY0oUnohuWKz+DvZ9/YJe74C1kfyCxROWBjHkp5xKWZ3m3wK/DsQl7Yh+2QX/+aSZ0gI/vvJq9vhr05aXIOHnHolWMH/0yeD1+Pv7qEnyqMmxxaSa+Kusfw19ZdD9nW1jLbWZAG+ThPnC3Pwn+Yi7ZJ2DnDmFcWeRSviJOZv8gXo/fWoN/NQB7mos8sK4XYqsb30V/HIw8k0P6hNhmHXbsR+zFiO/hryb2cTfiay9Dl2FPXsPfuNNDHuLEJvhn56/Hlygk/nwYnZPPmvVlrE9h48iPlKPPtrgQeiHPWfuzrv9A7hljy+Honb8x7qXoEnzmR55ljV6nzd2Qedb9fvTwIY9iu9AXq/Gtdq3w9H7CBuxWxbWsUQG/Q/OXdyMOYn3fWMw6HQYvY6cnnIOvBl89XYRuxDb/fX0m7bMWN5MnpI8G/IUtXlH2iHzQSnx4fN9B7O0tGYdOwJ4+dCg5NGxZ4XHoX3IXf3hQ5c7wD7Og6XRsFLKxgrVZxdzuwK9YG0eOxzBn/NV/oaf7/Ad/+hfkCR33JPz/y5nMZwo8tpA1goatKod2CPPCptZci1zA62t/D53GojNGZrJHwxmBiYzhTWziWZxHykX/k5duYs924q20W4IvUeiR44R3fs9c4PHL0JPnHICftAM0wy/OZ12zoMd3lxILFWD3nyYvORP7SE7tbMazJZNpfgj7jE7fDt13FDniE8gLDPkT+fXJ6LCl2EP85LfHw4f3oKeJZxcVoyeIU+IVxKt7Y69od+EL0BfeXdIM332PHlL7JPDkI+z1FuGr5WXDg+iYE6m/BznF1m1VrE675FLq7sQXIJYZ1i/DOw85+Cd27m5igb/87J8v/Rr/Yz3+zEXT8GWPQAccjt6lzjvEI3m0N7CRfP2W7KFtDX/9jO+0A7z1OP0ho+qawB4vEk8Qm5z0G3wCYvJW7MJFU6FLBes1Dl4ld3dIGb4aeYQ1x5A7uADZ2of1YB1Pwf4fhe/8Dvb0V6zZJRvwRW/DT7gOWlZlMT5id3TfMM4sHH0/tlDl7WfjFyC363eBh/HBLic2uvUf+LI7YoefxJ48BX3mId/kjXPg393ZSzoHXXVhI/JIXPZZPmdgBmfp/PPp6PkH4bmT/0b+Bd58dBd4nrV89Hzmiw1+GH9pZ14VW/ch40KWbke/7EFuriabObaoXBaxaj22h7W7ivlNYi2WhzK9Rfvx9xL2qaPs+R2Pnc9jzRvhW+K2CfehH48hvmUdtocfj8TeFvybGLaYfAa2JZ/+DmatdtmJPNNX6EJk67EM5A5+m7gNvEH7meOJr/eAH+CpLbD3X9Bv/FX800bmii1exdo8vRIZ4Pfv0NENs8hVYY8O4//3nkmccy95kH5+3HgGMn89Y3yNeD2TWOyTInJEc5R9JwfLul0GX428EJ+YfONj15CbuxG/diz5qOvJDaErD4NHaphT0d6UFUCf2fDNjdCNnOfTq/GfrkPWFhKz7oFf2x/fhTkMOttjn569pBPQccj5te+w1sz9d9i4vAug+4nkJ4c=
*/