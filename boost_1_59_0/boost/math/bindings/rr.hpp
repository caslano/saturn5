//  Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_NTL_RR_HPP
#define BOOST_MATH_NTL_RR_HPP

#include <boost/math/tools/real_cast.hpp>
#include <boost/math/tools/precision.hpp>
#include <boost/math/tools/config.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/tools/roots.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/math/bindings/detail/big_digamma.hpp>
#include <boost/math/bindings/detail/big_lanczos.hpp>
#include <stdexcept>
#include <ostream>
#include <istream>
#include <cmath>
#include <limits>
#include <NTL/RR.h>

namespace boost{ namespace math{

namespace ntl
{

class RR;

RR ldexp(RR r, int exp);
RR frexp(RR r, int* exp);

class RR
{
public:
   // Constructors:
   RR() {}
   RR(const ::NTL::RR& c) : m_value(c){}
   RR(char c)
   {
      m_value = c;
   }
   RR(wchar_t c)
   {
      m_value = c;
   }
   RR(unsigned char c)
   {
      m_value = c;
   }
   RR(signed char c)
   {
      m_value = c;
   }
   RR(unsigned short c)
   {
      m_value = c;
   }
   RR(short c)
   {
      m_value = c;
   }
   RR(unsigned int c)
   {
      assign_large_int(c);
   }
   RR(int c)
   {
      assign_large_int(c);
   }
   RR(unsigned long c)
   {
      assign_large_int(c);
   }
   RR(long c)
   {
      assign_large_int(c);
   }
   RR(unsigned long long c)
   {
      assign_large_int(c);
   }
   RR(long long c)
   {
      assign_large_int(c);
   }
   RR(float c)
   {
      m_value = c;
   }
   RR(double c)
   {
      m_value = c;
   }
   RR(long double c)
   {
      assign_large_real(c);
   }

   // Assignment:
   RR& operator=(char c) { m_value = c; return *this; }
   RR& operator=(unsigned char c) { m_value = c; return *this; }
   RR& operator=(signed char c) { m_value = c; return *this; }
   RR& operator=(wchar_t c) { m_value = c; return *this; }
   RR& operator=(short c) { m_value = c; return *this; }
   RR& operator=(unsigned short c) { m_value = c; return *this; }
   RR& operator=(int c) { assign_large_int(c); return *this; }
   RR& operator=(unsigned int c) { assign_large_int(c); return *this; }
   RR& operator=(long c) { assign_large_int(c); return *this; }
   RR& operator=(unsigned long c) { assign_large_int(c); return *this; }
   RR& operator=(long long c) { assign_large_int(c); return *this; }
   RR& operator=(unsigned long long c) { assign_large_int(c); return *this; }
   RR& operator=(float c) { m_value = c; return *this; }
   RR& operator=(double c) { m_value = c; return *this; }
   RR& operator=(long double c) { assign_large_real(c); return *this; }

   // Access:
   NTL::RR& value(){ return m_value; }
   NTL::RR const& value()const{ return m_value; }

   // Member arithmetic:
   RR& operator+=(const RR& other)
   { m_value += other.value(); return *this; }
   RR& operator-=(const RR& other)
   { m_value -= other.value(); return *this; }
   RR& operator*=(const RR& other)
   { m_value *= other.value(); return *this; }
   RR& operator/=(const RR& other)
   { m_value /= other.value(); return *this; }
   RR operator-()const
   { return -m_value; }
   RR const& operator+()const
   { return *this; }

   // RR compatibility:
   const ::NTL::ZZ& mantissa() const
   { return m_value.mantissa(); }
   long exponent() const
   { return m_value.exponent(); }

   static void SetPrecision(long p)
   { ::NTL::RR::SetPrecision(p); }

   static long precision()
   { return ::NTL::RR::precision(); }

   static void SetOutputPrecision(long p)
   { ::NTL::RR::SetOutputPrecision(p); }
   static long OutputPrecision()
   { return ::NTL::RR::OutputPrecision(); }


private:
   ::NTL::RR m_value;

   template <class V>
   void assign_large_real(const V& a)
   {
      using std::frexp;
      using std::ldexp;
      using std::floor;
      if (a == 0) {
         clear(m_value);
         return;
      }

      if (a == 1) {
         NTL::set(m_value);
         return;
      }

      if (!(boost::math::isfinite)(a))
      {
         throw std::overflow_error("Cannot construct an instance of NTL::RR with an infinite value.");
      }

      int e;
      long double f, term;
      ::NTL::RR t;
      clear(m_value);

      f = frexp(a, &e);

      while(f)
      {
         // extract 30 bits from f:
         f = ldexp(f, 30);
         term = floor(f);
         e -= 30;
         conv(t.x, (int)term);
         t.e = e;
         m_value += t;
         f -= term;
      }
   }

   template <class V>
   void assign_large_int(V a)
   {
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4146)
#endif
      clear(m_value);
      int exp = 0;
      NTL::RR t;
      bool neg = a < V(0) ? true : false;
      if(neg) 
         a = -a;
      while(a)
      {
         t = static_cast<double>(a & 0xffff);
         m_value += ldexp(RR(t), exp).value();
         a >>= 16;
         exp += 16;
      }
      if(neg)
         m_value = -m_value;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
   }
};

// Non-member arithmetic:
inline RR operator+(const RR& a, const RR& b)
{
   RR result(a);
   result += b;
   return result;
}
inline RR operator-(const RR& a, const RR& b)
{
   RR result(a);
   result -= b;
   return result;
}
inline RR operator*(const RR& a, const RR& b)
{
   RR result(a);
   result *= b;
   return result;
}
inline RR operator/(const RR& a, const RR& b)
{
   RR result(a);
   result /= b;
   return result;
}

// Comparison:
inline bool operator == (const RR& a, const RR& b)
{ return a.value() == b.value() ? true : false; }
inline bool operator != (const RR& a, const RR& b)
{ return a.value() != b.value() ? true : false;}
inline bool operator < (const RR& a, const RR& b)
{ return a.value() < b.value() ? true : false; }
inline bool operator <= (const RR& a, const RR& b)
{ return a.value() <= b.value() ? true : false; }
inline bool operator > (const RR& a, const RR& b)
{ return a.value() > b.value() ? true : false; }
inline bool operator >= (const RR& a, const RR& b)
{ return a.value() >= b.value() ? true : false; }

#if 0
// Non-member mixed compare:
template <class T>
inline bool operator == (const T& a, const RR& b)
{
   return a == b.value();
}
template <class T>
inline bool operator != (const T& a, const RR& b)
{
   return a != b.value();
}
template <class T>
inline bool operator < (const T& a, const RR& b)
{
   return a < b.value();
}
template <class T>
inline bool operator > (const T& a, const RR& b)
{
   return a > b.value();
}
template <class T>
inline bool operator <= (const T& a, const RR& b)
{
   return a <= b.value();
}
template <class T>
inline bool operator >= (const T& a, const RR& b)
{
   return a >= b.value();
}
#endif  // Non-member mixed compare:

// Non-member functions:
/*
inline RR acos(RR a)
{ return ::NTL::acos(a.value()); }
*/
inline RR cos(RR a)
{ return ::NTL::cos(a.value()); }
/*
inline RR asin(RR a)
{ return ::NTL::asin(a.value()); }
inline RR atan(RR a)
{ return ::NTL::atan(a.value()); }
inline RR atan2(RR a, RR b)
{ return ::NTL::atan2(a.value(), b.value()); }
*/
inline RR ceil(RR a)
{ return ::NTL::ceil(a.value()); }
/*
inline RR fmod(RR a, RR b)
{ return ::NTL::fmod(a.value(), b.value()); }
inline RR cosh(RR a)
{ return ::NTL::cosh(a.value()); }
*/
inline RR exp(RR a)
{ return ::NTL::exp(a.value()); }
inline RR fabs(RR a)
{ return ::NTL::fabs(a.value()); }
inline RR abs(RR a)
{ return ::NTL::abs(a.value()); }
inline RR floor(RR a)
{ return ::NTL::floor(a.value()); }
/*
inline RR modf(RR a, RR* ipart)
{
   ::NTL::RR ip;
   RR result = modf(a.value(), &ip);
   *ipart = ip;
   return result;
}
inline RR frexp(RR a, int* expon)
{ return ::NTL::frexp(a.value(), expon); }
inline RR ldexp(RR a, int expon)
{ return ::NTL::ldexp(a.value(), expon); }
*/
inline RR log(RR a)
{ return ::NTL::log(a.value()); }
inline RR log10(RR a)
{ return ::NTL::log10(a.value()); }
/*
inline RR tan(RR a)
{ return ::NTL::tan(a.value()); }
*/
inline RR pow(RR a, RR b)
{ return ::NTL::pow(a.value(), b.value()); }
inline RR pow(RR a, int b)
{ return ::NTL::power(a.value(), b); }
inline RR sin(RR a)
{ return ::NTL::sin(a.value()); }
/*
inline RR sinh(RR a)
{ return ::NTL::sinh(a.value()); }
*/
inline RR sqrt(RR a)
{ return ::NTL::sqrt(a.value()); }
/*
inline RR tanh(RR a)
{ return ::NTL::tanh(a.value()); }
*/
   inline RR pow(const RR& r, long l)
   {
      return ::NTL::power(r.value(), l);
   }
   inline RR tan(const RR& a)
   {
      return sin(a)/cos(a);
   }
   inline RR frexp(RR r, int* exp)
   {
      *exp = r.value().e;
      r.value().e = 0;
      while(r >= 1)
      {
         *exp += 1;
         r.value().e -= 1;
      }
      while(r < 0.5)
      {
         *exp -= 1;
         r.value().e += 1;
      }
      BOOST_MATH_ASSERT(r < 1);
      BOOST_MATH_ASSERT(r >= 0.5);
      return r;
   }
   inline RR ldexp(RR r, int exp)
   {
      r.value().e += exp;
      return r;
   }

// Streaming:
template <class charT, class traits>
inline std::basic_ostream<charT, traits>& operator<<(std::basic_ostream<charT, traits>& os, const RR& a)
{
   return os << a.value();
}
template <class charT, class traits>
inline std::basic_istream<charT, traits>& operator>>(std::basic_istream<charT, traits>& is, RR& a)
{
   ::NTL::RR v;
   is >> v;
   a = v;
   return is;
}

} // namespace ntl

namespace lanczos{

struct ntl_lanczos
{
   static ntl::RR lanczos_sum(const ntl::RR& z)
   {
      unsigned long p = ntl::RR::precision();
      if(p <= 72)
         return lanczos13UDT::lanczos_sum(z);
      else if(p <= 120)
         return lanczos22UDT::lanczos_sum(z);
      else if(p <= 170)
         return lanczos31UDT::lanczos_sum(z);
      else //if(p <= 370) approx 100 digit precision:
         return lanczos61UDT::lanczos_sum(z);
   }
   static ntl::RR lanczos_sum_expG_scaled(const ntl::RR& z)
   {
      unsigned long p = ntl::RR::precision();
      if(p <= 72)
         return lanczos13UDT::lanczos_sum_expG_scaled(z);
      else if(p <= 120)
         return lanczos22UDT::lanczos_sum_expG_scaled(z);
      else if(p <= 170)
         return lanczos31UDT::lanczos_sum_expG_scaled(z);
      else //if(p <= 370) approx 100 digit precision:
         return lanczos61UDT::lanczos_sum_expG_scaled(z);
   }
   static ntl::RR lanczos_sum_near_1(const ntl::RR& z)
   {
      unsigned long p = ntl::RR::precision();
      if(p <= 72)
         return lanczos13UDT::lanczos_sum_near_1(z);
      else if(p <= 120)
         return lanczos22UDT::lanczos_sum_near_1(z);
      else if(p <= 170)
         return lanczos31UDT::lanczos_sum_near_1(z);
      else //if(p <= 370) approx 100 digit precision:
         return lanczos61UDT::lanczos_sum_near_1(z);
   }
   static ntl::RR lanczos_sum_near_2(const ntl::RR& z)
   {
      unsigned long p = ntl::RR::precision();
      if(p <= 72)
         return lanczos13UDT::lanczos_sum_near_2(z);
      else if(p <= 120)
         return lanczos22UDT::lanczos_sum_near_2(z);
      else if(p <= 170)
         return lanczos31UDT::lanczos_sum_near_2(z);
      else //if(p <= 370) approx 100 digit precision:
         return lanczos61UDT::lanczos_sum_near_2(z);
   }
   static ntl::RR g()
   { 
      unsigned long p = ntl::RR::precision();
      if(p <= 72)
         return lanczos13UDT::g();
      else if(p <= 120)
         return lanczos22UDT::g();
      else if(p <= 170)
         return lanczos31UDT::g();
      else //if(p <= 370) approx 100 digit precision:
         return lanczos61UDT::g();
   }
};

template<class Policy>
struct lanczos<ntl::RR, Policy>
{
   typedef ntl_lanczos type;
};

} // namespace lanczos

namespace tools
{

template<>
inline int digits<boost::math::ntl::RR>(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(boost::math::ntl::RR))
{
   return ::NTL::RR::precision();
}

template <>
inline float real_cast<float, boost::math::ntl::RR>(boost::math::ntl::RR t)
{
   double r;
   conv(r, t.value());
   return static_cast<float>(r);
}
template <>
inline double real_cast<double, boost::math::ntl::RR>(boost::math::ntl::RR t)
{
   double r;
   conv(r, t.value());
   return r;
}

namespace detail{

template<class I>
void convert_to_long_result(NTL::RR const& r, I& result)
{
   result = 0;
   I last_result(0);
   NTL::RR t(r);
   double term;
   do
   {
      conv(term, t);
      last_result = result;
      result += static_cast<I>(term);
      t -= term;
   }while(result != last_result);
}

}

template <>
inline long double real_cast<long double, boost::math::ntl::RR>(boost::math::ntl::RR t)
{
   long double result(0);
   detail::convert_to_long_result(t.value(), result);
   return result;
}
template <>
inline boost::math::ntl::RR real_cast<boost::math::ntl::RR, boost::math::ntl::RR>(boost::math::ntl::RR t)
{
   return t;
}
template <>
inline unsigned real_cast<unsigned, boost::math::ntl::RR>(boost::math::ntl::RR t)
{
   unsigned result;
   detail::convert_to_long_result(t.value(), result);
   return result;
}
template <>
inline int real_cast<int, boost::math::ntl::RR>(boost::math::ntl::RR t)
{
   int result;
   detail::convert_to_long_result(t.value(), result);
   return result;
}
template <>
inline long real_cast<long, boost::math::ntl::RR>(boost::math::ntl::RR t)
{
   long result;
   detail::convert_to_long_result(t.value(), result);
   return result;
}
template <>
inline long long real_cast<long long, boost::math::ntl::RR>(boost::math::ntl::RR t)
{
   long long result;
   detail::convert_to_long_result(t.value(), result);
   return result;
}

template <>
inline boost::math::ntl::RR max_value<boost::math::ntl::RR>(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(boost::math::ntl::RR))
{
   static bool has_init = false;
   static NTL::RR val;
   if(!has_init)
   {
      val = 1;
      val.e = NTL_OVFBND-20;
      has_init = true;
   }
   return val;
}

template <>
inline boost::math::ntl::RR min_value<boost::math::ntl::RR>(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(boost::math::ntl::RR))
{
   static bool has_init = false;
   static NTL::RR val;
   if(!has_init)
   {
      val = 1;
      val.e = -NTL_OVFBND+20;
      has_init = true;
   }
   return val;
}

template <>
inline boost::math::ntl::RR log_max_value<boost::math::ntl::RR>(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(boost::math::ntl::RR))
{
   static bool has_init = false;
   static NTL::RR val;
   if(!has_init)
   {
      val = 1;
      val.e = NTL_OVFBND-20;
      val = log(val);
      has_init = true;
   }
   return val;
}

template <>
inline boost::math::ntl::RR log_min_value<boost::math::ntl::RR>(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(boost::math::ntl::RR))
{
   static bool has_init = false;
   static NTL::RR val;
   if(!has_init)
   {
      val = 1;
      val.e = -NTL_OVFBND+20;
      val = log(val);
      has_init = true;
   }
   return val;
}

template <>
inline boost::math::ntl::RR epsilon<boost::math::ntl::RR>(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(boost::math::ntl::RR))
{
   return ldexp(boost::math::ntl::RR(1), 1-boost::math::policies::digits<boost::math::ntl::RR, boost::math::policies::policy<> >());
}

} // namespace tools

//
// The number of digits precision in RR can vary with each call
// so we need to recalculate these with each call:
//
namespace constants{

template<> inline boost::math::ntl::RR pi<boost::math::ntl::RR>(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(boost::math::ntl::RR))
{
    NTL::RR result;
    ComputePi(result);
    return result;
}
template<> inline boost::math::ntl::RR e<boost::math::ntl::RR>(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(boost::math::ntl::RR))
{
    NTL::RR result;
    result = 1;
    return exp(result);
}

} // namespace constants

namespace ntl{
   //
   // These are some fairly brain-dead versions of the math
   // functions that NTL fails to provide.
   //


   //
   // Inverse trig functions:
   //
   struct asin_root
   {
      asin_root(RR const& target) : t(target){}

      boost::math::tuple<RR, RR, RR> operator()(RR const& p)
      {
         RR f0 = sin(p);
         RR f1 = cos(p);
         RR f2 = -f0;
         f0 -= t;
         return boost::math::make_tuple(f0, f1, f2);
      }
   private:
      RR t;
   };

   inline RR asin(RR z)
   {
      double r;
      conv(r, z.value());
      return boost::math::tools::halley_iterate(
         asin_root(z), 
         RR(std::asin(r)), 
         RR(-boost::math::constants::pi<RR>()/2),
         RR(boost::math::constants::pi<RR>()/2),
         NTL::RR::precision());
   }

   struct acos_root
   {
      acos_root(RR const& target) : t(target){}

      boost::math::tuple<RR, RR, RR> operator()(RR const& p)
      {
         RR f0 = cos(p);
         RR f1 = -sin(p);
         RR f2 = -f0;
         f0 -= t;
         return boost::math::make_tuple(f0, f1, f2);
      }
   private:
      RR t;
   };

   inline RR acos(RR z)
   {
      double r;
      conv(r, z.value());
      return boost::math::tools::halley_iterate(
         acos_root(z), 
         RR(std::acos(r)), 
         RR(-boost::math::constants::pi<RR>()/2),
         RR(boost::math::constants::pi<RR>()/2),
         NTL::RR::precision());
   }

   struct atan_root
   {
      atan_root(RR const& target) : t(target){}

      boost::math::tuple<RR, RR, RR> operator()(RR const& p)
      {
         RR c = cos(p);
         RR ta = tan(p);
         RR f0 = ta - t;
         RR f1 = 1 / (c * c);
         RR f2 = 2 * ta / (c * c);
         return boost::math::make_tuple(f0, f1, f2);
      }
   private:
      RR t;
   };

   inline RR atan(RR z)
   {
      double r;
      conv(r, z.value());
      return boost::math::tools::halley_iterate(
         atan_root(z), 
         RR(std::atan(r)), 
         -boost::math::constants::pi<RR>()/2,
         boost::math::constants::pi<RR>()/2,
         NTL::RR::precision());
   }

   inline RR atan2(RR y, RR x)
   {
      if(x > 0)
         return atan(y / x);
      if(x < 0)
      {
         return y < 0 ? atan(y / x) - boost::math::constants::pi<RR>() : atan(y / x) + boost::math::constants::pi<RR>();
      }
      return y < 0 ? -boost::math::constants::half_pi<RR>() : boost::math::constants::half_pi<RR>() ;
   }

   inline RR sinh(RR z)
   {
      return (expm1(z.value()) - expm1(-z.value())) / 2;
   }

   inline RR cosh(RR z)
   {
      return (exp(z) + exp(-z)) / 2;
   }

   inline RR tanh(RR z)
   {
      return sinh(z) / cosh(z);
   }

   inline RR fmod(RR x, RR y)
   {
      // This is a really crummy version of fmod, we rely on lots
      // of digits to get us out of trouble...
      RR factor = floor(x/y);
      return x - factor * y;
   }

   template <class Policy>
   inline int iround(RR const& x, const Policy& pol)
   {
      return tools::real_cast<int>(round(x, pol));
   }

   template <class Policy>
   inline long lround(RR const& x, const Policy& pol)
   {
      return tools::real_cast<long>(round(x, pol));
   }

   template <class Policy>
   inline long long llround(RR const& x, const Policy& pol)
   {
      return tools::real_cast<long long>(round(x, pol));
   }

   template <class Policy>
   inline int itrunc(RR const& x, const Policy& pol)
   {
      return tools::real_cast<int>(trunc(x, pol));
   }

   template <class Policy>
   inline long ltrunc(RR const& x, const Policy& pol)
   {
      return tools::real_cast<long>(trunc(x, pol));
   }

   template <class Policy>
   inline long long lltrunc(RR const& x, const Policy& pol)
   {
      return tools::real_cast<long long>(trunc(x, pol));
   }

} // namespace ntl

namespace detail{

template <class Policy>
ntl::RR digamma_imp(ntl::RR x, const std::integral_constant<int, 0>* , const Policy& pol)
{
   //
   // This handles reflection of negative arguments, and all our
   // error handling, then forwards to the T-specific approximation.
   //
   BOOST_MATH_STD_USING // ADL of std functions.

   ntl::RR result = 0;
   //
   // Check for negative arguments and use reflection:
   //
   if(x < 0)
   {
      // Reflect:
      x = 1 - x;
      // Argument reduction for tan:
      ntl::RR remainder = x - floor(x);
      // Shift to negative if > 0.5:
      if(remainder > 0.5)
      {
         remainder -= 1;
      }
      //
      // check for evaluation at a negative pole:
      //
      if(remainder == 0)
      {
         return policies::raise_pole_error<ntl::RR>("boost::math::digamma<%1%>(%1%)", 0, (1-x), pol);
      }
      result = constants::pi<ntl::RR>() / tan(constants::pi<ntl::RR>() * remainder);
   }
   result += big_digamma(x);
   return result;
}

} // namespace detail

} // namespace math
} // namespace boost

#endif // BOOST_MATH_REAL_CONCEPT_HPP



/* rr.hpp
hYr0imZurULZEeu0ZUXV1+UkxnIZFLyQMIZWfKLBbqOfAS/NNuy2d9J2Qv8DQR6oVb9IGF60U8Tj750dZH7ucIvHylj1JALx+dc43Vzmjx9oqkjGi6EeoZVERUW+QK4SMGTCPkg72nhNh7wLHanglr3+hese5ha5vyxqOlUpX2endwDw5ml/tVX/iY1+AQzOv1V6IGpM6hoW90V64pTXBPqrrpgdXkqhlKrEzTX6yHAThYG/HLbx049cjedGp6poXYqLf8HnkdKE+jN3csGLJsdV+p7bZZqcrT9gjrs7vKzqWpk9wUnddv+MPjicZ0JyQPRDUtzZwv9FTCoF/AresWpDIPTVj+30GciWc7tFOI1olD0BapIzzr8QzwiCm5hQkzDR9MCP5/QDEe3Qo8vFT1A3cELXbtv1EcsguxIoFaQk2GXVPTGIm5sY4aPrCxwrNZv6MlivlejcxjV+aPmEHWH2yvcbjXxZNuD3+uqmxut9nVhsda1noZpyVt+jrPiozFQWX8QmY2ishdEV7LnaHuqGGpqbJhW3APyx+KpVDFF6oYqfXtGdJgGcLNj0wA+BBMoEFt05CwkQXMbPNJsva7R1MsWGIsRXvsxLvQxX19+dfycxnga4/afrO2m7e0Sfk6HNNPVTsy1ww18RGBjX3T9nIZ7m4xfPAeA0iQnVAF1MF3OqnSgsFi96HulLpVrtTEv4jfptKeZ4wBejr9fj/WYBeFTncuvCk1To6z7rhzwWLMvkpGH8RIXltjX9JZ1wNyP+p4ev2bnLTDMtCkK3M2eZyvO+scugx14mz1Su+556kmqt9ybcXfuW2Gncjp4pD5owuLSHt2KK4emYHDifPGpnZZdICaRxNq0nn5Ik5HsJae0+F91M0T1BoW+l6eL1sSjMhTwcvSROW8BYhfwvsZYFGX7PJJlE6/H34mxI3cXJW+hC+gPNT8UL4DhG/ppjAV9klsRdoSxHHLD0wQfueJ0RIKp5kHYdlVkG9JkfMkDSLnyJ9rh+ndwtsk3HG51s5R2lvpyfSnsodZbMyCgrVBHxSjAixPk6EQ3XmtrLX3MJAQHDtafHcneZYDptemGK8I2RoqY0b8qBzETpCBVePB2XJeUMS5g784FlYGIDNBQqqWPMWtjYYCXSoYqdtrAJIDpKQ4DyrZuqv/9UHMEX2tmvDStgBlPY350wplulAPOhHhe7xWd7HnFIePBfhPDUzoHrX4vYOoYOVzEaf1dUBOGafBqQodF1aiUeJkUdTm86Ie6TQTteHlB9XgXNxPo0nwc6TuBbeEj/xoN1wbTNE/vObIi+doBrEn+GfcALERsB+Sd6Dzrx5SUYR1bv3MsxD3eY0ufrx3g+BeQUz+ANxVLIalBInnMCspzXN3dkZypVhngNORRZWCW98g/PA+W/MzxnRfV+pjij5v6hO6UHh2nXbabLIeSbElQlTg8IggSUtVNHApx0Kkx1EiGS8RK1nfFid+U5sBoMcF4px1JG5ZpgasGWD5FXBEgW5vdOkw7sa1FENRjW47o0GWraQ9fsOUtEmwRUzXfTKIb3/CyudxaA7g5qa4UbpP3A0pHhKiRRCQiGK6w82DEz66VIV0nvQxu4wYtyMBmYoBrFx9j6DnYngkEB6FgWFfdXrMZNLJ5IqhpoALEail61uaOMBdzfyuUCWONxevzCofGSb7Dgm42IURo2wWm+pnSny7z6pl+BKIdHuqOaIJCQtGUTjFSjuM63iDvT7P+waq/otvgOaWN2TYeJ+2qc2FVXUn08CTaYwclTiK07GRqzvmzyOhZXnwyI1GeoOsSbJ4WwshEWtk84mUAeAn5WNwFwopIKKXrWbzoO3tfWgvHvzp/cpj61XHntWbcB8q5pNNmshU7TmkA0DWKJqKFRZi8SC8hCzygHRaSLoLg70XmLlVrRscD14KeOUHAcatvmgIhAK3rhm1lluIgNdSTB9JuIjDiCG4XYBDMuq3WA+pVoA2bB20gWgUwoygJqO4I0hjBFUaLhzjhdHJkhMus4YYSx4M7PWoBfHe5VBYkjRcKMN5mLKj9wszn/kVA+Ws6ZwtD3H7gBE5DPIbQNN7i4Gu5+CkPURImdJvGnClJDET1GkWEHonIlFZBqwH1wlvYN6kHJsOJYu43gS7ugrKB0x8+gk0UpQV1yjDvB/XCu1vrHJafvMWJZXawAXyBlMLePElG1y4Ekti6nEqL+RtqyoauiTh5ItHmABxd/jgVtTaRA6LdAoJWcZRZz/xgz+FpwJJYzSmQEffgAn2FSmKtKYVjBmYrdZnbXkGlDpJw8cUFNQmJB8lc1S6VolfTdgmGz5ZkMLOhZoelwCusK+Degn0bXcA1bZqsagCJZuyzrEOgNHF6PiH/Wr2EG2zvzQMbIYeJk98KgmYNgs1/voHSfHkzQWk/5deUcpVHhf0m2yN5i+XpZ5uTvrGeFBC2mb6AfBlXGqcpr1Vx2/lhOTQ9U+OusoEZM5Ei8PFZPyWeDCFbLJpImG2UMaFw/UL9UVdIxP8kLQ5aAgREzyUhICLrFg4eOtQeGiBAnFlrsxyBZI0R5gowJVh5ieCUFXlyfV2YFa06/aoIj2t4tQDpbAVlKkFMs1pMEyLPrDLCgET86p0FUea1TQd+lm1+B9VCx8QJBn95cAv3vQ4DkVYcErtjHDsalONxbUWWWaRAK7U7tQsm/gCoyI7sNcOkaRCYEn8inTy5Qgm1kb7OTFEAor2ZhQss6/YkKfxqD/nnqUbjFktF96pBUCDmgWq9W4xouU/1TRYFkl4umUmJWze4BuADsL7GUbNTJ7hV4CnQ2LAI2wQYtd+4q55AMop0qximu2asfl6lXHVOFETK8LRS23QPYTQ5ddqDZHDTBZDHLJyj29IICxHiRfsrmCOYoMqP3sUyJmWQo9oKSOJ65gq5AOchIVD2fJy1ZE1YPkqHKTm8Is0g3iO3bHKN3CmO0PTuO3RRhcW6Aj5AFKIR1UIbERrjcaxasoJQh5PcdSvJxeCW8toL15YHacCSs/qFxmxwZRe0BTwvFsFZs3lGCAKdUDbambElZeA5E+BkN2bRyOeaEdQzbGE8HzavXMpsB6UuX4u8toBDJ3Hz40YGGsylWCPpnxBaAs0NiVVxiXNtqV/gsIVsl8QpN+TZhF8Q2xh6a9LGuiGSnFvOErYrKKkQBzToYDe0i2GkHqdlNZI0uyVb+CBc/iv1dxp/79iDOZ4X1jVSmbZhl6Wmw8JfMjkHyjy7QzyA39WDKD9zcEN0KRHbu3l/4tNITI9PnR14Kw3IuIFtY1v32MWKF4vo8BjtOJKgXWFGerXImxvnhLcLnJxIOK7QjQqICc+TuLvYOO74IzkC2YYl16dyjpGaLTIDzi4o8FuIi6tmg1sig5m4XZ0uzrEXfEg+IIAsLwxwUTvoFk2AASmlYfyCdQobwaX08lAfOgD9xk7TNZ6lptVGgWHblRE86SDiKYe9wOGiyvcBdsjKYX5qUi8sOE5BAYQ/V2WVHQGgRUpA4GW7uskix4QopIQeoiD0unmZIJPoExUpLNYMWwz68cPUw16+tcy5CK+hR1guUl17S1ZHfiYsnOWyE2N+Uy/D8Pf7uQdXIvv+gcexfh7A4F0/4FN+XBbwQuOwDNI4ePVemDRo9CfeAlmn6iCh6UmRChVPdP4VhpnEgOcBNzvMOmCAIuq06JvTPH3K6MqvBJEq1yRBBWyusjqUVjg4KqDWZQ6i429xpCqc/x+6j5VX8t/a5aHVqGq3SmmaLrR/dS1WTHknJSylxB0N0ptSbmmUIkMSXOY17FnUthd7++Cy+UTXJ1yYR7gBg9WVxKkXtKKS9I9Gz8ivATkRCnt6TojgLtVM0w+aW/Lkqji9QL4LDPc43d2fwowshBb/DpeW9poCPeIy9fJ2Qd5PaKdQ4z3VzrelQwUWb9HYvVvTMUYwjQMZidSvH6UUS/tn/Rmfl1xJwqDglv1uOBZa8wyUal38nqTYuLKyYvwWimxtUSXBGE3f37Bf+UWJC3C0plBV3kOCbHvWyZUV+YnohcHc4b0lsvxvNVXm/y0SpADUcs1ewR7kSOYEA6FWK3V1LJxlTeBonxAPld80hyFRh4ZFQYj7XfAHk/1td8OdHzxMYzL1Q94UF63xQovvVecvbkHd2i3jiWPEbjQFewUmLvW8QqxTdswVeDJ/r3ADE8vtlRy/GUwkLIm1xFkSJMKkwucginkLgkSng0jGLGmaCa4eg5ucdVa/6/kvZp5dQCqRt04sNx2mr1GBHrzkpVeKn7PpIpN6oibPgs8+mjNRXwmoog7wdpdyNGDWhCI4oH8M1bvCaBlJf1UzHTwjL1TFq2j43bWYzGNfTv4zukWIikzQrFJa0mdyMyHxQ5VGLOIXAImQWGVbnHfZYOWOpiGm7OXR8bfInmSI+Ir/8Nqw0zuaDbajHKlsoxeih2DjZCsYAb8rB1lRZgNKM5QYiaflto3F0HdsNyl7EP9i+aVeYGBHn/SxN3XL0U0RBmDVT+dTmuvzF/3AXl9BnmYE3+yXnqcf7qbTIdTebhiCTmMxavgZ666HpZu5o6gIlaDROauBiX0ZdJfIrm0nuRrqbcgzPC7Tjhny6BMFlZ1UaUfmBia8wMFEkjpnvFSftObcXRKkFIOL/56/MIvrEAADwJhhzP6lnVdxO0Z7+DUeGhFWWg5JCpvPt/TgN5htYTnx12gGlJRV6rCQ7jZ8v+s6RAGKmfeEwAIyAift4//QoeXJHg8QadrxwAhE+7WRM15LY1ShI+zYSZaVB1/+yu+UXKJh3P4FhA1EsKthtG6eKjtrRQwJS+XfdJ6YBAKUI6N7DCQNJxCvxsYKACBUdUnl4SUnjeqABMAEBiDIrGKsD3Ph0e71cu/3s+G71bJ5wnrRnm9q2Gh8xkfwba5PSVJPQDJLQAGAC7AGJJgZE2btF5IMSLyDoOyfGwP/5Loj/15zAaA1r52y8ibYQ338XhQXbz2bSlEkqbNAIIoX8o6BbKNkXrL3J3wIL4h6EGKIZGLVszaO9VVDAjIWoNp+sOXXmmJpxOSwk/kP4/gM0Xf2pVj6puP4nBhmUAcqYhrNzEo1ZywZSTBgerYB20MliDxtc/g+VF/yEoUyRGr5Kn3BCU+GfKf+/H1aaOGjxVm3FRDqKztgPTS3nHGNRxWEI0q5DK1yUTFl2OcQUHjbmKDarlFQHe696Yd60sms52Qc27hJTG4M0kDy9l2ZstU+TYv/CI9WBEQtnuVmeBN9DgxN5nEN5YUKti+uy60qVUicGYEC5rGlaWLKJyovXP+vVMUOuIqiH0xgiWEjXxsvg16uZ6uJ1w6nSifXLNQ85wAAOLPHTTgpf5eCokSfjQTmMjCPQUteLMjZl1kzMaK9vTrHHXWEmKgSTHruae3QMc8bWxVHm1DpJjH8mAhgtevSvmYXimRQWKdYltNu0uTamV9uB5Y6DkTQnSaaE92HKS6MBwDcJ5SGh/kzSuPM8q2v8pZUBWMC+NDvSNUlwg9s0UCqD/9q/sLqCQ+HpFDAfi8gwQenh282ktjc5ZI5MZMGHBQujBzopYpEnsS8MG+VXHQ4ozkaNX1YsSy/wEw+ArqOZu2FzGsTBrbKIMOP9xArMWrrRawqQjzKcupXEAKL1P5Krf1tcpFnm7WXD1ca2+Yg2/dCYOtrfu2DpmzAHXSfVk05aHt+o1gLN3UlYwjU9mxosCsJjCoFweQXE9wVOMBMxW4GbIG5X8rqC5eaNz8tyk8v3MFQV9yf45vg0AANmPiAZJ+BtakvNCJVhz1CXsqUc568HMwPbmK5NULtfEwgbnceL1lyNLv2biPbAuIwUsZWu9rObJonQFUe/SEHAfYQmmy7ThGUktG64c080/ZFokwUzzB2cK9j4xFIAqeEx//neHwjnfZx9JSzgUK5l82BEIu3zgxUGciWLp9RHzoYznHQ3p7Qmq2ZxHpF8JRg3tOeq4VAtsakWODJ2SOdJId5lDQM9dB/jpG3GCrLDC7S2CsAeuXrxNTN4t1xBf3cDrg1WNeXZ84qwCOMm9IJx/e+FCb80lT4TkHRMN8a/ui7o0G10WMOluV7PaISDHJXH7MOmwAxAlhzaAbAKBUZANqDtPpS7pQrVWcAeLJG3rrU8ar2idbVctCS2DFnP3p4M7bjrJKBpWFavqgtiK9ePM78c4uWoK/E8FFz29qh5nVVc57hiRQAxx3KW83ZrxiUKKaxuf0JtG2p1jE4Tbs60TIntwPnB3FxoSodzD73qXTsDWM8mkQ+IjNcwL3jAUcuxpz7IlshYlfH8lR6qDjGMpWZ702qttx7enSAeVf14VXcGT5p+IvWYYxbD9SLXKF1gyHDCHNmRWcPpuTImOhqtSEdJeqIcqnSshCyVt5Xvc7cx7WO80+yYFgRlmHNDIx0M7CKdzQbjzo3+SuDjHuQT7r4IbZB7sRyqy8NChTDP0qdGSRxp11gwinfzOt26K+vezxlPJ3PzBUwdZmB14Aos3HrEW4AAC1Pmjun5Ze+cjyZMYpWmhequiQY7lYDwhlhEU3OdZeXR+OCHPZ4/ppU+HtUeDu0AXaBz+T4k1hQ44QYj7h262A+LPO4QfBuMj3sS68/di1zPQMRUkDGx18OGz1dncM+IvZV4dAdC7iflnQZNTuk1o5Ic6FAPf8MmQkxy5UPbtReihQnAwyAghbZrq7YQZlG96EDnIUZUWyJJ55Lu9eF9SS1nMitwQBK0KdyWbdxWozwc91I0RBpRnt33ohNWOQOPLIBQwFXfZET6j85+vUVCL+GQH9GyEsOVySUj/flOQOF8/Ka959TQQoVGwbK2AWm4Vyz18CGXrBXVUuMe4OEEuDvEhEgmL+1uffHf+fnpfolOUwe2Yj2eW4fSquX2vHFaEESlcKo0xmH54nGMBQwJtZEizVUdNJPO28Y4bUdetweI/tVgA4oGmSpJuTHBdrdyRqMHnnQj6YT0++CoI4ybKClWZGwg4bvC1lYAvP0qruzdAKCgfLw1eSj7flTIV5aZhpdUOtKKpWQBLVn/8NA3LRb16vNI+dyXoM/AoooJPjhOyJ3RspsPktxKOZO/IJ4jL6nk6AmzZujRHYd3gGC1SlahQc39ESm8waAS3pQ4QHg+sWsWbBah2XEaRV2QcH6RNluZrKg3Sup2+7py4jmJEwWUGul7W23hMvp6JLUR5hOPByNheuCZ1IcTXxDRexxPsn5wxqL7HtGl+xvdt7omf4BjcA2ee+5ICJt+sjpnFWQ33G+2cOeRvpG5N9jLnCdFjOcTNzEgVcBFvpSV/nDcu1HsaSQYyOiXpCFCQAbS1Jqpg/sD+AtLAwL4//gpAtAYAqT/6Sw9aAa7AlWY4haOHg8ir8MkzFfmuFd4zXkUa4KTpuuDeSxs8jNTsW3uTSbNbpe2Iwp4CoNmKJkxTCLJgzSF9EZxyidswyJdkv53cQIHveSIvqwxGF5kxY+Pe+u7CIBIbz/9BQBaYqCMcYGhYqjLfQPcph13dAcp4ELus1YyxqPA1vUFNhNgbXPnr4KNuwAOsA2+M2vYfu/uyn4KCIdocgsUtj5GEx6MaQywkgD7lZ/g+lGDu5weTOVJSULJgs6l5tv+qajHwSTJH3QRHXyMquyDeKnOQJKPsGfsDyzw4s8/PdMyNUME
*/