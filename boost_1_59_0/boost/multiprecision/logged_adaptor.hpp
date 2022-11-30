///////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MATH_LOGGED_ADAPTER_HPP
#define BOOST_MATH_LOGGED_ADAPTER_HPP

#include <boost/multiprecision/detail/standalone_config.hpp>
#include <boost/multiprecision/traits/extract_exponent_type.hpp>
#include <boost/multiprecision/detail/integer_ops.hpp>

namespace boost {
namespace multiprecision {

template <class Backend>
inline void log_postfix_event(const Backend&, const char* /*event_description*/)
{
}
template <class Backend, class T>
inline void log_postfix_event(const Backend&, const T&, const char* /*event_description*/)
{
}
template <class Backend>
inline void log_prefix_event(const Backend&, const char* /*event_description*/)
{
}
template <class Backend, class T>
inline void log_prefix_event(const Backend&, const T&, const char* /*event_description*/)
{
}
template <class Backend, class T, class U>
inline void log_prefix_event(const Backend&, const T&, const U&, const char* /*event_description*/)
{
}
template <class Backend, class T, class U, class V>
inline void log_prefix_event(const Backend&, const T&, const U&, const V&, const char* /*event_description*/)
{
}

namespace backends {

template <class Backend>
struct logged_adaptor
{
   using signed_types = typename Backend::signed_types  ;
   using unsigned_types = typename Backend::unsigned_types;
   using float_types = typename Backend::float_types   ;
   using exponent_type = typename extract_exponent_type<Backend, number_category<Backend>::value>::type;

 private:
   Backend m_value;

 public:
   logged_adaptor()
   {
      log_postfix_event(m_value, "Default construct");
   }
   logged_adaptor(const logged_adaptor& o)
   {
      log_prefix_event(m_value, o.value(), "Copy construct");
      m_value = o.m_value;
      log_postfix_event(m_value, "Copy construct");
   }
   // rvalue copy
   logged_adaptor(logged_adaptor&& o)
   {
      log_prefix_event(m_value, o.value(), "Move construct");
      m_value = static_cast<Backend&&>(o.m_value);
      log_postfix_event(m_value, "Move construct");
   }
   logged_adaptor& operator=(logged_adaptor&& o)
   {
      log_prefix_event(m_value, o.value(), "Move Assignment");
      m_value = static_cast<Backend&&>(o.m_value);
      log_postfix_event(m_value, "Move construct");
      return *this;
   }
   logged_adaptor& operator=(const logged_adaptor& o)
   {
      log_prefix_event(m_value, o.value(), "Assignment");
      m_value = o.m_value;
      log_postfix_event(m_value, "Copy construct");
      return *this;
   }
   template <class T>
   logged_adaptor(const T& i, const typename std::enable_if<std::is_convertible<T, Backend>::value>::type* = 0)
       : m_value(i)
   {
      log_postfix_event(m_value, "construct from arithmetic type");
   }
   template <class T>
   logged_adaptor(const logged_adaptor<T>& i, const typename std::enable_if<std::is_convertible<T, Backend>::value>::type* = 0)
       : m_value(i.value())
   {
      log_postfix_event(m_value, "construct from arithmetic type");
   }
   template <class T, class U>
   logged_adaptor(const T& i, const U& j, typename std::enable_if<std::is_constructible<Backend, const T&, const U&>::value>::type* = nullptr)
      : m_value(i, j)
   {
      log_postfix_event(m_value, "construct from a pair of arithmetic types");
   }
   template <class D = Backend>
   logged_adaptor(const Backend& i, unsigned digits10, typename std::enable_if<std::is_constructible<D, Backend const&, unsigned>::value>::type const* = nullptr)
      : m_value(i, digits10)
   {
      log_postfix_event(m_value, "construct from arithmetic type and precision");
   }
   template <class D = Backend>
   logged_adaptor(const logged_adaptor<Backend>& i, unsigned digits10, typename std::enable_if<std::is_constructible<D, Backend const&, unsigned>::value>::type const* = nullptr)
      : m_value(i.value(), digits10)
   {
      log_postfix_event(m_value, "construct from arithmetic type and precision");
   }
   template <class T>
   typename std::enable_if<boost::multiprecision::detail::is_arithmetic<T>::value || std::is_assignable<Backend, T>::value, logged_adaptor&>::type operator=(const T& i)
   {
      log_prefix_event(m_value, i, "Assignment from arithmetic type");
      m_value = i;
      log_postfix_event(m_value, "Assignment from arithmetic type");
      return *this;
   }
   logged_adaptor& operator=(const char* s)
   {
      log_prefix_event(m_value, s, "Assignment from string type");
      m_value = s;
      log_postfix_event(m_value, "Assignment from string type");
      return *this;
   }
   void swap(logged_adaptor& o)
   {
      log_prefix_event(m_value, o.value(), "swap");
      std::swap(m_value, o.value());
      log_postfix_event(m_value, "swap");
   }
   std::string str(std::streamsize digits, std::ios_base::fmtflags f) const
   {
      log_prefix_event(m_value, "Conversion to string");
      std::string s = m_value.str(digits, f);
      log_postfix_event(m_value, s, "Conversion to string");
      return s;
   }
   void negate()
   {
      log_prefix_event(m_value, "negate");
      m_value.negate();
      log_postfix_event(m_value, "negate");
   }
   int compare(const logged_adaptor& o) const
   {
      log_prefix_event(m_value, o.value(), "compare");
      int r = m_value.compare(o.value());
      log_postfix_event(m_value, r, "compare");
      return r;
   }
   template <class T>
   int compare(const T& i) const
   {
      log_prefix_event(m_value, i, "compare");
      int r = m_value.compare(i);
      log_postfix_event(m_value, r, "compare");
      return r;
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
      log_prefix_event(m_value, "serialize");
      ar& boost::make_nvp("value", m_value);
      log_postfix_event(m_value, "serialize");
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

template <class T>
inline const T& unwrap_logged_type(const T& a) { return a; }
template <class Backend>
inline const Backend& unwrap_logged_type(const logged_adaptor<Backend>& a) { return a.value(); }

#define NON_MEMBER_OP1(name, str)                                        \
   template <class Backend>                                              \
   inline void BOOST_JOIN(eval_, name)(logged_adaptor<Backend> & result) \
   {                                                                     \
      using default_ops::BOOST_JOIN(eval_, name);                        \
      log_prefix_event(result.value(), str);                             \
      BOOST_JOIN(eval_, name)                                            \
      (result.value());                                                  \
      log_postfix_event(result.value(), str);                            \
   }

#define NON_MEMBER_OP2(name, str)                                                                          \
   template <class Backend, class T>                                                                       \
   inline void BOOST_JOIN(eval_, name)(logged_adaptor<Backend> & result, const T& a)                       \
   {                                                                                                       \
      using default_ops::BOOST_JOIN(eval_, name);                                                          \
      log_prefix_event(result.value(), unwrap_logged_type(a), str);                                        \
      BOOST_JOIN(eval_, name)                                                                              \
      (result.value(), unwrap_logged_type(a));                                                             \
      log_postfix_event(result.value(), str);                                                              \
   }                                                                                                       \
   template <class Backend>                                                                                \
   inline void BOOST_JOIN(eval_, name)(logged_adaptor<Backend> & result, const logged_adaptor<Backend>& a) \
   {                                                                                                       \
      using default_ops::BOOST_JOIN(eval_, name);                                                          \
      log_prefix_event(result.value(), unwrap_logged_type(a), str);                                        \
      BOOST_JOIN(eval_, name)                                                                              \
      (result.value(), unwrap_logged_type(a));                                                             \
      log_postfix_event(result.value(), str);                                                              \
   }

#define NON_MEMBER_OP3(name, str)                                                                                                            \
   template <class Backend, class T, class U>                                                                                                \
   inline void BOOST_JOIN(eval_, name)(logged_adaptor<Backend> & result, const T& a, const U& b)                                             \
   {                                                                                                                                         \
      using default_ops::BOOST_JOIN(eval_, name);                                                                                            \
      log_prefix_event(result.value(), unwrap_logged_type(a), unwrap_logged_type(b), str);                                                   \
      BOOST_JOIN(eval_, name)                                                                                                                \
      (result.value(), unwrap_logged_type(a), unwrap_logged_type(b));                                                                        \
      log_postfix_event(result.value(), str);                                                                                                \
   }                                                                                                                                         \
   template <class Backend, class T>                                                                                                         \
   inline void BOOST_JOIN(eval_, name)(logged_adaptor<Backend> & result, const logged_adaptor<Backend>& a, const T& b)                       \
   {                                                                                                                                         \
      using default_ops::BOOST_JOIN(eval_, name);                                                                                            \
      log_prefix_event(result.value(), unwrap_logged_type(a), unwrap_logged_type(b), str);                                                   \
      BOOST_JOIN(eval_, name)                                                                                                                \
      (result.value(), unwrap_logged_type(a), unwrap_logged_type(b));                                                                        \
      log_postfix_event(result.value(), str);                                                                                                \
   }                                                                                                                                         \
   template <class Backend, class T>                                                                                                         \
   inline void BOOST_JOIN(eval_, name)(logged_adaptor<Backend> & result, const T& a, const logged_adaptor<Backend>& b)                       \
   {                                                                                                                                         \
      using default_ops::BOOST_JOIN(eval_, name);                                                                                            \
      log_prefix_event(result.value(), unwrap_logged_type(a), unwrap_logged_type(b), str);                                                   \
      BOOST_JOIN(eval_, name)                                                                                                                \
      (result.value(), unwrap_logged_type(a), unwrap_logged_type(b));                                                                        \
      log_postfix_event(result.value(), str);                                                                                                \
   }                                                                                                                                         \
   template <class Backend>                                                                                                                  \
   inline void BOOST_JOIN(eval_, name)(logged_adaptor<Backend> & result, const logged_adaptor<Backend>& a, const logged_adaptor<Backend>& b) \
   {                                                                                                                                         \
      using default_ops::BOOST_JOIN(eval_, name);                                                                                            \
      log_prefix_event(result.value(), unwrap_logged_type(a), unwrap_logged_type(b), str);                                                   \
      BOOST_JOIN(eval_, name)                                                                                                                \
      (result.value(), unwrap_logged_type(a), unwrap_logged_type(b));                                                                        \
      log_postfix_event(result.value(), str);                                                                                                \
   }

#define NON_MEMBER_OP4(name, str)                                                                                                                                              \
   template <class Backend, class T, class U, class V>                                                                                                                         \
   inline void BOOST_JOIN(eval_, name)(logged_adaptor<Backend> & result, const T& a, const U& b, const V& c)                                                                   \
   {                                                                                                                                                                           \
      using default_ops::BOOST_JOIN(eval_, name);                                                                                                                              \
      log_prefix_event(result.value(), unwrap_logged_type(a), unwrap_logged_type(b), unwrap_logged_type(c), str);                                                              \
      BOOST_JOIN(eval_, name)                                                                                                                                                  \
      (result.value(), unwrap_logged_type(a), unwrap_logged_type(b), unwrap_logged_type(c));                                                                                   \
      log_postfix_event(result.value(), str);                                                                                                                                  \
   }                                                                                                                                                                           \
   template <class Backend, class T>                                                                                                                                           \
   inline void BOOST_JOIN(eval_, name)(logged_adaptor<Backend> & result, const logged_adaptor<Backend>& a, const logged_adaptor<Backend>& b, const T& c)                       \
   {                                                                                                                                                                           \
      using default_ops::BOOST_JOIN(eval_, name);                                                                                                                              \
      log_prefix_event(result.value(), unwrap_logged_type(a), unwrap_logged_type(b), unwrap_logged_type(c), str);                                                              \
      BOOST_JOIN(eval_, name)                                                                                                                                                  \
      (result.value(), unwrap_logged_type(a), unwrap_logged_type(b), unwrap_logged_type(c));                                                                                   \
      log_postfix_event(result.value(), str);                                                                                                                                  \
   }                                                                                                                                                                           \
   template <class Backend, class T>                                                                                                                                           \
   inline void BOOST_JOIN(eval_, name)(logged_adaptor<Backend> & result, const logged_adaptor<Backend>& a, const T& b, const logged_adaptor<Backend>& c)                       \
   {                                                                                                                                                                           \
      using default_ops::BOOST_JOIN(eval_, name);                                                                                                                              \
      log_prefix_event(result.value(), unwrap_logged_type(a), unwrap_logged_type(b), unwrap_logged_type(c), str);                                                              \
      BOOST_JOIN(eval_, name)                                                                                                                                                  \
      (result.value(), unwrap_logged_type(a), unwrap_logged_type(b), unwrap_logged_type(c));                                                                                   \
      log_postfix_event(result.value(), str);                                                                                                                                  \
   }                                                                                                                                                                           \
   template <class Backend, class T>                                                                                                                                           \
   inline void BOOST_JOIN(eval_, name)(logged_adaptor<Backend> & result, const T& a, const logged_adaptor<Backend>& b, const logged_adaptor<Backend>& c)                       \
   {                                                                                                                                                                           \
      using default_ops::BOOST_JOIN(eval_, name);                                                                                                                              \
      log_prefix_event(result.value(), unwrap_logged_type(a), unwrap_logged_type(b), unwrap_logged_type(c), str);                                                              \
      BOOST_JOIN(eval_, name)                                                                                                                                                  \
      (result.value(), unwrap_logged_type(a), unwrap_logged_type(b), unwrap_logged_type(c));                                                                                   \
      log_postfix_event(result.value(), str);                                                                                                                                  \
   }                                                                                                                                                                           \
   template <class Backend>                                                                                                                                                    \
   inline void BOOST_JOIN(eval_, name)(logged_adaptor<Backend> & result, const logged_adaptor<Backend>& a, const logged_adaptor<Backend>& b, const logged_adaptor<Backend>& c) \
   {                                                                                                                                                                           \
      using default_ops::BOOST_JOIN(eval_, name);                                                                                                                              \
      log_prefix_event(result.value(), unwrap_logged_type(a), unwrap_logged_type(b), unwrap_logged_type(c), str);                                                              \
      BOOST_JOIN(eval_, name)                                                                                                                                                  \
      (result.value(), unwrap_logged_type(a), unwrap_logged_type(b), unwrap_logged_type(c));                                                                                   \
      log_postfix_event(result.value(), str);                                                                                                                                  \
   }                                                                                                                                                                           \
   template <class Backend, class T, class U>                                                                                                                                  \
   inline void BOOST_JOIN(eval_, name)(logged_adaptor<Backend> & result, const logged_adaptor<Backend>& a, const T& b, const U& c)                                             \
   {                                                                                                                                                                           \
      using default_ops::BOOST_JOIN(eval_, name);                                                                                                                              \
      log_prefix_event(result.value(), unwrap_logged_type(a), unwrap_logged_type(b), unwrap_logged_type(c), str);                                                              \
      BOOST_JOIN(eval_, name)                                                                                                                                                  \
      (result.value(), unwrap_logged_type(a), unwrap_logged_type(b), unwrap_logged_type(c));                                                                                   \
      log_postfix_event(result.value(), str);                                                                                                                                  \
   }

NON_MEMBER_OP2(add, "+=")
NON_MEMBER_OP2(subtract, "-=")
NON_MEMBER_OP2(multiply, "*=")
NON_MEMBER_OP2(divide, "/=")

template <class Backend, class R>
inline void eval_convert_to(R* result, const logged_adaptor<Backend>& val)
{
   using default_ops::eval_convert_to;
   log_prefix_event(val.value(), "convert_to");
   eval_convert_to(result, val.value());
   log_postfix_event(val.value(), *result, "convert_to");
}

template <class Backend, class R>
inline void eval_convert_to(logged_adaptor<R>* result, const logged_adaptor<Backend>& val)
{
   using default_ops::eval_convert_to;
   log_prefix_event(val.value(), "convert_to");
   eval_convert_to(&result->value(), val.value());
   log_postfix_event(val.value(), &result->value(), "convert_to");
}
template <class Backend, class R>
inline void eval_convert_to(logged_adaptor<R>* result, const Backend& val)
{
   using default_ops::eval_convert_to;
   log_prefix_event(val, "convert_to");
   eval_convert_to(&result->value(), val);
   log_postfix_event(val, &result->value(), "convert_to");
}

template <class Backend>
inline void eval_convert_to(std::complex<float>* result, const logged_adaptor<Backend>& val)
{
   using default_ops::eval_convert_to;
   log_prefix_event(val.value(), "convert_to");
   eval_convert_to(result, val.value());
   log_postfix_event(val.value(), *result, "convert_to");
}
template <class Backend>
inline void eval_convert_to(std::complex<double>* result, const logged_adaptor<Backend>& val)
{
   using default_ops::eval_convert_to;
   log_prefix_event(val.value(), "convert_to");
   eval_convert_to(result, val.value());
   log_postfix_event(val.value(), *result, "convert_to");
}
template <class Backend>
inline void eval_convert_to(std::complex<long double>* result, const logged_adaptor<Backend>& val)
{
   using default_ops::eval_convert_to;
   log_prefix_event(val.value(), "convert_to");
   eval_convert_to(result, val.value());
   log_postfix_event(val.value(), *result, "convert_to");
}


template <class Backend, class Exp>
inline void eval_frexp(logged_adaptor<Backend>& result, const logged_adaptor<Backend>& arg, Exp* exp)
{
   log_prefix_event(arg.value(), "frexp");
   eval_frexp(result.value(), arg.value(), exp);
   log_postfix_event(result.value(), *exp, "frexp");
}

template <class Backend, class Exp>
inline void eval_ldexp(logged_adaptor<Backend>& result, const logged_adaptor<Backend>& arg, Exp exp)
{
   log_prefix_event(arg.value(), "ldexp");
   eval_ldexp(result.value(), arg.value(), exp);
   log_postfix_event(result.value(), exp, "ldexp");
}

template <class Backend, class Exp>
inline void eval_scalbn(logged_adaptor<Backend>& result, const logged_adaptor<Backend>& arg, Exp exp)
{
   using default_ops::eval_scalbn;
   log_prefix_event(arg.value(), "scalbn");
   eval_scalbn(result.value(), arg.value(), exp);
   log_postfix_event(result.value(), exp, "scalbn");
}

template <class Backend>
inline typename Backend::exponent_type eval_ilogb(const logged_adaptor<Backend>& arg)
{
   using default_ops::eval_ilogb;
   log_prefix_event(arg.value(), "ilogb");
   typename Backend::exponent_type r = eval_ilogb(arg.value());
   log_postfix_event(arg.value(), "ilogb");
   return r;
}

NON_MEMBER_OP2(floor, "floor")
NON_MEMBER_OP2(ceil, "ceil")
NON_MEMBER_OP2(sqrt, "sqrt")

template <class Backend>
inline int eval_fpclassify(const logged_adaptor<Backend>& arg)
{
   using default_ops::eval_fpclassify;
   log_prefix_event(arg.value(), "fpclassify");
   int r = eval_fpclassify(arg.value());
   log_postfix_event(arg.value(), r, "fpclassify");
   return r;
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
inline void eval_left_shift(logged_adaptor<Backend>& arg, std::size_t a)
{
   using default_ops::eval_left_shift;
   log_prefix_event(arg.value(), a, "<<=");
   eval_left_shift(arg.value(), a);
   log_postfix_event(arg.value(), "<<=");
}
template <class Backend>
inline void eval_left_shift(logged_adaptor<Backend>& arg, const logged_adaptor<Backend>& a, std::size_t b)
{
   using default_ops::eval_left_shift;
   log_prefix_event(arg.value(), a, b, "<<");
   eval_left_shift(arg.value(), a.value(), b);
   log_postfix_event(arg.value(), "<<");
}
template <class Backend>
inline void eval_right_shift(logged_adaptor<Backend>& arg, std::size_t a)
{
   using default_ops::eval_right_shift;
   log_prefix_event(arg.value(), a, ">>=");
   eval_right_shift(arg.value(), a);
   log_postfix_event(arg.value(), ">>=");
}
template <class Backend>
inline void eval_right_shift(logged_adaptor<Backend>& arg, const logged_adaptor<Backend>& a, std::size_t b)
{
   using default_ops::eval_right_shift;
   log_prefix_event(arg.value(), a, b, ">>");
   eval_right_shift(arg.value(), a.value(), b);
   log_postfix_event(arg.value(), ">>");
}

template <class Backend, class T>
inline T eval_integer_modulus(const logged_adaptor<Backend>& arg, const T& a)
{
   using default_ops::eval_integer_modulus;
   log_prefix_event(arg.value(), a, "integer-modulus");
   T r = eval_integer_modulus(arg.value(), a);
   log_postfix_event(arg.value(), r, "integer-modulus");
   return r;
}

template <class Backend>
inline std::size_t eval_lsb(const logged_adaptor<Backend>& arg)
{
   using default_ops::eval_lsb;
   log_prefix_event(arg.value(), "least-significant-bit");
   std::size_t r = eval_lsb(arg.value());
   log_postfix_event(arg.value(), r, "least-significant-bit");
   return r;
}

template <class Backend>
inline std::size_t eval_msb(const logged_adaptor<Backend>& arg)
{
   using default_ops::eval_msb;
   log_prefix_event(arg.value(), "most-significant-bit");
   std::size_t r = eval_msb(arg.value());
   log_postfix_event(arg.value(), r, "most-significant-bit");
   return r;
}

template <class Backend>
inline bool eval_bit_test(const logged_adaptor<Backend>& arg, std::size_t a)
{
   using default_ops::eval_bit_test;
   log_prefix_event(arg.value(), a, "bit-test");
   bool r = eval_bit_test(arg.value(), a);
   log_postfix_event(arg.value(), r, "bit-test");
   return r;
}

template <class Backend>
inline void eval_bit_set(const logged_adaptor<Backend>& arg, std::size_t a)
{
   using default_ops::eval_bit_set;
   log_prefix_event(arg.value(), a, "bit-set");
   eval_bit_set(arg.value(), a);
   log_postfix_event(arg.value(), arg, "bit-set");
}
template <class Backend>
inline void eval_bit_unset(const logged_adaptor<Backend>& arg, std::size_t a)
{
   using default_ops::eval_bit_unset;
   log_prefix_event(arg.value(), a, "bit-unset");
   eval_bit_unset(arg.value(), a);
   log_postfix_event(arg.value(), arg, "bit-unset");
}
template <class Backend>
inline void eval_bit_flip(const logged_adaptor<Backend>& arg, std::size_t a)
{
   using default_ops::eval_bit_flip;
   log_prefix_event(arg.value(), a, "bit-flip");
   eval_bit_flip(arg.value(), a);
   log_postfix_event(arg.value(), arg, "bit-flip");
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
NON_MEMBER_OP2(logb, "logb")
NON_MEMBER_OP3(fmod, "fmod")
NON_MEMBER_OP3(pow, "pow")
NON_MEMBER_OP3(atan2, "atan2")
NON_MEMBER_OP2(asinh, "asinh")
NON_MEMBER_OP2(acosh, "acosh")
NON_MEMBER_OP2(atanh, "atanh")
NON_MEMBER_OP2(conj, "conj")

template <class Backend>
int eval_signbit(const logged_adaptor<Backend>& val)
{
   using default_ops::eval_signbit;
   return eval_signbit(val.value());
}

template <class Backend>
std::size_t hash_value(const logged_adaptor<Backend>& val)
{
   return hash_value(val.value());
}

template <class Backend, expression_template_option ExpressionTemplates>
inline typename std::enable_if<number_category<Backend>::value == number_kind_rational, typename number<logged_adaptor<Backend>, ExpressionTemplates>::value_type>::type
numerator(const number<logged_adaptor<Backend>, ExpressionTemplates>& arg)
{
   number<Backend, ExpressionTemplates> t(arg.backend().value());
   return numerator(t).backend();
}
template <class Backend, expression_template_option ExpressionTemplates>
inline typename std::enable_if<number_category<Backend>::value == number_kind_rational, typename number<logged_adaptor<Backend>, ExpressionTemplates>::value_type>::type
denominator(const number<logged_adaptor<Backend>, ExpressionTemplates>& arg)
{
   number<Backend, ExpressionTemplates> t(arg.backend().value());
   return denominator(t).backend();
}

template <class To, class From>
inline BOOST_MP_CXX14_CONSTEXPR void eval_set_real(To& to, const logged_adaptor<From>& from)
{
   using default_ops::eval_set_real;
   log_prefix_event(to, from.value(), "Set real part");
   eval_set_real(to, from.value());
   log_postfix_event(to, from.value(), "Set real part");
}
template <class To, class From>
inline BOOST_MP_CXX14_CONSTEXPR void eval_set_real(logged_adaptor<To>& to, const logged_adaptor<From>& from)
{
   using default_ops::eval_set_real;
   log_prefix_event(to.value(), from.value(), "Set real part");
   eval_set_real(to.value(), from.value());
   log_postfix_event(to.value(), from.value(), "Set real part");
}
template <class To, class From>
inline BOOST_MP_CXX14_CONSTEXPR void eval_set_real(logged_adaptor<To>& to, const From& from)
{
   using default_ops::eval_set_real;
   log_prefix_event(to.value(), from, "Set real part");
   eval_set_real(to.value(), from);
   log_postfix_event(to.value(), from, "Set real part");
}

template <class To, class From>
inline BOOST_MP_CXX14_CONSTEXPR void eval_set_imag(To& to, const logged_adaptor<From>& from)
{
   using default_ops::eval_set_imag;
   log_prefix_event(to, from.value(), "Set imag part");
   eval_set_imag(to, from.value());
   log_postfix_event(to, from.value(), "Set imag part");
}
template <class To, class From>
inline BOOST_MP_CXX14_CONSTEXPR void eval_set_imag(logged_adaptor<To>& to, const logged_adaptor<From>& from)
{
   using default_ops::eval_set_imag;
   log_prefix_event(to.value(), from.value(), "Set imag part");
   eval_set_imag(to.value(), from.value());
   log_postfix_event(to.value(), from.value(), "Set imag part");
}
template <class To, class From>
inline BOOST_MP_CXX14_CONSTEXPR void eval_set_imag(logged_adaptor<To>& to, const From& from)
{
   using default_ops::eval_set_imag;
   log_prefix_event(to.value(), from, "Set imag part");
   eval_set_imag(to.value(), from);
   log_postfix_event(to.value(), from, "Set imag part");
}


#define NON_MEMBER_COMPLEX_TO_REAL(name, str)                                                    \
   template <class B1, class B2>                                                                 \
   inline void BOOST_JOIN(eval_, name)(logged_adaptor<B1> & result, const logged_adaptor<B2>& a) \
   {                                                                                             \
      using default_ops::BOOST_JOIN(eval_, name);                                                \
      log_prefix_event(a.value(), a.value(), str);                                               \
      BOOST_JOIN(eval_, name)                                                                    \
      (result.value(), a.value());                                                               \
      log_postfix_event(result.value(), str);                                                    \
   }                                                                                             \
   template <class B1, class B2>                                                                 \
   inline void BOOST_JOIN(eval_, name)(B1 & result, const logged_adaptor<B2>& a)                 \
   {                                                                                             \
      using default_ops::BOOST_JOIN(eval_, name);                                                \
      log_prefix_event(a.value(), a.value(), str);                                               \
      BOOST_JOIN(eval_, name)                                                                    \
      (result, a.value());                                                                       \
      log_postfix_event(result, str);                                                            \
   }

NON_MEMBER_COMPLEX_TO_REAL(real, "real")
NON_MEMBER_COMPLEX_TO_REAL(imag, "imag")

template <class T, class V, class U>
inline void assign_components(logged_adaptor<T>& result, const V& v1, const U& v2)
{
   using default_ops::assign_components;
   assign_components(result.value(), unwrap_logged_type(v1), unwrap_logged_type(v2));
}

} // namespace backends

using backends::logged_adaptor;

namespace detail {
   template <class Backend>
   struct is_variable_precision<logged_adaptor<Backend> > : public is_variable_precision<Backend>
   {};
#ifdef BOOST_HAS_INT128
   template <class Backend>
   struct is_convertible_arithmetic<int128_type, logged_adaptor<Backend> > : public is_convertible_arithmetic<int128_type, Backend>
   {};
   template <class Backend>
   struct is_convertible_arithmetic<uint128_type, logged_adaptor<Backend> > : public is_convertible_arithmetic<uint128_type, Backend>
   {};
#endif
#ifdef BOOST_HAS_FLOAT128
   template <class Backend>
   struct is_convertible_arithmetic<float128_type, logged_adaptor<Backend> > : public is_convertible_arithmetic<float128_type, Backend>
   {};
#endif
   } // namespace detail

template <class Backend>
struct number_category<backends::logged_adaptor<Backend> > : public number_category<Backend>
{};

template <class Number>
using logged_adaptor_t = number<logged_adaptor<typename Number::backend_type>, Number::et>;

template <class Backend, expression_template_option ExpressionTemplates>
struct component_type<number<logged_adaptor<Backend>, ExpressionTemplates>>
{
   //
   // We'll make the component_type also a logged_adaptor:
   //
   using base_component_type = typename component_type<number<Backend, ExpressionTemplates>>::type;
   using base_component_backend = typename base_component_type::backend_type;
   using type = number<logged_adaptor<base_component_backend>, ExpressionTemplates>;
};

template <class Backend>
struct is_interval_number<backends::logged_adaptor<Backend> > : public is_interval_number<Backend> {};

}} // namespace boost::multiprecision

namespace std {

template <class Backend, boost::multiprecision::expression_template_option ExpressionTemplates>
class numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::logged_adaptor<Backend>, ExpressionTemplates> >
    : public std::numeric_limits<boost::multiprecision::number<Backend, ExpressionTemplates> >
{
   using base_type = std::numeric_limits<boost::multiprecision::number<Backend, ExpressionTemplates> >                           ;
   using number_type = boost::multiprecision::number<boost::multiprecision::backends::logged_adaptor<Backend>, ExpressionTemplates>;

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
struct precision<boost::multiprecision::number<boost::multiprecision::logged_adaptor<Backend>, ExpressionTemplates>, Policy>
    : public precision<boost::multiprecision::number<Backend, ExpressionTemplates>, Policy>
{};

}

}} // namespace boost::math::policies
#endif // BOOST_MP_MATH_AVAILABLE

#undef NON_MEMBER_OP1
#undef NON_MEMBER_OP2
#undef NON_MEMBER_OP3
#undef NON_MEMBER_OP4

#endif

/* logged_adaptor.hpp
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
*/