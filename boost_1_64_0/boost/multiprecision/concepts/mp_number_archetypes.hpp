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
kzkKVaC2yDZGVgPrcbkLA1XBHEG7bbqZZ+aVAiPXAlkHpN3SaLJs9Kd+8h5FgzKR5/Pa72ZZB++MtJlKFob1IDR6fr1FaMsDXeaz7qLTaD9/VNLIGmT088PuamPMfn59B0bv5717bbqoCrEHlxgcjsaYu2bR6ZiL72bS6Zj7OKFjBZC+/+6CDgb6usO21g9vR7o139Ud8x6IMeagKufziNHGv37v3Yd0Mi71++WNIRhp7ouylu45BHdmHcfHbxDTjEkyT+9FaUI+Gf8GXZe7cm9Cm6l0fwWTZtgpr+836CCY6JWRTseUXvfz95EYusQp/4L7dtCbeiDmlV0YqItezsT9BGb56OKQcfMypA8fNxMHEDN03LwSMd3jZvz+SB86bl5GMMPHzcQDEDd03FxEjD1uxh+ItM5xc8Gg63L/hjR73AwOIq1z3NxCeve4WXkQ0oeOm98gpnvcLD0Y6UPHzc0ujKzLfTEnlsAM+vXjvYwJhLE0Dmk08sio7irf1PNK19lSPemQMdPoKNmUutfoWN6bf17PxuIbnI5NVgEGCo0XmgzO6uLM+vKqJ3ye2LSuz72u8/vCJ8wuTL9z3TDzaG9ubIB93eySyLmRLDJIfr38gPYdRMfOrvQdkQYLEA9u71kGHcQ9UeiKoMT5FnPLwMxIDLRipi3njwYm3OgJGT3MJfEl/U6SscDPU99Nbz/PCjSOyRhQLowVnsAYCSBt8VOa3Cs+/FadnOVz3slkNvEcDguGNyu8lvzAPRXV+Q3CYRgZRxrII97Jp1Sz5dxsLPIjz/ESUEBreHllM3bzwXIm63p3RSsLLxB6WByL85SrjaYBGi8ai/LpozZW2GbNi7v/otLtXrdxjYtgMz4Aq2Q+eawTa5V9zcYJK0UJVLjBNhsnlOXyyKH048NwcLQg6+64jRPDuwZruD3bO3Cbq3ONZ5zCXenA9bG9ah1a3GHjNldFoUrWzQ5Mk/m5weGefCeFk8m4hTYU33FX9Hfc5/bXQNH9xHY+PXZMo53rQf4ukY9GzacJYz7FoN4r4yC53fkkMigymS+8BwNYpcBxvEzokeD31wjduLe2AavRABy6YS0CbdNMb35jYWkGKus1QzDcXK3XKJqHaBElgo54sddbr9OXaPehUQsj1j115xrrpM+tDzbUudDCbJJzxuw2Spe5etTdr4sOjl7k/jxOMXI8I/2zJl0mGcK+2G7SwV26tuZWMg7toBg5F1DGZYuO6nqUsfdOJmbzHDnbmfT1NbLP3+ygm229OEExUu2vdBk7KV1MMH0OXuqgi+jbtY2EJmdyl4lbWj4zUPRLFl1MHe29aTelwwSWEjQZJka+kODdZo9Bf2FvY007i7ysptf+VRDRpBlZRXvO+CKdm6Wb5KBLvW2f9/7G+uOParriv91zmxZ3o3CDwnO9RPh7ZmiHdy/QO70K5vHe2vbk9Imp2mGh2RtfA79DC2ZOVk2S4/XnL6rEP3Lve53CnC0w1VDD/zabX8to1GDeTfmFO52SIteZ9wJGF9LyXrblS15Vvw8S+Vh6zf9Ru2zSvrsA5mOAaQCNvE9SHkSLPfvNEvtE15kJZN0/hfxNAW3dP2uXjbUjcQHE4q2kou5MxYygdNiLj4Avfd0hxHd/zMIhDO/tBmZ5leo3psYJnejePippaOhaW0ctg3RV15E7DcHMuYV+Xp+dAJzsNVP/8VmNhq4PGv3CTo2+vjK/AIlfVzX6YBfSewPA1LnqtDV1325Jp0MW+S/adNENKraFTe/XBY0ozMU9nRhQ/yvMoTt3YvrP02J3/HEYRvbnvdry7iJwYqmpgcg/eVf4/Tbyw73dwnXn83jYXsB1jmot10gXBjPsKdw=
*/