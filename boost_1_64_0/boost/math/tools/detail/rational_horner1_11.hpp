//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_11_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_11_HPP

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
   if(x <= 1)
     return static_cast<V>((a[1] * x + a[0]) / (b[1] * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((a[0] * z + a[1]) / (b[0] * z + b[1]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((a[2] * x + a[1]) * x + a[0]) / ((b[2] * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((a[0] * z + a[1]) * z + a[2]) / ((b[0] * z + b[1]) * z + b[2]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((a[3] * x + a[2]) * x + a[1]) * x + a[0]) / (((b[3] * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) / (((b[0] * z + b[1]) * z + b[2]) * z + b[3]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((((a[4] * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / ((((b[4] * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) / ((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((((a[5] * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / (((((b[5] * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) / (((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((((((a[6] * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / ((((((b[6] * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) / ((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((((((a[7] * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / (((((((b[7] * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) / (((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((((((((a[8] * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / ((((((((b[8] * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) / ((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((((((((a[9] * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / (((((((((b[9] * x + b[8]) * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) * z + a[9]) / (((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]) * z + b[9]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((((((((((a[10] * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / ((((((((((b[10] * x + b[9]) * x + b[8]) * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) * z + a[9]) * z + a[10]) / ((((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]) * z + b[9]) * z + b[10]));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner1_11.hpp
0f6C9kq/QJ451gAPbXA2A6/n8wDqfP4K8szlv7IdO7YFOWSs0WwxvteVAzlCztRWyTHNctAW6qLg9NbdRWJPV25Dfpf2I3ZrlwwuZgA54S2QQ82F0a7gguT0fkpC1R3bLrj0e0za6gPI6WJ+jL7Dx3coXu+5kqwf6UeyiwxNALkPHUFud/NmbKfzktt73kPr4ZadfBEp5pVy6NzLaPeH3gq4vcdaoMv6vYBcc/5K+tZDb014ZuGx7MjrNcaRemU7gd9z/kT074Li0m8cJ6Ev/9tQTjs17f1LidPvKZDQ9u62yOkyLyZ5ehNye+rOntshp4crccV9I3K7jPe0z+7dBVz6nRZ+6pR9cXiHTo5eXxcQJ0//yXafvCPixreV2OO+x+DJdG4r4tm3G/DKGeSM7oN6/M4yHM6AAUTsF3cRGDhPakMqvqm7KgykVDi7uwxvQjj6Z9dti5yI+albZEV5A+8XTs8y4R/4DZV/YMupOVNH+/Q64D8f75eIfL5d86vcT3Dwikl8SiNW+YpF+8lBgoE9mfDmDRcHMP6jQzoPPAIj9gvEfPm++22lzm1UGLjAVDLjm1X4oxpz9O3g8a0K4x/G9eW61ja/qLDl6RP12okV0Z7yTeRP9ENNVoaBkHelp3sHTKyy51SyOwcBhxdt1kVWUPahQ4BVttQQgax4hf/CwKHidfmRjQbeWiNvnH1rUycON3X0OF6zmXIg8zo+tYXi/I/j9RXAhY3IfUE/K6xtzc5v2C9wv9gPlvsl96VneIEdBZmXp6zgOnvkSHp4Atri8ASIrbb3RHnct7hlfZeM24yatssn+2W2Kt1TbfnsfoU1+c09pevn+c+n+p2Faf7v2ChUyYExPc7XDAI+uzA928b5JUxV1guDVVkd68hU7UitBfcDwXf2DoVv6sD3E3xrBz5G8B0d+AGC37oDHyf47TrwCYLfsQM/SPC7dOAPAvwOvD123kOWnxZfYZtMbD9iW01sDLEdJnYAsVub2DhitzOxCcTuaGIHBSbLSIpI/Op/uh8wMIEHnaJvXn2mja3Ozxwcx3sgdBz9bJszOzOLjCp+wIYVPlc3sD1bJSblaLyfE9jsjMRp3j4v0jXzdk9N77/Q73AHGEtLi9NQhv1jk4qIfu7P9Fdnh4roiQ6v3i25pYG3Y7CXVrn770eCN5qm4p77yxDhuvUOLumXFzF/sn4U/qd+gnfU0b5BgmP7afF/EXGtHmkdfUlxYGwgdUR4X9Z4Rl3iPcmBDp5kKc6+DSZHxUTyfgk5RLfkmW/fNdqFo3g23LVNkHcHvia+De8n5VXwv6BoR+ziaN+tOPalSY71QR86EgWZpfJ4E//5Sn/XaPH+2wByeqgDvqu/VXCpGkJ64v4ZxVdoemoOaHLM9HJp28DLi/OsDPwy5Glh+9c7z5pZn59nYp4hv01f7bcf5dcyL6s+TYi1+nXs+NrqU7Fcfxswsfa0gLzZNaRzYLqE9bZ3g4HV6id12Z0bJb5Wh9tide1b//VNgDXr/HO7xCuJM6r/oi3V7/qIb3jL9uMoy5ieW9MO508gQ2y3vDIP3IR1FrHDrn6b3iYZc8PAdh0/ZlrplP8G2GN9FH+3q6zuNgOD3l0G/Cuwx/oExPHus1b//OdreLeZE/Fu83Y+h/4aj8OOgvxRWXtO/U34/xxeTXBsLkruDn29nyNHDx3YX5sDU9s6PG24XIcGgfSwvZDHVby+Bh6QjzaejHGlm7pwMDbVfktbgDezUjupp7nYJ99ab3xzEPo+JyyvL9VgzdpU2OXPS2xu8SkKw7J8A9KH55AB0t8GHBAYiBlYOSSw5dUOuTdukBhkhWKXNgqMGxEgdouq7s/+EHRiZgU=
*/