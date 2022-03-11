///////////////////////////////////////////////////////////////
//  Copyright 2013 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MP_FLOAT128_HPP
#define BOOST_MP_FLOAT128_HPP

#include <boost/config.hpp>
#include <boost/scoped_array.hpp>
#include <boost/functional/hash.hpp>
#include <boost/multiprecision/number.hpp>

#if defined(BOOST_INTEL) && !defined(BOOST_MP_USE_FLOAT128) && !defined(BOOST_MP_USE_QUAD)
#if defined(BOOST_INTEL_CXX_VERSION) && (BOOST_INTEL_CXX_VERSION >= 1310) && defined(__GNUC__)
#if (__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 6))
#define BOOST_MP_USE_FLOAT128
#endif
#endif

#ifndef BOOST_MP_USE_FLOAT128
#define BOOST_MP_USE_QUAD
#endif
#endif

#if defined(__GNUC__) && !defined(BOOST_MP_USE_FLOAT128) && !defined(BOOST_MP_USE_QUAD)
#define BOOST_MP_USE_FLOAT128
#endif

#if !defined(BOOST_MP_USE_FLOAT128) && !defined(BOOST_MP_USE_QUAD)
#error "Sorry compiler is neither GCC, not Intel, don't know how to configure this header."
#endif
#if defined(BOOST_MP_USE_FLOAT128) && defined(BOOST_MP_USE_QUAD)
#error "Oh dear, both BOOST_MP_USE_FLOAT128 and BOOST_MP_USE_QUAD are defined, which one should I be using?"
#endif

#if defined(BOOST_MP_USE_FLOAT128)

extern "C" {
#include <quadmath.h>
}

typedef __float128 float128_type;

#elif defined(BOOST_MP_USE_QUAD)

#include <boost/multiprecision/detail/float_string_cvt.hpp>

typedef _Quad float128_type;

extern "C" {
_Quad __ldexpq(_Quad, int);
_Quad __frexpq(_Quad, int*);
_Quad __fabsq(_Quad);
_Quad __floorq(_Quad);
_Quad __ceilq(_Quad);
_Quad __sqrtq(_Quad);
_Quad __truncq(_Quad);
_Quad __expq(_Quad);
_Quad __powq(_Quad, _Quad);
_Quad __logq(_Quad);
_Quad __log10q(_Quad);
_Quad __sinq(_Quad);
_Quad __cosq(_Quad);
_Quad __tanq(_Quad);
_Quad __asinq(_Quad);
_Quad __acosq(_Quad);
_Quad __atanq(_Quad);
_Quad __sinhq(_Quad);
_Quad __coshq(_Quad);
_Quad __tanhq(_Quad);
_Quad __fmodq(_Quad, _Quad);
_Quad __atan2q(_Quad, _Quad);

#define ldexpq __ldexpq
#define frexpq __frexpq
#define fabsq __fabsq
#define floorq __floorq
#define ceilq __ceilq
#define sqrtq __sqrtq
#define truncq __truncq
#define expq __expq
#define powq __powq
#define logq __logq
#define log10q __log10q
#define sinq __sinq
#define cosq __cosq
#define tanq __tanq
#define asinq __asinq
#define acosq __acosq
#define atanq __atanq
#define sinhq __sinhq
#define coshq __coshq
#define tanhq __tanhq
#define fmodq __fmodq
#define atan2q __atan2q
}

inline _Quad isnanq(_Quad v)
{
   return v != v;
}
inline _Quad isinfq(_Quad v)
{
   return __fabsq(v) > 1.18973149535723176508575932662800702e4932Q;
}

#endif

namespace boost {
namespace multiprecision {

#ifndef BOOST_MP_BITS_OF_FLOAT128_DEFINED

namespace detail {

template <>
struct bits_of<float128_type>
{
   static const unsigned value = 113;
};

}

#endif

namespace backends {

struct float128_backend;

}

using backends::float128_backend;

template <>
struct number_category<backends::float128_backend> : public mpl::int_<number_kind_floating_point>
{};
#if defined(BOOST_MP_USE_QUAD)
template <>
struct number_category<float128_type> : public mpl::int_<number_kind_floating_point>
{};
#endif

typedef number<float128_backend, et_off> float128;

#ifndef BOOST_NO_CXX11_CONSTEXPR

namespace quad_constants {
constexpr __float128 quad_min = static_cast<__float128>(1) * static_cast<__float128>(DBL_MIN) * static_cast<__float128>(DBL_MIN) * static_cast<__float128>(DBL_MIN) * static_cast<__float128>(DBL_MIN) * static_cast<__float128>(DBL_MIN) * static_cast<__float128>(DBL_MIN) * static_cast<__float128>(DBL_MIN) * static_cast<__float128>(DBL_MIN) * static_cast<__float128>(DBL_MIN) * static_cast<__float128>(DBL_MIN) * static_cast<__float128>(DBL_MIN) * static_cast<__float128>(DBL_MIN) * static_cast<__float128>(DBL_MIN) * static_cast<__float128>(DBL_MIN) * static_cast<__float128>(DBL_MIN) * static_cast<__float128>(DBL_MIN) / 1073741824;

constexpr __float128 quad_denorm_min = static_cast<__float128>(1) * static_cast<__float128>(DBL_MIN) * static_cast<__float128>(DBL_MIN) * static_cast<__float128>(DBL_MIN) * static_cast<__float128>(DBL_MIN) * static_cast<__float128>(DBL_MIN) * static_cast<__float128>(DBL_MIN) * static_cast<__float128>(DBL_MIN) * static_cast<__float128>(DBL_MIN) * static_cast<__float128>(DBL_MIN) * static_cast<__float128>(DBL_MIN) * static_cast<__float128>(DBL_MIN) * static_cast<__float128>(DBL_MIN) * static_cast<__float128>(DBL_MIN) * static_cast<__float128>(DBL_MIN) * static_cast<__float128>(DBL_MIN) * static_cast<__float128>(DBL_MIN) / 5.5751862996326557854e+42;

constexpr double     dbl_mult = 8.9884656743115795386e+307;                                              // This has one bit set only.
constexpr __float128 quad_max = (static_cast<__float128>(1) - 9.62964972193617926527988971292463659e-35) // This now has all bits sets to 1
                                * static_cast<__float128>(dbl_mult) * static_cast<__float128>(dbl_mult) * static_cast<__float128>(dbl_mult) * static_cast<__float128>(dbl_mult) * static_cast<__float128>(dbl_mult) * static_cast<__float128>(dbl_mult) * static_cast<__float128>(dbl_mult) * static_cast<__float128>(dbl_mult) * static_cast<__float128>(dbl_mult) * static_cast<__float128>(dbl_mult) * static_cast<__float128>(dbl_mult) * static_cast<__float128>(dbl_mult) * static_cast<__float128>(dbl_mult) * static_cast<__float128>(dbl_mult) * static_cast<__float128>(dbl_mult) * static_cast<__float128>(dbl_mult) * 65536;
} // namespace quad_constants

#define BOOST_MP_QUAD_MIN boost::multiprecision::quad_constants::quad_min
#define BOOST_MP_QUAD_DENORM_MIN boost::multiprecision::quad_constants::quad_denorm_min
#define BOOST_MP_QUAD_MAX boost::multiprecision::quad_constants::quad_max

#else

#define BOOST_MP_QUAD_MIN 3.36210314311209350626267781732175260e-4932Q
#define BOOST_MP_QUAD_DENORM_MIN 6.475175119438025110924438958227646552e-4966Q
#define BOOST_MP_QUAD_MAX 1.18973149535723176508575932662800702e4932Q

#endif

namespace backends {

struct float128_backend
{
   typedef mpl::list<signed char, short, int, long, boost::long_long_type> signed_types;
   typedef mpl::list<unsigned char, unsigned short,
                     unsigned int, unsigned long, boost::ulong_long_type>
       unsigned_types;
   typedef mpl::list<float, double, long double> float_types;
   typedef int                                   exponent_type;

 private:
   float128_type m_value;

 public:
   BOOST_CONSTEXPR   float128_backend() BOOST_NOEXCEPT : m_value(0) {}
   BOOST_CONSTEXPR   float128_backend(const float128_backend& o) BOOST_NOEXCEPT : m_value(o.m_value) {}
   BOOST_MP_CXX14_CONSTEXPR float128_backend& operator=(const float128_backend& o) BOOST_NOEXCEPT
   {
      m_value = o.m_value;
      return *this;
   }
   template <class T>
   BOOST_CONSTEXPR float128_backend(const T& i, const typename enable_if_c<is_convertible<T, float128_type>::value>::type* = 0) BOOST_NOEXCEPT_IF(noexcept(std::declval<float128_type&>() = std::declval<const T&>()))
       : m_value(i) {}
   template <class T>
   BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_arithmetic<T>::value || is_convertible<T, float128_type>::value, float128_backend&>::type operator=(const T& i) BOOST_NOEXCEPT_IF(noexcept(std::declval<float128_type&>() = std::declval<const T&>()))
   {
      m_value = i;
      return *this;
   }
   BOOST_MP_CXX14_CONSTEXPR float128_backend(long double const& f) : m_value(f)
   {
      if (::fabsl(f) > LDBL_MAX)
         m_value = (f < 0) ? -static_cast<__float128>(HUGE_VAL) : static_cast<__float128>(HUGE_VAL);
   }
   BOOST_MP_CXX14_CONSTEXPR float128_backend& operator=(long double const& f)
   {
      if (f > LDBL_MAX)
         m_value = static_cast<__float128>(HUGE_VAL);
      else if (-f > LDBL_MAX)
         m_value = -static_cast<__float128>(HUGE_VAL);
      else
         m_value = f;
      return *this;
   }
   float128_backend& operator=(const char* s)
   {
#ifndef BOOST_MP_USE_QUAD
      char* p_end;
      m_value = strtoflt128(s, &p_end);
      if (p_end - s != (std::ptrdiff_t)std::strlen(s))
      {
         BOOST_THROW_EXCEPTION(std::runtime_error("Unable to interpret input string as a floating point value"));
      }
#else
      boost::multiprecision::detail::convert_from_string(*this, s);
#endif
      return *this;
   }
   BOOST_MP_CXX14_CONSTEXPR void swap(float128_backend& o) BOOST_NOEXCEPT
   {
      // We don't call std::swap here because it's no constexpr (yet):
      float128_type t(o.value());
      o.value() = m_value;
      m_value = t;
   }
   std::string str(std::streamsize digits, std::ios_base::fmtflags f) const
   {
#ifndef BOOST_MP_USE_QUAD
      char        buf[128];
      std::string format = "%";
      if (f & std::ios_base::showpos)
         format += "+";
      if (f & std::ios_base::showpoint)
         format += "#";
      format += ".*";
      if (digits == 0)
         digits = 36;
      format += "Q";

      if (f & std::ios_base::scientific)
         format += "e";
      else if (f & std::ios_base::fixed)
         format += "f";
      else
         format += "g";

      int v;
      if ((f & std::ios_base::scientific) && (f & std::ios_base::fixed))
      {
         v = quadmath_snprintf(buf, sizeof buf, "%Qa", m_value);
      }
      else
      {
         v = quadmath_snprintf(buf, sizeof buf, format.c_str(), digits, m_value);
      }

      if ((v < 0) || (v >= 127))
      {
         int                       v_max = v;
         boost::scoped_array<char> buf2;
         buf2.reset(new char[v + 3]);
         v = quadmath_snprintf(&buf2[0], v_max + 3, format.c_str(), digits, m_value);
         if (v >= v_max + 3)
         {
            BOOST_THROW_EXCEPTION(std::runtime_error("Formatting of float128_type failed."));
         }
         return &buf2[0];
      }
      return buf;
#else
      return boost::multiprecision::detail::convert_to_string(*this, digits ? digits : 37, f);
#endif
   }
   BOOST_MP_CXX14_CONSTEXPR void negate() BOOST_NOEXCEPT
   {
      m_value = -m_value;
   }
   BOOST_MP_CXX14_CONSTEXPR int compare(const float128_backend& o) const
   {
      return m_value == o.m_value ? 0 : m_value < o.m_value ? -1 : 1;
   }
   template <class T>
   BOOST_MP_CXX14_CONSTEXPR int compare(const T& i) const
   {
      return m_value == i ? 0 : m_value < i ? -1 : 1;
   }
   BOOST_MP_CXX14_CONSTEXPR float128_type& value()
   {
      return m_value;
   }
   BOOST_MP_CXX14_CONSTEXPR const float128_type& value() const
   {
      return m_value;
   }
};

inline BOOST_MP_CXX14_CONSTEXPR void eval_add(float128_backend& result, const float128_backend& a)
{
   result.value() += a.value();
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR void eval_add(float128_backend& result, const A& a)
{
   result.value() += a;
}
inline BOOST_MP_CXX14_CONSTEXPR void eval_subtract(float128_backend& result, const float128_backend& a)
{
   result.value() -= a.value();
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR void eval_subtract(float128_backend& result, const A& a)
{
   result.value() -= a;
}
inline BOOST_MP_CXX14_CONSTEXPR void eval_multiply(float128_backend& result, const float128_backend& a)
{
   result.value() *= a.value();
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR void eval_multiply(float128_backend& result, const A& a)
{
   result.value() *= a;
}
inline BOOST_MP_CXX14_CONSTEXPR void eval_divide(float128_backend& result, const float128_backend& a)
{
   result.value() /= a.value();
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR void eval_divide(float128_backend& result, const A& a)
{
   result.value() /= a;
}

inline BOOST_MP_CXX14_CONSTEXPR void eval_add(float128_backend& result, const float128_backend& a, const float128_backend& b)
{
   result.value() = a.value() + b.value();
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR void eval_add(float128_backend& result, const float128_backend& a, const A& b)
{
   result.value() = a.value() + b;
}
inline BOOST_MP_CXX14_CONSTEXPR void eval_subtract(float128_backend& result, const float128_backend& a, const float128_backend& b)
{
   result.value() = a.value() - b.value();
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR void eval_subtract(float128_backend& result, const float128_backend& a, const A& b)
{
   result.value() = a.value() - b;
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR void eval_subtract(float128_backend& result, const A& a, const float128_backend& b)
{
   result.value() = a - b.value();
}
inline BOOST_MP_CXX14_CONSTEXPR void eval_multiply(float128_backend& result, const float128_backend& a, const float128_backend& b)
{
   result.value() = a.value() * b.value();
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR void eval_multiply(float128_backend& result, const float128_backend& a, const A& b)
{
   result.value() = a.value() * b;
}
inline BOOST_MP_CXX14_CONSTEXPR void eval_divide(float128_backend& result, const float128_backend& a, const float128_backend& b)
{
   result.value() = a.value() / b.value();
}

template <class R>
inline BOOST_MP_CXX14_CONSTEXPR void eval_convert_to(R* result, const float128_backend& val)
{
   *result = static_cast<R>(val.value());
}

inline void eval_frexp(float128_backend& result, const float128_backend& arg, int* exp)
{
   result.value() = frexpq(arg.value(), exp);
}

inline void eval_ldexp(float128_backend& result, const float128_backend& arg, int exp)
{
   result.value() = ldexpq(arg.value(), exp);
}

inline void eval_floor(float128_backend& result, const float128_backend& arg)
{
   result.value() = floorq(arg.value());
}
inline void eval_ceil(float128_backend& result, const float128_backend& arg)
{
   result.value() = ceilq(arg.value());
}
inline void eval_sqrt(float128_backend& result, const float128_backend& arg)
{
   result.value() = sqrtq(arg.value());
}
#ifndef BOOST_MP_NO_CONSTEXPR_DETECTION
inline BOOST_MP_CXX14_CONSTEXPR 
#else
inline
#endif
int eval_fpclassify(const float128_backend& arg)
{
   float128_type v = arg.value();
#ifndef BOOST_MP_NO_CONSTEXPR_DETECTION
   if (BOOST_MP_IS_CONST_EVALUATED(v))
   {
      if (v != v)
         return FP_NAN;
      if (v == 0)
         return FP_ZERO;
      float128_type t(v);
      if (t < 0)
         t = -t;
      if (t > BOOST_MP_QUAD_MAX)
         return FP_INFINITE;
      if (t < BOOST_MP_QUAD_MIN)
         return FP_SUBNORMAL;
      return FP_NORMAL;
   }
   else
#endif
   {
      if (isnanq(v))
         return FP_NAN;
      else if (isinfq(v))
         return FP_INFINITE;
      else if (v == 0)
         return FP_ZERO;

      float128_backend t(arg);
      if (t.value() < 0)
         t.negate();
      if (t.value() < BOOST_MP_QUAD_MIN)
         return FP_SUBNORMAL;
      return FP_NORMAL;
   }
}
#if defined(BOOST_GCC) && (__GNUC__ == 9)
// See https://gcc.gnu.org/bugzilla/show_bug.cgi?id=91705
inline BOOST_MP_CXX14_CONSTEXPR void eval_increment(float128_backend& arg)
{
   arg.value() = 1 + arg.value();
}
inline BOOST_MP_CXX14_CONSTEXPR void eval_decrement(float128_backend& arg)
{
   arg.value() = arg.value() - 1;
}
#else
inline BOOST_MP_CXX14_CONSTEXPR void eval_increment(float128_backend& arg)
{
   ++arg.value();
}
inline BOOST_MP_CXX14_CONSTEXPR void eval_decrement(float128_backend& arg)
{
   --arg.value();
}
#endif

/*********************************************************************
*
* abs/fabs:
*
*********************************************************************/

#ifndef BOOST_MP_NO_CONSTEXPR_DETECTION
inline BOOST_MP_CXX14_CONSTEXPR void eval_abs(float128_backend& result, const float128_backend& arg)
#else
inline void eval_abs(float128_backend& result, const float128_backend& arg)
#endif
{
   float128_type v(arg.value());
#ifndef BOOST_MP_NO_CONSTEXPR_DETECTION
   if (BOOST_MP_IS_CONST_EVALUATED(v))
   {
      result.value() = v < 0 ? -v : v;
   }
   else
#endif
   {
      result.value() = fabsq(arg.value());
   }
}
#ifndef BOOST_MP_NO_CONSTEXPR_DETECTION
inline BOOST_MP_CXX14_CONSTEXPR void eval_fabs(float128_backend& result, const float128_backend& arg)
#else
inline void eval_fabs(float128_backend& result, const float128_backend& arg)
#endif
{
   float128_type v(arg.value());
#ifndef BOOST_MP_NO_CONSTEXPR_DETECTION
   if (BOOST_MP_IS_CONST_EVALUATED(v))
   {
      result.value() = v < 0 ? -v : v;
   }
   else
#endif
   {
      result.value() = fabsq(arg.value());
   }
}

/*********************************************************************
*
* Floating point functions:
*
*********************************************************************/

inline void eval_trunc(float128_backend& result, const float128_backend& arg)
{
   result.value() = truncq(arg.value());
}
/*
// 
// This doesn't actually work... rely on our own default version instead.
//
inline void eval_round(float128_backend& result, const float128_backend& arg)
{
   if(isnanq(arg.value()) || isinf(arg.value()))
   {
      result = boost::math::policies::raise_rounding_error(
            "boost::multiprecision::trunc<%1%>(%1%)", 0, 
            number<float128_backend, et_off>(arg), 
            number<float128_backend, et_off>(arg), 
            boost::math::policies::policy<>()).backend();
      return;
   }
   result.value() = roundq(arg.value());
}
*/

inline void eval_exp(float128_backend& result, const float128_backend& arg)
{
   result.value() = expq(arg.value());
}
inline void eval_log(float128_backend& result, const float128_backend& arg)
{
   result.value() = logq(arg.value());
}
inline void eval_log10(float128_backend& result, const float128_backend& arg)
{
   result.value() = log10q(arg.value());
}
inline void eval_sin(float128_backend& result, const float128_backend& arg)
{
   result.value() = sinq(arg.value());
}
inline void eval_cos(float128_backend& result, const float128_backend& arg)
{
   result.value() = cosq(arg.value());
}
inline void eval_tan(float128_backend& result, const float128_backend& arg)
{
   result.value() = tanq(arg.value());
}
inline void eval_asin(float128_backend& result, const float128_backend& arg)
{
   result.value() = asinq(arg.value());
}
inline void eval_acos(float128_backend& result, const float128_backend& arg)
{
   result.value() = acosq(arg.value());
}
inline void eval_atan(float128_backend& result, const float128_backend& arg)
{
   result.value() = atanq(arg.value());
}
inline void eval_sinh(float128_backend& result, const float128_backend& arg)
{
   result.value() = sinhq(arg.value());
}
inline void eval_cosh(float128_backend& result, const float128_backend& arg)
{
   result.value() = coshq(arg.value());
}
inline void eval_tanh(float128_backend& result, const float128_backend& arg)
{
   result.value() = tanhq(arg.value());
}
inline void eval_fmod(float128_backend& result, const float128_backend& a, const float128_backend& b)
{
   result.value() = fmodq(a.value(), b.value());
}
inline void eval_pow(float128_backend& result, const float128_backend& a, const float128_backend& b)
{
   result.value() = powq(a.value(), b.value());
}
inline void eval_atan2(float128_backend& result, const float128_backend& a, const float128_backend& b)
{
   result.value() = atan2q(a.value(), b.value());
}
#ifndef BOOST_MP_USE_QUAD
inline void eval_multiply_add(float128_backend& result, const float128_backend& a, const float128_backend& b, const float128_backend& c)
{
   result.value() = fmaq(a.value(), b.value(), c.value());
}
inline int eval_signbit BOOST_PREVENT_MACRO_SUBSTITUTION(const float128_backend& arg)
{
   return ::signbitq(arg.value());
}
#endif

inline std::size_t hash_value(const float128_backend& val)
{
   return boost::hash_value(static_cast<double>(val.value()));
}

} // namespace backends

template <boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<float128_backend, ExpressionTemplates> asinh BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<float128_backend, ExpressionTemplates>& arg)
{
   return asinhq(arg.backend().value());
}
template <boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<float128_backend, ExpressionTemplates> acosh BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<float128_backend, ExpressionTemplates>& arg)
{
   return acoshq(arg.backend().value());
}
template <boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<float128_backend, ExpressionTemplates> atanh BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<float128_backend, ExpressionTemplates>& arg)
{
   return atanhq(arg.backend().value());
}
template <boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<float128_backend, ExpressionTemplates> cbrt BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<float128_backend, ExpressionTemplates>& arg)
{
   return cbrtq(arg.backend().value());
}
template <boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<float128_backend, ExpressionTemplates> erf BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<float128_backend, ExpressionTemplates>& arg)
{
   return erfq(arg.backend().value());
}
template <boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<float128_backend, ExpressionTemplates> erfc BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<float128_backend, ExpressionTemplates>& arg)
{
   return erfcq(arg.backend().value());
}
template <boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<float128_backend, ExpressionTemplates> expm1 BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<float128_backend, ExpressionTemplates>& arg)
{
   return expm1q(arg.backend().value());
}
template <boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<float128_backend, ExpressionTemplates> lgamma BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<float128_backend, ExpressionTemplates>& arg)
{
   return lgammaq(arg.backend().value());
}
template <boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<float128_backend, ExpressionTemplates> tgamma BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<float128_backend, ExpressionTemplates>& arg)
{
   if(eval_signbit(arg.backend()) != 0)
   {
      const bool result_is_neg = ((static_cast<unsigned long long>(floorq(-arg.backend().value())) % 2U) == 0U);

      const boost::multiprecision::number<float128_backend, ExpressionTemplates> result_of_tgammaq = fabsq(tgammaq(arg.backend().value()));

      return ((result_is_neg == false) ? result_of_tgammaq : -result_of_tgammaq);
   }
   else
   {
      return tgammaq(arg.backend().value());
   }
}
template <boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<float128_backend, ExpressionTemplates> log1p BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<float128_backend, ExpressionTemplates>& arg)
{
   return log1pq(arg.backend().value());
}

#ifndef BOOST_MP_USE_QUAD
template <multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> copysign BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates>& a, const boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates>& b)
{
   return ::copysignq(a.backend().value(), b.backend().value());
}

inline void eval_remainder(float128_backend& result, const float128_backend& a, const float128_backend& b)
{
   result.value() = remainderq(a.value(), b.value());
}
inline void eval_remainder(float128_backend& result, const float128_backend& a, const float128_backend& b, int* pi)
{
   result.value() = remquoq(a.value(), b.value(), pi);
}
#endif

} // namespace multiprecision

namespace math {

using boost::multiprecision::copysign;
using boost::multiprecision::signbit;

} // namespace math

} // namespace boost

namespace boost {
namespace archive {

class binary_oarchive;
class binary_iarchive;

} // namespace archive

namespace serialization {
namespace float128_detail {

template <class Archive>
void do_serialize(Archive& ar, boost::multiprecision::backends::float128_backend& val, const mpl::false_&, const mpl::false_&)
{
   // saving
   // non-binary
   std::string s(val.str(0, std::ios_base::scientific));
   ar&         boost::make_nvp("value", s);
}
template <class Archive>
void do_serialize(Archive& ar, boost::multiprecision::backends::float128_backend& val, const mpl::true_&, const mpl::false_&)
{
   // loading
   // non-binary
   std::string s;
   ar&         boost::make_nvp("value", s);
   val = s.c_str();
}

template <class Archive>
void do_serialize(Archive& ar, boost::multiprecision::backends::float128_backend& val, const mpl::false_&, const mpl::true_&)
{
   // saving
   // binary
   ar.save_binary(&val, sizeof(val));
}
template <class Archive>
void do_serialize(Archive& ar, boost::multiprecision::backends::float128_backend& val, const mpl::true_&, const mpl::true_&)
{
   // loading
   // binary
   ar.load_binary(&val, sizeof(val));
}

} // namespace float128_detail

template <class Archive>
void serialize(Archive& ar, boost::multiprecision::backends::float128_backend& val, unsigned int /*version*/)
{
   typedef typename Archive::is_loading                                                                                                                            load_tag;
   typedef typename mpl::bool_<boost::is_same<Archive, boost::archive::binary_oarchive>::value || boost::is_same<Archive, boost::archive::binary_iarchive>::value> binary_tag;

   float128_detail::do_serialize(ar, val, load_tag(), binary_tag());
}

} // namespace serialization

} // namespace boost

namespace std {

template <boost::multiprecision::expression_template_option ExpressionTemplates>
class numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >
{
   typedef boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> number_type;

 public:
   BOOST_STATIC_CONSTEXPR bool is_specialized = true;
   static BOOST_MP_CXX14_CONSTEXPR number_type(min)() BOOST_NOEXCEPT { return BOOST_MP_QUAD_MIN; }
   static BOOST_MP_CXX14_CONSTEXPR number_type(max)() BOOST_NOEXCEPT { return BOOST_MP_QUAD_MAX; }
   static BOOST_MP_CXX14_CONSTEXPR number_type          lowest() BOOST_NOEXCEPT { return -(max)(); }
   BOOST_STATIC_CONSTEXPR int  digits       = 113;
   BOOST_STATIC_CONSTEXPR int  digits10     = 33;
   BOOST_STATIC_CONSTEXPR int  max_digits10 = 36;
   BOOST_STATIC_CONSTEXPR bool is_signed    = true;
   BOOST_STATIC_CONSTEXPR bool is_integer   = false;
   BOOST_STATIC_CONSTEXPR bool is_exact     = false;
   BOOST_STATIC_CONSTEXPR int  radix        = 2;
   static BOOST_MP_CXX14_CONSTEXPR number_type          epsilon() { return 1.92592994438723585305597794258492732e-34; /* this double value has only one bit set and so is exact */ }
   static BOOST_MP_CXX14_CONSTEXPR number_type          round_error() { return 0.5; }
   BOOST_STATIC_CONSTEXPR int  min_exponent                  = -16381;
   BOOST_STATIC_CONSTEXPR int  min_exponent10                = min_exponent * 301L / 1000L;
   BOOST_STATIC_CONSTEXPR int  max_exponent                  = 16384;
   BOOST_STATIC_CONSTEXPR int  max_exponent10                = max_exponent * 301L / 1000L;
   BOOST_STATIC_CONSTEXPR bool has_infinity                  = true;
   BOOST_STATIC_CONSTEXPR bool has_quiet_NaN                 = true;
   BOOST_STATIC_CONSTEXPR bool has_signaling_NaN             = false;
   BOOST_STATIC_CONSTEXPR float_denorm_style has_denorm      = denorm_present;
   BOOST_STATIC_CONSTEXPR bool               has_denorm_loss = true;
   static BOOST_MP_CXX14_CONSTEXPR number_type                        infinity() { return HUGE_VAL; /* conversion from double infinity OK */ }
   static BOOST_MP_CXX14_CONSTEXPR number_type                        quiet_NaN() { return number_type("nan"); }
   static BOOST_MP_CXX14_CONSTEXPR number_type                        signaling_NaN() { return 0; }
   static BOOST_MP_CXX14_CONSTEXPR number_type                        denorm_min() { return BOOST_MP_QUAD_DENORM_MIN; }
   BOOST_STATIC_CONSTEXPR bool               is_iec559       = true;
   BOOST_STATIC_CONSTEXPR bool               is_bounded      = true;
   BOOST_STATIC_CONSTEXPR bool               is_modulo       = false;
   BOOST_STATIC_CONSTEXPR bool               traps           = false;
   BOOST_STATIC_CONSTEXPR bool               tinyness_before = false;
   BOOST_STATIC_CONSTEXPR float_round_style round_style      = round_to_nearest;
};

template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::is_specialized;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::digits;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::digits10;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::max_digits10;

template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::is_signed;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::is_integer;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::is_exact;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::radix;

template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::min_exponent;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::max_exponent;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::min_exponent10;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::max_exponent10;

template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::has_infinity;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::has_quiet_NaN;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::has_signaling_NaN;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::has_denorm_loss;

template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::is_iec559;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::is_bounded;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::is_modulo;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::traps;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::tinyness_before;

template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST float_round_style numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::round_style;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST float_denorm_style numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::has_denorm;

} // namespace std

#endif

/* float128.hpp
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
*/