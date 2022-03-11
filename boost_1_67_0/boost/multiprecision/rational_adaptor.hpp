///////////////////////////////////////////////////////////////
//  Copyright 2011 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MATH_RATIONAL_ADAPTER_HPP
#define BOOST_MATH_RATIONAL_ADAPTER_HPP

#include <iostream>
#include <iomanip>
#include <sstream>
#include <boost/cstdint.hpp>
#include <boost/functional/hash_fwd.hpp>
#include <boost/multiprecision/number.hpp>
#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 4512 4127)
#endif
#include <boost/rational.hpp>
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

namespace boost {
namespace multiprecision {
namespace backends {

template <class IntBackend>
struct rational_adaptor
{
   typedef number<IntBackend>            integer_type;
   typedef boost::rational<integer_type> rational_type;

   typedef typename IntBackend::signed_types   signed_types;
   typedef typename IntBackend::unsigned_types unsigned_types;
   typedef typename IntBackend::float_types    float_types;

   rational_adaptor() BOOST_MP_NOEXCEPT_IF(noexcept(rational_type())) {}
   rational_adaptor(const rational_adaptor& o) BOOST_MP_NOEXCEPT_IF(noexcept(std::declval<rational_type&>() = std::declval<const rational_type&>()))
   {
      m_value = o.m_value;
   }
   rational_adaptor(const IntBackend& o) BOOST_MP_NOEXCEPT_IF(noexcept(rational_type(std::declval<const IntBackend&>()))) : m_value(o) {}

   template <class U>
   rational_adaptor(const U& u, typename enable_if_c<is_convertible<U, IntBackend>::value>::type* = 0)
       : m_value(static_cast<integer_type>(u)) {}
   template <class U>
   explicit rational_adaptor(const U& u,
                             typename enable_if_c<
                                 boost::multiprecision::detail::is_explicitly_convertible<U, IntBackend>::value && !is_convertible<U, IntBackend>::value>::type* = 0)
       : m_value(IntBackend(u)) {}
   template <class U>
   typename enable_if_c<(boost::multiprecision::detail::is_explicitly_convertible<U, IntBackend>::value && !is_arithmetic<U>::value), rational_adaptor&>::type operator=(const U& u)
   {
      m_value = IntBackend(u);
      return *this;
   }

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
   rational_adaptor(rational_adaptor&& o) BOOST_MP_NOEXCEPT_IF(noexcept(rational_type(std::declval<rational_type>()))) : m_value(static_cast<rational_type&&>(o.m_value))
   {}
   rational_adaptor(IntBackend&& o) BOOST_MP_NOEXCEPT_IF(noexcept(rational_type(std::declval<IntBackend>()))) : m_value(static_cast<IntBackend&&>(o)) {}
   rational_adaptor& operator=(rational_adaptor&& o) BOOST_MP_NOEXCEPT_IF(noexcept(std::declval<rational_type&>() = std::declval<rational_type>()))
   {
      m_value = static_cast<rational_type&&>(o.m_value);
      return *this;
   }
#endif
   rational_adaptor& operator=(const rational_adaptor& o)
   {
      m_value = o.m_value;
      return *this;
   }
   rational_adaptor& operator=(const IntBackend& o)
   {
      m_value = o;
      return *this;
   }
   template <class Int>
   typename enable_if<is_integral<Int>, rational_adaptor&>::type operator=(Int i)
   {
      m_value = i;
      return *this;
   }
   template <class Float>
   typename enable_if<is_floating_point<Float>, rational_adaptor&>::type operator=(Float i)
   {
      int   e;
      Float f = std::frexp(i, &e);
      f       = std::ldexp(f, std::numeric_limits<Float>::digits);
      e -= std::numeric_limits<Float>::digits;
      integer_type num(f);
      integer_type denom(1u);
      if (e > 0)
      {
         num <<= e;
      }
      else if (e < 0)
      {
         denom <<= -e;
      }
      m_value.assign(num, denom);
      return *this;
   }
   rational_adaptor& operator=(const char* s)
   {
      std::string                        s1;
      multiprecision::number<IntBackend> v1, v2;
      char                               c;
      bool                               have_hex = false;
      const char*                        p        = s; // saved for later

      while ((0 != (c = *s)) && (c == 'x' || c == 'X' || c == '-' || c == '+' || (c >= '0' && c <= '9') || (have_hex && (c >= 'a' && c <= 'f')) || (have_hex && (c >= 'A' && c <= 'F'))))
      {
         if (c == 'x' || c == 'X')
            have_hex = true;
         s1.append(1, c);
         ++s;
      }
      v1.assign(s1);
      s1.erase();
      if (c == '/')
      {
         ++s;
         while ((0 != (c = *s)) && (c == 'x' || c == 'X' || c == '-' || c == '+' || (c >= '0' && c <= '9') || (have_hex && (c >= 'a' && c <= 'f')) || (have_hex && (c >= 'A' && c <= 'F'))))
         {
            if (c == 'x' || c == 'X')
               have_hex = true;
            s1.append(1, c);
            ++s;
         }
         v2.assign(s1);
      }
      else
         v2 = 1;
      if (*s)
      {
         BOOST_THROW_EXCEPTION(std::runtime_error(std::string("Could not parse the string \"") + p + std::string("\" as a valid rational number.")));
      }
      data().assign(v1, v2);
      return *this;
   }
   void swap(rational_adaptor& o)
   {
      std::swap(m_value, o.m_value);
   }
   std::string str(std::streamsize digits, std::ios_base::fmtflags f) const
   {
      //
      // We format the string ourselves so we can match what GMP's mpq type does:
      //
      std::string result = data().numerator().str(digits, f);
      if (data().denominator() != 1)
      {
         result.append(1, '/');
         result.append(data().denominator().str(digits, f));
      }
      return result;
   }
   void negate()
   {
      m_value = -m_value;
   }
   int compare(const rational_adaptor& o) const
   {
      return m_value > o.m_value ? 1 : (m_value < o.m_value ? -1 : 0);
   }
   template <class Arithmatic>
   typename enable_if_c<is_arithmetic<Arithmatic>::value && !is_floating_point<Arithmatic>::value, int>::type compare(Arithmatic i) const
   {
      return m_value > i ? 1 : (m_value < i ? -1 : 0);
   }
   template <class Arithmatic>
   typename enable_if_c<is_floating_point<Arithmatic>::value, int>::type compare(Arithmatic i) const
   {
      rational_adaptor r;
      r = i;
      return this->compare(r);
   }
   rational_type&       data() { return m_value; }
   const rational_type& data() const { return m_value; }

   template <class Archive>
   void serialize(Archive& ar, const mpl::true_&)
   {
      // Saving
      integer_type n(m_value.numerator()), d(m_value.denominator());
      ar&          boost::make_nvp("numerator", n);
      ar&          boost::make_nvp("denominator", d);
   }
   template <class Archive>
   void serialize(Archive& ar, const mpl::false_&)
   {
      // Loading
      integer_type n, d;
      ar&          boost::make_nvp("numerator", n);
      ar&          boost::make_nvp("denominator", d);
      m_value.assign(n, d);
   }
   template <class Archive>
   void serialize(Archive& ar, const unsigned int /*version*/)
   {
      typedef typename Archive::is_saving tag;
      serialize(ar, tag());
   }

 private:
   rational_type m_value;
};

template <class IntBackend>
inline void eval_add(rational_adaptor<IntBackend>& result, const rational_adaptor<IntBackend>& o)
{
   result.data() += o.data();
}
template <class IntBackend>
inline void eval_subtract(rational_adaptor<IntBackend>& result, const rational_adaptor<IntBackend>& o)
{
   result.data() -= o.data();
}
template <class IntBackend>
inline void eval_multiply(rational_adaptor<IntBackend>& result, const rational_adaptor<IntBackend>& o)
{
   result.data() *= o.data();
}
template <class IntBackend>
inline void eval_divide(rational_adaptor<IntBackend>& result, const rational_adaptor<IntBackend>& o)
{
   using default_ops::eval_is_zero;
   if (eval_is_zero(o))
   {
      BOOST_THROW_EXCEPTION(std::overflow_error("Divide by zero."));
   }
   result.data() /= o.data();
}

template <class R, class IntBackend>
inline typename enable_if_c<number_category<R>::value == number_kind_floating_point>::type eval_convert_to(R* result, const rational_adaptor<IntBackend>& backend)
{
   //
   // The generic conversion is as good as anything we can write here:
   //
   ::boost::multiprecision::detail::generic_convert_rational_to_float(*result, backend);
}

template <class R, class IntBackend>
inline typename enable_if_c<(number_category<R>::value != number_kind_integer) && (number_category<R>::value != number_kind_floating_point)>::type eval_convert_to(R* result, const rational_adaptor<IntBackend>& backend)
{
   typedef typename component_type<number<rational_adaptor<IntBackend> > >::type comp_t;
   comp_t                                                                        num(backend.data().numerator());
   comp_t                                                                        denom(backend.data().denominator());
   *result = num.template convert_to<R>();
   *result /= denom.template convert_to<R>();
}

template <class R, class IntBackend>
inline typename enable_if_c<number_category<R>::value == number_kind_integer>::type eval_convert_to(R* result, const rational_adaptor<IntBackend>& backend)
{
   typedef typename component_type<number<rational_adaptor<IntBackend> > >::type comp_t;
   comp_t                                                                        t = backend.data().numerator();
   t /= backend.data().denominator();
   *result = t.template convert_to<R>();
}

template <class IntBackend>
inline bool eval_is_zero(const rational_adaptor<IntBackend>& val)
{
   using default_ops::eval_is_zero;
   return eval_is_zero(val.data().numerator().backend());
}
template <class IntBackend>
inline int eval_get_sign(const rational_adaptor<IntBackend>& val)
{
   using default_ops::eval_get_sign;
   return eval_get_sign(val.data().numerator().backend());
}

template <class IntBackend, class V>
inline void assign_components(rational_adaptor<IntBackend>& result, const V& v1, const V& v2)
{
   result.data().assign(v1, v2);
}

template <class IntBackend>
inline std::size_t hash_value(const rational_adaptor<IntBackend>& val)
{
   std::size_t result = hash_value(val.data().numerator());
   boost::hash_combine(result, val.data().denominator());
   return result;
}

} // namespace backends

template <class IntBackend>
struct expression_template_default<backends::rational_adaptor<IntBackend> > : public expression_template_default<IntBackend>
{};

template <class IntBackend>
struct number_category<backends::rational_adaptor<IntBackend> > : public mpl::int_<number_kind_rational>
{};

using boost::multiprecision::backends::rational_adaptor;

template <class Backend, expression_template_option ExpressionTemplates>
struct component_type<number<backends::rational_adaptor<Backend>, ExpressionTemplates> >
{
   typedef number<Backend, ExpressionTemplates> type;
};

template <class IntBackend, expression_template_option ET>
inline number<IntBackend, ET> numerator(const number<rational_adaptor<IntBackend>, ET>& val)
{
   return val.backend().data().numerator();
}
template <class IntBackend, expression_template_option ET>
inline number<IntBackend, ET> denominator(const number<rational_adaptor<IntBackend>, ET>& val)
{
   return val.backend().data().denominator();
}

#ifdef BOOST_NO_SFINAE_EXPR

namespace detail {

template <class U, class IntBackend>
struct is_explicitly_convertible<U, rational_adaptor<IntBackend> > : public is_explicitly_convertible<U, IntBackend>
{};

} // namespace detail

#endif

}} // namespace boost::multiprecision

namespace std {

template <class IntBackend, boost::multiprecision::expression_template_option ExpressionTemplates>
class numeric_limits<boost::multiprecision::number<boost::multiprecision::rational_adaptor<IntBackend>, ExpressionTemplates> > : public std::numeric_limits<boost::multiprecision::number<IntBackend, ExpressionTemplates> >
{
   typedef std::numeric_limits<boost::multiprecision::number<IntBackend> >                     base_type;
   typedef boost::multiprecision::number<boost::multiprecision::rational_adaptor<IntBackend> > number_type;

 public:
   BOOST_STATIC_CONSTEXPR bool is_integer = false;
   BOOST_STATIC_CONSTEXPR bool is_exact   = true;
   BOOST_STATIC_CONSTEXPR      number_type(min)() { return (base_type::min)(); }
   BOOST_STATIC_CONSTEXPR      number_type(max)() { return (base_type::max)(); }
   BOOST_STATIC_CONSTEXPR number_type lowest() { return -(max)(); }
   BOOST_STATIC_CONSTEXPR number_type epsilon() { return base_type::epsilon(); }
   BOOST_STATIC_CONSTEXPR number_type round_error() { return epsilon() / 2; }
   BOOST_STATIC_CONSTEXPR number_type infinity() { return base_type::infinity(); }
   BOOST_STATIC_CONSTEXPR number_type quiet_NaN() { return base_type::quiet_NaN(); }
   BOOST_STATIC_CONSTEXPR number_type signaling_NaN() { return base_type::signaling_NaN(); }
   BOOST_STATIC_CONSTEXPR number_type denorm_min() { return base_type::denorm_min(); }
};

#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION

template <class IntBackend, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::rational_adaptor<IntBackend>, ExpressionTemplates> >::is_integer;
template <class IntBackend, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::rational_adaptor<IntBackend>, ExpressionTemplates> >::is_exact;

#endif

} // namespace std

#endif

/* rational_adaptor.hpp
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
*/