/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_VIEW_IMPL_09272006_0725)
#define BOOST_FUSION_IS_VIEW_IMPL_09272006_0725

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion 
{
    struct boost_tuple_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_view_impl;

        template<>
        struct is_view_impl<boost_tuple_tag>
        {
            template<typename T>
            struct apply : mpl::false_ {};
        };
    }
}}

#endif

/* is_view_impl.hpp
DNU1vg6r0rPx41ie5vPW47pirc7zQVijy3wJ1us6P4SVaT5vsXdXlHSGd8EEXeBDMVaX+TxM1nV+EmXd5iH7dEVR5/kM5DxbnV/FSB1f6Yr9MVqX+XmM0VHsiicwTuf37Yq7MV53+Kdf7YqJus5T9+uKSam5f3xXTNFF/hOm6xb/eP+umJHm8B++1hWzdIdnHtAVs9M4b8JUnZngfb9ufXSRcwdaE13mh7FQZw5yDjFPV3nsxK5YoCt8DzboNj98sDOmM9/wDFisa/yDw+xvmn94VyzFCt3idzBXx6Su+CE2p/lcP97+/tczn9gV259pf3V5dlfseJ6zodtzu+LXF3pWXap1xecus7a6cXlXdF1p/VMn1z1r6qs9z+/tY2qe9Af7pat88UJ7rdt8zB/tqW7e4DuIabrDQxd7bp3nvdHUJZ6OFbrKv0VLN/gfiLd8lre50fdI5/le1NI1eZs/dcV8neeD0dZlPgPrdI0Xo+SzTX4ek3WHh/7Zd1DneW+M1SWejoyu8m+R1Q1eiaJu8weYoDMNZxB5XeRjMUpX+DXM8QyZm7piXyzSJT4ZDV3jG7FaN/nf6OgOb3Oz3yVd4INR12V+GJU0hw+4xVlM43wWqrrBj6KcnpM/v8T66BK/ibrO32p9bvM8qZd6x9s9j447/D5gaeo7rSWmpTnLuuKyvzrzunh3V9yHWbrDxaZ91GW+GS3d4oPv8V66wl+4z7V0g8fcb190nSsPeN80zh9/2PvqNv/wUedB5/9m/TBsgzk88TFrrau8DjmdaXmux11Xd3jyE/Y1zeFxq5xn3eDbnnJedfy9K/bEVF3iizFdt/jyp/1W6A4f9Iz76Qa/9Kxr6cJzXfE9zNJV3nqN3w1d4p2f91uhyzzyn76Pus6Ht33H03xuvuhZ0/yX/PtavwO6zXu/4nuty//piruwMI3ztq/6zdd5PuU151hnXu+K4YO6Y7muD+mOIz7eHSt1jV/7RHd0dCbTHSejncb5HmzULd5x++5Yp5t8VqE74m29R3f8ZGx3DNYNPnDP7sjpCh/z5e4o6joP7NUdBV3kf4zrjrG6tLfrf7U7Juj8+O64FlN0i3fbvzumpzk86GvdMUsX+TeYoZv8wAHdMVsXvt4dczBV1/lxzNX5A70jFuoKX4N5Og7qjslYkMb5m4d2xxLdOszcI7pjsS4f2R1fO6Y7VuvqlO74+nHdsSH1d7rjqu95x3e87wndccF0a5U+e7Jn/LF1SOOnuOaM7liR5vMOP+2Olq7xdqdaB3OKHDOtjy7w1Rirm1z7mefTmdM9F0q6zWPPtla6dU53fPaX3VFOzSeca0105tfueb7n0M0LumOXC62PLnJfzZroMj+IebrNf7rYGdCFS6znpd2xVFcu644XLrcWuji/O+6/wlqlOVd2x7gF3ZF51/X5jqu6Y7Pxar07nr/a2Ujzf98dN/3BmujMwu44/lqfMT+u645Gozsm6vwt3fGZO+y17tzp3N3fHeN1ZYVnf6w7Juni493xxCp7qptPed/V3TFat3jXZ7pjZJrDp2CGrvLKf3THGJ1vOw+Yrhtc/Vd3LNLNf3dH/6veXRfXd8ftb7mfrr/tPL/n+dOc97uja7N92eh9+eMfuG6az9lB2cgYb30kG9cNzcZm4+VPZGNiJhsj0zhftF02lhvPbJ+Nm7FMt/mUrmys0vnubPwKY82v8+3ZbJR09GTjTExP4/yF3mxM1WW+uC8bM3Sbd85lY4Iu8sL+bMxKPZCNrfPZmJ+aR+2YjabucH3nbMzWpV2ycduu2Vic+tPZ2HY3z6Nb/NEvZWOdzo/NxgXIbbJuXN0nG4N0FLNxKDabU+WHMdJ4m3ffNxs=
*/