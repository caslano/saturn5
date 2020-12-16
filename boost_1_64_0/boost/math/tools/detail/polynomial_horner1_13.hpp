//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_13_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_13_HPP

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
   return static_cast<V>((((a[4] * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((a[5] * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((a[6] * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((a[7] * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((a[8] * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((a[9] * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((((a[10] * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 12>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((((a[11] * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 13>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((((((a[12] * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_13.hpp
38040He9Ks+Ntu4Txrb5CMAKlKTE0VICsdDAdT4ceL10PrcP4IUGbmv9FwFWIZ1MIs66rWt9hbe19tsDPgmRuPZb8Y2+jfefjnXXmKnA07DWgvFefd4fNLRTTB6zGOC6t+4bzwQ4iqzHygkD1lnYNxrnKwdOy5kXWEPOpmm1MwM4kzm1kbhbo9/gwkkLh1KXzRqvCuA9kjoUp3DzL/D93gTXfd1QB5Kk41bXMgjV7PB8uiEEdVh0/xzAYxSsMV6maUzlE7UpHgEtz0XmXNr1XgbgGMrVVjqq6Xx3inS4SSN0J0e5Wt1vf6fHRqSFT9ZGVynvHZaZGdr6B4BPZz4ZRHI6n2ueZTf8coJ6mHd/061efgeZ8VDPSw+GbaytEySkypkfmc8nwAXW7pGf+mBQ1xSU1ELhHoePh/O5yyMGi6SUrZiL/GjgPYPf+7Uesyt95JobXSH775vXmcUeKMuD/bxI5XKzvGq/fTjdwWUXwBxvv/ae4VvvbQCPEXNG0twM4PB296w+fq3rccZBvwaXHN7MaXSq6t2987t5bqrINs4+NrSBU5KqIFjDlgPd6n7X5kKAoygG76JWtuGmTgDOn+pcCLASUV8inajYcc5Tw/3DPKWuvjG/PXCThJnJE0vDX0whFNvTqLYv/WGPTYgJRVM2c4Pm37Tz7ob762AnpXGMUUcALNcn74Jj5IkPgXMBLS5YMXSESb75rft7p3v5evnwYnVv9MqMhzlKNFfBNfi0Qxyv0pqtHMCzEsPLYWtYV8DU87edgd1+yDh/C+koGclb5+ji/n0YYB2KjpawfbhhN76wFGgOz0Q/3ZcREKPBYjwdD00OFptFYI4DU2MUAV6MBC5JXZhtoNnec74gsXwLA1xAipdI8Jzku/sP3psug+7kaez9e/l5GGissW/+YLCZttF6ql3jX9nsovaxHptQyQFEqW3QYjLactC0b+GHwrVd5ZpLSyU6nEy8pcaN8+UAS5DHzAc8zznTXJNfQN26m10W4Hz62h4XUYg0BrLcM+X5LrWrptYXHzqMW48D4SENtslftP5NY/z12wArkaaBKGZWUPLKNL0aG2OQfgTgGaLelM80vjLuLn2TH84aPjXUW1jngvFijb11Zfw+/MLAm60rtZFxjc3f4QPv14Z2FYbqIJRvWDlvBO6c3Ruw3x+wJJvaBWaWy96D9W4A1bcxsG2l4Mw6zTpbX8nekLBtH/kwaCNPlSgvXVCNZXZjZ1pjb+ysbPRCgGVIMkajD7QnnB7jXnzgYuW/NvByzl02kUEToCzU/5o3DVgrlAkSY9CpNKX5jGMVn/EuwCoknBdEYZTFb+ycnGXSqT/unAO3jdYfPzpwK+0SZ4o07rz1YQfvm3sFWD8/DbA6jyPmgtYanc/35bcPppAijRy21ZcGe3PCsBLU9revuxrfys+Z8w+I/XbGQr/56DWJHmDZYe5jdW5s728B1qIgFU1aGIDF98pede84B0doHl1tHX7ow0HfjEwwa3QARRhKVvGDntrjErKYWe4trPabDmvultMaKzDjwLlyCcBKrQRAn50Ky1J2dnv1HcMAHiOjolS5BIAPJ++7P+T4eEuPu66Vi7mDUMTK0x/KvBhjZNwG8im56HBkKEfJLDnF7r1rka97xlEvrRmx3peAKRHz1B6k3+S3xlgMPXbHGalD1Lnr33rjjd1Z9qz6VAJZbh1TiUZ0eHE/79Jm2QeWfj3YKiST+0dAJupwK/fImzH/6EjqHDvgGKPGY4bRu08Oj0uI3fP8BLhnvNTifn4VYH2Jk8UjwQll5MHZ8d68bd/tXenOh9ihPxzLkJ7w3GRIgzJ24pYyqr/9I8ZxlTyTSqB75zfv5Yk=
*/