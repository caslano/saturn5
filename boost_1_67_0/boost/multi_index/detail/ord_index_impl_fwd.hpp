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
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
*/