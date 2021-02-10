/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_IS_ACCEPTABLE_HPP
#define BOOST_POLY_COLLECTION_DETAIL_IS_ACCEPTABLE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <type_traits>

namespace boost{

namespace poly_collection{

namespace detail{

/* This can be further specialized by Model when the std type trait classes
 * fail to give the right info (as it can happen with class templates whose
 * nominally existing operators do not compile for certain instantiations).
 */

template<typename T,typename Model,typename=void>
struct is_acceptable:std::integral_constant<
  bool,
  Model::template is_implementation<T>::value&&
  std::is_move_constructible<typename std::decay<T>::type>::value&&
  (std::is_move_assignable<typename std::decay<T>::type>::value||
   std::is_nothrow_move_constructible<typename std::decay<T>::type>::value)
>{};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* is_acceptable.hpp
XTK9EovNDIv7xgPzRMwLEwV3quWZku1mmR+Fd+Du5CaQetbzMQrVq56zHvOzrrF6dJnFfR61VlxtcDoHXSbnYEvttxeHjJblxpy8y5iqnJ5JDzmBIdWXm42qfcl0xP37H5iPiYqqCbmVj1bECnEophHVjqhiS0vjoJpUC7k0Vi6N0aVux48xJN0QXzPvpd4IEvWZP6kzrNpJg42yVtwOUT/ElwmV67DQUNLana0RmRY0lNjt9d/4vPN5C6NoJ22ZCV8Di4MxaKwI7dO4k/wDBI/ijq6mvPbkdfOynQkJCJ8oRGaSkmsg6NZ3s/EpyNZylHt9lykhM5jC8jrjIjivFZzXCKfZpzuK6eUHmQX3To5WPUDxtNu7pROHd/235gv8wyeNUP/D9WVl4GbtuCibeQRwqHUYpCgUzNI45Gj3D/sEmkVc19cLoK6tFRG9rw1DR35xfjgOa0CjYNiLQ89y73wLWzBVdKQ4jMksy9VEQzkWipFwn6Qgx2O2H89bhayggzyI5SqBwmmVKM67LO9gr4dWiYq8gSOTuUI8nCtQcLIYPbCCy5SutMsSWwiwPU9CLCiuA/mbnUqpISbTiHvy66UquutWA/V9s71uFvJ/7QpQXAOAFlbBKLXLL+Bapptbmb4v1SsrCKLCLjP1
*/