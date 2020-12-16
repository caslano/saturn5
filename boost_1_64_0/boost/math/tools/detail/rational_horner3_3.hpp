//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_3_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_3_HPP

namespace boost{ namespace math{ namespace tools{ namespace detail{

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T*, const U*, const V&, const boost::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V&, const boost::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]) / static_cast<V>(b[0]);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((a[1] * x + a[0]) / (b[1] * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((a[2] * x + a[1]) * x + a[0]) / ((b[2] * x + b[1]) * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((a[3] * x + a[2]) * x + a[1]) * x + a[0]) / (((b[3] * x + b[2]) * x + b[1]) * x + b[0]));
}


}}}} // namespaces

#endif // include guard


/* rational_horner3_3.hpp
zxjXyErUfjWJ3vlz7umxncJ3Z+1YG9hGZE7A1rVb/DU9t4vb9u8i6zDXZwDlwy6RnpMmvUwdlrML502RhZ7YKPbh7saxBbKPpl8NJz134/w1sq2v9i8lH/bknp55j/DdSbvWukf0543WvGUfFafyt0fku1GT7zmYHjJVeqa9uTPzXuG7UeP7WmAVJeZcfLQf5S2wAhJbdTfAlWzRSc+0T/hu1M6RAduJMWiwlmm2KoV8Pyj6ilwzdsoCNh2ZYr3/peIuagPSDuGcB7KwzG/6kH+HcL8wsojLyfkpXg6p31n13LkXFPOHcc4RGavqVpDs1LCM1LMxFC/AVkvMGDP+K7LzCM6HICsW1jWYbAE2Q2Lh83+NIFuOcpYusfINL9Sg+uWY6Jcrmr1wQSqm3l9n0bCAyh8WoPSOYb4jS8i3wpN8UD2n3v+Zfkzt39h59WZQ/qmeU8+x5KiYet+odRP8KolVMKUmk2aZ2F9ClvaowHf03AnsT7zRs/RwsV//hNq/b24EdqayCSy/xP64k5pBWgM7KzHnGl1rkNYncc4fWZ+GDyaQ1iexTUVW4tCiXaSnhk3Zk/4bxe5JrHeRXf5y9xkqY6dgfkliLdpUHE62nMIxELJxHq2/pfgEtkVilX4Y6EXpneZsl8RezOg0ltgvYu+kot1rq2Lq/buZGlalUylfiolfco+zHM1zbZcspLlD9quKqfb2mjTMfXaCP9U9Gnb5r6nvUkyomHpPsJ+GXZwbcpZiApiHrEtGaC3K21/F+E/R7hkCliHXIZf3d6fnzuBaAbKfSg0/QnqeUcfLJr89j0izM2JPMLPuc6wwezyV6bPiOabZJ55+FssfMv+bv8dQvmvYVwMsoyjf1Uw9b6pi6volS8NWHP/ie/JBzdR1wTkVU9U9JhVT13XuwN6V2Il1Dymu/c/h2jyyKN+7NL61aFi/y0FZlEca1vFZHTfSTMMmmFakki4a1nxO6knyXcM8N2RUJ//Oq9lHrX+aSrGrYZPC7seTf+fV+X6y60WxD+I8jmGRlax1aB/5d1702V8pcK582Alat2cXcmcWYDUFU/VN1wIbaRCs5OAL5IPpCq55IztYtsVtil1goRL7JtUvmmy5ylmKxHpcebyH0ruKawzIHhijd1AMXsVxFbJ9R5o9Ij1/w/4LMlXfDZivxAb83uMGaQbMZBTs1JF8+ciWbFFPvAT2Q+2qGZTv2biOjqzYtJzZlH+3ODsmsa2JpSh2g27jPBGyZ+3GbKB8uMPZPi5Y9+Q+bpTef0QevdTkkfl3nLtAZjna6H2yRcPqOi0/S+n9jvM2yKpsbDqY6hdgmyQW98QQR5rlwJhSYktTttP9ROw+9oWRvbxcfwLZcl/93G2fdiaqlzTPPZ3Z8TLF2QPMW2SqvukDXD9CNsS9+vcUg8BKK4JdeZws7kd5iPPlyB683+o62fkHxi6yhCJXLFQX/IHrHch85o0tRLb8ydkciZ3duz6L0vtTvPMFsOC7AXspJh7hOA7Zrc/73aR8f4T5jkyV739x9p1BsOntf4kmO59x1ocJ5uFeiXTxe662pWidP50oH57jvBuyv2KVELIFWEeJVYv0rUmavcA5K2QhrWOvUj68wHKLLHHOTEovE5izYOp10Rc4tkBWM/FOBGn9Euoz4TvcLXKwA9nCDWwnPvcc2MMHvdsSMxhYPkWwKwHPginmjQbS+rlG6yxgxYyCjfzgFI1vWQEDq8EE238qqAxpDayrxLY03luP6hdg9SU23NyK+pisoIG1ldjq8abJFC/APCVW+dXCjeQDMGfB1Hs5gM1SBGt2us4Jeq6wwTaeRnaw6vZnlO/AKkms37ORTSkfihjYEIlFP34=
*/