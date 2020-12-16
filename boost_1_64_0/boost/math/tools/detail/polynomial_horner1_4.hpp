//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_4_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_4_HPP

namespace boost{ namespace math{ namespace tools{ namespace detail{

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T*, const V&, const boost::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V&, const boost::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[1] * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((a[2] * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((a[3] * x + a[2]) * x + a[1]) * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_4.hpp
GI4Zw58G4KIBl+Z6HoZlU3ElcId7uHH67Gg+//riXoETuOFcoT4mUz5feFy8ZwnzRNTMaldz8GaEnzGMfFaflsspRBRTmpHKH373WMnhAkU/4/OFjxNnnHObHo+ISEnmRRBHEdzWsq3Rim408xZVbjzvfvX5Ym0rBW4q4VLOLa8XFzgP431MIMsQYYxrUjVo5fxDO8glsr6/fs2234IJdw3h/bJc1iChia2c4Bls2BGE5+Kfz2UcsqJlulU8ezN2KD3oP/pjiKUbY61kvI/r99DTa6EVlGMHsI0jbiXVFdHw7Vg4s2wH/0NUnIW2lWgk4eN3EAL6EAEuJGLpmm2/iXAp21NBCNjcUMclEzq9KwttXor7cgjYTOtaK0dYstkfwZU2byJoM5FUkVZS6OM53+YXFTZzQWzbkOY/2xwSkWyOe20w7bV1jcOW5ksKylZg3fgwzCcpayWpqrP6tJnHp16KcQlQ4deqBGatKhfMHg/6X0U/bgT7SdzIulZmeEgqr1zL0Y+7yvdYBSFtZV0bNs8vHz528szYp7bDXLwq3iSraStMrcbxBOfXp63sfPpcBdeLmrWVrpgFe+oxXu6ST85RzLV45loBm42jDaVGJ5tT5dqL84Fc5qwHJZWmHE0yix862HtY2Ns2LadU29LecV1K9sY5bgXHwFoJJgUhaGxk9DMc6sYHgaxAtGbKSdMUnVSAzyvXQwebv5zLL2qmq7amLeovM0HflW9XRUx+VsnaNfLKWN2jO7Ogilm7P4nBuEGNUawJ7ii7cSQdsDfbYQzOZShFTdNWhFT/pe1mRJT5zuS6ljDlgmNMOiuG2HGL0ecCQ5uFVA2VVl2lzWcGzDdDTCEb2WLWaRmuE07bYd+/sLXVjtWc/E+2xnuNuLhHpUhNGqPTHfgQ1KLa2Egxirbi+RAsp4ZwSmWDM9PjpGwaz4cInCuxRhHbVgZl99/zMBpLAHrhTDusNQg8V2glldbyNoIPR7uzycaZ1NSWY2cW3wIjeR1XtrXOYIYsWXGxPbVD3SjS31qrKtXq8u24hJc6sdKf+8UE3HXkjhHXLbNm8Tni2dqA/erC5po1jVK0uQqbY2d2eugXCJzPVZgww2X37jWET/Xu44XtTrmqZk31H2z3uMD2iP9rAs8wsGyVNLrL9OJ4+3yMuUfgGVArRE1pZv3G9v7W5GA0vp2k0CfItaZxlHZYxWE6irFzaXG+3SqmqBP5nBK+HrqwdK9hfMplzxCstGNCoGbFwrOxR9LiTYtKMWl4NQ8jFmps1+me5hbE00xQrwr5M2+It1Pg1baqXUPx1eJFPyAKz0p0aPm2GoJ7LV+ztzm8x57m2UV+ElM1TGCTl14I0bKeArQsx3kRLfYxaloxUfMuR5f0DHUJR9Q4LwJyAnHttFBCF30zQAYxGigY72VV0UrPUJcftwLnjn8t8tYawmqikn0gQ1Or7MFBnKFTrIhlqgm1rVAzez0ytBnGbc5lw5BQC+ZYI/57OvZDPGPgt7qT61qyhFhnW+Pvm3iJh/W+I2aY7+S8lKDGkJYYfMUx6fwp0qTOgbTnlw794JjFcQHYrmoVx4IG7MUBO8XqZjDvnagpww35H2yO57A/ZsD3uuaOK1553Lg/lGz+NcAVSHpQxqS+epvhuzx35KBPpi1RjbNiMHqJ6KCDuqG/ibG9OLTfaGYxYfh/sH/dDOMbhzY1jnIsave/2jTk56s5iNVX24a3Le12/peGd1nx0K/wIq4kayTjphotgMZ9xWGMDwPxBGaVbNvZ9kHPu4mHfqXAM4LbigsyHlHGeNF3ixfzmaqqaaX1KO/7Fw0KRW2851rD9WKFGyb7d26ml4Kj4/Klvc3ijbM=
*/