//
// detail/type_traits.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_TYPE_TRAITS_HPP
#define BOOST_ASIO_DETAIL_TYPE_TRAITS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_STD_TYPE_TRAITS)
# include <type_traits>
#else // defined(BOOST_ASIO_HAS_STD_TYPE_TRAITS)
# include <boost/type_traits/add_const.hpp>
# include <boost/type_traits/add_lvalue_reference.hpp>
# include <boost/type_traits/aligned_storage.hpp>
# include <boost/type_traits/alignment_of.hpp>
# include <boost/type_traits/conditional.hpp>
# include <boost/type_traits/decay.hpp>
# include <boost/type_traits/has_nothrow_copy.hpp>
# include <boost/type_traits/has_nothrow_destructor.hpp>
# include <boost/type_traits/integral_constant.hpp>
# include <boost/type_traits/is_base_of.hpp>
# include <boost/type_traits/is_class.hpp>
# include <boost/type_traits/is_const.hpp>
# include <boost/type_traits/is_convertible.hpp>
# include <boost/type_traits/is_constructible.hpp>
# include <boost/type_traits/is_copy_constructible.hpp>
# include <boost/type_traits/is_destructible.hpp>
# include <boost/type_traits/is_function.hpp>
# include <boost/type_traits/is_object.hpp>
# include <boost/type_traits/is_same.hpp>
# include <boost/type_traits/remove_cv.hpp>
# include <boost/type_traits/remove_pointer.hpp>
# include <boost/type_traits/remove_reference.hpp>
# include <boost/utility/declval.hpp>
# include <boost/utility/enable_if.hpp>
# include <boost/utility/result_of.hpp>
#endif // defined(BOOST_ASIO_HAS_STD_TYPE_TRAITS)

namespace boost {
namespace asio {

#if defined(BOOST_ASIO_HAS_STD_TYPE_TRAITS)
using std::add_const;
using std::add_lvalue_reference;
using std::aligned_storage;
using std::alignment_of;
using std::conditional;
using std::decay;
using std::declval;
using std::enable_if;
using std::false_type;
using std::integral_constant;
using std::is_base_of;
using std::is_class;
using std::is_const;
using std::is_constructible;
using std::is_convertible;
using std::is_copy_constructible;
using std::is_destructible;
using std::is_function;
using std::is_move_constructible;
using std::is_nothrow_copy_constructible;
using std::is_nothrow_destructible;
using std::is_object;
using std::is_reference;
using std::is_same;
using std::is_scalar;
using std::remove_cv;
template <typename T>
struct remove_cvref : remove_cv<typename std::remove_reference<T>::type> {};
using std::remove_pointer;
using std::remove_reference;
#if defined(BOOST_ASIO_HAS_STD_INVOKE_RESULT)
template <typename> struct result_of;
template <typename F, typename... Args>
struct result_of<F(Args...)> : std::invoke_result<F, Args...> {};
#else // defined(BOOST_ASIO_HAS_STD_INVOKE_RESULT)
using std::result_of;
#endif // defined(BOOST_ASIO_HAS_STD_INVOKE_RESULT)
using std::true_type;
#else // defined(BOOST_ASIO_HAS_STD_TYPE_TRAITS)
using boost::add_const;
using boost::add_lvalue_reference;
using boost::aligned_storage;
using boost::alignment_of;
template <bool Condition, typename Type = void>
struct enable_if : boost::enable_if_c<Condition, Type> {};
using boost::conditional;
using boost::decay;
using boost::declval;
using boost::false_type;
using boost::integral_constant;
using boost::is_base_of;
using boost::is_class;
using boost::is_const;
using boost::is_constructible;
using boost::is_convertible;
using boost::is_copy_constructible;
using boost::is_destructible;
using boost::is_function;
#if defined(BOOST_ASIO_HAS_MOVE)
template <typename T>
struct is_move_constructible : false_type {};
#else // defined(BOOST_ASIO_HAS_MOVE)
template <typename T>
struct is_move_constructible : is_copy_constructible<T> {};
#endif // defined(BOOST_ASIO_HAS_MOVE)
template <typename T>
struct is_nothrow_copy_constructible : boost::has_nothrow_copy<T> {};
template <typename T>
struct is_nothrow_destructible : boost::has_nothrow_destructor<T> {};
using boost::is_object;
using boost::is_reference;
using boost::is_same;
using boost::is_scalar;
using boost::remove_cv;
template <typename T>
struct remove_cvref : remove_cv<typename boost::remove_reference<T>::type> {};
using boost::remove_pointer;
using boost::remove_reference;
using boost::result_of;
using boost::true_type;
#endif // defined(BOOST_ASIO_HAS_STD_TYPE_TRAITS)

template <typename> struct void_type { typedef void type; };

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename...> struct conjunction : true_type {};
template <typename T> struct conjunction<T> : T {};
template <typename Head, typename... Tail> struct conjunction<Head, Tail...> :
  conditional<Head::value, conjunction<Tail...>, Head>::type {};

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

struct defaulted_constraint
{
  BOOST_ASIO_CONSTEXPR defaulted_constraint() {}
};

template <bool Condition, typename Type = int>
struct constraint : enable_if<Condition, Type> {};

} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_TYPE_TRAITS_HPP

/* type_traits.hpp
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
*/