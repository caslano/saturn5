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
2VKxbPmjNxFRwIe+NtEJONN89Pl0wGSZLhEiARHpryKRxke2eZnhiHm5Qp4atZEaseFFDY2N2OYqWzzsZWO6L49Q9i/YatJio10p3ar5FjHY8hHoKdXvXBmxTatzuZ7Atv4QEgE1MqlFlnX8MqLWeaVDmtycpUfJHHNzxWOYr3STINq20+82SOvtjICCzDX7v+8u/9m+sFFPv7Ji7qie/4S6wvy6GkoJce8Lgk5Zzd7U+tgz20/JDYGTcwZmCT6fLvfqlWlH0xyVe+i1BjMpPT74NhCcXhUYM7Nn5UNtkCvwwQdk9+Nt2ak6VpXrtqBq3T1SlpwUgdzsnmTftLa62SDJtrpGpqx1WWn3dfbjzDWcf/aU4t02VqXcdo0B91Ltgj99nGp4lJh38b1I+vQH6yPDwDdveX9vYLZJgAMaGbg1Me5cOxifBCWXbGVEWXBVaCeRv18YsvVy+tnF/vW0IBqiVQEhKHuVgkCaHGR1M3+17tHpVQ955I21oLi7bkgaD0Sqxdva0iG1aHR6RJY93cZm0VImepD6CmfkovC//pvO/2JnqfC/sj/V39nfw9XJ9q/cz8vLbeHk5PLF3YbLws7upB3r3UedWwkEpkevylWDiZlZhz7fkoXm+NclE/18HjGe74p831NNmJNL+lIDI/4chfsNo3WRSNLkBaYsBrs5GkaiJCY6+220dNrXQBCyGTr+/Dr2e9Mw0wMc
*/