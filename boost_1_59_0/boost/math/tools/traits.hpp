//  Copyright John Maddock 2007.
//  Copyright Matt Borland 2021.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/*
This header defines two traits classes, both in namespace boost::math::tools.

is_distribution<D>::value is true iff D has overloaded "cdf" and
"quantile" functions, plus member typedefs value_type and policy_type.  
It's not much of a definitive test frankly,
but if it looks like a distribution and quacks like a distribution
then it must be a distribution.

is_scaled_distribution<D>::value is true iff D is a distribution
as defined above, and has member functions "scale" and "location".

*/

#ifndef BOOST_STATS_IS_DISTRIBUTION_HPP
#define BOOST_STATS_IS_DISTRIBUTION_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <type_traits>

namespace boost{ namespace math{ namespace tools{

namespace detail{

#define BOOST_MATH_HAS_NAMED_TRAIT(trait, name)                         \
template <typename T>                                                   \
class trait                                                             \
{                                                                       \
private:                                                                \
   using yes = char;                                                    \
   struct no { char x[2]; };                                            \
                                                                        \
   template <typename U>                                                \
   static yes test(typename U::name* = nullptr);                        \
                                                                        \
   template <typename U>                                                \
   static no test(...);                                                 \
                                                                        \
public:                                                                 \
   static constexpr bool value = (sizeof(test<T>(0)) == sizeof(char));  \
};

BOOST_MATH_HAS_NAMED_TRAIT(has_value_type, value_type)
BOOST_MATH_HAS_NAMED_TRAIT(has_policy_type, policy_type)
BOOST_MATH_HAS_NAMED_TRAIT(has_backend_type, backend_type)

template <typename D>
char cdf(const D& ...);
template <typename D>
char quantile(const D& ...);

template <typename D>
struct has_cdf
{
   static D d;
   static constexpr bool value = sizeof(cdf(d, 0.0f)) != 1;
};

template <typename D>
struct has_quantile
{
   static D d;
   static constexpr bool value = sizeof(quantile(d, 0.0f)) != 1;
};

template <typename D>
struct is_distribution_imp
{
   static constexpr bool value =
      has_quantile<D>::value 
      && has_cdf<D>::value
      && has_value_type<D>::value
      && has_policy_type<D>::value;
};

template <typename sig, sig val>
struct result_tag{};

template <typename D>
double test_has_location(const volatile result_tag<typename D::value_type (D::*)()const, &D::location>*);
template <typename D>
char test_has_location(...);

template <typename D>
double test_has_scale(const volatile result_tag<typename D::value_type (D::*)()const, &D::scale>*);
template <typename D>
char test_has_scale(...);

template <typename D, bool b>
struct is_scaled_distribution_helper
{
   static constexpr bool value = false;
};

template <typename D>
struct is_scaled_distribution_helper<D, true>
{
   static constexpr bool value = 
      (sizeof(test_has_location<D>(0)) != 1) 
      && 
      (sizeof(test_has_scale<D>(0)) != 1);
};

template <typename D>
struct is_scaled_distribution_imp
{
   static constexpr bool value = (::boost::math::tools::detail::is_scaled_distribution_helper<D, ::boost::math::tools::detail::is_distribution_imp<D>::value>::value);
};

} // namespace detail

template <typename T> struct is_distribution : public std::integral_constant<bool, ::boost::math::tools::detail::is_distribution_imp<T>::value> {};
template <typename T> struct is_scaled_distribution : public std::integral_constant<bool, ::boost::math::tools::detail::is_scaled_distribution_imp<T>::value> {};

}}}

#endif



/* traits.hpp
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
*/