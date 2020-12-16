//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_63EE924290FB11DC87BB856555D89593
#define BOOST_EXCEPTION_63EE924290FB11DC87BB856555D89593

#include <boost/exception/info.hpp>
#include <boost/tuple/tuple.hpp>

#ifndef BOOST_EXCEPTION_ENABLE_WARNINGS
#if __GNUC__*100+__GNUC_MINOR__>301
#pragma GCC system_header
#endif
#ifdef __clang__
#pragma clang system_header
#endif
#ifdef _MSC_VER
#pragma warning(push,1)
#endif
#endif

namespace
boost
    {
    template <
        class E >
    inline
    E const &
    operator<<(
        E const & x,
        tuple< > const & v )
        {
        return x;
        }

    template <
        class E,
        class Tag1,class T1 >
    inline
    E const &
    operator<<(
        E const & x,
        tuple<
            error_info<Tag1,T1> > const & v )
        {
        return x << v.template get<0>();
        }

    template <
        class E,
        class Tag1,class T1,
        class Tag2,class T2 >
    inline
    E const &
    operator<<(
        E const & x,
        tuple<
            error_info<Tag1,T1>,
            error_info<Tag2,T2> > const & v )
        {
        return x << v.template get<0>() << v.template get<1>();
        }

    template <
        class E,
        class Tag1,class T1,
        class Tag2,class T2,
        class Tag3,class T3 >
    inline
    E const &
    operator<<(
        E const & x,
        tuple<
            error_info<Tag1,T1>,
            error_info<Tag2,T2>,
            error_info<Tag3,T3> > const & v )
        {
        return x << v.template get<0>() << v.template get<1>() << v.template get<2>();
        }

    template <
        class E,
        class Tag1,class T1,
        class Tag2,class T2,
        class Tag3,class T3,
        class Tag4,class T4 >
    inline
    E const &
    operator<<(
        E const & x,
        tuple<
            error_info<Tag1,T1>,
            error_info<Tag2,T2>,
            error_info<Tag3,T3>,
            error_info<Tag4,T4> > const & v )
        {
        return x << v.template get<0>() << v.template get<1>() << v.template get<2>() << v.template get<3>();
        }
    }

#if defined(_MSC_VER) && !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(pop)
#endif
#endif

/* info_tuple.hpp
yu5LJpe1XPUjz9JpltB1eXnokQ9t+Onwlg51c94omSVV8hy3Xtpj9D2Tegt2E+MlWOeLDpMlOsyLOobpQySGn6JIEfJhWUnD9nF6je0lvXgHRfBVzKTx08u5D02VuZs4F3iZO17dV+0M6Ep1dAcK1RxxK0Co6ADGsELri5yTJcI08+7rV5dFGBTO16mUpku22pNEF+iZ/kKZeaKJ1H7lv5QjX+vALkpmr2b4j7OgW2BIxrYuTRY7wAwtyuDQwQifHQFK3D5sVi/QDqD/UYZG/0iapD+P6cPrDZzdP1t21MvopdxdOuwWBeuDzNq6Z5LxZTR1z/hSnwstgHqeywOoxY5qjzmjOjrMcFVE/kzCiYg5wSNxwclWlxyqlM7m0m11j7GiW1UNKWArk/yDlfwSMhcOCeOXrnXIL4UnD9/V8GmAzyrAcyVgnq6KP/xK1lt3lUtzgY9+45bU01/rI9EXmfrIwzqlUYrSX8jDabuemaoydzpZ8uwgHzMUH/dyNgZOKRgGeFboeIxBEk8BF9T1oLfCM96J6xOnnM9GxAUxtLlQYujvNE8fG7TpAx06eut0Zw2RiE84NMRvnach3nGBkh976n0/8SRjwu4D7CkA+vk5GvbEIewvy1NyOZmxYX7BrRwXfSJF+p3Nqm1u9Rtr3HKiGSGUldMfg3QdX2fg2lxihaXEAzAuBu7BsdrJ3m9PTQIoSAGbwLJ/P5vA/9Jf0PzXNUcerTUh5bw9raWDQuyy/1Ot8B9eIuE9BL9YwU+wB3+/gm9K8E8NlvDtFbyN9y0Sxf1fwuSXJxP4PmFUstibwT90RaLcy27pqf70qOSZwsAgztLTPYWxVArf7G8WeAF2zm2HtLQZ2SJ8/NOLBUOw35p4dpwjU5qS09PVVncsjJGYCPtqnHgxCphWrheX691fWq/Zwfi3MNdB8SiteCsu/mM/WRzlhamSj/qicwTUq2cFoU6kKag9GlSKDnXoEgG1ToOqZKjbNCgfg6zPFlPxV744WSyvX30u4zfgT4//PV6Lh7DzVFvxGTqNt8Qz+GGK7XgGH4zT6GXZo/fYOAu9Ffbp5ev03u1qi94wK70OddIzW8l+vEhZ9T+7RHs7hlcUK6AQv/NEp/B/EkfGsN2UHs4pUj3yjKE9cDIShYT5h5+BSh+GXnRtCs8IJi0+B7eLbeS5VAqaqCuWCkNXhHuKgfGBMZIvR+H5zBMdv6YTA9deTgFbmMpvYLKSKJMZZbJEmYzbJX53ZkfuSXlApY76Lhmr6nvuxWHe6jHuGxOmXj9ORimEoBONzwaEnj6fxzWpro/tHKoHZnvu1+Jsq7OoGLIfip/mUGxcFZsmN7gqrEPl+jGs1GnGAcSLagr2Xg/ae/tepwRjF12Ho14uuiHvv40xxevzY7C9InkrMckUfs7P9acH2/OJNc+dzazB9tInNCzYnvAvCLvpXZStO13QRhQXWORMkmJc4SGuszlDHlwl8cFVRxfgic6wHrpFubSDKbl0E0d4T+JpqVhYfihj25WLE6NufNNIli4XDHLpp6E0hy16rE8wIp3x8znyagq/zpbDsYQAcC4D0n6E6lidJEEwIDpB5He045fgpQ786Szw4j/wSu8XuHyOk/xugg95RlhEFs8DA9HieT1aPKeyxXMgaH/1T/jrok7aA3T+0AtIb7P1hiRHAsYtOUrybXQ9BaPm1RT4jAHdCVsua1KuwpaL2FbQlZVHTIEPd/SQJ283Bi4wXupFGPKYnzyFIQ9twhcGehgbZJl8LpOvyuRjmZ7gkNmNTnRZNWDfOYZeVuM38eJoRtjQB/v+f+rKPHK8x4xR1H+sIRkXtQ6GZNwi3wHszyEZ81hHvOmgI/M=
*/