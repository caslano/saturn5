/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    forward.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FORWARD_H
#define BOOST_HOF_GUARD_FORWARD_H

#include <utility>

namespace boost { namespace hof {

// contexpr-friendly forwarding

template<typename T>
constexpr T&& forward(typename std::remove_reference<T>::type& t) noexcept
{ return static_cast<T&&>(t); }


template<typename T>
constexpr T&& forward(typename std::remove_reference<T>::type&& t) noexcept
{
  static_assert(!std::is_lvalue_reference<T>::value, "T must not be an lvalue reference type");
  return static_cast<T&&>(t);
}

#if (defined(__GNUC__) && !defined (__clang__) && __GNUC__ == 4 && __GNUC_MINOR__ < 7) || defined(_MSC_VER)
#define BOOST_HOF_FORWARD(...) boost::hof::forward<__VA_ARGS__>
#else
#define BOOST_HOF_FORWARD(...) static_cast<__VA_ARGS__ &&>
#endif

}} // namespace boost::hof

#endif

/* forward.hpp
VD3yCA4WAR9lduBb0GuaSxRY1EdUadbqswnDhgulVuOgd+jiMb/6bY/QglOgKeu8nBSlEXjBEZkuTasXP+KqCH+bF2Es7CrHNKLxrpoUYwpXSoEXIHdiNke2pfkr4VY+9nv60d0ONcaxklYio7D31HbdaXmbp8sApiwS8iqcJGnZL2t50l9bDYyN/qGGYGzLMH877HERq7SVl7ASou94GpP9a60OSDmDNfrJBAuDbfeB6lFFjalZSlnv3d6+e3ti8g3jTkK58vySrRxmL2TAaxQaLTvye0tnp0YqpuR+wcKaexsfK0jk2Fzq2Q4g5p6cmXcRNUO2R7FmYlaMaYJVBZaewihiwEXeBeh8437O04y7VJ1DVl6SlIv2i1yDQStwhtbAuqeE7YqaxEQsDd6qOoiBA1He//Eian4hoeutu91gjpLZ/lkhptVjeXnxNWYPvTlhV9OOhacQDpIz83QEJRbSPc/es4k6e5/XjDkcMQndrFIEx2+uMGZLvOTgUpzodOPUT/NTtu0b48lIvarTpmwVPy2Mb6mLsJuseZgmARVduIgfHIbTR3W+4euoi3gtZTWZsCJTBe9nTZMtUz6YxzxMiyQk7quCFfxNUsIGmZEcf/FI+WJqEB0GdoBzUJrBH/jNPPDCxVxtULXPXEjZtHRrMeAGlfOsxLvUVt182L9I4eeiorbv5KSzIb0p9c3kvZk3zeCMg9oXstGe
*/