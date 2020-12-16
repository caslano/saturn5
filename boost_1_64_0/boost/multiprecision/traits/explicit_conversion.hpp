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
8Odh0FJU/z6opdWJ1boX05OIJAn8MEgKUdudqlu49T7udIdDDnjcn5o3fj7nY7quVPh2aGeO65OqqomnOKyrfLyiyzmucEvf9sOwEPgJq2x1q02n+ye66Jlq4HtkqgUXxvzRT9g3FtKCG4bW+vT9DIc35XROLCzTXAREsIW3Dq9o1mzcN6v6EJtyNc36uvAo5yuFNM87ZuKkhNYvw/uiDzt49rIDRy87KzjYgAtI5qlc474GPmeeOakVWPFtr7PiA3kT2r2BQ/o34illntmJF+TV/ezqzuAnq73JOvewE/mBHTulgIVyorP3YcbeMszuYcwT10k80N3rNtYod+m6n+onTurlroW6iU4+2Gt81+zQcsLc9sVsH9tieYrvJLwnCHLw2M/c/PrSi2RNLKraqA5Jg9/vdd9P7lZ+b7hd7SehcvjTIYQof2jdCTg0vjY4agqC9rjc3ISDfTnd3pdGmjwYCMAOf+LAWmKTQ/P4as8TcgZpK+sNpNQvvLSF4bD9fXBW/ec7dT+Hws6L0g/CQLRHX7l1mM7n62XV9kUQZXbg+pZoS5Zxl91eJusIv4z8snRzgU02np2g23nIrsB5kJnHwfhBzo8kro+xqgb+fbX/MHwC9LcZvirfgeprbc5N+PnZkHf0qOx/d2oiGO0P5n52St905l/UZQXmPrl6ewJwfi9vknll6f+/9fSKru+pseUnpZvGsn7MLq7xO+AOTWn17il2GIPt2EEuRLSiEvca0+sFWeQ4kYXcBbp74G5ZT1SaeZL18cIFLDNDYeL6VL5gTkmFdaqD6FT2cJymYdV4hcrtG8cQk2bAINU1wndu0XGqZ1Q39mxlOBVStjeac6h+0b7jbTpOdYvWz/d+Sq6fwyh+AwHy6Vv0vSNBby1bxtmiEBK/2PM2niMOTMB3ptZxPJfzD1W2q1TKDZe9DTkBUO8ffrRas3+/5C9DsalWtNbmcWMEfk5wg+LabhW3t48CD78v5LrVx9fY2z97b33vFx5gQIPVvWF9aXBJcS99o5Vb3WlWc9XZlpVr90Fu78wK2/zcfYTS9cHtmi4cLZxcOFWlr6/St/MC4ywtM9rQguKdfTfyJAgbgdC/1ZZHxVN+uPCNEZlH/ZcuzdUZ2NmtfP81Dev2ECU/7xcy3XCGYWGpJ9sBihNaoHjszRq81e4qZDXSKL5g6+4Gr/tS2Eq5MFfpozm2J2s8ciPXdWmpTjuUL3wCndGAp/Ju6LWVrtVVaVAVsqotq/OO/PRKxaXysqLs3SCs7uJrhQ6mfhZydRbrPrwPWOalE3jRbc9NYQao9XxMSLmB7XR/DS+Q6dZz44/ANkuGV3EAFCuoxKahbZ8hGfjSYYVb7Ut9o2NQnyUmaw3Or8nzR/fDOTkZfgKWrsFGbfs4hclSI+0/usa6EhtUQWRVNXIVJm6gDar1zktei+uxrah1LW7GIbNwx2bNXeF2sXK0CVJMUPYptewal/2fgnfXadiQckYTgefLa72vMPRyZrvOV0oZ3pToOl9j6ORMrvPJtczrGr6pxYx0PbCOwxslv2pb4J+U72e1cJUFKHPfnVC+q3ivrOAWaC0P32LYrqSZWeKea8bTpFO5fGtlD5snit/bB2EqelQu32Xorlikl/x/XvKqJka1akOa/z9g6OFMnq7dtc4Lms66BaS8uWjoY6yW+H1M06VaST1+nzD0cSaLH+m8pOnE7XTYAOg6Lxs6ObM9zVd0nXCDyYJWHj/X0EcsXRnl9ZckH1vzQVm8SmHNNuibhn5k6YpxDepZ2jw+nrbuTM8UZX1G8rkNzJuZifJgGnFt7voXxKJuzuCs01Ydp6Mz1I9+yzYdx2jWLY7GmR/XOfRdWdY=
*/