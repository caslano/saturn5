///////////////////////////////////////////////////////////////////////////////
//  Copyright 2015 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_IS_BACKEND_HPP
#define BOOST_MP_IS_BACKEND_HPP

#include <boost/mpl/has_xxx.hpp>
#include <boost/type_traits/conditional.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/multiprecision/detail/number_base.hpp>

namespace boost { namespace multiprecision { namespace detail {

BOOST_MPL_HAS_XXX_TRAIT_DEF(signed_types)
BOOST_MPL_HAS_XXX_TRAIT_DEF(unsigned_types)
BOOST_MPL_HAS_XXX_TRAIT_DEF(float_types)

template <class T>
struct is_backend
{
   static const bool value = has_signed_types<T>::value && has_unsigned_types<T>::value && has_float_types<T>::value;
};

template <class Backend>
struct other_backend
{
   typedef typename boost::conditional<
       boost::is_same<number<Backend>, number<Backend, et_on> >::value,
       number<Backend, et_off>, number<Backend, et_on> >::type type;
};

template <class B, class V>
struct number_from_backend
{
   typedef typename boost::conditional<
       boost::is_convertible<V, number<B> >::value,
       number<B>,
       typename other_backend<B>::type>::type type;
};

template <bool b, class T, class U>
struct is_first_backend_imp
{
   static const bool value = false;
};
template <class T, class U>
struct is_first_backend_imp<true, T, U>
{
   static const bool value = is_convertible<U, number<T, et_on> >::value || is_convertible<U, number<T, et_off> >::value;
};

template <class T, class U>
struct is_first_backend : is_first_backend_imp<is_backend<T>::value, T, U>
{};

template <bool b, class T, class U>
struct is_second_backend_imp
{
   static const bool value = false;
};
template <class T, class U>
struct is_second_backend_imp<true, T, U>
{
   static const bool value = (is_convertible<T, number<U, et_on> >::value || is_convertible<T, number<U, et_off> >::value) && !is_first_backend<T, U>::value;
};

template <class T, class U>
struct is_second_backend : is_second_backend_imp<is_backend<U>::value, T, U>
{};

}
}
} // namespace boost::multiprecision::detail

#endif // BOOST_MP_IS_BACKEND_HPP

/* is_backend.hpp
16cOrfUlKpVbalv6yw/5a3vM7LngFw3mrQUaLpimu6n9NPig9JQ5a1xlhVh9sDVdHDsEQXqCvjgHjilSmm1fLz7Luw7zedehYQ4BnePs5ahz0BpSxMxiuSyOm43FlC5B99Zf7axFP5+OAVgy5YXQVR+fB2NE9Raz09FEVU7+rKj9vFTMkfGJoAnyftmLg/FKRGpubVEkkBfqhdjwgcGo4dVZOsdOMNeEF4abP7qEDDeiBHaA7AItkw6kjAZq5SwL7it/RbXwz0GGphapa2o/EBdEAt9bXUsf1vn+1CByjS3l+j+ufP8saz/fPfBjH8sJ3KDP345gn7We8D6XcZ9Iymxlo1UT2nyU3Wolx0bR2S41SBtimJANLqiu4xoGtDlIdUQAxauLM0AV9cjs8BuvPjqIVeXtEbR86wmvScmtnRtL5ohd6jXcHQiSL9T3/zJ3Bm8ekMG6p7AvrVgVnoapfu4lhPHSzmEwNsBbAV0Hh4/V3CfT7BKv9WFErlLaDIKP3nuybPvcknSYlPTPX0OfDzQQD2Kzt69zfkqutSiTjqPy/cXW3r4IuGQvSklX0mo9WrmAo4BgLHZR5hMQJPvPUFAGQLcG6MSqY9KFgTBezUnHj63uVdSD+u5G72lPx235PS3xPWRPday3iM1rAsycpxsADNJVNFoFnSM5OtbQwWMRKEH3zEIyz6epT+EgMpKOw8hh4GiM/w5JIOlH
*/