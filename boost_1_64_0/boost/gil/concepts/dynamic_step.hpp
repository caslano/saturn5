//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_CONCEPTS_DYNAMIC_STEP_HPP
#define BOOST_GIL_CONCEPTS_DYNAMIC_STEP_HPP

#include <boost/gil/concepts/fwd.hpp>
#include <boost/gil/concepts/concept_check.hpp>

#if defined(BOOST_CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma clang diagnostic ignored "-Wunused-local-typedefs"
#endif

#if defined(BOOST_GCC) && (BOOST_GCC >= 40900)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#endif

namespace boost { namespace gil {

/// \ingroup PixelIteratorConcept
/// \brief Concept for iterators, locators and views that can define a type just like the given
///        iterator, locator or view, except it supports runtime specified step along the X navigation.
///
/// \code
/// concept HasDynamicXStepTypeConcept<typename T>
/// {
///     typename dynamic_x_step_type<T>;
///         where Metafunction<dynamic_x_step_type<T> >;
/// };
/// \endcode
template <typename T>
struct HasDynamicXStepTypeConcept
{
    void constraints()
    {
        using type = typename dynamic_x_step_type<T>::type;
        ignore_unused_variable_warning(type{});
    }
};

/// \ingroup PixelLocatorConcept
/// \brief Concept for locators and views that can define a type just like the given locator or view,
///        except it supports runtime specified step along the Y navigation
/// \code
/// concept HasDynamicYStepTypeConcept<typename T>
/// {
///     typename dynamic_y_step_type<T>;
///         where Metafunction<dynamic_y_step_type<T> >;
/// };
/// \endcode
template <typename T>
struct HasDynamicYStepTypeConcept
{
    void constraints()
    {
        using type = typename dynamic_y_step_type<T>::type;
        ignore_unused_variable_warning(type{});
    }
};

}} // namespace boost::gil

#if defined(BOOST_CLANG)
#pragma clang diagnostic pop
#endif

#if defined(BOOST_GCC) && (BOOST_GCC >= 40900)
#pragma GCC diagnostic pop
#endif

#endif

/* dynamic_step.hpp
KzTCveEVNq5u90p8txNeHfST+E4nvK7tEbR5vhFu4ZPhGFF0ZOv6YtgTLo5BgGecbEwPt8GswfHbiRspo98J2i+FHPc2vtyHi7u8Odri1S43op0ddTkRbWjWSr9WuqDwyTZ03JGjx+hxzuUuXp0ISknEs8Hl0HVHyCk69Tw6g39AFqwR4TrSkaPLepQ2TQd3vQtw7hE897UMzrs2x779Ls9p2jx6XeJ+E/1R2hxdkOScEPOh44WJnFmxJkoM7sontUeMx04Oh7bOBo70fQEm2hH14AbuZYnsELWQyU7Tx5rzIFy/BY1VHzxUD5k5rzZ3GJSmz9/D8m7Kd+wsiyUvv9E/ualuxYs14dEojnMf6FgkRx0MFGuvlQ5HpXzSv5Ic7hO6cgrJofQQFqsD2XwPhEob1lm/rTxZOhQo5bfnctCmt+f7Ag/trBvtj0DhjU4JvNRaE/9l2IJQ8dfLpfJ+OIdXjqvEGaiXCLwyocBR707mnZFygO0p7/dtq7S96zBqEal6EEYXtTVJ/x21v8N/hxtnMAKhry479yFrPR/P4u5BYkcim0t05dLwsJHuDPGWKHxzJ/FFLo5/4V4B8SVROORvBX7385X8VHawCN/vavGQhfUgmcjnlMUSLuHTft3gJGB6IJdIplP+eI1wi9pUuuHyLpnI5boSyT44vMsWBrJDu0r5wkB/Iqd9GE/PWe7Am5Y7MLfctcw7NC934K3njiNPxfSOdH7IbyeyLfg40h6Zck+/BzDF8CKoxmrAXMiEe7wKlyRqxfn9u9lxpvM7sgO4jLZjU+A35V6QsT1XyPeoP2rMFH5TLo1uP2yb8RuDNjI1PVKqlsv8XvyC+H7llfy++4vh92nBr31JfAff+L85/DfVhvFgQnBas1oeD/Zs+KZRiA9VpuAZSfukp3/voA/snYG/IG11rKo5wvf7jra0VbVRLT+XS/eg8fj1fzG+O3njdydv/G7njXw3b36Zvxb1lRjQDuW8wMfN+/BtfBTbQtPB7y9HYysVd3Tv0PjrgPdsz6YM/0OKHwSg/5i/KQUkqrzoo594ZHnt/oFfXpiJ8UoyrhnW1UMW8Nbglxd89LSr+e13Kj/rDig9pX5wn/JxQz+s90NYGrGD8h7B/eMqBIR+3r/nx+GbrMq+F78KZY/ZsunDZxSy7+uVIPLy+jQW8XwD5MJlrF86ZgyquDQxWaPcbX+MTvM05D60eXjGc/h0UC49gxnfI9hUUuUtOYmXlyf88kNbev/dPHDSB0YqNbUfk5ycwJt2M5VB/+S1F/gd/Cg4OwcTO9KlbjVUDXn6+3F8357PJguptJ6UkEd8P4HvxYGhXGn7YHpAOfZMpgcHg5vtaYyLgyb89YpXTHeVcqmBYIYK+rYar9i19bfPgevfi8NgMbAr+HajCo8xeAh3Vc2YchLf0juT6aLvVBS7IEMYmGU++vtLflYSMDJt6vTb5E06HaD5Y89X1e/b85dlcT0tk1W24V2lITUPeHrsWarwLEat4tCA/nYKYXQQVR5+Wr7pl8P2PPwyoui255MqTTqd31ZYz2Apk8incmmdfR3/+608qLmmMJjVYS8A/kPGZSfPlM163Q+LRZQ6Hs5lFWTzUHtYJn7efwxZ/TgUmdDp+olKV0QBqvL7syiXbL67YMp80fkivfppFEAcp2eweKlNT5WmNf+O4BdVthJDSbVZq6vQx77I+G1hfCPEtxe7bVq8ZxezcbfN0yeLmg9Fv9c93jenjVfUgyLgYiy81wK5azX3QDQ37JM/lGMVaRyxLjRj2o/m4qUPyHVgu/CNOjA9nizXpsFRXdlflB6gbdjm5XwfC916JzY9oZYx4f6xzd1RnZqeKY9vn7g=
*/