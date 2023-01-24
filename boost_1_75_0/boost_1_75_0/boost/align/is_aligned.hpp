/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)

*/
#ifndef BOOST_ALIGN_IS_ALIGNED_HPP
#define BOOST_ALIGN_IS_ALIGNED_HPP

#include <boost/align/detail/is_aligned.hpp>
#include <boost/align/detail/not_pointer.hpp>

namespace boost {
namespace alignment {

template<class T>
BOOST_CONSTEXPR inline typename detail::not_pointer<T, bool>::type
is_aligned(T value, std::size_t alignment) BOOST_NOEXCEPT
{
    return (value & (T(alignment) - 1)) == 0;
}

} /* alignment */
} /* boost */

#endif

/* is_aligned.hpp
8jGodlF51IQwaSMqxYEjQ2OP60qURZWIxp9FmkW/f1fBny2vJvdzf/fItSBJ0MbEKrLraLXWZ5AJvM75/tpNQkqDiNB3fqTsTYyhRD+uNUXJ78UyF+867Q0D3UV55A87n4eDGyr1rkiItaxSrLfbedPMejPvt4/v/YvuV3QBVpdi95ues5uBl/qXBe0EZ47Wt3m+S8UV+sRt0+Ka0C7CjWftqbRa0+M5+D5TC6S/Ldc/f+myRcqw47jlXle9+0RjuWxreumprfnuogJnarDWcN/n3jN0bD2uqDr7SZ+4mqzqiYHf7Kkktz2tLHSVXlRs+FsBNf/UdG1C7wPhVWvztennQaNJfJNHtwnOTuI408l3NiqOVHM7V/6bEPGfU99q2yKRWqJC92ezjm0Lqv2cgvhiLnBcI8dn1hcEb355vwkMZYkUKuT3cTAf9FFlAzD/A+KZORUsY3WgodML2zdtmRokqOcUluqKLWx1UbuE9cXIVar+yC0hyvruKoUW5L0wYL4kZjqnqX+r1GvDMAQG8IaeC4Zo9vnd5QPxaVWFWf4kc284GfER8FOqS06JCtzzNhSQ2lxuAvEtrvHg9aMx5WG9E1Re+R9rvtpR/x3dj6rJzGv3DFPCYLyY26ll2Ef5x9X1DLoLO01A4vO6p8kqC8JoB7+4H/oU0bPeQvNdlO8H5DSOYejcPClv65k2AsD0+yv06KnF9ONVzRso
*/