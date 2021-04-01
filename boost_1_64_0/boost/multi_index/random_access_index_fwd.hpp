/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_RANDOM_ACCESS_INDEX_FWD_HPP
#define BOOST_MULTI_INDEX_RANDOM_ACCESS_INDEX_FWD_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/multi_index/tag.hpp>

namespace boost{

namespace multi_index{

namespace detail{

template<typename SuperMeta,typename TagList>
class random_access_index;

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator==(
  const random_access_index<SuperMeta1,TagList1>& x,
  const random_access_index<SuperMeta2,TagList2>& y);

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator<(
  const random_access_index<SuperMeta1,TagList1>& x,
  const random_access_index<SuperMeta2,TagList2>& y);

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator!=(
  const random_access_index<SuperMeta1,TagList1>& x,
  const random_access_index<SuperMeta2,TagList2>& y);

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator>(
  const random_access_index<SuperMeta1,TagList1>& x,
  const random_access_index<SuperMeta2,TagList2>& y);

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator>=(
  const random_access_index<SuperMeta1,TagList1>& x,
  const random_access_index<SuperMeta2,TagList2>& y);

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator<=(
  const random_access_index<SuperMeta1,TagList1>& x,
  const random_access_index<SuperMeta2,TagList2>& y);

template<typename SuperMeta,typename TagList>
void swap(
  random_access_index<SuperMeta,TagList>& x,
  random_access_index<SuperMeta,TagList>& y);

} /* namespace multi_index::detail */

/* index specifiers */

template <typename TagList=tag<> >
struct random_access;

} /* namespace multi_index */

} /* namespace boost */

#endif

/* random_access_index_fwd.hpp
qP9uO0WxNKCigu8zLZUxQiCY+pdf0uqxSonNIXKoBsiR59sKSfutcXpdBNa+/+eDYg1Y1nUxA+rJdAQf5IWZjWrCc/URD1VyMOyg0jxk21BWplez6ewr9Jk1XvplskegREjxmwWzekV+TnEQFZjvFjMb39WSc7ah4B+Ly+esP8trY9P7EFNqMcYaxaYiZNZqEwxBbPOHKSFHCgx6auzCKWCbfF/SdXveztEevAr6rjjZ9rQNaL8ngMszEVIZmvvpZvb1Si3i56CZ7qSlYHCK+3xyZyGv9bQ4LFQbKDrBSWnTqujHtOAgZDvPu2sWoe2I86wMsZLdMcl2mM2a+mnUkDwoWXzNw183F6I0P2kv0Lwb64hGDBOxqUoJ1uGEj+sOyGe84Gbixsd/HEjR0EkBMLo/ijTgYRGZZn7JrU8hKVx7ZcduVzbgw/dEtE+raS1fBkGUFlFnL2bjOQF3HsQ6d7Z1t4DZ28T+lYV7UHpw2MuHlmAR1SLOxm5PcYMzIi3t3x7Y6sB1vrdc8+IbL3AOl87CgeJkymHCnZbtqwakmShlB6MpdimGOFyOCw==
*/