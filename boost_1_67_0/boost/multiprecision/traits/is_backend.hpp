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
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
*/