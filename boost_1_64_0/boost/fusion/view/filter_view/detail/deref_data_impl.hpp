/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_FILTER_VIEW_DETAIL_DEREF_DATA_IMPL_HPP
#define BOOST_FUSION_VIEW_FILTER_VIEW_DETAIL_DEREF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/deref_data.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_data_impl;

    template <>
    struct deref_data_impl<filter_view_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                result_of::deref_data<typename It::first_type>::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(It const& it)
            {
                return fusion::deref_data(it.first);
            }
        };
    };
}}}

#endif

/* deref_data_impl.hpp
a2m9I+PiGLr89Vhj7K1ONxhFNOryujvwHUw30vqIpFEfM2g4dzl5lYam83JtHZ9qRn4frhxrx6jC0j3ajt78/ApNGSuD42QpLHvDaO4TM21f7h/fIHFyLRzq9thg7ZGJqMjDMiqu2L9K2x6whbvukiHvbpEbOTI0g5jTdtna1uedZrr7ZXSLsC4zcf9be+Hq6ha3OTprYu+ZeEHmOkGosHN3uxfg8Ov0RRN/r8qtnTCLE3F0jTgSybV0/zn1D/1KG979cu82TfcLRxRvLHVQtO035ZmE0u8Gi1RgfD88Rd+bvrePNuL4fmLb6PsySbo+9hbtdwKbcpam2+8Epu/oO+/f0X5fVwa6A3POu9NVWpoK6d0Dz8xO8/v8YzaMc9kzioZ+MPKX8M22f9BYPUpHPVp1Xlo2YrB+dxKGRvlwU56nAvvob0/ELq7LPw0d4eK/eP8r/NxJi+r/1hFSfS7H+nMtQjcq4jArBd0u9TdHDtbJedjdZeCfIcUyuf+t/er+B5o8HhO9fdenvnBB6okXpCz1vYnZTd9/I7//Gd/pgOgxNHkOlF60W56b/cOm4Sk1jdcGc2sDQ1PocGVjle5TepBx+7H0eZlZyLiTwjxGPjhsa5d8JfePqz3YLXq9lnuo1pmf3VitM0VVHpazPfrKBvXf52B3Nk/T9CrlATqDonW3U0YM7+0tZmUAqrnHW5626Y9ZGAzlNM33eHNXIdyk/qfH1E5gJvYp+F2YAXZiX8XdwFUllgNVGfSYuTroTNBg4TESh7E1t1vinrQyXCMzgbavfJn6ivi5bKf5tRXZTvOkkbf94CtEO2nTpBLW8n6V6OcZfd++/S3v14g2Y9MM3q8TffYXjH7gHi3vM+Qe0aYZvN8g3j8z+t0P6nS/SbQLv7RoBu+3iC5+ZdIP7Ltby/ttOW5smuJV/V7t286pMlE/fyz5f+FVBszJXzEMim9ibv9rhkExTYxgGFZUYI4wDCuSGlffoTI1uwa5OXgM+v0pGjvPbsbOcI74MESbsgD3t0k4VR52vjEBp8oE3Gcn4ahcJm7v9HhcWzaM7+dqnIKQwtcUAPSlq1j0NuO4i5+x6ZRhk341m04ZNem7bLrKIOhf3W3R1XnW6A5q7hqSroiLG7QYs/spizY/Z+hTVxnpU/NPUgsH06fOH74a9pr2vu/Pr9kJmt73gbZo0/ZjP3J+2tj3UQS7YbP5A33jsUaaxj7tllr2Qwy64gcIMh5dGpjV9SfpvONsvOZ0Mx3sle9rYJZXHktT9KKWf+KuRGtHxLgy7B22dBouJv37+u3bz0Zr991CR+ReVkZFFQqpo91/v/F73/gvytZbudZVBvXqxHSAX6sKeC/5+26ak/2plNTHjMQtyl/qXcOTIXjYpAPM0TYh/D/pIg/WurVZHuUvInMDN/VFIxxZOqB+kxLS/ls2X5El/f7urbp/mnK9SPiZm3lhXCm5j2Mii67IhU7CccH+PXBFYo5CDPyBmOcQz2rPLs355Cbb6Hu3f0Afedp2ovO+Bd4zO0DjfRf+Bhmd9V3YQOw0MBb/nhnQuuNHn8ledYQxyKDP7SJ6t39D173w0x6zQQlS6gyFF/+/uq5ZzyfafcaxjRV8H0613+kjMWH8nb0BjT9ogjg3QP7O/I+664qNq6nC65LE9NA7hN7BCTiYmrm9F2IDoS4bexMbXBbvGvJTQweBEEgI0Qm9Q+hB4gEhJEIPVSCKIoQQQjwEgRAPSHBm7p1v59y7hoQm+H/ZSeb7ztQzc6ecOcPyF4swzGwrdq/6ve1Ja/MXIj2YvAB/yBTHm/sc72V4e5/jFtMcb+5zvLSFD/vMP+PMBLwrj7+4r77BbM07JU3FNsk=
*/