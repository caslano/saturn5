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
wbMUIlI81AYsliVBUZpEu5OMkOydCXwUVKRWOj9Zraxn2gi9ehFIFhJIURtFNGQBxXBNBgdQK46miW02/cSwd7Ox9g9H8qyVg1akBDrDBOKkAxmz0gZwGy++TW8WcDucz4eTxRKmVzCcLAnrezwZ0XlLYjKA28qgJWYDclWVEnlD+HbjLbHaAkS1hsXsCqKb+RhilZc1Vfl/ILwFiTDCQipsypBLurVOG1/7GyqW3aoVVIJUdJlvnpYutpUcW9jbfDpdjOOvo3iewMUn6PYKbZDlAnjQ7dFppT6gH3TpolbUnXRtcmy6QqhrV9UuLGXWb8WihHqld0LuKiUUyPw1bhrhb5615Ek8if7uSTr+8aote7n9Fyjv/xGl+WjH3n0FdkhJx/dKVE3vp88TW2EuC5lTR+bef4hIRWO8HbRgd3Q1Hl4nabc3nM363qqTkZdx9AtQSwMECgAAAAgALWdKUg1VF6dcAwAA3g4AACwACQBjdXJsLW1hc3Rlci9wYWNrYWdlcy9UUEYvbWFrZXRwZi5lbnZfY3VybGxpYlVUBQABtkgkYNVXbW8aORD+nl8xSvIBehu2109t1VZHoelxRwEBfYkUaeVdD1lXZr2yvSFI+fF9bIhyle4atcm2OiPitfG8+JmZZzZHjx5u
*/