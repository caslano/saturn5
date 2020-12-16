// (C) Copyright 2010 Daniel James
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_UNREACHABLE_RETURN_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_UNREACHABLE_RETURN_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/config.hpp>

#if defined(_MSC_VER) || defined(__GNUC__)
#define BOOST_IOSTREAMS_UNREACHABLE_RETURN(x) \
    BOOST_UNREACHABLE_RETURN(x)
#else
#define BOOST_IOSTREAMS_UNREACHABLE_RETURN(x) \
    return x;
#endif

#endif

/* unreachable_return.hpp
v0ebVxynHOG6vp/+3jRHn7VzgZyZzL9QeAdEj7+LO5mxZoZVGvdBXP3Q3D1hvCdutyaU5/VsCf9D3C6nbbCb2XtVf2/bieXms0Zi5PpW7GFzH343QAzukfwUA8Vsxu8WFfavKs6jSjh7GoXan14+b+Okhrw7KpJ8Smo/bPjp3fvi7rp2OmN/ecdEeXe9Y9LzpsesDeMa+anGUuS5ulfykvwtH0tx7UPtb7b0H7fPqdjfPOCy95xX0T6koKI9fX5F+4Uu+2Jtd7W1HSP7WTd3sotZxW+IeD3b2Sr0vp5H+VXznx76Wo6wP6usr+XySxmpvK9V+CN9rcJK+lqFP97XWl8FfS0S6NZTrpn19DODnkabo9/d1ZLfUj9pgYvgMruv5cp/6WyZv2cg4Z+0yPb/J59xfGLWCT136Zd7d5jHJ9F1RNenU+X+5ub5sRh0ptisM7qtfk7i6eQLt80Pif9zzHNiETo1l8DKdaqmhJXo7q9omYxfLH0PZQ/HlRrqJ1Ef3iX2if465eHrez+RsPN4Hue9vX2p1ufO9wQ6XdPEfw380+8j7JD/Qf506y3nvLBuP18Q/1ex/iNd7vmuwj0HHGmet6gwv7zdmiJpaqje6yIvsfe06qvv4BxS7/NUGWQp7Ly5+lsKuG2WOEb59btBPZZUc67yXHfzfZg5Ou33yz39fRmkXfrohHOLXMv1j6O8Jqv2j3UMtEmqvYO/bxBpbsPtfuW2LdKPCkN9OyDavIlqnx4q9NY+VWW55xoyVu2Oyhvnd032nWrJ75QE/MKT4bukacMSqQtyZ+blzs5mJTJOzrI8x9n3/I343Rffl5DrMV93NcZQJxCmuU4If7vjEXH/gv56LcvHGqZLfcZ5OMJxl7OFFeaEryuS9+O6f/j0ctseJ/7zJZOItnCm9n+3+D/J4N8c/jfiP8lz+A2Wynyl27+Us87kHyqh9wCH368Vo1MrMWHe2iRybi7R2JZo/ZkTTafqqf25xM21vNAcjNKHbd1DAa5RerQac3Un9HmF6EP+PMbgrFRxjIWn2+8vdVqXir86uo1oJPZEkz4Qpvt9SuE8y1G2m4t7CS1vbaMecL/5PbDSy9bi3kq32/3FnstZb3WN7YYKz/1eVcI613bjSfrhWu6+WNePw8R9OKOCxuXrIUQ25WPLNuLncp6AZyaf/Vy7sEFs706ln6pkXuFdgcjO/W4Nebja/qY9QoEuwcRJCkLlfX8ofynp2aEyv3DR9OmzihxtsO0k84RangfkntlWVyvBlL+E6W7HVaCO9+afi5+zedYapjzWYTQOy1yFoV5P67z+u/irQd7o9+q6zXlT3Gbi1gn/XMPmv1T8K7lHL1ONnWVKy4DrznKl06X3tTOKjr5f3Lx/Pfr+bPP+9ej7ws372qPv8+4l+9dv6J284I/NJq7YUvjtrjffubZ/1e1fj3Wfunmfd/RznG86U8LJuiP9k635vUq77n/pb/++7pRo+/irbl+7+byBaPvdYz/nINb98dH2wTepZ1/f+Nvbnn71+flHftFwV3KXWl+fH/v+eOf5yM9SQIPwMr/aNx/eLwNnYLa49s0vVedmXgIbwRWwM7wUdoNXwtPgZbA/vByOh1fAqXAlnK78hePboOJbbIiviS8U30lQ1rTBbrAl7A7bwR6wNZQzj+F02AbOh23hIuXvMNzgU+ue1b6ALepblGt86nsM+DsNdoVrYDe4DvaA62FP+BvYCwZgb3gQngHfgWepeM6GdQizH6wH+8MT4XmwCxwAT4MD4WCYBofBwXA6zIRz4RC4AA6Da+BweA8cATfDLPgUHAn3wPHwbTgBfgUnwuZ+dBCeAafAKXAazId5cBmcAR+Fs+E=
*/