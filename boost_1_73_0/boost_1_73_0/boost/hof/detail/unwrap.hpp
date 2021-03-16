/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    unwrap.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_UNWRAP_H
#define BOOST_HOF_GUARD_UNWRAP_H

#include <type_traits>
#include <functional>

namespace boost { namespace hof { namespace detail {

template <class T>
struct unwrap_reference
{
    typedef T type;
};
template <class T>
struct unwrap_reference<std::reference_wrapper<T>>
{
    typedef T& type;
};

}}} // namespace boost::hof

#endif

/* unwrap.hpp
GjqiimCsSkvCeAf9+KOmoSrPakfSFz9yqV62R9k18mOjXpTsqCcdNGJFAU1S2QuNA7j8lzTq+Uf+/0eib6KS/1JSRHk7JIYiAnqclr8bpaKHiCQv1xAk4Cuule2PorrGdUmBEiC6tKHJTV8lUc391v1E7Ijetp3edgenvmlLEu/hTVJzkpvuSHI5kYOSps3KfkALetXryOuV9/mW8DbQ0iX8jnR1m4f6n+S9oeJkOhxmeIp5U7xuI/qA4rplWqc=
*/