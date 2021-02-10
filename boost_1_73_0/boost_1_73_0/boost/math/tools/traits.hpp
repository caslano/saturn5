//  Copyright John Maddock 2007.

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

#include <boost/mpl/has_xxx.hpp>
#include <boost/type_traits/integral_constant.hpp>

namespace boost{ namespace math{ namespace tools{

namespace detail{

BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(has_value_type, value_type, true)
BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(has_policy_type, policy_type, true)

template<class D>
char cdf(const D& ...);
template<class D>
char quantile(const D& ...);

template <class D>
struct has_cdf
{
   static D d;
   BOOST_STATIC_CONSTANT(bool, value = sizeof(cdf(d, 0.0f)) != 1);
};

template <class D>
struct has_quantile
{
   static D d;
   BOOST_STATIC_CONSTANT(bool, value = sizeof(quantile(d, 0.0f)) != 1);
};

template <class D>
struct is_distribution_imp
{
   BOOST_STATIC_CONSTANT(bool, value = 
      has_quantile<D>::value 
      && has_cdf<D>::value
      && has_value_type<D>::value
      && has_policy_type<D>::value);
};

template <class sig, sig val>
struct result_tag{};

template <class D>
double test_has_location(const volatile result_tag<typename D::value_type (D::*)()const, &D::location>*);
template <class D>
char test_has_location(...);

template <class D>
double test_has_scale(const volatile result_tag<typename D::value_type (D::*)()const, &D::scale>*);
template <class D>
char test_has_scale(...);

template <class D, bool b>
struct is_scaled_distribution_helper
{
   BOOST_STATIC_CONSTANT(bool, value = false);
};

template <class D>
struct is_scaled_distribution_helper<D, true>
{
   BOOST_STATIC_CONSTANT(bool, value = 
      (sizeof(test_has_location<D>(0)) != 1) 
      && 
      (sizeof(test_has_scale<D>(0)) != 1));
};

template <class D>
struct is_scaled_distribution_imp
{
   BOOST_STATIC_CONSTANT(bool, value = (::boost::math::tools::detail::is_scaled_distribution_helper<D, ::boost::math::tools::detail::is_distribution_imp<D>::value>::value));
};

} // namespace detail

template <class T> struct is_distribution : public boost::integral_constant<bool, ::boost::math::tools::detail::is_distribution_imp<T>::value> {};
template <class T> struct is_scaled_distribution : public boost::integral_constant<bool, ::boost::math::tools::detail::is_scaled_distribution_imp<T>::value> {};

}}}

#endif



/* traits.hpp
cox/wObK2ATeGRf8+YUdggxROJsRA8X3joIVXmwIkXjlfHx/vVrfLG6Pn0ACJ/zkffJ98/VzT9H3RVgQoJFbdCn/P+l5MyTlx/Wl/O1v6QVQSwMECgAAAAgALWdKUq0P5nwmAgAA7gQAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMDQyVVQFAAG2SCRgvZTfa9swEMffBf4fjozCVuYoTrsfGNUQSreUlSUkbt9V+ZKIOpKRlKb+73uym2Sw5/bBtnQ6ne4+95VFQB+U9Fgwoc3K0ucJ2711lS/YtCzn3Qt+35RsgX63RfZrcnt3v7hhgp8cBe/3sk+wRPeMLvW6QiYcNnVbRKvdIvhuycNnHK6HMGmk2iBkw/EXcOgbayoIG+1hL1sIFqQBbZ5lrSt4bAOCk2ZNISsZZJ8Zz4YZjEcjmP1J2LU1BlXQ1uSgauuxMwU0Ib1Dsw6bHLLR6GQs2wZzCPgSeFNLbRKWsFE2vrj89v3Hz3ccCd4XQExKqn6la4RoodJlAHzRPnigUaBFH6QLYFfdJPYJtjt6PSKBUfWuwooGFCguE1i90kpGAsOeEtFVT8WHVPUu7ehRvVUh+JuWqN7rWsc9vcRUNyGHXl0F24TQkPthCsLILRZHGRO+NkoN
*/