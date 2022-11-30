///////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MATH_CONCEPTS_ER_HPP
#define BOOST_MATH_CONCEPTS_ER_HPP

#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <tuple>
#include <functional>
#include <boost/multiprecision/detail/standalone_config.hpp>
#include <boost/multiprecision/number.hpp>
#include <boost/multiprecision/detail/no_exceptions_support.hpp>
#include <boost/multiprecision/detail/fpclassify.hpp>

namespace boost {
namespace multiprecision {
namespace concepts {

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 4244)
#endif

struct number_backend_float_architype
{
   using signed_types = std::tuple<long long> ;
   using unsigned_types = std::tuple<unsigned long long>;
   using float_types = std::tuple<long double>;
   using exponent_type = int;

   number_backend_float_architype()
   {
      m_value = 0;
      std::cout << "Default construct" << std::endl;
   }
   number_backend_float_architype(const number_backend_float_architype& o)
   {
      std::cout << "Copy construct" << std::endl;
      m_value = o.m_value;
   }
   number_backend_float_architype& operator=(const number_backend_float_architype& o)
   {
      m_value = o.m_value;
      std::cout << "Assignment (" << m_value << ")" << std::endl;
      return *this;
   }
   number_backend_float_architype& operator=(unsigned long long i)
   {
      m_value = i;
      std::cout << "UInt Assignment (" << i << ")" << std::endl;
      return *this;
   }
   number_backend_float_architype& operator=(long long i)
   {
      m_value = i;
      std::cout << "Int Assignment (" << i << ")" << std::endl;
      return *this;
   }
   number_backend_float_architype& operator=(long double d)
   {
      m_value = d;
      std::cout << "long double Assignment (" << d << ")" << std::endl;
      return *this;
   }
   number_backend_float_architype& operator=(const char* s)
   {
#ifndef BOOST_NO_EXCEPTIONS
      try
      {
#endif
         #ifndef BOOST_MP_STANDALONE
         m_value = boost::lexical_cast<long double>(s);
         #else
         m_value = std::strtold(s, nullptr);

         if(m_value == HUGE_VALL || m_value == 0)
         {
            BOOST_MP_THROW_EXCEPTION(std::runtime_error("Value can not be assigned in standalone mode. Please disable and try again."));
         }
         #endif
#ifndef BOOST_NO_EXCEPTIONS
      }
      catch (const std::exception&)
      {
         BOOST_MP_THROW_EXCEPTION(std::runtime_error(std::string("Unable to parse input string: \"") + s + std::string("\" as a valid floating point number.")));
      }
#endif
      std::cout << "const char* Assignment (" << s << ")" << std::endl;
      return *this;
   }
   void swap(number_backend_float_architype& o)
   {
      std::cout << "Swapping (" << m_value << " with " << o.m_value << ")" << std::endl;
      std::swap(m_value, o.m_value);
   }
   std::string str(std::streamsize digits, std::ios_base::fmtflags f) const
   {
      std::stringstream ss;
      ss.flags(f);
      if (digits)
         ss.precision(digits);
      else
         ss.precision(std::numeric_limits<long double>::digits10 + 3);
      std::intmax_t  i = m_value;
      std::uintmax_t u = m_value;
      if (!(f & std::ios_base::scientific) && m_value == i)
         ss << i;
      else if (!(f & std::ios_base::scientific) && m_value == u)
         ss << u;
      else
         ss << m_value;
      std::string s = ss.str();
      std::cout << "Converting to string (" << s << ")" << std::endl;
      return s;
   }
   void negate()
   {
      std::cout << "Negating (" << m_value << ")" << std::endl;
      m_value = -m_value;
   }
   int compare(const number_backend_float_architype& o) const
   {
      std::cout << "Comparison" << std::endl;
      return m_value > o.m_value ? 1 : (m_value < o.m_value ? -1 : 0);
   }
   int compare(long long i) const
   {
      std::cout << "Comparison with int" << std::endl;
      return m_value > i ? 1 : (m_value < i ? -1 : 0);
   }
   int compare(unsigned long long i) const
   {
      std::cout << "Comparison with unsigned" << std::endl;
      return m_value > i ? 1 : (m_value < i ? -1 : 0);
   }
   int compare(long double d) const
   {
      std::cout << "Comparison with long double" << std::endl;
      return m_value > d ? 1 : (m_value < d ? -1 : 0);
   }
   long double m_value;
};

inline void eval_add(number_backend_float_architype& result, const number_backend_float_architype& o)
{
   std::cout << "Addition (" << result.m_value << " += " << o.m_value << ")" << std::endl;
   result.m_value += o.m_value;
}
inline void eval_subtract(number_backend_float_architype& result, const number_backend_float_architype& o)
{
   std::cout << "Subtraction (" << result.m_value << " -= " << o.m_value << ")" << std::endl;
   result.m_value -= o.m_value;
}
inline void eval_multiply(number_backend_float_architype& result, const number_backend_float_architype& o)
{
   std::cout << "Multiplication (" << result.m_value << " *= " << o.m_value << ")" << std::endl;
   result.m_value *= o.m_value;
}
inline void eval_divide(number_backend_float_architype& result, const number_backend_float_architype& o)
{
   std::cout << "Division (" << result.m_value << " /= " << o.m_value << ")" << std::endl;
   result.m_value /= o.m_value;
}

inline void eval_convert_to(unsigned long long* result, const number_backend_float_architype& val)
{
   *result = static_cast<unsigned long long>(val.m_value);
}
inline void eval_convert_to(long long* result, const number_backend_float_architype& val)
{
   *result = static_cast<long long>(val.m_value);
}
inline void eval_convert_to(long double* result, number_backend_float_architype& val)
{
   *result = val.m_value;
}

inline void eval_frexp(number_backend_float_architype& result, const number_backend_float_architype& arg, int* exp)
{
   result = std::frexp(arg.m_value, exp);
}

inline void eval_ldexp(number_backend_float_architype& result, const number_backend_float_architype& arg, int exp)
{
   result = std::ldexp(arg.m_value, exp);
}

inline void eval_floor(number_backend_float_architype& result, const number_backend_float_architype& arg)
{
   result = std::floor(arg.m_value);
}

inline void eval_ceil(number_backend_float_architype& result, const number_backend_float_architype& arg)
{
   result = std::ceil(arg.m_value);
}

inline void eval_sqrt(number_backend_float_architype& result, const number_backend_float_architype& arg)
{
   result = std::sqrt(arg.m_value);
}

inline int eval_fpclassify(const number_backend_float_architype& arg)
{
   return BOOST_MP_FPCLASSIFY(arg.m_value);
}

inline std::size_t hash_value(const number_backend_float_architype& v)
{
   std::hash<long double> hasher;
   return hasher(v.m_value);
}

using mp_number_float_architype = boost::multiprecision::number<number_backend_float_architype>;

} // namespace concepts

template <>
struct number_category<concepts::number_backend_float_architype> : public std::integral_constant<int, number_kind_floating_point>
{};

}} // namespace boost::multiprecision

namespace std {

template <boost::multiprecision::expression_template_option ExpressionTemplates>
class numeric_limits<boost::multiprecision::number<boost::multiprecision::concepts::number_backend_float_architype, ExpressionTemplates> > : public std::numeric_limits<long double>
{
   using base_type = std::numeric_limits<long double>                                                                                   ;
   using number_type = boost::multiprecision::number<boost::multiprecision::concepts::number_backend_float_architype, ExpressionTemplates>;

 public:
   static number_type(min)() noexcept { return (base_type::min)(); }
   static number_type(max)() noexcept { return (base_type::max)(); }
   static number_type lowest() noexcept { return -(max)(); }
   static number_type epsilon() noexcept { return base_type::epsilon(); }
   static number_type round_error() noexcept { return base_type::round_error(); }
   static number_type infinity() noexcept { return base_type::infinity(); }
   static number_type quiet_NaN() noexcept { return base_type::quiet_NaN(); }
   static number_type signaling_NaN() noexcept { return base_type::signaling_NaN(); }
   static number_type denorm_min() noexcept { return base_type::denorm_min(); }
};

} // namespace std

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif

/* mp_number_archetypes.hpp
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
*/