//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_9_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_9_HPP

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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>(((a[4] * x2 + a[2]) * x2 + a[0] + (a[3] * x2 + a[1]) * x) / ((b[4] * x2 + b[2]) * x2 + b[0] + (b[3] * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>(((a[0] * z2 + a[2]) * z2 + a[4] + (a[1] * z2 + a[3]) * z) / ((b[0] * z2 + b[2]) * z2 + b[4] + (b[1] * z2 + b[3]) * z));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((a[5] * x2 + a[3]) * x2 + a[1]) * x + (a[4] * x2 + a[2]) * x2 + a[0]) / (((b[5] * x2 + b[3]) * x2 + b[1]) * x + (b[4] * x2 + b[2]) * x2 + b[0]));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((a[0] * z2 + a[2]) * z2 + a[4]) * z + (a[1] * z2 + a[3]) * z2 + a[5]) / (((b[0] * z2 + b[2]) * z2 + b[4]) * z + (b[1] * z2 + b[3]) * z2 + b[5]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((a[5] * x2 + a[3]) * x2 + a[1]) * x) / (((b[6] * x2 + b[4]) * x2 + b[2]) * x2 + b[0] + ((b[5] * x2 + b[3]) * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6] + ((a[1] * z2 + a[3]) * z2 + a[5]) * z) / (((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6] + ((b[1] * z2 + b[3]) * z2 + b[5]) * z));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>(((((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0]) / ((((b[7] * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x + ((b[6] * x2 + b[4]) * x2 + b[2]) * x2 + b[0]));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>(((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z + ((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) / ((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z + ((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>(((((a[8] * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x) / ((((b[8] * x2 + b[6]) * x2 + b[4]) * x2 + b[2]) * x2 + b[0] + (((b[7] * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>(((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z2 + a[8] + (((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) * z) / ((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z2 + b[8] + (((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]) * z));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner2_9.hpp
dvehJ8hejnfuI7cgh6nOAANxMpxXTfd2nUtDcWDLg+w4cDhHcDjvrZYLZU8v4TnI1ViDnLYOQxxIS6vrIvr5wDNB9grGxRjB4p8ft+DthTw+bXf4msmSRf5gMyzKKY8GdBE9R2NRkI2A332uYLHhqdceR4STpzv1hOUc0WyCRbEBFNDQ9qMLguxz5DqOFRyWZCz9Wfa0wLmvPkBw6m6TIa7lgDYSPmuoSei5fk8G2VrME+cJDl+N+eEs+XUCX5aEUzTBwx4m9cR1PexGigk9Srx2QkLnwO4Psk/B4Xw7t+3Eoevk1zDv6AsOifMhA/EJ2lesNAk9PjE3yG4GhwsEh5pgztnya4Tn4A5mqk/OlZlD6OcH8m05BLR729eJ2AQY5AoGry08skh+LeSpiFXNQV78HBMMSqtKiCFIBa2GqvKjLrTrRob+Spe9LOJNsIi6NGkHbD8DDCiPSpWAbgdFQfYjGFwkGOx//vKj5deJvA/soCZJ1t4fsdDA3Eib6qok3HPjeUG2DzhcLDgUW7c9Bk+BN+JF2FG9ZK3EJiMcCDNNlIC+1x4bdM5Fx2nnolEecdVJzCauk2g3kfRIVAno+8tzg07u4njB4Pi/JsNnmsRDCZ8Je4piE3NCuJp4WpQCmh2cHmSfYC9xiWAQ+62+n/w6mS/DT21YH1uMMKiqqKZLzVMSbr/xtCCrhf+cJzicc+BG3Iwp4Y9aiFLCFrL3N8GhuDBMd5lSSbjPgYcEnXzNfMGhl7Vtm/xayluOgd+YJn2FehMcRE4pbbjaUVAMkoNsFBgUCAYnXV2KeaGMtx2OO6V9GBvIGMtZc78BBvTrJCT0dbIj4Ny5nyA4xL//FDkS5XwJtpChkBwTwXR6W8iiP9uDhM4h56cAm4QYQ9iOQ65IQQ5AjHsRh2wISA4xIxyoNxGOgoqzfBVw6uFFtHp4l/JK7CfXg0H6XPoxkUW/iYCEK/Z2R4AdBA6FgsOIV/ZErmEFX1Avf/LuJeMLrIDad+xcybKGDx96JCEJJdLl86s4X2n4/GpCOBKlu3Iu/3YtLj8jwL6GHUwUdvDl35OmyN5V8ta94Dd1RzyadjxE4p3/5k2Jlh1GVidTE+myHVTtUks3n3ZMJJpZXUpWpWcniS5zqOaNLg5NZjgQJ+27ZNzr5uUBVoUxMsmuG5myFl7DFD54d3jX3XBOcY+RMUIYddEl9Lf+As5ee7K2165x3iTIF38KFCxGu9dGIyl32ztJdHl8XLbL+Bgwwcj4iJQUhcnO8DSRLrOYusucOd0UC3oQ+v37qQEWwrgos2v3RK68Vfbycp5tYYRYOLujnh8KxhEfbWsSelx2Jw7lgsOstpU4q5nGYx685QMOmfca4UB5tK1paD5VTYCdCA4xweHq+XEMhSt4MID1wotzCjMcCBM+NAk9JndpgI0Eh0sFh0PHp10jv17Jl/VI7LWQW7yR9OwOjaQ9vdNFdBbriwOsB/beFYLF4pXX4zz3Kl7fHdWdAtIm2H1GbILyfN+toThEAqwaNhEXHEbX95mPm7F8MPbftUFZ/5DR3s9AG0kTzt0a6q7weDVXVgoOayrnYma4mrciXp3TTZ7dZC8iXjc720jrUyoJV5z24gDbGxyqBIeNl67Nk1+v4dnOO6lyXBSbGReEp1iahL52nhpgl4FDteAwsu7FZvn1Wh5LQ9w+WXJoMcNhYiH5miEltPflT1V7jCnaHmPGLu+eFX9H+l4FGkm7x1ASrnOcUwKsDBxqBIf9Nr16r/x6Ha/FuGiFL5V9vxF7iBTGyEEkNBSHHOVLXSY4lFmP4UTzer4B8+SyAGqD/jXbBAfKkxxNQ6uRmhVgB+Ncb6rgcP+1ox6QPb0=
*/