//  Copyright John Maddock 2007.
//  Copyright Paul A. Bristow 2007.

//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_POLICY_ERROR_HANDLING_HPP
#define BOOST_MATH_POLICY_ERROR_HANDLING_HPP

#include <iomanip>
#include <string>
#include <cstring>
#include <typeinfo>
#include <cerrno>
#include <complex>
#include <cmath>
#include <cstdint>
#include <stdexcept>
#include <boost/math/tools/config.hpp>
#include <boost/math/policies/policy.hpp>
#include <boost/math/tools/precision.hpp>
#include <boost/math/tools/throw_exception.hpp>

#ifdef _MSC_VER
#  pragma warning(push) // Quiet warnings in boost/format.hpp
#  pragma warning(disable: 4996) // _SCL_SECURE_NO_DEPRECATE
#  pragma warning(disable: 4512) // assignment operator could not be generated.
#  pragma warning(disable: 4127) // conditional expression is constant
// And warnings in error handling:
#  pragma warning(disable: 4702) // unreachable code.
// Note that this only occurs when the compiler can deduce code is unreachable,
// for example when policy macros are used to ignore errors rather than throw.
#endif
#include <sstream>

namespace boost{ namespace math{

class evaluation_error : public std::runtime_error
{
public:
   evaluation_error(const std::string& s) : std::runtime_error(s){}
};

class rounding_error : public std::runtime_error
{
public:
   rounding_error(const std::string& s) : std::runtime_error(s){}
};

namespace policies{
//
// Forward declarations of user error handlers,
// it's up to the user to provide the definition of these:
//
template <class T>
T user_domain_error(const char* function, const char* message, const T& val);
template <class T>
T user_pole_error(const char* function, const char* message, const T& val);
template <class T>
T user_overflow_error(const char* function, const char* message, const T& val);
template <class T>
T user_underflow_error(const char* function, const char* message, const T& val);
template <class T>
T user_denorm_error(const char* function, const char* message, const T& val);
template <class T>
T user_evaluation_error(const char* function, const char* message, const T& val);
template <class T, class TargetType>
T user_rounding_error(const char* function, const char* message, const T& val, const TargetType& t);
template <class T>
T user_indeterminate_result_error(const char* function, const char* message, const T& val);

namespace detail
{

template <class T>
std::string prec_format(const T& val)
{
   typedef typename boost::math::policies::precision<T, boost::math::policies::policy<> >::type prec_type;
   std::stringstream ss;
   if(prec_type::value)
   {
      int prec = 2 + (prec_type::value * 30103UL) / 100000UL;
      ss << std::setprecision(prec);
   }
   ss << val;
   return ss.str();
}

inline void replace_all_in_string(std::string& result, const char* what, const char* with)
{
   std::string::size_type pos = 0;
   std::string::size_type slen = std::strlen(what);
   std::string::size_type rlen = std::strlen(with);
   while((pos = result.find(what, pos)) != std::string::npos)
   {
      result.replace(pos, slen, with);
      pos += rlen;
   }
}

template <class T>
inline const char* name_of()
{
#ifndef BOOST_NO_RTTI
   return typeid(T).name();
#else
   return "unknown";
#endif
}
template <> inline const char* name_of<float>(){ return "float"; }
template <> inline const char* name_of<double>(){ return "double"; }
template <> inline const char* name_of<long double>(){ return "long double"; }

#ifdef BOOST_MATH_USE_FLOAT128
template <>
inline const char* name_of<BOOST_MATH_FLOAT128_TYPE>()
{
   return "__float128";
}
#endif

template <class E, class T>
void raise_error(const char* pfunction, const char* message)
{
  if(pfunction == 0)
     pfunction = "Unknown function operating on type %1%";
  if(message == 0)
     message = "Cause unknown";

  std::string function(pfunction);
  std::string msg("Error in function ");
#ifndef BOOST_NO_RTTI
  replace_all_in_string(function, "%1%", boost::math::policies::detail::name_of<T>());
#else
  replace_all_in_string(function, "%1%", "Unknown");
#endif
  msg += function;
  msg += ": ";
  msg += message;

  E e(msg);
  BOOST_MATH_THROW_EXCEPTION(e)
}

template <class E, class T>
void raise_error(const char* pfunction, const char* pmessage, const T& val)
{
  if(pfunction == 0)
     pfunction = "Unknown function operating on type %1%";
  if(pmessage == 0)
     pmessage = "Cause unknown: error caused by bad argument with value %1%";

  std::string function(pfunction);
  std::string message(pmessage);
  std::string msg("Error in function ");
#ifndef BOOST_NO_RTTI
  replace_all_in_string(function, "%1%", boost::math::policies::detail::name_of<T>());
#else
  replace_all_in_string(function, "%1%", "Unknown");
#endif
  msg += function;
  msg += ": ";

  std::string sval = prec_format(val);
  replace_all_in_string(message, "%1%", sval.c_str());
  msg += message;

  E e(msg);
  BOOST_MATH_THROW_EXCEPTION(e)
}

template <class T>
inline T raise_domain_error(
           const char* function,
           const char* message,
           const T& val,
           const ::boost::math::policies::domain_error< ::boost::math::policies::throw_on_error>&)
{
   raise_error<std::domain_error, T>(function, message, val);
   // we never get here:
   return std::numeric_limits<T>::quiet_NaN();
}

template <class T>
inline constexpr T raise_domain_error(
           const char* ,
           const char* ,
           const T& ,
           const ::boost::math::policies::domain_error< ::boost::math::policies::ignore_error>&) BOOST_MATH_NOEXCEPT(T)
{
   // This may or may not do the right thing, but the user asked for the error
   // to be ignored so here we go anyway:
   return std::numeric_limits<T>::quiet_NaN();
}

template <class T>
inline T raise_domain_error(
           const char* ,
           const char* ,
           const T& ,
           const ::boost::math::policies::domain_error< ::boost::math::policies::errno_on_error>&) BOOST_MATH_NOEXCEPT(T)
{
   errno = EDOM;
   // This may or may not do the right thing, but the user asked for the error
   // to be silent so here we go anyway:
   return std::numeric_limits<T>::quiet_NaN();
}

template <class T>
inline T raise_domain_error(
           const char* function,
           const char* message,
           const T& val,
           const  ::boost::math::policies::domain_error< ::boost::math::policies::user_error>&)
{
   return user_domain_error(function, message, val);
}

template <class T>
inline T raise_pole_error(
           const char* function,
           const char* message,
           const T& val,
           const  ::boost::math::policies::pole_error< ::boost::math::policies::throw_on_error>&)
{
   return boost::math::policies::detail::raise_domain_error(function, message, val,  ::boost::math::policies::domain_error< ::boost::math::policies::throw_on_error>());
}

template <class T>
inline constexpr T raise_pole_error(
           const char* function,
           const char* message,
           const T& val,
           const  ::boost::math::policies::pole_error< ::boost::math::policies::ignore_error>&) BOOST_MATH_NOEXCEPT(T)
{
   return  ::boost::math::policies::detail::raise_domain_error(function, message, val,  ::boost::math::policies::domain_error< ::boost::math::policies::ignore_error>());
}

template <class T>
inline constexpr T raise_pole_error(
           const char* function,
           const char* message,
           const T& val,
           const  ::boost::math::policies::pole_error< ::boost::math::policies::errno_on_error>&) BOOST_MATH_NOEXCEPT(T)
{
   return  ::boost::math::policies::detail::raise_domain_error(function, message, val,  ::boost::math::policies::domain_error< ::boost::math::policies::errno_on_error>());
}

template <class T>
inline T raise_pole_error(
           const char* function,
           const char* message,
           const T& val,
           const  ::boost::math::policies::pole_error< ::boost::math::policies::user_error>&)
{
   return user_pole_error(function, message, val);
}


template <class T>
inline T raise_overflow_error(
           const char* function,
           const char* message,
           const  ::boost::math::policies::overflow_error< ::boost::math::policies::throw_on_error>&)
{
   raise_error<std::overflow_error, T>(function, message ? message : "numeric overflow");
   // We should never get here:
   return std::numeric_limits<T>::has_infinity ? std::numeric_limits<T>::infinity() : boost::math::tools::max_value<T>();
}

template <class T>
inline T raise_overflow_error(
           const char* function,
           const char* message,
           const T& val,
           const ::boost::math::policies::overflow_error< ::boost::math::policies::throw_on_error>&)
{
   raise_error<std::overflow_error, T>(function, message ? message : "numeric overflow", val);
   // We should never get here:
   return std::numeric_limits<T>::has_infinity ? std::numeric_limits<T>::infinity() : boost::math::tools::max_value<T>();
}

template <class T>
inline constexpr T raise_overflow_error(
           const char* ,
           const char* ,
           const  ::boost::math::policies::overflow_error< ::boost::math::policies::ignore_error>&) BOOST_MATH_NOEXCEPT(T)
{
   // This may or may not do the right thing, but the user asked for the error
   // to be ignored so here we go anyway:
   return std::numeric_limits<T>::has_infinity ? std::numeric_limits<T>::infinity() : boost::math::tools::max_value<T>();
}

template <class T>
inline constexpr T raise_overflow_error(
           const char* ,
           const char* ,
           const T&,
           const  ::boost::math::policies::overflow_error< ::boost::math::policies::ignore_error>&) BOOST_MATH_NOEXCEPT(T)
{
   // This may or may not do the right thing, but the user asked for the error
   // to be ignored so here we go anyway:
   return std::numeric_limits<T>::has_infinity ? std::numeric_limits<T>::infinity() : boost::math::tools::max_value<T>();
}

template <class T>
inline T raise_overflow_error(
           const char* ,
           const char* ,
           const  ::boost::math::policies::overflow_error< ::boost::math::policies::errno_on_error>&) BOOST_MATH_NOEXCEPT(T)
{
   errno = ERANGE;
   // This may or may not do the right thing, but the user asked for the error
   // to be silent so here we go anyway:
   return std::numeric_limits<T>::has_infinity ? std::numeric_limits<T>::infinity() : boost::math::tools::max_value<T>();
}

template <class T>
inline T raise_overflow_error(
           const char* ,
           const char* ,
           const T&,
           const  ::boost::math::policies::overflow_error< ::boost::math::policies::errno_on_error>&) BOOST_MATH_NOEXCEPT(T)
{
   errno = ERANGE;
   // This may or may not do the right thing, but the user asked for the error
   // to be silent so here we go anyway:
   return std::numeric_limits<T>::has_infinity ? std::numeric_limits<T>::infinity() : boost::math::tools::max_value<T>();
}

template <class T>
inline T raise_overflow_error(
           const char* function,
           const char* message,
           const  ::boost::math::policies::overflow_error< ::boost::math::policies::user_error>&)
{
   return user_overflow_error(function, message, std::numeric_limits<T>::infinity());
}

template <class T>
inline T raise_overflow_error(
           const char* function,
           const char* message,
           const T& val,
           const  ::boost::math::policies::overflow_error< ::boost::math::policies::user_error>&)
{
   std::string m(message ? message : "");
   std::string sval = prec_format(val);
   replace_all_in_string(m, "%1%", sval.c_str());

   return user_overflow_error(function, m.c_str(), std::numeric_limits<T>::infinity());
}

template <class T>
inline T raise_underflow_error(
           const char* function,
           const char* message,
           const  ::boost::math::policies::underflow_error< ::boost::math::policies::throw_on_error>&)
{
   raise_error<std::underflow_error, T>(function, message ? message : "numeric underflow");
   // We should never get here:
   return 0;
}

template <class T>
inline constexpr T raise_underflow_error(
           const char* ,
           const char* ,
           const  ::boost::math::policies::underflow_error< ::boost::math::policies::ignore_error>&) BOOST_MATH_NOEXCEPT(T)
{
   // This may or may not do the right thing, but the user asked for the error
   // to be ignored so here we go anyway:
   return T(0);
}

template <class T>
inline T raise_underflow_error(
           const char* /* function */,
           const char* /* message */,
           const  ::boost::math::policies::underflow_error< ::boost::math::policies::errno_on_error>&) BOOST_MATH_NOEXCEPT(T)
{
   errno = ERANGE;
   // This may or may not do the right thing, but the user asked for the error
   // to be silent so here we go anyway:
   return T(0);
}

template <class T>
inline T raise_underflow_error(
           const char* function,
           const char* message,
           const  ::boost::math::policies::underflow_error< ::boost::math::policies::user_error>&)
{
   return user_underflow_error(function, message, T(0));
}

template <class T>
inline T raise_denorm_error(
           const char* function,
           const char* message,
           const T& /* val */,
           const  ::boost::math::policies::denorm_error< ::boost::math::policies::throw_on_error>&)
{
   raise_error<std::underflow_error, T>(function, message ? message : "denormalised result");
   // we never get here:
   return T(0);
}

template <class T>
inline constexpr T raise_denorm_error(
           const char* ,
           const char* ,
           const T&  val,
           const  ::boost::math::policies::denorm_error< ::boost::math::policies::ignore_error>&) BOOST_MATH_NOEXCEPT(T)
{
   // This may or may not do the right thing, but the user asked for the error
   // to be ignored so here we go anyway:
   return val;
}

template <class T>
inline T raise_denorm_error(
           const char* ,
           const char* ,
           const T& val,
           const  ::boost::math::policies::denorm_error< ::boost::math::policies::errno_on_error>&) BOOST_MATH_NOEXCEPT(T)
{
   errno = ERANGE;
   // This may or may not do the right thing, but the user asked for the error
   // to be silent so here we go anyway:
   return val;
}

template <class T>
inline T raise_denorm_error(
           const char* function,
           const char* message,
           const T& val,
           const  ::boost::math::policies::denorm_error< ::boost::math::policies::user_error>&)
{
   return user_denorm_error(function, message, val);
}

template <class T>
inline T raise_evaluation_error(
           const char* function,
           const char* message,
           const T& val,
           const  ::boost::math::policies::evaluation_error< ::boost::math::policies::throw_on_error>&)
{
   raise_error<boost::math::evaluation_error, T>(function, message, val);
   // we never get here:
   return T(0);
}

template <class T>
inline constexpr T raise_evaluation_error(
           const char* ,
           const char* ,
           const T& val,
           const  ::boost::math::policies::evaluation_error< ::boost::math::policies::ignore_error>&) BOOST_MATH_NOEXCEPT(T)
{
   // This may or may not do the right thing, but the user asked for the error
   // to be ignored so here we go anyway:
   return val;
}

template <class T>
inline T raise_evaluation_error(
           const char* ,
           const char* ,
           const T& val,
           const  ::boost::math::policies::evaluation_error< ::boost::math::policies::errno_on_error>&) BOOST_MATH_NOEXCEPT(T)
{
   errno = EDOM;
   // This may or may not do the right thing, but the user asked for the error
   // to be silent so here we go anyway:
   return val;
}

template <class T>
inline T raise_evaluation_error(
           const char* function,
           const char* message,
           const T& val,
           const  ::boost::math::policies::evaluation_error< ::boost::math::policies::user_error>&)
{
   return user_evaluation_error(function, message, val);
}

template <class T, class TargetType>
inline TargetType raise_rounding_error(
           const char* function,
           const char* message,
           const T& val,
           const TargetType&,
           const  ::boost::math::policies::rounding_error< ::boost::math::policies::throw_on_error>&)
{
   raise_error<boost::math::rounding_error, T>(function, message, val);
   // we never get here:
   return TargetType(0);
}

template <class T, class TargetType>
inline constexpr TargetType raise_rounding_error(
           const char* ,
           const char* ,
           const T& val,
           const TargetType&,
           const  ::boost::math::policies::rounding_error< ::boost::math::policies::ignore_error>&) BOOST_MATH_NOEXCEPT(T)
{
   // This may or may not do the right thing, but the user asked for the error
   // to be ignored so here we go anyway:
   static_assert(std::numeric_limits<TargetType>::is_specialized, "The target type must be specialized.");
   return  val > 0 ? (std::numeric_limits<TargetType>::max)() : (std::numeric_limits<TargetType>::is_integer ? (std::numeric_limits<TargetType>::min)() : -(std::numeric_limits<TargetType>::max)());
}

template <class T, class TargetType>
inline TargetType raise_rounding_error(
           const char* ,
           const char* ,
           const T& val,
           const TargetType&,
           const  ::boost::math::policies::rounding_error< ::boost::math::policies::errno_on_error>&) BOOST_MATH_NOEXCEPT(T)
{
   errno = ERANGE;
   // This may or may not do the right thing, but the user asked for the error
   // to be silent so here we go anyway:
   static_assert(std::numeric_limits<TargetType>::is_specialized, "The target type must be specialized.");
   return  val > 0 ? (std::numeric_limits<TargetType>::max)() : (std::numeric_limits<TargetType>::is_integer ? (std::numeric_limits<TargetType>::min)() : -(std::numeric_limits<TargetType>::max)());
}

template <class T>
inline T raise_rounding_error(
           const char* ,
           const char* ,
           const T& val,
           const T&,
           const  ::boost::math::policies::rounding_error< ::boost::math::policies::errno_on_error>&) BOOST_MATH_NOEXCEPT(T)
{
   errno = ERANGE;
   // This may or may not do the right thing, but the user asked for the error
   // to be silent so here we go anyway:
   return  val > 0 ? boost::math::tools::max_value<T>() : -boost::math::tools::max_value<T>();
}

template <class T, class TargetType>
inline TargetType raise_rounding_error(
           const char* function,
           const char* message,
           const T& val,
           const TargetType& t,
           const  ::boost::math::policies::rounding_error< ::boost::math::policies::user_error>&)
{
   return user_rounding_error(function, message, val, t);
}

template <class T, class R>
inline T raise_indeterminate_result_error(
           const char* function,
           const char* message,
           const T& val,
           const R& ,
           const ::boost::math::policies::indeterminate_result_error< ::boost::math::policies::throw_on_error>&)
{
   raise_error<std::domain_error, T>(function, message, val);
   // we never get here:
   return std::numeric_limits<T>::quiet_NaN();
}

template <class T, class R>
inline constexpr T raise_indeterminate_result_error(
           const char* ,
           const char* ,
           const T& ,
           const R& result,
           const ::boost::math::policies::indeterminate_result_error< ::boost::math::policies::ignore_error>&) BOOST_MATH_NOEXCEPT(T)
{
   // This may or may not do the right thing, but the user asked for the error
   // to be ignored so here we go anyway:
   return result;
}

template <class T, class R>
inline T raise_indeterminate_result_error(
           const char* ,
           const char* ,
           const T& ,
           const R& result,
           const ::boost::math::policies::indeterminate_result_error< ::boost::math::policies::errno_on_error>&)
{
   errno = EDOM;
   // This may or may not do the right thing, but the user asked for the error
   // to be silent so here we go anyway:
   return result;
}

template <class T, class R>
inline T raise_indeterminate_result_error(
           const char* function,
           const char* message,
           const T& val,
           const R& ,
           const ::boost::math::policies::indeterminate_result_error< ::boost::math::policies::user_error>&)
{
   return user_indeterminate_result_error(function, message, val);
}

}  // namespace detail

template <class T, class Policy>
inline constexpr T raise_domain_error(const char* function, const char* message, const T& val, const Policy&) noexcept(is_noexcept_error_policy<Policy>::value && BOOST_MATH_IS_FLOAT(T))
{
   typedef typename Policy::domain_error_type policy_type;
   return detail::raise_domain_error(
      function, message ? message : "Domain Error evaluating function at %1%",
      val, policy_type());
}

template <class T, class Policy>
inline constexpr T raise_pole_error(const char* function, const char* message, const T& val, const Policy&) noexcept(is_noexcept_error_policy<Policy>::value && BOOST_MATH_IS_FLOAT(T))
{
   typedef typename Policy::pole_error_type policy_type;
   return detail::raise_pole_error(
      function, message ? message : "Evaluation of function at pole %1%",
      val, policy_type());
}

template <class T, class Policy>
inline constexpr T raise_overflow_error(const char* function, const char* message, const Policy&) noexcept(is_noexcept_error_policy<Policy>::value && BOOST_MATH_IS_FLOAT(T))
{
   typedef typename Policy::overflow_error_type policy_type;
   return detail::raise_overflow_error<T>(
      function, message ? message : "Overflow Error",
      policy_type());
}

template <class T, class Policy>
inline constexpr T raise_overflow_error(const char* function, const char* message, const T& val, const Policy&) noexcept(is_noexcept_error_policy<Policy>::value && BOOST_MATH_IS_FLOAT(T))
{
   typedef typename Policy::overflow_error_type policy_type;
   return detail::raise_overflow_error(
      function, message ? message : "Overflow evaluating function at %1%",
      val, policy_type());
}

template <class T, class Policy>
inline constexpr T raise_underflow_error(const char* function, const char* message, const Policy&) noexcept(is_noexcept_error_policy<Policy>::value && BOOST_MATH_IS_FLOAT(T))
{
   typedef typename Policy::underflow_error_type policy_type;
   return detail::raise_underflow_error<T>(
      function, message ? message : "Underflow Error",
      policy_type());
}

template <class T, class Policy>
inline constexpr T raise_denorm_error(const char* function, const char* message, const T& val, const Policy&) noexcept(is_noexcept_error_policy<Policy>::value && BOOST_MATH_IS_FLOAT(T))
{
   typedef typename Policy::denorm_error_type policy_type;
   return detail::raise_denorm_error<T>(
      function, message ? message : "Denorm Error",
      val,
      policy_type());
}

template <class T, class Policy>
inline constexpr T raise_evaluation_error(const char* function, const char* message, const T& val, const Policy&) noexcept(is_noexcept_error_policy<Policy>::value && BOOST_MATH_IS_FLOAT(T))
{
   typedef typename Policy::evaluation_error_type policy_type;
   return detail::raise_evaluation_error(
      function, message ? message : "Internal Evaluation Error, best value so far was %1%",
      val, policy_type());
}

template <class T, class TargetType, class Policy>
inline constexpr TargetType raise_rounding_error(const char* function, const char* message, const T& val, const TargetType& t, const Policy&) noexcept(is_noexcept_error_policy<Policy>::value && BOOST_MATH_IS_FLOAT(T))
{
   typedef typename Policy::rounding_error_type policy_type;
   return detail::raise_rounding_error(
      function, message ? message : "Value %1% can not be represented in the target integer type.",
      val, t, policy_type());
}

template <class T, class R, class Policy>
inline constexpr T raise_indeterminate_result_error(const char* function, const char* message, const T& val, const R& result, const Policy&) noexcept(is_noexcept_error_policy<Policy>::value && BOOST_MATH_IS_FLOAT(T))
{
   typedef typename Policy::indeterminate_result_error_type policy_type;
   return detail::raise_indeterminate_result_error(
      function, message ? message : "Indeterminate result with value %1%",
      val, result, policy_type());
}

//
// checked_narrowing_cast:
//
namespace detail
{

template <class R, class T, class Policy>
inline bool check_overflow(T val, R* result, const char* function, const Policy& pol) noexcept(BOOST_MATH_IS_FLOAT(R) && BOOST_MATH_IS_FLOAT(T) && (Policy::value != throw_on_error) && (Policy::value != user_error))
{
   BOOST_MATH_STD_USING
   if(fabs(val) > tools::max_value<R>())
   {
      boost::math::policies::detail::raise_overflow_error<R>(function, 0, pol);
      *result = static_cast<R>(val);
      return true;
   }
   return false;
}
template <class R, class T, class Policy>
inline bool check_overflow(std::complex<T> val, R* result, const char* function, const Policy& pol) noexcept(BOOST_MATH_IS_FLOAT(R) && BOOST_MATH_IS_FLOAT(T) && (Policy::value != throw_on_error) && (Policy::value != user_error))
{
   typedef typename R::value_type r_type;
   r_type re, im;
   bool r = check_overflow<r_type>(val.real(), &re, function, pol);
   r = check_overflow<r_type>(val.imag(), &im, function, pol) || r;
   *result = R(re, im);
   return r;
}
template <class R, class T, class Policy>
inline bool check_underflow(T val, R* result, const char* function, const Policy& pol) noexcept(BOOST_MATH_IS_FLOAT(R) && BOOST_MATH_IS_FLOAT(T) && (Policy::value != throw_on_error) && (Policy::value != user_error))
{
   if((val != 0) && (static_cast<R>(val) == 0))
   {
      *result = static_cast<R>(boost::math::policies::detail::raise_underflow_error<R>(function, 0, pol));
      return true;
   }
   return false;
}
template <class R, class T, class Policy>
inline bool check_underflow(std::complex<T> val, R* result, const char* function, const Policy& pol) noexcept(BOOST_MATH_IS_FLOAT(R) && BOOST_MATH_IS_FLOAT(T) && (Policy::value != throw_on_error) && (Policy::value != user_error))
{
   typedef typename R::value_type r_type;
   r_type re, im;
   bool r = check_underflow<r_type>(val.real(), &re, function, pol);
   r = check_underflow<r_type>(val.imag(), &im, function, pol) || r;
   *result = R(re, im);
   return r;
}
template <class R, class T, class Policy>
inline bool check_denorm(T val, R* result, const char* function, const Policy& pol) noexcept(BOOST_MATH_IS_FLOAT(R) && BOOST_MATH_IS_FLOAT(T) && (Policy::value != throw_on_error) && (Policy::value != user_error))
{
   BOOST_MATH_STD_USING
   if((fabs(val) < static_cast<T>(tools::min_value<R>())) && (static_cast<R>(val) != 0))
   {
      *result = static_cast<R>(boost::math::policies::detail::raise_denorm_error<R>(function, 0, static_cast<R>(val), pol));
      return true;
   }
   return false;
}
template <class R, class T, class Policy>
inline bool check_denorm(std::complex<T> val, R* result, const char* function, const Policy& pol) noexcept(BOOST_MATH_IS_FLOAT(R) && BOOST_MATH_IS_FLOAT(T) && (Policy::value != throw_on_error) && (Policy::value != user_error))
{
   typedef typename R::value_type r_type;
   r_type re, im;
   bool r = check_denorm<r_type>(val.real(), &re, function, pol);
   r = check_denorm<r_type>(val.imag(), &im, function, pol) || r;
   *result = R(re, im);
   return r;
}

// Default instantiations with ignore_error policy.
template <class R, class T>
inline constexpr bool check_overflow(T /* val */, R* /* result */, const char* /* function */, const overflow_error<ignore_error>&) noexcept(BOOST_MATH_IS_FLOAT(R) && BOOST_MATH_IS_FLOAT(T)) 
{ return false; }
template <class R, class T>
inline constexpr bool check_overflow(std::complex<T> /* val */, R* /* result */, const char* /* function */, const overflow_error<ignore_error>&) noexcept(BOOST_MATH_IS_FLOAT(R) && BOOST_MATH_IS_FLOAT(T)) 
{ return false; }
template <class R, class T>
inline constexpr bool check_underflow(T /* val */, R* /* result */, const char* /* function */, const underflow_error<ignore_error>&) noexcept(BOOST_MATH_IS_FLOAT(R) && BOOST_MATH_IS_FLOAT(T)) 
{ return false; }
template <class R, class T>
inline constexpr bool check_underflow(std::complex<T> /* val */, R* /* result */, const char* /* function */, const underflow_error<ignore_error>&) noexcept(BOOST_MATH_IS_FLOAT(R) && BOOST_MATH_IS_FLOAT(T)) 
{ return false; }
template <class R, class T>
inline constexpr bool check_denorm(T /* val */, R* /* result*/, const char* /* function */, const denorm_error<ignore_error>&) noexcept(BOOST_MATH_IS_FLOAT(R) && BOOST_MATH_IS_FLOAT(T)) 
{ return false; }
template <class R, class T>
inline constexpr bool check_denorm(std::complex<T> /* val */, R* /* result*/, const char* /* function */, const denorm_error<ignore_error>&) noexcept(BOOST_MATH_IS_FLOAT(R) && BOOST_MATH_IS_FLOAT(T)) 
{ return false; }

} // namespace detail

template <class R, class Policy, class T>
inline R checked_narrowing_cast(T val, const char* function) noexcept(BOOST_MATH_IS_FLOAT(R) && BOOST_MATH_IS_FLOAT(T) && is_noexcept_error_policy<Policy>::value)
{
   typedef typename Policy::overflow_error_type overflow_type;
   typedef typename Policy::underflow_error_type underflow_type;
   typedef typename Policy::denorm_error_type denorm_type;
   //
   // Most of what follows will evaluate to a no-op:
   //
   R result = 0;
   if(detail::check_overflow<R>(val, &result, function, overflow_type()))
      return result;
   if(detail::check_underflow<R>(val, &result, function, underflow_type()))
      return result;
   if(detail::check_denorm<R>(val, &result, function, denorm_type()))
      return result;

   return static_cast<R>(val);
}

template <class T, class Policy>
inline void check_series_iterations(const char* function, std::uintmax_t max_iter, const Policy& pol) noexcept(BOOST_MATH_IS_FLOAT(T) && is_noexcept_error_policy<Policy>::value)
{
   if(max_iter >= policies::get_max_series_iterations<Policy>())
      raise_evaluation_error<T>(
         function,
         "Series evaluation exceeded %1% iterations, giving up now.", static_cast<T>(static_cast<double>(max_iter)), pol);
}

template <class T, class Policy>
inline void check_root_iterations(const char* function, std::uintmax_t max_iter, const Policy& pol) noexcept(BOOST_MATH_IS_FLOAT(T) && is_noexcept_error_policy<Policy>::value)
{
   if(max_iter >= policies::get_max_root_iterations<Policy>())
      raise_evaluation_error<T>(
         function,
         "Root finding evaluation exceeded %1% iterations, giving up now.", static_cast<T>(static_cast<double>(max_iter)), pol);
}

} //namespace policies

namespace detail{

//
// Simple helper function to assist in returning a pair from a single value,
// that value usually comes from one of the error handlers above:
//
template <class T>
std::pair<T, T> pair_from_single(const T& val) BOOST_MATH_NOEXCEPT(T)
{
   return std::make_pair(val, val);
}

}

#ifdef _MSC_VER
#  pragma warning(pop)
#endif

}} // namespaces boost/math

#endif // BOOST_MATH_POLICY_ERROR_HANDLING_HPP


/* error_handling.hpp
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
*/