///////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MATH_DEBUG_ADAPTER_HPP
#define BOOST_MATH_DEBUG_ADAPTER_HPP

#include <boost/multiprecision/detail/standalone_config.hpp>
#include <boost/multiprecision/traits/extract_exponent_type.hpp>
#include <boost/multiprecision/detail/integer_ops.hpp>

namespace boost {
namespace multiprecision {
namespace backends {

template <class Backend>
struct debug_adaptor
{
   using signed_types = typename Backend::signed_types  ;
   using unsigned_types = typename Backend::unsigned_types;
   using float_types = typename Backend::float_types   ;
   using exponent_type = typename extract_exponent_type<Backend, number_category<Backend>::value>::type;

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
   debug_adaptor(const T& i, const typename std::enable_if<std::is_convertible<T, Backend>::value>::type* = 0)
       : m_value(i)
   {
      update_view();
   }
   template <class T>
   debug_adaptor(const debug_adaptor<T>& i, const typename std::enable_if<std::is_convertible<T, Backend>::value>::type* = 0)
       : m_value(i.value())
   {
      update_view();
   }
   template <class T, class U>
   debug_adaptor(const T& i, const U& j, typename std::enable_if<std::is_constructible<Backend, const T&, const U&>::value>::type* = nullptr)
       : m_value(i, j)
   {
      update_view();
   }
   template <class B2>
   debug_adaptor(const B2& i, unsigned digits10, typename std::enable_if<std::is_same<B2, Backend>::value && std::is_constructible<Backend, const Backend&, unsigned>::value>::type* = nullptr)
       : m_value(i, digits10)
   {
      update_view();
   }
   template <class T>
   typename std::enable_if<boost::multiprecision::detail::is_arithmetic<T>::value || std::is_assignable<Backend, T>::value, debug_adaptor&>::type operator=(const T& i)
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

   #ifndef BOOST_MP_STANDALONE
   template <class Archive>
   void serialize(Archive& ar, const unsigned int /*version*/)
   {
      ar & boost::make_nvp("value", m_value);
      using tag = typename Archive::is_loading;
      if (tag::value)
         update_view();
   }
   #endif 
   
   static unsigned default_precision() noexcept
   {
      return Backend::default_precision();
   }
   static void default_precision(unsigned v) noexcept
   {
      Backend::default_precision(v);
   }
   static unsigned thread_default_precision() noexcept
   {
      return Backend::thread_default_precision();
   }
   static void thread_default_precision(unsigned v) noexcept
   {
      Backend::thread_default_precision(v);
   }
   unsigned precision() const noexcept
   {
      return value().precision();
   }
   void precision(unsigned digits10) noexcept
   {
      value().precision(digits10);
   }
   //
   // Variable precision options:
   // 
   static constexpr variable_precision_options default_variable_precision_options()noexcept
   {
      return Backend::default_variable_precision_options();
   }
   static constexpr variable_precision_options thread_default_variable_precision_options()noexcept
   {
      return Backend::thread_default_variable_precision_options();
   }
   static BOOST_MP_CXX14_CONSTEXPR void default_variable_precision_options(variable_precision_options opts)
   {
      Backend::default_variable_precision_options(opts);
   }
   static BOOST_MP_CXX14_CONSTEXPR void thread_default_variable_precision_options(variable_precision_options opts)
   {
      Backend::thread_default_variable_precision_options(opts);
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

template <class Backend, class V, class U>
inline BOOST_MP_CXX14_CONSTEXPR void assign_components(debug_adaptor<Backend>& result, const V& v1, const U& v2)
{
   using default_ops::assign_components;
   assign_components(result.value(), unwrap_debug_type(v1), unwrap_debug_type(v2));
   result.update_view();
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
template <class Backend, class R>
inline void eval_convert_to(debug_adaptor<R>* result, const debug_adaptor<Backend>& val)
{
   using default_ops::eval_convert_to;
   eval_convert_to(&result->value(), val.value());
}
template <class Backend, class R>
inline void eval_convert_to(debug_adaptor<R>* result, const Backend& val)
{
   using default_ops::eval_convert_to;
   eval_convert_to(&result->value(), val);
}

template <class Backend>
inline void eval_convert_to(std::complex<float>* result, const debug_adaptor<Backend>& val)
{
   using default_ops::eval_convert_to;
   eval_convert_to(result, val.value());
}
template <class Backend>
inline void eval_convert_to(std::complex<double>* result, const debug_adaptor<Backend>& val)
{
   using default_ops::eval_convert_to;
   eval_convert_to(result, val.value());
}
template <class Backend>
inline void eval_convert_to(std::complex<long double>* result, const debug_adaptor<Backend>& val)
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
inline T eval_integer_modulus(const debug_adaptor<Backend>& arg, const T& a)
{
   using default_ops::eval_integer_modulus;
   return eval_integer_modulus(arg.value(), a);
}

template <class Backend>
inline std::size_t eval_lsb(const debug_adaptor<Backend>& arg)
{
   using default_ops::eval_lsb;
   return eval_lsb(arg.value());
}

template <class Backend>
inline std::size_t eval_msb(const debug_adaptor<Backend>& arg)
{
   using default_ops::eval_msb;
   return eval_msb(arg.value());
}

template <class Backend>
inline bool eval_bit_test(const debug_adaptor<Backend>& arg, std::size_t a)
{
   using default_ops::eval_bit_test;
   return eval_bit_test(arg.value(), a);
}

template <class Backend>
inline void eval_bit_set(const debug_adaptor<Backend>& arg, std::size_t a)
{
   using default_ops::eval_bit_set;
   eval_bit_set(arg.value(), a);
   arg.update_view();
}
template <class Backend>
inline void eval_bit_unset(const debug_adaptor<Backend>& arg, std::size_t a)
{
   using default_ops::eval_bit_unset;
   eval_bit_unset(arg.value(), a);
   arg.update_view();
}
template <class Backend>
inline void eval_bit_flip(const debug_adaptor<Backend>& arg, std::size_t a)
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
NON_MEMBER_OP2(asinh, "asinh")
NON_MEMBER_OP2(acosh, "acosh")
NON_MEMBER_OP2(atanh, "atanh")
NON_MEMBER_OP3(fmod, "fmod")
NON_MEMBER_OP3(pow, "pow")
NON_MEMBER_OP3(atan2, "atan2")
NON_MEMBER_OP2(conj, "conj")

template <class Backend>
int eval_signbit(const debug_adaptor<Backend>& val)
{
   using default_ops::eval_signbit;
   return eval_signbit(val.value());
}

template <class Backend>
std::size_t hash_value(const debug_adaptor<Backend>& val)
{
   return hash_value(val.value());
}

template <class Backend, expression_template_option ExpressionTemplates>
inline typename std::enable_if<number_category<Backend>::value == number_kind_rational, typename number<debug_adaptor<Backend>, ExpressionTemplates>::value_type>::type
   numerator(const number<debug_adaptor<Backend>, ExpressionTemplates>& arg)
{
   number<Backend, ExpressionTemplates> t(arg.backend().value());
   return numerator(t).backend();
}
template <class Backend, expression_template_option ExpressionTemplates>
inline typename std::enable_if<number_category<Backend>::value == number_kind_rational, typename number<debug_adaptor<Backend>, ExpressionTemplates>::value_type>::type
   denominator(const number<debug_adaptor<Backend>, ExpressionTemplates>& arg)
{
   number<Backend, ExpressionTemplates> t(arg.backend().value());
   return denominator(t).backend();
}

template <class To, class From>
inline BOOST_MP_CXX14_CONSTEXPR void eval_real(To& to, const debug_adaptor<From>& from)
{
   using default_ops::eval_real;
   eval_real(to, from.value());
}
template <class To, class From>
inline BOOST_MP_CXX14_CONSTEXPR void eval_real(debug_adaptor<To>& to, const debug_adaptor<From>& from)
{
   using default_ops::eval_real;
   eval_real(to.value(), from.value());
   to.update_view();
}
template <class To, class From>
inline BOOST_MP_CXX14_CONSTEXPR void eval_real(debug_adaptor<To>& to, const From& from)
{
   using default_ops::eval_real;
   eval_real(to.value(), from);
   to.update_view();
}

template <class To, class From>
inline BOOST_MP_CXX14_CONSTEXPR void eval_imag(To& to, const debug_adaptor<From>& from)
{
   using default_ops::eval_imag;
   eval_imag(to, from.value());
}
template <class To, class From>
inline BOOST_MP_CXX14_CONSTEXPR void eval_imag(debug_adaptor<To>& to, const debug_adaptor<From>& from)
{
   using default_ops::eval_imag;
   eval_imag(to.value(), from.value());
   to.update_view();
}
template <class To, class From>
inline BOOST_MP_CXX14_CONSTEXPR void eval_imag(debug_adaptor<To>& to, const From& from)
{
   using default_ops::eval_imag;
   eval_imag(to.value(), from);
   to.update_view();
}

template <class To, class From>
inline BOOST_MP_CXX14_CONSTEXPR void eval_set_real(To& to, const debug_adaptor<From>& from)
{
   using default_ops::eval_set_real;
   eval_set_real(to, from.value());
}
template <class To, class From>
inline BOOST_MP_CXX14_CONSTEXPR void eval_set_real(debug_adaptor<To>& to, const debug_adaptor<From>& from)
{
   using default_ops::eval_set_real;
   eval_set_real(to.value(), from.value());
   to.update_view();
}
template <class To, class From>
inline BOOST_MP_CXX14_CONSTEXPR void eval_set_real(debug_adaptor<To>& to, const From& from)
{
   using default_ops::eval_set_real;
   eval_set_real(to.value(), from);
   to.update_view();
}

template <class To, class From>
inline BOOST_MP_CXX14_CONSTEXPR void eval_set_imag(To& to, const debug_adaptor<From>& from)
{
   using default_ops::eval_set_imag;
   eval_set_imag(to, from.value());
}
template <class To, class From>
inline BOOST_MP_CXX14_CONSTEXPR void eval_set_imag(debug_adaptor<To>& to, const debug_adaptor<From>& from)
{
   using default_ops::eval_set_imag;
   eval_set_imag(to.value(), from.value());
   to.update_view();
}
template <class To, class From>
inline BOOST_MP_CXX14_CONSTEXPR void eval_set_imag(debug_adaptor<To>& to, const From& from)
{
   using default_ops::eval_set_imag;
   eval_set_imag(to.value(), from);
   to.update_view();
}


} // namespace backends

using backends::debug_adaptor;

namespace detail {
   template <class Backend>
   struct is_variable_precision<debug_adaptor<Backend> > : public is_variable_precision<Backend>
   {};
#ifdef BOOST_HAS_INT128
   template <class Backend>
   struct is_convertible_arithmetic<int128_type, debug_adaptor<Backend> > : public is_convertible_arithmetic<int128_type, Backend>
   {};
   template <class Backend>
   struct is_convertible_arithmetic<uint128_type, debug_adaptor<Backend> > : public is_convertible_arithmetic<uint128_type, Backend>
   {};
#endif
#ifdef BOOST_HAS_FLOAT128
   template <class Backend>
   struct is_convertible_arithmetic<float128_type, debug_adaptor<Backend> > : public is_convertible_arithmetic<float128_type, Backend>
   {};
#endif
   } // namespace detail

template <class Backend>
struct number_category<backends::debug_adaptor<Backend> > : public number_category<Backend>
{};

template <class Number>
using debug_adaptor_t = number<debug_adaptor<typename Number::backend_type>, Number::et>;


template <class Backend, expression_template_option ExpressionTemplates>
struct component_type<number<debug_adaptor<Backend>, ExpressionTemplates>>
{
   //
   // We'll make the component_type also a debug_adaptor:
   //
   using base_component_type = typename component_type<number<Backend, ExpressionTemplates>>::type;
   using base_component_backend = typename base_component_type::backend_type;
   using type = number<debug_adaptor<base_component_backend>, ExpressionTemplates>;
};

template <class Backend>
struct is_interval_number<backends::debug_adaptor<Backend> > : public is_interval_number<Backend> {};

}} // namespace boost::multiprecision

namespace std {

template <class Backend, boost::multiprecision::expression_template_option ExpressionTemplates>
class numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::debug_adaptor<Backend>, ExpressionTemplates> >
    : public std::numeric_limits<boost::multiprecision::number<Backend, ExpressionTemplates> >
{
   using base_type = std::numeric_limits<boost::multiprecision::number<Backend, ExpressionTemplates> >                          ;
   using number_type = boost::multiprecision::number<boost::multiprecision::backends::debug_adaptor<Backend>, ExpressionTemplates>;

 public:
   static number_type(min)() noexcept { return (base_type::min)(); }
   static number_type(max)() noexcept { return (base_type::max)(); }
   static number_type lowest() noexcept { return -(max)(); }
   static number_type epsilon() noexcept { return base_type::epsilon(); }
   static number_type round_error() noexcept { return epsilon() / 2; }
   static number_type infinity() noexcept { return base_type::infinity(); }
   static number_type quiet_NaN() noexcept { return base_type::quiet_NaN(); }
   static number_type signaling_NaN() noexcept { return base_type::signaling_NaN(); }
   static number_type denorm_min() noexcept { return base_type::denorm_min(); }
};

} // namespace std

#ifdef BOOST_MP_MATH_AVAILABLE
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
#else
#undef NON_MEMBER_OP1
#undef NON_MEMBER_OP2
#undef NON_MEMBER_OP3
#undef NON_MEMBER_OP4
#endif // BOOST_MP_MATH_AVAILABLE

#endif

/* debug_adaptor.hpp
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
*/