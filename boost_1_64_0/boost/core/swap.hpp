// Copyright (C) 2007, 2008 Steven Watanabe, Joseph Gauterin, Niels Dekker
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// For more information, see http://www.boost.org


#ifndef BOOST_CORE_SWAP_HPP
#define BOOST_CORE_SWAP_HPP

// Note: the implementation of this utility contains various workarounds:
// - swap_impl is put outside the boost namespace, to avoid infinite
// recursion (causing stack overflow) when swapping objects of a primitive
// type.
// - swap_impl has a using-directive, rather than a using-declaration,
// because some compilers (including MSVC 7.1, Borland 5.9.3, and
// Intel 8.1) don't do argument-dependent lookup when it has a
// using-declaration instead.
// - boost::swap has two template arguments, instead of one, to
// avoid ambiguity when swapping objects of a Boost type that does
// not have its own boost::swap overload.

#include <boost/core/enable_if.hpp>
#include <boost/config.hpp>
#if __cplusplus >= 201103L || defined(BOOST_MSVC)
#include <utility> //for std::swap (C++11)
#else
#include <algorithm> //for std::swap (C++98)
#endif
#include <cstddef> //for std::size_t

namespace boost_swap_impl
{
  // we can't use type_traits here

  template<class T> struct is_const { enum _vt { value = 0 }; };
  template<class T> struct is_const<T const> { enum _vt { value = 1 }; };

  template<class T>
  BOOST_GPU_ENABLED
  void swap_impl(T& left, T& right)
  {
    using namespace std;//use std::swap if argument dependent lookup fails
    swap(left,right);
  }

  template<class T, std::size_t N>
  BOOST_GPU_ENABLED
  void swap_impl(T (& left)[N], T (& right)[N])
  {
    for (std::size_t i = 0; i < N; ++i)
    {
      ::boost_swap_impl::swap_impl(left[i], right[i]);
    }
  }
}

namespace boost
{
  template<class T1, class T2>
  BOOST_GPU_ENABLED
  typename enable_if_c< !boost_swap_impl::is_const<T1>::value && !boost_swap_impl::is_const<T2>::value >::type
  swap(T1& left, T2& right)
  {
    ::boost_swap_impl::swap_impl(left, right);
  }
}

#endif

/* swap.hpp
i/MdU11IgUU4h321boeunp5sj2oNvjdp8Gs8nAcBo5NPr3XPcdNhL4N91sMm1VlOaMfJKeGQI4zh165NaNimBJ5UzxbkSf+XmAJPQ5MqZ+TJGTUgp6YhfYN/wOqMA2OZPsN3d/O1ovqqcFPbfJ9nWSZpS7S+x8rxBa8dTIcHX+WqhTovRUPJUJmmfh+jvHGz57jmYDMfRkwbrsG+tNacIezkriBhmTmwDYwZe7req4ePf83HqR/iWtI3PNwb2JvuX/Le2dOgfzXfZ+W4bc9Y5vvfP15L/Yu/5Rfvx9gwWysKe3KbxbHhBjs26HvjMGb+Qo/jZDI5sqnqZJHHcXPvOsDJqiH/nT6ur5zY9XSvf1H5pj/8PsScs4V/9HmDDyHKDvdMRNm0Qdm9Sh+H73pr8k1RNHzTHvdw/hKnj6seBWMQpwUDhuV3G+ejcoksSJ8N4z1xusA0XjdcS3oiO3q9ivnCfuI/Oe0nkPYAp9Ug7UFOy0DaI5x2CqTNW6fTDoW0gzjtJZD2eE7rgLQncNp3IO0wTrsY0hZw2lGQdgSnDUDaIk4bhbRjOO00SFvCaV9UaQ2ufVbyUTX+pS7mBnOevOgnL6Ny+ruHKOBl11Bv92CW/nL8is8tDHDHl10e5HfvWn1yJePd2cHh3h5jh4uBP+K4jtSxzsWIsbHVFYgNDXcN7xgyvEH2gAbjkawUeKgykvLXGnxwWyI6yI2Y84bMOiefq48fJfro78sOZp8j6gNx1McJ61wMfeJMghHQ23dqv2aMfF2cGJu8G7y8vh91MuA7skPDEm/EkfcmL6/P+ykGJ9PZfNpwdkiyP8Rd+3tqkN/V99MR7+ka7tLswUY83Lv3/ww/v/f9eOdKwEX7Btyz72euczFszx7E+vuGspLciHtyZ/383jrrFovv7H92tgdsBsoQaOCOxNaQB9sOxBFNaIaygzt7u7Pb+ruFfhrSYD/dLvBAXfUbvHdLH/XiwaxkQ4i7NjQQ5lfsTR3estLgfVu2ZZVGhTqENFiH56wLcazDMOGFTClHNDCWWlt5LuA8Hpq8zwMMxjIzVr3A4jwmWb4vYgzGFcM3zxiODVjnMcaxfyNeMjj2T6uTSYND/4JxpeLjUOeawcDGwb6nAUf7RPlmgQZsy5RxlsHRNqz8ZwMO7Wryn0N4KVNIbdNXMC616bmASW16HuNSm76GMalNzwdMatPXAy616RsBl9r0AsClNr3Qx6HObwVMatO3A57WphcBjdSm7wJcatN3Aw5t2tAem/W/8pPh3OYTy6R9k/eE44K+4Q3z7vcmNPk9xfyEmkSUCqW6fQfyUsJVgBvlY8dLzcD//UneWvH06WIUr6Eo5qizy4kmmkBzce/6XSnwoLgvxRqcl/+gR6PjqqgVJavbDxHNliwV0LXNLuqh7bW6uP89+khQBm2cQ12vXKL1oK9fT8ezTS0CxCe0PKIqxzBN8l8NeoDmcN4Nvwbz83ytI1lPEvPzpA/O8X6WeVAzOPOvawPe8fnC6QjXyZAmthTbBl9MMBUMabIYo8zBlHF9kD9uyAjb4eshTamA6xghTjHiC9N5WokZIZtIp4tbjOSpOWvL30Q6OvMUS96pLl2U8uhLfMun05Vr+Iyh6Z+8cuLtgS9rdp8U+M3WA343Wn6gu+/oOsD3QPcm4pArZey6143cp3du0Dhhpg2/L/JQLKyd3sz5ZzYkGMTRD/LzErYig/72Y8MDcDynG/KhhtN1oe+iqcttti6EK8ja7A9FHm5dfm7ksNgqxn6Zmt/EajZl/Qr4eDSG369T+XFgZOD3W+Dn06xrSL58jQ6H5eGtUJBRplsF45jMlwc16De/R55Ig2cQiQY/AGiUzpo=
*/