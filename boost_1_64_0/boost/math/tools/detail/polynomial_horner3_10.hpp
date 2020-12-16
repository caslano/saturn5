//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_10_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_10_HPP

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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = static_cast<V>(a[4] * x2 + a[2]);
   t[1] = static_cast<V>(a[3] * x2 + a[1]);
   t[0] *= x2;
   t[0] += static_cast<V>(a[0]);
   t[1] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[5] * x2 + a[3];
   t[1] = a[4] * x2 + a[2];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[1]);
   t[1] += static_cast<V>(a[0]);
   t[0] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = static_cast<V>(a[6] * x2 + a[4]);
   t[1] = static_cast<V>(a[5] * x2 + a[3]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[2]);
   t[1] += static_cast<V>(a[1]);
   t[0] *= x2;
   t[0] += static_cast<V>(a[0]);
   t[1] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[7] * x2 + a[5];
   t[1] = a[6] * x2 + a[4];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[3]);
   t[1] += static_cast<V>(a[2]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[1]);
   t[1] += static_cast<V>(a[0]);
   t[0] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = static_cast<V>(a[8] * x2 + a[6]);
   t[1] = static_cast<V>(a[7] * x2 + a[5]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[4]);
   t[1] += static_cast<V>(a[3]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[2]);
   t[1] += static_cast<V>(a[1]);
   t[0] *= x2;
   t[0] += static_cast<V>(a[0]);
   t[1] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[9] * x2 + a[7];
   t[1] = a[8] * x2 + a[6];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[5]);
   t[1] += static_cast<V>(a[4]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[3]);
   t[1] += static_cast<V>(a[2]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[1]);
   t[1] += static_cast<V>(a[0]);
   t[0] *= x;
   return t[0] + t[1];
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_10.hpp
rv+/gGRw2BPKwzwPrkfGr5CMjKRpJquUVWQzN3BnT3/3e3F/iGkUJbDR7rlqKx08XbfFByC+lNRhFOdxJcgAF27Fb949TRB/RAoeJixIEtLm2u2d1c95vHVM46BKI8Pb3xbtW8Eub0WKOi1ZHeeW1Y7byzq916D0GOzt1pFM1DL5032b1/Meb52GURSVGem/Qtm3Zrz0XtzO4pTlIgiddHsD2oiVcRnJ4CSMA1HlRXA9Mna/z7tnWKQFr4KYbHZV05FRIBkpyXkuaFFV1yPjWV4+as7LoBQ1ltHe3s0e+fu8NwnyJE8y03f73eH980HEH5C8oAkNK7DhLTvj9g33X7l8JSlrmoSiEsS5sdjnG/JnlFZKwrAs4oBzMuAqo3+muOP93pvjWcxY46s0Ntd/Tmzftt+H+BjhWUZLIRjwbXZO/HAvzVK2k7hKgRUdE/vnvQLxBSQKapYmNZeMK8DYjK0On7EFiE9WY55yljNBzIZXf62Ycz+PNxSiSFhVELO5NJj37R5vlGWhSIUgZiOnn9f4KHllFUUR5DB+rIwt4LLic4QbvHpJaFKFmcjICuzQHkeHjb5/ya+8/FZJUUdlQUlrCA3v/cYP+O+a8pDVIiEtYUh8X7vdH/B0XOVRGhYVaQ0/gvU08QGvTVTwvFNcEi/cvdaTeTPc5atIXQsuEhYTN6qBP588/AFvLi+yMI+SGjGZ58ltWosunyBVWgZpWZgsohyaMQjzcKnNpM4igqMeYF28wcsfq8KAp7EgfigEL3/nsS54UdZlbbmg2vriX3zB5SkIr4u0KoKQwFmVdUHCtuqHfhsJwjIraUWOyRROLTUuofKH9HGUzlEndZXZ888riD8jVR5EeRzWxBmT2oXY/d4dH8R7DEURJzRinCjHnbkVkOF408lfoOXro+tMtzskRxAa1iXNy6vKAUWCO2XfPjaSJZVZ5SxPCwp+MzJ1tDS2Xm74zOtZSEYk8xPVXNCY2A0q7a72zO6a8mhx9HIW8VcE3qTmLIH9eOV3pZw54WVH2HXwMmLeWkFyApJmcRawjJNm3xieroS3K+U7xd7Z6bcRHyM8FFEIDf7kibGldvfGE1p/v/H0V8c1C3hGNo5MB2sPhjEtY/i8f75ShTxJahiUrl4H1vbeB8mIiEiLkIuI2BdjF6XaVo7BzEP7XZn9VsSbkbKiokxj951lG1NwEs0j9+k2MIdkpKSIgjQtC94vo/EylNfnPJvj8teE8ZiKtGKWHdq2X29vxr7KNIvKsOCFYrJP9k4apxrTVt6H8hvCW82xyFloeZsjRdNljO3B+eRVEReUWq6mqXk27usuT0ViWTc8y4VlgmsLXn3+EOWPE5FxHkd5oJlMx7Bee028pu+OyTFtb/POL3XfAIZ3Qb8naef3GRp6/9fE/ZT/nuS8/0vN2784BtaTh9BGWuvd7yfeaCButeO8p8r2uzH+8qyOkypKSSjvTk2pGH8GWyBsUWVpGEQVYMfGfewMxoZlJURRNthpH/tEhI2DKA+ziAJ2YmS/h51D2DBKgpoWOWAnHzLqYRcRNq3rjJZZQPK2sq0jbJZnCZeZAGx/2Z6FsXFJ8zrhgO0v2wsQlidRxNMsB2x/2V6BsIwmogBLnLeV7Q0IK6JC5LJlEyHLtn9M+fRq7Nu9egsiLlgFWDkH9rDvwzrLk5IVLG+wk1Me9qMYS+u8SmuAjk8rsRb7GYSNYKbHyhDAcj6s5GYKO/1SfH6UlQFPcpaRQ5zGB0YfO1McMg63K3KC2NwXGB0da0ybNJLEeV95EcmKSVqKMKrruJE1WIq+eTDpynq7J4tVlIZVGQySNTY9WNYNnqyShUVR03qQrKmRwbL+5emrYrI=
*/