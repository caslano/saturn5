///////////////////////////////////////////////////////////////////////////////
//  Copyright Vicente J. Botet Escriba 2009-2011
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_EXPLICIT_CONVERTIBLE_HPP
#define BOOST_MP_EXPLICIT_CONVERTIBLE_HPP

#include <boost/config.hpp>
#include <boost/type_traits/conditional.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/declval.hpp>
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
   typedef typename boost::conditional<
       is_number<S>::value && is_number<T>::value,
       typename boost::conditional<
           number_category<S>::value == number_kind_integer,
           typename boost::conditional<
               number_category<T>::value == number_kind_integer || number_category<T>::value == number_kind_floating_point || number_category<T>::value == number_kind_rational || number_category<T>::value == number_kind_fixed_point,
               boost::true_type,
               boost::false_type>::type,
           typename boost::conditional<
               number_category<S>::value == number_kind_rational,
               typename boost::conditional<
                   number_category<T>::value == number_kind_rational || number_category<T>::value == number_kind_rational,
                   boost::true_type,
                   boost::false_type>::type,
               typename boost::conditional<
                   number_category<T>::value == number_kind_floating_point,
                   boost::true_type,
                   boost::false_type>::type>::type>::type,
       boost::false_type>::type type;
};

template <typename S, typename T>
struct is_explicitly_convertible_imp
{
#ifndef BOOST_NO_SFINAE_EXPR
   template <typename S1, typename T1>
   static type_traits::yes_type selector(dummy_size<sizeof(new T1(boost::declval<
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
                                                                  S1
#else
                                                                  S1 const&
#endif
                                                                  >()))>*);

   template <typename S1, typename T1>
   static type_traits::no_type selector(...);

   static const bool value = sizeof(selector<S, T>(0)) == sizeof(type_traits::yes_type);

   typedef boost::integral_constant<bool, value> type;
#else
   typedef typename has_generic_interconversion<S, T>::type                                      gen_type;
   typedef boost::integral_constant<bool, boost::is_convertible<S, T>::value || gen_type::value> type;
#endif
};

template <typename From, typename To>
struct is_explicitly_convertible : public is_explicitly_convertible_imp<From, To>::type
{
};

#ifdef BOOST_NO_SFINAE_EXPR
template <class Backend1, expression_template_option ExpressionTemplates1, class Backend2, expression_template_option ExpressionTemplates2>
struct is_explicitly_convertible<number<Backend1, ExpressionTemplates1>, number<Backend2, ExpressionTemplates2> >
    : public is_explicitly_convertible<Backend1, Backend2>
{
};
#endif

}}} // namespace boost::multiprecision::detail

#endif

/* explicit_conversion.hpp
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
*/