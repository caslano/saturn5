/* Copyright 2003-2015 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_ORD_INDEX_IMPL_FWD_HPP
#define BOOST_MULTI_INDEX_DETAIL_ORD_INDEX_IMPL_FWD_HPP

#if defined(_MSC_VER)
#pragma once
#endif

namespace boost{

namespace multi_index{

namespace detail{

template<
  typename KeyFromValue,typename Compare,
  typename SuperMeta,typename TagList,typename Category,typename AugmentPolicy
>
class ordered_index;

template<
  typename KeyFromValue1,typename Compare1,
  typename SuperMeta1,typename TagList1,typename Category1,
  typename AugmentPolicy1,
  typename KeyFromValue2,typename Compare2,
  typename SuperMeta2,typename TagList2,typename Category2,
  typename AugmentPolicy2
>
bool operator==(
  const ordered_index<
    KeyFromValue1,Compare1,SuperMeta1,TagList1,Category1,AugmentPolicy1>& x,
  const ordered_index<
    KeyFromValue2,Compare2,SuperMeta2,TagList2,Category2,AugmentPolicy2>& y);

template<
  typename KeyFromValue1,typename Compare1,
  typename SuperMeta1,typename TagList1,typename Category1,
  typename AugmentPolicy1,
  typename KeyFromValue2,typename Compare2,
  typename SuperMeta2,typename TagList2,typename Category2,
  typename AugmentPolicy2
>
bool operator<(
  const ordered_index<
    KeyFromValue1,Compare1,SuperMeta1,TagList1,Category1,AugmentPolicy1>& x,
  const ordered_index<
    KeyFromValue2,Compare2,SuperMeta2,TagList2,Category2,AugmentPolicy2>& y);

template<
  typename KeyFromValue1,typename Compare1,
  typename SuperMeta1,typename TagList1,typename Category1,
  typename AugmentPolicy1,
  typename KeyFromValue2,typename Compare2,
  typename SuperMeta2,typename TagList2,typename Category2,
  typename AugmentPolicy2
>
bool operator!=(
  const ordered_index<
    KeyFromValue1,Compare1,SuperMeta1,TagList1,Category1,AugmentPolicy1>& x,
  const ordered_index<
    KeyFromValue2,Compare2,SuperMeta2,TagList2,Category2,AugmentPolicy2>& y);

template<
  typename KeyFromValue1,typename Compare1,
  typename SuperMeta1,typename TagList1,typename Category1,
  typename AugmentPolicy1,
  typename KeyFromValue2,typename Compare2,
  typename SuperMeta2,typename TagList2,typename Category2,
  typename AugmentPolicy2
>
bool operator>(
  const ordered_index<
    KeyFromValue1,Compare1,SuperMeta1,TagList1,Category1,AugmentPolicy1>& x,
  const ordered_index<
    KeyFromValue2,Compare2,SuperMeta2,TagList2,Category2,AugmentPolicy2>& y);

template<
  typename KeyFromValue1,typename Compare1,
  typename SuperMeta1,typename TagList1,typename Category1,
  typename AugmentPolicy1,
  typename KeyFromValue2,typename Compare2,
  typename SuperMeta2,typename TagList2,typename Category2,
  typename AugmentPolicy2
>
bool operator>=(
  const ordered_index<
    KeyFromValue1,Compare1,SuperMeta1,TagList1,Category1,AugmentPolicy1>& x,
  const ordered_index<
    KeyFromValue2,Compare2,SuperMeta2,TagList2,Category2,AugmentPolicy2>& y);

template<
  typename KeyFromValue1,typename Compare1,
  typename SuperMeta1,typename TagList1,typename Category1,
  typename AugmentPolicy1,
  typename KeyFromValue2,typename Compare2,
  typename SuperMeta2,typename TagList2,typename Category2,
  typename AugmentPolicy2
>
bool operator<=(
  const ordered_index<
    KeyFromValue1,Compare1,SuperMeta1,TagList1,Category1,AugmentPolicy1>& x,
  const ordered_index<
    KeyFromValue2,Compare2,SuperMeta2,TagList2,Category2,AugmentPolicy2>& y);

template<
  typename KeyFromValue,typename Compare,
  typename SuperMeta,typename TagList,typename Category,typename AugmentPolicy
>
void swap(
  ordered_index<
    KeyFromValue,Compare,SuperMeta,TagList,Category,AugmentPolicy>& x,
  ordered_index<
    KeyFromValue,Compare,SuperMeta,TagList,Category,AugmentPolicy>& y);

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* ord_index_impl_fwd.hpp
C54bJOo5nt4lu2r/L+xiLUUtWrIVj00kos+AZVOT21A/ur5B7LvUrJL5htLzubgVjA++HgXP6eX7LrU23r7n2PrwxuRHAtY1gbbBpNzeFEKWmNj0ibSNJlaaGpxbdypWPokabwNRzCOZTTGfZHbFaiQLUWytZKGK1UoWpth6yRzqMSZZuGJ1kjnV1yPJIhRrkMyljp9kfRRrkixSsWbJ+irWIlk/xbZJFq2+bkrWX33dlGyg
*/