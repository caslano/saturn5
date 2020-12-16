//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_9_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_9_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_9.hpp
NwdWPf68qllJKdTLxn2jZ45NTjlHJZo/1HevET88BlOFsgkWmB92ApydATU2G9vXlwdR1CKqkQx1GxJE6f6j+W9A/DmJkyAPKK0QP3LWwHPRyx5/FuZxzuIU8z9jQU6OntGdsznQ85jtb0H+6xkt4zyqc2IjyOC+sEfhTTzoKJZdLw6JFxrGH3NHXD5BJAdL01IQHNUFty2G0uKE1mXNKAUbsbF90sxfxlznwH1m3EW8MaEZE2lQVR5vMylZ8GKZn3Z5KSUhEzLVLCXagwwOQU6uLHXXzmzUbNNGFlYXiY3lfg7JSElSBFFOYyNi0FV0mGNGelxEZRCkyIM4EiUS4t/Htqqw4/PfkJwM7FDE06aNtHvEeW1891sxf0hZ3bx5McjzruG3uph+q+fznQY5r8sE8bfdgyYdomUs+jIyyuMsTNtl9FplnEMycsLLunGb3sz50J3rfM/TBctFCFdkSNs1NdukVzT/nz1+EfOQJlXVz4+6xIpu17vehtt1HqY0joKwn9/29VD3QcRbkZqWcIKYkatdd2tE2JjkM176JQ3KiuY1ab0Gh9NfRbwliaukKkqGWAe15Ui/sfE2vP6jVRnyouTEuWa6OjY20S7ItoWLKC8FEVTIrGSZLwebbrwv9mOUl4qwMq/SJC59GX0N23l7YtfbcXliSou8CLAMMOGblOfhb/fKk8S5VA315VytPE98Oy5PlomE86hol9Fenjd45aFpItKyCJCMybHR2c3qxytPwqsoEVmfnKvWj1eeNAtSVtNWGX55TH97B27vRRHGssflrgy/v2neEY+3SrOURWWEedv7SoF4S1JVKYtFifLerkNb/lVXBk1kXVDKo7Qkm4VDIVbGOZSPmkRJHqSp7SftQxCeo3wNycgJrUUuirwiA0N2ePttiD8lVZhlvLL87cOXnWd23unvH8eUx0Fs+fHw5e+Z7XH5aUjyUNZEJnKyWcgLYmUwJKMgEPk9jSmS0RoKxJFx2pfBYb9KRK0yeu0yPopkZKSC4BFUlnezsA3O+zA/c2UIksVVnAZlTjjyfsXt+c+oDkrCmUiiKAkxE3aZ9d8l2v0utKZlNBKRiBnhrifsBtNx8xbau7z5ecijBPZfeLsbqD8/Z4g/IXGUsywoWTv/qrFB5uwB8XNS1VWdhIFKH7uD+vsqpxFvTuIij/Kyppi3e9xujmGdn0X8JcmriCVRkPj87vaxf0f7IpIhSFoHURlGOZbhnP/MouMfEuo+jORUJIQL4yGNsRx1joOlEPNm6Dkc67mO4pQmqRFhV0edJXN2dc7bM4+zKkmp1X/f4XL//HkayUgILENEmDFi3KhABgS5bTyj+uYsM4hfEFnulBdOPRp+XJm+Dp91DtuhjDFZlijsl+NVKrFleR/KS0piERVpLJy89Nr6w5rmv+TpIsyLirKCY36/P1j+H3v8NOI0FLWtD+z+avin9FoG8YekquKAVVVBfNcPtQbRbWf7u/E+cZ4XURlnxPH26Ou7e96N+24ZRXmUBCHpd+fQzMS8N+vyFqSuspLmLCDWowGvqxlKi5IiYIxlQUX6XH8w3xMRX0CquqhZKRXjuTz4tnTV5atIFLOKB1CNaH8Y7/U910sry3mV8rA2THifxuTxDR4fC0QSxVw4fE9vG3fPu3wUHn0WVRxFZBNvArRe+/G7/feHIh4VRUra3AdsPa6YtfO7vb4fshB2KjF/n5rteu09mF9AnJ+EY3arATx/RLwxCXlBYbxr9Q713nArXN6KpHFJgyjLDK/zzuqy2f/FPFUhu2aZEtfZWrFYnkWXpyZlyGPBs8Qw2Z5leZ6F00kqDm+FhsT1ztZ5M3t1Lg+NSBIVtIqKmGziEu0=
*/