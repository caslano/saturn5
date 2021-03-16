/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    move.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_MOVE_H
#define BOOST_HOF_GUARD_MOVE_H

#include <utility>

namespace boost { namespace hof {

template<typename T>
constexpr typename std::remove_reference<T>::type&&
move(T&& x) noexcept
{ 
    return static_cast<typename std::remove_reference<T>::type&&>(x); 
}

}} // namespace boost::hof

#endif

/* move.hpp
gBdwInRfFcwBQt0GK4E+8AZgPvBOYD/gPcD+wE3AfYBs08l9tdl8hG/NZlJJxXjie4RXb6ik4vvW153k2es2O94Wx8uxEM1uoC76fad4NbQVFp9n1XOlpxkTrWN/3Y3bnwz0Uk2DmZofptagsqwes4vcJMKuRNme4zolCx0jmk/iZWOaj62Ew92b8P+TyLQrNN/MObUz51U31NdV1zY3Vk+YP7f28sYUd5Lr47J5q5WcmrKbjGutVF8bjRKvi6Q=
*/