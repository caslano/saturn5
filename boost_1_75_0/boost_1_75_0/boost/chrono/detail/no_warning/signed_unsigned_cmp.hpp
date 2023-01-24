//  is_evenly_divisible_by.hpp  --------------------------------------------------------------//

//  Copyright 2009-2010 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_CHRONO_DETAIL_NO_WARNING_SIGNED_UNSIGNED_CMP_HPP
#define BOOST_CHRONO_DETAIL_NO_WARNING_SIGNED_UNSIGNED_CMP_HPP

//
// We simply cannot include this header on gcc without getting copious warnings of the kind:
//
//../../../boost/chrono/detail/no_warning/signed_unsigned_cmp.hpp:37: warning: comparison between signed and unsigned integer expressions
//
// And yet there is no other reasonable implementation, so we declare this a system header
// to suppress these warnings.
//

#if defined(__GNUC__) && (__GNUC__ >= 4)
#pragma GCC system_header
#elif defined __SUNPRO_CC
#pragma disable_warn
#elif defined _MSC_VER
#pragma warning(push, 1)
#endif

namespace boost {
namespace chrono {
namespace detail {

  template <class T, class U>
  bool lt(T t, U u)
  {
    return t < u;
  }

  template <class T, class U>
  bool gt(T t, U u)
  {
    return t > u;
  }

} // namespace detail
} // namespace detail
} // namespace chrono

#if defined __SUNPRO_CC
#pragma enable_warn
#elif defined _MSC_VER
#pragma warning(pop)
#endif

#endif // BOOST_CHRONO_DETAIL_NO_WARNING_SIGNED_UNSIGNED_CMP_HPP

/* signed_unsigned_cmp.hpp
8zLaUjEtUoxFJOdez8gtFWOZS+z7I7TMXlpmL5aJZPWNl8vsxTLR7Hsy9u6Q0rtDWCycJfeWencIS0Xg56yxBOzL8SqSaD14s5GBkoQ5CIXsbJvuN4Sof0KybdBL6HL4LWq2vBoxf0fmlMlIcHqcpNSly0mKKO3Y7xbsd2P228B+X/mVPs+zZxV7/sqex9jzIHuWsOd29tzEnl+y58fs+R57vsmeL7Enz54u9pzDnrPY81H2fOBXvc4Hv6cS/P5ug4Tfl2T8Bgq4OYgRxy8pYlZTjK9mOLxORslqBYffpFkFumyCBoef15IIGYefDvKFeQmHHwjSwryEw2OCfGFewuGhQVqYl3C4d5Av9Eo43C5IC70SDjcO8oVeCYcvekGvhMOnKMTvVyOWhMMH5TL7NTi8nZY5pAZ3CYfXy2UOaXB4FWJJhYIlFRoczpGwpEKDw7NpSxoqK+HwNLmlcg0Oj6NljtMyxzU4bJPLHNfgcB/s3UmldycAECzv0zU43Fbq3Uk1DidKyElw2NLFyECJoCfeskYQBBxGnL0EOHvT69qrBgxnn66Q97lBJyh6PlhB0WBiBf09lv1OZc9E9hzEnv3Y81b2jGLP9uzZkj2bsKeRPa+eoM+/2fM0e55kz+PseYg997LnDvbczJ5fndDuxyhPMQZzNWUwTZ/KDCZF3KRYcXqie94JiqgnFDDebZQW6QROtwTCG9H7MeMR
*/