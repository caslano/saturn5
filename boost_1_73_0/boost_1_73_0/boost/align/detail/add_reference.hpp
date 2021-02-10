/*
Copyright 2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ADD_REFERENCE_HPP
#define BOOST_ALIGN_DETAIL_ADD_REFERENCE_HPP

#include <boost/config.hpp>

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
#include <type_traits>
#endif

namespace boost {
namespace alignment {
namespace detail {

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
using std::add_lvalue_reference;
#else
template<class T>
struct add_lvalue_reference {
    typedef T& type;
};

template<>
struct add_lvalue_reference<void> {
    typedef void type;
};

template<>
struct add_lvalue_reference<const void> {
    typedef const void type;
};
#endif

} /* detail */
} /* alignment */
} /* boost */

#endif

/* add_reference.hpp
knc5pZL/k96b1R/KD+AMuYBqWoXzOAQHnva3NyvMl6PnjN0h3i7saAKnF8IhCuoGPzS5KIrF3Wh5sxy7btaOq+J2WFTECRl9vP/82ZPhdDp/Nlx2j4dP7N79WJqqopBctpoylYwlhA/WBabY1P5CYmjtm1nVbwPnANBou2f33s6I8TBNHfyoqWqM19qEedAlWq2NS1lyDdytFFoQlakMUgcbqOdZzevYljIul16HHrXQ14u/LUDvlGGvJjihiQpuDOxRyUFDfKD61UqCjO46yUb4JpzQOZP8BirgC/lSsqs2hG3Ta7bdkAAPQNEYWTy1gen0mBVdUHx65uGjd28vz09evL88Hi1U0j15e3l8/vbw9EI+gILkGOG09qdkHmevncFohqlc4eVwsh7i3wMdR3a0XKe2BRlnrGmPw89HlraQM96qyxsKcMkTf8GR1O3fRjcYTehLMSu7hx9Qby7Ojsf47sKiA8Bxt5DXl7wr+/jAb/Q1dWcX2f0x6dn18UqNUgSQ1dNoxl+5qXIiIHd1M3CAt90aznhV7d2dRSUPq3k6ckc8F/T5aGruj4/B3aD5Mop4W1tbP5bkvfXzs7y3NMwIJnURWIOE1x+gqwOq2aa5NTXvx1BvGNDkepekTWGKALvA1m0RJuoFOh3f
*/