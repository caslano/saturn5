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
gl/YNKc9ofPwCSMPaWk5sZtGYvRpQSMPF44Ya4xrW1nixHXbKxn0pNeMbTB2lPe5wPZcv/Q90bCi8HfrN6Z8h/zYTfyiDAReVjT9CNzuKB9ffp7kvuuJrayn5hwfMhm2SOzMD+08FqZpvGJc03X0cMYXitxzyzD3MtFujm34kDjN+F0RZVFaup4lmqeAmlfg2sZ4MyErKS5jPxBbmHgba9tRIyaAzECQB5lg1wow8TWd788cNd/XJ4GflqloVVP5+LjAeFMRe7afFXEmRm8jsG/q9CceyOutjMvE92XjN9VxnGN0m92c8SYii4MgcONSNMwZ7fPDYYM/zMCFQ9rCzmc5X/cZxl+KKEkSN8gs0W7uMKQM5TydynEgdkhuWbFriSuYo7QgW/vHZHI8UXh2bmWpuJLVCfRJLeM7TAbE1Mzd2HYycSUzlBjKGHsQ953tFnHgpa4rrmSakjIwTimTYYnCz9M0S6O2uu0+WgqhLUzq9qghx0nDoIjyrF0ObSQu54mGHD90ZfUmCZbJkKMNkqacVz+I9xnfs4rEC51RcmqTXaPPfMGsn9Dz7SAu2+TIK61oUzXzc8nIT26lWRl5rfW8YVYzkXPzB3M5dmHbSeZkrXLMaiZ92H0w73+ZFVtxFNujyoVXIcmaucxkBCKTg9LJw5F1g9MjkfEyVp5ceJGdZb4dia2uNhhr9zkmIxWBk9pZWaSi/eoF1R+Er/U9VhZL2KUbJuDR7wrXN8y5YfKYsddNYy9zXW+kHMiMsde86zFj/+QkThkloTCvplWMc1p/FJQvF0WeF7EdOoKeKJq+w0rKU4o0cIssTwU7aDTjniyy/CUiyYMoimwx8tZbxY/le7pRviB3isQuC2EeOxs+F19E+WYLyVW6aS70IwvdFBgX4tUsHV+4FkSJsRzRdu2uziP2KaMdS8+1ZBtkYovrj6bv8QtMhidsx/YscKnVcr3WjMfzT8YbiDiw8yyKcoOXLdk67zd+CB8Pvp8kURw7YvRzDF13WP5ZJqMQgVvmheO0p29s6A/qdfshRj+Ok9gOSksYz2JqtgXdzuuUD0ZxbiWeG4ihnZq/i34KxZdC9grPjwHPXtdwnfmFPI089H3Hy0Lgad3XvZqXBXRmx3P9QsyDL/iqUukLZeiHtrafMd5MBGXuehH0QxpDfX4Z7OwyUhDkFutSy/gBkxEL180Tz3Z9LgNdNOGwpXPTzR9qzE1uIMd64ovqWGfoP2zQ8B+G6494KJ/z89jL7LwcypCuEOflq+U2cdSP2jrLiydCN4/8IIe9kiwCjEq1dcE80Ph2z6a893Rjx0tTu2KEV9+s3l7I0klFaCVxUeSZqHtsDyepRoCqAzqv72QyHBHHruuVpVPL0EGqTq5truo6X9Jz5RcYbwA6mh/YEoO8aptjpm2h/yRW3zb4X7ECN0s4f52DBbTPVVUoBcXatvAwwx9b7pa257mtcnALVYkxdZnZh/E1O7LdrEzzuFUWDA0uyMK9IJPjC8dOnTB3wqGceiTycbWB/vApP5iayiiws0jA0lh5pcFAZ31b279ZmrFICsf1kjzUPgiljrKhXPFV8WrVSDLb5DOsLgORJFZo+VGqZcA4VjJqc2VlLpIjXD56ouvD5YeZ+33XtR3f13IGdV4wD2RO2f1wPpazJAqC1I4bvGjWhimfj+UZJiMXcR5YjszEMEZgVxtfVB4wVKBRH8cezvto4hdhUKY+ygFmFAZTAc4SrD5exPLjiNyPo9QNHbEiRYDBRc0orDesY8xAlgdfuJ6fOn6cCrMN9MOz+x14XF86woMy0X3ZD1geUuHKwRaXmcvlIDOtkC6u3UyGCwFZZN+EcgxOyeGgRdBOvaE=
*/