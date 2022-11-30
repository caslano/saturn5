///////////////////////////////////////////////////////////////////////////////
//  Copyright Vicente J. Botet Escriba 2009-2011
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_EXPLICIT_CONVERTIBLE_HPP
#define BOOST_MP_EXPLICIT_CONVERTIBLE_HPP

#include <type_traits>
#include <boost/multiprecision/detail/standalone_config.hpp>
#include <boost/multiprecision/detail/number_base.hpp> // number_category

namespace boost {
namespace multiprecision {
namespace detail {

template <unsigned int N>
struct dummy_size
{};

template <typename S, typename T>
struct has_generic_interconversion
{
   using type = typename std::conditional<
       is_number<S>::value && is_number<T>::value,
       typename std::conditional<
           number_category<S>::value == number_kind_integer,
           typename std::conditional<
               number_category<T>::value == number_kind_integer || number_category<T>::value == number_kind_floating_point || number_category<T>::value == number_kind_rational || number_category<T>::value == number_kind_fixed_point,
               std::true_type,
               std::false_type >::type,
           typename std::conditional<
               number_category<S>::value == number_kind_rational,
               typename std::conditional<
                   number_category<T>::value == number_kind_rational || number_category<T>::value == number_kind_rational,
                   std::true_type,
                   std::false_type >::type,
               typename std::conditional<
                   number_category<T>::value == number_kind_floating_point,
                   std::true_type,
                   std::false_type >::type>::type>::type,
       std::false_type >::type;
};

template <typename S, typename T>
struct is_explicitly_convertible_imp
{
   template <typename S1, typename T1>
   static int selector(dummy_size<sizeof(new T1(std::declval<S1>()))>*);

   template <typename S1, typename T1>
   static char selector(...);

   static constexpr const bool value = sizeof(selector<S, T>(0)) == sizeof(int);

   using type = std::integral_constant<bool, value>;
};

template <typename From, typename To>
struct is_explicitly_convertible : public is_explicitly_convertible_imp<From, To>::type
{
};

}}} // namespace boost::multiprecision::detail

#endif

/* explicit_conversion.hpp
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
*/