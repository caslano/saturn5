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
O45pXDPXjjfw+azSdb/AZFoU3WnuzDLmUepXis+1GcYHdbJ+TnDS7dj6nuLDi6b0gc9/wDz/rNJO0O35vf9XvzhK/P7I+UWJl4RVN4vD3K1gjJqLOLVjE+wxtbpRiD9eC8WSPGc+yGXMvF4Z+H6Vh26eUM41H/yGKz8bK8JnrOYpy/06g2fl+WlU9Lq96bGLEvFnuLpyBj/T5dGZ2cX+utfyJL9vcX6dyovLqttN/WSKYoVqoxtJtZDi8cXGp1zVoyFf4IVBXuZ+kty4HldPn2b1yMt8zw8xnmAV4W3S2I96m/Ls721+vmi2LjQY6jJzft2OF+aoxaDw/19+Qge8tAN98Yg4c0ZQB3H1WeyCmvuHG2KwSsyXDQxMrYSQMRZPQ5esJ2B696pf/5umPvq2iG9sSKl1EgOldfuWc7rCeCM9kjB8WuR22ZO31HQclllTCYsBuJVwNOVMw10mnHva07iH34pwjumC23IvT8FhKVP3gIe31hiogFqdUVJijLEy/4fhofSSkqF4K74/vA3DEQhzJ3qs8G+drOsjtyW8tcTIfL9l0tHphA1K5yvtb9+/vcDd1JKg6vPz251ppIyqTFfvYOKWcHFAc5aiMLveHQnvdFlk7/ncaTOcOG/T2M/sIKxUWzbRHYM7C+yN3cpkG/xM4Xk31Xlfvwun62bQ1cr0wBOOuEwtTf/S5P0Q6DOa/jt5f8GKACPpf5Z02kPVLu8jrd91rPsHzbUALM7sDsgtnmNhWHyebaBN3HFgd6MuPlPSoeAeaGLrKFvYpK/9hI/4oy3MMoKCYBPLXPe1zvIUCztY0b7zPE5E4MJx33mT3uQFb1ZiNJDyV1Nw3Ha0ov3n9QONrP6e/hzmQ08YHkfqUyzOyMYa+tLpVijT7vqPtLuoYwQcmcFnVdIdd+poH48+hCbmdsT3cX9ywo+g6zd30M8qn793Ek4fvLwQutzCQsMXs2LzUoHSmX/KfKax/6fuuyDpa5+R/NRrL7PCvqd8Bg/bNkDaPG/iC7zrKdPSTPcFvnZwShqHL/DV/VOwDl/gPfumYaf7Al94/LQ0032Brz5hWprpvsAXNi+HnVDbgZ876VNrHSkMVL96g+0HbB43qX71AhvnPHpblvirL7PxzuO0ZSnHt1Yn8PwIcCxxl147gePHaGPlW3tmeh3QgdRAynp9qLD0WJDrwEaX7cJznLztFPp8oivtuhCSA5u3x8aqX/Wn8p3qf1vFMo0LyTo80qg2P2vXocle+aW+ckpd81IyP9ZTHWWnp8mHzzlC+VtcbgGvz4smy8uOqPQ9gD20H2SCcIcVQJYldp7m/KKbFCGeJMEcBHlYpaOPyr3A2NpHBqHfzaok+3/3keSDCV7kgwmz0418MG/ZUlCnD+ZWRrf9IG9l0ciPUNFvrehuP8nbaLrTR3Mbo3MfzQcR/baMbvs6SvlvxzC2L+PtGY37Mkr6dkV/Bvm6mnVzB0a36+aOmuYs+50YnfuISt47GN2W+86Mxv1HJf0umm6VC+9lY/8G5fB4AvpR/iQv0d9h0e148u/hdP60veUDun1TH1DQN/cBBd19VuHdArRN/Dy/TnSXn+ehW4K2iZ/n9wX9Jv0837QV2Jv086xuBewmfp5XXfTHs/S3dtD3YxzI9ETfzA908TbATPHl/CPRpvlynt8G+k34cu68LXCb+HK+10l/vKLf93Yu+n4lx2VBvwlfz0O3B24TX89PEN329bw70XdvF3S8uNhvrPky3Qeb75i7hZ4hnxvS+9NtdxD06cuDbK/f1ThjfZTBvdW+e3hHgbkpdVCluXgnkeam1EHl6/izep67adVO+y/e2Z3O5et48S5urMvX8b53FdibUk8=
*/