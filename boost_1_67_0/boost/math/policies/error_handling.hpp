//  Copyright John Maddock 2007.
//  Copyright Paul A. Bristow 2007.

//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_POLICY_ERROR_HANDLING_HPP
#define BOOST_MATH_POLICY_ERROR_HANDLING_HPP

#include <stdexcept>
#include <iomanip>
#include <string>
#include <cstring>
#include <typeinfo>
#include <cerrno>
#include <boost/config/no_tr1/complex.hpp>
#include <boost/config/no_tr1/cmath.hpp>
#include <stdexcept>
#include <boost/math/tools/config.hpp>
#include <boost/math/policies/policy.hpp>
#include <boost/math/tools/precision.hpp>
#include <boost/throw_exception.hpp>
#include <boost/cstdint.hpp>
#ifdef BOOST_MSVC
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
  boost::throw_exception(e);
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
  boost::throw_exception(e);
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
inline BOOST_MATH_CONSTEXPR T raise_domain_error(
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
inline BOOST_MATH_CONSTEXPR T raise_pole_error(
           const char* function,
           const char* message,
           const T& val,
           const  ::boost::math::policies::pole_error< ::boost::math::policies::ignore_error>&) BOOST_MATH_NOEXCEPT(T)
{
   return  ::boost::math::policies::detail::raise_domain_error(function, message, val,  ::boost::math::policies::domain_error< ::boost::math::policies::ignore_error>());
}

template <class T>
inline BOOST_MATH_CONSTEXPR T raise_pole_error(
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
inline BOOST_MATH_CONSTEXPR T raise_overflow_error(
           const char* ,
           const char* ,
           const  ::boost::math::policies::overflow_error< ::boost::math::policies::ignore_error>&) BOOST_MATH_NOEXCEPT(T)
{
   // This may or may not do the right thing, but the user asked for the error
   // to be ignored so here we go anyway:
   return std::numeric_limits<T>::has_infinity ? std::numeric_limits<T>::infinity() : boost::math::tools::max_value<T>();
}

template <class T>
inline BOOST_MATH_CONSTEXPR T raise_overflow_error(
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
inline BOOST_MATH_CONSTEXPR T raise_underflow_error(
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
inline BOOST_MATH_CONSTEXPR T raise_denorm_error(
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
inline BOOST_MATH_CONSTEXPR T raise_evaluation_error(
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
inline BOOST_MATH_CONSTEXPR TargetType raise_rounding_error(
           const char* ,
           const char* ,
           const T& val,
           const TargetType&,
           const  ::boost::math::policies::rounding_error< ::boost::math::policies::ignore_error>&) BOOST_MATH_NOEXCEPT(T)
{
   // This may or may not do the right thing, but the user asked for the error
   // to be ignored so here we go anyway:
   BOOST_STATIC_ASSERT(std::numeric_limits<TargetType>::is_specialized);
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
   BOOST_STATIC_ASSERT(std::numeric_limits<TargetType>::is_specialized);
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
inline BOOST_MATH_CONSTEXPR T raise_indeterminate_result_error(
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
inline BOOST_MATH_CONSTEXPR T raise_domain_error(const char* function, const char* message, const T& val, const Policy&) BOOST_NOEXCEPT_IF(is_noexcept_error_policy<Policy>::value && BOOST_MATH_IS_FLOAT(T))
{
   typedef typename Policy::domain_error_type policy_type;
   return detail::raise_domain_error(
      function, message ? message : "Domain Error evaluating function at %1%",
      val, policy_type());
}

template <class T, class Policy>
inline BOOST_MATH_CONSTEXPR T raise_pole_error(const char* function, const char* message, const T& val, const Policy&) BOOST_NOEXCEPT_IF(is_noexcept_error_policy<Policy>::value && BOOST_MATH_IS_FLOAT(T))
{
   typedef typename Policy::pole_error_type policy_type;
   return detail::raise_pole_error(
      function, message ? message : "Evaluation of function at pole %1%",
      val, policy_type());
}

template <class T, class Policy>
inline BOOST_MATH_CONSTEXPR T raise_overflow_error(const char* function, const char* message, const Policy&) BOOST_NOEXCEPT_IF(is_noexcept_error_policy<Policy>::value && BOOST_MATH_IS_FLOAT(T))
{
   typedef typename Policy::overflow_error_type policy_type;
   return detail::raise_overflow_error<T>(
      function, message ? message : "Overflow Error",
      policy_type());
}

template <class T, class Policy>
inline BOOST_MATH_CONSTEXPR T raise_overflow_error(const char* function, const char* message, const T& val, const Policy&) BOOST_NOEXCEPT_IF(is_noexcept_error_policy<Policy>::value && BOOST_MATH_IS_FLOAT(T))
{
   typedef typename Policy::overflow_error_type policy_type;
   return detail::raise_overflow_error(
      function, message ? message : "Overflow evaluating function at %1%",
      val, policy_type());
}

template <class T, class Policy>
inline BOOST_MATH_CONSTEXPR T raise_underflow_error(const char* function, const char* message, const Policy&) BOOST_NOEXCEPT_IF(is_noexcept_error_policy<Policy>::value && BOOST_MATH_IS_FLOAT(T))
{
   typedef typename Policy::underflow_error_type policy_type;
   return detail::raise_underflow_error<T>(
      function, message ? message : "Underflow Error",
      policy_type());
}

template <class T, class Policy>
inline BOOST_MATH_CONSTEXPR T raise_denorm_error(const char* function, const char* message, const T& val, const Policy&) BOOST_NOEXCEPT_IF(is_noexcept_error_policy<Policy>::value && BOOST_MATH_IS_FLOAT(T))
{
   typedef typename Policy::denorm_error_type policy_type;
   return detail::raise_denorm_error<T>(
      function, message ? message : "Denorm Error",
      val,
      policy_type());
}

template <class T, class Policy>
inline BOOST_MATH_CONSTEXPR T raise_evaluation_error(const char* function, const char* message, const T& val, const Policy&) BOOST_NOEXCEPT_IF(is_noexcept_error_policy<Policy>::value && BOOST_MATH_IS_FLOAT(T))
{
   typedef typename Policy::evaluation_error_type policy_type;
   return detail::raise_evaluation_error(
      function, message ? message : "Internal Evaluation Error, best value so far was %1%",
      val, policy_type());
}

template <class T, class TargetType, class Policy>
inline BOOST_MATH_CONSTEXPR TargetType raise_rounding_error(const char* function, const char* message, const T& val, const TargetType& t, const Policy&) BOOST_NOEXCEPT_IF(is_noexcept_error_policy<Policy>::value && BOOST_MATH_IS_FLOAT(T))
{
   typedef typename Policy::rounding_error_type policy_type;
   return detail::raise_rounding_error(
      function, message ? message : "Value %1% can not be represented in the target integer type.",
      val, t, policy_type());
}

template <class T, class R, class Policy>
inline BOOST_MATH_CONSTEXPR T raise_indeterminate_result_error(const char* function, const char* message, const T& val, const R& result, const Policy&) BOOST_NOEXCEPT_IF(is_noexcept_error_policy<Policy>::value && BOOST_MATH_IS_FLOAT(T))
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
inline bool check_overflow(T val, R* result, const char* function, const Policy& pol) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(R) && BOOST_MATH_IS_FLOAT(T) && (Policy::value != throw_on_error) && (Policy::value != user_error))
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
inline bool check_overflow(std::complex<T> val, R* result, const char* function, const Policy& pol) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(R) && BOOST_MATH_IS_FLOAT(T) && (Policy::value != throw_on_error) && (Policy::value != user_error))
{
   typedef typename R::value_type r_type;
   r_type re, im;
   bool r = check_overflow<r_type>(val.real(), &re, function, pol);
   r = check_overflow<r_type>(val.imag(), &im, function, pol) || r;
   *result = R(re, im);
   return r;
}
template <class R, class T, class Policy>
inline bool check_underflow(T val, R* result, const char* function, const Policy& pol) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(R) && BOOST_MATH_IS_FLOAT(T) && (Policy::value != throw_on_error) && (Policy::value != user_error))
{
   if((val != 0) && (static_cast<R>(val) == 0))
   {
      *result = static_cast<R>(boost::math::policies::detail::raise_underflow_error<R>(function, 0, pol));
      return true;
   }
   return false;
}
template <class R, class T, class Policy>
inline bool check_underflow(std::complex<T> val, R* result, const char* function, const Policy& pol) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(R) && BOOST_MATH_IS_FLOAT(T) && (Policy::value != throw_on_error) && (Policy::value != user_error))
{
   typedef typename R::value_type r_type;
   r_type re, im;
   bool r = check_underflow<r_type>(val.real(), &re, function, pol);
   r = check_underflow<r_type>(val.imag(), &im, function, pol) || r;
   *result = R(re, im);
   return r;
}
template <class R, class T, class Policy>
inline bool check_denorm(T val, R* result, const char* function, const Policy& pol) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(R) && BOOST_MATH_IS_FLOAT(T) && (Policy::value != throw_on_error) && (Policy::value != user_error))
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
inline bool check_denorm(std::complex<T> val, R* result, const char* function, const Policy& pol) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(R) && BOOST_MATH_IS_FLOAT(T) && (Policy::value != throw_on_error) && (Policy::value != user_error))
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
inline BOOST_MATH_CONSTEXPR bool check_overflow(T /* val */, R* /* result */, const char* /* function */, const overflow_error<ignore_error>&) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(R) && BOOST_MATH_IS_FLOAT(T)) 
{ return false; }
template <class R, class T>
inline BOOST_MATH_CONSTEXPR bool check_overflow(std::complex<T> /* val */, R* /* result */, const char* /* function */, const overflow_error<ignore_error>&) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(R) && BOOST_MATH_IS_FLOAT(T)) 
{ return false; }
template <class R, class T>
inline BOOST_MATH_CONSTEXPR bool check_underflow(T /* val */, R* /* result */, const char* /* function */, const underflow_error<ignore_error>&) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(R) && BOOST_MATH_IS_FLOAT(T)) 
{ return false; }
template <class R, class T>
inline BOOST_MATH_CONSTEXPR bool check_underflow(std::complex<T> /* val */, R* /* result */, const char* /* function */, const underflow_error<ignore_error>&) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(R) && BOOST_MATH_IS_FLOAT(T)) 
{ return false; }
template <class R, class T>
inline BOOST_MATH_CONSTEXPR bool check_denorm(T /* val */, R* /* result*/, const char* /* function */, const denorm_error<ignore_error>&) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(R) && BOOST_MATH_IS_FLOAT(T)) 
{ return false; }
template <class R, class T>
inline BOOST_MATH_CONSTEXPR bool check_denorm(std::complex<T> /* val */, R* /* result*/, const char* /* function */, const denorm_error<ignore_error>&) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(R) && BOOST_MATH_IS_FLOAT(T)) 
{ return false; }

} // namespace detail

template <class R, class Policy, class T>
inline R checked_narrowing_cast(T val, const char* function) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(R) && BOOST_MATH_IS_FLOAT(T) && is_noexcept_error_policy<Policy>::value)
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
inline void check_series_iterations(const char* function, boost::uintmax_t max_iter, const Policy& pol) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(T) && is_noexcept_error_policy<Policy>::value)
{
   if(max_iter >= policies::get_max_series_iterations<Policy>())
      raise_evaluation_error<T>(
         function,
         "Series evaluation exceeded %1% iterations, giving up now.", static_cast<T>(static_cast<double>(max_iter)), pol);
}

template <class T, class Policy>
inline void check_root_iterations(const char* function, boost::uintmax_t max_iter, const Policy& pol) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(T) && is_noexcept_error_policy<Policy>::value)
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

#ifdef BOOST_MSVC
#  pragma warning(pop)
#endif

}} // namespaces boost/math

#endif // BOOST_MATH_POLICY_ERROR_HANDLING_HPP


/* error_handling.hpp
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
*/