///////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MATH_CONCEPTS_ER_HPP
#define BOOST_MATH_CONCEPTS_ER_HPP

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <boost/cstdint.hpp>
#include <boost/multiprecision/number.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/mpl/list.hpp>
#include <boost/container_hash/hash.hpp>

namespace boost {
namespace multiprecision {
namespace concepts {

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 4244)
#endif

struct number_backend_float_architype
{
   typedef mpl::list<boost::long_long_type>  signed_types;
   typedef mpl::list<boost::ulong_long_type> unsigned_types;
   typedef mpl::list<long double>            float_types;
   typedef int                               exponent_type;

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
   number_backend_float_architype& operator=(boost::ulong_long_type i)
   {
      m_value = i;
      std::cout << "UInt Assignment (" << i << ")" << std::endl;
      return *this;
   }
   number_backend_float_architype& operator=(boost::long_long_type i)
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
         m_value = boost::lexical_cast<long double>(s);
#ifndef BOOST_NO_EXCEPTIONS
      }
      catch (const std::exception&)
      {
         BOOST_THROW_EXCEPTION(std::runtime_error(std::string("Unable to parse input string: \"") + s + std::string("\" as a valid floating point number.")));
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
      boost::intmax_t  i = m_value;
      boost::uintmax_t u = m_value;
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
   int compare(boost::long_long_type i) const
   {
      std::cout << "Comparison with int" << std::endl;
      return m_value > i ? 1 : (m_value < i ? -1 : 0);
   }
   int compare(boost::ulong_long_type i) const
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

inline void eval_convert_to(boost::ulong_long_type* result, const number_backend_float_architype& val)
{
   *result = static_cast<boost::ulong_long_type>(val.m_value);
}
inline void eval_convert_to(boost::long_long_type* result, const number_backend_float_architype& val)
{
   *result = static_cast<boost::long_long_type>(val.m_value);
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
   return (boost::math::fpclassify)(arg.m_value);
}

inline std::size_t hash_value(const number_backend_float_architype& v)
{
   boost::hash<long double> hasher;
   return hasher(v.m_value);
}

typedef boost::multiprecision::number<number_backend_float_architype> mp_number_float_architype;

} // namespace concepts

template <>
struct number_category<concepts::number_backend_float_architype> : public mpl::int_<number_kind_floating_point>
{};

}} // namespace boost::multiprecision

namespace std {

template <boost::multiprecision::expression_template_option ExpressionTemplates>
class numeric_limits<boost::multiprecision::number<boost::multiprecision::concepts::number_backend_float_architype, ExpressionTemplates> > : public std::numeric_limits<long double>
{
   typedef std::numeric_limits<long double>                                                                                    base_type;
   typedef boost::multiprecision::number<boost::multiprecision::concepts::number_backend_float_architype, ExpressionTemplates> number_type;

 public:
   static number_type(min)() BOOST_NOEXCEPT { return (base_type::min)(); }
   static number_type(max)() BOOST_NOEXCEPT { return (base_type::max)(); }
   static number_type lowest() BOOST_NOEXCEPT { return -(max)(); }
   static number_type epsilon() BOOST_NOEXCEPT { return base_type::epsilon(); }
   static number_type round_error() BOOST_NOEXCEPT { return base_type::round_error(); }
   static number_type infinity() BOOST_NOEXCEPT { return base_type::infinity(); }
   static number_type quiet_NaN() BOOST_NOEXCEPT { return base_type::quiet_NaN(); }
   static number_type signaling_NaN() BOOST_NOEXCEPT { return base_type::signaling_NaN(); }
   static number_type denorm_min() BOOST_NOEXCEPT { return base_type::denorm_min(); }
};

} // namespace std

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif

/* mp_number_archetypes.hpp
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
*/