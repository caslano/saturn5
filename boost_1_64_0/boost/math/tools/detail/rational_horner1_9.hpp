//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_9_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_9_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner1_9.hpp
adLUWbd1GknzLuWnqbIiSYXmtpJT2+oZwisSWUBIcVhQ07xzRfbDIsmjuFawVIUVNE1zgaRZxXVecxHD1pbumy/6vJoVkkeVzLLhHhiXl6RdL5M9cNYKnikpWSxBILiT2iZr1zquMsHLCrh0jexiz5L2TWKhkqoerqzdfZGt46Okjm1Vt3ESp7BvoWunx+l+VxWykHnBh/vQTtlo211X9BufKsWLBNbbtD/+QPqjTrJGpcLtN2gZ/k3aoa05eDMpcPcXvgueIr4z8zpTSSYz2PfR/jvi87pti8rqqGYLohLBds/JHKMyrSyrto20IvU2e/qBvdck2OeznyB9HrdFpPIc8nN9vuneY/vce7jmFmme2O0xbetVUk9YUJe8iMH3J+VtEF5ZZmlZVhETFxVt522fN580ZSxT3gKvkolcGNGhr5J0VZm2udCqIesg3YdIukrVrSiyFHg0XdsG3yVtUEohq0pyGFafOhcFevQo4VaRiHmVtdAGo9wfEW4bybosm0Zzx6T7JOEWOW9UHNcslsjFdyA+dzZXWZKpjKXtuZqm+TTRA64yUVVF3hEj0wpoV/+J4P15Wmctj+Strpvc3HuO+CmJs1RURcT0Wg8tGS132ufOJUlTyTyFCEyJlOFYO+xzT0mRyFqKjMESnaR5xOfdk9dNxdOom8sqeT7waXuU5N9ElchbJZj2EbSDhfViQB8nacs2E22rKcNvIUr0bJlnSZm5ziDL4ggifI3aFsZ27QDDG3xF6RXH2gR9Gx9yHjw1gfFdpxyuy3MSrEwxju4+wJa2dS+CJ7lt/xz5yQOADZcOXZxEtLe2v3eXIhMedviwwyAv3beIPfFqgsHiy+X12OsA027CNKJzw7umN8DvpFpO5rm3AAbVoeV79G3w+3CLoQtwSfcA3jW8AzDynsTezODZ/jsDDpq3ov+6YyGnuyLAOyuLU7tMLMe7EKd2mWhH9sBH6H6wzjiHqOtsyV7v+dtilBsQuZiVRZPHURWz8ClaYLf2cJBfnosi4WmNcuRzhOePvlzF4kgUsqwkQ62i5zBPkHwki8tCFm2Rs3FukbRK2HMMZz/9ETKOqyJvMl07o6h0T/1cUKdK6TGf5wkL3MuZPAYubp8v17A0jbPuCabvdc7IRB+xawSSV8aSVua1gIYY544uWAd8lKzjyqLVfcZNyDkQXdt2/rlt3Y75MnHCiiKXWZ6lmB/cD8MdMM3rXppXEUsuKx6bvNYv9fq2ang+U1EZ2bQyrdqYeZFUR2Tu92UalqumLOO0ZX6EVXsOZHVpw5eZL3mZ8SJWpmhXbRvg+e81Wq5YyCiJuWCed7+Rcj3sy7QszZIkqktGnP7ZclmdfZS0dcGk5HAZUo+N1alb4/PmzNTFTf1oMCb1SK6UkCyctodyq7asz/hyiuVVLLOsqJnbqXUR0KnOv0DyilhRyUy3SsX8LSjq76qVezmQa/O05EWUY2ZXvdywjNP3kn7Wg5/LNjZxJ9dPogZ6/XaXL1MzHpVlI4RyMqjveG5//N7AtqoRdd2kghEXlU5y1em7L9cyJZNca2KOYk6zcCxXJC/BeJxoMa7YGPeP4TywGsi2PMlrmH/HuFs2sng3QWQTxtM2KvNWYWFpi1q5HwRtE4uoymSSohxtVRdr1ZdTrNBdJ1TaMvpqh84fT1GZLEkTESvpyYChGD1LfZaUjzOulatJi1AIvHKP9Ptfg7q1aRq1cZWw8OlQcGf3n0AuV1zUSVp5cg/2dtbXvmzkXBzgjwX26VEh0pSbPrhinJDDMmzbiHo6SmQjJkrZZmXa+MFrg343Nhu0rIVMZdZmgoVmQkEsVuXLtazgtYirLGbEy30g8wCVKUtRJHk=
*/