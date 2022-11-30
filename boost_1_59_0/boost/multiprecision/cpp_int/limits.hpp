///////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt
//
// Comparison operators for cpp_int_backend:
//
#ifndef BOOST_MP_CPP_INT_LIM_HPP
#define BOOST_MP_CPP_INT_LIM_HPP

#include <boost/multiprecision/traits/max_digits10.hpp>

namespace std {

namespace detail {

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 4307)
#endif

template <std::size_t MinBits, std::size_t MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
inline BOOST_CXX14_CONSTEXPR_IF_DETECTION boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>
get_min(const std::integral_constant<bool, true>&, const std::integral_constant<bool, true>&, const std::integral_constant<bool, true>&)
{
   // Bounded, signed, and no allocator.
   using result_type = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>                                               ;
   using ui_type = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MaxBits, MaxBits, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked>, ExpressionTemplates>;
#ifdef BOOST_MP_NO_CONSTEXPR_DETECTION
   static
#else
   constexpr
#endif
   const result_type                                                                                                                                                                          val = -result_type(~ui_type(0));
   return val;
}

template <std::size_t MinBits, std::size_t MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>
get_min(const std::integral_constant<bool, true>&, const std::integral_constant<bool, true>&, const std::integral_constant<bool, false>&)
{
   // Bounded, signed, and an allocator (can't be constexpr).
   using result_type = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>                                               ;
   using ui_type = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MaxBits, MaxBits, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked>, ExpressionTemplates>;
   static const result_type                                                                                                                                                                          val = -result_type(~ui_type(0));
   return val;
}

template <std::size_t MinBits, std::size_t MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
inline BOOST_CXX14_CONSTEXPR_IF_DETECTION boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>
get_min(const std::integral_constant<bool, true>&, const std::integral_constant<bool, false>&, const std::integral_constant<bool, true>&)
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

template <std::size_t MinBits, std::size_t MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>
get_min(const std::integral_constant<bool, true>&, const std::integral_constant<bool, false>&, const std::integral_constant<bool, false>&)
{
   // Bounded and std::size_t with allocator (no constexpr):
   static const boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> val(0u);
   return val;
}

template <std::size_t MinBits, std::size_t MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates, bool has_allocator>
inline boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>
get_min(const std::integral_constant<bool, false>&, const std::integral_constant<bool, true>&, const std::integral_constant<bool, has_allocator>&)
{
   // Unbounded and signed, never constexpr because there must be an allocator.
   // There is no minimum value, just return 0:
   static const boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> val(0u);
   return val;
}

template <std::size_t MinBits, std::size_t MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates, bool has_allocator>
inline boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>
get_min(const std::integral_constant<bool, false>&, const std::integral_constant<bool, false>&, const std::integral_constant<bool, has_allocator>&)
{
   // Unbound and unsigned, never constexpr because there must be an allocator.
   static const boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> val(0u);
   return val;
}

template <std::size_t MinBits, std::size_t MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
inline BOOST_CXX14_CONSTEXPR_IF_DETECTION boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>
get_max(const std::integral_constant<bool, true>&, const std::integral_constant<bool, true>&, const std::integral_constant<bool, true>&)
{
   // Bounded and signed, no allocator, can be constexpr.
   using result_type = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>                                               ;
   using ui_type = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MaxBits, MaxBits, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked>, ExpressionTemplates>;
#ifdef BOOST_MP_NO_CONSTEXPR_DETECTION
   static
#else
   constexpr
#endif
   const result_type                                                                                                                                                                          val = ~ui_type(0);
   return val;
}

template <std::size_t MinBits, std::size_t MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>
get_max(const std::integral_constant<bool, true>&, const std::integral_constant<bool, true>&, const std::integral_constant<bool, false>&)
{
   // Bounded and signed, has an allocator, never constexpr.
   using result_type = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>                                               ;
   using ui_type = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MaxBits, MaxBits, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked>, ExpressionTemplates>;
   static const result_type                                                                                                                                                                          val = ~ui_type(0);
   return val;
}

template <std::size_t MinBits, std::size_t MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
inline BOOST_CXX14_CONSTEXPR_IF_DETECTION boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>
get_max(const std::integral_constant<bool, true>&, const std::integral_constant<bool, false>&, const std::integral_constant<bool, true>&)
{
   // Bound and unsigned, no allocator so can be constexpr:
   using result_type = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>                                                          ;
   using ui_type = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked, Allocator>, ExpressionTemplates>;
#ifdef BOOST_MP_NO_CONSTEXPR_DETECTION
   static
#else
   constexpr
#endif
   const result_type                                                                                                                                                                                     val = ~ui_type(0);
   return val;
}

template <std::size_t MinBits, std::size_t MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>
get_max(const std::integral_constant<bool, true>&, const std::integral_constant<bool, false>&, const std::integral_constant<bool, false>&)
{
   // Bound and unsigned, has an allocator so can never be constexpr:
   using result_type = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>                                                          ;
   using ui_type = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked, Allocator>, ExpressionTemplates>;
   static const result_type                                                                                                                                                                                     val = ~ui_type(0);
   return val;
}

template <std::size_t MinBits, std::size_t MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates, bool has_allocator>
inline boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>
get_max(const std::integral_constant<bool, false>&, const std::integral_constant<bool, true>&, const std::integral_constant<bool, has_allocator>&)
{
   // Unbounded and signed.
   // There is no maximum value, just return 0:
   static const boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> val(0u);
   return val;
}

template <std::size_t MinBits, std::size_t MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates, bool has_allocator>
inline boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates>
get_max(const std::integral_constant<bool, false>&, const std::integral_constant<bool, false>&, const std::integral_constant<bool, has_allocator>&)
{
   // Unbound and unsigned:
   static const boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> val(0u);
   return val;
}

} // namespace detail

template <std::size_t MinBits, std::size_t MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
class numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >
{
   using backend_type = boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>;
   using number_type = boost::multiprecision::number<backend_type, ExpressionTemplates>                      ;

 public:
   static constexpr bool is_specialized = true;
   //
   // Largest and smallest numbers are bounded only by available memory, set
   // to zero:
   //
   static BOOST_CXX14_CONSTEXPR_IF_DETECTION number_type(min)()
   {
      return detail::get_min<MinBits, MaxBits, SignType, Checked, Allocator, ExpressionTemplates>(boost::multiprecision::backends::is_fixed_precision<backend_type>(), boost::multiprecision::is_signed_number<backend_type>(), std::integral_constant<bool, std::is_void<Allocator>::value>());
   }
   static BOOST_CXX14_CONSTEXPR_IF_DETECTION number_type(max)()
   {
      return detail::get_max<MinBits, MaxBits, SignType, Checked, Allocator, ExpressionTemplates>(boost::multiprecision::backends::is_fixed_precision<backend_type>(), boost::multiprecision::is_signed_number<backend_type>(), std::integral_constant<bool, std::is_void<Allocator>::value>());
   }
   static BOOST_CXX14_CONSTEXPR_IF_DETECTION number_type          lowest() { return (min)(); }
   static constexpr int digits       = boost::multiprecision::backends::max_precision<backend_type>::value == SIZE_MAX ? INT_MAX : boost::multiprecision::backends::max_precision<backend_type>::value;
   static constexpr int digits10     = boost::multiprecision::detail::calc_digits10_s<digits>::value;
   static constexpr int max_digits10 = boost::multiprecision::detail::calc_max_digits10_s<digits>::value;
   static constexpr bool is_signed    = boost::multiprecision::is_signed_number<backend_type>::value;
   static constexpr bool is_integer   = true;
   static constexpr bool is_exact     = true;
   static constexpr int  radix        = 2;
   static BOOST_CXX14_CONSTEXPR_IF_DETECTION number_type          epsilon() { return 0; }
   static BOOST_CXX14_CONSTEXPR_IF_DETECTION number_type          round_error() { return 0; }
   static constexpr int  min_exponent                  = 0;
   static constexpr int  min_exponent10                = 0;
   static constexpr int  max_exponent                  = 0;
   static constexpr int  max_exponent10                = 0;
   static constexpr bool has_infinity                  = false;
   static constexpr bool has_quiet_NaN                 = false;
   static constexpr bool has_signaling_NaN             = false;
   static constexpr float_denorm_style has_denorm      = denorm_absent;
   static constexpr bool               has_denorm_loss = false;
   static BOOST_CXX14_CONSTEXPR_IF_DETECTION number_type                        infinity() { return 0; }
   static BOOST_CXX14_CONSTEXPR_IF_DETECTION number_type                        quiet_NaN() { return 0; }
   static BOOST_CXX14_CONSTEXPR_IF_DETECTION number_type                        signaling_NaN() { return 0; }
   static BOOST_CXX14_CONSTEXPR_IF_DETECTION number_type                        denorm_min() { return 0; }
   static constexpr bool               is_iec559       = false;
   static constexpr bool               is_bounded      = boost::multiprecision::backends::is_fixed_precision<backend_type>::value;
   static constexpr bool               is_modulo       = (boost::multiprecision::backends::is_fixed_precision<backend_type>::value && (Checked == boost::multiprecision::unchecked));
   static constexpr bool               traps           = false;
   static constexpr bool               tinyness_before = false;
   static constexpr float_round_style round_style      = round_toward_zero;
};

template <std::size_t MinBits, std::size_t MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::digits;
template <std::size_t MinBits, std::size_t MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::digits10;
template <std::size_t MinBits, std::size_t MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::max_digits10;
template <std::size_t MinBits, std::size_t MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::is_signed;
template <std::size_t MinBits, std::size_t MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::is_integer;
template <std::size_t MinBits, std::size_t MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::is_exact;
template <std::size_t MinBits, std::size_t MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::radix;
template <std::size_t MinBits, std::size_t MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::min_exponent;
template <std::size_t MinBits, std::size_t MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::min_exponent10;
template <std::size_t MinBits, std::size_t MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::max_exponent;
template <std::size_t MinBits, std::size_t MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr int numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::max_exponent10;
template <std::size_t MinBits, std::size_t MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::has_infinity;
template <std::size_t MinBits, std::size_t MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::has_quiet_NaN;
template <std::size_t MinBits, std::size_t MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::has_signaling_NaN;
template <std::size_t MinBits, std::size_t MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr float_denorm_style numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::has_denorm;
template <std::size_t MinBits, std::size_t MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::has_denorm_loss;
template <std::size_t MinBits, std::size_t MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::is_iec559;
template <std::size_t MinBits, std::size_t MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::is_bounded;
template <std::size_t MinBits, std::size_t MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::is_modulo;
template <std::size_t MinBits, std::size_t MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::traps;
template <std::size_t MinBits, std::size_t MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::tinyness_before;
template <std::size_t MinBits, std::size_t MaxBits, boost::multiprecision::cpp_integer_type SignType, boost::multiprecision::cpp_int_check_type Checked, class Allocator, boost::multiprecision::expression_template_option ExpressionTemplates>
constexpr float_round_style numeric_limits<boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MinBits, MaxBits, SignType, Checked, Allocator>, ExpressionTemplates> >::round_style;

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

} // namespace std

#endif

/* limits.hpp
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
*/