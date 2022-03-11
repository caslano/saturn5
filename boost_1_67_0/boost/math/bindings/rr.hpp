//  Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_NTL_RR_HPP
#define BOOST_MATH_NTL_RR_HPP

#include <boost/config.hpp>
#include <boost/limits.hpp>
#include <boost/math/tools/real_cast.hpp>
#include <boost/math/tools/precision.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/tools/roots.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/math/bindings/detail/big_digamma.hpp>
#include <boost/math/bindings/detail/big_lanczos.hpp>

#include <ostream>
#include <istream>
#include <boost/config/no_tr1/cmath.hpp>
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
#ifndef BOOST_NO_INTRINSIC_WCHAR_T
   RR(wchar_t c)
   {
      m_value = c;
   }
#endif
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
#ifdef BOOST_HAS_LONG_LONG
   RR(boost::ulong_long_type c)
   {
      assign_large_int(c);
   }
   RR(boost::long_long_type c)
   {
      assign_large_int(c);
   }
#endif
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
#ifndef BOOST_NO_INTRINSIC_WCHAR_T
   RR& operator=(wchar_t c) { m_value = c; return *this; }
#endif
   RR& operator=(short c) { m_value = c; return *this; }
   RR& operator=(unsigned short c) { m_value = c; return *this; }
   RR& operator=(int c) { assign_large_int(c); return *this; }
   RR& operator=(unsigned int c) { assign_large_int(c); return *this; }
   RR& operator=(long c) { assign_large_int(c); return *this; }
   RR& operator=(unsigned long c) { assign_large_int(c); return *this; }
#ifdef BOOST_HAS_LONG_LONG
   RR& operator=(boost::long_long_type c) { assign_large_int(c); return *this; }
   RR& operator=(boost::ulong_long_type c) { assign_large_int(c); return *this; }
#endif
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
#ifdef BOOST_MSVC
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
#ifdef BOOST_MSVC
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
      BOOST_ASSERT(r < 1);
      BOOST_ASSERT(r >= 0.5);
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
ntl::RR digamma_imp(ntl::RR x, const boost::integral_constant<int, 0>* , const Policy& pol)
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
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
*/