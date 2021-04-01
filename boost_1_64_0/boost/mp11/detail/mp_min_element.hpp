#ifndef BOOST_MP11_DETAIL_MP_MIN_ELEMENT_HPP_INCLUDED
#define BOOST_MP11_DETAIL_MP_MIN_ELEMENT_HPP_INCLUDED

//  Copyright 2015-2017 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/detail/mp_fold.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/utility.hpp>

namespace boost
{
namespace mp11
{

// mp_min_element<L, P>
namespace detail
{

template<template<class...> class P> struct select_min
{
    template<class T1, class T2> using fn = mp_if<P<T1, T2>, T1, T2>;
};

} // namespace detail

template<class L, template<class...> class P> using mp_min_element = mp_fold_q<mp_rest<L>, mp_first<L>, detail::select_min<P>>;
template<class L, class Q> using mp_min_element_q = mp_min_element<L, Q::template fn>;

// mp_max_element<L, P>
namespace detail
{

template<template<class...> class P> struct select_max
{
    template<class T1, class T2> using fn = mp_if<P<T2, T1>, T1, T2>;
};

} // namespace detail

template<class L, template<class...> class P> using mp_max_element = mp_fold_q<mp_rest<L>, mp_first<L>, detail::select_max<P>>;
template<class L, class Q> using mp_max_element_q = mp_max_element<L, Q::template fn>;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_DETAIL_MP_MIN_ELEMENT_HPP_INCLUDED

/* mp_min_element.hpp
BygGXqAe2/Nq14WDIWqAOJX4iwG2Z64VITyt26YIcF5uJvfj4L4X2Fmgo2fMXU6pHTGXiGXmQykJIwX0c3+k2PY7b+M0E85gnwvid8MqXN7ZjjLwsVG2UVH/PGHlOWUqw0CLdCDOp+tN5kC5U6oJ5lnKLZQ3jHm7CcdVCex7pigbfVLnmxfItFqhq4nu9RVOhMdlL4V2JhAanGc7xX7EaYOCytedrc5qNuG1SdRCy7xtlkGA3mekVaM67k4NAYHQbqPZLFRuFTLBuNQoucOTpmVIQi6kn7KHPHiZAZtu9AONF3PNv/dGIeb/wBNYQ7j+Lnc5Yt9/3mbZx1m5kIn04U8GSHz2PDA2r6Hfle26sa87S4fbGSjyVg3oA9BXfd0APYF02k4p8cdZKz2gKCm4+3lNwQZK2SC6mTmSlDATkFCiWcmxmQdO7+wNwves1Ih12DWDww8ObukSm5C25l/aJeF1XAUazfmq1r31HC8Lvh+xCMfXKZQbZH9wSCKcR71PYBKliIm+KW1TKveDm1flBB09lYRwcbGiA/VL8p6nQ3EnA/tQ4F4RZ2sACg==
*/