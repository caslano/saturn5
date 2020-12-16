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
L8Kc1duawQTwZbRPBj6S+zbJvLgIk4ZRDoKNHrx4rvYWjTw6B585SuLX566fOyUHVvrxAcrQD/JbZsznKCsqt6yZBtqF7Hhto2bNm1uvN+JOh3mZV6DPkOsDjCD1SEu/OcN9ltQhZ3Eu/COiypLRW2yC3RMxKtb9iiGnrMI48wveyhmIJvXFn4G8dEsXKikI/XyJHIfleZVHIoaTVDUZX2/Qlj81N0p1YHnlBNyJGFl5ji+u9VoFUy1FjkXly/F2Un7I4oBnUQxrkTJqEKEt1425uIH58p9j2MgXeVr5pcfwO6CpPNo1tN/zDlJ2ypI8z4rEEeopQIsAS1Irtbbaw8lk+KxfN8YwT5KocBLO5Hh6QR/OCSuk9hin8M/fonUPvCDLEqdgYvihShM6Qg3mDfR3/za561ew81RJmktWytWWd/DbtLzU80teOcDUn5dJ7vFzm+VN0/LiiPtFWjgNK5z+ZRIX4qcTk/JC5mdpwKsyYzgoOz8u+vQv6vw58x0nDKMUuJvTh/gglq5mQMoMYG/wee5XAfq2NBkl1jW/GMdtYz8S3pQF8DlyaCXNiX2uKy/2Bo6H/igpP0riPMnKjMhAWxu6r72X9nEZuWUVwR7/vHlYBeBEIR2rcR0NWz8wUu8c+jlJHLfI8UwAdtbNnnhm+SwIkTE9LX+R6TcY63HBudDYysTcuK7Kgw3R11yndY9gOw+qqmDkZbfhWUbfGfp9My+MeRU4THvxxXMp5kb4Dh1TeekVBYf1qss0xJhvBwzeCr5tnjol63pGNnxxpglvxrwQ4lqkYcSGPi/TufDk7xhjK09jJ61SNszNQ+4b6LNl1L0I4hgmfMkanwfw4NT0T3KvbMt+LeGNYY30ktILQAnZaTZu7ZuXDX6Y+76XJgHyU3Ny66z4JcKfsNiLw9BzXOSnZuZSgPJFukn4PcZTN40Kt2CWSwU9l4xcNfY24IlgAWKGq0Xrw4i5cQw+ePnzMx66ik9fPlQ7H3bV6Ke84EHBM9btdiHZ1Tf2rxrrZZwHjhekrMsdwxgfzyK8vlj3HGD3me2mYeU/3DLaW+ROxZ1YlNuoF+WB0vwuFwmfx6oqS8swquC7NnyY0cCIEWLUtUhLp6rc1ObrW3X9+FUjXkecxSEvEsqLtx7snytXjTtxkoRFmkXYxibafm0t1rbTbccf4eUsq/zY5UGMZerxtPC6Q/eFie/SNntJFpQJVMR2dbHypRwkvAlzc146Hq/YEHWnFIDz97GEP4a1p/LTpHRYt6rK6vMnE36XBUnmJ0FUMFOFZfiZrnzXWG8zp4h9P2Vdqq2GF+v8SqPNfuDFng/6qCFmSmab327wh0UeRiGs9UPMEcxvfgfhLxgsV0ng5Wy4dSHKwG9+w/jmsRMWSZW7lpBzaHe51tb/b8Y342keuZUfsm5TQ+vdaf/36JzOIqGNSplhEWiNtcOEL4W1wE+iDDblYaaCRvwnTvgjVjqJW3IQ1GlCSHUbS4SXszzJo4rHJRtuIojzrJXxSiIjZwncSVynitm/MfOTQlDGew0ZXlU5QZBmrNv0rvPbXyEyfBaFiVdWsEjaZi747XG9+R6917tx4cdFGLL/ZHrHRjYwD9T36fivnAQmUBagjO769/FeRfhDOMeCRiD2OOGnkwfP7VznLVjoZGXBXTX1tIP7mba+TyflpSyvkiiPXfxultutjJXb8p83+P0iKIsqddgwdxLJ3/b5pe8b4yaA0ZdUnP0bNxPzm99BZEQsikOoRppQGXSxxPwz3zf070kURHFFeLsWTFwvvm+e8XJhoJOxbjcU6960/xr93mUC0wY+AetyTzH21ilD3xymjpP5fsY63FbadbbVn3KiYwc=
*/