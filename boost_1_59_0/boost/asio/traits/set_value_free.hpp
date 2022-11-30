//
// traits/set_value_free.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_TRAITS_SET_VALUE_FREE_HPP
#define BOOST_ASIO_TRAITS_SET_VALUE_FREE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/detail/variadic_templates.hpp>

#if defined(BOOST_ASIO_HAS_DECLTYPE) \
  && defined(BOOST_ASIO_HAS_NOEXCEPT) \
  && defined(BOOST_ASIO_HAS_WORKING_EXPRESSION_SFINAE)
# define BOOST_ASIO_HAS_DEDUCED_SET_VALUE_FREE_TRAIT 1
#endif // defined(BOOST_ASIO_HAS_DECLTYPE)
       //   && defined(BOOST_ASIO_HAS_NOEXCEPT)
       //   && defined(BOOST_ASIO_HAS_WORKING_EXPRESSION_SFINAE)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace traits {

template <typename T, typename Vs, typename = void>
struct set_value_free_default;

template <typename T, typename Vs, typename = void>
struct set_value_free;

} // namespace traits
namespace detail {

struct no_set_value_free
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = false);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
};

#if defined(BOOST_ASIO_HAS_DEDUCED_SET_VALUE_FREE_TRAIT)

template <typename T, typename Vs, typename = void>
struct set_value_free_trait : no_set_value_free
{
};

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename T, typename... Vs>
struct set_value_free_trait<T, void(Vs...),
  typename void_type<
    decltype(set_value(declval<T>(), declval<Vs>()...))
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);

  using result_type = decltype(
    set_value(declval<T>(), declval<Vs>()...));

  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = noexcept(
    set_value(declval<T>(), declval<Vs>()...)));
};

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename T>
struct set_value_free_trait<T, void(),
  typename void_type<
    decltype(set_value(declval<T>()))
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);

  using result_type = decltype(set_value(declval<T>()));

  BOOST_ASIO_STATIC_CONSTEXPR(bool,
    is_noexcept = noexcept(set_value(declval<T>())));
};

#define BOOST_ASIO_PRIVATE_SET_VALUE_FREE_TRAIT_DEF(n) \
  template <typename T, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  struct set_value_free_trait<T, void(BOOST_ASIO_VARIADIC_TARGS(n)), \
    typename void_type< \
      decltype(set_value(declval<T>(), BOOST_ASIO_VARIADIC_DECLVAL(n))) \
    >::type> \
  { \
    BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true); \
  \
    using result_type = decltype( \
      set_value(declval<T>(), BOOST_ASIO_VARIADIC_DECLVAL(n))); \
  \
    BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = noexcept( \
      set_value(declval<T>(), BOOST_ASIO_VARIADIC_DECLVAL(n)))); \
  }; \
  /**/
BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_SET_VALUE_FREE_TRAIT_DEF)
#undef BOOST_ASIO_PRIVATE_SET_VALUE_FREE_TRAIT_DEF

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

#else // defined(BOOST_ASIO_HAS_DEDUCED_SET_VALUE_FREE_TRAIT)

template <typename T, typename Vs, typename = void>
struct set_value_free_trait;

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename T, typename... Vs>
struct set_value_free_trait<T, void(Vs...)> :
  conditional<
    is_same<T, typename remove_reference<T>::type>::value
      && conjunction<is_same<Vs, typename decay<Vs>::type>...>::value,
    typename conditional<
      is_same<T, typename add_const<T>::type>::value,
      no_set_value_free,
      traits::set_value_free<typename add_const<T>::type, void(Vs...)>
    >::type,
    traits::set_value_free<
      typename remove_reference<T>::type,
      void(typename decay<Vs>::type...)>
  >::type
{
};

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename T>
struct set_value_free_trait<T, void()> :
  conditional<
    is_same<T, typename remove_reference<T>::type>::value,
    typename conditional<
      is_same<T, typename add_const<T>::type>::value,
      no_set_value_free,
      traits::set_value_free<typename add_const<T>::type, void()>
    >::type,
    traits::set_value_free<typename remove_reference<T>::type, void()>
  >::type
{
};

#define BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME(n) \
  BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_##n

#define BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_1 \
  && is_same<T1, typename decay<T1>::type>::value
#define BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_2 \
  BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_1 \
  && is_same<T2, typename decay<T2>::type>::value
#define BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_3 \
  BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_2 \
  && is_same<T3, typename decay<T3>::type>::value
#define BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_4 \
  BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_3 \
  && is_same<T4, typename decay<T4>::type>::value
#define BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_5 \
  BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_4 \
  && is_same<T5, typename decay<T5>::type>::value
#define BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_6 \
  BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_5 \
  && is_same<T6, typename decay<T6>::type>::value
#define BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_7 \
  BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_6 \
  && is_same<T7, typename decay<T7>::type>::value
#define BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_8 \
  BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_7 \
  && is_same<T8, typename decay<T8>::type>::value

#define BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_TRAIT_DEF(n) \
  template <typename T, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  struct set_value_free_trait<T, void(BOOST_ASIO_VARIADIC_TARGS(n))> : \
    conditional< \
      is_same<T, typename remove_reference<T>::type>::value \
        BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME(n), \
      typename conditional< \
        is_same<T, typename add_const<T>::type>::value, \
        no_set_value_free, \
        traits::set_value_free< \
          typename add_const<T>::type, \
          void(BOOST_ASIO_VARIADIC_TARGS(n))> \
      >::type, \
      traits::set_value_free< \
        typename remove_reference<T>::type, \
        void(BOOST_ASIO_VARIADIC_DECAY(n))> \
    >::type \
  { \
  }; \
  /**/
BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_TRAIT_DEF)
#undef BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_TRAIT_DEF
#undef BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME
#undef BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_1
#undef BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_2
#undef BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_3
#undef BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_4
#undef BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_5
#undef BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_6
#undef BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_7
#undef BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_8

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

#endif // defined(BOOST_ASIO_HAS_DEDUCED_SET_VALUE_FREE_TRAIT)

} // namespace detail
namespace traits {

template <typename T, typename Vs, typename>
struct set_value_free_default :
  detail::set_value_free_trait<T, Vs>
{
};

template <typename T, typename Vs, typename>
struct set_value_free :
  set_value_free_default<T, Vs>
{
};

} // namespace traits
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_TRAITS_SET_VALUE_FREE_HPP

/* set_value_free.hpp
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
*/