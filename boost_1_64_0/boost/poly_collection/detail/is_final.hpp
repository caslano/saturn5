/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_IS_FINAL_HPP
#define BOOST_POLY_COLLECTION_DETAIL_IS_FINAL_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/type_traits/is_final.hpp>
#include <type_traits>

/* technique explained at
 * http://bannalia.blogspot.com/2016/09/compile-time-checking-existence-of.html 
 */

namespace boost{
namespace poly_collection{
namespace detail{
namespace is_final_fallback{

template<typename T> using is_final=boost::is_final<T>;

struct hook{};

}}}}

namespace std{

template<>
struct is_void< ::boost::poly_collection::detail::is_final_fallback::hook>:
  std::false_type
{      
  template<typename T>
  static constexpr bool is_final_f()
  {
    using namespace ::boost::poly_collection::detail::is_final_fallback;
    return is_final<T>::value;
  }
};

} /* namespace std */

namespace boost{

namespace poly_collection{

namespace detail{

template<typename T>
struct is_final:std::integral_constant<
  bool,
  std::is_void<is_final_fallback::hook>::template is_final_f<T>()
>{};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* is_final.hpp
z0t7YctTp0ENsWS0YRWECj/6L/U97uN7yUCe1NI82J8eLZsj9Xx1rGjMoZbaTRU7fvGqViFkl9PvGlw036Iq1S1CCgYI65f49u1lVikwmIzGiRS51m+ie7grR+DL/ZMSJ7cE49kr/FcxNhELiL2MpI1/iG6BlWvLQNUx6TiSf6IRQPRtsiCERhdUMuhZ5YMzYALbxuWva3fzEf1gfyuDXB5AjqVy4RB56SlpO9RqlNohJy/0Jvr1TGeZlLYeogQKZpjDMAhMdxXBYrex+dBlCn+QHxcOLNcrADmqBUW+BfniaEJ5ffuBVeNn2oI6MCcBJnWUUkIiFcqNJ0fNhq4RQIfc70S8RrW9pYK0ELfL14FPmCy4RCPKBQSDfYx3J9aj/uz4EFnug1wpM8rJPeOhHqbmj9vGpVYCUsWJvrR/umG6ZFeRlwJ4+T9VoMSFewVcz3Xrwbzyqa+GahhdWGygEEqrET+5ZDquPee0UjwZVrX/+EjdlpUR+18Ail/1EmRqLldug+To8zh2xvYtBgir+421ObzejHNZWgtovrlc1VcRayT1iNRPsQ5lnw==
*/