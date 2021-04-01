/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_IS_INVOCABLE_HPP
#define BOOST_POLY_COLLECTION_DETAIL_IS_INVOCABLE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <functional>
#include <type_traits>

/* technique explained at
 * http://bannalia.blogspot.com/2016/09/compile-time-checking-existence-of.html 
 */

namespace boost{
namespace poly_collection{
namespace detail{
namespace is_invocable_fallback{

template <typename F,typename... Args>
struct is_invocable:
  std::is_constructible<
    std::function<void(Args...)>,
    std::reference_wrapper<typename std::remove_reference<F>::type>
  >
{};

template <typename R,typename F,typename... Args>
struct is_invocable_r:
  std::is_constructible<
    std::function<R(Args...)>,
    std::reference_wrapper<typename std::remove_reference<F>::type>
  >
{};

struct hook{};

}}}}

namespace std{

template<>
struct is_void< ::boost::poly_collection::detail::is_invocable_fallback::hook>:
  std::false_type
{      
  template<typename F,typename... Args>
  static constexpr bool is_invocable_f()
  {
    using namespace ::boost::poly_collection::detail::is_invocable_fallback;
    return is_invocable<F,Args...>::value;
  }

  template<typename R,typename F,typename... Args>
  static constexpr bool is_invocable_r_f()
  {
    using namespace ::boost::poly_collection::detail::is_invocable_fallback;
    return is_invocable_r<R,F,Args...>::value;
  }
};

} /* namespace std */

namespace boost{

namespace poly_collection{

namespace detail{

template<typename F,typename... Args>
struct is_invocable:std::integral_constant<
  bool,
  std::is_void<is_invocable_fallback::hook>::template
    is_invocable_f<F,Args...>()
>{};

template<typename R,typename F,typename... Args>
struct is_invocable_r:std::integral_constant<
  bool,
  std::is_void<is_invocable_fallback::hook>::template
    is_invocable_r_f<R,F,Args...>()
>{};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* is_invocable.hpp
6IExB32MaQrpnfeEy5Kl6xfSQmZmEjATBQ+xf7myyISNdlbCNd0c9z8l8WL4pE5mHIJWa/SAbJFMPLNvmbC7p3eoUK5daeJ1INqzzQ3rkkGpr0B7+V/Cc2P6W/W1AKjCcSX1mW5E9pNlpKIWIhytb3k9aVTxs2K3xrJZCIgc6eUNu44V1Mb9X5A7fCfYjx2X9P+HUz5ClWJiuXPDPHC+kSIV5FNRNgpAuGjzTRSAIxQRSY8lrrVLcQCGutkyLeLdNd1S1m4/RtZQsY/ELnLwaiGMKYmZhVravok+JJrKwBa6R6REZ0nCn8DRBAiNC6rEq/jPGC7PLiHu9yZbS47yygee+DgtiCO8+KP6EEFcMFgr9hIq+6IT+FbRhvHL2jaQgEpRYGUkdXqzLsF+AXgsQCSKy0vJN1SOfvWKMm7VanwSatcM5BBad+kh4nsfNAVXMWXRyI9/0WgZb63IjXswYvS53KdLErB6YpGs2bQnYVhUEs5Uoq0+pTwnZr8jEysqFG6zZ2MjTJbXqrdQpbOjdrm/6LXZTTuMYIrITjxVdEzPo/IKmwdyHRAawg==
*/