/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_SEQUENCED_INDEX_FWD_HPP
#define BOOST_MULTI_INDEX_SEQUENCED_INDEX_FWD_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/multi_index/tag.hpp>

namespace boost{

namespace multi_index{

namespace detail{

template<typename SuperMeta,typename TagList>
class sequenced_index;

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator==(
  const sequenced_index<SuperMeta1,TagList1>& x,
  const sequenced_index<SuperMeta2,TagList2>& y);

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator<(
  const sequenced_index<SuperMeta1,TagList1>& x,
  const sequenced_index<SuperMeta2,TagList2>& y);

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator!=(
  const sequenced_index<SuperMeta1,TagList1>& x,
  const sequenced_index<SuperMeta2,TagList2>& y);

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator>(
  const sequenced_index<SuperMeta1,TagList1>& x,
  const sequenced_index<SuperMeta2,TagList2>& y);

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator>=(
  const sequenced_index<SuperMeta1,TagList1>& x,
  const sequenced_index<SuperMeta2,TagList2>& y);

template<
  typename SuperMeta1,typename TagList1,
  typename SuperMeta2,typename TagList2
>
bool operator<=(
  const sequenced_index<SuperMeta1,TagList1>& x,
  const sequenced_index<SuperMeta2,TagList2>& y);

template<typename SuperMeta,typename TagList>
void swap(
  sequenced_index<SuperMeta,TagList>& x,
  sequenced_index<SuperMeta,TagList>& y);

} /* namespace multi_index::detail */

/* index specifiers */

template <typename TagList=tag<> >
struct sequenced;

} /* namespace multi_index */

} /* namespace boost */

#endif

/* sequenced_index_fwd.hpp
muDi9TISOWcV4NwvH5LmYLZSs8Mqap77YgrGdob9bHuQ/WLkvarD9y/k4yitaSpYN4ro++G5KtUxqwTmmnVMDloN2SUG0pCLPzXLKrFpZdoNL3rsZxR6witFgPYFY1GLCdcCGRZKXf9uia5Kd5fCGytQx6E6oksMPTpcp8f8vnI4AMItj863x7hL7X3cJb/aY7wVqPdYDuLGbHi2WLnnX5qd3avAq0qCTezeYqEmf2UhWtjzH4cujyCrVVgpcUQohN616MpodzzAlQR9x8M4LSQ08B4hNYu3G7wgnlJjFlU47Yu2cqNMvRGHItILhOIU3iMuKobGFL/4SnqIxrGbOJyt7FxktTifBmrkpbiqq08ji1nCqePnbME1z8HmzP9nIL70DAPebdRbWAOLGShx8lSMccSYPBPebDPcw07mmJQ1XwPewLq57wNaN/MVSwl0LBaOWjDWJhaOigvn1oXawqnXhqsaTkBY8sI6uWMBfUn00goKdkYTES6jbXkXw75wgbGGcnkNwROXLdDW0EOmNQRdjtqHayjVimuo3sJqoox6WkM5C4w1VAYvr4SuymA/FDCtoTKJHvP7NsLBKVhDQ3ENlcEaehHXUCWuoTd5Uk9B5y/CFnM+6c/SiypokRzHRXKKF8lxsUhWmxaJXaJdjNeuOtIDPP/Hub9I6M8evEigUaLeSKyH46ZFckq7eMq0SOCTLjzDKwMG6rdn
*/