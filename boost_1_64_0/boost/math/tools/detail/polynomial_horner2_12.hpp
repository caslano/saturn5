//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_12_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_12_HPP

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
   return static_cast<V>((a[4] * x2 + a[2]) * x2 + a[0] + (a[3] * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((a[5] * x2 + a[3]) * x2 + a[1]) * x + (a[4] * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((a[5] * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((a[8] * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((a[9] * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((a[8] * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((a[10] * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((((a[9] * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 12>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((a[11] * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((((a[10] * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_12.hpp
Pv/814gys7ExHDygPZ9tvfj0idQ7xHwgjwHPKq4Iy4r2SHZxDi9SqwxGuP+TII3aNM9ueT4Zm/eObH1RKsKyzryoDvrLlCwOSYNn0oyeq7aeMBZJEdZx0Rb/U8/S+WnQY89v/402VY8G0HfwTRwj6/AyG9lE+vXLAGjnq5s47r4cYNLx282GV4WaQ9/2RxnG5HGesVVzIAf6BDbzZ73NwvUwbteZxe0ah+Fey5+Gg7/zxJkcszhah+aQv9MdwBkmUquRrk+oTz6408LPzAFG85hdgDnX2fTZjrMPkrpVmb9gcWlteXVlBcQtP1kgqtKGuGxrOs5NgC3ItQuF7d4MYbCepH7+bSoMz0DRWubfm7l/3ipoYz++5X5end/T/UgVQh/C++HNKv2hsiutCIlzebTLgVUXm9ts4xxrJYucH431cZQmOku0EzhzK7AjQCtveh/y6s/U99npC2fOiCPH/vsfW+6D/ya5o7P//Y8ag3XZv/5fIDdYnDl66LAseAy/asIPyVDkQ6PW4YcPT9j8cQw/eswOP2XCj0xqvp6fy7qzRdkK4qD6dpHCVRz2+cWvE6biYe8ibUYM4mJyLydM5dO+63tNYTDDoTBo81uG9Rrr8Ng2DIOYMfw6hUvNpOPqdgjn7WB1zISpjNH5mR0YLlVT+HsxHDJE4c/cacIhSgof2SXDsZ1R+IHdFC5jwPDyDhQuNWF/MKfKfm1pVT4xcOjYOOsPrsKegbIl4pBnLNNRpz/YsxnCuB0uQ5idTh3vQRUvnGuBKHkftBXilMH62AuV1SbAeJx/gTCKE+vA1p44r/8T4gTfcqaeU5zbVJyAUXz7N0E4j290M4Tx+N4AYRQf2vayju+oqvc8n1+WP9tVnAYfYbbd7tTTK1sgjKfl+iiE8bS8ayuEdfO+jmmBZPC8j5l0jPC8j/Xkfawn72M98U3q+CZ64tuh45tw4tvRiQ/CuvHt6BlfRmV8bI87LsuqCG95Tv8ocyb/H5a+o2Ep9fmhJ6ae0UYwMcY3Au05zC7Il5riTx6GlQDNHWBPEXGJHFYkGczOiBAOE4xD8vaaOsNL3wNH+znTp184XWchrbu3bcxr/Bx5n9y+IQ9eZKO58A7G0/epgWn5ktnJODC5AQLtie1ycZZ02n/Y7fJY0iUPz2/08mZXzp1dt8/M2uUYFKL1vbZJglveQ1VnZh8lx1B1Fmj19Ly67jNs62+U4at/g3hOn1taXl86Oy1xfe/kzRKzFjH0zQDmT5sQUZO8zPlm8IitFgfigyKy6sz49h5cLdFJx6UdFge/lFM/tG+njcPHSMIm7kCYfoaL5jZ3BMz6lgp5Pkz45TsBrrYjpQkBlFsLln/9k3sABxnYH7XecLqNwrufU0n+6p01D2jWnsZH7wLhfOWos0V3svZ2Oe731bm7djl9Z0afebcuzz0zmt69y3G/q177K6+nSetXQZ3c8ncRc2dm799sfbGo6qBI/cbvX9stu0v+lQW4OTP7pONCTueNTuHojL02SYs2uIl7OB2dtg/zO2ziuwLalSjI4B7oMzf18c4tyEttymUt83G5ucvV6yjU96ZeDvgPprs0Jo23b+lyzc6S3IhFnZOjnNc9NUf7w9c24Op0Kjp7K2lrly/X4eTHeFsvji+O4lq6n2fMiLwL27s8WLxrheTfc6zLg61tds69h6OPLaPtTu3o4civUc+BGQFk1OKO7ezhDvrt/Nt+rmtnzPe+3Zzv3LCi85Yb8CBf7BzNHXp46/MDrZDG4jty3nA3dn1luGFOtvz6nTjPaitYV9b3cI6b9n23cRzqnYpP2pmdHbsz5ynP3XA2RkVntbe7cB7VO3ZekXOoLtF3+r2co+s=
*/