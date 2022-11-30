///////////////////////////////////////////////////////////////////////////////
//  Copyright 2015 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_IS_BACKEND_HPP
#define BOOST_MP_IS_BACKEND_HPP

#include <type_traits>
#include <boost/multiprecision/detail/number_base.hpp>

namespace boost { namespace multiprecision { namespace detail {

template <class T>
struct has_signed_types
{
   template <class U>
   static double check(U*, typename U::signed_types* = nullptr);
   static char   check(...);
   static T* get();
   static constexpr bool value = sizeof(check(get())) == sizeof(double);
};
template <class T>
struct has_unsigned_types
{
   template <class U>
   static double check(U*, typename U::unsigned_types* = nullptr);
   static char   check(...);
   static T* get();
   static constexpr bool value = sizeof(check(get())) == sizeof(double);
};
template <class T>
struct has_float_types
{
   template <class U>
   static double check(U*, typename U::float_types* = nullptr);
   static char   check(...);
   static T* get();
   static constexpr bool value = sizeof(check(get())) == sizeof(double);
};

template <class T>
struct is_backend : public std::integral_constant<bool, has_signed_types<T>::value && has_unsigned_types<T>::value && has_float_types<T>::value> {};

template <class Backend>
struct other_backend
{
   using type = typename std::conditional<
       std::is_same<number<Backend>, number<Backend, et_on> >::value,
       number<Backend, et_off>, number<Backend, et_on> >::type;
};

template <class B, class V>
struct number_from_backend
{
   using type = typename std::conditional<
       std::is_convertible<V, number<B> >::value,
       number<B>,
       typename other_backend<B>::type>::type;
};

template <bool b, class T, class U>
struct is_first_backend_imp : public std::false_type {};

template <class T, class U>
    struct is_first_backend_imp<true, T, U> : public std::integral_constant < bool, std::is_convertible<U, number<T, et_on> >::value || std::is_convertible<U, number<T, et_off> >::value> {};

template <class T, class U>
struct is_first_backend : is_first_backend_imp<is_backend<T>::value, T, U>
{};

template <bool b, class T, class U>
struct is_second_backend_imp
{
   static constexpr const bool value = false;
};
template <class T, class U>
struct is_second_backend_imp<true, T, U>
{
   static constexpr const bool value = (std::is_convertible<T, number<U, et_on> >::value || std::is_convertible<T, number<U, et_off> >::value) && !is_first_backend<T, U>::value;
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