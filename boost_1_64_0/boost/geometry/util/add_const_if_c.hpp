// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_ADD_CONST_IF_C_HPP
#define BOOST_GEOMETRY_UTIL_ADD_CONST_IF_C_HPP


#include <boost/mpl/if.hpp>


namespace boost { namespace geometry
{


/*!
    \brief Meta-function to define a const or non const type
    \ingroup utility
    \details If the boolean template parameter is true, the type parameter
        will be defined as const, otherwise it will be defined as it was.
        This meta-function is used to have one implementation for both
        const and non const references
    \note This traits class is completely independant from Boost.Geometry
        and might be a separate addition to Boost
    \note Used in a.o. for_each, interior_rings, exterior_ring
    \par Example
    \code
        void foo(typename add_const_if_c<IsConst, Point>::type& point)
    \endcode
*/
template <bool IsConst, typename Type>
struct add_const_if_c
{
    typedef typename boost::mpl::if_c
        <
            IsConst,
            Type const,
            Type
        >::type type;
};



}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_UTIL_ADD_CONST_IF_C_HPP

/* add_const_if_c.hpp
tfK5d8BFKZt67OWFKgl2pCDh2A5XUbYKQ9mY+CmoYeWZ6r2Xzbdp98eoHD9W5yLvvW1T5T5dW9fH8GzDWKeVUu4WuvGz91Lu8DR9Hw57lrU4z6WevXWZq0v/vsVY0nMvK6S8LnW/GfIoLOZRkppFg45jdV/skvy2Sn4PSH6Vuvw80yE18HyR7aI9lHnOSLQz2jCLdTvm6fLh65e2UQ3Y9+qzGpvnuCMhnkxkubzfp2eGqOuZibNKvZdL+fZIPTwt7bJjvq582dYC2wXWu3ptHHSF/GYu+fVUrwMjquRXlM1UMkpvmbq829w8T9lGyTNB8oyTPJMX6PLMKfJsn5M5RRw5NNsN3A9S37r9YGyvu3Ti/3TjZTsSFvHHHn1ZlKY+p8Dd3NfxPFKfp66W9ONlW2MJ2e7ruj59Sbohx5r+HArprHzQLtfSdHTXa+QPdHkxpVdD8lHb0n8p35OHBckzslIGmnrGtocZt3ullGWtlGW1lOXsQl1ZuAI6V7i3vP7Xdv39cvcu3raqm7RV3d39vPTHMDMJ6o7jbLvVZnc2sB687Xq2+ymi1q73qvrdTupiq5SvvxwDfeR4P5muL192scvGxLwNLFO44XphbFPaXqlE/lDyPylta7hVn7/L6nQpp1xDjg/99i6X/PZKfs9KfrEZhvwKHUp2DcxL2fejuiof3CFt13pCrvteJ9OTl7slzyx2Ou0FyrbJcVbz7xWURX6vYL9623HtO8Zg5bu99r0+HPM962jP5byYq+Qf5JBnx1nyd3GVORNf6mo6ZyKZ+n/OROlT6LNPmHkfL199xeo/n495H0RffQQbb54f876Svvu6mfdd+++Zz8e8z2j95zuq77xV9Z2fyrzPpa++nvWfh+qcZ3tXxF42cvLh/T0fHtLi42/35veUPoXN5DdO+e3zdLDy/PWQ/DbzE8bB98c9OA5fxHh8CVPxZbTifnTiK7gSf40/xFdxAx7EXfga7sPX8QQewjN4GNtSiPexF36ACXgCk/FPmIl/xpvwFG7HD/FJPI0VeAbfwI/xb/gJfoN/xfZs2+fYB7/EQfgdxuO/MBFpIEoswYA2bIYF2AqXYmvciG2wHNvifrwSf4td8a/YDc/h1diM86IHzsA+uAr74iPYDx/H/rgHB+BhHIhHMQr/gtHYmn0Sg+1xDP4Ax+IPcRzejpNxD8bjYUzAozgdP8MUfKg5bRn+Eq/DA5iGb+I8PIc34D9wITbh+LFgX0zHAbgYJ2AeZmA+LkIHrsAlWInFeAaX4uX8lrIMQ3EVbsRbsBxL8Be4BpvTbt6J/fEuHIL3YSxuwKm4EWfiZszCB/FOfAg34sP4d9yJ3+Fj+C98Altexv0FhuJejMKf4RQsx8X4Ev4KX8YPsQI/x1ewFResAzgEX8VJ+Bo+hm/gu/g77NaG4xpX4btYisfwPjyOT+CfcB/+GSvxFH6IH+JH+BdsxXPXj3AgfoaT8HOcjefwfjyPj+DX+Dx+g9/h99j+co5vjEaueyWjsBWm4GWYj21wGbbFEmyH27A9Po9hWI6dcD9eiR9gV/wSe+A/sSc2bcdxju2wP/bHATgZB6IFB+EqjMJ7cBRuxfH4c5yAr2IsvoNxeAwn4SmcjM3ac5xjG5yC4TgNr8HpKPN5ye/JfJZwsknjzdtWJunOlnT180jNlPlPkjAGZ+EonI1TMAUTMVV7x7j8hgvtJD39fFbXynxZsXg5xunKET5Dv30XPn9ciaRHOUnvwuePOznDdz0Nk3qKknqKlnoaLvU0EhNxlJQvPUh+48TNkt5lmEqQ56klV+KLOBh/jjfgS7gQf4lOrMBb8Fe4Tq5b9+IBXT4hM33n8xfJ54zk84nk81c=
*/