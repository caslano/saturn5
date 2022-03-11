///////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MATH_DEBUG_ADAPTER_HPP
#define BOOST_MATH_DEBUG_ADAPTER_HPP

#include <boost/multiprecision/traits/extract_exponent_type.hpp>
#include <boost/multiprecision/detail/integer_ops.hpp>

namespace boost {
namespace multiprecision {
namespace backends {

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 4127) // conditional expression is constant
#endif

template <class Backend>
struct debug_adaptor
{
   typedef typename Backend::signed_types   signed_types;
   typedef typename Backend::unsigned_types unsigned_types;
   typedef typename Backend::float_types    float_types;
   typedef typename extract_exponent_type<
       Backend, number_category<Backend>::value>::type exponent_type;

 private:
   std::string debug_value;
   Backend     m_value;

 public:
   void update_view()
   {
#ifndef BOOST_NO_EXCEPTIONS
      try
      {
#endif
         debug_value = m_value.str(0, static_cast<std::ios_base::fmtflags>(0));
#ifndef BOOST_NO_EXCEPTIONS
      }
      catch (const std::exception& e)
      {
         debug_value = "String conversion failed with message: \"";
         debug_value += e.what();
         debug_value += "\"";
      }
#endif
   }
   debug_adaptor()
   {
      update_view();
   }
   debug_adaptor(const debug_adaptor& o) : debug_value(o.debug_value), m_value(o.m_value)
   {
   }
   debug_adaptor& operator=(const debug_adaptor& o)
   {
      debug_value = o.debug_value;
      m_value     = o.m_value;
      return *this;
   }
   template <class T>
   debug_adaptor(const T& i, const typename enable_if_c<is_convertible<T, Backend>::value>::type* = 0)
       : m_value(i)
   {
      update_view();
   }
   template <class T>
   debug_adaptor(const T& i, const T& j)
       : m_value(i, j)
   {
      update_view();
   }
   template <class T>
   typename enable_if_c<is_arithmetic<T>::value || is_convertible<T, Backend>::value, debug_adaptor&>::type operator=(const T& i)
   {
      m_value = i;
      update_view();
      return *this;
   }
   debug_adaptor& operator=(const char* s)
   {
      m_value = s;
      update_view();
      return *this;
   }
   void swap(debug_adaptor& o)
   {
      std::swap(m_value, o.value());
      std::swap(debug_value, o.debug_value);
   }
   std::string str(std::streamsize digits, std::ios_base::fmtflags f) const
   {
      return m_value.str(digits, f);
   }
   void negate()
   {
      m_value.negate();
      update_view();
   }
   int compare(const debug_adaptor& o) const
   {
      return m_value.compare(o.value());
   }
   template <class T>
   int compare(const T& i) const
   {
      return m_value.compare(i);
   }
   Backend& value()
   {
      return m_value;
   }
   const Backend& value() const
   {
      return m_value;
   }
   template <class Archive>
   void serialize(Archive& ar, const unsigned int /*version*/)
   {
      ar & boost::make_nvp("value", m_value);
      typedef typename Archive::is_loading tag;
      if (tag::value)
         update_view();
   }
   static unsigned default_precision() BOOST_NOEXCEPT
   {
      return Backend::default_precision();
   }
   static void default_precision(unsigned v) BOOST_NOEXCEPT
   {
      Backend::default_precision(v);
   }
   unsigned precision() const BOOST_NOEXCEPT
   {
      return value().precision();
   }
   void precision(unsigned digits10) BOOST_NOEXCEPT
   {
      value().precision(digits10);
   }
};

template <class Backend>
inline Backend const& unwrap_debug_type(debug_adaptor<Backend> const& val)
{
   return val.value();
}
template <class T>
inline const T& unwrap_debug_type(const T& val)
{
   return val;
}

#define NON_MEMBER_OP1(name, str)                                       \
   template <class Backend>                                             \
   inline void BOOST_JOIN(eval_, name)(debug_adaptor<Backend> & result) \
   {                                                                    \
      using default_ops::BOOST_JOIN(eval_, name);                       \
      BOOST_JOIN(eval_, name)                                           \
      (result.value());                                                 \
      result.update_view();                                             \
   }

#define NON_MEMBER_OP2(name, str)                                                                        \
   template <class Backend, class T>                                                                     \
   inline void BOOST_JOIN(eval_, name)(debug_adaptor<Backend> & result, const T& a)                      \
   {                                                                                                     \
      using default_ops::BOOST_JOIN(eval_, name);                                                        \
      BOOST_JOIN(eval_, name)                                                                            \
      (result.value(), unwrap_debug_type(a));                                                            \
      result.update_view();                                                                              \
   }                                                                                                     \
   template <class Backend>                                                                              \
   inline void BOOST_JOIN(eval_, name)(debug_adaptor<Backend> & result, const debug_adaptor<Backend>& a) \
   {                                                                                                     \
      using default_ops::BOOST_JOIN(eval_, name);                                                        \
      BOOST_JOIN(eval_, name)                                                                            \
      (result.value(), unwrap_debug_type(a));                                                            \
      result.update_view();                                                                              \
   }

#define NON_MEMBER_OP3(name, str)                                                                                                         \
   template <class Backend, class T, class U>                                                                                             \
   inline void BOOST_JOIN(eval_, name)(debug_adaptor<Backend> & result, const T& a, const U& b)                                           \
   {                                                                                                                                      \
      using default_ops::BOOST_JOIN(eval_, name);                                                                                         \
      BOOST_JOIN(eval_, name)                                                                                                             \
      (result.value(), unwrap_debug_type(a), unwrap_debug_type(b));                                                                       \
      result.update_view();                                                                                                               \
   }                                                                                                                                      \
   template <class Backend, class T>                                                                                                      \
   inline void BOOST_JOIN(eval_, name)(debug_adaptor<Backend> & result, const debug_adaptor<Backend>& a, const T& b)                      \
   {                                                                                                                                      \
      using default_ops::BOOST_JOIN(eval_, name);                                                                                         \
      BOOST_JOIN(eval_, name)                                                                                                             \
      (result.value(), unwrap_debug_type(a), unwrap_debug_type(b));                                                                       \
      result.update_view();                                                                                                               \
   }                                                                                                                                      \
   template <class Backend, class T>                                                                                                      \
   inline void BOOST_JOIN(eval_, name)(debug_adaptor<Backend> & result, const T& a, const debug_adaptor<Backend>& b)                      \
   {                                                                                                                                      \
      using default_ops::BOOST_JOIN(eval_, name);                                                                                         \
      BOOST_JOIN(eval_, name)                                                                                                             \
      (result.value(), unwrap_debug_type(a), unwrap_debug_type(b));                                                                       \
      result.update_view();                                                                                                               \
   }                                                                                                                                      \
   template <class Backend>                                                                                                               \
   inline void BOOST_JOIN(eval_, name)(debug_adaptor<Backend> & result, const debug_adaptor<Backend>& a, const debug_adaptor<Backend>& b) \
   {                                                                                                                                      \
      using default_ops::BOOST_JOIN(eval_, name);                                                                                         \
      BOOST_JOIN(eval_, name)                                                                                                             \
      (result.value(), unwrap_debug_type(a), unwrap_debug_type(b));                                                                       \
      result.update_view();                                                                                                               \
   }

#define NON_MEMBER_OP4(name, str)                                                                                                                                          \
   template <class Backend, class T, class U, class V>                                                                                                                     \
   inline void BOOST_JOIN(eval_, name)(debug_adaptor<Backend> & result, const T& a, const U& b, const V& c)                                                                \
   {                                                                                                                                                                       \
      using default_ops::BOOST_JOIN(eval_, name);                                                                                                                          \
      BOOST_JOIN(eval_, name)                                                                                                                                              \
      (result.value(), unwrap_debug_type(a), unwrap_debug_type(b), unwrap_debug_type(c));                                                                                  \
      result.update_view();                                                                                                                                                \
   }                                                                                                                                                                       \
   template <class Backend, class T>                                                                                                                                       \
   inline void BOOST_JOIN(eval_, name)(debug_adaptor<Backend> & result, const debug_adaptor<Backend>& a, const debug_adaptor<Backend>& b, const T& c)                      \
   {                                                                                                                                                                       \
      using default_ops::BOOST_JOIN(eval_, name);                                                                                                                          \
      BOOST_JOIN(eval_, name)                                                                                                                                              \
      (result.value(), unwrap_debug_type(a), unwrap_debug_type(b), unwrap_debug_type(c));                                                                                  \
      result.update_view();                                                                                                                                                \
   }                                                                                                                                                                       \
   template <class Backend, class T>                                                                                                                                       \
   inline void BOOST_JOIN(eval_, name)(debug_adaptor<Backend> & result, const debug_adaptor<Backend>& a, const T& b, const debug_adaptor<Backend>& c)                      \
   {                                                                                                                                                                       \
      using default_ops::BOOST_JOIN(eval_, name);                                                                                                                          \
      BOOST_JOIN(eval_, name)                                                                                                                                              \
      (result.value(), unwrap_debug_type(a), unwrap_debug_type(b), unwrap_debug_type(c));                                                                                  \
      result.update_view();                                                                                                                                                \
   }                                                                                                                                                                       \
   template <class Backend, class T>                                                                                                                                       \
   inline void BOOST_JOIN(eval_, name)(debug_adaptor<Backend> & result, const T& a, const debug_adaptor<Backend>& b, const debug_adaptor<Backend>& c)                      \
   {                                                                                                                                                                       \
      using default_ops::BOOST_JOIN(eval_, name);                                                                                                                          \
      BOOST_JOIN(eval_, name)                                                                                                                                              \
      (result.value(), unwrap_debug_type(a), unwrap_debug_type(b), unwrap_debug_type(c));                                                                                  \
      result.update_view();                                                                                                                                                \
   }                                                                                                                                                                       \
   template <class Backend>                                                                                                                                                \
   inline void BOOST_JOIN(eval_, name)(debug_adaptor<Backend> & result, const debug_adaptor<Backend>& a, const debug_adaptor<Backend>& b, const debug_adaptor<Backend>& c) \
   {                                                                                                                                                                       \
      using default_ops::BOOST_JOIN(eval_, name);                                                                                                                          \
      BOOST_JOIN(eval_, name)                                                                                                                                              \
      (result.value(), unwrap_debug_type(a), unwrap_debug_type(b), unwrap_debug_type(c));                                                                                  \
      result.update_view();                                                                                                                                                \
   }                                                                                                                                                                       \
   template <class Backend, class T, class U>                                                                                                                              \
   inline void BOOST_JOIN(eval_, name)(debug_adaptor<Backend> & result, const debug_adaptor<Backend>& a, const T& b, const U& c)                                           \
   {                                                                                                                                                                       \
      using default_ops::BOOST_JOIN(eval_, name);                                                                                                                          \
      BOOST_JOIN(eval_, name)                                                                                                                                              \
      (result.value(), unwrap_debug_type(a), unwrap_debug_type(b), unwrap_debug_type(c));                                                                                  \
      result.update_view();                                                                                                                                                \
   }

NON_MEMBER_OP2(add, "+=")
NON_MEMBER_OP2(subtract, "-=")
NON_MEMBER_OP2(multiply, "*=")
NON_MEMBER_OP2(divide, "/=")

template <class Backend, class R>
inline void eval_convert_to(R* result, const debug_adaptor<Backend>& val)
{
   using default_ops::eval_convert_to;
   eval_convert_to(result, val.value());
}

template <class Backend, class Exp>
inline void eval_frexp(debug_adaptor<Backend>& result, const debug_adaptor<Backend>& arg, Exp* exp)
{
   eval_frexp(result.value(), arg.value(), exp);
   result.update_view();
}

template <class Backend, class Exp>
inline void eval_ldexp(debug_adaptor<Backend>& result, const debug_adaptor<Backend>& arg, Exp exp)
{
   eval_ldexp(result.value(), arg.value(), exp);
   result.update_view();
}

template <class Backend, class Exp>
inline void eval_scalbn(debug_adaptor<Backend>& result, const debug_adaptor<Backend>& arg, Exp exp)
{
   using default_ops::eval_scalbn;
   eval_scalbn(result.value(), arg.value(), exp);
   result.update_view();
}

template <class Backend>
inline typename Backend::exponent_type eval_ilogb(const debug_adaptor<Backend>& arg)
{
   using default_ops::eval_ilogb;
   return eval_ilogb(arg.value());
}

NON_MEMBER_OP2(floor, "floor")
NON_MEMBER_OP2(ceil, "ceil")
NON_MEMBER_OP2(sqrt, "sqrt")
NON_MEMBER_OP2(logb, "logb")

template <class Backend>
inline int eval_fpclassify(const debug_adaptor<Backend>& arg)
{
   using default_ops::eval_fpclassify;
   return eval_fpclassify(arg.value());
}

/*********************************************************************
*
* Optional arithmetic operations come next:
*
*********************************************************************/

NON_MEMBER_OP3(add, "+")
NON_MEMBER_OP3(subtract, "-")
NON_MEMBER_OP3(multiply, "*")
NON_MEMBER_OP3(divide, "/")
NON_MEMBER_OP3(multiply_add, "fused-multiply-add")
NON_MEMBER_OP3(multiply_subtract, "fused-multiply-subtract")
NON_MEMBER_OP4(multiply_add, "fused-multiply-add")
NON_MEMBER_OP4(multiply_subtract, "fused-multiply-subtract")

NON_MEMBER_OP1(increment, "increment")
NON_MEMBER_OP1(decrement, "decrement")

/*********************************************************************
*
* Optional integer operations come next:
*
*********************************************************************/

NON_MEMBER_OP2(modulus, "%=")
NON_MEMBER_OP3(modulus, "%")
NON_MEMBER_OP2(bitwise_or, "|=")
NON_MEMBER_OP3(bitwise_or, "|")
NON_MEMBER_OP2(bitwise_and, "&=")
NON_MEMBER_OP3(bitwise_and, "&")
NON_MEMBER_OP2(bitwise_xor, "^=")
NON_MEMBER_OP3(bitwise_xor, "^")
NON_MEMBER_OP4(qr, "quotient-and-remainder")
NON_MEMBER_OP2(complement, "~")

template <class Backend>
inline void eval_left_shift(debug_adaptor<Backend>& arg, std::size_t a)
{
   using default_ops::eval_left_shift;
   eval_left_shift(arg.value(), a);
   arg.update_view();
}
template <class Backend>
inline void eval_left_shift(debug_adaptor<Backend>& arg, const debug_adaptor<Backend>& a, std::size_t b)
{
   using default_ops::eval_left_shift;
   eval_left_shift(arg.value(), a.value(), b);
   arg.update_view();
}
template <class Backend>
inline void eval_right_shift(debug_adaptor<Backend>& arg, std::size_t a)
{
   using default_ops::eval_right_shift;
   eval_right_shift(arg.value(), a);
   arg.update_view();
}
template <class Backend>
inline void eval_right_shift(debug_adaptor<Backend>& arg, const debug_adaptor<Backend>& a, std::size_t b)
{
   using default_ops::eval_right_shift;
   eval_right_shift(arg.value(), a.value(), b);
   arg.update_view();
}

template <class Backend, class T>
inline unsigned eval_integer_modulus(const debug_adaptor<Backend>& arg, const T& a)
{
   using default_ops::eval_integer_modulus;
   return eval_integer_modulus(arg.value(), a);
}

template <class Backend>
inline unsigned eval_lsb(const debug_adaptor<Backend>& arg)
{
   using default_ops::eval_lsb;
   return eval_lsb(arg.value());
}

template <class Backend>
inline unsigned eval_msb(const debug_adaptor<Backend>& arg)
{
   using default_ops::eval_msb;
   return eval_msb(arg.value());
}

template <class Backend>
inline bool eval_bit_test(const debug_adaptor<Backend>& arg, unsigned a)
{
   using default_ops::eval_bit_test;
   return eval_bit_test(arg.value(), a);
}

template <class Backend>
inline void eval_bit_set(const debug_adaptor<Backend>& arg, unsigned a)
{
   using default_ops::eval_bit_set;
   eval_bit_set(arg.value(), a);
   arg.update_view();
}
template <class Backend>
inline void eval_bit_unset(const debug_adaptor<Backend>& arg, unsigned a)
{
   using default_ops::eval_bit_unset;
   eval_bit_unset(arg.value(), a);
   arg.update_view();
}
template <class Backend>
inline void eval_bit_flip(const debug_adaptor<Backend>& arg, unsigned a)
{
   using default_ops::eval_bit_flip;
   eval_bit_flip(arg.value(), a);
   arg.update_view();
}

NON_MEMBER_OP3(gcd, "gcd")
NON_MEMBER_OP3(lcm, "lcm")
NON_MEMBER_OP4(powm, "powm")

/*********************************************************************
*
* abs/fabs:
*
*********************************************************************/

NON_MEMBER_OP2(abs, "abs")
NON_MEMBER_OP2(fabs, "fabs")

/*********************************************************************
*
* Floating point functions:
*
*********************************************************************/

NON_MEMBER_OP2(trunc, "trunc")
NON_MEMBER_OP2(round, "round")
NON_MEMBER_OP2(exp, "exp")
NON_MEMBER_OP2(log, "log")
NON_MEMBER_OP2(log10, "log10")
NON_MEMBER_OP2(sin, "sin")
NON_MEMBER_OP2(cos, "cos")
NON_MEMBER_OP2(tan, "tan")
NON_MEMBER_OP2(asin, "asin")
NON_MEMBER_OP2(acos, "acos")
NON_MEMBER_OP2(atan, "atan")
NON_MEMBER_OP2(sinh, "sinh")
NON_MEMBER_OP2(cosh, "cosh")
NON_MEMBER_OP2(tanh, "tanh")
NON_MEMBER_OP3(fmod, "fmod")
NON_MEMBER_OP3(pow, "pow")
NON_MEMBER_OP3(atan2, "atan2")

template <class Backend>
int eval_signbit(const debug_adaptor<Backend>& val)
{
   return eval_signbit(val.value());
}

template <class Backend>
std::size_t hash_value(const debug_adaptor<Backend>& val)
{
   return hash_value(val.value());
}

} // namespace backends

using backends::debug_adaptor;

template <class Backend>
struct number_category<backends::debug_adaptor<Backend> > : public number_category<Backend>
{};

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
}} // namespace boost::multiprecision

namespace std {

template <class Backend, boost::multiprecision::expression_template_option ExpressionTemplates>
class numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::debug_adaptor<Backend>, ExpressionTemplates> >
    : public std::numeric_limits<boost::multiprecision::number<Backend, ExpressionTemplates> >
{
   typedef std::numeric_limits<boost::multiprecision::number<Backend, ExpressionTemplates> >                           base_type;
   typedef boost::multiprecision::number<boost::multiprecision::backends::debug_adaptor<Backend>, ExpressionTemplates> number_type;

 public:
   static number_type(min)() BOOST_NOEXCEPT { return (base_type::min)(); }
   static number_type(max)() BOOST_NOEXCEPT { return (base_type::max)(); }
   static number_type lowest() BOOST_NOEXCEPT { return -(max)(); }
   static number_type epsilon() BOOST_NOEXCEPT { return base_type::epsilon(); }
   static number_type round_error() BOOST_NOEXCEPT { return epsilon() / 2; }
   static number_type infinity() BOOST_NOEXCEPT { return base_type::infinity(); }
   static number_type quiet_NaN() BOOST_NOEXCEPT { return base_type::quiet_NaN(); }
   static number_type signaling_NaN() BOOST_NOEXCEPT { return base_type::signaling_NaN(); }
   static number_type denorm_min() BOOST_NOEXCEPT { return base_type::denorm_min(); }
};

} // namespace std

namespace boost {
namespace math {

namespace policies {

template <class Backend, boost::multiprecision::expression_template_option ExpressionTemplates, class Policy>
struct precision<boost::multiprecision::number<boost::multiprecision::debug_adaptor<Backend>, ExpressionTemplates>, Policy>
    : public precision<boost::multiprecision::number<Backend, ExpressionTemplates>, Policy>
{};

#undef NON_MEMBER_OP1
#undef NON_MEMBER_OP2
#undef NON_MEMBER_OP3
#undef NON_MEMBER_OP4

}

}} // namespace boost::math::policies

#endif

/* debug_adaptor.hpp
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
*/