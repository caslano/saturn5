//  Copyright John Maddock 2008.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Wrapper that works with mpfr_class defined in gmpfrxx.h
// See http://math.berkeley.edu/~wilken/code/gmpfrxx/
// Also requires the gmp and mpfr libraries.
//

#ifndef BOOST_MATH_E_FLOAT_BINDINGS_HPP
#define BOOST_MATH_E_FLOAT_BINDINGS_HPP

#include <boost/config.hpp>


#include <e_float/e_float.h>
#include <functions/functions.h>

#include <boost/math/tools/precision.hpp>
#include <boost/math/tools/real_cast.hpp>
#include <boost/math/policies/policy.hpp>
#include <boost/math/distributions/fwd.hpp>
#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/math/bindings/detail/big_digamma.hpp>
#include <boost/math/bindings/detail/big_lanczos.hpp>
#include <boost/lexical_cast.hpp>


namespace boost{ namespace math{ namespace ef{

class e_float
{
public:
   // Constructors:
   e_float() {}
   e_float(const ::e_float& c) : m_value(c){}
   e_float(char c)
   {
      m_value = ::e_float(c);
   }
#ifndef BOOST_NO_INTRINSIC_WCHAR_T
   e_float(wchar_t c)
   {
      m_value = ::e_float(c);
   }
#endif
   e_float(unsigned char c)
   {
      m_value = ::e_float(c);
   }
   e_float(signed char c)
   {
      m_value = ::e_float(c);
   }
   e_float(unsigned short c)
   {
      m_value = ::e_float(c);
   }
   e_float(short c)
   {
      m_value = ::e_float(c);
   }
   e_float(unsigned int c)
   {
      m_value = ::e_float(c);
   }
   e_float(int c)
   {
      m_value = ::e_float(c);
   }
   e_float(unsigned long c)
   {
      m_value = ::e_float((UINT64)c);
   }
   e_float(long c)
   {
      m_value = ::e_float((INT64)c);
   }
#ifdef BOOST_HAS_LONG_LONG
   e_float(boost::ulong_long_type c)
   {
      m_value = ::e_float(c);
   }
   e_float(boost::long_long_type c)
   {
      m_value = ::e_float(c);
   }
#endif
   e_float(float c)
   {
      assign_large_real(c);
   }
   e_float(double c)
   {
      assign_large_real(c);
   }
   e_float(long double c)
   {
      assign_large_real(c);
   }

   // Assignment:
   e_float& operator=(char c) { m_value = ::e_float(c); return *this; }
   e_float& operator=(unsigned char c) { m_value = ::e_float(c); return *this; }
   e_float& operator=(signed char c) { m_value = ::e_float(c); return *this; }
#ifndef BOOST_NO_INTRINSIC_WCHAR_T
   e_float& operator=(wchar_t c) { m_value = ::e_float(c); return *this; }
#endif
   e_float& operator=(short c) { m_value = ::e_float(c); return *this; }
   e_float& operator=(unsigned short c) { m_value = ::e_float(c); return *this; }
   e_float& operator=(int c) { m_value = ::e_float(c); return *this; }
   e_float& operator=(unsigned int c) { m_value = ::e_float(c); return *this; }
   e_float& operator=(long c) { m_value = ::e_float((INT64)c); return *this; }
   e_float& operator=(unsigned long c) { m_value = ::e_float((UINT64)c); return *this; }
#ifdef BOOST_HAS_LONG_LONG
   e_float& operator=(boost::long_long_type c) { m_value = ::e_float(c); return *this; }
   e_float& operator=(boost::ulong_long_type c) { m_value = ::e_float(c); return *this; }
#endif
   e_float& operator=(float c) { assign_large_real(c); return *this; }
   e_float& operator=(double c) { assign_large_real(c); return *this; }
   e_float& operator=(long double c) { assign_large_real(c); return *this; }

   // Access:
   ::e_float& value(){ return m_value; }
   ::e_float const& value()const{ return m_value; }

   // Member arithmetic:
   e_float& operator+=(const e_float& other)
   { m_value += other.value(); return *this; }
   e_float& operator-=(const e_float& other)
   { m_value -= other.value(); return *this; }
   e_float& operator*=(const e_float& other)
   { m_value *= other.value(); return *this; }
   e_float& operator/=(const e_float& other)
   { m_value /= other.value(); return *this; }
   e_float operator-()const
   { return -m_value; }
   e_float const& operator+()const
   { return *this; }

private:
   ::e_float m_value;

   template <class V>
   void assign_large_real(const V& a)
   {
      using std::frexp;
      using std::ldexp;
      using std::floor;
      if (a == 0) {
         m_value = ::ef::zero();
         return;
      }

      if (a == 1) {
         m_value = ::ef::one();
         return;
      }

      if ((boost::math::isinf)(a))
      {
         m_value = a > 0 ? m_value.my_value_inf() : -m_value.my_value_inf();
         return;
      }
      if((boost::math::isnan)(a))
      {
         m_value = m_value.my_value_nan();
         return;
      }

      int e;
      long double f, term;
      ::e_float t;
      m_value = ::ef::zero();

      f = frexp(a, &e);

      ::e_float shift = ::ef::pow2(30);

      while(f)
      {
         // extract 30 bits from f:
         f = ldexp(f, 30);
         term = floor(f);
         e -= 30;
         m_value *= shift;
         m_value += ::e_float(static_cast<INT64>(term));
         f -= term;
      }
      m_value *= ::ef::pow2(e);
   }
};


// Non-member arithmetic:
inline e_float operator+(const e_float& a, const e_float& b)
{
   e_float result(a);
   result += b;
   return result;
}
inline e_float operator-(const e_float& a, const e_float& b)
{
   e_float result(a);
   result -= b;
   return result;
}
inline e_float operator*(const e_float& a, const e_float& b)
{
   e_float result(a);
   result *= b;
   return result;
}
inline e_float operator/(const e_float& a, const e_float& b)
{
   e_float result(a);
   result /= b;
   return result;
}

// Comparison:
inline bool operator == (const e_float& a, const e_float& b)
{ return a.value() == b.value() ? true : false; }
inline bool operator != (const e_float& a, const e_float& b)
{ return a.value() != b.value() ? true : false;}
inline bool operator < (const e_float& a, const e_float& b)
{ return a.value() < b.value() ? true : false; }
inline bool operator <= (const e_float& a, const e_float& b)
{ return a.value() <= b.value() ? true : false; }
inline bool operator > (const e_float& a, const e_float& b)
{ return a.value() > b.value() ? true : false; }
inline bool operator >= (const e_float& a, const e_float& b)
{ return a.value() >= b.value() ? true : false; }

std::istream& operator >> (std::istream& is, e_float& f)
{
   return is >> f.value();
}

std::ostream& operator << (std::ostream& os, const e_float& f)
{
   return os << f.value();
}

inline e_float fabs(const e_float& v)
{
   return ::ef::fabs(v.value());
}

inline e_float abs(const e_float& v)
{
   return ::ef::fabs(v.value());
}

inline e_float floor(const e_float& v)
{
   return ::ef::floor(v.value());
}

inline e_float ceil(const e_float& v)
{
   return ::ef::ceil(v.value());
}

inline e_float pow(const e_float& v, const e_float& w)
{
   return ::ef::pow(v.value(), w.value());
}

inline e_float pow(const e_float& v, int i)
{
   return ::ef::pow(v.value(), ::e_float(i));
}

inline e_float exp(const e_float& v)
{
   return ::ef::exp(v.value());
}

inline e_float log(const e_float& v)
{
   return ::ef::log(v.value());
}

inline e_float sqrt(const e_float& v)
{
   return ::ef::sqrt(v.value());
}

inline e_float sin(const e_float& v)
{
   return ::ef::sin(v.value());
}

inline e_float cos(const e_float& v)
{
   return ::ef::cos(v.value());
}

inline e_float tan(const e_float& v)
{
   return ::ef::tan(v.value());
}

inline e_float acos(const e_float& v)
{
   return ::ef::acos(v.value());
}

inline e_float asin(const e_float& v)
{
   return ::ef::asin(v.value());
}

inline e_float atan(const e_float& v)
{
   return ::ef::atan(v.value());
}

inline e_float atan2(const e_float& v, const e_float& u)
{
   return ::ef::atan2(v.value(), u.value());
}

inline e_float ldexp(const e_float& v, int e)
{
   return v.value() * ::ef::pow2(e);
}

inline e_float frexp(const e_float& v, int* expon)
{
   double d;
   INT64 i;
   v.value().extract_parts(d, i);
   *expon = static_cast<int>(i);
   return v.value() * ::ef::pow2(-i);
}

inline e_float sinh (const e_float& x)
{
   return ::ef::sinh(x.value());
}

inline e_float cosh (const e_float& x)
{
   return ::ef::cosh(x.value());
}

inline e_float tanh (const e_float& x)
{
   return ::ef::tanh(x.value());
}

inline e_float asinh (const e_float& x)
{
   return ::ef::asinh(x.value());
}

inline e_float acosh (const e_float& x)
{
   return ::ef::acosh(x.value());
}

inline e_float atanh (const e_float& x)
{
   return ::ef::atanh(x.value());
}

e_float fmod(const e_float& v1, const e_float& v2)
{
   e_float n;
   if(v1 < 0)
      n = ceil(v1 / v2);
   else
      n = floor(v1 / v2);
   return v1 - n * v2;
}

} namespace detail{

template <>
inline int fpclassify_imp< boost::math::ef::e_float> BOOST_NO_MACRO_EXPAND(boost::math::ef::e_float x, const generic_tag<true>&)
{
   if(x.value().isnan())
      return FP_NAN;
   if(x.value().isinf())
      return FP_INFINITE;
   if(x == 0)
      return FP_ZERO;
   return FP_NORMAL;
}

} namespace ef{

template <class Policy>
inline int itrunc(const e_float& v, const Policy& pol)
{
   BOOST_MATH_STD_USING
   e_float r = boost::math::trunc(v, pol);
   if(fabs(r) > (std::numeric_limits<int>::max)())
      return static_cast<int>(policies::raise_rounding_error("boost::math::itrunc<%1%>(%1%)", 0, 0, v, pol));
   return static_cast<int>(r.value().extract_int64());
}

template <class Policy>
inline long ltrunc(const e_float& v, const Policy& pol)
{
   BOOST_MATH_STD_USING
   e_float r = boost::math::trunc(v, pol);
   if(fabs(r) > (std::numeric_limits<long>::max)())
      return static_cast<long>(policies::raise_rounding_error("boost::math::ltrunc<%1%>(%1%)", 0, 0L, v, pol));
   return static_cast<long>(r.value().extract_int64());
}

#ifdef BOOST_HAS_LONG_LONG
template <class Policy>
inline boost::long_long_type lltrunc(const e_float& v, const Policy& pol)
{
   BOOST_MATH_STD_USING
   e_float r = boost::math::trunc(v, pol);
   if(fabs(r) > (std::numeric_limits<boost::long_long_type>::max)())
      return static_cast<boost::long_long_type>(policies::raise_rounding_error("boost::math::lltrunc<%1%>(%1%)", 0, v, 0LL, pol).value().extract_int64());
   return static_cast<boost::long_long_type>(r.value().extract_int64());
}
#endif

template <class Policy>
inline int iround(const e_float& v, const Policy& pol)
{
   BOOST_MATH_STD_USING
   e_float r = boost::math::round(v, pol);
   if(fabs(r) > (std::numeric_limits<int>::max)())
      return static_cast<int>(policies::raise_rounding_error("boost::math::iround<%1%>(%1%)", 0, v, 0, pol).value().extract_int64());
   return static_cast<int>(r.value().extract_int64());
}

template <class Policy>
inline long lround(const e_float& v, const Policy& pol)
{
   BOOST_MATH_STD_USING
   e_float r = boost::math::round(v, pol);
   if(fabs(r) > (std::numeric_limits<long>::max)())
      return static_cast<long int>(policies::raise_rounding_error("boost::math::lround<%1%>(%1%)", 0, v, 0L, pol).value().extract_int64());
   return static_cast<long int>(r.value().extract_int64());
}

#ifdef BOOST_HAS_LONG_LONG
template <class Policy>
inline boost::long_long_type llround(const e_float& v, const Policy& pol)
{
   BOOST_MATH_STD_USING
   e_float r = boost::math::round(v, pol);
   if(fabs(r) > (std::numeric_limits<boost::long_long_type>::max)())
      return static_cast<boost::long_long_type>(policies::raise_rounding_error("boost::math::llround<%1%>(%1%)", 0, v, 0LL, pol).value().extract_int64());
   return static_cast<boost::long_long_type>(r.value().extract_int64());
}
#endif

}}}

namespace std{

   template<>
   class numeric_limits< ::boost::math::ef::e_float> : public numeric_limits< ::e_float>
   {
   public:
      static const ::boost::math::ef::e_float (min) (void)
      {
         return (numeric_limits< ::e_float>::min)();
      }
      static const ::boost::math::ef::e_float (max) (void)
      {
         return (numeric_limits< ::e_float>::max)();
      }
      static const ::boost::math::ef::e_float epsilon (void)
      {
         return (numeric_limits< ::e_float>::epsilon)();
      }
      static const ::boost::math::ef::e_float round_error(void)
      {
         return (numeric_limits< ::e_float>::round_error)();
      }
      static const ::boost::math::ef::e_float infinity (void)
      {
         return (numeric_limits< ::e_float>::infinity)();
      }
      static const ::boost::math::ef::e_float quiet_NaN (void)
      {
         return (numeric_limits< ::e_float>::quiet_NaN)();
      }
      //
      // e_float's supplied digits member is wrong 
      // - it should be same the same as digits 10
      // - given that radix is 10.
      //
      static const int digits = digits10;
   };

} // namespace std

namespace boost{ namespace math{

namespace policies{

template <class Policy>
struct precision< ::boost::math::ef::e_float, Policy>
{
   typedef typename Policy::precision_type precision_type;
   typedef digits2<((::std::numeric_limits< ::boost::math::ef::e_float>::digits10 + 1) * 1000L) / 301L> digits_2;
   typedef typename mpl::if_c<
      ((digits_2::value <= precision_type::value) 
      || (Policy::precision_type::value <= 0)),
      // Default case, full precision for RealType:
      digits_2,
      // User customised precision:
      precision_type
   >::type type;
};

}

namespace tools{

template <>
inline int digits< ::boost::math::ef::e_float>(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC( ::boost::math::ef::e_float))
{
   return ((::std::numeric_limits< ::boost::math::ef::e_float>::digits10 + 1) * 1000L) / 301L;
}

template <>
inline  ::boost::math::ef::e_float root_epsilon< ::boost::math::ef::e_float>()
{
   return detail::root_epsilon_imp(static_cast< ::boost::math::ef::e_float const*>(0), boost::integral_constant<int, 0>());
}

template <>
inline  ::boost::math::ef::e_float forth_root_epsilon< ::boost::math::ef::e_float>()
{
   return detail::forth_root_epsilon_imp(static_cast< ::boost::math::ef::e_float const*>(0), boost::integral_constant<int, 0>());
}

}

namespace lanczos{

template<class Policy>
struct lanczos<boost::math::ef::e_float, Policy>
{
   typedef typename mpl::if_c<
      std::numeric_limits< ::e_float>::digits10 < 22,
      lanczos13UDT,
      typename mpl::if_c<
         std::numeric_limits< ::e_float>::digits10 < 36,
         lanczos22UDT,
         typename mpl::if_c<
            std::numeric_limits< ::e_float>::digits10 < 50,
            lanczos31UDT,
            typename mpl::if_c<
               std::numeric_limits< ::e_float>::digits10 < 110,
               lanczos61UDT,
               undefined_lanczos
            >::type
         >::type
      >::type
   >::type type;
};

} // namespace lanczos

template <class Policy>
inline boost::math::ef::e_float skewness(const extreme_value_distribution<boost::math::ef::e_float, Policy>& /*dist*/)
{
   //
   // This is 12 * sqrt(6) * zeta(3) / pi^3:
   // See http://mathworld.wolfram.com/ExtremeValueDistribution.html
   //
   return boost::lexical_cast<boost::math::ef::e_float>("1.1395470994046486574927930193898461120875997958366");
}

template <class Policy>
inline boost::math::ef::e_float skewness(const rayleigh_distribution<boost::math::ef::e_float, Policy>& /*dist*/)
{
  // using namespace boost::math::constants;
  return boost::lexical_cast<boost::math::ef::e_float>("0.63111065781893713819189935154422777984404221106391");
  // Computed using NTL at 150 bit, about 50 decimal digits.
  // return 2 * root_pi<RealType>() * pi_minus_three<RealType>() / pow23_four_minus_pi<RealType>();
}

template <class Policy>
inline boost::math::ef::e_float kurtosis(const rayleigh_distribution<boost::math::ef::e_float, Policy>& /*dist*/)
{
  // using namespace boost::math::constants;
  return boost::lexical_cast<boost::math::ef::e_float>("3.2450893006876380628486604106197544154170667057995");
  // Computed using NTL at 150 bit, about 50 decimal digits.
  // return 3 - (6 * pi<RealType>() * pi<RealType>() - 24 * pi<RealType>() + 16) /
  // (four_minus_pi<RealType>() * four_minus_pi<RealType>());
}

template <class Policy>
inline boost::math::ef::e_float kurtosis_excess(const rayleigh_distribution<boost::math::ef::e_float, Policy>& /*dist*/)
{
  //using namespace boost::math::constants;
  // Computed using NTL at 150 bit, about 50 decimal digits.
  return boost::lexical_cast<boost::math::ef::e_float>("0.2450893006876380628486604106197544154170667057995");
  // return -(6 * pi<RealType>() * pi<RealType>() - 24 * pi<RealType>() + 16) /
  //   (four_minus_pi<RealType>() * four_minus_pi<RealType>());
} // kurtosis

namespace detail{

//
// Version of Digamma accurate to ~100 decimal digits.
//
template <class Policy>
boost::math::ef::e_float digamma_imp(boost::math::ef::e_float x, const boost::integral_constant<int, 0>* , const Policy& pol)
{
   //
   // This handles reflection of negative arguments, and all our
   // eboost::math::ef::e_floator handling, then forwards to the T-specific approximation.
   //
   BOOST_MATH_STD_USING // ADL of std functions.

   boost::math::ef::e_float result = 0;
   //
   // Check for negative arguments and use reflection:
   //
   if(x < 0)
   {
      // Reflect:
      x = 1 - x;
      // Argument reduction for tan:
      boost::math::ef::e_float remainder = x - floor(x);
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
         return policies::raise_pole_error<boost::math::ef::e_float>("boost::math::digamma<%1%>(%1%)", 0, (1-x), pol);
      }
      result = constants::pi<boost::math::ef::e_float>() / tan(constants::pi<boost::math::ef::e_float>() * remainder);
   }
   result += big_digamma(x);
   return result;
}
boost::math::ef::e_float bessel_i0(boost::math::ef::e_float x)
{
    static const boost::math::ef::e_float P1[] = {
        boost::lexical_cast<boost::math::ef::e_float>("-2.2335582639474375249e+15"),
        boost::lexical_cast<boost::math::ef::e_float>("-5.5050369673018427753e+14"),
        boost::lexical_cast<boost::math::ef::e_float>("-3.2940087627407749166e+13"),
        boost::lexical_cast<boost::math::ef::e_float>("-8.4925101247114157499e+11"),
        boost::lexical_cast<boost::math::ef::e_float>("-1.1912746104985237192e+10"),
        boost::lexical_cast<boost::math::ef::e_float>("-1.0313066708737980747e+08"),
        boost::lexical_cast<boost::math::ef::e_float>("-5.9545626019847898221e+05"),
        boost::lexical_cast<boost::math::ef::e_float>("-2.4125195876041896775e+03"),
        boost::lexical_cast<boost::math::ef::e_float>("-7.0935347449210549190e+00"),
        boost::lexical_cast<boost::math::ef::e_float>("-1.5453977791786851041e-02"),
        boost::lexical_cast<boost::math::ef::e_float>("-2.5172644670688975051e-05"),
        boost::lexical_cast<boost::math::ef::e_float>("-3.0517226450451067446e-08"),
        boost::lexical_cast<boost::math::ef::e_float>("-2.6843448573468483278e-11"),
        boost::lexical_cast<boost::math::ef::e_float>("-1.5982226675653184646e-14"),
        boost::lexical_cast<boost::math::ef::e_float>("-5.2487866627945699800e-18"),
    };
    static const boost::math::ef::e_float Q1[] = {
        boost::lexical_cast<boost::math::ef::e_float>("-2.2335582639474375245e+15"),
        boost::lexical_cast<boost::math::ef::e_float>("7.8858692566751002988e+12"),
        boost::lexical_cast<boost::math::ef::e_float>("-1.2207067397808979846e+10"),
        boost::lexical_cast<boost::math::ef::e_float>("1.0377081058062166144e+07"),
        boost::lexical_cast<boost::math::ef::e_float>("-4.8527560179962773045e+03"),
        boost::lexical_cast<boost::math::ef::e_float>("1.0"),
    };
    static const boost::math::ef::e_float P2[] = {
        boost::lexical_cast<boost::math::ef::e_float>("-2.2210262233306573296e-04"),
        boost::lexical_cast<boost::math::ef::e_float>("1.3067392038106924055e-02"),
        boost::lexical_cast<boost::math::ef::e_float>("-4.4700805721174453923e-01"),
        boost::lexical_cast<boost::math::ef::e_float>("5.5674518371240761397e+00"),
        boost::lexical_cast<boost::math::ef::e_float>("-2.3517945679239481621e+01"),
        boost::lexical_cast<boost::math::ef::e_float>("3.1611322818701131207e+01"),
        boost::lexical_cast<boost::math::ef::e_float>("-9.6090021968656180000e+00"),
    };
    static const boost::math::ef::e_float Q2[] = {
        boost::lexical_cast<boost::math::ef::e_float>("-5.5194330231005480228e-04"),
        boost::lexical_cast<boost::math::ef::e_float>("3.2547697594819615062e-02"),
        boost::lexical_cast<boost::math::ef::e_float>("-1.1151759188741312645e+00"),
        boost::lexical_cast<boost::math::ef::e_float>("1.3982595353892851542e+01"),
        boost::lexical_cast<boost::math::ef::e_float>("-6.0228002066743340583e+01"),
        boost::lexical_cast<boost::math::ef::e_float>("8.5539563258012929600e+01"),
        boost::lexical_cast<boost::math::ef::e_float>("-3.1446690275135491500e+01"),
        boost::lexical_cast<boost::math::ef::e_float>("1.0"),
    };
    boost::math::ef::e_float value, factor, r;

    BOOST_MATH_STD_USING
    using namespace boost::math::tools;

    if (x < 0)
    {
        x = -x;                         // even function
    }
    if (x == 0)
    {
        return static_cast<boost::math::ef::e_float>(1);
    }
    if (x <= 15)                        // x in (0, 15]
    {
        boost::math::ef::e_float y = x * x;
        value = evaluate_polynomial(P1, y) / evaluate_polynomial(Q1, y);
    }
    else                                // x in (15, \infty)
    {
        boost::math::ef::e_float y = 1 / x - boost::math::ef::e_float(1) / 15;
        r = evaluate_polynomial(P2, y) / evaluate_polynomial(Q2, y);
        factor = exp(x) / sqrt(x);
        value = factor * r;
    }

    return value;
}

boost::math::ef::e_float bessel_i1(boost::math::ef::e_float x)
{
    static const boost::math::ef::e_float P1[] = {
        lexical_cast<boost::math::ef::e_float>("-1.4577180278143463643e+15"),
        lexical_cast<boost::math::ef::e_float>("-1.7732037840791591320e+14"),
        lexical_cast<boost::math::ef::e_float>("-6.9876779648010090070e+12"),
        lexical_cast<boost::math::ef::e_float>("-1.3357437682275493024e+11"),
        lexical_cast<boost::math::ef::e_float>("-1.4828267606612366099e+09"),
        lexical_cast<boost::math::ef::e_float>("-1.0588550724769347106e+07"),
        lexical_cast<boost::math::ef::e_float>("-5.1894091982308017540e+04"),
        lexical_cast<boost::math::ef::e_float>("-1.8225946631657315931e+02"),
        lexical_cast<boost::math::ef::e_float>("-4.7207090827310162436e-01"),
        lexical_cast<boost::math::ef::e_float>("-9.1746443287817501309e-04"),
        lexical_cast<boost::math::ef::e_float>("-1.3466829827635152875e-06"),
        lexical_cast<boost::math::ef::e_float>("-1.4831904935994647675e-09"),
        lexical_cast<boost::math::ef::e_float>("-1.1928788903603238754e-12"),
        lexical_cast<boost::math::ef::e_float>("-6.5245515583151902910e-16"),
        lexical_cast<boost::math::ef::e_float>("-1.9705291802535139930e-19"),
    };
    static const boost::math::ef::e_float Q1[] = {
        lexical_cast<boost::math::ef::e_float>("-2.9154360556286927285e+15"),
        lexical_cast<boost::math::ef::e_float>("9.7887501377547640438e+12"),
        lexical_cast<boost::math::ef::e_float>("-1.4386907088588283434e+10"),
        lexical_cast<boost::math::ef::e_float>("1.1594225856856884006e+07"),
        lexical_cast<boost::math::ef::e_float>("-5.1326864679904189920e+03"),
        lexical_cast<boost::math::ef::e_float>("1.0"),
    };
    static const boost::math::ef::e_float P2[] = {
        lexical_cast<boost::math::ef::e_float>("1.4582087408985668208e-05"),
        lexical_cast<boost::math::ef::e_float>("-8.9359825138577646443e-04"),
        lexical_cast<boost::math::ef::e_float>("2.9204895411257790122e-02"),
        lexical_cast<boost::math::ef::e_float>("-3.4198728018058047439e-01"),
        lexical_cast<boost::math::ef::e_float>("1.3960118277609544334e+00"),
        lexical_cast<boost::math::ef::e_float>("-1.9746376087200685843e+00"),
        lexical_cast<boost::math::ef::e_float>("8.5591872901933459000e-01"),
        lexical_cast<boost::math::ef::e_float>("-6.0437159056137599999e-02"),
    };
    static const boost::math::ef::e_float Q2[] = {
        lexical_cast<boost::math::ef::e_float>("3.7510433111922824643e-05"),
        lexical_cast<boost::math::ef::e_float>("-2.2835624489492512649e-03"),
        lexical_cast<boost::math::ef::e_float>("7.4212010813186530069e-02"),
        lexical_cast<boost::math::ef::e_float>("-8.5017476463217924408e-01"),
        lexical_cast<boost::math::ef::e_float>("3.2593714889036996297e+00"),
        lexical_cast<boost::math::ef::e_float>("-3.8806586721556593450e+00"),
        lexical_cast<boost::math::ef::e_float>("1.0"),
    };
    boost::math::ef::e_float value, factor, r, w;

    BOOST_MATH_STD_USING
    using namespace boost::math::tools;

    w = abs(x);
    if (x == 0)
    {
        return static_cast<boost::math::ef::e_float>(0);
    }
    if (w <= 15)                        // w in (0, 15]
    {
        boost::math::ef::e_float y = x * x;
        r = evaluate_polynomial(P1, y) / evaluate_polynomial(Q1, y);
        factor = w;
        value = factor * r;
    }
    else                                // w in (15, \infty)
    {
        boost::math::ef::e_float y = 1 / w - boost::math::ef::e_float(1) / 15;
        r = evaluate_polynomial(P2, y) / evaluate_polynomial(Q2, y);
        factor = exp(w) / sqrt(w);
        value = factor * r;
    }

    if (x < 0)
    {
        value *= -value;                 // odd function
    }
    return value;
}

} // namespace detail

}}
#endif // BOOST_MATH_E_FLOAT_BINDINGS_HPP


/* e_float.hpp
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
*/