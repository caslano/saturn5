///////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt
//
// Comparison operators for cpp_int_backend:
//
#ifndef BOOST_MP_CPP_INT_LIM_HPP
#define BOOST_MP_CPP_INT_LIM_HPP

namespace std {

namespace detail {

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4307)
#endif

template <unsigned MinBits, unsigned MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
inline BOOST_CXX14_CONSTEXPR_IF_DETECTION boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>
get_min(const boost::mpl::true_&, const boost::mpl::true_&, const boost::mpl::true_&)
{
   // Bounded, signed, and no allocator.
   typedef boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>                                                result_type;
   typedef boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MaxBits, MaxBits, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked>, ExpressionTemplates> ui_type;
#ifdef BOOST_MP_NO_CONSTEXPR_DETECTION
   static
#else
   constexpr
#endif
   const result_type                                                                                                                                                                          val = -result_type(~ui_type(0));
   return val;
}

template <unsigned MinBits, unsigned MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>
get_min(const boost::mpl::true_&, const boost::mpl::true_&, const boost::mpl::false_&)
{
   // Bounded, signed, and an allocator (can't be constexpr).
   typedef boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>                                                result_type;
   typedef boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MaxBits, MaxBits, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked>, ExpressionTemplates> ui_type;
   static const result_type                                                                                                                                                                          val = -result_type(~ui_type(0));
   return val;
}

template <unsigned MinBits, unsigned MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
inline BOOST_CXX14_CONSTEXPR_IF_DETECTION boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>
get_min(const boost::mpl::true_&, const boost::mpl::false_&, const boost::mpl::true_&)
{
   // Bounded, unsigned, no allocator (can be constexpr):
#ifdef BOOST_MP_NO_CONSTEXPR_DETECTION
   static
#else
   constexpr
#endif
   const boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> val(0u);
   return val;
}

template <unsigned MinBits, unsigned MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>
get_min(const boost::mpl::true_&, const boost::mpl::false_&, const boost::mpl::false_&)
{
   // Bounded and unsigned with allocator (no constexpr):
   static const boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> val(0u);
   return val;
}

template <unsigned MinBits, unsigned MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates, bool has_allocator>
inline boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>
get_min(const boost::mpl::false_&, const boost::mpl::true_&, const boost::mpl::bool_<has_allocator>&)
{
   // Unbounded and signed, never constexpr because there must be an allocator.
   // There is no minimum value, just return 0:
   static const boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> val(0u);
   return val;
}

template <unsigned MinBits, unsigned MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates, bool has_allocator>
inline boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>
get_min(const boost::mpl::false_&, const boost::mpl::false_&, const boost::mpl::bool_<has_allocator>&)
{
   // Unbound and unsigned, never constexpr because there must be an allocator.
   static const boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> val(0u);
   return val;
}

template <unsigned MinBits, unsigned MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
inline BOOST_CXX14_CONSTEXPR_IF_DETECTION boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>
get_max(const boost::mpl::true_&, const boost::mpl::true_&, const boost::mpl::true_&)
{
   // Bounded and signed, no allocator, can be constexpr.
   typedef boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>                                                result_type;
   typedef boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MaxBits, MaxBits, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked>, ExpressionTemplates> ui_type;
#ifdef BOOST_MP_NO_CONSTEXPR_DETECTION
   static
#else
   constexpr
#endif
   const result_type                                                                                                                                                                          val = ~ui_type(0);
   return val;
}

template <unsigned MinBits, unsigned MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>
get_max(const boost::mpl::true_&, const boost::mpl::true_&, const boost::mpl::false_&)
{
   // Bounded and signed, has an allocator, never constexpr.
   typedef boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>                                                result_type;
   typedef boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MaxBits, MaxBits, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked>, ExpressionTemplates> ui_type;
   static const result_type                                                                                                                                                                          val = ~ui_type(0);
   return val;
}

template <unsigned MinBits, unsigned MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
inline BOOST_CXX14_CONSTEXPR_IF_DETECTION boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>
get_max(const boost::mpl::true_&, const boost::mpl::false_&, const boost::mpl::true_&)
{
   // Bound and unsigned, no allocator so can be constexpr:
   typedef boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>                                                           result_type;
   typedef boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked, Allocator>, ExpressionTemplates> ui_type;
#ifdef BOOST_MP_NO_CONSTEXPR_DETECTION
   static
#else
   constexpr
#endif
   const result_type                                                                                                                                                                                     val = ~ui_type(0);
   return val;
}

template <unsigned MinBits, unsigned MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>
get_max(const boost::mpl::true_&, const boost::mpl::false_&, const boost::mpl::false_&)
{
   // Bound and unsigned, has an allocator so can never be constexpr:
   typedef boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>                                                           result_type;
   typedef boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked, Allocator>, ExpressionTemplates> ui_type;
   static const result_type                                                                                                                                                                                     val = ~ui_type(0);
   return val;
}

template <unsigned MinBits, unsigned MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates, bool has_allocator>
inline boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>
get_max(const boost::mpl::false_&, const boost::mpl::true_&, const boost::mpl::bool_<has_allocator>&)
{
   // Unbounded and signed.
   // There is no maximum value, just return 0:
   static const boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> val(0u);
   return val;
}

template <unsigned MinBits, unsigned MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates, bool has_allocator>
inline boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>
get_max(const boost::mpl::false_&, const boost::mpl::false_&, const boost::mpl::bool_<has_allocator>&)
{
   // Unbound and unsigned:
   static const boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> val(0u);
   return val;
}

} // namespace detail

template <unsigned MinBits, unsigned MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
class numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >
{
   typedef boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator> backend_type;
   typedef boost::multiprecision::number<backend_type, ExpressionTemplates>                       number_type;

   struct inititializer
   {
      BOOST_CXX14_CONSTEXPR_IF_DETECTION inititializer()
      {
         (std::numeric_limits<number_type>::max)();
         (std::numeric_limits<number_type>::min)();
      }
      BOOST_CXX14_CONSTEXPR_IF_DETECTION void do_nothing() const {}
   };

   static const inititializer init;

 public:
   BOOST_STATIC_CONSTEXPR bool is_specialized = true;
   //
   // Largest and smallest numbers are bounded only by available memory, set
   // to zero:
   //
   static BOOST_CXX14_CONSTEXPR_IF_DETECTION number_type(min)()
   {
      init.do_nothing();
      return detail::get_min<MinBits, MaxBits, SignType, Checked, Allocator, ExpressionTemplates>(boost::multiprecision::backends::is_fixed_precision<backend_type>(), boost::multiprecision::is_signed_number<backend_type>(), boost::mpl::bool_<boost::is_void<Allocator>::value>());
   }
   static BOOST_CXX14_CONSTEXPR_IF_DETECTION number_type(max)()
   {
      init.do_nothing();
      return detail::get_max<MinBits, MaxBits, SignType, Checked, Allocator, ExpressionTemplates>(boost::multiprecision::backends::is_fixed_precision<backend_type>(), boost::multiprecision::is_signed_number<backend_type>(), boost::mpl::bool_<boost::is_void<Allocator>::value>());
   }
   static BOOST_CXX14_CONSTEXPR_IF_DETECTION number_type          lowest() { return (min)(); }
   BOOST_STATIC_CONSTEXPR int  digits       = boost::multiprecision::backends::max_precision<backend_type>::value == UINT_MAX ? INT_MAX : boost::multiprecision::backends::max_precision<backend_type>::value;
   BOOST_STATIC_CONSTEXPR int  digits10     = (digits > INT_MAX / 301) ? (digits / 1000) * 301L : (digits * 301) / 1000;
   BOOST_STATIC_CONSTEXPR int  max_digits10 = digits10 + 3;
   BOOST_STATIC_CONSTEXPR bool is_signed    = boost::multiprecision::is_signed_number<backend_type>::value;
   BOOST_STATIC_CONSTEXPR bool is_integer   = true;
   BOOST_STATIC_CONSTEXPR bool is_exact     = true;
   BOOST_STATIC_CONSTEXPR int  radix        = 2;
   static BOOST_CXX14_CONSTEXPR_IF_DETECTION number_type          epsilon() { return 0; }
   static BOOST_CXX14_CONSTEXPR_IF_DETECTION number_type          round_error() { return 0; }
   BOOST_STATIC_CONSTEXPR int  min_exponent                  = 0;
   BOOST_STATIC_CONSTEXPR int  min_exponent10                = 0;
   BOOST_STATIC_CONSTEXPR int  max_exponent                  = 0;
   BOOST_STATIC_CONSTEXPR int  max_exponent10                = 0;
   BOOST_STATIC_CONSTEXPR bool has_infinity                  = false;
   BOOST_STATIC_CONSTEXPR bool has_quiet_NaN                 = false;
   BOOST_STATIC_CONSTEXPR bool has_signaling_NaN             = false;
   BOOST_STATIC_CONSTEXPR float_denorm_style has_denorm      = denorm_absent;
   BOOST_STATIC_CONSTEXPR bool               has_denorm_loss = false;
   static BOOST_CXX14_CONSTEXPR_IF_DETECTION number_type                        infinity() { return 0; }
   static BOOST_CXX14_CONSTEXPR_IF_DETECTION number_type                        quiet_NaN() { return 0; }
   static BOOST_CXX14_CONSTEXPR_IF_DETECTION number_type                        signaling_NaN() { return 0; }
   static BOOST_CXX14_CONSTEXPR_IF_DETECTION number_type                        denorm_min() { return 0; }
   BOOST_STATIC_CONSTEXPR bool               is_iec559       = false;
   BOOST_STATIC_CONSTEXPR bool               is_bounded      = boost::multiprecision::backends::is_fixed_precision<backend_type>::value;
   BOOST_STATIC_CONSTEXPR bool               is_modulo       = (boost::multiprecision::backends::is_fixed_precision<backend_type>::value && (Checked == boost::multiprecision::unchecked));
   BOOST_STATIC_CONSTEXPR bool               traps           = false;
   BOOST_STATIC_CONSTEXPR bool               tinyness_before = false;
   BOOST_STATIC_CONSTEXPR float_round_style round_style      = round_toward_zero;
};

template <unsigned MinBits, unsigned MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
const typename numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::inititializer numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::init;

#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION

template <unsigned MinBits, unsigned MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::digits;
template <unsigned MinBits, unsigned MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::digits10;
template <unsigned MinBits, unsigned MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::max_digits10;
template <unsigned MinBits, unsigned MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::is_signed;
template <unsigned MinBits, unsigned MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::is_integer;
template <unsigned MinBits, unsigned MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::is_exact;
template <unsigned MinBits, unsigned MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::radix;
template <unsigned MinBits, unsigned MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::min_exponent;
template <unsigned MinBits, unsigned MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::min_exponent10;
template <unsigned MinBits, unsigned MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::max_exponent;
template <unsigned MinBits, unsigned MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::max_exponent10;
template <unsigned MinBits, unsigned MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::has_infinity;
template <unsigned MinBits, unsigned MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::has_quiet_NaN;
template <unsigned MinBits, unsigned MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::has_signaling_NaN;
template <unsigned MinBits, unsigned MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST float_denorm_style numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::has_denorm;
template <unsigned MinBits, unsigned MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::has_denorm_loss;
template <unsigned MinBits, unsigned MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::is_iec559;
template <unsigned MinBits, unsigned MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::is_bounded;
template <unsigned MinBits, unsigned MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::is_modulo;
template <unsigned MinBits, unsigned MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::traps;
template <unsigned MinBits, unsigned MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::tinyness_before;
template <unsigned MinBits, unsigned MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST float_round_style numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::round_style;

#endif
#ifdef _MSC_VER
#pragma warning(pop)
#endif

} // namespace std

#endif

/* limits.hpp
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
*/