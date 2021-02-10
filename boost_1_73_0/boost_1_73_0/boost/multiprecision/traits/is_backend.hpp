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
iob7nx9wt8qP20ev3+r3g+FvzLuIW0pqpIzgYRkskegnI3TEBMCHNJPJhwo1T7OTN+cA0DSihKlvogs8s0E425WJFQdvkNc+T/Qtf/BjjKgBi41KBjUKFZFzIbpVXrJMAqdboUesuQyGw3jy2Rs7k894w9/naBxPrAhzKcgq7RlYChzTXhLaWJv6YkLmaQb5SUiJWY5ut/eXS9/CPCGl9W6ZQsr44mhIpXC3eAhVsjAaUvXcsYiAwjKFXAQobrGnCRjtWB/uxjXXvquvwv/Exp32EoFubDQzCQ+sDT/LafhZbsMI2tZkgtD8hnE4c4XO0AQ2RlhOrGaggbgvOvaUaW084Xuh9tGnbK6iiOjDyeAH+K9yUp//PdvZLPGNUH5+xEwMGLBKJpGT/kv0Pyn+bH5rojObs4tRktKT97jCODktNorN3AXKogOVn9n+xH/nhBg6ssGS/YrJSJ3cVvu3G0wOdeqwi9H+3e1NS1OsxWOw+A51xh5jKpAsiZLDo0sUFs9nX3VnYzIZ7x2+/VQSU/kNBs6X6iXEnQfTc/2sqiX6Gg8WxxeNQl3YJTJSGc/S5QVjVhRcoekU3ETzCWjiAYfGM8BW2SywD4pjB+xFPWhax5KayZSYg6wGUiGYArQkng8oAJcmb9QRwGVK
*/