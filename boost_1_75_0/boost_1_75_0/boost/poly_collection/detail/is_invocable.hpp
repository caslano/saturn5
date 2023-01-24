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
3uwktOo6+hba9uDgfd7mKnGVzd2E+/UC69m7F9MYPBDiM8AWjl7jxpTGYp7Q1ceWcnBcMewH9Y00VifOdmfWGwu7cFPpgR9UEjW9k0Q0TI9Clb0lzjTrsJ1rAvNBQsClUiQZoYR5xXa1Y0yd65o4yDyY239RyJpgEDRheVf3oVfuzz4bvzBMvb5Fxl55TL2gCgi+cAuXN9BDpMnnGR5h2I4j2SwbkayHdFKEePR7ksc9h7X2XCGYo3ahdgfrTTsbsMmgA1sDSuUactg1mPUStZedJIwwTYHyog5nxwwjfDLS3zjtojfE9KuWQPyHby5E3C7BwOcrbstfcwDdoLSxRuGKq5W72nr/2zveBGZ1WnGIfnKMV70D+KAPSkGoblTPDMdxqZkShkd8+UyADPoTCYIF+xTDkrvFczH1gtQ0D9vPEIOx1XGPxEHx7giAznjsExfwMhHfdhGBfVPse7CBfWIkKuM2X6GEZJl3pBtrsTgOlxEHS7y+OpRd/HHJzMF8Iq8rKRT1pjU8H5uEii7rAvlinsjKD3oknQf8mpFjJ1uSlcFSjGXq2XNO5CDt9WZTHgfrhX9UQ6STfs9lCIC5nPERfdOs5xSbCltCUZeLPBGp3IS2KUF0JpW6RuWHgwy9UOgJYFSRYl/hhb84eycUeqFZDg8BWZ0yPwrO+/fYUdtVvEgE196SIERsJTb3dR9wJMDL6ncYTzbuJ9X/
*/