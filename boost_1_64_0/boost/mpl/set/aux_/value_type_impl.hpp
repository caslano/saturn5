
#ifndef BOOST_MPL_SET_AUX_VALUE_TYPE_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_VALUE_TYPE_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/value_type_fwd.hpp>
#include <boost/mpl/set/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct value_type_impl< aux::set_tag >
{
    template< typename Set, typename T > struct apply
    {
        typedef T type;
    };
};

}}

#endif // BOOST_MPL_SET_AUX_VALUE_TYPE_IMPL_HPP_INCLUDED

/* value_type_impl.hpp
0DRjUan7DO3VlfX/iK+cH/OQ0Vi+/6XupbL+H77X+X/4pcDHbRX5LGtcvomf83z/9zZ15R3uJuq2T3Jsi7HMJ7z/PsSnw70uO9Bvu4z/GcvP9H7ZhS7yvL8Hn74h8//I+10+voX4Wc6FA/jqCc8O4+dbfHt/od+LnqVeZeVkT7NSxrKknywPa+FjdLKxXPneoJqxPFlzpRYyZEzhdMpd6+N7Fu3JOsznGyuQ/WYbUlf2cm6MfmfL/h/Gcqb5PM1Axi2+7tXG0mQdjGuNFfbyvrrRWFzH/7DtB9/vdqZcG29bd9qLyfifsYwynvWlPemv+lOulZd7N3b84PuNe41F8r3ckZR7SMb/YJU9e9hYtJqX8TjtVfC+z8H3UX8eTcU22TPnaey4Xcb/kPG9rP+HbTKHbwHt7S3u2GJiKe/UX0WXnV6/lcbSJcffMJZZSub/IVf6zo3oJ2sJvIcMef7Yiv9krtDH5J98g/oZOss3bAXkWh1fdzfltsn6f9jRTMb/kPGa99+v+HlxkmO/I0O+6zhqLF/e96Q0Nx/08vlX0liBzKEvZyztb97PJ8GaeF2q0p7MCz/FWKHkQW1j+e/L+B/lYjL+Zyy+zMcjHRllSjjWyFjWGO/nS5Ah+/VeaSx7q2+vBXa84nOjtbHILZ7dYCxd9km6Cbm5nnUylivfXnej7s0y/89YXgcft9thMif1LnR+x/t5EDFa7tlQ7F3kfXof+pXwcmPGYi1l/w/ktvd+eQy5pXy/NglfxWT8jxgd9bkxgxit8OxZ2OWePYdftvr+eT62yZp2iygnczVewV55LlsBk3lLq5HbVcb/jEVreV02GMuU+RabYZ/7vi5O3dY+/7bjK9m39FPseEDG/8gr2ZvyW+JR07O9+HSKjP8Zyxnh2X5jhdJfHSKW8u3wn9gha7Emt2DPHH++lWhBHsj8P2Nx+WaqorECeT9YxVhUxktqGiuU8yjNWMYMmf+HDHl/dK6xyEGf4w1gEsuL0GW77P+LbZU8u4K6MibdHF1k7lErY1myNl8bY/mSk+2w9xXZ/9dYpnxXfgu6yL6bPWGLvf9uww7pw+5EZ6mbbSxd7m3vQRcZGx6BT2XNsweI70bv04eou8/bMc5YtuzfPRFdtvi6U4zFpsr3v/hA1k6dRXuvyPp/yO0j6/9RN1XG//CV6PIycZN94pajS335/hcZH0cdyyeWso/EeurKusnvUu5Nb9sHxGiorP+HjO6y/y8xkmvPl/hvttflG3Jtk/fp9zAZC/qJ9uTbtF+MFV7tz/2DxFzWlzqCfpu9jKSrrS+RZ5fixtK6eR+UMVYg4zRR6srcy8rGsuX7shrGYu08O81Y5kVel7rUPV++/zWW9Z7s/4HcR318LzQWF10uRoY8T19uLP0TH7ersE3mDl5De728D643VtjT+6At7clcg5vx39c+Hl1h8l4yC7lLfLk+xjKWyPp/xnLlW6iBtCf38kPQr8C3NxyfxmT+n7F8edZ9EJ9Wke9/KZfpfTABe9fK/D/qyt7zT6HfGvn+FyZrJ8whRgtl/T/ak2v8QvJA1pLKo71Rvtwy7L3Kx+g16so+A2uoK996rDMWner99w763eB98L6xvKpe54+ou8jX/YS4dZfvf6krfv6ackk+Ht+hc6E/P36ElZf5f/hK9nz5zVhE5uf8Qa5JzCMtra5821LMWFZZmf8H6+LjVsFYVPafqWQs0s2Xq07dkTL/z1jGGh+POsbSReezYSKjHjJkjYoLaE/ud5sYy8tIcuwy6sq9QDNjaZLjLZHbzl8XrjOWv7SEY5mU+8j7vgM+HeZZF2MFss5TD2O5sjflrfhK1sHoBzsk8/+oK98FDjZWKDk=
*/