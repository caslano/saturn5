///////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MATH_LOGGED_ADAPTER_HPP
#define BOOST_MATH_LOGGED_ADAPTER_HPP

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
   typedef typename Backend::signed_types   signed_types;
   typedef typename Backend::unsigned_types unsigned_types;
   typedef typename Backend::float_types    float_types;
   typedef typename extract_exponent_type<
       Backend, number_category<Backend>::value>::type exponent_type;

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
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
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
#endif
   logged_adaptor& operator=(const logged_adaptor& o)
   {
      log_prefix_event(m_value, o.value(), "Assignment");
      m_value = o.m_value;
      log_postfix_event(m_value, "Copy construct");
      return *this;
   }
   template <class T>
   logged_adaptor(const T& i, const typename enable_if_c<is_convertible<T, Backend>::value>::type* = 0)
       : m_value(i)
   {
      log_postfix_event(m_value, "construct from arithmetic type");
   }
   template <class T>
   logged_adaptor(const logged_adaptor<T>& i, const typename enable_if_c<is_convertible<T, Backend>::value>::type* = 0)
       : m_value(i.value())
   {
      log_postfix_event(m_value, "construct from arithmetic type");
   }
   template <class T>
   typename enable_if_c<is_arithmetic<T>::value || is_convertible<T, Backend>::value, logged_adaptor&>::type operator=(const T& i)
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
   template <class Archive>
   void serialize(Archive& ar, const unsigned int /*version*/)
   {
      log_prefix_event(m_value, "serialize");
      ar& boost::make_nvp("value", m_value);
      log_postfix_event(m_value, "serialize");
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
   log_prefix_event(arg.value(), "scalbn");
   eval_scalbn(result.value(), arg.value(), exp);
   log_postfix_event(result.value(), exp, "scalbn");
}

template <class Backend>
inline typename Backend::exponent_type eval_ilogb(const logged_adaptor<Backend>& arg)
{
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
inline unsigned eval_integer_modulus(const logged_adaptor<Backend>& arg, const T& a)
{
   using default_ops::eval_integer_modulus;
   log_prefix_event(arg.value(), a, "integer-modulus");
   unsigned r = eval_integer_modulus(arg.value(), a);
   log_postfix_event(arg.value(), r, "integer-modulus");
   return r;
}

template <class Backend>
inline unsigned eval_lsb(const logged_adaptor<Backend>& arg)
{
   using default_ops::eval_lsb;
   log_prefix_event(arg.value(), "least-significant-bit");
   unsigned r = eval_lsb(arg.value());
   log_postfix_event(arg.value(), r, "least-significant-bit");
   return r;
}

template <class Backend>
inline unsigned eval_msb(const logged_adaptor<Backend>& arg)
{
   using default_ops::eval_msb;
   log_prefix_event(arg.value(), "most-significant-bit");
   unsigned r = eval_msb(arg.value());
   log_postfix_event(arg.value(), r, "most-significant-bit");
   return r;
}

template <class Backend>
inline bool eval_bit_test(const logged_adaptor<Backend>& arg, unsigned a)
{
   using default_ops::eval_bit_test;
   log_prefix_event(arg.value(), a, "bit-test");
   bool r = eval_bit_test(arg.value(), a);
   log_postfix_event(arg.value(), r, "bit-test");
   return r;
}

template <class Backend>
inline void eval_bit_set(const logged_adaptor<Backend>& arg, unsigned a)
{
   using default_ops::eval_bit_set;
   log_prefix_event(arg.value(), a, "bit-set");
   eval_bit_set(arg.value(), a);
   log_postfix_event(arg.value(), arg, "bit-set");
}
template <class Backend>
inline void eval_bit_unset(const logged_adaptor<Backend>& arg, unsigned a)
{
   using default_ops::eval_bit_unset;
   log_prefix_event(arg.value(), a, "bit-unset");
   eval_bit_unset(arg.value(), a);
   log_postfix_event(arg.value(), arg, "bit-unset");
}
template <class Backend>
inline void eval_bit_flip(const logged_adaptor<Backend>& arg, unsigned a)
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
   assign_components(result.value(), v1, v2);
}

} // namespace backends

using backends::logged_adaptor;

template <class Backend>
struct number_category<backends::logged_adaptor<Backend> > : public number_category<Backend>
{};

}} // namespace boost::multiprecision

namespace std {

template <class Backend, boost::multiprecision::expression_template_option ExpressionTemplates>
class numeric_limits<boost::multiprecision::number<boost::multiprecision::backends::logged_adaptor<Backend>, ExpressionTemplates> >
    : public std::numeric_limits<boost::multiprecision::number<Backend, ExpressionTemplates> >
{
   typedef std::numeric_limits<boost::multiprecision::number<Backend, ExpressionTemplates> >                            base_type;
   typedef boost::multiprecision::number<boost::multiprecision::backends::logged_adaptor<Backend>, ExpressionTemplates> number_type;

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
struct precision<boost::multiprecision::number<boost::multiprecision::logged_adaptor<Backend>, ExpressionTemplates>, Policy>
    : public precision<boost::multiprecision::number<Backend, ExpressionTemplates>, Policy>
{};

}

}} // namespace boost::math::policies

#undef NON_MEMBER_OP1
#undef NON_MEMBER_OP2
#undef NON_MEMBER_OP3
#undef NON_MEMBER_OP4

#endif

/* logged_adaptor.hpp
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
*/