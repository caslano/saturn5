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
ZdRLW8MrlnGOlFGyHLSU6fxIOB62myySbq64k5QhWKNEmkRSYBk93jU/Psp3yJfsKK0beWOx02Lw68GCvDuIXQ6jN+x2R67vm7376HsjZnPFXlgbCIklbjG4t8WyvNgXuwGn3ycO58FF4sjoXnsC6d+6H9DtN67eGCzaGnd73xvvr+lX3h9fRkywP8Y978/3AOYqvk9vewDgruL7dPhAixuz9933IKSF34p3naLfiplqRRPzq46tqjXlx/SbXPD3fipKy6Ju2ZnhcIO+69rt4460qYoKwTN2/HDg77zHxx3VbmJNVBWmwIGF3uTi+fnYZ8qsLTOdG3pq6pkGSb5Pv+ufNtrv+Y7+sntYurXJ5UWaj/LGSUofrgPEe5Oz7zpHB9aFVSgb76jv5dHs4YaFuPIv7XKYUWDks5sr/vvUW0mflSzPRJ1HV5+rwvYZvpWAAYB9UVZVliVRzsha2mEPvdDHtonK01pbC75NQ+yXTpG3bEkulGxL1jYuvzO+A/2Wjz0qqoQ3EqbtxPhj8triMZf/D338cQX2EyUcNHDYzuQez4o+r3ijd+42l8ySuCNf0usnoZrTAeusjf2yd0eIMwc2mEe0R7fRxZdW7Xtfe8+zs4fT9uzolyd7dDhY9vIXXtejr+nyMVbnWLqJOPwozPUaYGh+3m/t7tEHOuMCfCi6Mvj1DjMAl1YgmWY6+uEH9OhrVg82ln1IN3XAN/QPRrqJsL7l5nYbFAnn7b0P0VgzXIwy57TH3DO8s+D5YJ6TUR5l6qqDKOCYwTnke8GJ7chqYOWG7iLnPTvGYwFK87ju7OPMOe1wSUPRH2Kyj9OWpmWHcaUv3XM81sp2Zf7sum1x5sitVtxhJ3ddGdvEubsrvfHeV8YuwAczfHvbOMqYP2Q7Hnv0hWeJ9zVYXGhpJ+AZ4e4A5zoAy/rz/QKMr/wJki+Y4ojySWy7Ps4W9mSMbUcxgdJJfuYHhliqdN+P650P6mP7Ssc2/XDvdnh61rjxYMCRfR9ROPr1PHQcTsNQJtsXYqjC0T8qxBGFO5nvefg4nIZ5tvWIEBMqHLEXbgixocJR379+ZB/bVziWve/RIT60cMT+ELG4AaRqx/55zDbYwO7ueOwYHFE/Ym97XIDtTzg4hg5sg9VQT1+/fPx4HO0KxO954lh82B1u3pEHt8WHXYLtfNL2POE4mHqyw87DSfDG0C1NA5Lre/8hxG0unNER90bXu0Ec04NPtThyP2GuUnHNfprDmPs3S8a8XoeRDkHxLRnp+48gfXNFcVsFfAP8TEvHewSshR8r76jDwc50bvCaBbgrNoXhevzKZwHGfEfRMp5m6VvTQB9/jzs2tv6ft8fb03z8Zrr0bIs1b/zAMEQyi4UibvY5fRxew+H3XHljH2eFYk7bV9D3iYI3SkaCUY8BehbKfZ5YsqyJ0lhHbxh/TeX8R1yMMMIfMVHLROYpZ8H1lWXE3I+EL2FxUaVcJ7fsXTHTu413Er6YpTxtshT4wk8lw4Znku8nfCnL4zJO6yZl466jg3hm36J6TapSpUXGGb2lpvW8K2gfiFKqjCQLr66DtymXCZ9gVVo0dVQ1zBtyJono8tBqBt8bTMwFvFFTlEkasTFX2eGb0X1z1Jc+a1VbZS2jX4C0jYfmgj5sikzlRcrI8MXed+84g3o2ad7UkgvCR3ofc46+jPDmrM3TGlTUMnrsYhYGY0VBTu1zhD9mdd7GcZwpFm7bR3zLnX5u9/lKxnmrqqpsmc12qZ8Z9d7GvJ/IKlgtlRQ8a7v3Xsv6cRpM62dHR2xHTy8vrdiOwTPVoIyMN6LIZeqXMYTDPloGtf1fB/2UQotNBCJbhm66eaDjenhipZM=
*/