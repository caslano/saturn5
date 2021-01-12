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
bQl48EzX3ffdxevKqgpn2wBDsH0kWKRlvt+2NICqqiO1j7Cq0xcG7jjTzegIr6pJEP+hZNykmKp6oSrWQK2t6lWJ6Kp4vY/7JH6v47d/yMSAOLyLQWmFb0T8FQwVVUHdv+LfQIxVsy2GwYGGGDvmMirl/HtrutirabqtSTu+WCkevPd8J1ZImyZkyAr3jaReCHzvxwgpMXzfqExz6PfG2OEAcoec+5PpzVck/LE+krBOfsCC
*/