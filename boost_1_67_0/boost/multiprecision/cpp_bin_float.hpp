///////////////////////////////////////////////////////////////
//  Copyright 2013 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MATH_CPP_BIN_FLOAT_HPP
#define BOOST_MATH_CPP_BIN_FLOAT_HPP

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/integer.hpp>
#include <boost/math/special_functions/trunc.hpp>
#include <boost/multiprecision/detail/float_string_cvt.hpp>

//
// Some includes we need from Boost.Math, since we rely on that library to provide these functions:
//
#include <boost/math/special_functions/asinh.hpp>
#include <boost/math/special_functions/acosh.hpp>
#include <boost/math/special_functions/atanh.hpp>
#include <boost/math/special_functions/cbrt.hpp>
#include <boost/math/special_functions/expm1.hpp>
#include <boost/math/special_functions/gamma.hpp>

#ifdef BOOST_HAS_FLOAT128
#include <quadmath.h>
#endif

namespace boost {
namespace multiprecision {
namespace backends {

enum digit_base_type
{
   digit_base_2  = 2,
   digit_base_10 = 10
};

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 4522 6326) // multiple assignment operators specified, comparison of two constants
#endif

namespace detail {

template <class U>
inline typename enable_if_c<is_unsigned<U>::value, bool>::type is_negative(U) { return false; }
template <class S>
inline typename disable_if_c<is_unsigned<S>::value, bool>::type is_negative(S s) { return s < 0; }

template <class Float, int, bool = number_category<Float>::value == number_kind_floating_point>
struct is_cpp_bin_float_implicitly_constructible_from_type
{
   static const bool value = false;
};

template <class Float, int bit_count>
struct is_cpp_bin_float_implicitly_constructible_from_type<Float, bit_count, true>
{
   static const bool value = (std::numeric_limits<Float>::digits <= (int)bit_count) && (std::numeric_limits<Float>::radix == 2) && std::numeric_limits<Float>::is_specialized
#ifdef BOOST_HAS_FLOAT128
                             && !boost::is_same<Float, __float128>::value
#endif
                             && (is_floating_point<Float>::value || is_number<Float>::value);
};

template <class Float, int, bool = number_category<Float>::value == number_kind_floating_point>
struct is_cpp_bin_float_explicitly_constructible_from_type
{
   static const bool value = false;
};

template <class Float, int bit_count>
struct is_cpp_bin_float_explicitly_constructible_from_type<Float, bit_count, true>
{
   static const bool value = (std::numeric_limits<Float>::digits > (int)bit_count) && (std::numeric_limits<Float>::radix == 2) && std::numeric_limits<Float>::is_specialized
#ifdef BOOST_HAS_FLOAT128
                             && !boost::is_same<Float, __float128>::value
#endif
       ;
};

} // namespace detail

template <unsigned Digits, digit_base_type DigitBase = digit_base_10, class Allocator = void, class Exponent = int, Exponent MinExponent = 0, Exponent MaxExponent = 0>
class cpp_bin_float
{
 public:
   static const unsigned                                                                                                                                                          bit_count = DigitBase == digit_base_2 ? Digits : (Digits * 1000uL) / 301uL + (((Digits * 1000uL) % 301) ? 2u : 1u);
   typedef cpp_int_backend<is_void<Allocator>::value ? bit_count : 0, bit_count, is_void<Allocator>::value ? unsigned_magnitude : signed_magnitude, unchecked, Allocator>         rep_type;
   typedef cpp_int_backend<is_void<Allocator>::value ? 2 * bit_count : 0, 2 * bit_count, is_void<Allocator>::value ? unsigned_magnitude : signed_magnitude, unchecked, Allocator> double_rep_type;

   typedef typename rep_type::signed_types              signed_types;
   typedef typename rep_type::unsigned_types            unsigned_types;
   typedef boost::mpl::list<float, double, long double> float_types;
   typedef Exponent                                     exponent_type;

   static const exponent_type max_exponent_limit = boost::integer_traits<exponent_type>::const_max - 2 * static_cast<exponent_type>(bit_count);
   static const exponent_type min_exponent_limit = boost::integer_traits<exponent_type>::const_min + 2 * static_cast<exponent_type>(bit_count);

   BOOST_STATIC_ASSERT_MSG(MinExponent >= min_exponent_limit, "Template parameter MinExponent is too negative for our internal logic to function correctly, sorry!");
   BOOST_STATIC_ASSERT_MSG(MaxExponent <= max_exponent_limit, "Template parameter MaxExponent is too large for our internal logic to function correctly, sorry!");
   BOOST_STATIC_ASSERT_MSG(MinExponent <= 0, "Template parameter MinExponent can not be positive!");
   BOOST_STATIC_ASSERT_MSG(MaxExponent >= 0, "Template parameter MaxExponent can not be negative!");

   static const exponent_type max_exponent = MaxExponent == 0 ? max_exponent_limit : MaxExponent;
   static const exponent_type min_exponent = MinExponent == 0 ? min_exponent_limit : MinExponent;

   static const exponent_type exponent_zero     = max_exponent + 1;
   static const exponent_type exponent_infinity = max_exponent + 2;
   static const exponent_type exponent_nan      = max_exponent + 3;

 private:
   rep_type      m_data;
   exponent_type m_exponent;
   bool          m_sign;

 public:
   cpp_bin_float() BOOST_MP_NOEXCEPT_IF(noexcept(rep_type())) : m_data(), m_exponent(exponent_zero), m_sign(false) {}

   cpp_bin_float(const cpp_bin_float& o) BOOST_MP_NOEXCEPT_IF(noexcept(rep_type(std::declval<const rep_type&>())))
       : m_data(o.m_data), m_exponent(o.m_exponent), m_sign(o.m_sign) {}

   template <unsigned D, digit_base_type B, class A, class E, E MinE, E MaxE>
   cpp_bin_float(const cpp_bin_float<D, B, A, E, MinE, MaxE>& o, typename boost::enable_if_c<(bit_count >= cpp_bin_float<D, B, A, E, MinE, MaxE>::bit_count)>::type const* = 0)
   {
      *this = o;
   }
   template <unsigned D, digit_base_type B, class A, class E, E MinE, E MaxE>
   explicit cpp_bin_float(const cpp_bin_float<D, B, A, E, MinE, MaxE>& o, typename boost::disable_if_c<(bit_count >= cpp_bin_float<D, B, A, E, MinE, MaxE>::bit_count)>::type const* = 0)
       : m_exponent(o.exponent()), m_sign(o.sign())
   {
      *this = o;
   }
   template <class Float>
   cpp_bin_float(const Float& f,
                 typename boost::enable_if_c<detail::is_cpp_bin_float_implicitly_constructible_from_type<Float, bit_count>::value>::type const* = 0)
       : m_data(), m_exponent(0), m_sign(false)
   {
      this->assign_float(f);
   }

   template <class Float>
   explicit cpp_bin_float(const Float& f,
                          typename boost::enable_if_c<detail::is_cpp_bin_float_explicitly_constructible_from_type<Float, bit_count>::value>::type const* = 0)
       : m_data(), m_exponent(0), m_sign(false)
   {
      this->assign_float(f);
   }
#ifdef BOOST_HAS_FLOAT128
   template <class Float>
   cpp_bin_float(const Float& f,
                 typename boost::enable_if_c<
                     boost::is_same<Float, __float128>::value && ((int)bit_count >= 113)>::type const* = 0)
       : m_data(), m_exponent(0), m_sign(false)
   {
      this->assign_float(f);
   }
   template <class Float>
   explicit cpp_bin_float(const Float& f,
                          typename boost::enable_if_c<
                              boost::is_same<Float, __float128>::value && ((int)bit_count < 113)>::type const* = 0)
       : m_data(), m_exponent(0), m_sign(false)
   {
      this->assign_float(f);
   }
#endif
   cpp_bin_float& operator=(const cpp_bin_float& o) BOOST_MP_NOEXCEPT_IF(noexcept(std::declval<rep_type&>() = std::declval<const rep_type&>()))
   {
      m_data     = o.m_data;
      m_exponent = o.m_exponent;
      m_sign     = o.m_sign;
      return *this;
   }

   template <unsigned D, digit_base_type B, class A, class E, E MinE, E MaxE>
   cpp_bin_float& operator=(const cpp_bin_float<D, B, A, E, MinE, MaxE>& f)
   {
      switch (eval_fpclassify(f))
      {
      case FP_ZERO:
         m_data     = limb_type(0);
         m_sign     = f.sign();
         m_exponent = exponent_zero;
         break;
      case FP_NAN:
         m_data     = limb_type(0);
         m_sign     = false;
         m_exponent = exponent_nan;
         break;
         ;
      case FP_INFINITE:
         m_data     = limb_type(0);
         m_sign     = f.sign();
         m_exponent = exponent_infinity;
         break;
      default:
         typename cpp_bin_float<D, B, A, E, MinE, MaxE>::rep_type b(f.bits());
         this->exponent() = f.exponent() + (E)bit_count - (E)cpp_bin_float<D, B, A, E, MinE, MaxE>::bit_count;
         this->sign()     = f.sign();
         copy_and_round(*this, b);
      }
      return *this;
   }
#ifdef BOOST_HAS_FLOAT128
   template <class Float>
   typename boost::enable_if_c<
       (number_category<Float>::value == number_kind_floating_point)
           //&& (std::numeric_limits<Float>::digits <= (int)bit_count)
           && ((std::numeric_limits<Float>::radix == 2) || (boost::is_same<Float, __float128>::value)),
       cpp_bin_float&>::type
   operator=(const Float& f)
#else
   template <class Float>
   typename boost::enable_if_c<
       (number_category<Float>::value == number_kind_floating_point)
           //&& (std::numeric_limits<Float>::digits <= (int)bit_count)
           && (std::numeric_limits<Float>::radix == 2),
       cpp_bin_float&>::type
   operator=(const Float& f)
#endif
   {
      return assign_float(f);
   }

#ifdef BOOST_HAS_FLOAT128
   template <class Float>
   typename boost::enable_if_c<boost::is_same<Float, __float128>::value, cpp_bin_float&>::type assign_float(Float f)
   {
      using default_ops::eval_add;
      typedef typename boost::multiprecision::detail::canonical<int, cpp_bin_float>::type bf_int_type;
      if (f == 0)
      {
         m_data     = limb_type(0);
         m_sign     = (signbitq(f) > 0);
         m_exponent = exponent_zero;
         return *this;
      }
      else if (isnanq(f))
      {
         m_data     = limb_type(0);
         m_sign     = false;
         m_exponent = exponent_nan;
         return *this;
      }
      else if (isinfq(f))
      {
         m_data     = limb_type(0);
         m_sign     = (f < 0);
         m_exponent = exponent_infinity;
         return *this;
      }
      if (f < 0)
      {
         *this = -f;
         this->negate();
         return *this;
      }

      typedef typename mpl::front<unsigned_types>::type ui_type;
      m_data     = static_cast<ui_type>(0u);
      m_sign     = false;
      m_exponent = 0;

      static const int bits = sizeof(int) * CHAR_BIT - 1;
      int              e;
      f = frexpq(f, &e);
      while (f)
      {
         f = ldexpq(f, bits);
         e -= bits;
         int ipart = (int)truncq(f);
         f -= ipart;
         m_exponent += bits;
         cpp_bin_float t;
         t = static_cast<bf_int_type>(ipart);
         eval_add(*this, t);
      }
      m_exponent += static_cast<Exponent>(e);
      return *this;
   }
#endif
#ifdef BOOST_HAS_FLOAT128
   template <class Float>
   typename boost::enable_if_c<is_floating_point<Float>::value && !is_same<Float, __float128>::value, cpp_bin_float&>::type assign_float(Float f)
#else
   template <class Float>
   typename boost::enable_if_c<is_floating_point<Float>::value, cpp_bin_float&>::type assign_float(Float f)
#endif
   {
      BOOST_MATH_STD_USING
      using default_ops::eval_add;
      typedef typename boost::multiprecision::detail::canonical<int, cpp_bin_float>::type bf_int_type;

      switch ((boost::math::fpclassify)(f))
      {
      case FP_ZERO:
         m_data     = limb_type(0);
         m_sign     = ((boost::math::signbit)(f) > 0);
         m_exponent = exponent_zero;
         return *this;
      case FP_NAN:
         m_data     = limb_type(0);
         m_sign     = false;
         m_exponent = exponent_nan;
         return *this;
      case FP_INFINITE:
         m_data     = limb_type(0);
         m_sign     = (f < 0);
         m_exponent = exponent_infinity;
         return *this;
      }
      if (f < 0)
      {
         *this = -f;
         this->negate();
         return *this;
      }

      typedef typename mpl::front<unsigned_types>::type ui_type;
      m_data     = static_cast<ui_type>(0u);
      m_sign     = false;
      m_exponent = 0;

      static const int bits = sizeof(int) * CHAR_BIT - 1;
      int              e;
      f = frexp(f, &e);
      while (f)
      {
         f = ldexp(f, bits);
         e -= bits;
#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
         int ipart = itrunc(f);
#else
         int ipart = static_cast<int>(f);
#endif
         f -= ipart;
         m_exponent += bits;
         cpp_bin_float t;
         t = static_cast<bf_int_type>(ipart);
         eval_add(*this, t);
      }
      m_exponent += static_cast<Exponent>(e);
      return *this;
   }

   template <class Float>
   typename boost::enable_if_c<
       (number_category<Float>::value == number_kind_floating_point) && !boost::is_floating_point<Float>::value && (number_category<Float>::value == number_kind_floating_point),
       cpp_bin_float&>::type
   assign_float(Float f)
   {
      BOOST_MATH_STD_USING
      using default_ops::eval_add;
      using default_ops::eval_convert_to;
      using default_ops::eval_get_sign;
      using default_ops::eval_subtract;

      typedef typename boost::multiprecision::detail::canonical<int, Float>::type         f_int_type;
      typedef typename boost::multiprecision::detail::canonical<int, cpp_bin_float>::type bf_int_type;

      switch (eval_fpclassify(f))
      {
      case FP_ZERO:
         m_data     = limb_type(0);
         m_sign     = (eval_get_sign(f) > 0);
         m_exponent = exponent_zero;
         return *this;
      case FP_NAN:
         m_data     = limb_type(0);
         m_sign     = false;
         m_exponent = exponent_nan;
         return *this;
      case FP_INFINITE:
         m_data     = limb_type(0);
         m_sign     = eval_get_sign(f) < 0;
         m_exponent = exponent_infinity;
         return *this;
      }
      if (eval_get_sign(f) < 0)
      {
         f.negate();
         *this = f;
         this->negate();
         return *this;
      }

      typedef typename mpl::front<unsigned_types>::type ui_type;
      m_data     = static_cast<ui_type>(0u);
      m_sign     = false;
      m_exponent = 0;

      static const int bits = sizeof(int) * CHAR_BIT - 1;
      int              e;
      eval_frexp(f, f, &e);
      while (eval_get_sign(f) != 0)
      {
         eval_ldexp(f, f, bits);
         e -= bits;
         int ipart;
         eval_convert_to(&ipart, f);
         eval_subtract(f, static_cast<f_int_type>(ipart));
         m_exponent += bits;
         eval_add(*this, static_cast<bf_int_type>(ipart));
      }
      m_exponent += e;
      if (m_exponent > max_exponent)
         m_exponent = exponent_infinity;
      if (m_exponent < min_exponent)
      {
         m_data     = limb_type(0u);
         m_exponent = exponent_zero;
         m_sign     = (eval_get_sign(f) > 0);
      }
      else if (eval_get_sign(m_data) == 0)
      {
         m_exponent = exponent_zero;
         m_sign     = (eval_get_sign(f) > 0);
      }
      return *this;
   }
   template <class B, expression_template_option et>
   cpp_bin_float& assign_float(const number<B, et>& f)
   {
      return assign_float(f.backend());
   }
   
   template <class I>
   typename boost::enable_if<is_integral<I>, cpp_bin_float&>::type operator=(const I& i)
   {
      using default_ops::eval_bit_test;
      if (!i)
      {
         m_data     = static_cast<limb_type>(0);
         m_exponent = exponent_zero;
         m_sign     = false;
      }
      else
      {
         typedef typename make_unsigned<I>::type                                            ui_type;
         ui_type                                                                            fi = static_cast<ui_type>(boost::multiprecision::detail::unsigned_abs(i));
         typedef typename boost::multiprecision::detail::canonical<ui_type, rep_type>::type ar_type;
         m_data         = static_cast<ar_type>(fi);
         unsigned shift = msb(fi);
         if (shift >= bit_count)
         {
            m_exponent = static_cast<Exponent>(shift);
            m_data     = static_cast<ar_type>(fi >> (shift + 1 - bit_count));
         }
         else
         {
            m_exponent = static_cast<Exponent>(shift);
            eval_left_shift(m_data, bit_count - shift - 1);
         }
         BOOST_ASSERT(eval_bit_test(m_data, bit_count - 1));
         m_sign = detail::is_negative(i);
      }
      return *this;
   }

   cpp_bin_float& operator=(const char* s);

   void swap(cpp_bin_float& o) BOOST_NOEXCEPT
   {
      m_data.swap(o.m_data);
      std::swap(m_exponent, o.m_exponent);
      std::swap(m_sign, o.m_sign);
   }

   std::string str(std::streamsize dig, std::ios_base::fmtflags f) const;

   void negate()
   {
      if (m_exponent != exponent_nan)
         m_sign = !m_sign;
   }

   int compare(const cpp_bin_float& o) const BOOST_NOEXCEPT
   {
      if (m_sign != o.m_sign)
         return (m_exponent == exponent_zero) && (m_exponent == o.m_exponent) ? 0 : m_sign ? -1 : 1;
      int result;
      if (m_exponent == exponent_nan)
         return -1;
      else if (m_exponent != o.m_exponent)
      {
         if (m_exponent == exponent_zero)
            result = -1;
         else if (o.m_exponent == exponent_zero)
            result = 1;
         else
            result = m_exponent > o.m_exponent ? 1 : -1;
      }
      else
         result = m_data.compare(o.m_data);
      if (m_sign)
         result = -result;
      return result;
   }
   template <class A>
   int compare(const A& o) const BOOST_NOEXCEPT
   {
      cpp_bin_float b;
      b = o;
      return compare(b);
   }

   rep_type&            bits() { return m_data; }
   const rep_type&      bits() const { return m_data; }
   exponent_type&       exponent() { return m_exponent; }
   const exponent_type& exponent() const { return m_exponent; }
   bool&                sign() { return m_sign; }
   const bool&          sign() const { return m_sign; }
   void                 check_invariants()
   {
      using default_ops::eval_bit_test;
      using default_ops::eval_is_zero;
      if ((m_exponent <= max_exponent) && (m_exponent >= min_exponent))
      {
         BOOST_ASSERT(eval_bit_test(m_data, bit_count - 1));
      }
      else
      {
         BOOST_ASSERT(m_exponent > max_exponent);
         BOOST_ASSERT(m_exponent <= exponent_nan);
         BOOST_ASSERT(eval_is_zero(m_data));
      }
   }
   template <class Archive>
   void serialize(Archive& ar, const unsigned int /*version*/)
   {
      ar& boost::make_nvp("data", m_data);
      ar& boost::make_nvp("exponent", m_exponent);
      ar& boost::make_nvp("sign", m_sign);
   }
};

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE, class Int>
inline void copy_and_round(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& res, Int& arg, int bits_to_keep = cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count)
{
   // Precondition: exponent of res must have been set before this function is called
   // as we may need to adjust it based on how many bits_to_keep in arg are set.
   using default_ops::eval_bit_test;
   using default_ops::eval_get_sign;
   using default_ops::eval_increment;
   using default_ops::eval_left_shift;
   using default_ops::eval_lsb;
   using default_ops::eval_msb;
   using default_ops::eval_right_shift;

   // cancellation may have resulted in arg being all zeros:
   if (eval_get_sign(arg) == 0)
   {
      res.exponent() = cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_zero;
      res.sign()     = false;
      res.bits()     = static_cast<limb_type>(0u);
      return;
   }
   int msb = eval_msb(arg);
   if (static_cast<int>(bits_to_keep) > msb + 1)
   {
      // Must have had cancellation in subtraction,
      // or be converting from a narrower type, so shift left:
      res.bits() = arg;
      eval_left_shift(res.bits(), bits_to_keep - msb - 1);
      res.exponent() -= static_cast<Exponent>(bits_to_keep - msb - 1);
   }
   else if (static_cast<int>(bits_to_keep) < msb + 1)
   {
      // We have more bits_to_keep than we need, so round as required,
      // first get the rounding bit:
      bool roundup = eval_bit_test(arg, msb - bits_to_keep);
      // Then check for a tie:
      if (roundup && (msb - bits_to_keep == (int)eval_lsb(arg)))
      {
         // Ties round towards even:
         if (!eval_bit_test(arg, msb - bits_to_keep + 1))
            roundup = false;
      }
      // Shift off the bits_to_keep we don't need:
      eval_right_shift(arg, msb - bits_to_keep + 1);
      res.exponent() += static_cast<Exponent>(msb - bits_to_keep + 1);
      if (roundup)
      {
         eval_increment(arg);
         if (bits_to_keep)
         {
            if (eval_bit_test(arg, bits_to_keep))
            {
               // This happens very very rairly, all the bits left after
               // truncation must be 1's and we're rounding up an order of magnitude:
               eval_right_shift(arg, 1u);
               ++res.exponent();
            }
         }
         else
         {
            // We get here when bits_to_keep is zero but we're rounding up,
            // as a result we end up with a single digit that is a 1:
            ++bits_to_keep;
         }
      }
      if (bits_to_keep != cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count)
      {
         // Normalize result when we're rounding to fewer bits than we can hold, only happens in conversions
         // to narrower types:
         eval_left_shift(arg, cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count - bits_to_keep);
         res.exponent() -= static_cast<Exponent>(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count - bits_to_keep);
      }
      res.bits() = arg;
   }
   else
   {
      res.bits() = arg;
   }
   if (!bits_to_keep && !res.bits().limbs()[0])
   {
      // We're keeping zero bits and did not round up, so result is zero:
      res.exponent() = cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_zero;
      return;
   }
   // Result must be normalized:
   BOOST_ASSERT(((int)eval_msb(res.bits()) == cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count - 1));

   if (res.exponent() > cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::max_exponent)
   {
      // Overflow:
      res.exponent() = cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_infinity;
      res.bits()     = static_cast<limb_type>(0u);
   }
   else if (res.exponent() < cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::min_exponent)
   {
      // Underflow:
      res.exponent() = cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_zero;
      res.bits()     = static_cast<limb_type>(0u);
   }
}

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE>
inline void do_eval_add(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& res, const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& a, const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& b)
{
   if (a.exponent() < b.exponent())
   {
      bool s = a.sign();
      do_eval_add(res, b, a);
      if (res.sign() != s)
         res.negate();
      return;
   }

   using default_ops::eval_add;
   using default_ops::eval_bit_test;

   typedef typename cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_type exponent_type;

   typename cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::double_rep_type dt;

   // Special cases first:
   switch (a.exponent())
   {
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_zero:
   {
      bool s     = a.sign();
      res        = b;
      res.sign() = s;
      return;
   }
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_infinity:
      if (b.exponent() == cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_nan)
         res = b;
      else
         res = a;
      return; // result is still infinite.
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_nan:
      res = a;
      return; // result is still a NaN.
   }
   switch (b.exponent())
   {
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_zero:
      res = a;
      return;
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_infinity:
      res = b;
      if (res.sign())
         res.negate();
      return; // result is infinite.
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_nan:
      res = b;
      return; // result is a NaN.
   }

   BOOST_STATIC_ASSERT(boost::integer_traits<exponent_type>::const_max - cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count > cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::max_exponent);

   bool s = a.sign();
   dt     = a.bits();
   if (a.exponent() > (int)cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count + b.exponent())
   {
      res.exponent() = a.exponent();
   }
   else
   {
      exponent_type e_diff = a.exponent() - b.exponent();
      BOOST_ASSERT(e_diff >= 0);
      eval_left_shift(dt, e_diff);
      res.exponent() = a.exponent() - e_diff;
      eval_add(dt, b.bits());
   }

   copy_and_round(res, dt);
   res.check_invariants();
   if (res.sign() != s)
      res.negate();
}

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE>
inline void do_eval_subtract(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& res, const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& a, const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& b)
{
   using default_ops::eval_bit_test;
   using default_ops::eval_decrement;
   using default_ops::eval_subtract;

   typename cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::double_rep_type dt;

   // Special cases first:
   switch (a.exponent())
   {
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_zero:
      if (b.exponent() == cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_nan)
         res = std::numeric_limits<number<cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> > >::quiet_NaN().backend();
      else
      {
         bool s = a.sign();
         res    = b;
         if (res.exponent() == cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_zero)
            res.sign() = false;
         else if (res.sign() == s)
            res.negate();
      }
      return;
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_infinity:
      if ((b.exponent() == cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_nan) || (b.exponent() == cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_infinity))
         res = std::numeric_limits<number<cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> > >::quiet_NaN().backend();
      else
         res = a;
      return;
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_nan:
      res = a;
      return; // result is still a NaN.
   }
   switch (b.exponent())
   {
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_zero:
      res = a;
      return;
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_infinity:
      res.exponent() = cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_infinity;
      res.sign()     = !a.sign();
      res.bits()     = static_cast<limb_type>(0u);
      return; // result is a NaN.
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_nan:
      res = b;
      return; // result is still a NaN.
   }

   bool s = a.sign();
   if ((a.exponent() > b.exponent()) || ((a.exponent() == b.exponent()) && a.bits().compare(b.bits()) >= 0))
   {
      dt = a.bits();
      if (a.exponent() <= (int)cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count + b.exponent())
      {
         typename cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_type e_diff = a.exponent() - b.exponent();
         eval_left_shift(dt, e_diff);
         res.exponent() = a.exponent() - e_diff;
         eval_subtract(dt, b.bits());
      }
      else if (a.exponent() == (int)cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count + b.exponent() + 1)
      {
         if (eval_lsb(b.bits()) != cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count - 1)
         {
            eval_left_shift(dt, 1);
            eval_decrement(dt);
            res.exponent() = a.exponent() - 1;
         }
         else
            res.exponent() = a.exponent();
      }
      else
         res.exponent() = a.exponent();
   }
   else
   {
      dt = b.bits();
      if (b.exponent() <= (int)cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count + a.exponent())
      {
         typename cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_type e_diff = a.exponent() - b.exponent();
         eval_left_shift(dt, -e_diff);
         res.exponent() = b.exponent() + e_diff;
         eval_subtract(dt, a.bits());
      }
      else if (b.exponent() == (int)cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count + a.exponent() + 1)
      {
         if (eval_lsb(a.bits()) != cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count - 1)
         {
            eval_left_shift(dt, 1);
            eval_decrement(dt);
            res.exponent() = b.exponent() - 1;
         }
         else
            res.exponent() = b.exponent();
      }
      else
         res.exponent() = b.exponent();
      s = !s;
   }

   copy_and_round(res, dt);
   if (res.exponent() == cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_zero)
      res.sign() = false;
   else if (res.sign() != s)
      res.negate();
   res.check_invariants();
}

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE>
inline void eval_add(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& res, const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& a, const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& b)
{
   if (a.sign() == b.sign())
      do_eval_add(res, a, b);
   else
      do_eval_subtract(res, a, b);
}

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE>
inline void eval_add(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& res, const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& a)
{
   return eval_add(res, res, a);
}

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE>
inline void eval_subtract(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& res, const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& a, const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& b)
{
   if (a.sign() != b.sign())
      do_eval_add(res, a, b);
   else
      do_eval_subtract(res, a, b);
}

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE>
inline void eval_subtract(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& res, const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& a)
{
   return eval_subtract(res, res, a);
}

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE>
inline void eval_multiply(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& res, const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& a, const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& b)
{
   using default_ops::eval_bit_test;
   using default_ops::eval_multiply;

   // Special cases first:
   switch (a.exponent())
   {
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_zero:
   {
      if (b.exponent() == cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_nan)
         res = b;
      else if (b.exponent() == cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_infinity)
         res = std::numeric_limits<number<cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> > >::quiet_NaN().backend();
      else
      {
         bool s     = a.sign() != b.sign();
         res        = a;
         res.sign() = s;
      }
      return;
   }
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_infinity:
      switch (b.exponent())
      {
      case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_zero:
         res = std::numeric_limits<number<cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> > >::quiet_NaN().backend();
         break;
      case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_nan:
         res = b;
         break;
      default:
         bool s     = a.sign() != b.sign();
         res        = a;
         res.sign() = s;
         break;
      }
      return;
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_nan:
      res = a;
      return;
   }
   if (b.exponent() > cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::max_exponent)
   {
      bool s     = a.sign() != b.sign();
      res        = b;
      res.sign() = s;
      return;
   }
   if ((a.exponent() > 0) && (b.exponent() > 0))
   {
      if (cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::max_exponent + 2 - a.exponent() < b.exponent())
      {
         // We will certainly overflow:
         bool s         = a.sign() != b.sign();
         res.exponent() = cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_infinity;
         res.sign()     = s;
         res.bits()     = static_cast<limb_type>(0u);
         return;
      }
   }
   if ((a.exponent() < 0) && (b.exponent() < 0))
   {
      if (cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::min_exponent - 2 - a.exponent() > b.exponent())
      {
         // We will certainly underflow:
         res.exponent() = cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_zero;
         res.sign()     = a.sign() != b.sign();
         res.bits()     = static_cast<limb_type>(0u);
         return;
      }
   }

   typename cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::double_rep_type dt;
   eval_multiply(dt, a.bits(), b.bits());
   res.exponent() = a.exponent() + b.exponent() - (Exponent)cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count + 1;
   copy_and_round(res, dt);
   res.check_invariants();
   res.sign() = a.sign() != b.sign();
}

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE>
inline void eval_multiply(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& res, const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& a)
{
   eval_multiply(res, res, a);
}

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE, class U>
inline typename enable_if_c<is_unsigned<U>::value>::type eval_multiply(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& res, const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& a, const U& b)
{
   using default_ops::eval_bit_test;
   using default_ops::eval_multiply;

   // Special cases first:
   switch (a.exponent())
   {
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_zero:
   {
      bool s     = a.sign();
      res        = a;
      res.sign() = s;
      return;
   }
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_infinity:
      if (b == 0)
         res = std::numeric_limits<number<cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> > >::quiet_NaN().backend();
      else
         res = a;
      return;
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_nan:
      res = a;
      return;
   }

   typename cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::double_rep_type                                                                     dt;
   typedef typename boost::multiprecision::detail::canonical<U, typename cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::double_rep_type>::type canon_ui_type;
   eval_multiply(dt, a.bits(), static_cast<canon_ui_type>(b));
   res.exponent() = a.exponent();
   copy_and_round(res, dt);
   res.check_invariants();
   res.sign() = a.sign();
}

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE, class U>
inline typename enable_if_c<is_unsigned<U>::value>::type eval_multiply(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& res, const U& b)
{
   eval_multiply(res, res, b);
}

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE, class S>
inline typename enable_if_c<is_signed<S>::value>::type eval_multiply(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& res, const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& a, const S& b)
{
   typedef typename make_unsigned<S>::type ui_type;
   eval_multiply(res, a, static_cast<ui_type>(boost::multiprecision::detail::unsigned_abs(b)));
   if (b < 0)
      res.negate();
}

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE, class S>
inline typename enable_if_c<is_signed<S>::value>::type eval_multiply(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& res, const S& b)
{
   eval_multiply(res, res, b);
}

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE>
inline void eval_divide(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& res, const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& u, const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& v)
{
#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 6326) // comparison of two constants
#endif
   using default_ops::eval_bit_test;
   using default_ops::eval_get_sign;
   using default_ops::eval_increment;
   using default_ops::eval_qr;
   using default_ops::eval_subtract;

   //
   // Special cases first:
   //
   switch (u.exponent())
   {
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_zero:
   {
      switch (v.exponent())
      {
      case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_zero:
      case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_nan:
         res = std::numeric_limits<number<cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> > >::quiet_NaN().backend();
         return;
      }
      bool s     = u.sign() != v.sign();
      res        = u;
      res.sign() = s;
      return;
   }
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_infinity:
   {
      switch (v.exponent())
      {
      case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_infinity:
      case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_nan:
         res = std::numeric_limits<number<cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> > >::quiet_NaN().backend();
         return;
      }
      bool s     = u.sign() != v.sign();
      res        = u;
      res.sign() = s;
      return;
   }
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_nan:
      res = std::numeric_limits<number<cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> > >::quiet_NaN().backend();
      return;
   }
   switch (v.exponent())
   {
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_zero:
   {
      bool s     = u.sign() != v.sign();
      res        = std::numeric_limits<number<cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> > >::infinity().backend();
      res.sign() = s;
      return;
   }
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_infinity:
      res.exponent() = cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_zero;
      res.bits()     = limb_type(0);
      res.sign()     = u.sign() != v.sign();
      return;
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_nan:
      res = std::numeric_limits<number<cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> > >::quiet_NaN().backend();
      return;
   }

   // We can scale u and v so that both are integers, then perform integer
   // division to obtain quotient q and remainder r, such that:
   //
   // q * v + r = u
   //
   // and hense:
   //
   // q + r/v = u/v
   //
   // From this, assuming q has cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count
   // bits we only need to determine whether
   // r/v is less than, equal to, or greater than 0.5 to determine rounding -
   // this we can do with a shift and comparison.
   //
   // We can set the exponent and sign of the result up front:
   //
   if ((v.exponent() < 0) && (u.exponent() > 0))
   {
      // Check for overflow:
      if (cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::max_exponent + v.exponent() < u.exponent() - 1)
      {
         res.exponent() = cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_infinity;
         res.sign()     = u.sign() != v.sign();
         res.bits()     = static_cast<limb_type>(0u);
         return;
      }
   }
   else if ((v.exponent() > 0) && (u.exponent() < 0))
   {
      // Check for underflow:
      if (cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::min_exponent + v.exponent() > u.exponent())
      {
         // We will certainly underflow:
         res.exponent() = cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_zero;
         res.sign()     = u.sign() != v.sign();
         res.bits()     = static_cast<limb_type>(0u);
         return;
      }
   }
   res.exponent() = u.exponent() - v.exponent() - 1;
   res.sign()     = u.sign() != v.sign();
   //
   // Now get the quotient and remainder:
   //
   typename cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::double_rep_type t(u.bits()), t2(v.bits()), q, r;
   eval_left_shift(t, cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count);
   eval_qr(t, t2, q, r);
   //
   // We now have either "cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count"
   // or "cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count+1" significant
   // bits in q.
   //
   static const unsigned limb_bits = sizeof(limb_type) * CHAR_BIT;
   if (eval_bit_test(q, cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count))
   {
      //
      // OK we have cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count+1 bits,
      // so we already have rounding info,
      // we just need to changes things if the last bit is 1 and either the
      // remainder is non-zero (ie we do not have a tie) or the quotient would
      // be odd if it were shifted to the correct number of bits (ie a tiebreak).
      //
      BOOST_ASSERT((eval_msb(q) == cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count));
      if ((q.limbs()[0] & 1u) && (eval_get_sign(r) || (q.limbs()[0] & 2u)))
      {
         eval_increment(q);
      }
   }
   else
   {
      //
      // We have exactly "cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count" bits in q.
      // Get rounding info, which we can get by comparing 2r with v.
      // We want to call copy_and_round to handle rounding and general cleanup,
      // so we'll left shift q and add some fake digits on the end to represent
      // how we'll be rounding.
      //
      BOOST_ASSERT((eval_msb(q) == cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count - 1));
      static const unsigned lshift = (cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count < limb_bits) ? 2 : limb_bits;
      eval_left_shift(q, lshift);
      res.exponent() -= lshift;
      eval_left_shift(r, 1u);
      int c = r.compare(v.bits());
      if (c == 0)
         q.limbs()[0] |= static_cast<limb_type>(1u) << (lshift - 1);
      else if (c > 0)
         q.limbs()[0] |= (static_cast<limb_type>(1u) << (lshift - 1)) + static_cast<limb_type>(1u);
   }
   copy_and_round(res, q);
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
}

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE>
inline void eval_divide(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& res, const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& arg)
{
   eval_divide(res, res, arg);
}

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE, class U>
inline typename enable_if_c<is_unsigned<U>::value>::type eval_divide(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& res, const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& u, const U& v)
{
#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 6326) // comparison of two constants
#endif
   using default_ops::eval_bit_test;
   using default_ops::eval_get_sign;
   using default_ops::eval_increment;
   using default_ops::eval_qr;
   using default_ops::eval_subtract;

   //
   // Special cases first:
   //
   switch (u.exponent())
   {
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_zero:
   {
      if (v == 0)
      {
         res = std::numeric_limits<number<cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> > >::quiet_NaN().backend();
         return;
      }
      bool s     = u.sign() != (v < 0);
      res        = u;
      res.sign() = s;
      return;
   }
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_infinity:
      res = u;
      return;
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_nan:
      res = std::numeric_limits<number<cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> > >::quiet_NaN().backend();
      return;
   }
   if (v == 0)
   {
      bool s     = u.sign();
      res        = std::numeric_limits<number<cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> > >::infinity().backend();
      res.sign() = s;
      return;
   }

   // We can scale u and v so that both are integers, then perform integer
   // division to obtain quotient q and remainder r, such that:
   //
   // q * v + r = u
   //
   // and hense:
   //
   // q + r/v = u/v
   //
   // From this, assuming q has "cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count" cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count, we only need to determine whether
   // r/v is less than, equal to, or greater than 0.5 to determine rounding -
   // this we can do with a shift and comparison.
   //
   // We can set the exponent and sign of the result up front:
   //
   int gb         = msb(v);
   res.exponent() = u.exponent() - static_cast<Exponent>(gb) - static_cast<Exponent>(1);
   res.sign()     = u.sign();
   //
   // Now get the quotient and remainder:
   //
   typename cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::double_rep_type t(u.bits()), q, r;
   eval_left_shift(t, gb + 1);
   eval_qr(t, number<typename cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::double_rep_type>::canonical_value(v), q, r);
   //
   // We now have either "cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count" or "cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count+1" significant cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count in q.
   //
   static const unsigned limb_bits = sizeof(limb_type) * CHAR_BIT;
   if (eval_bit_test(q, cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count))
   {
      //
      // OK we have cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count+1 cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count, so we already have rounding info,
      // we just need to changes things if the last bit is 1 and the
      // remainder is non-zero (ie we do not have a tie).
      //
      BOOST_ASSERT((eval_msb(q) == cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count));
      if ((q.limbs()[0] & 1u) && eval_get_sign(r))
      {
         eval_increment(q);
      }
   }
   else
   {
      //
      // We have exactly "cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count" cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count in q.
      // Get rounding info, which we can get by comparing 2r with v.
      // We want to call copy_and_round to handle rounding and general cleanup,
      // so we'll left shift q and add some fake cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count on the end to represent
      // how we'll be rounding.
      //
      BOOST_ASSERT((eval_msb(q) == cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count - 1));
      static const unsigned lshift = cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count < limb_bits ? 2 : limb_bits;
      eval_left_shift(q, lshift);
      res.exponent() -= lshift;
      eval_left_shift(r, 1u);
      int c = r.compare(number<typename cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::double_rep_type>::canonical_value(v));
      if (c == 0)
         q.limbs()[0] |= static_cast<limb_type>(1u) << (lshift - 1);
      else if (c > 0)
         q.limbs()[0] |= (static_cast<limb_type>(1u) << (lshift - 1)) + static_cast<limb_type>(1u);
   }
   copy_and_round(res, q);
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
}

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE, class U>
inline typename enable_if_c<is_unsigned<U>::value>::type eval_divide(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& res, const U& v)
{
   eval_divide(res, res, v);
}

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE, class S>
inline typename enable_if_c<is_signed<S>::value>::type eval_divide(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& res, const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& u, const S& v)
{
   typedef typename make_unsigned<S>::type ui_type;
   eval_divide(res, u, static_cast<ui_type>(boost::multiprecision::detail::unsigned_abs(v)));
   if (v < 0)
      res.negate();
}

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE, class S>
inline typename enable_if_c<is_signed<S>::value>::type eval_divide(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& res, const S& v)
{
   eval_divide(res, res, v);
}

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE>
inline int eval_get_sign(const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& arg)
{
   return arg.exponent() == cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_zero ? 0 : arg.sign() ? -1 : 1;
}

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE>
inline bool eval_is_zero(const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& arg)
{
   return arg.exponent() == cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_zero;
}

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE>
inline bool eval_eq(const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& a, cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& b)
{
   if (a.exponent() == b.exponent())
   {
      if (a.exponent() == cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_zero)
         return true;
      return (a.sign() == b.sign()) && (a.bits().compare(b.bits()) == 0) && (a.exponent() != cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_nan);
   }
   return false;
}

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE>
inline void eval_convert_to(boost::long_long_type* res, const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& arg)
{
   switch (arg.exponent())
   {
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_zero:
      *res = 0;
      return;
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_nan:
      BOOST_THROW_EXCEPTION(std::runtime_error("Could not convert NaN to integer."));
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_infinity:
      *res = (std::numeric_limits<boost::long_long_type>::max)();
      if (arg.sign())
         *res = -*res;
      return;
   }
   typedef typename mpl::if_c<sizeof(typename cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_type) < sizeof(int), int, typename cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_type>::type shift_type;
   typename cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::rep_type                                                                                                                                                              man(arg.bits());
   shift_type                                                                                                                                                                                                                                        shift = (shift_type)cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count - 1 - arg.exponent();
   if (shift > (shift_type)cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count - 1)
   {
      *res = 0;
      return;
   }
   if (arg.sign() && (arg.compare((std::numeric_limits<boost::long_long_type>::min)()) <= 0))
   {
      *res = (std::numeric_limits<boost::long_long_type>::min)();
      return;
   }
   else if (!arg.sign() && (arg.compare((std::numeric_limits<boost::long_long_type>::max)()) >= 0))
   {
      *res = (std::numeric_limits<boost::long_long_type>::max)();
      return;
   }

   if (shift < 0)
   {
      if (cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count - shift <= std::numeric_limits<boost::long_long_type>::digits)
      {
         // We have more bits in long_long_type than the float, so it's OK to left shift:
         eval_convert_to(res, man);
         *res <<= -shift;
      }
      else
      {
         *res = (std::numeric_limits<boost::long_long_type>::max)();
         return;
      }
   }
   else
   {
      eval_right_shift(man, shift);
      eval_convert_to(res, man);
   }
   if (arg.sign())
   {
      *res = -*res;
   }
}

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE>
inline void eval_convert_to(boost::ulong_long_type* res, const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& arg)
{
   switch (arg.exponent())
   {
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_zero:
      *res = 0;
      return;
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_nan:
      BOOST_THROW_EXCEPTION(std::runtime_error("Could not convert NaN to integer."));
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_infinity:
      *res = (std::numeric_limits<boost::ulong_long_type>::max)();
      return;
   }
   typename cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::rep_type                                                                                                                                                              man(arg.bits());
   typedef typename mpl::if_c<sizeof(typename cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_type) < sizeof(int), int, typename cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_type>::type shift_type;
   shift_type                                                                                                                                                                                                                                        shift = (shift_type)cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count - 1 - arg.exponent();
   if (shift > (shift_type)cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count - 1)
   {
      *res = 0;
      return;
   }
   else if (shift < 0)
   {
      if (cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count - shift <= std::numeric_limits<boost::ulong_long_type>::digits)
      {
         // We have more bits in ulong_long_type than the float, so it's OK to left shift:
         eval_convert_to(res, man);
         *res <<= -shift;
         return;
      }
      *res = (std::numeric_limits<boost::ulong_long_type>::max)();
      return;
   }
   eval_right_shift(man, shift);
   eval_convert_to(res, man);
}

template <class Float, unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE>
inline typename boost::enable_if_c<boost::is_float<Float>::value>::type eval_convert_to(Float* res, const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& original_arg)
{
   typedef cpp_bin_float<std::numeric_limits<Float>::digits, digit_base_2, void, Exponent, MinE, MaxE> conv_type;
   typedef typename common_type<typename conv_type::exponent_type, int>::type                          common_exp_type;
   //
   // Special cases first:
   //
   switch (original_arg.exponent())
   {
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_zero:
      *res = 0;
      if (original_arg.sign())
         *res = -*res;
      return;
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_nan:
      *res = std::numeric_limits<Float>::quiet_NaN();
      return;
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_infinity:
      *res = (std::numeric_limits<Float>::infinity)();
      if (original_arg.sign())
         *res = -*res;
      return;
   }
   //
   // Check for super large exponent that must be converted to infinity:
   //
   if (original_arg.exponent() > std::numeric_limits<Float>::max_exponent)
   {
      *res = std::numeric_limits<Float>::has_infinity ? std::numeric_limits<Float>::infinity() : (std::numeric_limits<Float>::max)();
      if (original_arg.sign())
         *res = -*res;
      return;
   }
   //
   // Figure out how many digits we will have in our result,
   // allowing for a possibly denormalized result:
   //
   common_exp_type digits_to_round_to = std::numeric_limits<Float>::digits;
   if (original_arg.exponent() < std::numeric_limits<Float>::min_exponent - 1)
   {
      common_exp_type diff = original_arg.exponent();
      diff -= std::numeric_limits<Float>::min_exponent - 1;
      digits_to_round_to += diff;
   }
   if (digits_to_round_to < 0)
   {
      // Result must be zero:
      *res = 0;
      if (original_arg.sign())
         *res = -*res;
      return;
   }
   //
   // Perform rounding first, then afterwards extract the digits:
   //
   cpp_bin_float<std::numeric_limits<Float>::digits, digit_base_2, Allocator, Exponent, MinE, MaxE> arg;
   typename cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::rep_type             bits(original_arg.bits());
   arg.exponent() = original_arg.exponent();
   copy_and_round(arg, bits, (int)digits_to_round_to);
   common_exp_type e = arg.exponent();
   e -= cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count - 1;
   static const unsigned limbs_needed      = std::numeric_limits<Float>::digits / (sizeof(*arg.bits().limbs()) * CHAR_BIT) + (std::numeric_limits<Float>::digits % (sizeof(*arg.bits().limbs()) * CHAR_BIT) ? 1 : 0);
   unsigned              first_limb_needed = arg.bits().size() - limbs_needed;
   *res                                    = 0;
   e += first_limb_needed * sizeof(*arg.bits().limbs()) * CHAR_BIT;
   while (first_limb_needed < arg.bits().size())
   {
      *res += std::ldexp(static_cast<Float>(arg.bits().limbs()[first_limb_needed]), static_cast<int>(e));
      ++first_limb_needed;
      e += sizeof(*arg.bits().limbs()) * CHAR_BIT;
   }
   if (original_arg.sign())
      *res = -*res;
}

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE>
inline void eval_frexp(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& res, const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& arg, Exponent* e)
{
   switch (arg.exponent())
   {
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_zero:
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_nan:
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_infinity:
      *e  = 0;
      res = arg;
      return;
   }
   res            = arg;
   *e             = arg.exponent() + 1;
   res.exponent() = -1;
}

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE, class I>
inline void eval_frexp(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& res, const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& arg, I* pe)
{
   Exponent e;
   eval_frexp(res, arg, &e);
   if ((e > (std::numeric_limits<I>::max)()) || (e < (std::numeric_limits<I>::min)()))
   {
      BOOST_THROW_EXCEPTION(std::runtime_error("Exponent was outside of the range of the argument type to frexp."));
   }
   *pe = static_cast<I>(e);
}

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE>
inline void eval_ldexp(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& res, const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& arg, Exponent e)
{
   switch (arg.exponent())
   {
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_zero:
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_nan:
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_infinity:
      res = arg;
      return;
   }
   if ((e > 0) && (cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::max_exponent - e < arg.exponent()))
   {
      // Overflow:
      res        = std::numeric_limits<number<cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> > >::infinity().backend();
      res.sign() = arg.sign();
   }
   else if ((e < 0) && (cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::min_exponent - e > arg.exponent()))
   {
      // Underflow:
      res = limb_type(0);
   }
   else
   {
      res = arg;
      res.exponent() += e;
   }
}

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE, class I>
inline typename enable_if_c<is_unsigned<I>::value>::type eval_ldexp(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& res, const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& arg, I e)
{
   typedef typename make_signed<I>::type si_type;
   if (e > static_cast<I>((std::numeric_limits<si_type>::max)()))
      res = std::numeric_limits<number<cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> > >::infinity().backend();
   else
      eval_ldexp(res, arg, static_cast<si_type>(e));
}

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE, class I>
inline typename enable_if_c<is_signed<I>::value>::type eval_ldexp(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& res, const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& arg, I e)
{
   if ((e > (std::numeric_limits<Exponent>::max)()) || (e < (std::numeric_limits<Exponent>::min)()))
   {
      res = std::numeric_limits<number<cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> > >::infinity().backend();
      if (e < 0)
         res.negate();
   }
   else
      eval_ldexp(res, arg, static_cast<Exponent>(e));
}

/*
* Sign manipulation
*/

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE>
inline void eval_abs(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& res, const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& arg)
{
   res        = arg;
   res.sign() = false;
}

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE>
inline void eval_fabs(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& res, const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& arg)
{
   res        = arg;
   res.sign() = false;
}

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE>
inline int eval_fpclassify(const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& arg)
{
   switch (arg.exponent())
   {
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_zero:
      return FP_ZERO;
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_infinity:
      return FP_INFINITE;
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_nan:
      return FP_NAN;
   }
   return FP_NORMAL;
}

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE>
inline void eval_sqrt(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& res, const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& arg)
{
   using default_ops::eval_bit_test;
   using default_ops::eval_increment;
   using default_ops::eval_integer_sqrt;
   switch (arg.exponent())
   {
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_nan:
      errno = EDOM;
      // fallthrough...
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_zero:
      res = arg;
      return;
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_infinity:
      if (arg.sign())
      {
         res   = std::numeric_limits<number<cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> > >::quiet_NaN().backend();
         errno = EDOM;
      }
      else
         res = arg;
      return;
   }
   if (arg.sign())
   {
      res   = std::numeric_limits<number<cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> > >::quiet_NaN().backend();
      errno = EDOM;
      return;
   }

   typename cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::double_rep_type t(arg.bits()), r, s;
   eval_left_shift(t, arg.exponent() & 1 ? cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count : cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count - 1);
   eval_integer_sqrt(s, r, t);

   if (!eval_bit_test(s, cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count))
   {
      // We have exactly the right number of cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count in the result, round as required:
      if (s.compare(r) < 0)
      {
         eval_increment(s);
      }
   }
   typename cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_type ae = arg.exponent();
   res.exponent()                                                                               = ae / 2;
   if ((ae & 1) && (ae < 0))
      --res.exponent();
   copy_and_round(res, s);
}

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE>
inline void eval_floor(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& res, const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& arg)
{
   using default_ops::eval_increment;
   switch (arg.exponent())
   {
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_nan:
      errno = EDOM;
      // fallthrough...
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_zero:
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_infinity:
      res = arg;
      return;
   }
   typedef typename mpl::if_c<sizeof(typename cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_type) < sizeof(int), int, typename cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_type>::type shift_type;
   shift_type                                                                                                                                                                                                                                        shift =
       (shift_type)cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count - arg.exponent() - 1;
   if ((arg.exponent() > (shift_type)cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::max_exponent) || (shift <= 0))
   {
      // Either arg is already an integer, or a special value:
      res = arg;
      return;
   }
   if (shift >= (shift_type)cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count)
   {
      res = static_cast<signed_limb_type>(arg.sign() ? -1 : 0);
      return;
   }
   bool fractional = (shift_type)eval_lsb(arg.bits()) < shift;
   res             = arg;
   eval_right_shift(res.bits(), shift);
   if (fractional && res.sign())
   {
      eval_increment(res.bits());
      if (eval_msb(res.bits()) != cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count - 1 - shift)
      {
         // Must have extended result by one bit in the increment:
         --shift;
         ++res.exponent();
      }
   }
   eval_left_shift(res.bits(), shift);
}

template <unsigned Digits, digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE>
inline void eval_ceil(cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& res, const cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>& arg)
{
   using default_ops::eval_increment;
   switch (arg.exponent())
   {
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_infinity:
      errno = EDOM;
      // fallthrough...
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_zero:
   case cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_nan:
      res = arg;
      return;
   }
   typedef typename mpl::if_c<sizeof(typename cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_type) < sizeof(int), int, typename cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_type>::type shift_type;
   shift_type                                                                                                                                                                                                                                        shift = (shift_type)cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count - arg.exponent() - 1;
   if ((arg.exponent() > (shift_type)cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::max_exponent) || (shift <= 0))
   {
      // Either arg is already an integer, or a special value:
      res = arg;
      return;
   }
   if (shift >= (shift_type)cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count)
   {
      bool s     = arg.sign(); // takes care of signed zeros
      res        = static_cast<signed_limb_type>(arg.sign() ? 0 : 1);
      res.sign() = s;
      return;
   }
   bool fractional = (shift_type)eval_lsb(arg.bits()) < shift;
   res             = arg;
   eval_right_shift(res.bits(), shift);
   if (fractional && !res.sign())
   {
      eval_increment(res.bits());
      if (eval_msb(res.bits()) != cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count - 1 - shift)
      {
         // Must have extended result by one bit in the increment:
         --shift;
         ++res.exponent();
      }
   }
   eval_left_shift(res.bits(), shift);
}

template <unsigned D1, backends::digit_base_type B1, class A1, class E1, E1 M1, E1 M2>
int eval_signbit(const cpp_bin_float<D1, B1, A1, E1, M1, M2>& val)
{
   return val.sign();
}

template <unsigned D1, backends::digit_base_type B1, class A1, class E1, E1 M1, E1 M2>
inline std::size_t hash_value(const cpp_bin_float<D1, B1, A1, E1, M1, M2>& val)
{
   std::size_t result = hash_value(val.bits());
   boost::hash_combine(result, val.exponent());
   boost::hash_combine(result, val.sign());
   return result;
}

} // namespace backends

#ifdef BOOST_NO_SFINAE_EXPR

namespace detail {

template <unsigned D1, backends::digit_base_type B1, class A1, class E1, E1 M1, E1 M2, unsigned D2, backends::digit_base_type B2, class A2, class E2, E2 M3, E2 M4>
struct is_explicitly_convertible<backends::cpp_bin_float<D1, B1, A1, E1, M1, M2>, backends::cpp_bin_float<D2, B2, A2, E2, M3, M4> > : public mpl::true_
{};
template <class FloatT, unsigned D2, backends::digit_base_type B2, class A2, class E2, E2 M3, E2 M4>
struct is_explicitly_convertible<FloatT, backends::cpp_bin_float<D2, B2, A2, E2, M3, M4> > : public boost::is_floating_point<FloatT>
{};

} // namespace detail
#endif

template <unsigned Digits, boost::multiprecision::backends::digit_base_type DigitBase, class Exponent, Exponent MinE, Exponent MaxE, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::backends::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>, ExpressionTemplates>
    copysign BOOST_PREVENT_MACRO_SUBSTITUTION(
        const boost::multiprecision::number<boost::multiprecision::backends::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>, ExpressionTemplates>& a,
        const boost::multiprecision::number<boost::multiprecision::backends::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>, ExpressionTemplates>& b)
{
   boost::multiprecision::number<boost::multiprecision::backends::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>, ExpressionTemplates> res(a);
   res.backend().sign() = b.backend().sign();
   return res;
}

using backends::cpp_bin_float;
using backends::digit_base_10;
using backends::digit_base_2;

template <unsigned Digits, backends::digit_base_type DigitBase, class Exponent, Exponent MinE, Exponent MaxE, class Allocator>
struct number_category<cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> > : public boost::mpl::int_<boost::multiprecision::number_kind_floating_point>
{};

template <unsigned Digits, backends::digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE>
struct expression_template_default<cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> >
{
   static const expression_template_option value = is_void<Allocator>::value ? et_off : et_on;
};

typedef number<backends::cpp_bin_float<50> >  cpp_bin_float_50;
typedef number<backends::cpp_bin_float<100> > cpp_bin_float_100;

typedef number<backends::cpp_bin_float<24, backends::digit_base_2, void, boost::int16_t, -126, 127>, et_off>        cpp_bin_float_single;
typedef number<backends::cpp_bin_float<53, backends::digit_base_2, void, boost::int16_t, -1022, 1023>, et_off>      cpp_bin_float_double;
typedef number<backends::cpp_bin_float<64, backends::digit_base_2, void, boost::int16_t, -16382, 16383>, et_off>    cpp_bin_float_double_extended;
typedef number<backends::cpp_bin_float<113, backends::digit_base_2, void, boost::int16_t, -16382, 16383>, et_off>   cpp_bin_float_quad;
typedef number<backends::cpp_bin_float<237, backends::digit_base_2, void, boost::int32_t, -262142, 262143>, et_off> cpp_bin_float_oct;

} // namespace multiprecision

namespace math {

using boost::multiprecision::copysign;
using boost::multiprecision::signbit;

} // namespace math

} // namespace boost

#include <boost/multiprecision/cpp_bin_float/io.hpp>
#include <boost/multiprecision/cpp_bin_float/transcendental.hpp>

namespace std {

//
// numeric_limits [partial] specializations for the types declared in this header:
//
template <unsigned Digits, boost::multiprecision::backends::digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE, boost::multiprecision::expression_template_option ExpressionTemplates>
class numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>, ExpressionTemplates> >
{
   typedef boost::multiprecision::number<boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>, ExpressionTemplates> number_type;

 public:
   BOOST_STATIC_CONSTEXPR bool is_specialized = true;
   static number_type(min)()
   {
      initializer.do_nothing();
      static std::pair<bool, number_type> value;
      if (!value.first)
      {
         value.first = true;
         typedef typename boost::mpl::front<typename number_type::backend_type::unsigned_types>::type ui_type;
         value.second.backend()            = ui_type(1u);
         value.second.backend().exponent() = boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::min_exponent;
      }
      return value.second;
   }
   static number_type(max)()
   {
      initializer.do_nothing();
      static std::pair<bool, number_type> value;
      if (!value.first)
      {
         value.first = true;
         if (boost::is_void<Allocator>::value)
            eval_complement(value.second.backend().bits(), value.second.backend().bits());
         else
         {
            // We jump through hoops here using the backend type directly just to keep VC12 happy
            // (ie compiler workaround, for very strange compiler bug):
            using boost::multiprecision::default_ops::eval_add;
            using boost::multiprecision::default_ops::eval_decrement;
            using boost::multiprecision::default_ops::eval_left_shift;
            typedef typename number_type::backend_type::rep_type                                int_backend_type;
            typedef typename boost::mpl::front<typename int_backend_type::unsigned_types>::type ui_type;
            int_backend_type                                                                    i;
            i = ui_type(1u);
            eval_left_shift(i, boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count - 1);
            int_backend_type j(i);
            eval_decrement(i);
            eval_add(j, i);
            value.second.backend().bits() = j;
         }
         value.second.backend().exponent() = boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::max_exponent;
      }
      return value.second;
   }
   BOOST_STATIC_CONSTEXPR number_type lowest()
   {
      return -(max)();
   }
   BOOST_STATIC_CONSTEXPR int digits   = boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::bit_count;
   BOOST_STATIC_CONSTEXPR int digits10 = (digits - 1) * 301 / 1000;
   // Is this really correct???
   BOOST_STATIC_CONSTEXPR int  max_digits10 = (digits * 301 / 1000) + 3;
   BOOST_STATIC_CONSTEXPR bool is_signed    = true;
   BOOST_STATIC_CONSTEXPR bool is_integer   = false;
   BOOST_STATIC_CONSTEXPR bool is_exact     = false;
   BOOST_STATIC_CONSTEXPR int  radix        = 2;
   static number_type          epsilon()
   {
      initializer.do_nothing();
      static std::pair<bool, number_type> value;
      if (!value.first)
      {
         // We jump through hoops here just to keep VC12 happy (ie compiler workaround, for very strange compiler bug):
         typedef typename boost::mpl::front<typename number_type::backend_type::unsigned_types>::type ui_type;
         value.first            = true;
         value.second.backend() = ui_type(1u);
         value.second           = ldexp(value.second, 1 - (int)digits);
      }
      return value.second;
   }
   // What value should this be????
   static number_type round_error()
   {
      // returns 0.5
      initializer.do_nothing();
      static std::pair<bool, number_type> value;
      if (!value.first)
      {
         value.first = true;
         // We jump through hoops here just to keep VC12 happy (ie compiler workaround, for very strange compiler bug):
         typedef typename boost::mpl::front<typename number_type::backend_type::unsigned_types>::type ui_type;
         value.second.backend() = ui_type(1u);
         value.second           = ldexp(value.second, -1);
      }
      return value.second;
   }
   BOOST_STATIC_CONSTEXPR typename boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_type min_exponent      = boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::min_exponent;
   BOOST_STATIC_CONSTEXPR typename boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_type min_exponent10    = (min_exponent / 1000) * 301L;
   BOOST_STATIC_CONSTEXPR typename boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_type max_exponent      = boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::max_exponent;
   BOOST_STATIC_CONSTEXPR typename boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_type max_exponent10    = (max_exponent / 1000) * 301L;
   BOOST_STATIC_CONSTEXPR bool                                                                                                             has_infinity      = true;
   BOOST_STATIC_CONSTEXPR bool                                                                                                             has_quiet_NaN     = true;
   BOOST_STATIC_CONSTEXPR bool                                                                                                             has_signaling_NaN = false;
   BOOST_STATIC_CONSTEXPR float_denorm_style has_denorm                                                                                                      = denorm_absent;
   BOOST_STATIC_CONSTEXPR bool               has_denorm_loss                                                                                                 = false;
   static number_type                        infinity()
   {
      initializer.do_nothing();
      static std::pair<bool, number_type> value;
      if (!value.first)
      {
         value.first                       = true;
         value.second.backend().exponent() = boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_infinity;
      }
      return value.second;
   }
   static number_type quiet_NaN()
   {
      initializer.do_nothing();
      static std::pair<bool, number_type> value;
      if (!value.first)
      {
         value.first                       = true;
         value.second.backend().exponent() = boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_nan;
      }
      return value.second;
   }
   BOOST_STATIC_CONSTEXPR number_type signaling_NaN()
   {
      return number_type(0);
   }
   BOOST_STATIC_CONSTEXPR number_type denorm_min() { return number_type(0); }
   BOOST_STATIC_CONSTEXPR bool        is_iec559         = false;
   BOOST_STATIC_CONSTEXPR bool        is_bounded        = true;
   BOOST_STATIC_CONSTEXPR bool        is_modulo         = false;
   BOOST_STATIC_CONSTEXPR bool        traps             = true;
   BOOST_STATIC_CONSTEXPR bool        tinyness_before   = false;
   BOOST_STATIC_CONSTEXPR float_round_style round_style = round_to_nearest;

 private:
   struct data_initializer
   {
      data_initializer()
      {
         std::numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> > >::epsilon();
         std::numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> > >::round_error();
         (std::numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> > >::min)();
         (std::numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> > >::max)();
         std::numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> > >::infinity();
         std::numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE> > >::quiet_NaN();
      }
      void do_nothing() const {}
   };
   static const data_initializer initializer;
};

template <unsigned Digits, boost::multiprecision::backends::digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE, boost::multiprecision::expression_template_option ExpressionTemplates>
const typename numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>, ExpressionTemplates> >::data_initializer numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>, ExpressionTemplates> >::initializer;

#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION

template <unsigned Digits, boost::multiprecision::backends::digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>, ExpressionTemplates> >::digits;
template <unsigned Digits, boost::multiprecision::backends::digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>, ExpressionTemplates> >::digits10;
template <unsigned Digits, boost::multiprecision::backends::digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>, ExpressionTemplates> >::max_digits10;
template <unsigned Digits, boost::multiprecision::backends::digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>, ExpressionTemplates> >::is_signed;
template <unsigned Digits, boost::multiprecision::backends::digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>, ExpressionTemplates> >::is_integer;
template <unsigned Digits, boost::multiprecision::backends::digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>, ExpressionTemplates> >::is_exact;
template <unsigned Digits, boost::multiprecision::backends::digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>, ExpressionTemplates> >::radix;
template <unsigned Digits, boost::multiprecision::backends::digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST typename boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_type numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>, ExpressionTemplates> >::min_exponent;
template <unsigned Digits, boost::multiprecision::backends::digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST typename boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_type numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>, ExpressionTemplates> >::min_exponent10;
template <unsigned Digits, boost::multiprecision::backends::digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST typename boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_type numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>, ExpressionTemplates> >::max_exponent;
template <unsigned Digits, boost::multiprecision::backends::digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST typename boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>::exponent_type numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>, ExpressionTemplates> >::max_exponent10;
template <unsigned Digits, boost::multiprecision::backends::digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>, ExpressionTemplates> >::has_infinity;
template <unsigned Digits, boost::multiprecision::backends::digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>, ExpressionTemplates> >::has_quiet_NaN;
template <unsigned Digits, boost::multiprecision::backends::digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>, ExpressionTemplates> >::has_signaling_NaN;
template <unsigned Digits, boost::multiprecision::backends::digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST float_denorm_style numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>, ExpressionTemplates> >::has_denorm;
template <unsigned Digits, boost::multiprecision::backends::digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>, ExpressionTemplates> >::has_denorm_loss;
template <unsigned Digits, boost::multiprecision::backends::digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>, ExpressionTemplates> >::is_iec559;
template <unsigned Digits, boost::multiprecision::backends::digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>, ExpressionTemplates> >::is_bounded;
template <unsigned Digits, boost::multiprecision::backends::digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>, ExpressionTemplates> >::is_modulo;
template <unsigned Digits, boost::multiprecision::backends::digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>, ExpressionTemplates> >::traps;
template <unsigned Digits, boost::multiprecision::backends::digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>, ExpressionTemplates> >::tinyness_before;
template <unsigned Digits, boost::multiprecision::backends::digit_base_type DigitBase, class Allocator, class Exponent, Exponent MinE, Exponent MaxE, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST float_round_style numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_bin_float<Digits, DigitBase, Allocator, Exponent, MinE, MaxE>, ExpressionTemplates> >::round_style;

#endif

} // namespace std

#endif

/* cpp_bin_float.hpp
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
*/