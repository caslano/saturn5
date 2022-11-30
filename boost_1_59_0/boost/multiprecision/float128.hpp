///////////////////////////////////////////////////////////////
//  Copyright 2013 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MP_FLOAT128_HPP
#define BOOST_MP_FLOAT128_HPP

// https://gcc.gnu.org/onlinedocs/gcc/Floating-Types.html
#if !defined(__amd64__) && !defined(__amd64) && !defined(__x86_64__) && !defined(__x86_64) && !defined(_M_X64) && !defined(_M_AMD64) && \
    !defined(i386) && !defined(__i386) && !defined(__i386__) && !defined(_M_IX86) && !defined(__X86__) && !defined(_X86_) && !defined(__I86__) && \
    !defined(__ia64__) && !defined(_IA64) && !defined(__IA64__) && !defined(__ia64) && !defined(_M_IA64) && !defined(__itanium__) && \
    !defined(__hppa__) && !defined(__HPPA__) && !defined(__hppa) && \
    !defined(__powerpc) && !defined(_M_PPC) && !defined(_ARCH_PPC) && !defined(_ARCH_PPC64) && !defined(__PPCBROADWAY__)
#error libquadmath only works on on i386, x86_64, IA-64, and hppa HP-UX, as well as on PowerPC GNU/Linux targets that enable the vector scalar (VSX) instruction set.
#endif

#include <tuple>
#include <boost/multiprecision/detail/standalone_config.hpp>
#include <boost/multiprecision/number.hpp>
#include <boost/multiprecision/detail/hash.hpp>
#include <boost/multiprecision/detail/no_exceptions_support.hpp>

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

using float128_type = __float128;

#elif defined(BOOST_MP_USE_QUAD)

#include <boost/multiprecision/detail/float_string_cvt.hpp>

using float128_type = _Quad;

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
   static constexpr const unsigned value = 113;
};

}

#endif

namespace backends {

struct float128_backend;

}

using backends::float128_backend;

template <>
struct number_category<backends::float128_backend> : public std::integral_constant<int, number_kind_floating_point>
{};
#if defined(BOOST_MP_USE_QUAD)
template <>
struct number_category<float128_type> : public std::integral_constant<int, number_kind_floating_point>
{};
#endif

using float128 = number<float128_backend, et_off>;

namespace quad_constants {
constexpr float128_type quad_min = static_cast<float128_type>(1) * static_cast<float128_type>(DBL_MIN) * static_cast<float128_type>(DBL_MIN) * static_cast<float128_type>(DBL_MIN) * static_cast<float128_type>(DBL_MIN) * static_cast<float128_type>(DBL_MIN) * static_cast<float128_type>(DBL_MIN) * static_cast<float128_type>(DBL_MIN) * static_cast<float128_type>(DBL_MIN) * static_cast<float128_type>(DBL_MIN) * static_cast<float128_type>(DBL_MIN) * static_cast<float128_type>(DBL_MIN) * static_cast<float128_type>(DBL_MIN) * static_cast<float128_type>(DBL_MIN) * static_cast<float128_type>(DBL_MIN) * static_cast<float128_type>(DBL_MIN) * static_cast<float128_type>(DBL_MIN) / 1073741824;

constexpr float128_type quad_denorm_min = static_cast<float128_type>(1) * static_cast<float128_type>(DBL_MIN) * static_cast<float128_type>(DBL_MIN) * static_cast<float128_type>(DBL_MIN) * static_cast<float128_type>(DBL_MIN) * static_cast<float128_type>(DBL_MIN) * static_cast<float128_type>(DBL_MIN) * static_cast<float128_type>(DBL_MIN) * static_cast<float128_type>(DBL_MIN) * static_cast<float128_type>(DBL_MIN) * static_cast<float128_type>(DBL_MIN) * static_cast<float128_type>(DBL_MIN) * static_cast<float128_type>(DBL_MIN) * static_cast<float128_type>(DBL_MIN) * static_cast<float128_type>(DBL_MIN) * static_cast<float128_type>(DBL_MIN) * static_cast<float128_type>(DBL_MIN) / 5.5751862996326557854e+42;

constexpr double     dbl_mult = 8.9884656743115795386e+307;                                              // This has one bit set only.
constexpr float128_type quad_max = (static_cast<float128_type>(1) - 9.62964972193617926527988971292463659e-35) // This now has all bits sets to 1
                                * static_cast<float128_type>(dbl_mult) * static_cast<float128_type>(dbl_mult) * static_cast<float128_type>(dbl_mult) * static_cast<float128_type>(dbl_mult) * static_cast<float128_type>(dbl_mult) * static_cast<float128_type>(dbl_mult) * static_cast<float128_type>(dbl_mult) * static_cast<float128_type>(dbl_mult) * static_cast<float128_type>(dbl_mult) * static_cast<float128_type>(dbl_mult) * static_cast<float128_type>(dbl_mult) * static_cast<float128_type>(dbl_mult) * static_cast<float128_type>(dbl_mult) * static_cast<float128_type>(dbl_mult) * static_cast<float128_type>(dbl_mult) * static_cast<float128_type>(dbl_mult) * 65536;
} // namespace quad_constants

#define BOOST_MP_QUAD_MIN boost::multiprecision::quad_constants::quad_min
#define BOOST_MP_QUAD_DENORM_MIN boost::multiprecision::quad_constants::quad_denorm_min
#define BOOST_MP_QUAD_MAX boost::multiprecision::quad_constants::quad_max


namespace backends {

struct float128_backend
{
   using signed_types = std::tuple<signed char, short, int, long, long long>;
   using unsigned_types = std::tuple<unsigned char, unsigned short, unsigned int, unsigned long, unsigned long long>;
   using float_types = std::tuple<float, double, long double>;
   using exponent_type = int                                  ;

 private:
   float128_type m_value;

 public:
   constexpr   float128_backend() noexcept : m_value(0) {}
   constexpr   float128_backend(const float128_backend& o) noexcept : m_value(o.m_value) {}
   BOOST_MP_CXX14_CONSTEXPR float128_backend& operator=(const float128_backend& o) noexcept
   {
      m_value = o.m_value;
      return *this;
   }
   template <class T>
   constexpr float128_backend(const T& i, const typename std::enable_if<std::is_convertible<T, float128_type>::value>::type* = 0) noexcept(noexcept(std::declval<float128_type&>() = std::declval<const T&>()))
       : m_value(i) {}
   template <class T>
   BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<boost::multiprecision::detail::is_arithmetic<T>::value || std::is_convertible<T, float128_type>::value, float128_backend&>::type operator=(const T& i) noexcept(noexcept(std::declval<float128_type&>() = std::declval<const T&>()))
   {
      m_value = i;
      return *this;
   }
   BOOST_MP_CXX14_CONSTEXPR float128_backend(long double const& f) : m_value(f)
   {
      if (::fabsl(f) > LDBL_MAX)
         m_value = (f < 0) ? -static_cast<float128_type>(HUGE_VAL) : static_cast<float128_type>(HUGE_VAL);
   }
   BOOST_MP_CXX14_CONSTEXPR float128_backend& operator=(long double const& f)
   {
      if (f > LDBL_MAX)
         m_value = static_cast<float128_type>(HUGE_VAL);
      else if (-f > LDBL_MAX)
         m_value = -static_cast<float128_type>(HUGE_VAL);
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
         BOOST_MP_THROW_EXCEPTION(std::runtime_error("Unable to interpret input string as a floating point value"));
      }
#else
      boost::multiprecision::detail::convert_from_string(*this, s);
#endif
      return *this;
   }
   BOOST_MP_CXX14_CONSTEXPR void swap(float128_backend& o) noexcept
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
      if ((digits == 0) && !(f & std::ios_base::fixed))
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
         std::unique_ptr<char[]>   buf2;
         buf2.reset(new char[v + 3]);
         v = quadmath_snprintf(&buf2[0], v_max + 3, format.c_str(), digits, m_value);
         if (v >= v_max + 3)
         {
            BOOST_MP_THROW_EXCEPTION(std::runtime_error("Formatting of float128_type failed."));
         }
         return &buf2[0];
      }
      return buf;
#else
      return boost::multiprecision::detail::convert_to_string(*this, digits ? digits : 36, f);
#endif
   }
   BOOST_MP_CXX14_CONSTEXPR void negate() noexcept
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

inline void eval_rsqrt(float128_backend& result, const float128_backend& arg)
{
#if (LDBL_MANT_DIG > 100)
   // GCC can't mix and match __float128 and quad precision long double
   // error: __float128 and long double cannot be used in the same expression
   result.value() = 1 / sqrtq(arg.value());
#else
   using std::sqrt;
   if (arg.value() < std::numeric_limits<long double>::denorm_min() || arg.value() > (std::numeric_limits<long double>::max)()) {
      result.value() = 1/sqrtq(arg.value());
      return;
   }
   float128_backend xk = 1/sqrt(static_cast<long double>(arg.value()));

   // Newton iteration for f(x) = arg.value() - 1/x^2.
   BOOST_IF_CONSTEXPR (sizeof(long double) == sizeof(double)) {
       // If the long double is the same as a double, then we need two Newton iterations:
       xk.value() = xk.value() + xk.value()*(1-arg.value()*xk.value()*xk.value())/2;
       result.value() = xk.value() + xk.value()*(1-arg.value()*xk.value()*xk.value())/2;
   }
   else
   {
      // 80 bit long double only needs a single iteration to produce ~2ULPs.
      result.value() = xk.value() + xk.value() * (1 - arg.value() * xk.value() * xk.value()) / 2;
   }
#endif
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
#ifndef BOOST_MP_NO_CONSTEXPR_DETECTION
   float128_type v(arg.value());
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
#ifndef BOOST_MP_NO_CONSTEXPR_DETECTION
   float128_type v(arg.value());
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
   return boost::multiprecision::detail::hash_value(static_cast<double>(val.value()));
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
template <boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<float128_backend, ExpressionTemplates> rsqrt BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<float128_backend, ExpressionTemplates>& arg)
{
   boost::multiprecision::number<float128_backend, ExpressionTemplates> res;
   eval_rsqrt(res.backend(), arg.backend());
   return res;
}

#ifndef BOOST_MP_USE_QUAD
template <multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> copysign BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates>& a, const boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates>& b)
{
   return ::copysignq(a.backend().value(), b.backend().value());
}

namespace backends {

inline void eval_remainder(float128_backend& result, const float128_backend& a, const float128_backend& b)
{
   result.value() = remainderq(a.value(), b.value());
}
inline void eval_remainder(float128_backend& result, const float128_backend& a, const float128_backend& b, int* pi)
{
   result.value() = remquoq(a.value(), b.value(), pi);
}
} // namespace backends

#endif

} // namespace multiprecision

namespace math {

using boost::multiprecision::copysign;
using boost::multiprecision::signbit;

} // namespace math

} // namespace boost

#ifndef BOOST_MP_STANDALONE
namespace boost {
namespace archive {

class binary_oarchive;
class binary_iarchive;

} // namespace archive

namespace serialization {
namespace float128_detail {

template <class Archive>
void do_serialize(Archive& ar, boost::multiprecision::backends::float128_backend& val, const std::integral_constant<bool, false>&, const std::integral_constant<bool, false>&)
{
   // saving
   // non-binary
   std::string s(val.str(0, std::ios_base::scientific));
   ar&         boost::make_nvp("value", s);
}
template <class Archive>
void do_serialize(Archive& ar, boost::multiprecision::backends::float128_backend& val, const std::integral_constant<bool, true>&, const std::integral_constant<bool, false>&)
{
   // loading
   // non-binary
   std::string s;
   ar&         boost::make_nvp("value", s);
   val = s.c_str();
}

template <class Archive>
void do_serialize(Archive& ar, boost::multiprecision::backends::float128_backend& val, const std::integral_constant<bool, false>&, const std::integral_constant<bool, true>&)
{
   // saving
   // binary
   ar.save_binary(&val, sizeof(val));
}
template <class Archive>
void do_serialize(Archive& ar, boost::multiprecision::backends::float128_backend& val, const std::integral_constant<bool, true>&, const std::integral_constant<bool, true>&)
{
   // loading
   // binary
   ar.load_binary(&val, sizeof(val));
}

} // namespace float128_detail

template <class Archive>
void serialize(Archive& ar, boost::multiprecision::backends::float128_backend& val, unsigned int /*version*/)
{
   using load_tag = typename Archive::is_loading                                                                                                                                         ;
   using loading = std::integral_constant<bool, load_tag::value>                                                                                                                        ;
   using binary_tag = typename std::integral_constant<bool, std::is_same<Archive, boost::archive::binary_oarchive>::value || std::is_same<Archive, boost::archive::binary_iarchive>::value>;

   float128_detail::do_serialize(ar, val, loading(), binary_tag());
}

} // namespace serialization

} // namespace boost
#endif // BOOST_MP_STANDALONE

namespace std {

template <boost::multiprecision::expression_template_option ExpressionTemplates>
class numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >
{
   using number_type = boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates>;

 public:
   static constexpr bool is_specialized = true;
   static BOOST_MP_CXX14_CONSTEXPR number_type(min)() noexcept { return BOOST_MP_QUAD_MIN; }
   static BOOST_MP_CXX14_CONSTEXPR number_type(max)() noexcept { return BOOST_MP_QUAD_MAX; }
   static BOOST_MP_CXX14_CONSTEXPR number_type          lowest() noexcept { return -(max)(); }
   static constexpr int  digits       = 113;
   static constexpr int  digits10     = 33;
   static constexpr int  max_digits10 = 36;
   static constexpr bool is_signed    = true;
   static constexpr bool is_integer   = false;
   static constexpr bool is_exact     = false;
   static constexpr int  radix        = 2;
   static BOOST_MP_CXX14_CONSTEXPR number_type          epsilon() { return 1.92592994438723585305597794258492732e-34; /* this double value has only one bit set and so is exact */ }
   static BOOST_MP_CXX14_CONSTEXPR number_type          round_error() { return 0.5; }
   static constexpr int  min_exponent                  = -16381;
   static constexpr int  min_exponent10                = min_exponent * 301L / 1000L;
   static constexpr int  max_exponent                  = 16384;
   static constexpr int  max_exponent10                = max_exponent * 301L / 1000L;
   static constexpr bool has_infinity                  = true;
   static constexpr bool has_quiet_NaN                 = true;
   static constexpr bool has_signaling_NaN             = false;
   static constexpr float_denorm_style has_denorm      = denorm_present;
   static constexpr bool               has_denorm_loss = true;
   static BOOST_MP_CXX14_CONSTEXPR number_type                        infinity() { return HUGE_VAL; /* conversion from double infinity OK */ }
   static BOOST_MP_CXX14_CONSTEXPR number_type                        quiet_NaN() { return number_type(NAN); }
   static BOOST_MP_CXX14_CONSTEXPR number_type                        signaling_NaN() { return 0; }
   static BOOST_MP_CXX14_CONSTEXPR number_type                        denorm_min() { return BOOST_MP_QUAD_DENORM_MIN; }
   static constexpr bool               is_iec559       = true;
   static constexpr bool               is_bounded      = true;
   static constexpr bool               is_modulo       = false;
   static constexpr bool               traps           = false;
   static constexpr bool               tinyness_before = false;
   static constexpr float_round_style round_style      = round_to_nearest;
};

template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::is_specialized;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::digits;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::digits10;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::max_digits10;

template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::is_signed;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::is_integer;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::is_exact;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::radix;

template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::min_exponent;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::max_exponent;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::min_exponent10;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::max_exponent10;

template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::has_infinity;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::has_quiet_NaN;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::has_signaling_NaN;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::has_denorm_loss;

template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::is_iec559;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::is_bounded;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::is_modulo;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::traps;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::tinyness_before;

template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr float_round_style numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::round_style;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr float_denorm_style numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::float128_backend, ExpressionTemplates> >::has_denorm;

} // namespace std

#endif

/* float128.hpp
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
*/