
#ifndef BOOST_MPL_AUX_POP_FRONT_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_POP_FRONT_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/pop_front_fwd.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>

namespace boost { namespace mpl {

// no default implementation; the definition is needed to make MSVC happy

template< typename Tag >
struct pop_front_impl
{
    template< typename Sequence > struct apply
    // conservatively placed, but maybe should go outside surrounding
    // braces.
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300) 
    {
        typedef int type;
    }
#endif
    ;
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1, pop_front_impl)

}}

#endif // BOOST_MPL_AUX_POP_FRONT_IMPL_HPP_INCLUDED

/* pop_front_impl.hpp
w9WeApdAos9PuJ0IOxfG6Jv2zEmvMFl/wTwI2/w143yoyGylDtJLQeECKB9M+TwKwc53Yrluy5DYuekQV9/MYrV4H5jU1PTN+BHOGU/XwxbGJuMkYxzZwBqS2BiXc68ljpEKJy1z0pA7qr7oIFpfrK/2qiVvsUJ7pchjePzHYDndtXl1+b8CM/1/AmZu7r/lmm6WrrKO7pauVqbmlqxeNg5nWRgG+vvrg9i3eh7Hc4YbHUr1iiVuK1qrSiWOTWJ2gpVuWuuZbukpDTHfVSSt5e0c2jacZphSCeibXTEpvXDfUat8EmtBfZtngPHdF3RvZbMBT3R7C2V0942xg28KgRPpJvkPQVl04JtMOr+VmQQKHulvgQtfDbspygRL5ZvK5tZ3Z4qDDEgpyIu33j3d0GSM87Cm1VHCuaODhjw6wkG/vLoFQQf3HDklPTD/XJg4dlDAG+AH6If6nEz4uz4KZGGUJxzIYG5OUAD6E8XUpBgcA0gKdZv6mEsnzjzFJgZGekGH4kFspqrFJ4OykV9QoKSQ5txDcbag4uDiUKsgI6QOpHS0dOR0zCcyiOUUU+5mqBFyBwqQDIoKWyou5RVzE3MTr/rEGydoTW4tAlGcejslMZUj5hS8gcLytgPxiRNiOGUsdhFMELqB6v/m6QNUe2pTjCL4FevpDyj2FF1uYIgIsj+KWWhKUEqIkBjpFMeU6xT6B0Io/9DHPkSf
*/