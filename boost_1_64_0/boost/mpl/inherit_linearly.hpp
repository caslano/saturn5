
#ifndef BOOST_MPL_INHERIT_FRONT_TO_BACK_HPP_INCLUDED
#define BOOST_MPL_INHERIT_FRONT_TO_BACK_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/fold.hpp>
#include <boost/mpl/empty_base.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Types_)
    , typename BOOST_MPL_AUX_NA_PARAM(Node_)
    , typename Root_ = empty_base
    >
struct inherit_linearly
    : fold<Types_,Root_,Node_>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,inherit_linearly,(Types_,Node_,Root_))
};

BOOST_MPL_AUX_NA_SPEC(2, inherit_linearly)

}}

#endif // BOOST_MPL_INHERIT_FRONT_TO_BACK_HPP_INCLUDED

/* inherit_linearly.hpp
+zlfn6laE2BN3UeUc55H6qNEcPU70qczi/92QfmjoIXBJfK//Xw7f7rtH+S39n+9IG++UjNKzlfzxkOZLxrOm996nlN+fxM3VflYrYpJvTQaDK2bR1vXumQMPtDaLkEB4+JVJEuadsTn0T7f1L5OTcgRDKpvGvBQLq/LTTgm55EIXwKRnam4vFXqrkzfz0j3IzSQNGAgSQESHrjUMdXA+Sl97dh6NEsZd/2OtjXs/hK6uxzGjQgNQ3KbPx+UmEkhW0Dxr4YFrpmiY4ZU+2Aq/LFI+KMpvqRNhjvTg+iajt6MLhP9KotyQ1mUE6Rgel2rgR6bhACYe37AmR6LAK7IfaF1AiNBu0Jmpjc2fvCZiaALzExPTXf8TymZmBXluBSow8TgtBDp13ME+oZp64n9qTuQvke8yT9sKPtdzo8c8glnML127Cty0OVEAaIbLYhCV1+Lb7RY3cVVHOJIB6YJp1/gNFMo7++h3afJWRxKregdjwQ/xh+7kvgiGUO4ZUn6ewBn6QUdew8kJQCGg7nEuJDV642PH3D1OF1L0dXSOKYNJWVCAt2xh5CEk1DtOMalcCyyhUdjs9urZrIn+lC3L32XzMOlx+W3eIQqo9sDOv4hPf8AMzz2GkD+NiXf/fB5/+Pyna1P6T1G6E8dlVIkDV8QlN/RtloRAtvFsVZLCVXCtpdZpTWQjlCgUXqS294mH0EL+ZSJ/QEJQfq97PI9uS5jk3SyqLqcizponjeNk6nKSEB1l6xMP/BYuvukwtEvoCd3h17d4fPFk3P8YGP9mcP7M6sdobQ3qmyPr9ub/kOOhAWtTSCsNpYl3voOjJRxIGWrgdYY2MI8/XszPYfo+vkJ+dj4E5tn+e+EFYJGod3gLi41RdjbtbPBqZ8IB3iRd5LSRygpciqe1c8Q5ouTzzMWdu32CDFbPh9enTvRNM5mq9+qm+HLBLS9hfqSFZVGpN/qk694VvgMS9/pCd1FDAAp8RmRzRuZuoeFGisNLL5P1ICfxP94hbPuM8i2NS5RadkwOh+RU2Hx1rUexuj8qxRypHYjkXV27wXbwbuf0F39bLHFMCK7NzBnxC7Htsv4lMQI3bWbrTZ6jcgWC5gypf5BSWpQfGwyUNgknIu62yzPHz6bK7ebY6EKdlxXrOMKd8kZpUGc4QaxrDSIZW4QZxYFcaZqTlaoUlbokdwaFJn0nObLyK0wFWnGS/bjd96yW9Nfati799jl2HQZsc0ohm1lbnzwsclAXpPs2+duEwvDHY/mAkZkp14u1ZyMukKI0lE2dXEoHA068jVIbxZQWj8atIUUKkAKtRzTSPljsnuZkd7ETXVSkxJ6mhU1XKn2G/fufHFb2rSw6z6ZQni0hid/iyiSSq6/5AmM7PXM/Aj9ayD9O9IlXzuUuD3+yu7on0jnTkjGh5S7XfggxrL/qWtvA7yTR4cdS4L1GOraikWM/qlrZAYEXwcV6okNdgeBEiMe2QMhXlXAHst0y3Kh1QvQnJKUquIjIu5S9tkmYtgIzHwh4qfvtfAsZBFmVdACWxxjb/NXeiEHL42G2wJd/VNjV/gYJAuC5gt5UBjOyXMEmIfku49gZIAfBtT23BiwQAeytpWPR5bUJNv7U43lmUhjjR+Cqs7n3Vp/Moj/dyVXGHZ9mTTs7kgclbzhiK6ww5NqDyRbZhnJxllhlKUqeQP/jqi+atGXN9nel2qpzURwZ5KMb7XzhcT0JcNeWP0kkWWl5/rqU31tlb5IKXJ9wcwqx6m4YNbY9eEBA0EmzxVhihzhsf79IgeHIWOsRXvSQm90XKqzrlMOjpuUrMSxB2Z99akpWcGW6vHciWq3CPRxgxLvQLcP5HKAO9107HQ=
*/